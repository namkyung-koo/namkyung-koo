#include "../../include/CommandExecute.hpp"
#include "../../include/utils/Message.hpp"
#include "../../include/utils/Buffer.hpp"
#include "../../include/utils/reply.hpp"
#include "../../include/utils/error.hpp"
#include "../../include/utils/List.hpp"

static bool duplicate_nick(std::string const& nick) {
	cltmap& cltList = List::getClientList();

	for (cltmap::iterator it = cltList.begin(); it != cltList.end(); it++) {
		if (cltList[it->first]->getNick() == nick)
			return true;
	}
	return false;
}

static void successNickChange(Client& client, std::string changeNick) {
	cltmap& cltList = List::getClientList();

	for (cltmap::iterator it = cltList.begin(); it != cltList.end(); it++) {
		if (it->second != &client)
			Buffer::sendMessage(it->second->getClientFd(), reply::RPL_SUCCESSNICK(client.getNick(), client.getUser(), client.getHost(), changeNick));
	}
}

void CommandExecute::motd(Client& client, std::string const& serverHost) {
	Buffer::sendMessage(client.getClientFd(), reply::RPL_MOTDSTART(serverHost, client.getNick()));
	Buffer::sendMessage(client.getClientFd(), reply::RPL_MOTD(serverHost, client.getNick(), "Hello! This is FT_IRC!"));
	Buffer::sendMessage(client.getClientFd(), reply::RPL_ENDOFMOTD(serverHost, client.getNick()));
}

void CommandExecute::pass(Client& client, std::string const& password, std::string const& serverHost) {
	mesvec const& message = Message::getMessage();

	if (message.size() != 2) {
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "PASS"));
	} else if (client.getPassConnect() & IS_PASS) {
		Buffer::sendMessage(client.getClientFd(), error::ERR_ALREADYREGISTERED(serverHost));
	} else if (message[1] != password) {
		Buffer::sendMessage(client.getClientFd(), error::ERR_PASSWDMISMATCH(serverHost));
	} else {
		client.setPassConnect(IS_PASS);
	}
}

void CommandExecute::nick(Client& client, std::string const& serverHost) {
	mesvec const& message = Message::getMessage();

	if (message.size() != 2)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NONICKNAMEGIVEN(serverHost));
	else if (duplicate_nick(message[1]))
		Buffer::sendMessage(client.getClientFd(), error::ERR_NICKNAMEINUSE(serverHost, message[1]));
	else if (chkForbiddenChar(message[1], "#:") || std::isdigit(message[1][0]) || message[1] == "" || message[1].size() > 9)
		Buffer::sendMessage(client.getClientFd(), error::ERR_ERRONEUSNICKNAME(serverHost, message[1]));
	else {
		client.setPassConnect(IS_NICK);
		if (client.getNick() != "") {
			successNickChange(client, message[1]);
		}
		client.setNick(message[1]);
	}
}

void CommandExecute::user(Client& client, std::string const& serverHost, std::string const& serverIp, time_t const& serverStartTime) {
	mesvec const& message = Message::getMessage();

	if (message.size() != 5)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "USER"));
	else if (client.getPassConnect() & IS_USER)
		Buffer::sendMessage(client.getClientFd(), error::ERR_ALREADYREGISTERED(serverHost));
	else if (!(client.getPassConnect() & IS_PASS))
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOTREGISTERED(serverHost, "You input pass, before It enroll User"));
	else if (!(client.getPassConnect() & IS_NICK))
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOTREGISTERED(serverHost, "You input nick, before It enroll User"));	
	else {
		client.setPassConnect(IS_USER);
		client.setUser(message[1]);
		client.setHost(inet_ntoa(client.getAddr()));
		client.setServ(serverIp);
		if (message[4][0] == ':')
			client.setReal(message[4].substr(1, message[4].size()));
		else
			client.setReal(message[4]);
		if ((client.getPassConnect() & IS_LOGIN) == IS_LOGIN) {
			time_t serv_time = serverStartTime;
			Buffer::sendMessage(client.getClientFd(), reply::RPL_WELCOME(serverHost, client.getNick(), client.getUser(), client.getHost()));
			Buffer::sendMessage(client.getClientFd(), reply::RPL_YOURHOST(serverHost, client.getNick(), "1.0"));
			Buffer::sendMessage(client.getClientFd(), reply::RPL_CREATED(serverHost, client.getNick(), getStringTime(serv_time)));
			Buffer::sendMessage(client.getClientFd(), reply::RPL_MYINFO(serverHost, client.getNick(), "ircserv 1.0", "x", "itkol"));
			Buffer::sendMessage(client.getClientFd(), reply::RPL_ISUPPORT(serverHost, client.getNick()));
			CommandExecute::motd(client, serverHost);
		}
	}
}
