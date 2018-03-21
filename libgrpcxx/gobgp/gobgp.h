#ifndef __GOBGP_H__
#define __GOBGP_H__
#ifdef __cplusplus
extern "C" {
#endif

typedef struct gobgp_client gobgp_client_t;

gobgp_client_t* gobgp_client_create (const char* remote);
void gobgp_client_free (gobgp_client_t* client);
void gobgp_client_MonitorRib (gobgp_client_t* client);

#ifdef __cplusplus
} /* extern C */
#endif
#endif /* __GOBGP_H__ */
