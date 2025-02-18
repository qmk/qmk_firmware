// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#include "i2clib.h"
#include <stdint.h>
#include "i2c_master.h"
#include "debug.h"

DeviceList deviceList[MAX_MCP_NUM];
uint16_t   nDevices = 0;

bool change_channel(uint8_t channel) {
    // channel must be 1-4
    if (channel < 1 || 4 < channel) {
        dprintf("Invalid channel %u!\n", channel);
        return false;
    }
    const uint8_t data            = 0x01 << (channel - 1);
    i2c_status_t  expander_status = i2c_write_register(I2C_MULTIPX_ADDR << 1, 0x0, &data, 1, MY_I2C_TIMEOUT);
    if (expander_status == I2C_STATUS_SUCCESS) {
        return true;
    } else {
        dprintf("failed to change channel: %u!\n", expander_status);
        return false;
    }
}

bool write_PCA9557_register_1byte(uint8_t address, uint8_t ctrl_addr, uint8_t data) {
    i2c_status_t expander_status = i2c_write_register(address << 1, ctrl_addr, &data, 1, MY_I2C_TIMEOUT);
    if (expander_status == I2C_STATUS_SUCCESS) {
        dprintf("[PCA9557 set register] %X, reg:%X, data:%X\n", address, ctrl_addr, data);
        return true;
    } else {
        dprintf("[PCA9557 set register] failed to set input %u! %X, reg:%X, data:%X\n", expander_status, address, ctrl_addr, data);
        return false;
    }
}

Keys_Data read_PCA9557_register(uint8_t address) {
    Keys_Data    error_result    = {.type = Type_Unknown};
    uint8_t      inputData       = 0;
    i2c_status_t expander_status = i2c_read_register(address << 1, 0x0, &inputData, 1, MY_I2C_TIMEOUT);

    if (expander_status != I2C_STATUS_SUCCESS) {
        dprintf("failed to read data from %X! %X\n", address, expander_status);
        return error_result;
    }

    // upper 3 bits are type indication
    uint8_t type_data = (inputData & (0x07 << 5)) >> 5;

    Type type = Type_Unknown;
    if (type_data == 2) {
        type = Type_PCA9557_Keys5;
    } else if (type_data == 1) {
        type = Type_PCA9557_Keys4;
    } else {
        // unknown type
        dprintf("failed to read type from %X! Type Unknown: %X, type_data: %X\n", address, type, type_data);
        return error_result;
    }
    // lower 5 bits are key input data. They are pulled-up, so they need to be inverted
    uint8_t data = (~inputData & 0x1F);

    if (type == Type_PCA9557_Keys4) {
        // remove 1 bit if the device is `4 keys`
        data &= 0x0F;
    } else if (type == Type_PCA9557_Keys5) {
        // 5 keys
        // do nothing
    } else {
        // unknown
        return error_result;
    }

    Keys_Data d = {.type = type};
    memcpy(d.data, &data, 1);

    return d;
}

bool write_XL9555_register_1byte(uint8_t address, uint8_t ctrl_addr, uint8_t data) {
    i2c_status_t expander_status = i2c_write_register(address << 1, ctrl_addr, &data, 1, MY_I2C_TIMEOUT);
    if (expander_status == I2C_STATUS_SUCCESS) {
        dprintf("[XL9555 set register] %X, reg:%X, data:%X\n", address, ctrl_addr, data);
        return true;
    } else {
        dprintf("[XL9555 set register] failed to set input %u! %X, reg:%X, data:%X\n", expander_status, address, ctrl_addr, data);
        return false;
    }
}

