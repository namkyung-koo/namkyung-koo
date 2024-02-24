#include "../../include/CommandExecute.hpp"
#include "../../include/utils/Buffer.hpp"
#include "../../include/utils/Message.hpp"
#include "../../include/utils/reply.hpp"
#include "../../include/utils/error.hpp"
#include "../../include/utils/List.hpp"

static int findNick(cltmap const& cltList, std::string const& tgt) {
	for (cltmap::const_iterator it = cltList.begin(); it !=  cltList.end(); it++) {
		if (it->second->getNick() == tgt)
			return it->first;
	}
	return 0;
}

bool CommandExecute::oper(Client& client, std::string const& opName, std::string const& opPass, std::string const& serverHost, bool oper) {
	mesvec const& message = Message::getMessage();
	bool flag = false;

	if (message.size() != 3)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "OPER"));
	else if (message[1] != opName)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOOPERHOST(serverHost, client.getNick(), "you don't match operName"));
	else if (message[2] != opPass)
		Buffer::sendMessage(client.getClientFd(), error::ERR_PASSWDMISMATCH(serverHost));
	else if (oper)
		Buffer::sendMessage(client.getClientFd(), error::ERR_ALREADYOTHEROPER(serverHost, client.getNick()));
	else {
		Buffer::sendMessage(client.getClientFd(), reply::RPL_YOUREOPER(serverHost, client.getNick()));
		flag = true;
	}
	return flag;	
}

int CommandExecute::kill(Client& client, std::string const& serverHost, bool op) {
	mesvec const& message = Message::getMessage();
	std::string reason;
	int fd = 0;

	if (message.size() != 3)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, "KILL"));
	else if (!(fd = findNick(List::getClientList(), message[1])))
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOSUCHNICK(serverHost, message[1]));
	else if (!op)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOOPIVILEGES(serverHost, client.getNick()));
	else {
		reason = "QUIT :" + message[2] + "\r\n";
		Message::parsMessage(reason);
	}
	return (fd);
}
