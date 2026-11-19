// Copyright 2026 Copyright 2026 Steffen Olszewski (@sodevel)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

const rgblight_segment_t PROGMEM _guilock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_WHITE}, {14, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM _nkro_layer[]    = RGBLIGHT_LAYER_SEGMENTS({6, 3, HSV_WHITE});

const rgblight_segment_t *const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(_guilock_layer, _nkro_layer);

void keyboard_post_init_kb(void) {
    rgblight_layers = _rgb_layers;

    keyboard_post_init_user();
}

void post_process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GU_TOGG:
        case GU_ON:
        case GU_OFF:
            rgblight_set_layer_state(0, keymap_config.no_gui ? 1 : 0);
            break;
        case NK_TOGG:
        case NK_ON:
        case NK_OFF:
            rgblight_set_layer_state(1, keymap_config.nkro ? 1 : 0);
            break;
    }

    post_process_record_user(keycode, record);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    if (get_highest_layer(state) == 1) {
        rgblight_set_layer_state(0, keymap_config.no_gui ? 1 : 0);
        rgblight_set_layer_state(1, keymap_config.nkro ? 1 : 0);
    } else {
        rgblight_set_layer_state(0, 0);
        rgblight_set_layer_state(1, 0);
    }

    return layer_state_set_user(state);
}

#endif
