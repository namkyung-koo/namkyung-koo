# readyToIrc

## Update 1.05(2023/12/11)
### FIX
- CommandExecute
  - kill : segfault 수정
  - mode : bad key 수정
  - privmsg : irssi 채팅창 전환 수정
  - 사용자 등록 전에 명령어 사용 방지
## Update 1.04(2023/11/21)
### CLASS
- LIST
  - 클라이언트 명단, 채널 명단 관리 전용 정적 클래스 생성. 해당 역할 일원화.
### FIX
- Server
  - 멤버 변수 : cltList, chlList 삭제
  - 멤버 함수 
    - addClient, delClient : 직접 멤버 변수 cltList와 chlList를 불러오던 부분을 LIST를 이용해 불러옴
    - runCommand : switch 함수에서 default 부분 삭제
- CommandExecute
  - cltList와 chlList를 매개변수로 받던 부분 삭제. 각 함수 내에서 LIST 클래스 이용하도록 변경
  - USER 함수에서 rfc1459 사양 반영하여 hostname과 servername은 서버 자체적으로 해당 내용 채울 수 있도록 변경(client가 보내는 인자는 무시)
- Channel
  - userList와 inviteList를 소멸자를 불러올 시 삭제할 수 있도록 수정
## Update 1.03(2023/11/19)
### COMMAND
- OPER, KILL 추가
### FIX
- Refactoring
  - 각 Command 주제별로 분화
- ModeCommand
  - key 모드를 비롯해 inspircd처럼 나올 수 있게 조정
## Update 1.02(2023/11/17)
### COMMAND
- NOTICE, PART, KICK, INVITE, TOPIC 추가
### FIX
- Server
  - monitoring : SIGSEGV 문제 해결
  - loop : EVFILT_WRITE를 비트 마스킹으로 확인하는 과정에서 flag가 아닌 ident와 비교하던 부분 수정
- Client
  - Client : 생성자에서 생성 시간을 초기화하지 않은 점 수정
- CommandExecute
  - MODE : 각 모드 기능 활성화 시, 모드에 필요한 값을 반영하지 않던 부분 수정
  - NICK : nickname 설정 시, 길이가 9자 이상이거나 빈 문자열인 경우 오류 처리 되도록 수정
## Update 1.01(2023/11/15)
### COMMAND
- PRIVMSG 추가
### FIX
- namespace reply {}에서 기존에 host를 출력하던 부분을 serv로 교체
- class Message에서 istringstream으로 받은 내용의 잔여물을 tmp에 넣는 과정에서 << 연산자로 넣던 걸 getline으로 변경
  (whitespace를 전부 구분자로 삼는 걸 방지하기 위함)
