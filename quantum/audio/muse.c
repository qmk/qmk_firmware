#include "muse.h"

#include <stdbool.h>

enum { MUSE_OFF, MUSE_ON, MUSE_C_1_2, MUSE_C1, MUSE_C2, MUSE_C4, MUSE_C8, MUSE_C3, MUSE_C6, MUSE_B1, MUSE_B2, MUSE_B3, MUSE_B4, MUSE_B5, MUSE_B6, MUSE_B7, MUSE_B8, MUSE_B9, MUSE_B10, MUSE_B11, MUSE_B12, MUSE_B13, MUSE_B14, MUSE_B15, MUSE_B16, MUSE_B17, MUSE_B18, MUSE_B19, MUSE_B20, MUSE_B21, MUSE_B22, MUSE_B23, MUSE_B24, MUSE_B25, MUSE_B26, MUSE_B27, MUSE_B28, MUSE_B29, MUSE_B30, MUSE_B31 };

bool number_of_ones_to_bool[16] = {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1};

uint8_t muse_interval[4] = {MUSE_B7, MUSE_B19, MUSE_B3, MUSE_B28};
uint8_t muse_theme[4]    = {MUSE_B8, MUSE_B23, MUSE_B18, MUSE_B17};

bool     muse_timer_1bit         = 0;
uint8_t  muse_timer_2bit         = 0;
uint8_t  muse_timer_2bit_counter = 0;
uint8_t  muse_timer_4bit         = 0;
uint32_t muse_timer_31bit        = 0;

bool bit_for_value(uint8_t value) {
    switch (value) {
        case MUSE_OFF:
            return 0;
        case MUSE_ON:
            return 1;
        case MUSE_C_1_2:
            return muse_timer_1bit;
        case MUSE_C1:
            return (muse_timer_4bit & 1);
        case MUSE_C2:
            return (muse_timer_4bit & 2);
        case MUSE_C4:
            return (muse_timer_4bit & 4);
        case MUSE_C8:
            return (muse_timer_4bit & 8);
        case MUSE_C3:
            return (muse_timer_2bit & 1);
        case MUSE_C6:
            return (muse_timer_2bit & 2);
        default:
            return muse_timer_31bit & (1UL << (value - MUSE_B1));
    }
}

uint8_t muse_clock_pulse(void) {
    bool top = number_of_ones_to_bool[bit_for_value(muse_theme[0]) + (bit_for_value(muse_theme[1]) << 1) + (bit_for_value(muse_theme[2]) << 2) + (bit_for_value(muse_theme[3]) << 3)];

    if (muse_timer_1bit == 0) {
        if (muse_timer_2bit_counter == 0) {
            muse_timer_2bit = (muse_timer_2bit + 1) % 4;
        }
        muse_timer_2bit_counter = (muse_timer_2bit_counter + 1) % 3;
        muse_timer_4bit         = (muse_timer_4bit + 1) % 16;
        muse_timer_31bit        = (muse_timer_31bit << 1) + top;
    }

    muse_timer_1bit = (muse_timer_1bit + 1) % 2;

    return bit_for_value(muse_interval[0]) + (bit_for_value(muse_interval[1]) << 1) + (bit_for_value(muse_interval[2]) << 2) + (bit_for_value(muse_interval[3]) << 3);
}
