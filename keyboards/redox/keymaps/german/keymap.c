#include QMK_KEYBOARD_H
#include "keymap_german.h"

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _NAV 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMB,
  NAV,
  ADJUST,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,------------------------------------------------.            ,------------------------------------------------.
 * |^/Lyr2|   1  |   2  |   3  |   4  |   5  | Lyr1 |            | Lyr1 |   6  |   7  |   8  |   9  |   0  |--Lyr2|
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |  `   |            |   +  |   Y  |   U  |   I  |   O  |   P  |   =  |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  | PgUp |            | End  |   H  |   J  |   K  |   L  |   Ö  |   Ä  |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | PgDn |            | Home |   N  |   M  |   ,  |   .  |   -  |Shift |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * |  Gui |   <  |   #  |*(Alt)|/(Ctr)|Bcksp | Del  |            |Enter |Space |  Alt | Left | Down |  Up  | Right|
 * `------------------------------------------------'            `------------------------------------------------'
 */
  [_QWERTY] = LAYOUT(
  //,----+----+----+----+----+----+----.                                                         ,----+----+----+----+----+----+----.
     LT(_NAV, DE_CIRC) , DE_1  , DE_2  , DE_3  , DE_4  , DE_5  ,MO(_SYMB),                           MO(_SYMB), DE_6  , DE_7  , DE_8  , DE_9  , DE_0  ,LT(_NAV, DE_SS),
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
     KC_TAB , DE_Q  , DE_W  , DE_E  , DE_R  , DE_T  , DE_ACUT,                                       DE_PLUS , DE_Z  , DE_U  , DE_I  , DE_O  , DE_P  , DE_UE,
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
     KC_ESC , DE_A  , DE_S  , DE_D  , DE_F  , DE_G  , LT(_ADJUST, KC_PGUP),                         LT( _ADJUST, KC_END) , DE_H  , DE_J  , DE_K  , DE_L  , DE_OE , DE_AE,
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
     KC_LSFT, DE_Y  , DE_X  , DE_C  , DE_V  , DE_B  ,KC_PGDN,                                      KC_HOME , DE_N  , DE_M  , DE_COMM, DE_DOT , DE_MINS , KC_RSFT,
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
     KC_LGUI , DE_LESS , DE_HASH , LALT_T(KC_KP_PLUS),LCTL_T(KC_KP_ASTERISK),KC_BSPC,KC_DEL ,                     KC_ENT , KC_SPC, DE_ALGR , KC_LEFT, KC_DOWN, KC_UP , KC_RGHT
  //`----+----+----+----+----+----+----'                                                         `----+----+----+----+----+----+----'
  ),

/* Symbols
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |      |      |      |      |   7  |   8  |   9  |      | F12  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   #  |   $  |   [  |   ]  |   ~  |      |      |      |      |   4  |   5  |   6  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Shift|   %  |   ^  |   (  |   )  |   `  |      |      |      |      |   1  |   2  |   3  |      |Shift |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      | Alt  | Ctrl |      |      |      |      |      |   0  |   0  |   .  |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */

  [_SYMB] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                             _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, 
    _______, DE_EXLM, DE_AT ,  DE_LCBR, DE_RCBR, DE_PIPE, _______,                             _______, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX, KC_F12, 
    _______, DE_HASH, DE_DLR , DE_LBRC, DE_RBRC, DE_TILD,  _______,                             _______, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX, XXXXXXX, 
    KC_LSFT, DE_PERC, DE_CIRC, DE_LPRN, DE_RPRN, DE_GRV, _______,                             _______, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, XXXXXXX, KC_RSFT, 
    _______, _______, _______, KC_LALT, KC_LCTL, _______, _______,                             _______, _______, KC_KP_0, KC_KP_0, KC_PDOT, XXXXXXX, XXXXXXX 
  ),

/* Navigation
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |MOUS_U|      |WHEL_U|      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |MOUS_L|MOUS_D|MOUS_R|WHEL_D|      |      |      |      | LEFT | DOWN |  UP  |RIGHT |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |MOUS_1|MOUS_2|      |      |      |      |      |      |      |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
    XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, KC_WH_U, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX, _______,                            _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT,XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, _______,                            _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_ADJUST] = LAYOUT(
    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,
    XXXXXXX, RESET  , RGB_M_P, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,                            RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXXXXX, KC_DEL,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )

};
