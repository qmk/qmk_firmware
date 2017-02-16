#include "kinesis.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _DV 0 // Dvorak layer
#define _QW 1 // Qwerty layer
#define _CM 2 // Colemak layer
#define _LO 3 // Media Layer
#define _RA 4 // Keypad Layer

// Macro name shortcuts
#define DVORAK M(_DV)
#define QWERTY M(_QW)
#define COLEMAK M(_CM)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

/****************************************************************************************************
*
* Keymap: Default Layer in Qwerty
*
* ,-------------------------------------------------------------------------------------------------------------------.
* | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |  FN0 |  BOOT  |
* |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
* | =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | -_     |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | \|     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Caps   |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |  ;:  | '"     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Shift  |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |  ,.  |  .>  |  /?  | Shift  |
* `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
*          | `~   | INS  | Left | Right|                                         | Up   | Down |  [{  |  ]}  |
*          `---------------------------'                                         `---------------------------'
*                                        ,-------------.         ,-------------.
*                                        | Ctrl | Alt  |         | Gui  | Ctrl |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      | Home |         | PgUp |      |      |
*                                 | BkSp | Del  |------|         |------|Return| Space|
*                                 |      |      | End  |         | PgDn |      |      |
*                                 `--------------------'         `--------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DV] = KEYMAP(
           // Left Hand
           KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,
           KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,
           KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,
                    KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LCTL, KC_LALT,
                             KC_HOME,
           KC_BSPC, LT(_LO, KC_DEL),  KC_END,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, MO(_LO),  MO(_RA),
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
           KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
           KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
           KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                    KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, LT(_RA, KC_ENT),  KC_SPC
    ),

[_QW] = KEYMAP(
           // Left Hand
           KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
           KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
           KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                    KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LCTL, KC_LALT,
                             KC_HOME,
           KC_BSPC, LT(_LO, KC_DEL),  KC_END,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, MO(_LO),  MO(_RA),
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL ,
           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, LT(_RA, KC_ENT),  KC_SPC
    ),

[_CM] = KEYMAP(
           // Left Hand
           KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,
           KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,
           KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                    KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LCTL, KC_LALT,
                             KC_HOME,
           KC_BSPC, LT(_LO, KC_DEL),  KC_END,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, MO(_LO),  MO(_RA),
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
           KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
           KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
           KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, LT(_RA, KC_ENT),  KC_SPC
    ),

[_LO] = KEYMAP(
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
           _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
           _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,
           _______, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
           _______, _______, _______, _______, _______, _______,
           _______, _______, KC_PLUS, KC_LCBR, KC_RCBR, _______,
           _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
                    _______, _______, _______, _______,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    ),

[_RA] = KEYMAP(
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
           _______, _______, _______, _______, _______, _______,
           _______, _______, QWERTY,  COLEMAK, DVORAK,  _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand */
           _______, _______, _______, RESET,   _______, _______, _______, _______, _______,
           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
           _______, _______, _______, _______, _______, _______,
           _______, _______, KC_EQL,  KC_LBRC, KC_RBRC, _______,
           _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
                    _______, _______, _______, _______,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    )

};


const uint16_t PROGMEM fn_actions[] = {

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _DV:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_DV);
          }
          break;
        case _QW:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_QW);
          }
          break;
        case _CM:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_CM);
          }
          break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};
