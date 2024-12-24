/* Copyright 2020 yushakobo
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

#include "helix.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case EISU:
            if (record->event.pressed) {
                if (is_mac_mode()) {
                    register_code(KC_LNG2);
                } else {
                    tap_code16(LALT(KC_GRAVE));
                }
            } else {
                unregister_code(KC_LNG2);
            }
            return false;
            break;
        case KANA:
            if (record->event.pressed) {
                if (is_mac_mode()) {
                    register_code(KC_LNG1);
                } else {
                    tap_code16(LALT(KC_GRAVE));
                }
            } else {
                unregister_code(KC_LNG1);
            }
            return false;
            break;
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
#endif
            break;
    }
    return true;
}

bool is_mac_mode(void) {
    return keymap_config.swap_lalt_lgui == false;
}

void set_mac_mode(bool macmode) {
    keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = !macmode;
    eeconfig_update_keymap(keymap_config.raw);
}

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    set_mac_mode(!active);
    return true;
}
#endif

#ifdef OLED_ENABLE
void render_status(void) {
    static const char os_logo[][6] PROGMEM = {{0x95, 0x96, '\n', 0x97, 0x98, 0}, {0xb5, 0xb6, '\n', 0xb7, 0xb8, 0}};
    oled_write_P(os_logo[is_mac_mode()], false);

    oled_write_P(PSTR(" "), false);

    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("N/A"), false);
    }

    oled_write_P(PSTR("\n"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
}

static void render_logo(void) {
    static const char PROGMEM helix_logo[] = {
        // clang-format off
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4,
        0x0
        // clang-format on
    };
    oled_write_P(helix_logo, false);
}

static void render_rgbled_status(void) {
    // " LED %d:%d,%d,%d"
    oled_write_P(PSTR(" LED"), false);
    oled_write(get_u8_str(rgblight_get_mode(), ' '), false);
    oled_write_char(':', false);
    oled_write(get_u8_str(rgblight_get_hue() / RGBLIGHT_HUE_STEP, ' '), false);
    oled_write_char(',', false);
    oled_write(get_u8_str(rgblight_get_sat() / RGBLIGHT_SAT_STEP, ' '), false);
    oled_write_char(',', false);
    oled_write(get_u8_str(rgblight_get_val() / RGBLIGHT_VAL_STEP, ' '), false);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_logo();
        render_rgbled_status();
    }
    return false;
}
#endif
