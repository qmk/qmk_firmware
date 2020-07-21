//nobs keymap

#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include "action_layer.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWTY = 0,
  _UPC,
  _EMACS,
  _META,
  _SCT,
  _FN,
  _ADJUST,
};

/*Tap Dance declaretions
enum{
    TD_TAB_FUNC,
};
*/

//Declare custum keyCodes
enum custom_keycodes {
    RGB_RST = SAFE_RANGE,
    INS_L,      //Insert Line
    KILL_L, 	//Kill Line
    SEL_CPY,  	//Selection Copy
    SEL_CUT,	//Selection Cut
    SEL_DEL,	//Selection Delete
    SND_ID,     //Send ID
	RST_MOD     //Reset Modefier Key
};

//Alias
#define MT_USS LT(LM(_UPC,MOD_LSFT),KC_SPC) //hold
#define MT_US LT(_UPC,KC_SPC)       //hold:"uppercase"  tap:"Space"S
#define MT_EH LT(_EMACS,KC_HENK)    //hold:"EMACS"      tap:"MHEN"
#define MT_MM LT(_META,KC_MHEN)     //hold:"META"       tap:"HENK"
#define MT_RSH RSFT_T(KC_HENK)       //hold:"RSFT"      tap:"HENk"
#define MT_LSM LSFT_T(KC_MHEN)       //hold:"LSFT"      tap:"MHEN"
#define MT_RCH RCTL_T(KC_HENK)       //hold:"RSFT"      tap:"HENk"
#define MT_LAM LALT_T(KC_MHEN)       //hold:"LSFT"      tap:"MHEN"
#define MT_BR LCTL(KC_DOT)          //CTRL + .          'Bunsetsu Right'
#define MT_BL LCTL(KC_COMM)         //CTRL + ,          'Bunsetsu Left'
#define MT_HI LCTL(KC_U)			//CTRL + U          'Hiragana'
#define MT_KA LCTL(KC_I)			//CTRL + I          'Katakana'
#define MT_HN LCTL(KC_O)			//CTRL + O          'Hankaku'
#define MT_ZN LCTL(KC_P)			//CTRL + P 'Zenkaku'

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       JP_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_MINS,  JP_EQL, KC_BSPC, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, JP_LBRC, JP_RBRC,KC_INT3,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, JP_SCLN, JP_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
       MT_LSM,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, JP_SLSH,  MT_RSH, TG(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        KC_LCTL,MT_LAM,MO(_META),   MT_US,      MT_US,MO(_EMACS),  MT_RCH, KC_RGUI
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_UPC] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      JP_TILD, JP_EXLM,   JP_AT, JP_HASH,  JP_DLR, JP_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, JP_UNDS, JP_PLUS, KC_BSPC, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T),     S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), LSFT(JP_LBRC), LSFT(JP_RBRC),LSFT(KC_INT3),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),     S(KC_H), S(KC_J), S(KC_K), S(KC_L), JP_COLN,  JP_DQT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B),     S(KC_N), S(KC_M),   JP_LT,   JP_GT, JP_QUES, KC_RSFT,TG(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        _______, _______, _______, _______,     _______, _______, _______, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_EMACS] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       SND_ID,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_A), C(KC_X),  KC_END, KC_PGUP, XXXXXXX,     C(KC_V), XXXXXXX,  KC_TAB,   INS_L, XXXXXXX,  KC_ESC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
    S(KC_TAB), KC_HOME,  KILL_L,  KC_DEL, C(KC_F), XXXXXXX,     KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP,   KC_F2,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
     TO(_SCT), C(KC_Z), C(KC_Y), C(KC_C), KC_PGDN, XXXXXXX,  KC_MS_BTN3,  KC_ENT,   MT_BL,   MT_BR, KC_PGDN, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX, RST_MOD,TO(_SCT), XXXXXXX,  KC_MS_BTN1, XXXXXXX, XXXXXXX, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_META] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      SND_ID,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX,C(KC_A),C(KC_X),C(KC_END),C(KC_PGUP),XXXXXXX,     C(KC_V), XXXXXXX,  KC_TAB,   INS_L, XXXXXXX,  KC_ESC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
    S(KC_TAB),C(KC_HOME),XXXXXXX,C(KC_DEL),C(KC_H),XXXXXXX, C(KC_BSPC),C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),C(KC_PGUP),_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      TO(_SCT), C(KC_Z), C(KC_Y), C(KC_C),C(KC_PGDN),XXXXXXX,KC_MS_BTN3,  KC_ENT,   MT_BL,   MT_BR,C(KC_PGDN),XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX, RST_MOD, XXXXXXX, XXXXXXX,  KC_MS_BTN1, _______, XXXXXXX, RST_MOD
         //`---------------------------------- -----------|   |--------------------------------------------'
 ),

