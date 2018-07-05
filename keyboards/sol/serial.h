#ifndef MY_SERIAL_H
#define MY_SERIAL_H

#include "config.h"
#include <stdbool.h>

/* TODO:  some defines for interrupt setup */
#define SERIAL_PIN_DDR DDRD
#define SERIAL_PIN_PORT PORTD
#define SERIAL_PIN_INPUT PIND

#ifndef USE_SERIAL_PD3
#define SERIAL_PIN_MASK _BV(PD3)
#define SERIAL_PIN_INTERRUPT INT3_vect
#else
#define SERIAL_PIN_MASK _BV(PD3)
#define SERIAL_PIN_INTERRUPT INT3_vect
#endif

#define SERIAL_SLAVE_BUFFER_LENGTH MATRIX_ROWS/2
#ifdef KEYBOARD_helix_rev1
#define SERIAL_MASTER_BUFFER_LENGTH 1
#else
#define SERIAL_MASTER_BUFFER_LENGTH MATRIX_ROWS/2
#endif

// Buffers for master - slave communication
extern volatile uint8_t serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH];
extern volatile uint8_t serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH];

void serial_master_init(void);
void serial_slave_init(void);
int serial_update_buffers(void);
bool serial_slave_data_corrupt(void);

#endif
