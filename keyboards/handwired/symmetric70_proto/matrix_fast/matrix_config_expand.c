/*
Copyright 2021 mtei

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
// clang-format off

#include "matrix_extr.h"

#ifdef DEBUG_MATRIX_CONFIG
// config expand debug
//   avr-gcc -DDEBUG_MATRIX_CONFIG=\"test_config.h\" -E -C matrix_config_expand.c
#    include DEBUG_MATRIX_CONFIG
#endif

#undef NO_PIN /* cancel NO_PIN define in tmk_core/common/pin_defs.h */
#define NO_PIN  NO_PORT, 0
#if MATRIX_TYPE == DIRECT_SWITCH
#    undef MATRIX_OUT_PORTS
#    define MATRIX_OUT_PINS  (0, NO_PIN)
#endif

#include "cpp_map.h"

#if defined(MATRIX_EXTENSION_74HC157) || defined(MATRIX_EXTENSION_74HC153)
#   define  MATRIX_EXTENSION "matrix_extension_74hc15x.c"
#endif

#ifdef MATRIX_EXTENSION
#    include MATRIX_EXTENSION
#endif

#ifdef MATRIX_GPIO_NEED_SEPARATE_ATOMIC
#    ifndef setMatrixInputHigh
#        define setMatrixInputHigh(dev, port, bit) do { if ((dev) == MCU_GPIO) { setPortBitInputHigh_atomic(port, bit); }} while(0)
#    endif
#    ifndef setMatrixOutput_writeHighZ
#        define setMatrixOutput_writeHighZ(dev, port, bit) do { if ((dev) == MCU_GPIO) { setPortBitInputHigh_atomic(port, bit); }} while(0)
#    endif
#    ifndef setMatrixOutput_writeLow
#        define setMatrixOutput_writeLow(dev, port, bit) do { if ((dev) == MCU_GPIO) { setPortBitOutput_writeLow_atomic(port, bit); }} while(0)
#    endif
#else
#    ifndef setMatrixInputHigh
#        define setMatrixInputHigh(dev, port, bit) do { if ((dev) == MCU_GPIO) { setPortBitInputHigh(port, bit); }} while(0)
#    endif
#    ifndef setMatrixOutput_writeHighZ
#        define setMatrixOutput_writeHighZ(dev, port, bit) do { if ((dev) == MCU_GPIO) { setPortBitInputHigh(port, bit); }} while(0)
#    endif
#    ifndef setMatrixOutput_writeLow
#        define setMatrixOutput_writeLow(dev, port, bit) do { if ((dev) == MCU_GPIO) { setPortBitOutput_writeLow(port, bit); }} while(0)
#    endif
#endif

#ifndef readMatrixPort
#    define readMatrixPort(dev, port) (((dev) == MCU_GPIO) ? readPort(port) : 0)
#endif
#ifndef getMatrixInputMaskBit
#    define getMatrixInputMaskBit(dev, bit) (((dev) != NO_DEVICE) ? _BV((bit)&0xF) : 0)
#endif

#ifndef init_extension
#    define init_extension()
#endif

enum DEVICE_NAME {
    MCU_GPIO,
    NO_DEVICE,
#ifdef MATRIX_DEVICES
    MATRIX_DEVICES
#endif
};

#define _INPUT_PORTS_ENUM_ELEMENT(name, dev, port) inport_index_##name,
#define INPUT_PORTS_ENUM_ELEMENT(x) _INPUT_PORTS_ENUM_ELEMENT x
enum INPUT_PORTS {
    INPUT_PORTS_ENUM_ELEMENT((NO_PORT, NO_DEVICE, 0))
    MAP(INPUT_PORTS_ENUM_ELEMENT, MATRIX_IN_PORTS)
    NUM_OF_INPUT_PORTS
};

