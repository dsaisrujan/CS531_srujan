/******************************************
Authors:        Kevin Cochran,SAI SRUJAN DANDYALA
G_Numbers:      G01325780
Date:           April 18, 2022
Last Updated:   April 22, 2022
Purpose:        Project will connect to an e-commerce
                SQL database and display menus on how to
                manipulate the e-commerce database. User will
                be able to either search for products and add to a
                shopping cart, or use admin options of adding to or
                deleting a table in the database.

Platform:       Windows
Version:        1.0
Sources:        CS531 Powerpoint slides
                https://docs.oracle.com/en-us/iaas/mysql-database/index.html
                https://www.mysqltutorial.org/


*******************************************/
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "mysql_connect.h"
#include "admin.h"
#include "customer.h"

int main ()
{
    MYSQL *conn;                        //MYSQL connection variable
    conn = mysql_init(NULL);            //SQL initiation set to NULL
    char p[1];

    //Checking if all things in mysql_connect.h is able to connect to a database.
    //Make sure you have the right information if not connecting when editing mysql_connect.h
    if(!(mysql_real_connect(conn,host,user,pass,dbname,0,NULL,0))){
        fprintf(stderr,"\nError %s[%d]\n",mysql_error(conn),mysql_errno(conn));
        printf("Make sure you have the right information in mysql_connect.h for this program to work.");
        exit(1);
    }
    //printf("Connection Successful to the database is Successful\n");
	do{
		printf("\t ------------------------- Menu -------------------------\n");
		printf("\t|\t\t\t1) Login\t\t\t|\n");
		printf("\t|\t\t\t2) Quit\t\t\t\t|\n");
		printf("\t --------------------------------------------------------\n");
		/*printf("3) My Shopping Cart\n");
		printf("4) Customer\n");
		printf("5) Quit\n");*/
		printf("Please enter your selection:");

        //Taking in ans, fgets will ignore non int values.
		fgets(ans, BUFF, stdin);
		//Removing extra space from the buffer.
		ans[strcspn(ans, "\n")] = 0;

		switch(ans[0]){
			case '1':
				printf("\n\t ------------------------- Login -----------------------\n");
			    printf("\t|\t\t\t1) Admin\t\t\t|\n\t|\t\t\t2) Customer\t\t\t|\n");
				printf("\t -------------------------------------------------------\n");
				printf("please enter your choice:");
				fflush(stdin);
				fgets(p,BUFF,stdin);
				p[strcspn(p, "\n")] = 0;
				int pp = atoi(p);
			    if(pp==1){
                  printf("\nGoing to Admin Menu...");
                  admin(conn);
			    }
			    else if(pp==2){
                    printf("\nGoing to Customer Menu...");
                    customer(conn);
			    }

				break;
			case '2':
				printf("\nQuitting...\n");
				exit(1);
				break;

			default:
				printf("Invalid entry\n");
		}
	}
	while(ans[0]!= '4');
    printf("\nHappy shopping :) ");

    //Closing the connection when we are done with the database.
    //Notice how I only did it here, because if I send a query and fail, that does not
    //necessarily mean I want to close the connection, I can retry with it still open.
    mysql_close(conn);

    return 0;
}
