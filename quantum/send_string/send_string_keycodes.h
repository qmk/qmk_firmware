/* Copyright 2019
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

#pragma once

// clang-format off

/* Punctuation */
#define X_ENT  X_ENTER
#define X_ESC  X_ESCAPE
#define X_BSPC X_BACKSPACE
#define X_SPC  X_SPACE
#define X_MINS X_MINUS
#define X_EQL  X_EQUAL
#define X_LBRC X_LEFT_BRACKET
#define X_RBRC X_RIGHT_BRACKET
#define X_BSLS X_BACKSLASH
#define X_NUHS X_NONUS_HASH
#define X_SCLN X_SEMICOLON
#define X_QUOT X_QUOTE
#define X_GRV  X_GRAVE
#define X_COMM X_COMMA
#define X_SLSH X_SLASH
#define X_NUBS X_NONUS_BACKSLASH

/* Lock Keys */
#define X_CAPS X_CAPS_LOCK
#define X_SCRL X_SCROLL_LOCK
#define X_NUM  X_NUM_LOCK
#define X_LCAP X_LOCKING_CAPS_LOCK
#define X_LNUM X_LOCKING_NUM_LOCK
#define X_LSCR X_LOCKING_SCROLL_LOCK

/* Commands */
#define X_PSCR X_PRINT_SCREEN
#define X_PAUS X_PAUSE
#define X_BRK  X_PAUSE
#define X_INS  X_INSERT
#define X_PGUP X_PAGE_UP
#define X_DEL  X_DELETE
#define X_PGDN X_PAGE_DOWN
#define X_RGHT X_RIGHT
#define X_APP  X_APPLICATION
#define X_EXEC X_EXECUTE
#define X_SLCT X_SELECT
#define X_AGIN X_AGAIN
#define X_PSTE X_PASTE
#define X_ERAS X_ALTERNATE_ERASE
#define X_SYRQ X_SYSTEM_REQUEST
#define X_CNCL X_CANCEL
#define X_CLR  X_CLEAR
#define X_PRIR X_PRIOR
#define X_RETN X_RETURN
#define X_SEPR X_SEPARATOR
#define X_CLAG X_CLEAR_AGAIN
#define X_CRSL X_CRSEL
#define X_EXSL X_EXSEL

/* Keypad */
#define X_PSLS X_KP_SLASH
#define X_PAST X_KP_ASTERISK
#define X_PMNS X_KP_MINUS
#define X_PPLS X_KP_PLUS
#define X_PENT X_KP_ENTER
#define X_P1   X_KP_1
#define X_P2   X_KP_2
#define X_P3   X_KP_3
#define X_P4   X_KP_4
#define X_P5   X_KP_5
#define X_P6   X_KP_6
#define X_P7   X_KP_7
#define X_P8   X_KP_8
#define X_P9   X_KP_9
#define X_P0   X_KP_0
#define X_PDOT X_KP_DOT
#define X_PEQL X_KP_EQUAL
#define X_PCMM X_KP_COMMA

/* Language Specific */
#define X_INT1 X_INTERNATIONAL_1
#define X_INT2 X_INTERNATIONAL_2
#define X_INT3 X_INTERNATIONAL_3
#define X_INT4 X_INTERNATIONAL_4
#define X_INT5 X_INTERNATIONAL_5
#define X_INT6 X_INTERNATIONAL_6
#define X_INT7 X_INTERNATIONAL_7
#define X_INT8 X_INTERNATIONAL_8
#define X_INT9 X_INTERNATIONAL_9
#define X_LNG1 X_LANGUAGE_1
#define X_LNG2 X_LANGUAGE_2
#define X_LNG3 X_LANGUAGE_3
#define X_LNG4 X_LANGUAGE_4
#define X_LNG5 X_LANGUAGE_5
#define X_LNG6 X_LANGUAGE_6
#define X_LNG7 X_LANGUAGE_7
#define X_LNG8 X_LANGUAGE_8
#define X_LNG9 X_LANGUAGE_9

