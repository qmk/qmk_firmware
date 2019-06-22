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

/*
 * This callback is invoked when a transmission buffer has been completely
 * read by the driver.
 */
static void txend1(UARTDriver *uartp) {
    (void)uartp;
}

/*
 * This callback is invoked when a transmission has physically completed.
 */
static void txend2(UARTDriver *uartp) {
    (void)uartp;
}

/*
 * This callback is invoked on a receive error, the errors mask is passed
 * as parameter.
 */
static void rxerr(UARTDriver *uartp, uartflags_t e) {
    (void)uartp;
    (void)e;
}

/*
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 */
static void rxchar(UARTDriver *uartp, uint16_t c) {
    (void)uartp;
    (void)c;
}

/*
 * This callback is invoked when a receive buffer has been completely written.
 */
static void rxend(UARTDriver *uartp) {
    (void)uartp;
}


static UARTConfig uart_cfg = {
    .txend1_cb = txend1,
    .txend2_cb = txend2,
    .rxend_cb = rxend,
    .rxchar_cb = rxchar,
    .rxerr_cb = rxerr,
    .speed = 38400,
    .cr1 = 0,
    .cr2 = USART_CR2_LINEN,
    .cr3 = 0
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        /* Send 'next theme' command to lighting controller */
        uartStartSend(&UARTD3, 4, "\x09\x04\x05\x01\x00\x00");
    }
    return true;
}

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
    uartStartSend(&UARTD3, 4, "\x09\x02\x01\x01");

    matrix_init_user();
}
