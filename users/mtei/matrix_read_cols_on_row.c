// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

/* expand macro test command
gcc --include testconfig.h  -DCPP_EXPAND_TEST -E -C matrix_read_cols_on_row.c | sed '1,/^..-expand-start-/d'
*/
#define USE_INPUT_PORT_CHARGE

#ifndef DEBUG_UART_LOG
#    define DEBUG_UART_LOG_INIT(x)
#    define DEBUG_UART_LOG(x)
#endif

#ifdef DIRECT_PIN
#    error DIRECT_PIN is not yet supported.
#endif
#ifdef DIODE_DIRECTION
#  if DIODE_DIRECTION == ROW2COL
#     error DIODE_DIRECTION == ROW2COL is not yet supported.
#  endif
#endif

#define WAIT_SPECIFIED_TIME 1
#define ADAPTIVE_TO_INPUT 2
#define FORCE_INPUT_UP_TO_VCC 3
#ifndef MATRIX_IO_DELAY_TYPE
#    define MATRIX_IO_DELAY_TYPE ADAPTIVE_TO_INPUT
#endif

#define _GET_ITEM_1(_1, ...) _1
#define _GET_ITEM_2(_1,_2, ...) _2
#define GET_ITEM_1(...) _GET_ITEM_1(__VA_ARGS__)
#define GET_ITEM_2(...) _GET_ITEM_2(__VA_ARGS__)
#define _REMOVE_OUTER_PARENTHESES(...) __VA_ARGS__
#define REMOVE_OUTER_PARENTHESES(x)  _REMOVE_OUTER_PARENTHESES x
#define WRAP_BRACE(...) {__VA_ARGS__}
#define PARENTHESES_to_BRACE(x) WRAP_BRACE(REMOVE_OUTER_PARENTHESES(x))

#ifndef SWITCH_MATRIX_INPUT_0
#    error SWITCH_MATRIX_INPUT_0 undefined
#endif
#ifndef SWITCH_MATRIX_OUTPUT_0
#    error SWITCH_MATRIX_OUTPUT_0 undefined
#endif

#define INPUT_PORTS_0  REMOVE_OUTER_PARENTHESES(GET_ITEM_1(SWITCH_MATRIX_INPUT_0))
#define INPUT_PINS_0   REMOVE_OUTER_PARENTHESES(GET_ITEM_2(SWITCH_MATRIX_INPUT_0))
#define OUTPUT_PORTS_0 REMOVE_OUTER_PARENTHESES(GET_ITEM_1(SWITCH_MATRIX_OUTPUT_0))
#define OUTPUT_PINS_0  REMOVE_OUTER_PARENTHESES(GET_ITEM_2(SWITCH_MATRIX_OUTPUT_0))

#if defined(SWITCH_MATRIX_INPUT_1) || defined(SWITCH_MATRIX_OUTPUT_1)
//#    pragma message "DIFF_HAND"
#    ifdef SWITCH_MATRIX_INPUT_1
#        define INPUT_PORTS_1  REMOVE_OUTER_PARENTHESES(GET_ITEM_1(SWITCH_MATRIX_INPUT_1))
#        define INPUT_PINS_1   REMOVE_OUTER_PARENTHESES(GET_ITEM_2(SWITCH_MATRIX_INPUT_1))
#    else
#        define INPUT_PORTS_1 INPUT_PORTS_0
#        define INPUT_PINS_1 INPUT_PINS_0
#    endif
#    ifdef SWITCH_MATRIX_OUTPUT_1
#        define OUTPUT_PORTS_1 REMOVE_OUTER_PARENTHESES(GET_ITEM_1(SWITCH_MATRIX_OUTPUT_1))
#        define OUTPUT_PINS_1  REMOVE_OUTER_PARENTHESES(GET_ITEM_2(SWITCH_MATRIX_OUTPUT_1))
#    else
#        define OUTPUT_PORTS_1 OUTPUT_PORTS_0
#        define OUTPUT_PINS_1 OUTPUT_PINS_0
#    endif
#    define NUM_SIDE 2
#else
#    define NUM_SIDE 1
#endif

