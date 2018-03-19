
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgrpcxx.h>

int main(int argc, char** argv)
{
  openconfigd_client_t* client = openconfigd_client_create("localhost:2650");
  openconfigd_DoRegisterModule(client);
  openconfigd_DoRegister(client);
  openconfigd_DoConfig(client);
  getchar();
  openconfigd_client_free(client);
}

