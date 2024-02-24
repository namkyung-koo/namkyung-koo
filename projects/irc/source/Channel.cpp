#include "../../include/Channel.hpp"
#include <iostream>

Channel::Channel(std::string chName, Client* client) : chName(chName), chanOp(client), userLimit(0), mode(0), topic(""), password(""), creationTime(time(NULL)), key("") {
	this->userList.clear();
	this->inviteList.clear();
	this->userList.insert(std::make_pair(client->getClientFd(), client));
}

Channel::~Channel() {
	cltmap::iterator iter;

	while (this->inviteList.size() != 0) {
		iter = this->inviteList.begin();
		iter->second = NULL;
		this->inviteList.erase(iter->first);
	}
	while (this->userList.size() != 0) {
		iter = this->userList.begin();
		iter->second = NULL;
		this->userList.erase(iter->first);
	}
}

void Channel::setChName(std::string& name) {
	this->chName = name;
}

void Channel::setChanOp(Client* client) {
	this->chanOp = client;
}

void Channel::setUserLimit(int userLimit) {
	this->userLimit = userLimit;
}

void Channel::setTopic(std::string topic) {
	this->topic = topic;
}

void Channel::setPassword(std::string pw) {
	this->password = pw;
}

void Channel::setMode(int mode, bool flag) {
	if (flag)
		this->mode |= mode;
	else
		this->mode &= mode;
}

void Channel::setKey(std::string key) {
	this->key = key;
}

void Channel::addInviteList(Client* client) {
	if (this->inviteList.find(client->getClientFd()) == this->inviteList.end())
		this->inviteList.insert(std::make_pair(client->getClientFd(), client));
}

void Channel::delInviteList(Client* client) {
	if (this->inviteList.find(client->getClientFd()) != this->inviteList.end()) {
		this->inviteList[client->getClientFd()] = NULL;
		this->inviteList.erase(client->getClientFd());
	}
}

bool Channel::isClientInvite(Client* client) {
	if (this->inviteList.find(client->getClientFd()) != this->inviteList.end())
		return true;
	return false;
}

void Channel::addClientList(Client* client) {
	if (this->userList.find(client->getClientFd()) == this->userList.end())
		this->userList.insert(std::make_pair(client->getClientFd(), client));
}

void Channel::delClientList(Client* client) {
	if (this->userList.find(client->getClientFd()) != this->userList.end()) {
		this->userList[client->getClientFd()] = NULL;
		this->userList.erase(client->getClientFd());
	}
}

Client const* Channel::getChanOp() const {
	return this->chanOp;
}

cltmap const& Channel::getUserList() const {
	return this->userList;
}

int Channel::getUserLimit() const {
	return this->userLimit;
}

std::string Channel::getChName() const {
	return this->chName;
}

std::string Channel::getTopic() const {
	return this->topic;
}

time_t Channel::getTime() const {
	return this->creationTime;
}

int Channel::getMode() const {
	return this->mode;
}

std::string Channel::getKey() const {
	return this->key;
}

std::string Channel::getStrUserList() const {
	std::string list = "";

	if (this->chanOp) {
		list = "@" + this->chanOp->getNick() + " ";
	}
	for (cltmap::const_iterator it = this->userList.begin(); it != this->userList.end(); it++)
		if (it->second != this->chanOp)
			list += it->second->getNick() + " ";
	if (list[list.size() - 1] == ' ')
		list = list.substr(0, list.size() - 1);
	return list;
}
