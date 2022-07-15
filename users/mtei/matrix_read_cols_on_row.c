// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

/* expand macro test command
gcc --include <test_config.h> -DCPP_EXPAND_TEST -E -C matrix_read_cols_on_row.c 2>/tmp/err | sed '1,/^..-expand-start-/d' | cat - /tmp/err | less
*/
#ifdef DIRECT_PIN
#    error DIRECT_PIN is not yet supported.
#endif
#ifdef DIODE_DIRECTION
#    if DIODE_DIRECTION == ROW2COL
#        error DIODE_DIRECTION == ROW2COL is not yet supported.
#    endif
#endif

#ifdef DEBUG_UART_LOG
#    pragma message "DEBUG_UART_LOG on"
#else
#    define DEBUG_UART_LOG_INIT(x)
#    define DEBUG_UART_LOG(x)
#endif

/* DEBUG_PIN_*() macros defined in users/mtei/debug_config.h */
#ifdef DEBUG_PIN_INIT
#    pragma message "debug mode of matrix_read_cols_on_row.c"
#    define DEBUG_PIN_ENABLE
#else
#    define DEBUG_PIN_INIT()
#    define DEBUG_PIN_ON()
#    define DEBUG_PIN_OFF()
#    define DEBUG_PIN_WAIT(n)
#endif

/* MATRIX_DEBUG_*() macros defined in <keyboard>/config.h or <keyboard>/debug_config.h */
#ifndef MATRIX_DEBUG_PIN_INIT
#    define MATRIX_DEBUG_PIN_INIT()
#endif
#ifdef MATRIX_DEBUG_SCAN_START
#    pragma message "MATRIX_DEBUG_SCAN_* enable"
#    define DEBUG_PIN_ENABLE
#else
#    define MATRIX_DEBUG_SCAN_START()
#    define MATRIX_DEBUG_SCAN_END()
#endif
#ifdef MATRIX_DEBUG_DELAY_START
#    pragma message "MATRIX_DEBUG_DELAY_* enable"
#    define DEBUG_PIN_ENABLE
#else
#    define MATRIX_DEBUG_DELAY_START()
#    define MATRIX_DEBUG_DELAY_END()
#endif
#ifndef MATRIX_DEBUG_GAP
#    define MATRIX_DEBUG_GAP(n)
#endif

#define WAIT_SPECIFIED_TIME 1
#define ADAPTIVE_TO_INPUT 2
#define FORCE_INPUT_UP_TO_VCC 3
#ifndef MATRIX_IO_DELAY_TYPE
#    define MATRIX_IO_DELAY_TYPE ADAPTIVE_TO_INPUT
#endif

#define _GET_ITEM_1(_1, ...) _1
#define _GET_ITEM_2(_1, _2, ...) _2
#define GET_ITEM_1(...) _GET_ITEM_1(__VA_ARGS__)
#define GET_ITEM_2(...) _GET_ITEM_2(__VA_ARGS__)
#define _REMOVE_OUTER_PARENTHESES(...) __VA_ARGS__
#define REMOVE_OUTER_PARENTHESES(x) _REMOVE_OUTER_PARENTHESES x

#ifndef SWITCH_MATRIX_INPUT_0
#    error SWITCH_MATRIX_INPUT_0 undefined
#endif
#ifndef SWITCH_MATRIX_OUTPUT_0
#    error SWITCH_MATRIX_OUTPUT_0 undefined
#endif

#define INPUT_PORTS_0 REMOVE_OUTER_PARENTHESES(GET_ITEM_1(SWITCH_MATRIX_INPUT_0))
#define INPUT_PINS_0 REMOVE_OUTER_PARENTHESES(GET_ITEM_2(SWITCH_MATRIX_INPUT_0))
#define OUTPUT_PORTS_0 REMOVE_OUTER_PARENTHESES(GET_ITEM_1(SWITCH_MATRIX_OUTPUT_0))
#define OUTPUT_PINS_0 REMOVE_OUTER_PARENTHESES(GET_ITEM_2(SWITCH_MATRIX_OUTPUT_0))

