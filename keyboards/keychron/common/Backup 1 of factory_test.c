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
#include "raw_hid.h"
#include "via.h"

#include "keychron_task.h"
#ifdef LK_WIRELESS_ENABLE
#    include "transport.h"
#    include "battery.h"
#    include "lpm.h"
#    include "lkbt51.h"
#    include "indicator.h"
#endif
#include "config.h"
#include "version.h"

#ifndef RAW_EPSIZE
#    define RAW_EPSIZE 32
#endif

#ifndef BL_CYCLE_KEY
#    define BL_CYCLE_KEY KC_RIGHT
#endif

#ifndef BL_TRIG_KEY
#    define BL_TRIG_KEY KC_HOME
#endif

#ifndef P2P4G_CELAR_MASK
#    define P2P4G_CELAR_MASK P2P4G_CLEAR_PAIRING_TYPE_C
#endif

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
    KEY_PRESS_BL_KEY1        = 0x01 << 3,
    KEY_PRESS_BL_KEY2        = 0x01 << 4,
    KEY_PRESS_FACTORY_RESET  = KEY_PRESS_FN | KEY_PRESS_J | KEY_PRESS_Z,
    KEY_PRESS_BACKLIGTH_TEST = KEY_PRESS_FN | KEY_PRESS_BL_KEY1 | KEY_PRESS_BL_KEY2,
};

enum {
    FACTORY_TEST_CMD_BACKLIGHT = 0x01,
    FACTORY_TEST_CMD_OS_SWITCH,
    FACTORY_TEST_CMD_JUMP_TO_BL,
    FACTORY_TEST_CMD_INT_PIN,
    FACTORY_TEST_CMD_GET_TRANSPORT,
    FACTORY_TEST_CMD_CHARGING_ADC,
    FACTORY_TEST_CMD_RADIO_CARRIER,
    FACTORY_TEST_CMD_GET_BUILD_TIME,
};

