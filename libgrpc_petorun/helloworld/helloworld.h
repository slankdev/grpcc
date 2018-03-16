#ifndef __GRPC_HELLOWORLD_API_H__
#define __GRPC_HELLOWORLD_API_H__

#ifdef __cplusplus
extern "C" {
#endif

int good_kamuee (void);
void get_version (char* buf, size_t size);
void grpc_log (const char* str);
const char* get_grpc_log ();

#ifdef __cplusplus
}; /* extern C */
#endif

#endif /* __GRPC_HELLOWORLD_API_H__ */
