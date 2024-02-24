#include "../../include/CommandExecute.hpp"
#include "../../include/utils/Message.hpp"
#include "../../include/utils/Buffer.hpp"
#include "../../include/utils/reply.hpp"
#include "../../include/utils/error.hpp"
#include "../../include/utils/List.hpp"
#include <sstream>

static bool isChanName(std::string const& chanName) {
	if (chanName.size() < 2)
		return false;
	if (chanName[0] == '#')
		return true;
	return false;
}

static int findNick(cltmap const& cltList, std::string const& tgt) {
	for (cltmap::const_iterator it = cltList.begin(); it !=  cltList.end(); it++) {
		if (it->second->getNick() == tgt)
			return it->first;
	}
	return 0;
}

void CommandExecute::join(Client& client, std::string const& serverHost) {
	std::istringstream chan;
	std::istringstream key;
	std::string chanStr = "";
	std::string keyStr = "";
	mesvec const& message = Message::getMessage();
	Channel* channel;

	if (message.size() < 2 || message.size() > 3)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "JOIN"));
	else {
		chan.str(message[1]);
		if (message.size() == 3)
			key.str(message[2]);
		while (std::getline(chan, chanStr, ',')) {
			if (message.size() == 3)
				std::getline(key, keyStr, ',');
			if (!isChanName(chanStr) || chanStr.size() > 200) {
				Buffer::sendMessage(client.getClientFd(), error::ERR_BADCHANMASK(serverHost, client.getNick(), chanStr));
				continue;
			}
			if (!List::existChannel(chanStr))
				List::addChannelList(chanStr, &client);
			else {
				if (List::findChannel(chanStr).getUserList().size() == 0) {
					List::delChannelList(chanStr);
					List::addChannelList(chanStr, &client);
					if (channel->getChanOp() == NULL)
						channel->setChanOp(&client);
				}
			}
			channel = &List::findChannel(chanStr);
			switch (client.joinChannel(&List::findChannel(chanStr), keyStr)) {
				case TOOMANYCHANNELS:
					Buffer::sendMessage(client.getClientFd(), error::ERR_TOOMANYCHANNELS(serverHost, client.getNick(), chanStr));
					break;
				case CHANNELISFULL:
					Buffer::sendMessage(client.getClientFd(), error::ERR_CHANNELISFULL(serverHost, client.getNick(), chanStr));
					break;
				case INVITEONLYCHAN:
					Buffer::sendMessage(client.getClientFd(), error::ERR_INVITEONLYCHAN(serverHost, client.getNick(), chanStr));
					break;
				case BADCHANNELKEY:
					Buffer::sendMessage(client.getClientFd(), error::ERR_BADCHANNELKEY(serverHost, client.getNick(), chanStr));
					break;
				case IS_SUCCESS:
					channel->delInviteList(&client);
					Buffer::sendMessage(client.getClientFd(), reply::RPL_SUCCESSJOIN(client.getNick(), client.getUser(), client.getHost(), chanStr));
					if (channel->getTopic() != "")
						Buffer::sendMessage(client.getClientFd(), reply::RPL_TOPIC(serverHost, client.getNick(), chanStr, channel->getTopic()));
					Buffer::sendMessage(client.getClientFd(), reply::RPL_NAMREPLY(serverHost, client.getNick(), chanStr, channel->getStrUserList()));
					Buffer::sendMessage(client.getClientFd(), reply::RPL_ENDOFNAMES(serverHost, client.getNick(), chanStr));
					for (cltmap::const_iterator iter = channel->getUserList().begin(); iter != channel->getUserList().end(); iter++)
						if (iter->second != &client)
							Buffer::sendMessage(iter->second->getClientFd(), reply::RPL_SUCCESSJOIN(client.getNick(), client.getUser(), client.getHost(), chanStr));
					break;
			}
			chanStr = "";
			keyStr = "";
		}
	}
}

void CommandExecute::part(Client& client, std::string const& serverHost) {
	mesvec const& message = Message::getMessage();
	std::string chanStr = "";
	std::string reason = "";
	std::istringstream str;
	cltmap userList;
	Channel* chan;
	cltmap::const_iterator it;

	if (message.size() < 2 || message.size() > 3)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "PART"));
	else {
		str.str(message[1]);
		while (std::getline(str, chanStr, ',')) {
			if (List::existChannel(chanStr))
				chan = &List::findChannel(chanStr);
			else
				chan = NULL;
			if (chan == NULL)
				Buffer::sendMessage(client.getClientFd(), error::ERR_NOSUCHCHANNEL(serverHost, client.getNick(), chanStr));
			else if (chan->getUserList().find(client.getClientFd()) == chan->getUserList().end())
				Buffer::sendMessage(client.getClientFd(), error::ERR_NOTONCHANNEL(serverHost, client.getNick(), chan->getChName()));
			else {
				userList = chan->getUserList();
				if (chan->getChanOp() != NULL && chan->getChanOp()->getClientFd() == client.getClientFd())
					chan->setChanOp(NULL);
				for (it = userList.begin(); it != userList.end(); it++) {
					if (message.size() == 3)
						Buffer::sendMessage(it->second->getClientFd(), reply::RPL_SUCCESSPART(client.getNick(), client.getUser(), client.getHost(), chan->getChName(), message[2]));
					else
						Buffer::sendMessage(it->second->getClientFd(), reply::RPL_SUCCESSPART(client.getNick(), client.getUser(), client.getHost(), chan->getChName()));
				}
				chan->delClientList(&client);
				if (chan->getUserList().size() == 0)
					List::delChannelList(chan->getChName());
			}
		}
	}
}