#define _INPUT_PINS_ENUM_ELEMENT(index, port, bit) inpin_index_##index,
#define INPUT_PINS_ENUM_ELEMENT(x) _INPUT_PINS_ENUM_ELEMENT x
enum INPUT_PINS {
    MAP(INPUT_PINS_ENUM_ELEMENT, MATRIX_IN_PINS)
    END_inpin_index
};

#define _OUTPUT_PORTS_ENUM_ELEMENT(name, dev, port) outport_index_##name,
#define OUTPUT_PORTS_ENUM_ELEMENT(x) _OUTPUT_PORTS_ENUM_ELEMENT x
enum OUTPUT_PORTS {
    OUTPUT_PORTS_ENUM_ELEMENT((NO_PORT, NO_DEVICE, 0))
#ifdef MATRIX_OUT_PORTS
    MAP(OUTPUT_PORTS_ENUM_ELEMENT, MATRIX_OUT_PORTS)
#endif
    NUM_OF_OUTPUT_PORTS
};

#define _OUTPUT_PINS_ENUM_ELEMENT(index, port, bit) outpin_index_##index,
#define OUTPUT_PINS_ENUM_ELEMENT(x) _OUTPUT_PINS_ENUM_ELEMENT x
enum OUTPUT_PINS {
    MAP(OUTPUT_PINS_ENUM_ELEMENT, MATRIX_OUT_PINS)
    END_outpin_index
};

port_width_t iport_mask[NUM_OF_INPUT_PORTS];

