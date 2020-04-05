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

#define SFT_ENT RSFT_T(KC_ENT)
#define CTL_ENT MT(MOD_RCTL, KC_PENT)
#define NUMPAD MO(_NUMPAD)
#define SHELL LCA(KC_T)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Windows Qwerty
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * |   1   |   2   |   3   |   4   |   5   |   6   |   `   |                       |   6   |   7   |   8   |   9   |   0   |   -   |   =   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |   Q   |   W   |   E   |   R   |   T   |   [   |                       |   ]   |   Y   |   U   |   I   |   O   |   P   |BSpace |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Esc   |   A   |   S   |   D   |   F   |   G   | Del   |                       | Enter |   H   |   J   |   K   |   L   |   :   |   '   |
   * |-------+-------+-------+-------+-------+-------+-------+-------.       .-------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   Z   |   X   |   C   |   V   |   B   | Lower |       |       |       | Raise |   N   |   M   |   ,   |   .   |   /   |Sft/Ent|
   * |-------+-------+-------+-------+-------+-------+-------| Space |       | Space |-------+-------+-------+-------+-------+-------+-------|
   * | LCtrl |Numpad | LGUI  | Lalt  ||||||||| Lctrl | Lower |       |||||||||       | Raise | RCtrl ||||||||| RAlt  | RGui  | Menu  | RCtrl |
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_WINDOWS] = LAYOUT( \
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_GRV,                             KC_BSLS, KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                            KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_DEL,                             KC_ENT,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LOWER,                              RAISE,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT, \
    KC_LCTL, NUMPAD,  KC_LGUI, KC_LALT,          KC_LCTL, LOWER,   KC_SPC,           KC_SPC,  RAISE,   KC_RCTL,          KC_RALT, KC_RGUI, KC_APP,  KC_RCTL  \
  ),

  /* Linux Qwerty
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * |   1   |   2   |   3   |   4   |   5   |   6   |   `   |                       |   6   |   7   |   8   |   9   |   0   |   -   |   =   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |   Q   |   W   |   E   |   R   |   T   |   [   |                       |   ]   |   Y   |   U   |   I   |   O   |   P   |BSpace |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | Esc   |   A   |   S   |   D   |   F   |   G   | Del   |                       | Enter |   H   |   J   |   K   |   L   |   :   |   '   |
   * |-------+-------+-------+-------+-------+-------+-------+-------.       .-------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   Z   |   X   |   C   |   V   |   B   | Lower |       |       |       | Raise |   N   |   M   |   ,   |   .   |   /   |Sft/Ent|
   * |-------+-------+-------+-------+-------+-------+-------| Space |       | Space |-------+-------+-------+-------+-------+-------+-------|
   * | LCtrl |Numpad | LGUI  | Lalt  ||||||||| Lctrl | Lower |       |||||||||       | Raise | RCtrl ||||||||| RAlt  | RGui  | Menu  | RCtrl |
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_LINUX] = LAYOUT( \
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_GRV,                             KC_BSLS, KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                            KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_DEL,                             KC_ENT,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LOWER,                              RAISE,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT, \
    KC_LCTL, NUMPAD,  KC_LGUI, KC_LALT,          KC_LCTL, LOWER,   KC_SPC,           KC_SPC,  RAISE,   KC_RCTL,          KC_RALT, KC_RGUI, KC_APP,  KC_RCTL  \
  ),

  /* Numpad
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|NumLock|XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|NumLock|   /   |   *   |   -   |XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |XXXXXXX|XXXXXXX|   7   |   8   |   9   |XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|   7   |   8   |   9   |       |BSpace |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+   +   +-------|
   * |XXXXXXX|XXXXXXX|   4   |   5   |   6   |XXXXXXX|XXXXXXX|                       |XXXXXXX|XXXXXXX|   4   |   5   |   6   |       |XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-------.       .-------+-------+-------+-------+-------+-------+-------+-------|
   * |XXXXXXX|XXXXXXX|   1   |   2   |   3   |XXXXXXX|XXXXXXX|       |       |       |XXXXXXX|XXXXXXX|   1   |   2   |   3   |       |XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------|XXXXXXX|       |XXXXXXX|-------+-------+-------+-------+-------+ Enter +-------|
   * |XXXXXXX|Numpad |XXXXXXX|   0   |||||||||XXXXXXX|XXXXXXX|       |||||||||       |XXXXXXX|XXXXXXX|||||||||   0   |   .   |       | Enter |
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_NUMPAD] = LAYOUT( \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, XXXXXXX, \
    XXXXXXX, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, KC_BSPC, \
    XXXXXXX, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, XXXXXXX, \
    XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, XXXXXXX, \
    XXXXXXX, NUMPAD,  KC_PDOT, KC_KP_0,          XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,          KC_KP_0, KC_PDOT, KC_PENT, KC_PENT  \
  ),

  /* Lower
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * | F1    | F2    | F3    | F4    | F5    | F6    |       |                       |       | F7    | F8    | F9    | F10   | F11   | F12   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |CapsLk |PageUp | Home  | Up    | End   |       |       |                       |       |       | Home  | Up    | End   |PageUp | Ins   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |PageDwn| Left  | Down  | Right |       |       |                       |       |       | Left  | Down  | Right |PageDwn|       |
   * |-------+-------+-------+-------+-------+-------+-------+-------.       .-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       | Mute  |VolDown| VolUp |       |       |       |       |       |       |       | Prev  | Play  | Next  |       |       |
   * |-------+-------+-------+-------+-------+-------+-------|       |       |       |-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |||||||||       | Lower |       |||||||||       | Raise |       |||||||||       |       |PrtScr |       |
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______,                            _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    KC_CAPS, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______,                            _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_INS,  \
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                            _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, \
    _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,                            _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, \
    _______, _______, _______, _______,          _______, LOWER,   _______,          _______, RAISE,   _______,          _______, _______, KC_PSCR, _______  \
  ),

  /* Raise
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * | F1    | F2    | F3    | F4    | F5    | F6    |       |                       |       | F7    | F8    | F9    | F10   | F11   | F12   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |CapsLk |PageUp | Home  | Up    | End   |       |       |                       |       |       | Home  | Up    | End   |PageUp | Ins   |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * |       |PageDwn| Left  | Down  | Right |       |       |                       |       |       | Left  | Down  | Right |PageDwn|       |
   * |-------+-------+-------+-------+-------+-------+-------+-------.       .-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       | Mute  |VolDown| VolUp |       |       |       |       |       |       |       | Prev  | Play  | Next  |       |       |
   * |-------+-------+-------+-------+-------+-------+-------|       |       |       |-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |||||||||       | Lower |       |||||||||       | Raise |       |||||||||       |       |PrtScr |       |
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______,                            _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    KC_CAPS, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______,                            _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_INS,  \
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                            _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, \
    _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,                            _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, \
    _______, _______, _______, _______,          _______, LOWER,   _______,          _______, RAISE,   _______,          _______, _______, KC_PSCR, _______  \
  ),

  /* Adjust
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   * |BL Togg|Windows| Linux |XXXXXXX|XXXXXXX|XXXXXXX| Reset |                       | Hue+  | Sat+  | Val+  |Speed+ |RGB Tog| Mode- | Mode- |
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | BL+   |XXXXXXX| sWirl |XXXXXXX|Rainbow|XXXXXXX|XXXXXXX|                       | Hue-  | Sat-  | Val+  |Speed- |XXXXXXX| Plain |XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-----------------------+-------+-------+-------+-------+-------+-------+-------|
   * | BL-   |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX| Grad  |XXXXXXX|                       |XXXXXXX|XXXXXXX|XXXXXXX|Knight |XXXXXXX|XXXXXXX|XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------+-------.       .-------+-------+-------+-------+-------+-------+-------+-------|
   * |BL Brth|XXXXXXX| Xmas  |XXXXXXX|XXXXXXX|Breathe|XXXXXXX|       |       |       |XXXXXXX| sNake |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------|XXXXXXX|       |XXXXXXX|-------+-------+-------+-------+-------+-------+-------|
   * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|||||||||XXXXXXX| Lower |       |||||||||       | Raise |XXXXXXX|||||||||XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
   * .---------------------------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT( \
    BL_TOGG, WINDOWS, LINUX,   XXXXXXX, XXXXXXX, XXXXXXX, RESET,                              RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_TOG, RGB_RMOD,RGB_MOD, \
    BL_INC,  XXXXXXX, RGB_M_SW,XXXXXXX, RGB_M_R, XXXXXXX, XXXXXXX,                            RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX, RGB_M_P, XXXXXXX, \
    BL_DEC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_M_G, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, RGB_M_K, XXXXXXX, XXXXXXX, XXXXXXX, \
    BL_BRTG, XXXXXXX, RGB_M_X, XXXXXXX, XXXXXXX, RGB_M_B, XXXXXXX,                            XXXXXXX, RGB_M_SN,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, LOWER,   XXXXXXX,          XXXXXXX, RAISE,   XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
  )
};

bool is_numpad_layer_on = false;
bool numlock_changed = false;

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_NUM_LOCK)) {
    is_numpad_layer_on = true;
  } else {
    is_numpad_layer_on = false;
  }
}

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

    case NUMPAD:
      /* Hold to switch layer */
      if (record->event.pressed) {
        if (!is_numpad_layer_on) {
          numlock_changed = true;
          register_code(KC_NLCK);
          unregister_code(KC_NLCK);
        }
        layer_on(_NUMPAD);
      } else {
        if (is_numpad_layer_on && numlock_changed) {
          numlock_changed = false;
          register_code(KC_NLCK);
          unregister_code(KC_NLCK);
        }
        layer_off(_NUMPAD);
      }

      /* Press to toggle layer */
      // if (record->event.pressed) {
      //   register_code(KC_NLCK);
      //   unregister_code(KC_NLCK);
      //   if (is_numpad_layer_on) {
      //     layer_off(_NUMPAD);
      //   } else {
      //     layer_on(_NUMPAD);
      //   }
      // }
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
