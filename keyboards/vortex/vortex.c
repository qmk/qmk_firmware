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
#include "raw_hid.h"

#include <stdint.h>
#include <string.h>

#define BOOTLOADER_MAGIC 0x55aafaf5U
#define PROTO_VER 1

#define PKT_LEN RAW_EPSIZE
static uint8_t packet_buf[PKT_LEN];

enum pok3r_rgb_cmd {
#if PROTO_VER
    CMD_RESET       = 4,    //!< Reset command.
#else
    CMD_RESET       = 0x11, //!< Reset command.
#endif
    SUB_RESET_BL    = 0,    //!< Reset to bootloader.
    SUB_RESET_FW    = 1,    //!< Reset to firmware.

#if PROTO_VER
    CMD_READ        = 1,    //!< Read command.
    SUB_READ_ADDR   = 2,    //!< Patched command, read arbitrary address.
#else
    CMD_READ        = 0x12, //!< Read command.
    SUB_READ_400    = 0,
    SUB_READ_3C00   = 1,
    SUB_READ_MODE   = 2,    //!< Get firmware mode. 0 is bootloader, 1 is firmware.
    SUB_READ_VER1   = 0x20, //!< Read version string.
    SUB_READ_VER2   = 0x22, //!< Read version data.
    SUB_READ_ADDR   = 0xff, //!< Patched command, read arbitrary address.
#endif

    CMD_INFO        = 0x81,
};

void OVERRIDE bootloader_jump(void) {
    printf("Reset to Bootloader\n");
    // SBVT registers are not reset on reset
    // SBVT1 is read by pok3r bootloader to stop booting
    FMC->SBVT[1] = BOOTLOADER_MAGIC;
    NVIC_SystemReset();
}

void firmware_reset(void) {
    printf("Reset Firmware\n");
    FMC->SBVT[1] = 0;
    NVIC_SystemReset();
}

void OVERRIDE matrix_init_kb(void) {
    matrix_init_user();
}

void OVERRIDE matrix_scan_kb(void) {
    matrix_scan_user();
}

bool OVERRIDE process_record_kb(uint16_t keycode, keyrecord_t *record) {
//    printf("Code: %d %d\n", keycode, record->event.pressed);
    if (!process_record_user(keycode, record)) {
        return false;
    }

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
                bootloader_jump(); // doesn't return
            }
            return false;
    }
    return true;
}

void OVERRIDE raw_hid_receive(uint8_t *data, uint8_t length) {
    printf("Command Packet Receive\n");
    if (length == PKT_LEN) {
        memset(packet_buf, 0, PKT_LEN);
        // handle command
        switch (data[0]) {
            case CMD_RESET:
                switch (data[1]) {
                    case SUB_RESET_BL:
                        bootloader_jump();
                        return;
                    case SUB_RESET_FW:
                        firmware_reset();
                        return;
                }

            case CMD_READ:
#if !PROTO_VER
                packet_buf[0] = CMD_READ;
                packet_buf[1] = data[1];
#endif
                switch (data[1]) {
#if PROTO_VER
                    case SUB_READ_ADDR: {
                        uint32_t addr = data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 24);
                        printf("Read Addr %04x\n", addr);
                        if (addr + 64 < FLASH_SIZE) {
                            memcpy(packet_buf, (const uint8_t *)addr, 64);
                        }
                        break;
                    }
#endif
                }
                break;

            case CMD_INFO: {
                packet_buf[0] = PRODUCT_ID & 0xFF;
                packet_buf[1] = PRODUCT_ID >> 8;
                packet_buf[2] = DEVICE_VER & 0xFF;
                packet_buf[3] = DEVICE_VER >> 8;
                const char *str = "qmk_pok3r";
                memcpy(packet_buf + 4, str, strlen(str));
                break;
            }

            default:
                // Error
                printf("Bad command %x\n", data[0]);
                packet_buf[0] = 0xff;
                packet_buf[1] = 0xaa;
                break;
        }
        // send response
        raw_hid_send(packet_buf, PKT_LEN);

    } else {
        printf("Bad raw data\n");
    }
}

void OVERRIDE led_set_kb(uint8_t usb_led) {
    printf("Set LED: %02x\n", usb_led);
//    if ((usb_led >> USB_LED_CAPS_LOCK) & 1) {
//        palClearLine(LINE_LED65);
//    } else {
//        palSetLine(LINE_LED65);
//    }
    led_set_user(usb_led);
}
