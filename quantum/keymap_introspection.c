// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

// Pull the actual keymap code so that we can inspect stuff from it
#include KEYMAP_C

// Allow for keymap or userspace rules.mk to specify an alternate location for the keymap array
#ifdef INTROSPECTION_KEYMAP_C
#    include INTROSPECTION_KEYMAP_C
#endif // INTROSPECTION_KEYMAP_C

#include "keymap_introspection.h"
#include "util.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Key mapping

#define NUM_KEYMAP_LAYERS_RAW ((uint8_t)(sizeof(keymaps) / ((MATRIX_ROWS) * (MATRIX_COLS) * sizeof(uint16_t))))

uint8_t keymap_layer_count_raw(void) {
    return NUM_KEYMAP_LAYERS_RAW;
}

__attribute__((weak)) uint8_t keymap_layer_count(void) {
    return keymap_layer_count_raw();
}

#ifdef DYNAMIC_KEYMAP_ENABLE
_Static_assert(NUM_KEYMAP_LAYERS_RAW <= MAX_LAYER, "Number of keymap layers exceeds maximum set by DYNAMIC_KEYMAP_LAYER_COUNT");
#else
_Static_assert(NUM_KEYMAP_LAYERS_RAW <= MAX_LAYER, "Number of keymap layers exceeds maximum set by LAYER_STATE_(8|16|32)BIT");
#endif

uint16_t keycode_at_keymap_location_raw(uint8_t layer_num, uint8_t row, uint8_t column) {
    if (layer_num < NUM_KEYMAP_LAYERS_RAW && row < MATRIX_ROWS && column < MATRIX_COLS) {
        return pgm_read_word(&keymaps[layer_num][row][column]);
    }
    return KC_TRNS;
}

__attribute__((weak)) uint16_t keycode_at_keymap_location(uint8_t layer_num, uint8_t row, uint8_t column) {
    return keycode_at_keymap_location_raw(layer_num, row, column);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Encoder mapping

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

#    define NUM_ENCODERMAP_LAYERS_RAW ((uint8_t)(sizeof(encoder_map) / ((NUM_ENCODERS) * (NUM_DIRECTIONS) * sizeof(uint16_t))))

uint8_t encodermap_layer_count_raw(void) {
    return NUM_ENCODERMAP_LAYERS_RAW;
}

__attribute__((weak)) uint8_t encodermap_layer_count(void) {
    return encodermap_layer_count_raw();
}

_Static_assert(NUM_KEYMAP_LAYERS_RAW == NUM_ENCODERMAP_LAYERS_RAW, "Number of encoder_map layers doesn't match the number of keymap layers");

uint16_t keycode_at_encodermap_location_raw(uint8_t layer_num, uint8_t encoder_idx, bool clockwise) {
    if (layer_num < NUM_ENCODERMAP_LAYERS_RAW && encoder_idx < NUM_ENCODERS) {
        return pgm_read_word(&encoder_map[layer_num][encoder_idx][clockwise ? 0 : 1]);
    }
    return KC_TRNS;
}

__attribute__((weak)) uint16_t keycode_at_encodermap_location(uint8_t layer_num, uint8_t encoder_idx, bool clockwise) {
    return keycode_at_encodermap_location_raw(layer_num, encoder_idx, clockwise);
}

#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dip Switch mapping

#if defined(DIP_SWITCH_ENABLE) && defined(DIP_SWITCH_MAP_ENABLE)

uint16_t keycode_at_dip_switch_map_location_raw(uint8_t switch_idx, bool on) {
    if (switch_idx < NUM_DIP_SWITCHES) {
        return pgm_read_word(&dip_switch_map[switch_idx][!!on]);
    }
    return KC_TRNS;
}

__attribute__((weak)) uint16_t keycode_at_dip_switch_map_location(uint8_t switch_idx, bool on) {
    return keycode_at_dip_switch_map_location_raw(switch_idx, on);
}

#endif // defined(DIP_SWITCH_ENABLE) && defined(DIP_SWITCH_MAP_ENABLE)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Combos

#if defined(COMBO_ENABLE)

uint16_t combo_count_raw(void) {
    return ARRAY_SIZE(key_combos);
}
__attribute__((weak)) uint16_t combo_count(void) {
    return combo_count_raw();
}

_Static_assert(ARRAY_SIZE(key_combos) <= (QK_KB), "Number of combos is abnormally high. Are you using SAFE_RANGE in an enum for combos?");

combo_t* combo_get_raw(uint16_t combo_idx) {
    if (combo_idx >= combo_count_raw()) {
        return NULL;
    }
    return &key_combos[combo_idx];
}
__attribute__((weak)) combo_t* combo_get(uint16_t combo_idx) {
    return combo_get_raw(combo_idx);
}

#endif // defined(COMBO_ENABLE)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tap Dance

#if defined(TAP_DANCE_ENABLE)

uint16_t tap_dance_count_raw(void) {
    return ARRAY_SIZE(tap_dance_actions);
}

__attribute__((weak)) uint16_t tap_dance_count(void) {
    return tap_dance_count_raw();
}

_Static_assert(ARRAY_SIZE(tap_dance_actions) <= (QK_TAP_DANCE_MAX - QK_TAP_DANCE), "Number of tap dance actions exceeds maximum. Are you using SAFE_RANGE in tap dance enum?");

tap_dance_action_t* tap_dance_get_raw(uint16_t tap_dance_idx) {
    if (tap_dance_idx >= tap_dance_count_raw()) {
        return NULL;
    }
    return &tap_dance_actions[tap_dance_idx];
}

__attribute__((weak)) tap_dance_action_t* tap_dance_get(uint16_t tap_dance_idx) {
    return tap_dance_get_raw(tap_dance_idx);
}

#endif // defined(TAP_DANCE_ENABLE)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Key Overrides

#if defined(KEY_OVERRIDE_ENABLE)

uint16_t key_override_count_raw(void) {
    return ARRAY_SIZE(key_overrides);
}

__attribute__((weak)) uint16_t key_override_count(void) {
    return key_override_count_raw();
}

_Static_assert(ARRAY_SIZE(key_overrides) <= (QK_KB), "Number of key overrides is abnormally high. Are you using SAFE_RANGE in an enum for key overrides?");

const key_override_t* key_override_get_raw(uint16_t key_override_idx) {
    if (key_override_idx >= key_override_count_raw()) {
        return NULL;
    }
    return key_overrides[key_override_idx];
}

__attribute__((weak)) const key_override_t* key_override_get(uint16_t key_override_idx) {
    return key_override_get_raw(key_override_idx);
}

#endif // defined(KEY_OVERRIDE_ENABLE)
