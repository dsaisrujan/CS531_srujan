/******************************************
Name of Header:     delete_product.h
Purpose:            Deletes a product table or row in a database.

*******************************************/

#ifndef DELETE_PRODUCT_H
#define DELETE_PRODUCT_H

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "mysql_connect.h"

void delete_product(int select, MYSQL *conn)
{
    int num_fields;                     //Number of fields in a sql query
    int row_count;                      //Counting in case of no rows on a table
    int idd;
    char table[25];
    char id[25];
    char ans[2];                        //double checking the user if they really want something deleted.
    MYSQL_RES *result;

    MYSQL_ROW row;

    //If one is selected, we delete a whole table
    if(select == 1)
    {
        if(mysql_query(conn,"SHOW TABLES FROM kcochra7"))
        {
            printf("\nError, no tables to show.");
            return;
        }

        //Storing result from the query earlier
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
        printf("\nWhat table did you want to delete?");
        printf("\nTable: ");

        fgets(table,BUFF,stdin);
        table[strcspn(table,"\n")] = 0;

        //Confirming table deletion
        printf("\n***Are you sure you want to delete %s? This will permanently delete the table and all records", table);
        printf("\nPress Y to confirm: ");
        fgets(ans,BUFF,stdin);
        ans[strcspn(ans,"\n")] = 0;
        ans[0] = toupper(ans[0]);
        if(ans[0] == 'Y')
        {
            //Sending drop query, if table is not there we display an error and leave.
            printf("\nDeleting table %s", table);
            snprintf(query, 1000, "DROP TABLE %s", table);
            if(mysql_query(conn, query))
            {
                printf("\nError, unable to send query. Check table name.");
                return;
            }
            else
            {
                printf("\n%s has been dropped from the database.", table);
                return;
            }

        }
        else
        {
            printf("\nReturning...");
            return;
        }
    }

    //If two is selected, we delete a single row out of a table
    if(select == 2)
    {
        if(mysql_query(conn,"SHOW TABLES FROM kcochra7"))
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
        printf("\nWhat table did you want to delete from?");
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
            printf("\nNo records to be deleted in %s. Returning...",table);
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
                printf("%s",row[i]);
            }
            printf("\n");
        }

        //Acquire ID from row, since every record will have an ID in it.
        printf("\nWhat ID did you want deleted?");
        printf("\nID: ");
        fgets(id, BUFF, stdin);
        id[strcspn(id,"\n")] = 0;
        idd = atoi(id);
        printf("\n***Are you sure you want to delete ID: %d? This will permanently delete the record", idd);
        printf("\nPress Y to confirm: ");
        fgets(ans,BUFF,stdin);
        ans[strcspn(ans,"\n")] = 0;
        ans[0] = toupper(ans[0]);           //Changes answer to upper no matter what
        if(ans[0] == 'Y')
        {
            printf("\nDeleting record %s", id);
            snprintf(query, 1000, "DELETE FROM %s WHERE id = '%d'", table, idd);
            if(mysql_query(conn, query))
            {
                printf("\nError, unable to send query. Check item ID inputed.");
                return;
            }
            else
            {
                printf("\nItem ID: %d has been dropped from the table %s.", idd, table);
                return;
            }

        }
        else
        {
            printf("\nReturning...");
            return;
        }

}
}
#endif // DELETE_PRODUCT_H

