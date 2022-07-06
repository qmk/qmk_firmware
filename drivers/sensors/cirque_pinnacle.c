// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
// based on https://github.com/cirque-corp/Cirque_Pinnacle_1CA027/tree/master/Circular_Trackpad
// with modifications and changes for QMK
// refer to documentation: Gen2 and Gen3 (Pinnacle ASIC) at https://www.cirque.com/documentation

#include "cirque_pinnacle.h"
#include "print.h"
#include "debug.h"
#include "wait.h"
#include "timer.h"

// Registers for RAP
// clang-format off
#define FIRMWARE_ID          0x00
#define FIRMWARE_VERSION_C   0x01
#define STATUS_1             0x02
#define SYSCONFIG_1          0x03
#define FEEDCONFIG_1         0x04
#define FEEDCONFIG_2         0x05
#define CALIBRATION_CONFIG_1 0x07
#define PS2_AU_CONTROL       0x08
#define SAMPLE_RATE          0x09
#define Z_IDLE_COUNT         0x0A
#define Z_SCALER             0x0B
#define SLEEP_INTERVAL       0x0C
#define SLEEP_TIMER          0x0D
#define PACKET_BYTE_0        0x12
#define PACKET_BYTE_1        0x13
#define PACKET_BYTE_2        0x14
#define PACKET_BYTE_3        0x15
#define PACKET_BYTE_4        0x16
#define PACKET_BYTE_5        0x17

#define ERA_VALUE            0x1B
#define ERA_HIGH_BYTE        0x1C
#define ERA_LOW_BYTE         0x1D
#define ERA_CONTROL          0x1E

// ADC-attenuation settings (held in BIT_7 and BIT_6)
// 1X = most sensitive, 4X = least sensitive
#define ADC_ATTENUATE_1X     0x00
#define ADC_ATTENUATE_2X     0x40
#define ADC_ATTENUATE_3X     0x80
#define ADC_ATTENUATE_4X     0xC0

#ifndef CIRQUE_PINNACLE_ATTENUATION
#    define CIRQUE_PINNACLE_ATTENUATION ADC_ATTENUATE_4X
#endif
// clang-format on

bool     touchpad_init;
uint16_t scale_data = 1024;

void cirque_pinnacle_clear_flags(void);
void cirque_pinnacle_enable_feed(bool feedEnable);
void RAP_ReadBytes(uint8_t address, uint8_t* data, uint8_t count);
void RAP_Write(uint8_t address, uint8_t data);

