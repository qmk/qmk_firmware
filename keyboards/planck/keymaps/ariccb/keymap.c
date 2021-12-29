 /* Copyright 2021 Aric Crosson Bouwers 
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 

#include QMK_KEYBOARD_H
#include "muse.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers. 
#define _QWERTY 0
#define _COLEMAK 1
#define _LOWER 2  
#define _RAISE 3
#define _NUMPAD 4
#define _FN 5
#define _ADJUST 6
#define _GAMING 7
#define MICMUTE LCTL(LSFT(KC_M))
#define MTLSFT_F1 MT(MOD_LSFT, KC_F1)
#define MTLGUI_Z MT(MOD_LGUI, KC_Z)
#define MTLALT_F2 MT(MOD_LALT, KC_F2)
#define MTENTER MT(MOD_LCTL, KC_ENT)
// #define MTSPACE MT(MOD_LGUI, KC_SPC)
#define MTTAB MT(MOD_LCTL | MOD_LGUI | MOD_LALT, KC_TAB)
#define LTESC LT(_FN, KC_ESC)
#define RSE_DL LT(_RAISE, KC_DEL)
#define MTPLAY MT(MOD_RALT, KC_MPLY)

// UNCOMMENT IF WANTING TO USE SHIFT_SPACE_BACKSPACE OR SHIFT_BACKSPACE_DELETE
// //which shift is held?//
// static uint16_t held_shift = 0;
// //is shift held?//

// UNCOMMENT IF YOU WANT TO USE SHIFT_SPACE_BACKSPACE OR SHIFT_BACKSPACE_DELETE
// static bool shift_held = false; 
// static bool bsdel_mods = false;
// static bool bsspace_mods = false;

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  FN,
  ADJUST,
  NUMPAD,
  GAMING,
  EXT_NUM,
  EXT_GAMING,
  SHIFT_SPACE_BACKSPACE,
  SHIFT_BACKSPACE_DELETE
}; 

// This is a completely modified layout that stikes a balance between muscle memory for keys, where I was coming from a standard
// Qwerty keyboard, and efficiency gained by using layers. I've switched tab and esc because it's more natural to me this way, and
// added layer switch on hold functionality for each key. Enter has moved to the key beside LOWER, to allow usage while still having
// the right hand on the mouse.

// Lower incorporates a numpad which falls in line with the numberkeys at the top as well - my muscle memory appreciates both layouts.

// Upper has a layout that's optimized for coding symbols, and has a few duplicates just to entertain my existing muscle memory. Some 
// things apparently can't be un-taught.

// CAPS has moved to the Fn layer, and a few additional shortcut modifiers like CTRL_ALT_UP and DOWN for adding additional cursors in VSCode.
// Play/Pause has a prime spot on the base layer, and the Fn version skips to next track

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* MIT Layout (QWERTY)
 *
 * ,------------------------------------------------------------------------.
 * |FN,Esc|  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |Bsp  |
 * |------------------------------------------------------------------------|
|CSGUI,Tab|  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |
 * |------------------------------------------------------------------------|
 * |Shift |Win,z|  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |  \  |
 * |------------------------------------------------------------------------|
 * |      |     |     |Ctl,Ent|LOWER|  Space  |RSE_DL|Alt,Play|   |   |     |
 * `------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid( /* QWERTY */
    LTESC,   KC_Q,  KC_W,  KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_BSPC,
    MTTAB,   KC_A,  KC_S,  KC_D,    KC_F,  KC_G,   KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, 
    KC_LSFT, MTLGUI_Z,  KC_X,  KC_C,    KC_V,  KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, 
    KC_NO,   KC_NO, KC_NO, MTENTER, LOWER, KC_SPC, KC_SPC, RSE_DL, MTPLAY,  KC_NO,  KC_NO,   KC_NO
 ),

 /* MIT Layout (COLEMAK)
 *
 * ,------------------------------------------------------------------------.
 * |FN,ESC|  q  |  w  |  f  |  p  |  b  |  j  |  l  |  u  |  y  |  ;  | Bsp |
 * |------------------------------------------------------------------------|
|CSGUI,Tab|  a  |  r  |  s  |  t  |  g  |  m  |  n  |  e  |  i  |  o  |  '  |
 * |------------------------------------------------------------------------|
 * |Shift |Win,z|  x  |  c  |  d  |  v  |  k  |  h  |  ,  |  .  |  /  |Win,\|
 * |------------------------------------------------------------------------|
 * |      |     |     |Ctl,Ent|LOWER|  Space  |RSE_DL|Alt,Play|   |   |     |
 * `------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid( /* COLEMAK */
    LTESC,   KC_Q,  KC_W,  KC_F,    KC_P,  KC_B,   KC_J,   KC_L,   KC_U,    KC_Y,   KC_SCLN, KC_BSPC,
    MTTAB,   KC_A,  KC_R,  KC_S,    KC_T,  KC_G,   KC_M,   KC_N,   KC_E,    KC_I,   KC_O,    KC_QUOT, 
    KC_LSFT, MTLGUI_Z,  KC_X,  KC_C,    KC_D,  KC_V,   KC_K,   KC_H,   KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, 
    KC_NO,   KC_NO, KC_NO, MTENTER, LOWER, KC_SPC, KC_SPC, RSE_DL, MTPLAY,  KC_NO,  KC_NO,   KC_NO
 ),

