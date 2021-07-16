/* Copyright 2021 sekigon-gonnoc
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

enum {
    KQB_PIN_CHBOOT = 1,
    KQB_PIN_BOOT,
    KQB_PIN_CHRST,
    KQB_PIN_SCK,
    KQB_PIN_MISO,
    KQB_PIN_LED0,
    KQB_PIN_LED1,
    KQB_PIN_MOSI,
    KQB_PIN_CS,
    KQB_PIN_TX,
    KQB_PIN_RX,
} KQB_PIN;

void uart_recv_callback(uint8_t dat);
void uart_buf_init(void);
