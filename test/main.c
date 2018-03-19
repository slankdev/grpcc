
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <libgrpcxx.h>

void* server(void* param)
{
  printf("openconfigd server run\n");
  openconfigd_server_run();
  printf("openconfigd server fin\n");
  return NULL;
}

int main(int argc, char** argv)
{
  pthread_t thread;
  pthread_create(&thread, NULL, server, NULL);

  openconfigd_client_t* client = openconfigd_client_create("localhost:2650");
  openconfigd_DoRegisterModule(client);
  openconfigd_DoRegister(client);
  openconfigd_DoConfig(client);
  getchar();
  openconfigd_client_free(client);

  pthread_join(thread, NULL);
}

