/* Copyright 2020 Stephen J. Bush
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

#ifdef COMBO_ENABLE
#    include QMK_KEYBOARD_H

enum combos {
    H_COMM_TAB,
    L_U_SCLN,
    J_M_CAPS,
};

const uint16_t PROGMEM h_comm_tab[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM l_u_scln[]   = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM j_m_caps[]   = {KC_J, KC_M, COMBO_END};

// COMBO_COUNT defined in config.h
combo_t key_combos[COMBO_COUNT] = {
    [H_COMM_TAB] = COMBO(h_comm_tab, KC_TAB),
    [L_U_SCLN]   = COMBO(l_u_scln, KC_SCLN),
    [J_M_CAPS]   = COMBO(j_m_caps, KC_CAPS),
};
#endif
