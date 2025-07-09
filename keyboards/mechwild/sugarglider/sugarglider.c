// Copyright 2023 Kyle McCreery
// SPDX-License-Identifier: GPL-2.0-or-later

#include "sugarglider.h"

#ifndef GLIDEPOINT_DPI_OPTIONS
#    define GLIDEPOINT_DPI_OPTIONS \
        { 400, 800, 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000 }
#endif

#ifndef GLIDEPOINT_DPI_DEFAULT
#    define GLIDEPOINT_DPI_DEFAULT 1
#endif

keyboard_config_t keyboard_config;
uint16_t          dpi_array[] = GLIDEPOINT_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

void board_init(void) {
    // B9 is configured as I2C1_SDA in the board file; that function must be
    // disabled before using B7 as I2C1_SDA.
    gpio_set_pin_input_high(B9);
    gpio_set_pin_output(B12);
    gpio_set_pin_output(B13);
    gpio_set_pin_output(B14);
    gpio_write_pin_low(B12);
    gpio_write_pin_low(B13);
    gpio_write_pin_low(B14);
    gpio_set_pin_output(C13);
}

#ifdef DYNAMIC_TAPPING_TERM_ENABLE
void tap_modify(int change_value, bool tap_status) {
    if (keyboard_config.dt_term_config < 0) {
        keyboard_config.dt_term_config *= -1;
    }

    keyboard_config.dt_term_config += change_value;

    if (tap_status == false ) {
        keyboard_config.dt_term_config *= -1;
        g_tapping_term = 0;
    } else {
        g_tapping_term = keyboard_config.dt_term_config;
    }
    eeconfig_update_kb(keyboard_config.raw);
}

void tap_toggle(void) {
    keyboard_config.dt_term_config *= -1;
    if (keyboard_config.dt_term_config > 0) {
        g_tapping_term = keyboard_config.dt_term_config;
    } else {
        g_tapping_term = 0;
    }
    eeconfig_update_kb(keyboard_config.raw);
}
#endif  // ifdef DYNAMIC_TAPPING_TERM_ENABLE

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) { return false; }
    switch (index) {
        case 0:
            if(active != host_keyboard_led_state().caps_lock) { tap_code(KC_CAPS); }
            break;
        break;
    }
    return true;
}
#endif

#if defined(ENCODER_ENABLE) && ! defined(ENCODER_MAP_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        break;
        case 1:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        break;
        case 2:
            if (clockwise) {
                tap_code(KC_PGUP);
            } else {
                tap_code(KC_PGDN);
            }
        break;
        case 3:
            if (clockwise) {
                tap_code(KC_WH_U);
            } else {
                tap_code(KC_WH_D);
            }
        break;
    }
    return true;
}
#endif

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        gpio_write_pin(B12, led_state.num_lock);     // Updates status LEDs
        gpio_write_pin(B13, led_state.caps_lock);    // Updates status LEDs
        gpio_write_pin(B14, led_state.scroll_lock);  // Updates status LEDs
        gpio_write_pin(C13, !led_state.caps_lock);   // Updates status LEDs, this is the LED on the blackpill itself
    }
    return res;
}

#ifdef OLED_ENABLE
static void render_logo(void) {     // Render MechWild "MW" Logo
    static const char PROGMEM logo_1[] = {0xCC, 0xCD, 0xCE, 0xCF, 0x00};
    static const char PROGMEM logo_2[] = {0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};
    static const char PROGMEM logo_3[] = {0xD5, 0xD6, 0xD7, 0xD8, 0x00};
    static const char PROGMEM logo_4[] = {0xDE, 0xD9, 0xDA, 0xDB, 0x00};
    
    oled_write_P(logo_1, false);
    oled_set_cursor(0,1);
    oled_write_P(logo_2, false);
    oled_set_cursor(0,2);
    oled_write_P(logo_3, false);
    oled_set_cursor(0,3);
    oled_write_P(logo_4, false);
}

#ifdef OLED_DISPLAY_128X64 // Wide OLED Functionality
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;       // flips the display 180 degrees
}

