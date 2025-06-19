#include QMK_KEYBOARD_H
#include "config.h"
#include "ws2812.h"
#include "bhq_common.h"
#include "wireless.h"
#include "transport.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_5x4(
        MO(1), KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7, KC_P8, KC_P9, KC_PPLS,
        KC_P4, KC_P5, KC_P6,
        KC_P1, KC_P2, KC_P3,
        KC_P0, KC_PDOT, KC_PENT
    ),
    [1] = LAYOUT_5x4(
        KC_TRNS, RM_TOGG, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        USB_TOG, BLE_TOG, RF_TOG,
        BL_SW_0, BL_SW_1, BL_SW_2,
        BLE_OFF, BLE_RESET, QK_BOOT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RM_TOGG:
            if (record->event.pressed) {
                gpio_toggle_pin(RGB_POWER_ENABLED_PIN);
                rgb_matrix_toggle();
            }
            return false;
    }
    return process_record_bhq(keycode, record);
}

void keyboard_post_init_user(void) {
    gpio_set_pin_output(RGB_POWER_ENABLED_PIN);
    gpio_write_pin_high(RGB_POWER_ENABLED_PIN);
}

// 低功耗外围设备电源控制
void lpm_device_power_open(void) {
    gpio_set_pin_output(RGB_POWER_ENABLED_PIN);
    gpio_write_pin_high(RGB_POWER_ENABLED_PIN);
}

// 关闭外围设备电源
void lpm_device_power_close(void) {
    gpio_set_pin_output(RGB_POWER_ENABLED_PIN);
    gpio_write_pin_low(RGB_POWER_ENABLED_PIN);
    gpio_set_pin_output(WS2812_DI_PIN);
    gpio_write_pin_low(WS2812_DI_PIN);
}

// 将未使用的引脚设置为输入模拟
// PS：在6095中，如果不加以下代码休眠时是102ua。如果加了就是30ua~32ua浮动
void lpm_set_unused_pins_to_input_analog(void) {
    // 禁用调试功能以降低功耗
    DBGMCU->CR &= ~DBGMCU_CR_DBG_SLEEP;   // 禁用在Sleep模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STOP;    // 禁用在Stop模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STANDBY; // 禁用在Standby模式下的调试

    palSetLineMode(A0, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A1, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A2, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A3, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A4, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A5, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A6, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A7, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A8, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A9, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A10, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A11, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A13, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A14, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A15, PAL_MODE_INPUT_ANALOG);

    palSetLineMode(B0, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B1, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B2, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B3, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B4, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B5, PAL_MODE_INPUT_ANALOG);
    // palSetLineMode(B6, PAL_MODE_INPUT_ANALOG);
    // palSetLineMode(B7, PAL_MODE_INPUT_ANALOG);
    // palSetLineMode(B8, PAL_MODE_INPUT_ANALOG);
    // palSetLineMode(B9, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B10, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B11, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B13, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B14, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B15, PAL_MODE_INPUT_ANALOG);
}

__attribute__((weak)) bool via_command_kb(uint8_t *data, uint8_t length) {
    return via_command_bhq(data, length);
}