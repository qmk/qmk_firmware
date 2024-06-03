// Copyright 2023 Dasky (@daskygit)
// Copyright 2023 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "azoteq_iqs5xx.h"
#include "pointing_device_internal.h"
#include "wait.h"

#ifndef AZOTEQ_IQS5XX_ADDRESS
#    define AZOTEQ_IQS5XX_ADDRESS (0x74 << 1)
#endif
#ifndef AZOTEQ_IQS5XX_TIMEOUT_MS
#    define AZOTEQ_IQS5XX_TIMEOUT_MS 10
#endif

#define AZOTEQ_IQS5XX_REG_PRODUCT_NUMBER 0x0000
#define AZOTEQ_IQS5XX_REG_PREVIOUS_CYCLE_TIME 0x000C
#define AZOTEQ_IQS5XX_REG_SYSTEM_CONTROL_1 0x0432
#define AZOTEQ_IQS5XX_REG_REPORT_RATE_ACTIVE 0x057A
#define AZOTEQ_IQS5XX_REG_SYSTEM_CONFIG_0 0x058E
#define AZOTEQ_IQS5XX_REG_SYSTEM_CONFIG_1 0x058F
#define AZOTEQ_IQS5XX_REG_X_RESOLUTION 0x066E
#define AZOTEQ_IQS5XX_REG_XY_CONFIG_0 0x0669
#define AZOTEQ_IQS5XX_REG_Y_RESOLUTION 0x0670
#define AZOTEQ_IQS5XX_REG_SINGLE_FINGER_GESTURES 0x06B7
#define AZOTEQ_IQS5XX_REG_END_COMMS 0xEEEE

// Gesture configuration
#ifndef AZOTEQ_IQS5XX_TAP_ENABLE
#    define AZOTEQ_IQS5XX_TAP_ENABLE true
#endif
#ifndef AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE
#    define AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE false
#endif
#ifndef AZOTEQ_IQS5XX_TWO_FINGER_TAP_ENABLE
#    define AZOTEQ_IQS5XX_TWO_FINGER_TAP_ENABLE true
#endif
#ifndef AZOTEQ_IQS5XX_SCROLL_ENABLE
#    define AZOTEQ_IQS5XX_SCROLL_ENABLE true
#endif
#ifndef AZOTEQ_IQS5XX_SWIPE_X_ENABLE
#    define AZOTEQ_IQS5XX_SWIPE_X_ENABLE false
#endif
#ifndef AZOTEQ_IQS5XX_SWIPE_Y_ENABLE
#    define AZOTEQ_IQS5XX_SWIPE_Y_ENABLE false
#endif
#ifndef AZOTEQ_IQS5XX_ZOOM_ENABLE
#    define AZOTEQ_IQS5XX_ZOOM_ENABLE false
#endif
#ifndef AZOTEQ_IQS5XX_TAP_TIME
#    define AZOTEQ_IQS5XX_TAP_TIME 0x96
#endif
#ifndef AZOTEQ_IQS5XX_TAP_DISTANCE
#    define AZOTEQ_IQS5XX_TAP_DISTANCE 0x19
#endif
#ifndef AZOTEQ_IQS5XX_HOLD_TIME
#    define AZOTEQ_IQS5XX_HOLD_TIME 0x12C
#endif
#ifndef AZOTEQ_IQS5XX_SWIPE_INITIAL_TIME
#    define AZOTEQ_IQS5XX_SWIPE_INITIAL_TIME 0x64 // 0x96
#endif
#ifndef AZOTEQ_IQS5XX_SWIPE_INITIAL_DISTANCE
#    define AZOTEQ_IQS5XX_SWIPE_INITIAL_DISTANCE 0x12C
#endif
#ifndef AZOTEQ_IQS5XX_SWIPE_CONSECUTIVE_TIME
#    define AZOTEQ_IQS5XX_SWIPE_CONSECUTIVE_TIME 0x0
#endif
#ifndef AZOTEQ_IQS5XX_SWIPE_CONSECUTIVE_DISTANCE
#    define AZOTEQ_IQS5XX_SWIPE_CONSECUTIVE_DISTANCE 0x7D0
#endif
#ifndef AZOTEQ_IQS5XX_SCROLL_INITIAL_DISTANCE
#    define AZOTEQ_IQS5XX_SCROLL_INITIAL_DISTANCE 0x32
#endif
#ifndef AZOTEQ_IQS5XX_ZOOM_INITIAL_DISTANCE
#    define AZOTEQ_IQS5XX_ZOOM_INITIAL_DISTANCE 0x32
#endif
#ifndef AZOTEQ_IQS5XX_ZOOM_CONSECUTIVE_DISTANCE
#    define AZOTEQ_IQS5XX_ZOOM_CONSECUTIVE_DISTANCE 0x19
#endif

