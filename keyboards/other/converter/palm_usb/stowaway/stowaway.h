/*
Copyright 2018 milestogo

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


/* Stowaway Keyboard
 based on matrix from http://www.splorp.com/pdf/stowawayhwref.pdf

    1,    2,    3,    4,    5,    6,    7,    8,    9,    0,   MINS, EQL,   BACK         APP0,
    TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,   P,    LBRC,  RBRC, BSLS,  APP1,  
    CAPS, A,    S,    D,    F,    G,    H,    J,    K,    L,   SCLN, QUOT,  ENT,         APP2,  
    LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT, SLSH, RSFT,  UP,          APP3, 
    LCTL, FN,   LALT, CMD,  SPACE,SPACE,GRAVE,DONE, DEL, LEFT, DOWN, RIGHT     

*/
#define LAYOUT(                                                         \
    K000, K001, K002, K004, K005, K006, K007, K064, K065, K066, K060, K061, K062,       K063,\
    K031, K011, K012, K013, K014, K015, K016, K074, K075, K076, K077, K070, K071, K072, K073,\
    K030, K021, K022, K023, K024, K025, K026, K084, K085, K086, K087, K080, K081,       K082,\
    K110, K003, K020, K054, K055, K056, K057, K094, K095, K096, K090, K111, K091,       K092,\
    K032, K042, K043, K010, K027, K067, K017, K097, K100, K101, K102, K103 \
) { \
    { K000,  K001,   K002 , K003, K004,  K005, K006,  K007 }, \
    { K010,  K011,   K012 , K013, K014,  K015, K016,  K017 }, \
    { K020,  K021,   K022 , K023, K024,  K025, K026,  K027 }, \
    { K030,  K031,   K032 , KC_NO,KC_NO, KC_NO,KC_NO, KC_NO }, \
    { KC_NO, KC_NO,  K042 , K043, KC_NO, KC_NO,KC_NO, KC_NO }, \
    { KC_NO, KC_NO,  KC_NO, KC_NO,K054,  K055, K056,  K057 }, \
    { K060,  K061,   K062 , K063, K064,  K065, K066,  K067 }, \
    { K070,  K071,   K072 , K073, K074,  K075, K076,  K077 }, \
    { K080,  K081,   K082 , KC_NO,K084,  K085, K086,  K087 }, \
    { K090,  K091,   K092 , KC_NO,K094,  K095, K096,  K097 }, \
    { K100,  K101,   K102 , K103, KC_NO, KC_NO,KC_NO, KC_NO }, \
    { K110,  K111,   KC_NO, KC_NO,KC_NO, KC_NO,KC_NO, KC_NO } \
}

