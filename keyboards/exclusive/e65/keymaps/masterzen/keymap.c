#include QMK_KEYBOARD_H

enum layers {
    BASE,  // qwerty linux
    OSX,   // qwerty osx

    _ADJUST,  // function key layer
};

enum keycodes {
    // default layout switcher
    LAY_LIN = SAFE_RANGE,
    LAY_OSX
};

// clang-format off

/*
 * ,---------------------------------------------------------------------|
 * |`  |1  |2  |3  |4  |5  |6  |7  |8  |9  |0   |-   |=   |\  |Esc | Ins |
 * |---------------------------------------------------------------------|
 * |Tab  |Q  |W  |E  |R  |T  |Y  |U  |I  |O  |P  |[  | ]  |    BSpc| PgUp|
 * |---------------------------------------------------------------------|
 * |LCTRL |A  |S  |D  |F  |G  |H  |J  |K  |L  |;  |'  |  Enter    | PgDn |
 * |---------------------------------------------------------------------|
 * |Shft    |Z  |X  |C  |V  |B  |N  |M  |,  |.  |/   |   Shift | Up |Del |
 * |---------------------------------------------------------------------|
 * |Ctrl|GUI |Alt |     Space                    |Alt| Ctrl|▓|Lt |Dn |Rt |
 * `---------------------------------------------------------------------|'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT_65_ansi_blocker_splitbs(
        KC_ESC, KC_1,   KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, LT(_ADJUST,KC_INS),
        KC_TAB, KC_Q,   KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_PGUP,

        KC_LCTL, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN,  KC_QUOT,        KC_ENT, KC_PGDN,
        KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT,KC_SLSH,         KC_RSFT, KC_UP, KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC,                      KC_RALT, KC_RCTRL, KC_LEFT, KC_DOWN,KC_RGHT),

    [OSX] = LAYOUT_65_ansi_blocker_splitbs(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_LALT, KC_LGUI,                  _______,                             KC_LGUI, KC_RALT, _______, _______, _______),

    [_ADJUST] = LAYOUT_65_ansi_blocker_splitbs(
        RESET,   LAY_LIN, LAY_OSX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(_ADJUST),
        BL_TOGG, BL_DEC, BL_INC, KC_LGUI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI, _______,
        _______, _______, _______,                  _______,                             _______, _______, RGB_MOD, RGB_VAD, RGB_HUD),


};

// clang-format on

extern rgblight_config_t rgblight_config;

bool     edit = false;
rgblight_config_t temp_config;

void keyboard_post_init_user(void) { temp_config.raw = rgblight_config.raw; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* layout switcher */
        case LAY_LIN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(BASE);
            }
            return false;
            break;
        case LAY_OSX:
            if (record->event.pressed) {
                set_single_persistent_default_layer(OSX);
            }
            return false;
            break;
        case RGB_MOD:
            // allows to set the rgb mode while in the ADJUST layer which uses
            // its own mode
            if (record->event.pressed) {
                rgblight_mode(temp_config.mode);
                rgblight_step();
                temp_config.mode = rgblight_config.mode;
            }
            return false;
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (state == BASE && edit == true) {
        temp_config.hue  = rgblight_get_hue();
        temp_config.sat  = rgblight_get_sat();
        temp_config.val  = rgblight_get_val();
        edit = false;
    }

    switch (get_highest_layer(state)) {
        case _ADJUST:
            temp_config.mode = rgblight_get_mode();
            rgblight_mode_noeeprom(1);
            rgblight_setrgb(0xD3, 0x7F, 0xED);
            edit = true;
            break;
        default:
            rgblight_mode(temp_config.mode);
            rgblight_sethsv(temp_config.hue, temp_config.sat, temp_config.val);
            break;
    }
    return state;
}
