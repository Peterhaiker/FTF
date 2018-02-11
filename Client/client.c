/* client.c
 * Copyright (C) 2018-02-11 18:34 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include"Header/client.h"

int main(int argc,char*argv[])
{
  int sockfd;
  struct sockaddr_in cliaddr,srvaddr;
  socklen_t socklen;
  //create a socket
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  //assign sockaddr_in structure
  memset(&cliaddr,0,sizeof(cliaddr));
  memset(&srvaddr,0,sizeof(srvaddr));
  srvaddr.sin_family=AF_INET;
  srvaddr.sin_port=htons(SRV_PORT);
  inet_pton(AF_INET,SRV_ADDR,&srvaddr.sin_addr);
  socklen=sizeof(srvaddr);
  if(-1==connect(sockfd,(struct sockaddr*)&srvaddr,socklen)){
    perror("connect to server failed:");
    return -1;
  }
  while(0==login(sockfd))
    ;
  //login success
  return 0;
}
