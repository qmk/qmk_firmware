#pragma once
#include QMK_KEYBOARD_H
#include "keycodes_layers.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "global_variables.h"

#ifdef OLED_ENABLE
static void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

#ifdef BIG_MEMORY
void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}
#endif /* BIG_MEMORY */

void render_kb_LED_state(void) {
    // Host Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
    uint8_t led_count = 0;
    if (led_usb_state.num_lock)
    {
        oled_write_P(PSTR("N"), false);
        led_count++;
    }
    if (led_usb_state.caps_lock)
    {
        if (led_count != 0)
        {
            oled_write_P(PSTR(" "), false);
            led_count++;
        }
        oled_write_P(PSTR("C"), false);
        led_count++;
    }
    if (led_usb_state.scroll_lock)
    {
        if (led_count != 0)
        {
            oled_write_P(PSTR(" "), false);
            led_count++;
        }
        oled_write_P(PSTR("S"), false);
        led_count++;
    }
    while (led_count < 5)
    {
        oled_write_P(PSTR(" "), false);
        led_count++;
    }
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM syms_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM nums_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM navi_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _NUMS:
            oled_write_P(PSTR("NUMS "), false);
            oled_write_P(nums_layer, false);
            break;
        case _SYMS:
            oled_write_P(PSTR("SYMS "), false);
            oled_write_P(syms_layer, false);
            break;
        case _NAVI:
            oled_write_P(PSTR("NAVI "), false);
            oled_write_P(navi_layer, false);
            break;
        case _ONESHOT:
            oled_write_P(PSTR("ONES "), false);
            oled_write_P(default_layer, false);
            break;
#ifdef BIG_MEMORY
        case _GAMER:
            oled_write_P(PSTR("GAME "), false);
            oled_write_P(default_layer, false);
            break;
#endif
        case _NO_HOMEROW:
            oled_write_P(PSTR("NOROW"), false);
            oled_write_P(default_layer, false);
            break;
        default:
            oled_write_P(PSTR("HOME "), false);
            oled_write_P(default_layer, false);
            break;
    }
}

#ifdef WPM_ENABLE
void render_wpm(void)
{
    oled_write_P(PSTR("APM: "), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
}
#endif /* WPM_ENABLE */

void render_tap(void)
{
    oled_write(get_u16_str(timeout_tap, ' '), false);
}

void render_seq(void)
{
    oled_write(get_u16_str(timeout_seq, ' '), false);
}

void render_following(void)
{
    oled_write(get_u16_str(timeout_following, ' '), false);
}

void render_release(void)
{
    oled_write(get_u16_str(timeout_release_key, ' '), false);
}

void render_turbo_threshold(void)
{
    oled_write_P(PSTR("TURB:"), false);
    oled_write(get_u16_str(turbo_threshold, ' '), false);
}

void render_snap(void)
{
    if (snap_tap_entries_head != NULL)
    {
        oled_write_P(PSTR("SNAP"), false);
    }
    else
    {
        oled_write_P(PSTR("     "), false);
    }
}
#endif