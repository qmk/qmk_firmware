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
#pragma  once



typedef  struct {
    uint8_t index  ;
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



#define ACTION_MOD_LAYER( index,keycode,layer,mod_2_tap,mod_3_tap) { \
        .fn = { NULL, (void *)set_mod_layer, (void *)reset_mod_layer }, \
        .user_data =  (void *)&((mod_layer_t) { index, keycode,layer,mod_2_tap,mod_3_tap}), \
}

void reset_mod_layer(qk_tap_dance_state_t *state, void *user_data) ;
void set_mod_layer(qk_tap_dance_state_t *state, void *user_data) ;
