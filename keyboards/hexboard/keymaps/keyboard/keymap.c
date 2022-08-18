#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Hexboard Keyboard layout (landscape)
     *       ___   ___   ___
     *      ❬BnU ᚛-᚜OcU ᚛-᚜MiO❭__
     *   ❬BnD᚛-᚜OcD᚛-᚜Pnc᚛-᚜Pnc❭
     *    ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾ 
     *  ___   ___   ___   ___   ___   ___   ___
     * ❬F 5᚛-᚜Gb5᚛-᚜G 5᚛-᚜Ab5᚛-᚜A 5᚛-᚜Bb5᚛-᚜B 5❭__
     *  ᚛-᚜D 5᚛-᚜Eb5᚛-᚜E 5᚛-᚜F 5᚛-᚜Gb5᚛-᚜G 5᚛-᚜Ab5❭
     * ❬Bb4᚛-᚜B 4᚛-᚜C 5᚛-᚜Db5᚛-᚜D 5᚛-᚜Eb5᚛-᚜E 5᚛-᚜
     *  ᚛-᚜G 4᚛-᚜Ab4᚛-᚜A 4᚛-᚜Bb4᚛-᚜B 4᚛-᚜C 5᚛-᚜Db5❭
     * ❬Eb4᚛-᚜E 4᚛-᚜F 4᚛-᚜Gb4᚛-᚜G 4᚛-᚜Ab4᚛-᚜A 4᚛-᚜
     *  ᚛-᚜C 4᚛-᚜Db4᚛-᚜D 4᚛-᚜Eb4᚛-᚜E 4᚛-᚜F 4᚛-᚜Gb4❭
     * ❬Ab3᚛-᚜A 3᚛-᚜Bb3᚛-᚜B 3᚛-᚜C 4᚛-᚜Db4᚛-᚜D 4᚛-᚜
     *  ᚛-᚜F 3᚛-᚜Gb3᚛-᚜G 3᚛-᚜Ab3᚛-᚜A 3᚛-᚜Bb3᚛-᚜B 3❭
     * ❬Db3᚛-᚜D 3᚛-᚜Eb3᚛-᚜E 3᚛-᚜F 3᚛-᚜Gb3᚛-᚜G 3᚛-᚜
     *  ᚛-᚜Bb2᚛-᚜B 2᚛-᚜C 3᚛-᚜Db3᚛-᚜D 3᚛-᚜Eb3᚛-᚜E 3❭
     * ❬Gb2᚛-᚜G 2᚛-᚜Ab2᚛-᚜A 2᚛-᚜Bb2᚛-᚜B 2᚛-᚜C 3᚛-᚜
     *  ᚛-᚜Eb2᚛-᚜E 2᚛-᚜F 2᚛-᚜Gb2᚛-᚜G 2᚛-᚜Ab2᚛-᚜A 2❭
     * ❬B 1᚛-᚜C 2᚛-᚜Db2᚛-᚜D 2᚛-᚜Eb2᚛-᚜E 2᚛-᚜F 2᚛-᚜
     *  ᚛-᚜Ab1᚛-᚜A 1᚛-᚜Bb1᚛-᚜B 1᚛-᚜C 2᚛-᚜Db2᚛-᚜D 2❭
     * ❬E 1᚛-᚜F 1᚛-᚜Gb1᚛-᚜G 1᚛-᚜Ab1᚛-᚜A 1᚛-᚜Bb1᚛-᚜
     *  ᚛-᚜Db1᚛-᚜D 1᚛-᚜Eb1᚛-᚜E 1᚛-᚜F 1᚛-᚜Gb1᚛-᚜G 1❭
     * ❬A  ᚛-᚜Bb ᚛-᚜B  ᚛-᚜C 1᚛-᚜Db1᚛-᚜D 1᚛-᚜Eb1᚛-᚜
     *  ᚛-᚜Gb ᚛-᚜G  ᚛-᚜Ab ᚛-᚜A  ᚛-᚜Bb ᚛-᚜B  ᚛-᚜C 1❭
     * ❬D  ᚛-᚜Eb ᚛-᚜E  ᚛-᚜F  ᚛-᚜Gb ᚛-᚜G  ᚛-᚜Ab ❭‾‾
     *  ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾ 
     */
    [0] = LAYOUT_hexboard_landscape(
                MI_BENDU,MI_OCTU,  MI_ON,
          MI_BENDD,MI_OCTD,  MI_ALLOFF,MI_ALLOFF,


MI_F_5, MI_Gb_5, MI_G_5,   MI_Ab_5,  MI_A_5,  MI_Bb_5, MI_B_5,
    MI_D_5, MI_Eb_5,  MI_E_5,   MI_F_5,   MI_Gb_5, MI_G_5, MI_Ab_5,
MI_Bb_4,MI_B_4,  MI_C_5,   MI_Db_5,  MI_D_5,  MI_Eb_5, MI_E_5,
    MI_G_4, MI_Ab_4,  MI_A_4,   MI_Bb_4,  MI_B_4,  MI_C_5, MI_Db_5,
MI_Eb_4,MI_E_4,  MI_F_4,   MI_Gb_4,  MI_G_4,  MI_Ab_4, MI_A_4,
    MI_C_4, MI_Db_4,  MI_D_4,   MI_Eb_4,  MI_E_4,  MI_F_4, MI_Gb_4,
MI_Ab_3,MI_A_3,  MI_Bb_3,  MI_B_3,  MI_C_4,   MI_Db_4, MI_D_4,
    MI_F_3, MI_Gb_3,  MI_G_3,   MI_Ab_3,  MI_A_3,  MI_Bb_3,MI_B_3,
MI_Db_3,MI_D_3,  MI_Eb_3,  MI_E_3,  MI_F_3,   MI_Gb_3, MI_G_3,
    _______,KC_E,     _______,  _______,  KC_I,    _______,_______,
KC_TAB, KC_W,    KC_R,  _______,    KC_U,     KC_O,   KC_BSPC,
    KC_Q,   KC_D,    KC_T,     KC_Y,     KC_K,    KC_P,   _______,
KC_ESC, KC_S,    KC_F,  _______,     KC_J,     KC_L,   KC_QUOT,
    KC_A,   KC_C,     KC_G,    KC_H,     KC_COMM, KC_SCLN,_______,
KC_LSFT,KC_X,    KC_V,   _______,   KC_M,     KC_DOT,  KC_ENT, 
    KC_Z,  _______,  KC_B,     KC_N,     KC_LEFT, KC_SLSH,_______,
_______,_______, _______,  MI_C_1,  MI_Db_1,  KC_DOWN, MI_Eb_1,
    KC_LCTL,KC_LGUI, _______,    MI_A,   KC_LEFT,   KC_UP,_______,
_______,KC_LALT, MO(1),    KC_SPC,  MO(2),    KC_DOWN,   KC_RGHT
    ),
    // "lower"
    [1] = LAYOUT_hexboard_landscape(
                MI_BENDU,MI_OCTU,  MI_ON,
          MI_BENDD,MI_OCTD,  MI_ALLOFF,MI_ALLOFF,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,KC_HASH,_______,_______,KC_ASTR,_______,_______,
KC_TILD,KC_AT,  KC_DLR,_______, KC_AMPR,KC_LPRN,KC_BSPC,
    KC_EXLM,KC_F3,  KC_PERC,KC_CIRC,KC_PLUS,KC_RPRN,_______,
KC_DEL, KC_F2,  KC_F4, _______, KC_UNDS,KC_LCBR,KC_PIPE,
    KC_F1,  KC_F9,  KC_F5,  KC_F6,  KC_COMM,KC_RCBR,_______,
KC_LSFT,KC_F8,  KC_F10, _______,_______,_______,_______,
    KC_F7,  _______,KC_F11, KC_F12, KC_HOME,KC_SLSH,_______,
_______,_______,_______,_______,_______,KC_PGDN,_______,
    _______,_______,_______,_______,KC_HOME,KC_PGUP,_______,
_______,_______,_______,_______,_______,KC_PGDN,KC_END
    )

};
