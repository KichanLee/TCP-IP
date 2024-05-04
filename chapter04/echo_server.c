#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int ac, const char *av[]) {
  int serv_sock, clnt_sock;

  char msg[BUFF_SIZE];
  int str_len, i;

  struct sockaddr_in serv_adr, clnt_adr;
  socklen_t clnt_adr_size;

  if (ac != 2) {
    printf("Usage: %s <port>\n", av[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == -1) perror("server socket error!\n");

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(atoi(av[1]));

  if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    perror("bind error!\n");
  if (listen(serv_sock, 5) == -1) perror("listen_error!\n");

  clnt_adr_size = sizeof(clnt_adr);

  for (i = 0; i < 5; ++i) {
    printf("i %d\n", i);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_size);
    printf("check\n");
    if (clnt_sock == -1)
      perror("accept error!\n");
    else
      printf("Connected clinet %d\n", i + 1);

    while ((str_len = read(clnt_sock, msg, BUFF_SIZE) != 0)) {
      write(clnt_sock, msg, str_len);
      printf("while\n");
    }
    close(clnt_sock);
  }
  close(serv_sock);
  return 0;
}