#ifndef CPP_EXPAND_TEST
#    include "print.h"
#    include "debug.h"
#    include "wait.h"
#    include "matrix.h"
#    include "atomic_util.h"
#    include "gpio.h"
#    include "gpio_extr.h"
#    ifdef SPLIT_KEYBOARD
//  import: volatile bool isLeftHand
#         include "split_common/split_util.h"
#    endif
#endif // CPP_EXPAND_TEST
#include "cpp_map.h"

//-expand-start-

#if NUM_SIDE == 1
#    define MAX_NUM_INPUT_PINS GET_ITEM_COUNT(INPUT_PINS_0)
#    define MAX_NUM_INPUT_PORTS GET_ITEM_COUNT(INPUT_PORTS_0)
#    define MAX_NUM_OUTPUT_PINS GET_ITEM_COUNT(OUTPUT_PINS_0)
#    define MAX_NUM_OUTPUT_PORTS GET_ITEM_COUNT(OUTPUT_PORTS_0)
#else
#    if GET_ITEM_COUNT(INPUT_PINS_0) > GET_ITEM_COUNT(INPUT_PINS_1)
#        define MAX_NUM_INPUT_PINS GET_ITEM_COUNT(INPUT_PINS_0)
#    else
#        define MAX_NUM_INPUT_PINS GET_ITEM_COUNT(INPUT_PINS_1)
#    endif
#    if GET_ITEM_COUNT(INPUT_PORTS_0) > GET_ITEM_COUNT(INPUT_PORTS_1)
#        define MAX_NUM_INPUT_PORTS GET_ITEM_COUNT(INPUT_PORT_0)
#    else
#        define MAX_NUM_INPUT_PORTS GET_ITEM_COUNT(INPUT_PORTS_1)
#    endif
#    if GET_ITEM_COUNT(OUTPUT_PINS_0) > GET_ITEM_COUNT(OUTPUT_PINS_1)
#        define MAX_NUM_OUTPUT_PINS GET_ITEM_COUNT(OUTPUT_PINS_0)
#    else
#        define MAX_NUM_OUTPUT_PINS GET_ITEM_COUNT(OUTPUT_PINS_1)
#    endif
#    if GET_ITEM_COUNT(OUTPUT_PORTS_0) > GET_ITEM_COUNT(OUTPUT_PORTS_1)
#        define MAX_NUM_OUTPUT_PORTS GET_ITEM_COUNT(OUTPUT_PORTS_0)
#    else
#        define MAX_NUM_OUTPUT_PORTS GET_ITEM_COUNT(OUTPUT_PORTS_1)
#    endif
#endif

#ifdef MATRIX_DELAY_DEBUG_PIN
#  define DEBUG_PIN_INIT()  setPinOutput(MATRIX_DELAY_DEBUG_PIN);  writePinLow(MATRIX_DELAY_DEBUG_PIN)
#  define DEBUG_PIN_ON()    writePinHigh(MATRIX_DELAY_DEBUG_PIN)
#  define DEBUG_PIN_OFF()   writePinLow(MATRIX_DELAY_DEBUG_PIN)
#  define DEBUG_PIN_WAIT(n) wait_cpuclock(n);
#else
#  define DEBUG_PIN_INIT()
#  define DEBUG_PIN_ON()
#  define DEBUG_PIN_OFF()
#  define DEBUG_PIN_WAIT(n)
#endif

#define ALWAYS_INLINE __attribute__((always_inline)) inline
#define NO_INLINE __attribute__((noinline))

//////////////// pin,port table part ////////////////
typedef struct _port_list_element_t {
    pin_t       port;
    port_data_t mask;
    uint16_t    dev;
} port_list_element_t;

