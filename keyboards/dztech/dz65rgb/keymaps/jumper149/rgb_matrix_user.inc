/* Copyright 2021 Felix Springer
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
RGB_MATRIX_EFFECT(base_effect)
RGB_MATRIX_EFFECT(base_ad_effect)
RGB_MATRIX_EFFECT(vi_effect)
RGB_MATRIX_EFFECT(fn_indicator)
RGB_MATRIX_EFFECT(kb_indicator)
RGB_MATRIX_EFFECT(kitt_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/*
[_LEDS]    = LAYOUT_65_ansi(
     0  ,            1  ,     2  ,     3  ,     4  ,     5  ,     6  ,     7  ,     8  ,     9  ,    10  ,    11  ,    12  ,    13  ,    14  ,
    15  ,           16 Q,    17 W,    18 E,    19 R,    20 T,    21 Y,    22 U,    23 I,    24 O,    25 P,    26  ,    27  ,    28  ,    29  ,
    30  ,           31 A,    32 S,    33 D,    34 F,    35 G,    36 H,    37 J,    38 K,    39 L,    40  ,    41  ,             42  ,    43  ,
    44  ,                    45 Z,    46 X,    47 C,    48 V,    49 B,    50 N,    51 M,    52  ,    53  ,    54  ,    55  ,    56  ,    57  ,
    58  ,           59  ,    60  ,                               61  ,                      62  ,    63  ,    64  ,    65  ,    66  ,    67
)
*/

// variable for startup animation
bool BASE_EFFECT_NOT_STARTED_YET = true;
uint8_t base_effect_startup_counter = 255;

