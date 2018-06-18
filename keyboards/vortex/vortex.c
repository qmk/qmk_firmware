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

#include "quantum.h"
#include "raw_hid.h"
#include "debug.h"
#include "version.h"

#include "vortex.h"
#include "proto.h"
#include "gd25q_flash.h"

#include <stdint.h>
#include <string.h>

#define MIN(A, B) (A < B ? A : B)

#define RESET_FW_MAGIC  0x55aafaf0U
#define RESET_BL_MAGIC  0x55aafaf5U

#define EE_CONFIG_SIG       "CONF"
#define EE_CONFIG_SIG_LEN   4
#define EE_KEYMAP_SIG       "KEYM"
#define EE_KEYMAP_SIG_LEN   4

#define PKT_LEN RAW_EPSIZE
static uint8_t packet_buf[PKT_LEN];

typedef void (*apiHandler)(const uint8_t *data_in, uint8_t *data_out);

// Default keymaps
extern const uint16_t keymaps_default[NUM_LAYOUTS][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t keymaps_default_size;

extern const uint8_t keymap_layouts[NUM_LAYOUTS][MATRIX_ROWS][MATRIX_COLS];
static const uint32_t keymap_size = MAX_LAYERS * MATRIX_ROWS * MATRIX_COLS * sizeof(uint16_t);
extern const char *layout_names;
uint8_t current_layout = 0;

const uint8_t firmware_id[] __attribute__ ((section (".id.firmware"))) = {
    PRODUCT_ID & 0xFF, (PRODUCT_ID >> 8) & 0xFF,
    'q', 'm', 'k', '_', 'p', 'o', 'k', '3', 'r', 0
};

void OVERRIDE bootloader_jump(void) {
    printf("Bootloader Jump\n");
    firmware_reset(RESET_BL_MAGIC);
}

static void keymap_load_default(void) {
        printf("Load Default Keymaps\n");
        memset(keymaps, 0, keymap_size);
        memcpy(keymaps, keymaps_default, keymaps_default_size);
}

static void keymap_load(void) {
    // Check eeprom keymap signature
    uint8_t sig[EE_KEYMAP_SIG_LEN];
    spi_read(EE_KEYMAP_ADDR, EE_KEYMAP_SIG_LEN, sig);
    if(memcmp(sig, EE_KEYMAP_SIG, EE_KEYMAP_SIG_LEN) == 0){
        printf("Load Keymaps from EEPROM\n");
        spi_read(EE_KEYMAP_ADDR + EE_KEYMAP_SIG_LEN, keymap_size, (uint8_t *)keymaps);
    } else {
        keymap_load_default();
    }
}

void OVERRIDE matrix_init_kb(void) {
    keymap_load();
    matrix_init_user();
}

void OVERRIDE matrix_scan_kb(void) {
//    debug_enable = true;
//    debug_matrix = true;

    matrix_scan_user();
}

bool OVERRIDE process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            break;
    }
//    printf("Code: %d %d\n", keycode, record->event.pressed);
//    return false;
    return process_record_user(keycode, record);
}

static void cmd_compat_reset(const uint8_t *data_in, uint8_t *data_out){
//    printf("compat reset\n");
    const uint8_t subcmd = data_in[1];
    switch (subcmd) {
        case SUB_RESET_BL:
            printf(">> Reset Bootloader\n");
            reset_keyboard();
            return;
        case SUB_RESET_FW:
            printf(">> Reset Firmware\n");
            firmware_reset(RESET_FW_MAGIC);
            return;
    }
}

#if defined(UPDATE_PROTO_POK3R)
static void cmd_pok3r_flash(const uint8_t *data_in, uint8_t *data_out){
//    printf("pok3r flash\n");
    const uint8_t subcmd = data_in[1];
    switch (subcmd) {
        case SUB_READ: {
            uint32_t addr = from_leu32(data_in + 4);
            printf(">> POK3R Read Flash %04x\n", addr);
            if (addr < FLASH_SIZE) {
                memcpy(data_out, (const uint8_t *)addr, MIN(FLASH_SIZE - addr, 64));
            }
            break;
        }
    }
}
#endif

