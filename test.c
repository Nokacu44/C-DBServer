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

struct threadArgs {
  client_t* cli;
  MYSQL* con;
};

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

void *handle_client(void *args) {
  printf("Entered handle\n");
  char buff[2048];
  int leave_flag = 0;

  struct threadArgs* arguments = (struct threadArgs*)args;
  client_t *client = (client_t *)arguments->cli;

  while(1) {
    printf("INIZIO WHILE LOOP\n");
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

        queryResult_t* res = query_router(arguments->con, command->valuestring, array, length);

        cJSON* json_result = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_result, "error", res->error);
        cJSON* json_rows = cJSON_CreateArray();

        if (res->error == 0)
        {
          if (res->result != NULL) {
              MYSQL_ROW row;
              unsigned int num_fields;
              unsigned int i;

              num_fields = mysql_num_fields(res->result);
              while ((row = mysql_fetch_row(res->result)))
              {
                unsigned long *lengths;
                lengths = mysql_fetch_lengths(res->result);
                for(i = 0; i < num_fields; i++)
                {
                    cJSON_AddItemToArray(json_rows, cJSON_CreateString(row[i] ? row[i] : "NULL"));
                    printf("[%.*s] ", (int) lengths[i],
                            row[i] ? row[i] : "NULL");
                }
                printf("\n");
              }

              cJSON_AddItemToObject(json_result, "rows", json_rows);
          }
        } else if (res->error == 6969) {
          leave_flag = 1;
        }


        for(int j=0; j<length; j++){
            free(array[j]);
        }
        free(array);



        // Free results
        mysql_free_result(res->result);
        free(res);

        if (leave_flag == 1) {
          continue;
        }

        char* json_string = cJSON_Print(json_result);
        cJSON_Delete(json_result);

        // send message
        sprintf(buff, "%s\n", json_string);
        send(client->sockfd, buff, strlen(buff), 0);       

        printf("MESSAGGIO INVIATO\n");
      }
    } else if (receive == 0) {
      printf("Client uscito.\n");
      leave_flag = 1;
    } else {
      printf("ERROR: -1\n");
      leave_flag = 1;
    }
    printf("BUFF\n");
    bzero(buff, 2048);
  }

  printf("Client uscito.\n");
  close(client->sockfd);
  arguments->con = NULL;

  //free(arguments);
  free(client);
  pthread_detach(pthread_self());
  return NULL;
}


pthread_t tid;
void launch(struct Server* server)
{
  printf("===== SERVER STARTED =====\n");
  // Init mysql
  MYSQL* con = mysql_init(NULL);
  if (con == NULL) {
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(1);
  }
  #ifdef __APPLE__
  if (mysql_real_connect(con, "localhost", "root", "48752211852", "userDB", 0, NULL, 0) == NULL){
      finish_with_error(con);
  }
  #else
  if (mysql_real_connect(con, "localhost", "root", "poteredelcristallodiluna", "userDB", 0, NULL, 0) == NULL){
      finish_with_error(con);
  }
  #endif
  printf("DB Connection Stats: %s\n", mysql_stat(con));

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

    struct threadArgs args = {cli, con};
    pthread_create(&tid, NULL, &handle_client, (void*)&args);
    // Previene creazione di nuovi thread mentre client ancora connesso
    pthread_join(tid, NULL);
    sleep(1); // Previene uso eccessivo della ram
  }

  mysql_close(con);
}

int main() 
{
  struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
  server.launch(&server);
  close(server.socket);
}
