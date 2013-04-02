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

#include <stdint.h>
#include <stdbool.h>
#include "keyboard.h"
#include "keycode.h"
#include "action_macro.h"


typedef struct {
    keyevent_t  event;
#ifndef NO_ACTION_TAPPING
    /* tapping count and state */
    struct {
        bool    interrupted :1;
        bool    reserved2   :1;
        bool    reserved1   :1;
        bool    reserved0   :1;
        uint8_t count       :4;
    } tap;
#endif
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
    struct action_layer_bitop {
        uint8_t  bits   :4;
        uint8_t  xbit   :1;
        uint8_t  part   :3;
        uint8_t  on     :2;
        uint8_t  op     :2;
        uint8_t  kind   :4;
    } layer_bitop;
    struct action_layer_tap {
        uint8_t  code   :8;
        uint8_t  val    :5;
        uint8_t  kind   :3;
    } layer_tap;
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



/* Execute action per keyevent */
void action_exec(keyevent_t event);

/* action for key */
action_t action_for_key(uint8_t layer, key_t key);

/* macro */
const prog_macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt);

/* user defined special function */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt);

/* Utilities for actions.  */
void process_action(keyrecord_t *record);
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

/* debug */
void debug_event(keyevent_t event);
void debug_record(keyrecord_t record);
void debug_action(action_t action);



/*
 * Action codes
 * ============
 * 16bit code: action_kind(4bit) + action_parameter(12bit)
 *
 * Keyboard Keys(00XX)
 * -------------------
 * ACT_LMODS(0000):
 * 0000|0000|000000|00    No action
 * 0000|0000|000000|01    Transparent
 * 0000|0000| keycode     Key
 * 0000|mods|000000|00    Left mods
 * 0000|mods| keycode     Key & Left mods
 *
 * ACT_RMODS(0001):
 * 0001|0000|000000|00    No action(not used)
 * 0001|0000|000000|01    Transparent(not used)
 * 0001|0000| keycode     Key(no used)
 * 0001|mods|000000|00    Right mods
 * 0001|mods| keycode     Key & Right mods
 *
 * ACT_LMODS_TAP(0010):
 * 0010|mods|000000|00    Left mods OneShot
 * 0010|mods|000000|01    (reserved)
 * 0010|mods|000000|10    (reserved)
 * 0010|mods|000000|11    (reserved)
 * 0010|mods| keycode     Left mods + tap Key
 *
 * ACT_RMODS_TAP(0011):
 * 0011|mods|000000|00    Right mods OneShot
 * 0011|mods|000000|01    (reserved)
 * 0011|mods|000000|10    (reserved)
 * 0011|mods|000000|11    (reserved)
 * 0011|mods| keycode     Right mods + tap Key
 *
 *
 * Other keys(01XX)
 * --------------------
 * This action handles other usages than keyboard.
 * ACT_USAGE(0100):
 * 0100|00| usage(10)     System control(0x80) - General Desktop page(0x01)
 * 0100|01| usage(10)     Consumer control(0x01) - Consumer page(0x0C)
 * 0100|10| usage(10)     (reserved)
 * 0100|11| usage(10)     (reserved)
 *
 * ACT_MOUSEKEY(0110):
 * 0101|XXXX| keycode     Mouse key
 *
 *
 * Layer Actions(10XX)
 * -------------------
 * ACT_LAYER:
 * 1000|oo00|pppx BBBB   Default Layer Bitwise operation
 *   oo:    operation(00:AND, 01:OR, 10:XOR, 11:SET)
 *   ppp:   4-bit chunk part(0-7)
 *   xBBBB: bits and extra bit
 * 1000|ooee|pppx BBBB   Layer Bitwise Operation
 *   oo:    operation(00:AND, 01:OR, 10:XOR, 11:SET)
 *   ppp:   4-bit chunk part(0-7)
 *   xBBBB: bits and extra bit
 *   ee:    on event(00:default layer, 01:press, 10:release, 11:both)
 *
 * ACT_LAYER_TAP:
 * 101x|LLLL| keycode    Invert with tap key
 * 101x|LLLL|1110 xxxx   Reserved(0xE0-EF)
 * 101x|LLLL|1111 0000   Invert with tap toggle(0xF0)
 * 101x|LLLL|1111 0001   On  Off
 * 101x|LLLL|1111 0010   Off On
 * 101x|LLLL|1111 0011   Set Clear
 * 101x|LLLL|1111 xxxx   Reserved(0xF4-FF)
 *   xLLLL: layer(0-31)
 *
 *
 *
 *
 *
 * Extensions(11XX)
 * ----------------
 * ACT_MACRO(1100):
 * 1100|opt | id(8)      Macro play?
 * 1100|1111| id(8)      Macro record?
 *
 * ACT_COMMAND(1110):
 * 1110|opt | id(8)      Built-in Command exec
 *
 * ACT_FUNCTION(1111):
 * 1111| address(12)     Function?
 * 1111|opt | id(8)      Function?
 *
 */
