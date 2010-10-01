/* 
 * Key codes from HID Keyboard/Keypad Page
 * http://www.usb.org/developers/devclass_docs/Hut1_12.pdf
 *
 * Based on Keyboard Upgrade v0.3.0 http://github.com/rhomann/kbupgrade
 */
/*
 * Keyboard Upgrade -- Firmware for homebrew computer keyboard controllers.
 * Copyright (C) 2009  Robert Homann
 *
 * Based on RUMP (http://mg8.org/rump/), Copyright (C) 2008  Chris Lee
 *
 * Based on c64key (http://symlink.dk/projects/c64key/),
 * Copyright (C) 2006-2007  Mikkel Holm Olsen
 *
 * Based on HID-Test by Christian Starkjohann, Objective Development
 *
 * This file is part of the Keyboard Upgrade package.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Keyboard Upgrade package; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301  USA
 */

#ifndef USB_KEYCODES_H
#define USB_KEYCODES_H


enum keycodes {
    KB_NO = 0,
    KB_ROLL_OVER,
    KB_POST_FAIL,
    KB_UNDEFINED,
    KB_A,
    KB_B,
    KB_C,
    KB_D,
    KB_E,
    KB_F,
    KB_G,
    KB_H,
    KB_I,
    KB_J,
    KB_K,
    KB_L,
    KB_M,       /* 0x10 */
    KB_N,
    KB_O,
    KB_P,
    KB_Q,
    KB_R,
    KB_S,
    KB_T,
    KB_U,
    KB_V,
    KB_W,
    KB_X,
    KB_Y,
    KB_Z,
    KB_1,
    KB_2,
    KB_3,       /* 0x20 */
    KB_4,
    KB_5,
    KB_6,
    KB_7,
    KB_8,
    KB_9,
    KB_0,
    KB_ENTER,
    KB_ESCAPE,
    KB_BSPACE,
    KB_TAB,
    KB_SPACE,
    KB_MINUS,
    KB_EQUAL,
    KB_LBRACKET,          /* [ */
    KB_RBRACKET,          /* ] */
    KB_BSLASH,            /* \ (and |) */
    KB_NONUS_HASH,        /* Non-US # and ~ */
    KB_SCOLON,            /* ; (and :) */
    KB_QUOTE,             /* ' and " */
    KB_GRAVE,             /* Grave accent and tilde */
    KB_COMMA,             /* , and < */
    KB_DOT,               /* . and > */
    KB_SLASH,             /* / and ? */
    KB_CAPSLOCK,
    KB_F1,
    KB_F2,
    KB_F3,
    KB_F4,
    KB_F5,
    KB_F6,
    KB_F7,      /* 0x40 */
    KB_F8,
    KB_F9,
    KB_F10,
    KB_F11,
    KB_F12,
    KB_PSCREEN,
    KB_SCKLOCK,
    KB_BREAK,
    KB_INSERT,
    KB_HOME,
    KB_PGUP,
    KB_DELETE,
    KB_END,
    KB_PGDOWN,
    KB_RIGHT,
    KB_LEFT,    /* 0x50 */
    KB_DOWN,
    KB_UP,
    KB_NUMLOCK,
    KP_SLASH,
    KP_ASTERISK,
    KP_MINUS,
    KP_PLUS,
    KP_ENTER,
    KP_1,
    KP_2,
    KP_3,
    KP_4,
    KP_5,
    KP_6,
    KP_7,
    KP_8,       /* 0x60 */
    KP_9,
    KP_0,
    KP_DOT,
    KB_NONUS_BSLASH,      /* Non-US \ and | */
    KB_APPLICATION,
    KB_POWER,
    KP_EQUAL,
    KB_F13,
    KB_F14,
    KB_F15,
    KB_F16,
    KB_F17,
    KB_F18,
    KB_F19,
    KB_F20,
    KB_F21,     /* 0x70 */
    KB_F22,
    KB_F23,
    KB_F24,
    KB_EXECUTE,
    KB_HELP,
    KB_MENU,
    KB_SELECT,
    KB_STOP,
    KB_AGAIN,
    KB_UNDO,
    KB_CUT,
    KB_COPY,
    KB_PASTE,
    KB_FIND,
    KB_MUTE,
    KB_VOLUP,   /* 0x80 */
    KB_VOLDOWN,
    KB_LOCKING_CAPS,      /* locking Caps Lock */
    KB_LOCKING_NUM,       /* locking Num Lock */
    KB_LOCKING_SCROLL,    /* locking Scroll Lock */
    KP_COMMA,
    KP_EQUAL_AS400,       /* equal sign on AS/400 */
    KB_INT1,
    KB_INT2,
    KB_INT3,
    KB_INT4,
    KB_INT5,
    KB_INT6,
    KB_INT7,
    KB_INT8,
    KB_INT9,
    KB_LANG1,    /* 0x90 */
    KB_LANG2,
    KB_LANG3,
    KB_LANG4,
    KB_LANG5,
    KB_LANG6,
    KB_LANG7,
    KB_LANG8,
    KB_LANG9,
    KB_ALT_ERASE,
    KB_SYSREQ,
    KB_CANCEL,
    KB_CLEAR,
    KB_PRIOR,
    KB_RETURN,
    KB_SEPARATOR,
    KB_OUT,
    KB_OPER,
    KB_CLEAR_AGAIN,
    KB_CRSEL,
    KB_EXSEL,

