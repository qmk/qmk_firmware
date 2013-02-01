/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#ifndef ACTION_H
#define ACTION_H

#include "keyboard.h"
#include "keycode.h"


/* Execute action per keyevent */
void action_exec(keyevent_t event);


/* Struct to record event and tap count  */
typedef struct {
    keyevent_t  event;
    uint8_t     tap_count;
} keyrecord_t;

/* Action struct.
 *
 * In avr-gcc bit field seems to be assigned from LSB(bit0) to MSB(bit15). 
 * AVR looks like a little endian in avr-gcc.
 *
 * NOTE: not portable across compiler/endianness?
 * Byte order and bit order of 0x1234:
 * Big endian:     15 ...  8 7 ... 210
 *                |  0x12   |  0x34   |
 *                 0001 0010 0011 0100
 * Little endian:  012 ... 7  8 ... 15
 *                |  0x34   |  0x12   |
 *                 0010 1100 0100 1000
 */
typedef union {
    uint16_t code;
    struct action_kind {
        uint16_t param  :12;
        uint16_t id     :4;
    } kind;
    struct action_key {
        uint16_t code   :8;
        uint16_t mods   :4;
        uint16_t kind   :4;
    } key;
    struct action_layer {
        uint16_t code   :8;
        uint16_t val    :4;
        uint16_t kind   :4;
    } layer;
    struct action_usage {
        uint16_t code   :10;
        uint16_t page   :2;
        uint16_t kind   :4;
    } usage;
    struct action_command {
        uint16_t id     :8;
        uint16_t opt    :4;
        uint16_t kind   :4;
    } command;
    struct action_function {
        uint8_t  id     :8;
        uint8_t  opt    :4;
        uint8_t  kind   :4;
    } func;
} action_t;


/*
 * Utilities for actions.
 */
void register_code(uint8_t code);
void unregister_code(uint8_t code);
void add_mods(uint8_t mods);
void del_mods(uint8_t mods);
void set_mods(uint8_t mods);
void clear_keyboard(void);
void clear_keyboard_but_mods(void);
bool sending_anykey(void);
void layer_switch(uint8_t new_layer);
bool is_tap_key(key_t key);
bool waiting_buffer_has_anykey_pressed(void);




/*
 * Action codes
 * ============
 * 16bit code: action_kind(4bit) + action_parameter(12bit)
 *
Keyboard Keys
-------------
ACT_LMODS(0000):
0000|0000|000000|00    No action
0000|0000| keycode     Key
0000|mods|000000|00    Left mods
0000|mods| keycode     Key & Left mods

ACT_RMODS(0001):
0001|0000|000000|00    No action
0001|0000| keycode     Key(no used)
0001|mods|000000|00    Right mods
0001|mods| keycode     Key & Right mods

ACT_LMODS_TAP(0010):
0010|mods|000000|00    Left mods OneShot
0010|mods|000000|01    (reserved)
0010|mods|000000|10    (reserved)
0010|mods|000000|11    (reserved)
0010|mods| keycode     Left mods + tap Key

ACT_RMODS_TAP(0011):
0011|mods|000000|00    Right mods OneShot
0011|mods|000000|01    (reserved)
0011|mods|000000|10    (reserved)
0011|mods|000000|11    (reserved)
0011|mods| keycode     Right mods + tap Key
 

Other HID Usage
---------------
This action handles other usages than keyboard.
ACT_USAGE(0100):
0100|00| usage(10)     System control(0x80) - General Desktop page(0x01)
0100|01| usage(10)     Consumer control(0x01) - Consumer page(0x0C)
0100|10| usage(10)     (reserved)
0100|11| usage(10)     (reserved)


Mouse Keys
----------
TODO: can be combined with 'Other HID Usage'? to save action kind id.
ACT_MOUSEKEY(0110):
0101|XXXX| keycode     Mouse key


Layer Actions
-------------
TODO: reconsider layer methods.
1   momemtary + tap key                 up: L,     down: default
1   bitwise   + tap key                 up: xor B, down: xor B
3   momemtary go + tap key?             up: X,     down:
3   toggle(mementary back) + tap key?   up:        down: Y
3   no tap                              up: X,     down: Y

ACT_LAYER_PRESSED(1000):    Set layer on key pressed
ACT_LAYER_RELEASED(1001):   Set layer on key released
ACT_LAYER_BIT(1010):        On/Off layer bit
ACT_LAYER_EXT(1011):        Extentions

1000|LLLL|0000 0000   set layer L when pressed
1001|LLLL|0000 0000   set layer L when released
1010|BBBB|0000 0000   on/off bit B when pressed/released
1011|0000|0000 0000   set default layer when pressed
1011|0001|0000 0000   set default layer when released

1000|LLLL|1111 0000   set layer L when pressed + tap toggle
1001|LLLL|1111 0000   set layer L when released + tap toggle
1010|BBBB|1111 0000   on/off bit B when pressed/released + tap toggle
1011|0000|1111 0000   set default layer when pressed + tap toggle
1011|0001|1111 0000   set default layer when released + tap toggle

1000|LLLL|1111 1111   set L to default layer when pressed
1001|LLLL|1111 1111   set L to default layer when released
1010|BBBB|1111 1111   on/off bit B of default layer when pressed/released
1011|0000|1111 1111   set current to default layer when pressed
1011|0001|1111 1111   set current to default layer when released

1000|LLLL| keycode    set layer L when pressed + tap key
1001|LLLL| keyocde    set layer L when released + tap key
1010|BBBB| keyocde    on/off bit B when pressed/released + tap key
1011|0000| keyocde    set default layer when pressed + tap key
1011|0001| keyocde    set default layer when released + tap key
 

Extensions(11XX)
----------------
NOTE: NOT FIXED

ACT_MACRO(1100):
1100|opt | id(8)      Macro play?
1100|1111| id(8)      Macro record?

ACT_COMMAND(1110):
1110|opt | id(8)      Built-in Command exec

ACT_FUNCTION(1111):
1111| address(12)     Function?
1111|opt | id(8)      Function?

 */
