#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30

void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int ac, const char *av[]) {
  int sd;
  FILE *fp;

  char buf[BUF_SIZE];
  int read_cnt;
  struct sockaddr_in serv_adr;

  if (ac != 3) {
    printf("Usage: %s <IP> <PORT>\n", av[0]);
    exit(1);
  }
  fp = fopen("receive.dat", "wb");
  sd = socket(PF_INET, SOCK_STREAM, 0);

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(av[1]);
  serv_adr.sin_port = htons(atoi(av[2]));

  connect(sd, (struct sockaddr *)&serv_adr, sizeof(serv_adr));

  while ((read_cnt = read(sd, buf, BUF_SIZE)) != 0)
    fwrite((void *)buf, 1, read_cnt, fp);

  puts("Received file data");
  write(sd, "Thankyou", 10);
  fclose(fp);
  close(sd);
  return 0;
}