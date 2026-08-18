// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "uart.h"
#include "ch.h"
#include "hal.h"
#include "host.h"
#include "host_driver.h"
#include "report.h"
#include <string.h>
#include "smart_ble.h"

static uint8_t sc_ble_leds(void) {
    return 0; // TODO: Get LED status  BLE
}

static void sc_ble_mouse(report_mouse_t *report) {
    static uint8_t last_report[sizeof(report_mouse_t)] = {0};

    if (!has_mouse_report_changed((report_mouse_t *)last_report, report)) return;
    memcpy(last_report, report, sizeof(report_mouse_t));
    uart_write(0x55);
    uart_write(sizeof(report_mouse_t));
    uart_transmit(last_report, sizeof(report_mouse_t));
}

static void sc_ble_extra(report_extra_t *report) {
    uart_write(0x55);
    uart_write(sizeof(report_extra_t));
    uart_transmit((uint8_t *)report, sizeof(report_extra_t));
}

static void sc_ble_keyboard(report_keyboard_t *report) {
    uart_write(0x55);
    uart_write(0x09);
    uart_write(0x01);
    uart_transmit((uint8_t *)report, KEYBOARD_REPORT_SIZE);
}

static void sc_send_nkro(report_nkro_t *report) {
    uart_write(0x55);
    uart_write(0x12);
    uart_transmit((uint8_t *)report, 0x12);
}

static host_driver_t *last_host_driver = NULL;
static host_driver_t  sc_ble_driver    = {sc_ble_leds, sc_ble_keyboard, sc_send_nkro, sc_ble_mouse, sc_ble_extra};

void smart_ble_startup(void) {
    if (host_get_driver() == &sc_ble_driver) {
        return;
    }
    clear_keyboard();
    last_host_driver = host_get_driver();
    host_set_driver(&sc_ble_driver);
}

void smart_ble_disconnect(void) {
    if (host_get_driver() != &sc_ble_driver) {
        return;
    }
    clear_keyboard();
    host_set_driver(last_host_driver);
}

void sc_ble_battary(uint8_t batt_level) {
    uart_write(0x55);
    uart_write(0x02);
    uart_write(0x09);
    uart_write(batt_level);
}

void wireless_start(uint32_t mode) {
    uint8_t ble_command[24];
    smart_ble_startup();
    if (mode < 1 || mode > 4) {
        mode = 1;
    }
    ble_command[0] = 0x55;
    ble_command[1] = 20;
    ble_command[2] = 0;
    ble_command[3] = mode;
    strcpy((char *restrict)(ble_command + 4), PRODUCT);
    ble_command[strlen(PRODUCT) + 4] = '-';
    ble_command[strlen(PRODUCT) + 5] = '0' + mode;
    ble_command[strlen(PRODUCT) + 6] = 0;
    uart_transmit(ble_command, sizeof(ble_command));
}

void wireless_stop(void) {
    smart_ble_disconnect();
    uart_write(0x55);
    uart_write(0x02);
    uart_write(0x00);
    uart_write(0x00);
}
