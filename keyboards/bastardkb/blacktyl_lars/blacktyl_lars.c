
#include "blacktyl_lars.h"

void keyboard_post_init_user(void) {
    //debug_config.enable = true;
    //debug_config.matrix = true;
    //debug_config.keyboard = true;
    // debug_config.mouse    = true;

    if (is_keyboard_left()) {
        dprintln("I'm left!");
    } else {
        dprintln("I'm right!");
    }
    //rgblight_set();
}

/*
void housekeeping_task_user(void) {
    static uint16_t start = 0;
    if (timer_elapsed(start) > 1000) {
        start = timer_read();
        dprintf("Fresh into eeprom %d\n", (uint8_t)start);
        eeconfig_update_debug((uint8_t)start);
        dprintf("Fresh from eeprom %d\n", (uint8_t)eeconfig_read_debug());
    }
}
*/

/**
  * LEDs index.
  *
  * ╭────────────────────╮                 ╭────────────────────╮
  *    2   3   8   9  12                     30  27  26  21  20
  * ├────────────────────┤                 ├────────────────────┤
  *    1   4   7  10  13                     31  28  25  22  19
  * ├────────────────────┤                 ├────────────────────┤
  *    0   5   6  11  14                     32  29  24  23  18
  * ╰────────────────────╯                 ╰────────────────────╯
  *                   15  16  17     35  34  33
  *                 ╰────────────╯ ╰────────────╯
  */
// clang-format off
#ifdef RGB_MATRIX_ENABLE
 led_config_t g_led_config = { {
     /* Key Matrix to LED index. */
     // Left split.
      {     2,      3,      8,      9,     12 }, // Top row
      {     1,      4,      7,     10,     13 }, // Middle row
     {      0,      5,      6,     11,     14 }, // Bottom row
     {     17, NO_LED,     15,     16, NO_LED }, // Thumb cluster
     // Right split.
     {     20,     21,     26,     27,     30 }, // Top row
     {     19,     22,     25,     28,     31 }, // Middle row
     {     18,     23,     24,     29,     32 }, // Bottom row
     {     35, NO_LED,     33,     34, NO_LED }, // Thumb cluster
 }, {
     /* LED index to physical position. */
     // Left split.
     /* index=0  */ {   0,  42 }, {   0,  21 }, {   0,   0 }, // col 1 (left most)
     /* index=3  */ {  18,   0 }, {  18,  21 }, {  18,  42 }, // col 2
     /* index=6  */ {  36,  42 }, {  36,  21 }, {  36,   0 },
     /* index=9  */ {  54,   0 }, {  54,  21 }, {  54,  42 },
     /* index=12 */ {  72,   0 }, {  72,  21 }, {  72,  42 },
     /* index=15 */ {  72,  64 }, {  90,  64 }, { 108,  64 }, // Thumb cluster
     // Right split.
     /* index=18 */ { 224,  42 }, { 224,  21 }, { 224,   0 }, // col 10 (right most)
     /* index=21 */ { 206,   0 }, { 206,  21 }, { 206,  42 }, // col 9
     /* index=24 */ { 188,  42 }, { 188,  21 }, { 188,   0 },
     /* index=27 */ { 170,   0 }, { 170,  21 }, { 170,  42 },
     /* index=30 */ { 152,   0 }, { 152,  21 }, { 152,  42 },
     /* index=33 */ { 152,  64 }, { 134,  64 }, { 116,  64 }, // Thumb cluster
 }, {
     /* LED index to flag. */
     // Left split.
     /* index=0  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 1
     /* index=3  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 2
     /* index=6  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
     /* index=9  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
     /* index=12 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
     /* index=15 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
     // Right split.
     /* index=18 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 10
     /* index=21 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 9
     /* index=24 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
     /* index=27 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
     /* index=30 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
     /* index=33 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
 } };
#endif
// clang-format on
