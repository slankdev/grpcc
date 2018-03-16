
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"

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
          printf("err: code=%d, msg=%s\n",
              status.error_code (), status.error_message ().c_str ());
          return "Failed";
        }

      return rep.message ();
    }
  private:
    std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv)
{
  auto channel = grpc::CreateChannel ("localhost:9999",
      grpc::InsecureChannelCredentials ());
  GreeterClient greeter (channel);
  std::string user = "world";
  std::string rep  = greeter.SayHello(user);
  printf("recv: %s\n", rep.c_str());
}

