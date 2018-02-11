/* login.c
 * Copyright (C) 2018-02-11 13:56 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include<mysql.h>
#include<unistd.h>

int login(int connfd)
{
  int account;
  MYSQL_RES*result;
  MYSQL_ROWS row;
  char password[20]={'\0'};
  char nickname[20]={'\0'};
  char echotext[100]={'\0'};
  for(int i=0;i<3;i++){
    if(1==read(connfd,account,sizeof(int))){
      if(read(connfd,password,20)>0){
        if(!mysql_query(&mysql,"select nickname from passwd where account=%d,passwd=SHA2('%s',256)")){
          if(1==mysql_num_rows(result)){
            result=mysql_store_result(&mysql);
            row=mysql_fetch_row(result);
            write(connfd,row[0],sizeof(row[0]));
            return 1;
          }
          else{
            strncpy(echotext,"输入错误，请重新输入:_\b",100);
            write(connfd,"输入错误，请重新输入:_\b",sizeof(EOF));
          }
        }
      }
    }
  }
  return 0;
}