#if defined(AZOTEQ_IQS5XX_TPS43)
#    define AZOTEQ_IQS5XX_WIDTH_MM 43
#    define AZOTEQ_IQS5XX_HEIGHT_MM 40
#    define AZOTEQ_IQS5XX_RESOLUTION_X 2048
#    define AZOTEQ_IQS5XX_RESOLUTION_Y 1792
#elif defined(AZOTEQ_IQS5XX_TPS65)
#    define AZOTEQ_IQS5XX_WIDTH_MM 65
#    define AZOTEQ_IQS5XX_HEIGHT_MM 49
#    define AZOTEQ_IQS5XX_RESOLUTION_X 3072
#    define AZOTEQ_IQS5XX_RESOLUTION_Y 2048
#elif !defined(AZOTEQ_IQS5XX_WIDTH_MM) && !defined(AZOTEQ_IQS5XX_HEIGHT_MM)
#    error "You must define one of the available azoteq trackpads or specify at least the width and height"
#endif

#define DIVIDE_UNSIGNED_ROUND(numerator, denominator) (((numerator) + ((denominator) / 2)) / (denominator))
#define AZOTEQ_IQS5XX_INCH_TO_RESOLUTION_X(inch) (DIVIDE_UNSIGNED_ROUND((inch) * (uint32_t)AZOTEQ_IQS5XX_WIDTH_MM * 10, 254))
#define AZOTEQ_IQS5XX_RESOLUTION_X_TO_INCH(px) (DIVIDE_UNSIGNED_ROUND((px) * (uint32_t)254, AZOTEQ_IQS5XX_WIDTH_MM * 10))
#define AZOTEQ_IQS5XX_INCH_TO_RESOLUTION_Y(inch) (DIVIDE_UNSIGNED_ROUND((inch) * (uint32_t)AZOTEQ_IQS5XX_HEIGHT_MM * 10, 254))
#define AZOTEQ_IQS5XX_RESOLUTION_Y_TO_INCH(px) (DIVIDE_UNSIGNED_ROUND((px) * (uint32_t)254, AZOTEQ_IQS5XX_HEIGHT_MM * 10))

static uint16_t azoteq_iqs5xx_product_number = AZOTEQ_IQS5XX_UNKNOWN;

static struct {
    uint16_t resolution_x;
    uint16_t resolution_y;
} azoteq_iqs5xx_device_resolution_t;

i2c_status_t azoteq_iqs5xx_wake(void) {
    uint8_t      data   = 0;
    i2c_status_t status = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_PREVIOUS_CYCLE_TIME, (uint8_t *)&data, sizeof(data), 1);
    wait_us(150);
    return status;
}
i2c_status_t azoteq_iqs5xx_end_session(void) {
    const uint8_t END_BYTE = 1; // any data
    return i2c_write_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_END_COMMS, &END_BYTE, 1, AZOTEQ_IQS5XX_TIMEOUT_MS);
}

