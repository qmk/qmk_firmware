/* Copyright 2021 dogspace <https://github.com/dogspace>
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

#include QMK_KEYBOARD_H

enum layer_names {
    _LAY0,
    _LAY1,
    _LAY2,
    _LAY3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAY0] = LAYOUT(
                            KC_PSLS, KC_PAST, KC_PMNS, 
    KC_VOLD, KC_VOLU, KC_P7, KC_P8,   KC_P9,   KC_PPLS, 
    KC_TRNS, KC_TRNS, KC_P4, KC_P5,   KC_P6,   KC_PPLS, 
    KC_TRNS, KC_TRNS, KC_P1, KC_P2,   KC_P3,   KC_PENT, 
    KC_TRNS, KC_TRNS, KC_P0, KC_P0,   KC_PDOT, KC_PENT  
    ),

    [_LAY1] = LAYOUT(
                    ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___  
    ),

    [_LAY2] = LAYOUT(
                    ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___
    ),

    [_LAY3] = LAYOUT(
                    ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___
    ),
};

#ifdef OLED_ENABLE
/*===========================================    OLED CONFIGURATION    ===========================================*/
#define OLED_ROTATE      true         // OLED rotation (flip 180* from default orientation)
#define GRAPH_DIRECTION  true         // Graph movement  (true = right to left,  false = left to right)
#define GRAPH_TOP_WPM    100.0        // Minimum WPM required to reach the top of the graph
#define GRAPH_REFRESH    1000         // In milliseconds, determines the graph-line frequency
#define ICON_MED_WPM     10           // WPM required to display the medium snail
#define ICON_FAST_WPM    25           // WPM required to display the fast snail

// Layer names:  Should be exactly 5 characters in length if vertical display, or 6 characters if horizontal
#define MA_LAYER_NAME     "LAY 0"      // Layer _MA name
#define L1_LAYER_NAME     "LAY 1"      // Layer _L1 name
#define L2_LAYER_NAME     "LAY 2"      // Layer _L2 name
#define L3_LAYER_NAME     "LAY 3"      // Layer _L3 name

#define CAPLCK_STR        "CAPLK"       // Caps Lock string
#define NUMLCK_STR        "NUMLK"       // Num Lock string
#define SCRLK_STR         "SCRLK"       // Scroll Lock string
#define EMPTY_STR         "     "       // Empty string

/*================================================================================================================*/

typedef struct oled_params {
    bool first_loop : 1;
    uint8_t wpm_icon : 7;
    uint16_t timer;
    uint8_t wpm_limit;
    uint8_t max_wpm;
    uint8_t graph_lines[32];
} oled_params;

oled_params oled_data;

void oled_init_data(void) {
    // Initialize oled params
    oled_data.first_loop = true;
    oled_data.wpm_icon = 5;
    oled_data.timer = 0;
    oled_data.wpm_limit = 20;
    oled_data.max_wpm = 0;

    for (int i=0; i<32; i++) {
        oled_data.graph_lines[i] = 0;
    }
}

// Set OLED rotation
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_init_data();
    return OLED_ROTATE ? OLED_ROTATION_270 : OLED_ROTATION_90;
}

// Draw static background image to OLED (keyboard with no bottom row)
static void render_background(void) {
    static const char PROGMEM nullbits_n_oled[] = {
        0x00, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0x80, 0x20, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 
        0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
        0x1f, 0x1f, 0x1f, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf0, 0x00, 0x00, 
        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 
        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
        0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
        0x00, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x00, 
    };
    oled_write_raw_P(nullbits_n_oled, sizeof(nullbits_n_oled));
}

// Toggles pixel on/off, converts horizontal coordinates to vertical equivalent if necessary
static void write_pixel(uint8_t x, uint8_t y, bool onoff) {
    oled_write_pixel(y, 127 - x, onoff);
}

// Write active layer name
static void render_layer_state(void) {
  oled_set_cursor(0, 15);
  switch (get_highest_layer(layer_state)) {
  case _LAY0:
      oled_write_P(PSTR(MA_LAYER_NAME), false);
      break;
  case _LAY1:
      oled_write_P(PSTR(L1_LAYER_NAME), false);
      break;
  case _LAY2:
      oled_write_P(PSTR(L2_LAYER_NAME), false);
      break;
  case _LAY3:
      oled_write_P(PSTR(L3_LAYER_NAME), false);
      break;
  default:
      oled_write("ERROR", false);
      break;
  }
}

// Update WPM counters
static void render_wpm_counters(uint8_t current_wpm) {
    uint8_t cursorposition_cur = 13;
    uint8_t cursorposition_max = 14;

    oled_set_cursor(0, cursorposition_cur);
    oled_write(get_u8_str(current_wpm, '0'), false);

    if (current_wpm > oled_data.max_wpm) {
        oled_data.max_wpm = current_wpm;
        oled_data.wpm_limit = oled_data.max_wpm + 20;
        oled_set_cursor(0, cursorposition_max);
        oled_write(get_u8_str(current_wpm, '0'), false);
    }
}

