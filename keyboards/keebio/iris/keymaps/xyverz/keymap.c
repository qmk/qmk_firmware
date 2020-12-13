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

#define KC_____ KC_TRNS
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


  [_DVORAK] = LAYOUT_kc (
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSLS,
     TAB ,QUOT,COMM,DOT , P  , Y  ,                F  , G  , C  , R  , L  ,SLSH,
     ESC , A  , O  , E  , U  , I  ,                D  , H  , T  , N  , S  ,MINS,
     LSFT,SCLN, Q  , J  , K  , X  ,LOWR,     RASE, B  , M  , W  , V  , Z  ,RSFT,
                       LCTL,BSLT,LGUI,         ENT ,SPC ,LALT
  ),

  [_QWERTY] = LAYOUT_kc (
     EQL , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,MINS,
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,BSLS,
     ESC , A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
     LSFT, Z  , X  , C  , V  , B  ,LOWR,     RASE, N  , M  ,COMM,DOT ,SLSH,RSFT,
                       LCTL,BSPC,LGUI,         ENT ,SPC ,LALT
  ),

  [_COLEMAK] = LAYOUT_kc (
     EQL , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,MINS,
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,BSPC,
     ESC , A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
     LSFT, Z  , X  , C  , V  , B  ,LOWR,     RASE, K  , M  ,COMM,DOT ,SLSH,RSFT,
                       LCTL,BSPC,LGUI,         ENT ,SPC ,LALT
  ),

  [_WOW] = LAYOUT_kc (
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSLS,
     TAB ,QUOT,COMM,DOT , P  , Y  ,                F  , G  , C  , R  , L  ,SLSH,
     ESC , A  , O  , E  , U  , I  ,                D  , H  , T  , N  , S  ,MINS,
     LSFT,SCLN, Q  , J  , K  , X  ,LALT,     RGUI, B  , M  , W  , V  , Z  ,RSFT,
                       LOWR,BSPC,LCTL,         ENT ,SPC ,RASE
  ),

  [_LOWER] = LAYOUT_kc (
     F11 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F12 ,
     TILD,____,____, UP ,____,____,               ____,____,____,____,____,____,
     CAPS,____,LEFT,DOWN,RGHT,HOME,               PGUP,UNDS,PLUS,LCBR,RCBR,PIPE,
     BL_S,____,MUTE,VOLD,VOLU,END ,____,     ____,PGDN,MPRV,MPLY,MNXT,____,____,
                       ____,DEL ,____,         ____,INS ,____
  ),

  [_RAISE] = LAYOUT_kc (
     F11 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F12 ,
     GRV ,____,____, UP ,____,____,               ____,____,____,____,____,____,
     CAPS,____,LEFT,DOWN,RGHT,HOME,               PGUP,MINS,EQL ,LBRC,RBRC,BSLS,
     BL_S,____,MUTE,VOLD,VOLU,END ,____,     ____,PGDN,MPRV,MPLY,MNXT,____,____,
                       ____,DEL ,____,         ____,INS ,____
  ),

  [_ADJUST] = LAYOUT_kc (
     F11 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F12 ,
     ____,RST ,____,____,____,____,               ____,____,____,____,____,____,
     ____,____,____,____,____,____,               ____,QWRT,CLMK,DVRK,WOW ,____,
     ____,____,____,____,____,____,____,     ____,____,____,____,____,____,____,
                       ____,____,____,         ____,____,____
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