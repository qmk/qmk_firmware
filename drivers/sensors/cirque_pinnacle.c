// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
// based on https://github.com/cirque-corp/Cirque_Pinnacle_1CA027/tree/master/Circular_Trackpad
// with modifications and changes for QMK
// refer to documentation: Gen2 and Gen3 (Pinnacle ASIC) at https://www.cirque.com/documentation

#include "cirque_pinnacle.h"
#include "wait.h"
#include "timer.h"

#include <stdlib.h>

#ifndef CIRQUE_PINNACLE_ATTENUATION
#    ifdef CIRQUE_PINNACLE_CURVED_OVERLAY
#        define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X
#    else
#        define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X
#    endif
#endif

bool     touchpad_init;
uint16_t scale_data = CIRQUE_PINNACLE_DEFAULT_SCALE;

void cirque_pinnacle_clear_flags(void);
void cirque_pinnacle_enable_feed(bool feedEnable);
void RAP_ReadBytes(uint8_t address, uint8_t* data, uint8_t count);
void RAP_Write(uint8_t address, uint8_t data);

#if CIRQUE_PINNACLE_POSITION_MODE
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
#endif

uint16_t cirque_pinnacle_get_scale(void) {
    return scale_data;
}
void cirque_pinnacle_set_scale(uint16_t scale) {
    scale_data = scale;
}

// Scales data to desired X & Y resolution
void cirque_pinnacle_scale_data(pinnacle_data_t* coordinates, uint16_t xResolution, uint16_t yResolution) {
#if CIRQUE_PINNACLE_POSITION_MODE
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
#else
    int32_t        xTemp = 0, yTemp = 0;
    ldiv_t         temp;
    static int32_t xRemainder, yRemainder;

    temp       = ldiv(((int32_t)coordinates->xDelta) * (int32_t)xResolution + xRemainder, (int32_t)CIRQUE_PINNACLE_X_RANGE);
    xTemp      = temp.quot;
    xRemainder = temp.rem;

    temp       = ldiv(((int32_t)coordinates->yDelta) * (int32_t)yResolution + yRemainder, (int32_t)CIRQUE_PINNACLE_Y_RANGE);
    yTemp      = temp.quot;
    yRemainder = temp.rem;

    coordinates->xDelta = (int16_t)xTemp;
    coordinates->yDelta = (int16_t)yTemp;
#endif
}

// Clears Status1 register flags (SW_CC and SW_DR)
void cirque_pinnacle_clear_flags(void) {
    RAP_Write(HOSTREG__STATUS1, HOSTREG__STATUS1_DEFVAL & ~(HOSTREG__STATUS1__COMMAND_COMPLETE | HOSTREG__STATUS1__DATA_READY));
    wait_us(50);
}

// Enables/Disables the feed
void cirque_pinnacle_enable_feed(bool feedEnable) {
    uint8_t feedconfig1;
    RAP_ReadBytes(HOSTREG__FEEDCONFIG1, &feedconfig1, 1);

    if (feedEnable) {
        feedconfig1 |= HOSTREG__FEEDCONFIG1__FEED_ENABLE;
    } else {
        feedconfig1 &= ~HOSTREG__FEEDCONFIG1__FEED_ENABLE;
    }
    RAP_Write(HOSTREG__FEEDCONFIG1, feedconfig1);
}

/*  ERA (Extended Register Access) Functions  */
// Reads <count> bytes from an extended register at <address> (16-bit address),
// stores values in <*data>
void ERA_ReadBytes(uint16_t address, uint8_t* data, uint16_t count) {
    uint8_t  ERAControlValue = 0xFF;
    uint16_t timeout_timer;

    cirque_pinnacle_enable_feed(false); // Disable feed

    RAP_Write(HOSTREG__EXT_REG_AXS_ADDR_HIGH, (uint8_t)(address >> 8));    // Send upper byte of ERA address
    RAP_Write(HOSTREG__EXT_REG_AXS_ADDR_LOW, (uint8_t)(address & 0x00FF)); // Send lower byte of ERA address

    for (uint16_t i = 0; i < count; i++) {
        RAP_Write(HOSTREG__EXT_REG_AXS_CTRL, HOSTREG__EREG_AXS__INC_ADDR_READ | HOSTREG__EREG_AXS__READ); // Signal ERA-read (auto-increment) to Pinnacle

        // Wait for status register 0x1E to clear
        timeout_timer = timer_read();
        do {
            RAP_ReadBytes(HOSTREG__EXT_REG_AXS_CTRL, &ERAControlValue, 1);
        } while ((ERAControlValue != 0x00) && (timer_elapsed(timeout_timer) <= CIRQUE_PINNACLE_TIMEOUT));

        RAP_ReadBytes(HOSTREG__EXT_REG_AXS_VALUE, data + i, 1);

        cirque_pinnacle_clear_flags();
    }
}

