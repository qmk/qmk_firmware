//nobs keymap
#include QMK_KEYBOARD_H
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#include "keymap_jp.h"
#include "action_layer.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

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
  _NUM,
  _EMACS,
  _META,
  _SCT,
  _FN,
  _ADJUST,
};


//Declare custum keyCodes
enum custom_keycodes {
    RGB_RST = SAFE_RANGE,
    QT_SCT,     //Quit Select
    INS_L,      //Insert Line
    KILL_L, 	//Kill Line
    SEL_CPY,  	//Selection Copy
    SEL_CUT,	//Selection Cut
    SEL_DEL,	//Selection Delete
    SND_ID,     //Send ID
    RST_MOD,     //Reset Modefier Key
    T_TAB     //tap tab 
};

//Alias
#define MT_EE LT(_EMACS,KC_ESC)   //hold:"EMACS"      tap:"tab"
#define MT_MT LT(_META,KC_TAB)   //hold:"EMACS"      tap:"tab"
#define MT_EC LT(_EMACS,KC_TAB)          //MO "EMACS"    with CTRL

#define MT_UE LT(_UPC,KC_ENT)     //hold:"uppercase"  tap:"Enter"
#define MT_US LT(_UPC,KC_SPC)     //hold:"uppercase"  tap:"Space"
#define MT_NH LT(_NUM,KC_HENK)    //hold:"num"  tap:"HENK"
#define MT_NM LT(_NUM,KC_MHEN)    //hold:"num"    tap:"MHEN"
#define MT_BR LCTL(KC_DOT)        //CTRL + .          'Bunsetsu Right'
#define MT_BL LCTL(KC_COMM)       //CTRL + ,          'Bunsetsu Left'


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       JP_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_MINS,  JP_EQL,  KC_DEL,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  JP_EQL, KC_BSPC, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
   MO(_EMACS),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, JP_SCLN, JP_QUOT, JP_LBRC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
        MT_MT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, JP_SLSH, JP_RBRC, TG(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                       KC_RCTL, KC_LALT,   MT_NM,   MT_US,       MT_UE,   MT_NH, KC_RSFT, KC_RGUI
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_UPC] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      JP_TILD, JP_EXLM,   JP_AT, JP_HASH,  JP_DLR, JP_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, JP_UNDS, JP_PLUS,  KC_DEL, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      JP_TILD, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T),     S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), JP_PLUS, KC_BSPC, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
   MO(_EMACS), S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),     S(KC_H), S(KC_J), S(KC_K), S(KC_L), JP_COLN,  JP_DQT,S(JP_LBRC),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
    MO(_META), S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B),     S(KC_N), S(KC_M),   JP_LT,   JP_GT, JP_QUES,S(JP_RBRC),TG(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        RST_MOD, _______,   MT_NH, _______,     _______, MT_NH, _______, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_NUM] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      JP_GRV, JP_EXLM,   JP_AT, JP_HASH,  JP_DLR, JP_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, JP_UNDS, JP_PLUS, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
   MO(_EMACS),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_MINS,  JP_EQL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
    MO(_META),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,  KC_DOT,KC_INT3,S(KC_INT3),_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        RST_MOD, _______, _______,   MT_US,       MT_UE, _______, _______, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_EMACS] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       SND_ID,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_A), C(KC_X),  KC_END, KC_PGUP, XXXXXXX,     C(KC_V), XXXXXXX,  KC_TAB,   INS_L, XXXXXXX,  KC_ESC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, KC_HOME,  KILL_L,  KC_DEL, C(KC_F), XXXXXXX,     KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_F2, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F2, C(KC_Y), C(KC_C), KC_PGDN, XXXXXXX,  KC_MS_BTN3,  KC_ENT,   MT_BL,   MT_BR, C(KC_Z), _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        RST_MOD, XXXXXXX,TG(_SCT),   MT_US,  KC_MS_BTN1,   MT_NH, XXXXXXX, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  ),
  
  [_META] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       SND_ID,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______,C(KC_A),C(KC_X),C(KC_END),C(KC_PGUP),XXXXXXX,     C(KC_V), XXXXXXX,S(KC_TAB),  INS_L, XXXXXXX,  KC_ESC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______,C(KC_HOME),XXXXXXX,C(KC_DEL),C(KC_H),XXXXXXX, C(KC_BSPC),C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),KC_F2,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F2, C(KC_Y),C(KC_C),C(KC_PGDN),XXXXXXX,  KC_MS_BTN3,  KC_ENT,   MT_BL,   MT_BR, C(KC_Z), _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        RST_MOD, XXXXXXX,TG(_SCT),   MT_US,  KC_MS_BTN1,   MT_NH, XXXXXXX, RST_MOD
         //`---------------------------------- -----------|   |--------------------------------------------'
 ),

[_FN] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
  TO(_ADJUST),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      GE_NORM,  GUI_ON, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_WH_D, KC_WH_U, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
  XXXXXXX,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,XXXXXXX,XXXXXXX,     XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,XXXXXXX,_______,_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        RST_MOD, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  ),

   [_SCT] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_ESC, XXXXXXX, SEL_CUT,S(KC_END),XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
   TO(_QWTY),S(KC_HOME),XXXXXXX, SEL_DEL, C(KC_F), XXXXXXX,   SEL_DEL,S(KC_LEFT),S(KC_DOWN),S(KC_UP),S(KC_RGHT),XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), XXXXXXX, SEL_CPY, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
                        RST_MOD, XXXXXXX, _______,TO(_QWTY),    XXXXXXX, XXXXXXX, XXXXXXX, RST_MOD
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
               RST_MOD, XXXXXXX, XXXXXXX,   RESET,                RESET, XXXXXXX, KC_STOP, RST_MOD
          //`---------------------------------------------|   |--------------------------------------------'
  )
};


//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _UPC:
      rgblight_sethsv_at(HSV_YELLOW, 0);
      register_code(KC_LSFT);
      break;
    case _NUM:
      rgblight_sethsv_at(HSV_PINK, 0);
      unregister_code(KC_LSFT);
      break;
    case _EMACS:
      rgblight_sethsv_at(HSV_BLUE, 0);
      unregister_code(KC_LSFT);
       break;
    case _META:
      rgblight_sethsv_at(HSV_GREEN,0);
      unregister_code(KC_LSFT);
      break;
    case _SCT:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      unregister_code(KC_LSFT);
      break;
    case _FN:
      rgblight_sethsv_at(HSV_CHARTREUSE, 0);
      unregister_code(KC_LSFT);
      break;
    case _ADJUST:
      rgblight_sethsv_at(HSV_RED, 0);
      unregister_code(KC_LSFT);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at( 0, 0, 0, 0);
      unregister_code(KC_LSFT);
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

    case JP_AT:
    case JP_CIRC:
    case JP_COLN:
      if(record->event.pressed){
        unregister_code(KC_LSFT);
        tap_code(keycode);
      }
      return false;
      break;

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
