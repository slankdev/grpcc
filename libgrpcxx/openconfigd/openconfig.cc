
#include <iostream>
#include <string>
#include <unistd.h>
#include <grpcpp/grpcpp.h>
#include "openconfig.grpc.pb.h"
#include "openconfig.h"
#define XELLICO_MODULE "xellicod"
#define XELLICO_PORT 9088

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;

using openconfig::Register;
using openconfig::RegisterRequest;
using openconfig::RegisterReply;
using openconfig::RegisterModuleRequest;
using openconfig::RegisterModuleReply;
using openconfig::Config;
using openconfig::ConfigRequest;
using openconfig::ConfigReply;
using openconfig::Show;
using openconfig::ShowRequest;
using openconfig::ShowReply;

#include <stdarg.h>
namespace fmt {

inline std::string sprintf(const char* fmt_, ...)
{
  char str[1000];
  va_list args;
  va_start(args, fmt_);
  vsprintf(str, fmt_, args);
  va_end(args);
  return str;
}

} /* namespace fmt */

typedef struct openconfigd_client {
  public:
    std::unique_ptr< grpc::ClientReaderWriter<ConfigRequest, ConfigReply> > config_stream;

    openconfigd_client(std::shared_ptr<Channel> channel)
      : stub_ (Register::NewStub (channel))
      , config_stub_ (Config::NewStub (channel))
    { puts("construct"); }
    ~openconfigd_client() { puts("destruct"); }

    void DoRegister()
    {
      /*
       * "name": "quagga_show",
       * "line": "show running-config",
       * "mode": "exec",
       * "helps": [
       *     "Show running system information",
       *     "running configuration"
       * ]
       */
      RegisterRequest req;
      req.set_name("xellico_show");
      req.set_module(XELLICO_MODULE);
      req.set_line("show xellico");
      req.set_mode("exec");
      req.add_helps("Show running system information");
      req.add_helps("Show xellico information");
      req.set_privilege(1);
      req.set_code(openconfig::REDIRECT_SHOW);

      RegisterReply rep;
      ClientContext ctx;
      Status status = stub_->DoRegister(&ctx, req, &rep);
      if (!status.ok()){
        printf("noooo\n");
        return;
      }
      printf("command install callbackid=%u\n", rep.callbackid());
    }

    void DoConfig()
    {
      ClientContext ctx;
      this->config_stream = config_stub_->DoConfig(&ctx);

      ConfigRequest req;
      req.set_type(openconfig::SUBSCRIBE_MULTI);
      req.set_module(XELLICO_MODULE);
      req.set_port(XELLICO_PORT);
      req.add_path("interfaces");
      req.add_path("protocols");
      req.add_path("policy");
      bool b = config_stream->Write(req);
      if (!b) exit(-1);

      printf("wainting\n");
      while (1) {
        printf(".");
        sleep(1);
      }

      b = config_stream->WritesDone();
      if (!b) exit(-1);
    }

    void DoRegisterModule()
    {
      RegisterModuleRequest req;
      req.set_module(XELLICO_MODULE);
      req.set_port(fmt::sprintf("%d", XELLICO_PORT));

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
  client->DoConfig();
}

typedef struct openconfigd_server final : public Show::Service {
  Status Show(ServerContext* ctx, const ShowRequest* req,
      ServerWriter<ShowReply>* writer) override
  {
    printf("calling %s() from RPC\n", __func__);
    ShowReply rep;
    rep.set_str("xellico is dummy name, My name is slankdev.");
    writer->Write(rep);
    return Status::OK;
  }

} openconfigd_server_t;

void openconfigd_server_run()
{
  std::string server_addr = "0.0.0.0:9088";
  openconfigd_server_t service;

  ServerBuilder builder;
  builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  printf("server listening on %s\n", server_addr.c_str());
  server->Wait();
}

#if 0
openconfigd_server_t*
openconfigd_server_create(const char* local)
{
}

void openconfigd_server_free(openconfigd_server_t* client)
{
}
#endif

