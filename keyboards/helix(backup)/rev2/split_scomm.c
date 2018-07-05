#ifdef USE_SERIAL
#ifdef SERIAL_USE_MULTI_TRANSACTION
/* --- USE flexible API (using multi-type transaction function) --- */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <split_scomm.h>
#include "serial.h"
#ifdef SERIAL_DEBUG_MODE
#include <avr/io.h>
#endif

uint8_t volatile serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH] = {0};
uint8_t volatile serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH] = {0};
uint8_t volatile status_com = 0;
uint8_t volatile status1 = 0;
uint8_t slave_buffer_change_count = 0;
uint8_t s_change_old = 0xff;

SSTD_t transactions[] = {
#define GET_SLAVE_STATUS 0
    /* master buffer not changed, only recive slave_buffer_change_count */
    { (uint8_t *)&status_com,
      0, NULL,
      sizeof(slave_buffer_change_count), &slave_buffer_change_count,
    },
#define PUT_MASTER_GET_SLAVE_STATUS 1
    /* master buffer changed need send, and recive slave_buffer_change_count  */
    { (uint8_t *)&status_com,
      sizeof(serial_master_buffer), (uint8_t *)serial_master_buffer,
      sizeof(slave_buffer_change_count), &slave_buffer_change_count,
    },
#define GET_SLAVE_BUFFER 2
    /* recive serial_slave_buffer */
    { (uint8_t *)&status1,
      0, NULL,
      sizeof(serial_slave_buffer), (uint8_t *)serial_slave_buffer
    }
};

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
    int status;
    static int need_retry = 0;
    if( s_change_old != slave_buffer_change_count ) {
	status = soft_serial_transaction(GET_SLAVE_BUFFER);
	if( status == TRANSACTION_END )
	    s_change_old = slave_buffer_change_count;
    }
    if( !master_update && !need_retry)
	status = soft_serial_transaction(GET_SLAVE_STATUS);
    else
	status = soft_serial_transaction(PUT_MASTER_GET_SLAVE_STATUS);
    need_retry = ( status == TRANSACTION_END ) ? 0 : 1;
    return status;
}

#endif // SERIAL_USE_MULTI_TRANSACTION
#endif /* USE_SERIAL */
