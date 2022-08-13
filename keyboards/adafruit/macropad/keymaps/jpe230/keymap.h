/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#pragma once

#include QMK_KEYBOARD_H

#include "i2c_master.h"
#include "transpiler.h"
#include "lib/ds3231/ds3231.h"
#include "oled/oled_handler.h"
#include "rgb/rgb_handler.h"

#ifdef DISABLE_SECRETS
    #define PASSWORD_LEN 0
#endif

#ifdef VIA_ENABLE
    #define USER_START USER00
#else
    #define USER_START SAFE_RANGE
#endif

enum MACROPAD_KEYCODES {
    MC_OLED = USER_START,// Toggle OLED
    MC_INDI,             // Show Indicators
    MC_MSKI,             // Mask Indicators
    MC_SHWA,             // Show Anim
    MC_ODEF,             // Select Default OLED
    MC_OBNC,             // Select Bongo Cat OLED
    MC_OLOG,             // Select Logo OLED,
    LS_BTN0,             // Lockscreen Button 0
    LS_BTN1,             // Lockscreen Button 1
    LS_BTN2,             // Lockscreen Button 2
    LS_BTN3,             // Lockscreen Button 3
    LS_BTN4,             // Lockscreen Button 4
    LS_BTN5,             // Lockscreen Button 5
    LS_BTN6,             // Lockscreen Button 6
    LS_BTN7,             // Lockscreen Button 7
    LS_BTN8,             // Lockscreen Button 8
    LS_BTN9,             // Lockscreen Button 9
    LS_BACK,             // Lockscreen BackSpace
    OTPBTN0,             // OTP Button 0
    OTPBTN1,             // OTP Button 1
    OTPBTN2,             // OTP Button 2
    OTPBTN3,             // OTP Button 3
    OTPBTN4,             // OTP Button 4
    OTPBTN5,             // OTP Button 5
    OTPBTN6,             // OTP Button 6
    OTPBTN7,             // OTP Button 7
    OTPBTN8,             // OTP Button 8
    OTPBTN9,             // OTP Button 9
    TRANS_KEYCODES_ENUM
};

/* -----------------------
 * Custom Configuration
 * -----------------------
 */
#define SHOW_DEFAULT 1500
#define RGB_IDLE_TIMEOUT 60000

/* -----------------------
 * Prototypes
 * -----------------------
 */
void handle_layer_move(uint8_t layer);