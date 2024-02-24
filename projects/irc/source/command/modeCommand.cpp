#include "../../include/CommandExecute.hpp"
#include "../../include/utils/Buffer.hpp"
#include "../../include/utils/Message.hpp"
#include "../../include/utils/error.hpp"
#include "../../include/utils/reply.hpp"
#include "../../include/utils/List.hpp"
#include <sstream>

static bool chkNum(std::string const& str) {
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}

static int findNick(cltmap const& cltList, std::string const& tgt) {
	for (cltmap::const_iterator it = cltList.begin(); it !=  cltList.end(); it++) {
		if (it->second->getNick() == tgt)
			return it->first;
	}
	return 0;
}

static void createSetMode(int mode, Channel& chan, std::string& outputMode, std::string& outputValue) {
	std::ostringstream oss;

	outputMode += "+";
	for (int i = 0; i < 5; i++) {
		if (mode & (1 << i)) {
			switch (1 << i) {
				case USER_LIMIT_PER_CHANNEL:
					oss << chan.getUserLimit();
					outputMode += "l";
					outputValue += oss.str() + " ";
					oss.clear();
					break;
				case INVITE_CHANNEL:
					outputMode += "i";
					break;
				case KEY_CHANNEL:
					outputMode += "k";
					outputValue += chan.getKey() + " ";
					break;
				case SAFE_TOPIC:
					outputMode += "t";
					break;
				case SET_CHANOP:
					outputMode += "o";
					outputValue += chan.getChanOp()->getNick() + " ";
					break;
			}
		}
	}
	if (outputValue != "" && outputValue[outputValue.size() - 1] == ' ') {
		outputValue = outputValue.substr(0, outputValue.size() - 1);
	}
}

void CommandExecute::mode(Client& client, std::string const& serverHost) {
	mesvec const& message = Message::getMessage();
	chlmap::iterator it;
	std::string successMode = "";
	std::string successValue = "";
	std::string supportMode = "itkol";
	std::string last = "";
	std::ostringstream oss;
	bool flag = true;
	int set[5];
	size_t val = 3;
	int fd;
	chlmap& chlList = List::getChannelList();

	if (message.size() == 2 && (it = chlList.find(message[1])) != chlList.end()) {
		oss << it->second->getTime();
		createSetMode(it->second->getMode(), *it->second, successMode, successValue);
		Buffer::sendMessage(client.getClientFd(), reply::RPL_CHANNELMODEIS(serverHost, client.getNick(), message[1], successMode, successValue));
		Buffer::sendMessage(client.getClientFd(), reply::RPL_CREATIONTIME(serverHost, client.getNick(), message[1], oss.str()));
	}
	else if (message.size() < 3)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "MODE"));
	else if ((it = chlList.find(message[1])) == chlList.end())
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOSUCHCHANNEL(serverHost, client.getNick(), message[1]));
	else if (chlList[message[1]]->getChanOp() == NULL || chlList[message[1]]->getChanOp()->getClientFd() != client.getClientFd())
		Buffer::sendMessage(client.getClientFd(), error::ERR_CHANOPRIVSNEEDED(serverHost, client.getNick(), message[1]));
	else {
		for (size_t i = 0; i < message[2].size(); i++) {
			if (val == message.size() - 1)
				last = ":";
			if (message[2][i] == '+' || message[2][i] == '-') {
				if (message[2][i] == '+') {
					successMode += "+";
					flag = true;
					for (int j = 0; j < 5; j++)
						set[j] = (1 << j);
				} else {
					successMode += "-";
					flag = false;
					for (int k = 0; k < 5; k++)
						set[k] = ~(1 << k);
				}
				continue;
			}
			if (supportMode.find(message[2][i]) != std::string::npos) {
				switch (message[2][i]) {
					case 'l':
						if (flag == true && (val >= message.size() || !chkNum(message[val])))
							Buffer::sendMessage(client.getClientFd(),
								error::ERR_INVALIDMODEPARAM(serverHost, client.getNick(), message[1], message[2][i], "You must specify a parameter. Syntax: <limit>"));
						else {
							successMode += "l";
							it->second->setMode(set[0], flag);
							if (flag == true) {
								successValue += last + message[val] + " ";
								it->second->setUserLimit(atoi(message[val].c_str()));
								val++;
							}
							else
								it->second->setUserLimit(0);
						}
						break;
					case 'i':
						successMode += "i";
						it->second->setMode(set[1], flag);
						break;
					case 'k':
						if (val >= message.size() || message[val] == "")
							Buffer::sendMessage(client.getClientFd(),
								error::ERR_INVALIDMODEPARAM(serverHost, client.getNick(), message[1], message[2][i], "You must specify a parameter. Syntax: <key>"));
						else if ((flag == false && (it->second->getMode() & KEY_CHANNEL) && message[val] != it->second->getKey()))
							Buffer::sendMessage(client.getClientFd(),
								error::ERR_INVALIDMODEPARAM(serverHost, client.getNick(), it->second->getChName(), 'k', "You must specify a parameter for the key mode. Syntax: <key>."));
						else {
							successMode += "k";
							it->second->setMode(set[2], flag);
							if (flag == true) {
								successValue += last + message[val] + " ";
								it->second->setKey(message[val]);
							}
							else
								it->second->setKey("");
						}
						val++;
						break;
					case 't':
						successMode += "t";
						it->second->setMode(set[3], flag);
						break;
					case 'o':
						if (flag == true && (val >= message.size() || message[val] == ""))
							Buffer::sendMessage(client.getClientFd(),
								error::ERR_INVALIDMODEPARAM(serverHost, client.getNick(), message[1], message[2][i], "You must specify a parameter. Syntax: <nick>"));
						else if (flag == true && !(fd = findNick(it->second->getUserList(), message[val])))
							Buffer::sendMessage(client.getClientFd(), error::ERR_NOSUCHNICK(serverHost, message[val]));
						else {
							successMode += "o";
							it->second->setMode(set[4], flag);
							if (flag == true) {
								successValue += last + message[val] + " ";
								it->second->setChanOp(it->second->getUserList().find(fd)->second);
								val++;
							}
						}
						break;
				}
			} else {
				Buffer::sendMessage(client.getClientFd(), error::ERR_UNKNOWNMODE(serverHost, client.getNick(), message[2][i]));
			}
		}
	}
	if (message.size() != 2 && successMode != "") {
		cltmap const& userList = it->second->getUserList();
		if (successValue != "" && successValue[successValue.size() - 1] == ' ')
			successValue = successValue.substr(0, successValue.size() - 1);
		for (cltmap::const_iterator iter = userList.begin(); iter != userList.end(); iter++)
			Buffer::sendMessage(iter->second->getClientFd(), reply::RPL_SUCCESSMODE(client.getNick(), client.getUser(), client.getHost(), message[1], successMode, successValue));
	}
}
