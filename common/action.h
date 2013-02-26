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
#include "action_macro.h"


/* Struct to record event and tap count  */
typedef union {
    struct {
        bool    interrupted :1;
        bool    reserved2   :1;
        bool    reserved1   :1;
        bool    reserved0   :1;
        uint8_t count       :4;
    };
} tap_t;

typedef struct {
    keyevent_t  event;
    tap_t tap;
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



/* Execute action per keyevent */
void action_exec(keyevent_t event);

/* action for key */
action_t action_for_key(uint8_t layer, key_t key);

/* macro */
const prog_macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt);

/* user defined special function */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt);

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
 * ACT_KEYMAP:
 * 1000|--xx|0000 0000   Clear keyamp and overlay
 * 1000|LLLL|0000 00xx   Reset default layer and clear keymap and overlay
 * 1000|LLLL| keycode    Invert with tap key
 * 1000|LLLL|1111 0000   Invert with tap toggle
 * 1000|LLLL|1111 00xx   Invert[^=  1<<L]
 * 1000|LLLL|1111 0100   On/Off
 * 1000|LLLL|1111 01xx   On[|= 1<<L]
 * 1000|LLLL|1111 1000   Off/On
 * 1000|LLLL|1111 10xx   Off[&= ~(1<<L)]
 * 1000|LLLL|1111 1100   Set/Clear
 * 1000|LLLL|1111 11xx   Set[= 1<<L]
 * default layer: 0-15(4bit)
 * xx: On {00:for special use, 01:press, 10:release, 11:both}
 *
 * ACT_OVERLAY:
 * 1011|0000|0000 0000   Clear overlay
 * 1011|LLLL|0000 00ss   Invert 4-bit chunk [^= L<<(4*ss)]
 * 1011|LLLL| keycode    Invert with tap key
 * 1011|LLLL|1111 0000   Invert with tap toggle
 * 1011|LLLL|1111 00xx   Invert[^= 1<<L]
 * 1011|LLLL|1111 0100   On/Off(momentary)
 * 1011|LLLL|1111 01xx   On[|= 1<<L]
 * 1011|LLLL|1111 1000   Off/On
 * 1011|LLLL|1111 10xx   Off[&= ~(1<<L)]
 * 1011|LLLL|1111 1100   Set/Clear
 * 1011|LLLL|1111 11xx   Set[= 1<<L]
 * overlays: 16-layer on/off status(16bit)
 * xx: On {00:for special use, 01:press, 10:release, 11:both}
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
    ACT_LMODS           = 0b0000,
    ACT_RMODS           = 0b0001,
    ACT_LMODS_TAP       = 0b0010,
    ACT_RMODS_TAP       = 0b0011,

    ACT_USAGE           = 0b0100,
    ACT_MOUSEKEY        = 0b0101,

    ACT_KEYMAP          = 0b1000,
    ACT_OVERLAY         = 0b1001,

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



/* Layer Actions:
 *      Invert  layer ^= (1<<layer)
 *      On      layer |= (1<<layer)
 *      Off     layer &= ~(1<<layer)
 *      Set     layer = (1<<layer)
 *      Clear   layer = 0
 */
enum layer_params {
    ON_PRESS    = 1,
    ON_RELEASE  = 2,
    ON_BOTH     = 3,

    OP_RESET  = 0x00,
    OP_INV4  = 0x00,
    OP_INV   = 0xF0,
    OP_ON    = 0xF4,
    OP_OFF   = 0xF8,
    OP_SET   = 0xFC,
};

/* 
 * Default Layer
 */
#define ACTION_DEFAULT_LAYER                      ACTION(ACT_KEYMAP, 0<<8 | OP_RESET | 0)
#define ACTION_SET_DEFAULT_LAYER(layer)           ACTION_KEYMAP_RESET(layer)
#define ACTION_SET_DEFAULT_LAYER_P(layer)         ACTION_KEYMAP_RESET_P(layer)
#define ACTION_SET_DEFAULT_LAYER_R(layer)         ACTION_KEYMAP_RESET_R(layer)
#define ACTION_SET_DEFAULT_LAYER_B(layer)         ACTION_KEYMAP_RESET_B(layer)
/*
 * Keymap Layer
 */
