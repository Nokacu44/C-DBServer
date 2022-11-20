#include "server.h"
#include <stdio.h>
#include <stdlib.h>

#define INT_SIZE sizeof(int) 

struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*launch)(struct Server* server))
{
  struct Server server;
  server.domain = domain;
  server.service = service;
  server.interface = interface;
  server.port = port;
  server.protocol = protocol;
  server.backlog = backlog;

  server.address.sin_family = domain;
  server.address.sin_port = htons(port);
  server.address.sin_addr.s_addr = htonl(interface);

  server.socket = socket(domain, service, protocol);

  int option = 1;
  setsockopt(server.socket, SOL_SOCKET, SO_REUSEADDR, &option, INT_SIZE);
  
  if (server.socket == 0) {
    perror("Failed to connect socekt...\n");
    exit(1);
  }

  if ((bind(server.socket, (struct sockaddr*)&server.address, sizeof(server.address))) < 0) {
    perror("Failed to bind socket...\n");
    exit(1);
  }

  if((listen(server.socket, server.backlog)) < 0) {
    perror("Failed to start listening...\n");
  }

  server.launch = launch;

  return server;
}
