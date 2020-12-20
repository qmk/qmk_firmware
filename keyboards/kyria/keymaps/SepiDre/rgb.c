#include QMK_KEYBOARD_H

/*
1 = Static
2-5 = Breathing
6-8 = Rainbow
9-14 = Swirl
15-20 = Snake
21-24 = Nightrider
25 = Christmas   OFF
26-30 = Static Gradient
            Default HSV COLORS
            H= Farbe
            S= Weiß zu Farbe
            V= Schwarz zu Farbe

HSV_WHITE 0, 0, 255
HSV_RED 0, 255, 255
HSV_ORANGE 28, 255, 255
HSV_GOLDENROD 30, 218, 218
HSV_TURQUOISE 123, 90, 112
HSV_TEAL 128, 255, 128
HSV_CYAN 128, 255, 255
HSV_AZURE 132, 102, 255
HSV_PURPLE 191, 255, 255
*/

void matrix_init_user() {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
}

uint32_t layer_state_set_user(uint32_t state) {
    uint8_t layer = biton32(state);
    switch (get_highest_layer(default_layer_state)) {
        case _SHOOT:
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv(HSV_RED);
            break;
        default:
            switch (layer) {
                case _NEO2:
                    rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
                    rgblight_sethsv(15, 255, 255);
                    break;
                case _SYMBOLS:
                    rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                    rgblight_sethsv(HSV_RED);
                    break;
                case _NUMBER:
                    rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                    rgblight_sethsv(HSV_CYAN);
                    break;
                case _ADJUST:
                    rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                    rgblight_sethsv(HSV_PURPLE);
                    break;
                default:
                    break;
            }
            break;
    }
    return update_tri_layer_state(state, _NUMBER, _SYMBOLS, _ADJUST);
}
