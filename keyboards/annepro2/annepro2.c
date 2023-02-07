/* Copyright 2021 OpenAnnePro community
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

#include "hal.h"
#include "annepro2.h"
#include "annepro2_ble.h"
#include "spi_master.h"
#include "ap2_led.h"
#include "protocol.h"

#define RAM_MAGIC_LOCATION 0x20001ffc
#define IAP_MAGIC_VALUE 0x0000fab2

static const SerialConfig led_uart_init_config = {
    .speed = 115200,
};

#ifndef LED_UART_BAUD_RATE
#    define LED_UART_BAUD_RATE 115200
#endif  // LED_UART_BAUD_RATE

static const SerialConfig led_uart_runtine_config = {
    .speed = LED_UART_BAUD_RATE,
};

static const SerialConfig ble_uart_config = {
    .speed = 115200,
};

static uint8_t led_mcu_wakeup[11] = {0x7b, 0x10, 0x43, 0x10, 0x03, 0x00, 0x00, 0x7d, 0x02, 0x01, 0x02};

ble_capslock_t ble_capslock = {._dummy = {0}, .caps_lock = false};

#ifdef RGB_MATRIX_ENABLE
static uint8_t led_enabled = 1;
#endif

void bootloader_jump(void) {
    // Send msg to shine to boot into IAP
    ap2_set_IAP();

    // wait for shine to boot into IAP
    wait_ms(15);

    // Load ble into IAP
    annepro2_ble_bootload();
    wait_ms(15);

    // Magic key to set keyboard to IAP
    // It’s from reversing original boot loader
    // If value is that it stays in boot loader aka IAP
    *((uint32_t *)RAM_MAGIC_LOCATION) = IAP_MAGIC_VALUE;

    // Load the main MCU into IAP
    __disable_irq();
    NVIC_SystemReset();
}

void keyboard_pre_init_kb(void) {
    // Start LED UART
    sdStart(&SD0, &led_uart_init_config);
    /* Let the LED chip settle a bit before switching the mode.
     * That helped at least one person. */
    wait_ms(15);
    sdWrite(&SD0, led_mcu_wakeup, sizeof(led_mcu_wakeup));

    // wait to receive response from wakeup
    wait_ms(15);

    proto_init(&proto, led_command_callback);

    // loop to clear out receive buffer from shine wakeup
    while (!sdGetWouldBlock(&SD0)) sdGet(&SD0);

    sdStart(&SD0, &led_uart_runtine_config);
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // Start BLE UART
    sdStart(&SD1, &ble_uart_config);
    annepro2_ble_startup();

    // Give the send uart thread some time to
    // send out the queue before we read back
    wait_ms(100);

    // loop to clear out receive buffer from ble wakeup
    while (!sdGetWouldBlock(&SD1)) sdGet(&SD1);

    ap2_led_get_status();

    #ifdef RGB_MATRIX_ENABLE
    ap2_led_enable();
    ap2_led_set_manual_control(1);
    #endif

    keyboard_post_init_user();
}

