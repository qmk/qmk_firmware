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
#include "rgb.h"
#include "rgb_matrix_types.h"
#include <print.h>
#include "raw_hid.h"
#include "usb_descriptor.h"
#include "rgb_matrix.h"

led_config_t g_led_config = { {
  // esc  f1   f2   f3   f4   f5   f6   f7     f8    f9    f10   f11   f12   prtscr scrl  brk
  {  91,  95,  96,  97,  98,  99,  100,  101,  102,  103,  104,  105,  106,  107,  108,  109 },
  //tilde 1    2   3    4    5    6    7    8    9    0    -    =    ins  home  pgup
  {  90,  89,  88, 87,  86,  85,  84,  83,  82,  81,  80,  79,  78,  76,  75,  74 },
  //tab   q    w    e    r    t    y    u    i    o    p    [    ]    del   end  pgdn
  {  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  71,  72,  73 },
  //caps  a    s    d    f    g    h    j    k   l     ;    '  return bspc
  {  56,  55,  54,  53,  52,  51,  50,  49,  48,  47,  46,  45,  44,  77 },
  //lshift         z   x    c    v    b    n    m    ,    .    /   rshift  bsls  up  rctl
  {  31,  NO_LED,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  70,  43,  23 },
  //ctrl win  alt                             space                           alt  win  mod  left down right
  {  30,  29,  28,  NO_LED,  NO_LED,  NO_LED,  27,  NO_LED,  NO_LED,  NO_LED,  26,  25,  24,  22,  21,  20 },
}, {
    //  esc            f1            f2            f3            f4            f5            f6               f7            f8            f9            f10           f11           f12        prtscr         scrl          brk
    {   0,   0 }, {   26,   0 }, {   39,   0 }, {  52,   0 }, {  65,   0 }, {  91,   0 }, { 104,   0 }, { 117,   0 }, { 130,   0 }, { 143,   0 }, { 156,   0 }, { 169,   0 }, { 182,   0 }, { 195,   0 }, { 208,   0 }, { 224,   0 },
    //  tilde          1             2             3             4             5             6             7             8             9             0             -             =             ins         home         pgup
    {   0,  13 }, {  13,  13 }, {  26,  13 }, {  29,  13 }, {  52,  13 }, {  65,  13 }, {  78,  13 }, {  91,  13 }, { 104,  13 }, { 117,  13 }, { 130,  13 }, { 143,  13 }, { 156,  13 }, { 195,  13}, { 208,  13 }, {224,  13},
    //    tab           q            w             e             r             t              y            u             i             o             p             [              ]           del          end          pgdn
    {   0,  26 }, {  22,  26}, {  39,  26 }, {  52,  26 }, {  65,  26 }, {  78,  26 }, {  91,  26 }, { 104,  26 }, { 117,  26 }, { 130,  26 }, { 143,  26 }, { 156,  26 }, { 169,  26 }, { 195,  26 }, { 208,  26 }, {224,  26 },
    //  caps           a              s            d             f             g             h             j             k             l             ;              '          return        bspc
    {  0,  39 }, {  26,  39 }, {  39,  39 }, {  52,  39 }, {  65,  39 }, {  78,  39 }, {  91,  39 }, { 104,  39 }, { 117,  39 }, { 130,  39 }, { 143,  39 }, { 156,  39 }, { 182,  39 }, { 182,  13 },
    // lshift           z            x              c            v             b              n             m             ,           .             /          rshift        bsls           up            rctl
    {  0,  52 }, {  26,  52 }, {  39,  52 }, {  65,  52 }, {  78,  52 }, {  91,  52 }, { 104,  52 }, { 117,  52 }, { 130,  52 }, { 143,  52 }, { 156,  52 }, { 182,  52 }, { 182,  26 }, { 208,  52 }, { 182,  64},
    //  lctrl          win          alt          space          alt           win           mod          left         down         right
    {  0,  63 }, {  13,  63 }, {  39,  63 }, {  91,  63 }, { 143,  63 }, { 156,  63 }, { 169,  63}, { 195,  63 }, { 208,  63 }, { 224,  63 }
}, {
    // top row 
    4, 8, 8, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // 5th row up
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // 4th row up 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // 3rd row up
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // 2nd row up
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // bottom row
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // underglow
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

void rgb_matrix_indicators_user(void) {
    led_t host_leds = host_keyboard_led_state();
    if (host_leds.scroll_lock) {
        rgb_matrix_set_color(92, 0x64, 0x0, 0x0);
    } else {
        rgb_matrix_set_color(92, 0x0, 0x0, 0x0);
    }
    if (host_leds.num_lock) {
        rgb_matrix_set_color(93, 0x64, 0x0, 0x0);
    } else {
        rgb_matrix_set_color(93, 0x0, 0x0, 0x0);
    }
    if (host_leds.caps_lock) {
        rgb_matrix_set_color(94, 0x64, 0x0, 0x0);
    } else {
        rgb_matrix_set_color(94, 0x0, 0x0, 0x0);
    }
}
