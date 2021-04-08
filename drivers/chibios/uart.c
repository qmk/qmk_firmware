/* Copyright 2021
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "uart.h"

#include "quantum.h"

static SerialConfig serialConfig = {SERIAL_DEFAULT_BITRATE, SD1_CR1, SD1_CR2, SD1_CR3};

void uart_init(uint32_t baud) {
    static bool is_initialised = false;

    if (!is_initialised) {
        is_initialised = true;

        serialConfig.speed = baud;

#if defined(USE_GPIOV1)
        palSetLineMode(SD1_TX_PIN, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
        palSetLineMode(SD1_RX_PIN, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
#else
        palSetLineMode(SD1_TX_PIN, PAL_MODE_ALTERNATE(SD1_TX_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
        palSetLineMode(SD1_RX_PIN, PAL_MODE_ALTERNATE(SD1_RX_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
#endif
        sdStart(&SERIAL_DRIVER, &serialConfig);
    }
}

void uart_putchar(uint8_t c) { sdPut(&SERIAL_DRIVER, c); }

uint8_t uart_getchar(void) {
    msg_t res = sdGet(&SERIAL_DRIVER);

    return (uint8_t)res;
}

bool uart_available(void) { return !sdGetWouldBlock(&SERIAL_DRIVER); }
