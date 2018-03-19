
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "wrapper.h"


grpcxx_chan_t* grpcxx_chan_create(const char* remote)
{
  grpcxx_chan_t* ret = (grpcxx_chan_t*)malloc(sizeof(grpcxx_chan_t));
  ret->raw = grpc::CreateChannel (remote,
      grpc::InsecureChannelCredentials ());
}

void grpcxx_chan_free(grpcxx_chan_t* val)
{
  free(val);
}

void grpcxx_chan_dump(FILE* fp, grpcxx_chan_t* val)
{
  printf("slankdev %p\n", val);
}

