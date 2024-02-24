#include "../../include/CommandExecute.hpp"
#include "../../include/utils/Buffer.hpp"
#include "../../include/utils/Message.hpp"
#include "../../include/utils/reply.hpp"
#include "../../include/utils/List.hpp"

void CommandExecute::quit(Client& client) {
	mesvec const& message = Message::getMessage();
	cltmap const& cltList = List::getClientList();
	std::string reason = "";

	for (size_t i = 1; i < message.size(); i++)
		reason += message[i] + " ";
	if (reason != "" && reason[reason.size() - 1] == ' ')
		reason = reason.substr(0, reason.size() - 1);
	for (cltmap::const_iterator it = cltList.begin(); it != cltList.end(); it++) {
		if (it->second != &client)
			Buffer::sendMessage(it->second->getClientFd(), reply::RPL_SUCCESSQUIT(client.getNick(), client.getUser(), client.getHost(), reason));
		else
			Buffer::sendMessage(client.getClientFd(), "ERROR :Connection out");
	}
}