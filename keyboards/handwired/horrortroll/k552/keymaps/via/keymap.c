/*
Copyright 2021 HorrorTroll

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE = 0,
    _FN = 1
};

// enum layer_keycodes { };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │ Tab │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │  \  │ │Del│End│PgD│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │ Caps │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │  Enter │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
       │ LShift │ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │   RShift │     │ ↑ │
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
       │LCrl│GUI │LAlt│         Space          │RAlt│ Fn │ App│RCrl│ │ ← │ ↓ │ → │
       └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │   │   │   │   │   │   │ │   │   │   │   │ │   │   │   │   │ │   │   │   │
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │ │   │   │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ { │ } │  |  │ │   │   │   │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ : │ " │        │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
       │ LShift │ Z │ X │ C │ V │ B │ N │ M │ < │ > │ ? │   RShift │     │   │
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
       │    │    │    │                        │    │    │    │    │ │   │   │   │
       └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14       15        16      */
    [_BASE] = LAYOUT_tkl_ansi(
                KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SLCK,  KC_PAUSE,
                KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME,  KC_PGUP,
                KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,   KC_PGDN,
                KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
                KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
                KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_RALT, MO(_FN), KC_APP,           KC_RCTL,                                              KC_LEFT, KC_DOWN,  KC_RIGHT
            ),

/*
       ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
       │Rst│   │MeP│VoD│VoU│Mut│ │Stp│Prv│Ply│Nxt│ │Mai│Hom│Cal│Sch│ │Rod│Mod│Tog│
       └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
       │   │   │   │   │   │   │   │   │   │   │   │Spd│Spi│       │ │   │   │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
       │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │   │   │   │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
       │      │   │   │   │   │   │   │   │   │   │   │   │        │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
       │        │   │   │   │   │   │   │   │   │   │   │          │     │Vai│
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
       │    │    │    │                        │    │ Fn │    │    │ │Hud│Vad│Hui│
       └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14       15        16     */
    [_FN]   = LAYOUT_tkl_ansi(
                RESET,   KC_MSEL, KC_VOLD, KC_VOLU, KC_MUTE, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MAIL, KC_WHOM, KC_CALC, KC_WSCH,          RGB_RMOD, RGB_MOD,  RGB_TOG,
                NK_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______, _______,  _______,  _______,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,           RGB_VAI,
                _______, _______, _______, _______, _______, _______, _______,          _______,                                              RGB_HUD,  RGB_VAD,  RGB_HUI
            ),
};

#ifdef OLED_ENABLE
#define ANIM_SIZE 636  // number of bytes in array, minimize for adequate firmware size, max is 1024

static void render_logo(void) {
    static const char PROGMEM redragon[][ANIM_SIZE] = {
        {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x80,
        0x80, 0xc0, 0xe0, 0x80, 0xc0, 0xe0, 0x30, 0x8c, 0x83, 0xc0, 0x60, 0x18, 0x04, 0x00, 0x01, 0x03,
        0x0e, 0x3e, 0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x10, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0xf6, 0xf3, 0x31, 0xfc, 0xff, 0xff, 0x3f,
        0x9f, 0x5f, 0x5f, 0x5f, 0xcf, 0xcf, 0xcf, 0xcb, 0xc9, 0x8c, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xe0, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0xf0, 0xe0, 0x60, 0x60, 0xc0, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x40, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x10, 0xf0, 0xf0, 0xf0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00, 0x03, 0xcf, 0xff, 0x0c,
        0x02, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xf9, 0xff, 0xff, 0xff, 0xff, 0x1c, 0x00, 0x00, 0x00, 0x00,
        0x03, 0xfe, 0xf8, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x3f, 0x7f, 0xff, 0xff,
        0xfc, 0x80, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0xff, 0xff, 0x20, 0x60, 0xd9, 0x9f, 0x0f, 0x00,
        0x01, 0xff, 0xff, 0x23, 0x21, 0x21, 0x73, 0x00, 0xff, 0xff, 0x03, 0x22, 0x1e, 0xfc, 0xf8, 0x41,
        0xff, 0xff, 0xe3, 0xb2, 0x3e, 0x1c, 0x00, 0xe0, 0xfe, 0x7f, 0x43, 0x4f, 0x7d, 0xf0, 0x80, 0x70,
        0xfc, 0x9e, 0x22, 0x03, 0x43, 0x43, 0xc6, 0xcc, 0x80, 0x78, 0xfc, 0x06, 0x23, 0x22, 0x06, 0x9c,
        0xf8, 0x40, 0x20, 0xff, 0xff, 0xff, 0x07, 0x1f, 0x7c, 0xf8, 0xe0, 0xff, 0xff, 0xff, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf1, 0xf9, 0xfd, 0xff, 0xfe,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x97, 0x87, 0xc1, 0xe3, 0xf0, 0x78, 0x7e, 0x7f, 0x38,
        0x3e, 0x3f, 0x9f, 0x6f, 0x3f, 0x1f, 0x07, 0x00, 0x03, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x03,
        0x0f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0e, 0x0f, 0x0f, 0x08, 0x00, 0x01, 0x03, 0x0f, 0x1e,
        0x3c, 0x77, 0x67, 0x44, 0x04, 0x04, 0x04, 0x02, 0x07, 0x07, 0x06, 0x06, 0x03, 0x03, 0x01, 0x04,
        0x07, 0x07, 0x00, 0x03, 0x07, 0x04, 0x06, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x06,
        0x05, 0x03, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x00, 0x00, 0x03, 0x07, 0x06, 0x06, 0x06, 0x07,
        0x01, 0x00, 0x04, 0x07, 0x07, 0x07, 0x04, 0x00, 0x00, 0x01, 0x03, 0x0f, 0x3f, 0xff, 0x00, 0x00
        }
    };

    oled_write_raw_P(redragon[0], ANIM_SIZE);
}

void oled_task_user(void) {
    render_logo();
}
#endif