/* Modifiers */
#define X_LCTL X_LEFT_CTRL
#define X_LSFT X_LEFT_SHIFT
#define X_LALT X_LEFT_ALT
#define X_LOPT X_LEFT_ALT
#define X_LGUI X_LEFT_GUI
#define X_LCMD X_LEFT_GUI
#define X_LWIN X_LEFT_GUI
#define X_RCTL X_RIGHT_CTRL
#define X_RSFT X_RIGHT_SHIFT
#define X_RALT X_RIGHT_ALT
#define X_ALGR X_RIGHT_ALT
#define X_ROPT X_RIGHT_ALT
#define X_RGUI X_RIGHT_GUI
#define X_RCMD X_RIGHT_GUI
#define X_RWIN X_RIGHT_GUI

/* Generic Desktop Page (0x01) */
#define X_PWR  X_SYSTEM_POWER
#define X_SLEP X_SYSTEM_SLEEP
#define X_WAKE X_SYSTEM_WAKE

/* Consumer Page (0x0C) */
#define X_MUTE X_AUDIO_MUTE
#define X_VOLU X_AUDIO_VOL_UP
#define X_VOLD X_AUDIO_VOL_DOWN
#define X_MNXT X_MEDIA_NEXT_TRACK
#define X_MPRV X_MEDIA_PREV_TRACK
#define X_MSTP X_MEDIA_STOP
#define X_MPLY X_MEDIA_PLAY_PAUSE
#define X_MSEL X_MEDIA_SELECT
#define X_EJCT X_MEDIA_EJECT
#define X_CALC X_CALCULATOR
#define X_MYCM X_MY_COMPUTER
#define X_WSCH X_WWW_SEARCH
#define X_WHOM X_WWW_HOME
#define X_WBAK X_WWW_BACK
#define X_WFWD X_WWW_FORWARD
#define X_WSTP X_WWW_STOP
#define X_WREF X_WWW_REFRESH
#define X_WFAV X_WWW_FAVORITES
#define X_MFFD X_MEDIA_FAST_FORWARD
#define X_MRWD X_MEDIA_REWIND
#define X_BRIU X_BRIGHTNESS_UP
#define X_BRID X_BRIGHTNESS_DOWN
#define X_CPNL X_CONTROL_PANEL
#define X_ASST X_ASSISTANT

/* System Specific */
#define X_BRMU X_PAUSE
#define X_BRMD X_SCROLL_LOCK

/* Mouse Keys */
#define X_MS_U X_MS_UP
#define X_MS_D X_MS_DOWN
#define X_MS_L X_MS_LEFT
#define X_MS_R X_MS_RIGHT
#define X_BTN1 X_MS_BTN1
#define X_BTN2 X_MS_BTN2
#define X_BTN3 X_MS_BTN3
#define X_BTN4 X_MS_BTN4
#define X_BTN5 X_MS_BTN5
#define X_BTN6 X_MS_BTN6
#define X_BTN7 X_MS_BTN7
#define X_BTN8 X_MS_BTN8
#define X_WH_U X_MS_WH_UP
#define X_WH_D X_MS_WH_DOWN
#define X_WH_L X_MS_WH_LEFT
#define X_WH_R X_MS_WH_RIGHT
#define X_ACL0 X_MS_ACCEL0
#define X_ACL1 X_MS_ACCEL1
#define X_ACL2 X_MS_ACCEL2