typedef struct _pin_list_element_t {
    uint8_t      pindex;
    port_data_t  smask;
    matrix_row_t dmask; // ==0 mean NO_PIN
} pin_list_element_t;

typedef struct _port_pin_list_element_t {
    port_list_element_t iports[MAX_NUM_INPUT_PORTS];
    pin_list_element_t  ipins[MAX_NUM_INPUT_PINS];
    port_list_element_t oports[MAX_NUM_OUTPUT_PORTS];
    pin_list_element_t  opins[MAX_NUM_OUTPUT_PINS];
} port_pin_list_element_t;

#define GEN_PORT_PIN_LIST(x) PARENTHESES_to_BRACE(x),

const static port_pin_list_element_t minfo[] = {
    [0] = {
        .iports = { // { PORT, MASK },
            MAP(GEN_PORT_PIN_LIST, INPUT_PORTS_0)
        },
        .ipins = { // { PORTNUM, SMASK, DMASK },
            MAP(GEN_PORT_PIN_LIST, INPUT_PINS_0)
        },
        .oports  = { // { PORT, MASK },
            MAP(GEN_PORT_PIN_LIST, OUTPUT_PORTS_0)
        },
        .opins = { // { PORTNUM, SMASK, DMASK },
            MAP(GEN_PORT_PIN_LIST, OUTPUT_PINS_0)
        }
    }
#if NUM_SIDE == 2
    ,[1] = {
        .iports = { // { PORT, MASK },
            MAP(GEN_PORT_PIN_LIST, INPUT_PORTS_1)
        },
        .ipins = { // { PORTNUM, SMASK, DMASK },
            MAP(GEN_PORT_PIN_LIST, INPUT_PINS_1)
        },
        .oports  = { // { PORT, MASK },
            MAP(GEN_PORT_PIN_LIST, OUTPUT_PORTS_1)
        },
        .opins = { // { PORTNUM, SMASK, DMASK },
            MAP(GEN_PORT_PIN_LIST, OUTPUT_PINS_1)
        },
    }
#endif
};

ALWAYS_INLINE
static void writeOutputPin_Low(pin_t pin) {
    setPinOutput(pin);
    writePinLow(pin);
}

ALWAYS_INLINE
static void writeOutputPin_High_Z(pin_t pin) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
    setPinOutput(pin);
    writePinHigh(pin);
#else
    setPinInputHigh(pin);
#endif
}

ALWAYS_INLINE
static void writeOutputPortBunch_Low(pin_t port, port_data_t mask) {
    setPortBunchOutput(port, mask);
    writePortBunchLow(port, mask);
}

ALWAYS_INLINE
static void writeOutputPortBunch_High_Z(pin_t port, port_data_t mask) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
    setPortBunchOutput(port, mask);
    writePortBunchHigh(port, mask);
#else
    setPortBunchInputHigh(port, mask);
#endif
}

ALWAYS_INLINE
static void InputPortCharge(pin_t port, port_data_t mask) {
    setPortBunchOutput(port, mask); // set push-pull output mode
    writePortBunchHigh(port, mask); // set line-level high
    setPortBunchInputHigh(port, mask); // set input mode with pull-up
}

