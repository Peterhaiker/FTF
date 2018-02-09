/* init.c
 * Copyright (C) 2018-02-09 20:03 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<stdlib.h>
#include"../Header/server.h"

void init(void)
{
  daemon();
  //connect to mysql
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql,SQL_ADDR,SQL_USER,SQL_PASS,SQL_DB,0,NULL,CLIENT_MULTI_STATEMENT)){
    syslog(LOG_EMEGE,"init function:connect to mysql failed");
    exit(EXIT_FAILURE);
  }
  mysql_set_character_set(&mysql,"utf8");
  //create passwd table
  if(mysql_query(&mysql,"create table passwd(id int(8) not null primary key auto_increment,account varchar(20) not null,nickname varchar(20) not null)"))
  return;
}
