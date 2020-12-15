/* Copyright 2015-2017 Jack Humbert
 * Copyright 2020 Terence Rudkin
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

#include "tap.h"
#include "wrappers.h"


enum my_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
  _MOUSE,
 _FUNCTION,
};



#define TAP_CODE_DELAY 5
#define MAKE_BOOTLOADER

#define   NUMPAD TG(6)

#define LOWER_ TT(_LOWER)
#define RAISE_ TT(_RAISE)
//#define MY_LOW TT(_LOWER)
//#define MY_RAI TT(_RAISE)
#define MY_LOW TD(MOD_LOW)
#define MY_RAI TD(MOD_RAI)

/*
 * The `LAYOUT_ortho_5x12_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */
// clang-format off
#define LAYOUT_ortho_5x12_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A,  \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A  \
  ) \
  LAYOUT_ortho_5x12_wrapper( \
    KC_GESC,    K01,    K02,     K03,      K04,     K05,     K06,     K07,     K08,     K09,     K0A,      KC_BSPC, \
    KC_TAB,     K11,    K12,     K13,      K14,     K15,     K16,     K17,     K18,     K19,     K1A,      KC_BSLS,         \
    MY_DEL,     K21,    K22,     K23,      K24,     K25,     K26,     K27,     K28,     K29,     K2A,      KC_QUOT,         \
    KC_LSFT,    K31,    K32,     K33,      K34,     K35,     K36,     K37,     K38,     K39,     HYPR_T(KC_UP), RSFT_T(K3A), \
    LCTL_T(KC_LBRC), LGUI_T(KC_RBRC), MY_PIPE, KC_MINS, MY_LOW, KC_SPC,   KC_SFTENT, MY_RAI, KC_EQL, RALT_T(KC_LEFT), RGUI_T(KC_DOWN), RCTL_T(KC_RGHT) \
  )

#define LAYOUT_ortho_5x12_base_wrapper(...)   LAYOUT_ortho_5x12_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | GESC |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Lead |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  -   |Lower |Space |  Ent |Raise |   =  | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_QWERTY] = LAYOUT_ortho_5x12_base_wrapper(
         ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
         _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
         _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
         _________________QWERTY_L3_________________, _________________QWERTY_R3_________________),
