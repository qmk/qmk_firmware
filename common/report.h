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
#define REPORT_ID_MOUSE     1
#define REPORT_ID_SYSTEM    2
#define REPORT_ID_CONSUMER  3

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
#define TRANSPORT_REWIND        0x00B4
#define TRANSPORT_EJECT         0x00B8
#define AC_MINIMIZE             0x0206

/* Generic Desktop Page(0x01) - system power control */
#define SYSTEM_POWER_DOWN       0x0081
#define SYSTEM_SLEEP            0x0082
#define SYSTEM_WAKE_UP          0x0083


/* key report size(NKRO or boot mode) */
#if defined(PROTOCOL_PJRC)
#   include "usb.h"
#   if defined(KBD2_REPORT_KEYS) && KBD2_REPORT_KEYS > KBD_REPORT_KEYS
#       define REPORT_KEYS KBD2_REPORT_KEYS
#   else
#       define REPORT_KEYS KBD_REPORT_KEYS
#   endif
#else
#   define REPORT_KEYS 6
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t mods;
    uint8_t rserved;
    uint8_t keys[REPORT_KEYS];
} __attribute__ ((packed)) report_keyboard_t;

typedef struct {
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
    (key == KC_MEDIA_STOP       ?  TRANSPORT_STOP : \
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
    (key == KC_WWW_FAVORITES    ?  AC_BOOKMARKS : 0))))))))))))))))))

#ifdef __cplusplus
}
#endif

#endif
