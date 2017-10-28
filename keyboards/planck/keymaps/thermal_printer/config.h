#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#      define SERIAL_UART_BAUD 19200
#      define SERIAL_UART_DATA UDR1
#      define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#      define SERIAL_UART_RXD_VECT USART1_RX_vect
#      define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#      define SERIAL_UART_INIT() do { \
            /* baud rate */ \
            UBRR1L = SERIAL_UART_UBRR; \
            /* baud rate */ \
            UBRR1H = SERIAL_UART_UBRR >> 8; \
            /* enable TX */ \
            UCSR1B = _BV(TXEN1); \
            /* 8-bit data */ \
            UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
            sei(); \
        } while(0)

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

 #endif