// Writes a byte, <data>, to an extended register at <address> (16-bit address)
void ERA_WriteByte(uint16_t address, uint8_t data) {
    uint8_t  ERAControlValue = 0xFF;
    uint16_t timeout_timer;

    cirque_pinnacle_enable_feed(false); // Disable feed

    RAP_Write(HOSTREG__EXT_REG_AXS_VALUE, data); // Send data byte to be written

    RAP_Write(HOSTREG__EXT_REG_AXS_ADDR_HIGH, (uint8_t)(address >> 8));    // Upper byte of ERA address
    RAP_Write(HOSTREG__EXT_REG_AXS_ADDR_LOW, (uint8_t)(address & 0x00FF)); // Lower byte of ERA address

    RAP_Write(HOSTREG__EXT_REG_AXS_CTRL, HOSTREG__EREG_AXS__WRITE); // Signal an ERA-write to Pinnacle

    // Wait for status register 0x1E to clear
    timeout_timer = timer_read();
    do {
        RAP_ReadBytes(HOSTREG__EXT_REG_AXS_CTRL, &ERAControlValue, 1);
    } while ((ERAControlValue != 0x00) && (timer_elapsed(timeout_timer) <= CIRQUE_PINNACLE_TIMEOUT));

    cirque_pinnacle_clear_flags();
}

bool cirque_pinnacle_set_adc_attenuation(uint8_t adcGain) {
    uint8_t adcconfig = 0x00;

    ERA_ReadBytes(EXTREG__TRACK_ADCCONFIG, &adcconfig, 1);
    adcGain &= EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_MASK;
    if (adcGain == (adcconfig & EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_MASK)) {
        return false;
    }
    adcconfig &= ~EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_MASK;
    adcconfig |= adcGain;
    ERA_WriteByte(EXTREG__TRACK_ADCCONFIG, adcconfig);
    ERA_ReadBytes(EXTREG__TRACK_ADCCONFIG, &adcconfig, 1);

    return true;
}

// Changes thresholds to improve detection of fingers
// Not needed for flat overlay?
void cirque_pinnacle_tune_edge_sensitivity(void) {
    uint8_t widezmin = 0x00;

    ERA_ReadBytes(EXTREG__XAXIS_WIDEZMIN, &widezmin, 1);
    ERA_WriteByte(EXTREG__XAXIS_WIDEZMIN, 0x04); // magic number from Cirque sample code
    ERA_ReadBytes(EXTREG__XAXIS_WIDEZMIN, &widezmin, 1);

    ERA_ReadBytes(EXTREG__YAXIS_WIDEZMIN, &widezmin, 1);
    ERA_WriteByte(EXTREG__YAXIS_WIDEZMIN, 0x03); // magic number from Cirque sample code
    ERA_ReadBytes(EXTREG__YAXIS_WIDEZMIN, &widezmin, 1);
}

// Perform calibration
void cirque_pinnacle_calibrate(void) {
    uint8_t  calconfig;
    uint16_t timeout_timer;

    RAP_ReadBytes(HOSTREG__CALCONFIG1, &calconfig, 1);
    calconfig |= HOSTREG__CALCONFIG1__CALIBRATE;
    RAP_Write(HOSTREG__CALCONFIG1, calconfig);

    // Calibration takes ~100ms according to GT-AN-090624, doubling the timeout just to be safe
    timeout_timer = timer_read();
    do {
        RAP_ReadBytes(HOSTREG__CALCONFIG1, &calconfig, 1);
    } while ((calconfig & HOSTREG__CALCONFIG1__CALIBRATE) && (timer_elapsed(timeout_timer) <= 200));

    cirque_pinnacle_clear_flags();
}

// Enable/disable cursor smoothing, smoothing is enabled by default
void cirque_pinnacle_cursor_smoothing(bool enable) {
    uint8_t feedconfig3;

    RAP_ReadBytes(HOSTREG__FEEDCONFIG3, &feedconfig3, 1);
    if (enable) {
        feedconfig3 &= ~HOSTREG__FEEDCONFIG3__DISABLE_CROSS_RATE_SMOOTHING;
    } else {
        feedconfig3 |= HOSTREG__FEEDCONFIG3__DISABLE_CROSS_RATE_SMOOTHING;
    }
    RAP_Write(HOSTREG__FEEDCONFIG3, feedconfig3);
}

// Check sensor is connected
bool cirque_pinnacle_connected(void) {
    uint8_t current_zidle = 0;
    uint8_t temp_zidle    = 0;
    RAP_ReadBytes(HOSTREG__ZIDLE, &current_zidle, 1);
    RAP_Write(HOSTREG__ZIDLE, HOSTREG__ZIDLE_DEFVAL);
    RAP_ReadBytes(HOSTREG__ZIDLE, &temp_zidle, 1);
    if (temp_zidle == HOSTREG__ZIDLE_DEFVAL) {
        RAP_Write(HOSTREG__ZIDLE, current_zidle);
        return true;
    }
    return false;
}

