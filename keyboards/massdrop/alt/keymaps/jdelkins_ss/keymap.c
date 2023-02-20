/*
  Copyright 2020 Joel Elkins <joel@elkins.com>

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

#include "print.h"

// Idle handling

#define IDLE_TIMEOUT 360
uint16_t rgb_idle_seconds = 0;
uint16_t rgb_timer;
uint8_t save_layer;

#define NUMLOCK_ON (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))
#define MODS_SHIFT (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL (get_mods() & MOD_MASK_CTRL)

// Macro keycodes

enum alt_keycodes {
    KB_BOOT = SAFE_RANGE,
};

enum layers {
        _QWERTY,
        _ADJUST,
};

// Layers

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,    KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,    KC_RBRC, KC_BSLS, KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,    KC_ENT,           KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,             KC_UP,   KC_PGDN,
        KC_LCTL, KC_LALT, KC_LGUI,                       KC_SPC,                                  KC_RALT, MO(_ADJUST),KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_ADJUST] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_INS,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_CALC, KC_END,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,          KC_MPLY,
        _______, RGB_TOG, _______, _______, _______, KB_BOOT, _______, _______, _______, _______, _______, _______,          KC_VOLU, KC_MUTE,
        _______, _______, _______,                            _______,                            _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
    */
};

#ifdef _______
#undef _______
#endif

#define RGB_NULL 254, 254, 254
#define RGB_IS_NULL(rgb) ((rgb).r == 254 && (rgb).g == 254 && (rgb).b == 254)

#define DEFAULT_HSV 255, 255, 128
#define R(COL) { RGB_ ## COL }
#define _______ R(NULL)
#define xxxxxxx R(BLACK)

struct layer_rgb PROGMEM rgbs[] = {
    [_QWERTY] = LAYOUT_hsv(LED_FLAG_ALL, RGB_MATRIX_CYCLE_ALL, DEFAULT_HSV),
    [_ADJUST] = LAYOUT_rgb(LED_FLAG_NONE, RGB_MATRIX_SOLID_COLOR,
        R(GREEN),  R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),
        R(GREEN),  R(WHITE),  R(WHITE),  R(WHITE),  R(WHITE), R(WHITE), R(WHITE), R(WHITE), R(WHITE), R(WHITE), R(WHITE), R(WHITE), R(WHITE),  R(WHITE),  R(WHITE), R(WHITE),  R(GREEN),
        R(GREEN),  xxxxxxx,   R(BLUE),   R(YELLOW), R(BLUE),  R(GREEN), R(ORANGE),xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   R(GREEN),
                   xxxxxxx,   R(MAGENTA),R(YELLOW), R(MAGENTA),R(GREEN),R(ORANGE),xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,         xxxxxxx,       R(BLUE),
        R(GREEN),  xxxxxxx,   R(WHITE),  xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,         xxxxxxx,       R(YELLOW),R(ORANGE), R(GREEN),
        R(GREEN),  xxxxxxx,   xxxxxxx,   xxxxxxx,                                        xxxxxxx,                         xxxxxxx,  xxxxxxx,   R(RED),    R(YELLOW),R(RED),    R(GREEN),
        R(GREEN),  R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN)
    ),
    /*
    [X] = LAYOUT_rgb(
        _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,   _______,
        _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,   _______,
                   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,         _______,       _______,
        _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,         _______,       _______,  _______,   _______,
        _______,   _______,   _______,   _______,                                        _______,                         _______,  _______,   _______,   _______,  _______,   _______,
        _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
    ),
    */
};

#undef _______
#define _______ KC_TRANS

static void set_rgb_layer(int layer) {
    const struct layer_rgb *cur = &rgbs[layer];

    switch (cur->type) {
        case type_hsv:
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT ; i++) {
                if (!(g_led_config.flags[i] & cur->flags))
                    rgb_matrix_set_color(i, 0, 0, 0);
            }
            rgb_matrix_set_flags(cur->flags);
            if (cur->mode >= RGB_MATRIX_EFFECT_MAX)
                rgb_matrix_mode_noeeprom(rgbs[cur->mode - RGB_MATRIX_EFFECT_MAX].mode);
            else
                rgb_matrix_mode_noeeprom(cur->mode);
            rgb_matrix_sethsv_noeeprom(cur->hsv.h, cur->hsv.s, cur->hsv.v);
            break;
        case type_rgb:
            rgb_matrix_set_flags(cur->flags);
            if (cur->mode >= RGB_MATRIX_EFFECT_MAX)
                rgb_matrix_mode_noeeprom(rgbs[cur->mode - RGB_MATRIX_EFFECT_MAX].mode);
            else
                rgb_matrix_mode_noeeprom(cur->mode);
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                const RGB *m = &cur->rgb[i];
                if (!RGB_IS_NULL(*m))
                    rgb_matrix_set_color(i, m->r, m->g, m->b);
            }
            break;
    }
}