static void render_led_status(void) {
    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_set_cursor(0, 8);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR(CAPLCK_STR) : PSTR(EMPTY_STR), false);
    oled_set_cursor(0, 9);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR(NUMLCK_STR) : PSTR(EMPTY_STR), false);
    oled_set_cursor(0, 10);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR(SCRLK_STR) : PSTR(EMPTY_STR), false);
}

// Update WPM snail icon
static void render_wpm_icon(uint8_t current_wpm) {
    // wpm_icon is used to prevent unnecessary redraw
    if ((current_wpm < ICON_MED_WPM) && (oled_data.wpm_icon != 0)) {
        oled_data.wpm_icon = 0;
    } else if ((current_wpm >= ICON_MED_WPM) && (current_wpm < ICON_FAST_WPM) && (oled_data.wpm_icon != 1)) {
        oled_data.wpm_icon = 1;
    } else if ((current_wpm >= ICON_FAST_WPM) && (oled_data.wpm_icon != 2)) {
        oled_data.wpm_icon = 2;
    } else {
        return;
    }
    static const char PROGMEM snails[][2][24] = {
        {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0xA0, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x50, 0x88, 0x04, 0x00, 0x00},
         {0x40, 0x60, 0x50, 0x4E, 0x51, 0x64, 0x4A, 0x51, 0x54, 0x49, 0x41, 0x62, 0x54, 0x49, 0x46, 0x41, 0x40, 0x30, 0x09, 0x04, 0x02, 0x01, 0x00, 0x00}},
        {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x04, 0x98, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00},
         {0x60, 0x50, 0x54, 0x4A, 0x51, 0x64, 0x4A, 0x51, 0x55, 0x49, 0x41, 0x62, 0x54, 0x49, 0x46, 0x41, 0x21, 0x10, 0x0A, 0x08, 0x05, 0x02, 0x00, 0x00}},
        {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x10, 0x10, 0x10, 0x20, 0x40, 0x40, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00},
         {0x60, 0x58, 0x54, 0x62, 0x49, 0x54, 0x52, 0x51, 0x55, 0x49, 0x62, 0x52, 0x4D, 0x45, 0x46, 0x22, 0x21, 0x11, 0x10, 0x0A, 0x08, 0x05, 0x02, 0x00}}
    };
    oled_set_cursor(0, 11);
    oled_write_raw_P(snails[oled_data.wpm_icon][0], sizeof(snails[oled_data.wpm_icon][0]));
    oled_set_cursor(0, 12);
    oled_write_raw_P(snails[oled_data.wpm_icon][1], sizeof(snails[oled_data.wpm_icon][1]));
}

// Update WPM graph
static void render_wpm_graph(uint8_t current_wpm) {
    uint8_t line_height = ((current_wpm / GRAPH_TOP_WPM) * 7);
    if (line_height > 7) {
        line_height = 7;
    }
    // Count graph line pixels, return if nothing to draw
    uint8_t pixel_count = line_height;
    for (int i = 0; i < 31; i++) {
        pixel_count += oled_data.graph_lines[i];
    }
    if (pixel_count == 0) {
        return;
    }
    // Shift array elements left or right depending on GRAPH_DIRECTION pend new graph line
    if (GRAPH_DIRECTION) {
        for (int i = 0; i < 31; i++) {
            oled_data.graph_lines[i] = oled_data.graph_lines[i + 1];
        }
        oled_data.graph_lines[31] = line_height;
    } else {
        for (int i = 31; i > 0; i--) {
            oled_data.graph_lines[i] = oled_data.graph_lines[i - 1];
        }
        oled_data.graph_lines[0] = line_height;
    }
    // Draw all graph lines (left to right, bottom to top)
    uint16_t draw_count, arrpos;
    for (int x = 1; x <= 63; x += 2) {
        arrpos = x / 2;
        draw_count = oled_data.graph_lines[arrpos];
        for (int y = 31; y >= 25; y--) {
            if (draw_count > 0) {
                write_pixel(x, y, true);
                draw_count--;
            } else {
                write_pixel(x, y, false);
            }
        }
    }
}

// Call OLED functions
bool oled_task_user(void) {
    // Draw OLED keyboard, prevent redraw
    if (oled_data.first_loop) {
        render_background();
        oled_data.first_loop = false;
    }
    // Get current WPM, subtract 25% for accuracy and prevent large jumps caused by simultaneous keypresses
    uint8_t current_wpm = get_current_wpm();
    // Write active layer name to display
    render_layer_state();
    // Update WPM counters
    render_wpm_counters(current_wpm);
    // Update WPM snail icon
    render_wpm_icon(current_wpm);
    // Update LED status
    render_led_status();
    // Update WPM graph every graph_refresh milliseconds
    if (timer_elapsed(oled_data.timer) > GRAPH_REFRESH) {
        render_wpm_graph(current_wpm);
        oled_data.timer = timer_read();
    }
    return false;
}
#endif

bool wpm_keycode_user(uint16_t keycode) {
    // Count all keycodes on the macropad
    return true;
}