bool clear_screen = true;           // used to manage singular screen clears to prevent display glitch
bool clear_screen_art = true;       // used to manage singular screen clears to prevent display glitch
static void render_sugarglider_wide(void) {     // Render sugarglider logo
    static const char PROGMEM sgl_1[] = {0xDE, 0xDE, 0xDE, 0x98, 0x99, 0xDE, 0x9A, 0x9B, 0x9C, 0xDE, 0xDE, 0xDE, 0xDE, 0xDE, 0xCC, 0xCD, 0xCE, 0xCF, 0x00};
    static const char PROGMEM sgl_2[] = {0x9D, 0x9E, 0xDE, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xDE, 0xDE, 0xDE, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};
    static const char PROGMEM sgl_3[] = {0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xDE, 0xDE, 0xDE, 0xD5, 0xD6, 0xD7, 0xD8, 0x00};
    static const char PROGMEM sgl_4[] = {0xDE, 0xB2, 0xDE, 0xB3, 0xB4, 0xB5, 0xB6, 0xDE, 0xDE, 0xB7, 0xDE, 0xDE, 0xDE, 0xDE, 0xDE, 0xD9, 0xDA, 0xDB, 0x00};
    static const char PROGMEM sgl_5[] = {0xDE, 0xB8, 0xDE, 0xDE, 0xDE, 0xDE, 0xDE, 0xDE, 0xB9, 0x00};
    static const char PROGMEM sgl_6[] = {0xDE, 0xBA, 0xDE, 0xDE, 0xDE, 0xDE, 0xDE, 0xDE, 0xBB, 0xBC, 0x00};
    static const char PROGMEM sgl_7[] = {0xDE, 0xBD, 0xBE, 0xDE, 0xDE, 0xBF, 0xDE, 0xDE, 0xC0, 0xC1, 0x00};
    static const char PROGMEM sgl_8[] = {0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0x00};

    oled_write_P(sgl_1, false);
    oled_set_cursor(0,1);
    oled_write_P(sgl_2, false);
    oled_set_cursor(0,2);
    oled_write_P(sgl_3, false);
    oled_set_cursor(0,3);
    oled_write_P(sgl_4, false);
    oled_set_cursor(0,4);
    oled_write_P(sgl_5, false);
    oled_set_cursor(0,5);
    oled_write_P(sgl_6, false);
    oled_set_cursor(0,6);
    oled_write_P(sgl_7, false);
    oled_set_cursor(0,7);
    oled_write_P(sgl_8, false);
}

bool oled_task_kb(void) {
    if(!oled_task_user()) {
        return false;
    }
    if ( !(host_keyboard_led_state().num_lock || host_keyboard_led_state().caps_lock || host_keyboard_led_state().scroll_lock ) && get_highest_layer(layer_state) == 0 ) {      // If none of the status LEDs are active and also the active layer is the base layer
        if (clear_screen_art == true) {
            oled_clear();
            oled_render();
            clear_screen_art = false;
        }
        render_sugarglider_wide();
#ifdef POINTING_DEVICE_ENABLE                           // only display dpi and tap info if pointing devices are active
        oled_set_cursor(10,5);
        oled_write_P(PSTR(" DPI:"), false);
        oled_write(get_u16_str(dpi_array[keyboard_config.dpi_config], ' '), false);
#ifdef DYNAMIC_TAPPING_TERM_ENABLE                      // only display tap info if it is being configured dynamically
        oled_set_cursor(10,6);
        oled_write_P(PSTR(" TAP:"), false);
        if (keyboard_config.dt_term_config < 0) {
            oled_write_P(PSTR("Off  "), false);
        } else {
            oled_write(get_u16_str(g_tapping_term, ' '), false);
        }
#endif
#endif
        clear_screen = true;
    } else {        // If any of the status LEDs are active or if the active layer is not the base layer
        if (clear_screen == true) {
            oled_clear();
            oled_render();
            clear_screen = false;
        }
        render_logo();
        oled_set_cursor(8,1);
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("Base  "), false);
                break;
            case 1:
                oled_write_P(PSTR("Lower "), false);
                break;
            case 2:
                oled_write_P(PSTR("Raise "), false);
                break;
            case 3:
                oled_write_P(PSTR("Adjust"), false);
                break;
            case 4:
                oled_write_P(PSTR("Mouse "), false);
                break;
#ifdef STENO_ENABLE
            case 5:
                oled_write_P(PSTR("Steno Layer"), false);
                break;
#endif
            default:
                oled_write_P(PSTR("Layer ?"), false);    // Should never display, here as a catchall
        }
        led_t led_state = host_keyboard_led_state();
        oled_set_cursor(8,0);
        oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
        oled_write_P(led_state.scroll_lock ? PSTR("SCR") : PSTR("    "), false);
#ifdef POINTING_DEVICE_ENABLE                   // only display dpi and tap info if pointing devices are active
        oled_set_cursor(8,2);
        oled_write_P(PSTR("DPI:"), false);
        oled_write(get_u16_str(dpi_array[keyboard_config.dpi_config], ' '), false);
#ifdef DYNAMIC_TAPPING_TERM_ENABLE              // only display tap info if it is being configured dynamically
        oled_set_cursor(8,3);
        oled_write_P(PSTR("TAP:"), false);
        if (keyboard_config.dt_term_config < 0) {
            oled_write_P(PSTR("Off  "), false);
        } else {
            oled_write(get_u16_str(g_tapping_term, ' '), false);
        }
#endif
#endif
        clear_screen_art = true;
    }
    return true;
}
#else  // Using an OLED but not the wide OLED
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;       // flips the display 270 degrees
}


