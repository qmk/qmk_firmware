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
   KC_KP_1, KC_KP_2, KC_KP_3,       KC_AUDIO_VOL_UP,
   KC_KP_0, RGB_TOG, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN
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
#define ANIM_FRAME_DURATION 200 // Number of milliseconds per frame

uint32_t anim_timer = 0;
uint8_t current_frame = 0;
uint8_t rocket_rendered = 0;

static void render_exhaust(uint8_t startX, uint8_t startY, uint8_t phase)
{
    oled_set_cursor(startX, startY);
    oled_write_char(0x85 + (phase % 3), false);
    phase++;
    oled_write_char(0x85 + (phase % 3), false);
    phase++;
    oled_write_char(0x85 + (phase % 3), false);
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
    if(!rocket_rendered)
    {
        render_logo(9, 3); // Render the rocket
        rocket_rendered++;
    }

    if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION)
    {
        anim_timer = timer_read32();
        current_frame = (current_frame + 1) % ANIM_FRAMES;
        render_exhaust(6, 4, current_frame);
    }
}
#endif