enum {
    P2P4G_CLEAR_PAIRING_TYPE_A = 0x01 << 0,
    P2P4G_CLEAR_PAIRING_TYPE_C = 0x01 << 1,
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
static bool     keys_released           = true;

void factory_timer_start(void) {
    factory_reset_timer = timer_read32();
}

static inline void factory_timer_check(void) {
    if (timer_elapsed32(factory_reset_timer) > 3000) {
        factory_reset_timer = 0;

        if (factory_reset_state == KEY_PRESS_FACTORY_RESET) {
            factory_reset_ind_timer = timer_read32();
            factory_reset_ind_state++;
            keys_released = false;

            clear_keyboard(); // Avoid key being pressed after NKRO state changed
            layer_state_t default_layer_tmp = default_layer_state;
            eeconfig_init();
            keymap_config.raw = eeconfig_read_keymap();
            default_layer_set(default_layer_tmp);
#ifdef LED_MATRIX_ENABLE
            if (!led_matrix_is_enabled()) led_matrix_enable();
            led_matrix_init();
#endif
#ifdef RGB_MATRIX_ENABLE
            if (!rgb_matrix_is_enabled()) rgb_matrix_enable();
            rgb_matrix_init();
#endif
#ifdef LK_WIRELESS_ENABLE
            lkbt51_factory_reset(P2P4G_CELAR_MASK);
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
    if (factory_reset_ind_timer && timer_elapsed32(factory_reset_ind_timer) > 250) {
        if (factory_reset_ind_state++ > 6) {
            factory_reset_ind_timer = factory_reset_ind_state = 0;
        } else {
            factory_reset_ind_timer = timer_read32();
        }
    }
}

bool process_record_factory_test(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#if defined(FN_KEY_1) || defined(FN_KEY_2)
#    if defined(FN_KEY_1)
        case FN_KEY_1: /* fall through */
#    endif
#    if defined(FN_KEY_2)
        case FN_KEY_2:
#    endif
#    if defined(FN_KEY_3)
        case FN_KEY_3:
#    endif
            if (record->event.pressed) {
                factory_reset_state |= KEY_PRESS_FN;
            } else {
                factory_reset_state &= ~KEY_PRESS_FN;
                factory_reset_timer = 0;
            }
            break;
#endif
        case KC_J:
            if (record->event.pressed) {
                factory_reset_state |= KEY_PRESS_J;
                if (factory_reset_state == 0x07) factory_timer_start();
                if (factory_reset_state & KEY_PRESS_FN) return false;
            } else {
                factory_reset_state &= ~KEY_PRESS_J;
                factory_reset_timer = 0;
            }
            break;
        case KC_Z:
#if defined(FN_Z_KEY)
        case FN_Z_KEY:
#endif
            if (record->event.pressed) {
                factory_reset_state |= KEY_PRESS_Z;
                if (factory_reset_state == 0x07) factory_timer_start();
                if ((factory_reset_state & KEY_PRESS_FN) && keycode == KC_Z) return false;
            } else {
                factory_reset_state &= ~KEY_PRESS_Z;
                factory_reset_timer = 0;
                /* Avoid changing backlight effect on key released if FN_Z_KEY is mode*/

                if (!keys_released && keycode >= QK_BACKLIGHT_ON && keycode <= RGB_MODE_TWINKLE) {
                    keys_released = true;
                    return false;
                }
            }
            break;
#if defined(BL_CYCLE_KEY) || defined(BL_CYCLE_KEY_2)
#    if defined(BL_CYCLE_KEY)
        case BL_CYCLE_KEY:
#    endif
#    if defined(FN_BL_CYCLE_KEY)
        case FN_BL_CYCLE_KEY:
#    endif
            if (record->event.pressed) {
                if (backlight_test_mode) {
                    if (++backlight_test_mode >= BACKLIGHT_TEST_MAX) {
                        backlight_test_mode = BACKLIGHT_TEST_WHITE;
                    }
                } else {
                    factory_reset_state |= KEY_PRESS_BL_KEY1;
                    if (factory_reset_state == 0x19) {
                        factory_timer_start();
                    }
                }
            } else {
                factory_reset_state &= ~KEY_PRESS_BL_KEY1;
                factory_reset_timer = 0;
            }
            break;
#endif
#if defined(BL_TRIG_KEY) || defined(BL_TRIG_KEY_2)
#    if defined(BL_TRIG_KEY)
        case BL_TRIG_KEY:
#    endif
#    if defined(FN_BL_TRIG_KEY)
        case FN_BL_TRIG_KEY:
#    endif
            if (record->event.pressed) {
                if (backlight_test_mode) {
                    backlight_test_mode = BACKLIGHT_TEST_OFF;
                } else {
                    factory_reset_state |= KEY_PRESS_BL_KEY2;
                    if (factory_reset_state == 0x19) {
                        factory_timer_start();
                    }
                }
            } else {
                factory_reset_state &= ~KEY_PRESS_BL_KEY2;
                factory_reset_timer = 0;
            }
            break;
#endif
    }

    return true;
}

#ifdef LED_MATRIX_ENABLE
bool factory_test_indicator(void) {
    if (factory_reset_ind_state) {
        led_matrix_set_value_all(factory_reset_ind_state % 2 ? 0 : 255);
        return false;
    }

    return true;
}
#endif

#ifdef RGB_MATRIX_ENABLE
bool factory_test_indicator(void) {
    if (factory_reset_ind_state) {
        backlight_test_mode = BACKLIGHT_TEST_OFF;
        rgb_matrix_set_color_all(factory_reset_ind_state % 2 ? 0 : 255, 0, 0);
        return false;
    } else if (backlight_test_mode) {
        switch (backlight_test_mode) {
            case BACKLIGHT_TEST_WHITE:
                rgb_matrix_set_color_all(255, 255, 255);
                break;
            case BACKLIGHT_TEST_RED:
                rgb_matrix_set_color_all(255, 0, 0);
                break;
            case BACKLIGHT_TEST_GREEN:
                rgb_matrix_set_color_all(0, 255, 0);
                break;
            case BACKLIGHT_TEST_BLUE:
                rgb_matrix_set_color_all(0, 0, 255);
                break;
        }
        return false;
    }

    return true;
}
#endif

bool factory_reset_indicating(void) {
    return factory_reset_ind_timer;
}

bool factory_test_task(void) {
    if (factory_reset_timer) factory_timer_check();
    if (factory_reset_ind_timer) factory_reset_ind_timer_check();

    return true;
}

#ifdef LEMOKEY_CALLBACK_ENABLE
void factory_test_init(void) {
    register_lemokey_task(factory_test_task, false);
    register_record_process(process_record_factory_test, false);
    register_led_indicator_task(factory_test_indicator, false);
}
#endif

void factory_test_send(uint8_t *payload, uint8_t length) {
#ifdef RAW_ENABLE
    uint16_t checksum         = 0;
    uint8_t  data[RAW_EPSIZE] = {0};

    uint8_t i = 0;
    data[i++] = 0xAB;

    memcpy(&data[i], payload, length);
    i += length;

    for (uint8_t i = 1; i < RAW_EPSIZE - 3; i++)
        checksum += data[i];
    data[RAW_EPSIZE - 2] = checksum & 0xFF;
    data[RAW_EPSIZE - 1] = (checksum >> 8) & 0xFF;

    raw_hid_send(data, RAW_EPSIZE);
#endif
}

void factory_test_rx(uint8_t *data, uint8_t length) {
    if (data[0] == 0xAB) {
        uint16_t checksum = 0;

        for (uint8_t i = 1; i < RAW_EPSIZE - 3; i++) {
            checksum += data[i];
        }
        /* Verify checksum */
        if ((checksum & 0xFF) != data[RAW_EPSIZE - 2] || checksum >> 8 != data[RAW_EPSIZE - 1]) return;

#ifdef LK_WIRELESS_ENABLE
        uint8_t payload[32];
        uint8_t len = 0;
#endif

        switch (data[1]) {
            case FACTORY_TEST_CMD_BACKLIGHT:
                backlight_test_mode = data[2];
                factory_reset_timer = 0;
                break;
            case FACTORY_TEST_CMD_OS_SWITCH:
                report_os_sw_state = data[2];
                if (report_os_sw_state) {
                    // dip_switch_read(true);
                }
                break;
            case FACTORY_TEST_CMD_JUMP_TO_BL:
                // if (memcmp(&data[2], "JumpToBootloader", strlen("JumpToBootloader")) == 0) bootloader_jump();
                break;
#ifdef LK_WIRELESS_ENABLE
            case FACTORY_TEST_CMD_INT_PIN:
                switch (data[2]) {
                    /* Enalbe/disable test */
                    case 0xA1:
                        lkbt51_int_pin_test(data[3]);
                        break;
                    /* Set INT state */
                    case 0xA2:
                        kc_printf("pin %d\n\r", data[3]);
                        writePin(BLUETOOTH_INT_OUTPUT_PIN, data[3]);
                        break;
                        /* Report INT state */
                        //                    case 0xA3:
                        //                        payload[len++] = FACTORY_TEST_CMD_INT_PIN;
                        //                        payload[len++] = 0xA3;
                        //                        payload[len++] = readPin(LKBT51_INT_INPUT_PIN);
                        //                        factory_test_send(payload, len);
                        //                        break;
                }
                break;
            case FACTORY_TEST_CMD_GET_TRANSPORT:
                payload[len++] = FACTORY_TEST_CMD_GET_TRANSPORT;
                payload[len++] = get_transport();
                payload[len++] = readPin(USB_POWER_SENSE_PIN);
                factory_test_send(payload, len);
                break;
#endif
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
#ifdef LK_WIRELESS_ENABLE
            case FACTORY_TEST_CMD_RADIO_CARRIER:
                if (data[2] < 79) lkbt51_radio_test(data[2]);
                break;

#    ifdef WERELESS_PRESSURE_TEST
            case 0x70:
                switch (data[2]) {
                    /* Enalbe/disable test */
                    case 0xB1:
                        SEND_STRING("abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890\n");
                        break;
                    case 0xB2:
                        payload[len++] = 0x70;
                        payload[len++] = 0xB2;
                        payload[len++] = wireless_get_state();
                        factory_test_send(payload, len);
                        break;
                }
                break;
#    endif
#endif
            case FACTORY_TEST_CMD_GET_BUILD_TIME: {
                payload[len++] = FACTORY_TEST_CMD_GET_BUILD_TIME;
                payload[len++] = 'v';
                if ((DEVICE_VER & 0xF000) != 0) itoa((DEVICE_VER >> 12), (char *)&payload[len++], 16);
                itoa((DEVICE_VER >> 8) & 0xF, (char *)&payload[len++], 16);
                payload[len++] = '.';
                itoa((DEVICE_VER >> 4) & 0xF, (char *)&payload[len++], 16);
                payload[len++] = '.';
                itoa((DEVICE_VER >> 4) & 0xF, (char *)&payload[len++], 16);
                payload[len++] = ' ';
                memcpy(&payload[len], QMK_BUILDDATE, sizeof(QMK_BUILDDATE));
                len += sizeof(QMK_BUILDDATE);
                factory_test_send(payload, len);
            } break;
        }
    }
}

bool dip_switch_update_user(uint8_t index, bool active) {
    if (report_os_sw_state) {
#ifdef INVERT_OS_SWITCH_STATE
        active = !active;
#endif
        uint8_t payload[3] = {FACTORY_TEST_CMD_OS_SWITCH, OS_SWITCH, active};
        factory_test_send(payload, 3);
    }

    return true;
}
