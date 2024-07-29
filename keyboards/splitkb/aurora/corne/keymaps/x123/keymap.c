/*
Copyright 2022 x123 <@x123>
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
#include "keycodes.h"

#include "keycodes_layers.h"
#ifdef BIG_MEMORY
#include "snaptap.h"
#endif
#include "sm_td.h"
#include "oledstuff.h"
#include "global_variables.h"

void keyboard_pre_init_user(void)
{
    // Set our LED pin as output
    setPinOutput(24);
    // Turn the LED off
    // (Due to technical reasons, high is off and low is on)
    writePinHigh(24);
}

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI)
        SMTD_MT(CKC_S, KC_S, KC_LEFT_ALT)
        SMTD_MT(CKC_D, KC_D, KC_LEFT_CTRL)
        SMTD_MT(CKC_F, KC_F, KC_LSFT)
        SMTD_MT(CKC_SCLN, KC_SCLN, KC_LEFT_GUI)
        SMTD_MT(CKC_L, KC_L, KC_LEFT_ALT)
        SMTD_MT(CKC_K, KC_K, KC_LEFT_CTRL)
        SMTD_MT(CKC_J, KC_J, KC_LSFT)
        SMTD_LT(CKC_NUMS, KC_SPACE, _NUMS)
        SMTD_LT(CKC_SYMS, KC_SPACE, _SYMS)
    }
}

uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout) {
    switch (keycode) {
        case CKC_A:
            if (timeout == SMTD_TIMEOUT_RELEASE)
            {
                return 1;
            }
        case CKC_SCLN:
            if (timeout == SMTD_TIMEOUT_RELEASE)
            {
                return 1;
            }
    }

    if (timeout == SMTD_TIMEOUT_TAP)
    {
        return timeout_tap;
    }
    else if (timeout == SMTD_TIMEOUT_SEQUENCE)
    {
        return timeout_seq;
    }
    else if (timeout == SMTD_TIMEOUT_FOLLOWING_TAP)
    {
        return timeout_following;
    }
    else if (timeout == SMTD_TIMEOUT_RELEASE)
    {
        return timeout_release_key;
    }

    return get_smtd_timeout_default(timeout);
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable(); // enables RGB, without saving settings
  rgblight_sethsv(195, 66, 58); // sets the color to red without saving
  rgblight_mode(1);
#elif RGB_MATRIX_ENABLE
  rgb_matrix_enable();
  rgb_matrix_sethsv(195, 180, 90);
  rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
  rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
#endif

  set_single_persistent_default_layer(_DEFAULT);
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    led_t led_usb_state = host_keyboard_led_state();
    switch (get_highest_layer(layer_state)) 
    {
        case _NUMS:
            rgb_matrix_sethsv(118, 180, 90);
            break;
        case _SYMS:
            rgb_matrix_sethsv(50, 180, 90);
            break;
        case _DEFAULT:
            if (led_usb_state.caps_lock)
            {
                rgb_matrix_sethsv(255, 255, 90);
            }
            else
            {
                rgb_matrix_sethsv(195, 180, 90);
            }
            break;
        case _NAVI:
            rgb_matrix_sethsv(255, 180, 90);
            break;    
        default:
            break;
    }

    return true;
}
#endif /* RGB_MATRIX */

