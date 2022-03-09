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

#include "keymap.h" // to get keymaps[][][]
#include "eeprom.h"
#include "progmem.h" // to read default from flash
#include "quantum.h" // for send_string()
#include "dynamic_keymap.h"
#include "via.h" // for default VIA_EEPROM_ADDR_END

#ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#    define DYNAMIC_KEYMAP_LAYER_COUNT 4
#endif

#ifndef DYNAMIC_KEYMAP_MACRO_COUNT
#    define DYNAMIC_KEYMAP_MACRO_COUNT 16
#endif

#ifndef TOTAL_EEPROM_BYTE_COUNT
#    error Unknown total EEPROM size. Cannot derive maximum for dynamic keymaps.
#endif

#ifndef DYNAMIC_KEYMAP_EEPROM_MAX_ADDR
#    define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (TOTAL_EEPROM_BYTE_COUNT - 1)
#endif

#if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > (TOTAL_EEPROM_BYTE_COUNT - 1)
#    pragma message STR(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR) " > " STR((TOTAL_EEPROM_BYTE_COUNT - 1))
#    error DYNAMIC_KEYMAP_EEPROM_MAX_ADDR is configured to use more space than what is available for the selected EEPROM driver
#endif

// Due to usage of uint16_t check for max 65535
#if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 65535
#    pragma message STR(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR) " > 65535"
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

// Dynamic encoders starts after dynamic keymaps
#ifndef DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))
#endif

// Dynamic macro starts after dynamic encoders
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * NUM_ENCODERS * 2 * 2))
#endif

// Sanity check that dynamic keymaps fit in available EEPROM
// If there's not 100 bytes available for macros, then something is wrong.
// The keyboard should override DYNAMIC_KEYMAP_LAYER_COUNT to reduce it,
// or DYNAMIC_KEYMAP_EEPROM_MAX_ADDR to increase it, *only if* the microcontroller has
// more than the default.
#if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR < 100
#    pragma message STR(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR) " < 100"
#    error Dynamic keymaps are configured to use more EEPROM than is available.
#endif

// Dynamic macros are stored after the keymaps and use what is available
// up to and including DYNAMIC_KEYMAP_EEPROM_MAX_ADDR.
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 1)
#endif

uint8_t dynamic_keymap_get_layer_count(void) {
    return DYNAMIC_KEYMAP_LAYER_COUNT;
}

void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column) {
    // TODO: optimize this with some left shifts
    return ((void *)DYNAMIC_KEYMAP_EEPROM_ADDR) + (layer * MATRIX_ROWS * MATRIX_COLS * 2) + (row * MATRIX_COLS * 2) + (column * 2);
}

uint16_t dynamic_keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t column) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || row >= MATRIX_ROWS || column >= MATRIX_COLS) return KC_NO;
    void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
    // Big endian, so we can read/write EEPROM directly from host if we want
    uint16_t keycode = eeprom_read_byte(address) << 8;
    keycode |= eeprom_read_byte(address + 1);
    return keycode;
}

void dynamic_keymap_set_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || row >= MATRIX_ROWS || column >= MATRIX_COLS) return;
    void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
    // Big endian, so we can read/write EEPROM directly from host if we want
    eeprom_update_byte(address, (uint8_t)(keycode >> 8));
    eeprom_update_byte(address + 1, (uint8_t)(keycode & 0xFF));
}

#ifdef ENCODER_MAP_ENABLE
void *dynamic_keymap_encoder_to_eeprom_address(uint8_t layer, uint8_t encoder_id) {
    return ((void *)DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR) + (layer * NUM_ENCODERS * 2 * 2) + (encoder_id * 2 * 2);
}

uint16_t dynamic_keymap_get_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || encoder_id >= NUM_ENCODERS) return KC_NO;
    void *address = dynamic_keymap_encoder_to_eeprom_address(layer, encoder_id);
    // Big endian, so we can read/write EEPROM directly from host if we want
    uint16_t keycode = ((uint16_t)eeprom_read_byte(address + (clockwise ? 0 : 2))) << 8;
    keycode |= eeprom_read_byte(address + (clockwise ? 0 : 2) + 1);
    return keycode;
}

void dynamic_keymap_set_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise, uint16_t keycode) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || encoder_id >= NUM_ENCODERS) return;
    void *address = dynamic_keymap_encoder_to_eeprom_address(layer, encoder_id);
    // Big endian, so we can read/write EEPROM directly from host if we want
    eeprom_update_byte(address + (clockwise ? 0 : 2), (uint8_t)(keycode >> 8));
    eeprom_update_byte(address + (clockwise ? 0 : 2) + 1, (uint8_t)(keycode & 0xFF));
}
#endif // ENCODER_MAP_ENABLE

void dynamic_keymap_reset(void) {
    // Reset the keymaps in EEPROM to what is in flash.
    // All keyboards using dynamic keymaps should define a layout
    // for the same number of layers as DYNAMIC_KEYMAP_LAYER_COUNT.
    for (int layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            for (int column = 0; column < MATRIX_COLS; column++) {
                dynamic_keymap_set_keycode(layer, row, column, pgm_read_word(&keymaps[layer][row][column]));
            }
        }
#ifdef ENCODER_MAP_ENABLE
        for (int encoder = 0; encoder < NUM_ENCODERS; encoder++) {
            dynamic_keymap_set_encoder(layer, encoder, true, pgm_read_word(&encoder_map[layer][encoder][0]));
            dynamic_keymap_set_encoder(layer, encoder, false, pgm_read_word(&encoder_map[layer][encoder][1]));
        }
#endif // ENCODER_MAP_ENABLE
    }
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
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < dynamic_keymap_eeprom_size) {
            eeprom_update_byte(target, *source);
        }
        source++;
        target++;
    }
}

// This overrides the one in quantum/keymap_common.c
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    if (layer < DYNAMIC_KEYMAP_LAYER_COUNT && key.row < MATRIX_ROWS && key.col < MATRIX_COLS) {
        return dynamic_keymap_get_keycode(layer, key.row, key.col);
    }
#ifdef ENCODER_MAP_ENABLE
    else if (layer < DYNAMIC_KEYMAP_LAYER_COUNT && key.row == KEYLOC_ENCODER_CW && key.col < NUM_ENCODERS) {
        return dynamic_keymap_get_encoder(layer, key.col, true);
    } else if (layer < DYNAMIC_KEYMAP_LAYER_COUNT && key.row == KEYLOC_ENCODER_CCW && key.col < NUM_ENCODERS) {
        return dynamic_keymap_get_encoder(layer, key.col, false);
    }
#endif // ENCODER_MAP_ENABLE
    return KC_NO;
}

uint8_t dynamic_keymap_macro_get_count(void) {
    return DYNAMIC_KEYMAP_MACRO_COUNT;
}

uint16_t dynamic_keymap_macro_get_buffer_size(void) {
    return DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE;
}

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
        // If the char is magic (tap, down, up),
        // add the next char (key to use) and send a 3 char string.
        if (data[0] == SS_TAP_CODE || data[0] == SS_DOWN_CODE || data[0] == SS_UP_CODE) {
            data[1] = data[0];
            data[0] = SS_QMK_PREFIX;
            data[2] = eeprom_read_byte(p++);
            if (data[2] == 0) {
                break;
            }
        }
        send_string(data);
    }
}
