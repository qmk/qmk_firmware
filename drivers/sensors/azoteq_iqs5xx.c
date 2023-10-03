// Copyright 2023 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "azoteq_iqs5xx.h"
#include "pointing_device_internal.h"

#define AZOTEQ_IQS5XX_ADDRESS 0x74 << 1
#define AZOTEQ_IQS5XX_TIMEOUT_MS 10

#define AZOTEQ_IQS5XX_REG_PRODUCT_NUMBER 0x0000
#define AZOTEQ_IQS5XX_REG_PROJECT_NUMBER 0x0002
#define AZOTEQ_IQS5XX_REG_MAJOR_VERSION 0x0004
#define AZOTEQ_IQS5XX_REG_MINOR_VERSION 0x0005
#define AZOTEQ_IQS5XX_REG_BOOTLOADER_STATUS 0x0006
#define AZOTEQ_IQS5XX_REG_MAX_TOUCH_COL_ROW 0x000B
#define AZOTEQ_IQS5XX_REG_PREVIOUS_CYCLE_TIME 0x000C
#define AZOTEQ_IQS5XX_REG_GESTURE_EVENTS_O 0x000D
#define AZOTEQ_IQS5XX_REG_GESTURE_EVENTS_1 0x000E
#define AZOTEQ_IQS5XX_REG_SYSTEM_INFO_0 0x000F
#define AZOTEQ_IQS5XX_REG_SYSTEM_INFO_1 0x0010

#define AZOTEQ_IQS5XX_REG_NUMBER_OF_FINGERS 0x0011
#define AZOTEQ_IQS5XX_REG_RELATIVE_X 0x0012
#define AZOTEQ_IQS5XX_REG_RELATIVE_Y 0x0014

// Finger 1
#define AZOTEQ_IQS5XX_REG_ABSOLUTE_X 0x0016
#define AZOTEQ_IQS5XX_REG_ABSOLUTE_Y 0x0018
#define AZOTEQ_IQS5XX_REG_TOUCH_STRENGTH 0x001A
#define AZOTEQ_IQS5XX_REG_TOUCH_AREA 0x001C
// Finger 2
#define AZOTEQ_IQS5XX_REG_ABSOLUTE_X_2 0x001D
// Finger 3
#define AZOTEQ_IQS5XX_REG_ABSOLUTE_X_3 0x0024
// Finger 4
#define AZOTEQ_IQS5XX_REG_ABSOLUTE_X_4 0x002B
// Finger 5
#define AZOTEQ_IQS5XX_REG_ABSOLUTE_X_5 0x0032

#define AZOTEQ_IQS5XX_REG_REPORT_RATE_ACTIVE 0x057A
#define AZOTEQ_IQS5XX_REG_REPORT_RATE_IDLE_TOUCH 0x057C
#define AZOTEQ_IQS5XX_REG_REPORT_RATE_IDLE 0x057E
#define AZOTEQ_IQS5XX_REG_REPORT_RATE_LP1 0x0580
#define AZOTEQ_IQS5XX_REG_REPORT_RATE_LP2 0x0582

#define AZOTEQ_IQS5XX_REG_SYSTEM_CONFIG_1 0x058F

#define AZOTEQ_IQS5XX_REG_SINGLE_FINGER_GESTURES 0x06B7
#define AZOTEQ_IQS5XX_REG_MULTI_FINGER_GESTURES 0x06B8

#define AZOTEQ_IQS5XX_REG_ 0x000

#define AZOTEQ_IQS5XX_REG_END_COMMS 0xEEEE

i2c_status_t azoteq_iqs5xx_end_session(void) {
    const uint8_t END_BYTE = 1; // any data
    return i2c_writeReg16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_END_COMMS, &END_BYTE, 1, AZOTEQ_IQS5XX_TIMEOUT_MS);
}

i2c_status_t azoteq_iqs5xx_get_base_data(azoteq_iqs5xx_base_data_t *base_data) {
    //azoteq_iqs5xx_report_rate_t  report_rate  = {0};
    //azoteq_iqs5xx_get_report_rate(&report_rate, ACTIVE, false);
    i2c_status_t status = i2c_readReg16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_PREVIOUS_CYCLE_TIME, (uint8_t *)base_data,10, AZOTEQ_IQS5XX_TIMEOUT_MS);
    //uint16_t report_rate_f = AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(report_rate.h, report_rate.l);
    // uprintf("report rate: %d missed: %d mode: %d\n", report_rate_f, basic_report.system_info_1.rr_missed, basic_report.system_info_0.charging_mode);
    // if (report_rate_f == 13){
    //         azoteq_iqs5xx_set_report_rate(8, ACTIVE, true);
    // }
    azoteq_iqs5xx_end_session();
    return status;
}