/*  Pinnacle-based TM040040/TM035035/TM023023 Functions  */
void cirque_pinnacle_init(void) {
#if defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_spi)
    spi_init();
#elif defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_i2c)
    i2c_init();
#endif

    touchpad_init = true;

    // send a RESET command now, in case QMK had a soft-reset without a power cycle
    RAP_Write(HOSTREG__SYSCONFIG1, HOSTREG__SYSCONFIG1__RESET);
    wait_ms(30); // Pinnacle needs 10-15ms to boot, so wait long enough before configuring
    RAP_Write(HOSTREG__SYSCONFIG1, HOSTREG__SYSCONFIG1_DEFVAL);
    wait_us(50);

    // Host clears SW_CC flag
    cirque_pinnacle_clear_flags();

#if CIRQUE_PINNACLE_POSITION_MODE
    RAP_Write(HOSTREG__FEEDCONFIG2, HOSTREG__FEEDCONFIG2_DEFVAL);
#else
    // FeedConfig2 (Feature flags for Relative Mode Only)
    uint8_t feedconfig2 = HOSTREG__FEEDCONFIG2__GLIDE_EXTEND_DISABLE | HOSTREG__FEEDCONFIG2__INTELLIMOUSE_MODE;
#    if !defined(CIRQUE_PINNACLE_TAP_ENABLE)
    feedconfig2 |= HOSTREG__FEEDCONFIG2__ALL_TAP_DISABLE;
#    endif
#    if !defined(CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE)
    feedconfig2 |= HOSTREG__FEEDCONFIG2__SECONDARY_TAP_DISABLE;
#    elif !defined(CIRQUE_PINNACLE_TAP_ENABLE)
#        error CIRQUE_PINNACLE_TAP_ENABLE must be defined for CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE to work
#    endif
#    if !defined(CIRQUE_PINNACLE_SIDE_SCROLL_ENABLE)
    feedconfig2 |= HOSTREG__FEEDCONFIG2__SCROLL_DISABLE;
#    endif
    RAP_Write(HOSTREG__FEEDCONFIG2, feedconfig2);
#endif

    // FeedConfig1 (Data Output Flags)
    RAP_Write(HOSTREG__FEEDCONFIG1, CIRQUE_PINNACLE_POSITION_MODE ? HOSTREG__FEEDCONFIG1__DATA_TYPE__REL0_ABS1 : HOSTREG__FEEDCONFIG1_DEFVAL);

#if CIRQUE_PINNACLE_POSITION_MODE
    // Host sets z-idle packet count to 5 (default is 0x1E/30)
    RAP_Write(HOSTREG__ZIDLE, 5);
#endif

    bool calibrate = cirque_pinnacle_set_adc_attenuation(CIRQUE_PINNACLE_ATTENUATION);

#ifdef CIRQUE_PINNACLE_CURVED_OVERLAY
    cirque_pinnacle_tune_edge_sensitivity();
    calibrate = true;
#endif
    if (calibrate) {
        // Force a calibration after setting ADC attenuation
        cirque_pinnacle_calibrate();
    }

    cirque_pinnacle_enable_feed(true);

#ifndef CIRQUE_PINNACLE_SKIP_SENSOR_CHECK
    touchpad_init = cirque_pinnacle_connected();
#endif
}

pinnacle_data_t cirque_pinnacle_read_data(void) {
    uint8_t         data_ready = 0;
    uint8_t         data[6]    = {0};
    pinnacle_data_t result     = {0};

    // Check if there is valid data available
    RAP_ReadBytes(HOSTREG__STATUS1, &data_ready, 1);
    if ((data_ready & HOSTREG__STATUS1__DATA_READY) == 0) {
        // no data available yet
        result.valid = false; // be explicit
        return result;
    }

    // Read all data bytes
    RAP_ReadBytes(HOSTREG__PACKETBYTE_0, data, 6);

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
    result.buttons = data[0] & 0x07; // Only three buttons are supported
    if ((data[0] & 0x10) && data[1] != 0) {
        result.xDelta = -((int16_t)256 - (int16_t)(data[1]));
    } else {
        result.xDelta = data[1];
    }
    if ((data[0] & 0x20) && data[2] != 0) {
        result.yDelta = ((int16_t)256 - (int16_t)(data[2]));
    } else {
        result.yDelta = -((int16_t)data[2]);
    }
    result.wheelCount = ((int8_t*)data)[3];
#endif

#ifdef CIRQUE_PINNACLE_REACHABLE_CALIBRATION
    static uint16_t xMin = UINT16_MAX, yMin = UINT16_MAX, yMax = 0, xMax = 0;
    if (result.xValue < xMin) xMin = result.xValue;
    if (result.xValue > xMax) xMax = result.xValue;
    if (result.yValue < yMin) yMin = result.yValue;
    if (result.yValue > yMax) yMax = result.yValue;
    pd_dprintf("%s: xLo=%3d xHi=%3d yLo=%3d yHi=%3d\n", __FUNCTION__, xMin, xMax, yMin, yMax);
#endif

    result.valid = true;
    return result;
}
