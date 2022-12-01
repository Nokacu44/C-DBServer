
#ifndef QUERIES_H
#define QUERIES_H
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

void finish_with_error(MYSQL*);
unsigned int print_and_return_error(MYSQL*);

unsigned int signup(MYSQL*, char**, int);
unsigned int query_router(MYSQL*,char*, char**, int);


#endif //QUERIES_H