#define ACTION_KEYMAP(layer)                     ACTION_KEYMAP_MOMENTARY(layer)
#define ACTION_KEYMAP_MOMENTARY(layer)           ACTION_KEYMAP_ON_OFF(layer)
#define ACTION_KEYMAP_TOGGLE(layer)              ACTION_KEYMAP_INV_R(layer)
/* Keymap Set and clear overaly */
#define ACTION_KEYMAP_RESET(layer)               ACTION_KEYMAP_RESET_R(layer)
#define ACTION_KEYMAP_RESET_P(layer)             ACTION(ACT_KEYMAP, (layer)<<8 | OP_RESET | ON_PRESS)
#define ACTION_KEYMAP_RESET_R(layer)             ACTION(ACT_KEYMAP, (layer)<<8 | OP_RESET | ON_RELEASE)
#define ACTION_KEYMAP_RESET_B(layer)             ACTION(ACT_KEYMAP, (layer)<<8 | OP_RESET | ON_BOTH)
/* Keymap Invert */
#define ACTION_KEYMAP_INV(layer)                 ACTION_KEYMAP_INV_B(layer)
#define ACTION_KEYMAP_TAP_TOGGLE(layer)          ACTION(ACT_KEYMAP, (layer)<<8 | OP_INV | 0)
#define ACTION_KEYMAP_INV_P(layer)               ACTION(ACT_KEYMAP, (layer)<<8 | OP_INV | ON_PRESS)
#define ACTION_KEYMAP_INV_R(layer)               ACTION(ACT_KEYMAP, (layer)<<8 | OP_INV | ON_RELEASE)
#define ACTION_KEYMAP_INV_B(layer)               ACTION(ACT_KEYMAP, (layer)<<8 | OP_INV | ON_BOTH)
/* Keymap On */
#define ACTION_KEYMAP_ON(layer)                  ACTION_KEYMAP_ON_OFF(layer)
#define ACTION_KEYMAP_ON_OFF(layer)              ACTION(ACT_KEYMAP, (layer)<<8 | OP_ON  | 0)
#define ACTION_KEYMAP_ON_P(layer)                ACTION(ACT_KEYMAP, (layer)<<8 | OP_ON  | ON_PRESS)
#define ACTION_KEYMAP_ON_R(layer)                ACTION(ACT_KEYMAP, (layer)<<8 | OP_ON  | ON_RELEASE)
#define ACTION_KEYMAP_ON_B(layer)                ACTION(ACT_KEYMAP, (layer)<<8 | OP_ON  | ON_BOTH)
/* Keymap Off */
#define ACTION_KEYMAP_OFF(layer)                 ACTION_KEYMAP_OFF_ON(layer)
#define ACTION_KEYMAP_OFF_ON(layer)              ACTION(ACT_KEYMAP, (layer)<<8 | OP_OFF | 0)
#define ACTION_KEYMAP_OFF_P(layer)               ACTION(ACT_KEYMAP, (layer)<<8 | OP_OFF | ON_PRESS)
#define ACTION_KEYMAP_OFF_R(layer)               ACTION(ACT_KEYMAP, (layer)<<8 | OP_OFF | ON_RELEASE)
#define ACTION_KEYMAP_OFF_B(layer)               ACTION(ACT_KEYMAP, (layer)<<8 | OP_OFF | ON_BOTH)
/* Keymap Set */
#define ACTION_KEYMAP_SET(layer)                 ACTION_KEYMAP_SET_CLEAR(layer)
#define ACTION_KEYMAP_SET_CLEAR(layer)           ACTION(ACT_KEYMAP, (layer)<<8 | OP_SET | 0)
#define ACTION_KEYMAP_SET_P(layer)               ACTION(ACT_KEYMAP, (layer)<<8 | OP_SET | ON_PRESS)
#define ACTION_KEYMAP_SET_R(layer)               ACTION(ACT_KEYMAP, (layer)<<8 | OP_SET | ON_RELEASE)
#define ACTION_KEYMAP_SET_B(layer)               ACTION(ACT_KEYMAP, (layer)<<8 | OP_SET | ON_BOTH)
/* Keymap Invert with tap key */
#define ACTION_KEYMAP_TAP_KEY(layer, key)        ACTION(ACT_KEYMAP, (layer)<<8 | (key))

/*
 * Overlay Layer
 */
