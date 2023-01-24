
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


queryResult_t* query_router(MYSQL* con, char* command, char** param, int length) {

  if(strncmp(command, "signup", strlen(command)) == 0) {
    return signup(con,param, length);
  }
  else if(strncmp(command, "login", strlen(command)) == 0) {
    return login(con,param, length);
  }
  else if(strncmp(command, "updatePreferences", strlen(command)) == 0) {
      return updatePreferences(con, param, length);
  }
  else if(strncmp(command, "getPreferences", strlen(command)) == 0) {
      return getPreferences(con, param, length);
  }
  else if (strncmp(command, "exit", strlen(command)) == 0) {
    queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
    res->error = 6969;
    res->result = NULL;
    return res;    
  }
  else{ /*EX*/
      queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
      res->error = -1;
      res->result = NULL;
      return res;
  }
}

queryResult_t* signup(MYSQL* con, char** param, int length){

    queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
    res->error = 0;
    res->result = NULL;

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
        res->error = print_and_return_error(con);
        return res;
    }
    
    printf("QUERY COMPOSTA FINALE: %s\n", query);
    return res;
}

queryResult_t* login(MYSQL* con, char** param, int length){

    queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
    res->error = 0;
    res->result = NULL;

    char* query = "SELECT loginCheckFunct(";

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
        res->error = print_and_return_error(con);
        return res;
    }

    MYSQL_RES* result = mysql_store_result(con);
    res->result = result;

    /*
    MYSQL_ROW row = mysql_fetch_row(result);
    printf("CREDENZIALI TROVATE? (0=NO, 1=SI): %s\n", row[0]);
    */
    //TODO: MANDARE BIT DI RISULTATO AL CLIENT ANDROID

    //TODO: O FORSE NO PERCHè GIà FUNZIONA?

    printf("QUERY COMPOSTA FINALE: %s\n", query);
    return res;
}

queryResult_t* updatePreferences(MYSQL* con, char** param, int length){

    queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
    res->error = 0;
    res->result = NULL;

    char* query = "UPDATE preferences SET value = value+1 WHERE(ingr_ref=(SELECT i.ingr_id FROM ingredients AS i WHERE i.ingr_name = ";
    query = concat(query, param[0]);
    query = concat(query, ") AND user_ref=(SELECT u.user_id FROM users AS u WHERE u.username = '");
    query = concat(query, param[1]);
    query = concat(query, "'))");

    if (mysql_query(con, query)) {
        res->error = print_and_return_error(con);
        return res;
    }

    return res;
}

queryResult_t* getPreferences(MYSQL* con, char** param, int length){

    queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
    res->error = 0;
    res->result = NULL;

    char* query = "SELECT i.ingr_name FROM preferences AS p JOIN ingredients AS i ON i.ingr_id=p.ingr_ref "
                  "WHERE p.user_ref = (SELECT u.user_id FROM users AS u WHERE u.username = '";
    query = concat(query, param[0]);
    query = concat(query, "') ORDER BY p.value DESC LIMIT 3");

    if (mysql_query(con, query)) {
        res->error = print_and_return_error(con);
        return res;
    }

    puts("fsss");
    MYSQL_RES* result = mysql_store_result(con);
    res->result = result;

    printf("QUERY COMPOSTA FINALE: %s\n", query);
    return res;
}