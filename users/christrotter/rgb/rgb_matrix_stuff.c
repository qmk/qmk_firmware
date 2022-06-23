// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "christrotter.h"
#include "rgb_matrix.h"
#include "5x6_right.h"
extern led_config_t g_led_config;
    /* 
        re: rgb_matrix_set_hsv and max brightness...
        Dasky commented...
        rgb_matrix_get_val shouldn't ever be above the maximum if the eeprom has been reset since changing the maximum at least
        the situation where it can be above the maximum define gets sorted when you change brightness.

        if (value > rgb_matrix_get_val()) {
            value = rgb_matrix_get_val();
        }    
    */
/*
    We need to set per-key LED colour, but rgb_matrix_set_color does not honour RGB_MATRIX_MAXIMUM_BRIGHTNESS.
    So this is a way that lets you pass in an HSV_COLOUR value or h,s,v values.
    Using HSV somehow also saves a bunch of space compared to rgb direct, which makes no sense but ok.
*/
void rgb_matrix_set_hsv(uint8_t i, uint8_t hue, uint8_t sat, uint8_t value) {
    HSV hsv = {.h = hue, .s = sat, .v = value};
    hsv.v = (hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) ? RGB_MATRIX_MAXIMUM_BRIGHTNESS : hsv.v;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}
