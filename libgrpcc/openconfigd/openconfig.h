#ifndef __OPENCONFIG_H__
#define __OPENCONFIG_H__
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Config Client
 */
struct openconfigd_client;
typedef struct openconfigd_client openconfigd_client_t;
openconfigd_client_t* openconfigd_client_create (const char* remote, const char* modname, int modport);
void openconfigd_client_free (openconfigd_client_t* client);
void openconfigd_DoConfig (openconfigd_client_t* client, const char* modname, int modport);
void openconfigd_InstallCommand (
        openconfigd_client_t* client,
        const char* name,
        const char* module,
        const char* line,
        const char* helps,
        int32_t privilege);

/*
 * Show Service
 */
typedef struct openconfigd_vty openconfigd_vty_t;
typedef struct openconfigd_show_service openconfigd_show_service_t;
openconfigd_show_service_t* openconfigd_show_service_create (void);
void openconfigd_show_service_free (openconfigd_show_service_t* service);

typedef void (*openconfigd_show_service_cbfunc_t)(int argc, char** argv, openconfigd_vty_t* vty);
void openconfigd_printf (openconfigd_vty_t* vty, const char* fmt_, ...);
void openconfigd_show_service_set_callback (
        openconfigd_show_service_t* service,
        openconfigd_show_service_cbfunc_t fun);

/*
 * Exec Service
 */
typedef struct openconfigd_exec_service openconfigd_exec_service_t;
openconfigd_exec_service_t* openconfigd_exec_service_create (void);
void openconfigd_exec_service_free (openconfigd_exec_service_t* service);


#ifdef __cplusplus
} /* extern C */
#endif
#endif /* __OPENCONFIG_H__ */
