#ifndef DISABLE_TERRAZZO_EFFECT_STRIPES
TERRAZZO_EFFECT(STRIPES)
#   ifdef TERRAZZO_EFFECT_IMPLS

void STRIPES(uint8_t i, bool dir) {
    uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60};
    uint8_t levels = 12;
    float soften = 5;

    for (int y = 0; y < LED_MATRIX_ROWS; y++) {
        for (int x  = 0; x < LED_MATRIX_COLS; x++) {
            uint8_t target = (x+y+i)%levels;
            terrazzo_set_pixel(x, y, floor(sweep[target] / soften));
        }
    }
}

#   endif
#endif