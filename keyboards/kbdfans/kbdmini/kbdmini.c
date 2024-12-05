#include "quantum.h"

const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
    { 0, SW2_CS9,  SW1_CS9,  SW3_CS9  }, //LA33
    { 0, SW2_CS10, SW1_CS10, SW3_CS10 }, //LA37
    { 0, SW2_CS11, SW1_CS11, SW3_CS11 }, //LA41
    { 0, SW2_CS12, SW1_CS12, SW3_CS12 }, //LA45
    { 0, SW2_CS13, SW1_CS13, SW3_CS13 }, //LA49
    { 0, SW2_CS14, SW1_CS14, SW3_CS14 }, //LA53
    { 0, SW2_CS15, SW1_CS15, SW3_CS15 }, //LA57
    { 0, SW2_CS6,  SW1_CS6,  SW3_CS6  }, //LA21
    { 0, SW2_CS5,  SW1_CS5,  SW3_CS5  }, //LA17
    { 0, SW2_CS4,  SW1_CS4,  SW3_CS4  }, //LA13
    { 0, SW2_CS3,  SW1_CS3,  SW3_CS3  }, //LA9
    { 0, SW2_CS2,  SW1_CS2,  SW3_CS2  }, //LA5
    { 0, SW2_CS1,  SW1_CS1,  SW3_CS1  }, //LA1

    { 0, SW5_CS9,  SW4_CS9,  SW6_CS9  }, //LA34
    { 0, SW5_CS10, SW4_CS10, SW6_CS10 }, //LA38
    { 0, SW5_CS11, SW4_CS11, SW6_CS11 }, //LA42
    { 0, SW5_CS12, SW4_CS12, SW6_CS12 }, //LA46
    { 0, SW5_CS13, SW4_CS13, SW6_CS13 }, //LA50
    { 0, SW5_CS14, SW4_CS14, SW6_CS14 }, //LA54
    { 0, SW5_CS15, SW4_CS15, SW6_CS15 }, //LA58
    { 0, SW5_CS6,  SW4_CS6,  SW6_CS6  }, //LA22
    { 0, SW5_CS5,  SW4_CS5,  SW6_CS5  }, //LA18
    { 0, SW5_CS4,  SW4_CS4,  SW6_CS4  }, //LA14
    { 0, SW5_CS3,  SW4_CS3,  SW6_CS3  }, //LA10
    { 0, SW5_CS2,  SW4_CS2,  SW6_CS2  }, //LA6
    { 0, SW5_CS1,  SW4_CS1,  SW6_CS1  }, //LA2

    { 0, SW8_CS9,  SW7_CS9,  SW9_CS9  }, //LA35
    { 0, SW8_CS10, SW7_CS10, SW9_CS10 }, //LA39
    { 0, SW8_CS11, SW7_CS11, SW9_CS11 }, //LA43
    { 0, SW8_CS12, SW7_CS12, SW9_CS12 }, //LA47
    { 0, SW8_CS13, SW7_CS13, SW9_CS13 }, //LA51
    { 0, SW8_CS14, SW7_CS14, SW9_CS14 }, //LA55
    { 0, SW8_CS15, SW7_CS15, SW9_CS15 }, //LA59
    { 0, SW8_CS6,  SW7_CS6,  SW9_CS6  }, //LA23
    { 0, SW8_CS5,  SW7_CS5,  SW9_CS5  }, //LA19
    { 0, SW8_CS4,  SW7_CS4,  SW9_CS4  }, //LA15
    { 0, SW8_CS3,  SW7_CS3,  SW9_CS3  }, //LA11
    { 0, SW8_CS2,  SW7_CS2,  SW9_CS2  }, //LA7
    { 0, SW8_CS1,  SW7_CS1,  SW9_CS1  }, //LA3

    { 0, SW11_CS9,  SW10_CS9,  SW12_CS9  }, //LA36
    { 0, SW11_CS10, SW10_CS10, SW12_CS10 }, //LA40
    { 0, SW11_CS11, SW10_CS11, SW12_CS11 }, //LA44
    { 0, SW11_CS12, SW10_CS12, SW12_CS12 }, //LA48
    { 0, SW11_CS13, SW10_CS13, SW12_CS13 }, //LA52
    { 0, SW11_CS14, SW10_CS14, SW12_CS14 }, //LA56
    { 0, SW11_CS15, SW10_CS15, SW12_CS15 }, //LA60
    { 0, SW11_CS6,  SW10_CS6,  SW12_CS6  }, //LA24
    { 0, SW11_CS5,  SW10_CS5,  SW12_CS5  }, //LA20
    { 0, SW11_CS4,  SW10_CS4,  SW12_CS4  }, //LA16
    { 0, SW11_CS3,  SW10_CS3,  SW12_CS3  }, //LA12
    { 0, SW11_CS2,  SW10_CS2,  SW12_CS2  }, //LA8
    { 0, SW11_CS1,  SW10_CS1,  SW12_CS1  }  //LA4
};

led_config_t g_led_config = {
    {
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12 },
        { 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 },
        { 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38 },
        { 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 }
    }, {
        { 0,  0 }, { 19,  0 }, { 38,  0 }, { 57,  0 }, { 76,  0 }, { 95,  0 }, { 114,  0 }, { 133,  0 }, { 152,  0 }, { 171,  0 }, { 190,  0 }, { 209,  0 }, { 224,  0 },
        { 0, 21 }, { 19, 21 }, { 38, 21 }, { 57, 21 }, { 76, 21 }, { 95, 21 }, { 114, 21 }, { 133, 21 }, { 152, 21 }, { 171, 21 }, { 190, 21 }, { 209, 21 }, { 224, 21 },
        { 0, 42 }, { 19, 42 }, { 38, 42 }, { 57, 42 }, { 76, 42 }, { 95, 42 }, { 114, 42 }, { 133, 42 }, { 152, 42 }, { 171, 42 }, { 190, 42 }, { 209, 42 }, { 224, 42 },
        { 0, 64 }, { 19, 64 }, { 38, 64 }, { 57, 64 }, { 76, 64 }, { 95, 64 }, { 114, 64 }, { 133, 64 }, { 152, 64 }, { 171, 64 }, { 190, 64 }, { 209, 64 }, { 224, 64 }
    }, {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    }
};
