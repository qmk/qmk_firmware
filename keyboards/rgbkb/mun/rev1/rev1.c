/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include "rev1.h"

#define NUMBER_OF_TOUCH_ENCODERS 2
#define TOUCH_ENCODER_OPTIONS TOUCH_SEGMENTS + 2

#define NUMBER_OF_ENCODERS 4
#define ENCODER_OPTIONS 2

typedef struct PACKED {
    uint8_t r;
    uint8_t c;
} encodermap_t;

// this maps encoders and then touch encoders to their respective electrical matrix entry
// mapping is row (y) then column (x) when looking at the electrical layout
const encodermap_t encoder_map[NUMBER_OF_ENCODERS][ENCODER_OPTIONS] = 
{
    { {  5, 0 }, {  5, 1 } }, // Encoder 1 matrix entries
    { {  5, 2 }, {  5, 3 } }, // Encoder 2 matrix entries
    { { 12, 0 }, { 12, 1 } }, // Encoder 3 matrix entries
    { { 12, 2 }, { 12, 3 } }, // Encoder 4 matrix entries
}; 

const encodermap_t touch_encoder_map[NUMBER_OF_TOUCH_ENCODERS][TOUCH_ENCODER_OPTIONS] = 
{
    { {  6, 0 }, {  6, 1 }, {  6, 2 }, {  6, 3 }, {  6, 4 } }, // Touch Encoder 1 matrix entries
    { { 13, 0 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 } }  // Touch Encoder 2 matrix entries
};

static void process_encoder_matrix(encodermap_t pos) {
    action_exec((keyevent_t){
        .key = (keypos_t){.row = pos.r, .col = pos.c}, .pressed = true, .time = (timer_read() | 1) /* time should not be 0 */
    });
#if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
#endif
    action_exec((keyevent_t){
        .key = (keypos_t){.row = pos.r, .col = pos.c}, .pressed = false, .time = (timer_read() | 1) /* time should not be 0 */
    });
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise))
        return false;

    // Mapping clockwise (typically increase) to zero, and counter clockwise (decrease) to 1
    process_encoder_matrix(encoder_map[index][clockwise ? 0 : 1]);
    return false;
}

bool touch_encoder_update_kb(uint8_t index, bool clockwise) {
    if (!touch_encoder_update_user(index, clockwise))
        return false;

    // Mapping clockwise (typically increase) to zero, and counter clockwise (decrease) to 1
    process_encoder_matrix(touch_encoder_map[index][clockwise ? 0 : 1]);
    return false;
}

bool touch_encoder_tapped_kb(uint8_t index, uint8_t section) {
    if (!touch_encoder_tapped_user(index, section))
        return false;

    process_encoder_matrix(touch_encoder_map[index][section + 2]);
    return false;
}

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    {   0,   1,   2,   3,   4,   5,   6 },
    {  13,  12,  11,  10,   9,   8,   7 },
    {  14,  15,  16,  17,  18,  19,  20 },
    {  27,  26,  25,  24,  23,  22,  21 },
    {  28,  29,  30,  31,  32,  33,  34 },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    {  49,  50,  51,  52,  53,  54,  55 },
    {  62,  61,  60,  59,  58,  57,  56 },
    {  63,  64,  65,  66,  67,  68,  69 },
    {  76,  75,  74,  73,  72,  71,  70 },
    {  77,  78,  79,  80,  81,  82,  83 },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
    {  16,  16},{  34,  16},{  49,  16},{  64,  16},{  79,  16},{  94,  16},{ 109,  16},
    { 109,  31},{  94,  31},{  79,  31},{  64,  31},{  49,  31},{  34,  31},{  16,  31},
    {  16,  46},{  34,  46},{  49,  46},{  64,  46},{  79,  46},{  94,  46},{ 109,  46},
    { 109,  61},{  94,  61},{  79,  61},{  64,  61},{  49,  61},{  34,  61},{  16,  61},
    {  16,  76},{  34,  76},{  49,  76},{  64,  76},{  83,  72},{  98,  72},{ 113,  72},
    {  97,   5},{  91,   5},{  86,   5},{  80,   5},{  75,   5},{  69,   5},{  63,   5},{  58,   5},{  52,   5},{  46,   5},{  41,   5},{  35,   5},{  30,   5},{  24,   5},
    { 240,  16},{ 222,  16},{ 207,  16},{ 192,  16},{ 177,  16},{ 162,  16},{ 147,  16},
    { 147,  31},{ 162,  31},{ 177,  31},{ 192,  31},{ 207,  31},{ 222,  31},{ 240,  31},
    { 240,  46},{ 222,  46},{ 207,  46},{ 192,  46},{ 177,  46},{ 162,  46},{ 147,  46},
    { 147,  61},{ 162,  61},{ 177,  61},{ 192,  61},{ 207,  61},{ 222,  61},{ 240,  61},
    { 240,  76},{ 222,  76},{ 207,  76},{ 192,  76},{ 180,  72},{ 165,  72},{ 150,  72},
    { 159,   5},{ 164,   5},{ 170,   5},{ 176,   5},{ 181,   5},{ 187,   5},{ 192,   5},{ 198,   5},{ 204,   5},{ 209,   5},{ 215,   5},{ 221,   5},{ 226,   5},{ 232,   5},
}, {
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };
// clang-format on
#endif
