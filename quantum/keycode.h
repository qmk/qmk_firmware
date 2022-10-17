/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

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

/*
 * Keycodes based on HID Keyboard/Keypad Usage Page (0x07) plus media keys from Generic Desktop Page (0x01) and Consumer Page (0x0C)
 *
 * See https://web.archive.org/web/20060218214400/http://www.usb.org/developers/devclass_docs/Hut1_12.pdf
 * or http://www.usb.org/developers/hidpage/Hut1_12v2.pdf (older)
 */

#pragma once

/* FIXME: Add doxygen comments here */

#define IS_ERROR(code) (KC_ROLL_OVER <= (code) && (code) <= KC_UNDEFINED)
#define IS_ANY(code) (KC_A <= (code) && (code) <= 0xFF)
#define IS_KEY(code) (KC_A <= (code) && (code) <= KC_EXSEL)
#define IS_MOD(code) (KC_LEFT_CTRL <= (code) && (code) <= KC_RIGHT_GUI)

#define IS_SPECIAL(code) ((0xA5 <= (code) && (code) <= 0xDF) || (0xE8 <= (code) && (code) <= 0xFF))
#define IS_SYSTEM(code) (KC_PWR <= (code) && (code) <= KC_WAKE)
#define IS_CONSUMER(code) (KC_MUTE <= (code) && (code) <= KC_ASST)

#define IS_MOUSEKEY(code) (KC_MS_UP <= (code) && (code) <= KC_MS_ACCEL2)
#define IS_MOUSEKEY_MOVE(code) (KC_MS_UP <= (code) && (code) <= KC_MS_RIGHT)
#define IS_MOUSEKEY_BUTTON(code) (KC_MS_BTN1 <= (code) && (code) <= KC_MS_BTN8)
#define IS_MOUSEKEY_WHEEL(code) (KC_MS_WH_UP <= (code) && (code) <= KC_MS_WH_RIGHT)
#define IS_MOUSEKEY_ACCEL(code) (KC_MS_ACCEL0 <= (code) && (code) <= KC_MS_ACCEL2)

#define MOD_BIT(code) (1 << MOD_INDEX(code))
#define MOD_INDEX(code) ((code)&0x07)

#define MOD_MASK_CTRL (MOD_BIT(KC_LEFT_CTRL) | MOD_BIT(KC_RIGHT_CTRL))
#define MOD_MASK_SHIFT (MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_RIGHT_SHIFT))
#define MOD_MASK_ALT (MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_RIGHT_ALT))
#define MOD_MASK_GUI (MOD_BIT(KC_LEFT_GUI) | MOD_BIT(KC_RIGHT_GUI))
#define MOD_MASK_CS (MOD_MASK_CTRL | MOD_MASK_SHIFT)
#define MOD_MASK_CA (MOD_MASK_CTRL | MOD_MASK_ALT)
#define MOD_MASK_CG (MOD_MASK_CTRL | MOD_MASK_GUI)
#define MOD_MASK_SA (MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_SG (MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_AG (MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSA (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_CSG (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_CAG (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_SAG (MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSAG (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)

// clang-format off

/*
 * Short names for ease of definition of keymap
 */
/* Transparent */
#define KC_TRANSPARENT 0x01
#define KC_TRNS KC_TRANSPARENT

/* Punctuation */
#define KC_ENT  KC_ENTER
#define KC_ESC  KC_ESCAPE
#define KC_BSPC KC_BACKSPACE
#define KC_SPC  KC_SPACE
#define KC_MINS KC_MINUS
#define KC_EQL  KC_EQUAL
#define KC_LBRC KC_LEFT_BRACKET
#define KC_RBRC KC_RIGHT_BRACKET
#define KC_BSLS KC_BACKSLASH
#define KC_NUHS KC_NONUS_HASH
#define KC_SCLN KC_SEMICOLON
#define KC_QUOT KC_QUOTE
#define KC_GRV  KC_GRAVE
#define KC_COMM KC_COMMA
#define KC_SLSH KC_SLASH
#define KC_NUBS KC_NONUS_BACKSLASH

