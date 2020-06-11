#ifndef SPLIT_COMM_H
#define SPLIT_COMM_H

#ifndef SERIAL_USE_MULTI_TRANSACTION
/* --- USE Simple API (OLD API, compatible with let's split serial.c) --- */
#include "serial.h"

#else
/* --- USE flexible API (using multi-type transaction function) --- */
// Buffers for master - follower communication
#define SERIAL_follower_BUFFER_LENGTH MATRIX_ROWS/2
#define SERIAL_MASTER_BUFFER_LENGTH MATRIX_ROWS/2

extern volatile uint8_t serial_follower_buffer[SERIAL_follower_BUFFER_LENGTH];
extern volatile uint8_t serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH];
extern uint8_t follower_buffer_change_count;

void serial_master_init(void);
void serial_follower_init(void);
int serial_update_buffers(int master_changed);

#endif

#endif /* SPLIT_COMM_H */
