RGB_MATRIX_EFFECT(fn_indicator)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV fn_indicator_math(HSV hsv, uint8_t i, uint8_t time) {

    /*
    [_LEDS]    = LAYOUT_65_ansi(
         0  ,            1  ,     2  ,     3  ,     4  ,     5  ,     6  ,     7  ,     8  ,     9  ,    10  ,    11  ,    12  ,    13  ,    14  ,
        15  ,           16 Q,    17 W,    18 E,    19 R,    20 T,    21 Y,    22 U,    23 I,    24 O,    25 P,    26  ,    27  ,    28  ,    29  ,
        30  ,           31 A,    32 S,    33 D,    34 F,    35 G,    36 H,    37 J,    38 K,    39 L,    40  ,    41  ,             42  ,    43  ,
        44  ,           45 Z,    46 X,    47 C,    48 V,    49 B,    50 N,    51 M,    52  ,    53  ,    54  ,    55  ,             56  ,    57  ,
        58  ,           59  ,    60  ,                               61  ,                      62  ,    63  ,    64  ,    65  ,    66  ,    67
    )
    */

    if (i > 14) {
        hsv.v = 0;
    }

    switch (i) {

        case 16:
            hsv.s = 0;
            if (time < (255 / 2)) {
                hsv.v = 255;
            } else {
                hsv.v = 0;
            }
            break;

        case 17:
            hsv.s = 255;
            hsv.v = 255;
            if (time < (255 / 3)) {
                hsv.h = 0;
            } else if (time < (2 * 255 / 3)) {
                hsv.h = 255 / 3;
            } else {
                hsv.h = 2 * 255 / 3;
            }
            break;

        case 18:
            hsv.h = time;
            hsv.s = 255;
            hsv.v = 255;
            break;

        case 19:
            hsv.h = 255 - time;
            hsv.s = 255;
            hsv.v = 255;
            break;

        case 20:
            hsv.s = time;
            hsv.v = 255;
            break;

        case 21:
            hsv.s = 255 - time;
            hsv.v = 255;
            break;

        case 22:
            hsv.s = 0;
            hsv.v = time;
            break;

        case 23:
            hsv.s = 0;
            hsv.v = 255 - time;
            break;
    }

    return hsv;
}

bool fn_indicator(effect_params_t* params) {
    return effect_runner_i(params, &fn_indicator_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
