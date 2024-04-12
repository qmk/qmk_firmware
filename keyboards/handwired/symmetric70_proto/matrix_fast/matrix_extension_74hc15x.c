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

#include "atomic_util.h"
#include "gpio.h"
#include "wait.h"

#if defined(MATRIX_EXTENSION_74HC157)
#    define MATRIX_DEVICES MCU_GPIOa, MCU_GPIOb
#    define IS_74HC15x(dev) ((dev)==MCU_GPIOa || (dev)==MCU_GPIOb)
#    define MATRIX_EXT_74HC15x MATRIX_EXTENSION_74HC157
#elif defined(MATRIX_EXTENSION_74HC153)
#    define MATRIX_DEVICES MCU_GPIOa, MCU_GPIOb, MCU_GPIOc, MCU_GPIOd
#    define IS_74HC15x(dev) ((dev)==MCU_GPIOa || (dev)==MCU_GPIOb || (dev)==MCU_GPIOc || (dev)==MCU_GPIOd)
#    define MATRIX_EXT_74HC15x MATRIX_EXTENSION_74HC153
#endif

static const pin_t sel_pins[] = { MATRIX_EXT_74HC15x };

#ifdef MATRIX_GPIO_NEED_SEPARATE_ATOMIC
#    define setMatrixInputHigh(dev, port, bit) \
    do {                                            \
        if ((dev) == MCU_GPIO || IS_74HC15x(dev)) { \
            setPortBitInputHigh_atomic(port, bit);  \
        }
    } while(0)
#else
#    define setMatrixInputHigh(dev, port, bit) \
    do {                                            \
        if ((dev) == MCU_GPIO || IS_74HC15x(dev)) { \
            setPortBitInputHigh(port, bit);         \
        }                                           \
    } while(0)
#endif

LOCAL_FUNC ALWAYS_INLINE void select74HC15x(uint8_t devid);
LOCAL_FUNC
void select74HC15x(uint8_t devid) {
    writePin(sel_pins[0], devid&1);
#if defined(MATRIX_EXTENSION_74HC153)
    writePin(sel_pins[1], devid&2);
#endif
}

LOCAL_FUNC ALWAYS_INLINE port_width_t readPortMultiplexer(uint8_t devid, pin_t port);
LOCAL_FUNC port_width_t readPortMultiplexer(uint8_t devid, pin_t port) {
    select74HC15x(devid);
    waitInputPinDelay();
    return readPort(port);
}

#define readMatrixPort(dev, port) \
    ((dev) == MCU_GPIO)? readPort(port): (IS_74HC15x(dev))? readPortMultiplexer((dev)-MCU_GPIOa, port):0

#define INIT_74HC15X(x) setPinOutput(x); writePinLow(x);
LOCAL_FUNC
void init_74hc15x(void) {
    MAP(INIT_74HC15X, MATRIX_EXT_74HC15x)
}
#define init_extension() init_74hc15x()

