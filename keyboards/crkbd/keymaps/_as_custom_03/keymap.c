/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "config.h" 

enum layers {
    _QWERTY,
    _NUMP,
    _LOWER,
    _FUNC,
    _RGB,
};

uint8_t mod_state;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_QWERTY] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T			             ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSPC ,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G			             ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B  		                 ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_ESC  ,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_LGUI ,MO(1)   ,KC_SPC     ,KC_ENT  ,MO(2)   ,MO(3)
                                        //`--------------------------'  `--------------------------'

        ),

    [_NUMP] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
           KC_TAB  ,XXXXXXX ,KC_UP   ,XXXXXXX ,XXXXXXX ,KC_NO	                     ,KC_P7   ,KC_P8   ,KC_P9   ,XXXXXXX ,XXXXXXX ,KC_BSPC ,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           KC_LSFT ,KC_LEFT ,KC_DOWN ,KC_RGHT ,XXXXXXX ,KC_NO  		                 ,KC_P4   ,KC_P5   ,KC_P6   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           KC_LCTL ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_NO			             ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PDOT ,XXXXXXX ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               KC_LGUI ,_______ ,KC_SPC     ,KC_ENT  ,KC_P0   ,MO(4)
                                            //`--------------------------'  `--------------------------'
        ),

    [_LOWER] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
           KC_TAB  ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC		                 ,KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,KC_BSPC ,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           KC_LSFT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_NO			             ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LBRC ,KC_RBRC ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           KC_LCTL ,XXXXXXX ,KC_PSLS ,XXXXXXX ,KC_HASH ,KC_UNDS   		             ,KC_PMNS ,KC_PLUS ,KC_PEQL ,KC_LT   ,KC_GT   ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               KC_LGUI ,XXXXXXX   ,KC_SPC     ,KC_ENT  ,_______ ,XXXXXXX
                                            //`--------------------------'  `--------------------------'
        ),

    [_FUNC] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
           XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5                        ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           XXXXXXX ,KC_F11  ,KC_F12  ,XXXXXXX ,XXXXXXX ,XXXXXXX                      ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                      ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               KC_LGUI ,XXXXXXX ,KC_SPC     ,KC_ENT  ,XXXXXXX ,_______
                                            //`--------------------------'  `--------------------------'
        ),

    [_RGB] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
           QK_BOOT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                      ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           RGB_TOG ,RGB_HUI ,RGB_SAI ,RGB_VAI ,XXXXXXX ,XXXXXXX                      ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           RGB_MOD ,RGB_HUD ,RGB_SAD ,RGB_VAD ,XXXXXXX, XXXXXXX                      ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               KC_LGUI ,_______ ,KC_SPC     ,KC_ENT  ,_______ ,XXXXXXX
                                            //`--------------------------'  `--------------------------'
        )};

// Luna
/* KEYBOARD PET START */

/* settings */
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

/* advanced settings */
#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 96            // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;

bool isBarking  = false;
bool isJumping  = false;
bool showedJump = true;
bool isSneaking = false;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);

        } else if (isSneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[current_frame], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

#if OLED_TIMEOUT > 0
    /* the animation prevents the normal timeout from occuring */
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }
#endif

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

/* KEYBOARD PET END */

/* KEYBOARD PET RENDER START */
static void print_status_narrow(void) {
    render_luna(0, 13);
}
/* KEYBOARD PET RENDER END */


/* KEYBOARD PET STATUS START */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
    }
    return true;
};
/* KEYBOARD PET STATUS END */

