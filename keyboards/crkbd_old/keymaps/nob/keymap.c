/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

#ifdef SSD1306OLED
  #include "ssd1306.h"
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

enum macro_keycodes {
  KC_SAMPLEMACRO,
};



#define _QWERTY 0
#define _UPC 1
#define _NUM 2
#define _EMACS 3
#define _META 4
#define _FN 5
#define _SELECT 6
#define _ADJUST 7

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    RGBRST,
    INS_L,      //Insert Line
    KILL_L, 	//Kill Line
    SEL_CPY,  	//Selection Copy
    SEL_CUT,	//Selection Cut
    SEL_DEL,	//Selection Delete
    SND_ID,     //Send ID
    RST_MOD,     //Reset Modefier Key
};


//Alias
#define MT_AE ALT_T(KC_ENT)     //hold:"ALT" tap:"Enter"
#define MT_CU CTL_T(KC_SPC)     //hold:"Control" tap:"Space"
#define MT_MT LT(_META,KC_TAB)   //hold:"EMACS"      tap:"tab"
#define MT_NE LT(_NUM,KC_ENT)     //hold:"uppercase"  tap:"Enter"
#define MT_US LT(_UPC,KC_SPC)       //hold:"uppercase"  tap:"Space"
#define MT_GH LGUI_T(KC_HENK)    //hold:"num"  tap:"HENK"
#define MT_GM RGUI_T(KC_MHEN)    //hold:"num"    tap:"MHEN"
#define MT_FM LT(_FN,KC_MHEN)    //hold:"num"    tap:"MHEN"

#define MC_BR LCTL(KC_DOT)        //CTRL + .          'Bunsetsu Right'
#define MC_BL LCTL(KC_COMM)       //CTRL + ,          'Bunsetsu Left'
#define MC_E  MO(_EMACS)        //EMACS
#define MC_N MO(_NUM)           //Num
#define MC_PSC G(S(KC_S))       //Print screen
#define MC_DTR G(C(KC_RIGHT))    //Desk top move right
#define MC_DTL G(C(KC_LEFT))     //Desk top move left

#define JP_AT KC_LBRC    // @
#define JP_CIRC KC_EQL   // ^, ~
#define JP_COLN KC_QUOT  // :, *
#define JP_YEN KC_INT3   // yen, |
#define JP_LBRC KC_RBRC  // [, {
#define JP_RBRC KC_NUHS  // ], }

#define JP_LCBR LSFT(JP_LBRC)  // {
#define JP_RCBR LSFT(JP_RBRC)  // }
#define JP_QUOT LSFT(KC_7)         //'
#define JP_DQT LSFT(KC_2)      // "
#define JP_PIPE LSFT(KC_INT3)   //|
#define JP_AMPR LSFT(KC_6)     // &
#define JP_TILD LSFT(KC_EQL)    //~
#define JP_UNDS LSFT(KC_INT1)   //_
#define JP_LPRN LSFT(KC_8)     // (
#define JP_RPRN LSFT(KC_9)     // )
#define JP_PLUS LSFT(KC_SCLN)  // +
#define JP_EQL LSFT(KC_MINS)   // =
#define JP_ASTR LSFT(JP_COLN)  // *
#define JP_GRV LSFT(JP_AT)    //`

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_MINS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         MC_E,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, JP_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        MT_MT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, MO(_FN),\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            MT_FM,   MT_US,   MT_CU,      MT_AE,    MC_N,  MT_GH\
                                      //`--------------------------'  `--------------------------'

  ),

  [_UPC] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      JP_TILD, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T),     S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), JP_UNDS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),     S(KC_H), S(KC_J), S(KC_K), S(KC_L), JP_COLN,  JP_DQT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B),     S(KC_N), S(KC_M),   KC_LT,   KC_GT, KC_QUES,JP_PIPE,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------
                                 _______, _______, _______,     _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_NUM] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       JP_GRV, KC_EXLM,   JP_AT, KC_HASH,  KC_DLR, KC_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, JP_PLUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  JP_EQL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, JP_LPRN, JP_LCBR, JP_LBRC,     JP_RBRC, JP_RCBR, JP_RPRN,  KC_DOT,  JP_YEN, JP_PIPE,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,     _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_EMACS] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      SND_ID, C(KC_A), C(KC_X),  KC_END,  KC_PGUP, XXXXXXX,     C(KC_V), XXXXXXX,  KC_TAB,   INS_L,  MC_PSC,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME,  KILL_L,  KC_DEL, C(KC_F),  MC_DTR,     KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_F2,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, C(KC_Y), C(KC_C), KC_PGDN,  MC_DTL,  KC_MS_BTN3,  KC_ENT,   MC_BL,   MC_BR, C(KC_Z),LCA(KC_DEL),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                             TG(_SELECT), _______, _______,       RESET, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_META] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      SND_ID,_______,_______,C(KC_END),C(KC_PGUP),XXXXXXX,     C(KC_V), XXXXXXX,S(KC_TAB),_______, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,C(KC_HOME),_______,C(KC_DEL),C(KC_H),MC_DTR,C(KC_BSPC),C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, C(KC_Y),C(KC_C),C(KC_PGDN), MC_DTL,  KC_MS_BTN3,  KC_ENT,   MC_BL,   MC_BR, C(KC_Z), _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,     _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_FN] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
  TO(_ADJUST),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     XXXXXXX,  KC_ESC, KC_WH_D, KC_WH_U, KC_PSCR, KC_PAUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,     XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,   XXXXXXX,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,XXXXXXX,_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,     RESET, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

    [_SELECT] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       KC_ESC, XXXXXXX, SEL_CUT,S(KC_END),XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
 TO(_QWERTY),S(KC_HOME),XXXXXXX, SEL_DEL, C(KC_F), XXXXXXX,   SEL_DEL,S(KC_LEFT),S(KC_DOWN),S(KC_UP),S(KC_RGHT),XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), XXXXXXX, SEL_CPY, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,     _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, RGBRST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,     _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

layer_state_t layer_state_set_user(layer_state_t state){
  switch (get_highest_layer(state)) {
    case _UPC:
        register_code(KC_LSFT);
      break;

    default: //  for any other layers, or the default layer
        unregister_code(KC_LSFT);
      break;
    }
return state;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

   switch (keycode) {
    case  JP_COLN:
      if(record->event.pressed){
        unregister_code(KC_LSFT);
        tap_code(keycode);
      }
      return false;
     break;

    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
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
        SEND_STRING(SS_LCTL("c") );
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
            layer_move(_QWERTY);
        }
      return false;
      break;
  }
  return true;
}
