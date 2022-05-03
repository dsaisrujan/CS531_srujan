/******************************************
Name of Header:     customer.h
Purpose:            Menu for customers. Has two options to either leave
                    or search for products.

*******************************************/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string.h>
#include "mysql_connect.h"
#include "add_product.h"
#include "display_customer.h"

void customer(MYSQL *conn)
{
    char table[1];                                  //Holding which table customer wants to view
    MYSQL_ROW row;                                  //For query result printing of rows
    MYSQL_RES *result,*result2;                     //Holding query results
    char h[1];                                      //Holding what ID customer wants to buy
    char tb_name[50];                               //Holding name of tables
	do{
		printf("\n\t************************* Customer Menu *****************\n");
		printf("\t|\t\t\t1) Select categories\t\t|\n");
		printf("\t|\t\t\t2) My Shopping Cart\t\t|\n");
		printf("\t|\t\t\t3) Quit\t\t\t\t|\n");
        printf("\t*********************************************************\n");
		printf("Please enter your selection:  ");

        //Taking in ans, fgets will ignore non int values.
		fgets(ans, BUFF, stdin);
		//Removing extra space from the buffer.
		ans[strcspn(ans, "\n")] = 0;

		switch(ans[0]){
		    //Select your option for what shop you want
			case '1':
				printf("\n Select categories:");
				snprintf(query, 1000,"SELECT `category_id`,`category_name` FROM `inventory`");
                if(mysql_query(conn, query) !=0)
                {
                    printf("Query failed  with the following message:\n");
                    printf("%s\n", mysql_error(conn));
                    exit(1);
                }
                result = mysql_store_result(conn);
                //printf("Number of rows: %ld\n", (long) mysql_num_rows(result));
                printf("\n\t******************* Categories ************\n");
                while((row = mysql_fetch_row(result)) != NULL){
                    printf("\t|\t\t%s) %s\t\t\n",row[0],row[1]);

                }
                printf("\t*******************************************\n");
                printf("select ID of the category which you want to buy:");
                fgets(h,BUFF,stdin);
                h[strcspn(h,"\n")] = 0;
                int flag =0;
                int ides[50];
                int t=0;
                for(int i=0;i<t;i++){
                    if(ides[i]==atoi(h)){
                        flag = 1;
                    }
                }
                if(flag == 1){
                    printf("invalid entry");
                    break;
                }
                snprintf(query2,1000,"SELECT `category_name` FROM `inventory` WHERE `category_id` = %d",atoi(h));
                if(mysql_query(conn, query2) !=0)
                {
                    printf("Query failed  with the following message:\n");
                    printf("%s\n", mysql_error(conn));
                    exit(1);
                }
                result2 = mysql_store_result(conn);
                row = mysql_fetch_row(result2);
                display_customer(row[0],atoi(h),conn, 1);
				break;

				//View shopping cart
			case '2':
				printf("\nMy Shopping Cart...\n");
                display_customer(&ans[0],0,conn, 2);
				break;
            case '3':
                printf("\nReturning to previous menu\n");
                ans[0] = '4';
			default:
				printf("\nInvalid entry\n");
		}
        }
	while(ans[0]!= '4');


}




#endif // CUSTOMER_H