i2c_status_t azoteq_iqs5xx_get_report_rate(azoteq_iqs5xx_report_rate_t *report_rate, azoteq_charging_modes_t mode, bool END_SESSION) {
    if (mode > LP2) {
        pd_dprintf("IQS5XX - Invalid mode for get report rate.\n");
        return I2C_STATUS_ERROR;
    }
    uint16_t     selected_reg = AZOTEQ_IQS5XX_REG_REPORT_RATE_ACTIVE + (2 * mode);
    i2c_status_t status       = i2c_readReg16(AZOTEQ_IQS5XX_ADDRESS, selected_reg, (uint8_t *)report_rate, 2, AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (END_SESSION) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

i2c_status_t azoteq_iqs5xx_set_report_rate(uint16_t report_rate_ms, azoteq_charging_modes_t mode, bool END_SESSION) {
    if (mode > LP2) {
        pd_dprintf("IQS5XX - Invalid mode for set report rate.\n");
        return I2C_STATUS_ERROR;
    }
    uint16_t     selected_reg = AZOTEQ_IQS5XX_REG_REPORT_RATE_ACTIVE + (2 * mode);
    azoteq_iqs5xx_report_rate_t report_rate = {0};
    report_rate.h                           = (uint8_t)((report_rate_ms >> 8) & 0xFF);
    report_rate.l                           = (uint8_t)(report_rate_ms & 0xFF);
    i2c_status_t status                     = i2c_writeReg16(AZOTEQ_IQS5XX_ADDRESS, selected_reg, (uint8_t *)&report_rate, 2, AZOTEQ_IQS5XX_TIMEOUT_MS);

    if (END_SESSION) {
        azoteq_iqs5xx_end_session();
    }
    return status;
}

void azoteq_iqs5xx_set_event_mode(bool enabled) {
    azoteq_iqs5xx_system_config_1_t config = {0};
    i2c_status_t                    status = i2c_readReg16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SYSTEM_CONFIG_1, (uint8_t *)&config, sizeof(azoteq_iqs5xx_system_config_1_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (status == I2C_STATUS_SUCCESS) {
        config.event_mode  = true;
        config.touch_event = true;
        config.tp_event    = true;
        status             = i2c_writeReg16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SYSTEM_CONFIG_1, (uint8_t *)&config, sizeof(azoteq_iqs5xx_system_config_1_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    }
    azoteq_iqs5xx_end_session();
}

void azoteq_iqs5xx_set_gesture_config(void) {
    azoteq_iqs5xx_gesture_config_t config = {0};
    i2c_status_t                 status = i2c_readReg16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SINGLE_FINGER_GESTURES, (uint8_t *)&config, sizeof(azoteq_iqs5xx_gesture_config_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    if (status == I2C_STATUS_SUCCESS) {
        config.single_finger_gestures.single_tap    = true;
        config.single_finger_gestures.press_and_hold= true;
        config.multi_finger_gestures.two_finger_tap = true;
        config.multi_finger_gestures.scroll         = true;
        config.tap_time                             = 500;
        config.hold_time                            = 1000;
        config.tap_distance                         = 10;
        config.scroll_initial_distance              = 5;
        status = i2c_writeReg16(AZOTEQ_IQS5XX_ADDRESS, AZOTEQ_IQS5XX_REG_SINGLE_FINGER_GESTURES, (uint8_t *)&config, sizeof(azoteq_iqs5xx_gesture_config_t), AZOTEQ_IQS5XX_TIMEOUT_MS);
    }
    azoteq_iqs5xx_end_session();
}

void azoteq_iqs5xx_init(void) {
    i2c_init();
    azoteq_iqs5xx_set_report_rate(5, ACTIVE, true);
    azoteq_iqs5xx_set_event_mode(true);
    azoteq_iqs5xx_set_gesture_config();
};

report_mouse_t azoteq_iqs5xx_get_report(report_mouse_t mouse_report) {
    report_mouse_t              temp_report = {0};
    azoteq_iqs5xx_base_data_t   base_data = {0};
    i2c_status_t status = azoteq_iqs5xx_get_base_data(&base_data);

    if (status == I2C_STATUS_SUCCESS) {
        if (base_data.gesture_events_0.single_tap || base_data.gesture_events_0.press_and_hold) {
            temp_report.buttons = pointing_device_handle_buttons(temp_report.buttons, true, POINTING_DEVICE_BUTTON1);
        }
        if (base_data.gesture_events_1.two_finger_tap) {
            temp_report.buttons = pointing_device_handle_buttons(temp_report.buttons, true, POINTING_DEVICE_BUTTON2);
        }
        if (base_data.gesture_events_1.scroll) {
#if defined(MOUSE_EXTENDED_REPORT)
            temp_report.v = (int16_t) AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.x.h, base_data.x.l);
#else
            temp_report.v = (int8_t) base_data.x.l;
#endif
        }
        else if (base_data.number_of_fingers != 0) {
#if defined(MOUSE_EXTENDED_REPORT)
            temp_report.x = (int16_t)AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.x.h, base_data.x.l);
            temp_report.y = (int16_t)AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.y.h, base_data.y.l);
#else
            temp_report.x = (int8_t)base_data.x.l;
            temp_report.y = (int8_t)base_data.y.l;
#endif
        }
    }

    return temp_report;
}
