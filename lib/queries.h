
#ifndef QUERIES_H
#define QUERIES_H
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

static MYSQL* con = NULL;

void finish_with_error(MYSQL*);
unsigned int print_and_return_error(MYSQL*);

unsigned int signup(char**, int);
unsigned int query_router(char*, char**, int);


#endif //QUERIES_H
