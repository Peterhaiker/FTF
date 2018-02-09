/* daemon.c
 * Copyright (C) 2018-02-09 10:59 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 * Describe:init server.include create Mysql table ,init jo * journal deal
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

void deamon(void)
{
  //become a daemon
  //clear file creation mask
  umask(0);
  pid_t pid;

  if(0>(pid=fork())){
    perror("fork failed");
    exit(0);
  }
  else if(pid!=0)
    exit(0);
  //child
  setsid();
  //fork again
  if(0<(pid=fork())){
    perror("fork failed");
    exit(0);
  }
  else if(0!=pid)
    exit(0);
  //grandchild
  //now change the working diretory
  if(-1==chdir("/")){
    perror("change working directory failed");
    exit(0);
  }
  //get all file descriptor and close it
  struct rlimit max_fd;
  if(getrlimit(RLIMIT_NOFILE,&max_fd)<0){
    perror("get max file limit failed");
    exit(0);
  }
  if(max_fd.rlim_max==RLIM_INFINITY)
    max_fd.rlim_max=1024;
  for(int i=0;i<max_fd;i++)
    close(i);
  //init the log file
  openlog("FTF",LOG_CONS|LOG_PID,LOG_DAEMON);
  return;
}
