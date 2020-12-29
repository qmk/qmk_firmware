/* Copyright 2020 Nick Blyumberg
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


/**
 * Layer Names
 */
enum bdn9_layers {
    BASE = 0,
    APP1,
    APP2,
    APP3,
    APP4,
    APP5,
    APP6,
    ADJUST
};

enum bdn9_keycodes {
    KC_TEST = KEYMAP_SAFE_RANGE,
    KC_TEST1,
    KC_TEST2
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Layer: Base
        ┌───────────┐  ┌───────────┐
        │   Items   │  │    Subs   │
        │  Prv  Nxt │  │  Prv  Nxt │
        ├────────┬──┴──┴──┬────────┤
        │ VwBrsw │  Star  │  Sync  │
        ├────────┼────────┼────────┤
        │ CmdTab │ TgRead │  Clear │
        ├────────┼────────┼────────┤
        │ VwStard│ VwUnrd │  VwAll │
        └────────┴────────┴────────┘
     */
    [BASE] = LAYOUT(
        KC_MPLY, RESET, KC_MUTE,
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
    ),
    /*
        Layer: Media
        ┌───────────┐  ┌───────────┐
        │    Vol    │  │   Track   │
        │  Prv  Nxt │  │  Prv  Nxt │
        ├────────┬──┴──┴──┬────────┤
        │  Mute  │ Player │  Sync  │
        ├────────┼────────┼────────┤
        │ YT<10s │ YT Ply │ YT>10s │
        ├────────┼────────┼────────┤
        │  Left  │  Spce  │  Rght  │
        └────────┴────────┴────────┘
     */
    [APP1] = LAYOUT(
        KC_MPLY, KC_S, KC_MUTE,
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
    ),
    /*
        Layer: Navigation
        ┌───────────┐  ┌───────────┐
        │  Scroll   │  │    Tab    │
        │  Up   Dn  │  │  Prv  Nxt │
        ├────────┬──┴──┴──┬────────┤
        │ ReOTab │ CmdTab │ ClsTab │
        ├────────┼────────┼────────┤
        │  PgDn  │   Up   │  PgUp  │
        ├────────┼────────┼────────┤
        │  Left  │  Down  │  Rght  │
        └────────┴────────┴────────┘
     */
    [APP2] = LAYOUT(
        KC_MPLY, KC_S, KC_MUTE,
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
    ),
    /*
        Layer: Macro/Karabiner
        ┌───────────┐  ┌───────────┐
        │           │  │           │
        │   -    +  │  │   .    =  │
        ├────────┬──┴──┴──┬────────┤
        │    1   │    2   │    3   │
        ├────────┼────────┼────────┤
        │    4   │    5   │    6   │
        ├────────┼────────┼────────┤
        │    7   │    8   │    9   │
        └────────┴────────┴────────┘
     */
    [APP2] = LAYOUT(
        KC_MPLY, KC_S, KC_MUTE,
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
    ),
    /*
        Layer: Lightroom Navigation
        ┌───────────┐  ┌───────────┐
        │ Thumbnail │  │ Scrl Grid │
        │ Dec   Inc │  │ Up     Dn │
        ├────────┬──┴──┴──┬────────┤
        │ TgRevw │CylGrdVw│ TgEdit │
        ├────────┼────────┼────────┤
        │  Start │   Up   │  End   │
        ├────────┼────────┼────────┤
        │  Left  │  Down  │  Rght  │
        └────────┴────────┴────────┘
     */
    [APP3] = LAYOUT(
        KC_MPLY, KC_S, KC_MUTE,
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
    ),
    /*
        Layer: Review/Rate
        ┌───────────┐  ┌───────────┐
        │   Stars   │  │   Flag    │
        │ Dec   Inc │  │ Dec   Inc │
        ├────────┬──┴──┴──┬────────┤
        │ TgLNav │ Yellow │ TgEdit │
        ├────────┼────────┼────────┤
        │ NoStar │  Green │ UnFlag │
        ├────────┼────────┼────────┤
        │  Left  │  Blue  │  Rght  │
        └────────┴────────┴────────┘
     */
    [APP4] = LAYOUT(
        KC_MPLY, KC_S, KC_MUTE,
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
    ),
    /*
        Layer: Edit/Develop
        ┌───────────┐  ┌───────────┐
        │  Sliders  │  │   Value   │
        │ Prv   Nxt │  │ Dec   Inc │
        ├────────┬──┴──┴──┬────────┤
        │ TgRevw │ Bf/Aft │ TgLNav │
        ├────────┼────────┼────────┤
        │ FlgRjt │  Undo  │ FlgPkd │
        ├────────┼────────┼────────┤
        │  Left  │  Redo  │  Rght  │
        └────────┴────────┴────────┘
     */
    [APP5] = LAYOUT(
        KC_MPLY, KC_S, KC_MUTE,
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
    ),
    /*
        Layer: Light
        ┌───────────┐  ┌───────────┐
        │  RGB Hue  │  │  RGB Sat  │
        │ Prv   Nxt │  │ Dec   Inc │
        ├────────┬──┴──┴──┬────────┤
        │ RGBTgl │  Val+  │ TgLNav │
        ├────────┼────────┼────────┤
        │  Mode- │  Val-  │  Mode+ │
        ├────────┼────────┼────────┤
        │ LyrTgl │ NxtThm │  XXXX  │
        └────────┴────────┴────────┘
     */
    [APP6] = LAYOUT(
        KC_MPLY, KC_S, KC_MUTE,
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
    ),
    /*
        Layer: ADJUST
        ┌───────────┐  ┌───────────┐
        │    XXXX   │  │   XXXX    │
        │           │  │           │
        ├────────┬──┴──┴──┬────────┤
        │  MAKE  │ Reeder │  Light │
        ├────────┼────────┼────────┤
        │  Media │  Navi  │  Macro │
        ├────────┼────────┼────────┤
        │ LR Rvw │ LR Nav │ LR Edt │
        └────────┴────────┴────────┘
     */
    [ADJUST] = LAYOUT(
        KC_MPLY, KC_S, KC_MUTE,
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
    ),
};

