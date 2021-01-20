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

static SerialConfig serialConfig = {
    SERIAL_DEFAULT_BITRATE,
    0,
    USART_CR2_STOP_1,
    0
};

void uart_init(uint32_t baud) {
    static bool is_initialised = false;

    if (!is_initialised) {
        is_initialised = true;

        serialConfig.speed = baud;

#if defined(USE_GPIOV1)
        palSetPadMode(SD1_TX_BANK, SD1_TX, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
        palSetPadMode(SD1_RX_BANK, SD1_RX, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
#else
        palSetPadMode(SD1_TX_BANK, SD1_TX, PAL_MODE_ALTERNATE(SD1_TX_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
        palSetPadMode(SD1_RX_BANK, SD1_RX, PAL_MODE_ALTERNATE(SD1_RX_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
#endif
        sdStart(&SERIAL_DRIVER, &serialConfig);
    }
}

void uart_putchar(uint8_t c) {
    sdPut(&SERIAL_DRIVER, c);
}

uint8_t uart_getchar(void) {
    msg_t res = sdGet(&SERIAL_DRIVER);

    return (uint8_t)res;
}

uint8_t uart_available(void) {
    // TODO
    return 0;
}
