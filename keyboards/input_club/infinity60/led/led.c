// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef LED_MATRIX_ENABLE
const is31_led g_is31_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *  driver
 *  |   LED address
 *  |   | */
    {0, C1_1}, // LED1
    {0, C1_2}, // LED2
    {0, C1_3}, // LED3
    {0, C1_4}, // LED4
    {0, C1_5}, // LED5
    {0, C1_6}, // LED6
    {0, C1_7}, // LED7
    {0, C1_8}, // LED8

    {0, C2_1}, // LED9
    {0, C2_2}, // LED10
    {0, C2_3}, // LED11
    {0, C2_4}, // LED12
    {0, C2_5}, // LED13
    {0, C2_6}, // LED14/114
    {0, C2_7}, // LED15
    {0, C2_8}, // LED16

    {0, C3_1}, // LED17
    {0, C3_2}, // LED18
    {0, C3_3}, // LED19
    {0, C3_4}, // LED20
    {0, C3_5}, // LED21
    {0, C3_6}, // LED22
    {0, C3_7}, // LED23
    {0, C3_8}, // LED24

    {0, C4_1}, // LED25
    {0, C4_2}, // LED26
    {0, C4_3}, // LED27
    {0, C4_4}, // LED28
    {0, C4_5}, // LED29
    {0, C4_6}, // LED30
    {0, C4_7}, // LED31
    {0, C4_8}, // LED32

    {0, C5_1}, // LED33
    {0, C5_2}, // LED34
    {0, C5_3}, // LED35
    {0, C5_4}, // LED36
    {0, C5_5}, // LED37
    {0, C5_6}, // LED38
    {0, C5_7}, // LED39
    {0, C5_8}, // LED40

    {0, C6_1}, // LED41
    {0, C6_2}, // LED42
    {0, C6_3}, // LED43
    {0, C6_4}, // LED44
    {0, C6_5}, // LED45
    {0, C6_6}, // LED46
    {0, C6_7}, // LED47
    {0, C6_8}, // LED48

    {0, C7_1}, // LED49
    {0, C7_2}, // LED50
    {0, C7_3}, // LED51
    {0, C7_4}, // LED52
    {0, C7_5}, // LED53
    {0, C7_6}, // LED54/154
    {0, C7_7}, // LED55
    {0, C7_8}, // LED56/156

    {0, C8_1}, // LED57/157
    {0, C8_2}, // LED58/158
    {0, C8_3}, // LED59/159
    {0, C8_4}, // LED60/160
    {0, C8_5}, // LED61/161
    {0, C8_6}, // LED62/162
    {0, C8_7}  // LED63/163
};
#endif
