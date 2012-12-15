#ifndef ACTION_H
#define ACTION_H

#include "keyboard.h"


/* Key Action(16bit code)
 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
------------------------------------------------
ACT_LMODS(0000)
  0  0  0  0| 0  0  0  0| 0  0  0  0  0  0| 0  0    No action
  0  0  0  0| 0  0  0  0|     keycode(8)            Key
  0  0  0  0|  mods(4)  | 0  0  0  0  0  0| 0  0    Lmods Momentary
  0  0  0  0|  mods(4)  | 0  0  0  0  0  0| 0  1    Lmods OneShot
  0  0  0  0|  mods(4)  | 0  0  0  0  0  0| 1  0    (reserved)
  0  0  0  0|  mods(4)  | 0  0  0  0  0  0| 1  1    (reserved)
  0  0  0  0|  mods(4)  |     keycode(8)            Key+Lmods
???
  0  0  0  0|  mods(4)  | 1  1  1  1  0| tap(3)     Lmods+tap Switch(enable/disable)
  0  0  0  0|  mods(4)  | 1  1  1  1  1| tap(3)     Lmods+tap Toggle(on/off)
???

ACT_RMODS(0001)
  0  0  0  1| 0  0  0  0| 0  0  0  0  0  0  0  0    No action(not used)
  0  0  0  1| 0  0  0  0|     keycode(8)            Key(not used)
  0  0  0  1|  mods(4)  | 0  0  0  0  0  0| 0  0    Rmods Momentary
  0  0  0  1|  mods(4)  | 0  0  0  0  0  0| 0  1    Rmods OneShot
  0  0  0  1|  mods(4)  | 0  0  0  0  0  0| 1  0    (reserved)
  0  0  0  1|  mods(4)  | 0  0  0  0  0  0| 1  1    (reserved)
  0  0  0  1|  mods(4)  |     keycode(8)            Key+Rmod
???
  0  0  0  1|  mods(4)  | 1  1  1  1  0| tap(3)     Rmods+tap Switch(enable/disable)
  0  0  0  1|  mods(4)  | 1  1  1  1  1| tap(3)     Rmods+tap Toggle(on/off)
???

ACT_LMODS_TAP(0010)
  0  0  1  0| 0  0  0  0| X  X  X  X  X  X  X  X    (reserved)[00-FF]
  0  0  1  0|  mods(4)  | 0  0  0  0  0  0| X  X    (reserved)
  0  0  1  0|  mods(4)  |     keycode(8)            Lmods+tap Key
  0  0  1  0|  mods(4)  | 1  1  1  1| X  X  X  X    (reserved)[F0-FF]

ACT_RMODS_TAP(0011)
  0  0  1  1| 0  0  0  0| X  X  X  X  X  X  X  X    (reserved)[00-FF]
  0  0  1  1|  mods(4)  | 0  0  0  0  0  0| X  X    (reserved)
  0  0  1  1|  mods(4)  |     keycode(8)            Rmods+tap Key
  0  0  1  1|  mods(4)  | 1  1  1  1| X  X  X  X    (reserved)[F0-FF]
 
ACT_LAYER(0100)
  0  1  0  0|  layer(4) | 0  0  0  0  0  0| 0  0    Momentary
  0  1  0  0|  layer(4) | 0  0  0  0  0  0| 0  1    Oneshot
  0  1  0  0|  layer(4) | 0  0  0  0  0  0| 1  0    (reserved)
  0  1  0  0|  layer(4) | 0  0  0  0  0  0| 1  1    (reserved)
  0  1  0  0|  layer(4) |     keycode(8)            Fn momentary + tap Key
  0  1  0  0|  layer(4) | 1  1  1  1  0| tap(3)     Fn+tap Switch(enable/disable)
  0  1  0  0|  layer(4) | 1  1  1  1  1| tap(3)     Fn+tap Toggle(on/off)

ACT_USAGE(0101)
  0  1  0  1| 0  0|         usage(10)               System usage
  0  1  0  1| 0  1|         usage(10)               Consumer usage
  0  1  0  1| 1  0|         usage(10)               (reserved)
  0  1  0  1| 1  1|         usage(10)               (reserved)

ACT_MOUSEKEY(0110)
  0  1  1  0| X  X  X  X|        keycode(8)         Mouse key
??? TODO: refactor
  0  1  1  0| 0  0  X  X|  accel(5)    |cursor(3)   Mouse key
  0  1  1  0| 0  1  X  X|  accel(5)    |wheel(3)    Mouse key
  0  1  1  0| 1  0  X  X|        button(8)          Mouse key
  0  1  1  0| 1  1  X  X|        button(8)          Mouse key
???

  0  1  1  1|                                       (reserved)
  1  0  0  0|                                       (reserved)
  1  0  0  1|                                       (reserved)
  1  0  1  0|                                       (reserved)
  1  0  1  1|                                       (reserved)
  1  1  0  0|                                       (reserved)

ACT_MACRO(1100)
  1  1  0  0| option(4) |     macro-table id(8)     Macro play(Flash)
  1  1  0  0| option(4) |     macro-table id(8)     Macro play(EEPROM)
  1  1  0  0| 1  1  1  1|     macro-table id(8)     Macro record

ACT_COMMAND(1110)
  1  1  1  0| option(4) |     comamnd id(8)         Built-in Command exec

ACT_FUNCTION(1111)
  1  1  1  1|   function address(4K range)          Function
                                                    Macro record(dynamicly)
                                                    Macro play(dynamicly)
*/

