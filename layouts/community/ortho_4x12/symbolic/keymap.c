#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY  0
#define _LOWER   1
#define _RAISE   2
#define _NEUTRAL 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  L_LOWER,
  R_LOWER,
  L_RAISE,
  R_RAISE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------------------------------------------------------------------------------------.
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * | Esc  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |LCTL_T|      |      |      |      |      ||      |      |      |      |      |      |
 * | Tab  |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * |Shift |   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   !  |Shift |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * |LRaise| Alt  | GUI  |      |LLower|Space ||Space |RLower|      | GUI  | Del  |RRaise|
 * `------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_ESC,         KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC, \
  LCTL_T(KC_TAB), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_ENT,  \
  KC_LSFT,        KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_EXLM,  KC_RSFT, \
  L_RAISE,        KC_LALT,  KC_LGUI,  XXXXXXX,  L_LOWER,  KC_SPC,   KC_SPC,   R_LOWER,  XXXXXXX,  KC_RGUI,  KC_DEL,   R_RAISE  \
),

/* Raise
 * ,------------------------------------------------------------------------------------.
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * | Esc  |      |   &  |   {  |   }  |   %  ||   \  |   [  |   ]  |   #  |      | Bksp |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |LCTL_T|      |      |      |      |      ||      |      |      |      |      |      |
 * | Tab  |   ~  |   |  |   (  |   )  |   *  ||   /  |   <  |   >  |   '  |   :  |Enter |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * |Shift |   `  |   ^  |   @  |   $  |   +  ||   -  |   =  |   _  |   "  |   ?  |Shift |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * |LRaise| Alt  | GUI  |      |LLower|Space ||Space |RLower|      | GUI  | Del  |RRaise|
 * `------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  _______,  XXXXXXX,  KC_AMPR,  KC_LCBR,  KC_RCBR,  KC_PERC,  KC_BSLS,  KC_LBRC,  KC_RBRC,  KC_HASH,  XXXXXXX,  _______, \
  _______,  KC_TILD,  KC_PIPE,  KC_LPRN,  KC_RPRN,  KC_ASTR,  KC_SLSH,  KC_LABK,  KC_RABK,  KC_DQUO,  KC_COLN,  _______, \
  _______,  KC_GRV,   KC_CIRC,  KC_AT,    KC_DLR,   KC_PLUS,  KC_MINS,  KC_EQL,   KC_UNDS,  KC_QUOT,  KC_QUES,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  \
),
/* Lower
 * ,------------------------------------------------------------------------------------.
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * | Esc  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |LCTL_T|      |      |      |      |      ||      |      |      |      |      |      |
 * | Tab  |      |VolDn |VolUp | Mute |      || Left | Down |  Up  |Right |      |Enter |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * |Shift |      |      |      |      | PrSc || Home | PgDn | PgUp | End  |      |Shift |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * |LRaise| Alt  | GUI  |      |LLower|Space ||Space |RLower|      | GUI  | Del  |RRaise|
 * `------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______, \
  _______,  XXXXXXX,  KC_VOLD,  KC_VOLU,  KC_MUTE,  XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  _______, \
  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PSCR,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   XXXXXXX,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  \
),

/* Neutral
 * ,------------------------------------------------------------------------------------.
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * | Esc  |  F1  |  F2  |  F3  |  F4  |      ||   +  |   -  |   1  |   2  |   3  | Bksp |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |LCTL_T|      |      |      |      |      ||      |      |      |      |      |      |
 * | Tab  |  F5  |  F6  |  F7  |  F8  |      ||   *  |   /  |   4  |   5  |   6  |Enter |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * |Shift |  F9  |  F10 |  F11 |  F12 |      ||   .  |   ,  |   7  |   8  |   9  |Shift |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |
 * |LRaise| Alt  | GUI  |Reset |LLower|Space ||Space |RLower|Reset |   0  | Del  |RRaise|
 * `------------------------------------------------------------------------------------'
 */
[_NEUTRAL] = LAYOUT_ortho_4x12( \
  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    XXXXXXX,  KC_PPLS,  KC_PMNS,  KC_P1,    KC_P2,    KC_P3,     _______, \
  _______,  KC_F5,    KC_F6,    KC_F7,    KC_F8,    XXXXXXX,  KC_PAST,  KC_PSLS,  KC_P4,    KC_P5,    KC_P6,     _______, \
  _______,  KC_F9,    KC_F10,   KC_F11,   KC_F12,   XXXXXXX,  KC_PDOT,  KC_COMM,  KC_P7,    KC_P8,    KC_P9,     _______, \
  _______,  _______,  _______,  QK_BOOT,  _______,  _______,  _______,  _______,  QK_BOOT,  KC_P0,    _______,   _______  \
)


};



/****  Raise Layer functions *****/

  /* RaisePressed function */
    /* called RaiseSwitch  */
void RaisePressed ( keyevent_t *event, bool brother_state ){ 
  
  if( brother_state ) { return; }

  layer_on( _RAISE );
  update_tri_layer( _LOWER, _RAISE, _NEUTRAL );
  return;

}


  /* RaiseReleased function */
    /* called RaiseSwitch   */
void RaiseReleased ( bool brother_state ){ 
  
  if( brother_state ) { return; }

  layer_off( _RAISE );
  update_tri_layer( _LOWER, _RAISE, _NEUTRAL );
  return;
}


  /* RaiseSwitch function         */
    /* called process_record_user */
bool RaiseSwitch ( keyrecord_t *record, bool *key_state, bool brother ){ 

  if( record -> event.pressed ) {
    *key_state = true;
    RaisePressed( &(record -> event), brother );
  } else {
    *key_state = false;
    RaiseReleased( brother );
  }
  return false;

}






/**** Lower layer functions ****/

  /* LowerPressed function   */
    /* call from LowerSwitch */
void LowerPressed ( bool brother_state ){

  if( brother_state ) { return; }

  layer_on( _LOWER );
  update_tri_layer(_LOWER, _RAISE, _NEUTRAL );
  return;
}

  /* LowerReleased function  */
    /* call from LowerSwitch */
void LowerReleased ( bool brother_state ){ 

  if( brother_state ) { return; }

  layer_off( _LOWER );
  update_tri_layer(_LOWER, _RAISE, _NEUTRAL );
  return ;
}

  /* LowerSwitch function            */
    /* call from process_record_user */
bool LowerSwitch ( keyrecord_t *record, bool *key_state, bool brother ){ 
  if ( record -> event.pressed ) {
    *key_state = true;
    LowerPressed( brother );
  } else {
    *key_state = false;
    LowerReleased( brother );
  }

  return false;

}



/**** process_record_user ****/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  static bool l_lower = false;
  static bool r_lower = false;

  static bool l_raise = false;
  static bool r_raise = false;

  switch (keycode) {


    case L_LOWER : return LowerSwitch( record, &l_lower, r_lower ); break;
    case R_LOWER : return LowerSwitch( record, &r_lower, l_lower ); break;
    case L_RAISE : return RaiseSwitch( record, &l_raise, r_raise ); break;
    case R_RAISE : return RaiseSwitch( record, &r_raise, l_raise ); break;

    default: break;

  }
  return true;
}