/* Keyboard/Keypad Page (0x07) */
#define X_A                   04
#define X_B                   05
#define X_C                   06
#define X_D                   07
#define X_E                   08
#define X_F                   09
#define X_G                   0a
#define X_H                   0b
#define X_I                   0c
#define X_J                   0d
#define X_K                   0e
#define X_L                   0f
#define X_M                   10
#define X_N                   11
#define X_O                   12
#define X_P                   13
#define X_Q                   14
#define X_R                   15
#define X_S                   16
#define X_T                   17
#define X_U                   18
#define X_V                   19
#define X_W                   1a
#define X_X                   1b
#define X_Y                   1c
#define X_Z                   1d
#define X_1                   1e
#define X_2                   1f
#define X_3                   20
#define X_4                   21
#define X_5                   22
#define X_6                   23
#define X_7                   24
#define X_8                   25
#define X_9                   26
#define X_0                   27
#define X_ENTER               28
#define X_ESCAPE              29
#define X_BACKSPACE           2a
#define X_TAB                 2b
#define X_SPACE               2c
#define X_MINUS               2d
#define X_EQUAL               2e
#define X_LEFT_BRACKET        2f
#define X_RIGHT_BRACKET       30
#define X_BACKSLASH           31
#define X_NONUS_HASH          32
#define X_SEMICOLON           33
#define X_QUOTE               34
#define X_GRAVE               35
#define X_COMMA               36
#define X_DOT                 37
#define X_SLASH               38
#define X_CAPS_LOCK           39
#define X_F1                  3a
#define X_F2                  3b
#define X_F3                  3c
#define X_F4                  3d
#define X_F5                  3e
#define X_F6                  3f
#define X_F7                  40
#define X_F8                  41
#define X_F9                  42
#define X_F10                 43
#define X_F11                 44
#define X_F12                 45
#define X_PRINT_SCREEN        46
#define X_SCROLL_LOCK         47
#define X_PAUSE               48
#define X_INSERT              49
#define X_HOME                4a
#define X_PAGE_UP             4b
#define X_DELETE              4c
#define X_END                 4d
#define X_PAGE_DOWN           4e
#define X_RIGHT               4f
#define X_LEFT                50
#define X_DOWN                51
#define X_UP                  52
#define X_NUM_LOCK            53
#define X_KP_SLASH            54
#define X_KP_ASTERISK         55
#define X_KP_MINUS            56
#define X_KP_PLUS             57
#define X_KP_ENTER            58
#define X_KP_1                59
#define X_KP_2                5a
#define X_KP_3                5b
#define X_KP_4                5c
#define X_KP_5                5d
#define X_KP_6                5e
#define X_KP_7                5f
#define X_KP_8                60
#define X_KP_9                61
#define X_KP_0                62
#define X_KP_DOT              63
#define X_NONUS_BACKSLASH     64
#define X_APPLICATION         65
#define X_KB_POWER            66
#define X_KP_EQUAL            67
#define X_F13                 68
#define X_F14                 69
#define X_F15                 6a
#define X_F16                 6b
#define X_F17                 6c
#define X_F18                 6d
#define X_F19                 6e
#define X_F20                 6f
#define X_F21                 70
#define X_F22                 71
#define X_F23                 72
#define X_F24                 73
#define X_EXECUTE             74
#define X_HELP                75
#define X_MENU                76
#define X_SELECT              77
#define X_STOP                78
#define X_AGAIN               79
#define X_UNDO                7a
#define X_CUT                 7b
#define X_COPY                7c
#define X_PASTE               7d
#define X_FIND                7e
#define X_KB_MUTE             7f
#define X_KB_VOLUME_UP        80
#define X_KB_VOLUME_DOWN      81
#define X_LOCKING_CAPS_LOCK   82
#define X_LOCKING_NUM_LOCK    83
#define X_LOCKING_SCROLL_LOCK 84
#define X_KP_COMMA            85
#define X_KP_EQUAL_AS400      86
#define X_INTERNATIONAL_1     87
#define X_INTERNATIONAL_2     88
#define X_INTERNATIONAL_3     89
#define X_INTERNATIONAL_4     8a
#define X_INTERNATIONAL_5     8b
#define X_INTERNATIONAL_6     8c
#define X_INTERNATIONAL_7     8d
#define X_INTERNATIONAL_8     8e
#define X_INTERNATIONAL_9     8f
#define X_LANGUAGE_1          90
#define X_LANGUAGE_2          91
#define X_LANGUAGE_3          92
#define X_LANGUAGE_4          93
#define X_LANGUAGE_5          94
#define X_LANGUAGE_6          95
#define X_LANGUAGE_7          96
#define X_LANGUAGE_8          97
#define X_LANGUAGE_9          98
#define X_ALTERNATE_ERASE     99
#define X_SYSTEM_REQUEST      9a
#define X_CANCEL              9b
#define X_CLEAR               9c
#define X_PRIOR               9d
#define X_RETURN              9e
#define X_SEPARATOR           9f
#define X_OUT                 a0
#define X_OPER                a1
#define X_CLEAR_AGAIN         a2
#define X_CRSEL               a3
#define X_EXSEL               a4

/* Modifiers */
#define X_LEFT_CTRL           e0
#define X_LEFT_SHIFT          e1
#define X_LEFT_ALT            e2
#define X_LEFT_GUI            e3
#define X_RIGHT_CTRL          e4
#define X_RIGHT_SHIFT         e5
#define X_RIGHT_ALT           e6
#define X_RIGHT_GUI           e7

