/* Copyright 2020 yushakobo
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
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BASE = SAFE_RANGE,
    KC_LSPC,
    KC_LANG
};

enum layer_names {
    _CONTROL,
    _EDIT1,
    _EDIT2,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_CONTROL] = LAYOUT(
    KC_TAB, KC_PGUP,KC_UP,  KC_PGDN,KC_HOME,KC_INS,
    KC_LCTL,KC_LEFT,KC_DOWN,KC_RGHT,KC_END, KC_DEL,
    KC_LSFT,KC_LGUI,KC_ESC, KC_LALT,LT(3,KC_SPC),TO(1)
),
    [_EDIT1] = LAYOUT(
    KC_ESC, KC_W,   KC_E,   KC_R,   KC_Y,   KC_BSPC,
    KC_LCTL,KC_A,   KC_D,   KC_F,   KC_H,   LCTL(KC_Z),
    KC_LSFT,KC_X,   KC_V,   KC_B,   KC_LSPC,LCTL(KC_S)
),
    [_EDIT2] = LAYOUT(
    KC_ESC, KC_Q,   KC_BTN3,KC_INS, KC_NO,  KC_DEL,
    KC_LCTL,KC_LBRC,KC_RBRC,KC_PGDN,KC_PGUP,LCTL(KC_Y),
    KC_LSFT,TO(3),  RGB_TOG,TO(0),  _______,RESET
),
    [_FN] = LAYOUT(
    KC_ESC, KC_LANG,KC_NO,  RGB_TOG,KC_MNXT,KC_NLCK,
    KC_TAB, KC_PDOT,KC_NO,  RGB_MOD,KC_MPRV,KC_BSPC,
    CG_NORM,CG_SWAP,KC_NO,  KC_NO,  _______,KC_MUTE
)
};

static bool layer_shift = false;
static bool _mode_jaen = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSPC:
            if (record->event.pressed){
                layer_shift = 1;
                layer_on(2);
            }else{
                layer_off(2);
                if(layer_shift){
                    register_code(KC_SPC);
                    unregister_code(KC_SPC);
                }
            }
            return false;
            break;
        case KC_LANG:
            if (record->event.pressed){

            }
        default:
            if (record->event.pressed){
                layer_shift = 0;
            }
            break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise){
    if (index == 0) {
        if (IS_LAYER_ON(_EDIT1) && !layer_shift){
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        } else if (IS_LAYER_ON(_EDIT2)){
            if (clockwise) {
                tap_code(KC_LBRC);
            } else {
                tap_code(KC_RBRC);
            }
        } else if (IS_LAYER_ON(_FN)){
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        } else { // IS_LAYER_ON(_CONTROL)
            if (clockwise) {
                tap_code(KC_WH_U);
            } else {
                tap_code(KC_WH_D);
            }
        }
    }
}

#ifdef RGBLIGHT_LAYERS
#define INDICATOR_LAYERS 5
#define INDICATOR_PCS 17
#define INDICATOR_LANG 11
    const rgblight_segment_t PROGMEM mode_mac[] = RGBLIGHT_LAYER_SEGMENTS(
        {INDICATOR_PCS, 1, HSV_WHITE}
    );
    const rgblight_segment_t PROGMEM mode_win[] = RGBLIGHT_LAYER_SEGMENTS(
        {INDICATOR_PCS, 1, HSV_AZURE}
    );
    const rgblight_segment_t PROGMEM layer_ctrl[] = RGBLIGHT_LAYER_SEGMENTS(
        {INDICATOR_LAYERS, 1, HSV_TEAL}
    );
    const rgblight_segment_t PROGMEM layer_edit1[] = RGBLIGHT_LAYER_SEGMENTS(
        {INDICATOR_LAYERS, 1, HSV_GREEN}
    );
    const rgblight_segment_t PROGMEM layer_edit2[] = RGBLIGHT_LAYER_SEGMENTS(
        {INDICATOR_LAYERS, 1, HSV_GOLD}
    );
    const rgblight_segment_t PROGMEM layer_fn[] = RGBLIGHT_LAYER_SEGMENTS(
        {INDICATOR_LAYERS, 1, HSV_BLUE},
        {1, 1, HSV_RED},
        {2, 1, HSV_PURPLE}                
    );
    const rgblight_segment_t PROGMEM lang_ja[] = RGBLIGHT_LAYER_SEGMENTS(
        {INDICATOR_LANG, 1, HSV_RED}
    );
    const rgblight_segment_t PROGMEM lang_en[] = RGBLIGHT_LAYER_SEGMENTS(
        {INDICATOR_LANG, 1, HSV_PURPLE}
    );
    const rgblight_segment_t* const PROGMEM quick17_rgb_layers[] = 
    RGBLIGHT_LAYERS_LIST(
        layer_ctrl,
        layer_edit1,
        layer_edit2,
        layer_fn,
        mode_mac,
        mode_win,
        lang_ja,
        lang_en
    );
    void keyboard_post_init_user(void){
        rgblight_layers = quick17_rgb_layers;
        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
    }
    layer_state_t layer_state_set_user(layer_state_t state){
        rgblight_set_layer_state(0, layer_state_cmp(state, _CONTROL));
        rgblight_set_layer_state(1, layer_state_cmp(state, _EDIT1));
        rgblight_set_layer_state(2, layer_state_cmp(state, _EDIT2));
        rgblight_set_layer_state(3, layer_state_cmp(state, _FN));
        rgblight_set_layer_state(4, keymap_config.swap_lctl_lgui == true);
        rgblight_set_layer_state(5, keymap_config.swap_lctl_lgui == false);
        rgblight_set_layer_state(6, _mode_jaen);
        rgblight_set_layer_state(7, !_mode_jaen);
        return state;
    }
#else
    void keyboard_post_init_user(void){
        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
    }
#endif
