


#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3



enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};





// increase readability 
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Default Layer
     * ,-----------------------------------------------------------.
     * | Esc|  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P | BS |
     * |-----------------------------------------------------------|
     * | Tab |  A |  S |  D |  F |  G |  H |  J |  K |  L | Ent    |
     * |-----------------------------------------------------------|
     * | LSft   |  Z |  X |  C |  V |  B |  N |  M |  ,  |  . | /? |
     * |-----------------------------------------------------------|
     * | LCtl | LGui| LAlt|  spc fn0  |  spc fn1    |fn2|RAlt|RCtl |
     * `-----------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT( \
        KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,   KC_BSPC,\
        KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_ENT,\
        KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,\
        KC_LCTL, KC_LGUI, KC_LALT,          F(0),           F(1),        F(2), KC_RALT, KC_RCTL \
		),

    /* Function Layer 1 HHKB style
     * ,-----------------------------------------------------------.
     * |   ~  |   !   |  @  | # | $ | % | ^ | & | * | ( | ) | Bkspc|
     * |-----------------------------------------------------------|
     * |   F1   | F2 | F3 | F4 | F5 |  F6 | _ | + | [ | ] |  Pipe  |
     * |-----------------------------------------------------------|
     * |    F7    | F8 | F9 |  F10  |  F11 |  F12 | End|PgDn| ↓ |     |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             | Stop| App|     |
     * `-----------------------------------------------------------'
     */
    [_LOWER] = LAYOUT( \
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
		KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),BL_TOGG, BL_INC, BL_DEC, \
		_______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT \
		),
	
	/* Function Layer 1 HHKB style
     * ,-----------------------------------------------------------.
     * |Caps|    |MSel| ⏮ | ⏯ | ⏭ |PSCR|SkLk|Paus|  ↑ | Ins| Del|
     * |-----------------------------------------------------------|
     * |      | 🔇 | ⏏ |    |  * |  / |Hone|PgUp|  ← |  → |       |
     * |-----------------------------------------------------------|
     * |        | 🔉 | 🔊 |    |  + |  - | End|PgDn| ↓ |     |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             | Stop| App|     |
     * `-----------------------------------------------------------'
     */
    [_RAISE] = LAYOUT( \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
		KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, KC_DEL, \
		_______, KC_TRNS, _______, KC_TRNS, KC_TRNS, _______, _______, RGB_TOG \
		),
	
	/* Function Layer 1 HHKB style
     * ,-----------------------------------------------------------.
     * |Caps|    |MSel| ⏮ | ⏯ | ⏭ |PSCR|SkLk|Paus|  ↑ | Ins| Del|
     * |-----------------------------------------------------------|
     * |      | 🔇 | ⏏ |    |  * |  / |Hone|PgUp|  ← |  → |       |
     * |-----------------------------------------------------------|
     * |        | 🔉 | 🔊 |    |  + |  - | End|PgDn| ↓ |     |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             | Stop| App|     |
     * `-----------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT( \
        _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
		_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______,  _______,  \
		_______, _______, _______, RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD, \
		KC_SYSTEM_SLEEP, _______, _______, _______, _______, _______, _______, _______ \
		),

    

};


		

enum function_id {
    LAUNCH,
    RGBLED_TOGGLE,
};

const uint16_t PROGMEM fn_actions[] = {
	[0]  = ACTION_LAYER_TAP_KEY(_LOWER, KC_SPC),
	[1]  = ACTION_LAYER_TAP_KEY(_RAISE, KC_SPC),
	[2]  = ACTION_LAYER_TAP_KEY(_ADJUST, KC_LGUI),

};




const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
   
    return MACRO_NONE;
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
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
