/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#ifdef RGBLIGHT_ENABLE

#    include "drashna.h"
#    include "rgb_stuff.h"
#    include "eeprom.h"

bool has_initialized;

void rgblight_sethsv_default_helper(uint8_t index) { rgblight_sethsv_at(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), index); }

#    ifdef RGBLIGHT_TWINKLE
static rgblight_fadeout lights[RGBLED_NUM];

/* Handler for fading/twinkling effect */
void scan_rgblight_fadeout(void) {  // Don't effing change this function .... rgblight_sethsv is supppppper intensive
    bool litup = false;

    for (uint8_t light_index = 0; light_index < RGBLED_NUM; ++light_index) {
        if (lights[light_index].enabled && timer_elapsed(lights[light_index].timer) > 10) {
            rgblight_fadeout *light = &lights[light_index];
            litup                   = true;

            if (light->life) {
                light->life -= 1;
                if (get_highest_layer(layer_state) == 0) {
                    sethsv(light->hue + rand() % 0xF, 255, light->life, (LED_TYPE *)&led[light_index]);
                }
                light->timer = timer_read();
            } else {
                if (light->enabled && get_highest_layer(layer_state) == 0) {
                    rgblight_sethsv_default_helper(light_index);
                }
                litup = light->enabled = false;
            }
        }
    }
    if (litup && get_highest_layer(layer_state) == 0) {
        rgblight_set();
    }
}

/* Triggers a LED to fade/twinkle.
 * This function handles the selection of the LED and prepres for it to be used.
 */
void start_rgb_light(void) {
    uint8_t indices[RGBLED_NUM];
    uint8_t indices_count  = 0;
    uint8_t min_life       = 0xFF;
    uint8_t min_life_index = -1;

    for (uint8_t index = 0; index < RGBLED_NUM; ++index) {
        if (lights[index].enabled) {
            if (min_life_index == -1 || lights[index].life < min_life) {
                min_life       = lights[index].life;
                min_life_index = index;
            }
            continue;
        }

        indices[indices_count] = index;
        ++indices_count;
    }

    uint8_t light_index;
    if (!indices_count) {
        light_index = min_life_index;
    } else {
        light_index = indices[rand() % indices_count];
    }

    rgblight_fadeout *light = &lights[light_index];
    light->enabled          = true;
    light->timer            = timer_read();
    light->life             = 0xC0 + rand() % 0x40;

    light->hue = rgblight_get_hue() + (rand() % 0xB4) - 0x54;

    rgblight_sethsv_at(light->hue, 255, light->life, light_index);
}
#    endif

bool process_record_user_rgb_light(uint16_t keycode, keyrecord_t *record) {
    uint16_t temp_keycode = keycode;
    // Filter out the actual keycode from MT and LT keys.
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        temp_keycode &= 0xFF;
    }

    switch (temp_keycode) {
#    ifdef RGBLIGHT_TWINKLE
        case KC_A ... KC_SLASH:
        case KC_F1 ... KC_F12:
        case KC_INSERT ... KC_UP:
        case KC_KP_SLASH ... KC_KP_DOT:
        case KC_F13 ... KC_F24:
        case KC_AUDIO_MUTE ... KC_MEDIA_REWIND:
            if (record->event.pressed) {
                start_rgb_light();
            }
            break;
#    endif  // RGBLIGHT_TWINKLE
    }
    return true;
}

#    if defined(RGBLIGHT_STARTUP_ANIMATION)
static bool     is_enabled;
static bool     is_rgblight_startup;
static uint8_t  old_hue;
static uint16_t rgblight_startup_loop_timer;
#    endif

void keyboard_post_init_rgb_light(void) {
#    if defined(RGBLIGHT_STARTUP_ANIMATION)
    is_enabled = rgblight_is_enabled();
    if (userspace_config.rgb_layer_change) {
        rgblight_enable_noeeprom();
    }
    if (rgblight_is_enabled()) {
        layer_state_set_rgb_light(layer_state);
        old_hue = rgblight_get_hue();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        is_rgblight_startup = true;
    }
#    endif
    layer_state_set_rgb_light(layer_state);
}