// Runs just one time when the keyboard initializes.
void matrix_init_keymap(void) {
    set_rgb_layer(_QWERTY);
    // force numlock on upon startup
    if (!NUMLOCK_ON) {
        tap_code(KC_NUM_LOCK);
    }
};

// Runs constantly in the background, in a loop.
void matrix_scan_keymap(void) {
    if (rgb_matrix_get_flags() != LED_FLAG_NONE && timer_elapsed(rgb_timer) > 1000) {
        rgb_idle_seconds++;
        rgb_timer = timer_read();
    }
    if (rgb_idle_seconds > IDLE_TIMEOUT) {
        rgb_matrix_disable_noeeprom();
        rgb_idle_seconds = 0;
    }
};

layer_state_t layer_state_set_keymap(layer_state_t state) {
    set_rgb_layer(get_highest_layer(state));
    if (layer_state_cmp(state, _QWERTY))
        save_layer = _QWERTY;
    return state;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    static uint32_t boot_timer;
    struct layer_rgb *rgb_base_layer = &rgbs[save_layer];
    rgb_idle_seconds = 0;
    rgb_matrix_enable_noeeprom();

    switch (keycode) {
        case KB_BOOT:
            if (!get_mods()) {
                if (record->event.pressed) {
                    boot_timer = timer_read32();
                } else {
                    if (timer_elapsed32(boot_timer) >= 750) {
                        reset_keyboard();
                    }
                }
                return false;
            }
            break;
        case RGB_MOD:
            if (record->event.pressed) {
                if (++rgb_base_layer->mode >= RGB_MATRIX_EFFECT_MAX)
                    rgb_base_layer->mode = RGB_MATRIX_NONE;
                set_rgb_layer(save_layer);
            }
            return false;
        case RGB_RMOD:
            if (record->event.pressed) {
                if (--rgb_base_layer->mode <= RGB_MATRIX_NONE)
                    rgb_base_layer->mode = RGB_MATRIX_EFFECT_MAX - 1;
                set_rgb_layer(save_layer);
            }
            return false;
        case RGB_HUI:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.h > 235)
                    rgb_base_layer->hsv.h = 255;
                else
                    rgb_base_layer->hsv.h += 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_HUD:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.h < 20)
                    rgb_base_layer->hsv.h = 0;
                else
                    rgb_base_layer->hsv.h -= 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_SAI:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.s > 235)
                    rgb_base_layer->hsv.s = 255;
                else
                    rgb_base_layer->hsv.s += 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_SAD:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.s < 20)
                    rgb_base_layer->hsv.s = 0;
                else
                    rgb_base_layer->hsv.s -= 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_VAI:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.v > 235)
                    rgb_base_layer->hsv.v = 255;
                else
                    rgb_base_layer->hsv.v += 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_VAD:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.v < 20)
                    rgb_base_layer->hsv.v = 0;
                else
                    rgb_base_layer->hsv.v -= 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_base_layer->flags) {
                    case LED_FLAG_ALL:
                        rgb_base_layer->flags = LED_FLAG_KEYLIGHT;
                        break;
                    case LED_FLAG_KEYLIGHT:
                        rgb_base_layer->flags = LED_FLAG_UNDERGLOW;
                        break;
                    case LED_FLAG_UNDERGLOW:
                        rgb_base_layer->flags = LED_FLAG_NONE;
                        break;
                    default:
                        rgb_base_layer->flags = LED_FLAG_ALL;
                        break;
                }
            }
            set_rgb_layer(save_layer);
            return false;
        default:
            return true; //Process all other keycodes normally
    }
    return true;
}
