FROM alpine:3.18

RUN apk update && \
    apk upgrade && \
    apk add curl bash mysql-client php82 php82-fpm php82-xml php82-gd php82-intl php82-iconv php82-mysqli php82-phar dumb-init && \
    ln -s /usr/bin/php82 /usr/bin/php
# 심볼링 링크로인해 php 명령을 사용할 때, 실제론는 php82가 실행된다.

# wp-cli를 다운 받은 후, 실행 권한 부여
RUN curl -s -L https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar --output /usr/local/bin/wp && \
    chmod +x /usr/local/bin/wp

# Alpine Linux 기반의 컨테이너 이미지에서는 'www-data'의 Group id(gid), User id(uid)가 통상적으로 82로 설정되어 있다.
# 이미 존재하는 경우 exit 0으로 오류를 무시하고 스크립트가 성공적으로 종료됨을 알린다.
RUN addgroup -g 82 -S www-data;     exit 0

# www-data라는 이름의 유저를 만든 뒤, www-data 그룹에 넣는다.
RUN adduser -u 82 -D -S -G www-data www-data

COPY ./conf/www.conf /etc/php82/php-fpm.d/www.conf

# php 프로세스가 소켓 파일을 생성, 관리하기 위한 디렉토리를 만든다.
RUN mkdir -p /run/php

COPY ./tools/wordpress.sh /usr/local/bin/wordpress.sh

RUN chmod +x /usr/local/bin/wordpress.sh && \
    mkdir -p /var/www/html && \
    chown -R www-data:www-data /var/www/html && \
    chmod -R 755 /var/www/html

# docker container 내에서 작업 디렉토리로 /var/www/html을 설정한다.
WORKDIR /var/www/html

# PHP FastCGI Process Manager (FPM)을 위한 9000번 포트를 노출한다.
EXPOSE 9000

# Specify the command to run when the Docker container starts
ENTRYPOINT [ "/usr/bin/dumb-init", "--", "/usr/local/bin/wordpress.sh" ]