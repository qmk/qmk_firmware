/* Copyright 2022~2023 @ lokher (https://www.keychron.com)
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

/******************************************************************************
 *
 *  Filename:      lpm.c
 *
 *  Description:   Contains low power mode implementation
 *
 ******************************************************************************/

#include "quantum.h"
#if defined(PROTOCOL_CHIBIOS)
#    include <usb_main.h>
#endif
#include "debounce.h"
#include "wireless.h"
#include "indicator.h"
#include "lpm.h"
#include "transport.h"
#include "battery.h"
#include "report_buffer.h"
#include "keychron_common.h"

extern matrix_row_t matrix[MATRIX_ROWS];
extern wt_func_t    wireless_transport;

static uint32_t lpm_timer_buffer;
static bool     lpm_time_up = false;
#ifndef OPTICAL_SWITCH
static matrix_row_t empty_matrix[MATRIX_ROWS] = {0};
#endif

pin_t pins_row[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t pins_col[MATRIX_COLS] = MATRIX_COL_PINS;
;

__attribute__((weak)) void select_all_cols(void) {
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        setPinOutput(pins_col[i]);
        writePinLow(pins_col[i]);
    }
}

void lpm_init(void) {
#ifdef USB_POWER_SENSE_PIN
#    if (USB_POWER_CONNECTED_LEVEL == 0)
    setPinInputHigh(USB_POWER_SENSE_PIN);
#    else
    setPinInputLow(USB_POWER_SENSE_PIN);
#    endif
#endif
    lpm_timer_reset();
}

inline void lpm_timer_reset(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = timer_read32();
}

void lpm_timer_stop(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = 0;
}

static inline bool lpm_any_matrix_action(void) {
#ifdef OPTICAL_SWITCH
    bool any_key = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)
        if (matrix_get_row(i) != 0) {
            any_key = true;
        }
    return any_key;
#else
    return memcmp(matrix, empty_matrix, sizeof(empty_matrix));
#endif
}

/* Implement of entering low power mode and wakeup varies per mcu or platform */
__attribute__((weak)) void enter_power_mode(pm_t mode) {}

__attribute__((weak)) bool usb_power_connected(void) {
#ifdef USB_POWER_SENSE_PIN
    return readPin(USB_POWER_SENSE_PIN) == USB_POWER_CONNECTED_LEVEL;
#else
    return true;
#endif
}

__attribute__((weak)) bool lpm_is_kb_idle(void) {
    return true;
}

__attribute__((weak)) bool lpm_set(pm_t mode) {
    return false;
}

bool pre_enter_low_power_mode(pm_t mode) {
#if defined(KEEP_USB_CONNECTION_IN_WIRELESS_MODE)
    /* Don't enter low power mode if attached to the host */
    if (mode > PM_SLEEP && usb_power_connected()) return false;
#endif

    if (!lpm_set(mode)) return false;

#if defined(KEEP_USB_CONNECTION_IN_WIRELESS_MODE)
    /* Usb unit is actived and running, stop and disconnect first */
    usbStop(&USBD1);
    usbDisconnectBus(&USBD1);

    /* Isolate USB to save power.*/
    // PWR->CR2 &= ~PWR_CR2_USV; /*PWR_CR2_USV is available on STM32L4x2xx and STM32L4x3xx devices only. */
#endif

    palEnableLineEvent(LKBT51_INT_INPUT_PIN, PAL_EVENT_MODE_FALLING_EDGE);
#ifdef USB_POWER_SENSE_PIN
    palEnableLineEvent(USB_POWER_SENSE_PIN, PAL_EVENT_MODE_BOTH_EDGES);
#endif
#ifdef P2P4_MODE_SELECT_PIN
    palEnableLineEvent(P2P4_MODE_SELECT_PIN, PAL_EVENT_MODE_BOTH_EDGES);
#endif
#ifdef BT_MODE_SELECT_PIN
    palEnableLineEvent(BT_MODE_SELECT_PIN, PAL_EVENT_MODE_BOTH_EDGES);
#endif

#ifdef OPTICAL_SWITCH

    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (pins_row[x] != NO_PIN) {
            writePinLow(pins_row[x]);
        }
    }

    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (pins_col[x] != NO_PIN) {
            setPinInputLow(pins_col[x]);
        }
    }
