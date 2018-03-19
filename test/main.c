
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgrpcxx.h>

int main(int argc, char** argv)
{
  grpcxx_chan_t* chan = grpcxx_chan_create("localhost:9999");
  /* if (grpcxx_chan_is) */

  for (size_t i=0; i<5; i++) {
    grpcxx_chan_dump(stdout, chan);
    sleep(1);
  }

  grpcxx_chan_free(chan);
}