/* 32 * 32 logo */
static void render_logo(void) {
    static const char PROGMEM hell_logo[] = {0x00, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x1c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x1e, 0x06, 0x00, 0x0c, 0x1c, 0x18, 0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0x80, 0x00, 0x01, 0x03, 0x07, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x70, 0x60, 0x00, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x70, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x07, 0x03, 0x01, 0x00, 0xf8, 0xf8, 0x80, 0x80, 0x80, 0xf8, 0xf8, 0x00, 0x80, 0xc0, 0xc0, 0x40, 0xc0, 0xc0, 0x80, 0x00, 0xf8, 0xf8, 0x00, 0xf8, 0xf8, 0x00, 0x08, 0x38, 0x08, 0x00, 0x38, 0x08, 0x30, 0x08, 0x38, 0x00, 0x1f, 0x1f, 0x01, 0x01, 0x01, 0x1f, 0x1f, 0x00, 0x0f, 0x1f, 0x1a, 0x12, 0x1a, 0x1b, 0x0b, 0x00, 0x1f, 0x1f, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    oled_write_raw_P(hell_logo, sizeof(hell_logo));
}

static void print_logo_narrow(void) {
    render_logo();

    /* wpm counter */
    uint8_t n = get_current_wpm();
    char    wpm_str[4];
    oled_set_cursor(0, 14);
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10;
    oled_write(wpm_str, false);

    oled_set_cursor(0, 15);
    oled_write(" wpm", false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    /* KEYBOARD PET VARIABLES START */

    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    /* KEYBOARD PET VARIABLES END */

    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
    return false;
}

//Per key lights
bool rgb_matrix_indicators_user(void) {
#ifdef RGB_MATRIX_ENABLE
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            // isSneaking = false;
            mod_state  = get_mods();
            for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                // if (mod_state & MOD_MASK_SHIFT) {
                //     // isBarking = true;
                //     rgb_matrix_set_color(52, 255, 255, 255);
                //     rgb_matrix_set_color(i, 255, 150, 0);
                // } else if (mod_state & MOD_MASK_GUI || mod_state & MOD_MASK_CTRL) {
                    // isBarking = true;
                    // rgb_matrix_set_color(15, 255, 0, 0);
                    switch (i) {
                        case 0 ... 53:                           // all keys
                            rgb_matrix_set_color(i, 255, 255, 255);    // off
                            break;
                        // case 0 ... 5:                            // underglow left side
                        // case 9:                                  // cmd + T white (new tab)
                        // case 11:                                 // cmd + F white (find)
                        // case 18:                                 // cmd + W white (close tab)
                        // case 19:                                 // cmd + S white (save)
                        // case 21:                                 // cmd + Z white (undo)
                        // case 22:                                 // cmd + A white (select all)
                        // case 27 ... 32:                          // underglow right side
                        // case 43:                                 // cmd + K white (comment for desktop remote)
                        // case 48:                                 // cmd + / white (comment line)
                        //     rgb_matrix_set_color(i, 255, 255, 255); // white
                        //     break;
                        // case 6:                                  // space bar off
                        // case 24 ... 26:                          // left column off
                        // case 33:                                 // backspace off
                        // case 41:                                 // shift off
                        // case 51 ... 53:                          // right column off
                        //     rgb_matrix_set_color(i, 0, 0, 0);    //off
                        //     break;
                    }
            //         if (mod_state & MOD_MASK_GUI) {
            //             rgb_matrix_set_color(12, 255, 255, 255); // white V key
            //             rgb_matrix_set_color(15, 255, 255, 255); // white C key
            //             rgb_matrix_set_color(20, 255, 255, 255); // white X key
            //         } else {
            //         }
            //     } else if (mod_state & MOD_MASK_ALT) {
            //         // isBarking = true;
            //     } else {
            //         // isBarking = false;
            //         rgb_matrix_set_color(14, 0, 0, 0);          // command key off
                // }
            }
            // rgb_matrix_set_color(13, 23, 181, 255);             // cyan layer
            // rgb_matrix_set_color(40, 255, 33, 0);               // orange layer
            break;

        case _NUMP:
            // isSneaking = true;
            for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                switch (i) {
                    case 7:                                     // B key off
                    case 8:                                     // G key off
                    case 11:                                    // F key off
                    case 12:                                    // V key off
                    case 16:                                    // D key off
                    case 19 ... 21:                             // S, X, Z keys off
                    case 25:                                    // tab key off
                    case 26:                                    // shift key off
                    case 52 ... 53:                             // right column off
                        rgb_matrix_set_color(i, 0, 0, 0);       // off
                        break;
                    // case 15:                                    // Ç key
                    // case 22:                                    // Ã key
                    // case 24:                                    // Launch (F4)
                    // case 40:                                    // Active layer
                    //     rgb_matrix_set_color(i, 255, 255, 255); // white
                    //     break;
                    // case 13:                                    // active layer
                    //     rgb_matrix_set_color(i, 0, 255, 0);     // green
                    //     break;
                    // case 42:                                    // , shifted key
                    // case 47 ... 49:                             // . / ; shifted keys
                    //     rgb_matrix_set_color(i, 255, 214, 0);   // yellow
                    //     break;
                    // default:
                    //     rgb_matrix_set_color(i, 255, 33, 0);    // orange
                }
            }
            break;

        case _LOWER:
            isSneaking = true;
            for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                switch (i) {
                    case 7:                                     // Delete key
                    case 51:                                    // ESC key
                        rgb_matrix_set_color(i, 255, 0, 0);     // red
                        break;
                    case 12:                                    // V key off
                    case 15:                                    // C key off
                    case 20:                                    // X key off
                    case 21:                                    // Z key off

                    case 26:                                    // shift key off
                    case 52 ... 53:                             // right column off
                        rgb_matrix_set_color(i, 0, 0, 0);       // off
                        break;
                    case 11:                                    // Right arrow key
                    case 13:                                    // Active layer
                    case 16:                                    // Up arrow key
                    case 19:                                    // Down arrow key
                    case 22:                                    // Left arrow key
                    case 24:                                    // Print
                        rgb_matrix_set_color(i, 255, 255, 255); // white
                        break;
                    case 8:                                     // Enter key
                    case 40:                                    // Activate Numpad
                        rgb_matrix_set_color(i, 0, 255, 0);     // green
                        break;
                    case 42:                                    // , shifted key
                    case 47 ... 49:                             // . / ; shifted keys
                    case 25:                                    // opens emoji dialog (on macOS)
                        rgb_matrix_set_color(i, 255, 214, 0);   // yellow
                        break;
                    default:
                        rgb_matrix_set_color(i, 23, 181, 255);  // cyan
                }
            }

            break;

        case _FUNC:
            isSneaking = true;
            for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                switch (i) {
                    case 12:                                    // RGB speed-
                    case 15:                                    // RGB brigthness-
                    case 20:                                    // RGB saturation-
                    case 21:                                    // RGB hue-
                    case 49:                                    // Numpad -
                    case 51:                                    // Numpad /
                        rgb_matrix_set_color(i, 255, 0, 0);     // red
                        break;
                    case 8 ... 10:                              // G T R off
                    case 17:                                    // E off
                    case 18:                                    // W off
                    case 23:                                    // Q off
                    case 25:                                    // Tab off
                    case 26:                                    // LShift off
                    case 33:                                    // Backspace off
                    case 35:                                    // H off
                    case 36:                                    // Y off
                    case 53:                                    // RShift off
                        rgb_matrix_set_color(i, 0, 0, 0);       // off
                        break;
                    case 6:                                     // Space bar off
                    case 13:                                    // Return to default layer
                    case 16:                                    // RGB brigthness+
                    case 24:                                    // RGB toggle
                    case 37 ... 47:                             // Numpad numbers
                    case 52:                                    // Enter key
                        rgb_matrix_set_color(i, 255, 255, 255); // white
                        break;
                    case 11:                                    // RGB speed+
                    case 19:                                    // RGB saturation+
                    case 22:                                    // RGB hue+
                    case 48:                                    // Numpad +
                        rgb_matrix_set_color(i, 0, 255, 0);     // green
                        break;
                    case 34:                                    // . numpad key
                        rgb_matrix_set_color(i, 255, 214, 0);   // yellow
                        break;
                }
                rgb_matrix_set_color(13, 23, 181, 255);         // Activate cyan layer
                rgb_matrix_set_color(40, 255, 33, 0);           // Activate orange layer
                rgb_matrix_set_color(50, 0, 33, 255);           // Numpad *
                rgb_matrix_set_color(14, 0, 255, 0);            // Green layer active
            }
    }
    return false;
};
#endif
