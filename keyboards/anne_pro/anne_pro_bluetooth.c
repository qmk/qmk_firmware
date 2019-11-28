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
#include "anne_pro_lighting.h"
#include "uart_tx_ringbuf.h"
#include "host.h"
#include "host_driver.h"

#define BLUETOOTH_LAYER 3
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

/* Bluetooth processor state */
static bool bluetooth_enabled = false;
static volatile bool bluetooth_legacy = false;
static volatile uint8_t bluetooth_saved_hosts = 0;
static volatile uint8_t bluetooth_connected_host = 0;

/* State for lighting effect when opening the bluetooth layer */
static bool bluetooth_layer_enabled = false;
static bool lighting_before_bluetooth_layer = false;
/* Handle when layers are switched */
uint32_t layer_state_set_kb(uint32_t state) {
    if (!bluetooth_layer_enabled && (state & (1 << BLUETOOTH_LAYER)) != 0) {
        /* Bluetooth layer turned on */
        lighting_before_bluetooth_layer = anne_pro_lighting_enabled();
        bluetooth_layer_enabled = true;
        if (!lighting_before_bluetooth_layer) {
            anne_pro_lighting_on();
        }
        anne_pro_bluetooth_lighting_update();
    } else if (bluetooth_layer_enabled && (state & (1 << BLUETOOTH_LAYER)) == 0) {
        /* Bluetooth layer turned off */
        bluetooth_layer_enabled = false;
        if (!lighting_before_bluetooth_layer) {
            anne_pro_lighting_off();
        } else {
            anne_pro_lighting_mode_last();
        }
    }

    return layer_state_set_user(state);
}

/* Save state for QMK HID driver */
#ifdef NKRO_ENABLE
static bool nkro_enabled_last = false;
#endif
static host_driver_t *host_driver_last;

/* Enable the Bluetooth HID driver */
static void driver_enable_bluetooth(void) {
    /* Skip if the driver is already enabled */
    if (host_get_driver() == &anne_pro_bluetooth_driver) return;

    clear_keyboard();
    host_driver_last = host_get_driver();
#ifdef NKRO_ENABLE
    nkro_enabled_last = keymap_config.nkro;
    keymap_config.nkro = false;
#endif
    host_set_driver(&anne_pro_bluetooth_driver);
}

/* Enable the last HID driver */
static void driver_enable_last(void) {
    /* Skip if the driver is already enabled */
    if (host_get_driver() != &anne_pro_bluetooth_driver) return;

    clear_keyboard();
#ifdef NKRO_ENABLE
    keymap_config.nkro = nkro_enabled_last;
#endif
    host_set_driver(host_driver_last);
}

/* Receive buffer for the Bluetooth UART */
uint8_t bluetooth_rx_buffer[256] = {0};
size_t bluetooth_rx_index = 0;

/* Handle packets from the bluetooth receive buffer */
void bluetooth_handle_packet(void) {
    /* Packet type and length */
    uint8_t packet_type = bluetooth_rx_buffer[0];
    uint8_t packet_len = bluetooth_rx_buffer[1];
    uint8_t message_type = bluetooth_rx_buffer[2];
    uint8_t data_len = packet_len - 1;
    uint8_t *packet_data = &bluetooth_rx_buffer[3];

    /* Handle incomming packets over Bluetooth */
    switch (packet_type) {
    case 2: /* System packet */
        switch (message_type) {
        case 1: /* GetId */
            /* These two buffers of data were extracted from the original Anne Pro firmware
               however the exact meaning of all fields is unknown.
               [2, 15, 129, 10,  2,  0,  1,  2, 50, 55, 71,  1, 50, 48]
               [2, 15, 129,  8,  2,  1, 54, 48, 52,  0, 54,  0, 50, 48] */
            uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 28, "\x02\x0f\x81\x0a\x02\x00\x01\x02\x32\x37\x47\x01\x32\x30"
                                                               "\x02\x0f\x81\x08\x02\x01\x36\x30\x34\x00\x36\x00\x32\x30");
            break;
        }
        break;
    case 6: /* Bluetooth packet */
        switch (message_type) {
        case 13: /* Pair request */
            if (bluetooth_connected_host == 0) {
                /* Connected, turn to bluetooth */
                bluetooth_connected_host = 12;
                driver_enable_bluetooth();
                layer_off(BLUETOOTH_LAYER);
            }
            break;
        case 133: /* AckDeleteHost */
            /* Update the hostlist information when a saved host is deleted */
            anne_pro_bluetooth_hostlist_query();
            break;
        case 134: /* AckHostListQuery */
            if (data_len == 3) {
                if (bluetooth_connected_host == 0 && packet_data[1] != 0) {
                    /* Connected, turn to bluetooth */
                    driver_enable_bluetooth();
                } else if (bluetooth_connected_host != 0 && packet_data[1] == 0) {
                    /* Disconnected, turn off bluetooth */
                    driver_enable_last();
                }

                /* Save the hostlist query information */
                bluetooth_saved_hosts = packet_data[0];
                bluetooth_connected_host = packet_data[1];
                bluetooth_legacy = (packet_data[2] != 0);

                /* Update lighting if the bluetooth layer is active */
                if (bluetooth_layer_enabled) {
                    anne_pro_bluetooth_lighting_update();
                }
            }
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
    bluetooth_enabled = true;
}

/* Turn off Bluetooth */
void anne_pro_bluetooth_off(void) {
    /* When there is a connection disable it first, otherwise switching drivers
       will reactivate the Bluetooth controller */
    if (bluetooth_connected_host != 0) {
        /* Disconnected, turn off bluetooth */
        bluetooth_connected_host = 0;
        driver_enable_last();

        if (bluetooth_layer_enabled) {
            anne_pro_bluetooth_lighting_update();
        }
    }

    /* Disable the Bluetooth controller */
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 3, "\x06\x01\x02");
    bluetooth_enabled = false;
}

