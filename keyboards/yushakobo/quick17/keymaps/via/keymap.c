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
// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _PHOTO,
    _PHOTO_SHIFT,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    PS_LANG = SAFE_RANGE,
    FN_LANG
};

/*
    PHOTO,
    FN,
*/
#define FN MO(_FN)
#define BASE DF(_BASE)
#define PHOTO DF(_PHOTO)
#define PHOTO_S MO(_PHOTO_SHIFT)
#define MAC CG_NORM
#define WIN CG_SWAP
#define PS_CMRL KC_LGUI
#define PS_ERSE KC_E
#define PS_MGWD KC_W
#define PS_EYDR KC_I
#define PS_SLCT KC_A
#define PS_HAND KC_H
#define PS_LASS KC_L
#define PS_MRQE KC_M
#define PS_PEN KC_P
#define PS_MOVE KC_V
#define PS_ZOOM KC_Z
#define PS_CROP KC_C
#define PS_BRSD KC_LBRC
#define PS_BRSI KC_RBRC
#define PS_BRSP KC_COMM
#define PS_BRSN KC_DOT
#define PS_CSHR KC_CAPS
#define PS_ZIN LGUI(KC_PLUS)
#define PS_ZOUT LGUI(KC_MINS)
#define PS_CLYR SGUI(KC_N)//ctrl shift n
#define PS_UNDO LGUI(KC_Z)
#define PS_REDO SGUI(KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    KC_TAB,  KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, KC_INS,
    KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_DEL,
    KC_LSFT, KC_ESC,  KC_LALT, KC_SPC,  FN,      KC_ENT
),
    [_PHOTO] = LAYOUT(
    KC_ESC,  PS_ERSE, PS_MGWD, PS_EYDR, PS_ZIN,  KC_BSPC,
    PS_CMRL, PS_SLCT, PS_HAND, PS_LASS, PS_MRQE, PS_PEN,
    KC_LSFT, KC_Z,    KC_V,    KC_LALT, PHOTO_S, KC_ENT
),
    [_PHOTO_SHIFT] = LAYOUT(
    KC_ESC,  PS_BRSD, PS_BRSI, PS_UNDO, PS_REDO, KC_DEL,
    PS_CMRL, PS_BRSP, PS_BRSN, PS_CSHR, PS_CROP, PS_CLYR,
    KC_LSFT, PS_LANG, BASE,    _______, _______, _______
),
    [_FN] = LAYOUT(
    FN_LANG, KC_LANG1,XXXXXXX, RGB_TOG, KC_MNXT, KC_VOLU,
    PHOTO,   BASE,    KC_NO,   RGB_MOD, KC_MPRV, KC_VOLD,
    MAC,     WIN,     KC_NO,   KC_NO,   _______, KC_MUTE
)
};

static bool _mode_ja = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PS_LANG:
            if (record->event.pressed){
                if(keymap_config.swap_lctl_lgui == true){
                    SEND_STRING(SS_LALT("`"));
                } else {
                    if (_mode_ja == false){
                        register_code(KC_LANG2);
                    } else {
                        register_code(KC_LANG1);
                    }
                }
            } else {
                if (_mode_ja == false){
                    unregister_code(KC_LANG2);
                    _mode_ja = true;
                } else {
                    unregister_code(KC_LANG1);
                    _mode_ja = false;
                }
            }
            break;
        case FN_LANG:
            if(record->event.pressed){
                if(keymap_config.swap_lctl_lgui){
                    SEND_STRING(SS_LALT("`"));
                } else {
                    register_code(KC_LANG2);
                }
            } else {
                unregister_code(KC_LANG2);
            }
            break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (layer_state) {
            case _BASE:
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
                break;
            case _PHOTO:
            case _PHOTO_SHIFT:
                if (clockwise) {
                    tap_code(KC_RBRC);
                } else {
                    tap_code(KC_LBRC);
                }
                break;
            case _FN:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            default:
                break;
        }
    }
}

#ifdef RGBLIGHT_LAYERS
#define RGBINDICATOR_TEST_A HSV_RED
#define RGBINDICATOR_TEST_B HSV_BLUE
#define RGBINDICATOR_TEST_C HSV_WHITE
#define RGBINDICATOR_TEST_D HSV_GREEN
    const rgblight_segment_t PROGMEM mode_mac[] = RGBLIGHT_LAYER_SEGMENTS(
        {5, 1, RGBINDICATOR_TEST_A}
//        {5, 1, HSV_WHITE}
    );
    const rgblight_segment_t PROGMEM mode_win[] = RGBLIGHT_LAYER_SEGMENTS(
        {5, 1, RGBINDICATOR_TEST_B}
//        {5, 1, HSV_TEAL}
    );
    const rgblight_segment_t PROGMEM mode_base[] = RGBLIGHT_LAYER_SEGMENTS(
        {11, 1, RGBINDICATOR_TEST_D}
    );
    const rgblight_segment_t PROGMEM mode_photo[] = RGBLIGHT_LAYER_SEGMENTS(
        {11, 1, RGBINDICATOR_TEST_A}
//        {11, 1, HSV_TEAL}
    );
    const rgblight_segment_t PROGMEM mode_photo1[] = RGBLIGHT_LAYER_SEGMENTS(
        {11, 1, RGBINDICATOR_TEST_B}
//        {11, 1, HSV_BLUE}
    );
    const rgblight_segment_t PROGMEM mode_fn[] = RGBLIGHT_LAYER_SEGMENTS(
        {11, 1, RGBINDICATOR_TEST_C}
//        {11, 1, HSV_SPRINGGREEN}
    );
    const rgblight_segment_t PROGMEM mode_ja[] = RGBLIGHT_LAYER_SEGMENTS(
        {17, 1, RGBINDICATOR_TEST_A}
//        {17, 1, HSV_ORANGE}
    );
    const rgblight_segment_t PROGMEM mode_en[] = RGBLIGHT_LAYER_SEGMENTS(
        {17, 1, RGBINDICATOR_TEST_B}
//        {17, 1, HSV_YELLOW}
    );
    const rgblight_segment_t* const PROGMEM quick17_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        mode_base,
        mode_photo,
        mode_photo1,
        mode_fn,
        mode_mac,
        mode_win,
        mode_ja,
        mode_en
    );
    void keyboard_post_init_user(void){
        rgblight_layers = quick17_rgb_layers;
        
    }
    layer_state_t layer_state_set_user(layer_state_t state){
        rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
        rgblight_set_layer_state(1, layer_state_cmp(state, _PHOTO));
        rgblight_set_layer_state(2, layer_state_cmp(state, _PHOTO_SHIFT));
        rgblight_set_layer_state(3, layer_state_cmp(state, _FN));
        rgblight_set_layer_state(4, keymap_config.swap_lctl_lgui == true);
        rgblight_set_layer_state(5, keymap_config.swap_lctl_lgui == false);
        rgblight_set_layer_state(6, _mode_ja);
        rgblight_set_layer_state(7, !_mode_ja);
        return state;
    }
    /*
    bool led_update_user(led_t led_state){
        return true;
    }
    */
#endif
