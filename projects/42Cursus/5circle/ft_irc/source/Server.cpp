#include "../include/Server.hpp"
#include "../include/utils/List.hpp"
#include <fcntl.h>
#include <stdexcept>
#include <cstdlib>
#include <signal.h>
#include <netdb.h>

Server::Server(std::string port, std::string password) : opName("ircserv"), opPassword("ircserv"), op(NULL) {
	char* pointer;
	long strictPort;
	char hostnameBuf[1024];
	struct hostent* hostStruct;

	strictPort = std::strtol(port.c_str(), &pointer, 10);
	if (*pointer != 0 || strictPort <= 1024 || strictPort > 65535)
		throw std::runtime_error("Error : port is wrong");
	if (chkForbiddenChar(password, ":\r\n\0"))
		throw std::runtime_error("Error : password is wrong");
	this->password = password;
	this->port = static_cast<int>(strictPort);

	if (gethostname(hostnameBuf, sizeof(hostnameBuf)) == -1)
		this->ip = "127.0.0.1";
	else {
		if (!(hostStruct = gethostbyname(hostnameBuf)))
			this->ip = "127.0.0.1";
		else
			this->ip = inet_ntoa(*((struct in_addr*)hostStruct->h_addr_list[0]));
	}
	this->host = "irc.local.net";

	if ((this->kq = kqueue()) == -1)
		throw std::runtime_error("Error : kqueue error!");
}

Server::~Server() {
	List::clearClientList();
	List::clearChannelList();
	close(kq);
}

