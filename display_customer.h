/******************************************
Name of Header:     display_customer.h
Purpose:            Displays items in database to shop. Also
                    responsible for checking out, sorting and
                    producing total of items. The shopping cart
                    is also printed out to a file called receipts.


*******************************************/

#ifndef DISPLAY_CUSTOMER_H
#define DISPLAY_CUSTOMER_H

#include <string.h>
#include "mysql_connect.h"
#include "add_product.h"

static int uni_cat_cntr =0;                 //Counter for carts
float tot_prc =0;                        //Total price of all products
int ar[100];                                //Array items selected
int row_count = 0;                          //Row count for printing
int num_fields = 0;                         //Num of fields for printing query
static int prod[100];                       //Product number for shopping cart
static char tbnames[100][100];              //Table name double array
int tmprc=0;                                //Temporary product total

float tax = .06;                             //Sales tax int


void display_customer(char *tb_name,int k,MYSQL *conn, int select)
{
    /*if(elsflg == 1){
        uni_cat_cntr -=1;
    }*/
    FILE *fp;
    char table[1];


    MYSQL_ROW row,row2;
    MYSQL_RES *result,*result2;
    char h[1];
    char b[1];

    if (select == 1)
    {
        strcpy(tbnames[uni_cat_cntr],tb_name);

        snprintf(query, 1000, "SELECT COUNT(*) as size FROM %s",tb_name);
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
            printf("\n%s is sold out!  There are no more items to sell here.Returning...",tb_name);
            return;
        }
    else{

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
//Asking to sort the products
//Price : 1&2, Brand : 3, Condition, 4, ID, 5.
//Starts originally with ID sorting.
do{
    printf("\nSort the product by Price low to high press 1");
    printf("\nSort the product by Price high to low press 2");
    printf("\nSort the product by Brand press 3");
    printf("\nBuy a product press 4");
    printf("\nSelection: ");
    fgets(h,BUFF,stdin);
    h[strcspn(h,"\n")] = 0;

    if((h[0])=='1'){
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
    if((h[0])=='2'){
        snprintf(query,1000,"SELECT * FROM %s ORDER BY %s.`Price` DESC",tb_name,tb_name);
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
    if((h[0])=='3'){
        snprintf(query,1000,"SELECT * FROM %s ORDER BY %s.`Brand` ASC",tb_name,tb_name);
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
    //Ommited out Condition and ID since customer doesn't usually care about that
    /*
    if((h[0])=='4'){
        snprintf(query,1000,"SELECT * FROM %s ORDER BY %s.`Brand` ASC",tb_name,tb_name);
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
    if((h[0])=='5'){
        snprintf(query,1000,"SELECT * FROM %s ORDER BY %s.`id` ASC",tb_name,tb_name);
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
    } */
}
while(h[0] != '4');
    printf("select which product do you want to add to cart:");
    fgets(h,BUFF,stdin);
    h[strcspn(h,"\n")] = 0;

    //Showing what id is selected to put in our cart
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

        }
        printf("\t|-----------------------------------------------|\n");
        printf("\t|your cart total price + sales tax (6%) is : $%.2f\t\t\t|\n",tot_prc + (tot_prc *tax) );

        printf("\t*************************************************\n");
        printf("Do you want to add more to your cart (Y/N):");
        fgets(b,BUFF,stdin);
        b[strcspn(b,"\n")] = 0;
        if(towlower(b[0])=='y'){
    return;
    }
    select = 2;
        }
    }//End of IF === 1

    //if select == 2 this is we show our shopping cart
    //Responsible for printing out to a file and showing user
    //The shopping cart.
if(select == 2)
{
    printf("\n\t******************* Your Cart *******************\n");
    printf("\t|\tName, Price, Brand, Item Condition\t| \n");
    printf("\t|-----------------------------------------------|\n");

    //For loop going though shopping cart
    for(int l =0;l <uni_cat_cntr;l++){

        //Query of selecting each id in the cart, and adding it to the query to print out
        snprintf(query,1000,"SELECT * FROM %s WHERE `id` = %d",tbnames[l],prod[l]);
        if(mysql_query(conn, query) !=0)
        {
            printf("Query failed  with the following message:\n");
            printf("%s\n", mysql_error(conn));
            exit(1);
        }
    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    //print statement showing all items in cart
    printf("\t|\t %s, %s, %s, %s\t\n",row[1],row[2],row[3],row[4]);
        }
        printf("\t|-----------------------------------------------|\n");
        //If empty, we stop here. Can probably merge this around.
        if(tot_prc == 0)
        {
            printf("\t|Your cart is empty!\t\t\t\t|\n");
        }
        else
        {
            printf("\t|your cart total price + sales tax (6%) is : $%.2f\t\t\t|\n",tot_prc + (tot_prc *tax) );
        }
printf("\t*************************************************\n");
//Checking out shopping cart
printf("Do you want to check out (Y/N):");
    fgets(h,BUFF,stdin);
    h[strcspn(h,"\n")] = 0;
    if(towlower(h[0])=='y'){
        printf("please wait while we confirm your order....\n");
        //Querying so we delete this from inventory
        snprintf(query2,1000,"UPDATE `inventory` SET `instock` = `instock`-1 WHERE `inventory`.`category_id` = %d",k);
        if(mysql_query(conn, query2) !=0)
        {
            printf("Query failed  with the following message:\n");
            printf("%s\n", mysql_error(conn));
            exit(1);
        }
        int id = mysql_insert_id(conn);

        //Opening file to put in reciepts
        //This part of the code will go through our uni_cat_cntr and print it out as our
        //Bill.
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

        //After receiving query, we print it out in the rows and give the total amount at the end.
        fprintf(fp,"%s %s %s %s\n",row[1],row[2],row[3],row[4]);


        fprintf(fp,"\n-------------------------------------------------\n");
        }
        fprintf(fp,"\nYou paid + sales tax: $%.2f\n",tot_prc + (tot_prc * tax));
        fclose(fp);


        //Resetting all counters for a fresh new cart.
        ar[uni_cat_cntr]=0;
        prod[uni_cat_cntr]=0;
        tbnames[uni_cat_cntr][0]='\0';
        uni_cat_cntr = 0;
        printf("\nyou paid: $%.2f\n",tot_prc + (tot_prc * tax));
        printf("ordered successfully");

        //Putting total to 0
        tot_prc = 0;
    }

    //If the user makes a mistake, can delete the last product in cart
    //Program can only delete from last item in cart
    else{
        printf("do you want to delete the last product in the cart (Y/N):");
        fgets(h,BUFF,stdin);
        h[strcspn(h,"\n")] = 0;
        if(towlower(h[0])=='y'){

        ar[uni_cat_cntr]=0;
        prod[uni_cat_cntr]=0;
        tbnames[uni_cat_cntr][0]='\0';
        uni_cat_cntr-=1;

        //Minusing from total
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

    printf("\t|\t %s, %s, %s, %s\t\n",row[1],row[2],row[3],row[4]);

        }
        printf("\t|-----------------------------------------------|\n");
        printf("\t|your cart total price: $%2f\t\t\t|\n",tot_prc + (tot_prc * tax));

printf("\t*************************************************\n");
    }
        return;
    }

  } //End IF == 2
}// End main

#endif // DISPLAY_CUSTOMER_H
