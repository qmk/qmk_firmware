// Copyright 2022 LucW (@luc-languagetools)
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H
#include <stdio.h>
#include "dvorak_42_key.h"

// to build: qmk compile -kb crkbd/rev1 -km dvorak_42_key

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
   OSL(VSCODE), KC_QUOTE, KC_COMMA, KC_DOT,  KC_P,   KC_Y,                         KC_F,   KC_G,   KC_C,     KC_R,  KC_L,    KC_TAB,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
OSL(SHELL_NAV), KC_A,     KC_O,     KC_E,    KC_U,   KC_I,                         KC_D,   KC_H,   KC_T,     KC_N,  KC_S,   TD(TD_DEL_WORD_DEL),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
OSM(MOD_LSFT),KC_SEMICOLON, KC_Q,  KC_J,    KC_K,   KC_X,                             KC_B,   KC_M,   KC_W,     KC_V,  KC_Z,   OSM(MOD_LSFT),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                      MO(BROWSER_CONTROL), MO(COMBINED),MO(KEYNAV),     KC_ENTER, KC_SPACE, OSL(SHORTCUTS)
                                      //`--------------------------'  `--------------------------'

  ),

  [KEYNAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
KC_ESC, RCTL(KC_ENTER), RCTL(KC_K), RCTL(KC_Z), RCTL(KC_S), RCTL(KC_N),          KC_TRNS, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_DELETE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
KC_TRNS, MO(KEYSEL), KC_TRNS, RSFT(KC_TAB), KC_TAB, RCTL(KC_F),         LCTL(KC_LEFT), KC_LEFT, KC_DOWN, KC_RIGHT, LCTL(KC_RIGHT), KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
KC_TRNS, RCTL(KC_P), RCTL(KC_O),  RCTL(KC_A), RCTL(KC_B), NP_DUPE_LINE,     KC_TRNS, RCTL(KC_C), RCTL(KC_X), RCTL(KC_V), KC_PGDN, RCTL(KC_DELETE),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),


  [KEYSEL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, RSFT(KC_HOME), RSFT(KC_UP), RSFT(KC_END), RSFT(KC_PGUP), KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         RSFT(RCTL(KC_LEFT)), RSFT(KC_LEFT), RSFT(KC_DOWN), RSFT(KC_RIGHT), RSFT(RCTL(KC_RIGHT)), KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS, RCTL(KC_C), RCTL(KC_X), RCTL(KC_V), RSFT(KC_PGDN), KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),


  [SHELL_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                              ,-----------------------------------------------------.
TO(BASE),SHELL_GIT_DIFF, SHELL_PGREP, SHELL_PLESS, SHELL_LESS, KC_TRNS,              RCTL(KC_D), KC_HOME, KC_UP, KC_END, RCTL(KC_L), RCTL(KC_X),
  //|--------+--------+--------+--------+--------+--------|                             |--------+--------+--------+--------+--------+--------|
OSL(SHELL_SCREEN),SHELL_GIT_STATUS,SHELL_CDPRE,SHELL_LSLTR,SHELL_LS, SHELL_LSLA,              LALT(KC_B), KC_LEFT, KC_DOWN, KC_RIGHT, LALT(KC_F), RCTL(KC_W),
  //|--------+--------+--------+--------+--------+--------|                           |--------+--------+--------+--------+--------+--------|
KC_TRNS,SHELL_SCREEN_LIST, SHELL_SCREENRD, SHELL_SCREEN_NEW, SHELL_TAILF, KC_TRNS,   RCTL(KC_U), LALT(KC_DOT), RCTL(KC_R), KC_BTN2, RCTL(KC_K), RCTL(KC_C),
  //|--------+--------+--------+--------+--------+--------+--------|            |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS,  KC_TRNS, KC_TRNS,              LCTL(LSFT(KC_V)), KC_TRNS, KC_TRNS
                                      //`--------------------------'            `--------------------------'
  ),

  [SHELL_SCREEN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                 ,-----------------------------------------------------.
TO(BASE),KC_TRNS, SCREEN_READREG_3, SCREEN_READREG_2, SCREEN_READREG_1,KC_TRNS,          KC_TRNS,         SCREEN_7, SCREEN_8, SCREEN_9, SCREEN_RENAME, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                                 |--------+--------+--------+--------+--------+--------|
TO(BASE),KC_TRNS,SCREEN_PASTEREG_3,SCREEN_PASTEREG_2,SCREEN_PASTEREG_1,SCREEN_DETACH,    SCREEN_TAB_LEFT, SCREEN_4, SCREEN_5, SCREEN_6, SCREEN_TAB_RIGHT, SCREEN_COPY_MODE,
  //|--------+--------+--------+--------+--------+--------|                                 |--------+--------+--------+--------+--------+--------|
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS,         SCREEN_1, SCREEN_2, SCREEN_3, SCREEN_NUMBER, SCREEN_PASTE,
  //|--------+--------+--------+--------+--------+--------+--------|                |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS,  KC_TRNS, KC_TRNS,                     SCREEN_KILL, SCREEN_NEW_TAB, SCREEN_0
                                      //`--------------------------'                `--------------------------'
  ),

  [VSCODE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                             ,-----------------------------------------------------.
TO(BASE), KC_TRNS, VS_FIND_FILES, VS_CMT_BLOCK, VS_CMT_LINE, VS_BM_LISTALL,                     VS_COPYLINEDOWN, VS_REFERENCES, VS_DEFINITION, VS_IMPLEMENTATION, VS_LINE,   VS_BRACKET,
  //|--------+--------+--------+--------+--------+--------|                             |--------+--------+--------+--------+--------+--------|
KC_TRNS, KC_TRNS, VS_TOGGLE_TERMINAL, VS_FOCUS_TERMINAL, VS_FOCUS_EDITOR, VS_BM_LIST,    VS_CLOSETAB,     VS_TABLEFT,    VS_TABRIGHT,   VS_SYMBOLEDITOR,   VS_FILE,   VS_BACK,
  //|--------+--------+--------+--------+--------+--------|                             |--------+--------+--------+--------+--------+--------|
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, VS_BM_CLEARALL,                             VS_JUMPY,        VS_BM_PREV,    VS_BM_NEXT,    VS_GROUP_1,        VS_GROUP_2, VS_BM_TOGGLE,
//|--------+--------+--------+--------+--------+--------+--------|                |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS,  VS_DEL_LEFT, VS_DEL_RIGHT,                VS_DEL_LINE, VS_JUMPY, VS_COMMANDS
                                      //`--------------------------'            `--------------------------'
  ),
  
  [COMBINED] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_TILD,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC,                        KC_PLUS,   KC_7,  KC_8,   KC_9,  KC_ASTR,  KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 KC_GRAVE,  KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_UNDS,                  KC_MINUS, KC_4,  KC_5,   KC_6,  KC_SLSH,  KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 KC_CIRC,  KC_COLN,  KC_DQUO,   KC_LCBR,   KC_RCBR,     KC_AMPR,                  KC_EQUAL,  KC_1,  KC_2,   KC_3,  KC_QUES,  KC_DOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_0
                                      //`--------------------------'  `--------------------------'
  ),

  // chrome OS keyboard shortcuts: https://support.google.com/chromebook/answer/183101?hl=en
  // search key == windows key
  [BROWSER_CONTROL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                     ,-----------------------------------------------------.
KC_TRNS, KC_TRNS, KC_BTN3, KC_MS_U, KC_BTN1, KC_BTN2,                                       KC_UP, KC_PGUP, KC_PGDN, KC_MS_WH_UP, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
  CO_WS_LEFT, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,                                       KC_DOWN, RCTL(KC_PGUP), RCTL(KC_PGDN), KC_MS_WH_DOWN, LALT(KC_LEFT), CO_WS_RIGHT,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
KC_TRNS, RCTL(LSFT(KC_TAB)), RCTL(KC_TAB), WINDOWS10_WORKSPACE_LEFT, WINDOWS10_WORKSPACE_RIGHT, WINDOWS10_TASK_VIEW, KC_TRNS, RCTL(KC_1),   RCTL(KC_9), LCTL(KC_L), KC_F5, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS,  KC_TRNS, KC_TRNS,                         RCTL(KC_W), RCTL(KC_T), KC_TRNS
                                      //`--------------------------'                   `--------------------------'
  ),


  [SHORTCUTS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                             ,-----------------------------------------------------.
    KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                                MEH(KC_F1), MEH(KC_F2), MEH(KC_F3), MEH(KC_F4), MEH(KC_F5), MEH(KC_F6),
  //|--------+--------+--------+--------+--------+--------|                             |--------+--------+--------+--------+--------+--------|
    KC_F7,    KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,                               MEH(KC_F7), MEH(KC_F8), MEH(KC_F9), MEH(KC_F10), MEH(KC_F11), MEH(KC_F12),
  //|--------+--------+--------+--------+--------+--------|                             |--------+--------+--------+--------+--------+--------|
KC_TRNS, OSM(MOD_LSFT), OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), KC_TRNS,    MEH(KC_F13), MEH(KC_F14), MEH(KC_F15), MEH(KC_F16), MEH(KC_F17), MEH(KC_F18),
  //|--------+--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS,  KC_TRNS, KC_TRNS,                 KC_TRNS, TO(SHORTCUTS), TO(BASE)
                                      //`--------------------------'             `--------------------------'
  ),

  /*
  // empty layer
  [15] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),
  */


};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  // return rotation;
  return OLED_ROTATION_180;
}
  

