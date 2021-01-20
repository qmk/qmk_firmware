#include "d48tr.h"
#include "action_layer.h"
#include "eeconfig.h"
#include <print.h>
#include "trackball.c"
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

void startup_user() {
    debug_enable = true;
}

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
    INS_L,      //Insert Line
    KILL_L, 	//Kill Line
    SEL_CPY,  	//Selection Copy
    SEL_CUT,	//Selection Cut
    SEL_DEL,	//Selection Delete
    SND_ID,     //Send ID
    RST_MOD,     //Reset Modefier Key
    MS_L,
    MS_R,
    MS_WH
};


//Alias
#define MT_MT LT(_META,KC_TAB)   //hold:"EMACS"      tap:"tab"
#define MT_UE LT(_UPC,KC_ENT)     //hold:"uppercase"  tap:"Enter"
#define MT_US LT(_UPC,KC_SPC)       //hold:"uppercase"  tap:"Space"
#define MT_NH LT(_NUM,KC_HENK)    //hold:"num"  tap:"HENK"
#define MT_NM LT(_NUM,KC_MHEN)    //hold:"num"    tap:"MHEN"
#define MT_BR LCTL(KC_DOT)        //CTRL + .          'Bunsetsu Right'
#define MT_BL LCTL(KC_COMM)       //CTRL + ,          'Bunsetsu Left'
#define MT_CB LCTL_T(KC_BSPC)     //hold:CTRL tap:BS


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWTY] = KEYMAP(
  //,-----------------------------------------------------|   |------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, JP_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   MO(_EMACS),    KC_A,    KC_S,    KC_D,    KC_F,   KC_G,         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, JP_QUOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MT_MT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, JP_SLSH, TT(_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI,   MT_NM,   MT_US,KC_MS_BTN1,KC_MS_BTN2,   MT_UE,   MT_NH, KC_RGUI, KC_RCTL, KC_RSFT
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  ),

[_UPC] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      JP_TILD, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T),     S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), JP_UNDS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),     S(KC_H), S(KC_J), S(KC_K), S(KC_L), JP_COLN,  JP_DQT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B),     S(KC_N), S(KC_M),   JP_LT,   JP_GT, JP_QUES,S(KC_INT3),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+-------- 
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  ),  

[_NUM] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       JP_GRV, JP_EXLM,   JP_AT, JP_HASH,  JP_DLR, JP_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, JP_PLUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  JP_EQL, 
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______,JP_LPRN,S(JP_LBRC),JP_LBRC,     JP_RBRC,S(JP_RBRC),JP_RPRN, KC_DOT,KC_INT3,S(KC_INT3),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
  //|-----------------------------------------------------|   |-----------------------------------------------------'
 ),

  [_EMACS] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      SND_ID, C(KC_A), C(KC_X),  KC_END, KC_PGUP, XXXXXXX,     C(KC_V), XXXXXXX,  KC_TAB,   INS_L, XXXXXXX,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME,  KILL_L,  KC_DEL, C(KC_F), XXXXXXX,     KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_F2,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, C(KC_Y), C(KC_C), KC_PGDN, XXXXXXX,  KC_MS_BTN3,  KC_ENT,   MT_BL,   MT_BR, C(KC_Z), _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  ),
  
  [_META] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      SND_ID,_______,_______,C(KC_END),C(KC_PGUP),XXXXXXX,     C(KC_V), XXXXXXX,S(KC_TAB),_______, XXXXXXX, _______, 
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,C(KC_HOME),_______,C(KC_DEL),C(KC_H),XXXXXXX,C(KC_BSPC),C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, C(KC_Y),C(KC_C),C(KC_PGDN),XXXXXXX,  KC_MS_BTN3,  KC_ENT,   MT_BL,   MT_BR, C(KC_Z), _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
  //|-----------------------------------------------------|   |-----------------------------------------------------'
 ),

[_FN] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
  TO(_ADJUST),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     XXXXXXX,  KC_ESC, KC_WH_D, KC_WH_U, KC_PSCR, KC_PAUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,     XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,   XXXXXXX,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,XXXXXXX,_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      RST_MOD, _______, _______,  GUI_ON, GE_NORM, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RST_MOD
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  ),

   [_SCT] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       KC_ESC, XXXXXXX, SEL_CUT,S(KC_END),XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   TO(_QWTY),S(KC_HOME),XXXXXXX, SEL_DEL, C(KC_F), XXXXXXX,   SEL_DEL,S(KC_LEFT),S(KC_DOWN),S(KC_UP),S(KC_RGHT),XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), XXXXXXX, SEL_CPY, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  ),

  [_ADJUST] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
    TO(_QWTY), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_TOG,RGB_MOD,LCA(KC_DEL),LALT(KC_PSCR),KC_PSCR,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      RST_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   RESET,       RESET, XXXXXXX, XXXXXXX, XXXXXXX, KC_STOP, RST_MOD
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  )
};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;

  switch (keycode) {

    case JP_AT:
    case JP_CIRC:
    case JP_COLN:
      if(record->event.pressed){
        unregister_code(KC_LSFT);
        tap_code(keycode);
        register_code(KC_LSFT);
      }
      return false;
     break;

    case KILL_L:
      if(record->event.pressed){
   		  SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT) SS_TAP(X_DEL));
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
        SEND_STRING(SS_LCTL("c") SS_TAP(X_ESC));
        layer_move(_EMACS);
      }
      return false;
      break;

    case SEL_CUT:
      if(record->event.pressed){
        SEND_STRING(SS_LCTL("x"));
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
            clear_keyboard();
            layer_move(_QWTY);
        }
      return false;
      break;

    case MS_L:
      if (record->event.pressed) {
        mouse_btn1 = true;
      } else {
        mouse_btn1 = false;
      }
      return false;
      break;
    case MS_R:
      if (record->event.pressed) {
        mouse_btn2 = true;
      } else {
        mouse_btn2 = false;
      }
      return false;
      break;
    case MS_WH:
      if (record->event.pressed) {
        wheel = true;
      } else {
        wheel = false;
      }
      return false;
      break;

    default:
      result = true;
      break; 
  }
  return result;
}