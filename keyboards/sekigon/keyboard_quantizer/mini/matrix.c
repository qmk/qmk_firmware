// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "print.h"
#include "tusb.h"
#include "pio_usb_ll.h"

static uint8_t          kbd_addr;
static uint8_t          kbd_instance;
static int32_t          led_count = -1;
static uint8_t          hid_report_buffer[64];
static volatile uint8_t hid_report_size;
static uint8_t          hid_instance;
static bool             hid_disconnect_flag;
static uint8_t          pre_keyreport[8];
#define LED_BLINK_TIME_MS 50
#define KQ_PIN_LED 7
#define MATRIX_MODIFIER_ROW 21

extern void busy_wait_us(uint64_t delay_us);
static bool send_led_report(uint8_t* leds);

void matrix_init_custom(void) {
    // Configure LED pin
    setPinOutput(KQ_PIN_LED);
    writePinHigh(KQ_PIN_LED);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // If keyboard is disconnected, clear matrix
    if (hid_disconnect_flag) {
        for (uint8_t rowIdx = 0; rowIdx < MATRIX_ROWS; rowIdx++) {
            if (current_matrix[rowIdx] != 0) {
                matrix_has_changed     = true;
                current_matrix[rowIdx] = 0;
            }
        }

        hid_disconnect_flag = false;

        return matrix_has_changed;
    }

    // If keyboard report is received, apply it to matrix
    if (hid_report_size > 0) {
        hid_report_size = 0;
        dprintf("%02x %02x %02x %02x %02x %02x %02x %02x\n", hid_report_buffer[0], hid_report_buffer[1], hid_report_buffer[2], hid_report_buffer[3], hid_report_buffer[4], hid_report_buffer[5], hid_report_buffer[6], hid_report_buffer[7]);
        if (memcmp(pre_keyreport, hid_report_buffer, 8) == 0) {
            // no change
            matrix_has_changed = false;

            return matrix_has_changed;
        } else {
            matrix_has_changed = true;
            memcpy(pre_keyreport, hid_report_buffer, 8);
        }

        // clear all bit
        for (uint8_t rowIdx = 0; rowIdx < MATRIX_ROWS; rowIdx++) {
            current_matrix[rowIdx] = 0;
        }

        // set bits
        for (uint8_t keyIdx = 0; keyIdx < 6; keyIdx++) {
            uint8_t key    = hid_report_buffer[keyIdx + 2];
            uint8_t rowIdx = key / (sizeof(uint8_t) * 8);
            uint8_t colIdx = key - rowIdx * (sizeof(uint8_t) * 8);
            current_matrix[rowIdx] |= (1 << colIdx);
        }

        // modifier bits
        current_matrix[MATRIX_MODIFIER_ROW] = hid_report_buffer[0];
        return matrix_has_changed;
    } else {
        return false;
    }

    return matrix_has_changed;
}

void housekeeping_task_kb(void) {
    // Control keyboard indicator LED
    static uint8_t keyboard_led;
    if (keyboard_led != host_keyboard_leds()) {
        uint8_t led_backup = keyboard_led;
        keyboard_led       = host_keyboard_leds();
        if (!send_led_report(&keyboard_led)) {
            keyboard_led = led_backup;
        }
    }

    // Blink LED when USB reports are received
    if (led_count >= 0) {
        if (timer_elapsed(led_count) < LED_BLINK_TIME_MS) {
            writePinLow(KQ_PIN_LED);
        } else if (timer_elapsed(led_count) < 2 * LED_BLINK_TIME_MS) {
            writePinHigh(KQ_PIN_LED);
        } else {
            led_count = -1;
        }
    }
}

static bool send_led_report(uint8_t* leds) {
    if (kbd_addr != 0) {
        return tuh_hid_set_report(kbd_addr, kbd_instance, 0, HID_REPORT_TYPE_OUTPUT, leds, sizeof(*leds));
    }

    return false;
}

void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len) {
    dprintf("HID mounted:%d:%d\n", dev_addr, instance);

    if (led_count < 0) {
        led_count = timer_read();
    }

    for (int instance = 0; instance < tuh_hid_instance_count(dev_addr); instance++) {
        tuh_hid_receive_report(dev_addr, instance);

        uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);
        if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD) {
            kbd_addr     = dev_addr;
            kbd_instance = instance;
        }
    }
}

void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {
    dprintf("HID unmounted:%d:%d\n", dev_addr, instance);
    memset(pre_keyreport, 0, sizeof(pre_keyreport));
    hid_disconnect_flag = true;
    kbd_addr            = 0;
    kbd_instance        = 0;
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
    dprintf("Report received\n");
    if (led_count < 0) {
        led_count = timer_read();
    }

    if (len > 0 && instance == kbd_instance) {
        int cnt = 0;
        while (hid_report_size > 0 && cnt++ < 50000) {
            busy_wait_us(1);
            continue;
        }

        hid_instance = instance;
        memcpy(hid_report_buffer, report, len);
        __DSB();
        // hid_report_size is used as trigger of report parser
        hid_report_size = len;
    }

    tuh_hid_receive_report(dev_addr, instance);
}
