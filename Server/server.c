/* server.c
 * Copyright (C) 2018-02-09 11:07 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<mysql.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"Header/server.h"
MYSQL mysql;

int main(int argc,char*argv[])
{
  daemon();
  init();
  int choice;
  int listenfd,connfd;
  struct sockaddr_in srvaddr,cliaddr;
  socklen_t clilen;

  //create a socket
  listenfd=socket(AF_INET,SOCK_STREAM,0);
  //sign sockaddr_in structure
  memset(&srvaddr,0,sizeof(srvaddr));
  memset(&cliaddr,0,sizeof(cliaddr));
  srvaddr.sin_family=AF_INET;
  srvaddr.sin_port=htons(SRV_PORT);
  inet_pton(AF_INET,SRV_ADDR,&srvaddr.sin_addr);

  listen(listenfd,MAX_LIS);
  for(;;){
    clilen=sizeof(cliaddr);
    connfd=accept(listenfd,&srvaddr,&clilen);
    read(connfd,&choice,sizeof(int));
    switch(choice){
      case 1:login(connfd);
      case 2:sign_up(connfd);
    }
  }
  return 0;
}