void matrix_scan_kb() {
    // if there's stuff on the ble serial buffer
    // read it into the capslock struct
    while (!sdGetWouldBlock(&SD1)) {
        sdReadTimeout(&SD1, (uint8_t *)&ble_capslock, sizeof(ble_capslock_t), 10);
    }

    /* While there's data from LED keyboard sent - read it. */
    while (!sdGetWouldBlock(&SD0)) {
        uint8_t byte = sdGet(&SD0);
        proto_consume(&proto, byte);
    }


    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (ap2_led_status.matrix_enabled && ap2_led_status.is_reactive) {
            ap2_led_forward_keypress(record->event.key.row, record->event.key.col);
        }

        const ap2_led_t blue = {
            .p.blue  = 0xff,
            .p.red   = 0x00,
            .p.green = 0x00,
            .p.alpha = 0xff,
        };

        switch (keycode) {
            case KC_AP2_BT1:
                annepro2_ble_broadcast(0);
                /* FIXME: This hardcodes col/row position */
                ap2_led_blink(record->event.key.row, record->event.key.col, blue, 8, 50);
                return false;

            case KC_AP2_BT2:
                annepro2_ble_broadcast(1);
                ap2_led_blink(record->event.key.row, record->event.key.col, blue, 8, 50);
                return false;

            case KC_AP2_BT3:
                annepro2_ble_broadcast(2);
                ap2_led_blink(record->event.key.row, record->event.key.col, blue, 8, 50);
                return false;

            case KC_AP2_BT4:
                annepro2_ble_broadcast(3);
                ap2_led_blink(record->event.key.row, record->event.key.col, blue, 8, 50);
                return false;

            case KC_AP2_USB:
                annepro2_ble_disconnect();
                return false;

            case KC_AP2_BT_UNPAIR:
                annepro2_ble_unpair();
                return false;

            case KC_AP_LED_OFF:
                ap2_led_disable();
                break;

            case KC_AP_LED_ON:
                if (ap2_led_status.matrix_enabled) {
                    ap2_led_next_profile();
                } else {
                    ap2_led_enable();
                }
                ap2_led_reset_foreground_color();
                break;

            case KC_AP_LED_TOG:
                if (ap2_led_status.matrix_enabled) {
                    ap2_led_disable();
                } else {
                    ap2_led_enable();
                    ap2_led_reset_foreground_color();
                }
                break;

            case KC_AP_LED_NEXT_PROFILE:
                ap2_led_next_profile();
                ap2_led_reset_foreground_color();
                break;

            case KC_AP_LED_PREV_PROFILE:
                ap2_led_prev_profile();
                ap2_led_reset_foreground_color();
                break;

            case KC_AP_LED_NEXT_INTENSITY:
                ap2_led_next_intensity();
                ap2_led_reset_foreground_color();
                return false;

            case KC_AP_LED_SPEED:
                ap2_led_next_animation_speed();
                ap2_led_reset_foreground_color();
                return false;
            #ifdef RGB_MATRIX_ENABLE
            case RGB_TOG:
                if(rgb_matrix_is_enabled()) ap2_led_disable();
                else ap2_led_enable();
                return true;

            case KC_AP_RGB_VAI:
                if (record->event.pressed) {
                    if (get_mods() & MOD_MASK_SHIFT) {
                        rgb_matrix_increase_hue();
                        return false;
                    } else if (get_mods() & MOD_MASK_CTRL) {
                        rgb_matrix_decrease_hue();
                        return false;
                    } else {
                        rgb_matrix_increase_val();
                    }
                }
                return true;

            case KC_AP_RGB_VAD:
                if (record->event.pressed) {
                    if (get_mods() & MOD_MASK_SHIFT) {
                        rgb_matrix_increase_sat();
                        return false;
                    } else if (get_mods() & MOD_MASK_CTRL) {
                        rgb_matrix_decrease_sat();
                        return false;
                    } else {
                        rgb_matrix_decrease_val();
                    }
                }
                return true;

            case KC_AP_RGB_TOG:
                if (record->event.pressed) {
                    if (get_mods() & MOD_MASK_SHIFT) {
                        rgb_matrix_increase_speed();
                        return false;
                    } else if (get_mods() & MOD_MASK_CTRL) {
                        rgb_matrix_decrease_speed();
                        return false;
                    } else {
                        if (led_enabled) {
                            ap2_led_disable();
                            rgb_matrix_disable();
                            led_enabled = 0;
                        } else {
                            ap2_led_enable();
                            rgb_matrix_enable();
                            led_enabled = 1;
                        }
                        return true;
                    }
                }
                return true;

            case KC_AP_RGB_MOD:
                if (record->event.pressed) {
                    if (get_mods() & MOD_MASK_CTRL) {
                        rgb_matrix_step_reverse();
                        return false;
                    } else {
                        rgb_matrix_step();
                    }
                }
                return true;
            #endif

            default:
                break;
        }
    }
    return process_record_user(keycode, record);
}
