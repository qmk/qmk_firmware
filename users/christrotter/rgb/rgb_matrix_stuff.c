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
    rgb_matrix_set_hsv(0, HSV_GREEN);
    //rgb_matrix_set_color(0, 0, 90, 0);    // | // row1,col6
    rgb_matrix_set_color(1, 40, 0, 90);     // )
    rgb_matrix_set_color(2, 40, 0, 90);     // (
    rgb_matrix_set_color(3, 0, 90, 20);     // @
    rgb_matrix_set_color(4, 90, 20, 0);    // !
    rgb_matrix_set_color(5, 90, 50, 0);     // tab // row1,col1
    rgb_matrix_set_color(6, 0, 90, 0);      // shift? // row2,col1
    rgb_matrix_set_color(7, 0, 50, 50);    // #
    rgb_matrix_set_color(8, 90, 50, 0);    // $
    rgb_matrix_set_color(9, 0, 60, 90);     // {
    rgb_matrix_set_color(10, 0, 60, 90);    // }
    rgb_matrix_set_color(11, 0, 0, 90);   // ` // row2,col6
    rgb_matrix_set_color(12, 90, 0, 0);   // ~ // row3,col6
    rgb_matrix_set_color(13, 90, 60, 0);    // ]
    rgb_matrix_set_color(14, 90, 60, 0);    // [
    rgb_matrix_set_color(15, 30, 90, 0);   // ^
    rgb_matrix_set_color(16, 90, 30, 0);   // %
    rgb_matrix_set_color(17, 0, 75, 100);   // ~ // row3,col1
    rgb_matrix_set_color(18, 100, 0, 0);    // backspace
    rgb_matrix_set_color(19, 90, 20, 0);    // delete
    rgb_matrix_set_color(20, 60, 0, 90); // mplay
    rgb_matrix_set_color(21, 0, 0, 90);    // back
    rgb_matrix_set_color(22, 0, 50, 50);     // fwd
    rgb_matrix_set_color(23, 120, 0, 0);   // esc
    rgb_matrix_set_color(24, 120, 0, 70);    // SYMBOLS
    rgb_matrix_set_color(25, 70, 40, 0);    // ALT
    rgb_matrix_set_color(26, 20, 0, 90); // cmd
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_color(27, 0, 90, 0);   // + // row1,col1 // y
    rgb_matrix_set_color(28, 0, 80, 90);   // 1
    rgb_matrix_set_color(29, 0, 80, 90);   // 2
    rgb_matrix_set_color(30, 0, 80, 90);   // 3
    rgb_matrix_set_color(31, 0, 90, 0);   // -
    rgb_matrix_set_color(32, 0, 90, 0);   // = // row1,col6 // -_
    rgb_matrix_set_color(33, 90, 90, 90);   // ; // row2,col6 
    rgb_matrix_set_color(34, 90, 90, 90);   // '
    rgb_matrix_set_color(35, 0, 80, 90);   // 6
    rgb_matrix_set_color(36, 0, 80, 90);   // 5
    rgb_matrix_set_color(37, 0, 80, 90);   // 4
    rgb_matrix_set_color(38, 0, 90, 0);   // * // row2,col1  
    rgb_matrix_set_color(39, 0, 0, 90);    // & // row3,col1
    rgb_matrix_set_color(40, 0, 80, 90);   // 7
    rgb_matrix_set_color(41, 0, 80, 90);   // 8 // <,
    rgb_matrix_set_color(42, 0, 80, 90);   // 9 // >.
    rgb_matrix_set_color(43, 0, 80, 90);   // 0 // /?
    rgb_matrix_set_color(44, 90, 90, 0); // dragscroll toggle // row3, col6
    // everything below here doesn't change
    rgb_matrix_set_color(45, 0, 120, 0);    // arrow key
    rgb_matrix_set_color(46, 0, 120, 0);    // arrow key
    rgb_matrix_set_color(47, 0, 120, 0);    // arrow key
    rgb_matrix_set_color(48, 0, 120, 0);    // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_color(49, 90, 0, 20);    // < // left-most key on kb
    rgb_matrix_set_color(50, 0, 100, 100);  // > // key right next to trackball
    rgb_matrix_set_color(51, 20, 0, 90);    // cmd // bottom of space/enter key row
    rgb_matrix_set_color(52, 120, 0, 70);   // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_color(53, 0, 25, 120);   // enter key
    rgb_matrix_set_color(54, 0, 120, 200);  // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_color(55, 0, 90, 0);    // multiline // key below layer button
    rgb_matrix_set_color(56, 0, 0, 120);    // ctrl //far right key, 'below' enter key
            break;
