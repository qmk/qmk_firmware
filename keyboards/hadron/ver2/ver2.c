#include "ver2.h"

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oled_write_P(PSTR("LAYER "), false);
    oled_write_char(get_highest_layer(layer_state) + 0x30, true);

    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(18, 0);
    oled_write_P(PSTR("NUM"), led_state.num_lock);
    oled_set_cursor(18, 1);
    oled_write_P(PSTR("CAP"), led_state.caps_lock);
    oled_set_cursor(18, 2);
    oled_write_P(PSTR("SCR"), led_state.scroll_lock);

    uint8_t mod_state = get_mods();
    oled_set_cursor(10, 3);
    oled_write_P(PSTR("S"), mod_state & MOD_MASK_SHIFT);
    oled_advance_char();
    oled_write_P(PSTR("C"), mod_state & MOD_MASK_CTRL);
    oled_advance_char();
    oled_write_P(PSTR("A"), mod_state & MOD_MASK_ALT);
    oled_advance_char();
    oled_write_P(PSTR("G"), mod_state & MOD_MASK_GUI);
    oled_advance_char();

/* Matrix display is 12 x 12 pixels */
#define MATRIX_DISPLAY_X 5
#define MATRIX_DISPLAY_Y 18

    // matrix
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        for (uint8_t y = 0; y < MATRIX_COLS; y++) {
            bool on = (matrix_get_row(x) & (1 << y)) > 0;
            oled_write_pixel(MATRIX_DISPLAY_X + y + 2, MATRIX_DISPLAY_Y + x + 2, on);
        }
    }

    // outline
    for (uint8_t x = 0; x < 19; x++) {
        oled_write_pixel(MATRIX_DISPLAY_X + x, MATRIX_DISPLAY_Y, true);
        oled_write_pixel(MATRIX_DISPLAY_X + x, MATRIX_DISPLAY_Y + 9, true);
    }
    for (uint8_t y = 0; y < 9; y++) {
        oled_write_pixel(MATRIX_DISPLAY_X, MATRIX_DISPLAY_Y+y, true);
        oled_write_pixel(MATRIX_DISPLAY_X + 19, MATRIX_DISPLAY_Y+y, true);
    }

    // oled location
    for (uint8_t x = 0; x < 3; x++) {
        oled_write_pixel(MATRIX_DISPLAY_X + 14 + x, MATRIX_DISPLAY_Y + 2, true);
    }

    // bodge for layer number left hand side
    for (uint8_t y = 0; y < 8; y++) {
        oled_write_pixel(35, 0 + y, true);
    }
    return false;
}
#endif
