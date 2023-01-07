/* Copyright 2022 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
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

#define L2_SPC      LT(2,KC_SPC)
#define L3_SPC      LT(3,KC_SPC)
#define RWINALT     RALT_T(KC_RGUI)
#define ISO_LT      KC_NUBS
#define ISO_GT      LSFT(KC_NUBS)

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_all(

    KC_ESC ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_BSPC      , KC_DEL ,
    KC_TAB   ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,KC_ENT     , KC_PGUP,
    SC_LSPO      ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,SC_RSPC ,KC_UP , KC_PGDN,
    KC_LCTL  ,KC_LALT  ,MO(2)  ,L2_SPC               ,L3_SPC           ,MO(3)  ,RWINALT  ,MO(1)   ,KC_LEFT,KC_DOWN,KC_RGHT 
    ),
[1] = LAYOUT_all(
    QK_BOOT  ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_RBRC,KC_DEL       , KC_INS ,
    KC_CAPS  ,KC_F11 ,KC_F12 ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX    , KC_HOME,
    _______      ,XXXXXXX,XXXXXXX,KC_PSCR,KC_SCRL,KC_PAUS,KC_INS ,KC_APP ,KC_LGUI,KC_RGUI,XXXXXXX,_______ ,KC_PGUP,KC_END ,
    KC_RCTL  ,_______  ,_______,XXXXXXX              ,XXXXXXX          ,_______,_______  ,_______ ,KC_HOME,KC_PGDN,KC_END  
    ),
[2] = LAYOUT_all(
    KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,KC_EQL       , XXXXXXX,
    KC_TILD  ,KC_EXLM,KC_AT  ,KC_HASH,KC_DLR ,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_UNDS,KC_LBRC,KC_RBRC,KC_BSLS    , XXXXXXX,
    _______      ,ISO_LT ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______ ,XXXXXXX,XXXXXXX,
    _______  ,_______  ,_______,XXXXXXX              ,XXXXXXX          ,_______,_______  ,_______ ,XXXXXXX,XXXXXXX,XXXXXXX 
    ),
[3] = LAYOUT_all(
    KC_TILD,KC_EXLM,KC_AT  ,KC_HASH,KC_DLR ,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_UNDS,KC_PLUS      , XXXXXXX,
    _______  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_LCBR,KC_RCBR,KC_PIPE    , XXXXXXX,
    _______      ,ISO_GT ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______ ,XXXXXXX,XXXXXXX,
    _______  ,_______  ,_______,XXXXXXX              ,XXXXXXX          ,_______,_______  ,_______ ,XXXXXXX,XXXXXXX,XXXXXXX 
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        }
        else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            tap_code16(KC_TAB);
        }
        else {
            alt_tab_timer = timer_read();
            tap_code16(S(KC_TAB));
        }
    }
    
    return false;
}

void matrix_scan_user(void) {
    
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1250) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