/* Media and Function keys */
/* Generic Desktop Page (0x01) */
#define X_SYSTEM_POWER        a5
#define X_SYSTEM_SLEEP        a6
#define X_SYSTEM_WAKE         a7

/* Consumer Page (0x0C) */
#define X_AUDIO_MUTE          a8
#define X_AUDIO_VOL_UP        a9
#define X_AUDIO_VOL_DOWN      aa
#define X_MEDIA_NEXT_TRACK    ab
#define X_MEDIA_PREV_TRACK    ac
#define X_MEDIA_STOP          ad
#define X_MEDIA_PLAY_PAUSE    ae
#define X_MEDIA_SELECT        af
#define X_MEDIA_EJECT         b0
#define X_MAIL                b1
#define X_CALCULATOR          b2
#define X_MY_COMPUTER         b3
#define X_WWW_SEARCH          b4
#define X_WWW_HOME            b5
#define X_WWW_BACK            b6
#define X_WWW_FORWARD         b7
#define X_WWW_STOP            b8
#define X_WWW_REFRESH         b9
#define X_WWW_FAVORITES       ba
#define X_MEDIA_FAST_FORWARD  bb
#define X_MEDIA_REWIND        bc
#define X_BRIGHTNESS_UP       bd
#define X_BRIGHTNESS_DOWN     be
#define X_CONTROL_PANEL       bf
#define X_ASSISTANT           c0

/* Mouse Buttons (unallocated range in HID spec) */
#define X_MS_UP              cd
#define X_MS_DOWN            ce
#define X_MS_LEFT            cf
#define X_MS_RIGHT           d0
#define X_MS_BTN1            d1
#define X_MS_BTN2            d2
#define X_MS_BTN3            d3
#define X_MS_BTN4            d4
#define X_MS_BTN5            d5
#define X_MS_BTN6            d6
#define X_MS_BTN7            d7
#define X_MS_BTN8            d8
#define X_MS_WH_UP           d9
#define X_MS_WH_DOWN         da
#define X_MS_WH_LEFT         db
#define X_MS_WH_RIGHT        dc
#define X_MS_ACCEL0          dd
#define X_MS_ACCEL1          de
#define X_MS_ACCEL2          df

// Send string macros
#define STRINGIZE(z) #z
#define ADD_SLASH_X(y) STRINGIZE(\x##y)
#define SYMBOL_STR(x) ADD_SLASH_X(x)

#define SS_QMK_PREFIX 1

#define SS_TAP_CODE 1
#define SS_DOWN_CODE 2
#define SS_UP_CODE 3
#define SS_DELAY_CODE 4

#define SS_TAP(keycode) "\1\1" SYMBOL_STR(keycode)
#define SS_DOWN(keycode) "\1\2" SYMBOL_STR(keycode)
#define SS_UP(keycode) "\1\3" SYMBOL_STR(keycode)
#define SS_DELAY(msecs) "\1\4" STRINGIZE(msecs) "|"

// `string` arguments must not be parenthesized
#define SS_LCTL(string) SS_DOWN(X_LCTL) string SS_UP(X_LCTL)
#define SS_LSFT(string) SS_DOWN(X_LSFT) string SS_UP(X_LSFT)
#define SS_LALT(string) SS_DOWN(X_LALT) string SS_UP(X_LALT)
#define SS_LGUI(string) SS_DOWN(X_LGUI) string SS_UP(X_LGUI)
#define SS_LOPT(string) SS_LALT(string)
#define SS_LCMD(string) SS_LGUI(string)
#define SS_LWIN(string) SS_LGUI(string)

#define SS_RCTL(string) SS_DOWN(X_RCTL) string SS_UP(X_RCTL)
#define SS_RSFT(string) SS_DOWN(X_RSFT) string SS_UP(X_RSFT)
#define SS_RALT(string) SS_DOWN(X_RALT) string SS_UP(X_RALT)
#define SS_RGUI(string) SS_DOWN(X_RGUI) string SS_UP(X_RGUI)
#define SS_ALGR(string) SS_RALT(string)
#define SS_ROPT(string) SS_RALT(string)
#define SS_RCMD(string) SS_RGUI(string)
#define SS_RWIN(string) SS_RGUI(string)
