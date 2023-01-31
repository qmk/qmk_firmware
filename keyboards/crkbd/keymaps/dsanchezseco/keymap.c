#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ESC_CTL LCTL_T(KC_ESC)

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum crkbd_layers {
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------.          ,-----------------------------------------------.
     KC_TAB, KC_QUOT,KC_COMM, KC_DOT, KC_P,   KC_Y,              KC_F,   KC_G,   KC_C,   KC_R,   KC_L,  KC_SLSH,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     ESC_CTL, KC_A,   KC_O,   KC_E,   KC_U,   KC_I,              KC_D,   KC_H,   KC_T,   KC_N,   KC_S, KC_MINUS,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_LSFT,KC_SCLN, KC_Q,   KC_J,   KC_K,   KC_X,              KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,SC_SENT,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                KC_LGUI, LOWER, KC_SPC,    KC_BSPC, RAISE,KC_RALT \
                             //`-----------------------'  `----------------------'
  ),


  [_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------.          ,-----------------------------------------------.
     KC_TILD,KC_EXLM, KC_AT, KC_HASH, KC_DLR,KC_PERC,           KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RIGHT,KC_RPRN,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     _______,KC_VOLD,KC_VOLU,KC_MPRV,KC_MPLY,KC_MNXT,           _______,KC_LEFT,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     _______,_______,_______,KC_DOWN, KC_UP, _______,           _______,_______,_______,KC_HOME, KC_END,_______,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                _______,_______,_______,   KC_DEL,_______,_______ \
                             //`-----------------------'  `----------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------.          ,-----------------------------------------------.
     KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,  KC_5,              KC_6,    KC_7,  KC_8,    KC_9,KC_RIGHT,  KC_0, \
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,_______,_______,           _______,KC_LEFT, KC_EQL,KC_LBRC,KC_RBRC,KC_BSLS,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     _______,_______,_______,KC_DOWN, KC_UP, _______,           _______,_______,_______,KC_PGUP,KC_PGDN,_______,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                _______,_______,_______,   KC_DEL ,_______,_______ \
                             //`-----------------------'  `----------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------.          ,-----------------------------------------------.
     RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,_______,RGB_M_T,          _______,_______,_______,_______,KC_RIGHT,_______,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,_______,_______,           _______,KC_LEFT,_______,_______,_______,_______,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     _______,KC_PSCR,_______,KC_DOWN, KC_UP, _______,           _______,_______,_______,_______,_______,_______,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                _______,_______,_______,   KC_DEL ,_______,_______ \
                             //`-----------------------'  `----------------------'
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_left())
    return OLED_ROTATION_180;  // flips the display 180 to see it from my side
  return rotation;
}

const char *read_logo(void);
bool oled_task_user(void){
    switch (get_highest_layer(layer_state)){
        case _DVORAK:
            oled_write_ln_P(PSTR("DVRK"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("RAISE"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("ADJST"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?????"), false);
    }
  //now print logo
  oled_write(read_logo(), false);
    return false;
}
#endif
