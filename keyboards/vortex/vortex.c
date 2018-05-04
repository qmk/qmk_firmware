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
#include "proto.h"
#include "quantum.h"
#include "raw_hid.h"
#include "debug.h"
#include "gd25q_flash.h"

#include <stdint.h>
#include <string.h>

#define MIN(A, B) (A < B ? A : B)

#define RESET_FW_MAGIC  0x55aafaf0U
#define RESET_BL_MAGIC  0x55aafaf5U

#define EE_CONFIG_ADDR      (GD25Q40_SECTOR_BYTES * 0)  // sector 0
#define EE_CONFIG_SIG_LEN   4
#define EE_CONFIG_SIG       "CONF"
#define EE_KEYMAP_ADDR      (GD25Q40_SECTOR_BYTES * 1)  // sector 1
#define EE_KEYMAP_SIG_LEN   4
#define EE_KEYMAP_SIG       "KEYM"

#define PKT_LEN RAW_EPSIZE
static uint8_t packet_buf[PKT_LEN];

extern const uint16_t keymap_layouts[NUM_LAYOUTS][MATRIX_ROWS][MATRIX_COLS];
extern const char *layout_names[NUM_LAYOUTS];

const uint8_t firmware_id[] __attribute__ ((section (".id.firmware"))) = {
    PRODUCT_ID & 0xFF, (PRODUCT_ID >> 8) & 0xFF,
    'q', 'm', 'k', '_', 'p', 'o', 'k', '3', 'r', 0
};

// Compatibility commands
enum pok3r_cmd {
#if defined(UPDATE_PROTO_POK3R)
    CMD_RESET       = 4,    //!< Reset command.
    SUB_RESET_BL    = 1,    //!< Reset to bootloader.
    SUB_RESET_FW    = 2,    //!< Reset firmware.
#elif defined(UPDATE_PROTO_CYKB)
    CMD_RESET       = 0x11, //!< Reset command.
    SUB_RESET_BL    = 0,    //!< Reset to bootloader.
    SUB_RESET_FW    = 1,    //!< Reset firmware.
#endif

#if defined(UPDATE_PROTO_POK3R)
    CMD_FLASH       = 1,    //!< Internal flash command.
    SUB_WRITE       = 1,    //!< Write 52 bytes to internal flash.
    SUB_READ        = 2,    //!< Read 64 bytes from internal flash.
#elif defined(UPDATE_PROTO_CYKB)
    CMD_READ        = 0x12, //!< Read internal flash command.
    SUB_READ_400    = 0,
    SUB_READ_3C00   = 1,
    SUB_READ_MODE   = 2,    //!< Get firmware mode. 0 is bootloader, 1 is firmware.
    SUB_READ_VER1   = 0x20, //!< Read version string.
    SUB_READ_VER2   = 0x22, //!< Read version data.
    SUB_READ_ADDR   = 0xff, //!< Patched command, read arbitrary address.
#endif
};

static uint16_t from_leu16(const uint8_t *bytes) {
    return (bytes[0] | (bytes[1] << 8));
}

static uint32_t from_leu32(const uint8_t *bytes) {
    return (bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24));
}

static void to_leu16(uint8_t *bytes, uint16_t num) {
    bytes[0] = num & 0xFF;
    bytes[1] = (num >> 8) & 0xFF;
}

static void to_leu32(uint8_t *bytes, uint32_t num) {
    bytes[0] = num & 0xFF;
    bytes[1] = (num >> 8) & 0xFF;
    bytes[2] = (num >> 16) & 0xFF;
    bytes[3] = (num >> 24) & 0xFF;
}

static void firmware_reset(uint32_t key) {
    wait_us(10000); // 10 ms
    chSysDisable(); // mask all interrupts
    usbDisconnectBus(&USB_DRIVER); // disconnect usb
    // SBVT registers are not reset on reset
    // SBVT1 is read by pok3r bootloader to stop in bootloader
    FMC->SBVT[1] = key;
    wait_us(50000); // 50 ms
    NVIC_SystemReset();
}

void OVERRIDE bootloader_jump(void) {
    printf("Reset to Bootloader\n");
    firmware_reset(RESET_BL_MAGIC);
}

