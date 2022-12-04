// Copyright 2022 Simon Benezan (@Frooastside)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "walnut.h"

#if defined(RGB_MATRIX_ENABLE)

const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |        G location
 *   |  |        |        B location
 *   |  |        |        | */
    {0, K_1,     J_1,     L_1},
    {0, K_2,     J_2,     L_2},
    {0, K_3,     J_3,     L_3},
    {0, K_4,     J_4,     L_4},
    {0, K_5,     J_5,     L_5},
    {0, K_6,     J_6,     L_6},
    {0, K_7,     J_7,     L_7},
    {0, K_8,     J_8,     L_8},
    {0, K_9,     J_9,     L_9},
    {0, K_10,    J_10,    L_10},
    {0, K_11,    J_11,    L_11},
    {0, K_12,    J_12,    L_12},
    {0, H_1,     G_1,     I_1},
    {0, H_2,     G_2,     I_2},
    {0, H_3,     G_3,     I_3},
    {0, H_4,     G_4,     I_4},
    {0, H_5,     G_5,     I_5},
    {0, H_6,     G_6,     I_6},
    {0, H_7,     G_7,     I_7},
    {0, H_8,     G_8,     I_8},
    {0, H_9,     G_9,     I_9},
    {0, H_10,    G_10,    I_10},
    {0, H_11,    G_11,    I_11},
    {0, H_12,    G_12,    I_12},
    {0, E_1,     D_1,     F_1},
    {0, E_2,     D_2,     F_2},
    {0, E_3,     D_3,     F_3},
    {0, E_4,     D_4,     F_4},
    {0, E_5,     D_5,     F_5},
    {0, E_6,     D_6,     F_6},
    {0, E_7,     D_7,     F_7},
    {0, E_8,     D_8,     F_8},
    {0, E_9,     D_9,     F_9},
    {0, E_10,    D_10,    F_10},
    {0, E_11,    D_11,    F_11},
    {0, E_12,    D_12,    F_12},
    {0, B_1,     A_1,     C_1},
    {0, B_2,     A_2,     C_2},
    {0, B_3,     A_3,     C_3},
    {0, B_4,     A_4,     C_4},
    {0, B_5,     A_5,     C_5},
    {0, B_6,     A_6,     C_6},
    {0, B_7,     A_7,     C_7},
    {0, B_8,     A_8,     C_8},
    {0, B_9,     A_9,     C_9},
    {0, B_10,    A_10,    C_10},
    {0, B_11,    A_11,    C_11},
    {0, B_12,    A_12,    C_12}
};

led_config_t g_led_config = {
    {
        { NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
        { NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
        { NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
        { NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
        { NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
        { NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
        { NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
        { NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
        { NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED }
    }, {
        {0, 62},   {0, 50},   {0, 38},   {0, 26},   {0, 14},   {0, 2},
        {0, 2},    {12, 2},   {24, 2},   {36, 2},   {48, 2},   {60, 2},   {72, 2},   {84, 2},   {96, 2},   {108, 2},  {120, 2},  {132, 2},  {144, 2},  {156, 2},  {168, 2},  {180, 2},  {192, 2},  {204, 2},
        {204, 2},  {204, 14}, {204, 26}, {204, 38}, {204, 50}, {204, 62},
        {204, 62}, {192, 62}, {180, 62}, {168, 62}, {156, 62}, {144, 62}, {132, 62}, {120, 62}, {108, 62}, {96, 62},  {84, 62},  {72, 62},  {60, 62},  {48, 62},  {36, 62},  {24, 62},  {12, 62},  {0, 62}
    }, {
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    }
};

#endif // defined(RGB_MATRIX_ENABLE)
