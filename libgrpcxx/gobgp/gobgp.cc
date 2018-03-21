
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <sstream>
#include <string>
#include <grpc++/grpc++.h>
#include "gobgp.pb.h"
#include "gobgp.grpc.pb.h"
#include "gobgp.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using gobgpapi::GobgpApi;

namespace fmt
{
  std::string sprintf(const char* fmt, ...)
  {
    char str[1000];
    va_list args;
    va_start(args, fmt);
    vsprintf(str, fmt, args);
    va_end(args);
    return str;
  }
} /* namespace fmt */

static std::string inet_nlri2str(const std::string& nlri)
{
  assert(nlri.size() > 1);
  uint8_t prefix = nlri[0];
  uint32_t addr = 0;
  union {
    uint8_t u8[4];
    uint32_t u32;
  } U; U.u32 = 0;
  constexpr size_t inet_oct_max = 4;
  for (size_t i=0; i<inet_oct_max; i++) {
    U.u8[i] = nlri[i+1];
    if (i+2 >= nlri.size()) break;
  }
  return fmt::sprintf("%d.%d.%d.%d/%u",
      U.u8[0], U.u8[1], U.u8[2], U.u8[3], prefix);
}

static std::string Path2str(const gobgpapi::Path& path)
{
  std::string nexthop = path.neighbor_ip();
  if (nexthop == "<nil>") nexthop = "0.0.0.0";
  std::string str = "";
  str += fmt::sprintf("[%s] ", path.is_withdraw()?"DELROUTE":"ROUTE");
  str += fmt::sprintf("%s via %s aspath [%u]",
      inet_nlri2str(path.nlri()).c_str(),
      nexthop.c_str(), path.source_asn());
  return str;
}

typedef struct gobgp_client {
 public:
  gobgp_client(std::shared_ptr<Channel> channel)
    : stub_(GobgpApi::NewStub(channel)) {}

  void MonitorRib()
  {
    gobgpapi::MonitorRibRequest req;
    gobgpapi::Table t;
    t.set_family((1<<16) | 1);
    t.set_family(gobgpapi::IPv4|gobgpapi::FLOW_SPEC_IPv4);
    req.set_allocated_table(&t);
    req.set_current(true);

    gobgpapi::Destination dest;
    ClientContext ctx;

    std::unique_ptr< ClientReader<gobgpapi::Destination> >
      reader(stub_->MonitorRib(&ctx, req));

    while (reader->Read(&dest)) {
      for (size_t i=0, n=dest.paths().size(); i<n; i++) {
        printf("%s \n", Path2str(dest.paths()[i]).c_str());
      }
    }
    Status status = reader->Finish();

    if (!status.ok()) {
      printf("Error \n");
      printf("- error code: %d \n", status.error_code());
      printf("- error msg : %s \n", status.error_message().c_str());
      exit(1);
    }
  }

#if 0
  void GetPath()
  {
    gobgpapi::GetPathRequest req;
    req.set_family((1<<16) | 1);

    gobgpapi::Path path;
    ClientContext ctx;

    std::unique_ptr< ClientReader<gobgpapi::Path> >
      reader(stub_->GetPath(&ctx, req));
    while (reader->Read(&path)) {
      printf("%s \n", Path2str(path).c_str());
    }
    Status status = reader->Finish();

    if (!status.ok()) {
      printf("Error \n");
      printf("- error code: %d \n", status.error_code());
      printf("- error msg : %s \n", status.error_message().c_str());
      exit(1);
    }
  }

  void GetNeighbor()
  {
    gobgpapi::GetNeighborRequest  req;
    gobgpapi::GetNeighborResponse res;
    ClientContext ctx;

    Status status = stub_->GetNeighbor(&ctx, req, &res);
    if (!status.ok()) {
      printf("Error \n");
      printf("- error code: %d \n", status.error_code());
      printf("- error msg : %s \n", status.error_message().c_str());
      exit(1);
    }

    std::stringstream buffer;
    for (int i=0; i < res.peers_size(); i++) {
      gobgpapi::PeerConf peer_conf  = res.peers(i).conf();
      gobgpapi::PeerState peer_info = res.peers(i).info();
      gobgpapi::Timers peer_timers  = res.peers(i).timers();

      buffer
        << "BGP neighbor is: " << peer_conf.neighbor_address()
        << ", remote AS: " << peer_conf.peer_as() << "\n"
        << "\tBGP version: 4, remote route ID " << peer_conf.id() << "\n"
        << "\tBGP state = " << peer_info.bgp_state()
        << ", up for " << peer_timers.state().uptime() << "\n"
        << "\tBGP OutQ = " << peer_info.out_q()
        << ", Flops = " << peer_info.flops() << "\n"
        << "\tHold time is " << peer_timers.state().hold_time()
        << ", keepalive interval is " << peer_timers.state().keepalive_interval()
        << "seconds\n"
        << "\tConfigured hold time is " << peer_timers.config().hold_time() << "\n";
    }
    printf("%s", buffer.str().c_str());
  }

  void GetServer()
  {
    gobgpapi::GetServerRequest  req;
    gobgpapi::GetServerResponse res;
    ClientContext ctx;

    Status status = stub_->GetServer(&ctx, req, &res);
    if (!status.ok()) {
      printf("Error \n");
      printf("- error code: %d \n", status.error_code());
      printf("- error msg : %s \n", status.error_message().c_str());
      exit(1);
    }
  }
#endif

 private:
  std::unique_ptr<GobgpApi::Stub> stub_;
} gobgp_client_t;

gobgp_client_t*
gobgp_client_create (const char* remote)
{
  auto channel = grpc::CreateChannel (remote,
      grpc::InsecureChannelCredentials ());
  auto* client =  new gobgp_client (channel);
  return client;
}

void
gobgp_client_free (gobgp_client_t* client)
{
  delete client;
}

void
gobgp_client_MonitorRib (gobgp_client_t* client)
{
  client->MonitorRib ();
}


