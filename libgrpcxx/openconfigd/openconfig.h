#ifndef __OPENCONFIG_H__
#define __OPENCONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

struct openconfigd_client;
typedef struct openconfigd_client openconfigd_client_t;

openconfigd_client_t* openconfigd_client_create(const char* remote);
void openconfigd_client_free(openconfigd_client_t* client);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* __OPENCONFIG_H__ */