static HSV base_effect_math(HSV hsv, uint8_t i, uint8_t time) {

    if (BASE_EFFECT_NOT_STARTED_YET) {
        base_effect_startup_counter = 0;
        BASE_EFFECT_NOT_STARTED_YET = false;
    }

    // startup animation
    if (base_effect_startup_counter < 255) {

        // jump to correct indices for alpha keys
        if (i == 0) { // only run for one key (key 0 is an arbitrary choice)
            if (base_effect_startup_counter == 0) {
                base_effect_startup_counter = 1;
            } else if (base_effect_startup_counter == 1) {
                base_effect_startup_counter = 17;
            } else if (base_effect_startup_counter == 26) {
                base_effect_startup_counter = 31;
            } else if (base_effect_startup_counter == 40) {
                base_effect_startup_counter = 45;
            } else if (base_effect_startup_counter == 52) {
                base_effect_startup_counter = 100;
            } else if (base_effect_startup_counter == 120) {
                base_effect_startup_counter = 255;
            } else {
                base_effect_startup_counter++;
            }
        }

        // overwrite some highlit keys
        if (3 + 39 - i < base_effect_startup_counter - 100 && i >= 36 && i <= 39) {
            hsv.s = hsv.s;
        } else if (3 + 39 - i < base_effect_startup_counter - 100 && i >= 31 && i <= 34) {
            hsv.s = hsv.s;
        // light up alpha keys
        } else if (i < base_effect_startup_counter && i >= 16 && i <= 25) {
            hsv.s = 0;
        } else if (31 + 39 - i < base_effect_startup_counter && i >= 31 && i <= 39) {
            hsv.s = 0;
        } else if (i < base_effect_startup_counter && i >= 45 && i <= 51) {
            hsv.s = 0;
        // light up number row
        } else if (12 + 1 - i < base_effect_startup_counter - 100 && i == 2) {
            hsv.s = 0;
            hsv.v = 1 * (hsv.v / 8);
        } else if (12 + 1 - i < base_effect_startup_counter - 100 && i == 3) {
            hsv.s = 0;
            hsv.v = 2 * (hsv.v / 8);
        } else if (12 + 1 - i < base_effect_startup_counter - 100 && i == 4) {
            hsv.s = 0;
            hsv.v = 3 * (hsv.v / 8);
        } else if (12 + 1 - i < base_effect_startup_counter - 100 && i >= 5 && i <= 8) {
            hsv.v = hsv.v;
        } else if (12 + 1 - i < base_effect_startup_counter - 100 && i == 9) {
            hsv.s = 0;
            hsv.v = 3 * (hsv.v / 8);
        } else if (12 + 1 - i < base_effect_startup_counter - 100 && i == 10) {
            hsv.s = 0;
            hsv.v = 2 * (hsv.v / 8);
        } else if (12 + 1 - i < base_effect_startup_counter - 100 && i == 11) {
            hsv.s = 0;
            hsv.v = 1 * (hsv.v / 8);
        // light up punctuation keys
        } else if (27 + 1 - i < base_effect_startup_counter - 100 && i >= 26 && i <= 27) {
            hsv.s = 0;
            hsv.v = hsv.v / 8;
        } else if (41 + 2 - i < base_effect_startup_counter - 100 && i >= 40 && i <= 41) {
            hsv.s = 0;
            hsv.v = hsv.v / 8;
        } else if (54 + 3 - i < base_effect_startup_counter - 100 && i >= 52 && i <= 54) {
            hsv.s = 0;
            hsv.v = hsv.v / 8;
        // rest
        } else {
            hsv.v = 0;
        }

    } else {

        switch (i) {

            // number row
            case 0:
                hsv.v = 0;
                break;
            case 1:
                hsv.v = 0;
                break;
            case 2:
                hsv.s = 0;
                hsv.v = 1 * (hsv.v / 8);
                break;
            case 3:
                hsv.s = 0;
                hsv.v = 2 * (hsv.v / 8);
                break;
            case 4:
                hsv.s = 0;
                hsv.v = 3 * (hsv.v / 8);
                break;
            case 5:
                hsv.v = hsv.v;
                break;
            case 6:
                hsv.v = hsv.v;
                break;
            case 7:
                hsv.v = hsv.v;
                break;
            case 8:
                hsv.v = hsv.v;
                break;
            case 9:
                hsv.s = 0;
                hsv.v = 3 * (hsv.v / 8);
                break;
            case 10:
                hsv.s = 0;
                hsv.v = 2 * (hsv.v / 8);
                break;
            case 11:
                hsv.s = 0;
                hsv.v = 1 * (hsv.v / 8);
                break;
            case 12:
                hsv.v = 0;
                break;

            // punctuation keys
            case 26:
                hsv.s = 0;
                hsv.v = hsv.v / 8;
                break;
            case 27:
                hsv.s = 0;
                hsv.v = hsv.v / 8;
                break;
            case 40:
                hsv.s = 0;
                hsv.v = hsv.v / 8;
                break;
            case 41:
                hsv.s = 0;
                hsv.v = hsv.v / 8;
                break;
            case 52:
                hsv.s = 0;
                hsv.v = hsv.v / 8;
                break;
            case 53:
                hsv.s = 0;
                hsv.v = hsv.v / 8;
                break;
            case 54:
                hsv.s = 0;
                hsv.v = hsv.v / 8;
                break;

            default:
                if (
                    (i > 15 && i <= 25) ||
                    (i > 30 && i <= 39) ||
                    (i > 44 && i <= 51)
                ) {
                    if (i > 35 && i <= 39) {
                        hsv.s = hsv.s;
                    } else if (i > 30 && i <= 34) {
                        hsv.s = hsv.s;
                    } else {
                        hsv.s = 0;
                    }
                } else {
                    hsv.v = 0;
                }
                break;

        }

    }

    return hsv;
}

bool base_effect(effect_params_t* params) {
    return effect_runner_i(params, &base_effect_math);
}

static HSV base_ad_effect_math(HSV hsv, uint8_t i, uint8_t time) {

    // no startup animation
    if (BASE_EFFECT_NOT_STARTED_YET) {
        base_effect_startup_counter = 255; // act like startup is already completed
        BASE_EFFECT_NOT_STARTED_YET = false;
    }

    switch (i) {

        // delete
        case 14:
            hsv.h = 0;
            hsv.s = 255;
            break;

        // insert
        case 29:
            hsv.h = 255/3;
            hsv.s = 255;
            break;

        // home
        case 43:
            hsv.s = 0;
            break;

        // end
        case 57:
            hsv.s = 255;
            break;

        default:
            hsv = base_effect_math(hsv, i, time);
            break;

    }

    return hsv;
}

