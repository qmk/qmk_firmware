/* Copyright 2021 Kyle Xiao
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
#include "txkyel.h"

#ifdef TAP_DANCE_ENABLE
// Default Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [HC_A]         = ACTION_TAP_HOLD_CTL(KC_A),
    [HC_B]         = ACTION_TAP_HOLD_CTL(KC_B),
    [HC_C]         = ACTION_TAP_HOLD_CTL(KC_C),
    [HC_D]         = ACTION_TAP_HOLD_CTL(KC_D),
    [HC_E]         = ACTION_TAP_HOLD_CTL(KC_E),
    [HC_F]         = ACTION_TAP_HOLD_CTL(KC_F),
    [HC_G]         = ACTION_TAP_HOLD_CTL(KC_G),
    [HC_H]         = ACTION_TAP_HOLD_CTL(KC_H),
    [HC_I]         = ACTION_TAP_HOLD_CTL(KC_I),
    [HC_J]         = ACTION_TAP_HOLD_CTL(KC_J),
    [HC_K]         = ACTION_TAP_HOLD_CTL(KC_K),
    [HC_L]         = ACTION_TAP_HOLD_CTL(KC_L),
    [HC_M]         = ACTION_TAP_HOLD_CTL(KC_M),
    [HC_N]         = ACTION_TAP_HOLD_CTL(KC_N),
    [HC_O]         = ACTION_TAP_HOLD_CTL(KC_O),
    [HC_P]         = ACTION_TAP_HOLD_CTL(KC_P),
    [HC_Q]         = ACTION_TAP_HOLD_CTL(KC_Q),
    [HC_R]         = ACTION_TAP_HOLD_CTL(KC_R),
    [HC_S]         = ACTION_TAP_HOLD_CTL(KC_S),
    [HC_T]         = ACTION_TAP_HOLD_CTL(KC_T),
    [HC_U]         = ACTION_TAP_HOLD_CTL(KC_U),
    [HC_V]         = ACTION_TAP_HOLD_CTL(KC_V),
    [HC_W]         = ACTION_TAP_HOLD_CTL(KC_W),
    [HC_X]         = ACTION_TAP_HOLD_CTL(KC_X),
    [HC_Y]         = ACTION_TAP_HOLD_CTL(KC_Y),
    [HC_Z]         = ACTION_TAP_HOLD_CTL(KC_Z),
    [HC_BSPC]      = ACTION_TAP_HOLD_CTL(KC_BSPC),
    [HC_DEL]       = ACTION_TAP_HOLD_CTL(KC_DEL),
    [HC_LEFT]      = ACTION_TAP_HOLD_CTL(KC_LEFT),
    [HC_RGHT]      = ACTION_TAP_HOLD_CTL(KC_RGHT),
    [TH_ESC_TAB]   = ACTION_TAP_HOLD(KC_TAB, KC_ESC),
    [TH_HOME_BSLS] = ACTION_TAP_HOLD(KC_BSLASH, KC_HOME),
    [TH_HOME_BSLS] = ACTION_TAP_HOLD(KC_PIPE, KC_END),
    [TH_QUOT_GRV]  = ACTION_TAP_HOLD(KC_QUOT, KC_GRV),
};
#endif
