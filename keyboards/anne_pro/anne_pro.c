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

/* State of the leds on the keyboard */
volatile bool leds_enabled = false;

/* Process the Anne Pro custom keycodes */
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case APL_RGB:
        /* Toggle the RGB enabled/disabled */
        if (record->event.pressed) {
            leds_enabled = !leds_enabled;
            if (leds_enabled) {
                uartStartSend(&UARTD3, 3, "\x09\x01\x01");
            } else {
                uartStartSend(&UARTD3, 4, "\x09\x02\x01\x00");
            }
        }
        return false;
    case APL_RAT:
        /* Change the animation rate */
        if (leds_enabled && record->event.pressed) {
            uartStartSend(&UARTD3, 6, "\x09\x04\x05\x00\x01\x00");
        }
        return false;
    case APL_BRT:
        /* Change the brightness */
        if (leds_enabled && record->event.pressed) {
            uartStartSend(&UARTD3, 6, "\x09\x04\x05\x00\x00\x01");
        }
        return false;
    case APL_MOD:
        /* Change the lighting mode */
        if (leds_enabled && record->event.pressed) {
            uartStartSend(&UARTD3, 6, "\x09\x04\x05\x01\x00\x00");
        }
        return false;
    default:
        /* Handle other keycodes normally */
        return process_record_user(keycode, record);
    }
}

/* Initialize custom keyboard features */
void keyboard_post_init_kb(void) {
    /* Turn on lighting controller */
    setPinOutput(C15);
    writePinLow(C15);
    chThdSleepMilliseconds(10);
    writePinHigh(C15);
    chThdSleepMilliseconds(10);

    /* Initialize the lighting UART */
    uartStart(&UARTD3, &uart_cfg);
    palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOB, 11, PAL_MODE_ALTERNATE(7));

    /* Send 'set theme' command to lighting controller */
    leds_enabled = true;
    uartStartSend(&UARTD3, 3, "\x09\x01\x01");

    matrix_init_user();
}

/* Instead of doing some magic to get to the bootloader, just press ESC and reset */
void bootloader_jump(void) {
    /* Disable interrupts as changing the vector table can mess them up */
    __disable_irq();
    /* Move the vector table back to the bootloader */
    SCB->VTOR = 0x08000000;
    /* Reset the system into the bootloader */
    NVIC_SystemReset();
}
