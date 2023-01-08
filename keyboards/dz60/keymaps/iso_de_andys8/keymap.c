#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* ISO 60 layout by andys8 (ISO German keyboard layout shown)
   *
   * This layout starts from a standard ISO 60% layout, and adds a function layer.
   *
   * ,-----------------------------------------------------------------------------------------.
   * | Esc | 1 ! | 2 " | 3 § | 4 $ | 5 % | 6 & | 7 / | 8 ( | 9 ) | 0 = | ß ? | ´ ` | Backspace |
   * |-----------------------------------------------------------------------------------------|
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Z  |  U  |  I  |  O  |  P  |  Ä  | + * | Enter  |
   * |----------------------------------------------------------------------------------       |
   * | Layer_1 |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Ö  |  Ü  | # ' |       |
   * |-----------------------------------------------------------------------------------------|
   * | Shift | < > |  Y  |  X  |  C  |  V  |  B  |  N  |  M  | , ; | . : | - _ | Shift         |
   * |-----------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  | RAlt  | RGUI  | App  | RCtl |
   * `-----------------------------------------------------------------------------------------'
   */
  LAYOUT_60_iso(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, KC_APP,   KC_RCTL
  ),


  LAYOUT_60_iso(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT, KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_PSCR, KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,  KC_DEL,  KC_NO,   KC_NO,
    KC_LSFT, BL_TOGG, KC_APP,  KC_PAUS, KC_INS,  KC_NO,   KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_BSPC,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

};
