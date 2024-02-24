#include "../../include/utils/Buffer.hpp"
#include "../../include/utils/Print.hpp"
#include <sys/socket.h>
#include <sstream>

fdmap Buffer::bufForRead;
fdmap Buffer::bufForSend;

int Buffer::readMessage(int fd, intptr_t data) {
	char buf[data + 1];
	int byte;

	memset(buf, 0, sizeof(buf));
	byte = recv(fd, buf, data, 0);
	if (byte == -1)
		return byte;
	bufForRead[fd] += buf;
	return byte;
}

int Buffer::sendMessage(int fd) {
	int size = 0;

	if (bufForSend[fd] != "") {
		std::string mes = "";

		mes = bufForSend[fd];
		size = send(fd, &mes[0], mes.size(), 0);
		if (size == -1)
			return -1;
		bufForSend[fd] = "";
		if (static_cast<size_t>(size) < mes.size()) {
			bufForSend[fd] = mes.substr(size, mes.size());
		}
	}
	return size;
}

int Buffer::sendMessage(int fd, std::string message) {
	int size = 0;

	bufForSend[fd] += message;
	if (bufForSend[fd] != "") {
		std::string mes = "";

		mes = bufForSend[fd];
		size = send(fd, &mes[0], mes.size(), 0);
		if (size == -1) {
			return -1;
		}
		bufForSend[fd] = "";
		if (static_cast<size_t>(size) < mes.size()) {
			bufForSend[fd] = mes.substr(size, mes.size());
		}
	}
	return size;
}

std::string Buffer::getReadBuf(int fd) {
	if (bufForRead.find(fd) != bufForRead.end())
		return bufForRead[fd];
	return "";
}

std::string Buffer::getSendBuf(int fd) {
	if (bufForSend.find(fd) != bufForSend.end())
		return bufForSend[fd];
	return "";
}

void Buffer::setReadBuf(std::pair<int, std::string> val) {
	if (bufForRead.find(val.first) != bufForRead.end())
		bufForRead[val.first] += val.second;
	else
		bufForRead.insert(std::make_pair(val.first, val.second));
}

void Buffer::setSendBuf(std::pair<int, std::string> val) {
	if (bufForSend.find(val.first) != bufForSend.end())
		bufForSend[val.first] += val.second;
	else
		bufForSend.insert(std::make_pair(val.first, val.second));
}

void Buffer::resetReadBuf(int fd) {
	if (bufForRead.find(fd) != bufForRead.end())
		bufForRead[fd] = "";
	else
		bufForRead.insert(std::make_pair(fd, ""));
}

void Buffer::resetSendBuf(int fd) {
	if (bufForSend.find(fd) != bufForSend.end())
		bufForSend[fd] = "";
	else
		bufForSend.insert(std::make_pair(fd, ""));
}

void Buffer::eraseReadBuf(int fd) {
	if (bufForRead.find(fd) != bufForRead.end())
		bufForRead.erase(fd);
}

void Buffer::eraseSendBuf(int fd) {
	if (bufForSend.find(fd) != bufForSend.end())
		bufForSend.erase(fd);
}
