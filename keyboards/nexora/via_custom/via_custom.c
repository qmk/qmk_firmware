#include "via_custom.h"
#include "via.h"
#include "print.h"
#include "eeprom.h"

// 处理VIA设置值的命令
void via_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    uprintf("VIA Set Value: id=%d, data=%d\n", *value_id, value_data[0]);

    switch (*value_id) {
        case id_bool_keyboard: {
            if (value_data[0] == 0) {
                // 这里可以添加你想要的功能
                wait_ms(20);
                reset_keyboard();
            }
            break;
        }
        case id_reset_keyboard: {
            if (value_data[0] == 0) {
                clear_keyboard();
#ifdef NO_RESET
                eeconfig_init();
#else
                eeconfig_disable();
                soft_reset_keyboard();
#endif
            }
            break;
        }
        default: {
            uprintf("Unhandled value ID: %d\\n", *value_id);
            break;
        }
    }
}

// 处理VIA获取值的命令
void via_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);

    uprintf("VIA Get Value: id=%d\n", *value_id);

    switch (*value_id) {
        case id_reset_keyboard: {
            // 返回当前状态
            value_data[0] = 0;
            break;
        }
        default: {
            uprintf("Unhandled value ID: %d\n", *value_id);
            break;
        }
    }
}

// 处理VIA自定义命令
#ifdef VIA_CUSTOM_CONTROL_ENABLE
void via_custom_value_command_user(uint8_t *data, uint8_t length) {
#else 
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
#endif
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    // 打印详细的调试信息
    uprintf("VIA Command Details:\n");
    uprintf("  Command ID: %d (0x%02X)\n", *command_id, *command_id);
    uprintf("  Channel ID: %d (0x%02X)\n", *channel_id, *channel_id);
    uprintf("  Value ID: %d (0x%02X)\n", value_id_and_data[0], value_id_and_data[0]);
    uprintf("  Value Data: %d (0x%02X)\n", value_id_and_data[1], value_id_and_data[1]);

    // 检查通道ID
    if (*channel_id != 0) {  // 使用0作为通道ID，与VIA配置匹配
        uprintf("Unhandled channel ID: %d\n", *channel_id);
        *command_id = id_unhandled;
        return;
    }

    // 处理命令
    switch (*command_id) {
        case id_custom_set_value: {
            uprintf("Processing SET_VALUE command\n");
            via_config_set_value(value_id_and_data);
            *command_id = id_custom_set_value;  // 返回成功状态
            break;
        }
        case id_custom_get_value: {
            uprintf("Processing GET_VALUE command\n");
            via_config_get_value(value_id_and_data);
            *command_id = id_custom_get_value;  // 返回成功状态
            break;
        }
        case id_custom_save: {
            uprintf("Processing SAVE command\n");
            *command_id = id_custom_save;  // 返回成功状态
            break;
        }
        default: {
            uprintf("Unhandled command ID: %d\n", *command_id);
            *command_id = id_unhandled;
            break;
        }
    }
} 