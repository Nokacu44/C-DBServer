#ifndef HTTPRequest_h
#define HTTPRequest_h

enum HTTPMethods
{
  GET,
  POST,
  PUT,
  DELETE,
};


struct HTTPRequest
{
  int method;
  char* uri;
  float version;
};

struct HTTPRequest HTTPRequest_constructor(char* request_string);

#endif