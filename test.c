#include "lib/server.h"
#include "lib/HTTPRequest.h"
#include <stdio.h>
#include <string.h>

#include "lib/externals/cJSON.h"

#include <fcntl.h> // for open
#include <unistd.h> // for close


char* jsonTest()
{
    cJSON* persona = cJSON_CreateObject();
    
    cJSON_AddStringToObject(persona, "nome", "CARMINE");
    cJSON_AddStringToObject(persona, "cognome", "ARENA");
    cJSON_AddNumberToObject(persona, "eta", 69.0f);

    char* string = cJSON_Print(persona);
    cJSON_Delete(persona);

    return string;
}

void launch(struct Server* server)
{
  char buffer[1204];
  printf("===== WAIT FOR CONNECTION =====\n");
  int address_length = sizeof(server->address);
  while (1)
  {
    int new_socket = accept(server->socket, (struct sockaddr*)&server->address, (socklen_t*)&address_length);
    // invia messaggio etc
    read(new_socket, buffer, 1024);
    //struct HTTPRequest request = HTTPRequest_constructor(buffer);
    printf("%s", buffer);
    printf("%s", buffer);
    if (strncmp(buffer,"get-all-drinks", strlen("get-all-drinks")) == 0)
    {
      printf("PRENDO TUTTI I DRINKS\n");
    }
    // TODO: usare json
    //char* hello = "Messaggio ricevuto dal server Unix";
    char* jsonString = jsonTest();
    printf("%s\n",jsonString);
    write(new_socket, jsonString, strlen(jsonString));
    close(new_socket);
  }

}

int main() 
{
  struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
  server.launch(&server);
  close(server.socket);
}