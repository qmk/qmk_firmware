/*
Copyright 2020 Seth Bonner <fl3tching101@gmail.com>
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
#include "keycode_lookup.h"
#include <string.h>

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _SPEC 1 // Special layer

// Use the following format to create custom key codes to make macros out of and such
enum custom_keycodes {
    KC_EXAM = SAFE_RANGE // "Examine" key code to show the keycode of a key pressed afterwards on the OLED
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        RGB_MOD,                   KC_NUM,
        KC_P7,   KC_P8,   KC_P9,   KC_DEL,
        KC_P4,   KC_P5,   KC_P6,   KC_END,
        KC_P1,   KC_P2,   KC_P3,   KC_F13,
        KC_P0,   MO(1),   KC_PDOT, KC_PENT
    ),
    [_SPEC] = LAYOUT(
        RGB_RMOD,                   KC_MUTE,
        KC_NO,    KC_NO,   KC_NO,   KC_EXAM,
        KC_NO,    KC_NO,   KC_NO,   KC_NO,
        QK_BOOT,    RGB_TOG, RGB_SPI, RGB_SPD,
        KC_NO,    _______, KC_NO,   KC_NO
    )
};

bool encoder_update_user(uint8_t index, bool clockwise){
  if(index == 0) { // first encoder
    if(clockwise){
      tap_code(KC_AUDIO_VOL_UP);
    }else{
      tap_code(KC_AUDIO_VOL_DOWN);
    }
  }else if(index == 1){ // second encoder
    if(clockwise){
      rgblight_increase_val();
    }else{
      rgblight_decrease_val();
    }
  }
    return true;
}

#ifdef OLED_ENABLE

#define ANIM_FRAMES 3
#define ANIM_FRAME_DURATION 110 // Number of milliseconds per frame (no faster than 110ms, last line struggles)
#define BACKGROUND_FRAMES 21
#define ROCKET_CENTER_POS 3
#define SPLASH_DUR 100 // Measured in frames, see above for frame length (note, 231 is used as a key value later on, CTRL+F for uses of this to make sure everything is good)

uint32_t anim_timer = 0;
uint8_t current_frame = 0;
uint8_t rocket_y_position = 3;
uint8_t rocket_pos_change = 0;
uint8_t background_frame = 0;
uint8_t splash_dur_counter = 0;
bool examine_engaged = false;
uint16_t examined_keycode = KC_NO;
char lastKeycodeString[32] = { 0 };

const char star_background [8] [21] =
{
    {0x88, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x00, 0x93},
    {0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x00},
    {0x00, 0x8F, 0x00, 0x00, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x8B, 0x00, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00},
    {0x8D, 0x00, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x8F, 0x8B, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x8A, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00, 0x8F, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x8F, 0x00, 0x89, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x8D, 0x00, 0x00, 0x00, 0x8F},
    {0x00, 0x8B, 0x00, 0x00, 0x91, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x90, 0x00, 0x00, 0x8C, 0x00, 0x00},
};

static void oled_write_ln_centered(const char * data, bool inverted)
{
    if(strlen(data) >= 21) // If more than 1 line of text is passed in, return without doing anything
    {
        return;
    }

    // Character buffer to build up the string in
    char line_buf[21];

    // Amount to offset string from left side
    uint8_t offset = (22 - strlen(data)) / 2;

    // Formatted string centering... look, it works, don't ask how...
    snprintf(line_buf, 21, "%*s%s%*s", offset, "", data, offset, ""); // Centers data within 21 character buffer

    oled_write_ln(line_buf, inverted);
}

// Prints the exhaust characters in an order determined by the phase for animation purposes
// startX - The x axis starting point in characters for the exhaust (3 behind the rocket)
// startY - The y axis starting point in characters for the exhaust (middle of the rocket)
// phase - The "phase" of the animation, no real rhyme or reason to the exact number, but each frame move +1 to make the animation work
static void render_exhaust(uint8_t startX, uint8_t startY, uint8_t phase)
{
    oled_set_cursor(startX, startY);
    oled_write_char(0x85 + (phase % 3), false);
    phase++;
    oled_write_char(0x85 + (phase % 3), false);
    phase++;
    oled_write_char(0x85 + (phase % 3), false);
}

// Renders the "stars" behind the rocket
// startY - The starting Y location (in characters) of the rocket so that stars aren't rendered on top of the rocket
static void render_stars(uint8_t startY, uint8_t phase)
{
    // Line 0
    oled_set_cursor(0, 0);
    for(int i = 0; i < 21; i++)
    {
        oled_write_char(star_background[0][(i + phase) % 21], false);
    }
    // Line 1
    oled_set_cursor(0, 1);
    for(int i = 0; i < 21; i++)
    {
        oled_write_char(star_background[1][(i + phase) % 21], false);
    }
    // Line 2
    oled_set_cursor(0, 2);
    for(int i = 0; i < 21; i++)
    {
        oled_write_char(star_background[2][(i + phase) % 21], false);
    }
    // Line 3
    oled_set_cursor(0, 3);
    for(int i = 0; i < 21; i++)
    {
        oled_write_char(star_background[3][(i + phase) % 21], false);
    }
    // Line 4
    oled_set_cursor(0, 4);
    for(int i = 0; i < 21; i++)
    {
        oled_write_char(star_background[4][(i + phase) % 21], false);
    }
    // Line 5
    oled_set_cursor(0, 5);
    for(int i = 0; i < 21; i++)
    {
        oled_write_char(star_background[5][(i + phase) % 21], false);
    }
    // Line 6
    oled_set_cursor(0, 6);
    for(int i = 0; i < 21; i++)
    {
        oled_write_char(star_background[6][(i + phase) % 21], false);
    }
    // Line 7
    oled_set_cursor(0, 7);
    for(int i = 0; i < 21; i++)
    {
        oled_write_char(star_background[7][(i + phase) % 21], false);
    }

}

static void render_logo(uint8_t startX, uint8_t startY)
{
    oled_set_cursor(startX, startY);
    oled_write_char(0x80, false);
    oled_write_char(0x81, false);
    oled_write_char(0x82, false);
    oled_write_char(0x83, false);
    oled_write_char(0x84, false);
    oled_set_cursor(startX, startY + 1);
    oled_write_char(0xA0, false);
    oled_write_char(0xA1, false);
    oled_write_char(0xA2, false);
    oled_write_char(0xA3, false);
    oled_write_char(0xA4, false);
    oled_write_char(0xA5, false);
    oled_set_cursor(startX, startY + 2);
    oled_write_char(0xC0, false);
    oled_write_char(0xC1, false);
    oled_write_char(0xC2, false);
    oled_write_char(0xC3, false);
    oled_write_char(0xC4, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void)
{
    // Playing the animation
    if((timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) && (splash_dur_counter < SPLASH_DUR))
    {
        anim_timer = timer_read32(); // read the current timer value
        current_frame = (current_frame + 1) % ANIM_FRAMES; // Frame in the exhaust animation
        background_frame = (background_frame + 1) % BACKGROUND_FRAMES; // Frame in the star animation

        // Move the rocket up and down
        if((rocket_pos_change / 9) == 0)
        {
            rocket_y_position = ROCKET_CENTER_POS;
        }
        else if((rocket_pos_change / 9) == 1)
        {
            rocket_y_position = ROCKET_CENTER_POS + 1;
        }
        else if((rocket_pos_change / 9) == 2)
        {
            rocket_y_position = ROCKET_CENTER_POS;
        }
        if((rocket_pos_change / 9) == 3)
        {
            rocket_y_position = ROCKET_CENTER_POS - 1;
        }

        // Renders the scene piece by piece
        render_stars(8, background_frame); // Render star background
        render_exhaust(6, rocket_y_position + 1, current_frame); // Render exhaust
        render_logo(9, rocket_y_position); // Render the rocket

        // Timing for rocket position change
        if(rocket_pos_change < 36)
        {
            rocket_pos_change++;
        }
        else
        {
            rocket_pos_change = 0;
        }

        splash_dur_counter++;
    }
    else if((splash_dur_counter >= SPLASH_DUR) && (splash_dur_counter != 231)) // Should only run once at end of splash screen duration
    {
        splash_dur_counter = 231; // Nice known value
        oled_clear(); // Clear the screen
    }


    // After the splash screen
    if(splash_dur_counter == 231)
    {
        uint8_t light_level = rgblight_get_val();
        light_level = (uint8_t)(100.0 * ((float)light_level/(float)RGBLIGHT_LIMIT_VAL)); // Convert to %
        char c_light_level[3];
        itoa(light_level, c_light_level, 10);

        // Display lock LED statuses
        led_t led_state = host_keyboard_led_state();
        if(led_state.num_lock)
        {
            oled_write(PSTR("   |"), false);
            oled_write(PSTR("NUM"), true);
            oled_write(PSTR("|"), false);
        }
        else
        {
            oled_write(PSTR("   |NUM|"), false);
        }

        if(led_state.caps_lock)
        {
            oled_write(PSTR("|"), false);
            oled_write(PSTR("CAP"), true);
            oled_write(PSTR("|"), false);
        }
        else
        {
            oled_write(PSTR("|CAP|"), false);
        }

        if(led_state.scroll_lock)
        {
            oled_write(PSTR("|"), false);
            oled_write(PSTR("SCR"), true);
            oled_write(PSTR("|   "), false);
        }
        else
        {
            oled_write(PSTR("|SCR|   "), false);
        }

        // Print the examine info
        if(examine_engaged == true)
        {
            oled_set_cursor(0, 2);
            oled_write_ln(PSTR("      Keycode:      "), false);
            oled_write_ln_centered(lastKeycodeString, false);
        }
        else
        {
            oled_set_cursor(0, 2);
            oled_write_ln(PSTR("                    "), false);
            oled_write_ln(PSTR("                    "), false);
        }

        // Print the backlight % bottom right
        oled_set_cursor(11, 7);
        oled_write(PSTR("BKLT: "), false);
        oled_write(c_light_level, false);
        oled_write(PSTR("%"), false);

        // Print the layer number in bottom left
        oled_set_cursor(0, 7);
        oled_write(PSTR("L: "), false);
        switch (get_highest_layer(layer_state))
        {
        case 0:
            oled_write(PSTR("0"), false);
            break;
        case 1:
            oled_write(PSTR("1"), false);
            break;
        case 2:
            oled_write(PSTR("2"), false);
            break;
        case 3:
            oled_write(PSTR("3"), false);
            break;
        default:
            oled_write(PSTR("Und"), false);
            break;
        }


    }

    return false;
}

// Process the extra/extended keycode functionality
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    bool ret = true; // True will allow QMK to process the key as usual after the function runs, false skips QMK processing after this function runs

    switch (keycode)
    {
    case KC_EXAM:
        if(record->event.pressed) // On pressed, flip bool examine_engaged
        {
            if(examine_engaged == false)
            {
                examine_engaged = true;
            }
            else
            {
                examine_engaged = false;
            }
            ret = false;
        }
        else // On release do nothing
        {
            ret = false;
        }
        break;

    default: // For any key other than EX, simply let QMK process after saving away what it was
        memset(lastKeycodeString, 0, sizeof(lastKeycodeString));
        memcpy(lastKeycodeString, translate_keycode_to_string(keycode), sizeof(((lookup_table_t *)0)->key_string));
        ret = true;
        break;
    }

    return ret;
}
#endif