enum action_kind_id {
    ACT_MODS            = 0b0000,
    ACT_LMODS           = 0b0000,
    ACT_RMODS           = 0b0001,
    ACT_MODS_TAP        = 0b0010,
    ACT_LMODS_TAP       = 0b0010,
    ACT_RMODS_TAP       = 0b0011,

    ACT_USAGE           = 0b0100,
    ACT_MOUSEKEY        = 0b0101,

    ACT_LAYER           = 0b1000,
    ACT_LAYER_TAP       = 0b1010,
    ACT_LAYER_TAP1      = 0b1011,

    ACT_MACRO           = 0b1100,
    ACT_COMMAND         = 0b1110,
    ACT_FUNCTION        = 0b1111
};


/* action utility */
#define ACTION_NO                       0
#define ACTION_TRANSPARENT              1
#define ACTION(kind, param)             ((kind)<<12 | (param))
#define MODS4(mods)                     (((mods)>>4 | (mods)) & 0x0F)

/*
 * Key
 */
#define ACTION_KEY(key)                 ACTION(ACT_LMODS,    key)
/* Mods & key */
#define ACTION_LMODS(mods)              ACTION(ACT_LMODS,    MODS4(mods)<<8 | 0x00)
#define ACTION_LMODS_KEY(mods, key)     ACTION(ACT_LMODS,    MODS4(mods)<<8 | (key))
#define ACTION_RMODS(mods)              ACTION(ACT_RMODS,    MODS4(mods)<<8 | 0x00)
#define ACTION_RMODS_KEY(mods, key)     ACTION(ACT_RMODS,    MODS4(mods)<<8 | (key))
#define ACTION_LMOD(mod)                ACTION(ACT_LMODS,    MODS4(MOD_BIT(mod))<<8 | 0x00)
#define ACTION_LMOD_KEY(mod, key)       ACTION(ACT_LMODS,    MODS4(MOD_BIT(mod))<<8 | (key))
#define ACTION_RMOD(mod)                ACTION(ACT_RMODS,    MODS4(MOD_BIT(mod))<<8 | 0x00)
#define ACTION_RMOD_KEY(mod, key)       ACTION(ACT_RMODS,    MODS4(MOD_BIT(mod))<<8 | (key))
/* Tap key */
enum mods_codes {
    MODS_ONESHOT           = 0x00,
};
#define ACTION_LMODS_TAP_KEY(mods, key) ACTION(ACT_LMODS_TAP, MODS4(mods)<<8 | (key))
#define ACTION_LMODS_ONESHOT(mods)      ACTION(ACT_LMODS_TAP, MODS4(mods)<<8 | MODS_ONESHOT)
#define ACTION_RMODS_TAP_KEY(mods, key) ACTION(ACT_RMODS_TAP, MODS4(mods)<<8 | (key))
#define ACTION_RMODS_ONESHOT(mods)      ACTION(ACT_RMODS_TAP, MODS4(mods)<<8 | MODS_ONESHOT)
#define ACTION_LMOD_TAP_KEY(mod, key)   ACTION(ACT_LMODS_TAP, MODS4(MOD_BIT(mod))<<8 | (key))
#define ACTION_LMOD_ONESHOT(mod)        ACTION(ACT_LMODS_TAP, MODS4(MOD_BIT(mod))<<8 | MODS_ONESHOT)
#define ACTION_RMOD_TAP_KEY(mod, key)   ACTION(ACT_RMODS_TAP, MODS4(MOD_BIT(mod))<<8 | (key))
#define ACTION_RMOD_ONESHOT(mod)        ACTION(ACT_RMODS_TAP, MODS4(MOD_BIT(mod))<<8 | MODS_ONESHOT)

/* HID Usage */
enum usage_pages {
    PAGE_SYSTEM,
    PAGE_CONSUMER
};
#define ACTION_USAGE_SYSTEM(id)         ACTION(ACT_USAGE, PAGE_SYSTEM<<10 | (id))
#define ACTION_USAGE_CONSUMER(id)       ACTION(ACT_USAGE, PAGE_CONSUMER<<10 | (id))

/* Mousekey */
#define ACTION_MOUSEKEY(key)            ACTION(ACT_MOUSEKEY, key)



/* Layer Actions */
enum layer_param_on {
    ON_PRESS    = 1,
    ON_RELEASE  = 2,
    ON_BOTH     = 3,
};

enum layer_param_bit_op {
    OP_BIT_AND = 0,
    OP_BIT_OR,
    OP_BIT_XOR,
    OP_BIT_SET,
};

enum layer_pram_tap_op {
    OP_TAP_TOGGLE = 0xF0,
    OP_ON_OFF,
    OP_OFF_ON,
    OP_SET_CLEAR,
};

