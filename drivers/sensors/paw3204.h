#pragma once

#include <stdint.h>

#ifndef PAW3204_SCLK
#    error "No clock pin defined -- missing PAW3204_SCLK"
#endif

#ifndef PAW3204_DATA
#    error "No data pin defined -- missing PAW3204_DATA"
#endif

typedef struct {
    int8_t x;
    int8_t y;
} report_paw3204_t;

// A bunch of functions to implement the ADNS5050-specific serial protocol.
// Note that the "serial.h" driver is insufficient, because it does not
// manually manipulate a serial clock signal.

void PAW3204_init(void);
// void              adns5050_sync(void);
report_paw3204_t PAW3204_read(void);
uint8_t          PAW3204_serial_read(void);
void             PAW3204_serial_write(uint8_t reg_addr);
uint8_t          PAW3204_read_reg(uint8_t reg_addr);
void             PAW3204_write_reg(uint8_t reg_addr, uint8_t data);
// void              PAW3204_set_cpi(uint16_t cpi);
// uint16_t          PAW3204_get_cpi(void);
int8_t  convert_twoscomp(uint8_t data);
uint8_t read_pid_paw3204(void);
