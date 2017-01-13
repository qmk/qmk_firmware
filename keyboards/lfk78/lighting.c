#ifdef ISSI_ENABLE

#include "lfk78.h"
#include "issi.h"
#include <avr/sfr_defs.h>
#include "audio/audio.h"
#include "TWIlib.h"
#include "avr/timer_avr.h"
#include "lighting.h"
#include "rgblight.h"

extern rgblight_config_t rgblight_config; // Declared in rgblight.c

const uint8_t backlight_pwm_map[BACKLIGHT_LEVELS] = BACKLIGHT_PWM_MAP;

// RGB# to ISSI matrix, this is the same across all revisions
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

#ifdef LFK_REV_B
    // LFK RevB lighting info
    const uint8_t switch_matrices[] = {0, 6};
    const uint8_t rgb_matrices[] = {1, 7};

    // RGB Map:
    // 3   7    1   9  16  14   2  19  20  21  22  23   X  25
    // 4                                                   26
    // 5                                                   27
    // 6   8   15  13  12  10  11  18  17  32  31  30  29  28
    const uint8_t rgb_sequence[] = {
        3, 7, 1, 9, 16, 14, 2, 19, 20, 21, 22, 23, 25, 26, 27,
        28, 29, 30, 31, 32, 17, 18, 11, 10, 12, 13, 15, 8, 6, 5, 4
    };

    // Maps switch LEDs from Row/Col to ISSI matrix.
    // Value breakdown:
    //     Bit     | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    //             |  ISSI Column  |   | ISSI Row  |
    //                             /   |
    //                             Device

    const uint8_t switch_leds[MATRIX_ROWS][MATRIX_COLS] =
    KEYMAP(
      0x91, 0x81,   0x71, 0x61, 0x51, 0x41, 0x31, 0x21, 0x11, 0x99, 0x89, 0x79, 0x69, 0x59, 0x49,   0x39,   0x29, 0x19,
      0x92, 0x82,    0x72,  0x62, 0x52, 0x42, 0x32, 0x22, 0x12, 0x9A, 0x8A, 0x7A, 0x6A, 0x5A, 0x4A, 0x3A,   0x2A, 0x1A,
      0x93, 0x83,      0x73,  0x63, 0x53, 0x43, 0x33, 0x23, 0x13, 0x9B, 0x8B, 0x7B, 0x6B, 0x5B,     0x4B,
      0x94, 0x84,    0x74,     0x54, 0x44, 0x34, 0x24, 0x14, 0x9C, 0x8C, 0x7C, 0x6C, 0x5C,          0x4C,   0x2C,
      0x95, 0x85,   0x74,  0x65,  0x55,             0x15,                   0x6D, 0x5D, 0x4D,         0x3D, 0x2D, 0x1D);
#else
    // LFK RevC/D lighting info
    const uint8_t switch_matrices[] = {0, 1};
    const uint8_t rgb_matrices[] = {6, 7};

    // RGB Map:
    //     12  11  10  9   16  32  31  30      28
    // 13                                          25
    // 14                                          24
    // 8                                           22
    // 7                                           21
    //     6   5   4   3   2   1   17  18  19  20
    const uint8_t rgb_sequence[] = {
        12, 11, 10, 9, 16, 32, 31, 30, 28, 25, 24, 22, 21,
        20, 19, 18, 17, 1, 2, 3, 4, 5, 6, 7, 8, 14, 13
    };

    // Maps switch LEDs from Row/Col to ISSI matrix.
    // Value breakdown:
    //     Bit     | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    //             |   | ISSI Col  |    ISSI Row   |
    //             /   |
    //             Device
    const uint8_t switch_leds[MATRIX_ROWS][MATRIX_COLS] =
    KEYMAP(
      0x19, 0x18,   0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94,   0x93,   0x92, 0x91,
      0x29, 0x28,    0x27,  0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3,   0xA2, 0xA1,
      0x39, 0x38,      0x37,  0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0xB9, 0xB8, 0xB7, 0xB6, 0xB5,     0xB3,
      0x49, 0x48,    0x47,     0x45, 0x44, 0x43, 0x42, 0x41, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5,          0xC4,   0xC2,
      0x59, 0x58,   0x57,  0x56,  0x55,             0x51,                   0xD6, 0xE5, 0xE4,         0xE3, 0xE2, 0xE1);
