#ifndef _PRINTF_H_
#define _PRINTF_H_

int dpf(const char *_Format, ...);
#define __xprintf(fmt, ...) dpf(fmt, ##__VA_ARGS__)

#endif //_PRINTF_H_