#ifdef OLED_ENABLE
bool oled_task_user(void)
{
    if (is_keyboard_master())
    {
        render_layer_state();
        render_space();
        render_tap();
        render_seq();
        render_following();
        render_release();
        render_space();
        render_turbo_threshold();
        render_snap();
    }
    else
    {
#ifdef BIG_MEMORY
        render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
        render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
#endif
        render_kb_LED_state();
        render_space();
#ifdef WPM_ENABLE
        render_wpm();
#endif /* WPM_ENABLE */
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!process_smtd(keycode, record))
    {
        return false;
    }

    if (get_highest_layer(layer_state | default_layer_state) == _GAMER && 
        !snap_tap_wrapper(keycode, record))
    {
        return false;
    }

    switch (keycode)
    {
        case CLEAR_SNAPS:
            clear_snap_tap_entries(&snap_tap_entries_head);
            break;
        case TURBO_MODIFIER:
            if (record->event.pressed)
            {
                turbo_modifier_active = true;
            }
            else
            {
                turbo_modifier_active = false;
            }
            break;
        case UP:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_UP);
                }
                else if (turbo_modifier_active)
                {
                    turbo_up = true;
                }
                else
                {
                    register_code(KC_UP);
                }
            }
            else
            {
                unregister_code(KC_UP);
                turbo_up = false;
            }
            break;
        case DOWN:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_DOWN);
                }
                else if (turbo_modifier_active)
                {
                    turbo_down = true;
                }
                else
                {
                    register_code(KC_DOWN);
                }
            }
            else
            {
                unregister_code(KC_DOWN);
                turbo_down = false;
            }
            break;
        case LEFT:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_LEFT);
                }
                else if (turbo_modifier_active)
                {
                    turbo_left = true;
                }
                else
                {
                    register_code(KC_LEFT);
                }
            }
            else
            {
                unregister_code(KC_LEFT);
                turbo_left = false;
            }
            break;
        case RIGHT:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_RIGHT);
                }
                else if (turbo_modifier_active)
                {
                    turbo_right = true;
                }
                else
                {
                    register_code(KC_RIGHT);
                }
            }
            else
            {
                unregister_code(KC_RIGHT);
                turbo_right = false;
            }
            break;
        case ENTER_CLOSE_TAB:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    register_code(KC_ENTER);
                    unregister_code(KC_LALT);
                    is_alt_tab_active = false;
                }
                else
                {
                    register_code(KC_ENTER);
                }
            }
            else
            {
                unregister_code(KC_ENTER);
            }
            break;
        case TAB_CLOSE:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_LEFT_CTRL);
                    tap_code(KC_W);
                    unregister_code(KC_LEFT_CTRL);
                }
                else
                {
                    register_code(KC_TAB);
                }
            }
            else
            {
                unregister_code(KC_TAB);
            }
            break;
        case TURBO_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((uint16_t)(turbo_threshold + 3) > turbo_threshold)
                {
                    turbo_threshold += 3;
                }
            }
            break;
        case TURBO_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((uint16_t)(turbo_threshold - 3) < turbo_threshold)
                {
                    turbo_threshold -= 3;
                }
                else
                {
                    turbo_threshold = 0;
                }
            }
            break;
        case ALT_TAB:
            if (record->event.pressed)
            {
                if (!is_alt_tab_active) 
                {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } 
            else 
            {
                unregister_code(KC_TAB);
            }
            break;
        case ALT_F4:
            if (record->event.pressed) 
            {
                register_code(KC_LALT);
                register_code(KC_F4);
                unregister_code(KC_F4);
                unregister_code(KC_LALT);
            }
            break;
        case TAP_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_tap + 5) > timeout_tap)
                {
                    timeout_tap += 5;
                }
            }
            break;
        case TAP_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_tap - 5) < timeout_tap)
                {
                    timeout_tap -= 5;
                }
                else
                {
                    timeout_tap = 0;
                }
            }
            break;
            case SEQ_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_seq + 5) > timeout_seq)
                {
                    timeout_seq += 5;
                }
            }
            break;
        case SEQ_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_seq - 5) < timeout_seq)
                {
                    timeout_seq -= 5;
                }
                else
                {
                    timeout_seq = 0;
                }
            }
            break;
        case FOLLOW_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_following + 5) > timeout_following)
                {
                    timeout_following += 5;
                }
            }
            break;
        case FOLLOW_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_following - 5) < timeout_following)
                {
                    timeout_following -= 5;
                }
                else
                {
                    timeout_following = 0;
                }
            }
            break;
        case RELEASE_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_release_key + 5) > timeout_release_key)
                {
                    timeout_release_key += 5;
                }
            }
            break;
        case RELEASE_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_release_key - 5) < timeout_release_key)
                {
                    timeout_release_key -= 5;
                }
                else
                {
                    timeout_release_key = 0;
                }
            }
            break;
    }

    if (record->event.pressed)
    {
        caps_timer = timer_read();
    }

    return true;
}

void leader_start_user(void)
{
    rgb_matrix_sethsv(62, 180, 90);
    layer_on(_NO_HOMEROW);
}

void leader_end_user(void)
{
    if (leader_sequence_two_keys(KC_A, KC_E))
    {
        register_code(KC_LALT);
        register_code(KC_LCTL);
        tap_code(KC_Z); /* æÆ */
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);

    }
    else if (leader_sequence_two_keys(KC_O, KC_E))
    {
        register_code(KC_LALT);
        register_code(KC_LCTL);
        tap_code(KC_L); /* øØ */
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);

    }
    else if (leader_sequence_two_keys(KC_A, KC_A))
    {
        register_code(KC_LALT);
        register_code(KC_LCTL);
        tap_code(KC_W); /* åÅ */
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);   

    }
    else if (leader_sequence_two_keys(KC_M, KC_U))
    {
        register_code(KC_LALT);
        register_code(KC_LCTL);
        tap_code(KC_M); /* µ */
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);

    }
    layer_off(_NO_HOMEROW);
}

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void matrix_scan_user(void) // The very important timer.
{
    if (is_alt_tab_active)
    {
        if (timer_elapsed(alt_tab_timer) > 1000)
        {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }

    if (turbo_up && timer_elapsed(turbo_timer) > turbo_threshold)
    {
        /* Get variable that can be altered by keypresses, and use that for delay, so that we can set it ourselves. */
        tap_code(KC_UP);
        turbo_timer = timer_read();
    }

    if (turbo_down && timer_elapsed(turbo_timer) > turbo_threshold)
    {
        /* Get variable that can be altered by keypresses, and use that for delay, so that we can set it ourselves. */
        tap_code(KC_DOWN);
        turbo_timer = timer_read();
    }

    if (turbo_right && timer_elapsed(turbo_timer) > turbo_threshold)
    {
        /* Get variable that can be altered by keypresses, and use that for delay, so that we can set it ourselves. */
        tap_code(KC_RIGHT);
        turbo_timer = timer_read();
    }

    if (turbo_left && timer_elapsed(turbo_timer) > turbo_threshold)
    {
        /* Get variable that can be altered by keypresses, and use that for delay, so that we can set it ourselves. */
        tap_code(KC_LEFT);
        turbo_timer = timer_read();
    }

    led_t led_usb_state = host_keyboard_led_state();

    if (led_usb_state.caps_lock && timer_elapsed(caps_timer) > 3000 )
    {
        tap_code(KC_CAPS);
    }
}
