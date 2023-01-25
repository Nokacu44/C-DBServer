
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
  else if(strncmp(command, "updateUserInfo", strlen(command)) == 0) {
      return updateUserInfo(con, param, length);
  }
  else if(strncmp(command, "updatePassword", strlen(command)) == 0) {
      return updatePassword(con, param, length);
  }
  else if(strncmp(command, "getUserInfo", strlen(command)) == 0) {
      return getUserInfo(con, param, length);
  }
  else if(strncmp(command, "deleteUser", strlen(command)) == 0) {
      return deleteUser(con, param, length);
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

    printf("QUERY COMPOSTA FINALE: %s\n", query);
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

queryResult_t* updateUserInfo(MYSQL* con, char** param, int length){

    queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
    res->error = 0;
    res->result = NULL;

    char* query = "UPDATE users AS u SET u.nome = '";
    query = concat(query, param[1]);
    query = concat(query, "', u.cognome = '");
    query = concat(query, param[2]);
    query = concat(query, "', u.phone = '");
    query = concat(query, param[3]);
    query = concat(query, "', u.address = '");
    query = concat(query, param[4]);
    query = concat(query, "', u.cap = '");
    query = concat(query, param[5]);
    query = concat(query, "', u.city = '");
    query = concat(query, param[6]);
    query = concat(query, "', u.province = '");
    query = concat(query, param[7]);
    query = concat(query, "' WHERE (u.username = '");
    query = concat(query, param[0]);
    query = concat(query, "')");

    if (mysql_query(con, query)) {
        res->error = print_and_return_error(con);
        return res;
    }

    printf("QUERY COMPOSTA FINALE: %s\n", query);
    return res;
}

queryResult_t* updatePassword(MYSQL* con, char** param, int length){

    queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
    res->error = 0;
    res->result = NULL;

    char* query = "UPDATE users AS u SET u.passw = '";
    query = concat(query, param[1]);
    query = concat(query, "' WHERE u.username = '");
    query = concat(query, param[0]);
    query = concat(query, "'");

    if (mysql_query(con, query)) {
        res->error = print_and_return_error(con);
        return res;
    }

    printf("QUERY COMPOSTA FINALE: %s\n", query);
    return res;
}

queryResult_t* getUserInfo(MYSQL* con, char** param, int length){

    queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
    res->error = 0;
    res->result = NULL;

    char* query = "SELECT u.nome, u.cognome, u.phone, u.address, u.cap, u.city, u.province FROM users AS u WHERE u.username = '";
    query = concat(query, param[0]);
    query = concat(query, "'");

    if (mysql_query(con, query)) {
        res->error = print_and_return_error(con);
        return res;
    }

    MYSQL_RES* result = mysql_store_result(con);
    res->result = result;

    printf("QUERY COMPOSTA FINALE: %s\n", query);
    return res;
}

queryResult_t* deleteUser(MYSQL* con, char** param, int length){

    queryResult_t* res = (queryResult_t*) malloc(sizeof(queryResult_t));
    res->error = 0;
    res->result = NULL;

    char* query = "DELETE FROM users AS u WHERE u.username = '";
    query = concat(query, param[0]);
    query = concat(query, "'");

    if (mysql_query(con, query)) {
        res->error = print_and_return_error(con);
        return res;
    }

    printf("QUERY COMPOSTA FINALE: %s\n", query);
    return res;
}

