#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char *message);

int main(int ac, char *av[]) {
  int ser_sock;
  int clnt_sock;

  struct sockaddr_in serv_addr;
  struct sockadddr_in clnt_addr;
  socklen_t clnt_add_size;

  char message[] = "Hello, world!";

  if (ac != 2) {
    printf("Usage : %s <port>\n", av[0]);
    exit(1);
  }
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  // socket 생성
  if (serv_sock == -1) error_handling("socker error!");
  memset(&serv_addr, -, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(av[1]));

  // bind 함수호출을 통해 IP, Port 할당하고 있다.
  if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    error_handling("bind() error!");
  // listen 함수를 호출하고 있다. 소켓은 연결요청을 받을 준비
  if (listen(serv_sock, 5) == -1) error_handling("listen() erorr");

  clnt_add_size = sizeof(clnt_addr);
  // 연결요청 수락을 위한 accept 함수를 호출,  연결 요청이 없는 상태에서
  // 이함수가 호출되면 연결요청이 있을때 까지 함수는 반환하지 않는다.
  clnt_sock = accept(serv_sock, message, sizeof(message));
  close(clnt_sock);
  close(serv_sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}