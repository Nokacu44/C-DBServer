
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "queries.h"
#include <mysql.h>

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int query_router(char* command, char** param, int length) {

  if(strncmp(command, "signup", strlen(command)) == 0){
      return signup(param, length);
  }
  else{
      return -1;
  }
}

int signup(char** param, int length){

    MYSQL *con = mysql_init(NULL);

    if (con == NULL){
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "48752211852", "userDB", 0, NULL, 0) == NULL){
        finish_with_error(con);
    }

    char* query = "INSERT INTO users(username, passw) VALUES (";

    for(int i=0; i<length; i++){
        printf("PARAMI: %s\n", param[i]);
        query = concat(query, "'");
        query = concat(query, param[i]);
        query = concat(query, "'");
        query = concat(query, ",");
    }

    int query_size = strlen(query);
    query[query_size-1] = '\0';
    query = concat(query, ")");

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    printf("QUERY COMPOSTA FINALE: %s\n", query);
    return 0;
}
