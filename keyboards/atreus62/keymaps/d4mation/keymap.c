#include QMK_KEYBOARD_H
#include "d4mation.h"

enum layer_names {
  _DVR,
  _QWR,
  _LOWER,
  _RAISE,
  _NUM,
  _ADJUST
};

enum keymap_custom_keycodes {
  LOWER = NEW_SAFE_RANGE,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default/Dvorak layer
   * ,-----------------------------------------.                ,-----------------------------------------.
   * | `    |   1  |   2  |   3  |   4  |   5  |                |   6  |   7  |   8  |   9  |   0  |  /   |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |                |   F  |   G  |   C  |   R  |   L  |  =   |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |,------.,------.|   D  |   H  |   T  |   N  |   S  |  -   |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |Shift |   ;  |   Q  |   J  |   K  |   X  ||Super ||Enter ||   B  |   M  |   W  |   V  |   Z  |  \   |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * | NUM  | Alt  | Home |  End |Lower | Bksp |`------'`------'|Space |Raise | Left | Down |  Up  |Right |
   * `-----------------------------------------'                `-----------------------------------------'
   */

  [_DVR] = LAYOUT(
    _GRAVE_ESC,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH,
    KC_TAB,           KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_EQL,
    KC_LCTL,          KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
    TD(SHIFT_CAPS),   KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_BSLS,
    TG(_NUM),         KC_RALT, KC_HOME, KC_END,  LOWER,   KC_BSPC,  KC_LGUI, KC_ENT, KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
  ),

  /* Qwerty layer, more "standard" for other people who may need to use my keyboard or for games where using Qwerty is just easier
   * ,-----------------------------------------.                ,-----------------------------------------.
   * | `    |   1  |   2  |   3  |   4  |   5  |                |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |                |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |,------.,------.|   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  ||Super ||Enter ||   N  |   M  |   ,  |   .  |   /  |  =   |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * | NUM  | Alt  | Home |  End |Lower | Bksp |`------'`------'|Space |Raise | Left | Down |  Up  |Right |
   * `-----------------------------------------'                `-----------------------------------------'
   */

  [_QWR] = LAYOUT(
    _GRAVE_ESC,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_LCTL,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    TD(SHIFT_CAPS),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
    TG(_NUM),         KC_RALT, KC_HOME, KC_END,  LOWER,   KC_BSPC,  KC_LGUI, KC_ENT, KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
  ),

  /* "Lower" layer
   * ,-----------------------------------------.                ,-----------------------------------------.
   * | F11  |  F1  |  F2  |  F3  |  F4  |  F5  |                |  F6  |  F7  |  F8  |  F9  | F10  | F12  |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |      |      |      |      |SLEEP |      |                |      |      | SCRGB|      |      |      |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |      |      |      |      |      |      |,------.,------.|      |      |      |   {  |   }  |      |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |      |      |      |      |      |      ||      ||      ||      | Mute | VolD | VolU |      |      |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |      |      |PageUp|PgDown|      | Del  |`------'`------'|  Ins |      |      |      |      |      |
   * `-----------------------------------------'                `-----------------------------------------'
   */

  [_LOWER] = LAYOUT(
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    _______, _______, _______, _______, SLEEP,   _______,                   _______, _______, SCRGB,   _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, KC_LCBR, KC_RCBR, _______,
    _______, _______, _______, _______, _______, _______,                   _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
    _______, _______, KC_PGUP, KC_PGDN, _______, KC_DEL,  _______, _______, KC_INS,  _______, _______, _______, _______, _______
  ),

  /* "Raise" layer
   * ,-----------------------------------------.                ,-----------------------------------------.
   * | F11  |  F1  |  F2  |  F3  |  F4  |  F5  |                |  F6  |  F7  |  F8  |  F9  | F10  | F12  |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |      |      |<?php>|  ?>  |      |      |                |ZALGO |      |      |      |      |      |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |      | Shrug|Lenny |Magic |Disfac|      |,------.,------.|      |      |      |   [  |   ]  |      |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |      | Ameno| Tflip| Tput |      |      ||      ||      ||      | Prev | Play | Next |      |      |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |      |      |PageUp|PgDown|      | Del  |`------'`------'|  Ins |      |      |      |      |      |
   * `-----------------------------------------'                `-----------------------------------------'
   */

