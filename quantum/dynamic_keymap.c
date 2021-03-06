/* Copyright 2017 Jason Williams (Wilba)
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

#include "config.h"
#include "keymap.h"  // to get keymaps[][][]
#include "tmk_core/common/eeprom.h"
#include "progmem.h"  // to read default from flash
#include "quantum.h"  // for send_string()
#include "dynamic_keymap.h"
#include "via.h"  // for default VIA_EEPROM_ADDR_END

#ifdef VIAL_ENABLE
#include "vial.h"
#endif

#ifndef DYNAMIC_KEYMAP_MACRO_COUNT
#    define DYNAMIC_KEYMAP_MACRO_COUNT 16
#endif

// This is the default EEPROM max address to use for dynamic keymaps.
// The default is the ATmega32u4 EEPROM max address.
// Explicitly override it if the keyboard uses a microcontroller with
// more EEPROM *and* it makes sense to increase it.
#ifndef DYNAMIC_KEYMAP_EEPROM_MAX_ADDR
#    if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#        define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 2047
#    elif defined(__AVR_AT90USB162__)
#        define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 511
#    else
#        define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 1023
#    endif
#endif

// Due to usage of uint16_t check for max 65535
#if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 65535
#    error DYNAMIC_KEYMAP_EEPROM_MAX_ADDR must be less than 65536
#endif

// If DYNAMIC_KEYMAP_EEPROM_ADDR not explicitly defined in config.h,
// default it start after VIA_EEPROM_CUSTOM_ADDR+VIA_EEPROM_CUSTOM_SIZE
#ifndef DYNAMIC_KEYMAP_EEPROM_ADDR
#    ifdef VIA_EEPROM_CUSTOM_CONFIG_ADDR
#        define DYNAMIC_KEYMAP_EEPROM_ADDR (VIA_EEPROM_CUSTOM_CONFIG_ADDR + VIA_EEPROM_CUSTOM_CONFIG_SIZE)
#    else
#        error DYNAMIC_KEYMAP_EEPROM_ADDR not defined
#    endif
#endif

// Encoders are located right after the dynamic keymap
#define VIAL_ENCODERS_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))

#ifdef VIAL_ENCODERS_ENABLE
#ifdef SPLIT_KEYBOARD
#define NUMBER_OF_ENCODERS (2 * sizeof(encoders_pad_a) / sizeof(pin_t))
#else
#define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
#endif
static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
#define VIAL_ENCODERS_SIZE (NUMBER_OF_ENCODERS * DYNAMIC_KEYMAP_LAYER_COUNT * 2 * 2)
#else
#define VIAL_ENCODERS_SIZE 0
#endif

// Dynamic macro starts after encoders, or dynamic keymaps if encoders aren't enabled
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (VIAL_ENCODERS_EEPROM_ADDR + VIAL_ENCODERS_SIZE)
#endif

// Sanity check that dynamic keymaps fit in available EEPROM
// If there's not 100 bytes available for macros, then something is wrong.
// The keyboard should override DYNAMIC_KEYMAP_LAYER_COUNT to reduce it,
// or DYNAMIC_KEYMAP_EEPROM_MAX_ADDR to increase it, *only if* the microcontroller has
// more than the default.
_Static_assert(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR >= 100, "Dynamic keymaps are configured to use more EEPROM than is available.");

// Dynamic macros are stored after the keymaps and use what is available
// up to and including DYNAMIC_KEYMAP_EEPROM_MAX_ADDR.
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 1)
#endif

uint8_t dynamic_keymap_get_layer_count(void) { return DYNAMIC_KEYMAP_LAYER_COUNT; }

void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column) {
    // TODO: optimize this with some left shifts
    return ((void *)DYNAMIC_KEYMAP_EEPROM_ADDR) + (layer * MATRIX_ROWS * MATRIX_COLS * 2) + (row * MATRIX_COLS * 2) + (column * 2);
}

uint16_t dynamic_keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t column) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || row >= MATRIX_ROWS || column >= MATRIX_COLS)
        return KC_NO;

    void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
    // Big endian, so we can read/write EEPROM directly from host if we want
    uint16_t keycode = eeprom_read_byte(address) << 8;
    keycode |= eeprom_read_byte(address + 1);
    return keycode;
}

void dynamic_keymap_set_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || row >= MATRIX_ROWS || column >= MATRIX_COLS)
        return;

#ifdef VIAL_ENABLE
    if (keycode == RESET && !vial_unlocked)
        return;
#endif

    void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
    // Big endian, so we can read/write EEPROM directly from host if we want
    eeprom_update_byte(address, (uint8_t)(keycode >> 8));
    eeprom_update_byte(address + 1, (uint8_t)(keycode & 0xFF));
}

#ifdef VIAL_ENCODERS_ENABLE
static void *dynamic_keymap_encoder_to_eeprom_address(uint8_t layer, uint8_t idx, uint8_t dir) {
    return ((void *)VIAL_ENCODERS_EEPROM_ADDR) + (layer * NUMBER_OF_ENCODERS * 2 * 2) + (idx * 2 * 2) + dir * 2;
}

uint16_t dynamic_keymap_get_encoder(uint8_t layer, uint8_t idx, uint8_t dir) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || idx >= NUMBER_OF_ENCODERS || dir > 1)
        return 0;

    void *address = dynamic_keymap_encoder_to_eeprom_address(layer, idx, dir);
    uint16_t keycode = eeprom_read_byte(address) << 8;
    keycode |= eeprom_read_byte(address + 1);
    return keycode;
}

void dynamic_keymap_set_encoder(uint8_t layer, uint8_t idx, uint8_t dir, uint16_t keycode) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || idx >= NUMBER_OF_ENCODERS || dir > 1)
        return;

#ifdef VIAL_ENABLE
    if (keycode == RESET && !vial_unlocked)
        return;
#endif

    void *address = dynamic_keymap_encoder_to_eeprom_address(layer, idx, dir);
    eeprom_update_byte(address, (uint8_t)(keycode >> 8));
    eeprom_update_byte(address + 1, (uint8_t)(keycode & 0xFF));
}
#endif

#if defined(VIAL_ENCODERS_ENABLE) && defined(VIAL_ENCODER_DEFAULT)
static const uint16_t PROGMEM vial_encoder_default[] = VIAL_ENCODER_DEFAULT;
_Static_assert(sizeof(vial_encoder_default)/sizeof(*vial_encoder_default) == 2 * DYNAMIC_KEYMAP_LAYER_COUNT * NUMBER_OF_ENCODERS,
    "There should be DYNAMIC_KEYMAP_LAYER_COUNT * NUMBER_OF_ENCODERS * 2 entries in the VIAL_ENCODER_DEFAULT array.");
#endif

void dynamic_keymap_reset(void) {
#ifdef VIAL_ENABLE
    /* temporarily unlock the keyboard so we can set hardcoded RESET keycode */
    int vial_unlocked_prev = vial_unlocked;
    vial_unlocked = 1;
