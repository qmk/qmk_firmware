#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
  _BASE,
  _GAMING,
  _FUNCTION,
  _FIRMWARE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
      KC_ESC,               KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,          KC_8,    KC_9,     KC_0,    KC_MINS, KC_EQL,  KC_BSLS,   KC_BSPC,
      KC_TAB,               KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,          KC_I,    KC_O,     KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
      MT(MOD_LCTL, KC_ESC), KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,          KC_K,    KC_L,     KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
      KC_LSFT,              KC_NUBS, KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,          KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
      KC_LCTL,              KC_LGUI, KC_LALT,                    KC_SPC,           LT(2, KC_ENT),                    KC_RGUI, KC_RALT, KC_APP,  KC_RCTL),

  [_GAMING] = LAYOUT(
      KC_ESC,               KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,          KC_8,    KC_9,     KC_0,    KC_MINS, KC_EQL,  KC_BSLS,   KC_BSPC,
      KC_TAB,               KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,          KC_I,    KC_O,     KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
      KC_LCTL,              KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,          KC_K,    KC_L,     KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
      KC_LSFT,              KC_NUBS, KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,          KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, MO(2),
      KC_LCTL,              KC_LGUI, KC_LALT,                    KC_SPC,           XXXXXXX,                          KC_RGUI, KC_RALT, KC_APP,  KC_RCTL),

  [_FUNCTION] = LAYOUT(
      KC_ESC,               KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,         KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_BSLS,   KC_DEL,
      KC_TAB,               XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_LCTL,              KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,       KC_UP,   KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_LSFT,              XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_LCTL,              KC_LGUI, KC_LALT,                    KC_SPC,           LT(2, KC_ENT),                    KC_RGUI, KC_RALT, KC_APP,  KC_RCTL),

  [_FIRMWARE] = LAYOUT(
      QK_BOOT,                RGB_TOG,  RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD,       RGB_VAI, BL_DOWN,  BL_TOGG, BL_UP,   XXXXXXX, XXXXXXX,   TG(1),
      XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX,              XXXXXXX, XXXXXXX,                    XXXXXXX,          XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
};