    KP_00 = 0xB0,
    KP_000,
    KB_THOUSANDS_SEPARATOR,
    KB_DECIMAL_SEPARATOR,
    CURRENCY_UNIT,
    CURRENCY_SUB_UNIT,
    KP_LPAREN,
    KP_RPAREN,
    KP_LCBRACKET,         /* { */
    KP_RCBRACKET,         /* } */
    KP_TAB,
    KP_BSPACE,
    KP_A,
    KP_B,
    KP_C,
    KP_D,
    KP_E,
    KP_F,
    KP_XOR,
    KP_HAT,
    KP_PERC,
    KP_LT,
    KP_GT,
    KP_AND,
    KP_LAZYAND,
    KP_OR,
    KP_LAZYOR,
    KP_COLON,
    KP_HASH,
    KP_SPACE,
    KP_ATMARK,
    KP_EXCLAMATION,
    KP_MEM_STORE,
    KP_MEM_RECALL,
    KP_MEM_CLEAR,
    KP_MEM_ADD,
    KP_MEM_SUB,
    KP_MEM_MUL,
    KP_MEM_DIV,
    KP_PLUS_MINUS,
    KP_CLEAR,
    KP_CLEAR_ENTRY,
    KP_BINARY,
    KP_OCTAL,
    KP_DECIMAL,
    KP_HEXADECIMAL,

    /* modifiers */
    KB_LCTRL = 0xE0,    /* 0x01 */
    KB_LSHIFT,          /* 0x02 */
    KB_LALT,            /* 0x04 */
    KB_LGUI,            /* 0x08 */
    KB_RCTRL,           /* 0x10 */
    KB_RSHIFT,          /* 0x20 */
    KB_RALT,            /* 0x40 */
    KB_RGUI,            /* 0x80 */

    /* extensions for internal use */
    FN_0 = 0xE8,
    FN_1,
    FN_2,
    FN_3,
    MS_UP = 0xF0,
    MS_DOWN,
    MS_LEFT,
    MS_RIGHT,
    MS_BTN1 = 0xF4,
    MS_BTN2,
    MS_BTN3,
    MS_BTN4,
    MS_BTN5,
    MS_WH_UP,
    MS_WH_DOWN,
    MS_WH_LEFT,
    MS_WH_RIGHT,
};

#endif /* USB_KEYCODES_H */
