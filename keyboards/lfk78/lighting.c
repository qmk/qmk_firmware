#ifdef ISSI_ENABLE

#include "lfk78.h"
#include "issi.h"
#include <avr/sfr_defs.h>
#include "audio/audio.h"
#include "TWIlib.h"
#include "avr/timer_avr.h"
#include "lighting.h"

/* RGB Map:
    12  11  10   9  16  32  31  15  30  28
13                                          25
14                                          24
 8                                          22
 7                                          21
     6   5   4   3   2   1  17  18  19  20
*/
const uint8_t rgb_sequence[] = {
    12, 11, 10, 9, 16, 32, 31, 15, 30, 28, 25, 24, 22, 21,
    20, 19, 18, 17, 1, 2, 3, 4, 5, 6, 7, 8, 14, 13
};

const uint8_t rgb_leds[][3][2] = {
        {{0, 0}, {0, 0}, {0, 0}},
        {{1, 1}, {2, 3}, {2, 4}},   // RGB1/RGB17
        {{2, 1}, {2, 2}, {3, 4}},   // RGB2/RGB18
        {{3, 1}, {3, 2}, {3, 3}},   // RGB3/RGB19
        {{4, 1}, {4, 2}, {4, 3}},   // RGB4/RGB20
        {{5, 1}, {5, 2}, {5, 3}},   // RGB5/RGB21
        {{6, 1}, {6, 2}, {6, 3}},   // RGB6/RGB22
        {{7, 1}, {7, 2}, {7, 3}},   // RGB6/RGB23
        {{8, 1}, {8, 2}, {8, 3}},   // RGB8/RGB24
        {{1, 9}, {1, 8}, {1, 7}},   // RGB9/RGB25
        {{2, 9}, {2, 8}, {2, 7}},   // RGB10/RGB26
        {{3, 9}, {3, 8}, {3, 7}},   // RGB11/RGB27
        {{4, 9}, {4, 8}, {4, 7}},   // RGB12/RGB28
        {{5, 9}, {5, 8}, {5, 7}},   // RGB13/RGB29
        {{6, 9}, {6, 8}, {6, 7}},   // RGB14/RGB30
        {{7, 9}, {7, 8}, {6, 6}},   // RGB15/RGB31
        {{8, 9}, {7, 7}, {7, 6}}    // RGB16/RGB32
    };

/*
    Maps switch LEDs from Row/Col to ISSI matrix.
    Value breakdown:
        Bit     | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
                |  ISSI Column  |   | ISSI Row  |
                                /   \
                                Device
*/
const uint8_t switch_leds[MATRIX_ROWS][MATRIX_COLS] =
KEYMAP(
  0x91, 0x81,   0x71, 0x61, 0x51, 0x41, 0x31, 0x21, 0x11, 0x99, 0x89, 0x79, 0x69, 0x59, 0x49,   0x39,   0x29, 0x19,
  0x92, 0x82,    0x72,  0x62, 0x52, 0x42, 0x32, 0x22, 0x12, 0x9A, 0x8A, 0x7A, 0x6A, 0x5A, 0x4A, 0x3A,   0x2A, 0x1A,
  0x93, 0x83,      0x73,  0x63, 0x53, 0x43, 0x33, 0x23, 0x13, 0x9B, 0x8B, 0x7B, 0x6B, 0x5B,     0x4B,
  0x94, 0x84,    0x74,     0x54, 0x44, 0x34, 0x24, 0x14, 0x9C, 0x8C, 0x7C, 0x6C, 0x5C,          0x4C,   0x2C,
  0x95, 0x85,   0x74,  0x65,  0x55,             0x15,                   0x6D, 0x5D, 0x4D,         0x3D, 0x2D, 0x1D);

void set_rgb(uint8_t rgb_led, uint8_t red, uint8_t green, uint8_t blue){
    if(rgb_led == 24){
        return;
    }
    uint8_t matrix = 1;
    if(rgb_led >= 17){
        matrix = 7;
        rgb_led -= 16;
    }
    if(rgb_leds[rgb_led][0][1] != 0){
        activateLED(matrix, rgb_leds[rgb_led][0][0], rgb_leds[rgb_led][0][1], red);
    }
    if(rgb_leds[rgb_led][1][1] != 0){
        activateLED(matrix, rgb_leds[rgb_led][1][0], rgb_leds[rgb_led][1][1], green);
    }
    if(rgb_leds[rgb_led][2][1] != 0){
        activateLED(matrix, rgb_leds[rgb_led][2][0], rgb_leds[rgb_led][2][1], blue);
    }
}

void set_backlight(uint8_t level){
    for(int x = 1; x <= 9; x++){
        for(int y = 1; y <= 9; y++){
            activateLED(6, x, y, level);
            activateLED(0, x, y, level);
        }
    }
}

void set_underglow(uint8_t red, uint8_t green, uint8_t blue){
    for(uint8_t x = 1; x <= 32; x++){
        set_rgb(x, red, green, blue);
    }
}

void set_backlight_by_keymap(uint8_t col, uint8_t row){
    xprintf("event: %d %d\n", col, row);
    uint8_t lookup_value = switch_leds[row][col];
    uint8_t matrix = 0;
    if(lookup_value & 0x80){
        matrix = 1;
        issi_devices[0]->led_dirty = 1;
    }else{
        issi_devices[0]->led_dirty = 1;
    }
    uint8_t led_col = (lookup_value & 0x70) >> 4;
    uint8_t led_row = lookup_value & 0x0F;
    xprintf("LED: %02X, %d %d %d\n", lookup_value, matrix, led_col, led_row);
    activateLED(matrix, led_col, led_row, 255);
}

void force_issi_refresh(){
    issi_devices[0]->led_dirty = true;
    update_issi(0, true);
    issi_devices[3]->led_dirty = true;
    update_issi(3, true);
}

void led_test(){
    set_backlight(0);
    set_underglow(0, 0, 0);
    force_issi_refresh();
    set_underglow(0, 0, 0);
    for(uint8_t x = 1; x < sizeof(rgb_sequence); x++){
        set_rgb(rgb_sequence[x], 255, 0, 0);
        force_issi_refresh();
        click(500, 2);
        _delay_ms(250);
        set_rgb(rgb_sequence[x], 0, 255, 0);
        force_issi_refresh();
        click(500, 2);
        _delay_ms(250);
        set_rgb(rgb_sequence[x], 0, 0, 255);
        force_issi_refresh();
        click(500, 2);
        _delay_ms(250);
        set_rgb(rgb_sequence[x], 0, 0, 0);
        force_issi_refresh();
    }
}

#endif

