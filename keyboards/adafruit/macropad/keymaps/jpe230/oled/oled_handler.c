/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#include "keymap.h"

__attribute__ ((weak)) void render_lockscreen(){}
__attribute__ ((weak)) void render_authenticator(int layer){}

uint8_t oled_state = DEFAULT_OLED;

bool indicator_oled_state[MATRIX_ROWS][MATRIX_COLS] = {
    { false, false, false },
    { false, false, false },
    { false, false, false },
    { false, false, false },
    { false, false, false }
};

const char* PROGMEM layer_strings[] = {
    TRANS_LAYER_STRINGS
};

const char PROGMEM *key_strings[][MATRIX_ROWS][MATRIX_COLS] = {
    TRANS_KEYMAP_STRINGS
};

void center_text(const char *text, char *output, int width) {
    /* If string is bigger than the available width, trim it */
    if(strlen(text) > width){
        memcpy(output, text, width);
        return;
    }

    /* Try to center the TEXT, TODO: Handle Even lengths*/
    int padlen_l = (width - strlen(text)) / 2;
    int padlen_r = (padlen_l * 2) + strlen(text) == width ? padlen_l : padlen_l + 1;
    sprintf(output, "%*s%s%*s", padlen_l, "", text, padlen_r, "");
}

void render_layer_indicators(int layer) {
   
    /* Print Time */
    ds3231_time_t t;
    ds3231_get_time(&t);
    
    //dd/mm/yyyy hh:mm:ss
    char current_time[27] = {0};
    sprintf(current_time, "%02d/%02d/%04d %02d:%02d:%02d", t.month, t.date, t.year, t.hour, t.minute, t.second);
    char time_text[21];
    center_text(current_time, time_text, CHARS_PER_LINE);
    oled_write((const char*)time_text, true);

     /* Print Title */
    char title[CHARS_PER_LINE];
    center_text(layer_strings[layer], title, CHARS_PER_LINE);
    oled_write_ln((const char *)title, true);

    /* Print Keys */
    for(uint8_t row = 1; row < MATRIX_ROWS; row++)
    {
        for(uint8_t col = 0; col < MATRIX_COLS; col++)
        {
            char name[CHARS_PER_KEY];
            center_text(key_strings[layer][row][col], name, CHARS_PER_KEY);
            bool invert = key_strings[layer][row][col][0] != '\0' && indicator_oled_state[row][col];
            oled_write((const char*)name, invert);
        }
    }

    /* Empty Line */
    oled_write_ln("", false);
}

void render_layer(void){
    /* Get the active layer */
    int layer_idx = get_highest_layer(layer_state|default_layer_state);

    switch(layer_idx)
    {
        case (TRANS_LAYER_NO - 1):
            render_logo();
            return;
        #ifndef DISABLE_SECRETS
        case (TOTP_LAYER - 1):
            render_lockscreen();
            return;
        case TOTP_LAYER:
            render_authenticator(layer_idx);
            return;
        #endif
        default:
            /* Render the indicators */
            render_layer_indicators(layer_idx);
    }
}

bool oled_task_user(void) {
    /* Decay each frame */
    fake_wpm_decay();

    switch (oled_state)
    {
    case DEFAULT_OLED:
        render_layer();
        break;

    case BONGO_CAT:
        render_bongo_cat();
        break;

    case LOGO:
        render_logo();
        break;

    default:
        break;
    }

    return true;
}

/* Fake WPM */
static uint8_t current_wpm = 0;
static uint8_t decay_calls = 0;

void fake_wpm_increment(void)
{
    if (current_wpm + increment_amount >= 255)
        current_wpm = 255;
    else
        current_wpm += increment_amount;
}

void fake_wpm_decay(void)
{
    if (decay_calls == 0)
    {
        if (!current_wpm == 0){
            current_wpm --;
        }
        else
            return;
    }

    if (decay_calls > decay_every_x)
        decay_calls = 0;
    else
        decay_calls ++;
}

uint8_t get_current_wpm(void)
{
    return current_wpm;
}