#include "../../include/CommandExecute.hpp"
#include "../../include/utils/Buffer.hpp"
#include "../../include/utils/Message.hpp"
#include "../../include/utils/error.hpp"
#include "../../include/utils/reply.hpp"
#include "../../include/utils/List.hpp"
#include <iostream>
#include <sstream>

static int findNick(cltmap cltList, std::string const& tgt) {
	for (cltmap::const_iterator it = cltList.begin(); it != cltList.end(); it++) {
		if (it->second->getNick() == tgt)
			return it->first;
	}
	return 0;
}

void CommandExecute::privmsg(Client& client, std::string const& serverHost) {
	mesvec const& message = Message::getMessage();
	int fd;
	std::string tgtStr;
	std::string zipPrefix;
	std::istringstream str;
	size_t chanPrefix;
	Channel* chan;

	if (message.size() == 1)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NORECIPIENT(serverHost, client.getNick(), "PRIVMSG"));
	else if (message.size() == 2)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOTEXTTOSEND(serverHost, client.getNick()));
	else {
		str.str(message[1]);
		while (std::getline(str, tgtStr, ',')) {
			zipPrefix = "";
			chanPrefix = 0;
			if ((chanPrefix = tgtStr.find('#')) != std::string::npos) {
				zipPrefix = tgtStr.substr(0, chanPrefix);
				if (zipPrefix.size() == 1 && zipPrefix[0] == '@')
					tgtStr.substr(1, tgtStr.size());
				if (!List::existChannel(tgtStr))
					Buffer::sendMessage(client.getClientFd(), error::ERR_NOSUCHCHANNEL(serverHost, client.getNick(), tgtStr));
				else if (zipPrefix[0] == '@') {
					if ((chan = &List::findChannel(tgtStr))->getChanOp() == NULL
						|| chan->getChanOp()->getNick() != tgtStr)
						Buffer::sendMessage(client.getClientFd(), error::ERR_NOSUCHNICK(serverHost, client.getNick()));
					else if (chan->getUserList().find(client.getClientFd()) == chan->getUserList().end())
						Buffer::sendMessage(client.getClientFd(), error::ERR_CANNOTSENDTOCHAN(serverHost, client.getNick(), chan->getChName()));
					else
						Buffer::sendMessage(chan->getChanOp()->getClientFd(), message[2]);
				}
				else {
					chan = &List::findChannel(tgtStr);
					cltmap::const_iterator iter;
					cltmap const& userList = chan->getUserList();
				
					if (!findNick(chan->getUserList(), client.getNick()))
						Buffer::sendMessage(client.getClientFd(), error::ERR_CANNOTSENDTOCHAN(serverHost, client.getNick(), chan->getChName()));
					else {
						for (iter = userList.begin(); iter != userList.end(); iter++)
							if (iter->second->getNick() != client.getNick())
								Buffer::sendMessage(iter->second->getClientFd(), reply::RPL_SUCCESSPRIVMSG(client.getNick(), client.getUser(), client.getHost(), tgtStr, message[2]));
					}
				}
			}
			else {
				if (!(fd = findNick(List::getClientList(), tgtStr)))
					error::ERR_NOSUCHNICK(serverHost, tgtStr);
				else
					Buffer::sendMessage(fd, reply::RPL_SUCCESSPRIVMSG(client.getNick(), client.getUser(), client.getHost(), tgtStr, message[2]));
			}
		}
	}
}

void CommandExecute::notice(Client& client) {
	mesvec const& message = Message::getMessage();
	int fd;
	std::string tgtStr;
	std::string zipPrefix;
	std::istringstream str;
	size_t chanPrefix;
	Channel *chan;

	if (message.size() > 2) {
		str.str(message[1]);
		while (std::getline(str, tgtStr, ',')) {
			zipPrefix = "";
			chanPrefix = 0;
			if ((chanPrefix = tgtStr.find('#')) != std::string::npos) {
				zipPrefix = tgtStr.substr(0, chanPrefix);
				if (zipPrefix.size() == 1 && zipPrefix[0] == '@')
					tgtStr.substr(1, tgtStr.size());
				if (!List::existChannel(tgtStr))
					;
				else if (zipPrefix[0] == '@') {
					if ((chan = &List::findChannel(tgtStr))->getChanOp() == NULL
						|| chan->getChanOp()->getNick() != tgtStr
						|| chan->getUserList().find(client.getClientFd()) == chan->getUserList().end())
						;
					else
						Buffer::sendMessage(chan->getChanOp()->getClientFd(), message[2]);
				}
				else {
					chan = &List::findChannel(tgtStr);
					cltmap::const_iterator iter;
					cltmap const& userList = chan->getUserList();
				
					if (!findNick(chan->getUserList(), client.getNick()))
						;
					else {
						for (iter = userList.begin(); iter != userList.end(); iter++)
							if (iter->second->getNick() != client.getNick())
								Buffer::sendMessage(iter->second->getClientFd(), reply::RPL_SUCCESSNOTICE(client.getNick(), client.getUser(), client.getHost(), tgtStr, message[2]));
					}
				}
			}
			else {
				if (!(fd = findNick(List::getClientList(), tgtStr)))
					;
				else
					Buffer::sendMessage(fd, reply::RPL_SUCCESSNOTICE(client.getNick(), client.getUser(), client.getHost(), tgtStr, message[2]));
			}
		}
	}
}
