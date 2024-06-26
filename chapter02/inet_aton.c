#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int ac, const char *av[]) {
  char *addr = "127.232.124.77";

  struct sockaddr_in addr_inet;

  if (!inet_aton(addr, &addr_inet.sin_addr))
    error_handling("Conversion error!\n");
  else
    printf("NetWork ordered ineteger addr : %#x\n", addr_inet.sin_addr.s_addr);
  return 0;
}