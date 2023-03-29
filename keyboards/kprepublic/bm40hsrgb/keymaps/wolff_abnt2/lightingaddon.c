
//Number of layers with custom matrix lighting
#define ILLUM_LAYERS 1

uint8_t led_colors[ILLUM_LAYERS][MATRIX_COLS*MATRIX_ROWS*3] = {
    //Available colors: BLACK (off), WHITE, RED, CORAL, ORANGE, GOLDENROD, GOLD, YELLOW, CHARTREUSE, GREEN, SPRINGGREEN, TURQUOISE, TEAL, CYAN, AZURE, BLUE, PURPLE, MAGENTA, PINK.
    //_NAV
    {
    RGB_BLACK, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE,
    RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE,
    RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE,
    RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE,       RGB_WHITE,      RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE
    }
};


void set_leds(int led_layer) {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    for (int i = 0; i < MATRIX_ROWS*MATRIX_COLS; i++) {
        red = led_colors[led_layer][i*3];
        green = led_colors[led_layer][i*3+1];
        blue = led_colors[led_layer][i*3+2];
        rgb_matrix_set_color(i, red, green, blue);
    }
}

void rgb_matrix_indicators_kb(void) {
    switch(get_highest_layer(layer_state)) {
//             case _SYM:
//                 set_leds(0);
//                 break;
//             case _ADJUST:
//                 set_leds(0);
//                 break;
//             case _CPY:
//                 set_leds(0);
//                 break;
            case _NAV:
                set_leds(0);
                break;
            default:
                break;
    }

}
