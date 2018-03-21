
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <libgrpcxx.h>

void*
grpc_gobgp_manager (void* param)
{
  gobgp_client_t* client = gobgp_client_create ("localhost:50051");
  gobgp_client_MonitorRib (client);
  gobgp_client_free (client);
  pthread_exit (NULL);
}

void* grpc_manager ()
{
  pthread_t client_thread;
  pthread_create (&client_thread, NULL, grpc_gobgp_manager, NULL);
  pthread_join (client_thread, NULL);
}

int main(int argc, char** argv)
{
  pthread_t thread;
  pthread_create (&thread, NULL, grpc_manager, NULL);
  pthread_join (thread, NULL);
}

