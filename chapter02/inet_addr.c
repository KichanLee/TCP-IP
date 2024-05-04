#include <arpa/inet.h>
#include <stdio.h>

int main(int ac, const char *av[]) {
  char *addr1 = "1.2.3.4";
  char *addr2 = "10.22.33.330";

  unsigned long conv_addr = inet_addr(addr1);
  if (conv_addr == INADDR_NONE)
    printf("Error Occured\n");
  else
    printf("%#lx\n", conv_addr);
  conv_addr = inet_addr(addr2);
  if (conv_addr == INADDR_NONE)
    printf("Error Occured\n");
  else
    printf("%#lx\n", conv_addr);
}