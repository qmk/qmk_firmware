#ifndef XPRINTF_H
#define XPRINTF_H

//#define xprintf(format, ...)            __xprintf(format, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

int xprintf(const char *format, ...);

#ifdef __cplusplus
}
#endif


#endif
