
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterServiceImpl final : public Greeter::Service {
  Status SayHello(ServerContext* ctx, const HelloRequest* req, HelloReply* rep) override {
    std::string prefix = "Hello ";
    rep->set_message(prefix + req->name());
    return Status::OK;
  }
};

void RunServer()
{
  std::string server_addr = "0.0.0.0:9999";
  GreeterServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  printf("server listening on %s\n", server_addr.c_str());
  server->Wait();
}

int main(int argc, char** argv)
{
  RunServer();
}

