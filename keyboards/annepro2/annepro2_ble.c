/*
    Copyright (C) 2020 Yaotian Feng, Codetector<codetector@codetector.cn>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "annepro2_ble.h"
#include "ch.h"
#include "hal.h"
#include "host.h"
#include "host_driver.h"
#include "report.h"
#include "timer.h"

/* -------------------- Static Function Prototypes -------------------------- */
static uint8_t ap2_ble_leds(void);
static void    ap2_ble_mouse(report_mouse_t *report);
static void    ap2_ble_extra(report_extra_t *report);
static void    ap2_ble_keyboard(report_keyboard_t *report);

static void ap2_ble_swtich_ble_driver(void);

#ifndef ANNEPRO2_BLE_CONNECT_GUARD_MS
#    define ANNEPRO2_BLE_CONNECT_GUARD_MS 200
#endif

/* -------------------- Static Local Variables ------------------------------ */
static host_driver_t ap2_ble_driver = {
    ap2_ble_leds, ap2_ble_keyboard, NULL, ap2_ble_mouse, ap2_ble_extra
};

static const uint8_t ble_mcu_wakeup[11] = {0x7b, 0x12, 0x53, 0x00, 0x03, 0x00, 0x01, 0x7d, 0x02, 0x01, 0x02};

static const uint8_t ble_mcu_start_broadcast[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x03, 0x00, 0x00, 0x7d, 0x40, 0x01,  // Broadcast ID[0-3]
};

static const uint8_t ble_mcu_connect[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x03, 0x00, 0x00, 0x7d, 0x40, 0x04,  // Connect ID [0-3]
};

static const uint8_t ble_mcu_send_report[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x0A, 0x00, 0x00, 0x7d, 0x10, 0x04,
};

static const uint8_t ble_mcu_send_consumer_report[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x06, 0x00, 0x00, 0x7d, 0x10, 0x08,
};

static const uint8_t ble_mcu_unpair[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x02, 0x00, 0x00, 0x7d, 0x40, 0x05,
};

static const uint8_t ble_mcu_bootload[11] = {0x7b, 0x10, 0x51, 0x10, 0x03, 0x00, 0x00, 0x7d, 0x02, 0x01, 0x01};

static host_driver_t *last_host_driver = NULL;
static int8_t         last_broadcast = -1;
static bool           ble_connect_pending;
static uint32_t       ble_connect_started_at;
#ifdef NKRO_ENABLE
static bool lastNkroStatus = false;
#endif  // NKRO_ENABLE

/* -------------------- Public Function Implementation ---------------------- */

void annepro2_ble_bootload(void) { sdWrite(&SD1, ble_mcu_bootload, sizeof(ble_mcu_bootload)); }

void annepro2_ble_startup(void) { sdWrite(&SD1, ble_mcu_wakeup, sizeof(ble_mcu_wakeup)); }

void annepro2_ble_broadcast(uint8_t port) {
    if (port > 3) {
        port = 3;
    }
    const bool reconnect = last_broadcast == (int8_t)port;
    uint8_t    frame[sizeof(ble_mcu_start_broadcast) + 2];

    if (!reconnect) {
        /* Do not keep sending HID reports to a previously selected slot. */
        annepro2_ble_disconnect();
    }

    for (uint8_t i = 0; i < sizeof(ble_mcu_start_broadcast); i++) {
        frame[i] = ble_mcu_start_broadcast[i];
    }
    frame[sizeof(ble_mcu_start_broadcast)]     = port;
    frame[sizeof(ble_mcu_start_broadcast) + 1] = 0x00;
    sdWrite(&SD1, frame, sizeof(frame));

    if (reconnect) {
        annepro2_ble_connect(port);
    }
    last_broadcast = port;
}

