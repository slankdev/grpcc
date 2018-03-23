
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
#include "rfc5575bis.hh"

#include <slankdev/hexdump.h>

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

static std::string nlri_2str (const std::string& nlri)
{
  assert(nlri.size() > 1);
  printf("\n");
  slankdev::hexdump(stdout, nlri.data(), nlri.size());
  uint8_t prefix = nlri[2];
  uint32_t addr = 0;
  union {
    uint8_t u8[4];
    uint32_t u32;
  } U; U.u32 = 0;
  constexpr size_t inet_oct_max = 4;
  for (size_t i=0; i<inet_oct_max; i++) {
    U.u8[i] = nlri[i+3];
    if (i+3 >= nlri.size()) break;
  }
  return fmt::sprintf("%d.%d.%d.%d/%u",
      U.u8[0], U.u8[1], U.u8[2], U.u8[3], prefix);
}

enum ipv4flowspec_match_type
{
  DESTINATION      = 1,
  SOURCE           = 2,
  PROTOCOL         = 3,
  PORT             = 4,
  DESTINATION_PORT = 5,
  SOURCE_PORT      = 6,
  ICMP_TYPE        = 7,
  ICMP_CODE        = 8,
  TCP_FLAGS        = 9,
  PACKET_LENGTH	   = 10,
  DSCP             = 11,
  FRAGMENT         = 12,
  LABEL            = 13,
  ETHER_TYPE       = 14,
  SOURCE_MAC       = 15,
  DESTINATION_MAC  = 16,
  LLC_DSAP         = 17,
  LLC_SSAP         = 18,
  LLC_CONTROL	     = 19,
  SNAP             = 20,
  VID              = 21,
  COS              = 22,
  INNER_VID	       = 23,
  INNER_COS	       = 24,
}; /* enum ipv4flowspec_match_type */

static const char* ipv4flowspec_match_type2str (ipv4flowspec_match_type type)
{
  switch (type)
  {
    case DESTINATION      : return "destination     ";
    case SOURCE           : return "source          ";
    case PROTOCOL         : return "protocol        ";
    case PORT             : return "port            ";
    case DESTINATION_PORT : return "destination_port";
    case SOURCE_PORT      : return "source_port     ";
    case ICMP_TYPE        : return "icmp_type       ";
    case ICMP_CODE        : return "icmp_code       ";
    case TCP_FLAGS        : return "tcp_flags       ";
    case PACKET_LENGTH	  : return "packet_length	 ";
    case DSCP             : return "dscp            ";
    case FRAGMENT         : return "fragment        ";
    case LABEL            : return "label           ";
    case ETHER_TYPE       : return "ether_type      ";
    case SOURCE_MAC       : return "source_mac      ";
    case DESTINATION_MAC  : return "destination_mac ";
    case LLC_DSAP         : return "llc_dsap        ";
    case LLC_SSAP         : return "llc_ssap        ";
    case LLC_CONTROL	    : return "llc_control	   ";
    case SNAP             : return "snap            ";
    case VID              : return "vid             ";
    case COS              : return "cos             ";
    case INNER_VID	      : return "inner_vid	     ";
    case INNER_COS	      : return "inner_cos	     ";
    default: return "unkonwn";
  }
}

static inline uint32_t read_BE (const uint8_t* ptr, size_t byte_len)
{
  uint32_t retnum = 0;
  for (size_t i=0; i<byte_len; i++) {
    retnum = retnum << 8;
    retnum = retnum + *(ptr+i);
  }
  return retnum;
}

static void dump_nlri (FILE* fp, const std::string& nlri)
{
  const uint8_t* ptr = (const uint8_t*) nlri.data();
  ssize_t len = nlri.size();
  assert ((len - 1) == ptr[0]);
  len --;
  ptr ++;
  // printf ("==\n");
  slankdev::hexdump(stdout, nlri.data(), nlri.size());
  while (true) {
    if (len == 0) break;
    assert (len > 0);

    const ipv4flowspec_match_type type = (ipv4flowspec_match_type) *ptr;
    size_t seek_len = 0;
		printf("type: %s: ", ipv4flowspec_match_type2str (type));
    switch (type)
      {
        case DESTINATION:
          {
            uint8_t prefix = *(ptr+1);
            seek_len = prefix / 8 + 2;
            printf("X.X.X.X/%u", prefix);
            break;
          }
        case SOURCE:
          {
            uint8_t prefix = *(ptr+1);
            seek_len = prefix / 8 + 2;
            printf("X.X.X.X/%u", prefix);
            break;
          }
        case PROTOCOL:
          {
            uint8_t numop = *(ptr+1);
            seek_len = numop_len(numop) + 2;
            uint32_t id = read_BE(ptr+2, numop_len(numop));
            printf("%u", id);
            break;
          }
        case PORT:
          {
            uint8_t numop = *(ptr+1);
            seek_len = numop_len(numop) + 2;
            uint32_t id = read_BE(ptr+2, numop_len(numop));
            printf("%u", id);
            break;
          }
        case DESTINATION_PORT:
          {
            uint8_t numop = *(ptr+1);
            seek_len = numop_len(numop) + 2;
            uint32_t id = read_BE(ptr+2, numop_len(numop));
            printf("%u", id);
            break;
          }
        case SOURCE_PORT:
          {
            uint8_t numop = *(ptr+1);
            seek_len = numop_len(numop) + 2;
            uint32_t id = read_BE(ptr+2, numop_len(numop));
            printf("%u", id);
            break;
          }
        case ICMP_TYPE:
        case ICMP_CODE:
        case TCP_FLAGS:
        case PACKET_LENGTH:
        case DSCP:
        case FRAGMENT:
        case LABEL:
        case ETHER_TYPE:
        case SOURCE_MAC:
        case DESTINATION_MAC:
        case LLC_DSAP:
        case LLC_SSAP:
        case LLC_CONTROL:
        case SNAP:
        case VID:
        case COS:
        case INNER_VID:
        case INNER_COS:
        default:
          printf("unknown type(%u,0x%x)\n", type, type);
          assert (false);
          break;
      }

    printf ("\n");
    assert (seek_len != 0);
    // printf ("seek %zd bytes \n", seek_len);
    // printf ("current len=%zd\n", len);
    ptr += seek_len;
    len -= seek_len;
  }
  // printf ("==\n");
}