#else

    /* Enable key matrix wake up */
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (pins_row[x] != NO_PIN) {
            palEnableLineEvent(pins_row[x], PAL_EVENT_MODE_BOTH_EDGES);
        }
    }
#endif
    select_all_cols();

#if (HAL_USE_SPI == TRUE)
    palSetLineMode(SPI_SCK_PIN, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(SPI_MISO_PIN, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(SPI_MOSI_PIN, PAL_MODE_INPUT_PULLDOWN);
#endif
    palSetLineMode(A12, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(A11, PAL_MODE_INPUT_PULLDOWN);

#if defined(DIP_SWITCH_PINS)
#    define NUMBER_OF_DIP_SWITCHES (sizeof(dip_switch_pad) / sizeof(pin_t))
    static pin_t dip_switch_pad[] = DIP_SWITCH_PINS;

    for (uint8_t i = 0; i < NUMBER_OF_DIP_SWITCHES; i++) {
        setPinInputLow(dip_switch_pad[i]);
    }
#endif
    battery_stop();

    return true;
}

static inline void lpm_wakeup(void) {
    palSetLineMode(A11, PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING | PAL_MODE_ALTERNATE(10U));
    palSetLineMode(A12, PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING | PAL_MODE_ALTERNATE(10U));

#if (HAL_USE_SPI == TRUE)
    palSetLineMode(SPI_SCK_PIN, PAL_MODE_ALTERNATE(5));
    palSetLineMode(SPI_MISO_PIN, PAL_MODE_ALTERNATE(5));
    palSetLineMode(SPI_MOSI_PIN, PAL_MODE_ALTERNATE(5));
#endif

    halInit();

#ifdef ENCODER_ENABLE
    encoder_cb_init();
#endif

    if (wireless_transport.init) wireless_transport.init(true);
    battery_init();

    /* Disable all wake up pins */
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (pins_row[x] != NO_PIN) {
            palDisableLineEvent(pins_row[x]);
        }
    }

    palDisableLineEvent(LKBT51_INT_INPUT_PIN);
#ifdef P2P4_MODE_SELECT_PIN
    palDisableLineEvent(P2P4_MODE_SELECT_PIN);
#endif
#ifdef BT_MODE_SELECT_PIN
    palDisableLineEvent(BT_MODE_SELECT_PIN);
#endif
#ifdef USB_POWER_SENSE_PIN
    palDisableLineEvent(USB_POWER_SENSE_PIN);

#    if defined(KEEP_USB_CONNECTION_IN_WIRELESS_MODE)
    if (usb_power_connected()) {
        usb_event_queue_init();
        init_usb_driver(&USB_DRIVER);
    }
#    endif

#endif

#if defined(DIP_SWITCH_PINS)
    dip_switch_init();
    dip_switch_read(true);
#endif

    /* Call debounce_free() to avoiding memory leak of debounce_counters as debounce_init()
    invoked in matrix_init() alloc new memory to debounce_counters */
    debounce_free();
    matrix_init();
}

void lpm_task(void) {
    if (!lpm_time_up && sync_timer_elapsed32(lpm_timer_buffer) > RUN_MODE_PROCESS_TIME) {
        lpm_time_up      = true;
        lpm_timer_buffer = 0;
    }

    if (usb_power_connected() && USBD1.state == USB_STOP) {
        usb_event_queue_init();
        init_usb_driver(&USB_DRIVER);
    }

    if ((get_transport() == TRANSPORT_BLUETOOTH || get_transport() == TRANSPORT_P2P4) && lpm_time_up && !indicator_is_running() && lpm_is_kb_idle()) {
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
        if (
#    ifdef LED_MATRIX_ENABLE
            !led_matrix_is_enabled() ||
            (led_matrix_is_enabled() && led_matrix_is_driver_shutdown())
#    endif
#    ifdef RGB_MATRIX_ENABLE
                !rgb_matrix_is_enabled() ||
            (rgb_matrix_is_enabled() && rgb_matrix_is_driver_shutdown())
#    endif
        )
#endif
        {
            if (!lpm_any_matrix_action()) {
                if (pre_enter_low_power_mode(LOW_POWER_MODE)) {
                    enter_power_mode(LOW_POWER_MODE);

                    lpm_wakeup();
                    lpm_timer_reset();
                    report_buffer_init();
                    lpm_set(PM_RUN);
                }
            }
        }
    }
}
