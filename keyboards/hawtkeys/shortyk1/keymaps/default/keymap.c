// Copyright 2025 Hawtkeys
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LT(0,KC_NO),
        KC_A, KC_B, KC_C
    ),
    [1] = LAYOUT(
        LT(0,KC_NO),
        KC_1, KC_2, KC_3
    ),
    [2] = LAYOUT(
        LT(0,KC_NO),
        KC_Q, KC_W, KC_E
    ),
    [3] = LAYOUT(
        LT(0,KC_NO),
        KC_R, KC_T, KC_Y
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [3] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

#if defined(RGBLIGHT_LAYERS)
const rgblight_segment_t PROGMEM rgb_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_BLUE} 
);
const rgblight_segment_t PROGMEM rgb_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_YELLOW}
);
const rgblight_segment_t PROGMEM rgb_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_GREEN}
);
const rgblight_segment_t PROGMEM rgb_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PURPLE}
);

const rgblight_segment_t* const PROGMEM all_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_layer1_layer,
    rgb_layer2_layer,    
    rgb_layer3_layer,    
    rgb_layer4_layer     
);

void keyboard_post_init_user(void) {
    rgblight_layers = all_rgb_layers;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LT(0, KC_NO):
            if (record->event.pressed) {
                // on tap
                if (record->tap.count) {
                    uint8_t layer = get_highest_layer(layer_state);
                    if (layer < 4){
                        uint8_t next_layer = layer == 3 ? 0 : layer + 1;
                        bool was_enabled = rgblight_is_enabled();
                        if (!was_enabled){
                            rgblight_enable();
                        }
                        rgblight_unblink_all_but_layer(next_layer);
                        rgblight_blink_layer_repeat(next_layer, 300, 2);

                        if (!was_enabled){
                            rgblight_disable();
                        }
                    }
                    if (layer >= 3) {
                        layer_clear();
                    } else {
                        layer_move(layer + 1);
                    }
                }
            }
            return false;
    }
    return true;
}