#endif

void set_rgb(uint8_t rgb_led, uint8_t red, uint8_t green, uint8_t blue){
    if(rgb_led == 24){
        return;
    }
    uint8_t matrix = rgb_matrices[0];
    if(rgb_led >= 17){
        matrix = rgb_matrices[1];
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

void backlight_set(uint8_t level){
    if(!(issi_devices[0] && issi_devices[3])){
        // if either of the issi devices failed to init, try again
        issi_init();
    }
    uint8_t pwm_value = 0;
    if(level > 0){
        pwm_value = backlight_pwm_map[level-1];
    }
    dprintf("BACKLIGHT_LEVELS: %d\n", BACKLIGHT_LEVELS);
    dprintf("backlight_set level: %d pwm: %d\n", level, pwm_value);
    for(int x = 1; x <= 9; x++){
        for(int y = 1; y <= 9; y++){
            activateLED(switch_matrices[0], x, y, pwm_value);
            activateLED(switch_matrices[1], x, y, pwm_value);
        }
    }
}

void set_underglow(uint8_t red, uint8_t green, uint8_t blue){
    for(uint8_t x = 1; x <= 32; x++){
        set_rgb(x, red, green, blue);
    }
}


void rgblight_set(void) {
    for(uint8_t i = 0; (i < sizeof(rgb_sequence)) && (i < RGBLED_NUM); i++){
        if(rgblight_config.enable){
            set_rgb(rgb_sequence[i], led[i].r, led[i].g, led[i].b);
        }else{
            set_rgb(rgb_sequence[i], 0, 0, 0);
        }
    }
}

void set_backlight_by_keymap(uint8_t col, uint8_t row){
    dprintf("event: %d %d\n", col, row);
    uint8_t lookup_value = switch_leds[row][col];
    uint8_t matrix = switch_matrices[0];
#ifdef LFK_REV_B
    if(lookup_value & 0x08){
        matrix = switch_matrices[1];
        issi_devices[3]->led_dirty = 1;
    }else{
        issi_devices[0]->led_dirty = 1;
    }
    uint8_t led_col = (lookup_value & 0xF0) >> 4;
    uint8_t led_row = lookup_value & 0x07;
#else
    if(lookup_value & 0x80){
        matrix = switch_matrices[1];
    }
    issi_devices[0]->led_dirty = 1;
    uint8_t led_col = (lookup_value & 0x70) >> 4;
    uint8_t led_row = lookup_value & 0x0F;
#endif
    dprintf("LED: %02X, %d %d %d\n", lookup_value, matrix, led_col, led_row);
    activateLED(matrix, led_col, led_row, 255);
}

void force_issi_refresh(){
    issi_devices[0]->led_dirty = true;
    update_issi(0, true);
    issi_devices[3]->led_dirty = true;
    update_issi(3, true);
}

void led_test(){
    backlight_set(0);
    set_underglow(0, 0, 0);
    force_issi_refresh();
    set_underglow(0, 0, 0);
    for(uint8_t x = 1; x < sizeof(rgb_sequence); x++){
        set_rgb(rgb_sequence[x], 255, 0, 0);
        force_issi_refresh();
        _delay_ms(250);
        set_rgb(rgb_sequence[x], 0, 255, 0);
        force_issi_refresh();
        _delay_ms(250);
        set_rgb(rgb_sequence[x], 0, 0, 255);
        force_issi_refresh();
        _delay_ms(250);
        set_rgb(rgb_sequence[x], 0, 0, 0);
        force_issi_refresh();
    }
}

void backlight_init_ports(void){
    dprintf("backlight_init_ports\n");
    issi_init();
}

#endif

