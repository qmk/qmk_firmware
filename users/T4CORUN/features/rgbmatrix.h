#pragma once
#include "t4corun.h"


#if defined(CAPS_WORD_ENABLE)
#   include "capsword.h"
#endif //CAPS_WORD_ENABLE


//qmk_firmware\keyboards\crkbd\rev1\rev1.c
#if defined(KEYBOARD_crkbd_rev1)

//layers
#   define LED_NUMBER 13
#   define LED_NAVIGATION 40
#   define LED_FUNCTION 21
#   define LED_ADJUST 48
#   define LED_MOUSE 15
#   define LED_GAMENUMBER 22

//base layers
#   define LED_QWERTY 36
#   define LED_COLEMAKDH 37
#   define LED_GAME 44

//indicators
#   define LED_CAPSLOCK 35
#   define LED_SCRLOCK 36

//dpad
#   define LED_DPAD_L 19
#   define LED_DPAD_R 11
#   define LED_DPAD_U 17
#   define LED_DPAD_D 16

//mouse buttons
#   define LED_MOUSE_LB1 14
#   define LED_MOUSE_LB2 13
#   define LED_MOUSE_LB3 6

#   define LED_MOUSE_RB1 39
#   define LED_MOUSE_RB2 42
#   define LED_MOUSE_RB3 47
#   define LED_MOUSE_RB4 40
#   define LED_MOUSE_RB5 33

//shift keys
#   define LED_SHIFT_T 6
#   define LED_SHIFT_L 11
#   define LED_SHIFT_R 38

//control keys
#   define LED_CTRL_L 16
#   define LED_CTRL_R 43

//alt keys
#   define LED_ALT_L 19
#   define LED_ALT_R 46

//GUI keys
#   define LED_GUI_L 22
#   define LED_GUI_R 49


//qmk_firmware\keyboards\bastardkb\charybdis\3x5\3x5.c
#elif defined(KEYBOARD_bastardkb_charybdis_3x5)
//layers
#   define LED_NUMBER 16
#   define LED_NAVIGATION 34
#   define LED_FUNCTION 2
#   define LED_ADJUST 18
#   define LED_MOUSETOG 20
#   define LED_MOUSETAP 6
#   define LED_GAMENUMBER 1

//base layers
#   define LED_QWERTY 30
#   define LED_COLEMAKDH 27
#   define LED_GAME 26

//indicators
#   define LED_CAPSLOCK 31
#   define LED_SCRLOCK 30

//dpad
#   define LED_DPAD_L 4
#   define LED_DPAD_R 10
#   define LED_DPAD_U 8
#   define LED_DPAD_D 7

//mouse buttons
#   define LED_MOUSE_LB1 15
#   define LED_MOUSE_LB2 16
#   define LED_MOUSE_LB3 17

#   define LED_MOUSE_RB1 29
#   define LED_MOUSE_RB2 24
#   define LED_MOUSE_RB3 23
#   define LED_MOUSE_RB4 34
#   define LED_MOUSE_RB5 33

//shift keys
#   define LED_SHIFT_T 17
#   define LED_SHIFT_L 10
#   define LED_SHIFT_R 28

//control keys
#   define LED_CTRL_L 7
#   define LED_CTRL_R 25

//alt keys
#   define LED_ALT_L 4
#   define LED_ALT_R 22

//GUI keys
#   define LED_GUI_L 1
#   define LED_GUI_R 19
#endif