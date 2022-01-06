#include "networking.h"


char* cap(char* s, int size){
  int h;
  for(int i=0;i<size;i++){
    h=s[i];
    if(isalpha(s[i])){
      if(h>96){h=h-32;}else{h=h+32;}
    }
    s[i]=h;
  }
  return s;
}

static void sighandler(int signo){
  if(signo == SIGINT ){
    printf("\n[Server] Exiting...\n");
    exit(0);
  }
}

int main(){
  signal(SIGINT, sighandler);
  char s[50];
  int socket_fd;
  int f;
  socket_fd=server_setup();
  while(1){
    int client_socket;
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    printf("[Server] Waiting for connection...\n");
    client_socket = accept(socket_fd,(struct sockaddr *)&client_address, &sock_size);
    printf("[Server] Connection made! Now forking...\n");
    f=fork();
    if(f==0){
      while(1){
        if(read(client_socket, s, sizeof(s))<=0){break;}
        write(client_socket, cap(s, sizeof(s)), sizeof(s));
      }
      printf("[Subserver] Connection severed, now closing\n");
      exit(0);
    }
  }
}
