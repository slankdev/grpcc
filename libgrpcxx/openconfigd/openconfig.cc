
#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "openconfig.grpc.pb.h"
#include "openconfig.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using openconfig::Register;
using openconfig::RegisterRequest;
using openconfig::RegisterReply;
using openconfig::RegisterModuleRequest;
using openconfig::RegisterModuleReply;

typedef struct openconfigd_client {
  public:
    openconfigd_client(std::shared_ptr<Channel> channel)
      : stub_ (Register::NewStub (channel)) {}

    void DoRegister()
    {
      RegisterRequest req;
      req.set_name("df");
      req.set_module("dfd");
      req.set_mode("adfa");
      req.set_line("df");
      // req.set_privilege();

      RegisterReply rep;
      ClientContext ctx;

      Status status = stub_->DoRegister(&ctx, req, &rep);
      if (!status.ok()){
        printf("noooo\n");
      }
      printf("ok callbackid=%u\n", rep.callbackid());
    }

    void DoRegisterModule()
    {
      RegisterModuleRequest req;
      req.set_module("xellico");
      req.set_port("9980");

      RegisterModuleReply rep;
      ClientContext ctx;

      Status status = stub_->DoRegisterModule(&ctx, req, &rep);
      if (!status.ok()){
        printf("noooo\n");
      }
      printf("ok result=%u\n", rep.result());
    }
  private:
    std::unique_ptr<Register::Stub> stub_;
} openconfigd_client_t;

openconfigd_client_t*
openconfigd_client_create(const char* remote)
{
  auto channel = grpc::CreateChannel (remote,
      grpc::InsecureChannelCredentials ());
  openconfigd_client_t* ret = new openconfigd_client (channel);
  return ret;
}

void openconfigd_client_free(openconfigd_client_t* client)
{
  delete client;
}

