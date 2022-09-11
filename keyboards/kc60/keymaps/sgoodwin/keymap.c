
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Toggles between colemak and qwerty by tapping the bottom right key.
   * Holding capslock key gives a layer like the KBParadise v60.
   */
  [0] = LAYOUT( /* Basic Colemak */
      KC_ESC,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  \
      KC_TAB,   KC_Q,     KC_W,     KC_F,    KC_P,     KC_G,     KC_J,     KC_L,  KC_U,  KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,  \
      MO(2),    KC_A,     KC_R,     KC_S,    KC_T,     KC_D,     KC_H,     KC_N,  KC_E,  KC_I,     KC_O,     KC_QUOT,  KC_NO,    KC_ENT,   \
      KC_LSFT,  KC_NO,    KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,     KC_K,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,    KC_RSFT,  \
      KC_LCTL,  KC_LALT,  KC_LGUI,                     KC_SPC,                           KC_NO,    KC_RGUI,  KC_RALT,  KC_RCTL,  DF(1)  \
      ),
  [1] = LAYOUT( /* Basic QWERTY */
      KC_ESC,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,    KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  \
      KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,     KC_U,    KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  \
      MO(2),    KC_A,     KC_S,     KC_D,    KC_F,     KC_G,     KC_H,     KC_J,    KC_K,  KC_L,     KC_SCLN,  KC_QUOT,  KC_NO,    KC_ENT,   \
      KC_LSFT,  KC_NO,    KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,     KC_N,    KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,    KC_RSFT,  \
      KC_LCTL,  KC_LALT,  KC_LGUI,                     KC_SPC,                             KC_NO,    KC_RGUI,  KC_RALT,  KC_RCTL,  DF(0) \
      ),
  [2] = LAYOUT( /* KBP v60-like arrows, media keys, etc */
      KC_GRV,   KC_F1,    KC_F2,    KC_F3,     KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,  KC_DEL,   \
      KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_UP,    BL_INC,    BL_DEC,  BL_STEP,  \
      KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_NO,   KC_TRNS,  \
      KC_TRNS,  KC_NO,    KC_MPRV,  KC_MPLY,   KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MUTE,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_NO,   KC_TRNS,  \
      KC_TRNS,  KC_TRNS,  KC_TRNS,                       KC_SPC,                                 KC_NO,    DEBUG,    QK_BOOT,   KC_TRNS, KC_NO     \
      ),
};
