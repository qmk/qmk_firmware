/* Copyright 2021 HorrorTroll <https://github.com/HorrorTroll>
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

extern const unsigned char font[] PROGMEM;

#define ROW_1 OLED_DISPLAY_WIDTH
#define ROW_2 (OLED_DISPLAY_WIDTH * 2)

static uint32_t wave_sleep = 0;

#define FRAME_TIMEOUT (1000/24)

static uint16_t wave_timer = 0;

static uint8_t next_bar_val = 0;
static uint8_t next_log_byte[OLED_FONT_WIDTH] = {0};
static uint8_t line1[OLED_DISPLAY_WIDTH] = {0};
static uint8_t line2[OLED_DISPLAY_WIDTH] = {0};

static const uint8_t PROGMEM bar_lut[8] = {0, 16, 24, 56, 60, 124, 126, 255};

#define BAR_KEY_WEIGHT 128
#define BAR_KEY_DECAY_MAX 18

static uint8_t bar_key_decay = BAR_KEY_DECAY_MAX;

// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',  // 0x
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0', 128, 136, 132, 131,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 130,   7,   7,   7,   7,   7,   7,  // 3x
      7,   7,   7,   7,   7,   7, 137, 138, 139, 140, 141,  30, 143, 142,  31,  26,  // 4x
     27,  25,  24, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', 135, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
     15, 129, 133,   4,  15, 129, 133, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};
// clang-format on

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP   && keycode <= QK_MOD_TAP_MAX)   ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) ||
        (keycode >= QK_MODS      && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        char log_char = pgm_read_byte(&code_to_name[keycode]);

        for (uint8_t j = 0; j < OLED_FONT_WIDTH; j++) {
            const uint8_t glyph_line = pgm_read_byte(&font[log_char * OLED_FONT_WIDTH + j]);
            next_log_byte[j] = glyph_line;
        }
    }
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        wave_sleep = timer_read32();
        add_keylog(keycode);

        uint8_t t = next_bar_val + BAR_KEY_WEIGHT;

        if (t < next_bar_val) {
            next_bar_val = 255;
        } else {
            next_bar_val = t;
        }

        bar_key_decay = BAR_KEY_DECAY_MAX;
    }

    return true;
}

void render_layer_name(void) {
    oled_write_P(PSTR("LAYER: WAVE"), false);
}

void render_frame(void) {
    // rotate line 1, and stick in the next byte of the next char,
    // then rotate the next char buffer
    memmove(line1+1, line1, OLED_DISPLAY_WIDTH - 1);
    line1[0] = next_log_byte[OLED_FONT_WIDTH - 1];
    memmove(next_log_byte+1, next_log_byte, OLED_FONT_WIDTH - 1);
    next_log_byte[0] = 0;

    // rotate line 2, sticking in the next display value
    uint8_t disp_val = pgm_read_byte(&bar_lut[next_bar_val / 32]);
    memmove(line2+1, line2, OLED_DISPLAY_WIDTH - 1);
    line2[0] = disp_val;

    // draw both bars
    for (uint8_t i = 0; i < OLED_DISPLAY_WIDTH; i++) {
        oled_write_raw_byte(line1[i], ROW_1 + i);
        oled_write_raw_byte(line2[i], ROW_2 + i);
    }

    // decay the next bar value
    if (next_bar_val > bar_key_decay) {
        next_bar_val -= bar_key_decay;
    } else {
        next_bar_val = 0;
    }

    if (bar_key_decay > 1) {
        bar_key_decay -= 1;
    }
}
