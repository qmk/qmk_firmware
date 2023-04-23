/* Copyright 2021 datafx
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
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

led_config_t g_led_config = { {
  // esc  f1   f2   f3   f4   f5   f6   f7     f8    f9    f10   f11   f12   prtscr scrl  brk
  {  91,  95,  96,  97,  98,  99,  100,  101,  102,  103,  104,  105,  106,  107,  108,  109 },
  //tilde 1    2   3    4    5    6    7    8    9    0    -    =    ins  home  pgup
  {  90,  89,  88, 87,  86,  85,  84,  83,  82,  81,  80,  79,  78,  76,  75,  74 },
  //tab   q    w    e    r    t    y    u    i    o    p    [    ]    del   end  pgdn
  {  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  71,  72,  73 },
  //caps  a    s    d    f    g    h    j    k   l     ;    '  return bspc
  {  56,  55,  54,  53,  52,  51,  50,  49,  48,  47,  46,  45,  44,  77,  NO_LED,  NO_LED },
  //lshift         z   x    c    v    b    n    m    ,    .    /   rshift  bsls  up  rctl
  {  31,  NO_LED,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  70,  43,  23 },
  //ctrl win  alt                             space                           alt  win  mod  left down right
  {  30,  29,  28,  NO_LED,  NO_LED,  NO_LED,  27,  NO_LED,  NO_LED,  NO_LED,  26,  25,  24,  22,  21,  20 },
  //underglow lights
  //{ 10,  11,  12,  13,  14,  15,  16,  17,  18,  19 },
  //{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9 }

}, {
    // Underglow lights
    { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 }, { 254,  63 },
    // right         down         left            rctl         mod           rwin          ralt          space         lalt           lwin         lctl
    { 225,  63 }, { 215,  63 }, { 206,  63 }, { 180,  63 }, { 168,  63}, { 153,  63 }, { 135,  63 }, { 101,  63 }, {  33,  63 }, {  22,  63 }, {  0,  63 },
    // lshift          z             x            c              v            b            n              m              comma       period       question       rshift         up
    {  0,  48 }, {  30,  48 }, {  45,  48 }, {  60,  48 }, {  75,  48 }, {  90,  48 }, { 105,  48 }, { 120,  48 }, { 135,  48 }, { 150,  48 }, { 165,  48 }, { 198,  48 }, { 215,  48},
    // return         '              ;             l              k             j             h             g              f            d            s               a        capslock
    { 198,  36 }, { 180,  36 }, { 176,  36 }, { 161,  36 }, { 146,  36 }, { 131,  36 }, { 116,  36 }, { 101,  36 }, {  86,  36 }, {  71,  36 }, {  56,  36 }, {  41,  36 }, {  0,  36 },
    //   tab           q             w             e             r            t             y             u              i             o             p              [             ]         backslash      del          end         pgdn
    {   0,  24 }, {  22,  24}, {  37,  24 }, {  52,  24 }, {  67,  24 }, {  82,  24 }, {  97,  24 }, { 112,  24 }, { 127,  24 }, { 142,  24 }, { 157,  24 }, { 172,  24 }, { 187,  24 }, { 202,  24}, { 206,  24 }, {215,  24}, { 225,  24 },
    // pgup          home          ins        backspace        =            -             0              9             8             7            6               5              4             3             2            1         tilde
    { 225,  12 }, {215,  12}, { 206,  12 }, { 202,  12}, { 187,  12 }, { 172,  12 }, { 157,  12 }, { 142,  12 }, { 127,  12 }, { 112,  12 }, {  97,  12 }, {  82,  12 }, {  67,  12 }, {  52,  12 }, {  37,  12 }, {  22,  12}, {   0,  12 },
    //   esc          ind1         ind2         ind3           F1           F2           F3            F4            F5             F6             F7               F8            F9            F10          F11           F12        prtscr      scrlck         pause
    {   0,   0 }, {  0,  0 }, {  0,   0 }, {   0,   0 }, {  25,   0 }, {  40,   0 }, {  55,   0 }, {  82,   0 }, {  108,   0 }, {  120,   0 }, {  130,   0 }, { 148,   0 }, { 172,   0 }, { 187,   0 }, { 190,   0 }, { 195,   0 }, { 206,   0 }, { 215,  0}, { 225,   0 }
}, {
    // underglow
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    // bottom row
    1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1,
    // 2nd row up
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    // 3rd row up
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    // 4th row up
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1,
    // 5th row up
    1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // top row
    1, 8, 8, 8, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1
} };


bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    led_t host_leds = host_keyboard_led_state();
    if (host_leds.scroll_lock) {
        rgb_matrix_set_color(92, 0xFF, 0x0, 0x0);
    } else {
        rgb_matrix_set_color(92, 0x0, 0x0, 0x0);
    }
    if (host_leds.num_lock) {
        rgb_matrix_set_color(93, 0xFF, 0x0, 0x0);
    } else {
        rgb_matrix_set_color(93, 0x0, 0x0, 0x0);
    }
    if (host_leds.caps_lock) {
        rgb_matrix_set_color(94, 0xFF, 0x0, 0x0);
    } else {
        rgb_matrix_set_color(94, 0x0, 0x0, 0x0);
    }
    return true;
}
