#include "../include/CommandExecute.hpp"
#include "../include/utils/Message.hpp"
#include <iostream>

static int isCommand(std::string val) {
	if (val == "PASS")
		return IS_PASS;
	if (val == "NICK")
		return IS_NICK;
	if (val == "USER")
		return IS_USER;
	if (val == "PING")
		return IS_PING;
	if (val == "PONG")
		return IS_PONG;
	if (val == "MODE")
		return IS_MODE;
	if (val == "JOIN")
		return IS_JOIN;
	if (val == "QUIT")
		return IS_QUIT;
	if (val == "PART")
		return IS_PART;
	if (val == "PRIVMSG")
		return IS_PRIVMSG;
	if (val == "NOTICE")
		return IS_NOTICE;
	if (val == "PART")
		return IS_PART;
	if (val == "KICK")
		return IS_KICK;
	if (val == "INVITE")
		return IS_INVITE;
	if (val == "TOPIC")
		return IS_TOPIC;
	if (val == "OPER")
		return IS_OPER;
	if (val == "KILL")
		return IS_KILL;
	return IS_NOT_ORDER;
}

int CommandExecute::chkCommand(int pass) {
	mesvec const& message = Message::getMessage();
	int whatCommand;

	if (!message.size())
		return IS_NOT_ORDER;
	whatCommand = isCommand(message[0]);
	if (whatCommand != IS_PASS && whatCommand != IS_NICK && whatCommand != IS_USER
		&& whatCommand != IS_NOT_ORDER && pass != IS_LOGIN)
		return IS_NOT_LOGIN;
	return whatCommand;
}