bool base_ad_effect(effect_params_t* params) {
    return effect_runner_i(params, &base_ad_effect_math);
}

static HSV vi_effect_math(HSV hsv, uint8_t i, uint8_t time) {

    // no startup animation
    if (BASE_EFFECT_NOT_STARTED_YET) {
        base_effect_startup_counter = 255; // act like startup is already completed
        BASE_EFFECT_NOT_STARTED_YET = false;
    }

    switch (i) {

        // hjkl
        case 36:
            break;
        case 37:
            break;
        case 38:
            break;
        case 39:
            break;

        // page up
        case 22:
            hsv.s = 0;
            break;

        // page down
        case 33:
            hsv.s = 0;
            break;

        // find
        case 54:
            hsv.s = 0;
            break;

        default:
            hsv.v = 0;
            break;

    }

    return hsv;
}

bool vi_effect(effect_params_t* params) {
    return effect_runner_i(params, &vi_effect_math);
}

static HSV fn_indicator_math(HSV hsv, uint8_t i, uint8_t time) {

    // cancel base effect startup
    base_effect_startup_counter = 255;

    switch (i) {

        // F1 - F12
        case 1:
            hsv.h = 0 * 255 / 3;
            hsv.s = 255;
            break;
        case 2:
            hsv.h = 0 * 255 / 3;
            hsv.s = 255;
            break;
        case 3:
            hsv.h = 0 * 255 / 3;
            hsv.s = 255;
            break;
        case 4:
            hsv.h = 0 * 255 / 3;
            hsv.s = 255;
            break;
        case 5:
            hsv.h = 1 * 255 / 3;
            hsv.s = 255;
            break;
        case 6:
            hsv.h = 1 * 255 / 3;
            hsv.s = 255;
            break;
        case 7:
            hsv.h = 1 * 255 / 3;
            hsv.s = 255;
            break;
        case 8:
            hsv.h = 1 * 255 / 3;
            hsv.s = 255;
            break;
        case 9:
            hsv.h = 2 * 255 / 3;
            hsv.s = 255;
            break;
        case 10:
            hsv.h = 2 * 255 / 3;
            hsv.s = 255;
            break;
        case 11:
            hsv.h = 2 * 255 / 3;
            hsv.s = 255;
            break;
        case 12:
            hsv.h = 2 * 255 / 3;
            hsv.s = 255;
            break;

        // delete/insert
        case 13:
            hsv.h = 0;
            hsv.s = 255;
            break;
        case 14:
            hsv.h = 1 * (255 / 3);
            hsv.s = 255;
            break;

        // paste/copy/cut
        case 29:
            hsv.s = 0;
            break;
        case 43:
            hsv.h = 200;
            hsv.s = 255;
            break;
        case 57:
            hsv.h = 0;
            hsv.s = 255;
            break;

        // print/scroll/pause
        case 25:
            hsv.s = 0;
            break;
        case 26:
            hsv.s = 0;
            break;
        case 27:
            hsv.s = 0;
            break;

        // caps lock
        case 30:
            hsv.s = 0;
            break;

        // modifier
        case 44:
            hsv.s = 0;
            hsv.v = hsv.v / 2;
            break;
        case 55:
            hsv.s = 0;
            hsv.v = hsv.v / 2;
            break;
        case 58:
            hsv.s = 0;
            hsv.v = hsv.v / 2;
            break;
        case 59:
            hsv.s = 0;
            hsv.v = hsv.v / 2;
            break;
        case 60:
            hsv.s = 0;
            hsv.v = hsv.v / 2;
            break;
        case 64:
            hsv.s = 0;
            hsv.v = hsv.v / 2;
            break;

        // volume
        case 18: // mute
            hsv.h = 0;
            break;
        case 17: // increase
            hsv.s = 255;
            break;
        case 32: // decrease
            hsv.s = 0;
            break;

        // brightness
        case 33: // increase
            hsv.s = 255;
            break;
        case 31: // decrease
            hsv.s = 0;
            break;

        // media
        case 65: // previous
            hsv.s = 0;
            break;
        case 67: // next
            hsv.s = 0;
            break;
        case 56: // stop
            hsv.h = 0;
            break;
        case 66: // play/pause
            hsv.h = 255/3;
            break;

        // menu
        case 51:
            hsv.s = 0;
            break;

        // toggle AD layer
        case 36:
            hsv.h = 0;
            break;

        // toggle VI layer
        case 37:
            hsv.h = 255/3;
            break;

        // KB layer
        case 62:
            hsv.h = time;
            hsv.s = 255;
            break;

        // no function
        default:
            hsv.v = 0;
            break;

    }

    return hsv;
}