#define GEN_ALL_INPUT_HIGH(SIDE,INDEX,PORT) setPortBunchInputHigh(minfo[SIDE].iports[INDEX].port, minfo[SIDE].iports[INDEX].mask);
#define GEN_ALL_INPUT_CHARGE(SIDE,INDEX,PORT) InputPortCharge(minfo[SIDE].iports[INDEX].port, minfo[SIDE].iports[INDEX].mask);
#define GEN_CASE_WRITE_LOW(SIDE,INDEX,PIN) case INDEX: writeOutputPortBunch_Low(minfo[SIDE].oports[minfo[SIDE].opins[INDEX].pindex].port, minfo[SIDE].opins[INDEX].smask); break;
#define GEN_CASE_WRITE_HIGH_Z(SIDE,INDEX,PIN) case INDEX: writeOutputPortBunch_High_Z(minfo[SIDE].oports[minfo[SIDE].opins[INDEX].pindex].port, minfo[SIDE].opins[INDEX].smask); break;
#define GEN_ALL_WITE_HIGHT_Z(SIDE,INDEX,PORT) writeOutputPortBunch_High_Z(minfo[SIDE].oports[INDEX].port, minfo[SIDE].oports[INDEX].mask);
#define GEN_READ_PORT(SIDE,INDEX,PORT) buffer[INDEX] = readPort(minfo[SIDE].iports[INDEX].port);
#define GEN_ALL_MASK_ADJUST(SIDE,INDEX,PORT) data = mask_and_adjust_a_port(*buffer, minfo[SIDE].iports[INDEX].mask);  keypushd |= data;  *buffer++ = data;
#define GEN_BUILD(SIDE,INDEX,PIN) | (buffer[minfo[SIDE].ipins[INDEX].pindex] & minfo[SIDE].ipins[INDEX].smask ? minfo[SIDE].ipins[INDEX].dmask : 0)

//////////////// SIDE 0: select, unselect, read-port, build-line part ////////////////
#define GEN_ALL_INPUT_HIGH_0(INDEX,PORT) GEN_ALL_INPUT_HIGH(0,INDEX,PORT)
#define GEN_ALL_INPUT_CHARGE_0(INDEX,PORT) GEN_ALL_INPUT_CHARGE(0,INDEX,PORT)
#define GEN_CASE_WRITE_LOW_0(INDEX,PIN) GEN_CASE_WRITE_LOW(0,INDEX,PIN)
#define GEN_CASE_WRITE_HIGH_Z_0(INDEX,PIN) GEN_CASE_WRITE_HIGH_Z(0,INDEX,PIN)
#define GEN_ALL_WITE_HIGHT_Z_0(INDEX,PORT) GEN_ALL_WITE_HIGHT_Z(0,INDEX,PORT)
#define GEN_READ_PORT_0(INDEX,PORT) GEN_READ_PORT(0,INDEX,PORT)
#define GEN_ALL_MASK_ADJUST_0(INDEX,PORT) GEN_ALL_MASK_ADJUST(0,INDEX,PORT)
#define GEN_BUILD_0(INDEX,PIN) GEN_BUILD(0,INDEX,PIN)

static void init_all_input_pins_0(void) {
    ATOMIC_BLOCK_FORCEON {
        // setPortBunchInputHigh(minfo[SIDE].iports[INDEX].port, minfo[SIDE].iports[INDEX].mask);
        MAP_INDEX(GEN_ALL_INPUT_HIGH_0,INPUT_PORTS_0)
    }
}

//ALWAYS_INLINE
#if NUM_SIDE == 2 || MATRIX_IO_DELAY_TYPE == FORCE_INPUT_UP_TO_VCC
static void input_port_charge_0(void) {
#    if MATRIX_IO_DELAY_TYPE == FORCE_INPUT_UP_TO_VCC
    ATOMIC_BLOCK_FORCEON {
        // InputPortCharge(minfo[SIDE].iports[INDEX].port, minfo[SIDE].iports[INDEX].mask);
        MAP_INDEX(GEN_ALL_INPUT_CHARGE_0,INPUT_PORTS_0)
    }
#    endif
}
#endif

//ALWAYS_INLINE
static void select_output_0(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        switch(row) {
            // case INDEX: writeOutputPortBunch_Low(minfo[SIDE].oports[minfo[SIDE].opins[INDEX].pindex].port, minfo[SIDE].opins[INDEX].smask); break;
            MAP_INDEX(GEN_CASE_WRITE_LOW_0,OUTPUT_PINS_0)
        }
    }
}