enum action_id {
    ACT_LMODS = 0,
    ACT_RMODS,
    ACT_LMOD_TAP,
    ACT_RMOD_TAP,
    ACT_LAYER,
    ACT_USAGE,
    ACT_MOUSEKEY,
    ACT_MACRO = 14,
    ACT_COMMAND = 15,
    ACT_FUNCTION = 16
};

// TODO: not portable across compiler/endianness?
/*
In avr-gcc bit fields seems to be assigned from LSB(bit0) to MSB(bit15). 
AVR seems like little endian in avr-gcc.

Byte order and bit order of 0x1234:
Big endian:     15 ...  8 7 ... 210
               |  0x12   |  0x34   |
                0001 0010 0011 0100
Little endian:  012 ... 7  8 ... 15
               |  0x34   |  0x12   |
                0010 1100 0100 1000
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
    struct action_layer_key {
        uint16_t code   :8;
        uint16_t layer  :4;
        uint16_t kind   :4;
    } layer_key;
    struct action_layer_tap {
        uint16_t count  :3;
        uint16_t rest   :5;
        uint16_t layer  :4;
        uint16_t kind   :4;
    } layer_tap;
    struct action_usage {
        uint16_t code   :10;
        uint16_t page   :2;
        uint16_t kind   :4;
    } usage;
    struct action_command {
        uint16_t id     :8;
        uint16_t option :4;
        uint16_t kind   :4;
    } command;
} action_t;


enum stroke_cmd {
    STROKE_DOWN,
    STROKE_UP,
    STROKE_ALLUP, /* release all keys in reverse order */
};

void action_exec(action_t act, keyevent_t event);
/*
void key_action(uint8_t code, keyevent_t event);
void mod_action(uint8_t code, keyevent_t event);
void fn_action(uint8_t code, keyevent_t event);
*/


/* action_t utility */
#define ACTION(kind, param)             { .code = ((kind)<<12 | (param)) }
#define NO_ACTION                       ACTION(0, 0)
#define LAYER_PARAM(layer, key)         ((layer)<<8|(key))

/* Key & Mods */
#define ACTION_KEY(key)                 ACTION(ACT_LMODS,    key)
#define ACTION_LMODS(mods)              ACTION(ACT_LMODS,    (mods)<<8 | 0x00)
#define ACTION_LMODS_KEY(mods, key)     ACTION(ACT_LMODS,    (mods)<<8 | (key))
#define ACTION_LMODS_ONESHOT(mods)      ACTION(ACT_LMODS,    (mods)<<8 | 0x01)
#define ACTION_LMODS_SWITCH(mods, tap)  ACTION(ACT_LMODS,    (mods)<<8 | 0xF0 | (tap))
#define ACTION_LMODS_TOGGLE(mods, tap)  ACTION(ACT_LMODS,    (mods)<<8 | 0xF1 | (tap))
#define ACTION_RMODS(mods)              ACTION(ACT_RMODS,    (mods)<<8 | 0x00)
#define ACTION_RMODS_KEY(mods, key)     ACTION(ACT_RMODS,    (mods)<<8 | (key))
#define ACTION_RMODS_ONESHOT(mods)      ACTION(ACT_RMODS,    (mods)<<8 | 0x01)
#define ACTION_RMODS_SWITCH(mods, tap)  ACTION(ACT_RMODS,    (mods)<<8 | 0xF0 | (tap))
#define ACTION_RMODS_TOGGLE(mods, tap)  ACTION(ACT_RMODS,    (mods)<<8 | 0xF1 | (tap))
/* Mods + Tap key */
#define ACTION_LMODS_TAP(mods, key)     ACTION(ACT_LMODS_TAP,(mods)<<8 | (key))
#define ACTION_RMODS_TAP(mods, key)     ACTION(ACT_RMODS_TAP,(mods)<<8 | (key))
/* Layer Switch */
#define ACTION_LAYER(layer)             ACTION(ACT_LAYER,    (layer)<<8 | 0x00)
#define ACTION_LAYER_ONESHOT(layer)     ACTION(ACT_LAYER,    (layer)<<8 | 0x01)
#define ACTION_LAYER_KEY(layer, key)    ACTION(ACT_LAYER,    (layer)<<8 | (key))
#define ACTION_LAYER_SWITCH(layer, tap) ACTION(ACT_LAYER,    (layer)<<8 | 0xF0 | (tap))
#define ACTION_LAYER_TOGGLE(layer, tap) ACTION(ACT_LAYER,    (layer)<<8 | 0xF1 | (tap))
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
#define ACTION_FUNCTION(addr)           ACTION(ACT_FUNCTION, addr)


/* helpers for readability */
#define LAYER(layer)    (layer)
#define TAP(tap)        (tap)
#define DOUBLE_TAP      2
#define TRIPLE_TAP      3
#define QUADRUPLE_TAP   4
#define QUINTUPLE_TAP   5
#define DOWN(key)       (key)
#define UP(key)         STROKE_UP, (key)

#endif  /* ACTION_H */
