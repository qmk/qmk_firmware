#ifndef _uart_included_h_
#define _uart_included_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void    uart_init(uint32_t baud);
void    uart_putchar(uint8_t c);
void    uart_flush(void);
uint8_t uart_peek(void);
uint8_t uart_getchar(void);
uint8_t uart_available(void);

#ifdef __cplusplus
}
#endif

#endif
