#ifndef _CHANNEL_HPP_
# define _CHANNEL_HPP_

# include "./utils/utils.hpp"
# include "./Client.hpp"

class Channel {
private:
	// 채널 이름
	std::string chName;

	// 채널 운영자
	Client* chanOp;

	// 채널 가입자 명단
	cltmap userList;

	// 가입자수 상한
	int userLimit;

	// 채널 모드(비트 마스킹)
	int mode;

	// 채널 주제
	std::string topic;

	// 채널 비밀번호
	std::string password;

	// 채널 생성 시간
	time_t creationTime;

	// 채널 암호
	std::string key;

	// 초대자 명단
	cltmap inviteList;
public:
	Channel(std::string chName, Client* client);
	~Channel();

	// setter
	void setChName(std::string& name);
	void setChanOp(Client* client);
	void setUserLimit(int userLimit);
	void setTopic(std::string topic);
	void setPassword(std::string pw);
	void setMode(int mode, bool flag);
	void setKey(std::string key);

	// add
	void addInviteList(Client* client);
	void addClientList(Client* client);

	// del
	void delInviteList(Client* client);
	void delClientList(Client* client);

	// getter
	Client const* getChanOp() const;
	cltmap const& getUserList() const;
	int getUserLimit() const;
	std::string getChName() const;
	std::string getTopic() const;
	int getMode() const;
	time_t getTime() const;
	std::string getKey() const;
	std::string getStrUserList() const;

	// chker
	bool isClientInvite(Client* client);
};

#endif