#endif

    // Reset the keymaps in EEPROM to what is in flash.
    // All keyboards using dynamic keymaps should define a layout
    // for the same number of layers as DYNAMIC_KEYMAP_LAYER_COUNT.
    for (int layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            for (int column = 0; column < MATRIX_COLS; column++) {
                dynamic_keymap_set_keycode(layer, row, column, pgm_read_word(&keymaps[layer][row][column]));
            }
        }

#ifdef VIAL_ENCODERS_ENABLE
    for (int idx = 0; idx < NUMBER_OF_ENCODERS; ++idx) {
#ifdef VIAL_ENCODER_DEFAULT
        dynamic_keymap_set_encoder(layer, idx, 0, pgm_read_word(&vial_encoder_default[2 * (layer * NUMBER_OF_ENCODERS + idx)]));
        dynamic_keymap_set_encoder(layer, idx, 1, pgm_read_word(&vial_encoder_default[2 * (layer * NUMBER_OF_ENCODERS + idx) + 1]));
#else
        dynamic_keymap_set_encoder(layer, idx, 0, KC_TRNS);
        dynamic_keymap_set_encoder(layer, idx, 1, KC_TRNS);
#endif
    }
#endif
    }

#ifdef VIAL_ENABLE
    /* re-lock the keyboard */
    vial_unlocked = vial_unlocked_prev;
#endif
}

void dynamic_keymap_get_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    uint16_t dynamic_keymap_eeprom_size = DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2;
    void *   source                     = (void *)(DYNAMIC_KEYMAP_EEPROM_ADDR + offset);
    uint8_t *target                     = data;
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < dynamic_keymap_eeprom_size) {
            *target = eeprom_read_byte(source);
        } else {
            *target = 0x00;
        }
        source++;
        target++;
    }
}

void dynamic_keymap_set_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    uint16_t dynamic_keymap_eeprom_size = DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2;
    void *   target                     = (void *)(DYNAMIC_KEYMAP_EEPROM_ADDR + offset);
    uint8_t *source                     = data;

#ifdef VIAL_ENABLE
    /* ensure the writes are bounded */
    if (offset >= dynamic_keymap_eeprom_size || dynamic_keymap_eeprom_size - offset < size)
        return;

