#include QMK_KEYBOARD_H
#include "dhertz.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backsp|Del|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Enter|Hom|
     * |------------------------------------------------------`    |---|
     * |SrCtl |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|    |End|
     * |---------------------------------------------------------------|
     * |Shif|  #|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |NcCtl|  Alt| CTab|       LyrSpc        |  CGv|  Alt|Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
  [0] = LAYOUT_65_iso_blocker(
      KC_ESC, KC_1,  KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
      KC_TAB,  KC_Q,  KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_HOME,
      SRCH_CTL,   KC_A,  KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT, KC_END,
      KC_LSFT, HSH_TLD, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
      NC_CTL, KC_LALT, CMD_TAB_CMD, LYR_SPC, CMD_GRV_CMD, KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT
      ),
    /* Layer 1: Special
     * ,---------------------------------------------------------------.
     * |  §| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|       |Iso|
     * |---------------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |
     * |------------------------------------------------------`    |---|
     * |      |   |   |   |   |   |   |   |   |CSL|   |   |  `|    |   |
     * |---------------------------------------------------------------|
     * |    |  `|   |   |CAC|   |   |   |   |   |   |   |      |PgU|   |
     * |---------------------------------------------------------------|
     * |     |     |     |                     |     |     |Hom|PgD|End|
     * `---------------------------------------------------------------'
     */
  [1] = LAYOUT_65_iso_blocker(
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, ISO_COUNTRY_CODE,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, CMD_SFT_L, KC_TRNS, KC_TRNS, KC_NUBS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_NUBS, KC_TRNS, KC_TRNS, CMD_ALT_C, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
      ),
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv(HSV_TEAL);
}

layer_state_t layer_state_set_keymap(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 1:
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            break;
        default: //  for any other layers, or the default layer
            rgblight_sethsv_noeeprom(HSV_TEAL);
            break;
    }
    return state;
}
