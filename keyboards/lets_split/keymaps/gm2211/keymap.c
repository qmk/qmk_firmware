#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER4,
  _LAYER5,
};

enum custom_keycodes {
  BASE = SAFE_RANGE
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_ortho_4x12(
    KC_TAB,      KC_Q,        KC_W,         KC_E,    KC_R,    KC_T,     KC_Y,   KC_U,    KC_I,      KC_O,     KC_P,        KC_BSPACE, \
    MO(4),       KC_A,        KC_S,         KC_D,    KC_F,    KC_G,     KC_H,   KC_J,    KC_K,      KC_L,     KC_SCOLON,   KC_QUOTE, \
    KC_LSHIFT,   KC_Z,        KC_X,         KC_C,    KC_V,    KC_B,     KC_N,   KC_M,    KC_COMMA,  KC_DOT,   KC_SLASH,    KC_RSHIFT, \
    KC_LCTRL,    KC_LCTRL,    KC_LALT,      KC_LGUI, LOWER,   KC_SPACE, RAISE,  RAISE,   KC_MINUS,  KC_MINUS, KC_GRAVE,    MO(5)
),

[_LOWER] = LAYOUT_ortho_4x12( \
    LGUI(KC_SCOLON), LGUI(KC_Q),               LGUI(KC_W),        LALT(LGUI(KC_L)),  LALT(KC_ENTER),   LGUI(KC_T),      KC_CIRC,          KC_AMPR,           KC_ASTR,           LALT(LGUI(KC_O)),    LGUI(KC_P),       KC_TRANSPARENT, \
    KC_TRANSPARENT,  LGUI(KC_A),               LGUI(KC_S),        KC_TRANSPARENT,    LGUI(KC_F),       LGUI(KC_G),      KC_TRANSPARENT,   KC_UNDS,           KC_PLUS,           KC_EQUAL,            KC_PIPE,          KC_PIPE, \
    KC_TRANSPARENT,  KC_MAC_UNDO,              KC_MAC_CUT,        KC_MAC_COPY,       KC_MAC_PASTE,     LGUI(KC_B),      LGUI(KC_N),       KC_ENTER,          KC_TRANSPARENT,    KC_GRAVE,            KC_BSLASH,        KC_TRANSPARENT, \
    KC_LCTRL,        LCTL(LGUI(LSFT(KC_4))),   KC_TRANSPARENT,    KC_TRANSPARENT,    KC_TRANSPARENT,   KC_TRANSPARENT,  KC_NO,            KC_TRANSPARENT,    KC_UNDS,           KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,  KC_TRANSPARENT
),

[_RAISE] = LAYOUT_ortho_4x12( \
  KC_GRAVE,       KC_1,            KC_2,     KC_3,     KC_4,     KC_5,            KC_6,     KC_ENTER,        KC_DELETE,            KC_DELETE,          KC_DELETE,        KC_TRANSPARENT, \
  KC_TRANSPARENT, KC_F1,           KC_F2,    KC_F3,    KC_F4,    KC_F5,           KC_LEFT,  KC_DOWN,         KC_UP,                KC_RIGHT,           KC_BSPACE,        KC_ENTER, \
  KC_LSHIFT,      KC_F7,           KC_F8,    KC_F9,    KC_F10,   KC_F11,          KC_EQUAL, KC_ESCAPE,       LCTL(KC_SPACE),       KC_TRANSPARENT,     KC_BSLASH,        KC_ENTER, \
  KC_LCTRL,       KC_TRANSPARENT,  KC_LALT,  KC_LGUI,  KC_LALT,  LALT(KC_SPACE),  KC_NO,    KC_TRANSPARENT,  KC_MEDIA_NEXT_TRACK,  KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,  KC_AUDIO_MUTE
),

[_ADJUST] =  LAYOUT_ortho_4x12( \
      KC_NO, KC_NO, KC_NO,   RGB_VAI, RGB_VAD,  RGB_M_P,  RGB_M_SN, KC_NO,   KC_NO,   KC_NO,  KC_NO, KC_NO, \
      KC_NO, KC_NO, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_M_P,  RGB_M_K,  BL_TOGG, BL_INC,  BL_DEC, KC_NO, RESET, \
      KC_NO, KC_NO, KC_NO,   RGB_HUI, RGB_HUD,  RGB_M_R,  RGB_M_X,  BL_STEP, BL_BRTG, KC_NO,  KC_NO, KC_NO, \
      KC_NO, KC_NO, KC_NO,   RGB_SAI, RGB_SAD,  RGB_M_SW, RGB_M_G,  KC_TRNS, KC_NO,   KC_NO,  KC_NO, KC_NO
),

[_LAYER4] =  LAYOUT_ortho_4x12( \
  KC_TILD,         KC_EXLM,         KC_AT,    KC_LCBR,      KC_RCBR,      KC_PIPE,         KC_KP_SLASH,     KC_7,            KC_8,     KC_9,    KC_AMPR,    KC_BSLASH, \
  KC_TRANSPARENT,  KC_HASH,         KC_DLR,   KC_LPRN,      KC_RPRN,      KC_GRAVE,        KC_KP_ASTERISK,  KC_4,            KC_5,     KC_6,    KC_0,       KC_DQUO, \
  KC_TRANSPARENT,  KC_PERC,         KC_CIRC,  KC_LBRACKET,  KC_RBRACKET,  KC_TILD,         KC_PLUS,         KC_1,            KC_2,     KC_3,    KC_KP_DOT,  KC_ENTER, \
  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_LALT,  KC_LGUI,      KC_LGUI,      KC_TRANSPARENT,  KC_NO,           KC_TRANSPARENT,  KC_UNDS,  KC_DOT,  KC_TILD,    KC_TRANSPARENT
),

[_LAYER5] =  LAYOUT_ortho_4x12( \
  KC_AUDIO_MUTE,   KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT, \
  KC_TRANSPARENT,  KC_BRIGHTNESS_DOWN,  KC_BRIGHTNESS_UP, KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT, \
  KC_TRANSPARENT,  KC_F1,               KC_F2,            KC_F3,           KC_F4,           KC_F5,           KC_F6,           KC_F7,           KC_F8,           KC_F9,           KC_F10,          KC_F11, \
  KC_TRANSPARENT,  KC_TRANSPARENT,      KC_TRANSPARENT,   KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_NO,           KC_F12,          KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        rgblight_mode(1);
        set_single_persistent_default_layer(_BASE);
      }
      return false;
  }
  return true;
}