Keys_Data read_XL9555_register(uint8_t address) {
    Keys_Data    error_result    = {.type = Type_Unknown};
    uint8_t      inputData[2]    = {0x11, 0x22};
    i2c_status_t expander_status = i2c_read_register(address << 1, 0x0, inputData, 2, MY_I2C_TIMEOUT);

    if (expander_status != I2C_STATUS_SUCCESS) {
        dprintf("failed to read data from %X! %X\n", address, expander_status);
        return error_result;
    }

    // upper 4 bits are type indication
    // Note: temporary, this device
    uint8_t type_data = (inputData[0] & 0xF0) >> 4;

    Type type = Type_Unknown;
    if (type_data == 0x2) {
        type = Type_XL9555_Keys5;
    } else if (type_data == 0x0 || type_data == 0xF) { // temporary
        type = Type_XL9555_Keys4;
    } else {
        // unknown type
        dprintf("failed to read data from %X! Type Unknown: %X, type_data: %X\n", address, type, type_data);
        return error_result;
    }
    // key input data are on 2 bytes
    // inputData[0]: lower 4 bits
    // inputData[1]: lower 1 bits
    // They are pulled-up, so they need to be inverted
    uint8_t data = (uint8_t)((inputData[1] << 4) | (0x0F & inputData[0]));
    if (type == Type_XL9555_Keys4) {
        // remove 1 bit if the device is `4 keys`
        data &= 0x0F;
        data ^= 0x0F;
    } else if (type == Type_XL9555_Keys5) {
        data ^= 0x1F;
    }

    Keys_Data d = {.type = type};
    memcpy(d.data, &data, 1);

    return d;
}

bool write_PCA9534A_register_1byte(uint8_t address, uint8_t ctrl_addr, uint8_t data) {
    i2c_status_t expander_status = i2c_write_register(address << 1, ctrl_addr, &data, 1, MY_I2C_TIMEOUT);
    if (expander_status == I2C_STATUS_SUCCESS) {
        dprintf("[PCA9534A set register] %X, reg:%X, data:%X\n", address, ctrl_addr, data);
        return true;
    } else {
        dprintf("[PCA9534A set register] failed to set input %u! %X, reg:%X, data:%X\n", expander_status, address, ctrl_addr, data);
        return false;
    }
}

Keys_Data read_PCA9534A_register(uint8_t address) {
    Keys_Data    error_result    = {.type = Type_Unknown};
    uint8_t      inputData       = 0;
    i2c_status_t expander_status = i2c_read_register(address << 1, 0x0, &inputData, 1, MY_I2C_TIMEOUT);

    if (expander_status != I2C_STATUS_SUCCESS) {
        dprintf("failed to read data from %X! %X\n", address, expander_status);
        return error_result;
    }

    // upper 3 bits are type indication
    uint8_t type_data = (inputData & (0xFF << 5)) >> 5;

    Type type = Type_Unknown;
    if (type_data == 2) {
        type = Type_PCA9534A_RE_CLICKABLE;
    } else {
        // unknown type
        dprintf("failed to read type from %X! Type Unknown: %X, type_data: %X, inputData: %X \n", address, type, type_data, inputData);
        return error_result;
    }
    // lower 5 bits are input data
    uint8_t data = (inputData & 0x1F);

    if (type == Type_PCA9534A_RE_CLICKABLE) {
        // use only lower 3 bits. RO_A, RO_B, L_E
        data &= 0x07;
    } else {
        // unknown
        return error_result;
    }

    Keys_Data d = {.type = type};
    memcpy(d.data, &data, 1);

    return d;
}

Keys_Data init_PCA9557(uint8_t address) {
    bool success = true;

    // pins: input
    success &= write_PCA9557_register_1byte(address, 0x3, 0xFF);
    // polarity: no change
    success &= write_PCA9557_register_1byte(address, 0x2, 0x00);

    if (!success) {
        dprintf("Failed to init PCA9557: %X\n", address);
        Keys_Data data = {Type_Unknown};
        return data;
    }

    // load inputs to detect the type
    Keys_Data data = read_PCA9557_register(address);
    return data;
}

