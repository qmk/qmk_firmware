/* Copyright 2021 JasonRen(biu)
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
#include "wpm_graph.h"
// #include "print.h"


const uint8_t single_bit_masks[] = {0, 128, 192, 224, 240, 248, 252, 254, 255};
const uint8_t max_wpm = 160;
const uint8_t max_wpm_byte_bar_height = 5; // 5*8 = 40 bit
const uint8_t wpm_graph_start_line = 11;
const uint16_t show_count_time = 60000;
uint16_t wpm_graph_timer_update = 0;
uint16_t wpm_graph_timer_countdown = 0;
bool countdown_over = false;
bool first_startup = true;

void draw_y_grad(uint8_t x, uint8_t y, bool inside) {
    uint16_t start_index = (y * OLED_DISPLAY_WIDTH) + (x*8);
    oled_buffer_reader_t reader;
    if (inside) {
	start_index += 2;
        for (uint8_t i=0; i < 4; i++)
	    oled_write_raw_byte(60, start_index + i);
    } else {
        reader = oled_read_raw(start_index);
	for (uint8_t i=0; i < 8; i++) {
	    if (i > 1 && i < 6)
		oled_write_raw_byte((*reader.current_element)++ | 129, start_index + i); // 129 = 0b1000 0001
	    else
		oled_write_raw_byte(255, start_index + i);
	}
    }
}

void render_wpm_graph(uint16_t wpm) {
    // init
    if (first_startup) {
        render_r65_logo();
    }
    if (wpm_graph_timer_countdown == 0) {
        wpm_graph_timer_countdown = timer_read();
    }
    if (wpm_graph_timer_update == 0) {
        wpm_graph_timer_update = timer_read();
        return;
    }

    // 2 frame
    if (timer_elapsed(wpm_graph_timer_update) < 500) return;
	wpm_graph_timer_update = timer_read();

    // global var for this function
    static uint8_t zero_bar_count = 0;
    static uint8_t bar_count = 0;

    uint8_t bar_height = 0;
    uint8_t bar_segment = 0;


	bar_height = wpm;
	if(bar_height > max_wpm) {
		bar_height = max_wpm;
    }

    if(bar_height == 0) {
	    // keep track of how many zero bars we have drawn.  If
	    // there is a whole screen worth, turn the display off and
	    // wait until there is something to do
        // uprintf("zero %u\n", zero_bar_count);
        if (first_startup) return;

	    if (zero_bar_count > 32) {
            // do some thing when not typing
            if (timer_elapsed(wpm_graph_timer_countdown) <= show_count_time+1 && !countdown_over) {
                render_countdown();
            } else {
                countdown_over = true;
                render_yandr_logo();
                // oled_off();
            }
            return;
	    }
	    zero_bar_count++;
        wpm_graph_timer_countdown = timer_read();
        countdown_over = false;
	} else {
        first_startup = false;
	    zero_bar_count=0;
    }
	bar_count++;

    // scale the ture wpm to fit the bar height
    uint8_t scale_rate = max_wpm/(max_wpm_byte_bar_height*8);
    bar_height = bar_height / scale_rate;

    // wpm history bar move one step to right
	// oled_precise_pan(false, wpm_graph_start_line*32);
    if (!first_startup) {
        oled_precise_pan_h(false, (uint16_t)wpm_graph_start_line);
    } else {
        return;
    }
	// oled_pan(false);


	for (uint8_t i = max_wpm_byte_bar_height; i >0; i--) {
	    if (bar_height > 8) {
            bar_segment = 255;
            bar_height -= 8;
	    } else {
            bar_segment = single_bit_masks[bar_height];
            bar_height = 0;
        }
        // uprintf("max%u",max_wpm_byte_bar_height);
	    oled_write_raw_byte(bar_segment, (uint16_t)((i - 1 + wpm_graph_start_line) * 32));
	}
}



void render_countdown(void) {
    uint16_t pass_time_mm = timer_elapsed(wpm_graph_timer_countdown);
    // second
    uint16_t pass_time_s = show_count_time/1000 - pass_time_mm / 1000;

    oled_set_cursor(0, wpm_graph_start_line+1);
    if (pass_time_s < 10) {
        // 0
        oled_set_cursor(0, wpm_graph_start_line+1);
        oled_write_raw(my_font_lib_etc_countdown[0], 16);
        oled_set_cursor(0, wpm_graph_start_line+2);
        oled_write_raw(my_font_lib_etc_countdown[0]+16, 16);
        oled_set_cursor(0, wpm_graph_start_line+3);
        oled_write_raw(my_font_lib_etc_countdown[0]+32, 16);

        // pass_time_s
        oled_set_precise_cursor((wpm_graph_start_line+1)*32 + 16);
        oled_write_raw(my_font_lib_etc_countdown[pass_time_s], 16);
        oled_set_precise_cursor((wpm_graph_start_line+2)*32 + 16);
        oled_write_raw(my_font_lib_etc_countdown[pass_time_s]+16, 16);
        oled_set_precise_cursor((wpm_graph_start_line+3)*32 + 16);
        oled_write_raw(my_font_lib_etc_countdown[pass_time_s]+32, 16);
    } else {
        uint16_t pass_time_s_h = pass_time_s / 10;
        uint16_t pass_time_s_l =  pass_time_s % 10;
        // heigh bit
        oled_set_cursor(0, wpm_graph_start_line+1);
        oled_write_raw(my_font_lib_etc_countdown[pass_time_s_h], 16);
        oled_set_cursor(0, wpm_graph_start_line+2);
        oled_write_raw(my_font_lib_etc_countdown[pass_time_s_h]+16, 16);
        oled_set_cursor(0, wpm_graph_start_line+3);
        oled_write_raw(my_font_lib_etc_countdown[pass_time_s_h]+32, 16);

        // low bit
        oled_set_precise_cursor((wpm_graph_start_line+1)*32 + 16);
        oled_write_raw(my_font_lib_etc_countdown[pass_time_s_l], 16);
        oled_set_precise_cursor((wpm_graph_start_line+2)*32 + 16);
        oled_write_raw(my_font_lib_etc_countdown[pass_time_s_l]+16, 16);
        oled_set_precise_cursor((wpm_graph_start_line+3)*32 + 16);
        oled_write_raw(my_font_lib_etc_countdown[pass_time_s_l]+32, 16);
    }
    oled_set_cursor(0, wpm_graph_start_line+4);
}



void render_yandr_logo() {
    oled_set_cursor(0, wpm_graph_start_line+1);
    oled_write_raw(my_font_lib_etc_logo, 32);
    oled_set_cursor(0, wpm_graph_start_line+2);
    oled_write_raw(my_font_lib_etc_logo+32, 32);
    oled_set_cursor(0, wpm_graph_start_line+3);
    oled_write_raw(my_font_lib_etc_logo+64, 32);
    oled_set_cursor(0,0);
}

void render_r65_logo() {
    oled_set_cursor(0, wpm_graph_start_line+1);
    oled_write_raw(my_font_lib_etc_r65_logo, 32);
    oled_set_cursor(0, wpm_graph_start_line+2);
    oled_write_raw(my_font_lib_etc_r65_logo+32, 32);
    oled_set_cursor(0, wpm_graph_start_line+3);
    oled_write_raw(my_font_lib_etc_r65_logo+64, 32);
    oled_set_cursor(0,0);
}
