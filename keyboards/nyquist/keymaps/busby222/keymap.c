#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------| |-------------------------------------------
 * | GEsc |   1  |   2  |   3  |   4  |   5  | |   6  |   7   |   8  |   9  |   0  |  Bksp |
 * |------+------+------+------+------+------| |------+-------+------+------+------+-------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  | |   Y  |   U   |   I  |   O  |   P  |  Del  |
 * |------+------+------+------+------+------| |------+-------+------+------+------+-------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  | |   H  |   J   |   K  |   L  |   ;  |   "   |
 * |------+------+------+------+------+------| |------+-------+------+------+------+-------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | |   N  |   M   |   ,  |   .  |  Up  | Enter |
 * |------+------+------+------+------+------| |------+-------+------+------+------+-------|
 * | Ctrl |Adjust| GUI  | Alt  |Lower |Space | | Space |Raise |  /   | Left | Down | Right |
 * `-----------------------------------------| |-------------------------------------------|
 */

[_QWERTY] = LAYOUT( \
  KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL, \
  KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT , \
  KC_LCTL,  ADJUST,  KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT \
),

/* Lower
 * ,-----------------------------------------| |------------------------------------------.
 * |  Esc |   F1  |  F2  |  F3 |      |      | |      |   -  |   =  |   (  |   )  |  Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+-------|
 * |   ~  |   F4 |  F5  |  F6  |      |      | |      |   &  |   *  |   {  |   }  |  Del  |
 * |------+------+------+------+------+------| |------+------+------+------+------+-------|
 * | Del  |  F7  |  F8  |  F9  |      |      | |      |   _  |   +  |   [  |   ]  |   \   |
 * |------+------+------+------+------+------| |------+------+------+------+------+-------|
 * |      |  F10 |  F11 |  F12 |      |      | |      |      |      |  F5  | PgUp | Enter |
 * |------+------+------+------+------+------| |------+------+------+------+------+-------|
 * |      |      |      |      |      |      | |      |      |      | Home | PgDn |  End  |
 * `-----------------------------------------| |------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_ESC,  KC_F1,    KC_F2,    KC_F3,    _______, _______, _______, KC_MINS, KC_EQL,  KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_TILD, KC_F4,    KC_F5,    KC_F6,    _______, _______, _______, KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, KC_DEL, \
  KC_DEL,  KC_F7,    KC_F8,    KC_F9,    _______, _______, _______, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F10,   KC_F11,   KC_F12,   _______, _______, _______, _______, _______, KC_F5,   KC_PGUP,   _______, \
  _______, _______,  _______,  _______,  _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END \
),

/* Raise
 * ,-----------------------------------------| |-----------------------------------------.
 * |   `  |  m0  |  m1  |  m2  |      |      | |      |   7  |   8  |   9  |  -   | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |   `  |  sD  |  mU  |  sU  |      |      | |      |   4  |   5  |   6  |   +  |  Del |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Del  |  mL  |  mD  |  mR  |      |      | |      |   1  |   2  |   3  |   *  |  \   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |   0  |  mB1 |  mB1 |  mB2 |      | |      |   0  |   .  |   =  |   /  |Enter |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------| |----------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_GRV,  KC_MS_ACCEL0,  KC_MS_ACCEL1, KC_MS_ACCEL2, _______,    _______, _______, KC_7,    KC_8,    KC_9,    KC_MINS, KC_BSPC, \
  KC_GRV,  KC_MS_WH_DOWN, KC_MS_UP,     KC_MS_WH_UP,  _______,    _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_DEL, \
  KC_DEL,  KC_MS_LEFT,    KC_MS_DOWN,   KC_MS_RIGHT,  _______,    _______, _______, KC_1,    KC_2,    KC_3,    KC_ASTR, KC_BSLS, \
  _______, KC_P0,         KC_MS_BTN1,   KC_MS_BTN1,   KC_MS_BTN2, _______, _______, KC_0,    KC_DOT,  KC_EQL,  KC_SLSH, _______, \
  _______, _______,       _______,      _______,      _______,    _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|Sat Up|Sat Dn|Val Up|Val Dn|      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty| Raise| Lower|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  RAISE,   LOWER,  _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
// float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
// float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    // case COLEMAK:
    //   if (record->event.pressed) {
    //     #ifdef AUDIO_ENABLE
    //       PLAY_SONG(tone_colemak);
    //     #endif
    //     persistent_default_layer_set(1UL<<_COLEMAK);
    //   }
    //   return false;
    //   break;
    // case DVORAK:
    //   if (record->event.pressed) {
    //     #ifdef AUDIO_ENABLE
    //       PLAY_SONG(tone_dvorak);
    //     #endif
    //     persistent_default_layer_set(1UL<<_DVORAK);
    //   }
    //   return false;
    //   break;
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
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_ADJUST);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