#if defined(SWITCH_MATRIX_INPUT_1) || defined(SWITCH_MATRIX_OUTPUT_1)
//#    pragma message "DIFF_HAND"
#    ifdef SWITCH_MATRIX_INPUT_1
#        define INPUT_PORTS_1 REMOVE_OUTER_PARENTHESES(GET_ITEM_1(SWITCH_MATRIX_INPUT_1))
#        define INPUT_PINS_1 REMOVE_OUTER_PARENTHESES(GET_ITEM_2(SWITCH_MATRIX_INPUT_1))
#    else
#        define INPUT_PORTS_1 INPUT_PORTS_0
#        define INPUT_PINS_1 INPUT_PINS_0
#    endif
#    ifdef SWITCH_MATRIX_OUTPUT_1
#        define OUTPUT_PORTS_1 REMOVE_OUTER_PARENTHESES(GET_ITEM_1(SWITCH_MATRIX_OUTPUT_1))
#        define OUTPUT_PINS_1 REMOVE_OUTER_PARENTHESES(GET_ITEM_2(SWITCH_MATRIX_OUTPUT_1))
#    else
#        define OUTPUT_PORTS_1 OUTPUT_PORTS_0
#        define OUTPUT_PINS_1 OUTPUT_PINS_0
#    endif
#    define NUM_SIDE 2
#else
#    define NUM_SIDE 1
#endif

#ifdef MATRIX_EXTENSION_74HC157
#    define MATRIX_DEVICES MCU_GPIO_74HC157_A, MCU_GPIO_74HC157_B
#    define IS_74HC157(dev) ((dev) == MCU_GPIO_74HC157_A || (dev) == MCU_GPIO_74HC157_B)
#endif

enum DEVICE_NAME {
    MCU_GPIO,
#ifdef MATRIX_DEVICES
    MATRIX_DEVICES
#endif
};

#ifndef CPP_EXPAND_TEST
#    include "print.h"
#    include "debug.h"
#    include "wait.h"
#    include "matrix.h"
#    include "atomic_util.h"
#    include "gpio.h"
#    ifndef readPort
#        include "gpio_extr.h"
#    endif
#    ifndef readPort
#        error matrix_read_cols_on_row.c requires readPort() and related macros.
#    endif
#    ifdef SPLIT_KEYBOARD
//  import: volatile bool isLeftHand
#        include "split_common/split_util.h"
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

// clang-format off
#ifdef CPP_EXPAND_TEST
    "INPUT_PORTS_0" is INPUT_PORTS_0
    "INPUT_PINS_0" is INPUT_PINS_0
    "OUTPUT_PORTS_0" is OUTPUT_PORTS_0
    "OUTPUT_PINS_0" is OUTPUT_PINS_0
#    if NUM_SIDE == 2
    "INPUT_PORTS_1" is INPUT_PORTS_1
    "INPUT_PINS_1" is INPUT_PINS_1
    "OUTPUT_PORTS_1" is OUTPUT_PORTS_1
    "OUTPUT_PINS_1" is OUTPUT_PINS_1
#    endif
    "MAX_NUM_INPUT_PINS" is MAX_NUM_INPUT_PINS
    "MAX_NUM_INPUT_PORTS" is MAX_NUM_INPUT_PORTS
    "MAX_NUM_OUTPUT_PINS" is MAX_NUM_OUTPUT_PINS
    "MAX_NUM_OUTPUT_PORTS" is MAX_NUM_OUTPUT_PORTS
#endif

#define ALWAYS_INLINE __attribute__((always_inline)) inline
#define NO_INLINE __attribute__((noinline))

//////////////// pin,port table part ////////////////
typedef struct _port_list_element_t {
    pin_t       port;
    port_data_t mask;
    uint8_t     dev;
} port_list_element_t;