Keys_Data init_XL9555(uint8_t address) {
    bool success = true;

    // pins: input
    success &= write_XL9555_register_1byte(address, 0x6, 0xFF);
    success &= write_XL9555_register_1byte(address, 0x7, 0xFF);
    // polarity: no change
    success &= write_XL9555_register_1byte(address, 0x4, 0x00);
    success &= write_XL9555_register_1byte(address, 0x5, 0x00);

    if (!success) {
        dprintf("Failed to init XL9555: %X\n", address);
        Keys_Data data = {Type_Unknown};
        return data;
    }

    // load inputs to detect the type
    Keys_Data data = read_XL9555_register(address);
    return data;
}

Keys_Data init_PCA9534A(uint8_t address) {
    bool success = true;

    // pins: input
    success &= write_PCA9534A_register_1byte(address, 0x3, 0xFF);
    // polarity: no change
    success &= write_PCA9534A_register_1byte(address, 0x2, 0x00);

    if (!success) {
        dprintf("Failed to init PCA9534A: %X\n", address);
        Keys_Data data = {Type_Unknown};
        return data;
    }

    // load inputs to detect the type
    Keys_Data data = read_PCA9534A_register(address);
    return data;
}

typedef enum {
    ShiftType_Key_Start = 0,
    ShiftType_RE_Start  = 1,
} ShiftType;

uint16_t get_keymap_shift(uint8_t ch, ShiftType type) {
    uint16_t keyShift = MAX_KEY_PER_CH_NUM * 5;
    uint16_t reShift  = MAX_RE_PER_CH_NUM * 1;
    uint16_t chShift  = keyShift + reShift + CH_BUFFER_NUM;

    if (type == ShiftType_Key_Start) {
        return SYSTEM_KEY_NUM + chShift * (ch - 1);
    } else if (type == ShiftType_RE_Start) {
        return SYSTEM_KEY_NUM + chShift * (ch - 1) + keyShift;
    } else {
        dprintf("Invalid Shift Type: %d", type);
        return 0;
    }
}

uint16_t get_updated_keymap_shift(uint16_t keymapShift, uint16_t shiftValue) {
    int prevAlign = keymapShift / MATRIX_COLS;
    int nextAlign = (keymapShift + shiftValue - 1) / MATRIX_COLS;
    if (prevAlign != nextAlign) {
        // shiftValue  = nextAlign * MATRIX_COLS - keymapShift;
        keymapShift = nextAlign * MATRIX_COLS;
    }

    return keymapShift;
}

