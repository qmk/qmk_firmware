/**
 * @file tca6424.h
 */

#pragma once

#include <stdint.h>

#ifndef TCA6424_ADDR
    #define TCA6424_ADDR 0x44
#endif

typedef enum {
    TCA6424_PORT0 = 0,
    TCA6424_PORT1,
    TCA6424_PORT2,
} TCA6424_PORT;

void tca6424_init(void);

void    tca6424_write_config(TCA6424_PORT port, uint8_t data);
void    tca6424_write_polarity(TCA6424_PORT port, uint8_t data);

void    tca6424_write_port(TCA6424_PORT port, uint8_t data);
uint8_t tca6424_read_port(TCA6424_PORT port);
