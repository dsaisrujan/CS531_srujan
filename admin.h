/******************************************
Name of Header:     admin.h
Purpose:            Admin options of the database. Able to
                    add entries and delete from the database.

*******************************************/

#ifndef ADMIN_H
#define ADMIN_H

#include "mysql_connect.h"
#include "add_product.h"
#include "delete_product.h"
#include "display.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void admin(MYSQL *conn)
{
    char table[1];
    int pcc;
    char pc[10];
    printf("\nenter admin passcode:\n");
    fflush(stdin);
    fgets(pc, BUFF, stdin);
    pc[strcspn(pc, "\n")] = 0;
    pcc = atoi(pc);
    
    if(pcc == 23){
	do{
        printf("\t------------------------- Admin Menu -----------------------\n");
		printf("\t|\t\t\t1) Insert Product Info\t\t|\n");
		printf("\t|\t\t\t2) Delete Product Info\t\t|\n");
		printf("\t|\t\t\t3) Display the list of Products\t|\n");
		printf("\t|\t\t\t4) Quit\t\t\t\t|\n");
        printf(" \t---------------------------------------------------------\n");
		printf("Please enter your selection:  ");

        //Taking in ans, fgets will ignore non int values.
		fgets(ans, BUFF, stdin);
		//Removing extra space from the buffer.
		ans[strcspn(ans, "\n")] = 0;

		switch(ans[0]){
			case '1':
				printf("\nInserting Product...");
				printf("\n please select the option \n1)to enter new category\n2)to enter products into category: \n");
				fgets(table,BUFF,stdin);
				table[strcspn(table,"\n")] = 0;

				if(table[0] == '1')
                {
                    add_product(1, conn);
                }
                else if(table[0] == '2')
                {
                    add_product(2, conn);
                }
                else
                {
                    printf("Invalid entry");
                }
				break;
			case '2':
				printf("\nDeleting product...");
				printf("\nPress 1 for table or 2 for row: ");
				fgets(table,BUFF,stdin);
				table[strcspn(table,"\n")] = 0;

				if(table[0] == '1')
                {
                    delete_product(1, conn);
                }
                else if(table[0] == '2')
                {
                    delete_product(2, conn);
                }
                else
                {
                    printf("Invalid entry");
                }
				break;
			case '3':
				printf("\nDisplaying data...");
				printf("\nPress 1 for a list of categories (tables in DB)\nPress 2 for selecting a single category(table) only\nPress 3 for all products in the categories: ");
				fgets(table,BUFF,stdin);
				table[strcspn(table,"\n")] = 0;

				if(table[0] == '1')
                {
                    display(1, conn);
                }
                else if(table[0] == '2')
                {
                    display(2, conn);
                }
                else if(table[0] == '3')
                {
                    display(3, conn);
                }
                else
                {
                    printf("Invalid entry");
                }
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

else{
        printf("wrong admin passcode!!\n please contact owner for admin privilage");
        return;
    }
}



#endif // ADMIN_H
