#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int ac, const char *av[]) {
  int sock;
  struct sockaddr_in serv_addr;
  char *message;
  int str_len;

  if (ac != 3) {
    printf("Usage: %S <IP> <PORT>\n", av[0]);
    exit(1);
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  // server 접속을 위한 소켓 생성
  if (sock == -1) perror("socket error!\n");
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(av[1]);
  serv_addr.sin_port = atoi(av[2]);
  // 초기화 되는 값은 연결을 목적으로 하는 서버 소켓의 ip, port의 정보
  if (connect(sock, (struct addr *)&serv_addr, sizeof(serv_addr)) == -1)
    perror("connect error!\n");
  str_len = read(sock, message, sizeof(message));
  printf("message from server : %s\n", message);
  close(sock);
  return 0;
}