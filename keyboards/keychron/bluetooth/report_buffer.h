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

#pragma once

#include "report.h"

/* Default report interval value */
#ifndef DEFAULT_REPORT_INVERVAL_MS
#    define DEFAULT_REPORT_INVERVAL_MS 3
#endif

/* Default report interval value */
#ifndef RETPORT_RETRY_COUNT
#    define RETPORT_RETRY_COUNT 30
#endif

enum { REPORT_TYPE_NONE, REPORT_TYPE_KB, REPORT_TYPE_NKRO, REPORT_TYPE_CONSUMER };

typedef struct {
    uint8_t type;
    union {
        report_keyboard_t keyboard;
        uint16_t          consumer;
    };
} report_buffer_t;

void    report_buffer_init(void);
bool    report_buffer_enqueue(report_buffer_t *report);
bool    report_buffer_dequeue(report_buffer_t *report);
bool    report_buffer_is_empty(void);
void    report_buffer_update_timer(void);
bool    report_buffer_next_inverval(void);
void    report_buffer_set_inverval(uint8_t interval);
uint8_t report_buffer_get_retry(void);
void    report_buffer_set_retry(uint8_t times);
void    report_buffer_task(void);
