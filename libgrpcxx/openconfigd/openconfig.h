#ifndef __OPENCONFIG_H__
#define __OPENCONFIG_H__
#ifdef __cplusplus
extern "C" {
#endif

struct openconfigd_client;
typedef struct openconfigd_client openconfigd_client_t;

openconfigd_client_t* openconfigd_client_create (const char* remote);
void openconfigd_client_free (openconfigd_client_t* client);
void openconfigd_DoConfig (openconfigd_client_t* client);

void openconfigd_InstallCommand (
        openconfigd_client_t* client,
        const char* name,
        const char* module,
        const char* line,
        const char* helps,
        int32_t privilege);

struct openconfigd_server;
typedef struct openconfigd_server openconfigd_server_t;

openconfigd_server_t* openconfigd_server_create ();
void openconfigd_server_free (openconfigd_server_t* server);
void openconfigd_server_run (openconfigd_server_t* server, const char* local);

#ifdef __cplusplus
} /* extern C */
#endif
#endif /* __OPENCONFIG_H__ */
