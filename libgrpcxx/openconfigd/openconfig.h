#ifndef __OPENCONFIG_H__
#define __OPENCONFIG_H__
#ifdef __cplusplus
extern "C" {
#endif

#define XELLICO_MODULE "xellicod"
#define XELLICO_PORT 9088

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

typedef struct openconfigd_vty openconfigd_vty_t;
typedef struct openconfigd_server openconfigd_server_t;
typedef void (*openconfigd_server_cbfunc_t)(int argc, char** argv, openconfigd_vty_t* vty);

void openconfigd_printf (openconfigd_vty_t* vty, const char* fmt_, ...);
openconfigd_server_t* openconfigd_server_create ();
void openconfigd_server_free (openconfigd_server_t* server);
void openconfigd_server_run (openconfigd_server_t* server, const char* local);

void openconfigd_server_set_callback (
        openconfigd_server_t* server,
        openconfigd_server_cbfunc_t fun);

#ifdef __cplusplus
} /* extern C */
#endif
#endif /* __OPENCONFIG_H__ */
