/*

██████       █████  ████████▖    ▗████████     ▗█████▘ ██████  ██████▌        ▝██████
█▓██▓█     ▂▟█▓██▘  █▓██▓████▖  ▗████▓██▓█    ▗█▓█▓█▘  █▓██▓█ ▐█▓██▓█          █▓██▓█▌
█▓▓▓▓█▀▀▀▀█▓▓▓▓█▄   █▓▓▓▓█▝█▓█▖▗█▓█▘█▓▓▓▓█   ▗█▓▓▓█▘   █▓▓▓▓█ █▓▓▓▓█▌          ▐█▓▓▓▓█
█▓▓▓▓█     ▀█▓▓▓▓█▖ █▓▓▓▓█ ▝█▓▓▓▓█▘ █▓▓▓▓█  ▗█▓▓▓█▘    █▓▓▓▓█ █▓▓▓▓█▌          ▐█▓▓▓▓█
█▒▓▓▒█      ▝█▒▓▓▒█▖█▒▓▓▒█  ▝█▓▓█▘  █▒▓▓▒█ ▗█▒▓▓█▘     █▒▓▓▒█ █▒▓▓▒█▌          ▐█▒▓▓▒█
█▒▒▒▒█       ▝█▒▒▒▒██▒▒▒▒█   ▝██▘   █▒▒▒▒█▗█▒▒▒█▘      █▒▒▒▒█ ▐█▒▒▒▒█          █▒▒▒▒█▌
█▒▒▒▒█        █▒▒▒▒██▒▒▒▒█    ▝▘    █▒▒▒▒███████▄▄▄▄▄▄▄█▒▒▒▒█▄▄█▒▒▒▒█▖        ▗█▒▒▒▒█▄▄
█░░░░█       ▟█░░░█▘█░░░░█          █░░░░█             █░░░░█   ▀█░░░█▖      ▗█░░░█▀
█▄▄▄▄█▄▄▄▄▄▆██▄▄█▀  █▄▄▄▄█          █▄▄▄▄█             █▄▄▄▄█     ▀█▄▄█▆▄▄▄▄▆█▄▄█▀
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>

enum layers {
  _BASE,
  _LOWER,
  _LOW_AE,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  LOW_AE,
  RAISE,
  MAKE_H,
  M_AE,
  M_UE,
  M_OE,
  M_EU,
  SNAP1,
  SNAP2,
  WMAIL,
  GMAIL,
  GIPHY,
  AE_MOD,
  AE_TRIM,
  AE_SLD,
  AE_ADJ,
  PRT_MAP,
  CD_QMK,
  OS_SWAP
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)


// RGB vars

bool rgbs_on;
int rgbs_mode;
HSV rgbs_hsv;
bool rgbs_set = false;


// ╭───────────────────────────────────────────────────────────╮
// │ i n t   v a r s                                           │
// ╰───────────────────────────────────────────────────────────╯


bool int_press = false;
bool interrupt = false;
char int_code[24];
char int_replacement_code[24];
static uint16_t int_duration;
static uint16_t int_timer;


bool AEmod = false;

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ K E Y M A P S                                                                                                          ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
// ▐████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████▌

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
   ┃ b a s e                                                   ┃
   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
   ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
   ┃   TAB   ┃    Q    ┃    W    ┃    E    ┃    R    ┃    T    ┃    Y    ┃    U    ┃    I    ┃    O    ┃    ;    ┃    \    ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃  GESC   ┃    A    ┃    S    ┃    D    ┃    F    ┃    G    ┃    H    ┃    J    ┃    K    ┃    L    ┃    P    ┃    "    ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃  SHIFT  ┃    Z    ┃    X    ┃    C    ┃    V    ┃    B    ┃    N    ┃    M    ┃    ,    ┃    .    ┃    /    ┃  SHIFT  ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃   DEL   ┃  CTRL   ┃   ALT   ┃   GUI   ┃  LOWER  ┃       SPACE       ┃  RAISE  ┃  BSPACE ┃    !    ┃   VOL-  ┃   VOL+  ┃
   ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
 */

[_BASE] = LAYOUT_planck_mit(
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_SCLN,  KC_BSLS,  \
    KC_GESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_P,     KC_QUOT, \
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, \
    KC_DEL,   KC_LCTL,  KC_LALT,  KC_LGUI,  LOWER,    KC_SPC,             RAISE,    KC_BSPC,  KC_EXLM,  KC_VOLD,  KC_VOLU  \
),