typedef struct _pin_list_element_t {
    uint8_t      pindex;
    port_data_t  smask;
    matrix_row_t dmask; // ==0 mean NO_PIN
} pin_list_element_t;

typedef struct _port_pin_list_element_t {
    port_list_element_t oports[MAX_NUM_OUTPUT_PORTS];
    uint8_t             opin_enable[MAX_NUM_OUTPUT_PINS];
} port_pin_list_element_t;

#define GEN_PORT_PIN_LIST(x) {REMOVE_OUTER_PARENTHESES(x)},
#define _GEN_OPIN_ENABLE(PORT, SMASK, DMASK) (DMASK != 0),
#define GEN_OPIN_ENABLE(x) _GEN_OPIN_ENABLE x

const static port_pin_list_element_t minfo[] = {
    [0] = {
        .oports  = { // { PORT, MASK },
            MAP(GEN_PORT_PIN_LIST, OUTPUT_PORTS_0)
        },
        .opin_enable = {
            MAP(GEN_OPIN_ENABLE, OUTPUT_PINS_0)
        }
    }
#if NUM_SIDE == 2
    ,[1] = {
        .oports  = { // { PORT, MASK },
            MAP(GEN_PORT_PIN_LIST, OUTPUT_PORTS_1)
        },
        .opin_enable = {
            MAP(GEN_OPIN_ENABLE, OUTPUT_PINS_1)
        }
    }
#endif
};

// clang-format on
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
    setPortBunchOutput(port, mask);    // set push-pull output mode
    writePortBunchHigh(port, mask);    // set line-level high
    setPortBunchInputHigh(port, mask); // set input mode with pull-up
}

// clang-format off
#ifdef MATRIX_EXTENSION_74HC157
ALWAYS_INLINE
static void select74HC157(uint8_t devid) {
    writePin(MATRIX_EXTENSION_74HC157, devid & 1);
}

ALWAYS_INLINE
static port_data_t readPortMultiplexer(uint8_t devid, pin_t port) {
    select74HC157(devid);
    waitInputPinDelay();
    return readPort(port);
}

#    define readMatrixPort(dev, port) \
        ((dev) == MCU_GPIO)? readPort(port) : (IS_74HC157(dev)) ? readPortMultiplexer((dev)-MCU_GPIO_74HC157_A, port) : 0

#else

#    define readMatrixPort(dev, port) readPort(port)
#endif

// clang-format off
#define _GEN_ALL_INPUT_HIGH(PORT, MASK, ...) setPortBunchInputHigh(PORT, MASK);
#define GEN_ALL_INPUT_HIGH(x) _GEN_ALL_INPUT_HIGH x

#define _GEN_ALL_INPUT_CHARGE(PORT, MASK, ...) InputPortCharge(PORT, MASK);
#define GEN_ALL_INPUT_CHARGE(x) _GEN_ALL_INPUT_CHARGE x

#define __GEN_CASE_WRITE_LOW(INDEX, PORT_INDEX, PMASK, RMASK)     \
    case INDEX:                                                   \
        writeOutputPortBunch_Low(oports[PORT_INDEX].port, PMASK); \
        break;
#define _GEN_CASE_WRITE_LOW(...) __GEN_CASE_WRITE_LOW(__VA_ARGS__)
#define GEN_CASE_WRITE_LOW(INDEX, PIN) \
    _GEN_CASE_WRITE_LOW(INDEX, REMOVE_OUTER_PARENTHESES(PIN))

#define __GEN_CASE_WRITE_HIGH_Z(INDEX, PORT_INDEX, PMASK, RMASK)     \
    case INDEX:                                                      \
        writeOutputPortBunch_High_Z(oports[PORT_INDEX].port, PMASK); \
        break;
#define _GEN_CASE_WRITE_HIGH_Z(...) __GEN_CASE_WRITE_HIGH_Z(__VA_ARGS__)
#define GEN_CASE_WRITE_HIGH_Z(INDEX,PIN) \
    _GEN_CASE_WRITE_HIGH_Z(INDEX, REMOVE_OUTER_PARENTHESES(PIN))

