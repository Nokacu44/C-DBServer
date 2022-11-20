#include "lib/server.h"
#include <neo4j-client.h>
#include <errno.h>
#include "lib/externals/cJSON.h"
#include <mysql.h>

#include <stdio.h>
#include <string.h>
#include <fcntl.h> // for open()
#include <unistd.h> // for close()


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

void neo4jTest()
{
    mysql_init(NULL);
   neo4j_client_init();

    /* use NEO4J_INSECURE when connecting to disable TLS */
    neo4j_connection_t *connection =
            neo4j_connect("neo4j://user:pass@localhost:7687", NULL, NEO4J_INSECURE);
    if (connection == NULL)
    {
        neo4j_perror(stderr, errno, "Connection failed");
        exit(1);
    }

    neo4j_result_stream_t *results =
            neo4j_run(connection, "RETURN 'hello world'", neo4j_null);
    if (results == NULL)
    {
        neo4j_perror(stderr, errno, "Failed to run statement");
        exit(1);
    }

    neo4j_result_t *result = neo4j_fetch_next(results);
    if (result == NULL)
    {
        neo4j_perror(stderr, errno, "Failed to fetch result");
        exit(1);

    }

    neo4j_value_t value = neo4j_result_field(result, 0);
    char buf[128];
    printf("%s\n", neo4j_tostring(value, buf, sizeof(buf)));

    neo4j_close_results(results);
    neo4j_close(connection);
    neo4j_client_cleanup();
}

void launch(struct Server* server)
{
  neo4jTest();

  char buffer[1204];
  printf("===== WAIT FOR CONNECTION =====\n");
  int address_length = sizeof(server->address);
  while (1)
  {
    int new_socket = accept(
        server->socket, 
        (struct sockaddr*)&server->address, 
        (socklen_t*)&address_length
    );

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