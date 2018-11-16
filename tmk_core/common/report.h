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

#ifndef REPORT_H
#define REPORT_H

#include <stdint.h>
#include "keycode.h"


/* report id */
#define REPORT_ID_KEYBOARD  1
#define REPORT_ID_MOUSE     2
#define REPORT_ID_SYSTEM    3
#define REPORT_ID_CONSUMER  4
#define REPORT_ID_NKRO      5

/* mouse buttons */
#define MOUSE_BTN1 (1<<0)
#define MOUSE_BTN2 (1<<1)
#define MOUSE_BTN3 (1<<2)
#define MOUSE_BTN4 (1<<3)
#define MOUSE_BTN5 (1<<4)

/* Consumer Page(0x0C)
 * following are supported by Windows: http://msdn.microsoft.com/en-us/windows/hardware/gg463372.aspx
 */
#define AUDIO_MUTE              0x00E2
#define AUDIO_VOL_UP            0x00E9
#define AUDIO_VOL_DOWN          0x00EA
#define TRANSPORT_NEXT_TRACK    0x00B5
#define TRANSPORT_PREV_TRACK    0x00B6
#define TRANSPORT_STOP          0x00B7
#define TRANSPORT_STOP_EJECT    0x00CC
#define TRANSPORT_PLAY_PAUSE    0x00CD
/* application launch */
#define AL_CC_CONFIG            0x0183
#define AL_EMAIL                0x018A
#define AL_CALCULATOR           0x0192
#define AL_LOCAL_BROWSER        0x0194
/* application control */
#define AC_SEARCH               0x0221
#define AC_HOME                 0x0223
#define AC_BACK                 0x0224
#define AC_FORWARD              0x0225
#define AC_STOP                 0x0226
#define AC_REFRESH              0x0227
#define AC_BOOKMARKS            0x022A
/* supplement for Bluegiga iWRAP HID(not supported by Windows?) */
#define AL_LOCK                 0x019E
#define TRANSPORT_RECORD        0x00B2
#define TRANSPORT_FAST_FORWARD  0x00B3
#define TRANSPORT_REWIND        0x00B4
#define TRANSPORT_EJECT         0x00B8
#define AC_MINIMIZE             0x0206

/* Generic Desktop Page(0x01) - system power control */
#define SYSTEM_POWER_DOWN       0x0081
#define SYSTEM_SLEEP            0x0082
#define SYSTEM_WAKE_UP          0x0083


#define NKRO_SHARED_EP
/* key report size(NKRO or boot mode) */
#if defined(NKRO_ENABLE)
  #if defined(PROTOCOL_LUFA) || defined(PROTOCOL_CHIBIOS)
    #include "protocol/usb_descriptor.h"
    #define KEYBOARD_REPORT_BITS (SHARED_EPSIZE - 2)
  #elif defined(PROTOCOL_ARM_ATSAM)
    #include "protocol/arm_atsam/usb/udi_device_epsize.h"
    #define KEYBOARD_REPORT_BITS (NKRO_EPSIZE - 1)
    #undef NKRO_SHARED_EP
    #undef MOUSE_SHARED_EP
  #else
    #error "NKRO not supported with this protocol"
  #endif
#endif

#ifdef KEYBOARD_SHARED_EP
#   define KEYBOARD_REPORT_SIZE 9
#else
#   define KEYBOARD_REPORT_SIZE 8
#endif

#define KEYBOARD_REPORT_KEYS 6

/* VUSB hardcodes keyboard and mouse+extrakey only */
#if defined(PROTOCOL_VUSB)
  #undef KEYBOARD_SHARED_EP
  #undef MOUSE_SHARED_EP
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
#ifdef NKRO_SHARED_EP
        uint8_t report_id;
#endif
        uint8_t mods;
        uint8_t bits[KEYBOARD_REPORT_BITS];
    } nkro;
#endif
} __attribute__ ((packed)) report_keyboard_t;

typedef struct {
#ifdef MOUSE_SHARED_EP
    uint8_t report_id;
#endif
    uint8_t buttons;
    int8_t x;
    int8_t y;
    int8_t v;
    int8_t h;
} __attribute__ ((packed)) report_mouse_t;


/* keycode to system usage */
#define KEYCODE2SYSTEM(key) \
    (key == KC_SYSTEM_POWER ? SYSTEM_POWER_DOWN : \
    (key == KC_SYSTEM_SLEEP ? SYSTEM_SLEEP : \
    (key == KC_SYSTEM_WAKE  ? SYSTEM_WAKE_UP : 0)))

/* keycode to consumer usage */
#define KEYCODE2CONSUMER(key) \
    (key == KC_AUDIO_MUTE       ?  AUDIO_MUTE : \
    (key == KC_AUDIO_VOL_UP     ?  AUDIO_VOL_UP : \
    (key == KC_AUDIO_VOL_DOWN   ?  AUDIO_VOL_DOWN : \
    (key == KC_MEDIA_NEXT_TRACK ?  TRANSPORT_NEXT_TRACK : \
    (key == KC_MEDIA_PREV_TRACK ?  TRANSPORT_PREV_TRACK : \
    (key == KC_MEDIA_FAST_FORWARD ?  TRANSPORT_FAST_FORWARD : \
    (key == KC_MEDIA_REWIND     ?  TRANSPORT_REWIND : \
    (key == KC_MEDIA_STOP       ?  TRANSPORT_STOP : \
    (key == KC_MEDIA_EJECT      ?  TRANSPORT_STOP_EJECT : \
    (key == KC_MEDIA_PLAY_PAUSE ?  TRANSPORT_PLAY_PAUSE : \
    (key == KC_MEDIA_SELECT     ?  AL_CC_CONFIG : \
    (key == KC_MAIL             ?  AL_EMAIL : \
    (key == KC_CALCULATOR       ?  AL_CALCULATOR : \
    (key == KC_MY_COMPUTER      ?  AL_LOCAL_BROWSER : \
    (key == KC_WWW_SEARCH       ?  AC_SEARCH : \
    (key == KC_WWW_HOME         ?  AC_HOME : \
    (key == KC_WWW_BACK         ?  AC_BACK : \
    (key == KC_WWW_FORWARD      ?  AC_FORWARD : \
    (key == KC_WWW_STOP         ?  AC_STOP : \
    (key == KC_WWW_REFRESH      ?  AC_REFRESH : \
    (key == KC_WWW_FAVORITES    ?  AC_BOOKMARKS : 0)))))))))))))))))))))

uint8_t has_anykey(report_keyboard_t* keyboard_report);
uint8_t get_first_key(report_keyboard_t* keyboard_report);

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

#endif
