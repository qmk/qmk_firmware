
#include "anton.h"


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        // Key Matrix to LED index
        {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14,     15 },
        { 30,     29,     28,     27,     26,     25,     24,     23,     22,     21,     20,     19,     18, NO_LED,     17,     16 },
        { 31, NO_LED,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42,     43,     44,     45 },
        { 59, NO_LED,     58,     57,     56,     55,     54,     53,     52,     51,     50,     49,     48,     47, NO_LED,     46 },
        { 60, NO_LED,     61,     62,     63,     64,     65,     66,     67,     68,     69, NO_LED,     70,     71,     72,     73 },
        { 83,     82, NO_LED,     81, NO_LED, NO_LED,     80, NO_LED, NO_LED, NO_LED,     79,     78,     77,     76,     75,     74 }
    },
    {
        // LED index to phcsical position
         {0, 0},  {16, 0},  {32, 0},  {48, 0},  {64, 0},  {80, 0},  {96, 0},  {112, 0},  {128, 0},  {144, 0},  {160, 0},  {176, 0},  {192, 0},  {208, 0},  {224, 0},  {240, 0},
        {0, 16}, {16, 16}, {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16}, {112, 16}, {128, 16}, {144, 16}, {160, 16}, {176, 16}, {192, 16},            {224, 16}, {240, 16},
        {0, 32},           {32, 32}, {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32}, {192, 32}, {208, 32}, {224, 32}, {240, 32},
        {0, 48},           {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48}, {112, 48}, {128, 48}, {144, 48}, {160, 48}, {176, 48}, {192, 48}, {208, 48},            {240, 48},
        {0, 64},           {32, 64}, {48, 64}, {64, 64}, {80, 64}, {96, 64}, {112, 64}, {128, 64}, {144, 64}, {160, 64},            {192, 64}, {208, 64}, {224, 64}, {240, 64},
        {0, 80}, {16, 80},           {48, 80},                     {96, 80},                                  {160, 80}, {176, 80}, {192, 80}, {208, 80}, {224, 80}, {240, 80} 
    },
    {
        // LED index to flag
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,       0x04, 0x04,
        0x04,       0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
        0x08,       0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,       0x04,
        0x04,       0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,       0x04, 0x04, 0x04, 0x04,
        0x04, 0x04,       0x04,             0x04,                   0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    }
};
#endif
}
/**
void encoder_update_kb(uint8_t index, bool clockwise) {
  uint16_t mapped_code = 0;
  if (index == 0) {
    if (clockwise) {
        switch(layer){
            case 0:
            default:
                mapped_code = KC_VOLU;
                break;
            case 1:
                mapped_code = KC_MEDIA_NEXT_TRACK;
                break;
            case 2:
                mapped_code = KC_PGDN;
                break;
        }
    } else {
        switch(layer){
            case 0:
            default:
                mapped_code = KC_VOLD;
                break;
            case 1:
                mapped_code = KC_MEDIA_PREV_TRACK;
                break;
            case 2:
                mapped_code = KC_PGUP;
                break;
        }
    }
    uint16_t held_keycode_timer = timer_read();
    register_code(mapped_code);
    while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ 
        // no-op 
    }
    unregister_code(mapped_code);
  }
}
*/