#if defined(UPDATE_PROTO_CYKB)
static void cmd_cykb_read(const uint8_t *data_in, uint8_t *data_out){
//    printf("cykb read\n");
    const uint8_t subcmd = data_in[1];
    switch (subcmd) {
        case SUB_READ_400: {
            uint32_t addr = 0x400;
            printf(">> CYKB Read 0x400\n");
            memcpy(data_out, (const uint8_t *)addr, 60);
            break;
        }
        case SUB_READ_3C00: {
            uint32_t addr = 0x3c00;
            printf(">> CYKB Read 0x3c00\n");
            memcpy(data_out, (const uint8_t *)addr, 4);
            break;
        }
        case SUB_READ_MODE: {
            printf(">> CYKB Read Mode\n");
            data_out[0] = 1;
            break;
        }
        case SUB_READ_ADDR: {
            uint32_t addr = from_leu32(data_in + 4);
            printf(">> CYKB Read Addr %04x\n", addr);
            if (addr < FLASH_SIZE) {
                memcpy(data_out, (const uint8_t *)addr, MIN(FLASH_SIZE - addr, 60));
            }
            break;
        }
        default: {
            if(subcmd >= SUB_READ_VER1 && subcmd < 0x30){
                uint32_t addr = 0x3000 + ((subcmd - 0x20) * 60);
                printf(">> CYKB Read Version %04x\n", addr);
                memcpy(data_out, (const uint8_t *)addr, 60);
            }
            break;
        }
    }
}
#endif

static void cmd_qmk_ctrl(const uint8_t *data_in, uint8_t *data_out){
//    printf("qmk ctrl\n");
    const uint8_t subcmd = data_in[1];
    switch (subcmd) {
        case SUB_CT_INFO: {
            to_leu16(data_out, PRODUCT_ID);
            to_leu16(data_out + 2, DEVICE_VER);
            const char *str = "qmk_pok3r;" QMK_VERSION ";" QMK_BUILDDATE;
            memcpy(data_out + 4, str, MIN(strlen(str), 56));
            printf(">> Info\n");
            break;
        }
        case SUB_CT_LAYOUT: {
            const uint8_t ln = data_in[4];
            printf(">> Set Layout %d\n", ln);
            current_layout = ln;
            break;
        }
    }
}
static void cmd_qmk_eeprom(const uint8_t *data_in, uint8_t *data_out){
//    printf("qmk eeprom\n");
    const uint8_t subcmd = data_in[1];
    uint32_t addr = from_leu32(data_in + 4);
    switch (subcmd) {
        case SUB_EE_INFO: {
            spi_rdid(data_out);
            printf(">> Info EEPROM %02x %02x %02x\n", data_out[1], data_out[2], data_out[3]);
            break;
        }
        case SUB_EE_READ: {
            rtcnt_t start = chSysGetRealtimeCounterX();
            spi_read(addr, 60, data_out);
            rtcnt_t end = chSysGetRealtimeCounterX();
            printf(">> Read EEPROM %04x, %d us\n", addr, RTC2US(HT32_HCLK_FREQUENCY, end - start));
            break;
        }
        case SUB_EE_WRITE:
            printf(">> Write EEPROM %04x\n", addr);
            spi_write(addr, 56, data_in + 8);
            break;
        case SUB_EE_ERASE:
            printf(">> Erase EEPROM %04x\n", addr);
            spi_erase(addr);
            break;
    }
}
static void cmd_qmk_keymap(const uint8_t *data_in, uint8_t *data_out){
//    printf("qmk keymap\n");
    const uint8_t subcmd = data_in[1];
    const uint32_t keymap_size = MAX_LAYERS * MATRIX_ROWS * MATRIX_COLS;
    const uint32_t total_size = keymap_size * sizeof(uint16_t);
    switch (subcmd) {
        case SUB_KM_INFO: {
            printf(">> Info Keymap\n");
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
            printf(">> Read Keymap %x %04x\n", page, offset);
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
            printf(">> Write Keymap %04x %d\n", offset, len);
            if (offset < total_size) {
                memcpy(((uint8_t *)keymaps) + offset, data_in + 8, MIN(total_size - offset, len));
            }
            break;
        }
        case SUB_KM_COMMIT: {
            printf(">> Commit Keymap\n");
            uint16_t crc0 = crc16((const uint8_t *)EE_KEYMAP_SIG, 4, 0);
            crc0 = crc16((const uint8_t *)keymaps, total_size, crc0);
            spi_wait_wip();
            spi_erase(EE_KEYMAP_ADDR);
            spi_write(EE_KEYMAP_ADDR, EE_KEYMAP_SIG_LEN, (const uint8_t *)EE_KEYMAP_SIG);
            spi_write(EE_KEYMAP_ADDR + EE_KEYMAP_SIG_LEN, total_size, (const uint8_t *)keymaps);
            spi_wait_wip();
            uint16_t crc1 = spi_crc(EE_KEYMAP_ADDR, EE_KEYMAP_SIG_LEN + total_size);
            if(crc0 != crc1){
                printf("EE Write Write Failed CRC\n");
            }
            break;
        }
        case SUB_KM_RELOAD: {
            printf(">> Reload Keymap\n");
            keymap_load();
            break;
        }
        case SUB_KM_RESET: {
            printf(">> Reset Keymap\n");
            keymap_load_default();
            break;
        }
    }
}
static void cmd_qmk_backlight(const uint8_t *data_in, uint8_t *data_out){
//    printf("qmk backlight\n");
}