#define _INPUT_PORTS_LIST_ELEMENT(name, dev, port) \
    [inport_index_##name] = { dev, port },
#define INPUT_PORTS_LIST_ELEMENT(x) _INPUT_PORTS_LIST_ELEMENT x
LOCAL_DATA
const port_descriptor inport_list[NUM_OF_INPUT_PORTS] = {
    INPUT_PORTS_LIST_ELEMENT((NO_PORT, NO_DEVICE, 0))
    MAP(INPUT_PORTS_LIST_ELEMENT, MATRIX_IN_PORTS)
};

#define _OUTPUT_PORTS_LIST_ELEMENT(name, dev, port) \
    [outport_index_##name] = { dev, port },
#define OUTPUT_PORTS_LIST_ELEMENT(x) _OUTPUT_PORTS_LIST_ELEMENT x
LOCAL_DATA
const port_descriptor outport_list[NUM_OF_OUTPUT_PORTS] = {
    OUTPUT_PORTS_LIST_ELEMENT((NO_PORT, NO_DEVICE, 0))
#ifdef MATRIX_OUT_PORTS
    MAP(OUTPUT_PORTS_LIST_ELEMENT, MATRIX_OUT_PORTS)
#endif
};

#define _SELECT_OUTPUT_PIN(index, pname, bit) \
    case outpin_index_##index: \
        setMatrixOutput_writeLow(outport_list[outport_index_##pname].device,     \
                                 outport_list[outport_index_##pname].port, bit); \
    break;
#define SELECT_OUTPUT_PIN(x) _SELECT_OUTPUT_PIN x
LOCAL_FUNC ALWAYS_INLINE void select_output(uint8_t out_index);
LOCAL_FUNC
void select_output(uint8_t out_index) {
    switch (out_index) {
        MAP(SELECT_OUTPUT_PIN, MATRIX_OUT_PINS)
    }
}

#define _UNSELECT_OUTPUT_PIN(index, pname, bit) \
    case outpin_index_##index: \
        setMatrixOutput_writeHighZ(outport_list[outport_index_##pname].device,     \
                                   outport_list[outport_index_##pname].port, bit); \
    break;
#define UNSELECT_OUTPUT_PIN(x) _UNSELECT_OUTPUT_PIN x
LOCAL_FUNC ALWAYS_INLINE void unselect_output_inline(uint8_t out_index);
LOCAL_FUNC
void unselect_output_inline(uint8_t out_index) {
    switch (out_index) {
        MAP(UNSELECT_OUTPUT_PIN, MATRIX_OUT_PINS)
    }
}

#define _INIT_INPUT_PIN(index, pname, bit) \
    setMatrixInputHigh(inport_list[inport_index_##pname].device,    \
                       inport_list[inport_index_##pname].port, bit);
#define INIT_INPUT_PIN(x) _INIT_INPUT_PIN x
LOCAL_FUNC
void init_input_ports(void) {
    MAP(INIT_INPUT_PIN, MATRIX_IN_PINS)
}

#define _INIT_INPORT_MASK(index, pname, bit) \
    iport_mask[inport_index_##pname] |= getMatrixInputMaskBit(inport_list[inport_index_##pname].device, bit);
#define INIT_INPORT_MASK(x)  _INIT_INPORT_MASK x
LOCAL_FUNC
void init_inport_mask(void) {
    for (int i = 0; i < NUM_OF_INPUT_PORTS; i++ ) {
        iport_mask[i] = 0;
    }
    MAP(INIT_INPORT_MASK, MATRIX_IN_PINS)
}

#define _READ_INPUT_PORT(name, dev, port) \
    buffer[inport_index_##name] = readMatrixPort(dev, port);
#define READ_INPUT_PORT(x) _READ_INPUT_PORT x
LOCAL_FUNC
ALWAYS_INLINE void read_all_input_ports(port_width_t buffer[NUM_OF_INPUT_PORTS], bool wait_unselect);
LOCAL_FUNC
void read_all_input_ports(port_width_t buffer[NUM_OF_INPUT_PORTS], bool wait_unselect) {
    READ_INPUT_PORT((NO_PORT, NO_DEVICE, 0))
    MAP(READ_INPUT_PORT, MATRIX_IN_PORTS)
}

#define _MASK_INPUT(name, dev, port) \
    mask |= ((~buffer[inport_index_##name]) & iport_mask[inport_index_##name]);
#define MASK_INPUT(x) _MASK_INPUT x
LOCAL_FUNC ALWAYS_INLINE void wait_unselect_done(void);
LOCAL_FUNC
void wait_unselect_done(void) {
    port_width_t mask;
    port_width_t buffer[NUM_OF_INPUT_PORTS];
    do {
        read_all_input_ports(buffer, true);
        MATRIX_DEBUG_DELAY_END();
        mask = 0;
        MAP(MASK_INPUT, MATRIX_IN_PORTS);
        MATRIX_DEBUG_DELAY_START();
    } while (mask != 0);
}

#define _BUILD_INPUT_PORT(index, pname, bit) \
    result |= (buffer[inport_index_##pname] & _BV(bit)) ? 0 : _BV(inpin_index_##index);
#define BUILD_INPUT_PORT(x) _BUILD_INPUT_PORT x
LOCAL_FUNC ALWAYS_INLINE matrix_line_t build_matrix_line(port_width_t buffer[NUM_OF_INPUT_PORTS]);
LOCAL_FUNC
matrix_line_t build_matrix_line(port_width_t buffer[NUM_OF_INPUT_PORTS]) {
    matrix_line_t result = 0;
    MAP(BUILD_INPUT_PORT, MATRIX_IN_PINS);
    return result;
}

#define _BUILD_INPUT_PORT_DIRECT(index, pname, bit) \
    matrix[(inpin_index_##index)/MATRIX_COLS] \
        |= (buffer[inport_index_##pname] & _BV(bit)) ? 0 : _BV((inpin_index_##index)%MATRIX_COLS);
#define BUILD_INPUT_PORT_DIRECT(x) _BUILD_INPUT_PORT_DIRECT x
LOCAL_FUNC ALWAYS_INLINE void build_matrix_direct(port_width_t buffer[NUM_OF_INPUT_PORTS], matrix_line_t matrix[]);
LOCAL_FUNC
void build_matrix_direct(port_width_t buffer[NUM_OF_INPUT_PORTS], matrix_line_t matrix[]) {
    MAP(BUILD_INPUT_PORT_DIRECT, MATRIX_IN_PINS);
}
