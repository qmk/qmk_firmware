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


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _SPEC 1 // Special layer

// Use the following format to create custom key codes to make macros out of and such
/*
enum custom_keycodes {
 FOO = SAFE_RANGE,
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_default(
        RGB_MODE_FORWARD,                KC_NUMLOCK,
        KC_KP_7, KC_KP_8, KC_KP_9,       KC_DELETE,
        KC_KP_4, KC_KP_5, KC_KP_6,       KC_END,
        KC_KP_1, KC_KP_2, KC_KP_3,       KC_F13,
        KC_KP_0, MO(1),   KC_KP_DOT,     KC_KP_ENTER
    ),
    [_SPEC] = LAYOUT_default(
        RGB_MODE_REVERSE,               KC_AUDIO_MUTE,
        KC_NO,   KC_NO,   KC_NO,         KC_NO,
        KC_NO,   KC_NO,   KC_NO,         KC_NO,
        RESET,   RGB_TOG, RGB_SPI,       RGB_SPD,
        KC_NO,   _______, KC_NO,         KC_NO
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

uint32_t anim_timer = 0;
uint8_t current_frame = 0;
uint8_t rocket_y_position = 3;
uint8_t rocket_pos_change = 0;
uint8_t background_frame = 0;

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

void oled_task_user(void)
{
    if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION)
    {
        anim_timer = timer_read32();
        current_frame = (current_frame + 1) % ANIM_FRAMES;
        background_frame = (background_frame + 1) % BACKGROUND_FRAMES;

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

        render_stars(8, background_frame);
        render_exhaust(6, rocket_y_position + 1, current_frame);
        render_logo(9, rocket_y_position); // Render the rocket
        if(rocket_pos_change < 36)
        {
            rocket_pos_change++;
        }
        else
        {
            rocket_pos_change = 0;
        }
    }
}
#endif
