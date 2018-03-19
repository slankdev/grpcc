
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <libgrpcxx.h>

void* server_launcher(void* param)
{
  openconfigd_server_run("0.0.0.0:9088");
  pthread_exit(NULL);
}

void* client_launcher(void* param)
{
  openconfigd_client_t* client = openconfigd_client_create("localhost:2650");
  openconfigd_DoRegisterModule(client);
  openconfigd_DoRegisterCommand(client);
  openconfigd_DoConfig(client);
  getchar();
  openconfigd_client_free(client);
  pthread_exit(NULL);
}

int main(int argc, char** argv)
{
  pthread_t server_thread;
  pthread_t client_thread;
  pthread_create(&server_thread, NULL, server_launcher, NULL);
  pthread_create(&client_thread, NULL, client_launcher, NULL);
  pthread_join(server_thread, NULL);
  pthread_join(client_thread, NULL);
}

