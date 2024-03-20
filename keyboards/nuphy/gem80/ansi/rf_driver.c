/*
Copyright 2023 @ Nuphy <https://nuphy.com/> (Source from jincao1, extended by Nuphy)

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

#include "host_driver.h"
#include "host.h"
#include "user_kb.h"
#include "rf_queue.h"
#include "report.h"

/* Variable declaration */
extern DEV_INFO_STRUCT dev_info;
extern report_buffer_t report_buff_a;
extern report_buffer_t report_buff_b;
extern rf_queue_t      rf_queue;

/* Host driver */
static uint8_t rf_keyboard_leds(void);
static void    rf_send_keyboard(report_keyboard_t *report);
static void    rf_send_nkro(report_nkro_t *report);
static void    rf_send_mouse(report_mouse_t *report);
static void    rf_send_extra(report_extra_t *report);

const host_driver_t rf_host_driver = {rf_keyboard_leds, rf_send_keyboard, rf_send_nkro, rf_send_mouse, rf_send_extra};

/* defined in rf.c */
void uart_send_report(uint8_t report_type, uint8_t *report_buf, uint8_t report_size);

/**
 * @brief Send or queue the RF report.
 *
 */
static void send_or_queue(report_buffer_t *report) {
    if (dev_info.rf_state == RF_CONNECT && rf_queue.is_empty()) {
        uart_send_report(report->cmd, report->buffer, report->length);
    } else {
        rf_queue.enqueue(report);
    }
}

/**
 * @brief Uart auto nkey send
 */
static void uart_auto_nkey_send(uint8_t *now_bit_report, uint8_t size) {
    static uint8_t bytekb_report_buf[8]    = {0};
    static uint8_t uart_bit_report_buf[16] = {0};
    static uint8_t pre_bit_report[16]      = {0};

    uint8_t i, j, byte_index;
    uint8_t change_mask, offset_mask;
    uint8_t key_code = 0;

    bool f_byte_send = 0;
    bool f_bit_send  = 0;

    if (pre_bit_report[0] ^ now_bit_report[0]) {
        bytekb_report_buf[0] = now_bit_report[0];
        f_byte_send          = 1;
    }

    for (i = 1; i < size; i++) {
        change_mask = pre_bit_report[i] ^ now_bit_report[i];
        offset_mask = 1;
        for (j = 0; j < 8; j++) {
            if (change_mask & offset_mask) {
                if (now_bit_report[i] & offset_mask) {
                    for (byte_index = 2; byte_index < 8; byte_index++) {
                        if (bytekb_report_buf[byte_index] == 0) {
                            bytekb_report_buf[byte_index] = key_code;
                            f_byte_send                   = 1;
                            break;
                        }
                    }
                    if (byte_index >= 8) {
                        uart_bit_report_buf[i] |= offset_mask;
                        f_bit_send = 1;
                    }
                } else {
                    for (byte_index = 2; byte_index < 8; byte_index++) {
                        if (bytekb_report_buf[byte_index] == key_code) {
                            bytekb_report_buf[byte_index] = 0;
                            f_byte_send                   = 1;
                            break;
                        }
                    }
                    if (byte_index >= 8) {
                        uart_bit_report_buf[i] &= ~offset_mask;
                        f_bit_send = 1;
                    }
                }
            }
            key_code++;
            offset_mask <<= 1;
        }
    }
    memcpy(pre_bit_report, now_bit_report, 16);

    if (f_byte_send) {
        report_buffer_t rpt = {.cmd = CMD_RPT_BYTE_KB, .length = 8};
        memcpy(rpt.buffer, &bytekb_report_buf[0], rpt.length);
        send_or_queue(&rpt);
        report_buff_a = rpt;
    }

    if (f_bit_send) {
        report_buffer_t rpt = {.cmd = CMD_RPT_BIT_KB, .length = 16};
        memcpy(rpt.buffer, &uart_bit_report_buf[0], rpt.length);
        send_or_queue(&rpt);
        report_buff_b = rpt;
    }
}

static uint8_t rf_keyboard_leds(void) {
    return dev_info.rf_led;
}

static void rf_send_keyboard(report_keyboard_t *report) {
    report->reserved    = 0;
    report_buffer_t rpt = {.cmd = CMD_RPT_BYTE_KB, .length = 8};
    memcpy(rpt.buffer, &report->mods, rpt.length);
    send_or_queue(&rpt);
    report_buff_a = rpt;
}

static void rf_send_nkro(report_nkro_t *report) {
    memset(&report_buff_a.cmd, 0, sizeof(report_buffer_t));
    memset(&report_buff_b.cmd, 0, sizeof(report_buffer_t));
    uart_auto_nkey_send(&nkro_report->mods, 16); // only need 1 byte mod + 15 byte keys
}

static void rf_send_mouse(report_mouse_t *report) {
    report_buffer_t rpt = {.cmd = CMD_RPT_MS, .length = 5};
    memcpy(rpt.buffer, &report->buttons, rpt.length);
    send_or_queue(&rpt);
}

static void rf_send_extra_helper(uint8_t cmd, report_extra_t *report) {
    report_buffer_t rpt = {.cmd = cmd, .length = 2};
    memcpy(rpt.buffer, (uint8_t *)(&report->usage), rpt.length);
    send_or_queue(&rpt);
}

static void rf_send_extra(report_extra_t *report) {
    if (report->report_id == REPORT_ID_CONSUMER) {
        rf_send_extra_helper(CMD_RPT_CONSUME, report);
    } else if (report->report_id == REPORT_ID_SYSTEM) {
        rf_send_extra_helper(CMD_RPT_SYS, report);
    }
}