void keyboard_post_init_keymap(void){
    // Debug to Console by default
    debug_enable = true;
}

/**
 * Encoder
 */
const uint16_t PROGMEM encoders[][2][2] = {
    [BASE] = {{ KC_MPRV, KC_MNXT }, { KC_VOLD, KC_VOLU }},
    [APP1] = {{ KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT }},
    [APP2] = {{ KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT }},
    [APP3] = {{ KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT }},
    [APP4] = {{ KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT }},
    [APP5] = {{ KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT }},
    [APP6] = {{ KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT }},
    [ADJUST] = {{ KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT }}
};

void encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);

    switch (layer) {
        case BASE:
            switch (index) {
                case 0:
                    if (clockwise) {
                        tap_code(KC_MPRV);
                    } else {
                        tap_code(KC_MNXT);
                    }
                    break;
                case 1:
                    if (clockwise) {
                        tap_code(KC_VOLD);
                    } else {
                        tap_code(KC_VOLU);
                    }
                    break;
            }
        case ADJUST:
            switch (index) {
                case 0:
                    if (clockwise) {
                        rgblight_increase_hue();
                    } else {
                        rgblight_decrease_hue();
                    }
                    break;
                case 1:
                    if (clockwise) {
                        rgblight_increase_sat();
                    } else {
                        rgblight_decrease_sat();
                    }
                    break;
            }
            break;
        case APP1:

            break;
        case APP2:

            break;
        case APP3:

            break;
        case APP4:

            break;
        case APP5:

            break;
        case APP6:

            break;
        default:
            break;
    }
}

/**
 * Keycodes
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TEST:
            if (!record->event.pressed) {
                tap_code(KC_G);
                layer_move(APP1);
            }
            break;
        case KC_TEST1:
            if (!record->event.pressed) {
                tap_code(KC_E);
                layer_move(APP2);
            }
            break;
        case KC_TEST2:
            if (!record->event.pressed) {
                tap_code(KC_D);
                layer_move(APP3);
            }
            break;
    }
    return true;
}

