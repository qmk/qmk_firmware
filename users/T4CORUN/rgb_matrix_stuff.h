#pragma once

#include "T4CORUN.h"

//#define RGB_AZURE       0x99, 0xF5, 0xFF
#define RGB_DARKGREEN     0x00, 0x33, 0x19
#define RGB_DARKORANGE    0x50, 0x20, 0x00
#define RGB_DARKPURPLE    0x19, 0x00, 0x33

#if defined(KEYBOARD_crkbd_rev1)
#   define LED_NUMBER 13
#   define LED_NAVIGATION 40
#   define LED_FUNCTION 21
#   define LED_ADJUST 48
#   define LED_MOUSE 14
#   define LED_GAMENUMBER 22
#   define LED_CAPSLOCK 8
#   define LED_SCRLOCK 35

#   define LED_QWERTY 36
#   define LED_COLEMAKDH 37
#   define LED_GAME 44

const uint8_t dpad_LED[] = { 11, 16, 17, 19 };
const uint8_t mouse_LED[] = {
  //thumb keys
  6, 13, 14, 33, 40, 41,
  //inner column of both splits
  7, 8, 9, 34, 35, 36 
};

#elif defined(KEYBOARD_bastardkb_charybdis_3x5)
//start of the second half
#   define LED_NUMBER 16
#   define LED_NAVIGATION 34
#   define LED_FUNCTION 0
#   define LED_ADJUST 18
#   define LED_MOUSE 15
#   define LED_GAMENUMBER 1
#   define LED_CAPSLOCK 13
#   define LED_SCRLOCK 31

#   define LED_QWERTY 30
#   define LED_COLEMAKDH 27
#   define LED_GAME 26

const uint8_t dpad_LED[] = { 4, 7, 8, 10 };
const uint8_t mouse_LED[] = {
  //thumb keys
  15, 16, 17, 33, 34,
  //inner column of both splits
  12, 13, 14, 30, 31, 32
};

#endif

#define NUM_DPADKEYS 4
#define NUM_MOUSEKEYS (sizeof(mouse_LED) / sizeof(mouse_LED[0]))




/*
Corne
mou: 14L
num: 13L
nav: 40R
fun: 21L
adj: 48R
gno: 22L
sft: 6L, 11L, 38R
ctl: 16L, 43R
alt: 19L, 46R
win: 22L, 49R
capslock: 8L
scrlock: 35R

dpad: 11L, 16L, 17L, 19L
thumbs: 6L, 13L, 14L, 33R, 40R, 41R
inside columns: 7L, 8L, 9L, 34R, 35R, 36R
*/

/*
Cnano
LED Assignments

mou: 15T
num: 16T
nav: 34R
fun: 0L
adj: 18R
gno: 1L
sft: 16T, 10L, 28R
ctl: 7L, 25R
alt: 4L, 22R
win: 1L, 19R
capslock: 13L
scrlock: 31R


dpad: 4L, 7L, 8L, 10L
thumbs: 15L, 16L, 17L, 33R, 34R
inside columns: 12L, 13L, 14L, 30R, 31R, 32R

*/