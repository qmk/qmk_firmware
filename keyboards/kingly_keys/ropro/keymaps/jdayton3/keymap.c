/* Copyright 2019 Jonathan Dayton (jdayton3)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layer_names {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _PLOVER,
    _ADJUST
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY
   *        ,-----------------------------------------------------------------------------------.
   *        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   *        |------+------+------+------+------+------+------+------+------+------+------+------|
   *        | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
   *        |------+------+------+------+------+------+------+------+------+------+------+------|
   *  RotEn | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * ,------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgUp | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------|
   * | Home | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgDn | Brite| Ctrl | ALT  | GUI  |Lower |SPACE |SPACE |Raise | Left | Down |  Up  |Right |
   * `------------------------------------------------------------------------------------------'
   */
  	[_QWERTY] = LAYOUT(
              KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
              KC_ESC,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,      KC_0,    KC_MINUS,
    KC_NO,    KC_TAB,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_BSPC,
    KC_PGUP,  KC_ESC,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,      KC_SCLN,  KC_QUOT,
    KC_HOME,  KC_LSFT,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,   KC_ENT,
    KC_PGDN,  RGB_TOG,   KC_RCTL,  KC_LALT,  KC_LGUI,  LOWER,    KC_SPC,   KC_SPC,   RAISE,    KC_LEFT,  KC_DOWN,   KC_UP,    KC_RGHT
  ),

  /* Colemak
   *        ,-----------------------------------------------------------------------------------.
   *        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   *        |------+------+------+------+------+------+------+------+------+------+------+------|
   *        | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
   *        |-----------------------------------------------------------------------------------|
   *  RotEn | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
   * ,------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgUp | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | Home | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgDn | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
   * `------------------------------------------------------------------------------------------'
   */
  	[_COLEMAK] = LAYOUT(
              KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
              KC_ESC,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,      KC_0,    KC_MINUS,
    KC_NO,    KC_TAB,    KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,      KC_SCLN,   KC_ESC,
    KC_PGUP,  KC_BSPC,   KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I,      KC_O,     KC_QUOT,
    KC_HOME,  KC_LSFT,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,   KC_ENT,
    KC_PGDN,  RGB_TOG,   KC_RCTL,  KC_LALT,  KC_LGUI,  LOWER,    KC_SPC,   KC_SPC,   RAISE,    KC_LEFT,  KC_DOWN,   KC_UP,    KC_RGHT
  ),

  /* Dvorak
   *        ,-----------------------------------------------------------------------------------.
   *        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   *        |------+------+------+------+------+------+------+------+------+------+------+------|
   *        | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
   *        |-----------------------------------------------------------------------------------.
   *  RotEn | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
   * ,------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgUp | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | Home | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgDn | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
   * `------------------------------------------------------------------------------------------'
   */
  	[_DVORAK] = LAYOUT(
              KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
              KC_ESC,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,      KC_0,    KC_MINUS,
    KC_NO,    KC_TAB,    KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,     KC_Y,     KC_F,     KC_G,     KC_C,     KC_R,      KC_L,     KC_BSPC,
    KC_PGUP,  KC_ESC,    KC_A,     KC_O,     KC_E,     KC_U,     KC_I,     KC_D,     KC_H,     KC_T,     KC_N,      KC_S,     KC_SLSH,
    KC_HOME,  KC_LSFT,   KC_SCLN,  KC_Q,     KC_J,     KC_K,     KC_X,     KC_B,     KC_M,     KC_W,     KC_V,      KC_Z,      KC_ENT,
    KC_PGDN,  RGB_TOG,   KC_RCTL,  KC_LALT,  KC_LGUI,  LOWER,    KC_SPC,   KC_SPC,   RAISE,    KC_LEFT,  KC_DOWN,   KC_UP,    KC_RGHT
  ),

  /* LOWER
   *        ,-----------------------------------------------------------------------------------.
   *        |TOGRGB|      |      |      |Sat(-)|Hue(-)|Hue(+)|Sat(+)|      |      |Brght-|Brght+|
   *        |------+------+------+------+------+-------------+------+------+------+------+------|
   *        |  `   |      |      |      |      |      |      |      |      |      |      |   =  |
   *        |-----------------------------------------------------------------------------------.
   *  RotEn |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
   * ,------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Home | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | End  |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
   * `------------------------------------------------------------------------------------------'
   */
    [_LOWER] = LAYOUT(
              RGB_TOG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_SAD,  RGB_HUD,  RGB_HUI,  RGB_SAI,    KC_TRNS,    KC_TRNS,  RGB_VAD,  RGB_VAI,
              KC_GRAVE, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS, KC_EQUAL,
    KC_NUM,   KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,    KC_ASTR,    KC_LPRN,  KC_RPRN,  KC_BSPC,
    KC_HOME,  KC_DEL,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_UNDS,    KC_PLUS,    KC_LCBR,  KC_RCBR,  KC_PIPE,
    KC_TRNS,  _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   S(KC_NUHS), S(KC_NUBS), KC_HOME,  KC_END,   _______,
    KC_END,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    KC_MNXT,    KC_VOLD,  KC_VOLU,  KC_MPLY
  ),

  /* RAISE
   *        ,-----------------------------------------------------------------------------------.
   *        |TOGRGB|      |      |      |Sat(-)|Hue(-)|Hue(+)|Sat(+)|      |      |Brght-|Brght+|
   *        |------+------+------+------+------+-------------+------+------+------+------+------|
   *        |  `   |      |      |      |      |      |      |      |      |      |      |   =  |
   *        |-----------------------------------------------------------------------------------.
   *  RotEn |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
   * ,------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Home | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | End  |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
   * `------------------------------------------------------------------------------------------'
   */
    [_RAISE] = LAYOUT(
              RGB_TOG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_SAD,  RGB_HUD,  RGB_HUI,  RGB_SAI,  KC_TRNS,  KC_TRNS,  RGB_VAD,  RGB_VAI,
              KC_GRAVE, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_EQUAL,
    KC_NUM,   KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
    KC_HOME,  KC_DEL,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
    KC_TRNS,  _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_NUHS,  KC_NUBS,  KC_PGUP,  KC_PGDN,  _______,
    KC_END,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MPLY
  ),

  /* Plover layer (http://opensteno.org)
   *        ,-----------------------------------------------------------------------------------.
   *        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   *        |------+------+------+------+------+------+------+------+------+------+------+------|
   *        | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
   *        |-----------------------------------------------------------------------------------.
   *  RotEn |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
   * ,------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgUp |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | Home |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgDn | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
   * `------------------------------------------------------------------------------------------'
   */
  	[_PLOVER] = LAYOUT(
              KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
              KC_ESC,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,      KC_0,    KC_MINUS,
    KC_NO,    KC_1,      KC_1,     KC_1,     KC_1,     KC_1,     KC_1,     KC_1,     KC_1,     KC_1,     KC_1,      KC_1,     KC_1   ,
    KC_PGUP,  XXXXXXX,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_LBRC,
    KC_HOME,  XXXXXXX,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,      KC_SCLN,  KC_QUOT,
    KC_PGDN,  EXT_PLV,   XXXXXXX,  XXXXXXX,  KC_C,     KC_V,     XXXXXXX,  XXXXXXX,  KC_N,     KC_M,     XXXXXXX,   XXXXXXX,  XXXXXXX
  ),

  /* Adjust (Lower + Raise)
   *        ,-----------------------------------------------------------------------------------.
   *        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   *        |------+------+------+------+------+------+------+------+------+------+------+------|
   *        | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
   *        |-----------------------------------------------------------------------------------.
   *  RotEn |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
   * ,------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgUp |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | Home |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgDn |      |      |      |      |      |             |      |      |      |      |      |
   * `------------------------------------------------------------------------------------------'
   */
  	[_ADJUST] = LAYOUT(
              KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
              KC_ESC,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,      KC_0,    KC_MINUS,
    KC_NO,    _______,   QK_BOOT,  DB_TOGG,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,   RGB_VAD,  KC_DEL ,
    KC_PGUP,  _______,   _______,  MU_NEXT,  AU_ON,    AU_OFF,   AG_NORM,  AG_SWAP,  QWERTY,   COLEMAK,  DVORAK,    PLOVER,   _______,
    KC_HOME,  _______,   AU_PREV,  AU_NEXT,  MU_ON,    MU_OFF,   MI_ON,    MI_OFF,   _______,  _______,  _______,   _______,  _______,
    KC_PGDN,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_WH_L);
        } else {
            tap_code(KC_WH_R);
        }
    }
    return true;
}


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}