i2c_status_t azoteq_iqs5xx_get_base_data(azoteq_iqs5xx_base_data_t *base_data) {
    i2c_status_t status = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_PREVIOUS_CYCLE_TIME, (uint8_t *)base_data, 10, AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (status == I2C_STATUS_SUCCESS) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

i2c_status_t azoteq_iqs5xx_get_report_rate(azoteq_iqs5xx_report_rate_t *report_rate, azoteq_iqs5xx_charging_modes_t mode, bool end_session) {
    if (mode > AZOTEQ_IQS5XX_LP2) {
        pd_dprintf("IQS5XX - Invalid mode for get report rate.\n");
        return I2C_STATUS_ERROR;
    }
    uint16_t     selected_reg = AZOTEQ_IQS5XX_REG_REPORT_RATE_ACTIVE + (2 * mode);
    i2c_status_t status       = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, selected_reg, (uint8_t *)report_rate, 2, AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (end_session) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

i2c_status_t azoteq_iqs5xx_set_report_rate(uint16_t report_rate_ms, azoteq_iqs5xx_charging_modes_t mode, bool end_session) {
    if (mode > AZOTEQ_IQS5XX_LP2) {
        pd_dprintf("IQS5XX - Invalid mode for set report rate.\n");
        return I2C_STATUS_ERROR;
    }
    uint16_t                    selected_reg = AZOTEQ_IQS5XX_REG_REPORT_RATE_ACTIVE + (2 * mode);
    azoteq_iqs5xx_report_rate_t report_rate  = {0};
    report_rate.h                            = (uint8_t)((report_rate_ms >> 8) & 0xFF);
    report_rate.l                            = (uint8_t)(report_rate_ms & 0xFF);
    i2c_status_t status                      = i2c_write_register16(AZOTEQ_IQS5XX_ADDRESS, selected_reg, (uint8_t *)&report_rate, 2, AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (end_session) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

i2c_status_t azoteq_iqs5xx_set_reati(bool enabled, bool end_session) {
    azoteq_iqs5xx_system_config_0_t config = {0};
    i2c_status_t                    status = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SYSTEM_CONFIG_0, (uint8_t *)&config, sizeof(azoteq_iqs5xx_system_config_0_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (status == I2C_STATUS_SUCCESS) {
        config.reati = enabled;
        status       = i2c_write_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SYSTEM_CONFIG_0, (uint8_t *)&config, sizeof(azoteq_iqs5xx_system_config_0_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    }
    if (end_session) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

i2c_status_t azoteq_iqs5xx_set_event_mode(bool enabled, bool end_session) {
    azoteq_iqs5xx_system_config_1_t config = {0};
    i2c_status_t                    status = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SYSTEM_CONFIG_1, (uint8_t *)&config, sizeof(azoteq_iqs5xx_system_config_1_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (status == I2C_STATUS_SUCCESS) {
        config.event_mode     = enabled;
        config.touch_event    = true;
        config.tp_event       = true;
        config.prox_event     = false;
        config.snap_event     = false;
        config.reati_event    = false;
        config.alp_prox_event = false;
        config.gesture_event  = true;
        status                = i2c_write_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SYSTEM_CONFIG_1, (uint8_t *)&config, sizeof(azoteq_iqs5xx_system_config_1_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    }
    if (end_session) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

i2c_status_t azoteq_iqs5xx_set_gesture_config(bool end_session) {
    azoteq_iqs5xx_gesture_config_t config = {0};
    i2c_status_t                   status = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SINGLE_FINGER_GESTURES, (uint8_t *)&config, sizeof(azoteq_iqs5xx_gesture_config_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    pd_dprintf("azo scroll: %d\n", config.multi_finger_gestures.scroll);
    if (status == I2C_STATUS_SUCCESS) {
        config.single_finger_gestures.single_tap     = AZOTEQ_IQS5XX_TAP_ENABLE;
        config.single_finger_gestures.press_and_hold = AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE;
        config.single_finger_gestures.swipe_x_plus   = AZOTEQ_IQS5XX_SWIPE_X_ENABLE;
        config.single_finger_gestures.swipe_x_minus  = AZOTEQ_IQS5XX_SWIPE_X_ENABLE;
        config.single_finger_gestures.swipe_y_plus   = AZOTEQ_IQS5XX_SWIPE_Y_ENABLE;
        config.single_finger_gestures.swipe_y_minus  = AZOTEQ_IQS5XX_SWIPE_Y_ENABLE;
        config.multi_finger_gestures.two_finger_tap  = AZOTEQ_IQS5XX_TWO_FINGER_TAP_ENABLE;
        config.multi_finger_gestures.scroll          = AZOTEQ_IQS5XX_SCROLL_ENABLE;
        config.multi_finger_gestures.zoom            = AZOTEQ_IQS5XX_ZOOM_ENABLE;
        config.tap_time                              = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_TAP_TIME);
        config.tap_distance                          = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_TAP_DISTANCE);
        config.hold_time                             = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_HOLD_TIME);
        config.swipe_initial_time                    = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_SWIPE_INITIAL_TIME);
        config.swipe_initial_distance                = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_SWIPE_INITIAL_DISTANCE);
        config.swipe_consecutive_time                = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_SWIPE_CONSECUTIVE_TIME);
        config.swipe_consecutive_distance            = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_SWIPE_CONSECUTIVE_DISTANCE);
        config.scroll_initial_distance               = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_SCROLL_INITIAL_DISTANCE);
        config.zoom_initial_distance                 = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_ZOOM_INITIAL_DISTANCE);
        config.zoom_consecutive_distance             = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(AZOTEQ_IQS5XX_ZOOM_CONSECUTIVE_DISTANCE);
        status                                       = i2c_write_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SINGLE_FINGER_GESTURES, (uint8_t *)&config, sizeof(azoteq_iqs5xx_gesture_config_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    }
    if (end_session) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

i2c_status_t azoteq_iqs5xx_set_xy_config(bool flip_x, bool flip_y, bool switch_xy, bool palm_reject, bool end_session) {
    azoteq_iqs5xx_xy_config_0_t config = {0};
    i2c_status_t                status = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_XY_CONFIG_0, (uint8_t *)&config, sizeof(azoteq_iqs5xx_xy_config_0_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (status == I2C_STATUS_SUCCESS) {
        if (flip_x) {
            config.flip_x = !config.flip_x;
        }
        if (flip_y) {
            config.flip_y = !config.flip_y;
        }
        if (switch_xy) {
            config.switch_xy_axis = !config.switch_xy_axis;
        }
        config.palm_reject = palm_reject;
        status             = i2c_write_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_XY_CONFIG_0, (uint8_t *)&config, sizeof(azoteq_iqs5xx_xy_config_0_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    }
    if (end_session) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

i2c_status_t azoteq_iqs5xx_reset_suspend(bool reset, bool suspend, bool end_session) {
    azoteq_iqs5xx_system_control_1_t config = {0};
    i2c_status_t                     status = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SYSTEM_CONTROL_1, (uint8_t *)&config, sizeof(azoteq_iqs5xx_system_control_1_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (status == I2C_STATUS_SUCCESS) {
        config.reset   = reset;
        config.suspend = suspend;
        status         = i2c_write_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SYSTEM_CONTROL_1, (uint8_t *)&config, sizeof(azoteq_iqs5xx_system_control_1_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    }
    if (end_session) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

void azoteq_iqs5xx_set_cpi(uint16_t cpi) {
    if (azoteq_iqs5xx_product_number != AZOTEQ_IQS5XX_UNKNOWN) {
        azoteq_iqs5xx_resolution_t resolution = {0};
        resolution.x_resolution               = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(MIN(azoteq_iqs5xx_device_resolution_t.resolution_x, AZOTEQ_IQS5XX_INCH_TO_RESOLUTION_X(cpi)));
        resolution.y_resolution               = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(MIN(azoteq_iqs5xx_device_resolution_t.resolution_y, AZOTEQ_IQS5XX_INCH_TO_RESOLUTION_Y(cpi)));
        i2c_write_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_X_RESOLUTION, (uint8_t *)&resolution, sizeof(azoteq_iqs5xx_resolution_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    }
}

uint16_t azoteq_iqs5xx_get_cpi(void) {
    if (azoteq_iqs5xx_product_number != AZOTEQ_IQS5XX_UNKNOWN) {
        azoteq_iqs5xx_resolution_t resolution = {0};
        i2c_status_t               status     = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_X_RESOLUTION, (uint8_t *)&resolution, sizeof(azoteq_iqs5xx_resolution_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
        if (status == I2C_STATUS_SUCCESS) {
            return AZOTEQ_IQS5XX_RESOLUTION_X_TO_INCH(AZOTEQ_IQS5XX_SWAP_H_L_BYTES(resolution.x_resolution));
        }
    }
    return 0;
}

uint16_t azoteq_iqs5xx_get_product(void) {
    i2c_status_t status = i2c_read_register16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_PRODUCT_NUMBER, (uint8_t *)&azoteq_iqs5xx_product_number, sizeof(uint16_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (status == I2C_STATUS_SUCCESS) {
        azoteq_iqs5xx_product_number = AZOTEQ_IQS5XX_SWAP_H_L_BYTES(azoteq_iqs5xx_product_number);
    }
    pd_dprintf("AZOTEQ: Product number %u\n", azoteq_iqs5xx_product_number);
    return azoteq_iqs5xx_product_number;
}

void azoteq_iqs5xx_setup_resolution(void) {
#if !defined(AZOTEQ_IQS5XX_RESOLUTION_X) && !defined(AZOTEQ_IQS5XX_RESOLUTION_Y)
    switch (azoteq_iqs5xx_product_number) {
        case AZOTEQ_IQS550:
            azoteq_iqs5xx_device_resolution_t.resolution_x = 3584;
            azoteq_iqs5xx_device_resolution_t.resolution_y = 2304;
            break;
        case AZOTEQ_IQS572:
            azoteq_iqs5xx_device_resolution_t.resolution_x = 2048;
            azoteq_iqs5xx_device_resolution_t.resolution_y = 1792;
            break;
        case AZOTEQ_IQS525:
            azoteq_iqs5xx_device_resolution_t.resolution_x = 1280;
            azoteq_iqs5xx_device_resolution_t.resolution_y = 768;
            break;
        default:
            // shouldn't be here
            azoteq_iqs5xx_device_resolution_t.resolution_x = 0;
            azoteq_iqs5xx_device_resolution_t.resolution_y = 0;
            break;
    }
#endif
#ifdef AZOTEQ_IQS5XX_RESOLUTION_X
    azoteq_iqs5xx_device_resolution_t.resolution_x = AZOTEQ_IQS5XX_RESOLUTION_X;
#endif
#ifdef AZOTEQ_IQS5XX_RESOLUTION_Y
    azoteq_iqs5xx_device_resolution_t.resolution_y = AZOTEQ_IQS5XX_RESOLUTION_Y;
#endif
}
