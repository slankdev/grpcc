
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "wrapper.h"


grpcxx_chan_t* grpcxx_chan_create(const char* remote)
{
  grpcxx_chan_t* ret = (grpcxx_chan_t*)malloc(sizeof(grpcxx_chan_t));
  ret->raw = grpc::CreateChannel (remote,
      grpc::InsecureChannelCredentials ());
  return ret;
}

void grpcxx_chan_free(grpcxx_chan_t* val)
{
  free(val);
}

static const char* GRPC_CHANNEL_2STR(grpc_connectivity_state e)
{
	switch (e) {
	case GRPC_CHANNEL_IDLE 	           : return "GRPC_CHANNEL_IDLE 	           ";
	case GRPC_CHANNEL_CONNECTING 	     : return "GRPC_CHANNEL_CONNECTING 	     ";
	case GRPC_CHANNEL_READY 	         : return "GRPC_CHANNEL_READY 	         ";
	case GRPC_CHANNEL_TRANSIENT_FAILURE: return "GRPC_CHANNEL_TRANSIENT_FAILURE";
	case GRPC_CHANNEL_SHUTDOWN 	       : return "GRPC_CHANNEL_SHUTDOWN 	       ";
	default: return "unknown";
	}
}

void grpcxx_chan_dump(FILE* fp, grpcxx_chan_t* val)
{
  fprintf(fp, "grpc::Channel@<%p> \r\n", val);
  fprintf(fp, "  state: %s \r\n", GRPC_CHANNEL_2STR(val->raw.get()->GetState(true)));
  fprintf(fp, "  service_config: %s \r\n", val->raw.get()->GetServiceConfigJSON().c_str());
}

