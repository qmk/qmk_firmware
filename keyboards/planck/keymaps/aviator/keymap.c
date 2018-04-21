/* Copyright 2017 John Ramsay
 * Aviator Keymap v1.0
 *
 * Designed for aeronautical data entry on the OLKB Planck.
 */

 #include "planck.h"
 #include "action_layer.h"

 extern keymap_config_t keymap_config;

 enum planck_layers {
   _QWERTY,
   _DATA,
   _LOWER,
   _RAISE,
   _ADJUST
 };

 enum planck_keycodes {
   QWERTY = SAFE_RANGE,
   DATA,
   LOWER,
   RAISE,
   BACKLIT
 };

#define _______ KC_TRNS
#define ___x___ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Data
 * ,-----------------------------------------------------------------------------------.
 * | Esc  | Home |  Up  | End  |      |      |   N  |   S  |   7  |   8  |   9  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  | Left | Down | Right|      |      |   E  |   W  |   4  |   5  |   6  | Tab  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |      |   +  |   -  |   1  |   2  |   3  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise |   0  |   .  |Shift |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_DATA] = {
  {KC_ESC,  KC_HOME, KC_UP,   KC_END,   ___x___, ___x___, KC_N,    KC_S,    KC_7, KC_8,   KC_9,    KC_BSPC},
  {KC_TAB,  KC_LEFT, KC_DOWN, KC_RIGHT, ___x___, ___x___, KC_E,    KC_W,    KC_4, KC_5,   KC_6,    KC_TAB},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V,    ___x___, KC_PLUS, KC_MINS, KC_1, KC_2,   KC_3,    KC_ENT},
  {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI,  LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_0, KC_DOT, KC_RSFT, KC_ENT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Del  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   ~  |   `  |      |      |      |      |   _  |   +  |   {  |   }  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home |Pg Dn |Pg Up | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_DEL,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {_______, KC_TILD, KC_GRV,  ___x___, ___x___, ___x___, ___x___, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS},
  {_______, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Del  |  F1  |  F2  |  F3  |  F4  |      |   N  |   S  |   7  |   8  |   9  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |   E  |   W  |   4  |   5  |   6  | Tab  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |   +  |   -  |   1  |   2  |   3  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |   0  |   .  |Shift |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   ___x___, KC_N,    KC_S,    KC_7, KC_8,   KC_9,    KC_BSPC},
  {_______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   ___x___, KC_E,    KC_W,    KC_4, KC_5,   KC_6,    KC_TAB},
  {_______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___x___, KC_PLUS, KC_MINS, KC_1, KC_2,   KC_3,    _______,},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_0, KC_DOT, KC_RSFT, KC_ENT}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Esc  | Reset| Debug|      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty| Data |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {KC_ESC,  RESET,   DEBUG,   ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, KC_DEL},
  {_______, ___x___, ___x___, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  DATA,    ___x___, ___x___, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  ___x___, ___x___, ___x___, ___x___, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        #ifdef BACKLIGHT_BREATHING
          breathing_self_disable();
        #endif
      }
      return false;
      break;
    case DATA:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DATA);
        #ifdef BACKLIGHT_BREATHING
          breathing_enable();
        #endif
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        uint8_t default_layer = biton32(default_layer_state);
        if (default_layer == _QWERTY) {
          #ifdef BACKLIGHT_BREATHING
            breathing_enable();
          #endif
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        uint8_t default_layer = biton32(default_layer_state);
        if (default_layer == _QWERTY) {
          #ifdef BACKLIGHT_BREATHING
            breathing_self_disable();
          #endif
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        uint8_t default_layer = biton32(default_layer_state);
        if (default_layer == _QWERTY) {
          #ifdef BACKLIGHT_BREATHING
            breathing_enable();
          #endif
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        uint8_t default_layer = biton32(default_layer_state);
        if (default_layer == _QWERTY) {
          #ifdef BACKLIGHT_BREATHING
            breathing_self_disable();
          #endif
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_BREATHING
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
  }
  return true;
}