/* MIT Layout (RAISE)
 *
 * ,-----------------------------------------------------------------------.
 * |     | F1  | F2  | F3  | F4  |     |     |     |     |     |     | Bsp |  
 * |-----------------------------------------------------------------------|
 * |     | F5  | F6  | F7  | F8  |     |     |     |     |     |     |     |
 * |-----------------------------------------------------------------------|
 * |     | F9  | F10 | F11 | F12  |    |     |     |     |     |     |     |
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |     |           |     |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid( /* RAISE */
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,
  KC_TRNS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
  KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* MIT Layout (LOWER)
 *.
 * ,-----------------------------------------------------------------------.
 * |  `  |  !  |  {  |  }  |  $  |  &  |  :  |  7  |  8  |  9  |  =  | Bsp |
 * |-----------------------------------------------------------------------|
 * |  ~  |  _  |  (  |  )  |  %  |  C  |  M  |  4  |  5  |  6  |  -  |  +  |
 * |-----------------------------------------------------------------------|
 * | Menu|  |  |  [  |  ]  |  ^  |  #  |  @  |  1  |  2  |  3  |  /  |  *  |
 * |-----------------------------------------------------------------------|
 * |     |     |     |NUMPAD|    |           |  0  |  .  |     |     |     |
 * `-----------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid( /* LOWER */
  KC_GRV,  KC_EXLM, KC_LCBR, KC_RCBR, KC_DLR,  KC_AMPR, KC_COLN, KC_7, KC_8,   KC_9,  KC_EQL,  KC_BSPC, 
  KC_TILD, KC_UNDS, KC_LPRN, KC_RPRN, KC_PERC, KC_C,    KC_M,    KC_4, KC_5,   KC_6,  KC_PMNS, KC_PPLS, 
  KC_MENU, KC_PIPE, KC_LBRC, KC_RBRC, KC_CIRC, KC_HASH, KC_AT,   KC_1, KC_2,   KC_3,  KC_PSLS, KC_ASTR, 
  KC_TRNS, KC_TRNS, KC_TRNS, NUMPAD,  KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_DOT, KC_NO, KC_NO,   KC_NO
),    

/* MIT Layout (NUMPAD)
 *.
 * ,-----------------------------------------------------------------------.
 * |  `  |  !  |  {  |  }  |  $  |  &  |  :  |  7  |  8  |  9  |  =  | Bsp |
 * |-----------------------------------------------------------------------|
 * |  ~  |  _  |  (  |  )  |  %  |  C  |  M  |  4  |  5  |  6  |  -  |  +  |
 * |-----------------------------------------------------------------------|
 * | Menu|  |  |  [  |  ]  |  ^  |  #  |  @  |  1  |  2  |  3  |  /  |  *  |
 * |-----------------------------------------------------------------------|
 * |     |     |     |     | EXIT|           |  0  |  .  |     |     |     |
 * `-----------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid( /* LOWER */
  KC_GRV,  KC_EXLM, KC_LCBR, KC_RCBR, KC_DLR,  KC_AMPR, KC_COLN, KC_7, KC_8,   KC_9,  KC_EQL,  KC_BSPC, 
  KC_TILD, KC_UNDS, KC_LPRN, KC_RPRN, KC_PERC, KC_C,    KC_M,    KC_4, KC_5,   KC_6,  KC_PMNS, KC_PPLS, 
  KC_MENU, KC_TRNS, KC_LBRC, KC_RBRC, KC_CIRC, KC_HASH, KC_AT,   KC_1, KC_2,   KC_3,  KC_PSLS, KC_ASTR, 
  KC_TRNS, KC_TRNS, KC_TRNS, NUMPAD,  EXT_NUM, KC_TRNS, KC_TRNS, KC_0, KC_DOT, KC_NO, KC_NO,   KC_NO
),

