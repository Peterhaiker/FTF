/* login.c
 * Copyright (C) 2018-02-11 19:56 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include"../Header/client.h"

void sign_in(int connfd);
void sign_up(int connfd);
int choice;

int login(int connfd)
{
  puts(DOUBLE_FORMAT);
  puts("|                           FTF                         |");
  puts(DOUBLE_FORMAT);
  printf("           1:登录        2:注册        3:退出\n");
  int choice;
  printf("                         请选择:_\b");
  while(1!=scanf("%[123]",&choice)){
    printf("                      输入有误，重新选择:_\b");
  }
  switch(choice){
    case 1:sign_in(connfd);break;
    case 2:sign_up(connfd);break;
    case 3:exit(EXIT_SUCCESS);
  }
  return 0;
}

void sign_in(int connfd)
{
  choice=1;
  write(connfd,&choice,sizeof(int));
  printf("                        账户名(按q退出):");
  int account;
  char password[20]={'\0'};
  char login_state[20]={'\0'};
  while(1){
    if(1!=scanf("%d",&account)){
      printf("              账户名不合法，请重新输入(按q退出):_\b");
      continue;
    }
    else{
      if('q'==account){
        return;
      }
      else{
        if(100000>account){
          printf("                   账户名不合法，请重新输入(按q退出):_\b");
          continue;
        }
        else
          break;
      }
    }
    //账户输入成功，开始输入密码
    printf("                        密码:");
    while(1){
      fgets(password,20,stdin);
      password[strlen(password)-1]='\0';
      if(NULL!=strpbrk(password,"#*/'\"-;")){
        printf("                密码输入不合法，请重新输入:_\b");
        continue;
      }
      break;
    }
    //input success,now pass to server
    write(connfd,account,sizeof(int));
    write(connfd,password,sizeof(char)*20);
    read(connfd,login_state,sizeof(char)*20);
    if(0==strcmp("-1",login_state)){
      printf("                   账户或密码输入出错\n");
      printf("                           账户:");
      continue;
    }
    else{
      printf("           %s 欢迎您\n",login_state);
      break;
    }
  }
  return;
}

void sign_up(int connfd)
{

}
