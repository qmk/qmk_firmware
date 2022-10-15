/*
 * dbroqua HHKB Layout
 */
#include QMK_KEYBOARD_H

enum layer_names {
  _DEFAULT,
  _ALTERNATE,
  _FN,
  _RGB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE layer: Default Layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
     * |-----------------------------------------------------------------------------------------+
     * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Bksp  |
     * |-----------------------------------------------------------------------------------------+
     * | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
     * |-----------------------------------------------------------------------------------------+
     * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Shift     | fn  |
     * +-----------------------------------------------------------------------------------------+
     *         | Alt |  Gui   |                    Space                   | Gui   |RCtrl|
     *         `-------------------------------------------------------------------------´
      */
    [_DEFAULT] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(_FN),
        KC_TRNS, KC_LALT, KC_LGUI, /*        */ KC_SPC, KC_RGUI, KC_RCTL, KC_TRNS),
    /* Alternamte layer: swap alt/gui
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
     * |-----------------------------------------------------------------------------------------+
     * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Bksp  |
     * |-----------------------------------------------------------------------------------------+
     * | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
     * |-----------------------------------------------------------------------------------------+
     * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Shift     | fn  |
     * +-----------------------------------------------------------------------------------------+
     *         | Gui |  Alt   |                    Space                   | AltGr |RCtrl|
     *         `-------------------------------------------------------------------------´
      */
    [_ALTERNATE] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(_FN),
        KC_TRNS, KC_LGUI, KC_LALT, /*        */ KC_SPC, KC_RALT, KC_RCTL, KC_TRNS),

    /* FN Layer
     * ,-----------------------------------------------------------------------------------------.
     * | Pwr |  F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F0  | F11 | F12 | Ins | Del|
     * |-----------------------------------------------------------------------------------------+
     * | Caps   |     |     |     |     |     |     |     |PrtSc| Slck| Paus|  Up |     |        |
     * |-----------------------------------------------------------------------------------------+
     * |         | Vol-| Vol+| Mute|Eject|     | *   | /   | Home| PgUp| Left |Right|            |
     * |-----------------------------------------------------------------------------------------+
     * |           | Prev| Play| Next|     |     | +   | -   | End |PgDwn| Down| _RGB      |     |
     * +-----------------------------------------------------------------------------------------+
     *         | _DEF| _ALTER |                                            | Stop  |     |
     *         `-------------------------------------------------------------------------´
      */
    [_FN] = LAYOUT(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, RGB_TOG, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_TRNS,
        KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, DF(_RGB), KC_TRNS,
        KC_TRNS, DF(_DEFAULT), DF(_ALTERNATE), KC_TRNS, KC_MSTP, KC_TRNS, KC_TRNS),


    /* RGB Layer
     * ,-----------------------------------------------------------------------------------------.
     * | RST |      |     |     |     |     |     |     |     |     |     |     |     |     |    |
     * |-----------------------------------------------------------------------------------------+
     * |        |R_TOG|R_MOD|RRMOD|R_HUI|R_HUD|R_SAI|R_SAD|R_VAI|R_VAD|R_SPI|R_SPD|     |        |
     * |-----------------------------------------------------------------------------------------+
     * |         |R_M_P|R_M_B|R_M_R|R_MSW|R_MSN|R_M_K|R_M_X|R_M_G|     |      |     |            |
     * |-----------------------------------------------------------------------------------------+
     * |           |BL_TG|BL_ST|BL_ON|BL_OF|BL_IN|BL_DC|BL_BR|     |     |     |           |     |
     * +-----------------------------------------------------------------------------------------+
     *         | _DEF| _ALTER |                                            |       |     |
     *         `-------------------------------------------------------------------------´
     */
    [_RGB] = LAYOUT(
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, BL_TOGG, BL_STEP, BL_ON, BL_OFF, BL_INC, BL_DEC, BL_BRTG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, DF(_DEFAULT), DF(_ALTERNATE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};
