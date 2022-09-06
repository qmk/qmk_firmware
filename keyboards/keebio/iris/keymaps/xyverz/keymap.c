#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;


enum layer_names {
  _DVORAK,
  _QWERTY,
  _COLEMAK,
  _WOW,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  WOW,
  LOWER,
  RAISE,
  ADJUST
};

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_QWRT QWERTY
#define KC_CLMK COLEMAK
#define KC_DVRK DVORAK
#define KC_WOW WOW
#define KC_BSLT ALT_T(KC_BSPC)
#define ADJUST MO(_ADJUST)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_DVORAK] = LAYOUT (
     KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSLS,
     KC_TAB ,KC_QUOT,KC_COMM,KC_DOT , KC_P  , KC_Y  ,                KC_F  , KC_G  , KC_C  , KC_R  , KC_L  ,KC_SLSH,
     KC_ESC , KC_A  , KC_O  , KC_E  , KC_U  , KC_I  ,                KC_D  , KC_H  , KC_T  , KC_N  , KC_S  ,KC_MINS,
     KC_LSFT,KC_SCLN, KC_Q  , KC_J  , KC_K  , KC_X  ,KC_LOWR,     KC_RASE, KC_B  , KC_M  , KC_W  , KC_V  , KC_Z  ,KC_RSFT,
                       KC_LCTL,KC_BSLT,KC_LGUI,         KC_ENT ,KC_SPC ,KC_LALT
  ),

  [_QWERTY] = LAYOUT (
     KC_EQL , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSLS,
     KC_ESC , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_LOWR,     KC_RASE, KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,
                       KC_LCTL,KC_BSPC,KC_LGUI,         KC_ENT ,KC_SPC ,KC_LALT
  ),

  [_COLEMAK] = LAYOUT (
     KC_EQL , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,
     KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_G  ,                KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_BSPC,
     KC_ESC , KC_A  , KC_R  , KC_S  , KC_T  , KC_D  ,                KC_H  , KC_N  , KC_E  , KC_I  , KC_O  ,KC_QUOT,
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_LOWR,     KC_RASE, KC_K  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,
                       KC_LCTL,KC_BSPC,KC_LGUI,         KC_ENT ,KC_SPC ,KC_LALT
  ),

  [_WOW] = LAYOUT (
     KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSLS,
     KC_TAB ,KC_QUOT,KC_COMM,KC_DOT , KC_P  , KC_Y  ,                KC_F  , KC_G  , KC_C  , KC_R  , KC_L  ,KC_SLSH,
     KC_ESC , KC_A  , KC_O  , KC_E  , KC_U  , KC_I  ,                KC_D  , KC_H  , KC_T  , KC_N  , KC_S  ,KC_MINS,
     KC_LSFT,KC_SCLN, KC_Q  , KC_J  , KC_K  , KC_X  ,KC_LALT,     KC_RGUI, KC_B  , KC_M  , KC_W  , KC_V  , KC_Z  ,KC_RSFT,
                       KC_LOWR,KC_BSPC,KC_LCTL,         KC_ENT ,KC_SPC ,KC_RASE
  ),

  [_LOWER] = LAYOUT (
     KC_F11 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F12 ,
     KC_TILD,_______,_______, KC_UP ,_______,_______,               _______,_______,_______,_______,_______,_______,
     KC_CAPS,_______,KC_LEFT,KC_DOWN,KC_RGHT,KC_HOME,               KC_PGUP,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,
     KC_BL_S,_______,KC_MUTE,KC_VOLD,KC_VOLU,KC_END ,_______,     _______,KC_PGDN,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,
                       _______,KC_DEL ,_______,         _______,KC_INS ,_______
  ),

  [_RAISE] = LAYOUT (
     KC_F11 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F12 ,
     KC_GRV ,_______,_______, KC_UP ,_______,_______,               _______,_______,_______,_______,_______,_______,
     KC_CAPS,_______,KC_LEFT,KC_DOWN,KC_RGHT,KC_HOME,               KC_PGUP,KC_MINS,KC_EQL ,KC_LBRC,KC_RBRC,KC_BSLS,
     KC_BL_S,_______,KC_MUTE,KC_VOLD,KC_VOLU,KC_END ,_______,     _______,KC_PGDN,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,
                       _______,KC_DEL ,_______,         _______,KC_INS ,_______
  ),

  [_ADJUST] = LAYOUT (
     KC_F11 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F12 ,
     _______,KC_RST ,_______,_______,_______,_______,               _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,               _______,KC_QWRT,KC_CLMK,KC_DVRK,KC_WOW ,_______,
     _______,_______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,_______,
                       _______,_______,_______,         _______,_______,_______
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void matrix_init_user(void) {
   // This will disable the red LEDs on the ProMicros
   setPinOutput(D5);
   writePinLow(D5);
   setPinOutput(B0);
   writePinLow(B0);
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case WOW:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WOW);
      }
      return false;
  }
  return true;
}
