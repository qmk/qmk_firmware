#include <util/delay.h>

#include "i2c.h"
#include "usb_mux.h"

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

struct USB7206 usb_hub = { .addr = 0x2D };

// Perform USB7206 register access
// Returns bytes written on success or negative number on error
int usb7206_register_access(struct USB7206 * self) {
    uint8_t data[3] = {
        0x99,
        0x37,
        0x00,
    };
    return i2c_send(self->addr, data, sizeof(data));
}

// Read data from USB7206 register region
// Returns number of bytes read on success or negative number on error
int usb7206_read_reg(struct USB7206 * self, uint32_t addr, uint8_t * data, int length) {
    int res;

    uint8_t command[9] = {
        // Buffer address high: always 0
        0x00,
        // Buffer address low: always 0
        0x00,
        // Number of bytes to write to command block buffer area
        0x06,
        // Direction: 0 = write, 1 = read
        0x01,
        // Number of bytes to read from register
        (uint8_t)length,
        // Register address byte 3
        (uint8_t)(addr >> 24),
        // Register address byte 2
        (uint8_t)(addr >> 16),
        // Register address byte 1
        (uint8_t)(addr >> 8),
        // Register address byte 0
        (uint8_t)(addr >> 0),
    };
    res = i2c_send(self->addr, command, sizeof(command));
    if (res < 0) return res;

    res = usb7206_register_access(self);
    if (res < 0) return res;

    res = i2c_start(self->addr, false);
    if (res < 0) return res;

    uint8_t command2[2] = {
        // Buffer address high: always 0
        0x00,
        // Buffer address low: 6 to skip header
        0x06,
    };
    res = i2c_write(command2, sizeof(command2));
    if (res < 0) return res;

    res = i2c_start(self->addr, true);
    if (res < 0) return res;

    // Read and ignore buffer length
    res = i2c_read_byte(true);
    if (res < 0) return res;

    res = i2c_read(data, length);
    if (res < 0) return res;

    i2c_stop();

    return length;
}

// Read 32-bit value from USB7206 register region
// Returns number of bytes read on success or negative number on error
int usb7206_read_reg_32(struct USB7206 * self, uint32_t addr, uint32_t * data) {
    int res;

    // First byte is available length
    uint8_t bytes[4] = { 0, 0, 0, 0, };
    res = usb7206_read_reg(self, addr, bytes, sizeof(bytes));
    if (res < 0) return res;

    // Must convert from little endian
    *data =
        (((uint32_t)bytes[0]) << 0) |
        (((uint32_t)bytes[1]) << 8) |
        (((uint32_t)bytes[2]) << 16) |
        (((uint32_t)bytes[3]) << 24);

    return res;
}

// Write data to USB7206 register region
// Returns number of bytes written on success or negative number on error
int usb7206_write_reg(struct USB7206 * self, uint32_t addr, uint8_t * data, int length) {
    int res;

    res = i2c_start(self->addr, false);
    if (res < 0) return res;

    uint8_t command[9] = {
        // Buffer address high: always 0
        0x00,
        // Buffer address low: always 0
        0x00,
        // Number of bytes to write to command block buffer area
        //TODO: check length!
        ((uint8_t)length) + 6,
        // Direction: 0 = write, 1 = read
        0x00,
        // Number of bytes to write to register
        (uint8_t)length,
        // Register address byte 3
        (uint8_t)(addr >> 24),
        // Register address byte 2
        (uint8_t)(addr >> 16),
        // Register address byte 1
        (uint8_t)(addr >> 8),
        // Register address byte 0
        (uint8_t)(addr >> 0),
    };
    res = i2c_write(command, sizeof(command));
    if (res < 0) return res;

    res = i2c_write(data, length);
    if (res < 0) return res;

    i2c_stop();

    res = usb7206_register_access(self);
    if (res < 0) return res;

    return length;
}

// Write 8-bit value to USB7206 register region
// Returns number of bytes written on success or negative number on error
int usb7206_write_reg_8(struct USB7206 * self, uint32_t addr, uint8_t data) {
    return usb7206_write_reg(self, addr, &data, sizeof(data));
}

// Write 32-bit value to USB7206 register region
// Returns number of bytes written on success or negative number on error
int usb7206_write_reg_32(struct USB7206 * self, uint32_t addr, uint32_t data) {
    // Must convert to little endian
    uint8_t bytes[4] = {
        (uint8_t)(data >> 0),
        (uint8_t)(data >> 8),
        (uint8_t)(data >> 16),
        (uint8_t)(data >> 24),
    };
    return usb7206_write_reg(self, addr, bytes, sizeof(bytes));
}

// Initialize USB7206
// Returns zero on success or negative number on error
int usb7206_init(struct USB7206 * self) {
    int res;

    // DM and DP are swapped on ports 2 and 3
    res = usb7206_write_reg_8(self, REG_PRT_SWAP, 0x0C);
    if (res < 0) return res;

    // Disable audio
    res = usb7206_write_reg_8(self, REG_I2S_FEAT_SEL, 0);
    if (res < 0) return res;

    // Set HFC_DISABLE
    uint32_t data = 0;
    res = usb7206_read_reg_32(self, REG_RUNTIME_FLAGS2, &data);
    if (res < 0) return res;
    data |= 1;
    res = usb7206_write_reg_32(self, REG_RUNTIME_FLAGS2, data);
    if (res < 0) return res;

    // Set Vendor ID and Product ID of USB 2 hub
    res = usb7206_write_reg_32(self, REG_VID, 0x00033384);
    if (res < 0) return res;

    // Set Vendor ID and Product ID of USB 3 hub
    res = usb7206_write_reg_32(self, REG_USB3_HUB_VID, 0x00043384);
    if (res < 0) return res;

    return 0;
}

