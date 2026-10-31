/**
 * @file bt_task.h
 * @brief
 * @author Joy chang.li@westberrytech.com
 * @version 1.1.0
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022 Westberry Technology (ChangZhou) Corp., Ltd
 */

#pragma once

#include "bts_lib.h"
#include "quantum.h"

// #define BT_DEBUG_MODE
#define ENTRY_STOP_TIMEOUT 100 // ms
// #define ENTRY_STOP_TIMEOUT (30 * 60000) // ms

enum multimode_keycodes {
    BT_HOST1 = QK_KB_0,
    BT_HOST2,
    BT_HOST3,
    BT_2_4G,
    BT_USB,
    BT_VOL,
    BLED_MOD,
    BLED_HUI,
    BLED_VAI,
    BLED_SPI,
    WORK_MOD,
    // KC_FLXP,
    AN_TASK,
    KC_SPOTLIGHT,

    // RGB_TOG,
    // RGB_MOD,
    // RGB_HUD,
    // RGB_HUI,
    // RGB_SAD,
    // RGB_SAI,
    // RGB_VAD,
    // RGB_VAI,
    // RGB_SPD,
    // RGB_SPI,

    // RGB_TEST,
};

enum my_keycodes {
    RGB_TEST = SAFE_RANGE,
    KEY_WIN,
    KEY_AND,
    KEY_MAC,

};

typedef enum {
    MODE_WORKING,
    MODE_GAMING,
} bt_mode_t;

extern bt_mode_t mode;

typedef union {
    uint32_t raw;
    struct {
        uint8_t devs : 3;
        uint8_t last_devs : 3;
        uint8_t bled_speed;
        uint8_t bled_val;
        uint8_t bled_mode : 3;
        uint8_t bled_color : 4;
        uint8_t encoder_mode : 1;
    };
} dev_info_t;

extern dev_info_t dev_info;
extern bts_info_t bts_info;

void bt_housekeeping_task(void);
void led_config_all(void);
void led_deconfig_all(void);

/**
 * @brief bluetooth 初始化函数
 * @param None
 * @return None
 */
void bt_init(void);

/**
 * @brief bluetooth交互任务
 * @param None
 * @return None
 */
void bt_task(void);

/**
 * @brief 处理和BT相关的按键
 * @param keycode: 键值
 * @param record: 记录值
 * @return None
 */
bool bt_process_record(uint16_t keycode, keyrecord_t *record);

/**
 * @brief rgb指示灯任务
 * @param None
 * @return None
 */
bool bt_indicators_advanced(uint8_t led_min, uint8_t led_max);

/**
 * @brief 切换工作模式
 * @param None
 * @return None
 */
void bt_switch_mode(uint8_t last_mode, uint8_t now_mode, uint8_t reset);

/**
 * @brief usb suspend task
 * @param none
 * @param none
 * @return None
 */
void bt_housekeeping_task(void);
