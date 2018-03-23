#ifndef __GRPC_HELLOWORLD_API_H__
#define __GRPC_HELLOWORLD_API_H__
#ifdef __cplusplus
extern "C" {
#endif

struct helloworld_client;
typedef struct helloworld_client helloworld_client_t;

helloworld_client_t* helloworld_client_create(const char* remote);
void helloworld_client_free(helloworld_client_t* client);
void helloworld_say_hello(helloworld_client_t* client);

#ifdef __cplusplus
}; /* extern C */
#endif
#endif /* __GRPC_HELLOWORLD_API_H__ */
