#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
    {0, CS3_SW8, CS2_SW8, CS1_SW8},        //   ESC 0
    {0, CS3_SW6, CS2_SW6, CS1_SW6},        //   F1
    {0, CS3_SW4, CS2_SW4, CS1_SW4},        //   F2
    {0, CS3_SW2, CS2_SW2, CS1_SW2},        //   F3
    {0, CS3_SW1, CS2_SW1, CS1_SW1},        //   F4
    {0, CS3_SW3, CS2_SW3, CS1_SW3},        //   F5
    {0, CS3_SW5, CS2_SW5, CS1_SW5},        //   F6
    {0, CS3_SW7, CS2_SW7, CS1_SW7},        //   F7
    {0, CS3_SW9, CS2_SW9, CS1_SW9},        //   F8
    {1, CS3_SW8, CS2_SW8, CS1_SW8},        //   F9
    {1, CS3_SW6, CS2_SW6, CS1_SW6},        //   F10
    {1, CS3_SW4, CS2_SW4, CS1_SW4},        //   F11
    {1, CS3_SW2, CS2_SW2, CS1_SW2},        //   F12 
    {1, CS3_SW1, CS2_SW1, CS1_SW1},        //   PGUP
    {1, CS3_SW3, CS2_SW3, CS1_SW3},        //   PGDN
    {1, CS3_SW5, CS2_SW5, CS1_SW5},        //   DEL  
    {1, CS3_SW7, CS2_SW7, CS1_SW7},        //   HOME
    {1, CS3_SW9, CS2_SW9, CS1_SW9},        //   END   17

    {0, CS6_SW8, CS5_SW8, CS4_SW8},        //  ~  18
    {0, CS6_SW6, CS5_SW6, CS4_SW6},        //  1
    {0, CS6_SW4, CS5_SW4, CS4_SW4},        //  2
    {0, CS6_SW2, CS5_SW2, CS4_SW2},        //  3
    {0, CS6_SW1, CS5_SW1, CS4_SW1},        //  4
    {0, CS6_SW3, CS5_SW3, CS4_SW3},        //  5
    {0, CS6_SW5, CS5_SW5, CS4_SW5},        //  6
    {0, CS6_SW7, CS5_SW7, CS4_SW7},        //  7
    {0, CS6_SW9, CS5_SW9, CS4_SW9},        //  8
    {1, CS6_SW8, CS5_SW8, CS4_SW8},        //  9
    {1, CS6_SW6, CS5_SW6, CS4_SW6},        //  0
    {1, CS6_SW4, CS5_SW4, CS4_SW4},        //  -
    {1, CS6_SW2, CS5_SW2, CS4_SW2},        //  =
    {1, CS6_SW1, CS5_SW1, CS4_SW1},        //  Backspace
    {1, CS6_SW3, CS5_SW3, CS4_SW3},        //  NUM
    {1, CS6_SW5, CS5_SW5, CS4_SW5},        //  /
    {1, CS6_SW7, CS5_SW7, CS4_SW7},        //  *
    {1, CS6_SW9, CS5_SW9, CS4_SW9},        //  -   35


    {0, CS9_SW8, CS8_SW8, CS7_SW8},        //  Tab   36
    {0, CS9_SW6, CS8_SW6, CS7_SW6},        //  q
    {0, CS9_SW4, CS8_SW4, CS7_SW4},        //  w
    {0, CS9_SW2, CS8_SW2, CS7_SW2},        //  e
    {0, CS9_SW1, CS8_SW1, CS7_SW1},        //  r
    {0, CS9_SW3, CS8_SW3, CS7_SW3},        //  t
    {0, CS9_SW5, CS8_SW5, CS7_SW5},        //  y
    {0, CS9_SW7, CS8_SW7, CS7_SW7},        //  u
    {0, CS9_SW9, CS8_SW9, CS7_SW9},        //  i
    {1, CS9_SW8, CS8_SW8, CS7_SW8},        //  o
    {1, CS9_SW6, CS8_SW6, CS7_SW6},        //  p
    {1, CS9_SW4, CS8_SW4, CS7_SW4},        //  [
    {1, CS9_SW2, CS8_SW2, CS7_SW2},        //  ]
    {1, CS9_SW1, CS8_SW1, CS7_SW1},        //  |
    {1, CS9_SW3, CS8_SW3, CS7_SW3},        //  7
    {1, CS9_SW5, CS8_SW5, CS7_SW5},        //  8
    {1, CS9_SW7, CS8_SW7, CS7_SW7},        //  9   52
        

    {0, CS12_SW8, CS11_SW8, CS10_SW8},        //  caps   53
    {0, CS12_SW6, CS11_SW6, CS10_SW6},        //  a
    {0, CS12_SW4, CS11_SW4, CS10_SW4},        //  s
    {0, CS12_SW2, CS11_SW2, CS10_SW2},        //  d
    {0, CS12_SW1, CS11_SW1, CS10_SW1},        //  f
    {0, CS12_SW3, CS11_SW3, CS10_SW3},        //  g
    {0, CS12_SW5, CS11_SW5, CS10_SW5},        //  h
    {0, CS12_SW7, CS11_SW7, CS10_SW7},        //  j
    {0, CS12_SW9, CS11_SW9, CS10_SW9},        //  k
    {1, CS12_SW8, CS11_SW8, CS10_SW8},        //  l
    {1, CS12_SW6, CS11_SW6, CS10_SW6},        //  ;
    {1, CS12_SW4, CS11_SW4, CS10_SW4},        //  '
    {1, CS12_SW2, CS11_SW2, CS10_SW2},        //  enter
    {1, CS12_SW3, CS11_SW3, CS10_SW3},        //  4
    {1, CS12_SW5, CS11_SW5, CS10_SW5},        //  5
    {1, CS12_SW7, CS11_SW7, CS10_SW7},        //  6   
    {1, CS12_SW9, CS11_SW9, CS10_SW9},        //  +    69

    {0, CS15_SW8, CS14_SW8, CS13_SW8},        //  shift-L   70
    {0, CS15_SW6, CS14_SW6, CS13_SW6},        //  z   
    {0, CS15_SW4, CS14_SW4, CS13_SW4},        //  x
    {0, CS15_SW2, CS14_SW2, CS13_SW2},        //  c
    {0, CS15_SW1, CS14_SW1, CS13_SW1},        //  v
    {0, CS15_SW3, CS14_SW3, CS13_SW3},        //  b
    {0, CS15_SW5, CS14_SW5, CS13_SW5},        //  n
    {0, CS15_SW7, CS14_SW7, CS13_SW7},        //  m
    {0, CS15_SW9, CS14_SW9, CS13_SW9},        //  ,
    {1, CS15_SW8, CS14_SW8, CS13_SW8},        //  .
    {1, CS15_SW6, CS14_SW6, CS13_SW6},        //  /
    {1, CS15_SW4, CS14_SW4, CS13_SW4},        //  shift-R
    {1, CS15_SW2, CS14_SW2, CS13_SW2},        //  up
    {1, CS15_SW3, CS14_SW3, CS13_SW3},        //  1
    {1, CS15_SW5, CS14_SW5, CS13_SW5},        //  2
    {1, CS15_SW7, CS14_SW7, CS13_SW7},        //  3   85
                                                             
    {0, CS18_SW8, CS17_SW8, CS16_SW8},        //  ctrl-L   86
    {0, CS18_SW6, CS17_SW6, CS16_SW6},        //  win
    {0, CS18_SW4, CS17_SW4, CS16_SW4},        //  alt-L
    {0, CS18_SW3, CS17_SW3, CS16_SW3},        //  space
    {0, CS18_SW9, CS17_SW9, CS16_SW9},        //  alt-R
    {1, CS18_SW8, CS17_SW8, CS16_SW8},        //  Fn
    {1, CS18_SW6, CS17_SW6, CS16_SW6},        //  ctrl-R
    {1, CS18_SW4, CS17_SW4, CS16_SW4},        //  left
    {1, CS18_SW2, CS17_SW2, CS16_SW2},        //  down
    {1, CS18_SW3, CS17_SW3, CS16_SW3},        //  right
    {1, CS18_SW5, CS17_SW5, CS16_SW5},        //  0
    {1, CS18_SW7, CS17_SW7, CS16_SW7},        //  .     
    {1, CS18_SW9, CS17_SW9, CS16_SW9},        //  enter   98  

    {1, CS12_SW1, CS11_SW1, CS10_SW1},        //      99
    {1, CS15_SW1, CS14_SW1, CS13_SW1}        //     100
};
#endif