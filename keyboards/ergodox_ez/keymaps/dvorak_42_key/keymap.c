// Copyright 2022 LucW (@luc-languagetools)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "dvorak_42_key.h"


// to build this keymap
// make ergodox_ez:dvorak_42_key:teensy
// or:
// qmk compile -kb ergodox_ez -km dvorak_42_key
// flashing from rpi:
// sudo teensy_loader_cli -v -w .build/ergodox_ez_dvorak_42_key.hex --mcu atmega32u4

// keeping fork up to date:
// https://help.github.com/articles/configuring-a-remote-for-a-fork/
// https://help.github.com/articles/syncing-a-fork/
// pushing dev branch
// git push origin dev:dev

// debounce settings
// remove these after getting a new keyboard
// #define DEBOUNCE 50




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_ergodox(
      // left hand
      KC_TRNS,           KC_TRNS,       KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,
      OSL(VSCODE),       KC_QUOTE,      KC_COMMA,   KC_DOT,       KC_P,    KC_Y,    KC_TRNS,
      OSL(SHELL_NAV),    KC_A,          KC_O,       KC_E,         KC_U,    KC_I,
      OSL(SHELL_SCREEN), KC_SCLN,       KC_Q,       KC_J,         KC_K,    KC_X,    MO(VSCODE),
      MEH(KC_0),         OSM(MOD_LSFT), OSM(MOD_LCTL), MO(KEYSEL), MO(BROWSER_CONTROL),

      // left thumb cluster
                KC_TRNS,KC_TRNS,
                        KC_TRNS,
      MO(COMBINED),MO(KEYNAV), KC_TRNS,

      // right hand
      KC_F7,     KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, MEH(KC_7),
      MEH(KC_1), KC_F,  KC_G,  KC_C,   KC_R,   KC_L,   KC_TAB,
                 KC_D,  KC_H,  KC_T,   KC_N,   KC_S,   RCTL(KC_BSPC),
      MEH(KC_2), KC_B,  KC_M,  KC_W,   KC_V,   KC_Z,   MEH(KC_8),
      KC_BSPC,   RCTL(KC_BSPC), KC_CAPS, OSM(MOD_LSFT),MEH(KC_9),

      // right thumb cluster
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_ENTER, KC_SPACE

  ),

  [KEYNAV] = LAYOUT_ergodox(
    // left hand
    KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_TRNS,         KC_TRNS,          KC_TRNS,      KC_TRNS,
    KC_ESC,          RCTL(KC_ENTER), RCTL(KC_K),     RCTL(KC_Z),      RCTL(KC_S),       RCTL(KC_N),   KC_TRNS,
    KC_TRNS,         MO(KEYSEL),     KC_TRNS,        RSFT(KC_TAB),    KC_TAB,           RCTL(KC_F),
    KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_TRNS,         KC_TRNS,          NP_DUPE_LINE, KC_TRNS,
    KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_TRNS,         KC_TRNS,
    // left thumb cluster
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,


    // right hand
    KC_TRNS,KC_TRNS,       KC_TRNS,    KC_TRNS,         KC_TRNS,    KC_TRNS,         MEH(KC_G),
    KC_TRNS,KC_NO,         KC_HOME,    KC_UP,           KC_END,     KC_PGUP,         MEH(KC_H),
            LCTL(KC_LEFT), KC_LEFT,    KC_DOWN,         KC_RIGHT,   LCTL(KC_RIGHT),  MEH(KC_I),
    KC_TRNS,KC_TRNS,       RCTL(KC_C), RCTL(KC_X),      RCTL(KC_V), KC_PGDN,         MEH(KC_J),
                           KC_BSPC,   RCTL(KC_BSPC),    KC_DELETE,  LCTL(KC_DELETE), MEH(KC_K),

    // right thumb cluster
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
  ),

    // key selection layer
    [KEYSEL] = LAYOUT_ergodox(
           // left hand
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                   // bottom row
                   QK_BOOT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                           // thumb cluster
                                           KC_TRNS,KC_TRNS,
                                                   KC_TRNS,
                                   KC_TRNS,KC_TRNS,KC_TRNS,
           // right hand
           KC_TRNS,   KC_TRNS,             KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,              KC_TRNS,
           KC_TRNS,   KC_TRNS,             RSFT(KC_HOME), RSFT(KC_UP),   RSFT(KC_END),   RSFT(KC_PGUP),        KC_TRNS,
                      RSFT(RCTL(KC_LEFT)), RSFT(KC_LEFT), RSFT(KC_DOWN), RSFT(KC_RIGHT), RSFT(RCTL(KC_RIGHT)), KC_TRNS,
           KC_TRNS,   KC_TRNS,             RCTL(KC_C),    RCTL(KC_X),    RCTL(KC_V),     RSFT(KC_PGDN),        KC_TRNS,
                    // bottom row
                      KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,
           // thumb cluster
           KC_TRNS, KC_TRNS,
           KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS
    ),

  // shell navigation layer
  [SHELL_NAV] = LAYOUT_ergodox(
       // left hand
       KC_NO,  KC_TRNS,           KC_TRNS,        KC_TRNS,          KC_TRNS,     KC_TRNS,     KC_TRNS,
       KC_TRNS,SHELL_GIT_DIFF,    SHELL_PGREP,    SHELL_PLESS,      SHELL_LESS,  KC_TRNS,     KC_TRNS,
       KC_TRNS,SHELL_GIT_STATUS,  SHELL_CDPRE,    SHELL_LSLTR,      SHELL_LS,    SHELL_LSLA,
       KC_TRNS,SHELL_SCREEN_LIST, SHELL_SCREENRD, SHELL_SCREEN_NEW, SHELL_TAILF, KC_TRNS,     KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,    KC_TRNS,    KC_TRNS,             KC_TRNS,         KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,    RCTL(KC_D), KC_HOME,             KC_UP,           KC_END,     RCTL(KC_L), RCTL(KC_X),
                   LALT(KC_B), KC_LEFT,             KC_DOWN,         KC_RIGHT,   LALT(KC_F), RCTL(KC_W),
       KC_TRNS,    RCTL(KC_U), LALT(KC_DOT),        RCTL(KC_R),      KC_BTN2,    RCTL(KC_K), RCTL(KC_C),
                   // bottom row 
                   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
  ),


    // linux screen layer
  [SHELL_SCREEN] = LAYOUT_ergodox(
       // left hand
       KC_NO,  KC_TRNS,   KC_TRNS,            KC_TRNS,             KC_TRNS,            KC_TRNS,       KC_TRNS,
       KC_TRNS,KC_TRNS,   SCREEN_READREG_3,   SCREEN_READREG_2,    SCREEN_READREG_1,   KC_TRNS,       KC_TRNS,
       KC_TRNS,KC_TRNS,   SCREEN_PASTEREG_3,  SCREEN_PASTEREG_2,   SCREEN_PASTEREG_1,  SCREEN_DETACH,
       KC_TRNS,KC_TRNS,   KC_TRNS,            KC_TRNS,             KC_TRNS,            KC_TRNS,       KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS,            KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,             KC_TRNS,
       KC_TRNS, KC_TRNS,            SCREEN_7,    SCREEN_8,    SCREEN_9,    SCREEN_RENAME,       KC_TRNS,
                SCREEN_TAB_LEFT,    SCREEN_4,    SCREEN_5,    SCREEN_6,    SCREEN_TAB_RIGHT,    SCREEN_COPY_MODE,
       KC_TRNS, KC_TRNS,            SCREEN_1,    SCREEN_2,    SCREEN_3,    SCREEN_NUMBER,       SCREEN_PASTE,
                                    // bottom row
                                    SCREEN_0,    KC_TRNS,     KC_TRNS,     KC_TRNS,             KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, SCREEN_KILL, SCREEN_NEW_TAB
  ),

    // android studio shortcuts
  [ANDROID_STUDIO] = LAYOUT_ergodox(
       // left hand
       KC_NO,  KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,   KC_TRNS,
       KC_TRNS,KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,   KC_TRNS,
       KC_TRNS,KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
       KC_TRNS,KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,   KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,      KC_TRNS,         KC_TRNS,       KC_TRNS,           KC_TRNS,              KC_TRNS,              KC_TRNS,
       AS_CMT_LINE,  AS_COPYLINEDOWN, AS_FINDUSAGE,  AS_GO_DECLARATION, AS_GO_IMPLEMENTATION, AS_LINE,              AS_BRACKET,
                     AS_CLOSETAB,     AS_TABLEFT,    AS_TABRIGHT,       AS_SYMBOL,            AS_CLASS,             AS_BACK,
       AS_CMT_BLOCK, KC_TRNS,         AS_BM_PREV,    AS_BM_NEXT,        KC_TRNS,              AS_CLOSETOOLWINDOW,   AS_BM_TOGGLE,
                         // bottom row
                         KC_TRNS,     AS_BM_LIST,    KC_TRNS,        KC_TRNS,              KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, AS_DEL_LINE, KC_TRNS
  ),

    // vscode shortcuts shortcuts
  [VSCODE] = LAYOUT_ergodox(
       // left hand
       KC_NO,   KC_TRNS,    KC_TRNS,             KC_TRNS,           KC_TRNS,             KC_TRNS,        KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_TRNS,             VS_CMT_BLOCK,      VS_CMT_LINE,         VS_BM_LISTALL,  KC_TRNS,
       KC_TRNS, KC_TRNS,    VS_TOGGLE_TERMINAL,  VS_FOCUS_TERMINAL, VS_FOCUS_EDITOR,     VS_BM_LIST,
       KC_TRNS, KC_TRNS,    KC_TRNS,             KC_TRNS,           KC_TRNS,             VS_BM_CLEARALL, KC_TRNS,
                // bottom row
                KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,      KC_TRNS,          KC_TRNS,       KC_TRNS,          KC_TRNS,             KC_TRNS,         KC_TRNS,
       KC_TRNS,      VS_COPYLINEDOWN,  VS_REFERENCES, VS_DEFINITION,    VS_IMPLEMENTATION,   VS_LINE,         VS_BRACKET,
                     VS_CLOSETAB,      VS_TABLEFT,    VS_TABRIGHT,      VS_SYMBOLEDITOR,     VS_FILE,         VS_BACK,
       KC_TRNS,      VS_JUMPY,         VS_BM_PREV,    VS_BM_NEXT,       VS_GROUP_1,          VS_GROUP_2,      VS_BM_TOGGLE,
                                       // bottom row
                                       VS_COMMANDS,   KC_TRNS,          KC_TRNS,             KC_TRNS,         KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, VS_DEL_LINE, KC_TRNS
  ),


  [COMBINED] = LAYOUT_ergodox(

    // left hand
    KC_NO,  KC_TRNS, KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS, KC_TRNS,
    KC_TRNS,KC_EXLM, KC_AT,      KC_HASH,     KC_DLR,      KC_PERC, KC_TRNS,
    KC_TRNS,KC_LPRN, KC_RPRN,    KC_LBRC,     KC_RBRC,     KC_UNDS,
    KC_TRNS,KC_COLN, KC_DQUO,    KC_LCBR,     KC_RCBR,     KC_AMPR, KC_TRNS,
    // bottom row
    KC_TRNS,KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,
    // thumb cluster
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

    // right hand
    KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
    KC_TRNS, KC_PLUS,     KC_7,    KC_8,    KC_9,    KC_ASTR,     KC_PIPE,
             KC_MINS,     KC_4,    KC_5,    KC_6,    KC_SLSH,     KC_BSLS,
    KC_TRNS, KC_EQUAL,    KC_1,    KC_2,    KC_3,    KC_QUES,     KC_DOT,
    // bottom row
                          KC_0,    KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
    // thumb cluster
    KC_TRNS,KC_TRNS,
	KC_TRNS,
	KC_TRNS,KC_TRNS,KC_TRNS),


    [BROWSER_CONTROL] = LAYOUT_ergodox(
		   // left hand
           KC_TRNS, KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,      KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS,      KC_BTN3,       KC_MS_U,       KC_BTN1,      KC_BTN2, KC_TRNS,
           KC_TRNS, KC_TRNS,      KC_MS_L,       KC_MS_D,       KC_MS_R,      KC_TRNS,
           KC_TRNS, KC_TRNS,      KC_TRNS,       WINDOWS10_WORKSPACE_LEFT,   WINDOWS10_WORKSPACE_RIGHT, WINDOWS10_TASK_VIEW, KC_TRNS,
		   // bottom row
           KC_TRNS, KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,

                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
          // right hand
           KC_TRNS,  KC_TRNS,   KC_TRNS,            KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,
           KC_TRNS,  KC_UP,     KC_PGUP,            KC_PGDN,      KC_MS_WH_UP,   KC_TRNS,       KC_TRNS,
                     KC_DOWN,   RCTL(KC_PGUP), 	    RCTL(KC_PGDN),KC_MS_WH_DOWN, LALT(KC_LEFT), KC_TRNS,
           KC_TRNS,  KC_TRNS,   RCTL(KC_1),         RCTL(KC_9),   KC_F6,         KC_F5,         KC_TRNS,
                                // bottom row
                                RCTL(LSFT(KC_TAB)), RCTL(KC_TAB),      KC_TRNS,       KC_TRNS,       KC_TRNS,
           KC_TRNS, KC_TRNS,
           KC_TRNS,
           KC_TRNS, RCTL(KC_W), RCTL(KC_T)
    ),


  // shortcuts to be intercepted by autohotkey
  [SHORTCUTS] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,   KC_TRNS,       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,   KC_TRNS,
       KC_F1,     KC_F2,         KC_F3,          KC_F4,          KC_F5,          KC_F6,     KC_TRNS,
       KC_F7,     KC_F8,         KC_F9,          KC_F10,         KC_F11,         KC_F12,
       KC_TRNS,   OSM(MOD_LSFT), OSM(MOD_LGUI),  OSM(MOD_LALT),  OSM(MOD_LCTL),  KC_TRNS,   KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,DF(BASE),KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,     QK_BOOT,
       KC_TRNS, MEH(KC_I), MEH(KC_J), MEH(KC_K), MEH(KC_L),   MEH(KC_M),   MEH(KC_N),
                MEH(KC_O), MEH(KC_P), MEH(KC_Q), MEH(KC_R),   MEH(KC_S),   MEH(KC_T),
       KC_TRNS, MEH(KC_U), MEH(KC_V), MEH(KC_W), MEH(KC_X),   MEH(KC_Y),   MEH(KC_Z),
                                    // bottom row
                KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,             KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
  ),


};





bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }
    return false;
}


void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case COMBINED:
            ergodox_right_led_2_on();
            break;
        case SHELL_NAV:
        case SHELL_SCREEN:
        case KEYNAV:
        case KEYSEL:
        case VSCODE:
            ergodox_right_led_3_on();
            break;
	case BROWSER_CONTROL:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
	case SHORTCUTS:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;            
        default:
            break;
    }

};
