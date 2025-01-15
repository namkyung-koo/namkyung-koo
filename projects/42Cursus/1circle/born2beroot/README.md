1. 가상화 및 운영체제 설치
    - VirtualBox를 사용해 CLI 환경에서 Debian 설치
2. 시스템 보안 및 사용자 관리
    - 보안을 위한 비밀번호 정책 설정
    - 사용자 및 그룹 관리(adduser, usermod 명령어 사용)
3. 디스크 파티셔닝 및 LVM
    - LVM(Logical Volume Manager)를 사용하여 디스크를 논리적으로 분할
4. 네트워크 및 SSH 설정
    - SSH(Secure Shell): 포트 4242에서만 SSH 연결 허용
    - 포트포워딩: VirtualBox 네트워크 설정에서 호스트와 게스트 간 통신을 위한 포트포워딩 구성
5. 방화벽(UFW) 설정
    - UFW(Uncomplicated Firewall)를 사용하여 포트 4242만 허용. 방화벽이 서버 시작 시 자동으로 활성화되도록 설정
6. 시스템 모니터링
    - 서버 상태(CPU, 메모리, 디스크 사용량, 네트워크 상태 등)를 주기적으로 확인하고 정보를 출력하는 스크립트 작성(monitoring.sh)
7. AppArmor 보안 모듈
    - Debian에서 AppArmor를 활성화하여 프로세스 보안을 강화