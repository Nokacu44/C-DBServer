
#include <string.h>
#include "queries.h"

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

unsigned int print_and_return_error(MYSQL* con) {
    const char* error = mysql_error(con);
    unsigned int number = mysql_errno(con);

    fprintf(stderr, "%s with code: %d \n", error, number);
    return number;
}
 
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


unsigned int query_router(MYSQL* con, char* command, char** param, int length) {

  if(strncmp(command, "signup", strlen(command)) == 0){
      return signup(con,param, length);
  }
  else{
      return -6969;
  }
}

unsigned int signup(MYSQL* con, char** param, int length){


    char* query = "INSERT INTO users(username, passw) VALUES (";

    // Add params to the query
    for(int i=0; i<length; i++){
        printf("PARAMI: %s\n", param[i]);
        query = concat(query, "'");
        query = concat(query, param[i]);
        query = concat(query, "'");
        query = concat(query, ",");
    }
    
    // Remove last ","
    int query_size = strlen(query);
    query[query_size-1] = '\0';

    // Add ")"
    query = concat(query, ")");

    if (mysql_query(con, query)) {
        return print_and_return_error(con);
    }

    printf("QUERY COMPOSTA FINALE: %s\n", query);
    return 0;
}
