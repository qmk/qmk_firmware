/* Copyright 2019 Michiel Visser
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

#include "anne_pro.h"
#include "ch.h"
#include "hal.h"

static UARTConfig uart_cfg = {
    .txend1_cb = NULL,
    .txend2_cb = NULL,
    .rxend_cb = NULL,
    .rxchar_cb = NULL,
    .rxerr_cb = NULL,
    .speed = 38400,
    .cr1 = 0,
    .cr2 = USART_CR2_LINEN,
    .cr3 = 0
};

extern volatile bool leds_enabled;

void matrix_init_kb(void) {
    /* Turn on lighting controller */
    setPinOutput(C15);
    writePinLow(C15);
    chThdSleepMilliseconds(100);
    writePinHigh(C15);
    chThdSleepMilliseconds(100);

    /* Initialize the lighting UART */
    uartStart(&UARTD3, &uart_cfg);
    palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOB, 11, PAL_MODE_ALTERNATE(7));

    /* Send 'set theme' command to lighting controller */
    leds_enabled = true;
    uartStartSend(&UARTD3, 4, "\x09\x01\x01");

    matrix_init_user();
}
