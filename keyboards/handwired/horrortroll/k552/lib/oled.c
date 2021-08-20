#include <stdio.h>

// OLED animation
#include "layers.c"
#include "bongocat.c"
#include "wave.c"
#include "galaxy.c"

char wpm_str[10];

#ifdef OLED_ENABLE
uint16_t startup_timer; 

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    wave_timer = timer_read();
    return rotation;
}

static void redragon_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
    static bool finished_logo = false;
    if ((timer_elapsed(startup_timer) < 6000) && !finished_logo) {
        redragon_logo();
    } else {
        finished_logo = true;
        led_t led_usb_state = host_keyboard_led_state();
        static uint8_t old_layer;
        uint8_t layer = get_highest_layer(layer_state | default_layer_state);
        if (layer != old_layer) {
            oled_clear();
        }
        old_layer = layer;
        switch (layer) {
            case _BASE:
                render_bongocat();
                oled_set_cursor(14, 0);                           // sets cursor to (row, column) using charactar spacing (5 rows on 128x32 screen, anything more will overflow back to the top)
                sprintf(wpm_str, "WPM:%03d", get_current_wpm());  // edit the string to change wwhat shows up, edit %03d to change how many digits show up
                oled_write(wpm_str, false);                       // writes wpm on top right corner of string
                oled_set_cursor(17, 2);
                oled_write_P(led_usb_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);
                oled_set_cursor(17, 3);
                oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRL") : PSTR("    "), false);
                break;
            case _WAVE:
                // sleep if it has been long enough since we last got a char
                if (timer_elapsed32(wave_sleep) > OLED_TIMEOUT) {
                    oled_off();
                    return;
                } else {
                    oled_on();
                }
                render_layer_name();
                oled_set_cursor(0, 3);
                oled_write_P(led_usb_state.caps_lock ? PSTR("CAPSLK") : PSTR("      "), false);
                oled_set_cursor(15, 3);
                oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLK") : PSTR("     "), false);
                // time for the next frame?
                if (timer_elapsed(wave_timer) > FRAME_TIMEOUT) {
                    wave_timer = timer_read();
                    render_frame();
                }
                break;
            case _FN:
                render_galaxy();
                break;
        }
    }
}
#endif