/* MIT Layout (GAMING)
 *.
 * ,-----------------------------------------------------------------------.
 * |ESC,`|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |EXIT GAMING|
 * |-----------------------------------------------------------------------|
 * | TAB |  Q  |  W  |  E  |  R  |  T  |  I  |  4  |  5  |  6  |  -  |  +  |
 * |-----------------------------------------------------------------------|
 * | Shift|  A  |  S  |  D  |  F  |  G  |  K  |  1  |  2  |  3  |  /  |  *  |
 * |-----------------------------------------------------------------------|
 * |     |     |     |  Ctl | Alt |   SPACE   |  0  |  .  |     |     |     |
 * `-----------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid( /* GAMING */
  KC_GESC, KC_1, KC_2, KC_3,    KC_4,    KC_5,   KC_6,   KC_7,  KC_P8,   KC_9,    KC_0,    EXT_GAMING, 
  KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,   KC_I,   KC_P4, KC_P5,   KC_P6,   KC_PMNS, KC_PPLS, 
  KC_LSFT, KC_A, KC_S, KC_D,    KC_F,    KC_G,   KC_K,   KC_P1, KC_P2,   KC_P3,   KC_PSLS, KC_PAST, 
  KC_NO, KC_NO, KC_NO, KC_LCTL, KC_LALT, KC_SPC, KC_SPC, KC_P0, KC_PDOT, KC_NO,   KC_NO,   KC_NO
),

/* MIT Layout (FN)
 *
 * ,----------------------------------------------------------------------.
 * |    |Shift| Alt |     |     |Calc|    |home | up   | end |PrtScr| Del |
 * |----------------------------------------------------------------------|
 * |    |     |     |     |     |    |    |left | down |right|ScrLck|Ins  |
 * |----------------------------------------------------------------------|
 * |    |     |     |     |     |Mute|MicM|pgup |LCA_dn| pgdn|      |CAPS |
 * |----------------------------------------------------------------------|
 * |    |     |     |     |Vol- |         |Vol+ |next  |     |      |     |
 * `----------------------------------------------------------------------'
 */
[_FN] = LAYOUT_planck_grid( /* FUNCTION */
  KC_TRNS, KC_LSFT, KC_LALT,   KC_TRNS,  KC_TRNS, KC_CALC, KC_TRNS, KC_HOME, KC_UP,        KC_END,  KC_PSCR, KC_BSPC,
  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN,      KC_RGHT, KC_SLCK, KC_INS, 
  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS, KC_MUTE, MICMUTE, KC_PGUP, LCA(KC_DOWN), KC_PGDN, KC_TRNS, KC_CAPS, 
  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_VOLD, KC_TRNS, KC_TRNS, KC_VOLU, KC_MNXT,      KC_NO,   KC_NO,   KC_NO
),

/* MIT Layout (ADJUST)
 *
 * ,----------------------------------------------------------------------------.
 * |reset| Ms3 | Ms2 |MsUp | Ms1  |  Hue+|   Hue-| Sat+| Sat-|Brt+ |Brt- |RGB Tg|
 * |----------------------------------------------------------------------------|
 * |debug| MWL | MsL |MDn  |MsR   |GAMING|       |AU_ON|AU_OFF|    |     |RGBMod|
 * |----------------------------------------------------------------------------|
 * |     |     |MWUp |NWDn |      |QWERTY|COLEMAK|MI_ON|MI_OF|MU_ON|MU_OF|MU_Mod|
 * |----------------------------------------------------------------------------|
 * |MSP0 |MSP1 |MSP2 |SLEEP|      |              |     |     |     |     |      |
 * `----------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid( /* ADJUST LAYER */
  RESET,        KC_BTN3,      KC_BTN2,      KC_MS_U, KC_BTN1, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_TOG, 
  DEBUG,        KC_NO,        KC_MS_L,      KC_MS_D, KC_MS_R, GAMING,  KC_NO,   AU_ON,   AU_OFF,  KC_NO,   KC_NO,   RGB_MOD, 
  KC_TRNS,      KC_WH_L,      KC_WH_U,      KC_WH_D, KC_WH_R, QWERTY,  COLEMAK, MI_ON,   MI_OFF,  MU_ON,   MU_OFF,  MU_MOD,
  KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, KC_SLEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO
)
};

