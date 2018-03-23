
#include <iostream>
#include <vector>
#include <string>
#include <stdarg.h>
#include <unistd.h>
#include <grpcpp/grpcpp.h>
#include "grpcc.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReaderWriter;
using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;


typedef struct grpcc_server {
  ServerBuilder builder;
  std::unique_ptr <Server> server_ptr;
} grpcc_server_t;

static void grpcc_server_AddListeningPort (grpcc_server_t* server, const char* local)
{
  std::string server_addr = local;
  server->builder.AddListeningPort (server_addr, grpc::InsecureServerCredentials ());
}

grpcc_server_t* grpcc_server_create (const char* local)
{
  auto* server = new grpcc_server;
  grpcc_server_AddListeningPort (server, local);
  return server;
}

void grpcc_server_free (grpcc_server_t* server)
{
  delete server;
}

void
grpcc_server_RegisterService (grpcc_server_t* server, void* service)
{
  server->builder.RegisterService ((grpc::Service*) service);
}

void
grpcc_server_BuildAndStart (grpcc_server_t* server)
{
  server->server_ptr = server->builder.BuildAndStart ();
}

void
grpcc_server_wait (grpcc_server_t* server)
{
  server->server_ptr->Wait ();
}

