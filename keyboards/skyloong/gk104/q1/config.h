// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MAC_PIN C13
#define DEBOUNCE 10

#ifdef ENCODER_ENABLE
#    define ENCODER_MAP_KEY_DELAY 20
#endif

#ifdef RGB_MATRIX_ENABLE
#    define AW20216S_CS_PIN_1 B12
#    define AW20216S_CS_PIN_2 B11
// Hardware enable lines may be connected to the same pin
#    define AW20216S_EN_PIN_1 B5
#    define AW20216S_EN_PIN_2 B5

#    define NUM_LOCK_INDEX 31
#    define WIN_MOD_INDEX 23
#    define MAC_MOD_INDEX 24
#    define WIN_LOCK_INDEX 75
#    define CAPS_LOCK_INDEX 35
#    define SCR_LOCK_INDEX 14
#    define SDB B5
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#endif // RGB_MATRIX_ENABLE

/*
 *LED display driver.74HC595 Serial to parallel control LED field on/off.
 *  data(default):1-on/0-off
 *    bit0 --- MAC layer indicator
 *    bit1 --- Win layer indicator
 *    bit2 --- CAPS indicator
 *    bit3 --- NUM indicator
 *    bit4 --- SCR indicator
 *    bit7 --- Skyloong LOGO display
 */


#define MAC_ON 0b00000001
#define WIN_ON 0b00000010
#define CAPS_ON 0b00000100
#define NUM_ON 0b00001000
#define SCR_ON 0b00010000
#define SKYLOONG 0b10000000


