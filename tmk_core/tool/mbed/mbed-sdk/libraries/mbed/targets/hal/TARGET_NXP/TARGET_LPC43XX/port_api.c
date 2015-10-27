/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Ported to NXP LPC43XX by Micromint USA <support@micromint.com>
 */
#include "mbed_assert.h"
#include "port_api.h"
#include "pinmap.h"
#include "gpio_api.h"

// Lookup table to determine SCU offset for GPIO [port][pin]
// Supports eight 16-bit ports to limit table size
#define _SO(MBED_PIN)            (MBED_PIN >> 18)

static const uint8_t _scu_off[][16] =
{   // GPIO0 to GPIO3
    { _SO(GPIO0_0),  _SO(GPIO0_1),  _SO(GPIO0_2),  _SO(GPIO0_3),
      _SO(GPIO0_4),  _SO(GPIO0_5),  _SO(GPIO0_6),  _SO(GPIO0_7),
      _SO(GPIO0_8),  _SO(GPIO0_9),  _SO(GPIO0_10), _SO(GPIO0_11),
      _SO(GPIO0_12), _SO(GPIO0_13), _SO(GPIO0_14), _SO(GPIO0_15)
    },
    { _SO(GPIO1_0),  _SO(GPIO1_1),  _SO(GPIO1_2),  _SO(GPIO1_3),
      _SO(GPIO1_4),  _SO(GPIO1_5),  _SO(GPIO1_6),  _SO(GPIO1_7),
      _SO(GPIO1_8),  _SO(GPIO1_9),  _SO(GPIO1_10), _SO(GPIO1_11),
      _SO(GPIO1_12), _SO(GPIO1_13), _SO(GPIO1_14), _SO(GPIO1_15)
    },
    { _SO(GPIO2_0),  _SO(GPIO2_1),  _SO(GPIO2_2),  _SO(GPIO2_3),
      _SO(GPIO2_4),  _SO(GPIO2_5),  _SO(GPIO2_6),  _SO(GPIO2_7),
      _SO(GPIO2_8),  _SO(GPIO2_9),  _SO(GPIO2_10), _SO(GPIO2_11),
      _SO(GPIO2_12), _SO(GPIO2_13), _SO(GPIO2_14), _SO(GPIO2_15)
    },
    { _SO(GPIO3_0),  _SO(GPIO3_1),  _SO(GPIO3_2),  _SO(GPIO3_3),
      _SO(GPIO3_4),  _SO(GPIO3_5),  _SO(GPIO3_6),  _SO(GPIO3_7),
      _SO(GPIO3_8),  _SO(GPIO3_9),  _SO(GPIO3_10), _SO(GPIO3_11),
      _SO(GPIO3_12), _SO(GPIO3_13), _SO(GPIO3_14), _SO(GPIO3_15)
    },
};

// Use alternate encoding for ports 4 to 7 so lookup stays within uint8
#define _S2(MBED_PIN)            (((MBED_PIN >> 19) & 0xf0) | ((MBED_PIN >> 18) & 0x0f))

static const uint8_t _scu_off2[][16] = 
{   // GPIO4 to GPIO7
    { _S2(GPIO4_0),  _S2(GPIO4_1),  _S2(GPIO4_2),  _S2(GPIO4_3),
      _S2(GPIO4_4),  _S2(GPIO4_5),  _S2(GPIO4_6),  _S2(GPIO4_7),
      _S2(GPIO4_8),  _S2(GPIO4_9),  _S2(GPIO4_10), _S2(GPIO4_11),
      _S2(GPIO4_12), _S2(GPIO4_13), _S2(GPIO4_14), _S2(GPIO4_15)
    },
    { _S2(GPIO5_0),  _S2(GPIO5_1),  _S2(GPIO5_2),  _S2(GPIO5_3),
      _S2(GPIO5_4),  _S2(GPIO5_5),  _S2(GPIO5_6),  _S2(GPIO5_7),
      _S2(GPIO5_8),  _S2(GPIO5_9),  _S2(GPIO5_10), _S2(GPIO5_11),
      _S2(GPIO5_12), _S2(GPIO5_13), _S2(GPIO5_14), _S2(GPIO5_15)
    },
    { _S2(GPIO6_0),  _S2(GPIO6_1),  _S2(GPIO6_2),  _S2(GPIO6_3),
      _S2(GPIO6_4),  _S2(GPIO6_5),  _S2(GPIO6_6),  _S2(GPIO6_7),
      _S2(GPIO6_8),  _S2(GPIO6_9),  _S2(GPIO6_10), _S2(GPIO6_11),
      _S2(GPIO6_12), _S2(GPIO6_13), _S2(GPIO6_14), _S2(GPIO6_15)
    },
    { _S2(GPIO7_0),  _S2(GPIO7_1),  _S2(GPIO7_2),  _S2(GPIO7_3),
      _S2(GPIO7_4),  _S2(GPIO7_5),  _S2(GPIO7_6),  _S2(GPIO7_7),
      _S2(GPIO7_8),  _S2(GPIO7_9),  _S2(GPIO7_10), _S2(GPIO7_11),
      _S2(GPIO7_12), _S2(GPIO7_13), _S2(GPIO7_14), _S2(GPIO7_15)
    },
};

PinName port_pin(PortName port, int pin_n) {
    MBED_ASSERT((port <= Port7) && (pin_n < 32));
    int offset = 0;

    // Lookup table only maps pins 0 to 15
    if (pin_n > 15) {
        return NC;
    }

    // Lookup SCU offset
    if (port < Port4) {
        offset = _scu_off[port][pin_n];
    } else {
        offset = _scu_off2[port - Port4][pin_n];
        offset = ((offset & 0xf0) << 1) | (offset & 0x0f);
    }

    // Return pin name
    return (PinName)((offset << 18) | GPIO_OFF(port, pin_n));
}

void port_init(port_t *obj, PortName port, int mask, PinDirection dir) {
    obj->port = port;
    obj->mask = mask;
    
    LPC_GPIO_T *port_reg = (LPC_GPIO_T *)(LPC_GPIO_PORT_BASE);
    
    // Do not use masking, because it prevents the use of the unmasked pins
    // port_reg->MASK[port] = ~mask;
    
    obj->reg_out = &port_reg->PIN[port];
    obj->reg_in  = &port_reg->PIN[port];
    obj->reg_dir = &port_reg->DIR[port];
	
    uint32_t i;
    // The function is set per pin: reuse gpio logic
    for (i=0; i<32; i++) {
        if (obj->mask & (1<<i)) {
            gpio_set(port_pin(obj->port, i));
        }
    }

    port_dir(obj, dir);
}

void port_mode(port_t *obj, PinMode mode) {
    uint32_t i;
    // The mode is set per pin: reuse pinmap logic
    for (i=0; i<32; i++) {
        if (obj->mask & (1<<i)) {
            pin_mode(port_pin(obj->port, i), mode);
        }
    }
}

void port_dir(port_t *obj, PinDirection dir) {
    switch (dir) {
        case PIN_INPUT : *obj->reg_dir &= ~obj->mask; break;
        case PIN_OUTPUT: *obj->reg_dir |=  obj->mask; break;
    }
}

void port_write(port_t *obj, int value) {
    *obj->reg_out = (*obj->reg_in & ~obj->mask) | (value & obj->mask);
}

int port_read(port_t *obj) {
    return (*obj->reg_in & obj->mask);
}
