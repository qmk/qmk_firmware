#ifndef SPLIT_COMMON_MATRIX_H
#define SPLIT_COMMON_MATRIX_H

#include <common/matrix.h>

// Serial Master to Slave buffer Address location defines
#define SERIAL_BACKLIT_START   0x00

extern volatile uint8_t serial_master_buffer[];

void serial_master_init(void);
void serial_slave_init(void);

#endif