#if 0
#define GEN_ALL_WRITE_LOW(SIDE,INDEX,PIN) if (minfo[SIDE].opins[INDEX].dmask != 0) { writeOutputPortBunch_Low(minfo[SIDE].oports[minfo[SIDE].opins[INDEX].pindex].port, minfo[SIDE].opins[INDEX].smask); }
#define GEN_ALL_WRITE_LOW_0(INDEX,PIN) GEN_ALL_WRITE_LOW(0,INDEX,PIN)
#define GEN_ALL_WRITE_LOW_1(INDEX,PIN) GEN_ALL_WRITE_LOW(1,INDEX,PIN)

static void select_all_output_0(void) {
    ATOMIC_BLOCK_FORCEON {
        // if (minfo[SIDE].opins[INDEX].dmask != 0) { writeOutputPortBunch_Low(minfo[SIDE].oports[minfo[SIDE].opins[INDEX].pindex].port, minfo[SIDE].opins[INDEX].smask); }
        MAP_INDEX(GEN_ALL_WRITE_LOW_0,OUTPUT_PINS_0)
    }
}
#endif

//ALWAYS_INLINE
static void unselect_output_0(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        switch(row) {
            // case INDEX: writeOutputPortBunch_High_Z(minfo[SIDE].oports[minfo[SIDE].opins[INDEX].pindex].port, minfo[SIDE].opins[INDEX].smask); break;
            MAP_INDEX(GEN_CASE_WRITE_HIGH_Z_0,OUTPUT_PINS_0)
        }
    }
}

static void unselect_all_output_0(void) {
    ATOMIC_BLOCK_FORCEON {
        // writeOutputPortBunch_High_Z(minfo[SIDE].oports[INDEX].port, minfo[SIDE].oports[INDEX].mask);
        MAP_INDEX(GEN_ALL_WITE_HIGHT_Z_0,OUTPUT_PORTS_0)
    }
}

//ALWAYS_INLINE
static void read_all_pins_0(port_data_t *buffer) {
    // buffer[INDEX] = readPort(minfo[SIDE].iports[INDEX].port);
    MAP_INDEX(GEN_READ_PORT_0,INPUT_PORTS_0)
}

ALWAYS_INLINE
static port_data_t mask_and_adjust_a_port(port_data_t data, port_data_t mask) {
    data &= mask;
#ifndef MATRIX_SWITCH_LOGIC_IS_ACTIVE_HIGH
    data ^= mask; // change to active-High
#endif
    return data;
}

//ALWAYS_INLINE
static bool mask_and_adjust_pins_0(port_data_t *buffer) {
    port_data_t keypushd = 0;
    port_data_t data;

    // data = mask_and_adjust_a_port(*buffer, minfo[SIDE].iports[INDEX].mask);  keypushd |= data;  *buffer++ = data;
    MAP_INDEX(GEN_ALL_MASK_ADJUST_0,INPUT_PORTS_0)
    return keypushd != 0;
}

static matrix_row_t build_line_0(port_data_t *buffer) {
    return 0
    //  | (buffer[minfo[SIDE].ipins[INDEX].pindex] & minfo[SIDE].ipins[INDEX].smask ? minfo[SIDE].ipins[INDEX].dmask : 0)
        MAP_INDEX(GEN_BUILD_0,INPUT_PINS_0)
        ;
}

#if NUM_SIDE == 2
//////////////// SIDE 1: select, unselect, read-port, build-line part ////////////////
#define GEN_ALL_INPUT_HIGH_1(INDEX,PORT) GEN_ALL_INPUT_HIGH(1,INDEX,PORT)
#define GEN_ALL_INPUT_CHARGE_1(INDEX,PORT) GEN_ALL_INPUT_CHARGE(1,INDEX,PORT)
#define GEN_CASE_WRITE_LOW_1(INDEX,PIN) GEN_CASE_WRITE_LOW(1,INDEX,PIN)
#define GEN_CASE_WRITE_HIGH_Z_1(INDEX,PIN) GEN_CASE_WRITE_HIGH_Z(1,INDEX,PIN)
#define GEN_ALL_WITE_HIGHT_Z_1(INDEX,PORT) GEN_ALL_WITE_HIGHT_Z(1,INDEX,PORT)
#define GEN_READ_PORT_1(INDEX,PORT) GEN_READ_PORT(1,INDEX,PORT)
#define GEN_ALL_MASK_ADJUST_1(INDEX,PORT) GEN_ALL_MASK_ADJUST(1,INDEX,PORT)
#define GEN_BUILD_1(INDEX,PIN) GEN_BUILD(1,INDEX,PIN)

