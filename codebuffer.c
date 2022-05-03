  printf("--------------------cart--------------------");
    snprintf(query,1000,"SELECT * FROM %s WHERE `id` = %s",tbnames[l],prod[l]);
        if(mysql_query(conn, query) !=0)
        {
            printf("Query failed  with the following message:\n");
            printf("%s\n", mysql_error(conn));
            exit(1);
        }
    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    printf("%s %s %s %s",row[1],row[2],row[3],row[4]);
    printf("--------------------------------------------------------------");