
#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"
#include "helloworld.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterClient
{
  public:
    GreeterClient(std::shared_ptr<Channel> channel)
      : stub_ (Greeter::NewStub (channel)) {}

    std::string SayHello (const std::string& user)
    {
      HelloRequest req;
      req.set_name (user);

      HelloReply rep;
      ClientContext ctx;

      Status status = stub_->SayHello (&ctx, req, &rep);
      if (!status.ok ())
        {
          char str[100];
          snprintf(str, sizeof (str), "Failed(err: code=%d, msg=%s)",
              status.error_code (), status.error_message ().c_str ());
          return str;
        }

      return rep.message ();
    }
  private:
    std::unique_ptr<Greeter::Stub> stub_;
};

int
good_kamuee (void)
{
  auto channel = grpc::CreateChannel ("localhost:9999",
      grpc::InsecureChannelCredentials ());
  GreeterClient greeter (channel);
  std::string user = "world";
  std::string rep  = greeter.SayHello(user);
  printf("good_kamuee recv: %s\n", rep.c_str());
}

void
get_version (char* buf, size_t size)
{
  auto channel = grpc::CreateChannel ("localhost:9999",
      grpc::InsecureChannelCredentials ());
  GreeterClient greeter (channel);
  std::string user = "version";
  std::string rep  = greeter.SayHello(user);
  snprintf(buf, size, "%s", rep.c_str());
}


std::string buffer = "";

void
grpc_log (const char* str)
{
  buffer += str;
  buffer += "\r\n";
}

const char*
get_grpc_log ()
{
  return buffer.c_str();
}

