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
        uint8_t  id     :4;
    } kind;
    struct action_key {
        uint8_t  code   :8;
        uint8_t  mods   :4;
        uint8_t  kind   :4;
    } key;
    struct action_layer {
        uint8_t  code   :8;
        uint8_t  val    :4;
        uint8_t  kind   :4;
    } layer;
    struct action_usage {
        uint16_t code   :10;
        uint8_t  page   :2;
        uint8_t  kind   :4;
    } usage;
    struct action_command {
        uint8_t  id     :8;
        uint8_t  opt    :4;
        uint8_t  kind   :4;
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
ACT_LAYER(1000):            Set layer
ACT_LAYER_BIT(1001):        Bit-op layer

1000|LLLL|0000 0000   set L to layer on press and set default on release(momentary)
1000|LLLL|0000 0001   set L to layer on press
1000|LLLL|0000 0010   set L to layer on release
1000|----|0000 0011   set default to layer on both(return to default layer)
1000|LLLL|xxxx xxxx   set L to layer while hold and send key on tap
1000|LLLL|1111 0000   set L to layer while hold and toggle on several taps
1000|LLLL|1111 1111   set L to default and layer(on press)

1001|BBBB|0000 0000   (not used)
1001|BBBB|0000 0001   bit-xor layer with B on press
1001|BBBB|0000 0010   bit-xor layer with B on release
1001|BBBB|0000 0011   bit-xor layer with B on both(momentary)
1001|BBBB|xxxx xxxx   bit-xor layer with B while hold and send key on tap
1001|BBBB|1111 0000   bit-xor layer with B while hold and toggle on several taps
1001|BBBB|1111 1111   bit-xor default with B and set layer(on press)



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

    ACT_LAYER           = 0b1000,
    ACT_LAYER_BIT       = 0b1001,

    ACT_MACRO           = 0b1100,
    ACT_COMMAND         = 0b1110,
    ACT_FUNCTION        = 0b1111
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
enum mods_codes {
    MODS_ONESHOT           = 0x00,
};
#define ACTION_LMODS_TAP_KEY(mods, key) ACTION(ACT_LMODS_TAP, MODS4(mods)<<8 | (key))
#define ACTION_LMODS_ONESHOT(mods)      ACTION(ACT_LMODS_TAP, MODS4(mods)<<8 | MODS_ONESHOT)
#define ACTION_RMODS_TAP_KEY(mods, key) ACTION(ACT_RMODS_TAP, MODS4(mods)<<8 | (key))
#define ACTION_RMODS_ONESHOT(mods)      ACTION(ACT_RMODS_TAP, MODS4(mods)<<8 | MODS_ONESHOT)
/* Mod + Tap key */
#define ACTION_LMOD_TAP_KEY(mod, key)   ACTION(ACT_LMODS_TAP, MODS4(MOD_BIT(mod))<<8 | (key))
#define ACTION_LMOD_ONESHOT(mod)        ACTION(ACT_LMODS_TAP, MODS4(MOD_BIT(mod))<<8 | MODS_ONESHOT)
#define ACTION_RMOD_TAP_KEY(mod, key)   ACTION(ACT_RMODS_TAP, MODS4(MOD_BIT(mod))<<8 | (key))
#define ACTION_RMOD_ONESHOT(mod)        ACTION(ACT_RMODS_TAP, MODS4(MOD_BIT(mod))<<8 | MODS_ONESHOT)


/* 
 * Switch layer
 */
enum layer_codes {
    LAYER_MOMENTARY = 0,
    LAYER_ON_PRESS = 1,
    LAYER_ON_RELEASE = 2,
    LAYER_DEFAULT =3,
    LAYER_TAP_TOGGLE = 0xF0,
    LAYER_CHANGE_DEFAULT = 0xFF
};
enum layer_vals_default {
    DEFAULT_ON_PRESS = 1,
    DEFAULT_ON_RELEASE = 2,
    DEFAULT_ON_BOTH = 3,
};

/* 
 * return to default layer
 */
#define ACTION_LAYER_DEFAULT                    ACTION_LAYER_DEFAULT_R
/* set default layer on press */
#define ACTION_LAYER_DEFAULT_P                  ACTION(ACT_LAYER, DEFAULT_ON_PRESS<<8 | LAYER_DEFAULT)
/* set default layer on release */
#define ACTION_LAYER_DEFAULT_R                  ACTION(ACT_LAYER, DEFAULT_ON_RELEASE<<8 | LAYER_DEFAULT)
/* change default layer and set layer */

/*
 * Set layer
 */
/* set layer on press and set default on release */
#define ACTION_LAYER_SET(layer)                 ACTION_LAYER_SET_MOMENTARY(layer)
#define ACTION_LAYER_SET_MOMENTARY(layer)       ACTION(ACT_LAYER, (layer)<<8 | LAYER_MOMENTARY)
/* set layer on press and none on release */
#define ACTION_LAYER_SET_TOGGLE(layer)          ACTION_LAYER_SET_R(layer)
/* set layer while hold and send key on tap */
#define ACTION_LAYER_SET_TAP_KEY(layer, key)    ACTION(ACT_LAYER, (layer)<<8 | (key))
/* set layer on press */
#define ACTION_LAYER_SET_P(layer)               ACTION(ACT_LAYER, (layer)<<8 | LAYER_ON_PRESS)
/* set layer on release */
#define ACTION_LAYER_SET_R(layer)               ACTION(ACT_LAYER, (layer)<<8 | LAYER_ON_RELEASE)
/* set layer on hold and toggle on several taps */
#define ACTION_LAYER_SET_TAP_TOGGLE(layer)      ACTION(ACT_LAYER, (layer)<<8 | LAYER_TAP_TOGGLE)
/* set default layer on both press and release */
#define ACTION_LAYER_SET_DEFAULT(layer)         ACTION(ACT_LAYER, (layer)<<8 | LAYER_CHANGE_DEFAULT)

/* 
 * Bit-op layer
 */
/* bit-xor on both press and release */
#define ACTION_LAYER_BIT(bits)                  ACTION_LAYER_BIT_MOMENTARY(bits)
#define ACTION_LAYER_BIT_MOMENTARY(bits)        ACTION(ACT_LAYER_BIT, (bits)<<8 | LAYER_MOMENTARY)
/* bit-xor on press */
#define ACTION_LAYER_BIT_TOGGLE(bits)           ACTION_LAYER_BIT_R(bits)
/* bit-xor while hold and send key on tap */
#define ACTION_LAYER_BIT_TAP_KEY(bits, key)     ACTION(ACT_LAYER_BIT, (bits)<<8 | (key))
/* bit-xor on press */
#define ACTION_LAYER_BIT_P(bits)                ACTION(ACT_LAYER_BIT, (bits)<<8 | LAYER_ON_PRESS)
/* bit-xor on release */
#define ACTION_LAYER_BIT_R(bits)                ACTION(ACT_LAYER_BIT, (bits)<<8 | LAYER_ON_RELEASE)
/* bit-xor while hold and toggle on several taps */
#define ACTION_LAYER_BIT_TAP_TOGGLE(bits)       ACTION(ACT_LAYER_BIT, (bits)<<8 | LAYER_TAP_TOGGLE)
/* bit-xor default layer and set layer */
#define ACTION_LAYER_BIT_DEFAULT(bits)          ACTION(ACT_LAYER, (bits)<<8 | LAYER_CHANGE_DEFAULT)


/* HID Usage */
enum usage_pages {
    PAGE_SYSTEM,
    PAGE_CONSUMER
};
#define ACTION_USAGE_SYSTEM(id)         ACTION(ACT_USAGE, PAGE_SYSTEM<<10 | (id))
#define ACTION_USAGE_CONSUMER(id)       ACTION(ACT_USAGE, PAGE_CONSUMER<<10 | (id))

/* Mousekey */
#define ACTION_MOUSEKEY(key)            ACTION(ACT_MOUSEKEY, key)

/* Macro */
#define ACTION_MACRO(opt, id)           ACTION(ACT_FUNCTION, (opt)<<8 | (addr))

/* Command */
#define ACTION_COMMAND(opt, id)         ACTION(ACT_COMMAND,  (opt)<<8 | (addr))

/* Function */
enum function_opts {
    FUNC_TAP        = 0x8,      /* indciates function is tappable */
};
#define ACTION_FUNCTION(id, opt)        ACTION(ACT_FUNCTION, (opt)<<8 | id)
#define ACTION_FUNCTION_TAP(id)         ACTION(ACT_FUNCTION, FUNC_TAP<<8 | id)

#endif  /* ACTION_H */
