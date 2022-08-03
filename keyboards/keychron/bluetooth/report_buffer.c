/* Copyright 2022 @ lokher (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "report_buffer.h"
#include "bluetooth.h"
#include "lpm.h"

/* The report buffer is mainly used to fix key press lost issue of macro
 * when bluetooth module fifo isn't large enough. The maximun macro
 * string length is determined by this queue size, and should be
 * REPORT_BUFFER_QUEUE_SIZE devided by 2 since each character is implemented
 * by sending a key pressing then a key releasing report.
 * Please note that it cosume sizeof(report_buffer_t)  * REPORT_BUFFER_QUEUE_SIZE
 * bytes RAM, with default setting, used RAM size is
 *        sizeof(report_buffer_t) * 256 = 34* 256  =  8704 bytes
 */
#ifndef REPORT_BUFFER_QUEUE_SIZE
#    define REPORT_BUFFER_QUEUE_SIZE 256
#endif

extern bluetooth_transport_t bluetooth_transport;

/* report_interval value should be less than bluetooth connection interval because
 * it takes some time for communicating between mcu and bluetooth module. Carefully
 * set this value to feed the bt module so that we don't lost the key report nor lost
 * the anchor point of bluetooth interval. The bluetooth connection interval varies
 * if BLE is used, invoke report_buffer_set_inverval() to update the value
 */
uint8_t report_interval = DEFAULT_REPORT_INVERVAL_MS;

static uint32_t report_timer_buffer = 0;
uint32_t        retry_time_buffer   = 0;
report_buffer_t report_buffer_queue[REPORT_BUFFER_QUEUE_SIZE];
uint8_t         report_buffer_queue_head;
uint8_t         report_buffer_queue_tail;
report_buffer_t kb_rpt;
uint8_t         retry = 0;

void report_buffer_init(void) {
    // Initialise the report queue
    memset(&report_buffer_queue, 0, sizeof(report_buffer_queue));
    report_buffer_queue_head = 0;
    report_buffer_queue_tail = 0;
    retry                    = 0;
    report_timer_buffer      = sync_timer_read32();
}

bool report_buffer_enqueue(report_buffer_t *report) {
    uint8_t next = (report_buffer_queue_head + 1) % REPORT_BUFFER_QUEUE_SIZE;
    if (next == report_buffer_queue_tail) {
        return false;
    }

    report_buffer_queue[report_buffer_queue_head] = *report;
    report_buffer_queue_head                      = next;
    return true;
}

inline bool report_buffer_dequeue(report_buffer_t *report) {
    if (report_buffer_queue_head == report_buffer_queue_tail) {
        return false;
    }

    *report                  = report_buffer_queue[report_buffer_queue_tail];
    report_buffer_queue_tail = (report_buffer_queue_tail + 1) % REPORT_BUFFER_QUEUE_SIZE;
    return true;
}

bool report_buffer_is_empty() {
    return report_buffer_queue_head == report_buffer_queue_tail;
}

void report_buffer_update_timer(void) {
    report_timer_buffer = sync_timer_read32();
}

bool report_buffer_next_inverval(void) {
    return sync_timer_elapsed32(report_timer_buffer) > report_interval;
}

void report_buffer_set_inverval(uint8_t interval) {
    report_interval = interval;
}

uint8_t report_buffer_get_retry(void) {
    return retry;
}

void report_buffer_set_retry(uint8_t times) {
    retry = times;
}

void report_buffer_task(void) {
    if (bluetooth_get_state() == BLUETOOTH_CONNECTED && (!report_buffer_is_empty() || retry) && report_buffer_next_inverval()) {
        bool pending_data = false;

        if (!retry) {
            if (report_buffer_dequeue(&kb_rpt) && kb_rpt.type != REPORT_TYPE_NONE) {
                if (sync_timer_read32() > 2) {
                    pending_data      = true;
                    retry             = RETPORT_RETRY_COUNT;
                    retry_time_buffer = sync_timer_read32();
                }
            }
        } else {
            if (sync_timer_elapsed32(retry_time_buffer) > 7) {
                pending_data = true;
                --retry;
                retry_time_buffer = sync_timer_read32();
            }
        }

        if (pending_data) {
#if defined(NKRO_ENABLE) && defined(BLUETOOTH_NKRO_ENABLE)
            if (kb_rpt.type == REPORT_TYPE_NKRO && bluetooth_transport.send_nkro) {
                bluetooth_transport.send_nkro(&kb_rpt.keyboard.nkro.mods);
            } else if (kb_rpt.type == REPORT_TYPE_KB && bluetooth_transport.send_keyboard)
                bluetooth_transport.send_keyboard(&kb_rpt.keyboard.mods);
#else
            if (kb_rpt.type == REPORT_TYPE_KB && bluetooth_transport.send_keyboard) bluetooth_transport.send_keyboard(&kb_rpt.keyboard.mods);
#endif
            if (kb_rpt.type == REPORT_TYPE_CONSUMER && bluetooth_transport.send_consumer) bluetooth_transport.send_consumer(kb_rpt.consumer);
            report_timer_buffer = sync_timer_read32();
            lpm_timer_reset();
        }
    }
}
