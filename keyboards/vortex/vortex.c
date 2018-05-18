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

uint8_t current_layout = 0;
extern const uint8_t keymap_layouts[NUM_LAYOUTS][MATRIX_ROWS][MATRIX_COLS];
extern const char *layout_names;

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
    printf("Bootloader Jump\n");
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

// From http://mdfs.net/Info/Comp/Comms/CRC16.htm
// CRC-CCITT
#define CCITT_POLY 0x1021
static uint16_t crc16(const uint8_t *ptr, uint32_t size) {
    uint32_t crc = 0;
    for(uint32_t i = 0; i < size; ++i){
        crc ^= (uint16_t)(ptr[i] << 8);
        for(int j = 0; j < 8; j++){
            crc = crc << 1;
            if(crc & 0x10000)
                crc = (crc ^ CCITT_POLY) & 0xFFFF;
        }
    }
    return (uint16_t)(crc & 0xFFFF);
}

void OVERRIDE raw_hid_receive(uint8_t *data_in, uint8_t length) {
//    printf("Command Packet Receive\n");
    if (length == PKT_LEN) {
        // parse command
        const uint8_t cmd = data_in[0];
        const uint8_t subcmd = data_in[1];
        const uint16_t crc0 = from_leu16(data_in + 2);
        to_leu16(data_in + 2, 0);
        const uint16_t crc = crc16(data_in, PKT_LEN);
        if(crc != crc0){
            printf("Corrupt Command CRC\n");
            return;
        }
        uint8_t *data_out = packet_buf + 4;

        // clear response
        memset(packet_buf, 0, PKT_LEN);

        // handle command
        switch (cmd) {

            // vortex commands for pok3r or cykb
            // /////////////////////////////////

            case CMD_RESET:
                switch (subcmd) {
                    case SUB_RESET_BL:
                        printf("Reset Bootloader\n");
                        reset_keyboard();
                        return;
                    case SUB_RESET_FW:
                        printf("Reset Firmware\n");
                        //firmware_reset(RESET_FW_MAGIC);
                        return;
                }

#if defined(UPDATE_PROTO_POK3R)
            case CMD_FLASH:
                switch (subcmd) {
                    case SUB_READ: {
                        uint32_t addr = from_leu32(data_in + 4);
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
                packet_buf[1] = subcmd;
                switch (subcmd) {
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
                        uint32_t addr = from_leu32(data_in + 4);
                        printf("Read Addr %04x\n", addr);
                        if (addr < FLASH_SIZE) {
                            memcpy(packet_buf + 4, (const uint8_t *)addr, MIN(FLASH_SIZE - addr, 60));
                        }
                        break;
                    }
                    default: {
                        if(subcmd >= SUB_READ_VER1 && subcmd < 0x30){
                            uint32_t addr = 0x3000 + ((subcmd - 0x20) * 60);
                            printf("Read Version %04x\n", addr);
                            memcpy(packet_buf + 4, (const uint8_t *)addr, 60);
                        }
                        break;
                    }
                }
                break;
#endif

            // new qmk commands
            // /////////////////////////////////

            case CMD_CTRL: {
                switch (subcmd) {
                    case SUB_CT_INFO: {
                        to_leu16(data_out, PRODUCT_ID);
                        to_leu16(data_out + 2, DEVICE_VER);
                        const char *str = "qmk_pok3r";
                        memcpy(data_out + 4, str, strlen(str));
                        printf("Info %s\n", str);
                        break;
                    }
                    case SUB_CT_LAYOUT: {
                        const uint8_t ln = data_in[4];
                        printf("Set Layout %d\n", ln);
                        current_layout = ln;
                        break;
                    }
                }
                break;
            }

            case CMD_EEPROM: {
                uint32_t addr = from_leu32(data_in + 4);
                switch (subcmd) {
                    case SUB_EE_INFO: {
                        spi_rdid(data_out);
                        printf("Info EEPROM %02x %02x %02x\n", data_out[1], data_out[2], data_out[3]);
                        break;
                    }
                    case SUB_EE_READ: {
                        rtcnt_t start = chSysGetRealtimeCounterX();
                        spi_read(addr, 60, data_out);
                        rtcnt_t end = chSysGetRealtimeCounterX();
                        printf("Read EEPROM %04x, %d us\n", addr, RTC2US(HT32_HCLK_FREQUENCY, end - start));
                        break;
                    }
                    case SUB_EE_WRITE:
                        printf("Write EEPROM %04x\n", addr);
                        spi_write(addr, 56, data_in + 8);
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
                switch (subcmd) {
                    case SUB_KM_INFO: {
                        printf("Info Keymap\n");
                        data_out[0] = MAX_LAYERS;         // max layers
                        data_out[1] = MATRIX_ROWS;        // matrix rows
                        data_out[2] = MATRIX_COLS;        // matrix cols
                        data_out[3] = sizeof(uint16_t);   // keycode size
                        data_out[4] = NUM_LAYOUTS;        // num layouts
                        data_out[5] = current_layout;     // current layout
                        break;
                    }
                    case SUB_KM_READ: {
                        const uint32_t arg = from_leu32(data_in + 4);
                        const uint8_t page = (arg & 0xF0000) >> 16;
                        const uint32_t offset = arg & 0xFFFF;
                        printf("Read Keymap %x %04x\n", page, offset);
                        switch (page) {
                            case KM_PAGE_MATRIX:
                                // read matrix layers
                                if (offset < total_size) {
                                    memcpy(data_out, ((const uint8_t *)keymaps) + offset, MIN(total_size - offset, 60));
                                }
                                break;
                            case KM_PAGE_LAYOUT:
                                // read layouts
                                if (offset < keymap_size) {
                                    memcpy(data_out, ((const uint8_t *)keymap_layouts) + offset, MIN(keymap_size - offset, 60));
                                }
                                break;
                            case KM_PAGE_STRS: {
                                // read layout strings
                                const uint16_t strsize = strlen(layout_names);
                                if (offset < strsize) {
                                    memcpy(data_out, ((const uint8_t *)layout_names) + offset, MIN(strsize - offset, 60));
                                }
                                break;
                            }
                        }
                        break;
                    }
                    case SUB_KM_WRITE: {
                        uint16_t offset = from_leu16(data_in + 4);
                        uint16_t len = MIN(from_leu16(data_in + 6), 56);
                        printf("Write Keymap %04x %d\n", offset, len);
                        if (offset < total_size) {
                            memcpy(((uint8_t *)keymaps) + offset, data_in + 8, MIN(total_size - offset, len));
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
                printf("Bad command %x\n", cmd);
                packet_buf[0] = 0xff;
                packet_buf[1] = 0xaa;
                break;
        }

        if(cmd & 0x80){
            to_leu16(packet_buf, crc);
            to_leu16(packet_buf + 2, 0);
            const uint16_t crc1 = crc16(packet_buf, PKT_LEN);
            to_leu16(packet_buf + 2, crc1);
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