  [_RAISE] = LAYOUT(
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    _______, _______, PHPOPEN, PHPCLSE, _______, _______,                   ZALGO,   _______, _______, _______, _______, _______,
    _______, SHRUG,   LENNY,   MAGIC,   DISFACE, _______,                   _______, _______, _______, KC_LBRC, KC_RBRC,_______,
    _______, AMENO,   TFLIP,   TPUT,    _______, _______,                   _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
    _______, _______, KC_PGUP, KC_PGDN, _______, KC_DEL,  _______, _______, KC_INS,  _______, _______, _______, _______, _______
  ),

  /* "Numpad" layer
   * ,-----------------------------------------.                ,-----------------------------------------.
   * |      |      |   /  |   *  |   -  |      |                |      |      |   /  |   *  |   -  |      |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |      |   7  |   8  |   9  |   +  |      |                |      |   7  |   8  |   9  |   +  |      |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |      |   4  |   5  |   6  |   +  |      |,------.,------.|      |   4  |   5  |   6  |   +  |      |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |      |   1  |   2  |   3  | Enter|      ||      ||      ||      |   1  |   2  |   3  | Enter|      |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |      |   0  |   0  |   .  | Enter|      |`------'`------'|      |   0  |   0  |   .  | Enter|      |
   * `-----------------------------------------'                `-----------------------------------------'
   */

  [_NUM] = LAYOUT(
    _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______,                   _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______,
    _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, _______,                   _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, _______,
    _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,                   _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
    _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______,                   _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______,
    _______, KC_KP_0, KC_KP_0, KC_PDOT, KC_PENT, _______, _______, _______, _______, KC_KP_0, KC_KP_0, KC_PDOT, KC_PENT, _______
  ),

  /* "Adjust" layer, only active if both "Lower" and "Raise" are active at the same time
   * All unused keys are blanked out for this layer
   * ,-----------------------------------------.                ,-----------------------------------------.
   * |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |                |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |  NO  |RESET |  NO  |  NO  |  NO  |  NO  |                |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |  NO  |  NO  |  NO  |UC WIN|UC OSX|  NO  |,------.,------.|  NO  |Dvorak|Qwerty|  NO  |  NO  |  NO  |
   * |------+------+------+------+------+------|| Swap ||      ||------+------+------+------+------+------|
   * |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  ||  to  || Swap ||  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
   * |------+------+------+------+------+------|| Ctrl || Back ||------+------+------+------+------+------|
   * |  NO  |  NO  |  NO  |  NO  |      |  NO  |`------'`------'|  NO  |      |  NO  |  NO  |  NO  |  NO  |
   * `-----------------------------------------'                `-----------------------------------------'
   */

  [_ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, UC_M_WI, UC_M_MA, XXXXXXX,                   XXXXXXX, DF(_DVR),DF(_QWR),XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, CG_SWAP, CG_NORM, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

};

/* Runs just one time when the keyboard initializes. */
void eeconfig_init_keymap( void ) {
  set_unicode_input_mode( UC_OSX );
};

bool process_record_keymap( uint16_t keycode, keyrecord_t *record ) {

  switch ( keycode ) {

    case LOWER:

      if ( record->event.pressed ) {
        layer_on( _LOWER );
        update_tri_layer( _LOWER, _RAISE, _ADJUST );
      }
      else {
        layer_off( _LOWER );
        update_tri_layer( _LOWER, _RAISE, _ADJUST );
      }

      return false;
      break;

    case RAISE :

      if ( record->event.pressed ) {
        layer_on( _RAISE );
        update_tri_layer( _LOWER, _RAISE, _ADJUST );
      }
      else {
        layer_off( _RAISE );
        update_tri_layer( _LOWER, _RAISE, _ADJUST );
      }

      return false;
      break;

  }

  return true;

};
