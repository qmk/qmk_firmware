#include QMK_KEYBOARD_H


enum layers {
    _WINDOWS,
    _LINUX, 
    _NUMPAD,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  WINDOWS = SAFE_RANGE,
  LINUX,
  NUMPAD,
  LOWER,
  RAISE,
  ADJUST
};

#define CTL_ENT MT(MOD_RCTL, KC_PENT)
#define NUMPAD MO(_NUMPAD)
#define SHELL LCA(KC_T)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Windows Qwerty
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * | `     |   1   |   2   |   3   |   4   |   5   |   -   |                       |   =   |   6   |   7   |   8   |   9   |   0   |BSpace |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |   Q   |   W   |   E   |   R   |   T   |   [   |                       |   ]   |   Y   |   U   |   I   |   O   |   P   |   \   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Esc   |   A   |   S   |   D   |   F   |   G   | Home  |                       | Del   |   H   |   J   |   K   |   L   |   :   |   '   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   Z   |   X   |   C   |   V   |   B   |   -   |                       |   =   |   N   |   M   |   ,   |   .   |   /   | Shift |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | LCtrl | LGUI  | LAlt  |Numpad ||||||||| Space | Lower | Enter ||||||||| Enter | Raise |BSpace ||||||||| F5    | RAlt  | RGui  |Ctl/Ent|
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_WINDOWS] = LAYOUT( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,                            KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                            KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,                            KC_DEL,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS,                            KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_LCTL, KC_LGUI, KC_LALT, NUMPAD,           KC_SPC,  LOWER,   KC_ENT,           KC_ENT,  RAISE,   KC_BSPC,          KC_F5,   KC_RALT, KC_RGUI, CTL_ENT  \
  ),

  /* Linux Qwerty
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * | `     |   1   |   2   |   3   |   4   |   5   |   -   |                       |   =   |   6   |   7   |   8   |   9   |   0   |BSpace |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |   Q   |   W   |   E   |   R   |   T   |   [   |                       |   ]   |   Y   |   U   |   I   |   O   |   P   |   \   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Esc   |   A   |   S   |   D   |   F   |   G   | Home  |                       | Del   |   H   |   J   |   K   |   L   |   :   |   '   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   Z   |   X   |   C   |   V   |   B   |   -   |                       |   =   |   N   |   M   |   ,   |   .   |   /   | Shift |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | LCtrl | LGUI  | LAlt  |Numpad ||||||||| Space | Lower | Enter ||||||||| Enter | Raise |BSpace ||||||||| Shell | RAlt  | RGui  |Ctl/Ent|
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_LINUX] = LAYOUT( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,                            KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                            KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,                            KC_DEL,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS,                            KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_LCTL, KC_LGUI, KC_LALT, NUMPAD,           KC_SPC,  LOWER,   KC_ENT,           KC_ENT,  RAISE,   KC_BSPC,          SHELL,   KC_RALT, KC_RGUI, CTL_ENT  \
  ),

  /* Numpad
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|NumLock|   /   |   *   |   -   |XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|   7   |   8   |   9   |       |XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+   +   +-------|
   * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|   4   |   5   |   6   |       |XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|   1   |   2   |   3   |       |XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+ Enter +-------|
   * |XXXXXXX|XXXXXXX|XXXXXXX|Numpad |||||||||XXXXXXX|XXXXXXX|XXXXXXX|||||||||XXXXXXX|XXXXXXX|XXXXXXX|||||||||   0   |   .   |       | Enter |
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_NUMPAD] = LAYOUT( \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_BSPC, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, NUMPAD,           XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,          KC_KP_0, KC_PDOT, KC_PENT, KC_PENT  \
  ),

  /* Lower
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * | F11   | F1    | F2    | F3    | F4    | F5    |       |                       |       | F6    | F7    | F8    | F9    | F10   | F12   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |   (   |   {   |   [   |       |                       |       |   ]   |   }   |   )   |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |PageUp |       |                       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |VolDown| VolUp |       |       |PageDwn|       |                       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |||||||||       | Lower |       |||||||||       | Raise |       |||||||||       |       |       |       |
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT( \
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                            _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
    _______, _______, _______, KC_LPRN, KC_LCBR, KC_LBRC, _______,                            _______, KC_RBRC, KC_RCBR, KC_RPRN, _______, _______, _______, \
    _______, _______, _______, _______, _______, KC_PGUP, _______,                            _______, _______, _______, _______, _______, _______, _______, \
    KC_CAPS, KC_VOLD, KC_VOLU, _______, _______, KC_PGDN, _______,                            _______, _______, _______, _______, _______, _______, KC_CAPS, \
    _______, _______, _______, _______,          _______, LOWER,   _______,          _______, RAISE,   _______,          _______, _______, _______, _______  \
  ),

  /* Raise
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * | F11   | F1    | F2    | F3    | F4    | F5    |       |                       |       | F6    | F7    | F8    | F9    | F10   | F12   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |   (   |   {   |   [   |       |                       |       |   ]   |   }   |   )   |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |       | End   |                       |       | Left  | Down  | Up    | Right |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |       |       |                       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |||||||||       | Lower |       |||||||||       | Raise |       |||||||||       |       |       |       |
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT( \
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                            _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
    _______, _______, _______, KC_LPRN, KC_LCBR, KC_LBRC, _______,                            _______, KC_RBRC, KC_RCBR, KC_RPRN, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_END,                             _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    KC_CAPS, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_CAPS, \
    _______, _______, _______, _______,          _______, LOWER,   _______,          _______, RAISE,            _______, _______, _______, _______, _______  \
  ),

  /* Adjust
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * |XXXXXXX|Windows| Linux |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |XXXXXXX|XXXXXXX|XXXXXXX| Cycle |On/Off |XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|On/Off | Cycle |XXXXXXX|XXXXXXX|XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Reset |XXXXXXX|XXXXXXX|Breathe| Inc   |XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|Hue inc|Sat inc| Inc   |XXXXXXX|XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX| Dec   |XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|Hue dec|Sat dec| Dec   |XXXXXXX|XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|||||||||XXXXXXX| Lower |XXXXXXX|||||||||XXXXXXX| Raise |XXXXXXX|||||||||XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT( \
    XXXXXXX, WINDOWS, LINUX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, BL_STEP, BL_TOGG, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, \
    RESET,   XXXXXXX, XXXXXXX, BL_BRTG, BL_INC,  XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_DEC,  XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, LOWER,   XXXXXXX,          XXXXXXX, RAISE,   XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WINDOWS:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WINDOWS);
      }
      return false;
      break;
    case LINUX:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LINUX);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
