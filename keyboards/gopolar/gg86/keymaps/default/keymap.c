/* Copyright 2021 Gopolar
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

#include <string.h>
#include <math.h>

#include <lib/lib8tion/lib8tion.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// enum layer_names { };

enum user_rgb_mode {
    RGB_MODE_ALL,
    RGB_MODE_KEYLIGHT,
    RGB_MODE_UNDERGLOW,
    RGB_MODE_NONE,
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t rgb_mode :8;
    };
} user_config_t;

user_config_t user_config;

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
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI,  RGB_SAI, RGB_SPI,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD,  RGB_SAD, RGB_SPD,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,
                _______, _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______, _______,           RGB_VAI,
                _______, _______, _______,                   _______,                                     _______, _______, _______,          RGB_RMOD, RGB_VAD, RGB_MOD
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
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI,  RGB_SAI, RGB_SPI,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD,  RGB_SAD, RGB_SPD,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,
                _______, _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______, _______,           RGB_VAI,
                _______, _______, _______,                   _______,                                     _______, _______, _______,          RGB_RMOD, RGB_VAD, RGB_MOD
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
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI,  RGB_SAI, RGB_SPI,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD,  RGB_SAD, RGB_SPD,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,
                _______, _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______, _______,           RGB_VAI,
                _______, _______, _______,                   _______,                                     _______, _______, _______,          RGB_RMOD, RGB_VAD, RGB_MOD
    ),
};

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    switch (user_config.rgb_mode) {
        case RGB_MODE_ALL:
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            break;
        case RGB_MODE_KEYLIGHT:
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case RGB_MODE_UNDERGLOW:
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case RGB_MODE_NONE:
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        rgb_matrix_set_color_all(0, 0, 0);
                        user_config.rgb_mode = RGB_MODE_KEYLIGHT;
                    }
                    break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                        user_config.rgb_mode = RGB_MODE_UNDERGLOW;
                    }
                    break;
                    case (LED_FLAG_UNDERGLOW): {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                        user_config.rgb_mode = RGB_MODE_NONE;
                    }
                    break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                        user_config.rgb_mode = RGB_MODE_ALL;
                    }
                    break;
                }
                eeconfig_update_user(user_config.raw);
            }
            return false;
	}

    return true;
}

bool rgb_matrix_indicators_user(void) {
    HSV      hsv = rgb_matrix_config.hsv;
    uint8_t time = scale16by8(g_rgb_timer, qadd8(32, 1));
    hsv.h        = time;
    RGB      rgb = hsv_to_rgb(hsv);

    if ((rgb_matrix_get_flags() & LED_FLAG_KEYLIGHT)) {
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(25, rgb.r, rgb.g, rgb.b);
        }
        if (host_keyboard_led_state().scroll_lock) {
            rgb_matrix_set_color(73, rgb.r, rgb.g, rgb.b);
        }
    } else {
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(25, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(25, 0, 0, 0);
        }
        if (host_keyboard_led_state().scroll_lock) {
            rgb_matrix_set_color(73, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(73, 0, 0, 0);
        }
    }
    return false;
}

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
