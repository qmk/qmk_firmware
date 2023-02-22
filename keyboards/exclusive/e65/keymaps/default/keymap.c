#include QMK_KEYBOARD_H

/*
 * ,---------------------------------------------------------------------|
 * |`  |1  |2  |3  |4  |5  |6  |7  |8  |9  |0   |-   |=  |Backspace| INS |
 * |---------------------------------------------------------------------|
 * |Tab  |Q  |W  |E  |R  |T  |Y  |U  |I  |O  |P  |[  | ]  |   \     |PgUp|
 * |---------------------------------------------------------------------|
 * |Caps  |A  |S  |D  |F  |G  |H  |J  |K  |L  |;  |'  |  Enter     | PgDn|
 * |---------------------------------------------------------------------|
 * |Shft    |Z  |X  |C  |V  |B  |N  |M  |,  |.  |/  |Shift       |Up| Del|
 * |---------------------------------------------------------------------|
 * |Ctrl|GUI |Alt |     Space                    |Alt |Fn  |  Lt |Dn |Rt |
 * `---------------------------------------------------------------------|'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_noblocker(
        KC_ESC, KC_1,   KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0, KC_MINS, KC_EQL,  KC_BSPC, KC_INS,
        KC_TAB, KC_Q,   KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN,  KC_QUOT,        KC_ENT, KC_PGDN,
        KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT,KC_SLSH,         KC_RSFT, KC_UP, KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC,                      KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT),

    [1] = LAYOUT_65_ansi_noblocker(
        KC_GRV,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, QK_BOOT,
        BL_TOGG, BL_DOWN,BL_UP,  BL_STEP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI,_______,
        _______, _______, _______,                  _______,                             _______,   MO(1), RGB_SAI, RGB_VAD, RGB_SAD),
};