#define _GEN_ALL_WRITE_HIGHT_Z(PORT, MASK, ...) \
    writeOutputPortBunch_High_Z(PORT, MASK);
#define GEN_ALL_WRITE_HIGHT_Z(x) _GEN_ALL_WRITE_HIGHT_Z x

#define __GEN_READ_PORT(INDEX, PORT, MASK, DEV) \
    buffer[INDEX] = readMatrixPort(DEV,PORT);
#define _GEN_READ_PORT(...) __GEN_READ_PORT(__VA_ARGS__)
#define GEN_READ_PORT(INDEX, PORT) \
    _GEN_READ_PORT(INDEX, REMOVE_OUTER_PARENTHESES(PORT))

#define _GEN_ALL_MASK_ADJUST(PORT, MASK, DEV)     \
    data = mask_and_adjust_a_port(*buffer, MASK); \
    keypushd |= data;                             \
    *buffer++ = data;
#define GEN_ALL_MASK_ADJUST(PORT) \
    _GEN_ALL_MASK_ADJUST PORT

#define _GEN_BUILD(PORT_INDEX, SMASK, DMASK) \
    | ((buffer[PORT_INDEX] & SMASK) ? DMASK : 0)
#define GEN_BUILD(PIN) _GEN_BUILD PIN

//////////////// SIDE 0: select, unselect, read-port, build-line part ////////////////
static void init_all_input_pins_0(void) {
    ATOMIC_BLOCK_FORCEON {
        // setPortBunchInputHigh(PORT, MASK);
        MAP(GEN_ALL_INPUT_HIGH, INPUT_PORTS_0)
    }
#ifdef MATRIX_EXTENSION_74HC157
    setPinOutput(MATRIX_EXTENSION_74HC157);
    writePinLow(MATRIX_EXTENSION_74HC157);
#endif
}

// ALWAYS_INLINE
#if NUM_SIDE == 2 || MATRIX_IO_DELAY_TYPE == FORCE_INPUT_UP_TO_VCC
static void input_port_charge_0(void) {
#    if MATRIX_IO_DELAY_TYPE == FORCE_INPUT_UP_TO_VCC
    ATOMIC_BLOCK_FORCEON {
        // InputPortCharge(PORT, MASK);
        MAP(GEN_ALL_INPUT_CHARGE, INPUT_PORTS_0)
    }
#    endif // if MATRIX_IO_DELAY_TYPE == FORCE_INPUT_UP_TO_VCC
}
#endif // NUM_SIDE == 2 ...

// ALWAYS_INLINE
static void select_output_0(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        const port_list_element_t *oports = minfo[0].oports;
        switch (row) {
            // case INDEX: writeOutputPortBunch_Low(oports[PORT_INDEX].port,PMASK); break;
            MAP_INDEX(GEN_CASE_WRITE_LOW, OUTPUT_PINS_0)
        }
    }
}

// ALWAYS_INLINE
static void unselect_output_0(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        const port_list_element_t *oports = minfo[0].oports;
        switch (row) {
            // case INDEX: writeOutputPortBunch_High_Z(oports[PORT_INDEX].port,PMASK); break;
            MAP_INDEX(GEN_CASE_WRITE_HIGH_Z, OUTPUT_PINS_0)
        }
    }
}

static void unselect_all_output_0(void) {
    ATOMIC_BLOCK_FORCEON {
        // writeOutputPortBunch_High_Z(PORT, MASK);
        MAP(GEN_ALL_WRITE_HIGHT_Z, OUTPUT_PORTS_0)
    }
}

// ALWAYS_INLINE
static void read_all_pins_0(port_data_t *buffer) {
    // buffer[INDEX] = readMatrixPort(DEV,PORT);
    MAP_INDEX(GEN_READ_PORT, INPUT_PORTS_0)
}