/*
   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
   ┃ l o w e r                                                 ┃
   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
   ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
   ┃  CAPSL  ┃    @    ┃    &    ┃   UP    ┃    #    ┃    {    ┃    }    ┃    +    ┃    7    ┃    8    ┃    9    ┃         ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃ AE MOD  ┃    %    ┃  LEFT   ┃  DOWN   ┃  RIGHT  ┃    [    ┃    ]    ┃    -    ┃    4    ┃    5    ┃    6    ┃         ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃         ┃         ┃  PGUP   ┃         ┃  PGDWN  ┃    (    ┃    )    ┃    *    ┃    1    ┃    2    ┃    3    ┃         ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃  SNAP2  ┃  SNAP1  ┃         ┃         ┃         ┃       ENTER       ┃         ┃    0    ┃    =    ┃  MUTE   ┃  PLAY   ┃
   ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
 */

[_LOWER] = LAYOUT_planck_mit(
    KC_CAPS,  KC_AT,    KC_AMPR,  KC_UP,    KC_HASH,  KC_LCBR,  KC_RCBR,  KC_PLUS,  KC_P7,    KC_P8,    KC_P9,    XXXXXXX, \
    AE_MOD,   KC_PERC,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_LBRC,  KC_RBRC,  KC_MINS,  KC_P4,    KC_P5,    KC_P6,    XXXXXXX, \
    _______,  XXXXXXX,  KC_PGUP,  XXXXXXX,  KC_PGDN,  KC_LPRN,  KC_RPRN,  KC_ASTR,  KC_P1,    KC_P2,    KC_P3,    _______, \
    SNAP2,    SNAP1,    _______,  _______,  _______,  KC_ENT,             _______,  KC_P0,    KC_EQL,   KC_MUTE,  KC_MPLY  \
),

/*
   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
   ┃ l o w  a e                                                ┃
   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
   ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
   ┃  CAPSL  ┃         ┃    &    ┃   UP    ┃    #    ┃    {    ┃    }    ┃    +    ┃    7    ┃    8    ┃    9    ┃ ADJ/NUL ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃ AE MOD  ┃    %    ┃  LEFT   ┃  DOWN   ┃  RIGHT  ┃    [    ┃    ]    ┃    -    ┃    4    ┃    5    ┃    6    ┃ SLD/SHP ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃         ┃  CACHE  ┃  PGUP   ┃         ┃  PGDWN  ┃    (    ┃    )    ┃    *    ┃    1    ┃    2    ┃    3    ┃         ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃  SNAP1  ┃  SNAP2  ┃         ┃         ┃         ┃       ENTER       ┃         ┃    0    ┃    =    ┃  MUTE   ┃  PLAY   ┃
   ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
 */

[_LOW_AE] = LAYOUT_planck_mit(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_7,     KC_8,     KC_9,     AE_ADJ, \
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_4,     KC_5,     KC_6,     AE_SLD, \
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_1,     KC_2,     KC_3,     _______, \
    KC_F5,    KC_F6,    _______,  _______,  _______,  _______,            _______,  KC_0,     _______,  _______,  _______  \
),

/*
   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
   ┃ r a i s e                                                 ┃
   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
   ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
   ┃  CAPSL  ┃         ┃         ┃   EU    ┃         ┃         ┃   YEN   ┃    Ü    ┃         ┃    Ö    ┃         ┃         ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃         ┃    Ä    ┃   SZ    ┃    $    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃         ┃         ┃         ┃   CUE   ┃         ┃         ┃         ┃         ┃         ┃ DM REC1 ┃ DM STOP ┃ DM PLY1 ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃   WEB   ┃   GMX   ┃         ┃  GIPHY  ┃         ┃       DELETE      ┃         ┃         ┃ DM REC2 ┃ DM STOP ┃ DM PLY2 ┃
   ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
 */
