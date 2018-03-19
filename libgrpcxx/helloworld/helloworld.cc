
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

typedef struct helloworld_client
{
  public:
    helloworld_client(std::shared_ptr<Channel> channel)
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
} helloworld_client_t;

helloworld_client_t*
helloworld_client_create(const char* remote)
{
  auto channel = grpc::CreateChannel (remote,
      grpc::InsecureChannelCredentials ());
  helloworld_client_t* ret = new helloworld_client (channel);
  return ret;
}

void helloworld_client_free(helloworld_client_t* client)
{
  delete client;
}

void helloworld_say_hello(helloworld_client_t* client)
{
  std::string user = "world";
  std::string rep  = client->SayHello(user);
  printf("good_kamuee recv: %s\n", rep.c_str());
}