static void init_all_input_pins_1(void) {
    ATOMIC_BLOCK_FORCEON {
        // setPortBunchInputHigh(minfo[SIDE].iports[INDEX].port, minfo[SIDE].iports[INDEX].mask);
        MAP_INDEX(GEN_ALL_INPUT_HIGH_1,INPUT_PORTS_1)
    }
}

//ALWAYS_INLINE
static void input_port_charge_1(void) {
#if MATRIX_IO_DELAY_TYPE == FORCE_INPUT_UP_TO_VCC
    ATOMIC_BLOCK_FORCEON {
        // InputPortCharge(minfo[SIDE].iports[INDEX].port, minfo[SIDE].iports[INDEX].mask);
        MAP_INDEX(GEN_ALL_INPUT_CHARGE_1,INPUT_PORTS_1)
    }
#endif
}

//ALWAYS_INLINE
static void select_output_1(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        switch(row) {
            // case INDEX: writeOutputPortBunch_Low(minfo[SIDE].oports[minfo[SIDE].opins[INDEX].pindex].port, minfo[SIDE].opins[INDEX].smask); break;
            MAP_INDEX(GEN_CASE_WRITE_LOW_1,OUTPUT_PINS_1)
        }
    }
}

//ALWAYS_INLINE
static void unselect_output_1(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        switch(row) {
            // case INDEX: writeOutputPortBunch_High_Z(minfo[SIDE].oports[minfo[SIDE].opins[INDEX].pindex].port, minfo[SIDE].opins[INDEX].smask); break;
            MAP_INDEX(GEN_CASE_WRITE_HIGH_Z_1,OUTPUT_PINS_1)
        }
    }
}

static void unselect_all_output_1(void) {
    ATOMIC_BLOCK_FORCEON {
        // writeOutputPortBunch_High_Z(minfo[SIDE].oports[INDEX].port, minfo[SIDE].oports[INDEX].mask);
        MAP_INDEX(GEN_ALL_WITE_HIGHT_Z_1,OUTPUT_PORTS_1)
    }
}

//ALWAYS_INLINE
static void read_all_pins_1(port_data_t *buffer) {
    // buffer[INDEX] = readPort(minfo[SIDE].iports[INDEX].port);
    MAP_INDEX(GEN_READ_PORT_1,INPUT_PORTS_1)
}

//ALWAYS_INLINE
static bool mask_and_adjust_pins_1(port_data_t *buffer) {
    port_data_t keypushd = 0;
    port_data_t data;

    // data = mask_and_adjust_a_port(*buffer, minfo[SIDE].iports[INDEX].mask);  keypushd |= data;  *buffer++ = data;
    MAP_INDEX(GEN_ALL_MASK_ADJUST_1,INPUT_PORTS_1)
    return keypushd != 0;
}

static matrix_row_t build_line_1(port_data_t *buffer) {
    return 0
    //  | (buffer[minfo[SIDE].ipins[INDEX].pindex] & minfo[SIDE].ipins[INDEX].smask ? minfo[SIDE].ipins[INDEX].dmask : 0)
        MAP_INDEX(GEN_BUILD_1,INPUT_PINS_1)
        ;
}
#endif // NUM_SIDE == 2

//////////////// matrix.c override part ////////////////
#ifdef DEBUG_ON_TEST_BENCH
#define matrix_init_pins x_matrix_init_pins
#define matrix_read_cols_on_row x_matrix_read_cols_on_row
#endif