/* Lock Keys */
#define KC_CAPS KC_CAPS_LOCK
#define KC_SCRL KC_SCROLL_LOCK
#define KC_NUM  KC_NUM_LOCK
#define KC_LCAP KC_LOCKING_CAPS_LOCK
#define KC_LNUM KC_LOCKING_NUM_LOCK
#define KC_LSCR KC_LOCKING_SCROLL_LOCK

/* Commands */
#define KC_PSCR KC_PRINT_SCREEN
#define KC_PAUS KC_PAUSE
#define KC_BRK  KC_PAUSE
#define KC_INS  KC_INSERT
#define KC_PGUP KC_PAGE_UP
#define KC_DEL  KC_DELETE
#define KC_PGDN KC_PAGE_DOWN
#define KC_RGHT KC_RIGHT
#define KC_APP  KC_APPLICATION
#define KC_EXEC KC_EXECUTE
#define KC_SLCT KC_SELECT
#define KC_AGIN KC_AGAIN
#define KC_PSTE KC_PASTE
#define KC_ERAS KC_ALTERNATE_ERASE
#define KC_SYRQ KC_SYSTEM_REQUEST
#define KC_CNCL KC_CANCEL
#define KC_CLR  KC_CLEAR
#define KC_PRIR KC_PRIOR
#define KC_RETN KC_RETURN
#define KC_SEPR KC_SEPARATOR
#define KC_CLAG KC_CLEAR_AGAIN
#define KC_CRSL KC_CRSEL
#define KC_EXSL KC_EXSEL

/* Keypad */
#define KC_PSLS KC_KP_SLASH
#define KC_PAST KC_KP_ASTERISK
#define KC_PMNS KC_KP_MINUS
#define KC_PPLS KC_KP_PLUS
#define KC_PENT KC_KP_ENTER
#define KC_P1   KC_KP_1
#define KC_P2   KC_KP_2
#define KC_P3   KC_KP_3
#define KC_P4   KC_KP_4
#define KC_P5   KC_KP_5
#define KC_P6   KC_KP_6
#define KC_P7   KC_KP_7
#define KC_P8   KC_KP_8
#define KC_P9   KC_KP_9
#define KC_P0   KC_KP_0
#define KC_PDOT KC_KP_DOT
#define KC_PEQL KC_KP_EQUAL
#define KC_PCMM KC_KP_COMMA

/* Language Specific */
#define KC_INT1 KC_INTERNATIONAL_1
#define KC_INT2 KC_INTERNATIONAL_2
#define KC_INT3 KC_INTERNATIONAL_3
#define KC_INT4 KC_INTERNATIONAL_4
#define KC_INT5 KC_INTERNATIONAL_5
#define KC_INT6 KC_INTERNATIONAL_6
#define KC_INT7 KC_INTERNATIONAL_7
#define KC_INT8 KC_INTERNATIONAL_8
#define KC_INT9 KC_INTERNATIONAL_9
#define KC_LNG1 KC_LANGUAGE_1
#define KC_LNG2 KC_LANGUAGE_2
#define KC_LNG3 KC_LANGUAGE_3
#define KC_LNG4 KC_LANGUAGE_4
#define KC_LNG5 KC_LANGUAGE_5
#define KC_LNG6 KC_LANGUAGE_6
#define KC_LNG7 KC_LANGUAGE_7
#define KC_LNG8 KC_LANGUAGE_8
#define KC_LNG9 KC_LANGUAGE_9

/* Modifiers */
#define KC_LCTL KC_LEFT_CTRL
#define KC_LSFT KC_LEFT_SHIFT
#define KC_LALT KC_LEFT_ALT
#define KC_LOPT KC_LEFT_ALT
#define KC_LGUI KC_LEFT_GUI
#define KC_LCMD KC_LEFT_GUI
#define KC_LWIN KC_LEFT_GUI
#define KC_RCTL KC_RIGHT_CTRL
#define KC_RSFT KC_RIGHT_SHIFT
#define KC_RALT KC_RIGHT_ALT
#define KC_ALGR KC_RIGHT_ALT
#define KC_ROPT KC_RIGHT_ALT
#define KC_RGUI KC_RIGHT_GUI
#define KC_RCMD KC_RIGHT_GUI
#define KC_RWIN KC_RIGHT_GUI