/* Query if Bluetooth is enabled */
bool anne_pro_bluetooth_enabled(void) {
    return bluetooth_enabled;
}

/* Start broadcasting on Bluetooth */
void anne_pro_bluetooth_broadcast(void) {
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 3, "\x06\x01\x07");
}

/* Turn Bluetooth legacy mode on or off */
void anne_pro_bluetooth_legacy(bool enable) {
    uint8_t buf[] = {6, 2, 12, enable ? 1 : 0};
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 4, buf);
    bluetooth_legacy = enable;
}

/* Toggle Bluetooth legacy mode */
void anne_pro_bluetooth_legacy_toggle(void) {
    anne_pro_bluetooth_legacy(!bluetooth_legacy);
}

/* Connect to a saved host */
void anne_pro_bluetooth_host_connect(uint8_t host) {
    uint8_t buf[] = {6, 2, 4, host};
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 4, buf);
}

/* Save the current host into a slot */
void anne_pro_bluetooth_host_save(uint8_t host) {
    uint8_t buf[] = {6, 2, 3, host};
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 4, buf);
}

/* Delete the host from a slot */
void anne_pro_bluetooth_host_delete(uint8_t host) {
    uint8_t buf[] = {6, 2, 5, host};
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 4, buf);
}

/* Query the hostlist of the Bluetooth controller */
void anne_pro_bluetooth_hostlist_query(void) {
    uart_tx_ringbuf_write(&bluetooth_uart_ringbuf, 3, "\x06\x01\x06");
}

/* Update the lighting effect for the Bluetooth layer */
void anne_pro_bluetooth_lighting_update(void) {
    /* Status of host 1 */
    uint8_t r1 = (bluetooth_connected_host != 1) ? 255 : 0;
    uint8_t g1 = (bluetooth_connected_host == 1 || bluetooth_saved_hosts & (1 << 0)) ? 255 : 0;
    /* Status of host 2 */
    uint8_t r2 = (bluetooth_connected_host != 2) ? 255 : 0;
    uint8_t g2 = (bluetooth_connected_host == 2 || bluetooth_saved_hosts & (1 << 1)) ? 255 : 0;
    /* Status of host 3 */
    uint8_t r3 = (bluetooth_connected_host != 3) ? 255 : 0;
    uint8_t g3 = (bluetooth_connected_host == 3 || bluetooth_saved_hosts & (1 << 2)) ? 255 : 0;
    /* Status of host 4 */
    uint8_t r4 = (bluetooth_connected_host != 4) ? 255 : 0;
    uint8_t g4 = (bluetooth_connected_host == 4 || bluetooth_saved_hosts & (1 << 3)) ? 255 : 0;
    /* Legacy mode? */
    uint8_t leg = (bluetooth_legacy) ? 255 : 0;
    /* Bluetooth driver selected? */
    bool connected = (bluetooth_connected_host != 0);
    bool drvr = (host_get_driver() == &anne_pro_bluetooth_driver);

    /* Payload for the lighting effect */
    uint8_t keybuf[] = {
        0, drvr ? 0 : 255, connected ? 255 : 0, drvr ? 255 : 0, 1, /* ESC-key */
        1, r1, g1, 0, 1, /* 1-key */
        2, r2, g2, 0, 1, /* 2-key */
        3, r3, g3, 0, 1, /* 3-key */
        4, r4, g4, 0, 1, /* 4-key */
        10, leg, 255, 0, 1, /* 0-key (legacy) */
        11, 255, 0, 0, 1, /* '-'-key (off) */
        12, 0, 255, 0, 2, /* '='-key (on) */
    };

    anne_pro_lighting_set_keys(8, keybuf);
}

/*
    Anne Pro Bluetooth HID driver for QMK
 */

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