bool oled_task_kb(void) {
    if(!oled_task_user()) {
        return false;
    }
    render_logo();

    oled_set_cursor(0,5);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base "), false);
            break;
        case 1:
            oled_write_P(PSTR("Lower"), false);
            break;
        case 2:
            oled_write_P(PSTR("Raise"), false);
            break;
        case 3:
            oled_write_P(PSTR("Adjst"), false);
            break;
        case 4:
            oled_write_P(PSTR("Mouse"), false);
            break;
#ifdef STENO_ENABLE
        case 5:
            oled_write_P(PSTR("Steno"), false);
            break;
#endif
        default:
            oled_write_P(PSTR("?????"), false);    // Should never display, here as a catchall
    }
        led_t led_state = host_keyboard_led_state();
        oled_set_cursor(0,6);
        oled_write_P(led_state.num_lock ? PSTR("NUM  ") : PSTR("     "), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAP  ") : PSTR("     "), false);
        oled_write_P(led_state.scroll_lock ? PSTR("SCR  ") : PSTR("     "), false);
#ifdef POINTING_DEVICE_ENABLE
        oled_set_cursor(0,11);
        oled_write_P(PSTR("DPI: "), false);
        oled_write(get_u16_str(dpi_array[keyboard_config.dpi_config], ' '), false);
#endif
#ifdef DYNAMIC_TAPPING_TERM_ENABLE              // only display tap info if it is being configured dynamically
        oled_set_cursor(0,13);
        oled_write_P(PSTR("TAP: "), false);
        if (keyboard_config.dt_term_config < 0) {
            oled_write_P(PSTR("Off  "), false);
        } else {
            oled_write(get_u16_str(g_tapping_term, ' '), false);
        }
#endif
    return true;
}
#endif // Not using wide OLED
#endif // ifdef OLED_ENABLE

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
#ifdef POINTING_DEVICE_ENABLE
        case DPI_UP:
            if (record->event.pressed) {
                keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
                eeconfig_update_kb(keyboard_config.raw);
                pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }
            return false;
        case DPI_DN:
            if (record->event.pressed) {
                if (keyboard_config.dpi_config > 0) {
                    keyboard_config.dpi_config = (keyboard_config.dpi_config - 1) % DPI_OPTION_SIZE;
                } else {
                    keyboard_config.dpi_config = DPI_OPTION_SIZE - 1;
                }
                eeconfig_update_kb(keyboard_config.raw);
                pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }
            return false;
        case DPI_FINE:
            if (record->event.pressed) {
                pointing_device_set_cpi(dpi_array[0]);
            } else {
                pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }
            return false;
#endif
#ifdef DYNAMIC_TAPPING_TERM_ENABLE // only include tap info keycodes if it is being configured dynamically
        case TAP_UP:
            if (record->event.pressed) {
                if (keyboard_config.dt_term_config < 5000) {
                    tap_modify(DYNAMIC_TAPPING_TERM_INCREMENT, true);
                }
            }
            return false;
        case TAP_DN:
            if (record->event.pressed) {
                if (keyboard_config.dt_term_config > 0) {
                    tap_modify(-1 * DYNAMIC_TAPPING_TERM_INCREMENT, true);
                }
            }
            return false;
        case TAP_ON:
            if (record->event.pressed) {
                tap_modify(0, true);
            }
            return false;
        case TAP_OFF:
            if (record->event.pressed) {
                tap_modify(0, false);
            }
            return false;
        case TAP_TOG:
            if (record->event.pressed) {
                tap_toggle();
            }
            return false;
#endif // ifdef 
    }
    return process_record_user(keycode, record);
}

void pointing_device_init_kb(void) {
#ifdef POINTING_DEVICE_ENABLE
    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
#endif
}

void eeconfig_init_kb(void) {
#ifdef POINTING_DEVICE_ENABLE
    keyboard_config.dpi_config = GLIDEPOINT_DPI_DEFAULT;
#endif
#ifdef DYNAMIC_TAPPING_TERM_ENABLE // only set tap term from eeprom if it is being configured dynamically
    keyboard_config.dt_term_config = TAPPING_TERM;
#endif
    eeconfig_update_kb(keyboard_config.raw);
#ifdef STENO_ENABLE
    steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
#endif
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    // is safe to just read DPI setting since matrix init
    // comes before pointing device init.
    keyboard_config.raw = eeconfig_read_kb();
#ifdef POINTING_DEVICE_ENABLE
    if (keyboard_config.dpi_config > DPI_OPTION_SIZE) {
        eeconfig_init_kb();
    }
#endif
    matrix_init_user();
}

void keyboard_post_init_kb(void) {
#ifdef POINTING_DEVICE_ENABLE
    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_toggle_noeeprom();     //double toggle post init removes the weirdness with rgb strips having a yellow first LED
    rgblight_toggle_noeeprom();
#endif
#ifdef DYNAMIC_TAPPING_TERM_ENABLE
    tap_toggle();   // Need it to reevaluate this setting after initiating so that it is current after init
    tap_toggle();
#endif
    keyboard_post_init_user();
#ifdef OLED_ENABLE  // purposefully after user post init to allow the RGB to startup first
    wait_ms(200);   // Avoids a startup issue where the oled renders and then turns off with blackpill
    oled_on();
#endif
}