static void cmd_qmk_flash(const uint8_t *data_in, uint8_t *data_out){
//    printf("qmk flash\n");
    const uint8_t subcmd = data_in[1];
    switch (subcmd) {
        case SUB_FL_READ: {
            uint32_t addr = from_leu32(data_in + 4);
            printf(">> Flash Read %04x\n", addr);
            if (addr < FLASH_SIZE) {
                memcpy(data_out, (const uint8_t *)addr, MIN(FLASH_SIZE - addr, 60));
            }
            break;
        }
    }
}

#define CMDH_POK3R  0x00
#define CMD_POK3R_N 7
#define CMDH_CYKB   0x10
#define CMD_CYKB_N  3
#define CMDH_QMK    0x80
#define CMD_QMK_N   6

static const apiHandler cmd_lut[] = {
#if defined(UPDATE_PROTO_POK3R)
    // pok3r 0x0
    NULL,               // erase
    cmd_pok3r_flash,    // flash
    NULL,               // crc
    NULL,               // update start
    cmd_compat_reset,   // reset
    NULL,               // disconnect
    NULL,               // debug
#else
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#endif

#if defined(UPDATE_PROTO_CYKB)
    // cykb 0x1
    NULL,               // ?
    cmd_compat_reset,   // reset
    cmd_cykb_read,      // read
#else
    NULL,
    NULL,
    NULL,
#endif

    // qmk 0x8
    NULL,
    cmd_qmk_ctrl,       // ctrl
    cmd_qmk_eeprom,     // eeprom
    cmd_qmk_keymap,     // keymap
    cmd_qmk_backlight,  // backlight
    cmd_qmk_flash,      // flash
};

void OVERRIDE raw_hid_receive(uint8_t *data_in, uint8_t length) {
//    printf("Command Packet Receive\n");
    if (length != PKT_LEN) {
        printf("Bad raw data\n");
    }
    // parse command
    const uint8_t cmd = data_in[0];
    const uint8_t subcmd = data_in[1];
    const uint16_t crc_in = from_leu16(data_in + 2);
    const uint8_t h = cmd & 0xF0;
    const uint8_t l = cmd & 0x0F;
    uint8_t *data_out;
    apiHandler func = NULL;

    // clear response
    memset(packet_buf, 0, PKT_LEN);

    // command group
    if(h == CMDH_POK3R && l < CMD_POK3R_N){
        // pok3r
        func = cmd_lut[l];
        data_out = packet_buf;

    } else if(h == CMDH_CYKB && l < CMD_CYKB_N){
        // cykb
        func = cmd_lut[CMD_POK3R_N + l];
        packet_buf[0] = cmd;
        packet_buf[1] = subcmd;
        to_leu16(packet_buf + 2, crc_in);
        data_out = packet_buf + 4;

    } else if(h == CMDH_QMK && l < CMD_POK3R_N){
        // qmk
        func = cmd_lut[CMD_POK3R_N + CMD_CYKB_N + l];
        data_out = packet_buf + 4;

        to_leu16(data_in + 2, 0);
        const uint16_t crc_check = crc16(data_in, PKT_LEN, 0);
        if(crc_check != crc_in){
            printf("Corrupt Request CRC\n");
            return;
        }
        to_leu16(packet_buf, crc_in);
        to_leu16(packet_buf + 2, 0);
    }

    if(func){
        // Command handler
        func(data_in, data_out);
        if(h == CMDH_QMK){
            const uint16_t crc_out = crc16(packet_buf, PKT_LEN, 0);
            to_leu16(packet_buf + 2, crc_out);
        }

    } else {
        // Error
        printf("Bad command %x\n", cmd);
        packet_buf[0] = 0xff;
        packet_buf[1] = 0xaa;
        packet_buf[2] = 0;
        packet_buf[3] = 0;
    }

    // send response
    raw_hid_send(packet_buf, PKT_LEN);
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
