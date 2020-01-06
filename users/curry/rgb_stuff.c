#include "curry.h"
#include "rgb_stuff.h"
#include "eeprom.h"

#if defined(RGBLIGHT_ENABLE)
extern rgblight_config_t rgblight_config;
bool                     has_initialized;

void rgblight_sethsv_default_helper(uint8_t index) { rgblight_sethsv_at(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, index); }
#endif  // RGBLIGHT_ENABLE

#if defined(RGB_MATRIX_ENABLE)
static uint32_t hypno_timer;
#    if defined(SPLIT_KEYBOARD) || defined(KEYBOARD_ergodox_ez) || defined(KEYBOARD_crkbd)
#        define RGB_MATRIX_REST_MODE RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    else
#        define RGB_MATRIX_REST_MODE RGB_MATRIX_CYCLE_OUT_IN
#    endif

void suspend_power_down_keymap(void) { rgb_matrix_set_suspend_state(true); }

void suspend_wakeup_init_keymap(void) { rgb_matrix_set_suspend_state(false); }

void check_default_layer(uint8_t mode, uint8_t type) {
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            rgb_matrix_layer_helper(HSV_CYAN, mode, rgb_matrix_config.speed, type);
            break;
        case _COLEMAK:
            rgb_matrix_layer_helper(HSV_MAGENTA, mode, rgb_matrix_config.speed, type);
            break;
        case _DVORAK:
            rgb_matrix_layer_helper(HSV_SPRINGGREEN, mode, rgb_matrix_config.speed, type);
            break;
    }
}

