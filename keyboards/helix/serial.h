#ifndef MY_SERIAL_H
#define MY_SERIAL_H

#include "config.h"
#include <stdbool.h>

/* TODO:  some defines for interrupt setup */
#define SERIAL_PIN_DDR DDRD
#define SERIAL_PIN_PORT PORTD
#define SERIAL_PIN_INPUT PIND

#ifndef USE_SERIAL_PD2
#define SERIAL_PIN_MASK _BV(PD0)
#define SERIAL_PIN_INTERRUPT INT0_vect
#else
#define SERIAL_PIN_MASK _BV(PD2)
#define SERIAL_PIN_INTERRUPT INT2_vect
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

// debug flags
#define SERIAL_DEBUG_MODE_WATCH_OUTMODE 0x1
#define SERIAL_DEBUG_MODE_WATCH_RCVSAMPLE 0x2
#define SERIAL_DEBUG_MODE_WATCH_BYTEWIDTH 0x4
#define SERIAL_DEBUG_MODE_WATCH_SYNC 0x8
#define SERIAL_DEBUG_MODE_WATCH_IOCHG 0x10

//#define SERIAL_DEBUG_MODE SERIAL_DEBUG_MODE_WATCH_OUTMODE
//#define SERIAL_DEBUG_MODE SERIAL_DEBUG_MODE_WATCH_RCVSAMPLE
//#define SERIAL_DEBUG_MODE SERIAL_DEBUG_MODE_WATCH_BYTEWIDTH
//#define SERIAL_DEBUG_MODE (SERIAL_DEBUG_MODE_WATCH_RCVSAMPLE|SERIAL_DEBUG_MODE_WATCH_BYTEWIDTH)
//#define SERIAL_DEBUG_MODE SERIAL_DEBUG_MODE_WATCH_SYNC
//#define SERIAL_DEBUG_MODE (SERIAL_DEBUG_MODE_WATCH_RCVSAMPLE|SERIAL_DEBUG_MODE_WATCH_SYNC)
//#define SERIAL_DEBUG_MODE SERIAL_DEBUG_MODE_WATCH_IOCHG
#define SERIAL_DEBUG_MODE (SERIAL_DEBUG_MODE_WATCH_IOCHG|SERIAL_DEBUG_MODE_WATCH_SYNC)

// Helix keyboard unused port (for Logic analyzer or oscilloscope)
#ifdef SERIAL_DEBUG_MODE
#define SERIAL_DBGPIN_DDR DDRB
#define SERIAL_DBGPIN_PORT PORTB
#define SERIAL_DBGPIN_MASK _BV(PB5)
#endif

#endif
