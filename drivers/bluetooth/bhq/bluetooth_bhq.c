/* Copyright 2024 keymagichorse
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

#include "bluetooth_bhq.h"
#include "bhq.h"
#include "report_buffer.h"

uint8_t bhq_led_sta = 0;

void bluetooth_bhq_init(void) {
    bhq_init();
    report_buffer_init();
}

void bluetooth_bhq_task(void) {
    bhq_task();
    report_buffer_task();
}

/**
 * \brief Send a keyboard report.
 *
 * \param report The keyboard report to send.
 */

void bluetooth_bhq_send_keyboard(report_keyboard_t *report)
{
    bool firstBuffer = false;

    if (report_buffer_is_empty() && report_buffer_next_inverval() && report_buffer_get_retry() == 0) {
        firstBuffer = true;
    }

    report_buffer_t *last_report = report_buffer_peek_last();
    if (last_report &&
        last_report->type == REPORT_TYPE_KB &&
        timer_elapsed32(last_report->tm) < 5)
    {
        memcpy(&last_report->report_data, report, sizeof(report_keyboard_t));
        last_report->tm = timer_read32();
        return;  
    }

    report_buffer_t report_buffer;
    report_buffer.type = REPORT_TYPE_KB;
    report_buffer.tm = timer_read32();
    memcpy(&report_buffer.report_data, report, sizeof(report_keyboard_t));
    report_buffer_enqueue(&report_buffer);

    if (firstBuffer) {
        report_buffer_task();
    }
}
/**
 * \brief Send a mouse report.
 *
 * \param report The mouse report to send.
 */
void bluetooth_bhq_send_mouse(report_mouse_t *report)
{
    bhq_send_mouse((uint8_t *)report);
}

/**
 * \brief Send a consumer usage.
 *
 * \param usage The consumer usage to send.
 */
void bluetooth_bhq_send_consumer(uint16_t usage)
{
    bool firstBuffer = false;
    if (report_buffer_is_empty() && report_buffer_next_inverval()) {
        firstBuffer = true;
    }

    report_buffer_t report_buffer;
    report_buffer.type     = REPORT_TYPE_CONSUMER;
    report_buffer.consumer = usage;
    report_buffer_enqueue(&report_buffer);

    if (firstBuffer) {
        report_buffer_task();
    }
}

/**
 * \brief Send a system usage.
 *
 * \param usage The system usage to send.
 */
void bluetooth_bhq_send_system(uint16_t usage)
{
    bool firstBuffer = false;
    if (report_buffer_is_empty() && report_buffer_next_inverval()) {
        firstBuffer = true;
    }

    report_buffer_t report_buffer;
    report_buffer.type     = REPORT_TYPE_SYSTEM;
    report_buffer.consumer = usage;
    report_buffer_enqueue(&report_buffer);

    if (firstBuffer) {
        report_buffer_task();
    }
}

/**
 * \brief Send a nkro report.
 *
 * \param report The nkro report to send.
 */

void bluetooth_bhq_send_nkro(report_nkro_t *report)
{
    bool firstBuffer = false;

    if (report_buffer_is_empty() && report_buffer_next_inverval()) {
        firstBuffer = true;
    }

    report_buffer_t *last_report = report_buffer_peek_last();

    if (last_report &&
        last_report->type == REPORT_TYPE_NKRO &&
        timer_elapsed32(last_report->tm) < 5) {
        
        last_report->report_data[0] = report->mods;
        for (size_t i = 0; i < NKRO_REPORT_BITS; i++) {
            last_report->report_data[1 + i] = report->bits[i];
        }

        last_report->tm = timer_read32();
        return; 
    }

    report_buffer_t report_buffer;
    report_buffer.type = REPORT_TYPE_NKRO;
    report_buffer.tm = timer_read32();

    report_buffer.report_data[0] = report->mods;
    for (size_t i = 0; i < NKRO_REPORT_BITS; i++) {
        report_buffer.report_data[1 + i] = report->bits[i];
    }

    report_buffer_enqueue(&report_buffer);

    if (firstBuffer) {
        report_buffer_task();  
    }
}

/**
 * \brief Send a hid_raw report.
 *
 * \param report The hid_raw report to send.
 */
void bluetooth_bhq_send_hid_raw(uint8_t *data, uint8_t length)
{
    bhq_send_hid_raw(data,length);
}


void bluetooth_bhq_set_keyboard_leds(uint8_t led_sta)
{
    bhq_led_sta = led_sta;
}

uint8_t bluetooth_bhq_get_keyboard_leds(void)
{
    return bhq_led_sta;
}

