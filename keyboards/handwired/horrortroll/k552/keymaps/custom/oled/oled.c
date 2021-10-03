#include <stdio.h>
#include "layers.c"

// OLED animation
#include "logo.c"
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

void oled_task_user(void) {
    static bool finished_logo = false;

    if ((timer_elapsed(startup_timer) < 5000) && !finished_logo) {
        render_logo();
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
                oled_set_cursor(16, 3);
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
