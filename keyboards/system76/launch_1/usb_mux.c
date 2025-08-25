/*
 * Copyright (C) 2021-2022 System76
 * Copyright (C) 2021-2025 Jimmy Cassis <KernelOops@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "usb_mux.h"

#include <stdbool.h>

#include "i2c_master.h"
#include "wait.h"

// USB signal prefixes from schematic
//  - UP = USB C upstream (center)
//  - AR = USB A right side
//  - AL = USB A left side
//  - CR = USB C right side
//  - CL = USB C left side

// System76 USB Vendor ID and Product IDs from `https://github.com/system76/usb_ids'.
#define SYSTEM76_VID 0x3384
#define LAUNCH_1_PID 0x0001
#define LAUNCH_USB2_HUB_PID 0x0003
#define LAUNCH_USB3_HUB_PID 0x0004

// USB7206 is a 6-Port USB 3.1 Gen 2 controller hub.
// I2C address: 0x5A = 0x2D << 1
#define USB7206_PF1_CTL 0xBF800C04
#define USB7206_VID 0xBF803000
#define USB7206_HUB_PRT_SWAP 0xBF8030FA
#define USB7206_PIO96_OEN 0xBF800908
#define USB7206_PIO96_OUT 0xBF800928
#define USB7206_RUNTIME_FLAGS2 0xBFD23408
#define USB7206_I2S_FEAT_SEL 0xBFD23412
#define USB7206_USB3_HUB_VID 0xBFD2E548

struct USB7206 {
    uint8_t addr;
};

struct USB7206 usb_hub = {.addr = 0x2D};

// Read or write USB7206 configuration register.
// The configuration register access opcode is `0x9937'.
// Returns zero on success or a negative number on error.
i2c_status_t usb7206_register_access(struct USB7206 *self) {
    uint8_t register_access[3] = {
        0x99,
        0x37,
        0x00,
    };

    return i2c_transmit(self->addr << 1, register_access, sizeof(register_access), I2C_TIMEOUT);
}

// Read data from USB7206 register region.
// Returns number of bytes read on success or a negative number on error.
i2c_status_t usb7206_read_reg(struct USB7206 *self, uint32_t addr, uint8_t *data, int length) {
    i2c_status_t status;

    uint8_t register_read[9] = {
        0x00,                  // Buffer address MSB: always 0
        0x00,                  // Buffer address LSB: always 0
        0x06,                  // Number of bytes to write to command block buffer area
        0x01,                  // Transaction type: 0 = write, 1 = read
        (uint8_t)length,       // Number of bytes to read from register
        (uint8_t)(addr >> 24), // Register address byte 3
        (uint8_t)(addr >> 16), // Register address byte 2
        (uint8_t)(addr >> 8),  // Register address byte 1
        (uint8_t)(addr >> 0),  // Register address byte 0
    };

    status = i2c_transmit(self->addr << 1, register_read, sizeof(register_read), I2C_TIMEOUT);
    if (status < 0) {
        return status;
    }

    status = usb7206_register_access(self);
    if (status < 0) {
        return status;
    }

    uint16_t read = 0x0006; // Buffer address LSB 6 to skip header
    uint8_t data_with_buffer_length[length];
    status = i2c_read_register16(self->addr << 1, read, data_with_buffer_length, length, I2C_TIMEOUT);

    for (uint16_t i = 0; i < (length - 1) && status >= 0; i++) {
        data[i] = data_with_buffer_length[i+1];
    }

    return (status < 0) ? status : length;
}

// Read 32-bit value from USB7206 register region.
// Returns number of bytes read on success or a negative number on error.
i2c_status_t usb7206_read_reg_32(struct USB7206 *self, uint32_t addr, uint32_t *data) {
    i2c_status_t status;

    // First byte is available length
    uint8_t bytes[4] = {0, 0, 0, 0};

    status = usb7206_read_reg(self, addr, bytes, sizeof(bytes));
    if (status < 0) {
        return status;
    }

    // Convert from little endian
    *data = (((uint32_t)bytes[0]) << 0) | (((uint32_t)bytes[1]) << 8) | (((uint32_t)bytes[2]) << 16) | (((uint32_t)bytes[3]) << 24);

    return status;
}

// Write data to USB7206 register region.
// Returns number of bytes written on success or a negative number on error.
i2c_status_t usb7206_write_reg(struct USB7206 *self, uint32_t addr, uint8_t *data, int length) {
    i2c_status_t status;

    uint8_t register_write[9] = {
        0x00,                  // Buffer address MSB: always 0
        0x00,                  // Buffer address LSB: always 0
        ((uint8_t)length) + 6, // Number of bytes to write to command block buffer area
        0x00,                  // Transaction type: 0 = write, 1 = read
        (uint8_t)length,       // Number of bytes to write to register
        (uint8_t)(addr >> 24), // Register address byte 3
        (uint8_t)(addr >> 16), // Register address byte 2
        (uint8_t)(addr >> 8),  // Register address byte 1
        (uint8_t)(addr >> 0),  // Register address byte 0
    };
    uint8_t send_buffer_length = sizeof(register_write) + length;
    uint8_t send_buffer[send_buffer_length];
    uint8_t j = 0;

    for (uint16_t i = 0; i < sizeof(register_write); i++) {
        send_buffer[j++] = register_write[i];
    }

    for (uint16_t i = 0; i < length; i++) {
        send_buffer[j++] = data[i];
    }

    status = i2c_transmit((self->addr << 1), send_buffer, send_buffer_length, I2C_TIMEOUT);

    status = usb7206_register_access(self);

    return (status < 0) ? status : length;
}

// Write 8-bit value to USB7206 register region.
// Returns number of bytes written on success or a negative number on error.
i2c_status_t usb7206_write_reg_8(struct USB7206 *self, uint32_t addr, uint8_t data) {
    return usb7206_write_reg(self, addr, &data, sizeof(data));
}

// Write 32-bit value to USB7206 register region.
// Returns number of bytes written on success or a negative number on error.
i2c_status_t usb7206_write_reg_32(struct USB7206 *self, uint32_t addr, uint32_t data) {
    // Convert to little endian
    uint8_t bytes[4] = {
        (uint8_t)(data >> 0),
        (uint8_t)(data >> 8),
        (uint8_t)(data >> 16),
        (uint8_t)(data >> 24),
    };

    return usb7206_write_reg(self, addr, bytes, sizeof(bytes));
}

// Initialize USB7206.
// Returns zero on success or a negative number on error.
i2c_status_t usb7206_init(struct USB7206 *self) {
    i2c_status_t status;
    uint32_t data;

    // DM and DP are swapped on ports 2 (AR) and 3 (AL)
    // [5:0] PRT_SWAP => Swaps the upstream and downstream USB DP and DM pins for ease of board routing to devices and connectors:
    //  - '0' = USB D+ functionality is associated with the DP pin, and D– functionality is associated with the DM pin (default).
    //  - '1' = USB D+ functionality is associated with the DM pin, and D– functionality is associated with the DP pin.
    status = usb7206_write_reg_8(self, USB7206_HUB_PRT_SWAP, 0x0C);
    if (status < 0) {
        return status;
    }

    // Disable audio
    // [7:0] I2S_UNIT_SEL => Control features of the I2S interface if an I2S configuration is selected:
    //  - 0x00 = I2S is disabled.
    //  - 0x01 = Audio `IN' through microphone is enabled.
    //  - 0x02 = Audio `OUT' is enabled.
    //  - 0x03 = Both audio `IN' are enabled (default).
    status = usb7206_write_reg_8(self, USB7206_I2S_FEAT_SEL, 0x00);
    if (status < 0) {
        return status;
    }

    // Disable Hub Feature Controller (HFC)
    // [0] HFC_DISABLE:
    //  - '0': HFC is enabled (default).
    //  - '1': HFC is disabled.
    data = 0;
    status = usb7206_read_reg_32(self, USB7206_RUNTIME_FLAGS2, &data);
    if (status < 0) {
        return status;
    }
    data |= 1;
    status = usb7206_write_reg_32(self, USB7206_RUNTIME_FLAGS2, data);
    if (status < 0) {
        return status;
    }

    // Set Vendor ID and Product ID of USB 2 hub
    data = ((uint32_t)LAUNCH_USB2_HUB_PID << 16) | SYSTEM76_VID;
    status = usb7206_write_reg_32(self, USB7206_VID, data);
    if (status < 0) {
        return status;
    }

    // Set Vendor ID and Product ID of USB 3 hub
    data = ((uint32_t)LAUNCH_USB3_HUB_PID << 16) | SYSTEM76_VID;
    status = usb7206_write_reg_32(self, USB7206_USB3_HUB_VID, data);
    if (status < 0) {
        return status;
    }

    return I2C_STATUS_SUCCESS;
}

// Attach USB7206 (exit `SOC_CONFIG' and enter `HUB_CONFIG' stage).
// The USB attach opcode is `0xAA55'.
// Returns zero on success or a negative number on error.
i2c_status_t usb7206_attach(struct USB7206 *self) {
    uint8_t data[3] = {
        0xAA,
        0x56,
        0x00,
    };

    return i2c_transmit(self->addr << 1, data, sizeof(data), I2C_TIMEOUT);
}

struct USB7206_GPIO {
    struct USB7206 *usb7206;
    uint32_t pf;
};

struct USB7206_GPIO usb_gpio_sink         = {.usb7206 = &usb_hub, .pf = 29}; // UP_SEL = PF29 = GPIO93 (93 = 64 + 29)
struct USB7206_GPIO usb_gpio_source_left  = {.usb7206 = &usb_hub, .pf = 10}; // CL_SEL = PF10 = GPIO74 (74 = 64 + 10)
struct USB7206_GPIO usb_gpio_source_right = {.usb7206 = &usb_hub, .pf = 25}; // CR_SEL = PF25 = GPIO89 (89 = 64 + 25)

// Set USB7206 GPIO to specified value.
// Returns zero on success or negative number on error.
i2c_status_t usb7206_gpio_set(struct USB7206_GPIO *self, bool value) {
    i2c_status_t status;
    uint32_t data;

    // Set GPIO output value
    // PIO[96:64] OUTPUT REGISTER => PIO96_OUT[x]:
    //  - '0' = Output is `0'.
    //  - '1' = Output is `1'.
    data = 0;
    status = usb7206_read_reg_32(self->usb7206, USB7206_PIO96_OUT, &data);
    if (status < 0) {
        return status;
    }

    if (value) {
        data |= (((uint32_t)1) << self->pf);
    } else {
        data &= ~(((uint32_t)1) << self->pf);
    }
    status = usb7206_write_reg_32(self->usb7206, USB7206_PIO96_OUT, data);
    if (status < 0) {
        return status;
    }

    return I2C_STATUS_SUCCESS;
}

// Initialize USB7206 GPIO.
// Returns zero on success or a negative number on error.
i2c_status_t usb7206_gpio_init(struct USB7206_GPIO *self) {
    i2c_status_t status;
    uint32_t data;

    // Set programmable function to GPIO
    status = usb7206_write_reg_8(self->usb7206, USB7206_PF1_CTL + (self->pf - 1), 0x00);
    if (status < 0) {
        return status;
    }

    // Set GPIO to false by default
    usb7206_gpio_set(self, false);

    // Set GPIO to output
    // PIO[96:64] OUTPUT ENABLE REGISTER => PIO96_OEN[x]:
    //  - '0' = Disabled.
    //  - '1' = Enabled.
    data = 0;
    status = usb7206_read_reg_32(self->usb7206, USB7206_PIO96_OEN, &data);
    if (status < 0) {
        return status;
    }

    data |= (((uint32_t)1) << self->pf);
    status = usb7206_write_reg_32(self->usb7206, USB7206_PIO96_OEN, data);
    if (status < 0) {
        return status;
    }

    return I2C_STATUS_SUCCESS;
}

// PTN5110N is a 1-port Type-C Port controller (TCPC) supporting TCPC Rev 1.0 version 1.1.
#define PTN5110_ROLE_CTRL 0x1A
#define PTN5110_ROLE_CTRL_RP_VAL_SHIFT 4
#define PTN5110_ROLE_CTRL_RP_VAL_DEF 0x0
#define PTN5110_ROLE_CTRL_CC2_SHIFT 2
#define PTN5110_ROLE_CTRL_CC1_SHIFT 0
#define PTN5110_ROLE_CTRL_CC_RP 0x1
#define PTN5110_CC_STATUS 0x1D
#define PTN5110_CC_STATUS_CC2_SHIFT 2
#define PTN5110_CC_STATUS_CC2_MASK 0x3
#define PTN5110_CC_STATUS_CC1_SHIFT 0
#define PTN5110_CC_STATUS_CC1_MASK 0x3
#define PTN5110_CC_STATE_SNK_OPEN 0
#define PTN5110_CC_STATE_SRC_RD 2
#define PTN5110_COMMAND 0x23
#define PTN5110_CMD_SRC_VBUS_DEFAULT 0x77 // 0b01110111
#define PTN5110_CMD_DISABLE_SRC_VBUS 0x66 // 0b01100110

enum TCPC_TYPE {
    TCPC_TYPE_SINK,
    TCPC_TYPE_SOURCE,
};

struct PTN5110 {
    enum TCPC_TYPE type;
    uint8_t addr;
    uint8_t cc;
    struct USB7206_GPIO *gpio;
};

// USB C upstream port controller (PTN5110DHQ)
//  - Configured for Upstream Facing Port (UFP)/Sink role at Power On or Reset (POR).
//  - The CC1/2 pins present sink (Rd) role.
//  - I2C address: 0xA2 (0b1010001x) = 0x51 << 1
// USB C left port controller (PTN5110THQ)
//  - Configured for Downstream Facing Port (DFP)/Source role at Power On or Reset (POR).
//  - I2C address: 0xA4 (0b1010010x) = 0x52 << 1
// USB C right port controller (PTN5110THQ)
//  - Configured for  Downstream Facing Port (DFP)/Source role at Power On or Reset (POR).
//  - I2C address: 0xA0 (0b1010000x) = 0x50 << 1
struct PTN5110 usb_sink         = {.type = TCPC_TYPE_SINK,   .addr = 0x51, .gpio = &usb_gpio_sink};
struct PTN5110 usb_source_left  = {.type = TCPC_TYPE_SOURCE, .addr = 0x52, .gpio = &usb_gpio_source_left};
struct PTN5110 usb_source_right = {.type = TCPC_TYPE_SOURCE, .addr = 0x50, .gpio = &usb_gpio_source_right};

// Write PTN5110 ROLE_CONTROL.
// Returns zero on success or a negative number on error.
int ptn5110_set_role_control(struct PTN5110 *self, uint8_t role_control) {
    return i2c_write_register(self->addr << 1, PTN5110_ROLE_CTRL, &role_control, 1, I2C_TIMEOUT);
}

// Read PTN5110 CC_STATUS.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_get_cc_status(struct PTN5110 *self, uint8_t *cc) {
    return i2c_read_register(self->addr << 1, PTN5110_CC_STATUS, cc, 1, I2C_TIMEOUT);
}

// Set PTN5110 SSMUX orientation.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_set_ssmux(struct PTN5110 *self, bool orientation) {
    return usb7206_gpio_set(self->gpio, orientation);
}

// Write PTN5110 COMMAND.
// Returns zero on success or negative number on error.
i2c_status_t ptn5110_command(struct PTN5110 *self, uint8_t command) {
    return i2c_write_register(self->addr << 1, PTN5110_COMMAND, &command, 1, I2C_TIMEOUT);
}

// Set orientation of PTN5110 operating as a sink, call this once.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_sink_set_orientation(struct PTN5110 *self) {
    i2c_status_t status;
    uint8_t cc;

    status = ptn5110_get_cc_status(self, &cc);
    if (status < 0) {
        return status;
    }

    // PTN5110N in UFP and therefore ROLE_CONTROL.CC1 = Rd
    if (((cc >> PTN5110_CC_STATUS_CC1_SHIFT) & PTN5110_CC_STATUS_CC1_MASK) == PTN5110_CC_STATE_SNK_OPEN) {
        // CC_STATUS[1:0] CC1 State:
        //  - 0b00 = SNK_Open (Below maximum vRa)
        status = ptn5110_set_ssmux(self, false);
        if (status < 0) {
            return status;
        }
    } else {
        // CC_STATUS[1:0] CC1 State:
        //  - 0b01 = SNK_Default (Above minimum vRd-Connect)
        //  - 0b10 = SNK_Power1_5 (Above minimum vRd-Connect) Detects Rp-1.5A
        //  - 0b11 = SNK_Power3_0 (Above minimum vRd-Connect) Detects Rp-3.0A
        status = ptn5110_set_ssmux(self, true);
        if (status < 0) {
            return status;
        }
    }

    return I2C_STATUS_SUCCESS;
}

// Update PTN5110 operating as a source, call this repeatedly.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_source_update(struct PTN5110 *self) {
    i2c_status_t status;
    uint8_t cc;

    status = ptn5110_get_cc_status(self, &cc);
    if (status < 0) {
        return status;
    }

    if (cc != self->cc) {
        self->cc = cc; // WARNING: Setting this here will disable retries

        bool connected = false;
        bool orientation = false;

        // PTN5110N in DFP and therefore ROLE_CONTROL.CC1 = Rp and ROLE_CONTROL.CC2 = Rp
        if (((cc >> PTN5110_CC_STATUS_CC1_SHIFT) & PTN5110_CC_STATUS_CC1_MASK) == PTN5110_CC_STATE_SRC_RD) {
            // CC_STATUS[1:0] CC1 State:
            //  - 0b10 = SRC_Rd (within the vRd range)
            connected = true;
            orientation = true;
        } else if (((cc >> PTN5110_CC_STATUS_CC2_SHIFT) & PTN5110_CC_STATUS_CC2_MASK) == PTN5110_CC_STATE_SRC_RD) {
            // CC_STATUS[1:0] CC2 State:
            //  - 0b10 = SRC_Rd (within the vRd range)
            connected = true;
            orientation = false;
        }

        if (connected) {
            // Set SS multiplexer orientation
            status = ptn5110_set_ssmux(self, orientation);
            if (status < 0) {
                return status;
            }

            // Enable source Vbus command
            //  - 0b01110111: SourceVbusDefaultVoltage => Enable sourcing vSafe5V over Vbus and enable Vbus present detection.
            status = ptn5110_command(self, PTN5110_CMD_SRC_VBUS_DEFAULT);
            if (status < 0) {
                return status;
            }
        } else {
            // Disable source Vbus command
            //  - 0b01100110: DisableSourceVbus => Disable sourcing power over Vbus.
            status = ptn5110_command(self, PTN5110_CMD_DISABLE_SRC_VBUS);
            if (status < 0) {
                return status;
            }
        }
    }

    return I2C_STATUS_SUCCESS;
}

// Initialize PTN5110.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_init(struct PTN5110 *self) {
    i2c_status_t status;
    uint8_t reg;

    self->cc = 0xFF; // Set last cc to invalid value, to force update

    // Initialize GPIO
    status = usb7206_gpio_init(self->gpio);
    if (status < 0) {
        return status;
    }

    switch (self->type) {
        case TCPC_TYPE_SINK:
            // UFP Initialization
            status = ptn5110_sink_set_orientation(self);
            break;
        case TCPC_TYPE_SOURCE:
            // DFP Initialization
            // [6] DRP: 0b0 = No DRP.
            // [5:4] Rp Value: 0b00 = Rp default.
            // [3:2] CC2: 0b01 = Rp definition from [5:4].
            // [1:0] CC1: 0b01 = Rp definition from [5:4].
            reg = (PTN5110_ROLE_CTRL_RP_VAL_DEF << PTN5110_ROLE_CTRL_RP_VAL_SHIFT) |
                  (PTN5110_ROLE_CTRL_CC_RP << PTN5110_ROLE_CTRL_CC2_SHIFT) |
                  (PTN5110_ROLE_CTRL_CC_RP << PTN5110_ROLE_CTRL_CC1_SHIFT); // 0x05
            status = ptn5110_set_role_control(self, reg);
            break;
    }

    return (status < 0) ? status : I2C_STATUS_SUCCESS;
}

// The interrupt pin is not wired due to lack of pins on the AVR.
// The TCPCs will need to be periodically polled.
void usb_mux_event(void) {
    // `tVbusOFF' in the USB C spec is 650 ms which sets the maximum
    // polling interval so run every 1000th matrix scan
    static int cycle = 0;
    if (cycle >= 1000) {
        cycle = 0;
        ptn5110_source_update(&usb_source_left);
        ptn5110_source_update(&usb_source_right);
    } else {
        cycle += 1;
    }
}

void usb_mux_init(void) {
    // Run I2C bus at 100 kHz
    i2c_init();

    // Set up hub
    // I2C pullups are present on the board, so the hub will wait in `SOC_CFG'
    // (allowing for external configuration) until it receives the "Attach" command
    // and becomes active
    usb7206_init(&usb_hub);

    // Set up sink and the upstream SS multiplexer first
    ptn5110_init(&usb_sink);

    // Set up sources and the downstream SS multiplexers
    ptn5110_init(&usb_source_left);
    ptn5110_init(&usb_source_right);

    // Attach hub
    usb7206_attach(&usb_hub);

    // Ensure orientation is correct after attaching hub
    // TODO: Find reason why GPIO for sink orientation is reset
    for (int i = 0; i < 100; i++) {
        ptn5110_sink_set_orientation(&usb_sink);
        wait_ms(10);
    }
}