////////////////////// MOUSE LAYER RGB SETTINGS //////////////////////
        case _MOUSE:
    rgb_matrix_set_color(0, 90, 90, 90); // row1,col6
    rgb_matrix_set_color(1, 90, 90, 90);
    rgb_matrix_set_color(2, 90, 90, 90);
    rgb_matrix_set_color(3, 90, 90, 90);
    rgb_matrix_set_color(4, 90, 90, 90);
    rgb_matrix_set_color(5, 90, 50, 0); // tab // row1,col1
    rgb_matrix_set_color(6, 0, 90, 0); // shift? // row2,col1
    rgb_matrix_set_color(7, 90, 90, 90);
    rgb_matrix_set_color(8, 90, 90, 90);
    rgb_matrix_set_color(9, 90, 90, 90);
    rgb_matrix_set_color(10, 90, 90, 90);
    rgb_matrix_set_color(11, 90, 90, 90); // row2,col6
    rgb_matrix_set_color(12, 90, 90, 90); // row3,col6
    rgb_matrix_set_color(13, 90, 90, 90);
    rgb_matrix_set_color(14, 90, 90, 90);
    rgb_matrix_set_color(15, 90, 90, 90);
    rgb_matrix_set_color(16, 90, 90, 90);
    rgb_matrix_set_color(17, 0, 75, 100); // tilde-backtick // row3,col1
    rgb_matrix_set_color(18, 100, 0, 0); // backspace
    rgb_matrix_set_color(19, 90, 20, 0); // delete
    rgb_matrix_set_color(20, 60, 0, 90); // mplay
    rgb_matrix_set_color(21, 90, 0, 30); // mac lock KC_MACLOCK
    rgb_matrix_set_color(22, 90, 0, 0); // KC_CAD
    rgb_matrix_set_color(23, 120, 0, 0);   // esc
    rgb_matrix_set_color(24, 120, 0, 70); // SYMBOLS
    rgb_matrix_set_color(25, 70, 40, 0);    // ALT
    rgb_matrix_set_color(26, 20, 0, 90); // cmd
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_color(27, 15, 15, 15); // row1,col1 // y
    rgb_matrix_set_color(28, 15, 15, 15); // mouse-surround
    rgb_matrix_set_color(29, 120, 120, 120); // MIDDLE CLICK
    rgb_matrix_set_color(30, 15, 15, 15); // mouse-surround
    rgb_matrix_set_color(31, 90, 90, 90);
    rgb_matrix_set_color(32, 90, 50, 0); // screenshot // row1,col6
    rgb_matrix_set_color(33, 0, 75, 100); // row2,col6 // ;:
    rgb_matrix_set_color(34, 0, 75, 100); // "'
    rgb_matrix_set_color(35, 30, 30, 30); // mouse-surround // l
    rgb_matrix_set_color(36, 120, 120, 120); // RIGHT CLICK // k
    rgb_matrix_set_color(37, 120, 120, 120); // LEFT CLICK // j
    rgb_matrix_set_color(38, 15, 15, 15); // mouse-surround // h // row2,col1 
    rgb_matrix_set_color(39, 15, 15, 15); // n // row3,col1  
    rgb_matrix_set_color(40, 15, 15, 15); // mouse-surround // m
    rgb_matrix_set_color(41, 0, 15, 25); // mouse-surround // <,
    rgb_matrix_set_color(42, 0, 15, 25); // mouse-surround // >.
    rgb_matrix_set_color(43, 100, 85, 0); // /?
    rgb_matrix_set_color(44, 90, 90, 0); // dragscroll toggle //row3, col6 // not sure what this key should be
    rgb_matrix_set_color(45, 0, 120, 0); // arrow key
    rgb_matrix_set_color(46, 0, 120, 0); // arrow key
    rgb_matrix_set_color(47, 0, 120, 0); // arrow key
    rgb_matrix_set_color(48, 0, 120, 0); // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_color(49, 90, 0, 20); // < // left-most key on kb
    rgb_matrix_set_color(50, 0, 100, 100); // > // key right next to trackball
    rgb_matrix_set_color(51, 20, 0, 90); // cmd // bottom of space/enter key row
    rgb_matrix_set_color(52, 120, 0, 70); // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_color(53, 0, 25, 120); // enter key
    rgb_matrix_set_color(54, 0, 120, 200); // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_color(55, 0, 90, 0);    // multiline // key below layer button
    rgb_matrix_set_color(56, 0, 0, 120); // ctrl //far right key, 'below' enter key
            break;
