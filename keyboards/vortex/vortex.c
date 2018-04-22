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
#include "debug.h"

#include <stdint.h>
#include <string.h>

#define RESET_FW_MAGIC 0x55aafaf0U
#define RESET_BL_MAGIC 0x55aafaf5U

#define PKT_LEN RAW_EPSIZE
static uint8_t packet_buf[PKT_LEN];

extern bool bootloader_reset;

const uint8_t firmware_id[] __attribute__ ((section (".id.firmware"))) = {
    PRODUCT_ID & 0xFF, (PRODUCT_ID >> 8) & 0xFF,
    'q', 'm', 'k', '_', 'p', 'o', 'k', '3', 'r', 0
};

enum pok3r_rgb_cmd {
#if UPDATE_PROTO_VER == 1
    CMD_RESET       = 4,    //!< Reset command.
#else
    CMD_RESET       = 0x11, //!< Reset command.
#endif
    SUB_RESET_BL    = 0,    //!< Reset to bootloader.
    SUB_RESET_FW    = 1,    //!< Reset to firmware.

#if UPDATE_PROTO_VER == 1
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

    // New QMK commands
    CMD_INFO        = 0x81,
    CMD_EEPROM      = 0x82,
    SUB_EE_READ     = 0x01,
    SUB_EE_WRITE    = 0x02,
};

static void to_leu16(uint8_t *bytes, uint16_t num) {
    bytes[0] = num & 0xFF;
    bytes[1] = (num >> 8) & 0xFF;
}

static uint32_t from_leu32(const uint8_t *bytes) {
    return (bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24));
}

void OVERRIDE bootloader_jump(void) {
    printf("Reset to Bootloader\n");
    wait_us(10000); // 10 ms
    chSysDisable(); // mask all interrupts
    usbDisconnectBus(&USB_DRIVER); // disconnect usb
    // SBVT registers are not reset on reset
    // SBVT1 is read by pok3r bootloader to stop in bootloader
    FMC->SBVT[1] = RESET_BL_MAGIC;
    wait_us(50000); // 50 ms
    NVIC_SystemReset();
}

void firmware_reset(void) {
    printf("Reset Firmware\n");
    FMC->SBVT[1] = RESET_FW_MAGIC;
    NVIC_SystemReset();
}

void OVERRIDE matrix_init_kb(void) {
    matrix_init_user();
}

void OVERRIDE matrix_scan_kb(void) {
//    debug_enable = true;
//    debug_matrix = true;

    matrix_scan_user();
}

bool OVERRIDE process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EX_DUMP:
            if (record->event.pressed) {
                printf(">> Dump SPI Flash\n");
                spi_dump();
                printf(">> End Dump\n");
            }
            return false;
    }

//    printf("Code: %d %d\n", keycode, record->event.pressed);
//    return false;

    return process_record_user(keycode, record);
}

void OVERRIDE raw_hid_receive(uint8_t *data, uint8_t length) {
//    printf("Command Packet Receive\n");
    if (length == PKT_LEN) {
        memset(packet_buf, 0, PKT_LEN);
        // handle command
        switch (data[0]) {
            case CMD_RESET:
                switch (data[1]) {
                    case SUB_RESET_BL:
//                        bootloader_jump();
//                        reset_keyboard();
                        bootloader_reset = true;
                        return;
                    case SUB_RESET_FW:
                        firmware_reset();
                        return;
                }

            case CMD_READ:
#if UPDATE_PROTO_VER != 1
                packet_buf[0] = CMD_READ;
                packet_buf[1] = data[1];
#endif
                switch (data[1]) {
#if UPDATE_PROTO_VER == 1
                    case SUB_READ_ADDR: {
                        uint32_t addr = data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 24);
                        printf("Read Flash %04x\n", addr);
                        if (addr + 64 < FLASH_SIZE) {
                            memcpy(packet_buf, (const uint8_t *)addr, 64);
                        }
                        break;
                    }
#endif
                }
                break;

            case CMD_INFO: {
                to_leu16(packet_buf + 0, PRODUCT_ID);
                to_leu16(packet_buf + 2, DEVICE_VER);
                const char *str = "qmk_pok3r";
                memcpy(packet_buf + 4, str, strlen(str));
                printf("Info: %s\n", str);
                break;
            }

            case CMD_EEPROM: {
                uint32_t addr = from_leu32(data + 4);
                switch (data[1]) {
                    case SUB_EE_READ:
                        printf("Read EEPROM %04x\n", addr);
                        spi_read(addr, 64, packet_buf);
                        break;
                    case SUB_EE_WRITE:
                        printf("Write EEPROM %04x\n", addr);
                        //spi_write(addr, 56, data + 8);
                        break;
                }
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
    static uint8_t prev = 0;
    if (usb_led != prev) {
        printf("Set LED: %02x\n", usb_led);
    }
    prev = usb_led;
    if ((usb_led >> USB_LED_CAPS_LOCK) & 1) {
//        palClearLine(LINE_LED65);
    } else {
//        palSetLine(LINE_LED65);
    }
    led_set_user(usb_led);
}
