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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"

/* HID report IDs */
enum hid_report_ids {
    REPORT_ID_KEYBOARD = 1,
    REPORT_ID_MOUSE,
    REPORT_ID_SYSTEM,
    REPORT_ID_CONSUMER,
    REPORT_ID_NKRO
};

/* Mouse buttons */
enum mouse_buttons {
    MOUSE_BTN1 = (1 << 0),
    MOUSE_BTN2 = (1 << 1),
    MOUSE_BTN3 = (1 << 2),
    MOUSE_BTN4 = (1 << 3),
    MOUSE_BTN5 = (1 << 4)
};

// clang-format off

/* Consumer Page (0x0C)
 *
 * See https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf#page=75
 */
enum consumer_usages {
    // 15.5 Display Controls
    BRIGHTNESS_UP          = 0x06F,
    BRIGHTNESS_DOWN        = 0x070,
    // 15.7 Transport Controls
    TRANSPORT_RECORD       = 0x0B2,
    TRANSPORT_FAST_FORWARD = 0x0B3,
    TRANSPORT_REWIND       = 0x0B4,
    TRANSPORT_NEXT_TRACK   = 0x0B5,
    TRANSPORT_PREV_TRACK   = 0x0B6,
    TRANSPORT_STOP         = 0x0B7,
    TRANSPORT_EJECT        = 0x0B8,
    TRANSPORT_STOP_EJECT   = 0x0CC,
    TRANSPORT_PLAY_PAUSE   = 0x0CD,
    // 15.9.1 Audio Controls - Volume
    AUDIO_MUTE             = 0x0E2,
    AUDIO_VOL_UP           = 0x0E9,
    AUDIO_VOL_DOWN         = 0x0EA,
    // 15.15 Application Launch Buttons
    AL_CC_CONFIG           = 0x183,
    AL_EMAIL               = 0x18A,
    AL_CALCULATOR          = 0x192,
    AL_LOCAL_BROWSER       = 0x194,
    AL_LOCK                = 0x19E,
    // 15.16 Generic GUI Application Controls
    AC_MINIMIZE            = 0x206,
    AC_SEARCH              = 0x221,
    AC_HOME                = 0x223,
    AC_BACK                = 0x224,
    AC_FORWARD             = 0x225,
    AC_STOP                = 0x226,
    AC_REFRESH             = 0x227,
    AC_BOOKMARKS           = 0x22A
};

/* Generic Desktop Page (0x01)
 *
 * See https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf#page=26
 */
enum desktop_usages {
    // 4.5.1 System Controls - Power Controls
    SYSTEM_POWER_DOWN = 0x81,
    SYSTEM_SLEEP      = 0x82,
    SYSTEM_WAKE_UP    = 0x83
};

// clang-format on

#define NKRO_SHARED_EP
/* key report size(NKRO or boot mode) */
#if defined(NKRO_ENABLE)
#    if defined(PROTOCOL_LUFA) || defined(PROTOCOL_CHIBIOS)
#        include "protocol/usb_descriptor.h"
#        define KEYBOARD_REPORT_BITS (SHARED_EPSIZE - 2)
#    elif defined(PROTOCOL_ARM_ATSAM)
#        include "protocol/arm_atsam/usb/udi_device_epsize.h"
#        define KEYBOARD_REPORT_BITS (NKRO_EPSIZE - 1)
#        undef NKRO_SHARED_EP
#        undef MOUSE_SHARED_EP
#    else
#        error "NKRO not supported with this protocol"
#    endif
#endif

#ifdef KEYBOARD_SHARED_EP
#    define KEYBOARD_REPORT_SIZE 9
#else
#    define KEYBOARD_REPORT_SIZE 8
#endif

#define KEYBOARD_REPORT_KEYS 6

/* VUSB hardcodes keyboard and mouse+extrakey only */
#if defined(PROTOCOL_VUSB)
#    undef KEYBOARD_SHARED_EP
#    undef MOUSE_SHARED_EP
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * keyboard report is 8-byte array retains state of 8 modifiers and 6 keys.
 *
 * byte |0       |1       |2       |3       |4       |5       |6       |7
 * -----+--------+--------+--------+--------+--------+--------+--------+--------
 * desc |mods    |reserved|keys[0] |keys[1] |keys[2] |keys[3] |keys[4] |keys[5]
 *
 * It is exended to 16 bytes to retain 120keys+8mods when NKRO mode.
 *
 * byte |0       |1       |2       |3       |4       |5       |6       |7        ... |15
 * -----+--------+--------+--------+--------+--------+--------+--------+--------     +--------
 * desc |mods    |bits[0] |bits[1] |bits[2] |bits[3] |bits[4] |bits[5] |bits[6]  ... |bit[14]
 *
 * mods retains state of 8 modifiers.
 *
 *  bit |0       |1       |2       |3       |4       |5       |6       |7
 * -----+--------+--------+--------+--------+--------+--------+--------+--------
 * desc |Lcontrol|Lshift  |Lalt    |Lgui    |Rcontrol|Rshift  |Ralt    |Rgui
 *
 */
