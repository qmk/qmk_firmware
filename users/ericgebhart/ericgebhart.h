#pragma once

#ifndef ericgebhart
#define ericgebhart

#include QMK_KEYBOARD_H
#include "base_layers.h"


//#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */

#define DVORAK 0 // dvorak layout (default)
#define QWERTY 1
#define COLEMAK 2
#define WORKMAN 3
#define NORMAN 4
// bepo layers
#define DVORAK_ON_BEPO 6 // dvorak layout (default)
#define BEPO 7 // Bepo
// non-default layers
#define SYMB 8 // symbols and numbers
#define SYMB_ON_BEPO 9 // symbols and numbers
#define MDIA 10 // mouse knd media eys
#define LAYERS 11 // layers and right mousekeys.
#define XMONAD 12 // xmonad ie. dvorak.
#define XMONAD_FR 13 // xmonad ie. dvorak.
#define KEYPAD 14 // number and Fkey pads
#define KEYPAD_ON_BEPO 15 // number and Fkey pads.
#define _RGB 16 // RGB stuff.


#endif
