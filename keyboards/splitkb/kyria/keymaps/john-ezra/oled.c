/* Copyright 2021 John Ezra
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

//Sets up what the OLED screens display.

#include QMK_KEYBOARD_H

int timer = 0;
char wpm_counter[5];
int x = 31;
int currwpm = 0;
int vert_count = 0;

//=============  USER CONFIG PARAMS  ===============
float max_wpm = 150.0f; //WPM value at the top of the graph window
int graph_refresh_interval = 80; //in milliseconds
int graph_area_fill_interval = 3; //determines how dense the horizontal lines under the graph line are; lower = more dense
int vert_interval = 3; //determines frequency of vertical lines under the graph line
bool vert_line = false; //determines whether to draw vertical lines
int graph_line_thickness = 2; //determines thickness of graph line in pixels
//=============  END USER PARAMS  ===============

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

void render_bootmagic_status(void) {
		oled_write_P((keymap_config.swap_lctl_lgui) ? PSTR("OS:    Windows\n\n") : PSTR("OS:    MacOS\n\n"), false);
		oled_write_P((keymap_config.nkro) ? PSTR("NKRO   ") : PSTR("       "), false);
}

void render_wpm(void) {
		//get current WPM value
		currwpm = get_current_wpm();
		//check if it's been long enough before refreshing graph
		if(timer_elapsed(timer) > graph_refresh_interval){
			// main calculation to plot graph line
			x = 64 - ((currwpm / max_wpm) * 64);
			//first draw actual value line
			for(int i = 0; i <= graph_line_thickness - 1; i++){
				oled_write_pixel(1, x + i, true);
			}
			//then fill in area below the value line
			if(vert_line){
				if(vert_count == vert_interval){
					vert_count = 0;
					while(x <= 64){
						oled_write_pixel(1, x, true);
						x++;
					}
				} else {
					for(int i = 64; i > x; i--){
						if(i % graph_area_fill_interval == 0){
							oled_write_pixel(1, i, true);
						}
					}
					vert_count++;
				}
			} else {
				for(int i = 64; i > x; i--){
					if(i % graph_area_fill_interval == 0){
						oled_write_pixel(1, i, true);
					}
				}
			}
			//then move the entire graph one pixel to the right
			oled_pan(false);
			//refresh the timer for the next iteration
			timer = timer_read();
		}
		//format current WPM value into a printable string
		char buf[4];
		oled_set_cursor(14, 0);
		oled_write("WPM:", false);
		buf[0] = currwpm >= 100 ? ((currwpm/100) + '0') : ' ';
		buf[1] = currwpm >= 10 ? (((currwpm/10) % 10) + '0') : ' ';
		buf[2] = (currwpm % 10) + '0';
		buf[3] = 0;
		oled_write(buf, false);
}

static void render_status(void) {
    // QMK Logo and version information
		render_qmk_logo();
    oled_write_P(PSTR("Kyria: Rev1.0\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case 4:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

		render_bootmagic_status();

// Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
				render_status();
    } else {
				render_wpm();
    }
}
#endif
