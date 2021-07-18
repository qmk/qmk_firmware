/*Copyright 2021 @Gam3cat

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include "gam3cat.h"

enum layers {
    _L0 = 0,
    _L1,
    _L2,
    _L3,
    _L4,
    _L5,
    _L6,
    _L7,
    _L8,
    _L9
};

enum custom_keycodes {
    KC_WCLS = NEW_SAFE_RANGE,
};

extern backlight_config_t backlight_config;

#define FN_ZERO LT(_L9, KC_KP_0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*## Layout Config:
    *     .-----------.  .-----------.  .-----------.  .-----------.  .-----------.
    *     |7  |8  |9  |  |+  |-  |*  |  |^  |&  |!  |  |VLU|Ver|WFD|  |VLU|NXT|FFD|
    *     |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *     |4  |5  |6  |  |/  |%  |,  |  |D  |E  |F  |  |MUT|C-W|CHR|  |MUT|STP|PLY|
    *     |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *     |1  |2  |3  |  |.  |=  |Ent|  |A  |B  |C  |  |VLD|CMP|WBK|  |VLD|PRV|RWD|
    *     |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *     |#L0|_L9/0  |  |#L1|_L9    |  |#L2|_L9    |  |#L3|_L9    |  |#L4|_L9    |
    *     *-----------*  *-----------*  *-----------*  *-----------*  *-----------*
    *     .-----------.  .-----------.  .-----------.  .-----------.  .-----------.
    *     |   |   |   |  |   |   |   |  |MP1|   |MP2|  |   |   |RST|  |_L6|_L7|_L8|
    *     |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *     |   |   |   |  |   |   |   |  |   |MRS|   |  |   |   |   |  |_L3|_L4|_L5|
    *     |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *     |   |   |   |  |   |   |   |  |MR1|   |MR2|  |   |   |   |  |_L0|_L1|_L2|
    *     |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *     |#L5|_L9    |  |#L6|_L9    |  |#L7|_L9    |  |#L8|_L9    |  |#L9|       |
    *     *-----------*  *-----------*  *-----------*  *-----------*  *-----------*
    */
    [_L0] = {{KC_KP_7, KC_KP_8, KC_KP_9}, {KC_KP_4, KC_KP_5, KC_KP_6}, {KC_KP_1, KC_KP_2, KC_KP_3}, {XXXXXXX, XXXXXXX, FN_ZERO}},
    [_L1] = {{KC_PPLS, KC_PMNS, KC_PAST}, {KC_PSLS, KC_PERC, KC_COMM}, {KC_PDOT, KC_EQL,  KC_PENT}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L2] = {{KC_CIRC, KC_AMPR, KC_EXLM}, {S(KC_D), S(KC_E), S(KC_F)}, {S(KC_A), S(KC_B), S(KC_C)}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L3] = {{KC_VOLU, QMK_REV, KC_WFWD}, {KC_MUTE, KC_WCLS, KC_WEB }, {KC_VOLD, KC_MYCM, KC_WBAK}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L4] = {{KC_VOLU, KC_MNXT, KC_MFFD}, {KC_MUTE, KC_MSTP, KC_MPLY}, {KC_VOLD, KC_MPRV, KC_MRWD}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L5] = {{_______, _______, _______}, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L6] = {{_______, _______, _______}, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L7] = {{DM_PLY1, _______, DM_PLY2}, {_______, DM_RSTP, _______}, {DM_REC1, _______, DM_REC2}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L8] = {{_______, _______, RESET  }, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L9] = {{DF(_L6), DF(_L7), DF(_L8)}, {DF(_L3), DF(_L4), DF(_L5)}, {DF(_L0), DF(_L1), DF(_L2)}, {XXXXXXX, XXXXXXX, _______}},
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_WCLS:
            if (record->event.pressed) {
                SEND_STRING (SS_LCTRL("w"));
            }
            return false;
            break;
    }
    return true;
}

void custom_backlight_level(uint8_t level) {
    if (level > BACKLIGHT_LEVELS)
        level = BACKLIGHT_LEVELS;
    backlight_config.level = level;
    backlight_config.enable = !!backlight_config.level;
    backlight_set(backlight_config.level);
}

void matrix_init_user(void) {
  #ifdef BACKLIGHT_ENABLE
    custom_backlight_level(0);
  #endif
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case _L0:
            custom_backlight_level(0);
            break;
        case _L1:
            custom_backlight_level(1);
            break;
        case _L2:
            custom_backlight_level(2);
            break;
        case _L3:
            custom_backlight_level(3);
            break;
        case _L4:
            custom_backlight_level(4);
            break;
        case _L5:
            custom_backlight_level(5);
            break;
        case _L6:
            custom_backlight_level(6);
            break;
        case _L7:
            custom_backlight_level(6);
            break;
        case _L8:
            custom_backlight_level(6);
            break;
        case _L9:
            custom_backlight_level(0);
            break;
        default:
            custom_backlight_level(0);
            break;
    }
    return state;
}