enum action_kind_id {
    ACT_LMODS           = 0b0000,
    ACT_RMODS           = 0b0001,
    ACT_LMODS_TAP       = 0b0010,
    ACT_RMODS_TAP       = 0b0011,

    ACT_USAGE           = 0b0100,
    ACT_MOUSEKEY        = 0b0101,

    ACT_LAYER_PRESSED   = 0b1000,
    ACT_LAYER_RELEASED  = 0b1001,
    ACT_LAYER_BIT       = 0b1010,
    ACT_LAYER_EXT       = 0b1011,

    ACT_MACRO           = 0b1100,
    ACT_COMMAND         = 0b1110,
    ACT_FUNCTION        = 0b1111
};

enum params {
    P_ONESHOT           = 0x00,
};

enum options {
    O_TAP               = 0x8,
};


/* action utility */
#define ACTION_NO                       0
#define ACTION(kind, param)             ((kind)<<12 | (param))
#define MODS4(mods)                     (((mods)>>4 | (mods)) & 0x0F)

/* Key */
#define ACTION_KEY(key)                 ACTION(ACT_LMODS,    key)
/* Mods & key */
#define ACTION_LMODS(mods)              ACTION(ACT_LMODS,    (mods)<<8 | 0x00)
#define ACTION_LMODS_KEY(mods, key)     ACTION(ACT_LMODS,    (mods)<<8 | (key))
#define ACTION_RMODS(mods)              ACTION(ACT_RMODS,    (mods)<<8 | 0x00)
#define ACTION_RMODS_KEY(mods, key)     ACTION(ACT_RMODS,    (mods)<<8 | (key))
/* Mod & key */
#define ACTION_LMOD(mod)                ACTION(ACT_LMODS,    MODS4(MOD_BIT(mod))<<8 | 0x00)
#define ACTION_LMOD_KEY(mod, key)       ACTION(ACT_LMODS,    MODS4(MOD_BIT(mod))<<8 | (key))
#define ACTION_RMOD(mod)                ACTION(ACT_RMODS,    MODS4(MOD_BIT(mod))<<8 | 0x00)
#define ACTION_RMOD_KEY(mod, key)       ACTION(ACT_RMODS,    MODS4(MOD_BIT(mod))<<8 | (key))

/* Mods + Tap key */
#define ACTION_LMODS_TAP_KEY(mods, key) ACTION(ACT_LMODS_TAP, MODS4(mods)<<8 | (key))
#define ACTION_LMODS_ONESHOT(mods)      ACTION(ACT_LMODS_TAP, MODS4(mods)<<8 | P_ONESHOT)
#define ACTION_RMODS_TAP_KEY(mods, key) ACTION(ACT_RMODS_TAP, MODS4(mods)<<8 | (key))
#define ACTION_RMODS_ONESHOT(mods)      ACTION(ACT_RMODS_TAP, MODS4(mods)<<8 | P_ONESHOT)
/* Mod + Tap key */
#define ACTION_LMOD_TAP_KEY(mod, key)   ACTION(ACT_LMODS_TAP, MODS4(MOD_BIT(mod))<<8 | (key))
#define ACTION_LMOD_ONESHOT(mod)        ACTION(ACT_LMODS_TAP, MODS4(MOD_BIT(mod))<<8 | P_ONESHOT)
#define ACTION_RMOD_TAP_KEY(mod, key)   ACTION(ACT_RMODS_TAP, MODS4(MOD_BIT(mod))<<8 | (key))
#define ACTION_RMOD_ONESHOT(mod)        ACTION(ACT_RMODS_TAP, MODS4(MOD_BIT(mod))<<8 | P_ONESHOT)