void OVERRIDE matrix_init_kb(void) {
    // Check eeprom keymap signature
    uint8_t sig[EE_KEYMAP_SIG_LEN];
    spi_read(EE_KEYMAP_ADDR, EE_KEYMAP_SIG_LEN, sig);
    if(memcmp(sig, EE_KEYMAP_SIG, EE_KEYMAP_SIG_LEN) == 0){
        // Load keymaps from eeprom
        const uint32_t keymap_size = MAX_LAYERS * MATRIX_ROWS * MATRIX_COLS * sizeof(uint16_t);
        spi_read(EE_KEYMAP_ADDR + EE_KEYMAP_SIG_LEN, keymap_size, (uint8_t *)keymaps);
    }

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
//                spi_dump();
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
        // clear response
        memset(packet_buf, 0, PKT_LEN);

        // handle command
        switch (data[0]) {
            case CMD_RESET:
                switch (data[1]) {
                    case SUB_RESET_BL:
                        reset_keyboard();
                        return;
                    case SUB_RESET_FW:
                        //firmware_reset();
                        return;
                }

#if defined(UPDATE_PROTO_POK3R)
            case CMD_FLASH:
                switch (data[1]) {
                    case SUB_READ: {
                        uint32_t addr = from_leu32(data + 4);
                        printf("Read Flash %04x\n", addr);
                        if (addr < FLASH_SIZE) {
                            memcpy(packet_buf, (const uint8_t *)addr, MIN(FLASH_SIZE - addr, 64));
                        }
                        break;
                    }
                }
                break;
#endif
#if defined(UPDATE_PROTO_CYKB)
            case CMD_READ:
                packet_buf[0] = CMD_READ;
                packet_buf[1] = data[1];
                switch (data[1]) {
                    case SUB_READ_400: {
                        uint32_t addr = 0x400;
                        printf("Read 0x400\n");
                        memcpy(packet_buf + 4, (const uint8_t *)addr, 60);
                        break;
                    }
                    case SUB_READ_3C00: {
                        uint32_t addr = 0x3c00;
                        printf("Read 0x3c00\n");
                        memcpy(packet_buf + 4, (const uint8_t *)addr, 4);
                        break;
                    }
                    case SUB_READ_MODE: {
                        printf("Read Mode\n");
                        packet_buf[4] = 1;
                        break;
                    }
                    case SUB_READ_ADDR: {
                        uint32_t addr = from_leu32(data + 4);
                        printf("Read Addr %04x\n", addr);
                        if (addr < FLASH_SIZE) {
                            memcpy(packet_buf + 4, (const uint8_t *)addr, MIN(FLASH_SIZE - addr, 60));
                        }
                        break;
                    }
                    default: {
                        if(data[1] >= SUB_READ_VER1 && data[1] < 0x30){
                            uint32_t addr = 0x3000 + ((data[1] - 0x20) * 60);
                            printf("Read Version %04x\n", addr);
                            memcpy(packet_buf + 4, (const uint8_t *)addr, 60);
                        }
                        break;
                    }
                }
                break;
#endif

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
                    case SUB_EE_INFO: {
                        spi_rdid(packet_buf);
                        printf("Info EEPROM %02x %02x %02x\n", packet_buf[1], packet_buf[2], packet_buf[3]);
                        break;
                    }
                    case SUB_EE_READ: {
                        rtcnt_t start = chSysGetRealtimeCounterX();
                        spi_read(addr, 64, packet_buf);
                        rtcnt_t end = chSysGetRealtimeCounterX();
                        printf("Read EEPROM %04x, %d us\n", addr, RTC2US(HT32_HCLK_FREQUENCY, end - start));
                        break;
                    }
                    case SUB_EE_WRITE:
                        printf("Write EEPROM %04x\n", addr);
                        spi_write(addr, 56, data + 8);
                        break;
                    case SUB_EE_ERASE:
                        printf("Erase EEPROM %04x\n", addr);
                        spi_erase(addr);
                        break;
                }
                break;
            }

            case CMD_KEYMAP: {
                const uint32_t keymap_size = MAX_LAYERS * MATRIX_ROWS * MATRIX_COLS;
                const uint32_t total_size = keymap_size * sizeof(uint16_t);
                switch (data[1]) {
                    case SUB_KM_INFO: {
                        printf("Info Keymap\n");
                        packet_buf[0] = MAX_LAYERS;         // max layers
                        packet_buf[1] = MATRIX_ROWS;        // matrix rows
                        packet_buf[2] = MATRIX_COLS;        // matrix cols
                        packet_buf[3] = sizeof(uint16_t);   // keycode size
                        packet_buf[4] = NUM_LAYOUTS;        // num layouts
                        packet_buf[5] = 0;                  // current layout
                        break;
                    }
                    case SUB_KM_READ: {
                        const uint32_t arg = from_leu32(data + 4);
                        const uint8_t page = (arg & 0xF0000) >> 16;
                        const uint32_t offset = arg & 0xFFFF;
                        printf("Read Keymap %x %04x\n", page, offset);
                        switch (page) {
                            case 0:
                                // read matrix layers
                                if (offset < total_size) {
                                    memcpy(packet_buf, ((const uint8_t *)keymaps) + offset, MIN(total_size - offset, 64));
                                }
                                break;
                            case 1:
                                // read layouts
                                if (offset < keymap_size) {
                                    memcpy(packet_buf, ((const uint8_t *)keymap_layouts) + offset, MIN(keymap_size - offset, 64));
                                }
                                break;
                        }
                        break;
                    }
                    case SUB_KM_WRITE: {
                        uint16_t offset = from_leu16(data + 4);
                        uint16_t len = MIN(from_leu16(data + 6), 56);
                        printf("Write Keymap %04x %d\n", offset, len);
                        if (offset < total_size) {
                            memcpy(((uint8_t *)keymaps) + offset, data + 8, MIN(total_size - offset, len));
                        }
                        break;
                    }
                    case SUB_KM_COMMIT: {
                        printf("Commit Keymap\n");
                        spi_erase(EE_KEYMAP_ADDR);
                        spi_wait_wip();
                        spi_write(EE_KEYMAP_ADDR, EE_KEYMAP_SIG_LEN, (const uint8_t *)EE_KEYMAP_SIG);
                        spi_wait_wip();
                        spi_write(EE_KEYMAP_ADDR + EE_KEYMAP_SIG_LEN, total_size, (const uint8_t *)keymaps);
                    }
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