/* Generic Desktop Page (0x01) */
#define KC_PWR  KC_SYSTEM_POWER
#define KC_SLEP KC_SYSTEM_SLEEP
#define KC_WAKE KC_SYSTEM_WAKE

/* Consumer Page (0x0C) */
#define KC_MUTE KC_AUDIO_MUTE
#define KC_VOLU KC_AUDIO_VOL_UP
#define KC_VOLD KC_AUDIO_VOL_DOWN
#define KC_MNXT KC_MEDIA_NEXT_TRACK
#define KC_MPRV KC_MEDIA_PREV_TRACK
#define KC_MSTP KC_MEDIA_STOP
#define KC_MPLY KC_MEDIA_PLAY_PAUSE
#define KC_MSEL KC_MEDIA_SELECT
#define KC_EJCT KC_MEDIA_EJECT
#define KC_CALC KC_CALCULATOR
#define KC_MYCM KC_MY_COMPUTER
#define KC_WSCH KC_WWW_SEARCH
#define KC_WHOM KC_WWW_HOME
#define KC_WBAK KC_WWW_BACK
#define KC_WFWD KC_WWW_FORWARD
#define KC_WSTP KC_WWW_STOP
#define KC_WREF KC_WWW_REFRESH
#define KC_WFAV KC_WWW_FAVORITES
#define KC_MFFD KC_MEDIA_FAST_FORWARD
#define KC_MRWD KC_MEDIA_REWIND
#define KC_BRIU KC_BRIGHTNESS_UP
#define KC_BRID KC_BRIGHTNESS_DOWN
#define KC_CPNL KC_CONTROL_PANEL
#define KC_ASST KC_ASSISTANT

/* System Specific */
#define KC_BRMU KC_PAUSE
#define KC_BRMD KC_SCROLL_LOCK

/* Mouse Keys */
#define KC_MS_U KC_MS_UP
#define KC_MS_D KC_MS_DOWN
#define KC_MS_L KC_MS_LEFT
#define KC_MS_R KC_MS_RIGHT
#define KC_BTN1 KC_MS_BTN1
#define KC_BTN2 KC_MS_BTN2
#define KC_BTN3 KC_MS_BTN3
#define KC_BTN4 KC_MS_BTN4
#define KC_BTN5 KC_MS_BTN5
#define KC_BTN6 KC_MS_BTN6
#define KC_BTN7 KC_MS_BTN7
#define KC_BTN8 KC_MS_BTN8
#define KC_WH_U KC_MS_WH_UP
#define KC_WH_D KC_MS_WH_DOWN
#define KC_WH_L KC_MS_WH_LEFT
#define KC_WH_R KC_MS_WH_RIGHT
#define KC_ACL0 KC_MS_ACCEL0
#define KC_ACL1 KC_MS_ACCEL1
#define KC_ACL2 KC_MS_ACCEL2

// clang-format on

