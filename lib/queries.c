
#include <string.h>
#include <stdio.h>

void query_router(char* command, char* param) {
  if (strncmp(command, "get-carmine", strlen(command)) == 0) {
    get_carmine(param);
    // return risultato o errore
  }
  // ...
}



void get_carmine(char* param) {
  // roba
}