/*
    This is where we set per-layer/per-key RGB.  In future, this should live in the keyboard space...?
    NOTE: if you do not specify a per-key setting, the key's LED defaults to whatever the base colour is...
    ... red unless otherwise set.
    NOTE: if, for a layer, you do the pattern "set all, then set a few individual"...
    ... it makes seeing other keys very difficult... i.e. there is no 'layer functionality' i.e. transparency
*/
void matrix_scan_rgb_matrix(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
////////////////////// SYMBOLS LAYER RGB SETTINGS //////////////////////
        case _SYMBOLS:
    rgb_matrix_set_hsv(0, HSV_GREEN);       // | // row1,col6
    rgb_matrix_set_hsv(1, HSV_PURPLE);      // )
    rgb_matrix_set_hsv(2, HSV_PURPLE);      // (
    rgb_matrix_set_hsv(3, HSV_GREEN);       // @
    rgb_matrix_set_hsv(4, HSV_ORANGE);      // !
    rgb_matrix_set_hsv(5, HSV_GOLD);        // tab // row1,col1
    rgb_matrix_set_hsv(6, HSV_WHITE);       // ? // row2,col1
    rgb_matrix_set_hsv(7, HSV_CYAN);        // #
    rgb_matrix_set_hsv(8, HSV_GOLD);        // $
    rgb_matrix_set_hsv(9, HSV_MAGENTA);     // {
    rgb_matrix_set_hsv(10, HSV_MAGENTA);    // }
    rgb_matrix_set_hsv(11, HSV_BLUE);       // ` // row2,col6
    rgb_matrix_set_hsv(12, HSV_CYAN);       // ~ // row3,col6
    rgb_matrix_set_hsv(13, HSV_PINK);       // ]
    rgb_matrix_set_hsv(14, HSV_PINK);       // [
    rgb_matrix_set_hsv(15, HSV_GREEN);      // ^
    rgb_matrix_set_hsv(16, HSV_ORANGE);     // %
    rgb_matrix_set_hsv(17, HSV_CYAN);       // ~ // row3,col1
    rgb_matrix_set_hsv(18,  HSV_RED);       // backspace
    rgb_matrix_set_hsv(19, HSV_ORANGE);     // delete
    rgb_matrix_set_hsv(20, HSV_GREEN);      // shift
    rgb_matrix_set_hsv(21, HSV_PURPLE);     // cmd
    rgb_matrix_set_hsv(22, HSV_YELLOW);     // alt
    rgb_matrix_set_hsv(23, HSV_RED);        // esc
    rgb_matrix_set_hsv(24, HSV_CHARTREUSE); // _NAV
    rgb_matrix_set_hsv(25, HSV_CYAN);       // tab-r
    rgb_matrix_set_hsv(26, HSV_BLUE);       // tab-l
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_hsv(27, HSV_GREEN);      // + // row1,col1 // y
    rgb_matrix_set_hsv(28, HSV_CYAN);       // 1
    rgb_matrix_set_hsv(29, HSV_CYAN);       // 2
    rgb_matrix_set_hsv(30, HSV_CYAN);       // 3
    rgb_matrix_set_hsv(31, HSV_GREEN);      // -
    rgb_matrix_set_hsv(32, HSV_YELLOW);     // = // row1,col6 // -_
    rgb_matrix_set_hsv(33, HSV_RED);      // , // row2,col6 
    rgb_matrix_set_hsv(34, HSV_CYAN);      // 0
    rgb_matrix_set_hsv(35, HSV_CYAN);       // 6
    rgb_matrix_set_hsv(36, HSV_CYAN);       // 5
    rgb_matrix_set_hsv(37, HSV_CYAN);       // 4
    rgb_matrix_set_hsv(38, HSV_GREEN);      // * // row2,col1  
    rgb_matrix_set_hsv(39, HSV_RED);       // . // row3,col1
    rgb_matrix_set_hsv(40, HSV_CYAN);       // 7
    rgb_matrix_set_hsv(41, HSV_CYAN);       // 8 // <,
    rgb_matrix_set_hsv(42, HSV_CYAN);       // 9 // >.
    rgb_matrix_set_hsv(43, HSV_ORANGE);     // \ // /?
    rgb_matrix_set_hsv(44, HSV_YELLOW);     // dragscroll toggle // row3, col6
    rgb_matrix_set_hsv(45, HSV_GOLD);       // shift + alt + arrow // arrow key
    rgb_matrix_set_hsv(46, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(47, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(48, HSV_GOLD);       // shift + alt + arrow // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_hsv(49, HSV_BLUE);       // ctrl // left-most key on kb
    rgb_matrix_set_hsv(50, HSV_GREEN);      // shift // key right next to trackball
    rgb_matrix_set_hsv(51, HSV_PURPLE);     // cmd // bottom of space/enter key row
    rgb_matrix_set_hsv(52, HSV_PINK);       // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_hsv(53, HSV_CYAN);       // enter key
    rgb_matrix_set_hsv(54, HSV_GREEN);       // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_hsv(55, HSV_GREEN);       // multiline // key below layer button
    rgb_matrix_set_hsv(56, HSV_CYAN);      // ctrl //far right key, 'below' enter key
            break;
////////////////////// MOUSE LAYER RGB SETTINGS //////////////////////
        case _MOUSE:
    rgb_matrix_set_hsv(0, HSV_WHITE);       // row1,col6
    rgb_matrix_set_hsv(1, HSV_WHITE);
    rgb_matrix_set_hsv(2, HSV_WHITE);
    rgb_matrix_set_hsv(3, HSV_WHITE);
    rgb_matrix_set_hsv(4, HSV_WHITE);
    rgb_matrix_set_hsv(5, HSV_GOLD);        // tab // row1,col1
    rgb_matrix_set_hsv(6, HSV_WHITE);       // ? // row2,col1
    rgb_matrix_set_hsv(7, HSV_WHITE);
    rgb_matrix_set_hsv(8, HSV_WHITE);
    rgb_matrix_set_hsv(9, HSV_WHITE);
    rgb_matrix_set_hsv(10, HSV_WHITE);
    rgb_matrix_set_hsv(11, HSV_WHITE);      // row2,col6
    rgb_matrix_set_hsv(12, HSV_WHITE);      // row3,col6
    rgb_matrix_set_hsv(13, HSV_WHITE);
    rgb_matrix_set_hsv(14, HSV_WHITE);
    rgb_matrix_set_hsv(15, HSV_WHITE);
    rgb_matrix_set_hsv(16, HSV_WHITE);
    rgb_matrix_set_hsv(17, HSV_CYAN);       // tilde-backtick // row3,col1
    rgb_matrix_set_hsv(18, HSV_RED);        // backspace
    rgb_matrix_set_hsv(19, HSV_ORANGE);     // delete
    rgb_matrix_set_hsv(20, HSV_RED);        // mac lock
    rgb_matrix_set_hsv(21, HSV_WHITE);      //
    rgb_matrix_set_hsv(22, HSV_RED);        // CAD
    rgb_matrix_set_hsv(23, HSV_WHITE);      // esc
    rgb_matrix_set_hsv(24, HSV_CHARTREUSE); // _NAV
    rgb_matrix_set_hsv(25, HSV_CYAN);       // tab-r
    rgb_matrix_set_hsv(26, HSV_BLUE);       // tab-l
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_hsv(27, HSV_WHITE);      // row1,col1 // y
    rgb_matrix_set_hsv(28, HSV_WHITE);
    rgb_matrix_set_hsv(29, HSV_WHITE);
    rgb_matrix_set_hsv(30, HSV_WHITE);
    rgb_matrix_set_hsv(31, HSV_WHITE);
    rgb_matrix_set_hsv(32, HSV_GOLD);       // screenshot // row1,col6
    rgb_matrix_set_hsv(33, HSV_CYAN);       // row2,col6 // ;:
    rgb_matrix_set_hsv(34, HSV_CYAN);       // "'
    rgb_matrix_set_hsv(35, HSV_SPRINGGREEN);// RIGHT CLICK // l
    rgb_matrix_set_hsv(36, HSV_SPRINGGREEN);// MIDDLE CLICK // k
    rgb_matrix_set_hsv(37, HSV_SPRINGGREEN);// LEFT CLICK // j
    rgb_matrix_set_hsv(38, HSV_WHITE);      // h // row2,col1 
    rgb_matrix_set_hsv(39, HSV_WHITE);      // n // row3,col1  
    rgb_matrix_set_hsv(40, HSV_WHITE);      // m
    rgb_matrix_set_hsv(41, HSV_CYAN);       // <,
    rgb_matrix_set_hsv(42, HSV_CYAN);       // >.
    rgb_matrix_set_hsv(43, HSV_GOLD);       // /?
    rgb_matrix_set_hsv(44, HSV_YELLOW);     // dragscroll toggle //row3, col6 // not sure what this key should be
    rgb_matrix_set_hsv(45, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(46, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(47, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(48, HSV_GREEN);      // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_hsv(49, HSV_BLUE);       // ctrl // left-most key on kb
    rgb_matrix_set_hsv(50, HSV_GREEN);      // shift // key right next to trackball
    rgb_matrix_set_hsv(51, HSV_PURPLE);     // cmd // bottom of space/enter key row
    rgb_matrix_set_hsv(52, HSV_PINK);       // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_hsv(53, HSV_CYAN);       // enter key
    rgb_matrix_set_hsv(54, HSV_GREEN);       // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_hsv(55, HSV_GREEN);       // multiline // key below layer button
    rgb_matrix_set_hsv(56, HSV_CYAN);      // ctrl //far right key, 'below' enter key
            break;
////////////////////// MOUSE LAYER RGB SETTINGS //////////////////////
////////////////////// QWERTY LAYER RGB SETTINGS //////////////////////            
        case _QWERTY:
    rgb_matrix_set_hsv(0, HSV_WHITE);       // row1,col6
    rgb_matrix_set_hsv(1, HSV_WHITE);
    rgb_matrix_set_hsv(2, HSV_WHITE);
    rgb_matrix_set_hsv(3, HSV_WHITE);
    rgb_matrix_set_hsv(4, HSV_WHITE);
    rgb_matrix_set_hsv(5, HSV_GOLD);        // tab // row1,col1
    rgb_matrix_set_hsv(6, HSV_WHITE);       // ? // row2,col1
    rgb_matrix_set_hsv(7, HSV_WHITE);
    rgb_matrix_set_hsv(8, HSV_WHITE);
    rgb_matrix_set_hsv(9, HSV_WHITE);
    rgb_matrix_set_hsv(10, HSV_WHITE);
    rgb_matrix_set_hsv(11, HSV_WHITE);      // row2,col6
    rgb_matrix_set_hsv(12, HSV_WHITE);      // row3,col6
    rgb_matrix_set_hsv(13, HSV_WHITE);
    rgb_matrix_set_hsv(14, HSV_WHITE);
    rgb_matrix_set_hsv(15, HSV_WHITE);
    rgb_matrix_set_hsv(16, HSV_WHITE);
    rgb_matrix_set_hsv(17, HSV_CYAN);       // tilde-backtick // row3,col1
    rgb_matrix_set_hsv(18,  HSV_RED);       // backspace
    rgb_matrix_set_hsv(19, HSV_ORANGE);     // delete
    rgb_matrix_set_hsv(20, HSV_GREEN);      // shift
    rgb_matrix_set_hsv(21, HSV_PURPLE);     // cmd
    rgb_matrix_set_hsv(22, HSV_YELLOW);     // alt
    rgb_matrix_set_hsv(23, HSV_RED);        // esc
    rgb_matrix_set_hsv(24, HSV_CHARTREUSE); // _NAV
    rgb_matrix_set_hsv(25, HSV_CYAN);       // tab-r
    rgb_matrix_set_hsv(26, HSV_BLUE);       // tab-l
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_hsv(27, HSV_WHITE);      // row1,col1 // y
    rgb_matrix_set_hsv(28, HSV_WHITE);
    rgb_matrix_set_hsv(29, HSV_WHITE);
    rgb_matrix_set_hsv(30, HSV_WHITE);
    rgb_matrix_set_hsv(31, HSV_WHITE);
    rgb_matrix_set_hsv(32, HSV_CYAN);       // row1,col6 // -_
    rgb_matrix_set_hsv(33, HSV_CYAN);       // row2,col6 // ;:
    rgb_matrix_set_hsv(34, HSV_CYAN);       // "'
    rgb_matrix_set_hsv(35, HSV_WHITE);      // l
    rgb_matrix_set_hsv(36, HSV_WHITE);      // k
    rgb_matrix_set_hsv(37, HSV_WHITE);      // j
    rgb_matrix_set_hsv(38, HSV_WHITE);      // h // row2,col1 
    rgb_matrix_set_hsv(39, HSV_WHITE);      // n // row3,col1  
    rgb_matrix_set_hsv(40, HSV_WHITE);
    rgb_matrix_set_hsv(41, HSV_CYAN);       // <,
    rgb_matrix_set_hsv(42, HSV_CYAN);       // >.
    rgb_matrix_set_hsv(43, HSV_GOLD);       // /?
    rgb_matrix_set_hsv(44, HSV_YELLOW);     // dragscroll toggle //row3, col6 // not sure what this key should be
    rgb_matrix_set_hsv(45, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(46, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(47, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(48, HSV_GREEN);      // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_hsv(49, HSV_BLUE);       // ctrl // left-most key on kb
    rgb_matrix_set_hsv(50, HSV_GREEN);      // shift // key right next to trackball
    rgb_matrix_set_hsv(51, HSV_PURPLE);     // cmd // bottom of space/enter key row
    rgb_matrix_set_hsv(52, HSV_PINK);       // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_hsv(53, HSV_CYAN);       // enter key
    rgb_matrix_set_hsv(54, HSV_GREEN);       // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_hsv(55, HSV_GREEN);       // multiline // key below layer button
    rgb_matrix_set_hsv(56, HSV_CYAN);      // ctrl //far right key, 'below' enter key
            break;
    ////////////////////// QWERTY LAYER RGB SETTINGS //////////////////////            
    ////////////////////// NAV LAYER RGB SETTINGS //////////////////////            
        case _NAV:
    rgb_matrix_set_hsv(0, HSV_WHITE);       // row1,col6
    rgb_matrix_set_hsv(1, HSV_WHITE);
    rgb_matrix_set_hsv(2, HSV_WHITE);
    rgb_matrix_set_hsv(3, HSV_WHITE);
    rgb_matrix_set_hsv(4, HSV_WHITE);
    rgb_matrix_set_hsv(5, HSV_GOLD);        // tab // row1,col1
    rgb_matrix_set_hsv(6, HSV_WHITE);       // ? // row2,col1
    rgb_matrix_set_hsv(7, HSV_WHITE);
    rgb_matrix_set_hsv(8, HSV_WHITE);
    rgb_matrix_set_hsv(9, HSV_WHITE);
    rgb_matrix_set_hsv(10, HSV_WHITE);
    rgb_matrix_set_hsv(11, HSV_WHITE);      // row2,col6
    rgb_matrix_set_hsv(12, HSV_WHITE);      // row3,col6
    rgb_matrix_set_hsv(13, HSV_WHITE);
    rgb_matrix_set_hsv(14, HSV_WHITE);
    rgb_matrix_set_hsv(15, HSV_WHITE);
    rgb_matrix_set_hsv(16, HSV_WHITE);
    rgb_matrix_set_hsv(17, HSV_CYAN);       // tilde-backtick // row3,col1
    rgb_matrix_set_hsv(18,  HSV_RED);       // backspace
    rgb_matrix_set_hsv(19, HSV_ORANGE);     // delete
    rgb_matrix_set_hsv(20, HSV_GREEN);      // shift
    rgb_matrix_set_hsv(21, HSV_PURPLE);     // cmd
    rgb_matrix_set_hsv(22, HSV_YELLOW);     // alt
    rgb_matrix_set_hsv(23, HSV_RED);        // esc
    rgb_matrix_set_hsv(24, HSV_CHARTREUSE); // _NAV
    rgb_matrix_set_hsv(25, HSV_CYAN);       // tab-r
    rgb_matrix_set_hsv(26, HSV_BLUE);       // tab-l
    // RIGHT HALF STARTS HERE
    rgb_matrix_set_hsv(27, HSV_CHARTREUSE);       // PGUP // row1,col1 // y
    rgb_matrix_set_hsv(28, HSV_WHITE);
    rgb_matrix_set_hsv(29, HSV_GREEN);      // up arrow
    rgb_matrix_set_hsv(30, HSV_WHITE);
    rgb_matrix_set_hsv(31, HSV_ORANGE);     // PGDN
    rgb_matrix_set_hsv(32, HSV_CYAN);       // row1,col6 // -_
    rgb_matrix_set_hsv(33, HSV_CYAN);       // row2,col6 // ;:
    rgb_matrix_set_hsv(34, HSV_RED);        // END // "'
    rgb_matrix_set_hsv(35, HSV_GREEN);      // right arrow // l
    rgb_matrix_set_hsv(36, HSV_GREEN);      // down arrow // k
    rgb_matrix_set_hsv(37, HSV_GREEN);      // left arrow // j
    rgb_matrix_set_hsv(38, HSV_CHARTREUSE);       // HOME // h // row2,col1 
    rgb_matrix_set_hsv(39, HSV_WHITE);      // n // row3,col1  
    rgb_matrix_set_hsv(40, HSV_WHITE);
    rgb_matrix_set_hsv(41, HSV_CYAN);       // <,
    rgb_matrix_set_hsv(42, HSV_CYAN);       // >.
    rgb_matrix_set_hsv(43, HSV_GOLD);       // /?
    rgb_matrix_set_hsv(44, HSV_YELLOW);     // dragscroll toggle //row3, col6 // not sure what this key should be
    rgb_matrix_set_hsv(45, HSV_GOLD);       // arrow key
    rgb_matrix_set_hsv(46, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(47, HSV_GREEN);      // arrow key
    rgb_matrix_set_hsv(48, HSV_GOLD);       // arrow key
    // this is the group of two keys on the right thumb cluster right next to the trackball
    rgb_matrix_set_hsv(49, HSV_RED);        // chrome back     // ctrl // left-most key on kb
    rgb_matrix_set_hsv(50, HSV_GREEN);      // multiline       // shift // key right next to trackball
    rgb_matrix_set_hsv(51, HSV_PINK);       // mplay // bottom of space/enter key row
    rgb_matrix_set_hsv(52, HSV_PINK);       // SYMBOLS // key to the 'left' of enter key
    rgb_matrix_set_hsv(53, HSV_CYAN);       // enter key
    rgb_matrix_set_hsv(54, HSV_GREEN);       // space key
    // this is the group of two keys on the right thumb cluster NOT next to the trackball
    rgb_matrix_set_hsv(55, HSV_ORANGE);     // multiline // key below layer button
    rgb_matrix_set_hsv(56, HSV_YELLOW);     // ctrl //far right key, 'below' enter key
        break;
    }
    // info: using one line per key, 3% of flash is used to set one layer of 57 keys per-key rgb    
}

void keyboard_post_init_rgb_matrix(void) {
}

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    return true;
}