#define ACTION_OVERLAY(layer)                     ACTION_OVERLAY_MOMENTARY(layer)
#define ACTION_OVERLAY_MOMENTARY(layer)           ACTION_OVERLAY_ON_OFF(layer)
#define ACTION_OVERLAY_TOGGLE(layer)              ACTION_OVERLAY_INV_R(layer)
/* Overlay Clear */
#define ACTION_OVERLAY_CLEAR                      ACTION(ACT_OVERLAY, 0<<8 | OP_INV4 | 0)
#define ACTION_OVERLAY_CLEAR_P                    ACTION(ACT_OVERLAY, 0<<8 | OP_INV4 | ON_PRESS)
#define ACTION_OVERLAY_CLEAR_R                    ACTION(ACT_OVERLAY, 0<<8 | OP_INV4 | ON_RELEASE)
#define ACTION_OVERLAY_CLEAR_B                    ACTION(ACT_OVERLAY, 0<<8 | OP_INV4 | ON_BOTH)
/* Overlay Invert 4-bit chunk */
#define ACTION_OVERLAY_INV4(bits, shift)          ACTION(ACT_OVERLAY, (bits)<<8 | OP_INV4 | shift)
/* Overlay Invert */
#define ACTION_OVERLAY_INV(layer)                 ACTION_OVERLAY_INV_B(layer)
#define ACTION_OVERLAY_TAP_TOGGLE(layer)          ACTION(ACT_OVERLAY, (layer)<<8 | OP_INV | 0)
#define ACTION_OVERLAY_INV_P(layer)               ACTION(ACT_OVERLAY, (layer)<<8 | OP_INV | ON_PRESS)
#define ACTION_OVERLAY_INV_R(layer)               ACTION(ACT_OVERLAY, (layer)<<8 | OP_INV | ON_RELEASE)
#define ACTION_OVERLAY_INV_B(layer)               ACTION(ACT_OVERLAY, (layer)<<8 | OP_INV | ON_BOTH)
/* Overlay On */
#define ACTION_OVERLAY_ON(layer)                  ACTION_OVERLAY_ON_OFF(layer)
#define ACTION_OVERLAY_ON_OFF(layer)              ACTION(ACT_OVERLAY, (layer)<<8 | OP_ON  | 0)
#define ACTION_OVERLAY_ON_P(layer)                ACTION(ACT_OVERLAY, (layer)<<8 | OP_ON  | ON_PRESS)
#define ACTION_OVERLAY_ON_R(layer)                ACTION(ACT_OVERLAY, (layer)<<8 | OP_ON  | ON_RELEASE)
#define ACTION_OVERLAY_ON_B(layer)                ACTION(ACT_OVERLAY, (layer)<<8 | OP_ON  | ON_BOTH)
/* Overlay Off */
#define ACTION_OVERLAY_OFF(layer)                 ACTION_OVERLAY_OFF_ON(layer)
#define ACTION_OVERLAY_OFF_ON(layer)              ACTION(ACT_OVERLAY, (layer)<<8 | OP_OFF | 0)
#define ACTION_OVERLAY_OFF_P(layer)               ACTION(ACT_OVERLAY, (layer)<<8 | OP_OFF | ON_PRESS)
#define ACTION_OVERLAY_OFF_R(layer)               ACTION(ACT_OVERLAY, (layer)<<8 | OP_OFF | ON_RELEASE)
#define ACTION_OVERLAY_OFF_B(layer)               ACTION(ACT_OVERLAY, (layer)<<8 | OP_OFF | ON_BOTH)
/* Overlay Set */
#define ACTION_OVERLAY_SET(layer)                 ACTION_OVERLAY_SET_CLEAR(layer)
#define ACTION_OVERLAY_SET_CLEAR(layer)           ACTION(ACT_OVERLAY, (layer)<<8 | OP_SET | 0)
#define ACTION_OVERLAY_SET_P(layer)               ACTION(ACT_OVERLAY, (layer)<<8 | OP_SET | ON_PRESS)
#define ACTION_OVERLAY_SET_R(layer)               ACTION(ACT_OVERLAY, (layer)<<8 | OP_SET | ON_RELEASE)
#define ACTION_OVERLAY_SET_B(layer)               ACTION(ACT_OVERLAY, (layer)<<8 | OP_SET | ON_BOTH)
/* Overlay Invert with tap key */
#define ACTION_OVERLAY_TAP_KEY(layer, key)        ACTION(ACT_OVERLAY, (layer)<<8 | (key))


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
