
#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "openconfig.grpc.pb.h"
#include "openconfig.h"
#define XELLICO_MODULE "xellicod"
#define XELLICO_PORT 9088

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using openconfig::Register;
using openconfig::RegisterRequest;
using openconfig::RegisterReply;
using openconfig::RegisterModuleRequest;
using openconfig::RegisterModuleReply;

using openconfig::Config;
using openconfig::ConfigRequest;
using openconfig::ConfigReply;


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
        return;
      }
      printf("ok callbackid=%u\n", rep.callbackid());
    }

    std::unique_ptr< grpc::ClientReaderWriter<ConfigRequest, ConfigReply> >
    DoConfig()
    {
      ClientContext ctx;
      std::unique_ptr< grpc::ClientReaderWriter<ConfigRequest, ConfigReply> > stream =
			config_stub_->DoConfig(&ctx);

      ConfigRequest req;
      req.set_type(openconfig::SUBSCRIBE_MULTI);
      req.set_module(XELLICO_MODULE);
      req.set_port(XELLICO_PORT);
      req.add_path("interfaces");
      req.add_path("protocols");
      req.add_path("policy");
      stream->Write(req);
      return stream;
    }

    void DoRegisterModule()
    {
      RegisterModuleRequest req;
      req.set_module("xellicod");
      req.set_port("9980");

      RegisterModuleReply rep;
      ClientContext ctx;

      Status status = stub_->DoRegisterModule(&ctx, req, &rep);
      if (!status.ok()){
        printf("noooo\n");
        return;
      }
      printf("ok result=%u\n", rep.result());
    }
  private:
    std::unique_ptr<Register::Stub> stub_;
    std::unique_ptr<Config::Stub> config_stub_;
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

void openconfigd_DoRegister(openconfigd_client_t* client)
{
  client->DoRegister();
}

void openconfigd_DoRegisterModule(openconfigd_client_t* client)
{
  client->DoRegisterModule();
}

void openconfigd_DoConfig(openconfigd_client_t* client)
{
	std::unique_ptr< grpc::ClientReaderWriter<ConfigRequest, ConfigReply> > stream;
	stream = client->DoConfig();
	// printf("slank %p\n", &ret);
}

