extern uint8_t oled_buffer[OLED_MATRIX_SIZE];
extern OLED_BLOCK_TYPE oled_dirty;
#define OLED_ALL_BLOCKS_MASK (((((OLED_BLOCK_TYPE)1 << (OLED_BLOCK_COUNT - 1)) - 1) << 1) | 1)

// x range: 0..127
// y range: 0..7
void oled_pan_area(char start_x, char end_x, char start_y, char end_y, bool left) {
    uint16_t i = 0;
    for (uint16_t y = start_y; y <= end_y; y++) {
        if (left) {
            for (uint16_t x = start_x; x < end_x; x++) {
                i              = y * OLED_DISPLAY_WIDTH + x;
                oled_buffer[i] = oled_buffer[i + 1];
            }
        } else {
            for (uint16_t x = end_x; x > start_x; x--) {
                i              = y * OLED_DISPLAY_WIDTH + x;
                oled_buffer[i] = oled_buffer[i - 1];
            }
        }
    }
    oled_dirty = OLED_ALL_BLOCKS_MASK;
}

void draw_line_h(uint8_t x, uint8_t y, uint8_t len, bool on) {
    for (uint8_t i = 0; i < len; i++) {
        oled_write_pixel(i + x, y, on);
    }
}
void draw_line_v(uint8_t x, uint8_t y, uint8_t len, bool on) {
    for (uint8_t i = 0; i < len; i++) {
        oled_write_pixel(x, i + y, on);
    }
}
void draw_rect(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, bool on) {
    for (uint8_t i = 0; i < sizey; i++) {
        draw_line_h(x, y+i, sizex, on);
    }
}