#ifdef CONSOLE_ENABLE
void print_byte(uint8_t byte) {
    xprintf("%c%c%c%c%c%c%c%c|", (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0'));
}
#endif

/*  Logical Scaling Functions */
// Clips raw coordinates to "reachable" window of sensor
// NOTE: values outside this window can only appear as a result of noise
void ClipCoordinates(pinnacle_data_t* coordinates) {
    if (coordinates->xValue < CIRQUE_PINNACLE_X_LOWER) {
        coordinates->xValue = CIRQUE_PINNACLE_X_LOWER;
    } else if (coordinates->xValue > CIRQUE_PINNACLE_X_UPPER) {
        coordinates->xValue = CIRQUE_PINNACLE_X_UPPER;
    }
    if (coordinates->yValue < CIRQUE_PINNACLE_Y_LOWER) {
        coordinates->yValue = CIRQUE_PINNACLE_Y_LOWER;
    } else if (coordinates->yValue > CIRQUE_PINNACLE_Y_UPPER) {
        coordinates->yValue = CIRQUE_PINNACLE_Y_UPPER;
    }
}

uint16_t cirque_pinnacle_get_scale(void) {
    return scale_data;
}
void cirque_pinnacle_set_scale(uint16_t scale) {
    scale_data = scale;
}

// Scales data to desired X & Y resolution
void cirque_pinnacle_scale_data(pinnacle_data_t* coordinates, uint16_t xResolution, uint16_t yResolution) {
    uint32_t xTemp = 0;
    uint32_t yTemp = 0;

    ClipCoordinates(coordinates);

    xTemp = coordinates->xValue;
    yTemp = coordinates->yValue;

    // translate coordinates to (0, 0) reference by subtracting edge-offset
    xTemp -= CIRQUE_PINNACLE_X_LOWER;
    yTemp -= CIRQUE_PINNACLE_Y_LOWER;

    // scale coordinates to (xResolution, yResolution) range
    coordinates->xValue = (uint16_t)(xTemp * xResolution / CIRQUE_PINNACLE_X_RANGE);
    coordinates->yValue = (uint16_t)(yTemp * yResolution / CIRQUE_PINNACLE_Y_RANGE);
}

// Clears Status1 register flags (SW_CC and SW_DR)
void cirque_pinnacle_clear_flags() {
    RAP_Write(STATUS_1, 0x00);
    wait_us(50);
}

// Enables/Disables the feed
void cirque_pinnacle_enable_feed(bool feedEnable) {
    uint8_t temp;
    RAP_ReadBytes(FEEDCONFIG_1, &temp, 1); // Store contents of FeedConfig1 register

    if (feedEnable) {
        temp |= 0x01; // Set Feed Enable bit
    } else {
        temp &= ~0x01; // Clear Feed Enable bit
    }
    RAP_Write(FEEDCONFIG_1, temp);
}

/*  ERA (Extended Register Access) Functions  */
// Reads <count> bytes from an extended register at <address> (16-bit address),
// stores values in <*data>
void ERA_ReadBytes(uint16_t address, uint8_t* data, uint16_t count) {
    uint8_t ERAControlValue = 0xFF;

    cirque_pinnacle_enable_feed(false); // Disable feed

    RAP_Write(ERA_HIGH_BYTE, (uint8_t)(address >> 8));    // Send upper byte of ERA address
    RAP_Write(ERA_LOW_BYTE, (uint8_t)(address & 0x00FF)); // Send lower byte of ERA address

    for (uint16_t i = 0; i < count; i++) {
        RAP_Write(ERA_CONTROL, 0x05); // Signal ERA-read (auto-increment) to Pinnacle

        // Wait for status register 0x1E to clear
        do {
            RAP_ReadBytes(ERA_CONTROL, &ERAControlValue, 1);
        } while (ERAControlValue != 0x00);

        RAP_ReadBytes(ERA_VALUE, data + i, 1);

        cirque_pinnacle_clear_flags();
    }
}

// Writes a byte, <data>, to an extended register at <address> (16-bit address)
void ERA_WriteByte(uint16_t address, uint8_t data) {
    uint8_t ERAControlValue = 0xFF;

    cirque_pinnacle_enable_feed(false); // Disable feed

    RAP_Write(ERA_VALUE, data); // Send data byte to be written

    RAP_Write(ERA_HIGH_BYTE, (uint8_t)(address >> 8));    // Upper byte of ERA address
    RAP_Write(ERA_LOW_BYTE, (uint8_t)(address & 0x00FF)); // Lower byte of ERA address

    RAP_Write(ERA_CONTROL, 0x02); // Signal an ERA-write to Pinnacle

    // Wait for status register 0x1E to clear
    do {
        RAP_ReadBytes(ERA_CONTROL, &ERAControlValue, 1);
    } while (ERAControlValue != 0x00);

    cirque_pinnacle_clear_flags();
}

void cirque_pinnacle_set_adc_attenuation(uint8_t adcGain) {
    uint8_t temp = 0x00;

    ERA_ReadBytes(0x0187, &temp, 1);
    temp &= 0x3F; // clear top two bits
    temp |= adcGain;
    ERA_WriteByte(0x0187, temp);
    ERA_ReadBytes(0x0187, &temp, 1);
}

// Changes thresholds to improve detection of fingers
void cirque_pinnacle_tune_edge_sensitivity(void) {
    uint8_t temp = 0x00;

    ERA_ReadBytes(0x0149, &temp, 1);
    ERA_WriteByte(0x0149, 0x04);
    ERA_ReadBytes(0x0149, &temp, 1);

    ERA_ReadBytes(0x0168, &temp, 1);
    ERA_WriteByte(0x0168, 0x03);
    ERA_ReadBytes(0x0168, &temp, 1);
}

/*  Pinnacle-based TM040040/TM035035/TM023023 Functions  */
void cirque_pinnacle_init(void) {
#if defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_spi)
    spi_init();
#elif defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_i2c)
    i2c_init();
#endif

    touchpad_init = true;

    // Host clears SW_CC flag
    cirque_pinnacle_clear_flags();

    // SysConfig1 (Low Power Mode)
    // Bit 0: Reset, 1=Reset
    // Bit 1: Shutdown, 1=Shutdown, 0=Active
    // Bit 2: Sleep Enable, 1=low power mode, 0=normal mode
    // send a RESET command now, in case QMK had a soft-reset without a power cycle
    RAP_Write(SYSCONFIG_1, 0x01);
    wait_ms(30); // Pinnacle needs 10-15ms to boot, so wait long enough before configuring
    RAP_Write(SYSCONFIG_1, 0x00);
    wait_us(50);

    // FeedConfig2 (Feature flags for Relative Mode Only)
    // Bit 0: IntelliMouse Enable, 1=enable, 0=disable
    // Bit 1: All Taps Disable, 1=disable, 0=enable
    // Bit 2: Secondary Tap Disable, 1=disable, 0=enable
    // Bit 3: Scroll Disable, 1=disable, 0=enable
    // Bit 4: GlideExtend® Disable, 1=disable, 0=enable
    // Bit 5: reserved
    // Bit 6: reserved
    // Bit 7: Swap X & Y, 1=90° rotation, 0=0° rotation
    RAP_Write(FEEDCONFIG_2, 0x00);

    // FeedConfig1 (Data Output Flags)
    // Bit 0: Feed enable, 1=feed, 0=no feed
    // Bit 1: Data mode, 1=absolute, 0=relative
    // Bit 2: Filter disable, 1=no filter, 0=filter
    // Bit 3: X disable, 1=no X data, 0=X data
    // Bit 4: Y disable, 1=no Y data, 0=Y data
    // Bit 5: reserved
    // Bit 6: X data Invert, 1=X max to 0, 0=0 to Y max
    // Bit 7: Y data Invert, 1=Y max to 0, 0=0 to Y max
    RAP_Write(FEEDCONFIG_1, CIRQUE_PINNACLE_POSITION_MODE << 1);

    // Host sets z-idle packet count to 5 (default is 0x1F/30)
    RAP_Write(Z_IDLE_COUNT, 5);

    cirque_pinnacle_set_adc_attenuation(CIRQUE_PINNACLE_ATTENUATION);

    cirque_pinnacle_tune_edge_sensitivity();
    cirque_pinnacle_enable_feed(true);
}

pinnacle_data_t cirque_pinnacle_read_data(void) {
    uint8_t         data_ready = 0;
    uint8_t         data[6]    = {0};
    pinnacle_data_t result     = {0};

    // Check if there is valid data available
    RAP_ReadBytes(STATUS_1, &data_ready, 1); // bit2 is Software Data Ready, bit3 is Command Complete, bit0 and bit1 are reserved/unused
    if ((data_ready & 0x04) == 0) {
        // no data available yet
        result.valid = false; // be explicit
        return result;
    }

    // Read all data bytes
    RAP_ReadBytes(PACKET_BYTE_0, data, 6);

    // Get ready for the next data sample
    cirque_pinnacle_clear_flags();

#if CIRQUE_PINNACLE_POSITION_MODE
    // Decode data for absolute mode
    // Register 0x13 is unused in this mode (palm detection area)
    result.buttonFlags = data[0] & 0x3F;                             // bit0 to bit5 are switch 0-5, only hardware button presses (from input pin on the Pinnacle chip)
    result.xValue      = data[2] | ((data[4] & 0x0F) << 8);          // merge high and low bits for X
    result.yValue      = data[3] | ((data[4] & 0xF0) << 4);          // merge high and low bits for Y
    result.zValue      = data[5] & 0x3F;                             // Z is only lower 6 bits, upper 2 bits are reserved/unused
    result.touchDown   = (result.xValue != 0 || result.yValue != 0); // (0,0) is a "magic coordinate" to indicate "finger touched down"
#else
    // Decode data for relative mode
    // Registers 0x16 and 0x17 are unused in this mode
    result.buttons    = data[0] & 0x07; // bit0 = primary button, bit1 = secondary button, bit2 = auxilary button, if Taps enabled then also software-recognized taps are reported
    result.xDelta     = data[1];
    result.yDelta     = data[2];
    result.wheelCount = data[3];
#endif

    result.valid = true;
    return result;
}
