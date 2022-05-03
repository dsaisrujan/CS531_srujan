/******************************************
Name of Header:     mysql_connect.h
Purpose:            Connecting to a database.

*******************************************/

#ifndef MYSQL_CONNECT_H
#define MYSQL_CONNECT_H

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF 100                            //I put the buffer here for user entries to make it simple.

char ans[2];                                //Storing user menu selection entry
char query[1000];
char query2[1000];
char query3[1000];

static char *host = "127.0.0.1";            //Local host or aka the octet address for your database
static char *user = "root";                 //Put your username (here is root for me since its my local machine)
static char *pass = "root";            //Put your password here
static char *dbname = "kcochra7";           //Put your database name here

unsigned int flag = 0;


#endif // MYSQL_CONNECT_H
