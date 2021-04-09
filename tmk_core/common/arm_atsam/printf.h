#pragma once

#define CONSOLE_PRINTBUF_SIZE 512

void console_printf(char *fmt, ...);

#define __xprintf console_printf
