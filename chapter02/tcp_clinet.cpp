#include <sys/socket.h>

#include <iostream>
#include <string>

int main(int ac, const char *av[]) {
  int socket;
  struct sockaddr_in serv_addr;
  char message[30];
  int str_len[30];
  int idx = 0, read_len = 0;

  if (ac != 3) {
    printf("Usage : %s <IP> <PORT>\n", av[0]);
    exit(1);
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1) printf("error\n")
}