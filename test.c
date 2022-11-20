#include "lib/server.h"
#include "lib/HTTPRequest.h"
#include <stdio.h>
#include <string.h>

#include "lib/externals/cJSON.h"

#include <fcntl.h> // for open
#include <unistd.h> // for close


char* jsonTest()
{
    const unsigned int resolution_numbers[3][2] = {
        {1280, 720},
        {1920, 1080},
        {3840, 2160}
    };
    char *string = NULL;
    cJSON *resolutions = NULL;
    size_t index = 0;

    cJSON *monitor = cJSON_CreateObject();

    if (cJSON_AddStringToObject(monitor, "name", "Awesome 4K") == NULL)
    {
        goto end;
    }

    resolutions = cJSON_AddArrayToObject(monitor, "resolutions");
    if (resolutions == NULL)
    {
        goto end;
    }

    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
    {
        cJSON *resolution = cJSON_CreateObject();

        if (cJSON_AddNumberToObject(resolution, "width", resolution_numbers[index][0]) == NULL)
        {
            goto end;
        }

        if (cJSON_AddNumberToObject(resolution, "height", resolution_numbers[index][1]) == NULL)
        {
            goto end;
        }

        cJSON_AddItemToArray(resolutions, resolution);
    }

    string = cJSON_Print(monitor);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

end:
    cJSON_Delete(monitor);
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