typedef union {
    uint8_t raw[KEYBOARD_REPORT_SIZE];
    struct {
#ifdef KEYBOARD_SHARED_EP
        uint8_t report_id;
#endif
        uint8_t mods;
        uint8_t reserved;
        uint8_t keys[KEYBOARD_REPORT_KEYS];
    };
#ifdef NKRO_ENABLE
    struct nkro_report {
#    ifdef NKRO_SHARED_EP
        uint8_t report_id;
#    endif
        uint8_t mods;
        uint8_t bits[KEYBOARD_REPORT_BITS];
    } nkro;
#endif
} __attribute__((packed)) report_keyboard_t;

typedef struct {
    uint8_t  report_id;
    uint16_t usage;
} __attribute__((packed)) report_extra_t;

typedef struct {
#ifdef MOUSE_SHARED_EP
    uint8_t report_id;
#endif
    uint8_t buttons;
    int8_t  x;
    int8_t  y;
    int8_t  v;
    int8_t  h;
} __attribute__((packed)) report_mouse_t;

/* keycode to system usage */
static inline uint16_t KEYCODE2SYSTEM(uint8_t key) {
    switch (key) {
        case KC_SYSTEM_POWER:
            return SYSTEM_POWER_DOWN;
        case KC_SYSTEM_SLEEP:
            return SYSTEM_SLEEP;
        case KC_SYSTEM_WAKE:
            return SYSTEM_WAKE_UP;
        default:
            return 0;
    }
}

/* keycode to consumer usage */
static inline uint16_t KEYCODE2CONSUMER(uint8_t key) {
    switch (key) {
        case KC_AUDIO_MUTE:
            return AUDIO_MUTE;
        case KC_AUDIO_VOL_UP:
            return AUDIO_VOL_UP;
        case KC_AUDIO_VOL_DOWN:
            return AUDIO_VOL_DOWN;
        case KC_MEDIA_NEXT_TRACK:
            return TRANSPORT_NEXT_TRACK;
        case KC_MEDIA_PREV_TRACK:
            return TRANSPORT_PREV_TRACK;
        case KC_MEDIA_FAST_FORWARD:
            return TRANSPORT_FAST_FORWARD;
        case KC_MEDIA_REWIND:
            return TRANSPORT_REWIND;
        case KC_MEDIA_STOP:
            return TRANSPORT_STOP;
        case KC_MEDIA_EJECT:
            return TRANSPORT_STOP_EJECT;
        case KC_MEDIA_PLAY_PAUSE:
            return TRANSPORT_PLAY_PAUSE;
        case KC_MEDIA_SELECT:
            return AL_CC_CONFIG;
        case KC_MAIL:
            return AL_EMAIL;
        case KC_CALCULATOR:
            return AL_CALCULATOR;
        case KC_MY_COMPUTER:
            return AL_LOCAL_BROWSER;
        case KC_WWW_SEARCH:
            return AC_SEARCH;
        case KC_WWW_HOME:
            return AC_HOME;
        case KC_WWW_BACK:
            return AC_BACK;
        case KC_WWW_FORWARD:
            return AC_FORWARD;
        case KC_WWW_STOP:
            return AC_STOP;
        case KC_WWW_REFRESH:
            return AC_REFRESH;
        case KC_BRIGHTNESS_UP:
            return BRIGHTNESS_UP;
        case KC_BRIGHTNESS_DOWN:
            return BRIGHTNESS_DOWN;
        case KC_WWW_FAVORITES:
            return AC_BOOKMARKS;
        default:
            return 0;
    }
}

uint8_t has_anykey(report_keyboard_t* keyboard_report);
uint8_t get_first_key(report_keyboard_t* keyboard_report);
bool    is_key_pressed(report_keyboard_t* keyboard_report, uint8_t key);

void add_key_byte(report_keyboard_t* keyboard_report, uint8_t code);
void del_key_byte(report_keyboard_t* keyboard_report, uint8_t code);
#ifdef NKRO_ENABLE
void add_key_bit(report_keyboard_t* keyboard_report, uint8_t code);
void del_key_bit(report_keyboard_t* keyboard_report, uint8_t code);
#endif

void add_key_to_report(report_keyboard_t* keyboard_report, uint8_t key);
void del_key_from_report(report_keyboard_t* keyboard_report, uint8_t key);
void clear_keys_from_report(report_keyboard_t* keyboard_report);

#ifdef __cplusplus
}
#endif