ALWAYS_INLINE
static port_data_t mask_and_adjust_a_port(port_data_t data, port_data_t mask) {
    data &= mask;
#ifndef MATRIX_SWITCH_LOGIC_IS_ACTIVE_HIGH
    data ^= mask; // change to active-High
#endif
    return data;
}

// ALWAYS_INLINE
static bool mask_and_adjust_pins_0(port_data_t *buffer) {
    port_data_t keypushd = 0;
    port_data_t data;

    // data = mask_and_adjust_a_port(*buffer, MASK);  keypushd |= data;  *buffer++ = data;
    MAP(GEN_ALL_MASK_ADJUST, INPUT_PORTS_0)
    return keypushd != 0;
}

static matrix_row_t build_line_0(port_data_t *buffer) {
    return 0
    //  | (buffer[PORT_INDEX] & SMASK ? DMASK : 0)
        MAP(GEN_BUILD, INPUT_PINS_0)
        ;
}

#if NUM_SIDE == 2
//////////////// SIDE 1: select, unselect, read-port, build-line part ////////////////
static void init_all_input_pins_1(void) {
    ATOMIC_BLOCK_FORCEON {
        // setPortBunchInputHigh(PORT, MASK);
        MAP(GEN_ALL_INPUT_HIGH, INPUT_PORTS_1)
    }
#ifdef MATRIX_EXTENSION_74HC157
    setPinOutput(MATRIX_EXTENSION_74HC157);
    writePinLow(MATRIX_EXTENSION_74HC157);
#endif
}

// ALWAYS_INLINE
static void input_port_charge_1(void) {
#    if MATRIX_IO_DELAY_TYPE == FORCE_INPUT_UP_TO_VCC
    ATOMIC_BLOCK_FORCEON {
        // InputPortCharge(PORT, MASK);
        MAP(GEN_ALL_INPUT_CHARGE, INPUT_PORTS_1)
    }
#    endif
}

// ALWAYS_INLINE
static void select_output_1(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        const port_list_element_t *oports = minfo[1].oports;
        switch (row) {
            // case INDEX: writeOutputPortBunch_Low(oports[PORT_INDEX].port,PMASK); break;
            MAP_INDEX(GEN_CASE_WRITE_LOW, OUTPUT_PINS_1)
        }
    }
}

// ALWAYS_INLINE
static void unselect_output_1(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        const port_list_element_t *oports = minfo[1].oports;
        switch (row) {
            // case INDEX: writeOutputPortBunch_High_Z(oports[PORT_INDEX].port,PMASK); break;
            MAP_INDEX(GEN_CASE_WRITE_HIGH_Z, OUTPUT_PINS_1)
        }
    }
}

static void unselect_all_output_1(void) {
    ATOMIC_BLOCK_FORCEON {
        // writeOutputPortBunch_High_Z(PORT, MASK);
        MAP(GEN_ALL_WRITE_HIGHT_Z, OUTPUT_PORTS_1)
    }
}

// ALWAYS_INLINE
static void read_all_pins_1(port_data_t *buffer) {
    // buffer[INDEX] = readMatrixPort(DEV,PORT);
    MAP_INDEX(GEN_READ_PORT, INPUT_PORTS_1)
}

// ALWAYS_INLINE
static bool mask_and_adjust_pins_1(port_data_t *buffer) {
    port_data_t keypushd = 0;
    port_data_t data;

    // data = mask_and_adjust_a_port(*buffer, MASK);  keypushd |= data;  *buffer++ = data;
    MAP(GEN_ALL_MASK_ADJUST, INPUT_PORTS_1)
    return keypushd != 0;
}

static matrix_row_t build_line_1(port_data_t *buffer) {
    return 0
    //  | (buffer[PORT_INDEX] & SMASK ? DMASK : 0)
        MAP(GEN_BUILD, INPUT_PINS_1)
        ;
}
#endif // NUM_SIDE == 2

