// Copyright 2022 Simon Benezan (@Frooastside)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"

#if defined(RGB_MATRIX_ENABLE)

const is31fl3737_led_t PROGMEM g_is31fl3737_leds[IS31FL3737_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |        G location
 *   |  |        |        B location
 *   |  |        |        | */
    {0, SW11_CS1,     SW10_CS1,     SW12_CS1},
    {0, SW11_CS2,     SW10_CS2,     SW12_CS2},
    {0, SW11_CS3,     SW10_CS3,     SW12_CS3},
    {0, SW11_CS4,     SW10_CS4,     SW12_CS4},
    {0, SW11_CS5,     SW10_CS5,     SW12_CS5},
    {0, SW11_CS6,     SW10_CS6,     SW12_CS6},
    {0, SW11_CS7,     SW10_CS7,     SW12_CS7},
    {0, SW11_CS8,     SW10_CS8,     SW12_CS8},
    {0, SW11_CS9,     SW10_CS9,     SW12_CS9},
    {0, SW11_CS10,    SW10_CS10,    SW12_CS10},
    {0, SW11_CS11,    SW10_CS11,    SW12_CS11},
    {0, SW11_CS12,    SW10_CS12,    SW12_CS12},
    {0, SW8_CS1,     SW7_CS1,     SW9_CS1},
    {0, SW8_CS2,     SW7_CS2,     SW9_CS2},
    {0, SW8_CS3,     SW7_CS3,     SW9_CS3},
    {0, SW8_CS4,     SW7_CS4,     SW9_CS4},
    {0, SW8_CS5,     SW7_CS5,     SW9_CS5},
    {0, SW8_CS6,     SW7_CS6,     SW9_CS6},
    {0, SW8_CS7,     SW7_CS7,     SW9_CS7},
    {0, SW8_CS8,     SW7_CS8,     SW9_CS8},
    {0, SW8_CS9,     SW7_CS9,     SW9_CS9},
    {0, SW8_CS10,    SW7_CS10,    SW9_CS10},
    {0, SW8_CS11,    SW7_CS11,    SW9_CS11},
    {0, SW8_CS12,    SW7_CS12,    SW9_CS12},
    {0, SW5_CS1,     SW4_CS1,     SW6_CS1},
    {0, SW5_CS2,     SW4_CS2,     SW6_CS2},
    {0, SW5_CS3,     SW4_CS3,     SW6_CS3},
    {0, SW5_CS4,     SW4_CS4,     SW6_CS4},
    {0, SW5_CS5,     SW4_CS5,     SW6_CS5},
    {0, SW5_CS6,     SW4_CS6,     SW6_CS6},
    {0, SW5_CS7,     SW4_CS7,     SW6_CS7},
    {0, SW5_CS8,     SW4_CS8,     SW6_CS8},
    {0, SW5_CS9,     SW4_CS9,     SW6_CS9},
    {0, SW5_CS10,    SW4_CS10,    SW6_CS10},
    {0, SW5_CS11,    SW4_CS11,    SW6_CS11},
    {0, SW5_CS12,    SW4_CS12,    SW6_CS12},
    {0, SW2_CS1,     SW1_CS1,     SW3_CS1},
    {0, SW2_CS2,     SW1_CS2,     SW3_CS2},
    {0, SW2_CS3,     SW1_CS3,     SW3_CS3},
    {0, SW2_CS4,     SW1_CS4,     SW3_CS4},
    {0, SW2_CS5,     SW1_CS5,     SW3_CS5},
    {0, SW2_CS6,     SW1_CS6,     SW3_CS6},
    {0, SW2_CS7,     SW1_CS7,     SW3_CS7},
    {0, SW2_CS8,     SW1_CS8,     SW3_CS8},
    {0, SW2_CS9,     SW1_CS9,     SW3_CS9},
    {0, SW2_CS10,    SW1_CS10,    SW3_CS10},
    {0, SW2_CS11,    SW1_CS11,    SW3_CS11},
    {0, SW2_CS12,    SW1_CS12,    SW3_CS12}
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
