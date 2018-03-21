
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <libgrpcxx.h>
#define OPENCONFIGD_PORT 2650

void
callback (int argc, char** argv, openconfigd_vty_t* vty)
{
  openconfigd_printf (vty, "slankdev %s \n", "world");
  for (size_t i=0; i<argc; i++)
    {
      openconfigd_printf (vty, " argv[%zd]: %s\n", i, argv[i]);
    }
}

void*
grpc_server_manager (void* param)
{
  openconfigd_server_t* server = openconfigd_server_create ();
  openconfigd_server_set_callback (server, callback);

  char str[256];
  snprintf (str, sizeof (str), "0.0.0.0:%d", XELLICO_PORT);
  openconfigd_server_run (server, "0.0.0.0:9088");
  openconfigd_server_free (server);
  pthread_exit (NULL);
}

void*
grpc_client_manager (void* param)
{
  char str[256];
  snprintf (str, sizeof (str), "localhost:%d", OPENCONFIGD_PORT);
  openconfigd_client_t* client =
    openconfigd_client_create (str);

  openconfigd_InstallCommand (client,
      "xellico_show_version",
      XELLICO_MODULE,
      "show xellico version",
      "Show running system info\n"
      "Show xellico info\n"
      "Show xellico version\n", 1);

  openconfigd_InstallCommand (client,
      "xellico_show",
      XELLICO_MODULE,
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

