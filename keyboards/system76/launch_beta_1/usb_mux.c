#include "i2c.c"

#define PRT_SWAP 0xBF8030FA
#define I2S_FEAT_SEL 0xBFD23412

struct USB7206 {
    uint8_t addr;
};

struct USB7206 usb_hub = { .addr = 0x2D };

int usb7206_write(struct USB7206 * self, uint8_t * data, int length) {
    return i2c_send(self->addr, data, length);
}

int usb7206_register_access(struct USB7206 * self) {
    uint8_t data[3] = {
        0x99,
        0x37,
        0x00,
    };
    return usb7206_write(self, data, sizeof(data));
}

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
        length,
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

    res = i2c_read(data, length);
    if (res < 0) return res;

    i2c_stop();

    return 0;
}

int usb7206_read_reg_32(struct USB7206 * self, uint32_t addr, uint32_t * data) {
    int res;

    // First byte is available length
    uint8_t bytes[5] = { 0, 0, 0, 0, 0, };
    res = usb7206_read_reg(self, addr, bytes, sizeof(bytes));
    if (res < 0) return res;

    // Must convert from little endian
    *data =
        (((uint32_t)bytes[1]) << 0) |
        (((uint32_t)bytes[2]) << 8) |
        (((uint32_t)bytes[3]) << 16) |
        (((uint32_t)bytes[4]) << 24);

    return 0;
}

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
        length,
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

    return usb7206_register_access(self);
}

int usb7206_write_reg_8(struct USB7206 * self, uint32_t addr, uint8_t data) {
    return usb7206_write_reg(self, addr, &data, sizeof(data));
}

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

int usb7206_init(struct USB7206 * self) {
    int res;

    // DM and DP are swapped on ports 2 and 3
    res = usb7206_write_reg_8(self, PRT_SWAP, 0x0C);
    if (res < 0) return res;

    // Disable audio
    return usb7206_write_reg_8(self, I2S_FEAT_SEL, 0);
}

int usb7206_attach(struct USB7206 * self) {
    uint8_t data[3] = {
        0xAA,
        0x56,
        0x00,
    };
    return usb7206_write(self, data, sizeof(data));
}

#define PF1_CTL 0xBF800C04
#define PIO64_OEN 0xBF800908
#define PIO64_OUT 0xBF800928

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

int usb7206_gpio_set(struct USB7206_GPIO * self, bool value) {
    int res;

    uint32_t data = 0;
    res = usb7206_read_reg_32(self->usb7206, PIO64_OUT, &data);
    if (res < 0) return res;

    if (value) {
        data |= (1UL << self->pf);
    } else {
        data &= ~(1UL << self->pf);
    }
    return usb7206_write_reg_32(self->usb7206, PIO64_OUT, data);
}

int usb7206_gpio_init(struct USB7206_GPIO * self) {
    int res = 0;

    // Set programmable function to GPIO
    res = usb7206_write_reg_8(self->usb7206, PF1_CTL + (self->pf - 1), 0);
    if (res < 0) return res;

    // Set GPIO to false by default
    usb7206_gpio_set(self, false);

    // Set GPIO to output
    uint32_t data = 0;
    res = usb7206_read_reg_32(self->usb7206, PIO64_OEN, &data);
    if (res < 0) return res;

    data |= (1 << self->pf);
    return usb7206_write_reg_32(self->usb7206, PIO64_OEN, data);
}

struct PTN5110 {
    uint8_t addr;
    uint8_t cc;
    struct USB7206_GPIO * gpio;
};

struct PTN5110 usb_sink = { .addr = 0x51, .gpio = &usb_gpio_sink };
struct PTN5110 usb_source_left = { .addr = 0x52, .gpio = &usb_gpio_source_left };
struct PTN5110 usb_source_right = { .addr = 0x50, .gpio = &usb_gpio_source_right };

int ptn5110_init(struct PTN5110 * self) {
    // Set last cc to disconnected value
    self->cc = 0;
    // Initialize GPIO
    return usb7206_gpio_init(self->gpio);
}

int ptn5110_get_cc_status(struct PTN5110 * self, uint8_t * cc) {
    return i2c_get(self->addr, 0x1D, cc, 1);
}

int ptn5110_set_ssmux(struct PTN5110 * self, bool orientation) {
    return usb7206_gpio_set(self->gpio, orientation);
}

int ptn5110_command(struct PTN5110 * self, uint8_t command) {
    return i2c_set(self->addr, 0x23, &command, 1);
}

int ptn5110_sink_set_orientation(struct PTN5110 * self) {
    int res;

    uint8_t cc;
    res = ptn5110_get_cc_status(self, &cc);
    if (res < 0) return res;

    if ((cc & 3) == 0) {
        ptn5110_set_ssmux(self, false);
    } else {
        ptn5110_set_ssmux(self, true);
    }

    return 0;
}

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
}
