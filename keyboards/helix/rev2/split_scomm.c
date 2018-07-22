#ifdef USE_SERIAL
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <split_scomm.h>
#include "serial.h"

uint8_t volatile serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH] = {0};
uint8_t volatile serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH] = {0};
uint8_t volatile status0 = 0;

#ifdef SERIAL_USE_SIMPLE_TRANSACTION
SSTD_t transactions[] = {
    { (uint8_t *)&status0,
      sizeof(serial_master_buffer), (uint8_t *)serial_master_buffer,
      sizeof(serial_slave_buffer), (uint8_t *)serial_slave_buffer
    }
};
#else
SSTD_t transactions[] = {
#define WHOLE_MATRIX_EXCHANGE 0
    { (uint8_t *)&status0,
      sizeof(serial_master_buffer), (uint8_t *)serial_master_buffer,
      sizeof(serial_slave_buffer), (uint8_t *)serial_slave_buffer
    }
};
#endif

void serial_master_init(void)
{
    soft_serial_initiator_init(transactions);
}

void serial_slave_init(void)
{
    soft_serial_target_init(transactions);
}

// 0 => no error
// 1 => slave did not respond
// 2 => checksum error
int serial_update_buffers(int master_update)
{
#ifdef SERIAL_USE_SIMPLE_TRANSACTION
    return soft_serial_transaction();
#else
    return soft_serial_transaction(WHOLE_MATRIX_EXCHANGE);
#endif
}
#endif /* USE_SERIAL */
