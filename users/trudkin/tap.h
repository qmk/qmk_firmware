/* Copyright 2020 Terence Rudkin
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
#pragma once



enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  BACKLIT,
  KC_MAKE,
  RGB_SLD, 
  HSV_0_255_255,
  HSV_86_255_128,
  HSV_172_255_255,
  HSV_27_255_255,
  HSV_215_255_128,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3,
};



enum  td_keycodes {
     TD_ESC_CAPS,
    TD_DEL_INS,
    TD_SPC_ENT,
    TD_CUT,
    TD_COPY,
    TD_PASTE,
    NUM_LAYR,
    LBRC_9,
    RBRC_0,
    TD_PIPE,
    MOD_LOW,
    MOD_RAI,
    MOD_LOW1,
    MOD_RAI1,
    TD_M
};


#define MY_ESC TD(TD_ESC_CAPS)
#define MY_Q TD(NUM_LAYR)
#define MY_X TD(TD_CUT)
#define MY_C TD(TD_COPY)
#define MY_V TD(TD_PASTE)
#define MY_PIPE TD(TD_PIPE)
#define MY_DEL TD(TD_DEL_INS)
#define MY_9 TD(LBRC_9)
#define MY_0 TD(RBRC_0)
#define MY_M TD(TD_M)


typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

typedef  struct {
    uint8_t index;
    uint8_t keycode;
    uint8_t layer;
    uint8_t mod_2_tap;
    uint8_t mod_3_tap;
} mod_layer_t;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD,
    FUTURE_STATE
};


#ifndef MOD_LMT 
#   define MOD_LMT 8
#endif 


uint8_t cur_dance(qk_tap_dance_state_t *state);

// For the left brace tap dance. Put it here so it can be used in any keymap
void l_brc_finished(qk_tap_dance_state_t *state, void *user_data);
void l_brc_reset(qk_tap_dance_state_t *state, void *user_data);
// For the right brace tap dance. Put it here so it can be used in any keymap
void r_brc_finished(qk_tap_dance_state_t *state, void *user_data);
void r_brc_reset(qk_tap_dance_state_t *state, void *user_data);
// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

void pipe_finished(qk_tap_dance_state_t *state, void *user_data);
void pipe_reset(qk_tap_dance_state_t *state, void *user_data);


void reset_mod_layer(qk_tap_dance_state_t *state, void *user_data);
void set_mod_layer(qk_tap_dance_state_t *state, void *user_data);



#define MOD_LAYER( index,keycode,layer,mod_2_tap,mod_3_tap) { \
        .fn = { NULL, (void *)set_mod_layer, (void *)reset_mod_layer }, \
        .user_data =  (void *)&((mod_layer_t) { index, keycode,layer,mod_2_tap,mod_3_tap}), \
}