#ifdef AUDIO_ENABLE
float layerswitch_song[][2] = SONG(PLANCK_SOUND);   
float tone_startup[][2]     = SONG(STARTUP_SOUND);
float tone_qwerty[][2]      = SONG(QWERTY_SOUND);
float tone_colemak[][2]     = SONG(COLEMAK_SOUND);
float music_scale[][2]      = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2]     = SONG(GOODBYE_SOUND);

#endif
 
layer_state_t layer_state_set_user(layer_state_t state) {
 
	static bool is_this_layer_on = false;
	if (layer_state_cmp(state, 4) != is_this_layer_on) {
		is_this_layer_on = layer_state_cmp(state, 4);
		if (is_this_layer_on) {
			PLAY_SONG(layerswitch_song);
		}
		else {
			stop_all_notes();
		}
	}
 
	switch (get_highest_layer(state)) {
		case _ADJUST:
			rgblight_setrgb (0xFF,  0x00, 0x00);
			break;
		case _LOWER:
			rgblight_setrgb (0x00,  0x00, 0xFF);
			break;
    case _NUMPAD:
			rgblight_setrgb (0x00,  0x00, 0xFF);
			break;
		case _RAISE:
			rgblight_setrgb (0x7A,  0x00, 0xFF);
			break;
		case _FN:
			rgblight_setrgb (0x00,  0xFF, 0x00);
			break;
		default: //  for any other layers, or the default layer
			rgblight_setrgb (0xFF,  0xFF, 0xFF);
			break;
		}
	  return state;
 
}

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case KC_CAPS:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        register_code(KC_CAPS);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_NUMPAD);
        #ifdef AUDIO_ENABLE
          PLAY_SONG(layerswitch_song);
        #endif
      }
      return false;
      break;
    case EXT_NUM:
      if (record->event.pressed) {
        layer_off(_NUMPAD);
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_goodbye);
        #endif
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_GAMING);
        #ifdef AUDIO_ENABLE
          PLAY_SONG(layerswitch_song);
        #endif
      }
      return false;
      break;
    case EXT_GAMING:
      if (record->event.pressed) {
        layer_off(_GAMING);
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_goodbye);
        #endif
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    // UNCOMMENT TO USE SHIFT_SPACE_BACKSPACE OR SHIFT_BACKSPACE_DELETE
    // case KC_LSFT:
    //     // set "shift is held" variable//
    //     shift_held = record->event.pressed;
    //     // specify which shift is held//
    //     held_shift = keycode;
    //     return true;
    //     break;
    // case KC_RSFT:
    //     shift_held = record->event.pressed;
    //     held_shift = keycode;
    //     return true;
    //     break;
    // case SHIFT_BACKSPACE_DELETE:
    //     if (record->event.pressed) {
    //         if (shift_held) {
    //             unregister_code(held_shift);
    //             register_code(KC_DEL);
    //             bsdel_mods = true;
    //         } else {
    //             register_code(KC_BSPC);
    //         }
    //     } else {
    //         if (bsdel_mods) {
    //             unregister_code(KC_DEL);
    //             bsdel_mods = false;
    //         } else {
    //             unregister_code(KC_BSPC);
    //         }
    //     }
    //     return false;
    //     break;
    // case SHIFT_SPACE_BACKSPACE:
    //     if (record->event.pressed) {
    //         if (shift_held) {
    //             unregister_code(held_shift);
    //             register_code(KC_BSPC);
    //             bsspace_mods = true;
    //         } else {
    //             register_code(KC_SPACE);
    //         }
    //     } else {
    //         if (bsspace_mods) {
    //             unregister_code(KC_BSPC);
    //             bsspace_mods = false;
    //         } else {
    //             unregister_code(KC_SPACE);
    //         }
    //     }
    //     return false;
    //     break;
  }
  return true;
}