void rgb_matrix_indicators_user(void) {
    if (userspace_config.rgb_layer_change &&
#    ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
        !g_suspend_state &&
#    endif
#    if defined(RGBLIGHT_ENABLE)
        (!rgblight_config.enable && rgb_matrix_config.enable)
#    else
        rgb_matrix_config.enable
#    endif
    ) {
        switch (get_highest_layer(layer_state)) {
            case _RAISE:
                rgb_matrix_layer_helper(HSV_YELLOW, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            default: {
                check_default_layer(IS_LAYER_ON(_MODS), LED_FLAG_UNDERGLOW);
                break;
            }
        }
        check_default_layer(0, LED_FLAG_MODIFIER);
    }
}
#endif

/* Custom indicators for modifiers.
 * This allows for certain lights to be lit up, based on what mods are active, giving some visual feedback.
 * This is especially useful for One Shot Mods, since it's not always obvious if they're still lit up.
 */
#ifdef RGBLIGHT_ENABLE
#    ifdef INDICATOR_LIGHTS
void set_rgb_indicators(uint8_t this_mod, uint8_t this_led, uint8_t this_osm) {
    if (userspace_config.rgb_layer_change && get_highest_layer(layer_state) == 0) {
        if ((this_mod | this_osm) & MOD_MASK_SHIFT || this_led & (1 << USB_LED_CAPS_LOCK)) {
#        ifdef SHFT_LED1
            rgblight_sethsv_at(120, 255, 255, SHFT_LED1);
#        endif  // SHFT_LED1
#        ifdef SHFT_LED2
            rgblight_sethsv_at(120, 255, 255, SHFT_LED2);
#        endif  // SHFT_LED2
        } else {
#        ifdef SHFT_LED1
            rgblight_sethsv_default_helper(SHFT_LED1);
#        endif  // SHFT_LED1
#        ifdef SHFT_LED2
            rgblight_sethsv_default_helper(SHFT_LED2);
#        endif  // SHFT_LED2
        }
        if ((this_mod | this_osm) & MOD_MASK_CTRL) {
#        ifdef CTRL_LED1
            rgblight_sethsv_at(0, 255, 255, CTRL_LED1);
#        endif  // CTRL_LED1
#        ifdef CTRL_LED2
            rgblight_sethsv_at(0, 255, 255, CTRL_LED2);
#        endif  // CTRL_LED2
        } else {
#        ifdef CTRL_LED1
            rgblight_sethsv_default_helper(CTRL_LED1);
#        endif  // CTRL_LED1
#        ifdef CTRL_LED2
            rgblight_sethsv_default_helper(CTRL_LED2);
#        endif  // CTRL_LED2
        }
        if ((this_mod | this_osm) & MOD_MASK_GUI) {
#        ifdef GUI_LED1
            rgblight_sethsv_at(51, 255, 255, GUI_LED1);
#        endif  // GUI_LED1
#        ifdef GUI_LED2
            rgblight_sethsv_at(51, 255, 255, GUI_LED2);
#        endif  // GUI_LED2
        } else {
#        ifdef GUI_LED1
            rgblight_sethsv_default_helper(GUI_LED1);
#        endif  // GUI_LED1
#        ifdef GUI_LED2
            rgblight_sethsv_default_helper(GUI_LED2);
#        endif  // GUI_LED2
        }
        if ((this_mod | this_osm) & MOD_MASK_ALT) {
#        ifdef ALT_LED1
            rgblight_sethsv_at(240, 255, 255, ALT_LED1);
#        endif  // ALT_LED1
#        ifdef GUI_LED2
            rgblight_sethsv_at(240, 255, 255, ALT_LED2);
#        endif  // GUI_LED2
        } else {
#        ifdef GUI_LED1
            rgblight_sethsv_default_helper(ALT_LED1);
#        endif  // GUI_LED1
#        ifdef GUI_LED2
            rgblight_sethsv_default_helper(ALT_LED2);
#        endif  // GUI_LED2
        }
    }
}

/* Function for the indicators */
void matrix_scan_indicator(void) {
    if (has_initialized) {
        set_rgb_indicators(get_mods(), host_keyboard_leds(), get_oneshot_mods());
    }
}
#    endif  // INDICATOR_LIGHTS

#    ifdef RGBLIGHT_TWINKLE
static rgblight_fadeout lights[RGBLED_NUM];

__attribute__((weak)) bool rgblight_twinkle_is_led_used_keymap(uint8_t index) { return false; }

/* This function checks for used LEDs.  This way, collisions don't occur and cause weird rendering */
bool rgblight_twinkle_is_led_used(uint8_t index) {
    switch (index) {
#        ifdef INDICATOR_LIGHTS
#            ifdef SHFT_LED1
        case SHFT_LED1:
            return true;
#            endif  // SHFT_LED1
#            ifdef SHFT_LED2
        case SHFT_LED2:
            return true;
#            endif  // SHFT_LED2
#            ifdef CTRL_LED1
        case CTRL_LED1:
            return true;
#            endif  // CTRL_LED1
#            ifdef CTRL_LED2
        case CTRL_LED2:
            return true;
#            endif  // CTRL_LED2
#            ifdef GUI_LED1
        case GUI_LED1:
            return true;
#            endif  // GUI_LED1
#            ifdef GUI_LED2
        case GUI_LED2:
            return true;
#            endif  // GUI_LED2
#            ifdef ALT_LED1
        case ALT_LED1:
            return true;
#            endif  // ALT_LED1
#            ifdef ALT_LED2
        case ALT_LED2:
            return true;
#            endif  // ALT_LED2
#        endif      // INDICATOR_LIGHTS
        default:
            return rgblight_twinkle_is_led_used_keymap(index);
    }
}

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
        if (rgblight_twinkle_is_led_used(index)) {
            continue;
        }
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

    light->hue = rgblight_config.hue + (rand() % 0xB4) - 0x54;

    rgblight_sethsv_at(light->hue, 255, light->life, light_index);
}
#    endif
#endif  // RGBLIGHT_ENABLE

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
    uint16_t temp_keycode = keycode;
    // Filter out the actual keycode from MT and LT keys.
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        temp_keycode &= 0xFF;
    }

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    hypno_timer = timer_read32();
    if (userspace_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == RGB_MATRIX_REST_MODE) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    }
#endif

    switch (temp_keycode) {
#ifdef RGBLIGHT_TWINKLE
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
#endif                  // RGBLIGHT_TWINKLE
        case KC_RGB_T:  // This allows me to use underglow as layer indication, or as normal
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                userspace_config.rgb_layer_change ^= 1;
                dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                eeconfig_update_user(userspace_config.raw);
                if (userspace_config.rgb_layer_change) {
                    layer_state_set(layer_state);  // This is needed to immediately set the layer color (looks better)
                }
            }
#endif  // RGBLIGHT_ENABLE
            break;
        case RGB_IDL:  // This allows me to use underglow as layer indication, or as normal
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
            if (record->event.pressed) {
                userspace_config.rgb_matrix_idle_anim ^= 1;
                dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                eeconfig_update_user(userspace_config.raw);
                if (userspace_config.rgb_matrix_idle_anim) {
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
                }
            }