void Server::init() {
	int yes = 1;

	this->servSock = socket(PF_INET, SOCK_STREAM, 0);

	if (servSock == -1)
		throw std::runtime_error("Error : server socket is wrong");

	memset(&this->servAddr, 0, sizeof(this->servAddr));
	this->servAddr.sin_family = AF_INET;
	this->servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->servAddr.sin_port = htons(this->port);

	pushEvents(this->newEventFds, this->servSock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

	setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	if (bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1)
		throw std::runtime_error("Error : bind");
	if (listen(servSock, CONNECT) == -1)
		throw std::runtime_error("Error : listen");
	
	fcntl(servSock, F_SETFL, O_NONBLOCK);

	running = true;
	this->startTime = getCurTime();
}

void Server::loop() {
	int new_events;
	struct kevent eventList[EVENT_LIMIT];

	Print::PrintLineWithColor("[" + getStringTime(getCurTime()) + "] server start!", BLUE);

	while (running) {
		new_events = kevent(this->kq, &this->newEventFds[0], this->newEventFds.size(), eventList, EVENT_LIMIT, NULL);

		this->newEventFds.clear();
	
		for (int i = 0; i < new_events; i++) {
			if (eventList[i].flags & EV_ERROR) {
				if (eventList[i].ident == static_cast<uintptr_t>(this->servSock)) {
					running = false;
					break;
				}
				else {
					std::string tmp = "Quit :Closed\r\n";
					Message::parsMessage(tmp);
					CommandExecute::quit(List::findClient(eventList[i].ident));
					delClient(eventList[i].ident);
				}
			} else if (eventList[i].flags & EVFILT_READ) {
				if (eventList[i].ident == static_cast<uintptr_t>(this->servSock)) {
					addClient(eventList[i].ident);
				}
				else if (List::existClient(eventList[i].ident)) {
					chkReadMessage(eventList[i].ident, eventList[i].data);
				}
			} else  if (eventList[i].flags & EVFILT_WRITE) {
				if (List::existClient(eventList[i].ident))
					chkSendMessage(eventList[i].ident);
			}
		}
		monitoring();
	}
}

void Server::pushEvents(kquvec& list, uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void* udata) {
	struct kevent tmp;

	EV_SET(&tmp, ident, filter, flags, fflags, data, udata);
	list.push_back(tmp);
}

void Server::addClient(int fd) {
	int clntSock;
	struct sockaddr_in clntAdr;
	socklen_t clntSz;

	clntSz = sizeof(clntAdr);
	if ((clntSock = accept(fd, (struct sockaddr*)&clntAdr, &clntSz)) == -1)
		throw std::runtime_error("Error : accept!()");
	pushEvents(this->newEventFds, clntSock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	pushEvents(this->newEventFds, clntSock, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	List::addClientList(clntSock, clntAdr.sin_addr);
	Buffer::resetReadBuf(clntSock);
	Buffer::resetSendBuf(clntSock);
	fcntl(clntSock, F_SETFL, O_NONBLOCK);

	Print::PrintComplexLineWithColor("[" + getStringTime(time(NULL)) + "] " + "Connected Client : ", clntSock, GREEN);
}

void Server::delClient(int fd) {

	if (this->op == &List::findClient(fd))
		this->op = NULL;
	List::delClientList(fd);
	Buffer::eraseReadBuf(fd);
	Buffer::eraseSendBuf(fd);
	Print::PrintComplexLineWithColor("[" + getStringTime(time(NULL)) + "] " + "Disconnected Client : ", fd, RED);
}

void Server::monitoring() {
	time_t cur = time(NULL);
	std::vector<int> deleteList;
	std::string timeout = "Quit :timeout\r\n";
	cltmap& cltList = List::getClientList();

	Message::parsMessage(timeout);
	for (cltmap::const_iterator it = cltList.begin(); it != cltList.end(); it++) {
		if (cur - it->second->getTime() > 120)
			deleteList.push_back(it->second->getClientFd());
	}
	for (size_t i = 0; i < deleteList.size(); i++) {
		CommandExecute::quit(*cltList[deleteList[i]]);
		delClient(deleteList[i]);
	}
}

void Server::chkReadMessage(int fd, intptr_t data) {
	std::string buffer;
	std::string message;
	int byte = 0;
	size_t size = 0;
	int cut;

	byte = Buffer::readMessage(fd, data);

	if (byte == -1)
		return ;
	if (byte == 0)
		return delClient(fd);

	List::findClient(fd).setTime();
	buffer = Buffer::getReadBuf(fd);
	Buffer::resetReadBuf(fd);
	while (1) {
		if ((size = buffer.find("\r\n")) != std::string::npos) {
			cut = size + 2;
		} else if ((size = buffer.find("\r")) != std::string::npos
			|| (size = buffer.find("\n")) != std::string::npos) {
			cut = size + 1;
		} else {
			break;
		}

		message = "";
		message += buffer.substr(0, cut);
		buffer = buffer.substr(cut, buffer.size());
		if (message.size() > 512) {
			Buffer::sendMessage(fd, error::ERR_INPUTTOOLONG(this->getHost()));
			continue;
		}
		if (Message::parsMessage(message)) {
			runCommand(fd);
		}
	}
	Buffer::setReadBuf(std::make_pair(fd, buffer));
}

void Server::chkSendMessage(int fd) {
	Buffer::sendMessage(fd);
}

void Server::runCommand(int fd) {
	bool killFlag;
	int killFd;
	Client& tgt = List::findClient(fd);

	switch (CommandExecute::chkCommand(tgt.getPassConnect())) {
		case IS_NOT_ORDER:
			Buffer::sendMessage(fd, error::ERR_UNKNOWNCOMMAND(this->host, (Message::getMessage())[0]));
			break;
		case IS_PASS:
			CommandExecute::pass(tgt, this->password, this->host);
			break;
		case IS_NICK:
			CommandExecute::nick(tgt, this->host);
			break;
		case IS_USER:
			CommandExecute::user(tgt, this->host, this->ip, this->startTime);
			break;
		case IS_NOT_LOGIN:
			Buffer::sendMessage(fd, error::ERR_NOTREGISTERED(this->host, "You input pass and nick, before It enroll User"));
			break;
		case IS_PING:
			CommandExecute::ping(tgt, this->host);
			break;
		case IS_PONG:
			List::findClient(fd).setTime();
			break;
		case IS_MODE:
			CommandExecute::mode(tgt, this->host);
			break;
		case IS_JOIN:
			CommandExecute::join(tgt, this->host);
			break;
		case IS_PART:
			CommandExecute::part(tgt, this->host);
			break;
		case IS_KICK:
			CommandExecute::kick(tgt, this->host);
			break;
		case IS_INVITE:
			CommandExecute::invite(tgt, this->host);
			break;
		case IS_TOPIC:
			CommandExecute::topic(tgt, this->host);
			break;
		case IS_PRIVMSG:
			CommandExecute::privmsg(tgt, this->host);
			break;
		case IS_NOTICE:
			CommandExecute::notice(tgt);
			break;
		case IS_QUIT:
			CommandExecute::quit(tgt);
			this->delClient(fd);
			break;
		case IS_OPER:
			if (CommandExecute::oper(tgt, this->opName, this->opPassword, this->host, this->op != NULL ? true : false))
				this->op = &tgt;
			break;
		case IS_KILL:
			if (this->op == NULL || fd != this->op->getClientFd())
				killFlag = false;
			else
				killFlag = true;
			if ((killFd = CommandExecute::kill(tgt, this->host, killFlag))) {
				CommandExecute::quit(List::findClient(killFd));
				delClient(killFd);
			}
			break;
	};
}

int const& Server::getServerSocket() const {
	return this->servSock;
}

std::string const& Server::getHost() const {
	return this->host;
}

struct sockaddr_in const& Server::getServAddr() const {
	return this->servAddr;
}

int const& Server::getPort() const {
	return this->port;
}

std::string const& Server::getPassword() const {
	return this->password;
}

Client& Server::getOp() const {
	return *this->op;
}

time_t const& Server::getServStartTime() const {
	return this->startTime;
}
