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

ACT_RMODS(0001)
  0  0  0  1| 0  0  0  0| 0  0  0  0  0  0  0  0    No action(not used)
  0  0  0  1| 0  0  0  0|     keycode(8)            Key(not used)
  0  0  0  1|  mods(4)  | 0  0  0  0  0  0| 0  0    Rmods Momentary
  0  0  0  1|  mods(4)  | 0  0  0  0  0  0| 0  1    Rmods OneShot
  0  0  0  1|  mods(4)  | 0  0  0  0  0  0| 1  0    (reserved)
  0  0  0  1|  mods(4)  | 0  0  0  0  0  0| 1  1    (reserved)
  0  0  0  1|  mods(4)  |     keycode(8)            Key+Rmod

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
 
ACT_USAGE - other HID usage than keyboard
  0  1  0  0| 0  0|         usage(10)               System usage
  0  1  0  0| 0  1|         usage(10)               Consumer usage
  0  1  0  0| 1  0|         usage(10)               (reserved)
  0  1  0  0| 1  1|         usage(10)               (reserved)

ACT_MOUSEKEY(0110)
  0  1  0  1| X  X  X  X|        keycode(8)         Mouse key
??? TODO: refactor
  0  1  0  1| 0  0  X  X|  accel(5)    |cursor(3)   Mouse key
  0  1  0  1| 0  1  X  X|  accel(5)    |wheel(3)    Mouse key
  0  1  0  1| 1  0  X  X|        button(8)          Mouse key
  0  1  0  1| 1  1  X  X|        button(8)          Mouse key
???

Layer Action
------------
1000|LLLL|0000 0000   set layer L when pressed
1001|LLLL|0000 0000   set layer L when released
1010|BBBB|0000 0000   on/off bit B when pressed/released
1011|0000|0000 0000   set default layer when pressed
1011|0001|0000 0000   set default layer when released

1000|LLLL|1111 0000   set layer L when pressed + tap toggle
1001|LLLL|1111 0000   set layer L when released[tap is ignored/not used]
1010|BBBB|1111 0000   on/off bit B when pressed/released + tap toggle
1011|0000|1111 0000   set default layer when pressed + tap toggle
1011|0001|1111 0000   set default layer when released[tap is ignored/not used]

1000|LLLL|1111 1111   set L to default layer when pressed
1001|LLLL|1111 1111   set L to default layer when released
1010|BBBB|1111 1111   on/off bit B of default layer when pressed/released
1011|0000|1111 1111   set current to default layer when pressed
1011|0001|1111 1111   set current to default layer when released

1000|LLLL| keycode    set layer L when pressed + tap key
1001|LLLL| keyocde    set layer L when released[tap is ignored/not used]
1010|BBBB| keyocde    on/off bit B when pressed/released + tap key
1011|0000| keyocde    set default layer when pressed + tap key
1011|0001| keyocde    set default layer when released[tap is ignored/not used]
 

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
TODO: modifier + [tap key /w mod]
    : layerkey + [tap key /w mod]
    for example: LShift + '('[Shift+9] and RShift + ')'[Shift+0]
    http://deskthority.net/workshop-f7/tmk-keyboard-firmware-collection-t4478.html#p90052
*/

enum action_id {
    ACT_LMODS    = 0b0000,
    ACT_RMODS    = 0b0001,
    ACT_LMOD_TAP = 0b0010,
    ACT_RMOD_TAP = 0b0011,
    ACT_USAGE    = 0b0100,
    ACT_MOUSEKEY = 0b0101,
    ACT_LAYER_PRESSED  = 0b1000,
    ACT_LAYER_RELEASED = 0b1001,
    ACT_LAYER_BIT      = 0b1010,
    ACT_LAYER_EXT      = 0b1011,
    ACT_MACRO    = 0b1100,
    ACT_COMMAND  = 0b1110,
    ACT_FUNCTION = 0b1111
};

// TODO: not portable across compiler/endianness?
/*
In avr-gcc bit fields seems to be assigned from LSB(bit0) to MSB(bit15). 
AVR looks like a little endian in avr-gcc.

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
    struct action_layer {
        uint16_t code   :8;
        uint16_t opt    :4;
        uint16_t kind   :4;
    } layer;
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

typedef struct {
    keyevent_t  event;
    action_t    action;
    uint8_t     mods;
} keyrecord_t;


void action_exec(keyevent_t event);
/*
void key_action(uint8_t code, keyevent_t event);
void mod_action(uint8_t code, keyevent_t event);
void fn_action(uint8_t code, keyevent_t event);
*/


/* action_t utility */
/*
#define ACTION_NO                       { .code = 0 }
#define ACTION(kind, param)             { .code = ((kind)<<12 | (param)) }
*/
#define ACTION_NO                       0
#define ACTION(kind, param)             ((kind)<<12 | (param))

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
#define ACTION_LAYER_SET_ON_PRESSED(layer)   ACTION(ACT_LAYER_PRESSED,  (layer)<<8 | 0x00)
#define ACTION_LAYER_SET_ON_RELEASED(layer)  ACTION(ACT_LAYER_RELEASED, (layer)<<8 | 0x00)
#define ACTION_LAYER_BIT(bits)               ACTION(ACT_LAYER_BIT,      (layer)<<8 | 0x00)
#define ACTION_LAYER_TO_DEFAULT_ON_PRESSED   ACTION(ACT_LAYER_EXT,      0x0<<8     | 0x00)
#define ACTION_LAYER_TO_DEFAULT_ON_RELEASED  ACTION(ACT_LAYER_EXT,      0x1<<8     | 0x00)

#define ACTION_LAYER_TAP_TOGGLE(layer)      ACTION(ACT_LAYER_PRESSED, (layer)<<8 | 0xF0)
#define ACTION_LAYER_BIT_TAP_TOGGLE(layer)  ACTION(ACT_LAYER_BIT,     (layer)<<8 | 0xF0)
#define ACTION_LAYER_DEFAULT_TAP_TOGGLE     ACTION(ACT_LAYER_EXT,     0x0<<8     | 0xF0)

#define ACTION_LAYER_DEFAULT_SET_ON_PRESSED(layer)   ACTION(ACT_LAYER_PRESSED, (layer)<<8 | 0xFF)
#define ACTION_LAYER_DEFAULT_SET_ON_RELEASED(layer)  ACTION(ACT_LAYER_RELEASED, (layer)<<8 | 0xFF)
#define ACTION_LAYER_DEFAULT_BIT(bits)               ACTION(ACT_LAYER_BIT, (bits)<<8 | 0xFF)
#define ACTION_LAYER_DEFAULT_SET_CURRENT_ON_PRESSED  ACTION(ACT_LAYER_EXT, 0x0<<8    | 0xFF)
#define ACTION_LAYER_DEFAULT_SET_CURRENT_ON_RELEASED ACTION(ACT_LAYER_EXT, 0x1<<8    | 0xFF)

#define ACTION_LAYER_SET_TAP_KEY(layer, key)  ACTION(ACT_LAYER_PRESSED, (layer)<<8 | (key))
#define ACTION_LAYER_BIT_TAP_KEY(bits, key)   ACTION(ACT_LAYER_BIT,     (layer)<<8 | (key))
#define ACTION_LAYER_DEFAULT_SET_TAP_KEY(key) ACTION(ACT_LAYER_EXT,     0x0<<8     | (key))

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
