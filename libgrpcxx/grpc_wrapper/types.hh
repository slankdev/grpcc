#ifndef _GRPC_TYPES_
#define _GRPC_TYPES_

#include <grpcpp/grpcpp.h>

typedef struct grpcxx_chan {
  std::shared_ptr<grpc::Channel> raw;
} grpcxx_chan_t;

#endif /* _GRPC_TYPES_ */
