/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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
#ifndef ACTION_MACRO_H
#define ACTION_MACRO_H
#include <stdint.h>
#include <avr/pgmspace.h>


#define MACRO_NONE  0
#define MACRO(...) ({ static const macro_t __m[] PROGMEM = { __VA_ARGS__ }; &__m[0]; })


typedef uint8_t macro_t;


#ifndef NO_ACTION_MACRO
void action_macro_play(const macro_t *macro_p);
#else
#define action_macro_play(macro)
#endif



/* TODO: NOT FINISHED 
normal mode command:
    key(down):      0x04-7f/73(F24)
    key(up):        0x84-ff
command:        0x00-03, 0x80-83(0x74-7f, 0xf4-ff)
    mods down   0x00
    mods up     0x01
    wait        0x02
    interval    0x03
    extkey down 0x80
    extkey up   0x81
    ext commad  0x82
    ext mode    0x83
    end         0xff

extension mode command: NOT IMPLEMENTED
    key down            0x00
    key up              0x01
    key down + wait
    key up   + wait
    mods push
    mods pop
    wait
    interval
    if
    loop
    push
    pop
    all up
    end
*/
enum macro_command_id{
    /* 0x00 - 0x03 */
    END                 = 0x00,
    MODS_DOWN           = 0x01,
    MODS_UP             = 0x02,
    MODS_SET,
    MODS_PUSH,
    MODS_POP,

    WAIT                = 0x74,
    INTERVAL,
    /* 0x74 - 0x7f */
    /* 0x80 - 0x84 */

    EXT_DOWN,
    EXT_UP,
    EXT_WAIT,
    EXT_INTERVAL,
    COMPRESSION_MODE,

    EXTENSION_MODE      = 0xff,
};


/* normal mode */
#define DOWN(key)       (key)
#define UP(key)         ((key) | 0x80)
#define TYPE(key)       (key), (key | 0x80)
#define MODS_DOWN(mods) MODS_DOWN, (mods)
#define MODS_UP(mods)   MODS_UP, (mods)
#define WAIT(ms)        WAIT, (ms)
#define INTERVAL(ms)    INTERVAL, (ms)

#define D(key)          DOWN(KC_##key)
#define U(key)          UP(KC_##key)
#define T(key)          TYPE(KC_##key)
#define MD(key)         MODS_DOWN(MOD_BIT(KC_##key))
#define MU(key)         MODS_UP(MOD_BIT(KC_##key))
#define W(ms)           WAIT(ms)
#define I(ms)           INTERVAL(ms)


/* extension mode */


#endif /* ACTION_MACRO_H */
