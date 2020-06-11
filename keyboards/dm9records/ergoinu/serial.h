#pragma once

#include <stdbool.h>

// ////////////////////////////////////////////
// Need Soft Serial defines in serial_config.h
// ////////////////////////////////////////////
// ex.
//  #define SERIAL_PIN_DDR DDRD
//  #define SERIAL_PIN_PORT PORTD
//  #define SERIAL_PIN_INPUT PIND
//  #define SERIAL_PIN_MASK _BV(PD?)   ?=0,2
//  #define SERIAL_PIN_INTERRUPT INT?_vect  ?=0,2
//  #define SERIAL_follower_BUFFER_LENGTH MATRIX_ROWS/2
//  #define SERIAL_MASTER_BUFFER_LENGTH MATRIX_ROWS/2

// Buffers for master - follower communication
extern volatile uint8_t serial_follower_buffer[SERIAL_follower_BUFFER_LENGTH];
extern volatile uint8_t serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH];

void serial_master_init(void);
void serial_follower_init(void);
int serial_update_buffers(void);
bool serial_follower_data_corrupt(void);
