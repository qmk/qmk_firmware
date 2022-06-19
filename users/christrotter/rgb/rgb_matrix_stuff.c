// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "christrotter.h"
#include "rgb_matrix.h"
#include "lib/lib8tion/lib8tion.h" // this is used for math or something?
extern led_config_t g_led_config;

//int led_min = 100; 
//int led_max = 200;

// void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max) {
//     // this is used for setting layer colours?
//     HSV hsv = {hue, sat, val};
//     if (hsv.v > rgb_matrix_get_val()) {
//         hsv.v = rgb_matrix_get_val();
//     }
// 
//     switch (mode) {
//         default:  // Solid Color
//         {
//             RGB rgb = hsv_to_rgb(hsv);
//             for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
//                 if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
//                     RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
//                 }
//             }
//             
//             break;
//         }
//     }
// }

// __attribute__((weak)) void rgb_matrix_indicator_keymap(void) {}
//
    /* 
     * ,-----------------------------------------,                                           ,-----------------------------------------,
     * |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |                                           |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |
     * |------+------+------+------+------+------|                                           |-------------+------+------+------+------|
     * |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |                               (TRACKBALL) |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |
     * |------+------+------+------+------|------|------|------|------,        |------|------|------|------+------+------+------+------|
     * |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |  4,3 |  4,4 |  4,5 |        |  4,1 |  4,2 |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |
     * |------+------+------+------,------,------,------,------,------,      ,------,------,------,------,-----------------------------,
     *                             |      |      |      |      |             |      |      |      |      |        ,------,
     *                             |  4,1 |  4,2 |  5,3 |  5,4 |             |  4,3 |  4,4 |  4,5 |  4,6 |        |  5,4 |
     *                             |      |      |      |      |             |      |      |      |      | ,------+------+-----,
     *                             '------+------+------+------'             '------'------+------+------' |  5,3 |------| 5,6 |
     *                                    '------+------'                                  '------+------' '------+------+-----'
     *                                    |  5,1 |  5,2 |                                  |  5,1 |  5,2 |        |  5,5 |
     *                                    '------+------'                                  '------+------'        '------'
     */

