#pragma once

#include <stdint.h>

void uart_init(uint32_t baud);

void uart_putchar(uint8_t c);

uint8_t uart_getchar(void);

bool uart_available(void);
