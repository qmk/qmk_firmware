#ifndef MY_SERIAL_H
#define MY_SERIAL_H

#include <stdbool.h>

// /////////////////////////////////////////////////////////////////
// Need Soft Serial defines in config.h
// /////////////////////////////////////////////////////////////////
// ex.
//  /* Configuration of lower interface with the lower layer(hardware) of serial.c */
//  #define SOFT_SERIAL_PIN ??   // ?? = D0,D1,D2,D3,E6
//
//  /* Configuration of upper interface with the upper layer of serial.c */
//  #define SERIAL_SLAVE_BUFFER_LENGTH MATRIX_ROWS/2
//  #define SERIAL_MASTER_BUFFER_LENGTH 1

// Buffers for master - slave communication
extern volatile uint8_t serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH];
extern volatile uint8_t serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH];

void serial_master_init(void);
void serial_slave_init(void);
int serial_update_buffers(void);
bool serial_slave_data_corrupt(void);

#endif
