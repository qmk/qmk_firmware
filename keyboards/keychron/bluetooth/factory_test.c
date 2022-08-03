/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "ckbt51.h"
#include "raw_hid.h"
#include "transport.h"
#include "battery.h"
#include "via.h"
#include "indicator.h"
#include "lpm.h"

extern bool bt_factory_reset;

enum {
    BACKLIGHT_TEST_OFF = 0,
    BACKLIGHT_TEST_WHITE,
    BACKLIGHT_TEST_RED,
    BACKLIGHT_TEST_GREEN,
    BACKLIGHT_TEST_BLUE,
    BACKLIGHT_TEST_MAX,
};

enum {
    KEY_PRESS_FN             = 0x01 << 0,
    KEY_PRESS_J              = 0x01 << 1,
    KEY_PRESS_Z              = 0x01 << 2,
    KEY_PRESS_RIGHT          = 0x01 << 3,
    KEY_PRESS_HOME           = 0x01 << 4,
    KEY_PRESS_FACTORY_RESET  = KEY_PRESS_FN | KEY_PRESS_J | KEY_PRESS_Z,
    KEY_PRESS_BACKLIGTH_TEST = KEY_PRESS_FN | KEY_PRESS_RIGHT | KEY_PRESS_HOME,
};

enum {
    FACTORY_TEST_CMD_BACKLIGHT = 0x01,
    FACTORY_TEST_CMD_OS_SWITCH,
    FACTORY_TEST_CMD_JUMP_TO_BL,
    FACTORY_TEST_CMD_INT_PIN,
    FACTORY_TEST_CMD_GET_TRANSPORT,
    FACTORY_TEST_CMD_CHARGING_ADC,
};

enum {
    OS_SWITCH = 0x01,
};

static uint32_t factory_reset_timer = 0;
static uint8_t  factory_reset_state = 0;
static uint8_t  backlight_test_mode = BACKLIGHT_TEST_OFF;

static uint32_t factory_reset_ind_timer = 0;
static uint8_t  factory_reset_ind_state = 0;
static bool     report_os_sw_state      = false;

void factory_timer_start(void) {
    factory_reset_timer = sync_timer_read32() | 1;
}

static inline void factory_timer_check(void) {
    if (sync_timer_elapsed32(factory_reset_timer) > 3000) {
        factory_reset_timer = 0;

        if (factory_reset_state == KEY_PRESS_FACTORY_RESET) {
            factory_reset_ind_timer = sync_timer_read32() | 1;
            factory_reset_ind_state++;

            layer_state_t default_layer_tmp = default_layer_state;
            eeconfig_init();
            default_layer_set(default_layer_tmp);
#ifdef LED_MATRIX_ENABLE
            if (!led_matrix_is_enabled()) led_matrix_enable();
            led_matrix_init();
#endif
#ifdef RGB_MATRIX_ENABLE
            if (!rgb_matrix_is_enabled()) rgb_matrix_enable();
            rgb_matrix_init();
#endif
#ifdef BLUETOOTH_ENABLE
            ckbt51_factory_reset();
            bt_factory_reset = true;
#endif
        } else if (factory_reset_state == KEY_PRESS_BACKLIGTH_TEST) {
#ifdef LED_MATRIX_ENABLE
            if (!led_matrix_is_enabled()) led_matrix_enable();
#endif
#ifdef RGB_MATRIX_ENABLE
            if (!rgb_matrix_is_enabled()) rgb_matrix_enable();
#endif
            backlight_test_mode = BACKLIGHT_TEST_WHITE;
        }

        factory_reset_state = 0;
    }
}

static inline void factory_reset_ind_timer_check(void) {
    if (factory_reset_ind_timer && sync_timer_elapsed32(factory_reset_ind_timer) > 250) {
        if (factory_reset_ind_state++ > 6) {
            factory_reset_ind_timer = factory_reset_ind_state = 0;
        } else {
            factory_reset_ind_timer = sync_timer_read32() | 1;
        }
    }
}

void process_record_factory_reset(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(1): /* fall through */
        case MO(2):
        case MO(3):
        case MO(4):
            if (record->event.pressed) {
                factory_reset_state |= KEY_PRESS_FN;
            } else {
                factory_reset_state &= ~KEY_PRESS_FN;
                factory_reset_timer = 0;
            }
            break;
        case KC_J:
            if (record->event.pressed) {
                factory_reset_state |= KEY_PRESS_J;
                if (factory_reset_state == 0x07) factory_timer_start();
            } else {
                factory_reset_state &= ~KEY_PRESS_J;
                factory_reset_timer = 0;
            }
            break;
        case KC_Z:
            if (record->event.pressed) {
                factory_reset_state |= KEY_PRESS_Z;
                if (factory_reset_state == 0x07) factory_timer_start();
            } else {
                factory_reset_state &= ~KEY_PRESS_Z;
                factory_reset_timer = 0;
            }
            break;
        case KC_RIGHT:
            if (record->event.pressed) {
                if (backlight_test_mode) {
                    if (++backlight_test_mode >= BACKLIGHT_TEST_MAX) {
                        backlight_test_mode = BACKLIGHT_TEST_WHITE;
                    }
                } else {
                    factory_reset_state |= KEY_PRESS_RIGHT;
                    if (factory_reset_state == 0x19) factory_timer_start();
                }
            } else {
                factory_reset_state &= ~KEY_PRESS_RIGHT;
                factory_reset_timer = 0;
            }
            break;
        case KC_HOME:
            if (record->event.pressed) {
                if (backlight_test_mode) {
                    backlight_test_mode = BACKLIGHT_TEST_OFF;
                } else {
                    factory_reset_state |= KEY_PRESS_HOME;
                    if (factory_reset_state == 0x19) factory_timer_start();
                }
            } else {
                factory_reset_state &= ~KEY_PRESS_HOME;
                factory_reset_timer = 0;
            }
            break;
    }
}

