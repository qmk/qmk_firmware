#ifndef LIGHTING_H
#define LIGHTING_H


// rgb_sequence[RGBLED_NUM]
//
// Array used for sequential lighting effects.
//
// Example LFK78 RevC+ RGB Map:
//   27  29  10   9   8   7   6
// 26                                   5
// 25                                   4
// 24                                   3
//   23  22  21  20  14  15  11   1   2
//
// const uint8_t rgb_sequence[] = {
//     27, 29, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
//     11, 15, 14, 20, 21, 22, 23, 24, 25, 26
// };
extern const uint8_t rgb_sequence[RGBLED_NUM];

// switch_matrices[]
//
// The ISSI matrices for switch backlighting
//
// Example LFK78 RevC+ - ISSI Device 0, banks 0 and 1:
// switch_matrices[] = {0, 1};
extern const uint8_t switch_matrices[];

// rgb_matrices[]
// The ISSI matrices for RGB Underglow
//
// Example LFK78 RevC+ - ISSI Device 3, banks 0 and 1:
// rgb_matrices[] = {6, 7};
extern const uint8_t rgb_matrices[];

// switch_leds[MATRIX_ROWS][MATRIX_COLS]
// Maps switch LEDs from Row/Col to ISSI matrix.
// Value breakdown:
//     Bit     | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
//             |   | ISSI Col  |    ISSI Row   |
//             |   |
//             Device
extern const uint8_t switch_leds[MATRIX_ROWS][MATRIX_COLS];

void led_test(void);
void force_issi_refresh(void);
void set_backlight(uint8_t level);
void set_underglow(uint8_t red, uint8_t green, uint8_t blue);
void set_rgb(uint8_t rgb_led, uint8_t red, uint8_t green, uint8_t blue);
void set_backlight_by_keymap(uint8_t col, uint8_t row);

#endif