/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | G_ESC|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |   \  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Lead |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |  Up  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  -   |Lower |Space |  Ent |Raise |   =  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_COLEMAK] = LAYOUT_ortho_5x12_base_wrapper(
         ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
         _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
         _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
         _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
),
/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | G_ESC|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Lead |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Up |  Z   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  -   |Lower |Space |  Ent |Raise |   =  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_DVORAK] = LAYOUT_ortho_5x12_base_wrapper(
         ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, 
         _________________DVORAK_L1_________________, _________________DVORAK_R1_________________, 
         _________________DVORAK_L2_________________, _________________DVORAK_R2_________________, 
         _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ESC |  F1  |  F2  |   F3 |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | BKSP |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  INS |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  =   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | DEL  |      |      |      |      |      |      |      |   {  |   }  |   _  |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |NUMPAD|  #   |  !   |  /   |  *   |ISO | |ISO > |   <  |   >  | PgUp |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | F11  |      |      |      |      | F12  | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
    [_LOWER] = LAYOUT_ortho_5x12_wrapper(
      MY_ESC,  _________________FUNC_LEFT_________________,_________________FUNC_RIGHT________________,  KC_BSPC,
      KC_INS,  _________________LOWER_L1__________________, _________________LOWER_R1__________________, KC_EQL,   
      KC_DEL,  _________________LOWER_L2__________________, _________________LOWER_R2__________________, KC_PLUS,
      _______, _________________LOWER_L3__________________, _________________LOWER_R3__________________, KC_NO,
      _______,NUMPAD  ,_______,KC_F11,_______,_______,_______,_______,KC_F12,KC_HOME,KC_PGDN,KC_END),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  ESC | C_F1 | C_F2 | C_F3 | C_F4 | C_F5 | C_F6 | C_F7 | C_F8 | C_F9 |C_F10 | BKSP |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |      | BTN1 | BTN3 | BTN2 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      | up   |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | MS < | DN   | MS > |      |      |      | Prev | Next | Vol+ |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | C_F11|      |             |      | C_F12| Stop | Vol- |Pause |
 * `-----------------------------------------------------------------------------------'
 */
    [_RAISE] = LAYOUT_ortho_5x12_wrapper(
         KC_ESC,  ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_BSPC,
         KC_INS,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, KC_NO,
         KC_DEL,  _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
         _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, RGB_TOG,
         _______, NUMPAD , _______,KC_F11, _______, _______, _______, _______, KC_F12, KC_MSTP, KC_VOLD, KC_MPLY),

    [_ADJUST] = LAYOUT_ortho_5x12_wrapper( 
        KC_ESC, QWERTY, COLEMAK, DVORAK, KC_NO, KC_PSCR, KC_NLCK, 7, RGB_SPD, RGB_MOD, RGB_RMOD, RGB_TOG, 
        _______, RESET, DEBUG, _______, _______, TERM_ON, TERM_OFF, RGB_VAI, RGB_VAD, RGB_M_R, RGB_M_X, RGB_M_B, 
        _______, _______, MU_MOD, AU_ON, AU_OFF, AG_NORM, AG_SWAP, RGB_HUI, RGB_HUD, RGB_M_K, RGB_M_SW, RGB_M_SN, - 
        _______, MUV_DE, MUV_IN, MU_ON, MU_OFF, MI_ON, MI_OFF, RGB_SAI, RGB_SAD, RGB_M_T, RGB_M_X, RGB_M_G, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
//        KC_ESC, QWERTY,  COLEMAK, DVORAK, KC_NO, KC_NO, KC_NLCK, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_PAST,
//        _______, RESET, DEBUG, _______, _______, TERM_ON, TERM_OFF, KC_P4, KC_P5, KC_P6, KC_NO, KC_PMNS,
//        _______, _______, MU_MOD, AU_ON, AU_OFF, AG_NORM, AG_SWAP, KC_P1, KC_P2, KC_P3, KC_NO, KC_PPLS,
//        _______, MUV_DE, MUV_IN, MU_ON, MU_OFF, MI_ON, MI_OFF, KC_P0, KC_P0, KC_PDOT, _______, KC_PEQL,
//        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
    [_NUMPAD] = LAYOUT_ortho_5x12_wrapper(
       _______, _________________NUMPAD_1__________________,_________________NUMPAD_1__________________, _______,
       _______, _________________NUMPAD_2__________________,_________________NUMPAD_2__________________, _______,
       _______, _________________NUMPAD_3__________________,_________________NUMPAD_3__________________, _______,
       _______, _______, _______NUMPAD_4________,_______,   _______,  _______NUMPAD_4________, _______,  _______,
       KC_NO, KC_NO, KC_NO, KC_NO, _______, KC_NO, KC_NO, _______, KC_NO, KC_NO, KC_NO, KC_NO)

};
/*
/ * Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 * /
[_LOWER] = LAYOUT_preonic_grid( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),KC_HOME, (KC_END), _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/ * Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 * /
[_RAISE] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/ * Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 * /

//[_ADJUST] = LAYOUT_preonic_grid( \
//  KC_ESC, QWERTY,  COLEMAK, DVORAK,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
//  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
//  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______, \
//  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
//)

*/


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RALT_T(KC_LEFT):
        case RGUI_T(KC_DOWN): 
        case RCTL_T(KC_RGHT):
        case HYPR_T(KC_UP):
        case MY_PIPE:
        case LCTL_T(KC_LBRC):
        case LGUI_T(KC_RBRC):
        case MY_LOW:
        case MY_RAI:
            return TAPPING_TERM + 500;
        case LT(1, KC_GRV):
            return 130;
        default:
            return TAPPING_TERM;
    }
}


const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_TEAL}
);
const rgblight_segment_t PROGMEM my_colemak_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_CYAN}
);
const rgblight_segment_t PROGMEM my_dvorak_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_AZURE}
);
const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_RED}
);
const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_BLUE}
);
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM my_number_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_GREEN}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_qwerty_layer,
    my_colemak_layer,             
    my_dvorak_layer,                
    my_raise_layer,                 
    my_lower_layer,
    my_adjust_layer,
    my_number_layer
     );

void keyboard_post_init_user(void) {
    // Enable the LED layers
 	rgblight_layers = my_rgb_layers;
	//layer_state_set_user(layer_state);
}



layer_state_t layer_state_set_user(layer_state_t state) {
   state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);


    // Both layers will light up if both kb layers are active

  rgblight_set_layer_state(1, layer_state_cmp(state, 1));
  rgblight_set_layer_state(2, layer_state_cmp(state, 2));
  rgblight_set_layer_state(3, layer_state_cmp(state, 3));
  rgblight_set_layer_state(4, layer_state_cmp(state, 4));
  rgblight_set_layer_state(5, layer_state_cmp(state, 5));
  rgblight_set_layer_state(6, layer_state_cmp(state, 6));
  rgblight_set_layer_state(7, layer_state_cmp(state, 7));

    return state;
}
                
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;
        case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (!record->event.pressed) {
#ifndef MAKE_BOOTLOADER
                uint8_t temp_mod = mod_config(get_mods());
                uint8_t temp_osm = mod_config(get_oneshot_mods());
                clear_mods();
                clear_oneshot_mods();
#endif
                send_string_with_delay_P(PSTR("qmk"), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
#endif
                {
                    send_string_with_delay_P(PSTR(" flash "), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                } else {
                    send_string_with_delay_P(PSTR(" compile "), TAP_CODE_DELAY);
#endif
                }
                send_string_with_delay_P(PSTR("-kb " QMK_KEYBOARD " -km " QMK_KEYMAP), TAP_CODE_DELAY);
#ifdef RGB_MATRIX_SPLIT_RIGHT
                send_string_with_delay_P(PSTR(" RGB_MATRIX_SPLIT_RIGHT=yes"), TAP_CODE_DELAY);
#    ifndef OLED_DRIVER_ENABLE
                send_string_with_delay_P(PSTR(" OLED_DRIVER_ENABLE=no"), TAP_CODE_DELAY);
#    endif
#endif
                send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
            }

            break;

      }
    return true;
};



bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}



void matrix_init_user (void) {
  if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
      register_code(KC_NUMLOCK);
      unregister_code(KC_NUMLOCK);
  }
};




// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
//    [NUM_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, nl_finished, nl_reset, 275),
//    [MOD_LOW] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, mod_low_finished, mod_low_reset, 275),
    [MOD_LOW] = MOD_LAYER( 1,KC_MINS, _LOWER, KC_RCTL, KC_RSFT),
    [MOD_RAI] = MOD_LAYER( 2,KC_EQL, _RAISE, KC_RALT, KC_RSFT),
    [LBRC_9] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, l_brc_finished, l_brc_reset, 275),
    [RBRC_0] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, r_brc_finished, r_brc_reset, 275),
    // Tap Dance definitions

      // Tap once for Escape, twice for Caps Lock
   [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),      
    [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT), 
    [TD_DEL_INS] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_INS),
      [TD_CUT] = ACTION_TAP_DANCE_DOUBLE(KC_X,RSFT(KC_DEL)),
     [TD_COPY] = ACTION_TAP_DANCE_DOUBLE(KC_C,LCTL(KC_INS)),
    [TD_PASTE] = ACTION_TAP_DANCE_DOUBLE(KC_V,RSFT(KC_INS)),
    [TD_PIPE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pipe_finished, pipe_reset)

};