/* Layer Bitwise Operation   1000|ooee|pppx BBBB */
#define ACTION_LAYER_BITOP(op, part, bits, on)      (ACT_LAYER<<12 | (op)<<10 | (on)<<8 | (part)<<5 | ((bits)&0x1f))
/* Layer with Tapping        101x|LLLL| keycode  */
#define ACTION_LAYER_TAP(layer, key)                (ACT_LAYER_TAP<<12 | (layer)<<8 | (key))

/* Default Layer Operation */
#define ACTION_DEFAULT_LAYER_SET(layer)             ACTION_DEFAULT_LAYER_BIT_SET((layer)/4, 1<<((layer)%4))
/* Layer Operation */
#define ACTION_LAYER_CLEAR(on)                      ACTION_LAYER_AND(0x1f, (on))
#define ACTION_LAYER_MOMENTARY(layer)               ACTION_LAYER_ON_OFF(layer)
#define ACTION_LAYER_TOGGLE(layer)                  ACTION_LAYER_INVERT(layer, ON_RELEASE)
#define ACTION_LAYER_INVERT(layer, on)              ACTION_LAYER_BIT_XOR((layer)/4,   1<<((layer)%4),  (on))
#define ACTION_LAYER_ON(layer, on)                  ACTION_LAYER_BIT_OR( (layer)/4,   1<<((layer)%4),  (on))
#define ACTION_LAYER_OFF(layer, on)                 ACTION_LAYER_BIT_AND((layer)/4, ~(1<<((layer)%4)), (on))
#define ACTION_LAYER_SET(layer, on)                 ACTION_LAYER_BIT_SET((layer)/4,   1<<((layer)%4),  (on))
#define ACTION_LAYER_ON_OFF(layer)                  ACTION_LAYER_TAP((layer), OP_ON_OFF)
#define ACTION_LAYER_OFF_ON(layer)                  ACTION_LAYER_TAP((layer), OP_OFF_ON)
#define ACTION_LAYER_SET_CLEAR(layer)               ACTION_LAYER_TAP((layer), OP_SET_CLEAR)
/* Bitwise Operation */
#define ACTION_LAYER_BIT_AND(part, bits, on)        ACTION_LAYER_BITOP(OP_BIT_AND, (part), (bits), (on))
#define ACTION_LAYER_BIT_OR( part, bits, on)        ACTION_LAYER_BITOP(OP_BIT_OR,  (part), (bits), (on))
#define ACTION_LAYER_BIT_XOR(part, bits, on)        ACTION_LAYER_BITOP(OP_BIT_XOR, (part), (bits), (on))
#define ACTION_LAYER_BIT_SET(part, bits, on)        ACTION_LAYER_BITOP(OP_BIT_SET, (part), (bits), (on))
#define ACTION_DEFAULT_LAYER_BIT_AND(part, bits)    ACTION_LAYER_BITOP(OP_BIT_AND, (part), (bits), 0)
#define ACTION_DEFAULT_LAYER_BIT_OR( part, bits)    ACTION_LAYER_BITOP(OP_BIT_OR,  (part), (bits), 0)
#define ACTION_DEFAULT_LAYER_BIT_XOR(part, bits)    ACTION_LAYER_BITOP(OP_BIT_XOR, (part), (bits), 0)
#define ACTION_DEFAULT_LAYER_BIT_SET(part, bits)    ACTION_LAYER_BITOP(OP_BIT_SET, (part), (bits), 0)
/* with Tapping */
#define ACTION_LAYER_TAP_KEY(layer, key)            ACTION_LAYER_TAP((layer), (key))
#define ACTION_LAYER_TAP_TOGGLE(layer)              ACTION_LAYER_TAP((layer), OP_TAP_TOGGLE)


/*
 * Extensions
 */
/* Macro */
#define ACTION_MACRO(id)                ACTION(ACT_MACRO, (id))
#define ACTION_MACRO_TAP(id)            ACTION(ACT_MACRO, FUNC_TAP<<8 | (id))
#define ACTION_MACRO_OPT(id, opt)       ACTION(ACT_MACRO, (opt)<<8 | (id))

/* Command */
#define ACTION_COMMAND(id, opt)         ACTION(ACT_COMMAND,  (opt)<<8 | (addr))

/* Function */
enum function_opts {
    FUNC_TAP        = 0x8,      /* indciates function is tappable */
};
#define ACTION_FUNCTION(id)             ACTION(ACT_FUNCTION, (id))
#define ACTION_FUNCTION_TAP(id)         ACTION(ACT_FUNCTION, FUNC_TAP<<8 | (id))
#define ACTION_FUNCTION_OPT(id, opt)    ACTION(ACT_FUNCTION, (opt)<<8 | (id))

#endif  /* ACTION_H */
