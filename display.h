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
    int num_fields;                     //Number of fields in a sql query
    int row_count;
    int k = 0;

    char table[25];
    char *table_holder[200];
    char id[25];
    char ans[2];                        //double checking the user if they really want something deleted.

    MYSQL_RES *result;


    MYSQL_ROW row;



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
    }

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

}
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

        printf("\n--------------Full data list---------------***");
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
        //Freeing result to see if this helps
        mysql_free_result(result);

        //Size of my table holder
        int length = (sizeof(table_holder)/sizeof(table_holder[0]));

        //I realized that if I do length of table_holder, I will go all the way to
        //a null value in my pointer string array. So I stop just when im about to reach
        //The null value with length -1
        for(int j = 0; j <length - 1; j++)
        {
            //Adding query for each element in table_holder.
            snprintf(query, 1000, "SELECT * FROM %s", table_holder[j]);
            if(mysql_query(conn,query)){
                printf("\nEnd of tables. Total items = %d", j);
                return;
            }

            //Getting new result and fetching it for my row query
            result = mysql_store_result(conn);
            num_fields = mysql_num_fields(result);
            printf("\n--------------Table %s---------------\n", table_holder[j]);
            while((row = mysql_fetch_row(result)))
            {
                //Printing out each record of the current table.
                for(int i = 0; i < num_fields; i++)
                {
                    printf(" %s", row[i]);
                }
                printf("\n");
            }
        }
    }
    return;
}
#endif // DISPLAY_H

