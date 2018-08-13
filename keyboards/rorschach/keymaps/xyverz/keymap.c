#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layer Definitions
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Aliases to keep the keymap tidy
#define GUIBSPC GUI_T(KC_BSPC) // GUI when held, BSPC when tapped.
#define RGB_SWR RGB_M_SW // Swirl Animation alias
#define RGB_SNK RGB_M_SN // Snake Animation alias

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,\
  KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC,                   KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT \
                                               KC_LGUI, KC_HOME, KC_END,  KC_ENT
),

[_COLEMAK] = LAYOUT_ortho_4x12 ( \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   GUIBSPC,                   KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT \
                                               KC_LGUI, KC_HOME, KC_END,  KC_ENT
),

[_DVORAK] = LAYOUT_ortho_4x12 ( \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
  KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   GUIBSPC,                   KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT \
                                               KC_LGUI, KC_HOME, KC_END,  KC_ENT
),


[_LOWER] = LAYOUT_ortho_4x12 ( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
  KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                   _______, _______, _______, _______, _______, _______, \
  BL_STEP, _______, KC_HOME, KC_END,  _______, KC_DEL,                    KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______ \
                                               _______, _______, _______, _______
),

[_RAISE] = LAYOUT_ortho_4x12 ( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                   _______, _______, _______, _______, _______, _______, \
  BL_STEP, _______, KC_HOME, KC_END,  _______, KC_DEL,                    KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______ \
                                               _______, _______, _______, _______
),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
#ifdef BOOTLOADER_CATERINA
   // This will disable the red LEDs on the ProMicros
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);
   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
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
/*    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break; */
  }
  return true;
}