/* Keyboard/Keypad Page (0x07) */
enum hid_keyboard_keypad_usage {
    KC_NO = 0x00,
    KC_ROLL_OVER,
    KC_POST_FAIL,
    KC_UNDEFINED,
    KC_A,
    KC_B,
    KC_C,
    KC_D,
    KC_E,
    KC_F,
    KC_G,
    KC_H,
    KC_I,
    KC_J,
    KC_K,
    KC_L,
    KC_M, // 0x10
    KC_N,
    KC_O,
    KC_P,
    KC_Q,
    KC_R,
    KC_S,
    KC_T,
    KC_U,
    KC_V,
    KC_W,
    KC_X,
    KC_Y,
    KC_Z,
    KC_1,
    KC_2,
    KC_3, // 0x20
    KC_4,
    KC_5,
    KC_6,
    KC_7,
    KC_8,
    KC_9,
    KC_0,
    KC_ENTER,
    KC_ESCAPE,
    KC_BACKSPACE,
    KC_TAB,
    KC_SPACE,
    KC_MINUS,
    KC_EQUAL,
    KC_LEFT_BRACKET,
    KC_RIGHT_BRACKET, // 0x30
    KC_BACKSLASH,
    KC_NONUS_HASH,
    KC_SEMICOLON,
    KC_QUOTE,
    KC_GRAVE,
    KC_COMMA,
    KC_DOT,
    KC_SLASH,
    KC_CAPS_LOCK,
    KC_F1,
    KC_F2,
    KC_F3,
    KC_F4,
    KC_F5,
    KC_F6,
    KC_F7, // 0x40
    KC_F8,
    KC_F9,
    KC_F10,
    KC_F11,
    KC_F12,
    KC_PRINT_SCREEN,
    KC_SCROLL_LOCK,
    KC_PAUSE,
    KC_INSERT,
    KC_HOME,
    KC_PAGE_UP,
    KC_DELETE,
    KC_END,
    KC_PAGE_DOWN,
    KC_RIGHT,
    KC_LEFT, // 0x50
    KC_DOWN,
    KC_UP,
    KC_NUM_LOCK,
    KC_KP_SLASH,
    KC_KP_ASTERISK,
    KC_KP_MINUS,
    KC_KP_PLUS,
    KC_KP_ENTER,
    KC_KP_1,
    KC_KP_2,
    KC_KP_3,
    KC_KP_4,
    KC_KP_5,
    KC_KP_6,
    KC_KP_7,
    KC_KP_8, // 0x60
    KC_KP_9,
    KC_KP_0,
    KC_KP_DOT,
    KC_NONUS_BACKSLASH,
    KC_APPLICATION,
    KC_KB_POWER,
    KC_KP_EQUAL,
    KC_F13,
    KC_F14,
    KC_F15,
    KC_F16,
    KC_F17,
    KC_F18,
    KC_F19,
    KC_F20,
    KC_F21, // 0x70
    KC_F22,
    KC_F23,
    KC_F24,
    KC_EXECUTE,
    KC_HELP,
    KC_MENU,
    KC_SELECT,
    KC_STOP,
    KC_AGAIN,
    KC_UNDO,
    KC_CUT,
    KC_COPY,
    KC_PASTE,
    KC_FIND,
    KC_KB_MUTE,
    KC_KB_VOLUME_UP, // 0x80
    KC_KB_VOLUME_DOWN,
    KC_LOCKING_CAPS_LOCK,
    KC_LOCKING_NUM_LOCK,
    KC_LOCKING_SCROLL_LOCK,
    KC_KP_COMMA,
    KC_KP_EQUAL_AS400,
    KC_INTERNATIONAL_1,
    KC_INTERNATIONAL_2,
    KC_INTERNATIONAL_3,
    KC_INTERNATIONAL_4,
    KC_INTERNATIONAL_5,
    KC_INTERNATIONAL_6,
    KC_INTERNATIONAL_7,
    KC_INTERNATIONAL_8,
    KC_INTERNATIONAL_9,
    KC_LANGUAGE_1, // 0x90
    KC_LANGUAGE_2,
    KC_LANGUAGE_3,
    KC_LANGUAGE_4,
    KC_LANGUAGE_5,
    KC_LANGUAGE_6,
    KC_LANGUAGE_7,
    KC_LANGUAGE_8,
    KC_LANGUAGE_9,
    KC_ALTERNATE_ERASE,
    KC_SYSTEM_REQUEST,
    KC_CANCEL,
    KC_CLEAR,
    KC_PRIOR,
    KC_RETURN,
    KC_SEPARATOR,
    KC_OUT, // 0xA0
    KC_OPER,
    KC_CLEAR_AGAIN,
    KC_CRSEL,
    KC_EXSEL,

#if 0
  // ***************************************************************
  // These keycodes are present in the HID spec, but are           *
  // nonfunctional on modern OSes. QMK uses this range (0xA5-0xDF) *
  // for the media and function keys instead - see below.          *
  // ***************************************************************

