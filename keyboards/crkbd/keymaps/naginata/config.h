/* Copyright 2018-2019 eswai <@eswai>
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

#undef PRODUCT
#define PRODUCT         Crkbd Naginata Style

#define SELECT_SOFT_SERIAL_SPEED 2

// 薙刀式
#define NAGINATA_JDOUJI // 順序つきの同時押しに対応する
#define NAGINATA_TATEGAKI // カーソル移動縦書き用（オリジナル）
// #define NAGINATA_YOKOGAKI // カーソル移動横書き用
#define DQWERTY // IME ON/OFFをQWERTYで(FG, HJ)
// #define DEUCALYN
// #define DWORKMAN
// #define NAGINATA_EDIT_WIN // 編集モード Windows用 JP106
#define NAGINATA_EDIT_MAC // 編集モード Mac用 JP106
#define COMBO_COUNT 2
#define COMBO_TERM 300
// 薙刀式

//#define USE_MATRIX_I2C

#define QMK_ESC_OUTPUT F4 // usually COL
#define QMK_ESC_INPUT D4 // usually ROW
#define QMK_LED B0

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SSD1306OLED

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 300
#define PERMISSIVE_HOLD

#undef RGBLED_NUM
// #define RGBLIGHT_ANIMATIONS
// #define RGBLIGHT_EFFECT_BREATHING
// #define RGBLIGHT_EFFECT_BREATHE_TABLE
// #define RGBLIGHT_EFFECT_RAINBOW_MOOD
// #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #define RGBLIGHT_EFFECT_SNAKE
// #define RGBLIGHT_EFFECT_KNIGHT
// #define RGBLIGHT_EFFECT_CHRISTMAS
// #define RGBLIGHT_EFFECT_STATIC_GRADIENT
// #define RGBLIGHT_EFFECT_RGB_TEST
// #define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define DISABLE_LEADER

// #ifndef NO_DEBUG
// #define NO_DEBUG
// #endif // !NO_DEBUG
// #if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
// #define NO_PRINT
// #endif // !NO_PRINT

#define USB_MAX_POWER_CONSUMPTION 100