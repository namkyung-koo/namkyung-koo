#include "../../include/utils/List.hpp"
#include "../../include/Client.hpp"
#include "../../include/Channel.hpp"
#include "../../include/utils/Message.hpp"
#include "../../include/CommandExecute.hpp"
#include <iostream>

chlmap List::chlList;
cltmap List::cltList;

List::List() {}
List::~List() {}

bool List::addClientList(int fd, in_addr info) {
	if (cltList.find(fd) == cltList.end()) {
		cltList.insert(std::make_pair(fd, new Client(fd, info)));
		return true;
	}
	return false;
}

bool List::addChannelList(std::string name, Client* creator) {
	if (chlList.find(name) == chlList.end()) {
		chlList.insert(std::make_pair(name, new Channel(name, creator)));
		return true;
	}
	return false;
}

bool List::delClientList(int fd) {
	if (cltList.find(fd) != cltList.end()) {
		delete cltList[fd];
		cltList[fd] = NULL;
		cltList.erase(fd);
		return true;
	}
	return false;
}

bool List::delChannelList(std::string name) {
	if (chlList.find(name) != chlList.end()) {
		delete chlList[name];
		chlList[name] = NULL;
		chlList.erase(name);
		return true;
	}
	return false;
}

void List::clearClientList() {
	for (cltmap::iterator iter = cltList.begin(); iter != cltList.end(); iter++) {
		delete iter->second;
		iter->second = NULL;
	}
	cltList.clear();
}

void List::clearChannelList() {
	for (chlmap::iterator iter = chlList.begin(); iter != chlList.end(); iter++) {
		delete iter->second;
		iter->second = NULL;
	}
	chlList.clear();
}

Client& List::findClient(int fd) {
	return *cltList.find(fd)->second;
}

Channel& List::findChannel(std::string name) {
	return *chlList.find(name)->second;
}

bool List::existClient(int fd) {
	if (cltList.find(fd) != cltList.end())
		return true;
	return false;
}

bool List::existChannel(std::string name) {
	if (chlList.find(name) != chlList.end())
		return true;
	return false;
}

cltmap& List::getClientList() {
	return List::cltList;
}

chlmap& List::getChannelList() {
	return List::chlList;
}