enum flowspec_action_type : uint16_t {
  RATE_LIMIT = 0x8006,
  ACTION     = 0x8007,
  REDIRECT   = 0x8008,
  MARK       = 0x8009,
};

static void
dump_attr (FILE* fp, const std::string& attr)
{
  const uint8_t* ptr = (const uint8_t*) attr.data();
  ssize_t len = attr.size();

  if (ptr[0] == 0xc0 &&
      ptr[1] == 0x10 &&
      ptr[2] == 0x08)
    {
      printf("flowspec action: ");
      ptr += 3;
      len -= 3;

      flowspec_action_type type = (flowspec_action_type) read_BE(ptr, 2);
      // printf("type=0x%04x ", type);
      ptr += 2;
      len -= 2;
      ptr += 2;
      len -= 2;
      switch (type)
        {
          case RATE_LIMIT:
            {
              uint32_t tmp = read_BE (ptr, 4);
              float f = 0;
              memcpy(&f, &tmp, 4);
              printf("rate-limit rate=%f", f);
              break;
            }
          case ACTION:
            {
              printf("action ");
              uint32_t id = read_BE (ptr, 4);
              if      (id == 1) printf("terminal");
              else if (id == 2) printf("sample");
              else if (id == 3) printf("sample-terminal");
              else assert(false);
              break;
            }
          case REDIRECT:
            {
              printf("redirect ");
              for (ssize_t i=0; i<len; i++)
                printf("%02x ", ptr[i]);
              break;
            }
          case MARK:
            {
              printf("mark ");
              uint32_t value = read_BE (ptr, 4);
              printf("value=%u\n", value);
              break;
            }
          default:
            for (size_t i=0; i<len; i++)
              printf("%02x ", ptr[i]);
        }

      printf("\n");
    }
  else
    {
      printf("unknown pattr\n");
      // slankdev::hexdump(stdout, attr.data(), attr.size());
      // printf("\n");
    }
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
    while (reader->Read(&dest))
      {
        printf("prefix: %s \n", dest.prefix().c_str());
        printf("paths.size: %d \n", dest.paths().size());
        for (size_t i=0, n=dest.paths().size(); i<n; i++)
          {
            auto& path = dest.paths()[i];
            printf("paths[%zd] \n", i );
            dump_nlri (stdout, path.nlri());

            printf("  pattrs.szie: %d\n", path.pattrs().size());
            for (size_t i=0; i<path.pattrs().size(); i++)
              {
                const std::string& attr = path.pattrs()[i];
                dump_attr (stdout, attr);
              }

#if 0
            /* not support yet */
            printf("  age: %ld\n", path.age());
            printf("  best: %s\n", path.best()?"true":"false");
            printf("  is_withdraw: %s\n", path.is_withdraw()?"true":"false");
            printf("  validation: %d\n", path.validation());
            auto& detail = path.validation_detail();
            printf("  validation_detail.state: \n");
            printf("  validation_detail.reason: \n");
            printf("  validation_detail.matched.size: %d\n", detail.matched().size());
            printf("  validation_detail.matched[0]: \n");
            printf("  validation_detail.unmatched_as.size: %d\n", detail.unmatched_as().size());
            printf("  validation_detail.unmatched_as[0]: \n");
            printf("  validation_detail.unmatched_length.size: %d\n", detail.unmatched_length().size());
            printf("  validation_detail.unmatched_length[0]: \n");
            printf("  no_implicit_withdraw: \n");
            printf("  family: \n");
            printf("  source_asn: \n");
            printf("  source_id: \n");
            printf("  filtered: \n");
            printf("  stale: \n");
            printf("  is_from_external: \n");
            printf("  neighbor_ip: \n");
            printf("  uuid: \n");
            printf("  is_nexthop_invalid: \n");
            printf("  identifer: \n");
            printf("  local_identifer: \n");
#endif
          }
        // printf("longer_prefixes: %s\n", dest.longer_prefixes()?"true":"false");
        // printf("shorter_prefixes: %s\n", dest.shorter_prefixes()?"true":"false");
        printf("\n");
      }
    Status status = reader->Finish();
    if (!status.ok()) {
      printf("Error \n");
      printf("- error code: %d \n", status.error_code());
      printf("- error msg : %s \n", status.error_message().c_str());
      exit(1);
    }
  }

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


#if 0
void gobgp_client::GetPath()
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

void gobgp_client::GetNeighbor()
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

void gobgp_client::GetServer()
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