  KC_KP_00                = 0xB0,
  KC_KP_000,
  KC_THOUSANDS_SEPARATOR,
  KC_DECIMAL_SEPARATOR,
  KC_CURRENCY_UNIT,
  KC_CURRENCY_SUB_UNIT,
  KC_KP_LEFT_PARENTHESIS,
  KC_KP_RIGHT_PARENTHESIS,
  KC_KP_LEFT_BRACE,
  KC_KP_RIGHT_BRACE,
  KC_KP_TAB,
  KC_KP_BACKSPACE,
  KC_KP_A,
  KC_KP_B,
  KC_KP_C,
  KC_KP_D,
  KC_KP_E,                //0xC0
  KC_KP_F,
  KC_KP_XOR,
  KC_KP_HAT,
  KC_KP_PERCENT,
  KC_KP_LESS_THAN,
  KC_KP_GREATER_THAN,
  KC_KP_AND,
  KC_KP_LAZY_AND,
  KC_KP_OR,
  KC_KP_LAZY_OR,
  KC_KP_COLON,
  KC_KP_HASH,
  KC_KP_SPACE,
  KC_KP_AT,
  KC_KP_EXCLAMATION,
  KC_KP_MEM_STORE,        //0xD0
  KC_KP_MEM_RECALL,
  KC_KP_MEM_CLEAR,
  KC_KP_MEM_ADD,
  KC_KP_MEM_SUB,
  KC_KP_MEM_MUL,
  KC_KP_MEM_DIV,
  KC_KP_PLUS_MINUS,
  KC_KP_CLEAR,
  KC_KP_CLEAR_ENTRY,
  KC_KP_BINARY,
  KC_KP_OCTAL,
  KC_KP_DECIMAL,
  KC_KP_HEXADECIMAL,
#endif

    /* Modifiers */
    KC_LEFT_CTRL = 0xE0,
    KC_LEFT_SHIFT,
    KC_LEFT_ALT,
    KC_LEFT_GUI,
    KC_RIGHT_CTRL,
    KC_RIGHT_SHIFT,
    KC_RIGHT_ALT,
    KC_RIGHT_GUI

    // **********************************************
    // * 0xF0-0xFF are unallocated in the HID spec. *
    // * QMK uses these for Mouse Keys - see below. *
    // **********************************************
};

/* Media and Function keys */
enum internal_special_keycodes {
    /* Generic Desktop Page (0x01) */
    KC_SYSTEM_POWER = 0xA5,
    KC_SYSTEM_SLEEP,
    KC_SYSTEM_WAKE,

    /* Consumer Page (0x0C) */
    KC_AUDIO_MUTE,
    KC_AUDIO_VOL_UP,
    KC_AUDIO_VOL_DOWN,
    KC_MEDIA_NEXT_TRACK,
    KC_MEDIA_PREV_TRACK,
    KC_MEDIA_STOP,
    KC_MEDIA_PLAY_PAUSE,
    KC_MEDIA_SELECT,
    KC_MEDIA_EJECT, // 0xB0
    KC_MAIL,
    KC_CALCULATOR,
    KC_MY_COMPUTER,
    KC_WWW_SEARCH,
    KC_WWW_HOME,
    KC_WWW_BACK,
    KC_WWW_FORWARD,
    KC_WWW_STOP,
    KC_WWW_REFRESH,
    KC_WWW_FAVORITES,
    KC_MEDIA_FAST_FORWARD,
    KC_MEDIA_REWIND,
    KC_BRIGHTNESS_UP,
    KC_BRIGHTNESS_DOWN,
    KC_CONTROL_PANEL,
    KC_ASSISTANT // 0xC0
};

enum mouse_keys {
/* Mouse Buttons */
#ifdef VIA_ENABLE
    KC_MS_UP = 0xF0,
#else
    KC_MS_UP = 0xCD,
#endif
    KC_MS_DOWN,
    KC_MS_LEFT,
    KC_MS_RIGHT,
    KC_MS_BTN1,
    KC_MS_BTN2,
    KC_MS_BTN3,
    KC_MS_BTN4,
    KC_MS_BTN5,
#ifdef VIA_ENABLE
    KC_MS_BTN6 = KC_MS_BTN5,
    KC_MS_BTN7 = KC_MS_BTN5,
    KC_MS_BTN8 = KC_MS_BTN5,
#else
    KC_MS_BTN6,
    KC_MS_BTN7,
    KC_MS_BTN8,
#endif

    /* Mouse Wheel */
    KC_MS_WH_UP,
    KC_MS_WH_DOWN,
    KC_MS_WH_LEFT,
    KC_MS_WH_RIGHT,

    /* Acceleration */
    KC_MS_ACCEL0,
    KC_MS_ACCEL1,
    KC_MS_ACCEL2 // 0xDF, or 0xFF if via enabled
};