void do_scan(void) {
    nDevices = 0;

    dprintf("Scanning...\n");

    // firstly, access to the I2C multiplexer
    {
        i2c_status_t error = i2c_ping_address(I2C_MULTIPX_ADDR << 1, MY_I2C_TIMEOUT);
        if (error == I2C_STATUS_SUCCESS) {
            dprintf(" MUX found at address 0x%02X\n", I2C_MULTIPX_ADDR);
        } else {
            dprintf(" MUX Unknown error (%u) at address 0x%02X\n", error, I2C_MULTIPX_ADDR);
        }
    }

    for (uint8_t ch = 1; ch <= MAX_MEX_CH; ch++) {
        change_channel(ch);

        uint16_t keymapShift = get_keymap_shift(ch, ShiftType_Key_Start);

        // detect PCA9557
        for (uint8_t address = PCA9557_FROM_ADDR; address < PCA9557_END_ADDR; address++) {
            i2c_status_t error = i2c_ping_address(address << 1, MY_I2C_TIMEOUT);
            if (error == I2C_STATUS_SUCCESS) {
                dprintf("[PCA9557_init] %d, 0x%X \n", ch, address);
                Keys_Data data = init_PCA9557(address);

                if (data.type == Type_Unknown) {
                    dprintf("[PCA9557_init] Failed: %d, 0x%X, type: %d \n", ch, address, data.type);
                    continue;
                }

                int shiftValue = 0;
                if (data.type == Type_PCA9557_Keys4) {
                    shiftValue = 5; // Ideally, this value should be 4. However, for easy re-layout, use the same value as key5
                } else if (data.type == Type_PCA9557_Keys5) {
                    shiftValue = 5;
                } else {
                    dprintf("[PCA9557_init] type is not covered: %d \n", data.type);
                }

                keymapShift          = get_updated_keymap_shift(keymapShift, shiftValue);
                deviceList[nDevices] = (DeviceList){.ch = ch, .address = address, .type = data.type, .keymapShift = keymapShift};
                keymapShift += shiftValue;
                nDevices++;
            } else {
                dprintf("  Missing: (%u) at address 0x%02X\n", error, address);
            }
        }

        // XL9555 devices can overwrite PCA9557 devices' results
        keymapShift = get_keymap_shift(ch, ShiftType_Key_Start);

        // detect XL9555
        for (uint8_t address = XL9555_FROM_ADDR; address < XL9555_END_ADDR; address++) {
            i2c_status_t error = i2c_ping_address(address << 1, MY_I2C_TIMEOUT);
            if (error == I2C_STATUS_SUCCESS) {
                dprintf("[XL9555_init] %d, 0x%X \n", ch, address);
                Keys_Data data = init_XL9555(address);

                if (data.type == Type_Unknown) {
                    dprintf("[XL9555_init] Failed: %d, 0x%X, type: %d \n", ch, address, data.type);
                    continue;
                }

                int shiftValue = 0;
                if (data.type == Type_XL9555_Keys4) {
                    shiftValue = 5; // Ideally, this value should be 4, but for easy re-layout, use the same value as key5
                } else if (data.type == Type_XL9555_Keys5) {
                    shiftValue = 5;
                } else {
                    dprintf("[XL9555_init] type is not covered: %d \n", data.type);
                }

                keymapShift          = get_updated_keymap_shift(keymapShift, shiftValue);
                deviceList[nDevices] = (DeviceList){.ch = ch, .address = address, .type = data.type, .keymapShift = keymapShift};
                keymapShift += shiftValue;
                nDevices++;
            } else {
                dprintf("  Missing: (%u) at address 0x%02X\n", error, address);
            }
        }

        // proceed to the begining of the position of rotary encoders
        keymapShift = get_keymap_shift(ch, ShiftType_RE_Start);

        // detect PCA9534A, rotary encoders
        for (uint8_t address = PCA9534A_FROM_ADDR; address < PCA9534A_END_ADDR; address++) {
            i2c_status_t error = i2c_ping_address(address << 1, MY_I2C_TIMEOUT);
            if (error == I2C_STATUS_SUCCESS) {
                dprintf("[PCA9534A_init] %d, 0x%X \n", ch, address);
                Keys_Data data = init_PCA9534A(address);

                if (data.type == Type_Unknown) {
                    dprintf("[PCA9534A_init] Failed: %d, 0x%X, type: %d \n", ch, address, data.type);
                    continue;
                }

                int shiftValue = 0;
                if (data.type == Type_PCA9534A_RE_CLICKABLE) {
                    shiftValue = 1; // for click button
                } else {
                    dprintf("[PCA9534A_init] type is not covered: %d \n", data.type);
                }

                keymapShift          = get_updated_keymap_shift(keymapShift, shiftValue);
                deviceList[nDevices] = (DeviceList){.ch = ch, .address = address, .type = data.type, .keymapShift = keymapShift};
                keymapShift += shiftValue;
                nDevices++;
            } else {
                dprintf("  Missing: (%u) at address 0x%02X\n", error, address);
            }
        }
    }

    if (nDevices == 0) {
        dprintf("No I2C devices found\n");
    } else {
        dprintf("#devices: %d\n", nDevices);
        for (uint16_t i = 0; i < nDevices; i++) {
            dprintf("[I2C] %d, 0x%X \n", deviceList[i].ch, deviceList[i].address);
        }
    }
}
