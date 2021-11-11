/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Cory Ginsberg (@coryginsberg)

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
#include "rgb_matrix_map.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Alt_L    Win_L                               SPACE                               Ct_R        Alt_R   FN     Left     Down     Right

    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    [0] = LAYOUT( // Windows
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT( // Mac
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  TD(1),            KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        TT(3),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        TD(0),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RALT, MO(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [2] = LAYOUT( // Fn
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS,           _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,             _______,
        _______, RGB_SAI, RGB_VAD, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,          _______,           _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD,  RGB_TOG,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),
    [3] = LAYOUT( // Num Pad
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                      KC_MUTE,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______,                      KC_DEL,
        _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_PDOT, _______, _______, _______,                      KC_PGUP,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_P1,   KC_P2,   KC_P3,   XXXXXXX, KC_PAST,          KC_PENT,                      KC_PGDN,
        _______,          XXXXXXX, KC_DEL,  KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX, KC_P0,   KC_P0,   KC_PDOT, KC_PSLS,          _______,       RCTL(KC_PGUP), KC_END,
        _______, _______, _______,                            KC_BSPC,                            _______, _______, _______, RCTL(KC_LEFT), RCTL(KC_PGDN), RCTL(KC_RIGHT)
    ),
    [4] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_P, _______, _______, RESET,            RGB_MODE_FORWARD,
        _______, _______, RGB_SAI, _______, _______, _______, RGB_HUI, _______, _______, _______, _______, _______,          _______,          RGB_MODE_REVERSE,
        _______,          _______, _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______,          _______, _______, RGB_TOG,
        _______, _______, _______,                            _______,                            _______, _______, _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK
    ),
};

void dance_media(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_MPLY);
    } else if (state->count == 2) {
        tap_code(KC_MNXT);
    } else if (state->count == 3) {
        tap_code(KC_MPRV);
    } else {
        reset_tap_dance(state);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for shift, twice for Caps Lock
    [0] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [1] = ACTION_TAP_DANCE_FN(dance_media)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}

// Capslock, Scroll lock and Numlock indicator on Left side lights.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
        rgb_matrix_set_color(LED_L1, RGB_GREEN);
        rgb_matrix_set_color(LED_L2, RGB_GREEN);
    }
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {
        rgb_matrix_set_color(LED_L3, RGB_MAGENTA);
        rgb_matrix_set_color(LED_L4, RGB_MAGENTA);
    }
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(LED_L5, RGB_RED);
        rgb_matrix_set_color(LED_L6, RGB_RED);
        rgb_matrix_set_color(LED_L7, RGB_RED);
        rgb_matrix_set_color(LED_CAPS, RGB_RED);
    }
    if (keymap_config.no_gui) {
        rgb_matrix_set_color(LED_LWIN, RGB_RED);  //light up Win key when disabled
    }
    switch(get_highest_layer(layer_state)){  // special handling per layer
        case 2:  // on Fn layer select what the encoder does when pressed
            for (uint8_t i=0; i<ARRAYSIZE(LED_SIDE_LEFT); i++) {
                rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_OFF);
                rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_OFF);
            }
            for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_FUNCROW); i++) {
                rgb_matrix_set_color(LED_LIST_FUNCROW[i], RGB_OFF);
            }
            rgb_matrix_set_color(LED_FN, RGB_GREEN); //FN key
            rgb_matrix_set_color(LED_END, RGB_RED);
            rgb_matrix_set_color(LED_1, RGB_RED);
            rgb_matrix_set_color(LED_INS, RGB_YELLOW);
            rgb_matrix_set_color(LED_BSLS, RGB_RED);
            for (uint8_t i=0; i < ARRAYSIZE(LED_LIST_ARROWS); i++) {
                rgb_matrix_set_color(LED_LIST_ARROWS[i], RGB_BLUE);
            }
            for (uint8_t i=0; i< ARRAYSIZE(LED_LIST_WASD); i++) {
                rgb_matrix_set_color(LED_LIST_WASD[i], RGB_PURPLE);
            }
            break;
        case 3:  // on Fn layer select what the encoder does when pressed
            rgb_matrix_set_color_all(RGB_OFF);
            for (uint8_t i=0; i < ARRAYSIZE(LED_LIST_NUMPAD); i++) {
                rgb_matrix_set_color(LED_LIST_NUMPAD[i], RGB_GREEN);
                rgb_matrix_set_color(LED_LIST_NUM_OTHERS[i], RGB_YELLOW);
            }
            for (uint8_t i=0; i < ARRAYSIZE(LED_LIST_NUMPAD_ACTIONS); i++) {
                rgb_matrix_set_color(LED_LIST_NUMPAD_ACTIONS[i], RGB_BLUE);
            }
            for (uint8_t i=0; i < ARRAYSIZE(LED_SIDE_LEFT); i++) {
                rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_WHITE);
                rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_WHITE);
            }
            break;
    }
}

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

void keyboard_post_init_keymap(void) {
    // keyboard_post_init_user() moved to userspace
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_color_all(RGB_WHITE); // Default startup colour
}
