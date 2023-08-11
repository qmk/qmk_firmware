/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <gourdo1@outlook.com>
   
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

#include "gourdo1.h"

#ifdef ENCODER_ENABLE
    #ifndef DYNAMIC_KEYMAP_LAYER_COUNT
        #define DYNAMIC_KEYMAP_LAYER_COUNT 4  //default in case this is not already defined elsewhere
    #endif
    #ifndef ENCODER_DEFAULTACTIONS_INDEX
        #define ENCODER_DEFAULTACTIONS_INDEX 0  // can select encoder index if there are multiple encoders
    #endif

    static uint16_t key_timer;

    void encoder_action_volume(bool clockwise) {
        if (clockwise) {
            tap_code(KC_VOLU);
            if (timer_elapsed(key_timer) < 50) {
              tap_code(KC_VOLU); // if less than 50ms have passed, hit vol up again.
              key_timer = timer_read();
            } else {
              key_timer = timer_read();
              // do nothing if 50ms or more have passed
            }
        }
        else {
            tap_code(KC_VOLD);
            if (timer_elapsed(key_timer) < 100) {
              tap_code(KC_VOLD); // if less than 100ms have passed, hit vol down twice.
              tap_code(KC_VOLD);
              key_timer = timer_read();
            } else {
              key_timer = timer_read();
              // do nothing if 100ms or more have passed
            }
        }
    }
	
    void encoder_action_mediatrack(bool clockwise) {
        if (clockwise)
            tap_code(KC_MEDIA_NEXT_TRACK);
        else
            tap_code(KC_MEDIA_PREV_TRACK);
    }

    void encoder_action_navword(bool clockwise) {
        if (clockwise)
            tap_code16(LCTL(KC_RGHT));
        else
            tap_code16(LCTL(KC_LEFT));
    }

    void encoder_action_navpage(bool clockwise) {
        if (clockwise)
            tap_code16(KC_PGUP);
        else
            tap_code16(KC_PGDN);
    }

    // LAYER HANDLING
    uint8_t selected_layer = 0;

    uint8_t get_selected_layer(void) {
        return selected_layer;
    }

    void encoder_action_layerchange(bool clockwise) {
        if (clockwise) {
            if(selected_layer  < (DYNAMIC_KEYMAP_LAYER_COUNT - 1)) {
                selected_layer ++;
                layer_move(selected_layer);
            }
        } else {
            if (selected_layer  > 0) {
                selected_layer --;
                layer_move(selected_layer);
            }
        }
    }

    #ifdef RGB_MATRIX_ENABLE
        void encoder_action_rgb_speed(bool clockwise) {
            if (clockwise)
                rgb_matrix_increase_speed_noeeprom();
            else
                rgb_matrix_decrease_speed_noeeprom();
        }
        void encoder_action_rgb_hue(bool clockwise) {
            if (clockwise)
                rgb_matrix_increase_hue_noeeprom();
            else
                rgb_matrix_decrease_hue_noeeprom();
        }
        void encoder_action_rgb_saturation(bool clockwise) {
            if (clockwise)
                rgb_matrix_increase_sat_noeeprom();
            else
                rgb_matrix_decrease_sat_noeeprom();
        }
        void encoder_action_rgb_brightness(bool clockwise) {
            if (clockwise)
                rgb_matrix_increase_val_noeeprom();
            else
                rgb_matrix_decrease_val_noeeprom();
        }
        void encoder_action_rgb_mode(bool clockwise) {
            if (clockwise)
                rgb_matrix_step_noeeprom();
            else
                rgb_matrix_step_reverse_noeeprom();
        }
    #elif defined(RGBLIGHT_ENABLE)
        void encoder_action_rgb_speed(bool clockwise) {
            if (clockwise)
                rgblight_increase_speed_noeeprom();
            else
                rgblight_decrease_speed_noeeprom();
        }
        void encoder_action_rgb_hue(bool clockwise) {
            if (clockwise)
                rgblight_increase_hue_noeeprom();
            else
                rgblight_decrease_hue_noeeprom();
        }
        void encoder_action_rgb_saturation(bool clockwise) {
            if (clockwise)
                rgblight_increase_sat_noeeprom();
            else
                rgblight_decrease_sat_noeeprom();
        }
        void encoder_action_rgb_brightness(bool clockwise) {
            if (clockwise)
                rgblight_increase_val_noeeprom();
            else
                rgblight_decrease_val_noeeprom();
        }
        void encoder_action_rgb_mode(bool clockwise) {
            if (clockwise)
                rgblight_step_noeeprom();
            else
                rgblight_step_reverse_noeeprom();
        }
    #endif // RGB_MATRIX_ENABLE || RGBLIGHT_ENABLE

    #ifdef ALTTAB_SCROLL_ENABLE
        bool is_tab_scrolling = false;
        bool is_alt_tab_active = false;
        uint16_t alt_tab_timer = 0;


        void encoder_toggle_alttabscroll(void) {
            is_tab_scrolling = !is_tab_scrolling;
        }

        void encoder_action_alttabscroll(bool clockwise) {
            if (clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_mods(MOD_RALT);
                }
                tap_code16(KC_TAB);
            }
            else {
                tap_code16(S(KC_TAB));
            }
            alt_tab_timer = timer_read();
        }

        void encoder_tick_alttabscroll(void) {
            if (is_alt_tab_active) {
                if (timer_elapsed(alt_tab_timer) > 600) {
                    unregister_mods(MOD_RALT);
                    is_alt_tab_active = false;
                }
            }
        }
    #endif // ALTTAB_SCROLL_ENABLE
#endif // ENCODER_ENABLE

#if defined(ENCODER_ENABLE) && defined(ENCODER_DEFAULTACTIONS_ENABLE)       // Encoder Functionality

    __attribute__((weak)) bool encoder_update_keymap(uint8_t index, bool clockwise) { return true; }

    bool encoder_update_user(uint8_t index, bool clockwise) {
        if (!encoder_update_keymap(index, clockwise)) { return false; }
        if (index != ENCODER_DEFAULTACTIONS_INDEX) {return true;}  // exit if the index doesn't match
        uint8_t mods_state = get_mods();
        if (mods_state & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, encoder changes layers
            encoder_action_layerchange(clockwise);
        } else if (mods_state & MOD_BIT(KC_RSFT) ) { // If you are holding R shift, Page up/dn
            unregister_mods(MOD_BIT(KC_RSFT));
            encoder_action_navpage(clockwise);
            register_mods(MOD_BIT(KC_RSFT));
        } else if (mods_state & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate next/prev word
            encoder_action_navword(clockwise);
        } else if (mods_state & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next/prev track
            encoder_action_mediatrack(clockwise);
        } else  {
            switch(get_highest_layer(layer_state)) {
            case _FN1:
                #ifdef IDLE_TIMEOUT_ENABLE
                    timeout_update_threshold(clockwise);
                #endif
                break;
            default:
                #ifdef ALTTAB_SCROLL_ENABLE
                    if (is_tab_scrolling)
                        encoder_action_alttabscroll(clockwise);
                    else
                        encoder_action_volume(clockwise);       // Otherwise it just changes volume
                #else
                    encoder_action_volume(clockwise);       // Otherwise it just changes volume
                #endif // ALTTAB_SCROLL_ENABLE
                break;
            }
        }
        return false;
    }
#endif // ENCODER_ENABLE


