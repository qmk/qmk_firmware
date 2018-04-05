/*
 * Copyright (c) 2018 Jonathan A. Kollasch
 *           (c) 2018 Charlie Waters
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

#include "vortex.h"
#include "quantum.h"

#define BOOTLOADER_MAGIC 0x55aafaf5U

void bootloader_jump(void) {
    // SBVT registers are not reset on reset
    // SBVT1 is read by pok3r bootloader to stop booting
    FMC->SBVT[1] = BOOTLOADER_MAGIC;
    NVIC_SystemReset();
}

void matrix_init_kb(void) {
    matrix_init_user();
}

void matrix_scan_kb(void) {
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

//    printf("Code: %d %d\n", keycode, record->event.pressed);

    switch (keycode) {
        case EX_DUMP:
            if (record->event.pressed) {
                printf(">> Dump SPI Flash\n");
                spi_dump();
                printf(">> End Dump\n");
            }
            return false;
        case EX_RESET:
            if (record->event.pressed) {
                printf("Reset to Bootloader\n");
                bootloader_jump();
            }
    }
    return true;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    printf("Raw HID Data\n");
    if (length == RAW_EPSIZE) {
        printf("%02x%02x%02x%02x %02x%02x%02x%02x\n", data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
        printf("%02x%02x%02x%02x %02x%02x%02x%02x\n", data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15]);
        printf("%02x%02x%02x%02x %02x%02x%02x%02x\n", data[16],data[17],data[18],data[19],data[20],data[21],data[22],data[23]);
        printf("%02x%02x%02x%02x %02x%02x%02x%02x\n", data[24],data[25],data[26],data[27],data[28],data[29],data[30],data[31]);
    } else {
        printf("Bad data\n");
    }
}

void led_set_kb(uint8_t usb_led) {
    printf("Set LED: %02x\n", usb_led);
//    if ((usb_led >> USB_LED_CAPS_LOCK) & 1) {
//        palClearLine(LINE_LED65);
//    } else {
//        palSetLine(LINE_LED65);
//    }
    led_set_user(usb_led);
}
