/*
Copyright 2020 Jacob Jerrell <jacob.jerrell@gmail.com> @JacobJerrell

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

#include "bocaj.h"

#ifdef BACKLIGHT_ENABLE
enum planck_keycodes {
    BACKLIT = NEW_SAFE_RANGE,
    TH_LVL,
};

#else
#    define BACKLIT OSM(MOD_LSFT)
enum planck_keycodes {
    TH_LVL = NEW_SAFE_RANGE,
};
#endif

/*
 * Tap/Hold Wrapper
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |Shift | Cmd  | Alt  |      |      | Alt  | Cmd  |Shift |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl |      |      |      |      |      |      |      |      | Ctrl |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower |             |Raise |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
#define LAYOUT_ortho_4x12_bocaj(...) WRAPPER_planck_bocaj(__VA_ARGS__)

/*
 * Base Alphanumeric Wrapper + Tap/Hold Wrapper
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |      |      |      |      |      |      |      |      |      |      |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Tab |      |      |      |      | HYPR | MEH  |      |      |      |      |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |      |      |      | TTMOD|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | MOMOD| Lead |  Up  | Left |BkSpc |    Space    |Enter |Right | Down | XXX  | XXX  |
 * `-----------------------------------------------------------------------------------'
 */
#define LAYOUT_ortho_4x12_bocaj_base(...) WRAPPER_planck_bocaj_base(__VA_ARGS__)
#define LAYOUT_ortho_4x12_bocaj_base_WIN(...) WRAPPER_planck_bocaj_base_WIN(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_WORKMAN] = LAYOUT_ortho_4x12_bocaj_base(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),
  [_WWORKMAN] = LAYOUT_ortho_4x12_bocaj_base_WIN(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),

  [_QWERTY] = LAYOUT_ortho_4x12_bocaj_base(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),
  [_WQWERTY] = LAYOUT_ortho_4x12_bocaj_base_WIN(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

  [_LOWER] = LAYOUT_ortho_4x12_bocaj(
    ___________________LOWER_L1_EXT____________________, ___________________LOWER_R1_EXT____________________,
    ___________________LOWER_L2_EXT____________________, ___________________LOWER_R2_EXT____________________,
    ___________________LOWER_L3_EXT____________________, ___________________LOWER_R3_EXT____________________,
    _______, _______, _______, _______, _______, _______,  _______, KC_0,  KC_DOT,  KC_COMM, _______, _______
  ),

  [_RAISE] = LAYOUT_ortho_4x12_bocaj(
    KC_TILD, _________________RAISE_L1__________________, _________________RAISE_R1__________________, KC_EQUAL,
    KC_F11,  _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_F12,
    _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ADJUST] = WRAPPER_ortho_4x12(
    KC_MAKE, _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, KC_RST,
    VRSN,    _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, EEP_RST,
    TH_LVL,  _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, RGB_IDL,
    HPT_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )

};
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef BACKLIGHT_ENABLE
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#    ifdef BACKLIGHT_ENABLE
                backlight_step();
#    endif
            } else {
                unregister_code(KC_RSFT);
            }
            break;
#endif
#ifdef KEYBOARD_planck_ez
        case TH_LVL:
            if (record->event.pressed) {
                keyboard_config.led_level++;
                if (keyboard_config.led_level > 4) {
                    keyboard_config.led_level = 0;
                }
                planck_ez_right_led_level((uint8_t)keyboard_config.led_level * 255 / 4);
                planck_ez_left_led_level((uint8_t)keyboard_config.led_level * 255 / 4);
                eeconfig_update_kb(keyboard_config.raw);
                layer_state_set_kb(layer_state);
            }
            break;
#endif
    }
    return true;
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        default:
            return true;
    }
}

#ifdef RGB_MATRIX_ENABLE

// clang-format off
void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}
// clang-format on

void rgb_matrix_indicators_user(void) {
    uint8_t this_mod = get_mods();
    uint8_t this_led = host_keyboard_leds();
    uint8_t this_osm = get_oneshot_mods();
    bool    is_ez;
#    ifdef KEYBOARD_planck_ez
    is_ez = true;
#    endif

    if (g_suspend_state || !rgb_matrix_config.enable) return;

#    if defined(RGBLIGHT_ENABLE)
    if (!userspace_config.rgb_layer_change)
#    else
    if (userspace_config.rgb_layer_change)
#    endif
    {
        switch (get_highest_layer(layer_state)) {
            case _MOD:
                rgb_matrix_layer_helper(HSV_ORANGE, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            case _RAISE:
                rgb_matrix_layer_helper(HSV_BLUE, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            default: {
                bool mods_enabled = false;
                switch (get_highest_layer(default_layer_state)) {
                    case _QWERTY:
                        rgb_matrix_layer_helper(HSV_CYAN, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _WQWERTY:
                        rgb_matrix_layer_helper(HSV_BLUE, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _WORKMAN:
                        rgb_matrix_layer_helper(HSV_SPRINGGREEN, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _WWORKMAN:
                        rgb_matrix_layer_helper(HSV_GREEN, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                }
                break;
            }
        }
    }

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            rgb_matrix_set_color(is_ez ? 41 : 42, 0x00, 0xFF, 0xFF);
            break;
        case _WORKMAN:
            rgb_matrix_set_color(is_ez ? 41 : 42, 0xD9, 0xA5, 0x21);
            break;
    }

    if ((this_mod | this_osm) & MODS_SHIFT_MASK || this_led & (1 << USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color_row(0, 0x00, 0xFF, 0x00);
    }
    if ((this_mod | this_osm) & MODS_CTRL_MASK && (this_mod | this_osm) & MODS_GUI_MASK) {
        rgb_matrix_set_color_row(1, 0xFF, 0xD9, 0xFF);
    } else if ((this_mod | this_osm) & MODS_CTRL_MASK) {
        rgb_matrix_set_color_row(1, 0xFF, 0x00, 0x00);
    } else if ((this_mod | this_osm) & MODS_GUI_MASK) {
        rgb_matrix_set_color_row(1, 0xFF, 0xD9, 0x00);
    }
    if ((this_mod | this_osm) & MODS_ALT_MASK) {
        rgb_matrix_set_color_row(2, 0x00, 0x00, 0xFF);
    }
}
#endif  // RGB_MATRIX_INIT

void matrix_init_keymap(void) {}

#ifdef ENCODER_ENABLE
void encoder_update(bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _RAISE:
            clockwise ? tap_code(KC_VOLD) : tap_code(KC_VOLU);
            break;
        case _LOWER:
#    ifdef RGB_MATRIX_ENABLE
            clockwise ? rgb_matrix_step() : rgb_matrix_step_reverse();
#    else
            clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
#    endif
            break;
        case _ADJUST:
#    ifdef AUDIO_CLICKY
            clockwise ? clicky_freq_up() : clicky_freq_down();
#    endif
            break;
        default:
            clockwise ? tap_code(KC_DOWN) : tap_code(KC_UP);
    }
#    ifdef AUDIO_CLICKY
    clicky_play();
#    endif
}
#endif  // ENCODER_ENABLE

#ifdef KEYBOARD_planck_ez
layer_state_t layer_state_set_keymap(layer_state_t state) {
    planck_ez_left_led_off();
    planck_ez_right_led_off();
    switch (get_highest_layer(state)) {
        case _LOWER:
            planck_ez_left_led_on();
            break;
        case _RAISE:
            planck_ez_right_led_on();
            break;
        case _ADJUST:
            planck_ez_right_led_on();
            planck_ez_left_led_on();
            break;
        default:
            break;
    }
    return state;
}
#endif
