#ifndef HEADER_OS_PORT_H
#define HEADER_OS_PORT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

//#include <Thread.h>
#define SSL_CTX_MUTEX_TYPE          //Mutex
#define SSL_CTX_MUTEX_INIT(A)       //pthread_mutex_init(&A, NULL)
#define SSL_CTX_MUTEX_DESTROY(A)    //pthread_mutex_destroy(&A)
#define SSL_CTX_LOCK(A)             //pthread_mutex_lock(&A)
#define SSL_CTX_UNLOCK(A)           //pthread_mutex_unlock(&A)

#define malloc(A)       ax_malloc(A, __FILE__, __LINE__)
#ifndef realloc
#define realloc(A,B)    ax_realloc(A,B, __FILE__, __LINE__)
#endif
#define calloc(A,B)     ax_calloc(A,B, __FILE__, __LINE__)
#define free(A)         ax_free(A, __FILE__, __LINE__)

#define STDCALL
#define EXP_FUNC
void init_memory_buf(void);
void disable_memory_buf(void);
void enable_memory_buf(void);
void print_buf_stats(void);
void print_all_buf_stats(void);

EXP_FUNC void * STDCALL ax_malloc(size_t s, const char* f, const int l);
EXP_FUNC void * STDCALL ax_realloc(void *y, size_t s, const char* f, const int l);
EXP_FUNC void * STDCALL ax_calloc(size_t n, size_t s, const char* f, const int l);
EXP_FUNC void   STDCALL ax_free(void *y, const char* f, const int l);

//EXP_FUNC int STDCALL ax_open(const char *pathname, int flags); 

#define SOCKET_READ(A,B,C)      lwip_read(A,B,C)
#define SOCKET_WRITE(A,B,C)     lwip_write(A,B,C)
#define SOCKET_CLOSE(A)         closesocket(A)
#define TTY_FLUSH()
#ifdef __cplusplus
}
#endif
#endif 
