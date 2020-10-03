/*
Copyright 2018 Jeff Shufelt <jshuf@puppyfish.com> @jshuf

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"
#include "led.h"

inline void kbd19x_caps_led_on(void)    { DDRB |=  (1<<0); PORTB &= ~(1<<0); }
inline void kbd19x_caps_led_off(void)   { DDRB &= ~(1<<0); PORTB &= ~(1<<0); }

inline void kbd19x_sclk_led_on(void)    { DDRB |=  (1<<1); PORTB &= ~(1<<1); }
inline void kbd19x_sclk_led_off(void)   { DDRB &= ~(1<<1); PORTB &= ~(1<<1); }

inline void kbd19x_nmlk_led_on(void)    { DDRB |=  (1<<2); PORTB &= ~(1<<2); }
inline void kbd19x_nmlk_led_off(void)   { DDRB &= ~(1<<2); PORTB &= ~(1<<2); }

#define XXXX KC_NO

/*
// 2u backspace: XXXX, k701
// split backspace: k700, k701

// 2u numpad +: k212, XXXX
// split numpad +: k212, k312

// 2u numpad enter: k412, XXXX
// split numpad enter: k412, k512

// 2.25u lshift: k400, XXXX
// split (1.25u, 1u) lshift: k400, k401

// ANSI enter or ISO enter: k308
// backslash or NUHS: k208

// left winkey: k500, k501, k502
// left WKL: k500, XXXX, k502

// right winkey: k505, k506, k507
// right WKL: k505, XXXX, k507
*/

#define LAYOUT_all( \
  k000, k001, k002, k003, k004, k600, k601, k602, k603, k005, k006, k007, k008,       k702,  k009, k010, k011, k012, \
  k100, k101, k102, k103, k104, k604, k605, k606, k607, k105, k106, k107, k108, k700, k701,  k109, k110, k111, k112, \
  k200, k201, k202, k203, k204, k608, k609, k610, k611, k205, k206, k207, k208,       k703,  k209, k210, k211, k212, \
  k300, k301, k302, k303, k304, k612, k705, k706, k707, k305, k306, k307, k308,              k309, k310, k311, k312, \
  k400, k401, k402, k403, k404, k708, k709, k710, k711, k405, k406, k407, k408,     k704,    k409, k410, k411, k412, \
  k500, k501, k502,                   k509,             k505, k506, k507,     k508, k503, k504,    k510, k511, k512  \
)\
{\
  {k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012},\
  {k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112},\
  {k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212},\
  {k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, k312},\
  {k400, k401, k402, k403, k404, k405, k406, k407, k408, k409, k410, k411, k412},\
  {k500, k501, k502, k503, k504, k505, k506, k507, k508, k509, k510, k511, k512},\
  {k600, k601, k602, k603, k604, k605, k606, k607, k608, k609, k610, k611, k612},\
  {k700, k701, k702, k703, k704, k705, k706, k707, k708, k709, k710, k711, XXXX},\
}

#define LAYOUT_ansi( \
  k000, k001, k002, k003, k004, k600, k601, k602, k603, k005, k006, k007, k008,       k702,  k009, k010, k011, k012, \
  k100, k101, k102, k103, k104, k604, k605, k606, k607, k105, k106, k107, k108,       k701,  k109, k110, k111, k112, \
  k200, k201, k202, k203, k204, k608, k609, k610, k611, k205, k206, k207, k208,       k703,  k209, k210, k211, k212, \
  k300, k301, k302, k303, k304, k612, k705, k706, k707, k305, k306, k307, k308,              k309, k310, k311,       \
  k400,       k402, k403, k404, k708, k709, k710, k711, k405, k406, k407, k408,     k704,    k409, k410, k411, k412, \
  k500, k501, k502,                   k509,             k505, k506, k507,     k508, k503, k504,    k510, k511,       \
)\
{\
  {k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012},\
  {k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112},\
  {k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212},\
  {k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, XXXX},\
  {k400, XXXX, k402, k403, k404, k405, k406, k407, k408, k409, k410, k411, k412},\
  {k500, k501, k502, k503, k504, k505, k506, k507, k508, k509, k510, k511, XXXX},\
  {k600, k601, k602, k603, k604, k605, k606, k607, k608, k609, k610, k611, k612},\
  {XXXX, k701, k702, k703, k704, k705, k706, k707, k708, k709, k710, k711, XXXX},\
}

#define LAYOUT_WKL( \
  k000, k001, k002, k003, k004, k600, k601, k602, k603, k005, k006, k007, k008,       k702,  k009, k010, k011, k012, \
  k100, k101, k102, k103, k104, k604, k605, k606, k607, k105, k106, k107, k108,       k701,  k109, k110, k111, k112, \
  k200, k201, k202, k203, k204, k608, k609, k610, k611, k205, k206, k207, k208,       k703,  k209, k210, k211, k212, \
  k300, k301, k302, k303, k304, k612, k705, k706, k707, k305, k306, k307, k308,              k309, k310, k311,       \
  k400,       k402, k403, k404, k708, k709, k710, k711, k405, k406, k407, k408,     k704,    k409, k410, k411, k412, \
  k500,       k502,                   k509,             k505,       k507,     k508, k503, k504,    k510, k511,       \
)\
{\
  {k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012},\
  {k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112},\
  {k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212},\
  {k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, XXXX},\
  {k400, XXXX, k402, k403, k404, k405, k406, k407, k408, k409, k410, k411, k412},\
  {k500, XXXX, k502, k503, k504, k505, XXXX, k507, k508, k509, k510, k511, XXXX},\
  {k600, k601, k602, k603, k604, k605, k606, k607, k608, k609, k610, k611, k612},\
  {XXXX, k701, k702, k703, k704, k705, k706, k707, k708, k709, k710, k711, XXXX},\
}
