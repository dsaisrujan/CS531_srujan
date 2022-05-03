/******************************************
Name of Header:     add_product.h
Purpose:            Adds a product table or row in a database.

*******************************************/

#ifndef ADD_PRODUCT_H
#define ADD_PRODUCT_H

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "mysql_connect.h"

void add_product(int select, MYSQL *conn)
{
    int check;                          //Checking if attribute length is appropriate
    int num_fields;                     //Number of fields in a sql query
    int j = 0;
    long int stk =0;                          //Used for iterating through enter_data[] for adding to a row

    char table[25];
    char *enter_data[150];
    char attr_num[2];
    char *attr_name[150];

    MYSQL_ROW row;

    //Adding tables
    if(select == 1)
    {
        printf("\nAdding a table");
        printf("\nName of category: ");
        fgets(table,BUFF,stdin);
        table[strcspn(table,"\n")] = 0;

        //We preset the 4 attributes already because to make sure we can describe the products with the basic
        printf("\nWe automatically set 4 premade attributes (Key ID, Name, Price, Brand, Condition).");
        printf("\nHow many attributes did you want to add to %s:",table);

        fgets(attr_num,BUFF,stdin);
        attr_num[strcspn(attr_num,"\n")] = 0;
        check = atoi(attr_num);
        if(check > 6)
        {
            do
            {
                printf("\nError, too many attributes. Please select 6 or under attributes: ");
                fgets(attr_num,BUFF,stdin);
                attr_num[strcspn(attr_num,"\n")] = 0;
                check = atoi(attr_num);
            }
            while(check > 6);
        }
        for(int i = 0; i < check; i++)
        {
            //Allocating memory to pointer in array
            attr_name[i] = malloc(25);

            printf("\nName of attribute %d: ", i+1);
            fgets(attr_name[i],BUFF,stdin);
            attr_name[i][strcspn(attr_name[i],"\n")] = 0;
        }
        printf("please enter quantity of the %s to be added in stock:",table);
        scanf("%ld",&stk);
        printf("\nThank you. %s will be made.", table);

        //If else statements based on user selecting the number of tables.
        //So the query part in our code is used to put our user based inputs into the query.
        //Unable to just directly put it in SQL, because SQL is not C language. We need to first put it
        //In our query variable then we can send it to mysql.
        //Primary key, Name, Price, Brand, and Condition will be automatically made.

        printf("\nINSERTING THIS TABLE %s TO OUR DATABASE", table);
        if(check == 0)
        {
            //Funny thing about Condition, since it is mysql keyword, you need to put ` ` around the word otherwise
            //won't work.
            snprintf(query, 1000, "CREATE TABLE %s(id INT PRIMARY KEY AUTO_INCREMENT"
                                    " , Name VARCHAR(255), Price INT, Brand VARCHAR(255), `Condition` VARCHAR(255))",table);
            snprintf(query2,1000,"INSERT INTO `inventory` (`category_id`, `category_name`, `instock`) VALUES (NULL, '%s', '%ld')",table,stk);

        }
        else if(check == 1)
        {
            snprintf(query, 1000, "CREATE TABLE %s(id INT PRIMARY KEY AUTO_INCREMENT"
                                ",Name VARCHAR(255), Price INT, Brand VARCHAR(255), `Condition` VARCHAR(255),"
                                "%s VARCHAR(255))",table, attr_name[0]);
            snprintf(query2,1000,"INSERT INTO `inventory` (`category_id`, `category_name`, `instock`) VALUES (NULL, '%s', '%ld')",table,stk);
        }

        else if(check == 2)
        {
            snprintf(query, 1000, "CREATE TABLE %s(id INT PRIMARY KEY"
                           " AUTO_INCREMENT, Name VARCHAR(255), Price INT, Brand VARCHAR(255), `Condition` VARCHAR(255),"
                           " %s VARCHAR(255), %s VARCHAR(255))"
                           ,table, attr_name[0], attr_name[1]);
        }
        else if(check ==  3)
        {
            snprintf(query, 1000, "CREATE TABLE %s(id INT PRIMARY KEY"
                           " AUTO_INCREMENT, Name VARCHAR(255), Price INT, Brand VARCHAR(255), `Condition` VARCHAR(255),"
                           "Condition VARCHAR(255), %s VARCHAR(255), %s VARCHAR(255),"
                           "%s VARCHAR(255))", table, attr_name[0], attr_name[1], attr_name[2]);
        }
        else if(check == 4)
        {
            snprintf(query, 1000, "CREATE TABLE %s(id INT PRIMARY KEY"
                           " AUTO_INCREMENT, Name VARCHAR(255), Price INT, Brand VARCHAR(255), `Condition` VARCHAR(255),"
                           "%s VARCHAR(255), %s VARCHAR(255)"
                           ", %s VARCHAR(255), %s VARCHAR(255))"
                           ,table, attr_name[0], attr_name[1], attr_name[2], attr_name[3]);
        }
        else if(check == 5)
        {
            snprintf(query, 1000, "CREATE TABLE %s(id INT PRIMARY KEY"
                           " AUTO_INCREMENT, Name VARCHAR(255), Price INT, Brand VARCHAR(255), `Condition` VARCHAR(255),"
                           "%s VARCHAR(255), %s VARCHAR(255)"
                           ", %s VARCHAR(255), %s VARCHAR(255), %s VARCHAR(255))"
                           ,table, attr_name[0], attr_name[1], attr_name[2], attr_name[3], attr_name[4]);
            snprintf(query2,1000,"INSERT INTO `inventory` (`category_id`, `category_name`, `instock`) VALUES (NULL, '%s', '%ld')",table,stk);
        }
        else if(check == 6)
        {
            snprintf(query, 1000, "CREATE TABLE %s(id INT PRIMARY KEY"
                           " AUTO_INCREMENT, Name VARCHAR(255), Price INT, Brand VARCHAR(255), `Condition` VARCHAR(255),"
                           "%s VARCHAR(255), %s VARCHAR(255),%s VARCHAR(255), %s VARCHAR(255),"
                           "%s VARCHAR(255), %s VARCHAR(255))"
                           ,table, attr_name[0], attr_name[1], attr_name[2], attr_name[3], attr_name[4], attr_name[5]);
            snprintf(query2,1000,"INSERT INTO `inventory` (`category_id`, `category_name`, `instock`) VALUES (NULL, '%s', '%ld')",table,stk);
        }
        //Testing to make sure sql_query can go through. If not error is shown.
        if(mysql_query(conn, query)||mysql_query(conn,query2)){
            printf("\nError, unable to add table");
            }

        else
        {
            printf("\n\nTable made successfully!");
        }

        return;
    }

    //Adding rows
    if(select == 2)
    {
        printf("\nName of table: ");
        fgets(table,BUFF,stdin);
        table[strcspn(table,"\n")] = 0;

        //looks for name of table, if error returned we return to admin menu

        snprintf(query, 1000, "SELECT * FROM %s", table);
        if(mysql_query(conn, query)){
            printf("Error, unable to find %s table", table);
            return;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        num_fields = mysql_num_fields(result);

        printf("\n---------------%s Table Info---------------\n", table);
        while((row = mysql_fetch_row(result)))
        {
            for(int i = 0; i < num_fields; i++)
            {
                printf(" %s", row[i]);
            }
            printf("\n");
        }

        //For MYSQL only. This is where your database matters, might not work for others.
        //MySQL selects the column name from the megadatabse of all databases in information_schema
        //Then you can pick what you want to show and in this case we did columns in the users selected table.
        // SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'table_name';
        //ORDINAL_POSITION because it would put it in alphabetical order, not by inserted.
        snprintf(query, 1000, "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = '%s'"
                 " ORDER BY ORDINAL_POSITION", table);
        if(mysql_query(conn, query)||mysql_query(conn, query2)){
            printf("Error, unable to find %s table. SQL Select from table error.", table);
        }
        result = mysql_store_result(conn);
        num_fields = mysql_num_fields(result);


        //Once table is  found we display the requirements for entry
        //Then prompt user to enter the requirements
        printf("\n---------------%s entry requirements---------------\n", table);


        //While loop to go through result from MySql
        //Will first display the primary key for entry, then other attributes of the data
        while((row = mysql_fetch_row(result)))
        {
            for(int i = 0; i < num_fields; i++)
            {
                 //Since Primary ID, Name, Price, Brand, and Condition are made automatically, we will
                 //Make enter them in first.
                printf("\n\nOUR i = %d\n\n",i);
                //If j = 0, that is our Primary key. Record it as such for later.
                if(j == 0)
                {
                    //Allocating data for pointer array
                    enter_data[j] = malloc(25);
                    printf("--->Please enter the primary ID of item: ");
                    fgets(enter_data[0],BUFF,stdin);
                    enter_data[j][strcspn(enter_data[j],"\n")] = 0;
                    j++;
                }

                //Commented out my if statments since it wasn't working correctly.
                //User will have to enter in right information for now

                /*
                //If j = 1, that is our Name column.
                if(j == 1)
                {
                    //Allocating data for pointer array
                    enter_data[j] = malloc(25);
                    printf("***>Please enter in %s of item:", row[i]);
                    fgets(enter_data[j],BUFF,stdin);
                    enter_data[j][strcspn(enter_data[j],"\n")] = 0;
                    j++;
                }
                //If j = 2, that is our Price column.
                if(j == 2)
                {
                    //Allocating data for pointer array
                    enter_data[j] = malloc(25);
                    printf("???Please enter in %s of item:", row[i]);
                    fgets(enter_data[j],BUFF,stdin);
                    enter_data[j][strcspn(enter_data[j],"\n")] = 0;
                    check = atoi(enter_data[j]);
                    //Prices can't be less than or equal to 0.
                    if(check <= 0)
                    {
                        do
                        {
                            printf("\nWe aint selling anything for free! Please re-enter the item price:");
                            fgets(enter_data[j],BUFF,stdin);
                            enter_data[j][strcspn(enter_data[j],"\n")] = 0;
                            check = atoi(enter_data[j]);
                        }
                        while(check <= 0);
                    }
                    j++;
                }
                //If j = 3, that is our Brand name
                if(j == 3)
                {
                    //Allocating data for pointer array
                    enter_data[j] = malloc(25);
                    printf("!!!Please enter in %s of item:", row[i]);
                    fgets(enter_data[j],BUFF,stdin);
                    enter_data[j][strcspn(enter_data[j],"\n")] = 0;
                    j++;
                }
                //If j = 4, that is our Condition.
                if(j == 4)
                {
                    //Allocating data for pointer array
                    enter_data[j] = malloc(25);
                    printf("++++Please enter in %s of item:", row[i]);
                    fgets(enter_data[j],BUFF,stdin);
                    enter_data[j][strcspn(enter_data[j],"\n")] = 0;

                    //Sends string to upper for comparison
                    //Not working for me, maybe someone can solve this?
                   for(char *p = enter_data[j]; *p; p++)
                    {
                        *p = toupper(*p);
                    }
                    if(enter_data[j] != "NEW" || enter_data[j] != "REFURBISHED" ||
                        enter_data[j] != "USED" || enter_data[j] != "OPENED-BOX")
                    {
                        do
                        {
                            printf("\nCondition may only be New, Used, Refurbished, or Opened-box.");
                            printf("\nPlease re-enter the condition: ");
                            fgets(enter_data[j],BUFF,stdin);
                            enter_data[j][strcspn(enter_data[j],"\n")] = 0;
                            for(char *p = enter_data[j], *p, p++)
                            {
                                *p = toupper(*p);
                            }
                        }
                        while(enter_data[j] != "NEW" || enter_data[j] != "REFURBISHED"||
                        enter_data[j] != "USED" || enter_data[j] != "OPENED-BOX");
                    }
                    j++;
                } */
                else
                {
                    enter_data[j] = malloc(25);
                    printf("\nEnter the attribute of %s: ", row[i]);
                    fgets(enter_data[j],BUFF,stdin);
                    enter_data[j][strcspn(enter_data[j],"\n")] = 0;
                    j++;
                }
            }

        }
            printf("\n");

        //ORDER OF INSERTION : Primary ID, Name, Price, Brand, Condition and attributes from users
        printf("\nINSERTING ID: %s ROW INTO THIS TABLE %s ",enter_data[0],table);
        if(j < 4 )
        {
            printf("ERROR: Table is incorrectly put in our database. Please delete and re-add the table in database. ");
            return;
        }
        else if (j == 4)
        {
            snprintf(query, 1000, "INSERT INTO %s VALUES(%s, '%s', %s,'%s')",table, enter_data[0],
                     enter_data[1], enter_data[2], enter_data[3]);
        }
        else if (j == 5)
        {
            snprintf(query, 1000, "INSERT INTO %s VALUES(%s, '%s', %s,'%s', '%s')",table,enter_data[0], enter_data[1],
                     enter_data[2], enter_data[3], enter_data[4]);
        }
        else if (j == 6)
        {
            snprintf(query, 1000, "INSERT INTO %s VALUES(%s, '%s', %s,'%s', '%s', '%s')",
                     table,enter_data[0], enter_data[1], enter_data[2], enter_data[3], enter_data[4], enter_data[5]);
        }
        //Putting 7 to account for the id int we automatically put in for creating a table
        else if(j == 7 )
        {
            snprintf(query, 1000, "INSERT INTO %s VALUES(%s, '%s', %s,'%s', '%s', '%s', '%s')",
                     table,enter_data[0], enter_data[1], enter_data[2], enter_data[3],
                     enter_data[4], enter_data[5], enter_data[6]);
        }
        else if(j == 8)
        {
            snprintf(query, 1000, "INSERT INTO %s VALUES(%s, '%s', %s,'%s', '%s', '%s', '%s')",
                     table,enter_data[0], enter_data[1], enter_data[2], enter_data[3],
                     enter_data[4], enter_data[5], enter_data[6], enter_data[7]);
        }
        else if(j == 9)
        {
            snprintf(query, 1000, "INSERT INTO %s VALUES(%s, '%s', %s,'%s', '%s', '%s', '%s')",
                     table,enter_data[0], enter_data[1], enter_data[2], enter_data[3],
                     enter_data[4], enter_data[5], enter_data[6], enter_data[7], enter_data[8]);
        }
        else if(j == 10)
        {
            snprintf(query, 1000, "INSERT INTO %s VALUES(%s, '%s', %s,'%s', '%s', '%s', '%s')",
                     table,enter_data[0], enter_data[1], enter_data[2], enter_data[3],
                     enter_data[4], enter_data[5], enter_data[6], enter_data[7], enter_data[8], enter_data[9]);
        }
        else
        {
            printf("\nInvalid values. ");
        }

        if(mysql_query(conn,query)){
            printf("\nERROR: Unable to send in query. Check your values. ");
        }
        else
        {
            printf("\n\nRecord successfully made!");
        }
        return;
    }
}
#endif // ADD_PRODUCT_H