#ifdef LED_MATRIX_ENABLE
void led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (factory_reset_ind_state) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            led_matrix_set_value(i, factory_reset_ind_state % 2 ? 0 : 255);
        }
    }
}
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (factory_reset_ind_state) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            rgb_matrix_set_color(i, factory_reset_ind_state % 2 ? 0 : 255, 0, 0);
        }
    } else if (backlight_test_mode) {
        switch (backlight_test_mode) {
            case BACKLIGHT_TEST_WHITE:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, 255, 255, 255);
                }
                break;
            case BACKLIGHT_TEST_RED:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, 255, 0, 0);
                }
                break;
            case BACKLIGHT_TEST_GREEN:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, 0, 255, 0);
                }
                break;
            case BACKLIGHT_TEST_BLUE:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, 0, 0, 255);
                }
                break;
        }
    }
}
#endif

void factory_reset_task(void) {
    if (factory_reset_timer) factory_timer_check();
    if (factory_reset_ind_timer) factory_reset_ind_timer_check();
}

void factory_test_send(uint8_t *payload, uint8_t length) {
    uint16_t checksum         = 0;
    uint8_t  data[RAW_EPSIZE] = {0};

    uint8_t i = 0;
    data[i++] = 0xAB;

    memcpy(&data[i], payload, length);
    i += length;

    for (uint8_t i = 1; i < RAW_EPSIZE - 3; i++) checksum += data[i];
    data[RAW_EPSIZE - 2] = checksum & 0xFF;
    data[RAW_EPSIZE - 1] = (checksum >> 8) & 0xFF;

    raw_hid_send(data, RAW_EPSIZE);
}

void factory_test_rx(uint8_t *data, uint8_t length) {
    if (data[0] == 0xAB) {
        uint16_t checksum = 0;

        for (uint8_t i = 1; i < RAW_EPSIZE - 3; i++) {
            checksum += data[i];
        }
        /* Verify checksum */
        if ((checksum & 0xFF) != data[RAW_EPSIZE - 2] || checksum >> 8 != data[RAW_EPSIZE - 1]) return;

        uint8_t payload[32];
        uint8_t len = 0;

        switch (data[1]) {
            case FACTORY_TEST_CMD_BACKLIGHT:
                backlight_test_mode = data[2];
                factory_reset_timer = 0;
                break;
            case FACTORY_TEST_CMD_OS_SWITCH:
                report_os_sw_state = data[2];
                if (report_os_sw_state) {
                    dip_switch_read(true);
                }
                break;
            case FACTORY_TEST_CMD_JUMP_TO_BL:
                // if (memcmp(&data[2], "JumpToBootloader", strlen("JumpToBootloader")) == 0) bootloader_jump();
                break;
            case FACTORY_TEST_CMD_INT_PIN:
                switch (data[2]) {
                    /* Enalbe/disable test */
                    case 0xA1:
                        ckbt51_int_pin_test(data[3]);
                        break;
                    /* Set INT state */
                    case 0xA2:
                        writePin(CKBT51_INT_INPUT_PIN, data[3]);
                        break;
                    /* Report INT state */
                    case 0xA3:
                        payload[len++] = FACTORY_TEST_CMD_INT_PIN;
                        payload[len++] = 0xA3;
                        payload[len++] = readPin(BLUETOOTH_INT_INPUT_PIN);
                        factory_test_send(payload, len);
                        break;
                }
                break;
            case FACTORY_TEST_CMD_GET_TRANSPORT:
                payload[len++] = FACTORY_TEST_CMD_GET_TRANSPORT;
                payload[len++] = get_transport();
                payload[len++] = readPin(USB_POWER_SENSE_PIN);
                factory_test_send(payload, len);
                break;
#ifdef BATTERY_CHARGE_DONE_DETECT_ADC
            case FACTORY_TEST_CMD_CHARGING_ADC:
            case 0xA1:
                battery_charging_monitor(data[3]);
                break;
            case 0xA2:
                payload[len++] = FACTORY_TEST_CMD_CHARGING_ADC;
                payload[len++] = battery_adc_read_charging_pin();
                factory_test_send(payload, len);
                break;
#endif
        }
    }
}

bool dip_switch_update_user(uint8_t index, bool active) {
    if (report_os_sw_state) {
        uint8_t payload[3] = {FACTORY_TEST_CMD_OS_SWITCH, OS_SWITCH, active};
        factory_test_send(payload, 3);
    }

    return true;
}
