#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MIDI 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MIDI,
  ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------| |-------------------------------------------.
 * | GEsc |   1  |   2  |   3  |   4  |   5  | |   6  |   7   |   8  |   9  |   0  |  Bksp |
 * |------+------+------+------+------+------| |------+-------+------+------+------+-------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  | |   Y  |   U   |   I  |   O  |   P  |  Del  |
 * |------+------+------+------+------+------| |------+-------+------+------+------+-------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  | |   H  |   J   |   K  |   L  |   ;  |   "   |
 * |------+------+------+------+------+------| |------+-------+------+------+------+-------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | |   N  |   M   |   ,  |   .  |   /  | Enter |
 * |------+------+------+------+------+------| |------+-------+------+------+------+-------|
 * | Ctrl |Adjust| GUI  | Alt  |Lower |Space | | Space |Raise | Left |  Up  | Down | Right |
 * `-----------------------------------------| |-------------------------------------------|
 */

[_QWERTY] = LAYOUT( \
  QK_GESC,  KC_1,        KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,        KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL, \
  KC_RCTL,  KC_A,        KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,        KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  KC_LCTL,  MO(_ADJUST), KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT \
),

/* Lower
 * ,-----------------------------------------| |------------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |      |      | |   -  |   =  |   (  |   )  |      |  Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+-------|
 * |   ~  |  F4  |  F5  |  F6  |      |      | |   &  |   *  |   {  |   }  |      |  Del  |
 * |------+------+------+------+------+------| |------+------+------+------+------+-------|
 * | Del  |  F7  |  F8  |  F9  |      |      | |   _  |   +  |   [  |   ]  |      |   \   |
 * |------+------+------+------+------+------| |------+------+------+------+------+-------|
 * |      |  F10 |  F11 |  F12 |      |      | |      |      |      |  F5  |  Up  | Enter |
 * |------+------+------+------+------+------| |------+------+------+------+------+-------|
 * |      |      |      |      |      | Home | | End  |      |      | Left | Down | Right |
 * `-----------------------------------------| |------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_GRV,  KC_F1,    KC_F2,    KC_F3,    _______, _______, KC_MINS, KC_EQL,  _______, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_TILD, KC_F4,    KC_F5,    KC_F6,    _______, _______, KC_AMPR, KC_ASTR, _______, KC_LCBR, KC_RCBR, KC_DEL, \
  KC_DEL,  KC_F7,    KC_F8,    KC_F9,    _______, _______, KC_UNDS, KC_PLUS, _______, KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F10,   KC_F11,   KC_F12,   _______, _______, _______, _______, _______, KC_F5,   KC_UP,   _______, \
  _______, _______,  _______,  _______,  _______, KC_HOME, KC_END,  _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT \
),

/* Raise
 * ,-----------------------------------------| |-----------------------------------------.
 * | Back |  m0  |  m1  |  m2  |      |      | |      |   7  |   8  |   9  |  -   | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | For  |  sD  |  mU  |  sU  |      |      | |      |   4  |   5  |   6  |   +  |  Del |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Del  |  mL  |  mD  |  mR  |      |      | |      |   1  |   2  |   3  |   *  |  \   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |   0  |  mB1 |  mB1 |  mB2 |      | |      |   0  |   .  |   =  |   /  |Enter |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | MIDI |      |      |      |      |      | |      |      | Mute | Vol- | Vol+ | Play |
 * `-----------------------------------------| |-----------------------------------------'
 */
[_RAISE] = LAYOUT( \
  LALT(KC_LEFT),  KC_MS_ACCEL0,  KC_MS_ACCEL1, KC_MS_ACCEL2, _______,    _______, _______, KC_7,    KC_8,    KC_9,    KC_MINS, KC_BSPC, \
  LALT(KC_RIGHT), KC_MS_WH_DOWN, KC_MS_UP,     KC_MS_WH_UP,  _______,    _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_DEL, \
  KC_DEL,         KC_MS_LEFT,    KC_MS_DOWN,   KC_MS_RIGHT,  _______,    _______, _______, KC_1,    KC_2,    KC_3,    KC_ASTR, KC_BSLS, \
  _______,        KC_P0,         KC_MS_BTN1,   KC_MS_BTN1,   KC_MS_BTN2, _______, _______, KC_0,    KC_DOT,  KC_EQL,  KC_SLSH, _______, \
  MO(_MIDI),      _______,       _______,      _______,      _______,    _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY \
),

/*
 * MIDI
 */

[_MIDI] = LAYOUT( \
  QWERTY,   MI_C,    MI_D,    MI_E,    MI_F,    MI_G,    MI_A,    MI_B,    MI_C1,   MI_C2,   MI_C3,   QWERTY, \
  MI_A3,    MI_As3,  MI_B3,   MI_C3,   MI_Cs3,  MI_D3,   MI_Ds3,  MI_E3,   MI_F3,   MI_Fs3,  MI_G3,   MI_Gs3, \
  MI_A2,    MI_As2,  MI_B2,   MI_C2,   MI_Cs2,  MI_D2,   MI_Ds2,  MI_E2,   MI_F2,   MI_Fs2,  MI_G2,   MI_Gs2, \
  MI_A1,    MI_As1,  MI_B1,   MI_C1,   MI_Cs1,  MI_D1,   MI_Ds1,  MI_E1,   MI_F1,   MI_Fs1,  MI_G1,   MI_Gs1, \
  MI_A,     MI_As,   MI_B,    MI_C,    MI_Cs,   MI_D,    MI_Ds,   MI_E,    MI_F,    MI_Fs,   MI_G,    MI_Gs \
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------| |-----------------------------------------.
 * |QWERTY|  F2  |  F3  |  F4  |  F5  |  F6  | |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn| |Sat Up|  7   |  8   |  9   |      |  Del |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm| |AGswap|  6   |  5   |  4   |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |   [  | |   ]  |  1   |  2   |  3   |      |      |
 * |------+------+------+------+------+------+ |------+------+------+------+------+------|
 * |      |      |      |      |      |   {  | |   }  |  0   |  .   |      |      |      |
 * `-----------------------------------------| |-----------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
  QWERTY,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  _______, QK_BOOT, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, KC_7,    KC_8,    KC_9,    _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, KC_6,    KC_5,    KC_4,    _______, _______, \
  _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_1,    KC_2,    KC_3,    _______, _______, \
  _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, KC_0,    KC_DOT,  _______, _______, _______ \
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(1UL<<_QWERTY);
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
  }
  return true;
}