#ifndef VIAL_INSECURE
    /* Check whether it is trying to send a RESET keycode; only allow setting these if unlocked */
    if (!vial_unlocked) {
        /* how much of the input array we'll have to check in the loop */
        uint16_t chk_offset = 0;
        uint16_t chk_sz = size;

        /* initial byte misaligned -- this means the first keycode will be a combination of existing and new data */
        if (offset % 2 != 0) {
            uint16_t kc = (eeprom_read_byte((uint8_t*)target - 1) << 8) | data[0];
            if (kc == RESET)
                data[0] = 0xFF;

            /* no longer have to check the first byte */
            chk_offset += 1;
        }

        /* final byte misaligned -- this means the last keycode will be a combination of new and existing data */
        if ((offset + size) % 2 != 0) {
            uint16_t kc = (data[size - 1] << 8) | eeprom_read_byte((uint8_t*)target + size);
            if (kc == RESET)
                data[size - 1] = 0xFF;

            /* no longer have to check the last byte */
            chk_sz -= 1;
        }

        /* check the entire array, replace any instances of RESET with invalid keycode 0xFFFF */
        for (uint16_t i = chk_offset; i < chk_sz; i += 2) {
            uint16_t kc = (data[i] << 8) | data[i + 1];
            if (kc == RESET) {
                data[i] = 0xFF;
                data[i + 1] = 0xFF;
            }
        }
    }
#endif
#endif

    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < dynamic_keymap_eeprom_size) {
            eeprom_update_byte(target, *source);
        }
        source++;
        target++;
    }
}

#ifdef VIAL_ENCODERS_ENABLE
extern uint16_t g_vial_magic_keycode_override;
#endif

// This overrides the one in quantum/keymap_common.c
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
#ifdef VIAL_ENABLE
    /* Disable any keycode processing while unlocking */
    if (vial_unlock_in_progress)
        return KC_NO;
#endif

#ifdef VIAL_ENCODERS_ENABLE
    if (key.row == VIAL_ENCODER_MATRIX_MAGIC && key.col == VIAL_ENCODER_MATRIX_MAGIC)
        return g_vial_magic_keycode_override;
#endif

    if (layer < DYNAMIC_KEYMAP_LAYER_COUNT && key.row < MATRIX_ROWS && key.col < MATRIX_COLS) {
        return dynamic_keymap_get_keycode(layer, key.row, key.col);
    } else {
        return KC_NO;
    }
}

uint8_t dynamic_keymap_macro_get_count(void) { return DYNAMIC_KEYMAP_MACRO_COUNT; }

uint16_t dynamic_keymap_macro_get_buffer_size(void) { return DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE; }

void dynamic_keymap_macro_get_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    void *   source = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + offset);
    uint8_t *target = data;
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE) {
            *target = eeprom_read_byte(source);
        } else {
            *target = 0x00;
        }
        source++;
        target++;
    }
}

void dynamic_keymap_macro_set_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    void *   target = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + offset);
    uint8_t *source = data;
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE) {
            eeprom_update_byte(target, *source);
        }
        source++;
        target++;
    }
}

void dynamic_keymap_macro_reset(void) {
    void *p   = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR);
    void *end = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE);
    while (p != end) {
        eeprom_update_byte(p, 0);
        ++p;
    }
}

void dynamic_keymap_macro_send(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return;
    }

    // Check the last byte of the buffer.
    // If it's not zero, then we are in the middle
    // of buffer writing, possibly an aborted buffer
    // write. So do nothing.
    void *p = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE - 1);
    if (eeprom_read_byte(p) != 0) {
        return;
    }

    // Skip N null characters
    // p will then point to the Nth macro
    p         = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR);
    void *end = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE);
    while (id > 0) {
        // If we are past the end of the buffer, then the buffer
        // contents are garbage, i.e. there were not DYNAMIC_KEYMAP_MACRO_COUNT
        // nulls in the buffer.
        if (p == end) {
            return;
        }
        if (eeprom_read_byte(p) == 0) {
            --id;
        }
        ++p;
    }

    // Send the macro string one or three chars at a time
    // by making temporary 1 or 3 char strings
    char data[4] = {0, 0, 0, 0};
    // We already checked there was a null at the end of
    // the buffer, so this cannot go past the end
    while (1) {
        data[0] = eeprom_read_byte(p++);
        data[1] = 0;
        // Stop at the null terminator of this macro string
        if (data[0] == 0) {
            break;
        }
        if (data[0] == SS_QMK_PREFIX) {
            // If the char is magic, process it as indicated by the next character
            // (tap, down, up, delay)
            data[1] = eeprom_read_byte(p++);
            if (data[1] == 0)
                break;
            if (data[1] == SS_TAP_CODE || data[1] == SS_DOWN_CODE || data[1] == SS_UP_CODE) {
                // For tap, down, up, just stuff it into the array and send_string it
                data[2] = eeprom_read_byte(p++);
                if (data[2] != 0)
                    send_string(data);
            } else if (data[1] == SS_DELAY_CODE) {
                // For delay, decode the delay and wait_ms for that amount
                uint8_t d0 = eeprom_read_byte(p++);
                uint8_t d1 = eeprom_read_byte(p++);
                if (d0 == 0 || d1 == 0)
                    break;
                // we cannot use 0 for these, need to subtract 1 and use 255 instead of 256 for delay calculation
                int ms = (d0 - 1) + (d1 - 1) * 255;
                while (ms--) wait_ms(1);
            }
        } else {
            // If the char wasn't magic, just send it
            send_string(data);
        }
    }
}
