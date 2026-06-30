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

#include "uart3.h"

#include "quantum.h"

#if defined(MCU_KINETIS)
static SerialConfig serialConfig = {SERIAL_DEFAULT_BITRATE};
#elif defined(WB32F3G71xx) || defined(WB32FQ95xx)
static SerialConfig serialConfig = {SERIAL_DEFAULT_BITRATE, SD3_WRDLEN, SD3_STPBIT, SD3_PARITY, SD3_ATFLCT};
#else
static SerialConfig serialConfig = {SERIAL_DEFAULT_BITRATE, SD3_CR1, SD3_CR2, SD3_CR3};
#endif

void uart3_init(uint32_t baud) {
    static bool is_initialised = false;

    if (!is_initialised) {
        is_initialised = true;

#if defined(MCU_KINETIS)
        serialConfig.sc_speed = baud;
#else
        serialConfig.speed = baud;
#endif

#if defined(USE_GPIOV1)
        palSetLineMode(SD3_TX_PIN, SD3_TX_PAL_MODE);
        palSetLineMode(SD3_RX_PIN, SD3_RX_PAL_MODE);
#else
        palSetLineMode(SD3_TX_PIN, PAL_MODE_ALTERNATE(SD3_TX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetLineMode(SD3_RX_PIN, PAL_MODE_ALTERNATE(SD3_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
#endif
        sdStart(&SERIAL3_DRIVER, &serialConfig);
    }
}

void uart3_write(uint8_t data) {
    sdPut(&SERIAL3_DRIVER, data);
}

uint8_t uart3_read(void) {
    msg_t res = sdGet(&SERIAL3_DRIVER);

    return (uint8_t)res;
}

void uart3_transmit(const uint8_t *data, uint16_t length) {
    sdWrite(&SERIAL3_DRIVER, data, length);
}

void uart3_receive(uint8_t *data, uint16_t length) {
    sdRead(&SERIAL3_DRIVER, data, length);
}

bool uart3_available(void) {
    return !sdGetWouldBlock(&SERIAL3_DRIVER);
}
