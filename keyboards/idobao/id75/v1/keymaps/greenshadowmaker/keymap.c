#include QMK_KEYBOARD_H

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
};

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | =      |        | -      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      |        |        | [      | Y      | U      | I      | O      | P      | ]      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | RAISE  | A      | S      | D      | F      | G      |        | UP     | PrtScr | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | LEFT   | DOWN   | RIGHT  | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | `      | \      | LALT   | LCTRL  | LOWER  | SPACE  | LGUI   | DEL    | ENTER  | SPACE  | RAISE  |  LEFT  |  DOWN  |  UP    | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_5x15( 
    KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_EQL,  XXXXXXX,   KC_MINS,   KC_6,    KC_7,    KC_8,       KC_9,     KC_0, KC_BSPC,  
    KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, XXXXXXX,   KC_LBRC,   KC_Y,    KC_U,    KC_I,       KC_O,     KC_P, KC_RBRC,  
     RAISE,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX,   KC_UP,   KC_PSCR,   KC_H,    KC_J,    KC_K,       KC_L,  KC_SCLN, KC_QUOT, 
   KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LEFT, KC_DOWN,   KC_RGHT,   KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, 
  KC_GRAVE,  KC_BSLS, KC_LALT, KC_LCTL,   LOWER,  KC_SPC,    KC_LGUI,  KC_DEL,    KC_ENT, KC_SPC,   RAISE,    KC_LEFT,  KC_DOWN,   KC_UP, KC_RGHT  
),


/* LOWER
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     |        |        |        | F6     | F7     | F8     | F9     | F10    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |  UP    |        |        |        |        |        |        |        |        |        | PR SCR |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RAISE  | LEFT   |  DOWN  |  RIGHT |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        | LOWER  |        |  APP   |        |        |        |  RAISE |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_5x15( 
    XXXXXXX,   KC_F1,   KC_F2,   KC_F3, XXXXXXX,   KC_F5, XXXXXXX, XXXXXXX, XXXXXXX,    KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,  
    XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
      RAISE, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   LOWER, XXXXXXX,  KC_APP, XXXXXXX, XXXXXXX,  XXXXXXX,   RAISE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  
),

 /* RAISE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |  pgup  |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RAISE  | home   |  pgdn  | end    |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        | LOWER  |        |        |        |        |        |  RAISE |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_5x15( 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
    XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
      RAISE, KC_HOME, KC_PGDN,  KC_END, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   LOWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   RAISE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  
),


 /* ADJUST
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | QK_BOOT  |        |        |        |        |        |        |        |        |rgbplain|rgbtest | rgbmode|        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |rgb tog | bl_tog |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RAISE  |        | rgb hi | rgb sai|rgb vai | bl inc |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | EEP Rst|        | rgb hd | rgb sad|rgb vad | bl dec |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        | LOWER  |        |        |        |        |        |  RAISE |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_5x15( 
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  RGB_M_P, RGB_M_T, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX,  
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, BL_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
    RAISE, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI,  BL_UP,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  EE_CLR,  XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD,  BL_DOWN,XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   LOWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   RAISE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  
),


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
  }
  return true;
}