// TODO: contemplate about layer action
/* Switch current layer */
#define ACTION_LAYER_SET(layer)                        ACTION(ACT_LAYER_PRESSED,  (layer)<<8 | 0x00)
#define ACTION_LAYER_SET_ON_PRESSED(layer)             ACTION(ACT_LAYER_PRESSED,  (layer)<<8 | 0x00)
#define ACTION_LAYER_SET_ON_RELEASED(layer)            ACTION(ACT_LAYER_RELEASED, (layer)<<8 | 0x00)
#define ACTION_LAYER_BIT(bits)                         ACTION(ACT_LAYER_BIT,      (bits)<<8 | 0x00)
#define ACTION_LAYER_SET_DEFAULT                       ACTION(ACT_LAYER_EXT,      0x0<<8     | 0x00)
#define ACTION_LAYER_RETURN_DEFAULT                    ACTION(ACT_LAYER_EXT,      0x1<<8     | 0x00)
#define ACTION_LAYER_SET_DEFAULT_ON_PRESSED            ACTION(ACT_LAYER_EXT,      0x0<<8     | 0x00)
#define ACTION_LAYER_SET_DEFAULT_ON_RELEASED           ACTION(ACT_LAYER_EXT,      0x1<<8     | 0x00)
/* Switch default layer */
#define ACTION_LAYER_DEFAULT_SET(layer)                ACTION(ACT_LAYER_PRESSED,  (layer)<<8 | 0xFF)
#define ACTION_LAYER_DEFAULT_SET_ON_PRESSED(layer)     ACTION(ACT_LAYER_PRESSED,  (layer)<<8 | 0xFF)
#define ACTION_LAYER_DEFAULT_SET_ON_RELEASED(layer)    ACTION(ACT_LAYER_RELEASED, (layer)<<8 | 0xFF)
#define ACTION_LAYER_DEFAULT_BIT(bits)                 ACTION(ACT_LAYER_BIT, (bits)<<8 | 0xFF)
#define ACTION_LAYER_DEFAULT_SET_CURRENT_ON_PRESSED    ACTION(ACT_LAYER_EXT, 0x0<<8    | 0xFF)
#define ACTION_LAYER_DEFAULT_SET_CURRENT_ON_RELEASED   ACTION(ACT_LAYER_EXT, 0x1<<8    | 0xFF)
/* Layer switch with tap key */
#define ACTION_LAYER_SET_TAP_KEY(layer, key)           ACTION(ACT_LAYER_PRESSED, (layer)<<8 | (key))
#define ACTION_LAYER_BIT_TAP_KEY(bits, key)            ACTION(ACT_LAYER_BIT,     (bits)<<8 | (key))
#define ACTION_LAYER_DEFAULT_SET_TAP_KEY(key)          ACTION(ACT_LAYER_EXT,     0x0<<8     | (key))
/* Layer switch with tap toggle */
#define ACTION_LAYER_SET_ON_PRESSED_TAP_TOGGLE(layer)  ACTION(ACT_LAYER_PRESSED,  (layer)<<8 | 0xF0)
#define ACTION_LAYER_SET_ON_RELEASED_TAP_TOGGLE(layer) ACTION(ACT_LAYER_RELEASED, (layer)<<8 | 0xF0)
#define ACTION_LAYER_BIT_TAP_TOGGLE(layer)             ACTION(ACT_LAYER_BIT,     (layer)<<8 | 0xF0)
#define ACTION_LAYER_DEFAULT_TAP_TOGGLE                ACTION(ACT_LAYER_EXT,     0x0<<8     | 0xF0)

/* HID Usage */
#define ACTION_USAGE_PAGE_SYSTEM        0
#define ACTION_USAGE_PAGE_CONSUMER      1
#define ACTION_USAGE_SYSTEM(id)         ACTION(ACT_USAGE,    ACTION_USAGE_PAGE_SYSTEM<<10 | (id))
#define ACTION_USAGE_CONSUMER(id)       ACTION(ACT_USAGE,    ACTION_USAGE_PAGE_CONSUMER<<10 | (id))

/* Mousekey */
#define ACTION_MOUSEKEY(key)            ACTION(ACT_MOUSEKEY, key)

/* Macro */
#define ACTION_MACRO(opt, id)           ACTION(ACT_FUNCTION, (opt)<<8 | (addr))

/* Command */
#define ACTION_COMMAND(opt, id)         ACTION(ACT_COMMAND,  (opt)<<8 | (addr))

/* Function */
#define ACTION_FUNCTION(id, opt)        ACTION(ACT_FUNCTION, (opt)<<8 | id)
#define ACTION_FUNCTION_TAP(id)         ACTION(ACT_FUNCTION, O_TAP<<8 | id)

#endif  /* ACTION_H */
