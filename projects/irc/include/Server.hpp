#ifndef _SERVER_HPP_
# define _SERVER_HPP_

# include <iostream>
# include <string>
# include <vector>
# include <map>

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/event.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <unistd.h>

# include "Client.hpp"
# include "Channel.hpp"
# include "CommandExecute.hpp"
# include "./utils/Message.hpp"
# include "./utils/Buffer.hpp"
# include "./utils/Print.hpp"
# include "./utils/error.hpp"

# define EVENT_LIMIT 15 // kevent를 한 번에 확인해서 불러오는 최대 개수

/*
	server가 하는 일
	1. client의 연결, 연결 해제, 연결 오류 처리 등. 전반적인 네트워크 연결을 담당한다.
		a. 소켓을 보유
		b. 클라이언트 목록 보유
		c. IRC 서버 운영자
	2. 채널의 생성, 해제 관리
		a. 채널 목록 보유
	3. 메세지 파싱
	4. IRC 프로토콜 명령어를 연결
		a. 명령어 핸들링 보유
		b. 명령어 핸들링 결과 나오는 숫적 응답 및 오류 처리
	5. 클라이언트에 주기적으로 핑 보내기
	6. 시그널 핸들링
*/
class Server {
	typedef std::vector<struct kevent> kquvec;
private:
	// irc 서버로서 가져야 할 기본 정보들
	int servSock;
	struct sockaddr_in servAddr;
	std::string password;
	std::string opName;
	std::string opPassword;
	std::string host;
	std::string ip;
	int port;
	Client* op;
	time_t startTime;

	// 서버 종료가 필요할 때, 플래그를 올려줄 함수
	bool running;

	// 소켓 이용 통신 및 명령어 집행 시 필요
	int kq;
	kquvec newEventFds;

	void runCommand(int fd);
public:
	// 생성자와 파괴자
	Server(std::string port, std::string password);
	~Server();

	// 소켓 연결 및 통신
	void init();

	// 소켓을 연 후에 계속 돌아가는 부분
	void loop();

	// event 넣기
	void pushEvents(kquvec& list, uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void* udata);

	// 클라이언트 생성 및 삭제
	void addClient(int fd);
	void delClient(int fd);

	// I/O
	void chkReadMessage(int fd, intptr_t data);
	void chkSendMessage(int fd);

	// time check
	void monitoring();

	// private 변수 내용물 받기
	int const& getServerSocket() const;
	std::string const& getHost() const;
	struct sockaddr_in const& getServAddr() const;
	int const& getPort() const;
	std::string const& getPassword() const;
	Client& getOp() const;
	time_t const& getServStartTime() const;
};

#endif
