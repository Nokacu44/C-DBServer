#include "lib/server.h"
#include <errno.h>
#include "lib/externals/cJSON.h"
#include <mysql.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> // for open()
#include <unistd.h> // for close()
#include <arpa/inet.h>
#include <stdlib.h>
#include "lib/queries.h"


// Struct del client
typedef struct {
  struct sockaddr_in address;
  int sockfd;
} client_t;

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

void *handle_client(void *cli) {
  printf("Entered handle");
  char buff[2048];
  int leave_flag = 0;

  client_t *client = (client_t *)cli;

  while(1) {
    if (leave_flag) break;

    int receive = recv(client->sockfd, buff, 2048, 0);
    if (receive > 0) {
      if (strlen(buff) > 0) {
 
        // Check se è json...
        // parsing
        cJSON* query = cJSON_ParseWithLength(buff, strlen(buff));
        cJSON* command = cJSON_GetObjectItemCaseSensitive(query, "command");
        cJSON* params = cJSON_GetObjectItemCaseSensitive(query, "params");

        // Printa messaggio da client
        printf("Query command: %s\n", command->valuestring);
        

        const cJSON* parametro = NULL;
        int length = cJSON_GetArraySize(params);
        char** array = malloc(length*sizeof(char*));

        int i = 0;
        cJSON_ArrayForEach(parametro, params) {
          array[i] = malloc((strlen(parametro->valuestring) + 1) * sizeof(char));
          strcpy(array[i], (char*)parametro->valuestring);
          printf("Query param: %s\n", parametro->valuestring);
          ++i;
        }

        unsigned int error = query_router(command->valuestring, array, length);

        for(int j=0; j<length; j++){
            free(array[j]);
        }
        free(array);

        // send message
        sprintf(buff, "Messaggio da server linux -> codice query: %d", error);
        send(client->sockfd, buff, strlen(buff), 0);       
      }
    } else if (receive == 0 || strncmp(buff, "exit", strlen("exit")) == 0) {
      printf("Client uscito.");
      leave_flag = 1;
    } else {
      printf("ERROR: -1\n");
      leave_flag = 1;
    }

    bzero(buff, 2048);
  }

  printf("Client uscito.");
  close(client->sockfd);
  free(client);
  pthread_detach(pthread_self());
  return NULL;
}


pthread_t tid;
void launch(struct Server* server)
{
  // Init mysql
  con = mysql_init(NULL);

  if (con == NULL) {
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(1);
  }

  #ifdef __APPLE__
  if (mysql_real_connect(con, "localhost", "root", "48752211852", "userDB", 0, NULL, 0) == NULL){
      finish_with_error(con);
  }
  #endif



  char buffer[1204];
  printf("===== WAIT FOR CONNECTION =====\n");
  struct sockaddr_in cli_addr;
  while (1)
  {
    int address_length = sizeof(cli_addr);
    int new_socket = accept(
        server->socket, 
        (struct sockaddr*)&cli_addr, 
        (socklen_t*)&address_length
    );

    // Create client
    client_t* cli = (client_t*)malloc(sizeof(client_t));
    cli->address = cli_addr;
    cli->sockfd = new_socket;

    pthread_create(&tid, NULL, &handle_client, (void*)cli);

    sleep(1); // Previene uso eccessivo della ram
  }
}

int main() 
{
  struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
  server.launch(&server);
  close(server.socket);
}
