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
#include "trudkin.h"









#define THUMB_CLUSTER_1x2 KC_MINS, MY_LOW, KC_SPC, KC_ENT, MY_RAI, KC_EQL
#define THUMB_CLUSTER_2x2 MY_LOW, KC_SPC, KC_SPC, KC_ENT, KC_ENT, MY_RAI
#define THUMB_CLUSTER_2x1 MY_LOW, KC_DEL, KC_SPC, KC_SPC, KC_ENT, MY_RAI

#ifdef USE_1X2_LAYOUT
#    define _______THUMB_CLUSTER_______ THUMB_CLUSTER_1x2
#    define LOW_KEY KC_SPC
#    define RAI_KEY KC_ENT
#elif USE_2X1_LAYOUT
#    define LOW_KEY KC_MINS
#    define RAI_KEY KC_EQL
#    define _______THUMB_CLUSTER_______ THUMB_CLUSTER_2x1
#else 
#    define LOW_KEY KC_MINS
#    define RAI_KEY KC_EQL
#    define _______THUMB_CLUSTER_______ THUMB_CLUSTER_2x2
#endif




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
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A,  \
              K43, K44, K45, K46, K47, K48 \
  ) \
  LAYOUT_ortho_5x12_wrapper( \
    KC_GESC,    K01,    K02,     K03,      K04,     K05,     K06,     K07,     K08,     K09,     K0A,      KC_BSPC, \
    KC_TAB,     K11,    K12,     K13,      K14,     K15,     K16,     K17,     K18,     K19,     K1A,      KC_BSLS,         \
    MY_DEL,     K21,    K22,     K23,      K24,     K25,     K26,     K27,     K28,     K29,     K2A,      KC_QUOT,         \
    OSM(MOD_LSFT),    K31,    K32,     K33,      K34,     K35,     K36,     K37,     K38,     K39,     HYPR_T(KC_UP), RSFT_T(K3A), \
    KC_LCTL, MY_LGUI,KC_LALT,    K43,      K44,     K45,     K46,     K47,     K48, RALT_T(KC_LEFT), RGUI_T(KC_DOWN), RCTL_T(KC_RGHT) \
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
 * | Ctrl | GUI  | Alt  |Lower |    Space    |    Enter    |Raise | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_QWERTY] = LAYOUT_ortho_5x12_base_wrapper(
         ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
         _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
         _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
         _________________QWERTY_L3_________________, _________________QWERTY_R3_________________,
                                          _______THUMB_CLUSTER_______
         ),
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
 * | Ctrl | GUI  | Alt  |Lower |    Space    |    Enter    |Raise | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_COLEMAK] = LAYOUT_ortho_5x12_base_wrapper(
         ________________NUMBER_LEFT________________, _____________MY_NUMBER_RIGHT_______________,
         _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
         _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
         _________________COLEMAK_L3________________, _________________COLEMAK_R3________________,
                                            _______THUMB_CLUSTER_______
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
 * | Ctrl | GUI  | Alt  |Lower |    Space    |    Enter    |Raise | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_DVORAK] = LAYOUT_ortho_5x12_base_wrapper(
         ________________NUMBER_LEFT________________, _____________MY_NUMBER_RIGHT_______________, 
         _________________DVORAK_L1_________________, _________________DVORAK_R1_________________, 
         _________________DVORAK_L2_________________, _________________DVORAK_R2_________________, 
         _________________DVORAK_L3_________________, _________________DVORAK_R3_________________,
                                           _______THUMB_CLUSTER_______
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
 * |      |      |      |      |             |             |     | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
    [_LOWER] = LAYOUT_ortho_5x12_wrapper(
      LSFT(KC_ESC),  _________________FUNC_LEFT_________________,_________________FUNC_RIGHT________________,  KC_BSPC,
      KC_INS,     _________________LOWER_L1__________________, _________________LOWER_R1__________________, KC_EQL,   
      KC_DEL,     _________________LOWER_L2__________________, _________________LOWER_R2__________________, KC_PLUS,
      _______,   _________________LOWER_L3__________________, _________________LOWER_R3__________________, KC_NO,
      _______,NUMPAD  ,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGDN,KC_END),

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
 * |      |      |      |      |      |             |      |      | Stop | Vol- |Pause |
 * `-----------------------------------------------------------------------------------'
 */
    [_RAISE] = LAYOUT_ortho_5x12_wrapper(
         KC_ESC,  ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_BSPC,
         KC_INS,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, KC_NO,
         KC_DEL,  _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
         _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, RGB_TOG,
         _______, NUMPAD , _______,_______, _______, _______, _______, _______, _______, KC_MSTP, KC_VOLD, KC_MPLY),

    [_FUNCTION] = LAYOUT_ortho_5x12_wrapper(
       _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, _______,
       _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15, KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20, _______,
       _______, SECRET1, SECRET2, SECRET3, SECRET4, SECRET5, _______, _______, _______, _______, _______, _______,
       _______, RCTL(KC_F11), RCTL(KC_F12), _______, _______, _______, _______, _______, _______, _______, _______,  _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),


    [_NUMPAD] = LAYOUT_ortho_5x12_wrapper(
       _______, _______, _______, _______, _______, _______, _________________NUMPAD_1__________________, _______,
       _______, _________________MOUSE_1___________________, _________________NUMPAD_2__________________, _______,
       _______, _________________MOUSE_2___________________, _________________NUMPAD_3__________________, _______,
       _______, _________________MOUSE_3___________________, _________________NUMPAD_4__________________, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    [_ADJUST] = LAYOUT_ortho_5x12_wrapper( 
        KC_ESC,  _________________ADJUST_L1_________________,   _________________ADJUST_R1_________________,   KC_SYSREQ,
        KC_MAKE, _________________ADJUST_L2_________________,   _________________ADJUST_R2_________________,   MY_PRINT_LAYOUT,  
        _______, _________________ADJUST_L3_________________,   _________________ADJUST_R3_________________,   _______,  
        _______, _________________ADJUST_L4_________________,   _________________ADJUST_R4_________________,   _______,  
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

};
// clang-format on




uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RALT_T(KC_LEFT):
        case RGUI_T(KC_DOWN):
        case RCTL_T(KC_RGHT):
        case HYPR_T(KC_UP):
            return TAPPING_TERM + 500;
            break;
        case MY_K: 
        case MY_LOW:      
        case MY_RAI:  
            return TAPPING_TERM +25;
            break;
        case MY_LGUI:  
            return TAPPING_TERM +125;
            break;
        default:
            return TAPPING_TERM;
    }
}

const rgblight_segment_t PROGMEM        my_lower_layer[]  = RGBLIGHT_LAYER_SEGMENTS({4, 2, HSV_RED});
const rgblight_segment_t PROGMEM        my_raise_layer[]  = RGBLIGHT_LAYER_SEGMENTS({4, 2, HSV_BLUE});
const rgblight_segment_t PROGMEM        my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 2, HSV_PURPLE});
const rgblight_segment_t PROGMEM        my_number_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 2, HSV_GREEN});
const rgblight_segment_t PROGMEM        my_function_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 2, HSV_CHARTREUSE});
const rgblight_segment_t *const PROGMEM my_rgb_layers[]   = RGBLIGHT_LAYERS_LIST(my_lower_layer, my_raise_layer, my_adjust_layer, my_number_layer,my_function_layer);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    // layer_state_set_user(layer_state);
    // Customise these values to desired behaviour

    //   debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    // Both layers will light up if both kb layers are active

    rgblight_set_layer_state(0, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUMPAD));
    rgblight_set_layer_state(4, layer_state_cmp(state, _FUNCTION));
    return state;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;



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

void matrix_init_user(void) {
    if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) {
        register_code(KC_NUMLOCK);
        unregister_code(KC_NUMLOCK);
    }
};



#ifdef TAP_DANCE_ENABLE
// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [MOD_LOW]  = MOD_LAYER(1, LOW_KEY, _LOWER, KC_RCTL, KC_RSFT),
    [MOD_RAI]  = MOD_LAYER(2, RAI_KEY, _RAISE, KC_RSFT, KC_RALT),
    [TD_B]     = MOD_LAYER(3, KC_B, _NUMPAD, KC_NO, KC_NO),
    [MOD_FN]   = MOD_LAYER(4, KC_K, _FUNCTION, KC_RCTL, KC_RSFT),

    [LBRC_9] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, l_brc_finished, l_brc_reset, 275),
    [RBRC_0] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, r_brc_finished, r_brc_reset, 275),
    // Tap Dance definitions

    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_SPC_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
    [TD_DEL_INS]  = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_INS),

};
#endif
