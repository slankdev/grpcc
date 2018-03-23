#ifndef __GRPCC_H__
#define __GRPCC_H__
#ifdef __cplusplus
extern "C" {
#endif

/*
 * gRPC server
 */
typedef struct grpcc_server grpcc_server_t;
grpcc_server_t* grpcc_server_create (const char* local);
void grpcc_server_free (grpcc_server_t* server);
void grpcc_server_RegisterService (grpcc_server_t* server, void* service);
void grpcc_server_BuildAndStart (grpcc_server_t* server);
void grpcc_server_wait (grpcc_server_t* server);

#ifdef __cplusplus
} /* extern C */
#endif
#endif /* __GRPCC_H__ */