#endif
            break;
        case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT:  // quantum_keycodes.h L400 for definitions
            if (record->event.pressed) {
                bool is_eeprom_updated = false;
#ifdef RGBLIGHT_ENABLE
                // This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
                if (userspace_config.rgb_layer_change) {
                    userspace_config.rgb_layer_change = false;
                    dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                    is_eeprom_updated = true;
                }
#endif
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
                if (userspace_config.rgb_matrix_idle_anim) {
                    userspace_config.rgb_matrix_idle_anim = false;
                    dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                    is_eeprom_updated = true;
                }
#endif
                if (is_eeprom_updated) {
                    eeconfig_update_user(userspace_config.raw);
                }
            }
            break;
    }
    return true;
}

void keyboard_post_init_rgb(void) {
#if defined(RGBLIGHT_ENABLE)
#    if defined(RGBLIGHT_STARTUP_ANIMATION)
    bool is_enabled = rgblight_config.enable;
    if (userspace_config.rgb_layer_change) {
        rgblight_enable_noeeprom();
    }
    if (rgblight_config.enable) {
        layer_state_set_user(layer_state);
        uint16_t old_hue = rgblight_config.hue;
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        for (uint16_t i = 255; i > 0; i--) {
            rgblight_sethsv_noeeprom((i + old_hue) % 255, 255, 255);
            matrix_scan();
            wait_ms(10);
        }
    }
    if (!is_enabled) {
        rgblight_disable_noeeprom();
    }

#    endif
    layer_state_set_user(layer_state);
#endif
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    if (userspace_config.rgb_matrix_idle_anim) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_REST_MODE);
    }
#endif
}

void matrix_scan_rgb(void) {
#ifdef RGBLIGHT_ENABLE
#    ifdef RGBLIGHT_TWINKLE
    scan_rgblight_fadeout();
#    endif  // RGBLIGHT_ENABLE

#    ifdef INDICATOR_LIGHTS
    matrix_scan_indicator();
#    endif
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    if (userspace_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == RGB_MATRIX_TYPING_HEATMAP && timer_elapsed32(hypno_timer) > 15000) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_REST_MODE);
    }
#endif
}

#ifdef RGBLIGHT_ENABLE
void rgblight_set_hsv_and_mode(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode) {
    rgblight_sethsv_noeeprom(hue, sat, val);
    wait_us(175);  // Add a slight delay between color and mode to ensure it's processed correctly
    rgblight_mode_noeeprom(mode);
}
#endif

layer_state_t layer_state_set_rgb(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    if (userspace_config.rgb_layer_change) {
        switch (get_highest_layer(state)) {
            case _RAISE:
                rgblight_set_hsv_and_mode(HSV_YELLOW, RGBLIGHT_MODE_BREATHING + 3);
                break;
            case _LOWER:
                rgblight_set_hsv_and_mode(HSV_GREEN, RGBLIGHT_MODE_BREATHING + 3);
                break;
            case _ADJUST:
                rgblight_set_hsv_and_mode(HSV_RED, RGBLIGHT_MODE_KNIGHT + 2);
                break;
            default:  //  for any other layers, or the default layer
            {
                uint8_t mode = get_highest_layer(state) == _MODS ? RGBLIGHT_MODE_BREATHING : RGBLIGHT_MODE_STATIC_LIGHT;
                switch (get_highest_layer(default_layer_state)) {
                    case _COLEMAK:
                        rgblight_set_hsv_and_mode(HSV_MAGENTA, mode);
                        break;
                    case _DVORAK:
                        rgblight_set_hsv_and_mode(HSV_SPRINGGREEN, mode);
                        break;
                    default:
                        rgblight_set_hsv_and_mode(HSV_CYAN, mode);
                        break;
                }
                break;
            }
        }
    }
#endif  // RGBLIGHT_ENABLE

    return state;
}

#ifdef RGB_MATRIX_ENABLE
#    include "lib/lib8tion/lib8tion.h"
extern led_config_t g_led_config;

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_config.hsv.v) {
        hsv.v = rgb_matrix_config.hsv.v;
    }

    switch (mode) {
        case 1:  // breathing
        {
            uint16_t time = scale16by8(g_rgb_counters.tick, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
    }
}
#endif
