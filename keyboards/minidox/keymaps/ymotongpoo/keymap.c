#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _EUCALYN 1
#define _LOWER 2
#define _RAISE 3
#define _FUNC  4
#define _ADJUST 16

#define CTL_A       CTL_T(KC_A)
#define CTL_SCLN    CTL_T(KC_SCLN)
#define SFT_Z       LSFT_T(KC_Z)
#define ALT_X       ALT_T(KC_X)
#define ALT_N       ALGR_T(KC_N)
#define CTL_M       RCTL_T(KC_M)
#define CTL_N       RCTL_T(KC_N)
#define SFT_SLSH    RSFT_T(KC_SLSH)
#define SFT_ENT     RSFT_T(KC_ENT)
#define SFTSPC      LSFT(KC_SPC)
#define FN_K        LT(FUNC, KC_K)
#define KC_DQOT     LSFT(KC_QUOT)
// Defines for task manager and such
#define CALTDEL     LCTL(LALT(KC_DEL))
#define TSKMGR      LCTL(LSFT(KC_ESC))

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EUCALYN,
  LOWER,
  RAISE,
  FUNC,
  ADJUST,
};

enum minidox_layers {
  LQWERTY,
  LEUCALYN,
  LLOWER,
  LRAISE,
  LFUNC,
  LADJUST,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Qwerty
[_QWERTY] = LAYOUT_split_3x5_3( \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   CTL_A,   KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    FN_K,    KC_L,    CTL_SCLN, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   SFT_Z,   KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  SFT_SLSH, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
                     KC_LGUI, RAISE,   LOWER,          KC_ENT,  KC_SPC,  KC_LALT                    \
),

// Eucalyn
[_EUCALYN] = LAYOUT_split_3x5_3( \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   KC_Q,    KC_W,    KC_COMM, KC_DOT,  KC_SLSH,        KC_M,    KC_R,    KC_D,    KC_Y,    KC_P,    \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   CTL_A,   KC_O,    KC_E,    KC_I,    KC_U,           KC_G,    KC_T,    FN_K,    KC_S,    CTL_N,   \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   SFT_Z,   KC_X,    KC_C,    KC_V,    KC_F,           KC_B,    KC_H,    KC_J,    KC_L,    SFT_SLSH, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
                     KC_LGUI, RAISE,   LOWER,          KC_ENT,  KC_SPC,  KC_LALT                    \
),


// Lower
[_LOWER] = LAYOUT_split_3x5_3( \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   _______, _______, KC_QUOT, KC_DQOT, KC_TAB,         KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   _______, _______, _______, _______, _______,        KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
                     _______, _______, _______,        KC_GRV,  KC_TILD, _______                    \
),

// Raise
[_RAISE] = LAYOUT_split_3x5_3( \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
                     _______, _______, _______,        KC_BSPC, KC_DEL,  _______                    \
),

// FUNC
[_FUNC] = LAYOUT_split_3x5_3( \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   KC_F11,  KC_F12,  _______, _______, _______,        _______, _______, _______, _______, _______, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
                     _______, _______, _______,        _______, _______, _______                    \
),

// Adjust (Lower + Raise)
[_ADJUST] =  LAYOUT_split_3x5_3( \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   _______, _______, _______, _______, _______,        QWERTY,  EUCALYN, _______, _______, _______, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   _______, _______, _______, _______, _______,        _______, _______, _______, TSKMGR,  CALTDEL, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
   RESET,   _______, _______, _______, _______,        _______, _______, _______, _______, _______, \
//+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+
                     _______, _______, _______,        _______, _______, _______                    \
)
};

const rgblight_segment_t PROGMEM rgb_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM rgb_eucalyn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM rgb_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM rgb_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_AZURE}
);

const rgblight_segment_t PROGMEM rgb_func_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_TEAL}
);

const rgblight_segment_t PROGMEM rgb_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_CYAN}
);

const rgblight_segment_t PROGMEM rgb_green_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GREEN}
);

const rgblight_segment_t PROGMEM rgb_red_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_RED}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_qwerty_layer,
    rgb_eucalyn_layer,
    rgb_lower_layer,
    rgb_raise_layer,
    rgb_func_layer,
    rgb_adjust_layer,
    rgb_green_layer,
    rgb_red_layer
);

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_orange();
    rgblight_layers = rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, LQWERTY));
    rgblight_set_layer_state(1, layer_state_cmp(state, LEUCALYN));
    rgblight_set_layer_state(2, layer_state_cmp(state, LLOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, LRAISE));
    rgblight_set_layer_state(4, layer_state_cmp(state, LFUNC));
    rgblight_set_layer_state(5, layer_state_cmp(state, LADJUST));
    return state;
}

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_EUCALYN);
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
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
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