////////////////////// MOUSE LAYER RGB SETTINGS //////////////////////
////////////////////// QWERTY LAYER RGB SETTINGS //////////////////////            
        case _QWERTY:
    rgb_matrix_set_color(0, 90, 90, 90); // row1,col6
    rgb_matrix_set_color(1, 90, 90, 90);
    rgb_matrix_set_color(2, 90, 90, 90);
    rgb_matrix_set_color(3, 90, 90, 90);
    rgb_matrix_set_color(4, 90, 90, 90);
    rgb_matrix_set_color(5, 90, 50, 0); // tab // row1,col1
    rgb_matrix_set_color(6, 0, 90, 0); // shift? // row2,col1
    rgb_matrix_set_color(7, 90, 90, 90);
    rgb_matrix_set_color(8, 90, 90, 90);
    rgb_matrix_set_color(9, 90, 90, 90);
    rgb_matrix_set_color(10, 90, 90, 90);
    rgb_matrix_set_color(11, 90, 90, 90); // row2,col6
    rgb_matrix_set_color(12, 90, 90, 90); // row3,col6
    rgb_matrix_set_color(13, 90, 90, 90);
    rgb_matrix_set_color(14, 90, 90, 90);
    rgb_matrix_set_color(15, 90, 90, 90);
    rgb_matrix_set_color(16, 90, 90, 90);
    rgb_matrix_set_color(17, 0, 75, 100); // tilde-backtick // row3,col1
    rgb_matrix_set_color(18, 100, 0, 0); // backspace
    rgb_matrix_set_color(19, 90, 20, 0); // delete
    rgb_matrix_set_color(20, 90, 0, 0); // chrome back
    rgb_matrix_set_color(21, 0, 0, 90);    // back
    rgb_matrix_set_color(22, 0, 50, 50);   // fwd
    rgb_matrix_set_color(23, 120, 0, 0);   // esc
    rgb_matrix_set_color(24, 120, 0, 70); // SYMBOLS
    rgb_matrix_set_color(25, 70, 40, 0);    // ALT
    rgb_matrix_set_color(26, 20, 0, 90); // cmd
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_color(27, 90, 90, 90); // row1,col1 // y
    rgb_matrix_set_color(28, 90, 90, 90);
    rgb_matrix_set_color(29, 90, 90, 90);
    rgb_matrix_set_color(30, 90, 90, 90);
    rgb_matrix_set_color(31, 90, 90, 90);
    rgb_matrix_set_color(32, 0, 75, 100); // row1,col6 // -_
    rgb_matrix_set_color(33, 0, 75, 100); // row2,col6 // ;:
    rgb_matrix_set_color(34, 0, 75, 100); // "'
    rgb_matrix_set_color(35, 90, 90, 90); // l
    rgb_matrix_set_color(36, 90, 90, 90); // k
    rgb_matrix_set_color(37, 90, 90, 90); // j
    rgb_matrix_set_color(38, 90, 90, 90); // h // row2,col1 
    rgb_matrix_set_color(39, 90, 90, 90); // n // row3,col1  
    rgb_matrix_set_color(40, 90, 90, 90);
    rgb_matrix_set_color(41, 0, 75, 100); // <,
    rgb_matrix_set_color(42, 0, 75, 100); // >.
    rgb_matrix_set_color(43, 100, 85, 0); // /?
    rgb_matrix_set_color(44, 90, 90, 0); // dragscroll toggle //row3, col6 // not sure what this key should be
    rgb_matrix_set_color(45, 0, 120, 0); // arrow key
    rgb_matrix_set_color(46, 0, 120, 0); // arrow key
    rgb_matrix_set_color(47, 0, 120, 0); // arrow key
    rgb_matrix_set_color(48, 0, 120, 0); // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_color(49, 90, 0, 20); // < // left-most key on kb
    rgb_matrix_set_color(50, 0, 100, 100); // > // key right next to trackball
    rgb_matrix_set_color(51, 20, 0, 90); // cmd // bottom of space/enter key row
    rgb_matrix_set_color(52, 120, 0, 70); // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_color(53, 0, 25, 120); // enter key
    rgb_matrix_set_color(54, 0, 120, 200); // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_color(55, 0, 90, 0);    // multiline // key below layer button
    rgb_matrix_set_color(56, 0, 0, 120); // ctrl //far right key, 'below' enter key
            break;
    }
    // info: using one line per key, 3% of flash is used to set one layer of 57 keys per-key rgb    
}

void keyboard_post_init_rgb_matrix(void) {
}

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    return true;
}
