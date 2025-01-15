#ifndef _LIST_HPP_
# define _LIST_HPP_

# include "utils.hpp"

# include <sys/socket.h>

class List {
private:
	static cltmap cltList;
	static chlmap chlList;
	List();
public:
	~List();
	static bool addClientList(int fd, struct in_addr info);
	static bool addChannelList(std::string name, Client* creator);
	static bool delClientList(int fd);
	static bool delChannelList(std::string name);
	static void clearClientList();
	static void clearChannelList();
	static Client& findClient(int fd);
	static Channel& findChannel(std::string name);
	static bool existClient(int fd);
	static bool existChannel(std::string name);
	static cltmap& getClientList();
	static chlmap& getChannelList();
};

#endif
