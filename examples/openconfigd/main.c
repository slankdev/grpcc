
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <libgrpcc.h>
#define XELLICO_MODULE "xellicod"
#define XELLICO_PORT 9088
#define OPENCONFIGD_PORT 2650

void
callback (int argc, char** argv, openconfigd_vty_t* vty)
{
  openconfigd_printf (vty, "slankdev %s %d\n", "world", 1);
  for (size_t i=0; i<argc; i++)
      openconfigd_printf (vty, " argv[%zd]: %s\n", i, argv[i]);
}

void*
grpc_service_manager (void* param)
{
  openconfigd_show_service_t* show_service = openconfigd_show_service_create ();
  openconfigd_show_service_set_callback (show_service, callback);
  openconfigd_exec_service_t* exec_service = openconfigd_exec_service_create ();

  char str[256];
  snprintf (str, sizeof (str), "0.0.0.0:%d", XELLICO_PORT);
  grpcc_server_t* server = grpcc_server_create (str);
  grpcc_server_RegisterService (server, show_service);
  grpcc_server_RegisterService (server, exec_service);
  grpcc_server_BuildAndStart (server);
  grpcc_server_wait (server);

  grpcc_server_free (server);
  openconfigd_show_service_free (show_service);
  openconfigd_exec_service_free (exec_service);
  pthread_exit (NULL);
}

void*
openconfigd_client_manager (void* param)
{
  char str[256];
  snprintf (str, sizeof (str), "localhost:%d", OPENCONFIGD_PORT);
  openconfigd_client_t* client =
    openconfigd_client_create (str, XELLICO_MODULE, XELLICO_PORT);

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

  openconfigd_DoConfig (client, XELLICO_MODULE, XELLICO_PORT);
  openconfigd_client_free (client);
  pthread_exit (NULL);
}

void* grpc_manager ()
{
  pthread_t show_server_thread;
  pthread_t client_thread;
  pthread_create (&show_server_thread, NULL, grpc_service_manager, NULL);
  pthread_create (&client_thread, NULL, openconfigd_client_manager, NULL);
  pthread_join (show_server_thread, NULL);
  pthread_join (client_thread, NULL);
}

int main(int argc, char** argv)
{
  pthread_t thread;
  pthread_create (&thread, NULL, grpc_manager, NULL);
  pthread_join (thread, NULL);
}

