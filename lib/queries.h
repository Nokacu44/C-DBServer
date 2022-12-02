
#ifndef QUERIES_H
#define QUERIES_H
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int error;
  MYSQL_RES* result;
} queryResult_t; 


void finish_with_error(MYSQL*);
unsigned int print_and_return_error(MYSQL*);

queryResult_t* signup(MYSQL*, char**, int);
queryResult_t* login(MYSQL*, char**, int);
queryResult_t* query_router(MYSQL*,char*, char**, int);


#endif //QUERIES_H
