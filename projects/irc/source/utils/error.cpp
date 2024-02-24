#include "../../include/utils/error.hpp"

std::string const suffix = "\r\n";

std::string const error::ERR_INPUTTOOLONG(std::string const& serverHost) {
	return ":" + serverHost + " 417 :Input line was too long" + suffix;
}

std::string const error::ERR_NEEDMOREPARAMS(std::string const& serverHost, std::string const& command) {
	return ":" + serverHost + " 461 " + command + " :Not enough parameters" + suffix;
}

std::string const error::ERR_ALREADYREGISTERED(std::string const& serverHost) {
	return ":" + serverHost + " 462 :You may not reregister" + suffix;
}

std::string const error::ERR_PASSWDMISMATCH(std::string const& serverHost) {
	return ":" + serverHost + " 464 :Password incorrect" + suffix;
}

std::string const error::ERR_NONICKNAMEGIVEN(std::string const& serverHost) {
	return ":" + serverHost + " 431 :No nickname given" + suffix;
}

std::string const error::ERR_NICKNAMEINUSE(std::string const& serverHost, std::string const& nick) {
	return ":" + serverHost + " 433 " + nick + " :Nickname is already in use" + suffix;
}

std::string const error::ERR_ERRONEUSNICKNAME(std::string const& serverHost, std::string const& nick) {
	return ":" + serverHost + " 432 " + nick + " :Erroneus nickname" + suffix;
}

std::string const error::ERR_NOTREGISTERED(std::string const& serverHost, std::string const& reason) {
	return ":" + serverHost + " 451 :" + reason + suffix;
}

std::string const error::ERR_UNKNOWNCOMMAND(std::string const& serverHost, std::string const& command) {
	return ":" + serverHost + " 421 " + command + " :Unknown Command" + suffix;
}

std::string const error::ERR_NOORIGIN(std::string const& serverHost, std::string const& nick) {
	return ":" + serverHost + " 409 " + nick + " :No origin specified" + suffix;
}

std::string const error::ERR_INVALIDMODEPARAM(std::string const& serverHost, std::string const& nick, std::string const& chName, char const& mode, std::string const& reason) {
	return ":" + serverHost + " 696 " + nick + " " + chName + " " + mode + " :" + reason + suffix;
}

std::string const error::ERR_UNKNOWNMODE(std::string const& serverHost, std::string const& nick, char const& mode) {
	return ":" + serverHost + " 472 " + nick + " " + mode + " :is not a recognised channel mode" + suffix;
}

std::string const error::ERR_NOSUCHCHANNEL(std::string const& serverHost, std::string const& nick, std::string const& chName) {
	return ":" + serverHost + " 403 " + nick + " " + chName + " :No such channel" + suffix;
}

std::string const error::ERR_CHANOPRIVSNEEDED(std::string const& serverHost, std::string const& nick, std::string const& chName) {
	return ":" + serverHost + " 482 " + nick + " " + chName + " :You're not channel operator" + suffix;
}

std::string const error::ERR_BADCHANMASK(std::string const& serverHost, std::string const& nick, std::string const& chName) {
	return ":" + serverHost + " 476 " + nick + " " + chName + " :Bad Channel Mask" + suffix;
}

std::string const error::ERR_TOOMANYCHANNELS(std::string const& serverHost, std::string const& nick, std::string const& chName) {
	return ":" + serverHost + " 405 " + nick + " " + chName + " :You have joined too many channels" + suffix;
}

std::string const error::ERR_CHANNELISFULL(std::string const& serverHost, std::string const& nick, std::string const& chName) {
	return ":" + serverHost + " 471 " + nick + " " + chName + " :Cannot join channel (+l)" + suffix;
}

std::string const error::ERR_INVITEONLYCHAN(std::string const& serverHost, std::string const& nick, std::string const& chName) {
	return ":" + serverHost + " 473 " + nick + " " + chName + " :Cannot join channel (+i)" + suffix;
}

std::string const error::ERR_BADCHANNELKEY(std::string const& serverHost, std::string const& nick, std::string const& chName) {
	return ":" + serverHost + " 475 " + nick + " " + chName + " :Cannot join channel (+k)" + suffix;
}

std::string const error::ERR_NORECIPIENT(std::string const& serverHost, std::string const& nick, std::string const& command) {
	return ":" + serverHost + " 411 " + nick + " :No recipient given (" + command + ")" + suffix; 
}

std::string const error::ERR_NOTEXTTOSEND(std::string const& serverHost, std::string const& nick) {
	return ":" + serverHost + " 412 " + nick + " :No text to send" + suffix;
}

std::string const error::ERR_NOSUCHNICK(std::string const& serverHost, std::string const& nick) {
	return ":" + serverHost + " 401 " + nick + " :No such nick" + suffix; 
}

std::string const error::ERR_CANNOTSENDTOCHAN(std::string const& serverHost, std::string const& nick, std::string const& chName) {
	return ":" + serverHost + " 404 " + nick + " " + chName + " :You cannot send external message to this channel" + suffix;
}

std::string const error::ERR_NOTONCHANNEL(std::string const& serverHost, std::string const& nick, std::string const& chName) {
	return ":" + serverHost + " 442 " + nick + " " + chName + " :You're not on that channel" + suffix;
}

std::string const error::ERR_USERNOTINCHANNEL(std::string const& serverHost, std::string const& nick, std::string const& tgt, std::string const& chName) {
	return ":" + serverHost + " 441 " + nick + " " + tgt + " " + chName + " :They aren't on that channel" + suffix;
}

std::string const error::ERR_USERONCHANNEL(std::string const& serverHost, std::string const& nick, std::string const& tgt, std::string const& chName) {
	return ":" + serverHost + " 443 " + nick + " " + tgt + " " + chName + " :is already on channel" + suffix;
}

std::string const error::ERR_NOOPERHOST(std::string const& serverHost, std::string const& nick, std::string const& reason) {
	return ":" + serverHost + " 491 " + nick + " :" + reason + suffix;
}

std::string const error::ERR_ALREADYOTHEROPER(std::string const& serverHost, std::string const& nick) {
	return ":" + serverHost + " 486 " + nick + " :already enrolled other operator" + suffix;
}

std::string const error::ERR_NOOPIVILEGES(std::string const& serverHost, std::string const& nick) {
	return ":" + serverHost + " 481 " + nick + " :Permission Denied- You're not an IRC operator" + suffix;
}
