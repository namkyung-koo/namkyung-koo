#ifndef _CLIENT_HPP_
# define _CLIENT_HPP_

# include <arpa/inet.h>
# include <unistd.h>

# include "./utils/utils.hpp"
# include "./Channel.hpp"

class Client {
private:
	// PASS, NICK, USER 전부를 거쳤는 지 검증. 비트마스킹.
	int passConnect;

	// 운영자 권한 여부 확인
	bool op;

	// final_ping_time
	time_t finalTime;

	// client socket
	int fd;

	// client addr info
	in_addr info;

	// client hostname
	std::string host;

	// client nickname
	std::string nick;

	// client realname
	std::string real;

	// client username
	std::string user;

	// client servername
	std::string serv;

	// 현재 참여하고 있는 채널 목록
	chlmap joinList;

public:
	// 생성자와 파괴자
	Client(int fd, in_addr info);
	~Client();

	// setter
	void setPassConnect(int flag);
	void setNick(std::string nick);
	void setReal(std::string real);
	void setHost(std::string host);
	void setUser(std::string user);
	void setServ(std::string serv);
	void setTime();

	// add
	void addJoinList(Channel* channel);

	// del
	void delJoinList(Channel* channel);

	// join channel
	int joinChannel(Channel* channel, std::string const& key);

	// getter
	int getPassConnect() const;
	int getClientFd() const;
	bool getOp() const;
	std::string const& getHost() const;
	std::string const& getNick() const;
	std::string const& getReal() const;
	std::string const& getUser() const;
	std::string const& getServ() const;
	time_t const& getTime() const;
	in_addr const& getAddr() const;
};

#endif