#define DISPLAY_LAYER_NAME(LAYER_NAME, LAYER_STRING) \
  if(get_highest_layer(layer_state) == LAYER_NAME) { \
      oled_write_ln_P(PSTR(LAYER_STRING), false); \
      return;\
  }\


void oled_render_layer_state(void) {
  // if caps word is enabled, show
  if(is_caps_word_on()) {
      oled_write_ln_P(PSTR("CAPS WORD"), false);
      return;
  }
  DISPLAY_LAYER_NAME(SHORTCUTS, "SHORTCUTS");
  DISPLAY_LAYER_NAME(VSCODE, "VSCODE");
  DISPLAY_LAYER_NAME(COMBINED, "SYMBOLS");
  DISPLAY_LAYER_NAME(BROWSER_CONTROL, "BROWSER");
  DISPLAY_LAYER_NAME(SHELL_SCREEN, "SHELL SCREEN");
  DISPLAY_LAYER_NAME(SHELL_NAV, "SHELL NAV");
  DISPLAY_LAYER_NAME(KEYSEL, "KEYSEL");
  DISPLAY_LAYER_NAME(KEYNAV, "KEYNAV");
  DISPLAY_LAYER_NAME(BASE, "BASE");

}

const rgblight_segment_t PROGMEM rgb_layer_off[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 0, 0}
);

