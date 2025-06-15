#pragma once

#include "quantum.h"
#include "via.h"

// 枚举名和 VIA 配置字符串完全一致，数值也要一致
enum via_custom_value_id {
    id_bool_keyboard = 2,      // BOOL按钮
    id_reset_keyboard = 3,     // 重置键盘
};

#ifdef VIA_CUSTOM_CONTROL_ENABLE
void via_custom_value_command_user(uint8_t *data, uint8_t length);
#else
void via_custom_value_command_kb(uint8_t *data, uint8_t length);
#endif
void via_config_set_value(uint8_t *data);
void via_config_get_value(uint8_t *data);