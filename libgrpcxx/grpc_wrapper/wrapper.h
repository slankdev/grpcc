#ifndef _GRPC_WRAPPER_
#define _GRPC_WRAPPER_
#ifdef __cplusplus
extern "C" {
#endif

struct grpcxx_chan;
typedef struct grpcxx_chan grpcxx_chan_t;

grpcxx_chan_t* grpcxx_chan_create(const char* remote);
void grpcxx_chan_free(grpcxx_chan_t* val);
void grpcxx_chan_dump(FILE* fp, grpcxx_chan_t* val);

#ifdef __cplusplus
} /* extern C */
#endif
#endif /* _GRPC_WRAPPER_ */
