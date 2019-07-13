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

#include "anne_pro_bluetooth.h"
#include "uart_tx_ringbuf.h"
#include "host.h"
#include "host_driver.h"

#define BLUETOOTH_UART (&UARTD2)
/* UART transmission ringbuffer for the Bluetooth UART */
static uint8_t bluetooth_uart_tx_buffer[256] = {0};
static uart_tx_ringbuf_t bluetooth_uart_ringbuf = {
    .buf = bluetooth_uart_tx_buffer,
    .uart = BLUETOOTH_UART,
    .size = sizeof(bluetooth_uart_tx_buffer),
    .sending_elements = 0,
    .head = 0,
    .tail = 0,
};

/* Handler for finsihed Bluetooth UART transmissions */
static void bluetooth_uart_txend(UARTDriver *uart) {
    uart_tx_ringbuf_finish_transmission(&bluetooth_uart_ringbuf);
}

/* Wakeup bluetooth chip and wait for acknoledgement */
msg_t bluetooth_wakeup(void) {
    char rx_buf[3];
    size_t frames = 3;
    palSetPad(GPIOA, 1);
    msg_t result = uartReceiveTimeout(BLUETOOTH_UART, &frames, &rx_buf, 10);
    palClearPad(GPIOA, 1);
    return result;
}

/* Update Bluetooth, should be called every matrix scan */
void anne_pro_bluetooth_update(void) {
    if (!uart_tx_ringbuf_empty(&bluetooth_uart_ringbuf)) {
        if (bluetooth_wakeup() == MSG_OK) {
            uart_tx_ringbuf_start_transmission(&bluetooth_uart_ringbuf);
        }
    }
}

void bluetooth_rx_char(UARTDriver *driver, uint16_t c);
/* Bluetooth UART configuration */
static UARTConfig bluetooth_uart_cfg = {
    .txend1_cb = bluetooth_uart_txend,
    .txend2_cb = NULL,
    .rxend_cb = NULL,
    .rxchar_cb = bluetooth_rx_char,
    .rxerr_cb = NULL,
    .speed = 38400,
    .cr1 = 0,
    .cr2 = USART_CR2_LINEN,
    .cr3 = 0
};

/* Receive buffer for the Bluetooth UART */
uint8_t bluetooth_rx_buffer[256] = {0};
size_t bluetooth_rx_index = 0;

/* Lookup table for translation to hex */
char hex_lookup[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

/* Handle packets from the bluetooth receive buffer */
void bluetooth_handle_packet(void) {
    /* Packet type and length */
    uint8_t packet_type = bluetooth_rx_buffer[0];
    // uint8_t packet_len = bluetooth_rx_buffer[1];

    /* Handle incomming packets over Bluetooth */
    switch (packet_type) {
    case 2: // System
        switch (bluetooth_rx_buffer[2]) {
        case 1: // GetId
            // [2, 15, 129, 10,  2,  0,  1,  2, 50, 55, 71,  1, 50, 48]
            // [2, 15, 129,  8,  2,  1, 54, 48, 52,  0, 54,  0, 50, 48]
            uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 28, "\x02\x0f\x81\x0a\x02\x00\x01\x02\x32\x37\x47\x01\x32\x30"
                                                               "\x02\x0f\x81\x08\x02\x01\x36\x30\x34\x00\x36\x00\x32\x30");
            break;
        }
        break;
    }
}

/* Receive single character from the Bluetooth UART */
void bluetooth_rx_char(UARTDriver *driver, uint16_t c) {
    bluetooth_rx_buffer[bluetooth_rx_index++] = c;

    if (bluetooth_rx_index > 2) {
        uint8_t packet_len = bluetooth_rx_buffer[1];
        if (bluetooth_rx_index >= (2 + packet_len)) {
            bluetooth_handle_packet();
            bluetooth_rx_index = 0;
        }
    }
}

/* Initialize the Anne Pro Bluetooth */
void anne_pro_bluetooth_init(void) {
    /* Initialize the bleutooth UART */
    uartStart(BLUETOOTH_UART, &bluetooth_uart_cfg);
    palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOA, 1, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOA, 1);

    /* Disable bluetooth on startup */
    anne_pro_bluetooth_off();
}

/* Turn on Bluetooth */
void anne_pro_bluetooth_on(void) {
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 3, "\x06\x01\x01");
}

/* Turn off Bluetooth */
void anne_pro_bluetooth_off(void) {
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 3, "\x06\x01\x02");
}

/* Start broadcasting on Bluetooth */
void anne_pro_bluetooth_broadcast(void) {
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 3, "\x06\x01\x07");
}

/* Status of keyboard leds for Bluetooth driver*/
static uint8_t keyboard_leds(void) {
    return 0;
}

/* Send keyboard HID report for Bluetooth driver */
static void send_keyboard(report_keyboard_t *report) {
    uint8_t bluetooth_report[11] = {7, 9, 1, 0};
    bluetooth_report[3] = report->mods;
    bluetooth_report[4] = report->reserved;
    for (int i = 0; i < 6; i++) {
        bluetooth_report[5+i] = report->keys[i];
    }
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 11, bluetooth_report);
}

/* Send mouse HID report for Bluetooth driver */
static void send_mouse(report_mouse_t *report) {
}

/* Send system report for Bluetooth driver */
static void send_system(uint16_t data) {
}

/* Send consumer report for Bluetooth driver */
static void send_consumer(uint16_t data) {
}

/* Bluetooth host driver, this allows us to switch from USB output to Bluetooth output */
host_driver_t anne_pro_bluetooth_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer
};
