/******************************************
Name of Header:     display.h
Purpose:            Deletes a product table or row in a database.

*******************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "mysql_connect.h"

void display(int select, MYSQL *conn)
{
    int num_fields = 0;                     //Number of fields in a sql query
    int row_count;                          //Counts number of rows so we dont display null tables
    int k = 0;                              //iterator

    char table[25];                         //Name of table holder
    char *table_holder[200];                //Holds pointers of names of tables
    char id[25];                            //Holds id
    char ans[2];                            //double checking the user if they really want something deleted.

    MYSQL_RES *result;                      //MYSQL_RES query
    MYSQL_ROW row;                          //MYSQL_ROW printer for row[i] manipulation


    //If select ==1, we are only showing the tables in the database.
    if(select == 1)
    {
        snprintf(query, 1000, "SHOW TABLES FROM %s", dbname);
        if(mysql_query(conn,query))
        {
            printf("\nError, no tables to show.");
            return;
        }

        result = mysql_store_result(conn);
        num_fields = mysql_num_fields(result);

        printf("\n---------------Table list---------------\n");
        while((row = mysql_fetch_row(result)))
        {
            for(int i =0; i< num_fields; i++)
            {
                printf("%s",row[i]);
            }
            printf("\n");
        }
        return;
    } //end if select == 1


    //If select 2, we are displaying a table of records.
    else if(select == 2)
    {
        snprintf(query, 1000, "SHOW TABLES FROM %s", dbname);
        if(mysql_query(conn,query)){
            printf("\nError, no tables to show.");
            return;
        }
        result = mysql_store_result(conn);
        num_fields = mysql_num_fields(result);

        printf("\n---------------Table list---------------\n");
        while((row = mysql_fetch_row(result)))
        {
            for(int i =0; i< num_fields; i++)
            {
                printf("%s",row[i]);
            }
            printf("\n");
        }

        //Asks what table the user wants to see
        printf("\nWhat table did you want to view");
        printf("\nTable: ");

        //Received table name, check if there are records to be deleted in the table
        fgets(table,BUFF,stdin);
        table[strcspn(table,"\n")] = 0;
        //SELECT COUNT(column*) as counter_name FROM table_name in MySQL
        snprintf(query, 1000, "SELECT COUNT(*) as size FROM %s",table);
        if(mysql_query(conn, query))
        {
            printf("\nError, unable to send query. Check table name.");
            return;
        }
        result = mysql_store_result(conn);
        num_fields = mysql_num_fields(result);

        //Since there is only one result coming out, we don't need a forloop
        while((row = mysql_fetch_row(result)))
        {
            //The string returned is turned to an int for comparison to 0.
            row_count = atoi(row[0]);

        }

         //If 0, we step out of this and return.
        if(row_count <= 0)
        {
            printf("\nNo records in %s. Returning...",table);
            return;
        }


        //Redoes query, technically this error statement should never be reached since first query mysql_query checks the name
        snprintf(query, 1000, "SELECT * FROM %s", table);
        if(mysql_query(conn, query))
        {
            printf("\nError, unable to send query. Check table name.");
            return;
        }
        result = mysql_store_result(conn);
        num_fields = mysql_num_fields(result);
        //Printing out current contents of Row
        printf("\n---------------Row list in %s---------------\n",table);
        while((row = mysql_fetch_row(result)))
        {
            for(int i =0; i< num_fields; i++)
            {
                printf(" %s ",row[i]);
            }
            printf("\n");
        }

} //end if select == 2
    //3rd option is displaying whole data base
    else if(select == 3)
    {
        snprintf(query, 1000, "SHOW TABLES FROM %s", dbname);
        //I don't add a conn print statement here because the last record will not give us a query
        if(mysql_query(conn,query)){
            return;
        }

        //Getting new result from query
        result = mysql_store_result(conn);
        num_fields = mysql_num_fields(result);

        printf("\n--------------Full data list------------------");
        printf("\n----------------------------------------------\n");
        while((row = mysql_fetch_row(result)))
        {
            for(int i =0; i< num_fields; i++)
            {
                //Here  I assign table_holder array pointer to new row (which is the table names)
                table_holder[k] = malloc(25);
                table_holder[k] = row[i];
                k++;
            }
        }

        //mysql_free_result(result); is not good to use, it makes the result undefined
        //for some reason. That is why earlier this display.h was not working properly.



        //Actually goes through an array of strings aka the table holders.
        //They contain all table names, and I simply go through each name in the array
        //And put it in a query and when I received the result, its just like earlier
        //of printing each row in my result.
        for(int i = 0; i < k; i++)
        {
            //Redoes query, technically this error statement should never be reached since first query mysql_query checks the name
            snprintf(query, 1000, "SELECT * FROM %s", table_holder[i]);
            if(mysql_query(conn, query))
            {
                printf("\nError, unable to send query. Check table name.");
                return;
            }
            result = mysql_store_result(conn);
            num_fields = mysql_num_fields(result);
            //Printing out current contents of Row
            printf("\n---------------Row list in %s---------------\n",table_holder[i]);
            while((row = mysql_fetch_row(result)))
            {
                for(int i =0; i< num_fields; i++)
                {
                    printf(" %s ",row[i]);
                }
                printf("\n");
            }
        }

    } //end if select == 3
    return;
}
#endif // DISPLAY_H

