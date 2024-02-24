#include "../../include/CommandExecute.hpp"
#include "../../include/utils/Message.hpp"
#include "../../include/utils/Buffer.hpp"
#include "../../include/utils/reply.hpp"
#include "../../include/utils/error.hpp"

void CommandExecute::ping(Client& client, std::string const& serverHost) {
	mesvec const& message = Message::getMessage();

	if (message.size() == 1 || (message.size() == 2 && message[1] == ""))
		Buffer::sendMessage(client.getClientFd(), error::ERR_NOORIGIN(serverHost, client.getNick()));	
	else if (message.size() != 2)
		Buffer::sendMessage(client.getClientFd(), error::ERR_NEEDMOREPARAMS(serverHost, message[0]));
	else
		CommandExecute::pong(client, serverHost, message[1]);
}

void CommandExecute::pong(Client& client, std::string const& serverHost, std::string const& token) {
	Buffer::sendMessage(client.getClientFd(), ":" + serverHost + " PONG " + serverHost + " :" + token + "\r\n");
}
