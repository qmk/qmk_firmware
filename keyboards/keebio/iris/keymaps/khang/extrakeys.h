/* Copyright 2021 Nguyen Vu Khang <brew4k@gmail.com>
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

enum my_keycodes {
    ______ = SAFE_RANGE,
    HYPR1, HYPR2, HYPR3, HYPR4, HYPR5, HYPR6, HYPR7, HYPR8, HYPR9, HYPR0,
    HYPRL,
    HYPRM,
    HYPRP,
    HYPRQ,
    HYPRS,
    HYPRT,
    KC_STAB
};

#undef _______
#define ______ KC_NO

#define HYPR1 HYPR(KC_1)
#define HYPR2 HYPR(KC_2)
#define HYPR3 HYPR(KC_3)
#define HYPR4 HYPR(KC_4)
#define HYPR5 HYPR(KC_5)
#define HYPR6 HYPR(KC_6)
#define HYPR7 HYPR(KC_7)
#define HYPR8 HYPR(KC_8)
#define HYPR9 HYPR(KC_9)
#define HYPR0 HYPR(KC_0)

#define HYPRL HYPR(KC_L)
#define HYPRM HYPR(KC_M)
#define HYPRP HYPR(KC_P)
#define HYPRQ HYPR(KC_Q)
#define HYPRS HYPR(KC_S)
#define HYPRT HYPR(KC_T)

#define KC_STAB LSFT(KC_TAB)

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    switch (keycode) {
        case KC_BSPC: {
            static bool delkey_registered;
            if (record->event.pressed) { // on key-down of Backspace
                if (mod_state & MOD_MASK_CTRL) {
                    // Ctrl + Backspace -> Forward Delete
                    del_mods(MOD_MASK_CTRL);
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of Backspace
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            return true;
        };
        break;
    }
    return true;
};
