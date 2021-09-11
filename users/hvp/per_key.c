 /* Copyright 2021 hvp
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


// #include per_key.h

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_A):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_LALT, KC_S):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_LSFT, KC_D):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_LCTL, KC_F):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_RCTL, KC_H):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_RSFT, KC_J):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_RALT, KC_K):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case MT(MOD_RGUI, KC_L):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        case KC_LCPO:
            return TAPPING_TERM 75;
        default:
            return TAPPING_TERM;
    }
}