[_RAISE] = LAYOUT_planck_mit(
   KC_CAPS,  XXXXXXX,  XXXXXXX,   M_EU,     XXXXXXX,  XXXXXXX,  LALT(KC_Y),M_UE,    XXXXXXX,  M_OE,     XXXXXXX,  XXXXXXX, \
   XXXXXXX,  M_AE,     RALT(KC_S),KC_DLR,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
   _______,  XXXXXXX,  XXXXXXX,  LALT(KC_C),XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DM_REC1,  DM_RSTP,  DM_PLY1, \
   WMAIL,    GMAIL,    _______,   GIPHY,    _______,  KC_DEL,             _______,  _______,  DM_REC2,  DM_RSTP,  DM_PLY2  \
),

/*
   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
   ┃ a d j u s t                                               ┃
   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
   ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
   ┃  RESET  ┃  DEBUG  ┃   RGB   ┃ RGB MOD ┃  HUE+   ┃  SAT+   ┃ BRGTH+  ┃ SPEED+  ┃   F7    ┃   F8    ┃   F9    ┃         ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃  MAKE   ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃   F4    ┃   F5    ┃   F6    ┃         ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃  QMK    ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃   F1    ┃   F2    ┃   F3    ┃         ┃
   ┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┻━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫
   ┃ OS SWAP ┃         ┃         ┃         ┃         ┃                   ┃         ┃   F10   ┃   F11   ┃   F12   ┃         ┃
   ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛
 */
[_ADJUST] = LAYOUT_planck_mit(
    RESET,    DEBUG,    RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,   KC_F7,     KC_F8,    KC_F9,    XXXXXXX,
    MAKE_H,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_F4,     KC_F5,    KC_F6,    XXXXXXX,
    CD_QMK,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_F1,     KC_F2,    KC_F3,    _______,
    OS_SWAP,  _______,  _______,  _______,  _______,  _______,            _______,   KC_F10,    KC_F11,   KC_F12,   XXXXXXX
  )

};

void matrix_scan_user(void) {
   // Interrupted Press
   if(int_press) {
      if (timer_elapsed(int_timer) > int_duration) {
            send_string (int_replacement_code);
            interrupt = true;
            int_press = false;
       }
    }
 }



// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ F U N C T I O N S                                                                                                                         ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
// ▐███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████▌


// ╭───────────────────────────────────────────────────────────╮
// │ i n t e r r u p t e d   p r e s s                         │
// ╰───────────────────────────────────────────────────────────╯

bool replace_on_hold_int(const char code[24], const char replacement_code[24], uint16_t duration, bool pressed) {
  if(pressed) {
      int_press = true;
      interrupt = false;
      strcpy (int_code, code);
      strcpy (int_replacement_code, replacement_code);
      int_duration = duration;
      int_timer = timer_read();
    }
  else {
      if(interrupt == false) {
        send_string (code);
        int_press = false;
      }
    }
  return false;
}


// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ L E D S                                                                                                                                   ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
// ▐███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████▌

bool capsSetMac = false;

void rgb_matrix_indicators_user(void) {

// WINDOWS ├─────────────────────────────────────────────────────────────┐

  if(keymap_config.swap_lctl_lgui && IS_LAYER_ON(_ADJUST)) {
    rgb_matrix_set_color(36, 1, 120, 214);
  }

// MAC ├─────────────────────────────────────────────────────────────────┐

  if(keymap_config.swap_lctl_lgui == false && IS_LAYER_ON(_ADJUST)) {
    rgb_matrix_set_color(36, 255, 132, 0);
  }

// CAPSLOCK ├───────────────────────────────────────────────────────────┐

  if (keymap_config.swap_lctl_lgui) {  // if win
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
      rgb_matrix_set_color(0, 255, 0, 48);
    }
  }
  else {
    if (capsSetMac) {
      rgb_matrix_set_color(0, 255, 0, 48);
    }
  }

