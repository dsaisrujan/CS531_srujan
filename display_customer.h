
/******************************************
Name of Header:     display_customer.h
Purpose:            Admin options of the database. Able to
                    add entries and delete from the database.

*******************************************/

#ifndef DISPLAY_CUSTOMER_H
#define DISPLAY_CUSTOMER_H

#include <string.h>
#include "mysql_connect.h"
#include "add_product.h"

static int uni_cat_cntr =0;
long int tot_prc =0;
int ar[100];
static int prod[100];
static char tbnames[100][100];
int tmprc=0;
//int elsflg = 0;
void display_customer(char *tb_name,int k,MYSQL *conn)
{
    /*if(elsflg == 1){
        uni_cat_cntr -=1;
    }*/
    FILE *fp;
    char table[1];
    //ar[uni_cat_cntr]=k;
    strcpy(tbnames[uni_cat_cntr],tb_name);
    MYSQL_ROW row,row2;
    MYSQL_RES *result,*result2;
    char h[1];
    char b[1];
    /*printf("select which product do you want to add to cart:");
    fgets(h,BUFF,stdin);
    h[strcspn(h,"\n")] = 0;*/

    snprintf(query,1000,"SELECT * FROM %s",tb_name);
                if(mysql_query(conn, query) !=0)
                {
                    printf("Query failed  with the following message:\n");
                    printf("%s\n", mysql_error(conn));
                    exit(1);
                }
                result = mysql_store_result(conn);
                printf("\n\t******************* Products ********************\n");
                printf("\t|\tID,  Name, Price, Brand, Item Condition\t| \n");
                printf("\t|------------------------------------------------\n");
                while((row = mysql_fetch_row(result)) != NULL){
                    
                    printf("\t|\t%s) %s, %s, %s, %s\t\n",row[0],row[1],row[2],row[3],row[4]);
                }
                printf("\t*************************************************\n");
//ask to sort the products
printf("Sort the product by price low to high(Y/N):");
fgets(h,BUFF,stdin);
h[strcspn(h,"\n")] = 0;
if(towlower(h[0])=='y'){
    snprintf(query,1000,"SELECT * FROM %s ORDER BY %s.`Price` ASC",tb_name,tb_name);
                if(mysql_query(conn, query) !=0)
                {
                    printf("Query failed  with the following message:\n");
                    printf("%s\n", mysql_error(conn));
                    exit(1);
                }
                result = mysql_store_result(conn);
                printf("\n\t******************* Products ********************\n");
                printf("\t|\tID,  Name, Price, Brand, Item Condition\t| \n");
                printf("\t|------------------------------------------------\n");
                while((row = mysql_fetch_row(result)) != NULL){
                    
                    printf("\t|\t%s) %s, %s, %s, %s\t\n",row[0],row[1],row[2],row[3],row[4]);
                }
                printf("\t*************************************************\n"); 
}

    printf("select which product do you want to add to cart:");
    fgets(h,BUFF,stdin);
    h[strcspn(h,"\n")] = 0;
    snprintf(query2, 1000,"SELECT * from %s WHERE `id` = %s",tb_name,h);
    prod[uni_cat_cntr]=atoi(h);
    ar[uni_cat_cntr]=k;
    if(mysql_query(conn, query2) !=0)
    {
     printf("Query failed  with the following message:\n");
     printf("%s\n", mysql_error(conn));
     exit(1);
    }
    result2 = mysql_store_result(conn);
    row2 = mysql_fetch_row(result2);
    tmprc = atoi(row2[2]);
    tot_prc += tmprc;
    //printf("k = %d,h = %d\t",k,atoi(h));
    uni_cat_cntr+=1;
    printf("\n\t******************* Your Cart *******************\n");
    printf("\t|\tName, Price, Brand, Item Condition\t| \n");
    printf("\t|-----------------------------------------------|\n");
    for(int l =0;l <uni_cat_cntr;l++){
        //printf("selected category ids: %d,%s\n", prod[l],tbnames[l]);

        snprintf(query,1000,"SELECT * FROM %s WHERE `id` = %d",tbnames[l],prod[l]);
        if(mysql_query(conn, query) !=0)
        {
            printf("Query failed  with the following message:\n");
            printf("%s\n", mysql_error(conn));
            exit(1);
        }
    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    printf("\t|\t %s, %s, %s, %s\t\n",row[1],row[2],row[3],row[4]);
    //printf("%s %s %s %s\n",row[1],row[2],row[3],row[4]);

        }
        printf("\t|-----------------------------------------------|\n");
        printf("\t|your cart total price: $%ld\t\t\t|\n",tot_prc);
    
printf("\t*************************************************\n");
printf("Do you want to add more to your cart (Y/N):");
fgets(b,BUFF,stdin);
b[strcspn(b,"\n")] = 0;
if(towlower(b[0])=='y'){
    return;
}

printf("you want to proceed to check out (Y/N):");
    fgets(h,BUFF,stdin);
    h[strcspn(h,"\n")] = 0;
    if(towlower(h[0])=='y'){
        printf("please wait while we confirm your order....\n");
        snprintf(query2,1000,"UPDATE `inventory` SET `instock` = `instock`-1 WHERE `inventory`.`category_id` = %d",k);
        if(mysql_query(conn, query2) !=0)
        {
            printf("Query failed  with the following message:\n");
            printf("%s\n", mysql_error(conn));
            exit(1);
        }
        int id = mysql_insert_id(conn);

        fp = fopen("reciepts/reciept.txt","w+");
        fprintf(fp,"\n-----------------------BILL----------------------\n");
        
        for(int l =0;l <uni_cat_cntr;l++){
        //printf("\ncategory ids: %d,%s", prod[l],tbnames[l]);

         snprintf(query,1000,"SELECT * FROM %s WHERE `id` = %d",tbnames[l],prod[l]);
        if(mysql_query(conn, query) !=0)
        {
            printf("Query failed  with the following message:\n");
            printf("%s\n", mysql_error(conn));
            exit(1);
        }
        result = mysql_store_result(conn);
        row = mysql_fetch_row(result);
        fprintf(fp,"%s %s %s %s\n",row[1],row[2],row[3],row[4]);

        fprintf(fp,"\nyou paid: $%ld\n",tot_prc);
        fprintf(fp,"\n-------------------------------------------------\n");
        }
        fclose(fp);

        ar[uni_cat_cntr]=0;
        prod[uni_cat_cntr]=0;
        tbnames[uni_cat_cntr][0]='\0';
        uni_cat_cntr-=1;
        printf("\nyou paid: $%ld\n",tot_prc);
        printf("ordered successfully");
    }
    else{
        printf("do you want to delete the last product in the cart (Y/N):");
        fgets(h,BUFF,stdin);
        h[strcspn(h,"\n")] = 0;
        if(towlower(h[0])=='y'){
        //elsflg=1;
        ar[uni_cat_cntr]=0;
        prod[uni_cat_cntr]=0;
        tbnames[uni_cat_cntr][0]='\0';
        uni_cat_cntr-=1;

        //printf("tmprc = %d",tmprc);
        tot_prc -= tmprc;

        printf("\n\t******************* Your Cart *******************\n");
        printf("\t|\tName, Price, Brand, Item Condition\t| \n");
        printf("\t|-----------------------------------------------|\n");
        for(int l =0;l <uni_cat_cntr;l++){
        //printf("\ncategory ids: %d,%s", prod[l],tbnames[l]);

         snprintf(query,1000,"SELECT * FROM %s WHERE `id` = %d",tbnames[l],prod[l]);
        if(mysql_query(conn, query) !=0)
        {
            printf("Query failed  with the following message:\n");
            printf("%s\n", mysql_error(conn));
            exit(1);
        }
    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    //printf("%s %s %s %s\n",row[1],row[2],row[3],row[4]);
    printf("\t|\t %s, %s, %s, %s\t\n",row[1],row[2],row[3],row[4]);

        }
        printf("\t|-----------------------------------------------|\n");
        printf("\t|your cart total price: $%ld\t\t\t|\n",tot_prc);
    
printf("\t*************************************************\n");
    }
        return;
    }


//return;
}




#endif // DISPLAY_CUSTOMER_H
