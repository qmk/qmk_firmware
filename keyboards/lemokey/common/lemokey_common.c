/* Copyright 2022~2024 @ Keychron (https://www.keychron.com)
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
#include "lemokey_common.h"

#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#    include "lemokey_common.h"
#endif

#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#endif

static uint8_t mac_keycode[4] = {KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD};

static key_combination_t key_comb_list[3] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}},
    {2, {KC_LWIN, KC_L}},
};

#if defined(WIN_LOCK_HOLD_TIME)
static uint32_t winlock_timer = 0;
#endif

void gui_toggle(void) {
    keymap_config.no_gui = !keymap_config.no_gui;
    eeconfig_update_keymap(keymap_config.raw);
    led_update_kb(host_keyboard_led_state());
}

bool process_record_lemokey_common(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TASK_VIEW:
        case KC_FILE_EXPLORER:
        case KC_LOCK_SCREEN:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false; // Skip all further processing of this key

        case KC_MCTRL:
            if (record->event.pressed) {
                register_code(KC_MISSION_CONTROL);
            } else {
                unregister_code(KC_MISSION_CONTROL);
            }
            return false; // Skip all further processing of this key

        case KC_LNPAD:
            if (record->event.pressed) {
                register_code(KC_LAUNCHPAD);
            } else {
                unregister_code(KC_LAUNCHPAD);
            }
            return false; // Skip all further processing of this key

        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false; // Skip all further processing of this key

#if defined(WIN_LOCK_HOLD_TIME) || defined(WIN_LOCK_LED_PIN) || defined(WINLOCK_LED_LIST)
        case GU_TOGG:
#    if defined(WIN_LOCK_HOLD_TIME)
            if (record->event.pressed) {
                winlock_timer = timer_read32();
            } else {
                winlock_timer = 0;
            }
#    else
            if (record->event.pressed) gui_toggle();
#    endif
            return false;
#endif
        default:
            return true; // Process all other keycodes normally
    }
}

void lemokey_common_task(void) {
#if defined(WIN_LOCK_HOLD_TIME)
    if (winlock_timer) {
        if (keymap_config.no_gui) {
            winlock_timer = 0;
            gui_toggle();
        } else if (timer_elapsed32(winlock_timer) > WIN_LOCK_HOLD_TIME) {
            winlock_timer = 0;
            gui_toggle();
        }
    }
#endif
}

#ifdef ENCODER_ENABLE
static void encoder_pad_cb(void *param) {
    uint8_t index = (uint32_t)param;
    encoder_inerrupt_read(index);
}

void encoder_cb_init(void) {
    pin_t encoders_pad_a[] = ENCODERS_PAD_A;
    pin_t encoders_pad_b[] = ENCODERS_PAD_B;
    for (uint32_t i=0; i<NUM_ENCODERS; i++)
    {
        palEnableLineEvent(encoders_pad_a[i], PAL_EVENT_MODE_BOTH_EDGES);
        palEnableLineEvent(encoders_pad_b[i], PAL_EVENT_MODE_BOTH_EDGES);
        palSetLineCallback(encoders_pad_a[i], encoder_pad_cb, (void*)i);
        palSetLineCallback(encoders_pad_b[i], encoder_pad_cb, (void*)i);
    }
}
#endif

__attribute__((weak)) void suspend_power_down_lemokey(void) {}
__attribute__((weak)) void suspend_wakeup_init_lemokey(void) {}

void suspend_power_down_kb(void) {
#ifdef WIN_LOCK_LED_PIN
    writePin(WIN_LOCK_LED_PIN, !WIN_LOCK_LED_ON_LEVEL);
#endif
    suspend_power_down_lemokey();
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
#ifdef WIN_LOCK_LED_PIN
    if (keymap_config.no_gui) writePin(WIN_LOCK_LED_PIN, !WIN_LOCK_LED_ON_LEVEL);
#endif
    suspend_wakeup_init_lemokey();
    suspend_wakeup_init_user();
}