typedef void (*funcp_void_row)(uint8_t row);
typedef void (*funcp_void_void)(void);
typedef void (*funcp_void_port_data)(port_data_t *buffer);
typedef bool (*funcp_bool_port_data)(port_data_t *buffer);
typedef matrix_row_t (*funcp_build_line)(port_data_t *buffer);

const pin_list_element_t *current_sides_opins = minfo[0].opins;
#if NUM_SIDE == 2
funcp_void_void init_all_input_pins = init_all_input_pins_0;
funcp_void_row select_output = select_output_0;
funcp_void_row unselect_output = unselect_output_0;
funcp_void_void unselect_all_output = unselect_all_output_0;
funcp_void_port_data read_all_pins = read_all_pins_0;
funcp_void_void input_port_charge = input_port_charge_0;
funcp_bool_port_data mask_and_adjust_pins = mask_and_adjust_pins_0;
funcp_build_line build_line = build_line_0;
#else
#    define init_all_input_pins() init_all_input_pins_0()
#    define select_output(x) select_output_0(x)
#    define unselect_output(x) unselect_output_0(x)
#    define unselect_all_output() unselect_all_output_0()
#    define read_all_pins(x) read_all_pins_0(x)
#    define input_port_charge() input_port_charge_0()
#    define mask_and_adjust_pins(x) mask_and_adjust_pins_0(x)
#    define build_line(x) build_line_0(x)
#endif

void matrix_init_pins(void) {
    DEBUG_PIN_INIT();
    DEBUG_UART_LOG_INIT(0);
#if NUM_SIDE == 2
    bool is_side1 = !isLeftHand;
    if (is_side1) {
        current_sides_opins = minfo[1].opins;
        init_all_input_pins = init_all_input_pins_1;
        select_output = select_output_1;
        unselect_output = unselect_output_1;
        unselect_all_output = unselect_all_output_1;
        read_all_pins = read_all_pins_1;
        input_port_charge = input_port_charge_1;
        mask_and_adjust_pins = mask_and_adjust_pins_1;
        build_line = build_line_1;
    }
#endif
    unselect_all_output();
    init_all_input_pins();
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    port_data_t port_buffer[MAX_NUM_INPUT_PORTS];
    matrix_row_t current_row_value = 0;
    bool key_pressed;

    if (current_sides_opins[current_row].dmask == 0) {
        return;                        // skip NO_PIN row
    }
    DEBUG_PIN_ON();
    select_output(current_row);
    matrix_output_select_delay();
    read_all_pins(port_buffer);
    unselect_output(current_row);
    DEBUG_PIN_OFF();
    key_pressed = mask_and_adjust_pins(port_buffer);
    DEBUG_PIN_ON();
#if MATRIX_IO_DELAY_TYPE == WAIT_SPECIFIED_TIME
    //#    pragma message "WAIT_SPECIFIED_TIME"
    if (key_pressed) {
        current_row_value = build_line(port_buffer);
    }
    matrix_output_unselect_delay(current_row, key_pressed);
#endif
#if MATRIX_IO_DELAY_TYPE == FORCE_INPUT_UP_TO_VCC
    //#    pragma message "FORCE_INPUT_UP_TO_VCC"
    if (key_pressed) {
        input_port_charge();
        current_row_value = build_line(port_buffer);
    }
#endif
#if MATRIX_IO_DELAY_TYPE == ADAPTIVE_TO_INPUT
    //#    pragma message "ADAPTIVE_TO_INPUT"
    if (key_pressed) {
        current_row_value = build_line(port_buffer);
        // wait unselect done
        while (key_pressed) {
            read_all_pins(port_buffer);
            key_pressed = mask_and_adjust_pins(port_buffer);
        }
    }
#endif
    // Update the matrix
    current_matrix[current_row] = current_row_value;
    DEBUG_PIN_OFF();
}

#ifdef DEBUG_ON_TEST_BENCH
#include "matrix_testbench.c"
#endif