[_FN] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
  TO(_ADJUST),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_WH_D, KC_WH_U, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
    XXXXXXX,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,XXXXXXX,XXXXXXX,   XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,XXXXXXX,_______,_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,  GE_NORM, GUI_ON, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  ),

   [_SCT] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
    MO(_META), XXXXXXX, SEL_CUT,S(KC_END),XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX,S(KC_HOME),XXXXXXX,SEL_DEL, C(KC_F), XXXXXXX,     SEL_DEL,S(KC_LEFT),S(KC_DOWN),S(KC_UP),S(KC_RGHT),XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
    TO(_QWTY), C(KC_Z), XXXXXXX, SEL_CPY, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX, RST_MOD,TO(_QWTY),XXXXXXX,    XXXXXXX,TO(_QWTY), XXXXXXX, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_ADJUST] = LAYOUT( /* Base */
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
    TO(_QWTY), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  RST_MOD,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_TOG, RGB_MOD, XXXXXXX, LCA(KC_DEL), LALT(KC_PSCR),KC_PSCR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               XXXXXXX, XXXXXXX, XXXXXXX,   RESET,                RESET, XXXXXXX, KC_STOP, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  )
};


//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _UPC:
      rgblight_sethsv_at(HSV_YELLOW, 0);
      break;
    case _EMACS:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case _META:
      rgblight_sethsv_at(HSV_GREEN,0);
      break;
    case _SCT:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      break;
    case _FN:
      rgblight_sethsv_at(HSV_PINK, 0);
      break;
    case _ADJUST:
      rgblight_sethsv_at(HSV_RED, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at( 0, 0, 0, 0);
      break;
    }
    rgblight_set_effect_range( 1, 4);
#endif
return state;
}


int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;

  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif

    case KILL_L:
      if(record->event.pressed){
   			register_code(KC_LSFT);
  			tap_code(KC_END);
	  		unregister_code(KC_LSFT);
			tap_code(KC_DEL);
      }
    return false;
    break;

    case INS_L:
        if(record->event.pressed){
            tap_code(KC_HOME);
            tap_code(KC_ENT);
            tap_code(KC_UP);
        }
    return false;
    break;

    case SEL_DEL:
      if(record->event.pressed){
        tap_code(KC_DEL);
        layer_move(_EMACS);
      }
    return false;
    break;

    case SEL_CPY:
      if(record->event.pressed){
        register_code(KC_LCTL);
        tap_code(KC_C);
        unregister_code(KC_LCTL);
        tap_code(KC_UP);
        layer_move(_EMACS);
      }
    return false;
    break;

    case SEL_CUT:
      if(record->event.pressed){
        register_code(KC_LCTL);
        tap_code(KC_X);
        unregister_code(KC_LCTL);
        layer_move(_EMACS);
      }
    return false;
    break;

    case SND_ID:
        if(record->event.pressed){
            SEND_STRING("aaa031963"SS_TAP(X_TAB));
        }
    return false;
    break;

    case RST_MOD:
        if(record->event.pressed){
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_RCTL);
            layer_move(_QWTY);
        }
    return false;
    break;

    default:
      result = true;
    break;
  }

  return result;
}
