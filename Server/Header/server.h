/* server.h
 * Copyright (C) 2018-02-09 10:55 
 * author peterhaiker 
 * email  vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SERVER_H
#define SERVER_H

#define SRV_ADDR "127.0.0.1"
#define SRV_PORT  6666
#define SQL_ADDR "127.0.0.1"
#define SQL_USER "root"
#define SQL_PASS "2391457146"
#define SQL_DB   "FTF"
#define MAX_LIS  1024

#include<mysql.h>
#include<syslog.h>
extern MYSQL mysql;//mysql对象

void daemon(void);
void init(void);
int login(int connfd);
#endif /* !SERVER_H */
