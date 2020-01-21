#ifndef _PRINTF_H_
#define _PRINTF_H_

#define CONSOLE_PRINTBUF_SIZE 512

void console_printf(char *fmt, ...);

#define __xprintf console_printf

#endif  //_PRINTF_H_