// AE ├─────────────────────────────────────────────────────────────────┐

  if(AEmod) {
    rgb_matrix_set_color(12, 92, 70, 255);
  }
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ M A C R O S                                                                                                                               ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
// ▐███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████▌


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
      case LOWER:
            if (record->event.pressed) {
                if (AEmod) {
                  layer_on(_LOW_AE);
                }
              return true;
            }
            layer_off(_LOW_AE);
            break;

      case KC_VOLU:
            return replace_on_hold_int(SS_TAP(X_VOLU), SS_TAP(X_MNXT), 400, record->event.pressed);

      case KC_VOLD:
            return replace_on_hold_int(SS_TAP(X_VOLD), SS_TAP(X_MPRV), 400, record->event.pressed);

      case OS_SWAP:
            if (record->event.pressed) {
                if (!keymap_config.swap_lctl_lgui) {
                  keymap_config.swap_lctl_lgui = true;  //WIN
                }
                else {
                  keymap_config.swap_lctl_lgui = false; //MAC
                }
            eeconfig_update_keymap(keymap_config.raw);
            clear_keyboard();  // clear to prevent stuck keys
            return false;
          }

      case KC_CAPS:
          if (record->event.pressed) {
            capsSetMac ^= 1;
            return true;
          }

      case AE_MOD:
          if (record->event.pressed) {
            AEmod ^= 1;
            return true;
          }

      case AE_SLD:
          if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) {
              SEND_STRING(SS_LCTL("y"));                  //WIN
            } else {
              SEND_STRING(SS_LCMD("y"));                  //MAC
            }
          }
          break;

      case AE_ADJ:
          if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) {
              SEND_STRING(SS_LALT(SS_LCTL("y")));         //WIN
            } else {
              SEND_STRING(SS_LALT(SS_LCMD("y")));         //MAC
            }
          }
          break;


      case DM_REC1:
          if (record->event.pressed) {
            rgbs_on = rgb_matrix_is_enabled();
            rgbs_mode = rgb_matrix_get_mode();
            rgbs_hsv = rgb_matrix_get_hsv();
            rgbs_set = true;

            rgb_matrix_enable();
            rgb_matrix_mode(1);
            rgb_matrix_sethsv(0, 255, 255);
            return true;
          }

      case DM_REC2:
          if (record->event.pressed) {
            rgbs_on = rgb_matrix_is_enabled();
            rgbs_mode = rgb_matrix_get_mode();
            rgbs_hsv = rgb_matrix_get_hsv();
            rgbs_set = true;

            rgb_matrix_enable();
            rgb_matrix_mode(1);
            rgb_matrix_sethsv(0, 255, 255);
            return true;
          }

      case DM_RSTP:
          if (record->event.pressed) {
            if (rgbs_set) {
                if (!rgbs_on) { rgb_matrix_disable(); }
                rgb_matrix_mode(rgbs_mode);
                rgb_matrix_sethsv(rgbs_hsv.h, rgbs_hsv.s,rgbs_hsv.v);
                rgbs_set = false;
            }
            return true;
          }

      case SNAP1:
          if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) {
              SEND_STRING(SS_LWIN(SS_TAP(X_PSCR)));         //WIN
            } else {
              SEND_STRING(SS_LSFT(SS_LCMD("4")));           //MAC
            }
          }
          break;

      case SNAP2:
          if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) {
              SEND_STRING(SS_LSFT(SS_LWIN("S")));           //WIN
            } else {
              SEND_STRING(SS_LSFT(SS_LCMD(SS_LCTL("4"))));  //MAC
            }
          }
          break;

      case MAKE_H:
          if (record->event.pressed) {
            SEND_STRING ("make bm40hsrgb:schwarz");
            tap_code(KC_ENTER);
          }
          break;

      case CD_QMK:
          if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) {
              SEND_STRING("cd /Users/igiti/qmk_firmware"); //WIN
              tap_code(KC_ENTER);
            } else {
              SEND_STRING("cd qmk_firmware");              //MAC
              tap_code(KC_ENTER);
            }
          }
          break;

      case M_AE:
          if (record->event.pressed) {
            SEND_STRING(SS_LSFT("'")"a");
          }
          break;

      case M_UE:
          if (record->event.pressed) {
            SEND_STRING(SS_LSFT("'")"u");
          }
          break;

      case M_OE:
          if (record->event.pressed) {
            SEND_STRING(SS_LSFT("'")"o");
          }
          break;

      case M_EU:
          if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) {
              SEND_STRING(SS_LALT("5"));                   //WIN
            } else {
              SEND_STRING(SS_LALT(SS_LSFT("2")));          //MAC
            }
          }
          break;

      case WMAIL:
          if (record->event.pressed) {

            SEND_STRING ("igit.igit@web.de");
          }
          break;

      case GMAIL:
          if (record->event.pressed) {
            SEND_STRING ("igit@gmx.de");
          }
          break;

      case GIPHY:
          if (record->event.pressed) {
            SEND_STRING ("@gif ");
          }
          break;
      }
    return true;
};


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
