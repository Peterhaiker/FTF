/* init.c
 * Copyright (C) 2018-02-09 20:03 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<mysql.h>
#include"../Header/server.h"

void init(void)
{
  daemon();
  //ensure only one daemon running in background
  int fd;
  if(-1==(fd=open("/var/run/FTF.lock",O_CREAT|O_RDRW,0666))){
    syslog(LOG_EMEGE,"create /var/run/FTF.lock failed:%m");
    exit(EXIT_FAILURE);
  }
  struct flock flock;
  flock.l_type=F_WRLCK;
  flock.l_whence=SEEK_SET;
  flock.l_start=0;
  flock.l_len=0;
  if(-1==fcntl(fd,F_SETLK,&flock)){
    syslog(LOG_EMEGE,"FTF has runned in background:%m");
    exit(EXIT_FAILURE);
  }
  write(fd,"%d",getpid());

  //connect to mysql
  mysql_init(&mysql);
  if(!mysql_real_connect(&mysql,SQL_ADDR,SQL_USER,SQL_PASS,SQL_DB,0,NULL,CLIENT_MULTI_STATEMENT)){
    syslog(LOG_EMEGE,"init function:connect to mysql failed %m");
    exit(EXIT_FAILURE);
  }
  mysql_set_character_set(&mysql,"utf8");
  //start transaction
  if(mysql_query(&mysql,"set autocommit=0;start transaction")){
    syslog(LOG_EMEGE,"init start transaction failed:%m");
    exit(EXIT_FAILURE);
  }
  //create passwd table
  while(mysql_next_result(&mysql))
    mysql_store_result(&mysql);
  if(!mysql_query(&mysql,"create table passwd(account mediumint not null primary key,nickname varchar(20),password varchar(50) not null)")){
    //create profile table
    if(!mysql_query(&mysql,"create table profile(account mediumint not null,name varchar(20) default null,sex varchar(1),fri_nums tinyint,grp_nums tinyint,ip_addr int not null,ip_port smallint not null,primary key(account),key pro_ip_addr_ind(ip_addr),key pro_id_port_ind(ip_port),constraint fk_account foreign key(account) references passwd(account))")){
      //create friends table
      if(!mysql_query(&mysql,"create table friends(account mediumint not null,ip_addr int not null,ip_port smallint not null,primary key(account),key fri_ip_addr_fk(ip_addr),key fri_ip_port_fk(ip_port),constraint fk_fri_account foreign key(account) references passwd(account),constraint fri_ip_addr_fk foreign key(ip_addr) references profile(ip_addr),constraint fri_ip_port_fk foreign key(ip_port) references profile(ip_port))")){
        goto success;
      }
    }
  }
  if(mysql_query(&mysql,"rollback")){
    syslog(LOG_EMEGE,"rollback transaction failed:%m");
    exit(EXIT_FAILURE);
  }
success:syslog(LOG_INFO,"init successed");
  return;
}