void matrix_scan_rgb_light(void) {
#    ifdef RGBLIGHT_TWINKLE
    scan_rgblight_fadeout();
#    endif  // RGBLIGHT_ENABLE

#    if defined(RGBLIGHT_STARTUP_ANIMATION)
    if (is_rgblight_startup && is_keyboard_master()) {
        if (timer_elapsed(rgblight_startup_loop_timer) > 10) {
            static uint8_t counter;
            counter++;
            rgblight_sethsv_noeeprom((counter + old_hue) % 255, 255, 255);
            rgblight_startup_loop_timer = timer_read();
            if (counter == 255) {
                is_rgblight_startup = false;
                if (!is_enabled) {
                    rgblight_disable_noeeprom();
                }
                if (userspace_config.rgb_layer_change) {
                    layer_state_set_rgb_light(layer_state);
                }
            }
        }
    }
#    endif
}

void rgblight_set_hsv_and_mode(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode) {
    rgblight_sethsv_noeeprom(hue, sat, val);
    // wait_us(175);  // Add a slight delay between color and mode to ensure it's processed correctly
    rgblight_mode_noeeprom(mode);
}

layer_state_t layer_state_set_rgb_light(layer_state_t state) {
#    ifdef RGBLIGHT_ENABLE
    if (userspace_config.rgb_layer_change) {
        uint8_t mode = layer_state_cmp(state, _MODS) ? RGBLIGHT_MODE_BREATHING : RGBLIGHT_MODE_STATIC_LIGHT;
        switch (get_highest_layer(state | default_layer_state)) {
            case _MACROS:
#        ifdef RGBLIGHT_EFFECT_TWINKLE
                rgblight_set_hsv_and_mode(HSV_CHARTREUSE, RGBLIGHT_MODE_TWINKLE + 5);
#        else
                rgblight_set_hsv_and_mode(HSV_CHARTREUSE, RGBLIGHT_MODE_BREATHING + 3);
#        endif
                break;
            case _MEDIA:
                rgblight_set_hsv_and_mode(HSV_CHARTREUSE, RGBLIGHT_MODE_KNIGHT + 1);
                break;
            case _GAMEPAD:
                rgblight_set_hsv_and_mode(HSV_ORANGE, RGBLIGHT_MODE_SNAKE + 2);
                break;
            case _DIABLO:
                rgblight_set_hsv_and_mode(HSV_RED, RGBLIGHT_MODE_BREATHING + 3);
                break;
            case _RAISE:
                rgblight_set_hsv_and_mode(HSV_YELLOW, RGBLIGHT_MODE_BREATHING + 3);
                break;
            case _LOWER:
                rgblight_set_hsv_and_mode(HSV_GREEN, RGBLIGHT_MODE_BREATHING + 3);
                break;
            case _ADJUST:
                rgblight_set_hsv_and_mode(HSV_RED, RGBLIGHT_MODE_KNIGHT + 2);
                break;
            case _COLEMAK:
                rgblight_set_hsv_and_mode(HSV_MAGENTA, mode);
                break;
            case _DVORAK:
                rgblight_set_hsv_and_mode(HSV_SPRINGGREEN, mode);
                break;
            case _WORKMAN:
                rgblight_set_hsv_and_mode(HSV_GOLDENROD, mode);
                break;
            case _NORMAN:
                rgblight_set_hsv_and_mode(HSV_CORAL, mode);
                break;
            case _MALTRON:
                rgblight_set_hsv_and_mode(HSV_YELLOW, mode);
                break;
            case _EUCALYN:
                rgblight_set_hsv_and_mode(HSV_PINK, mode);
                break;
            case _CARPLAX:
                rgblight_set_hsv_and_mode(HSV_BLUE, mode);
                break;
            default:
                rgblight_set_hsv_and_mode(HSV_CYAN, mode);
                break;
        }
    }
#    endif  // RGBLIGHT_ENABLE

    return state;
}

#endif
