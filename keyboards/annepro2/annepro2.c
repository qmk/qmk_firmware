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

static const SerialConfig ledUartInitConfig = {
    .speed = 115200,
};

#ifndef LED_UART_BAUD_RATE
#    define LED_UART_BAUD_RATE 115200
#endif  // LED_UART_BAUD_RATE

static const SerialConfig ledUartRuntimeConfig = {
    .speed = LED_UART_BAUD_RATE,
};

static const SerialConfig bleUartConfig = {
    .speed = 115200,
};

static uint8_t ledMcuWakeup[11] = {0x7b, 0x10, 0x43, 0x10, 0x03, 0x00, 0x00, 0x7d, 0x02, 0x01, 0x02};

ble_capslock_t BLECapsLock = {._dummy = {0}, .caps_lock = false};

void bootloader_jump(void) {
    // Send msg to shine to boot into IAP
    annepro2SetIAP();

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
    sdStart(&SD0, &ledUartInitConfig);
    /* Let the LED chip settle a bit before switching the mode.
     * That helped at least one person. */
    wait_ms(15);
    sdWrite(&SD0, ledMcuWakeup, sizeof(ledMcuWakeup));

    // wait to receive response from wakeup
    wait_ms(15);

    protoInit(&proto, ledCommandCallback);

    // loop to clear out receive buffer from shine wakeup
    while (!sdGetWouldBlock(&SD0)) sdGet(&SD0);

    sdStart(&SD0, &ledUartRuntimeConfig);
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // Start BLE UART
    sdStart(&SD1, &bleUartConfig);
    annepro2_ble_startup();

    // Give the send uart thread some time to
    // send out the queue before we read back
    wait_ms(100);

    // loop to clear out receive buffer from ble wakeup
    while (!sdGetWouldBlock(&SD1)) sdGet(&SD1);

    annepro2LedGetStatus();

    keyboard_post_init_user();
}

void matrix_scan_kb() {
    // if there's stuff on the ble serial buffer
    // read it into the capslock struct
    while (!sdGetWouldBlock(&SD1)) {
        sdReadTimeout(&SD1, (uint8_t *)&BLECapsLock, sizeof(ble_capslock_t), 10);
    }

    /* While there's data from LED keyboard sent - read it. */
    while (!sdGetWouldBlock(&SD0)) {
        uint8_t byte = sdGet(&SD0);
        protoConsume(&proto, byte);
    }

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (annepro2LedStatus.matrixEnabled && annepro2LedStatus.isReactive) {
            annepro2LedForwardKeypress(record->event.key.row, record->event.key.col);
        }

        const annepro2Led_t blue = {
            .p.blue  = 0xff,
            .p.red   = 0x00,
            .p.green = 0x00,
            .p.alpha = 0xff,
        };

        switch (keycode) {
            case KC_AP2_BT1:
                annepro2_ble_broadcast(0);
                /* FIXME: This hardcodes col/row position */
                annepro2LedBlink(0, 1, blue, 8, 50);
                return false;

            case KC_AP2_BT2:
                annepro2_ble_broadcast(1);
                annepro2LedBlink(0, 2, blue, 8, 50);
                return false;

            case KC_AP2_BT3:
                annepro2_ble_broadcast(2);
                annepro2LedBlink(0, 3, blue, 8, 50);
                return false;

            case KC_AP2_BT4:
                annepro2_ble_broadcast(3);
                annepro2LedBlink(0, 4, blue, 8, 50);
                return false;

            case KC_AP2_USB:
                annepro2_ble_disconnect();
                return false;

            case KC_AP2_BT_UNPAIR:
                annepro2_ble_unpair();
                return false;

            case KC_AP_LED_OFF:
                annepro2LedDisable();
                break;

            case KC_AP_LED_ON:
                if (annepro2LedStatus.matrixEnabled) {
                    annepro2LedNextProfile();
                } else {
                    annepro2LedEnable();
                }
                annepro2LedResetForegroundColor();
                break;

            case KC_AP_LED_NEXT_PROFILE:
                annepro2LedNextProfile();
                annepro2LedResetForegroundColor();
                break;

            case KC_AP_LED_PREV_PROFILE:
                annepro2LedPrevProfile();
                annepro2LedResetForegroundColor();
                break;

            case KC_AP_LED_NEXT_INTENSITY:
                annepro2LedNextIntensity();
                annepro2LedResetForegroundColor();
                return false;

            case KC_AP_LED_SPEED:
                annepro2LedNextAnimationSpeed();
                annepro2LedResetForegroundColor();
                return false;

            default:
                break;
        }
    }
    return process_record_user(keycode, record);
}