// clang-format on
//////////////// matrix.c override part ////////////////
#ifdef DEBUG_ON_TEST_BENCH
#    define matrix_init_pins x_matrix_init_pins
#    define matrix_read_cols_on_row x_matrix_read_cols_on_row
#endif

typedef void (*funcp_void_row)(uint8_t row);
typedef void (*funcp_void_void)(void);
typedef void (*funcp_void_port_data)(port_data_t *buffer);
typedef bool (*funcp_bool_port_data)(port_data_t *buffer);
typedef matrix_row_t (*funcp_build_line)(port_data_t *buffer);

const uint8_t *current_sides_opins = minfo[0].opin_enable;

#if NUM_SIDE == 2
funcp_void_void      init_all_input_pins  = init_all_input_pins_0;
funcp_void_row       select_output        = select_output_0;
funcp_void_row       unselect_output      = unselect_output_0;
funcp_void_void      unselect_all_output  = unselect_all_output_0;
funcp_void_port_data read_all_pins        = read_all_pins_0;
funcp_void_void      input_port_charge    = input_port_charge_0;
funcp_bool_port_data mask_and_adjust_pins = mask_and_adjust_pins_0;
funcp_build_line     build_line           = build_line_0;
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
    MATRIX_DEBUG_PIN_INIT();
#if NUM_SIDE == 2
    bool is_side1 = !isLeftHand;
    if (is_side1) {
        current_sides_opins  = minfo[1].opin_enable;
        init_all_input_pins  = init_all_input_pins_1;
        select_output        = select_output_1;
        unselect_output      = unselect_output_1;
        unselect_all_output  = unselect_all_output_1;
        read_all_pins        = read_all_pins_1;
        input_port_charge    = input_port_charge_1;
        mask_and_adjust_pins = mask_and_adjust_pins_1;
        build_line           = build_line_1;
    }
#endif
    unselect_all_output();
    init_all_input_pins();
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    port_data_t  port_buffer[MAX_NUM_INPUT_PORTS];
    matrix_row_t current_row_value = 0;
    bool         key_pressed;

    if (!current_sides_opins[current_row]) {
        return; // skip NO_PIN row
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
#    ifdef DEBUG_PIN_ENABLE
#        pragma message "WAIT_SPECIFIED_TIME"
#    endif
    if (key_pressed) {
        current_row_value = build_line(port_buffer);
    }
    MATRIX_DEBUG_DELAY_START();
    matrix_output_unselect_delay(current_row, key_pressed);
    MATRIX_DEBUG_DELAY_END();
#endif
#if MATRIX_IO_DELAY_TYPE == FORCE_INPUT_UP_TO_VCC
#    ifdef DEBUG_PIN_ENABLE
#        pragma message "FORCE_INPUT_UP_TO_VCC"
#    endif
    if (key_pressed) {
        MATRIX_DEBUG_DELAY_START();
        input_port_charge();
        MATRIX_DEBUG_DELAY_END();
        current_row_value = build_line(port_buffer);
    }
#endif
#if MATRIX_IO_DELAY_TYPE == ADAPTIVE_TO_INPUT
#    ifdef DEBUG_PIN_ENABLE
#        pragma message "ADAPTIVE_TO_INPUT"
#    endif
    if (key_pressed) {
        current_row_value = build_line(port_buffer);
        // wait unselect done
        MATRIX_DEBUG_DELAY_START();
        while (key_pressed) {
            MATRIX_DEBUG_DELAY_END();
            read_all_pins(port_buffer);
            key_pressed = mask_and_adjust_pins(port_buffer);
            MATRIX_DEBUG_DELAY_START();
        }
        MATRIX_DEBUG_DELAY_END();
    }
#endif
    // Update the matrix
    current_matrix[current_row] = current_row_value;
    DEBUG_PIN_OFF();
}

#ifdef DEBUG_ON_TEST_BENCH
#    pragma message "DEBUG_ON_TEST_BENCH enable"
#    include "matrix_testbench.c"
#endif
