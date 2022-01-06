#include "networking.h"


int main() {
  char s[50];
  int socket_fd;
  socket_fd = client_setup();
  while(1){
    printf("\nEnter a string: ");
    fgets(s, 50, stdin);
    if(strcmp(s,"exit")==0){printf("\n[Subserver] Exiting...\n"); break;}
    write(socket_fd, s, sizeof(s));
    read(socket_fd, s, sizeof(s));
    printf("\nReturned string: %s", s);
  }
}
