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
#include "uart_tx_ringbuf.h"
#include "ch.h"
#include "hal.h"

#define LED_UART (&UARTD3)
/* UART transmission ringbuffer for the LED UART */
static uint8_t led_uart_tx_buffer[256] = {0};
static uart_tx_ringbuf_t led_uart_ringbuf = {
    .buf = led_uart_tx_buffer,
    .uart = LED_UART,
    .size = sizeof(led_uart_tx_buffer),
    .sending_elements = 0,
    .head = 0,
    .tail = 0,
};

/* Should the main loop try a transmission, used when transmission finishes
   to send any data that might have been added to the buffer while the
   transmission was in progress.
*/
static volatile bool led_uart_try_transmission = false;

/* Handler for finsihed LED UART transmissions */
static void led_uart_txend(UARTDriver *uart) {
    uart_tx_ringbuf_finish_transmission(&led_uart_ringbuf);
    led_uart_try_transmission = true;
}

/* LED UART configuration */
static UARTConfig led_uart_cfg = {
    .txend1_cb = led_uart_txend,
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
static volatile bool leds_enabled = false;

/* Buffer for the keystate packet */
static uint8_t keystate[12] = {9, 10, 7, 0};

/* Update the dynamic lighting packet based on a keypress */
void update_dynamic_lighting(keyrecord_t *record) {
    /* Only update dynamic lighting modes when leds are enabled */
    if (leds_enabled) {
        /* Calculate the position of the key that was pressed */
        uint8_t row = record->event.key.row;
        uint8_t col = record->event.key.col;
        int position = row * MATRIX_COLS + col;
        int index = position / 8;
        int bit = position % 8;

        /* Update the keystate based on the location */
        if (record->event.pressed) {
            keystate[3 + index] |= (1 << bit);
        } else {
            keystate[3 + index] &= ~(1 << bit);
        }

        /* Send the keystate to the LED controller */
        uart_tx_ringbuf_write(&led_uart_ringbuf, 12, keystate);
    }
}

/* Process the Anne Pro custom keycodes */
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    update_dynamic_lighting(record);

    switch (keycode) {
    case APL_RGB:
        /* Toggle the RGB enabled/disabled */
        if (record->event.pressed) {
            leds_enabled = !leds_enabled;
            if (leds_enabled) {
                uart_tx_ringbuf_write(&led_uart_ringbuf, 3, "\x09\x01\x01");
            } else {
                uart_tx_ringbuf_write(&led_uart_ringbuf, 4, "\x09\x02\x01\x00");
            }
        }
        return false;
    case APL_RAT:
        /* Change the animation rate */
        if (leds_enabled && record->event.pressed) {
            uart_tx_ringbuf_write(&led_uart_ringbuf, 6, "\x09\x04\x05\x00\x01\x00");
        }
        return false;
    case APL_BRT:
        /* Change the brightness */
        if (leds_enabled && record->event.pressed) {
            uart_tx_ringbuf_write(&led_uart_ringbuf, 6, "\x09\x04\x05\x00\x00\x01");
        }
        return false;
    case APL_MOD:
        /* Change the lighting mode */
        if (leds_enabled && record->event.pressed) {
            uart_tx_ringbuf_write(&led_uart_ringbuf, 6, "\x09\x04\x05\x01\x00\x00");
        }
        return false;
    default:
        /* Handle other keycodes normally */
        return process_record_user(keycode, record);
    }
}

/* Initialize custom keyboard features */
void keyboard_pre_init_kb(void) {
    /* Turn on lighting controller */
    setPinOutput(C15);
    writePinLow(C15);
    chThdSleepMilliseconds(10);
    writePinHigh(C15);
    chThdSleepMilliseconds(10);

    /* Initialize the lighting UART */
    uartStart(LED_UART, &led_uart_cfg);
    palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOB, 11, PAL_MODE_ALTERNATE(7));

    keyboard_pre_init_user();
}

/* Turn on the lighting when init is finished */
void keyboard_post_init_kb(void) {
    /* Send 'set theme' command to lighting controller */
    uart_tx_ringbuf_write(&led_uart_ringbuf, 4, "\x09\x02\x01\x0e");
    /* Send 'set speed and brightness' command to lighting controller */
    uart_tx_ringbuf_write(&led_uart_ringbuf, 6, "\x09\x04\x02\x80\x01\x00");
    /* Mark LEDs as enabled */
    leds_enabled = true;

    keyboard_post_init_user();
}

/* Start transmissions when the flag is set */
void matrix_scan_kb(void) {
    if (led_uart_try_transmission) {
        uart_tx_ringbuf_start_transmission(&led_uart_ringbuf);
        led_uart_try_transmission = false;
    }

    /* Run matrix_scan_user code */
    matrix_scan_user();
}
