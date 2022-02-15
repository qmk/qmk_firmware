//Animation loader file
#include "helix.c" //animation file
#include <stdio.h>
// static uint16_t oled_timer = 0;
char wpm_str[10];

#    define ANIM_SIZE 1024  // number of bytes in array, minimize for adequate firmware size, max is 1024
#    define ANIM_FRAMES 50 // Number of frames
#    define ANIM_FRAME_DURATION 120 // How long each frame lasts in ms

uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t  current_idle_frame = 0;

static void render_anim(void) {
    // assumes 1 frame prep stage
    void animation_phase(void) {
        current_idle_frame = (current_idle_frame + 1) % ANIM_FRAMES;
        oled_write_raw_P(animation[abs((ANIM_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);

    }
    if (get_current_wpm() != 000) {
        oled_on();  
        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

// Used to draw on to the oled screen
void oled_task_user(void) {
    render_anim();  // renders pixelart
     // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer:"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Settings\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    sprintf(wpm_str, "WPM:%03d", get_current_wpm());  // edit the string to change wwhat shows up, edit %03d to change how many digits show up
    oled_write(wpm_str, false);                       // writes wpm on top left corner of string
}
