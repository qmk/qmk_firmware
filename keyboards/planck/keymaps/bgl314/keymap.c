/* Copyright 2015-2021 Jack Humbert
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
//#include "features/caps_word.h"
#include "song_list.h"

#define MASTER1_SOUND  Q__NOTE(_E4),Q__NOTE(_E4),Q__NOTE(_E5) , Q__NOTE(_E4),Q__NOTE(_E4),Q__NOTE(_DS5) , Q__NOTE(_E4),Q__NOTE(_E4),H__NOTE(_D5) , H__NOTE(_CS5) , W__NOTE(_C5),                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       \

#define MASTER2_SOUND  Q__NOTE(_E4),Q__NOTE(_E4),Q__NOTE(_B4),Q__NOTE(_E4),Q__NOTE(_E4),Q__NOTE(_AS4),Q__NOTE(_E4),Q__NOTE(_E4), Q__NOTE(_A4), Q__NOTE(_E4),Q__NOTE(_GS4) , Q__NOTE(_E4), \
Q__NOTE(_G4), Q__NOTE(_E4), H__NOTE(_E4), H__NOTE(_E4) ,

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
#define ANGEL_SONG1 Q__NOTE(_E4) ,E__NOTE(_E4),    E__NOTE(_E4),E__NOTE(_E4),E__NOTE(_E4),E__NOTE(_E4),E__NOTE(_E4),\
Q__NOTE(_E4), Q__NOTE(_F4), Q__NOTE(_F4),    E__NOTE(_E4), E__NOTE(_E4), E__NOTE(_E4), E__NOTE(_E4), E__NOTE(_E4), E__NOTE(_E4), Q__NOTE(_E4), Q__NOTE(_FS4), Q__NOTE(_FS4),E__NOTE(_E4), E__NOTE(_E4), E__NOTE(_E4), E__NOTE(_E4), E__NOTE(_E4), E__NOTE(_E4),


 #define ANGEL_SONG2  Q__NOTE(_F4) , Q__NOTE(_E4)  , Q__NOTE(_F4) , H__NOTE(_A4), H__NOTE(_GS4) ,

//#define MASTER_SOUND E__NOTE(_B5)
enum td_keycodes {
    SHIFT_CAPS, // Our example key: `lshift` when held, `capslock` when tapped. Add additional keycodes for each tapdance.
    SCLN_ENT, // tap ent, hold shift, doubletap semicolon enter
    BSPC_QWERTY // tap backspace, doubletap qwerty
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;
// Create a global instance of the tapdance state type
static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void shift_ent_caps_finished(qk_tap_dance_state_t *state, void *user_data);
void shift_ent_caps_reset(qk_tap_dance_state_t *state, void *user_data);

void shift_ent_sent_finished(qk_tap_dance_state_t *state, void *user_data);
void shift_ent_sent_reset(qk_tap_dance_state_t *state, void *user_data);

enum layers {
_COLEMAK,
_QWERTY,
_NUMBERS,
_SYMBOLS,
_ADJUST,
_NAV,
_FN
};


float snd_qwerty[][2] = SONG(MASTER1_SOUND);
float snd_exit_qwerty[][2] = SONG(MASTER2_SOUND);

//float snd_lefthand[][2] = SONG(MASTER1_SOUND);
//float snd_exit_lefthand[][2] = SONG(MASTER2_SOUND);

float snd_adjust[][2] = SONG(WORKMAN_SOUND);


layer_state_t prior = -1;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_ortho_4x12(
    KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, TD(SCLN_ENT), KC_BSPC,
    KC_ESC, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
    TD(SHIFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT),
     MO(_FN), KC_MENU,KC_INS,MT(MOD_LALT,KC_ENT),TT(_NUMBERS),MT(MOD_LCTL,KC_SPC), LT(_NAV,KC_SPC), MO(_SYMBOLS),MT(MOD_RALT,KC_LGUI) ,KC_PRINT_SCREEN, TG(_QWERTY), KC_DEL ),

	[_QWERTY] = LAYOUT_ortho_4x12(
    KC_TRNS, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TRNS,
    KC_TRNS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[_NUMBERS] = LAYOUT_ortho_4x12(
        KC_BSPC, KC_PLUS, KC_7, KC_8, KC_9, KC_PAST, KC_PLUS, KC_7, KC_8, KC_9, KC_PAST, KC_TRNS,
        KC_DEL, KC_PMNS, KC_4, KC_5, KC_6, KC_PSLS, KC_PMNS, KC_4, KC_5, KC_6, KC_PSLS, KC_TRNS,
        KC_ENT, KC_0,  KC_1, KC_2, KC_3, KC_DOT, KC_0, KC_1, KC_2, KC_3, KC_DOT, KC_TRNS,
        KC_NO, KC_NO, KC_NO,KC_DOT, KC_TRNS,KC_NO,KC_0, MO(_ADJUST),  KC_DOT, KC_NO, KC_NO, KC_TRNS),

	[_SYMBOLS] = LAYOUT_ortho_4x12(
        KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
        KC_DEL, KC_TILD, KC_GRV ,KC_LCBR, KC_LPRN,  KC_LBRC, KC_RBRC, KC_RPRN,  KC_RCBR, KC_PIPE , KC_BSLASH, KC_NO,
        KC_TRNS, KC_LT,    KC_NO, KC_NO, KC_UNDS, KC_MINUS,KC_PLUS , KC_EQL , KC_LT,   KC_GT,  KC_GT, KC_TRNS,
        KC_NO, KC_NO, KC_NO,KC_NO,MO(_ADJUST),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS),

    [_ADJUST] = LAYOUT_ortho_4x12(
	KC_SLEP, KC_WAKE, KC_NO, 	KC_NO, 		KC_NO, 		KC_NO,  KC_NO,  MU_ON,   MU_OFF, AU_ON, AU_OFF, KC_NO,
	KC_BRIU, RGB_VAI, RGB_HUI, 	RGB_SAI, 	RGB_TOG, 	KC_BRIU, 	KC_MPLY, KC_VOLU, KC_MUTE, KC_NO, 	KC_NO, 	KC_NO,
	KC_BRID, RGB_VAD, RGB_HUD, 	RGB_SAD, 	KC_NO, 		KC_BRID, 	KC_MSTP,  KC_VOLD,  KC_NO,   KC_NO, 	KC_NO,   KC_NO,
	KC_NO, 	 KC_NO,   KC_NO, 	KC_NO, 	KC_NO,	KC_NO, 	KC_NO,  KC_NO, 	KC_NO, 	 KC_NO,   DEBUG, 	RESET),
	[_NAV] = LAYOUT_ortho_4x12(
        KC_NO, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_DEL, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_RSHIFT,KC_RCTL, KC_INS, KC_NO, KC_NO,
        KC_TRNS,  RCTL(KC_Z),RCTL(KC_X),RCTL(KC_C),RCTL(KC_V), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_NO, KC_NO,  KC_NO,KC_NO,KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS),
	[_FN] = LAYOUT_ortho_4x12(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,
        KC_NO, KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
    case _COLEMAK:
        if(get_highest_layer(prior)== _QWERTY){
             #ifdef AUDIO_ENABLE
            PLAY_SONG(snd_exit_qwerty);
            #endif

        }
        // else if(get_highest_layer(prior)== _FN){
        //      #ifdef AUDIO_ENABLE
        //     PLAY_SONG(snd_exit_lefthand);
        //     #endif

        // }

        rgblight_setrgb (0x85,  0xbe, 0xff);
        break;
    case _QWERTY:
        if(-1 != prior && get_highest_layer(prior)== _COLEMAK){
            #ifdef AUDIO_ENABLE
            PLAY_SONG(snd_qwerty);
            #endif
        }
        //  else if(get_highest_layer(prior)== _FN){
        //      #ifdef AUDIO_ENABLE
        //     PLAY_SONG(snd_exit_lefthand);
        //     #endif

        // }
        rgblight_setrgb (0xff,  0x00, 0x00);
        break;

    case _ADJUST:
    #ifdef AUDIO_ENABLE
            PLAY_SONG(snd_adjust);
            #endif
        rgblight_setrgb (0x26,  0xFF, 0x00);
        break;
    case _NAV:
    // #ifdef AUDIO_ENABLE
    //         PLAY_SONG(snd_nav);
    //         #endif
        rgblight_setrgb (0x00,  0x19, 0xFF);
        break;
    case _NUMBERS:
    // #ifdef AUDIO_ENABLE
    //         PLAY_SONG(snd_numbers);
    //         #endif
        rgblight_setrgb (0x7A,  0x00, 0xFF);

        break;
    case _SYMBOLS:
    // #ifdef AUDIO_ENABLE
    //         PLAY_SONG(snd_symbols);
    //         #endif
        rgblight_setrgb (0x00,  0x77, 0xff);
        break;
    case _FN:
    // if(-1 != prior && (get_highest_layer(prior)== _COLEMAK || get_highest_layer(prior)== _QWERTY)){
    //         #ifdef AUDIO_ENABLE
    //         PLAY_SONG(snd_lefthand);
    //         #endif
    //     }
        rgblight_setrgb (0xFF,  0x82, 0xB2);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0xff,  0xFF, 0xFF);
        break;
    }
 prior = state;
  return state;
}

// bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//   if (!process_caps_word(keycode, record)) { return false; }
//   // Your macros ...

//   return true;
// }
//tapdancestuff

// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}


// SHIFT-ENTER-CAPS
// Handle the possible states for each tapdance keycode you define:

void shift_ent_caps_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            // register_code16(KC_ENT);
            // break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSHIFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_code16(KC_CAPS);
            break;
        default:
            break;
    }
}

void shift_ent_caps_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
        //     unregister_code16(KC_ENT);
        //     break;
        // case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSHIFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_CAPS);
            break;
        default:
            break;
    }
}

// END SHIFT-ENTER-CAPS


// SHIFT-ENTER-SEMICOLON/ENTER
// Handle the possible states for each tapdance keycode you define:

void scln_ent_sent_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_SCLN);
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_code16(KC_SCLN);
            register_code16(KC_ENT);
            break;
        default:
            break;
    }
}

void scln_ent_sent_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_SCLN);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SCLN);
            unregister_code16(KC_ENT);
            break;
        default:
            break;
    }
}
// END SHIFT-ENTER-CAPS

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [SHIFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_ent_caps_finished, shift_ent_caps_reset),
    [SCLN_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_ent_sent_finished, scln_ent_sent_reset),
    [BSPC_QWERTY] =ACTION_TAP_DANCE_LAYER_TOGGLE(KC_BSPC,_QWERTY)
};