void rgb_matrix_set_hsv(uint8_t i, uint8_t hue, uint8_t sat, uint8_t value) {
    HSV hsv = {.h = hue, .s = sat, .v = value};
    hsv.v = (hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) ? RGB_MATRIX_MAXIMUM_BRIGHTNESS : hsv.v;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

void matrix_scan_rgb_matrix(void) {
    /*
        This is where we set per-layer/per-key RGB.  In future, this should live in the keyboard space...?
        NOTE: if you do not specify a per-key setting, the key's LED defaults to whatever the base colour is...
        ... red unless otherwise set.
        NOTE: if, for a layer, you do the pattern "set all, then set a few individual"...
        ... it makes seeing other keys very difficult... i.e. there is no 'layer functionality' i.e. transparency
    */
    /*
     Ideas here about how we might turn this into less of a mess
        uint8_t g_brightness = // 5 to 10
        int led[][][][] = {
            {0, 0, 9, 0}, // where the 9 would be, at g_bright5, 45, at g_bright10, 90
            {1, 0, 0, 9} // the key descriptor
            {2, HSV_BLUE} // two dimensions, index and hsv...and this would rely on global brightness
        } 
        void rgb_set (uint8_t led_index, uint8_t led_red, uint8_t led_green, uint8_t led_blue) {
            // we need this cuz no global brightness with rgb_matrix_set_color
            if (led_red > 0) {
                int adjusted_led_red = led_red * g_brightness;
            } else { adjusted_led_red = led_red }
            if (led_green > 0) {
                int adjusted_led_green = led_green * g_brightness;
            } else { adjusted_led_green = led_green }
            if (led_blue > 0) {
                int adjusted_led_blue = led_blue * g_brightness;
            } else { adjusted_led_blue = led_blue }

            rgb_matrix_set_color(led_index, adjusted_led_red, adjusted_led_green, adjusted_led_blue); 
        }
        rgb_set(led[], led[], led[], led[]);
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max) {
    // this is used for setting layer colours?
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    switch (mode) {
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                }
// how do we pass in HSV_BLUE to this function..
void rgb_matrix_set_hsv(uint8_t i, uint8_t hue, uint8_t sat, uint8_t value) {
    // me-codehsv.v = (val > RGB_MATRIX_MAXIMUM_BRIGHTNESS) ? RGB_MATRIX_MAXIMUM_BRIGHTNESS : val;
    if 
    HSV hsv = {.h = hue, .s = sat, .v = value};
    hsv.v = (hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) ? RGB_MATRIX_MAXIMUM_BRIGHTNESS : val;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}        
     */
    switch (get_highest_layer(layer_state | default_layer_state)) {
////////////////////// SYMBOLS LAYER RGB SETTINGS //////////////////////
        case _SYMBOLS:
    rgb_matrix_set_hsv(0, HSV_GREEN); // | // row1,col6
    rgb_matrix_set_hsv(1, HSV_PURPLE);     // )
    rgb_matrix_set_hsv(2, HSV_PURPLE);     // (
    rgb_matrix_set_hsv(3, HSV_GREEN);     // @
    rgb_matrix_set_hsv(4, HSV_ORANGE);    // !
    rgb_matrix_set_hsv(5, HSV_GOLD);     // tab // row1,col1
    rgb_matrix_set_hsv(6, HSV_GREEN);      // shift? // row2,col1
    rgb_matrix_set_hsv(7, HSV_CYAN);    // #
    rgb_matrix_set_hsv(8, HSV_GOLD);    // $
    rgb_matrix_set_hsv(9, HSV_MAGENTA);     // {
    rgb_matrix_set_hsv(10, HSV_MAGENTA);    // }
    rgb_matrix_set_hsv(11, HSV_BLUE);   // ` // row2,col6
    rgb_matrix_set_hsv(12, HSV_CYAN);   // ~ // row3,col6
    rgb_matrix_set_hsv(13, HSV_PINK);    // ]
    rgb_matrix_set_hsv(14, HSV_PINK);    // [
    rgb_matrix_set_hsv(15, HSV_GREEN);   // ^
    rgb_matrix_set_hsv(16, HSV_ORANGE);   // %
    rgb_matrix_set_hsv(17, HSV_CYAN);   // ~ // row3,col1
    rgb_matrix_set_hsv(18,  HSV_RED);    // backspace
    rgb_matrix_set_hsv(19, HSV_ORANGE);    // delete
    rgb_matrix_set_hsv(20, HSV_PINK); // mplay
    rgb_matrix_set_hsv(21, HSV_BLUE);    // back
    rgb_matrix_set_hsv(22, HSV_CYAN);     // fwd
    rgb_matrix_set_hsv(23, HSV_RED);   // esc
    rgb_matrix_set_hsv(24, HSV_PINK);    // SYMBOLS
    rgb_matrix_set_hsv(25, HSV_GOLD);    // ALT
    rgb_matrix_set_hsv(26, HSV_PURPLE); // cmd
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_hsv(27, HSV_GREEN);   // + // row1,col1 // y
    rgb_matrix_set_hsv(28, HSV_CYAN);   // 1
    rgb_matrix_set_hsv(29, HSV_CYAN);   // 2
    rgb_matrix_set_hsv(30, HSV_CYAN);   // 3
    rgb_matrix_set_hsv(31, HSV_GREEN);   // -
    rgb_matrix_set_hsv(32, HSV_GREEN);   // = // row1,col6 // -_
    rgb_matrix_set_hsv(33, HSV_WHITE);   // ; // row2,col6 
    rgb_matrix_set_hsv(34, HSV_WHITE);   // '
    rgb_matrix_set_hsv(35, HSV_CYAN);   // 6
    rgb_matrix_set_hsv(36, HSV_CYAN);   // 5
    rgb_matrix_set_hsv(37, HSV_CYAN);   // 4
    rgb_matrix_set_hsv(38, HSV_GREEN);   // * // row2,col1  
    rgb_matrix_set_hsv(39, HSV_BLUE);    // & // row3,col1
    rgb_matrix_set_hsv(40, HSV_CYAN);   // 7
    rgb_matrix_set_hsv(41, HSV_CYAN);   // 8 // <,
    rgb_matrix_set_hsv(42, HSV_CYAN);   // 9 // >.
    rgb_matrix_set_hsv(43, HSV_CYAN);   // 0 // /?
    rgb_matrix_set_hsv(44, HSV_YELLOW); // dragscroll toggle // row3, col6
    // everything below here doesn't change
    rgb_matrix_set_hsv(45, HSV_GREEN);    // arrow key
    rgb_matrix_set_hsv(46, HSV_GREEN);    // arrow key
    rgb_matrix_set_hsv(47, HSV_GREEN);    // arrow key
    rgb_matrix_set_hsv(48, HSV_GREEN);    // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_hsv(49, HSV_RED);    // < // left-most key on kb
    rgb_matrix_set_hsv(50, HSV_CYAN);  // > // key right next to trackball
    rgb_matrix_set_hsv(51, HSV_PURPLE);    // cmd // bottom of space/enter key row
    rgb_matrix_set_hsv(52, HSV_PINK);   // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_hsv(53, HSV_BLUE);   // enter key
    rgb_matrix_set_hsv(54, HSV_CYAN);  // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_hsv(55, HSV_GREEN);    // multiline // key below layer button
    rgb_matrix_set_hsv(56, HSV_BLUE);    // ctrl //far right key, 'below' enter key
            break;
////////////////////// MOUSE LAYER RGB SETTINGS //////////////////////
        case _MOUSE:
    rgb_matrix_set_hsv(0, HSV_WHITE); // row1,col6
    rgb_matrix_set_hsv(1, HSV_WHITE);
    rgb_matrix_set_hsv(2, HSV_WHITE);
    rgb_matrix_set_hsv(3, HSV_WHITE);
    rgb_matrix_set_hsv(4, HSV_WHITE);
    rgb_matrix_set_hsv(5, HSV_GOLD); // tab // row1,col1
    rgb_matrix_set_hsv(6, HSV_GREEN); // shift? // row2,col1
    rgb_matrix_set_hsv(7, HSV_WHITE);
    rgb_matrix_set_hsv(8, HSV_WHITE);
    rgb_matrix_set_hsv(9, HSV_WHITE);
    rgb_matrix_set_hsv(10, HSV_WHITE);
    rgb_matrix_set_hsv(11, HSV_WHITE); // row2,col6
    rgb_matrix_set_hsv(12, HSV_WHITE); // row3,col6
    rgb_matrix_set_hsv(13, HSV_WHITE);
    rgb_matrix_set_hsv(14, HSV_WHITE);
    rgb_matrix_set_hsv(15, HSV_WHITE);
    rgb_matrix_set_hsv(16, HSV_WHITE);
    rgb_matrix_set_hsv(17, HSV_CYAN); // tilde-backtick // row3,col1
    rgb_matrix_set_hsv(18,  HSV_RED); // backspace
    rgb_matrix_set_hsv(19, HSV_ORANGE); // delete
    rgb_matrix_set_hsv(20, HSV_PINK); // mplay
    rgb_matrix_set_hsv(21, HSV_RED); // mac lock KC_MACLOCK
    rgb_matrix_set_hsv(22, HSV_RED); // KC_CAD
    rgb_matrix_set_hsv(23, HSV_RED);   // esc
    rgb_matrix_set_hsv(24, HSV_PINK); // SYMBOLS
    rgb_matrix_set_hsv(25, HSV_GOLD);    // ALT
    rgb_matrix_set_hsv(26, HSV_PURPLE); // cmd
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_hsv(27, HSV_WHITE); // row1,col1 // y
    rgb_matrix_set_hsv(28, HSV_WHITE); // mouse-surround
    rgb_matrix_set_hsv(29, HSV_SPRINGGREEN); // MIDDLE CLICK
    rgb_matrix_set_hsv(30, HSV_WHITE); // mouse-surround
    rgb_matrix_set_hsv(31, HSV_WHITE);
    rgb_matrix_set_hsv(32, HSV_GOLD); // screenshot // row1,col6
    rgb_matrix_set_hsv(33, HSV_CYAN); // row2,col6 // ;:
    rgb_matrix_set_hsv(34, HSV_CYAN); // "'
    rgb_matrix_set_hsv(35, HSV_WHITE); // mouse-surround // l
    rgb_matrix_set_hsv(36, HSV_SPRINGGREEN); // RIGHT CLICK // k
    rgb_matrix_set_hsv(37, HSV_SPRINGGREEN); // LEFT CLICK // j
    rgb_matrix_set_hsv(38, HSV_WHITE); // mouse-surround // h // row2,col1 
    rgb_matrix_set_hsv(39, HSV_WHITE); // n // row3,col1  
    rgb_matrix_set_hsv(40, HSV_WHITE); // mouse-surround // m
    rgb_matrix_set_hsv(41, HSV_CYAN); // mouse-surround // <,
    rgb_matrix_set_hsv(42, HSV_CYAN); // mouse-surround // >.
    rgb_matrix_set_hsv(43, HSV_GOLD); // /?
    rgb_matrix_set_hsv(44, HSV_YELLOW); // dragscroll toggle //row3, col6 // not sure what this key should be
    rgb_matrix_set_hsv(45, HSV_GREEN); // arrow key
    rgb_matrix_set_hsv(46, HSV_GREEN); // arrow key
    rgb_matrix_set_hsv(47, HSV_GREEN); // arrow key
    rgb_matrix_set_hsv(48, HSV_GREEN); // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_hsv(49, HSV_RED); // < // left-most key on kb
    rgb_matrix_set_hsv(50, HSV_CYAN); // > // key right next to trackball
    rgb_matrix_set_hsv(51, HSV_PURPLE); // cmd // bottom of space/enter key row
    rgb_matrix_set_hsv(52, HSV_PINK); // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_hsv(53, HSV_BLUE); // enter key
    rgb_matrix_set_hsv(54, HSV_CYAN); // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_hsv(55, HSV_GREEN);    // multiline // key below layer button
    rgb_matrix_set_hsv(56, HSV_BLUE); // ctrl //far right key, 'below' enter key
            break;
////////////////////// MOUSE LAYER RGB SETTINGS //////////////////////
////////////////////// QWERTY LAYER RGB SETTINGS //////////////////////            
        case _QWERTY:
    rgb_matrix_set_hsv(0, HSV_WHITE); // row1,col6
    rgb_matrix_set_hsv(1, HSV_WHITE);
    rgb_matrix_set_hsv(2, HSV_WHITE);
    rgb_matrix_set_hsv(3, HSV_WHITE);
    rgb_matrix_set_hsv(4, HSV_WHITE);
    rgb_matrix_set_hsv(5, HSV_GOLD); // tab // row1,col1
    rgb_matrix_set_hsv(6, HSV_GREEN); // shift? // row2,col1
    rgb_matrix_set_hsv(7, HSV_WHITE);
    rgb_matrix_set_hsv(8, HSV_WHITE);
    rgb_matrix_set_hsv(9, HSV_WHITE);
    rgb_matrix_set_hsv(10, HSV_WHITE);
    rgb_matrix_set_hsv(11, HSV_WHITE); // row2,col6
    rgb_matrix_set_hsv(12, HSV_WHITE); // row3,col6
    rgb_matrix_set_hsv(13, HSV_WHITE);
    rgb_matrix_set_hsv(14, HSV_WHITE);
    rgb_matrix_set_hsv(15, HSV_WHITE);
    rgb_matrix_set_hsv(16, HSV_WHITE);
    rgb_matrix_set_hsv(17, HSV_CYAN); // tilde-backtick // row3,col1
    rgb_matrix_set_hsv(18, HSV_RED); // backspace
    rgb_matrix_set_hsv(19, HSV_ORANGE); // delete
    rgb_matrix_set_hsv(20, HSV_RED); // chrome back
    rgb_matrix_set_hsv(21, HSV_BLUE);    // back
    rgb_matrix_set_hsv(22, HSV_CYAN);   // fwd
    rgb_matrix_set_hsv(23, HSV_RED);   // esc
    rgb_matrix_set_hsv(24, HSV_PINK); // SYMBOLS
    rgb_matrix_set_hsv(25, HSV_GOLD);    // ALT
    rgb_matrix_set_hsv(26, HSV_PURPLE); // cmd
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_hsv(27, HSV_WHITE); // row1,col1 // y
    rgb_matrix_set_hsv(28, HSV_WHITE);
    rgb_matrix_set_hsv(29, HSV_WHITE);
    rgb_matrix_set_hsv(30, HSV_WHITE);
    rgb_matrix_set_hsv(31, HSV_WHITE);
    rgb_matrix_set_hsv(32, HSV_CYAN); // row1,col6 // -_
    rgb_matrix_set_hsv(33, HSV_CYAN); // row2,col6 // ;:
    rgb_matrix_set_hsv(34, HSV_CYAN); // "'
    rgb_matrix_set_hsv(35, HSV_WHITE); // l
    rgb_matrix_set_hsv(36, HSV_WHITE); // k
    rgb_matrix_set_hsv(37, HSV_WHITE); // j
    rgb_matrix_set_hsv(38, HSV_WHITE); // h // row2,col1 
    rgb_matrix_set_hsv(39, HSV_WHITE); // n // row3,col1  
    rgb_matrix_set_hsv(40, HSV_WHITE);
    rgb_matrix_set_hsv(41, HSV_CYAN); // <,
    rgb_matrix_set_hsv(42, HSV_CYAN); // >.
    rgb_matrix_set_hsv(43, HSV_GOLD); // /?
    rgb_matrix_set_hsv(44, HSV_YELLOW); // dragscroll toggle //row3, col6 // not sure what this key should be
    rgb_matrix_set_hsv(45, HSV_GREEN); // arrow key
    rgb_matrix_set_hsv(46, HSV_GREEN); // arrow key
    rgb_matrix_set_hsv(47, HSV_GREEN); // arrow key
    rgb_matrix_set_hsv(48, HSV_GREEN); // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_hsv(49, HSV_RED); // < // left-most key on kb
    rgb_matrix_set_hsv(50, HSV_CYAN); // > // key right next to trackball
    rgb_matrix_set_hsv(51, HSV_PURPLE); // cmd // bottom of space/enter key row
    rgb_matrix_set_hsv(52, HSV_PINK); // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_hsv(53, HSV_BLUE); // enter key
    rgb_matrix_set_hsv(54, HSV_CYAN); // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_hsv(55, HSV_GREEN);    // multiline // key below layer button
    rgb_matrix_set_hsv(56, HSV_BLUE); // ctrl //far right key, 'below' enter key
            break;
    }
    // info: using one line per key, 3% of flash is used to set one layer of 57 keys per-key rgb    
}

void keyboard_post_init_rgb_matrix(void) {
}

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    return true;
}
