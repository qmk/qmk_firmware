/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef USE_SERIAL
#ifdef SERIAL_USE_MULTI_TRANSACTION
/* --- USE flexible API (using multi-type transaction function) --- */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "split_scomm.h"
#include "serial.h"
#ifdef CONSOLE_ENABLE
  #include "debug.h"
#endif

uint8_t volatile serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH] = {0};
uint8_t volatile serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH] = {0};
uint8_t volatile status_com = 0;
uint8_t volatile status1 = 0;
uint8_t slave_buffer_change_count = 0;
uint8_t s_change_old = 0xff;
uint8_t s_change_new = 0xff;

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
    soft_serial_initiator_init(transactions, TID_LIMIT(transactions));
}

void serial_slave_init(void)
{
    soft_serial_target_init(transactions, TID_LIMIT(transactions));
}

// 0 => no error
// 1 => slave did not respond
// 2 => checksum error
int serial_update_buffers(int master_update)
{
    int status, smatstatus;
    static int need_retry = 0;

    if( s_change_old != s_change_new ) {
        smatstatus = soft_serial_transaction(GET_SLAVE_BUFFER);
        if( smatstatus == TRANSACTION_END ) {
            s_change_old = s_change_new;
#ifdef CONSOLE_ENABLE
            if (debug_matrix) {
                uprintf("slave matrix = %b %b %b %b\n",
                    serial_slave_buffer[0], serial_slave_buffer[1],
                    serial_slave_buffer[2], serial_slave_buffer[3]);
            }
#endif
        }
    } else {
        // serial_slave_buffer dosen't change
        smatstatus = TRANSACTION_END; // dummy status
    }

    if( !master_update && !need_retry) {
        status = soft_serial_transaction(GET_SLAVE_STATUS);
    } else {
        status = soft_serial_transaction(PUT_MASTER_GET_SLAVE_STATUS);
    }
    if( status == TRANSACTION_END ) {
        s_change_new = slave_buffer_change_count;
        need_retry = 0;
    } else {
        need_retry = 1;
    }
    return smatstatus;
}

#endif // SERIAL_USE_MULTI_TRANSACTION
#endif /* USE_SERIAL */
