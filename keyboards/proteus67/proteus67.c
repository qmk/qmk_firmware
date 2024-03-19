// Copyright 2023 James Gzowski
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layer {
    _LAYERA,
    _LAYERB,
    _LAYERC,
};

// MO(_LAYERB)
const rgblight_segment_t PROGMEM backlight_layer_layerb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_GOLD}
);
// MO(_LAYERC)
const rgblight_segment_t PROGMEM backlight_layer_layerc[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_CYAN}
);
const rgblight_segment_t PROGMEM backlight_layer_layera[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_BLACK}
);
const rgblight_segment_t* const PROGMEM set_backlight_mode[] = RGBLIGHT_LAYERS_LIST(
    backlight_layer_layerb,
    backlight_layer_layerc,
    backlight_layer_layera
);

layer_state_t layer_state_set_kb(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _LAYERB));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LAYERC));
    rgblight_set_layer_state(2, layer_state_cmp(state, _LAYERA));

    return layer_state_set_user(state);
}

void keyboard_post_init_kb(void) {
    rgblight_set_effect_range(4, 17);
    rgblight_sethsv_range(HSV_BLACK, 0, 4);
    rgblight_layers = set_backlight_mode;

    keyboard_post_init_user();
}
