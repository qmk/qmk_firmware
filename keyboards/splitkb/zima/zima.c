/* Copyright 2019 Thomas Baart
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
#include "zima.h"
#include <stdio.h>

#ifdef HAPTIC_ENABLE
#    include "haptic.h"
extern haptic_config_t haptic_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static bool is_asleep = false;
static uint32_t oled_timer;

void suspend_power_down_kb(void) {
    is_asleep = true;
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    is_asleep = false;
    suspend_wakeup_init_user();
}

__attribute__((weak)) oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

__attribute__((weak)) void oled_task_user(void) {
    if (is_asleep) {
        oled_off();
        return;
    }

    if (timer_elapsed32(oled_timer) < 30000) {
        oled_on();
        oled_scroll_off();
        oled_write_P(PSTR("SplitKB's Zima"), false);
        char layer[2] = {0};
        snprintf(layer, sizeof(layer), "%d", get_highest_layer(layer_state));
        oled_write_P(PSTR("   L:"), false);
        oled_write_ln(layer, false);
        oled_write_ln_P(PSTR("--------------"), false);
        if (rgblight_is_enabled()) {
            oled_write_P(PSTR("HSV: "), false);
            char rgbs[14];
            snprintf(rgbs, sizeof(rgbs), "%3d, %3d, %3d", rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
            oled_write_ln(rgbs, false);
        } else {
            oled_write_ln_P(PSTR("RGB LIGHT DISABLED"), false);
        }
#    ifdef AUDIO_ENABLE
        oled_write_P(PSTR("Audio:"), false);
        is_audio_on() ? oled_write_P(PSTR(" on"), false) : oled_write_P(PSTR("off"), false);
#        ifdef AUDIO_CLICKY
        oled_write_P(PSTR(" Clicky:"), false);
        (is_clicky_on() && is_audio_on()) ? oled_write_P(PSTR(" on"), false) : oled_write_P(PSTR("off"), false);
#        endif
#    endif
    } else {
        if (timer_elapsed32(oled_timer) < 120000) {
            oled_on();
            // clang-format off
            static const char PROGMEM qmk_logo[] = {
                0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
                0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
                0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
            // clang-format on
            oled_write_ln_P(qmk_logo, false);
            oled_scroll_right();
        } else {
            oled_off();
        }
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    oled_timer = timer_read32();

    return process_record_user(keycode, record);
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
#    ifdef OLED_DRIVER_ENABLE
    oled_timer = timer_read32();
#    endif
#    if defined(AUDIO_ENABLE) && defined(AUDIO_CLICKY)
    if (is_audio_on() && is_clicky_on()) clicky_play();
#    endif
#    ifdef HAPTIC_ENABLE
    if (haptic_config.enable) haptic_play();
#    endif
    if (!encoder_update_user(index, clockwise)) return false;
    if (clockwise) {
        tap_code16(KC_VOLU);
    } else {
        tap_code16(KC_VOLD);
    }
    return true;
}
#endif
