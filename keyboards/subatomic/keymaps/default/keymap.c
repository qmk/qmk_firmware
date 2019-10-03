#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum subatomic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  BACKLIT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-------------------------------------------------------------------------------------------------.
   * |  Ins |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp | Del  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   -  | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |   =  | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   "  |Enter |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Pg Up| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Home | End  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Pg Dn| Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  | Right|   \  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_ortho_5x14_1x2uC(
    KC_TRNS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_TRNS,
    KC_TRNS, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  KC_TRNS,
    KC_TRNS, KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_TRNS,
    KC_TRNS, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  KC_TRNS,
    KC_TRNS, BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,       KC_SPC,       RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS
  ),

  /* Colemak
   * ,-------------------------------------------------------------------------------------------------.
   * |  Ins |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp | Del  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   -  | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |   [  |   ]  |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |   =  | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |   "  |Enter |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Pg Up| Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | Home | End  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Pg Dn| Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  | Right|   \  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT_ortho_5x14_1x2uC(
    KC_TRNS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_TRNS,
    KC_TRNS, KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,  KC_TRNS,
    KC_TRNS, KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_TRNS,
    KC_TRNS, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  KC_TRNS,
    KC_TRNS, BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,       KC_SPC,       RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS
  ),

  /* Dvorak
   * ,-------------------------------------------------------------------------------------------------.
   * |  Ins |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp | Del  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   [  | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |   /  |   =  |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |   ]  | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |   -  |Enter |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Pg Up| Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Home | End  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Pg Dn| Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  | Right|   \  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT_ortho_5x14_1x2uC(
    KC_TRNS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_TRNS,
    KC_TRNS, KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL,  KC_TRNS,
    KC_TRNS, KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, KC_TRNS,
    KC_TRNS, KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT,  KC_TRNS,
    KC_TRNS, BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,       KC_SPC,       RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS
  ),

  /* Lower
   * ,-------------------------------------------------------------------------------------------------.
   * |      |   ~  |  F1  |  F3  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |   _  | Tab  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   {  |   }  |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |   +  | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |      |      |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_ortho_5x14_1x2uC(
    KC_TRNS, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, KC_TRNS,
    KC_TRNS, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  KC_TRNS,
    KC_TRNS, KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
    KC_TRNS, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______,KC_TRNS,
    KC_TRNS, _______, _______, _______, _______, _______,     _______,      _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, KC_TRNS
  ),

  /* Raise
   * ,-------------------------------------------------------------------------------------------------.
   * |      |   ~  |  F1  |  F3  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   _  | Tab  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   {  |   }  |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |   +  | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |      |      |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      | Next | Vol- | Vol+ |      | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_ortho_5x14_1x2uC(
    KC_TRNS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_TRNS,
    KC_TRNS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  KC_TRNS,
    KC_TRNS, KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_TRNS,
    KC_TRNS, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, KC_TRNS,
    KC_TRNS, _______, _______, _______, _______, _______,     _______,      _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, KC_TRNS
  ),

  /* Adjust (Lower + Raise)
   * ,-------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | Reset|      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |      |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT_ortho_5x14_1x2uC(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,
    KC_TRNS, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_TRNS,
    KC_TRNS, _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______, KC_TRNS,
    KC_TRNS, _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, KC_TRNS,
    KC_TRNS, _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______, KC_TRNS
  )

};

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
      }
    return true;
};
