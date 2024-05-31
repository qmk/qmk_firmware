// Copyright 2024 ksmosna (@ksmosna)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "i2c_master.h"
#include "drivers/led/issi/is31fl3733.h"

const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |        G location
 *   |  |        |        B location
 *   |  |        |        | */
    {1, SW1_CS1,   SW2_CS1,   SW3_CS1}, //ESC
    {0, SW10_CS2,   SW11_CS2,   SW12_CS2}, //F1
    {0, SW10_CS3,   SW11_CS3,   SW12_CS3}, //F2
    {0, SW10_CS4,   SW11_CS4,   SW12_CS4}, //F3
    {0, SW10_CS5,   SW11_CS5,   SW12_CS5}, //F4
    {0, SW10_CS6,   SW11_CS6,   SW12_CS6}, //F5
    {0, SW10_CS7,   SW11_CS7,   SW12_CS7}, //F6
    {0, SW10_CS8,   SW11_CS8,   SW12_CS8}, //F7
    {0, SW10_CS9,   SW11_CS9,   SW12_CS9}, //F8
    {0, SW10_CS10,   SW11_CS10,   SW12_CS10}, //F9
    {0, SW10_CS11,   SW11_CS11,   SW12_CS11}, //F10
    {0, SW10_CS12,   SW11_CS12,   SW12_CS12}, //F11
    {0, SW10_CS13,   SW11_CS13,   SW12_CS13}, //F12

    {1, SW4_CS1,   SW5_CS1,   SW6_CS1}, //M1
    {1, SW1_CS2,   SW2_CS2,   SW3_CS2}, //Tylda
    {0, SW7_CS1,   SW8_CS1,   SW9_CS1}, //1
    {0, SW7_CS2,   SW8_CS2,   SW9_CS2}, //2
    {0, SW7_CS3,   SW8_CS3,   SW9_CS3}, //3
    {0, SW7_CS4,   SW8_CS4,   SW9_CS4}, //4
    {0, SW7_CS5,   SW8_CS5,   SW9_CS5}, //5
    {0, SW7_CS6,   SW8_CS6,   SW9_CS6}, //6
    {0, SW7_CS7,   SW8_CS7,   SW9_CS7}, //7
    {0, SW7_CS8,   SW8_CS8,   SW9_CS8}, //8
    {0, SW7_CS9,   SW8_CS9,   SW9_CS9}, //9
    {0, SW7_CS10,   SW8_CS10,   SW9_CS10}, //0
    {0, SW7_CS11,   SW8_CS11,   SW9_CS11}, //-
    {0, SW7_CS12,   SW8_CS12,   SW9_CS12}, //=
    {0, SW7_CS13,   SW8_CS13,   SW9_CS13}, //Backspace
    {0, SW7_CS14,   SW8_CS14,   SW9_CS14}, //PrintScreen
    {0, SW7_CS15,   SW8_CS15,   SW9_CS15}, //ScrollLock
    {0, SW7_CS16,   SW8_CS16,   SW9_CS16}, //Pause

    {1, SW4_CS2,   SW5_CS2,   SW6_CS2}, //M2
    {1, SW1_CS3,   SW2_CS3,   SW3_CS3}, //Tab
    {0, SW4_CS1,   SW5_CS1,   SW6_CS1}, //Q
    {0, SW4_CS2,   SW5_CS2,   SW6_CS2}, //W
    {0, SW4_CS3,   SW5_CS3,   SW6_CS3}, //E
    {0, SW4_CS4,   SW5_CS4,   SW6_CS4}, //R
    {0, SW4_CS5,   SW5_CS5,   SW6_CS5}, //T
    {0, SW4_CS6,   SW5_CS6,   SW6_CS6}, //Y
    {0, SW4_CS7,   SW5_CS7,   SW6_CS7}, //U
    {0, SW4_CS8,   SW5_CS8,   SW6_CS8}, //I
    {0, SW4_CS9,   SW5_CS9,   SW6_CS9}, //O
    {0, SW4_CS10,   SW5_CS10,   SW6_CS10}, //P
    {0, SW4_CS11,   SW5_CS11,   SW6_CS11}, //[
    {0, SW4_CS12,   SW5_CS12,   SW6_CS12}, //]
    {0, SW4_CS13,   SW5_CS13,   SW6_CS13}, //|
    {0, SW4_CS14,   SW5_CS14,   SW6_CS14}, //Ins
    {0, SW4_CS15,   SW5_CS15,   SW6_CS15}, //Home
    {0, SW4_CS16,   SW5_CS16,   SW6_CS16}, //PgUp
    
    {1, SW4_CS3,   SW5_CS3,   SW6_CS3}, //M3
    {1, SW1_CS4,   SW2_CS4,   SW3_CS4}, //Caps
    {0, SW1_CS1,   SW2_CS1,   SW3_CS1}, //A
    {0, SW1_CS2,   SW2_CS2,   SW3_CS2}, //S
    {0, SW1_CS3,   SW2_CS3,   SW3_CS3}, //D
    {0, SW1_CS4,   SW2_CS4,   SW3_CS4}, //F
    {0, SW1_CS5,   SW2_CS5,   SW3_CS5}, //G
    {0, SW1_CS6,   SW2_CS6,   SW3_CS6}, //H
    {0, SW1_CS7,   SW2_CS7,   SW3_CS7}, //J
    {0, SW1_CS8,   SW2_CS8,   SW3_CS8}, //K
    {0, SW1_CS9,   SW2_CS9,   SW3_CS9}, //L
    {0, SW1_CS10,   SW2_CS10,   SW3_CS10}, //;
    {0, SW1_CS11,   SW2_CS11,   SW3_CS11}, //'
    {0, SW1_CS13,   SW2_CS13,   SW3_CS13}, //Enter
    {0, SW1_CS14,   SW2_CS14,   SW3_CS14}, //Del
    {0, SW1_CS15,   SW2_CS15,   SW3_CS15}, //End
    {0, SW1_CS16,   SW2_CS16,   SW3_CS16}, //PgDown

    {1, SW4_CS4,   SW5_CS4,   SW6_CS4}, //M4
    {1, SW1_CS5,   SW2_CS5,   SW3_CS5}, //LShift
    {1, SW10_CS2,   SW11_CS2,   SW12_CS2}, //Z
    {1, SW10_CS3,   SW11_CS3,   SW12_CS3}, //X
    {1, SW10_CS4,   SW11_CS4,   SW12_CS4}, //C
    {1, SW10_CS5,   SW11_CS5,   SW12_CS5}, //V
    {1, SW10_CS6,   SW11_CS6,   SW12_CS6}, //B
    {1, SW10_CS7,   SW11_CS7,   SW12_CS7}, //N
    {1, SW10_CS8,   SW11_CS8,   SW12_CS8}, //M
    {1, SW10_CS9,   SW11_CS9,   SW12_CS9}, //,
    {1, SW10_CS10,   SW11_CS10,   SW12_CS10}, //.
    {1, SW10_CS11,   SW11_CS11,   SW12_CS11}, ///
    {1, SW10_CS13,   SW11_CS13,   SW12_CS13}, //RShift
    {1, SW10_CS15,   SW11_CS15,   SW12_CS15}, //Up

    {1, SW4_CS5,   SW5_CS5,   SW6_CS5}, //M5
    {1, SW1_CS6,   SW2_CS6,   SW3_CS6}, //LCtrl
    {1, SW7_CS1,   SW8_CS1,   SW9_CS1}, //Win
    {1, SW7_CS2,   SW8_CS2,   SW9_CS2}, //LAlt
    {1, SW7_CS6,   SW8_CS6,   SW9_CS6}, //Space
    {1, SW7_CS10,   SW8_CS10,   SW9_CS10}, //RAlt
    {1, SW7_CS11,   SW8_CS11,   SW9_CS11}, //Fn
    {1, SW7_CS12,   SW8_CS12,   SW9_CS12}, //Menu
    {1, SW7_CS13,   SW8_CS13,   SW9_CS13}, //RCtrl
    {1, SW7_CS14,   SW8_CS14,   SW9_CS14}, //Left
    {1, SW7_CS15,   SW8_CS15,   SW9_CS15}, //Down
    {1, SW7_CS16,   SW8_CS16,   SW9_CS16}, //Right
};

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    // Host Keyboard RGB backlight status
    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("Light"), false);
    return false;
}
#endif