/*
 * BÉPO layout for 4x12 orthogonal
 * Author: Vincent Duong
 */

#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

enum layers {
  _BASE,
  _GAMING,
  _GAMING_BIS,
  _AMONG_US,
  _MUSESCORE,
  _LOWER,
  _MOUSE,
  _RAISE,
  _ADJUST,
  _AWM,
  _FUNCTIONS
};

// Tap dance declarations
enum {
    TD_YANK,
    TD_PASTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base : Bépo
 * ,-----------------------------------------------------------------------------------.
 * |   W  |   B  |   É  |   P  |   O  |   È  |   ^  |   V  |   D  |   L  |   J  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   U  |   I  |   E  |   ,  |   C  |   T  |   S  |   R  |   N  |   M  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ê/Shft|   À  |   Y  |   X  |   .  |   K  |   '  |   Q  |   G  |   H  |   F  |Ç/Shft|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | Ctrl | Alt  | GUI  |Del/- |  Space/AWM  |Ent/Ra| BckSp| AltGr| Ctrl | Mouse|
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_planck_mit(
          BP_W    , BP_B   , BP_ECUT, BP_P   ,            BP_O    ,  BP_EGRV , BP_DCRC ,            BP_V   , BP_D   , BP_L   ,                BP_J   ,       BP_Z    ,
          KC_TAB  , BP_A   , BP_U   , BP_I   ,            BP_E    ,  BP_COMM , BP_C    ,            BP_T   , BP_S   , BP_R   ,                BP_N   ,       BP_M    ,
    SFT_T(BP_ECIR), BP_AGRV, BP_Y   , BP_X   ,            BP_DOT  ,  BP_K    , BP_APOS ,            BP_Q   , BP_G   , BP_H   , LT(_FUNCTIONS, BP_F)  , SFT_T(BP_CCED),
          KC_ESC  , KC_LCTL, KC_LALT, KC_LGUI, LT(_LOWER, BP_MINS),  LT(_AWM, KC_SPACE), LT(_RAISE, KC_ENT), KC_BSPC, KC_RALT,                KC_RCTL,    TG(_MOUSE)
),

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BckSp|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shfit|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   /  | Home |  Up  |  End |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Base | Ctrl | GUI  | Alt  | Game2|    Space    |   ,  |   .  | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_mit(
    KC_ESC   , KC_Q   , KC_W   , KC_E   ,     KC_R         , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    KC_TAB   , KC_A   , KC_S   , KC_D   ,     KC_F         , KC_G   , KC_E   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT ,
    KC_LSFT  , KC_Z   , KC_X   , KC_C   ,     KC_V         , KC_B   , KC_N   , KC_M   , KC_SLSH, KC_HOME, KC_UP  , KC_END ,
    TO(_BASE), KC_LCTL, KC_LGUI, KC_LALT, OSL(_GAMING_BIS) ,     KC_SPACE    , KC_COMM, KC_DOT , KC_LEFT, KC_DOWN, KC_RGHT
),

/* Gaming 2
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   6  |   7  |   8  |   9  |   0  |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Base |      |      |      | Game |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING_BIS] = LAYOUT_planck_mit(
      KC_F1  , KC_F2  , KC_F3  , KC_F4  ,     KC_F5      , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
      KC_GRV , KC_1   , KC_2   , KC_3   ,     KC_4       , KC_5   , _______, _______, _______, _______, _______, _______,
      _______, KC_6   , KC_7   , KC_8   ,     KC_9       , KC_0   , _______, _______, _______, _______, _______, _______,
    TO(_BASE), _______, _______, _______, TG(_GAMING_BIS),     _______     , _______, _______, _______, _______, _______
),

/* Among us
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |      | Kill | UpArr| Use  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |LftArr|DwnArr|RhtArr|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Report|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_AMONG_US] = LAYOUT_planck_mit(
    KC_ESC , _______, BP_Q   , KC_UP  , BP_E   , _______, _______, _______, _______, _______, _______,    _______,
    _______, KC_TAB , KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, C(S(BP_M)),
    _______, _______, _______, _______, BP_R   , _______, _______, _______, _______, _______, _______,    _______,
    _______, _______, _______, _______, _______,     _______     , _______, _______, _______, _______, TO(_BASE)
),

/* Musescore
 * ,-----------------------------------------------------------------------------------.
 * | Redo |PrvBar|NxtBar| Decr | Cresc|      |   0  |   C  |   D  |   E  |   F  | Undo |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Triplt|  1/2 |  1/4 |  1/8 | 1/16 | 1/32 | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Marcto|Accent|Tenuto| Stacc|Phrase| Notes|   G  |   A  |   B  |Repeat|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MUSESCORE] = LAYOUT_planck_mit(
    S(C(BP_Z)), C(KC_LEFT), C(KC_RGHT),   KC_GT,   KC_LT, _______, BP_0   , BP_C   , BP_D   , BP_E   , BP_F   , C(BP_Z),
      C(BP_3) ,   BP_7    ,   BP_6    ,   BP_5 ,   BP_4 , BP_3   , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,  _______,
      _______ , S(BP_O)   , S(BP_V)   , S(BP_N), S(BP_S), BP_S   , BP_N   , BP_G   , BP_A   , BP_B   , BP_R   , _______,
      _______ ,   _______ ,   _______ , _______, _______,     _______     , _______, _______, _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      | Paste|      |      |   €  |   7  |   8  |   9  |   /  | Bsp  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |CapsLo|AutoKp|      |      |   0  |   $  |   #  |   4  |   5  |   6  |   *  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Yank |      |      |      |   %  |   1  |   2  |   3  |   -  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |   ,  |   0  |   .  |   +  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_mit(
    _______,    _______,    _______ , TD(TD_PASTE), _______, _______, BP_EURO,            BP_7    , BP_8   , BP_9   , BP_SLSH, KC_BSPC,
    KC_CAPS, C(A(BP_A)),    _______ ,     _______ , BP_0   , BP_DLR , BP_HASH,            BP_4    , BP_5   , BP_6   , BP_ASTR, BP_EQL ,
    _______,    _______, TD(TD_YANK),     _______ , _______, _______, BP_PERC,            BP_1    , BP_2   , BP_3   , BP_MINS, KC_ENT ,
    _______,    _______,    _______ ,     _______ , _______,     _______     , LT(_RAISE, BP_COMM), BP_0   , BP_DOT , BP_PLUS, XXXXXXX
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |  Up  |      |      |      |Accel2|Accel1|Accel0|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Left | Down | Right|      |ScrolL|ScrolD|ScrolU|ScrolR|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Base |      |      |      |      |Middle Click |LftClk|RhtClk|      |      | Base |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_mit(
      _______, _______, _______, KC_MS_U, _______, _______, _______, KC_ACL2, KC_ACL1, KC_ACL0, _______, _______,
      _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    TO(_BASE), _______, _______, _______, _______,     KC_BTN3     , KC_BTN1, KC_BTN2, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   &  |   <  |   >  |   [  |   ]  |      |      |   +  |   -  |   /  |   *  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   |  |   ^  |   \  |   (  |   )  |   $  |LftArr|DwnArr| UpArr|RhtArr|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shft |   «  |   »  |   {  |   }  |   ~  |   "  |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      _      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_mit(
    BP_AMPR , BP_LESS, BP_GRTR, BP_LBRC, BP_RBRC, BP_AT  , _______, BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR, BP_EQL ,
    BP_PIPE , BP_CIRC, BP_BSLS, BP_LPRN, BP_RPRN, BP_DLR , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT,_______,  _______,
    KC_LSFT , BP_LGIL, BP_RGIL, BP_LCBR, BP_RCBR, BP_TILD, BP_DQOT, _______, _______, _______, _______, _______,
    _______ , _______, _______, _______, _______,     BP_UNDS     , _______, _______, _______, _______, _______
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * | Reset| Debug|      | Vol+ |      |PtScrn|CpScrn|      |Brght+| Hue -| Hue +|RgbTgl|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Game |AmngUs| Prev | Vol- | Next | PtSel| CpSel| Play |Brght-|Satur-|Satur+|RgbMod|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Mscz |      | Mute |      |PtWndw|CpWndw|      |      |Value-|Value+|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Base |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_mit(
        RESET  ,    DEBUG      , _______, KC_VOLU, _______,   KC_PSCR ,   C(KC_PSCR) , _______, KC_BRIU, RGB_HUD, RGB_HUI, RGB_TOG,
    TO(_GAMING), TG(_AMONG_US) , KC_MPRV, KC_VOLD, KC_MNXT, S(KC_PSCR), S(C(KC_PSCR)), KC_MPLY, KC_BRID, RGB_SAD, RGB_SAI, RGB_MOD,
        _______, TG(_MUSESCORE), _______, KC_MUTE, _______, A(KC_PSCR), A(C(KC_PSCR)), _______, _______, RGB_VAD, RGB_VAI, _______,
    TO(_BASE)  ,    _______    , _______, _______, _______,         _______          , _______, _______, _______, _______, _______
),

/* AwesomeWM : Modkey active
 * ,-----------------------------------------------------------------------------------.
 * |LstTag| Tag 1| Tag 2| Tag 3| Tag 4| Tag 5| Tag 6| Tag 7| Tag 8| Tag 9|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Rofi |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |KilCli|      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_AWM] = LAYOUT_planck_mit(
    KC_ESC ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  , _______, _______,
    _______, _______, _______, _______,  BP_P  , _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    S(BP_Y), _______, _______, _______, _______,     _______     , _______, _______, _______, _______, _______
),

/* Function keys
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      | Ctrl |  Alt |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTIONS] = LAYOUT_planck_mit(
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______, _______, KC_LCTL, KC_LALT, _______, _______, _______,
    _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______     , _______, _______, _______, _______, _______
)

};

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_GAMING] = {
        {  0,  0,  0},{  0,  0,  0},{ HSV_PURPLE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{ HSV_PURPLE},{ HSV_PURPLE},{ HSV_PURPLE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{ HSV_PURPLE},{  0,  0,  0},
        {  HSV_WHITE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{       0,  0,  0}         ,{  0,  0,  0},{  0,  0,  0},{ HSV_PURPLE},{ HSV_PURPLE},{ HSV_PURPLE} },

    [_GAMING_BIS] = {
        {   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},{   HSV_BLUE},
        {  0,  0,  0},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  HSV_WHITE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{       0,  0,  0}         ,{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0} },

    [_AMONG_US] = {
        {   HSV_BLUE},{  0,  0,  0},{         HSV_RED},{ HSV_SPRINGGREEN},{        HSV_GOLD},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{   HSV_BLUE},{ HSV_SPRINGGREEN},{ HSV_SPRINGGREEN},{ HSV_SPRINGGREEN},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{       0,  0,  0},{       0,  0,  0},{      HSV_PURPLE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{       0,  0,  0},{       0,  0,  0},{       0,  0,  0},      {  0,  0,  0}        ,{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  HSV_WHITE} },

    [_MUSESCORE] = {
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{HSV_SPRINGGREEN},{HSV_SPRINGGREEN},{HSV_SPRINGGREEN},{HSV_SPRINGGREEN},{HSV_SPRINGGREEN},{  0,  0,  0},
        {  0,  0,  0},{   HSV_GOLD},{   HSV_GOLD},{   HSV_GOLD},{   HSV_GOLD},{   HSV_GOLD},{     HSV_PURPLE},{     HSV_PURPLE},{     HSV_PURPLE},{     HSV_PURPLE},{      0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{      0,  0,  0},{HSV_SPRINGGREEN},{HSV_SPRINGGREEN},{HSV_SPRINGGREEN},{      0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},         {  0,  0,  0}         ,{      0,  0,  0},{      0,  0,  0},{      0,  0,  0},{      0,  0,  0},{  0,  0,  0} },

    [_LOWER] = {
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{   HSV_BLUE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{   HSV_PINK},{   HSV_PINK},{   HSV_PINK},{  HSV_YELLOW},{  0,  0,  0},
        {  HSV_WHITE},{  HSV_GREEN},{  0,  0,  0},{  0,  0,  0},{   HSV_PINK},{  0,  0,  0},{  0,  0,  0},{   HSV_PINK},{   HSV_PINK},{   HSV_PINK},{  HSV_YELLOW},{  HSV_YELLOW},
        {  0,  0,  0},{  0,  0,  0},{   HSV_BLUE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{   HSV_PINK},{   HSV_PINK},{   HSV_PINK},{  HSV_YELLOW},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  HSV_WHITE},      {  0,  0,  0}        ,{  0,  0,  0},{   HSV_PINK},{  0,  0,  0},{  HSV_YELLOW},{  0,  0,  0} },

    [_MOUSE] = {
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  HSV_GREEN},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{ HSV_PURPLE},{ HSV_PURPLE},{ HSV_PURPLE},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  0,  0,  0},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  HSV_WHITE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},      {  HSV_GOLD}         ,{   HSV_GOLD},{   HSV_GOLD},{  0,  0,  0},{  0,  0,  0},{  HSV_WHITE} },

    [_RAISE] = {
        { HSV_YELLOW},{  0,  0,  0},{  0,  0,  0},{   HSV_CYAN},{   HSV_CYAN},{  0,  0,  0},{  0,  0,  0},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},
        { HSV_YELLOW},{ HSV_YELLOW},{  0,  0,  0},{   HSV_CYAN},{   HSV_CYAN},{  0,  0,  0},{ HSV_PURPLE},{ HSV_PURPLE},{ HSV_PURPLE},{ HSV_PURPLE},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{   HSV_CYAN},{   HSV_CYAN},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},      {  0,  0,  0}        ,{  HSV_WHITE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0} },

    [_ADJUST] = {
        {    HSV_RED},{       0,  0,  0},{  0,  0,  0},{   HSV_GOLD},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{   HSV_GOLD},{  0,  0,  0},{  0,  0,  0},{  HSV_WHITE},
        { HSV_PURPLE},{ HSV_SPRINGGREEN},{   HSV_BLUE},{   HSV_GOLD},{   HSV_BLUE},{  0,  0,  0},{  0,  0,  0},{   HSV_BLUE},{   HSV_GOLD},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{ HSV_SPRINGGREEN},{  0,  0,  0},{   HSV_GOLD},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  HSV_WHITE},{       0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  HSV_WHITE},      {  0,  0,  0}        ,{  HSV_WHITE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0} },

    [_AWM] = {
        {  0,  0,  0},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  HSV_GREEN},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        { HSV_YELLOW},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},      {  HSV_WHITE}        ,{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0} },

    [_FUNCTIONS] = {
        {  0,  0,  0},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{  0,  0,  0},{  0,  0,  0},{  HSV_WHITE},{  HSV_WHITE},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},
        {  0,  0,  0},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{ HSV_YELLOW},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  HSV_WHITE},{  0,  0,  0},
        {  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},      {  0,  0,  0}        ,{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0},{  0,  0,  0} }
};

void set_layer_color(int layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
    if (!hsv.h && !hsv.s && !hsv.v) {
        continue;
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
    /* Set layer colors only if the lights are enabled */
    if (rgb_matrix_config.enable) {
        uint8_t layer = biton32(layer_state);
        switch (layer) {
            case _AMONG_US:
                set_layer_color(_AMONG_US);
            break;
            case _GAMING:
                set_layer_color(_GAMING);
            break;
            case _GAMING_BIS:
                set_layer_color(_GAMING_BIS);
            break;
            case _MUSESCORE:
                set_layer_color(_MUSESCORE);
            break;
            case _LOWER:
                set_layer_color(_LOWER);
            break;
            case _MOUSE:
                set_layer_color(_MOUSE);
            break;
            case _RAISE:
                set_layer_color(_RAISE);
            break;
            case _ADJUST:
                set_layer_color(_ADJUST);
            break;
            case _AWM:
                set_layer_color(_AWM);
            break;
            case _FUNCTIONS:
                set_layer_color(_FUNCTIONS);
            break;
            default:
                if (rgb_matrix_get_flags() == LED_FLAG_NONE)
                    rgb_matrix_set_color_all(0, 0, 0);
            break;
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = biton32(state);
    switch (layer) {
        /* LGUI modkey active for awesomeWM bindings */
        case _AWM:
            set_mods(MOD_BIT(KC_LGUI));
            break;
        default:
            clear_mods();
    }
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return state;
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_YANK]  = ACTION_TAP_DANCE_DOUBLE(C(KC_INS), C(BP_C)),
    [TD_PASTE] = ACTION_TAP_DANCE_DOUBLE(S(KC_INS), C(BP_V))
};

void press_key(uint16_t key) {
  register_code(key);
  unregister_code(key);
}

void press_two_keys(uint16_t key1, uint16_t key2) {
  register_code(key1);
  register_code(key2);
  unregister_code(key2);
  unregister_code(key1);
}

void press_three_keys(uint16_t key1, uint16_t key2, uint16_t key3) {
  register_code(key1);
  register_code(key2);
  register_code(key3);
  unregister_code(key3);
  unregister_code(key2);
  unregister_code(key1);
}

