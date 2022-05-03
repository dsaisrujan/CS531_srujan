/******************************************
Name of Header:     customer.h
Purpose:            Admin options of the database. Able to
                    add entries and delete from the database.

*******************************************/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string.h>
#include "mysql_connect.h"
#include "add_product.h"
#include "display_customer.h"

void customer(MYSQL *conn)
{
    char table[1];
    MYSQL_ROW row;
    MYSQL_RES *result,*result2;
    char h[1];
    char tb_name[50];
	do{
		printf("\n------------------------- Menu -------------------------\n");
		printf("1) Select categories\n");
		printf("2) Delete Product Info\n");
		printf("3) Display the list of Products\n");
		printf("4) Quit\n");
		printf("\n\nPlease enter your selection:  ");

        //Taking in ans, fgets will ignore non int values.
		fgets(ans, BUFF, stdin);
		//Removing extra space from the buffer.
		ans[strcspn(ans, "\n")] = 0;

		switch(ans[0]){
			case '1':
				printf("\n select categories:");
				snprintf(query, 1000,"SELECT `category_id`,`category_name` FROM `inventory`");
                if(mysql_query(conn, query) !=0)
                {
                    printf("Query failed  with the following message:\n");
                    printf("%s\n", mysql_error(conn));
                    exit(1);
                }
                result = mysql_store_result(conn);
                //printf("Number of rows: %ld\n", (long) mysql_num_rows(result));
                printf("\n------------------------- Menu -------------------------\n");
                while((row = mysql_fetch_row(result)) != NULL){
                    printf("%s) %s\n",row[0],row[1]);

                }
                printf("select which category do you want to buy:");
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
                //strcpy(tb_name,row[0]);
                display_customer(row[0],atoi(h),conn);
                /*snprintf(query2,1000,"SELECT * FROM %s",row[0]);
                if(mysql_query(conn, query2) !=0)
                {
                    printf("Query failed  with the following message:\n");
                    printf("%s\n", mysql_error(conn));
                    exit(1);
                }
                result2 = mysql_store_result(conn);
                printf("\n------------------------- Menu -------------------------\n");
                while((row = mysql_fetch_row(result2)) != NULL){
                    printf("%s) %s %s %s %s\n",row[0],row[1],row[2],row[3],row[4]);
                }*/

                //display_customer(tb_name,atoi(h),conn);

                //display shopping cart

				break;
			case '2':
				printf("\nDeleting product...");
				break;
			case '3':
				printf("\nDisplaying list of products...");
				break;
			case '4':
				printf("\nGoing back to Main Menu...\n");
				ans[0] = '5';                               //If I did ans = 4, I would break out of main menu.
				break;
			default:
				printf("Invalid entry\n");
		}
        }
	while(ans[0]!= '5');


}




#endif // CUSTOMER_H
