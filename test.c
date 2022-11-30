<<<<<<< HEAD
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
        // send message
        sprintf(buff, "Messaggio da server linux.");
        send(client->sockfd, buff, strlen(buff), 0);        

        // Check se è json...
        // parsing
        cJSON* query = cJSON_ParseWithLength(buff, strlen(buff));
        cJSON* command = cJSON_GetObjectItemCaseSensitive(query, "command");
        cJSON* params = cJSON_GetObjectItemCaseSensitive(query, "params");

        // Printa messaggio da client
        printf("Query command: %s\n", command->valuestring);
        /*
        cJSON_ArrayForEach(query, params) {
          printf("Query param: %s\n", par)
        }
        */
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

  printf("Uscito");
  close(client->sockfd);
  free(client);
  pthread_detach(pthread_self());
  return NULL;
}


pthread_t tid;
void launch(struct Server* server)
{
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
=======
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


// Struct describing a Client
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
        // send message
        sprintf(buff, "Messaggio da server linux.");
        send(client->sockfd, buff, strlen(buff), 0);
        printf("%s\n", buff);
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

  printf("Uscito");
  close(client->sockfd);
  free(client);
  pthread_detach(pthread_self());
  return NULL;
}


pthread_t tid;
void launch(struct Server* server)
{
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

    sleep(1);
  }
}

int main() 
{
  struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
  server.launch(&server);
  close(server.socket);
>>>>>>> 3ccc1c85a67cf4d54ea1d81da5ef1e348bc33fe9
}