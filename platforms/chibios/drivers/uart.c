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

#if defined(MCU_KINETIS)
static SerialConfig serialConfig = {SERIAL_DEFAULT_BITRATE};
#elif defined(WB32F3G71xx) || defined(WB32FQ95xx)
static SerialConfig serialConfig = {SERIAL_DEFAULT_BITRATE, SD_WRDLEN, SD_STPBIT, SD_PARITY, SD_ATFLCT};
#else
static SerialConfig serialConfig = {SERIAL_DEFAULT_BITRATE, SD_CR1, SD_CR2, SD_CR3};
#endif

void uart_init(uint32_t baud) {
    static bool is_initialised = false;

    if (!is_initialised) {
        is_initialised = true;

#if defined(MCU_KINETIS)
        serialConfig.sc_speed = baud;
#else
        serialConfig.speed = baud;
#endif

#if defined(USE_GPIOV1)
        palSetLineMode(SD_TX_PIN, PAL_MODE_ALTERNATE_PUSHPULL);
        palSetLineMode(SD_RX_PIN, PAL_MODE_INPUT);
#else
        palSetLineMode(SD_TX_PIN, PAL_MODE_ALTERNATE(SD_TX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetLineMode(SD_RX_PIN, PAL_MODE_ALTERNATE(SD_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
#endif
        sdStart(&SERIAL_DRIVER, &serialConfig);
    }
}

void uart_write(uint8_t data) {
    sdPut(&SERIAL_DRIVER, data);
}

uint8_t uart_read(void) {
    msg_t res = sdGet(&SERIAL_DRIVER);

    return (uint8_t)res;
}

void uart_transmit(const uint8_t *data, uint16_t length) {
    sdWrite(&SERIAL_DRIVER, data, length);
}

void uart_receive(uint8_t *data, uint16_t length) {
    sdRead(&SERIAL_DRIVER, data, length);
}

bool uart_available(void) {
    return !sdGetWouldBlock(&SERIAL_DRIVER);
}
