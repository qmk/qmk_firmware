/* Copyright 2023 Gopolar
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

// OLED animation
#include "lib/wave.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// enum layer_names { };

// enum layer_keycodes { };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Bckspc│ │Hom│Scr│Pse│
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │ Tab │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │  \  │ │End│Scr│Pse│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │ Caps │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │   Enter│
       ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐
       │LSft│ \ │ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │ RSft │RSt│     │ ↑ │
       ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤ ┌───┼───┼───┐
       │LCrl │GUI│ LAlt│           Space           │ RAlt│ Fn│ RCrl│ │ ← │ ↓ │ → │
       └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │   │   │   │   │   │   │ │   │   │   │   │ │   │   │   │   │ │   │   │   │
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │ │   │   │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ { │ } │  |  │ │   │   │   │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ : │ " │        │
       ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐
       │LSft│ | │ Z │ X │ C │ V │ B │ N │ M │ < │ > │ ? │ RSft │RSt│     │   │
       ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤ ┌───┼───┼───┐
       │     │   │     │                           │     │   │     │ │   │   │   │
       └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3      4      5       6      7      8      9        10       11       12       13       14       15       16      */
	[0] = LAYOUT_all(
                KC_ESC,  KC_F1,   KC_F2,   KC_F3, KC_F4, KC_F5,  KC_F6, KC_F7, KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SCRL, KC_PAUSE,
                KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,   KC_6,  KC_7,  KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
                KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,   KC_Y,  KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
                KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,   KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
                KC_LSFT, KC_NUBS, KC_Z,    KC_X,  KC_C,  KC_V,   KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,          KC_UP,
                KC_LCTL, KC_LGUI, KC_LALT,               KC_SPC,                               KC_RALT, MO(1),   KC_RCTL,          KC_LEFT, KC_DOWN, KC_RIGHT
    ),

/*
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │Slp│   │M_T│F13│F14│F15│ │F16│Rfh│Stp│   │ │   │   │   │Est│ │   │VoD│VoU│
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │Hui│Sai│Spi│
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │Hud│Sad│Spd│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │      │   │   │   │   │   │   │   │   │   │   │   │ RGB_Tog│
       ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐
       │    │   │   │   │Cal│   │   │   │   │   │   │   │      │   │     │Vai│
       ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤ ┌───┼───┼───┐
       │     │   │     │                           │     │   │     │ │Rod│Vad│Mod│
       └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14        15       16     */
	[1] = LAYOUT_all(
                KC_SLEP, RGB_M_T, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_WREF, KC_WSTP, _______, _______, _______, _______, EE_CLR,           _______,  KC_VOLD, KC_VOLU,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_HUEU,  RM_SATU, RM_SPDU,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_HUED,  RM_SATD, RM_SPDD,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RM_TOGG,
                _______, _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______, _______,           RM_VALU,
                _______, _______, _______,                   _______,                                     _______, _______, _______,          RM_PREV,  RM_VALD, RM_NEXT
    ),

/*
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │Slp│   │F13│F14│F15│F16│ │Rfh│Stp│   │   │ │   │   │   │   │ │   │VoD│VoU│
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │Hui│Sai│Spi│
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │Hud│Sad│Spd│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │      │   │   │   │   │   │   │   │   │   │   │   │ RGB_Tog│
       ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐
       │    │   │   │   │Cal│   │   │   │   │   │   │   │      │   │     │Vai│
       ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤ ┌───┼───┼───┐
       │     │   │     │                           │     │   │     │ │Rod│Vad│Mod│
       └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14        15       16     */
	[2] = LAYOUT_all(
                KC_SLEP, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_WREF, KC_WSTP, _______, _______, _______, _______, _______, _______,          _______,  KC_VOLD, KC_VOLU,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_HUEU,  RM_SATU, RM_SPDU,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_HUED,  RM_SATD, RM_SPDD,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RM_TOGG,
                _______, _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______, _______,           RM_VALU,
                _______, _______, _______,                   _______,                                     _______, _______, _______,          RM_PREV,  RM_VALD, RM_NEXT
    ),

/*
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │Slp│   │F13│F14│F15│F16│ │Rfh│Stp│   │   │ │   │   │   │   │ │   │VoD│VoU│
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │Hui│Sai│Spi│
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │Hud│Sad│Spd│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │      │   │   │   │   │   │   │   │   │   │   │   │ RGB_Tog│
       ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐
       │    │   │   │   │Cal│   │   │   │   │   │   │   │      │   │     │Vai│
       ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤ ┌───┼───┼───┐
       │     │   │     │                           │     │   │     │ │Rod│Vad│Mod│
       └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14        15       16     */
	[3] = LAYOUT_all(
                KC_SLEP, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_WREF, KC_WSTP, _______, _______, _______, _______, _______, _______,          _______,  KC_VOLD, KC_VOLU,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_HUEU,  RM_SATU, RM_SPDU,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_HUED,  RM_SATD, RM_SPDD,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RM_TOGG,
                _______, _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______, _______,           RM_VALU,
                _______, _______, _______,                   _______,                                     _______, _______, _______,          RM_PREV,  RM_VALD, RM_NEXT
    ),
};

#ifdef OLED_ENABLE
    static void render_layer_info(void) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("QWERTY       "), false);
                break;
            case 1:
                oled_write_P(PSTR("Function     "), false);
                break;
            case 2:
                oled_write_P(PSTR("Function     "), false);
                break;
            case 3:
                oled_write_P(PSTR("Function     "), false);
                break;
            default:
                oled_write_P(PSTR("Undefined    "), false);
        }
    }

    static void render_layer_number(void) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("0"), false);
                break;
            case 1:
                oled_write_P(PSTR("1"), false);
                break;
            case 2:
                oled_write_P(PSTR("2"), false);
                break;
            case 3:
                oled_write_P(PSTR("3"), false);
                break;
            default:
                oled_write_P(PSTR("X"), false);
        }
    }

    bool oled_task_user(void) {
        led_t led_usb_state = host_keyboard_led_state();

        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLK ") : PSTR("----- "), false);
        oled_write_P(PSTR(" GOPOLAR "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR(" SCRLK") : PSTR(" -----"), false);

        // sleep if it has been long enough since we last got a char
        if (timer_elapsed32(wave_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            oled_on();
        }
        // time for the next frame?
        if (timer_elapsed(wave_timer) > FRAME_TIMEOUT) {
            wave_timer = timer_read();
            render_frame();
        }

        oled_set_cursor(0, 3);
        render_layer_info();
        oled_write_P(PSTR("Layer: "), false);
        render_layer_number();

        return true;
    }
#endif
