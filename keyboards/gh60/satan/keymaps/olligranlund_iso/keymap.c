#include QMK_KEYBOARD_H

#define BASE    0    // Default layer
#define MOUSE   1    // Space layer
#define NUMPAD  2    // Alt layer
#define CAPS    3    // Caps layer

// General shortenings
#define ESCA KC_ESC
#define MINS KC_MINS
#define EQUL KC_EQL
#define BSPC KC_BSPC
#define DELE KC_DEL
#define LBRC KC_LBRC
#define RBRC KC_RBRC
#define ALTR KC_RALT
#define SCLN KC_SCLN
#define QUOT KC_QUOT
#define NUHS KC_NUHS
#define ENTE KC_ENT
#define NUBS KC_NUBS  // Less/ greater sign
#define COMM KC_COMM  // Comma
#define FSTO KC_DOT   // Full stop
#define SLSH KC_SLSH
#define ALTL KC_LALT
#define GUIL KC_LGUI
#define GUIR KC_RGUI
#define MENO KC_MENU

// Special Actions and Media Keys
#define INSE KC_INS   // Insert here
#define HOME KC_HOME  // Go to beginning of line
#define ENDI  KC_END  // go to end of line
#define PSCR  KC_PSCR   // Print Screen
#define SLCK  KC_SCRL   // go to end of line
#define PGDN  KC_PGDN   // go to end of line
#define PGUP  KC_PGUP   // go to end of line
#define PLPS KC_MPLY  // Play/Pause
#define PAUS KC_PAUS  // Pause button
#define MUTE KC_MUTE  // Mute sound
#define VOLU KC_VOLU  // Volume increase
#define VOLD KC_VOLD  // Volume decrease
#define MNXT KC_MNXT  // next track
#define MPRV KC_MPRV  // prev track
#define MSTP KC_MSTP  // stop playing
#define MSEL KC_MSEL  // Select media (Start playing it)
#define MAIL KC_MAIL  // Open default mail app
#define CALC KC_CALC  // Open default calculator app
#define MYCM KC_MYCM  // Open default file manager

// increase readability
#define XXXXX    KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap BASE: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  R  |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| # | R |
   * |-----------------------------------------------------------|
   * |Shft| \ |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space            |Alt |Gui |FN  |Ctrl |
   * `-----------------------------------------------------------|
   */

[ BASE ] = KEYMAP_ISO_SPLITRSHIFT(
  KC_ESC,         KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,      KC_BSPC, \
  KC_TAB,         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,     XXXXX,    \
  LT(CAPS, KC_CAPS), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT, KC_NUHS,     KC_ENT,  \
  KC_LSFT,        KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RSFT,     XXXXX, \
  KC_LCTL,        KC_LGUI,KC_LALT,                KC_SPC,                     KC_RALT, MO(CAPS), TG(NUMPAD),    TG(MOUSE)),

[ MOUSE ] = KEYMAP( // Mouse controls
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXX,\
		_______, _______, _______, _______, _______, _______, _______, KC_MS_BTN1, KC_MS_U, KC_MS_BTN2, _______, _______, _______, _______,\
		_______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______,\
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXX,\
		_______, _______, _______,           _______,           _______, _______, _______, _______),

[ NUMPAD ] = KEYMAP( //Numpad and alt shortcuts
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXX,\
        _______, BL_TOGG, BL_DOWN,BL_UP,  _______, _______, _______, KC_1, KC_2, KC_3, _______, _______, _______, _______,\
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, _______, _______, KC_4, KC_5, KC_6, _______, _______, _______, _______,\
        _______, _______, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_7, KC_8, KC_9, KC_0, _______, _______, XXXXX,\
        _______, _______, _______,           _______,             _______, _______, _______, _______),

[ CAPS ] = KEYMAP( // Main "function" key, arrows, media control
        KC_GRAVE, KC_F1,  KC_F2,    KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, XXXXX,\
        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, PGDN, KC_UP, PGUP, PSCR, SLCK, PAUS, _______,\
        _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______,\
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXX,\
        _______, _______, _______,           _______,           _______, _______, _______, _______)

};