const rgblight_segment_t PROGMEM rgb_layer_blue[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_BLUE}
);

const rgblight_segment_t PROGMEM rgb_layer_purple[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM rgb_layer_red[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_RED}
);

const rgblight_segment_t PROGMEM rgb_layer_orange[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM rgb_layer_yellow[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM rgb_layer_green[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GREEN}
);

const rgblight_segment_t PROGMEM rgb_layer_pink[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_PINK}
);


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_layer_off,
    rgb_layer_blue,
    rgb_layer_purple,
    rgb_layer_red,
    rgb_layer_orange,
    rgb_layer_yellow,
    rgb_layer_green,
    rgb_layer_pink
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {


    rgblight_set_layer_state(1, layer_state_cmp(state, KEYNAV));
    rgblight_set_layer_state(2, layer_state_cmp(state, KEYSEL));    

    
    rgblight_set_layer_state(3, layer_state_cmp(state, SHELL_NAV));    
    rgblight_set_layer_state(4, layer_state_cmp(state, SHELL_SCREEN));
    
    rgblight_set_layer_state(5, layer_state_cmp(state, SHORTCUTS));
    
    rgblight_set_layer_state(6, layer_state_cmp(state, VSCODE));
    
    return state;
}

void caps_word_set_user(bool active) {
    // will enable/disable rgb layer 7 based on whether caps word is active
    rgblight_set_layer_state(7, active);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master( )) {
        oled_render_layer_state();
    } else {
        oled_render_logo();
     }
    return false;
}

#endif // OLED_ENABLE
