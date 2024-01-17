/*
 *  Copyright (C) 2021  System76
 *  Copyright (C) 2021  Jimmy Cassis <KernelOops@outlook.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "usb_mux.h"

#include <stdbool.h>

#include "i2c_master.h"
#include "wait.h"

#define REG_PF1_CTL 0xBF800C04
#define REG_PIO64_OEN 0xBF800908
#define REG_PIO64_OUT 0xBF800928
#define REG_VID 0xBF803000
#define REG_PRT_SWAP 0xBF8030FA
#define REG_USB3_HUB_VID 0xBFD2E548
#define REG_RUNTIME_FLAGS2 0xBFD23408
#define REG_I2S_FEAT_SEL 0xBFD23412

struct USB7206 {
    uint8_t addr;
};

struct USB7206 usb_hub = {.addr = 0x2D};

// Perform USB7206 register access.
// Returns zero on success or a negative number on error.
i2c_status_t usb7206_register_access(struct USB7206* self) {
    uint8_t register_access[3] = {
        0x99,
        0x37,
        0x00,
    };

    return i2c_transmit(self->addr << 1, register_access, sizeof(register_access), I2C_TIMEOUT);
}

// Read data from USB7206 register region.
// Returns number of bytes read on success or a negative number on error.
i2c_status_t usb7206_read_reg(struct USB7206* self, uint32_t addr, uint8_t* data, int length) {
    i2c_status_t status;

    uint8_t register_read[9] = {
        0x00,                   // Buffer address MSB: always 0
        0x00,                   // Buffer address LSB: always 0
        0x06,                   // Number of bytes to write to command block buffer area
        0x01,                   // Direction: 0 = write, 1 = read
        (uint8_t)length,        // Number of bytes to read from register
        (uint8_t)(addr >> 24),  // Register address byte 3
        (uint8_t)(addr >> 16),  // Register address byte 2
        (uint8_t)(addr >> 8),   // Register address byte 1
        (uint8_t)(addr >> 0),   // Register address byte 0
    };

    status = i2c_transmit(self->addr << 1, register_read, sizeof(register_read), I2C_TIMEOUT);
    if (status < 0) {
        return status;
    }

    status = usb7206_register_access(self);
    if (status < 0) {
        return status;
    }

    uint8_t read[2] = {
        0x00,  // Buffer address MSB: always 0
        0x06,  // Buffer address LSB: 6 to skip header
    };

    status = i2c_start((self->addr << 1) | I2C_WRITE, I2C_TIMEOUT);
    if (status >= 0) {
        for (uint16_t i = 0; i < sizeof(read); i++) {
            status = i2c_write(read[i], I2C_TIMEOUT);
            if (status < 0) {
                goto error;
            }
        }
    } else {
        goto error;
    }

    status = i2c_start((self->addr << 1) | I2C_READ, I2C_TIMEOUT);
    if (status < 0) {
        goto error;
    }

    // Read and ignore buffer length
    status = i2c_read_ack(I2C_TIMEOUT);
    if (status < 0) {
        goto error;
    }

    for (uint16_t i = 0; i < (length - 1) && status >= 0; i++) {
        status = i2c_read_ack(I2C_TIMEOUT);
        if (status >= 0) {
            data[i] = (uint8_t)status;
        }
    }

    if (status >= 0) {
        status = i2c_read_nack(I2C_TIMEOUT);
        if (status >= 0) {
            data[(length - 1)] = (uint8_t)status;
        }
    }

error:
    i2c_stop();

    return (status < 0) ? status : length;
}

// Read 32-bit value from USB7206 register region.
// Returns number of bytes read on success or a negative number on error.
i2c_status_t usb7206_read_reg_32(struct USB7206* self, uint32_t addr, uint32_t* data) {
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
i2c_status_t usb7206_write_reg(struct USB7206* self, uint32_t addr, uint8_t* data, int length) {
    i2c_status_t status;

    uint8_t register_write[9] = {
        0x00,                   // Buffer address MSB: always 0
        0x00,                   // Buffer address LSB: always 0
        ((uint8_t)length) + 6,  // Number of bytes to write to command block buffer area
        0x00,                   // Direction: 0 = write, 1 = read
        (uint8_t)length,        // Number of bytes to write to register
        (uint8_t)(addr >> 24),  // Register address byte 3
        (uint8_t)(addr >> 16),  // Register address byte 2
        (uint8_t)(addr >> 8),   // Register address byte 1
        (uint8_t)(addr >> 0),   // Register address byte 0
    };

    status = i2c_start((self->addr << 1) | I2C_WRITE, I2C_TIMEOUT);
    if (status >= 0) {
        for (uint16_t i = 0; i < sizeof(register_write); i++) {
            status = i2c_write(register_write[i], I2C_TIMEOUT);
            if (status < 0) {
                goto error;
            }
        }

        for (uint16_t i = 0; i < length; i++) {
            status = i2c_write(data[i], I2C_TIMEOUT);
            if (status < 0) {
                goto error;
            }
        }
    } else {
        goto error;
    }

    i2c_stop();

    status = usb7206_register_access(self);
    if (status < 0) {
        goto error;
    }

error:
    i2c_stop();

    return (status < 0) ? status : length;
}

// Write 8-bit value to USB7206 register region.
// Returns number of bytes written on success or a negative number on error.
i2c_status_t usb7206_write_reg_8(struct USB7206* self, uint32_t addr, uint8_t data) { return usb7206_write_reg(self, addr, &data, sizeof(data)); }

// Write 32-bit value to USB7206 register region.
// Returns number of bytes written on success or a negative number on error.
i2c_status_t usb7206_write_reg_32(struct USB7206* self, uint32_t addr, uint32_t data) {
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
int usb7206_init(struct USB7206* self) {
    i2c_status_t status;
    uint32_t     data;

    // DM and DP are swapped on ports 2 and 3
    status = usb7206_write_reg_8(self, REG_PRT_SWAP, 0x0C);
    if (status < 0) {
        return status;
    }

    // Disable audio
    status = usb7206_write_reg_8(self, REG_I2S_FEAT_SEL, 0);
    if (status < 0) {
        return status;
    }

    // Set HFC_DISABLE
    data   = 0;
    status = usb7206_read_reg_32(self, REG_RUNTIME_FLAGS2, &data);
    if (status < 0) {
        return status;
    }
    data |= 1;
    status = usb7206_write_reg_32(self, REG_RUNTIME_FLAGS2, data);
    if (status < 0) {
        return status;
    }

    // Set Vendor ID and Product ID of USB 2 hub
    status = usb7206_write_reg_32(self, REG_VID, 0x00033384);
    if (status < 0) {
        return status;
    }

    // Set Vendor ID and Product ID of USB 3 hub
    status = usb7206_write_reg_32(self, REG_USB3_HUB_VID, 0x00043384);
    if (status < 0) {
        return status;
    }

    return 0;
}

// Attach USB7206.
// Returns bytes written on success or a negative number on error.
i2c_status_t usb7206_attach(struct USB7206* self) {
    uint8_t data[3] = {
        0xAA,
        0x56,
        0x00,
    };

    return i2c_transmit(self->addr << 1, data, sizeof(data), I2C_TIMEOUT);
}

struct USB7206_GPIO {
    struct USB7206* usb7206;
    uint32_t        pf;
};

struct USB7206_GPIO usb_gpio_sink         = {.usb7206 = &usb_hub, .pf = 29};  // UP_SEL = PF29 = GPIO93
struct USB7206_GPIO usb_gpio_source_left  = {.usb7206 = &usb_hub, .pf = 10};  // CL_SEL = PF10 = GPIO74
struct USB7206_GPIO usb_gpio_source_right = {.usb7206 = &usb_hub, .pf = 25};  // CR_SEL = PF25 = GPIO88

// Set USB7206 GPIO to specified value.
// Returns zero on success or negative number on error.
i2c_status_t usb7206_gpio_set(struct USB7206_GPIO* self, bool value) {
    i2c_status_t status;
    uint32_t     data;

    data   = 0;
    status = usb7206_read_reg_32(self->usb7206, REG_PIO64_OUT, &data);
    if (status < 0) {
        return status;
    }

    if (value) {
        data |= (((uint32_t)1) << self->pf);
    } else {
        data &= ~(((uint32_t)1) << self->pf);
    }
    status = usb7206_write_reg_32(self->usb7206, REG_PIO64_OUT, data);
    if (status < 0) {
        return status;
    }

    return 0;
}

// Initialize USB7206 GPIO.
// Returns zero on success or a negative number on error.
i2c_status_t usb7206_gpio_init(struct USB7206_GPIO* self) {
    i2c_status_t status;
    uint32_t     data;

    // Set programmable function to GPIO
    status = usb7206_write_reg_8(self->usb7206, REG_PF1_CTL + (self->pf - 1), 0);
    if (status < 0) {
        return status;
    }

    // Set GPIO to false by default
    usb7206_gpio_set(self, false);

    // Set GPIO to output
    data   = 0;
    status = usb7206_read_reg_32(self->usb7206, REG_PIO64_OEN, &data);
    if (status < 0) {
        return status;
    }

    data |= (((uint32_t)1) << self->pf);
    status = usb7206_write_reg_32(self->usb7206, REG_PIO64_OEN, data);
    if (status < 0) {
        return status;
    }

    return 0;
}

struct PTN5110 {
    uint8_t              addr;
    uint8_t              cc;
    struct USB7206_GPIO* gpio;
};

struct PTN5110 usb_sink         = {.addr = 0x51, .gpio = &usb_gpio_sink};
struct PTN5110 usb_source_left  = {.addr = 0x52, .gpio = &usb_gpio_source_left};
struct PTN5110 usb_source_right = {.addr = 0x50, .gpio = &usb_gpio_source_right};

// Initialize PTN5110.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_init(struct PTN5110* self) {
    // Set last cc to invalid value, to force update
    self->cc = 0xFF;
    // Initialize GPIO
    return usb7206_gpio_init(self->gpio);
}

// Read PTN5110 CC_STATUS.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_get_cc_status(struct PTN5110* self, uint8_t* cc) { return i2c_read_register(self->addr << 1, 0x1D, cc, 1, I2C_TIMEOUT); }

// Set PTN5110 SSMUX orientation.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_set_ssmux(struct PTN5110* self, bool orientation) { return usb7206_gpio_set(self->gpio, orientation); }

// Write PTN5110 COMMAND.
// Returns zero on success or negative number on error.
i2c_status_t ptn5110_command(struct PTN5110* self, uint8_t command) { return i2c_write_register(self->addr << 1, 0x23, &command, 1, I2C_TIMEOUT); }

// Set orientation of PTN5110 operating as a sink, call this once.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_sink_set_orientation(struct PTN5110* self) {
    i2c_status_t status;
    uint8_t      cc;

    status = ptn5110_get_cc_status(self, &cc);
    if (status < 0) {
        return status;
    }

    if ((cc & 0x03) == 0) {
        status = ptn5110_set_ssmux(self, false);
        if (status < 0) {
            return status;
        }
    } else {
        status = ptn5110_set_ssmux(self, true);
        if (status < 0) {
            return status;
        }
    }

    return 0;
}

// Update PTN5110 operating as a source, call this repeatedly.
// Returns zero on success or a negative number on error.
i2c_status_t ptn5110_source_update(struct PTN5110* self) {
    i2c_status_t status;
    uint8_t      cc;

    status = ptn5110_get_cc_status(self, &cc);
    if (status < 0) {
        return status;
    }

    if (cc != self->cc) {
        // WARNING: Setting this here will disable retries
        self->cc = cc;

        bool connected   = false;
        bool orientation = false;
        if ((cc & 0x03) == 2) {
            connected   = true;
            orientation = true;
        } else if (((cc >> 2) & 0x03) == 2) {
            connected   = true;
            orientation = false;
        }

        if (connected) {
            // Set SS mux orientation
            status = ptn5110_set_ssmux(self, orientation);
            if (status < 0) {
                return status;
            }

            // Enable source Vbus command
            status = ptn5110_command(self, 0b01110111);
            if (status < 0) {
                return status;
            }
        } else {
            // Disable source Vbus command
            status = ptn5110_command(self, 0b01100110);
            if (status < 0) {
                return status;
            }
        }
    }

    return 0;
}

void usb_mux_event(void) {
    // Run this on every 1000th matrix scan
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
    usb7206_init(&usb_hub);

    // Set up sink
    ptn5110_init(&usb_sink);
    ptn5110_sink_set_orientation(&usb_sink);

    // Set up sources
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
