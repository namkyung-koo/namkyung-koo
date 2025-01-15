#ifndef _BUFFER_HPP_
# define _BUFFER_HPP_

# include "utils.hpp"

class Buffer {
private:
	static fdmap bufForRead;
	static fdmap bufForSend;
public:
	static int readMessage(int fd, intptr_t data);
	static int sendMessage(int fd);
	static int sendMessage(int fd, std::string message);
	static std::string getReadBuf(int fd);
	static std::string getSendBuf(int fd);
	static void setReadBuf(std::pair<int, std::string> val);
	static void setSendBuf(std::pair<int, std::string> val);
	static void resetReadBuf(int fd);
	static void resetSendBuf(int fd);
	static void eraseReadBuf(int fd);
	static void eraseSendBuf(int fd);
};

#endif