void annepro2_ble_connect(uint8_t port) {
    if (port > 3) {
        port = 3;
    }
    uint8_t frame[sizeof(ble_mcu_connect) + 2];

    /* A reconnect must not let stale reports enter the newly selected slot. */
    annepro2_ble_disconnect();

    for (uint8_t i = 0; i < sizeof(ble_mcu_connect); i++) {
        frame[i] = ble_mcu_connect[i];
    }
    frame[sizeof(ble_mcu_connect)]     = port;
    frame[sizeof(ble_mcu_connect) + 1] = 0x00;
    sdWrite(&SD1, frame, sizeof(frame));

    /*
     * The BLE firmware's connect-complete indication is not decoded yet.
     * Keep QMK on its previous host driver briefly so the command reaches the
     * module before it can receive HID reports; this is not a link-state ACK.
     */
    ble_connect_started_at = timer_read32();
    ble_connect_pending    = true;
}

void annepro2_ble_disconnect(void) {
    ble_connect_pending = false;
    last_broadcast      = -1;

    /* Skip if the driver is already enabled */
    if (host_get_driver() != &ap2_ble_driver) {
        return;
    }

    clear_keyboard();
#ifdef NKRO_ENABLE
    keymap_config.nkro = lastNkroStatus;
#endif
    host_set_driver(last_host_driver);
}

void annepro2_ble_unpair(void) {
    sdWrite(&SD1, ble_mcu_unpair, sizeof(ble_mcu_unpair));
    annepro2_ble_disconnect();
}

void annepro2_ble_task(void) {
    if (!ble_connect_pending || timer_elapsed32(ble_connect_started_at) < ANNEPRO2_BLE_CONNECT_GUARD_MS) {
        return;
    }

    ble_connect_pending = false;
    ap2_ble_swtich_ble_driver();
}

/* ------------------- Static Function Implementation ----------------------- */
static void ap2_ble_swtich_ble_driver(void) {
    if (host_get_driver() == &ap2_ble_driver) {
        return;
    }
    clear_keyboard();
    last_host_driver = host_get_driver();
#ifdef NKRO_ENABLE
    lastNkroStatus = keymap_config.nkro;
#endif
    keymap_config.nkro = false;
    host_set_driver(&ap2_ble_driver);
}

static uint8_t ap2_ble_leds(void) {
    return 0;  // TODO: Figure out how to obtain LED status
}

static void ap2_ble_mouse(report_mouse_t *report) {}

static inline uint16_t CONSUMER2AP2(uint16_t usage) {
    switch (usage) {
        case AUDIO_VOL_DOWN:
            return 0x04;
        case AUDIO_VOL_UP:
            return 0x02;
        case AUDIO_MUTE:
            return 0x01;
        case TRANSPORT_PLAY_PAUSE:
            return 0x08;
        case TRANSPORT_NEXT_TRACK:
            return 0x10;
        case TRANSPORT_PREV_TRACK:
            return 0x20;
        default:
            return 0x00;
    }
}

static void ap2_ble_extra(report_extra_t *report) {
    if (report->report_id == REPORT_ID_CONSUMER) {
        uint8_t frame[1 + sizeof(ble_mcu_send_consumer_report) + 4] = {0};

        frame[0] = 0x00;
        for (uint8_t i = 0; i < sizeof(ble_mcu_send_consumer_report); i++) {
            frame[i + 1] = ble_mcu_send_consumer_report[i];
        }
        frame[sizeof(ble_mcu_send_consumer_report) + 1] = CONSUMER2AP2(report->usage);
        sdWrite(&SD1, frame, sizeof(frame));
    }
}

/*!
 * @brief  Send keyboard HID report for Bluetooth driver
 */
static void ap2_ble_keyboard(report_keyboard_t *report) {
    uint8_t frame[1 + sizeof(ble_mcu_send_report) + KEYBOARD_REPORT_SIZE];

    frame[0] = 0x00;
    for (uint8_t i = 0; i < sizeof(ble_mcu_send_report); i++) {
        frame[i + 1] = ble_mcu_send_report[i];
    }
    for (uint8_t i = 0; i < KEYBOARD_REPORT_SIZE; i++) {
        frame[sizeof(ble_mcu_send_report) + 1 + i] = ((const uint8_t *)report)[i];
    }
    sdWrite(&SD1, frame, sizeof(frame));
}
