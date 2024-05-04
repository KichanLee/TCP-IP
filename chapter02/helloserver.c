#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int ac, const char *av[]) {
  int serv_sock;
  int clnt_sock;

  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size;

  char *message = "hello world";

  if (ac != 2) {
    printf("wrong!\n");
    exit(1);
  }
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  // socket 생성
  if (serv_sock == -1) perror("server error!");
  memset(&serv_addr, 0, sizeof(serv_addr));
  // socket의 주소할당을 위해 구조체 변수를 초기화한다.
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(av[1]));
  // bind 함수 호출
  if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    perror("bind() error!");
  if (listen(serv_sock, 5) == -1) perror("listen error!");

  clnt_addr_size = sizeof(clnt_addr);
  clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
  if (clnt_sock == -1) perror("accept error!\n");
  write(clnt_sock, message, sizeof(message));
  close(clnt_sock);
  close(serv_sock);

  return 0;
}