// Attach USB7206
// Returns bytes written on success or negative number on error
int usb7206_attach(struct USB7206 * self) {
    uint8_t data[3] = {
        0xAA,
        0x56,
        0x00,
    };
    return i2c_send(self->addr, data, sizeof(data));
}

struct USB7206_GPIO {
    struct USB7206 * usb7206;
    uint32_t pf;
};

// UP_SEL = PF29 = GPIO93
struct USB7206_GPIO usb_gpio_sink = {
    .usb7206 = &usb_hub,
    .pf = 29,
};

// CL_SEL = PF10 = GPIO74
struct USB7206_GPIO usb_gpio_source_left = {
    .usb7206 = &usb_hub,
    .pf = 10,
};

// CR_SEL = PF25 = GPIO88
struct USB7206_GPIO usb_gpio_source_right = {
    .usb7206 = &usb_hub,
    .pf = 25,
};

// Set USB7206 GPIO to specified value
// Returns zero on success or negative number on error
int usb7206_gpio_set(struct USB7206_GPIO * self, bool value) {
    int res;

    uint32_t data = 0;
    res = usb7206_read_reg_32(self->usb7206, REG_PIO64_OUT, &data);
    if (res < 0) return res;

    if (value) {
        data |= (((uint32_t)1) << self->pf);
    } else {
        data &= ~(((uint32_t)1) << self->pf);
    }
    res = usb7206_write_reg_32(self->usb7206, REG_PIO64_OUT, data);
    if (res < 0) return res;

    return 0;
}

// Initialize USB7206 GPIO
// Returns zero on success or negative number on error
int usb7206_gpio_init(struct USB7206_GPIO * self) {
    int res = 0;

    // Set programmable function to GPIO
    res = usb7206_write_reg_8(self->usb7206, REG_PF1_CTL + (self->pf - 1), 0);
    if (res < 0) return res;

    // Set GPIO to false by default
    usb7206_gpio_set(self, false);

    // Set GPIO to output
    uint32_t data = 0;
    res = usb7206_read_reg_32(self->usb7206, REG_PIO64_OEN, &data);
    if (res < 0) return res;

    data |= (((uint32_t)1) << self->pf);
    res = usb7206_write_reg_32(self->usb7206, REG_PIO64_OEN, data);
    if (res < 0) return res;

    return 0;
}

struct PTN5110 {
    uint8_t addr;
    uint8_t cc;
    struct USB7206_GPIO * gpio;
};

struct PTN5110 usb_sink = { .addr = 0x51, .gpio = &usb_gpio_sink };
struct PTN5110 usb_source_left = { .addr = 0x52, .gpio = &usb_gpio_source_left };
struct PTN5110 usb_source_right = { .addr = 0x50, .gpio = &usb_gpio_source_right };

// Initialize PTN5110
// Returns zero on success or negative number on error
int ptn5110_init(struct PTN5110 * self) {
    // Set last cc to invalid value, to force update
    self->cc = 0xFF;
    // Initialize GPIO
    return usb7206_gpio_init(self->gpio);
}

// Read PTN5110 CC_STATUS
// Returns bytes read on success or negative number on error
int ptn5110_get_cc_status(struct PTN5110 * self, uint8_t * cc) {
    return i2c_get(self->addr, 0x1D, cc, 1);
}

// Set PTN5110 SSMUX orientation
// Returns zero on success or negative number on error
int ptn5110_set_ssmux(struct PTN5110 * self, bool orientation) {
    return usb7206_gpio_set(self->gpio, orientation);
}

// Write PTN5110 COMMAND
// Returns bytes written on success or negative number on error
int ptn5110_command(struct PTN5110 * self, uint8_t command) {
    return i2c_set(self->addr, 0x23, &command, 1);
}

// Set orientation of PTN5110 operating as a sink, call this once
// Returns zero on success or negative number on error
int ptn5110_sink_set_orientation(struct PTN5110 * self) {
    int res;

    uint8_t cc;
    res = ptn5110_get_cc_status(self, &cc);
    if (res < 0) return res;

    if ((cc & 3) == 0) {
        res = ptn5110_set_ssmux(self, false);
        if (res < 0) return res;
    } else {
        res = ptn5110_set_ssmux(self, true);
        if (res < 0) return res;
    }

    return 0;
}

// Update PTN5110 operating as a source, call this repeatedly
// Returns zero on success or negative number on error
int ptn5110_source_update(struct PTN5110 * self) {
    int res;

    uint8_t cc;
    res = ptn5110_get_cc_status(self, &cc);
    if (res < 0) return res;

    if (cc != self->cc) {
        //WARNING: Setting this here will disable retries
        self->cc = cc;

        bool connected = false;
        bool orientation = false;
        if ((cc & 3) == 2) {
            connected = true;
            orientation = true;
        } else if (((cc >> 2) & 3) == 2) {
            connected = true;
            orientation = false;
        }

        if (connected) {
            // Set SS mux orientation
            res = ptn5110_set_ssmux(self, orientation);
            if (res < 0) return res;

            // Enable source vbus command
            res = ptn5110_command(self, 0b01110111);
            if (res < 0) return res;
        } else {
            // Disable source vbus command
            res = ptn5110_command(self, 0b01100110);
            if (res < 0) return res;
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
    // Run I2C bus at 100 KHz
    i2c_init(100000);

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
    //TODO: find reason why GPIO for sink orientation is reset
    for(int i = 0; i < 100; i++) {
        ptn5110_sink_set_orientation(&usb_sink);
        _delay_ms(10);
    }
}
