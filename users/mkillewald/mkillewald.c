/* Copyright 2023 @ Mike Killewald (https://github.com/mkillewald)
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

#include "mkillewald.h"
#include "eeprom_user_config.h"
#include "rgb_matrix_user.h"
#include "layers.h"

static uint8_t win_mode;

__attribute__ ((weak))
bool dip_switch_update_keymap(uint8_t index, bool active) {
  return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    win_mode = (index == 0 && active ? true : false);
    return dip_switch_update_keymap(index, active);
}

uint8_t is_win_mode(void) { return win_mode; }

__attribute__ ((weak))
layer_state_t default_layer_state_set_keymap(layer_state_t state) {
  return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case MAC_BASE:
            set_mac_base_rgb();
            break;
        case WIN_BASE:
            set_win_base_rgb();
            break;
        default:
            break;
    }
    return default_layer_state_set_keymap(state);
}

void set_mac_base_rgb(void) {
    // load mac base settings
    rgb_matrix_enable_noeeprom();
    rgb_matrix_reload_from_eeprom();

    // check disable
    if (!user_config_get_enable_mac_base()) {
        rgb_matrix_disable_noeeprom();
    }
}

void set_win_base_rgb(void) {
    // load win base settings
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(user_config_get_mode_win_base());
    rgb_matrix_set_speed_noeeprom(user_config_get_spd_win_base());
    rgb_matrix_sethsv_noeeprom(user_config_get_hsv_win_base().h,
                               user_config_get_hsv_win_base().s,
                               user_config_get_hsv_win_base().v);

    // check disable
    if (!user_config_get_enable_win_base()) {
        rgb_matrix_disable_noeeprom();
    }
}

__attribute__ ((weak))
void matrix_init_keymap(void) {
  return;
}

void matrix_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init_user();
#endif

    matrix_init_keymap();
}

__attribute__ ((weak))
void keyboard_post_init_keymap(void) {
  return;
}

void keyboard_post_init_user(void) {
    user_config_read_eeprom();

#ifdef AUTOCORRECT_OFF_AT_STARTUP
    // toggle autocorrect off at startup
    if (autocorrect_is_enabled()) { autocorrect_toggle(); }
#endif

    keyboard_post_init_keymap();
}

void housekeeping_task_mkillewald(void) {
    switch(bootloader_state) {
        case BOOTLOADER_DO:
            // bootloader was pressed two frames ago. RGB should now be off,
            // so we can call the bootloader.
            reset_keyboard();
            break;
        case BOOTLOADER_WAIT:
            // bootloader was pressed on previous frame, we wait this frame and
            // set flag to do bootloader at end of next frame. For some reason, my
            // Q2 needed this extra wait frame.
            bootloader_state = BOOTLOADER_DO;
            break;
        case BOOTLOADER_PRESSED:
            // User pressed bootloader keycode and RGB was disabled earlier in this
            // frame. However RGB changes wont take place immediately, so we set a
            // flag here which will be caught at end of the next frame.
            bootloader_state = BOOTLOADER_WAIT;
            break;
        default:
            break;
    }
}

bool process_record_mkillewald(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_BOOT:
            // We want to turn off LEDs before calling bootloader, so here
            // we call rgb_matrix_disable_noeeprom() and set a flag because
            // the LEDs won't be updated until the next frame.
            if (record->event.pressed) {
                rgb_matrix_disable_noeeprom();
                bootloader_state = BOOTLOADER_PRESSED;
            }
            return false;  // Skip all further processing of this key
        case RGB_TOG:
            if (record->event.pressed) {
                rgb_matrix_toggle_noeeprom();
                if (win_mode) {
                    user_config_toggle_enable_win_base();
                } else {
                    user_config_toggle_enable_mac_base();
                }
            }
            return false;  // Skip all further processing of this key
        case RGB_MOD:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_step_noeeprom();
                    user_config_set_mode_win_base(rgb_matrix_get_mode());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case RGB_RMOD:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_step_reverse_noeeprom();
                    user_config_set_mode_win_base(rgb_matrix_get_mode());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case RGB_HUI:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_increase_hue_noeeprom();
                    user_config_set_hsv_win_base(rgb_matrix_get_hsv());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case RGB_HUD:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_decrease_hue_noeeprom();
                    user_config_set_hsv_win_base(rgb_matrix_get_hsv());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case RGB_SAI:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_increase_sat_noeeprom();
                    user_config_set_hsv_win_base(rgb_matrix_get_hsv());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case RGB_SAD:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_decrease_sat_noeeprom();
                    user_config_set_hsv_win_base(rgb_matrix_get_hsv());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case RGB_VAI:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_increase_val_noeeprom();
                    user_config_set_hsv_win_base(rgb_matrix_get_hsv());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case RGB_VAD:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_decrease_val_noeeprom();
                    user_config_set_hsv_win_base(rgb_matrix_get_hsv());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case RGB_SPI:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_increase_speed_noeeprom();
                    user_config_set_spd_win_base(rgb_matrix_get_speed());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case RGB_SPD:
            if (win_mode) {
                if (record->event.pressed) {
                    rgb_matrix_decrease_speed_noeeprom();
                    user_config_set_spd_win_base(rgb_matrix_get_speed());
                }
                return false;  // Skip all further processing of this key
            } else {
                return true; // Allow further processing of this key
            }
        case KC_LIGHT_TAB_TOGGLE:
            if (record->event.pressed) {
                user_config_toggle_caps_lock_light_tab();
            }
            return false;  // Skip all further processing of this key
        case KC_LIGHT_ALPHAS_TOGGLE:
            if (record->event.pressed) {
                user_config_toggle_caps_lock_light_alphas();
            }
            return false;  // Skip all further processing of this key
        case KC_FN_LAYER_TRANSPARENT_KEYS_TOGGLE:
            if (record->event.pressed) {
                user_config_toggle_fn_layer_transparent_keys_off();
            }
            return false;  // Skip all further processing of this key
        case KC_FN_LAYER_COLOR_TOGGLE:
            if (record->event.pressed) {
                user_config_toggle_fn_layer_color_enable();
            }
            return false;  // Skip all further processing of this key
        case KC_LOCK_BLANK_MAC:
            if (record->event.pressed) {
                send_string(SS_LCTL(SS_LGUI("q")) SS_DELAY(225) SS_TAP(X_ESC));
            }
            return false;  // Skip all further processing of this key
        default:
            return true;  // Process all other keycodes normally
    }
}