void CommandExecute::kick(Client& client, std::string const& serverHost) {
	mesvec const& message = Message::getMessage();
	std::string reason = "";
	std::string userStr = "";
	std::istringstream str;
	cltmap::const_iterator it;
	int tgtFd = 0;
	cltmap userList;
	Channel* chan;

	if (message.size() < 3 || message.size() > 4)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "KICK"));
	else if (!List::existChannel(message[1]))
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOSUCHCHANNEL(serverHost, client.getNick(), message[1]));
	else if ((chan = &List::findChannel(message[1]))->getChanOp() == NULL || chan->getChanOp()->getClientFd() != client.getClientFd())
		Buffer::sendMessage(client.getClientFd(), error::ERR_CHANOPRIVSNEEDED(serverHost, client.getNick(), message[1]));
	else {
		str.str(message[2]);

		while (std::getline(str, userStr, ',')) {
			userList = chan->getUserList();
			if ((tgtFd = findNick(userList, userStr)) == 0)
				Buffer::sendMessage(client.getClientFd(), error::ERR_USERNOTINCHANNEL(serverHost, client.getNick(), userStr, chan->getChName()));
			else {
				for (it = userList.begin(); it != userList.end(); it++) {
					if (message.size() == 4)
						Buffer::sendMessage(it->second->getClientFd(), reply::RPL_SUCCESSKICK(client.getNick(), client.getUser(), client.getHost(), message[1], userStr, message[3]));
					else
						Buffer::sendMessage(it->second->getClientFd(), reply::RPL_SUCCESSKICK(client.getNick(), client.getUser(), client.getHost(), message[1], userStr));
				}
					
				chan->delClientList(userList.find(tgtFd)->second);
			}
		}
	}
}

void CommandExecute::invite(Client& client, std::string const& serverHost) {
	mesvec const& message = Message::getMessage();
	cltmap userList;
	Channel* chan;
	int tgtFd;

	if (message.size() != 3)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "INVITE"));
	else if (!List::existChannel(message[2]))
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOSUCHCHANNEL(serverHost, client.getNick(), message[2]));
	else if ((userList = (chan = &List::findChannel(message[2]))->getUserList()).find(client.getClientFd()) == userList.end())
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOTONCHANNEL(serverHost, client.getNick(), message[2]));
	else if (chan->getMode() & INVITE_CHANNEL
				&& (chan->getChanOp() == NULL || chan->getChanOp()->getClientFd() != client.getClientFd()))
		Buffer::sendMessage(client.getClientFd(), error::ERR_CHANOPRIVSNEEDED(serverHost, client.getNick(), message[2]));
	else if (findNick(userList, message[1]))
		Buffer::sendMessage(client.getClientFd(), error::ERR_USERONCHANNEL(serverHost, client.getNick(), message[1], message[2]));
	else {
		if (!(tgtFd = findNick(List::getClientList(), message[1])))
			return ;
		else {
			chan->addInviteList(&List::findClient(tgtFd));
			Buffer::sendMessage(client.getClientFd(), reply::RPL_INVITING(serverHost, client.getNick(), message[2], message[1]));
			Buffer::sendMessage(tgtFd, reply::RPL_SUCCESSINVITING(client.getNick(), client.getUser(), client.getHost(), message[2], message[1]));
		}
	}
}

void CommandExecute::topic(Client& client, std::string const& serverHost) {
	mesvec const& message = Message::getMessage();
	cltmap::const_iterator it;
	cltmap userList;
	Channel *chan;

	if (message.size() < 2 || message.size() > 3)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "TOPIC"));
	else if (!List::existChannel(message[1]))
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOSUCHCHANNEL(serverHost, client.getNick(), message[1]));
	else if (message.size() == 2) {
		if ((chan = &List::findChannel(message[1]))->getTopic() == "")
			Buffer::sendMessage(client.getClientFd(), reply::RPL_NOTOPIC(serverHost, client.getNick(), message[1]));
		else
			Buffer::sendMessage(client.getClientFd(), reply::RPL_TOPIC(serverHost, client.getNick(), message[1], chan->getTopic()));
	}
	else if ((chan = &List::findChannel(message[1]))->getMode() & SAFE_TOPIC && (chan->getChanOp() == NULL || chan->getChanOp()->getClientFd() != client.getClientFd()))
		Buffer::sendMessage(client.getClientFd(), error::ERR_CHANOPRIVSNEEDED(serverHost, client.getNick(), message[1]));
	else {
		userList = chan->getUserList();
		chan->setTopic(message[2]);

		for (it = userList.begin(); it != userList.end(); it++)
			Buffer::sendMessage(it->second->getClientFd(), reply::RPL_SUCCESSTOPIC(client.getNick(), client.getUser(), client.getHost(), message[1], message[2]));
	}
}
