#include "rocket.h"

static void render_rocket(void) {
    char wpm = get_current_wpm();
    char render_row[128];
    int  i;
    oled_set_cursor(0, 0);
    for (i = 0; i < wpm / 4; i++) {
        render_row[i] = pgm_read_byte(space_row_1 + i + state);
    };
    for (i = wpm / 4; i < 128; i++) {
        render_row[i] = (pgm_read_byte(space_row_1 + i + state) & pgm_read_byte(mask_row_1 + i - wpm / 4)) | pgm_read_byte(ship_row_1 + i - wpm / 4);
    };

    oled_write_raw(render_row, 128);
    // oled_write_raw_P(space_row_1, 128);
    oled_set_cursor(0, 1);
    for (i = 0; i < wpm / 4; i++) {
        render_row[i] = pgm_read_byte(space_row_2 + i + state);
    };
    for (i = wpm / 4; i < 128; i++) {
        render_row[i] = (pgm_read_byte(space_row_2 + i + state) & pgm_read_byte(mask_row_2 + i - wpm / 4)) | pgm_read_byte(ship_row_2 + i - wpm / 4);
    };
    oled_write_raw(render_row, 128);
    oled_set_cursor(0, 2);
    for (i = 0; i < wpm / 4; i++) {
        render_row[i] = pgm_read_byte(space_row_3 + i + state);
    };
    for (i = wpm / 4; i < 128; i++) {
        render_row[i] = (pgm_read_byte(space_row_3 + i + state) & pgm_read_byte(mask_row_3 + i - wpm / 4)) | pgm_read_byte(ship_row_3 + i - wpm / 4);
    };

    oled_write_raw(render_row, 128);
    oled_set_cursor(0, 3);
    for (i = 0; i < wpm / 4; i++) {
        render_row[i] = pgm_read_byte(space_row_4 + i + state);
    };
    for (i = wpm / 4; i < 128; i++) {
        render_row[i] = (pgm_read_byte(space_row_4 + i + state) & pgm_read_byte(mask_row_4 + i - wpm / 4)) | pgm_read_byte(ship_row_4 + i - wpm / 4);
    };

    oled_write_raw(render_row, 128);

    state = (state + 1 + (wpm / 15)) % (128 * 2);
}
