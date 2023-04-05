/**
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

/**
 * LEDs index.
 *
 *  0 - 17 Underglow                36 - 53 Underglow
 * ╭────────────────────╮         ╭────────────────────╮
 *   22  21  20  19  18             54  55  56  57  58
 * ├────────────────────┤         ├────────────────────┤
 *   23  24  25  26  27             63  62  61  60  59
 * ├────────────────────┤         ├────────────────────┤
 *   32  31  30  29  28             64  65  66  67  68
 * ╰────────────────────╯         ╰────────────────────╯
 *               33  34  35     71  70  69
 *             ╰────────────╯ ╰────────────╯
 */
// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    /* Key Matrix to LED index. */
    // Left split.
    {     22,     21,     20,     19,     18 }, // Top row
    {     23,     24,     25,     26,     27 }, // Middle row
    {     32,     31,     30,     29,     28 }, // Bottom row
    {     34,     35,     33, NO_LED, NO_LED }, // Thumb cluster
    // Right split.
    {     58,     57,     56,     55,     54 }, // Top row
    {     59,     60,     61,     62,     63 }, // Middle row
    {     68,     67,     66,     65,     64 }, // Bottom row
    {     70,     71,     69, NO_LED, NO_LED }, // Thumb cluster
}, {
    /* LED index to physical position. */
    // Left split underglow.
    /* index=0  */ {  82,   0 }, {  60,   0 }, {  22,   0 }, {  15,   0 }, // Top 4
    /* index=4  */ {   0,  25 }, {   0,  40 }, {   0,  55 },               // Pinky edge 3
    /* index=7  */ {  15,  45 }, {  30,  45 }, {  35,  60 }, {  55,  62 }, // Bottom 8
    /* index=11 */ {  72,  64 }, {  90,  64 }, {  98,  47 }, { 107,  40 },
    /* index=15 */ { 110,  33 }, { 110,  19 }, { 110,   5 },               // Inner edge 3
    // Left split per-key.
    /* index=18 */ {  73,  11 }, {  56,   9 }, {  39,   5 }, {  22,  10 }, {   5,  15 }, // row 1 (left most) 90, 107
    /* index=23 */ {   5,  30 }, {  22,  25 }, {  39,  20 }, {  56,  24 }, {  73,  26 }, // row 2 (middle)
    /* index=28 */ {  73,  41 }, {  56,  39 }, {  39,  35 }, {  22,  25 }, {   5,  45 }, // row 3 (left most)
    /* index=33 */ {  45,  51 }, {  64,  53 }, {  81,  60 }, // Thumb cluster
    // Right split underglow.
    /* index=36 */ { 142,   0 }, { 164,   0 }, { 202,   0 }, { 209,   0 }, // Top 4
    /* index=40 */ { 224,  25 }, { 224,  40 }, { 224,  55 },               // Pinky edge 3
    /* index=43 */ { 209,  45 }, { 194,  45 }, { 189,  60 }, { 169,  62 }, // Bottom 8
    /* index=47 */ { 152,  64 }, { 134,  64 }, { 126,  47 }, { 117,  40 },
    /* index=51 */ { 114,  33 }, { 114,  19 }, { 114,   5 },               // Inner edge 3
    // Right split per-key.
    /* index=54 */ { 151,  11 }, { 168,   9 }, { 185,   5 }, { 202,  10 }, { 219,  15 }, // row 1 (right most) 117 134
    /* index=59 */ { 219,  30 }, { 202,  25 }, { 185,  20 }, { 168,  24 }, { 151,  26 }, // row 2 (middle)
    /* index=64 */ { 151,  41 }, { 168,  39 }, { 185,  35 }, { 202,  25 }, { 219,  45 }, // row 3 (right most)
    /* index=69 */ { 179,  51 }, { 160,  53 }, { 143,  60 }, // Thumb cluster
}, {
    /* LED index to flag. */
    // Left split underglow.
    /* index=0  */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=3  */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=6  */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=9  */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=12 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=15 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    // Left split per-key.
    /* index=18 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 1
    /* index=21 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 2
    /* index=24 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=27 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=30 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=33 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
    // Right split underglow.
    /* index=36 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=39 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=42 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=45 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=48 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    /* index=51 */ LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
    // Right split per-key.
    /* index=54 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 10
    /* index=57 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 9
    /* index=60 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=63 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=66 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=69 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
} };
#endif
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    switch (index) {
        case 0: // Left-half encoder, mouse scroll.
            tap_code(clockwise ? KC_MS_WH_UP : KC_MS_WH_DOWN);
            break;
        case 1: // Right-half encoder, volume control.
            tap_code(clockwise ? KC_AUDIO_VOL_UP : KC_AUDIO_VOL_DOWN);
            break;
    }
    return true;
}
#endif // ENCODER_ENABLE
