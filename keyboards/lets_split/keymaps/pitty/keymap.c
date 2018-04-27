#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _GAME 1
#define _LOWER 2
#define _NAV 3
#define _VIM 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  GAME,
  LOWER,
  NAV,
  VIM,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |  Z(Y)|   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |LTVIMF|   G  |   H  |   J  |   K  |   L  |  É(;)| Á(") |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Í/Shft| Y(Z) |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  -(/)| Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  GUI |  Alt |ADJUST|  Spc | LOWER| Bksp | Ent  |  Alt | =(&) | GAME | Del  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_TAB,                KC_Q,      KC_W,    KC_E,     KC_R,           KC_T,               KC_Y,     KC_U,    KC_I,    KC_O,         KC_P,          KC_BSPC, \
  KC_ESC,                KC_A,      KC_S,    KC_D,     LT(_VIM, KC_F), KC_G,               KC_H,     KC_J,    KC_K,    KC_L,         KC_SCLN,       KC_QUOT, \
  MT(MOD_LSFT, KC_NUBS), KC_Z,      KC_X,    KC_C,     KC_V,           KC_B,               KC_N,     KC_M,    KC_COMM, KC_DOT,       KC_SLSH,       KC_RSFT, \
  KC_LCTL,               KC_LGUI,   KC_LALT, TT(_NAV), KC_SPC,         LT(_LOWER, KC_SPC), KC_BSPC,  KC_ENT,  KC_RALT, KC_AMPERSAND, TG(_GAME),     KC_DEL \
),

/* Gaming mode
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |Lower |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |   F  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |      |      |      |QWERTY|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] =  LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, OSL(_LOWER),    \
  _______, _______, _______, _______, KC_F,    _______, _______, _______, _______, _______, _______, _______,    \
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_QWERTY),    \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | 0(') |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  | Ö(0) | Ü(-) |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F10 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  Ins | Home | PgUp | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  Del | End  | PgDn | AltGr|
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS, \
  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F11,  KC_F12, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, KC_RSFT, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_END,  KC_PGDN, KC_RALT \
),


/* NAV
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  Up  |      |  F2  |      |      |   7  |   8  |   9  |   /  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |      |   4  |   5  |   6  |   *  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |   1  |   2  |   3  |   -  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   0  |   .  |   =  |   +  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT( \
  _______,   _______, KC_UP,   _______, KC_F2,   _______, _______,  KC_7,    KC_8,      KC_9,         KC_KP_SLASH,    _______, \
  _______,   KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,  KC_4,    KC_5,      KC_6,         KC_KP_ASTERISK, _______, \
  KC_LSFT,   _______, _______, _______, _______, _______, _______,  KC_1,    KC_2,      KC_3,         KC_KP_MINUS,    _______, \
  _______,   _______, _______, _______, _______, _______, _______,  KC_GRV,  KC_KP_DOT, KC_KP_EQUAL,  KC_KP_PLUS,     _______ \
),

/* Vim Movement (Hold down F)
 * ,-----------------------------------------------------------------------------------.
 * |RGBMOD|RGBTOG|      |      |      |      |      |  Ú   |   Í  |   Ó  |   Ő  |  Ű   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |DM_stp|      |      | LCTRL|      |      | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |DM_REC|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | LShft|      |      |      |      |      |      | RESET|
 * `-----------------------------------------------------------------------------------'
 */
[_VIM] =  LAYOUT( \
  RGB_MOD, RGB_TOG,  _______, _______, _______, _______, _______, KC_RBRC, KC_NUBS, KC_EQL , KC_LBRC, KC_NUHS, \
  _______, _______,  _______, KC_LCTL, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______,  _______, _______, KC_LSFT, _______, _______, _______, _______, _______, _______, RESET \
)


};

// define variables for reactive RGB
bool RGB_INIT = false;
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


void matrix_scan_user(void) {
   uint8_t layer = biton32(layer_state);
   switch (layer) {
     case _NAV:
         if (RGB_INIT) {} else {
           RGB_current_mode = rgblight_config.mode;
           RGB_INIT = true;
         }
         if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
         } else {
           TOG_STATUS = !TOG_STATUS;
           rgblight_mode(29);
         }
         break;
     case _LOWER:
         if (RGB_INIT) {} else {
           RGB_current_mode = rgblight_config.mode;
           RGB_INIT = true;
         }
         if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
         } else {
           TOG_STATUS = !TOG_STATUS;
           rgblight_mode(29);
         }
         break;
     case _QWERTY:
         if (RGB_INIT) {} else {
           RGB_current_mode = rgblight_config.mode;
           RGB_INIT = true;
         }
         rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
         TOG_STATUS = false;
         break;
   }
 };
