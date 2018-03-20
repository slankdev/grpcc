
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <libgrpcxx.h>

void*
grpc_server_manager (void* param)
{
  openconfigd_server_run ("0.0.0.0:9088");
  pthread_exit (NULL);
}

void*
grpc_client_manager (void* param)
{
  openconfigd_client_t* client =
    openconfigd_client_create ("localhost:2650");

  openconfigd_InstallCommand (client,
      "xellico_show_version",
      "xellico",
      "show xellico version",
      "Show running system info\n"
      "Show xellico info\n"
      "Show xellico version\n", 1);

  openconfigd_InstallCommand (client,
      "xellico_show",
      "xellico",
      "show xellico",
      "Show running system info\n"
      "Show xellico info\n", 1);

  openconfigd_DoConfig (client);
  getchar ();
  openconfigd_client_free (client);
  pthread_exit (NULL);
}

void* grpc_manager ()
{
  pthread_t server_thread;
  pthread_t client_thread;
  pthread_create (&server_thread, NULL, grpc_server_manager, NULL);
  pthread_create (&client_thread, NULL, grpc_client_manager, NULL);
  pthread_join (server_thread, NULL);
  pthread_join (client_thread, NULL);
}

int main(int argc, char** argv)
{
  pthread_t thread;
  pthread_create (&thread, NULL, grpc_manager, NULL);
  pthread_join (thread, NULL);
}