bool fn_indicator(effect_params_t* params) {
    return effect_runner_i(params, &fn_indicator_math);
}

static HSV kb_indicator_math(HSV hsv, uint8_t i, uint8_t time) {

    // cancel base effect startup
    base_effect_startup_counter = 255;

    switch (i) {

        // test HSV
        case 14:
            break;
        case 29:
            break;
        case 43:
            break;
        case 57:
            break;
        case 67:
            break;

        // toggle RGB
        case 16:
            hsv.s = 0;
            if (time < (255 / 2)) {
                hsv.v = 255;
            } else {
                hsv.v = 0;
            }
            break;

        // cycle effect
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

        // adjust hue
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

        // adjust saturation
        case 32:
            hsv.s = 255;
            hsv.v = 255;
            break;
        case 33:
            hsv.s = 0;
            hsv.v = 255;
            break;

        // adjust value
        case 45:
            hsv.v = 255;
            break;
        case 46:
            hsv.v = 63;
            break;

        // adjust speed
        case 4:
            if (((time / 8) % 2) == 0) {
                hsv.v = 255;
            } else {
                hsv.v = 63;
            }
            break;
        case 5:
            if (((time / 16) % 2) == 0) {
                hsv.v = 63;
            } else {
                hsv.v = 255;
            }
            break;

        // set main effect
        case 36: // BASE
            hsv.s = 0;
            break;
        case 37: // KITT
            hsv.h = 0;
            hsv.s = 255;
            if (time < 128) {
                hsv.v = time;
            } else {
                hsv.v = 255 - time;
            }
            break;

        // reset (for flashing)
        case 13:
            hsv.s = 0;
            if (time < 16) {
                hsv.v = 255 - time * 128 / 16;
            } else {
                hsv.v = 127;
            }
            break;

        // reset (reinitialize EEPROM)
        case 42:
            hsv.s = 0;
            hsv.v = 127;
            break;

        // shift
        case 44:
            hsv.s = 0;
            hsv.v = 63;
            break;
        case 55:
            hsv.s = 0;
            hsv.v = 63;
            break;

        // no function
        default:
            hsv.v = 0;

    }

    return hsv;
}

bool kb_indicator(effect_params_t* params) {
    return effect_runner_i(params, &kb_indicator_math);
}

uint8_t led_count = 7;
uint8_t led_first = 33;
static uint8_t time_to_led(uint8_t time, uint8_t led_behind) {
    uint16_t led_time = led_count * time;
    uint16_t step = ((2 * led_count + (led_time / 128)) - led_behind) % (2 * led_count);
    uint8_t led;
    if (step < led_count) {
        led = step;
    } else {
        led = led_count - 1 - (step - led_count);
    }
    return led;
}

static HSV kitt_effect_math(HSV hsv, uint8_t i, uint8_t time) {

    // reset base effect startup
    if (i == 0) {
        BASE_EFFECT_NOT_STARTED_YET = true;
    }

    hsv.h = 0;
    hsv.s = 255;

    if (i >= led_first && i < led_first + led_count) {
        uint8_t j = i - led_first;
        if (j == time_to_led(time, 0)) {
            hsv.v = hsv.v;
        } else if (j == time_to_led(time, 1)) {
            hsv.v = hsv.v/2;
        } else if (j == time_to_led(time, 2)) {
            hsv.v = hsv.v/4;
        } else if (j == time_to_led(time, 3)) {
            hsv.v = hsv.v/8;
        } else {
            hsv.v = 0;
        }
    } else {
        hsv.v = 0;
    }

    return hsv;
}

bool kitt_effect(effect_params_t* params) {
    return effect_runner_i(params, &kitt_effect_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// vim: syntax=c
