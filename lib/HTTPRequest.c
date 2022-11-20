#include "HTTPRequest.h"

#include <string.h>
#include <stdlib.h>


int find_method(char* str_method)
{
  if (strcmp(str_method, "GET") == 0)
  {
    return GET;
  }
  else if (strcmp(str_method, "POST") == 0)
  {
    return POST;
  }
  else if (strcmp(str_method, "PUT") == 0)
  {
    return PUT;
  }
  else if (strcmp(str_method, "DELETE") == 0)
  {
    return DELETE;
  }
}

struct HTTPRequest HTTPRequest_constructor(char* request_string)
{
  struct HTTPRequest request;

  char requested[strlen(request_string)];
  strcpy(requested, request_string);

  for (size_t i = 0; i < strlen(requested) - 2; i++)
  {
    if (requested[i] == '\n' && requested[i+1] == '\n')
    {
      requested[i+1] = '|';
    }
  }

  char* request_lines = strtok(requested, "\n");
  char* header_fields = strtok(NULL, "|");
  char* body = strtok(NULL, "|");


  char* str_method = strtok(request_lines, " ");
  request.method = find_method(str_method);

  char* uri = strtok(NULL, " ");
  request.uri = uri;

  char* version = strtok(NULL, " ");// whole POST/Version
  version = strtok(version, "/"); // Only /Version
  version = strtok(NULL, "/"); // Version

  request.version = (float) atof(version);


  return request;
  
}