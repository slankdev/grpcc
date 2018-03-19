
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgrpcxx.h>

int main(int argc, char** argv)
{
  /* grpcxx_chan_t* chan = grpcxx_chan_create("localhost:9999"); */
  /* for (size_t i=0; i<4; i++) { */
  /*   grpcxx_chan_dump(stdout, chan); */
  /*   sleep(1); */
  /* } */
  /* grpcxx_chan_free(chan); */

  /* // TODO Next */
  /* helloworld_client_t* client = helloworld_client_create("localhost:9999"); */
  /* helloworld_say_hello(client); */
  /* helloworld_client_free(client); */

  // TODO Next
  openconfigd_client_t* client = openconfigd_client_create("localhost:2650");
  openconfigd_DoRegisterModule(client);
  openconfigd_DoRegister(client);
  getchar();
  /* openconfigd_DoConfig(client); */
  openconfigd_client_free(client);
}

