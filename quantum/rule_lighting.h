/* Copyright 2026 Javier Domingo
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

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef RGB_MATRIX_ENABLE

/* Maximum number of rule lighting entries
 * This is an internal constant for split sync buffer sizing
 * Limited to 31 entries max (248 bytes) due to split transaction buffer limit (uint8_t = 255 max)
 * Users can define any number of rules up to this limit in their keymap
 */
#    ifndef RULE_LIGHTING_ENTRIES
#        define RULE_LIGHTING_ENTRIES 31
#    endif

/*
 * Split keyboard configuration for rule lighting
 * Auto-configures RPC buffer size for split sync
 * Transaction IDs are defined in transaction_id_define.h
 *
 * RPC sync is only needed when DYNAMIC_KEYMAP is enabled (each half has independent EEPROM).
 * For static keymaps, both halves read rules directly from flash.
 */
#    if defined(SPLIT_KEYBOARD) && defined(RULE_LIGHTING_ENABLE) && defined(DYNAMIC_KEYMAP_ENABLE)

/*
 * RPC buffer size must fit the rules array
 * Buffer size = 8 bytes per entry * RULE_LIGHTING_ENTRIES
 */
#        define _RL_RPC_BUFFER_SIZE (8 * RULE_LIGHTING_ENTRIES)

#        ifndef RPC_M2S_BUFFER_SIZE
#            define RPC_M2S_BUFFER_SIZE _RL_RPC_BUFFER_SIZE
#        elif RPC_M2S_BUFFER_SIZE < _RL_RPC_BUFFER_SIZE
#            undef RPC_M2S_BUFFER_SIZE
#            define RPC_M2S_BUFFER_SIZE _RL_RPC_BUFFER_SIZE
#        endif

/* Split state syncing is automatically enabled by builddefs/common_features.mk */

#    endif /* SPLIT_KEYBOARD && RULE_LIGHTING_ENABLE && DYNAMIC_KEYMAP_ENABLE */

/**
 * Saturation modes (2 bits)
 */
typedef enum {
    RGB_MATRIX_SAT_OFF    = 0b00, // LED off (RGB 0,0,0)
    RGB_MATRIX_SAT_WHITE  = 0b01, // S=0 (white/grayscale)
    RGB_MATRIX_SAT_PASTEL = 0b10, // S=128 (soft color)
    RGB_MATRIX_SAT_PURE   = 0b11, // S=255 (vivid color)
} rgb_matrix_saturation_t;

#    define RGB_MATRIX_SAT_IS_ON(sat) ((sat) != RGB_MATRIX_SAT_OFF)

/**
 * RGB Rule Lighting Entry (8 bytes)
 *
 * Bit layout:
 *   Byte 0-1 (condition):
 *     Bit 0:    layer_enable (0 = any layer, 1 = match layer field)
 *     Bit 1:    caps_enable (0 = any caps state, 1 = caps must be ON)
 *     Bits 2-3: reserved
 *     Bits 4-7: layer (0-15)
 *     Bits 8-15: mods (modifier mask, 0 = any)
 *
 *   Byte 2-3: keycode_start (full 16-bit range)
 *   Byte 4-5: keycode_end (full 16-bit range, inclusive)
 *
 *   Byte 6 (color_idle):
 *     Bits 0-1: sat_idle
 *     Bits 2-7: h_idle (6-bit hue, use << 2 for 8-bit)
 *
 *   Byte 7 (color_pressed):
 *     Bits 0-1: sat_pressed
 *     Bits 2-7: h_pressed (6-bit hue)
 */
typedef struct {
    /* Condition (16 bits) */
    uint16_t layer_enable : 1;
    uint16_t caps_enable : 1;
    uint16_t reserved : 2;
    uint16_t layer : 4;
    uint16_t mods : 8;

    /* Keycode range (32 bits) */
    uint16_t keycode_start;
    uint16_t keycode_end;

    /* Colors (16 bits) */
    uint8_t sat_idle : 2;
    uint8_t h_idle : 6;
    uint8_t sat_pressed : 2;
    uint8_t h_pressed : 6;

} __attribute__((packed)) rule_lighting_entry_t;

_Static_assert(sizeof(rule_lighting_entry_t) == 8, "Unexpected size of rule_lighting_entry_t structure");

/**
 * Initialize the rule lighting system (early init)
 * Called from rgb_matrix_init() during keyboard_init()
 */
void rule_lighting_init(void);

/**
 * Post-initialization for split keyboard support
 * Registers RPC handlers - must be called AFTER split_post_init()
 * Called from keyboard_post_init_kb()
 */
void rule_lighting_post_init(void);

/**
 * Housekeeping task for rule lighting
 * Handles split keyboard sync on master
 */
void rule_lighting_task(void);

/**
 * Get the rules array
 * Returns flash array on master, RAM copy on slave
 */
const rule_lighting_entry_t *rule_lighting_get_rules(void);

/**
 * Get keycode for a key position (supports split keyboard sync)
 * Weak function - keyboards can override with synced keymap support
 */
uint16_t get_synced_keycode(uint8_t layer, uint8_t row, uint8_t col);

/**
 * Convert 6-bit hue to 8-bit
 */
#    define RGB_MATRIX_HUE_6TO8(h6) ((h6) << 2)

/**
 * Convert saturation mode to S value (0-255)
 */
static inline uint8_t rgb_matrix_sat_to_value(uint8_t sat_mode) {
    switch (sat_mode) {
        case RGB_MATRIX_SAT_OFF:
            return 0;
        case RGB_MATRIX_SAT_WHITE:
            return 0;
        case RGB_MATRIX_SAT_PASTEL:
            return 128;
        case RGB_MATRIX_SAT_PURE:
            return 255;
        default:
            return 0;
    }
}

#else /* RGB_MATRIX_ENABLE */

/* Stub when RGB Matrix is disabled */
#    define RULE_LIGHTING_ENTRIES 0

#endif /* RGB_MATRIX_ENABLE */
