#ifdef USE_SERIAL
#ifdef SERIAL_USE_MULTI_TRANSACTION
/* --- USE flexible API (using multi-type transaction function) --- */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <split_scomm.h>
#include "serial.h"
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

uint8_t volatile serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH] = {0};
#ifndef RGBLIGHT_SPLIT
uint8_t volatile serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH] = {0};
#endif
#ifdef RGBLIGHT_SPLIT
rgblight_syncinfo_t volatile serial_master_rgb = {};
#endif
uint8_t volatile status_com = 0;
uint8_t volatile status_rgb = 0;
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
#define GET_SLAVE_BUFFER 1
    /* recive serial_slave_buffer */
    { (uint8_t *)&status1,
      0, NULL,
      sizeof(serial_slave_buffer), (uint8_t *)serial_slave_buffer
    },
#ifndef RGBLIGHT_SPLIT
#define PUT_MASTER_GET_SLAVE_STATUS 2
    /* master buffer changed need send, and recive slave_buffer_change_count  */
    { (uint8_t *)&status_com,
      sizeof(serial_master_buffer), (uint8_t *)serial_master_buffer,
      sizeof(slave_buffer_change_count), &slave_buffer_change_count,
    }
#endif
#ifdef RGBLIGHT_SPLIT
#define PUT_MASTER_RGB_STATUS 2
    /* master rgb status changed need send  */
    { (uint8_t *)&status_rgb,
      sizeof(serial_master_rgb), (uint8_t *)&serial_master_rgb,
      0, NULL
    }
#endif
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
#ifndef RGBLIGHT_SPLIT
    static int need_retry = 0;
#endif
    if( s_change_old != s_change_new ) {
        smatstatus = soft_serial_transaction(GET_SLAVE_BUFFER);
        if( smatstatus == TRANSACTION_END ) {
            s_change_old = s_change_new;
#ifdef CONSOLE_ENABLE
            uprintf("slave matrix = %b %b %b %b %b\n",
                    serial_slave_buffer[0], serial_slave_buffer[1],
                    serial_slave_buffer[2], serial_slave_buffer[3],
                    serial_slave_buffer[4] );
#endif
        }
    } else {
        // serial_slave_buffer dosen't change
        smatstatus = TRANSACTION_END; // dummy status
    }

#ifndef RGBLIGHT_SPLIT
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
#else
    status = soft_serial_transaction(GET_SLAVE_STATUS);
    if( status == TRANSACTION_END ) {
        s_change_new = slave_buffer_change_count;
    }
#endif
    return smatstatus;
}

int serial_update_rgb(void)
{
#ifdef RGBLIGHT_SPLIT
    int status;
    if (rgblight_get_change_flags()) {
        rgblight_get_syncinfo((rgblight_syncinfo_t *)&serial_master_rgb);
        status = soft_serial_transaction(PUT_MASTER_RGB_STATUS);
        if (status == TRANSACTION_END) {
            rgblight_clear_change_flags();
        }
        return status;
    } else {
        return TRANSACTION_END;
    }
#else
    return TRANSACTION_END;
#endif
}

void serial_sync_rgb(void)
{
#ifdef RGBLIGHT_SPLIT
    if( status_rgb == TRANSACTION_ACCEPTED ) {
        rgblight_update_sync((rgblight_syncinfo_t *)&serial_master_rgb, false);
        status_rgb = TRANSACTION_END;
    }
#endif
}

#endif // SERIAL_USE_MULTI_TRANSACTION
#endif /* USE_SERIAL */
