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

/* Compile-time selected Anne Pro 2 C18/AP2D BLE transport. */
#include "annepro2_ble.h"
#include "annepro2_ble_213_slot.h"
#include "annepro2_ble_parser.h"
#include "annepro2_ble_profile.h"
#include "annepro2_ble_state.h"
#include "ch.h"
#include "eeconfig.h"
#include "hal.h"
#include "host.h"
#include "host_driver.h"
#include "led.h"
#include "print.h"
#include "report.h"
#include "timer.h"
#ifdef ANNEPRO2_LED_MCU_ENABLE
#    include "ap2_led.h"
#endif
#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
#    include "version.h"
#endif

#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
#    define AP2_BLE_LOG(fmt, ...) uprintf("AP2 BLE %08lX " fmt "\n", (unsigned long)timer_read32(), ##__VA_ARGS__)
#    define AP2_BLE_BUILD_LOG_DELAY 2000
#else
#    define AP2_BLE_LOG(fmt, ...)
#endif

/* -------------------- Static Function Prototypes -------------------------- */
static uint8_t ap2_ble_leds(void);
static void    ap2_ble_mouse(report_mouse_t *report);
static void    ap2_ble_extra(report_extra_t *report);
static void    ap2_ble_keyboard(report_keyboard_t *report);

static void   ap2_ble_switch_ble_driver(void);
static void   ap2_ble_execute_actions(ap2_ble_actions_t actions);
static void   ap2_ble_execute_actions_now(ap2_ble_actions_t actions);
#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
static void   ap2_ble_execute_213_slot_actions(ap2_ble_213_slot_actions_t actions);
#endif
static void   ap2_ble_handle_rx_frame(const uint8_t *frame, uint8_t size);
static void   ap2_ble_handle_command_ack(uint8_t command, uint8_t value);
static void   ap2_ble_notify_status(annepro2_ble_status_t status);
static void   ap2_ble_reset_rx_parser(void);
static void   ap2_ble_send_broadcast(void);
static void   ap2_ble_send_connect(void);
static void   ap2_ble_send_slot_state(void);
static int8_t ap2_ble_read_saved_slot(void);
static void   ap2_ble_save_slot(int8_t slot);
static void   ap2_ble_drain_rx(void);
#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
static void ap2_ble_log_build(void);
static void ap2_ble_log_rx_frame(const uint8_t *frame, uint8_t size);
#endif

/* -------------------- Static Local Variables ------------------------------ */
static host_driver_t ap2_ble_driver = {ap2_ble_leds, ap2_ble_keyboard, NULL, ap2_ble_mouse, ap2_ble_extra};

static const SerialConfig ble_uart_config = {
    .speed = 115200,
};

static uint8_t ble_mcu_wakeup[11] = {0x7b, 0x12, 0x53, 0x00, 0x03, 0x00, 0x01, 0x7d, 0x02, 0x01, 0x02};

static uint8_t ble_mcu_start_broadcast[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x03, 0x00, 0x00, 0x7d, 0x40, 0x01, // Broadcast ID[0-3]
};

static uint8_t ble_mcu_connect[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x03, 0x00, 0x00, 0x7d, 0x40, 0x04, // Connect ID [0-3]
};

static uint8_t ble_mcu_send_report[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x0A, 0x00, 0x00, 0x7d, 0x10, 0x04,
};

static uint8_t ble_mcu_send_consumer_report[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x06, 0x00, 0x00, 0x7d, 0x10, 0x08,
};

static uint8_t ble_mcu_unpair[10] = {
    0x7b, 0x12, 0x53, 0x00, 0x02, 0x00, 0x00, 0x7d, 0x40, 0x05,
};

/* One-shot slot-key state sent before the official 0x40/0x01 or 0x04 command. */
static uint8_t ble_mcu_slot_state[10] = {
    0x7b, 0x12, 0x43, 0x00, 0x04, 0x00, 0x00, 0x7d, 0x20, 0x0b,
};

/* Reply sent by the official keyboard MCU after a BLE 0x20/0x0c request. */
static uint8_t ble_mcu_hid_handshake_response[12] = {
    0x7b, 0x12, 0x43, 0x00, 0x04, 0x00, 0x00, 0x7d, 0x20, 0x0c, 0x00, 0x00,
};

/* Reply emitted by the official keyboard MCU for an incoming 0x20/0x07. */
static uint8_t ble_mcu_state_sync_response[10] = {
    0x7b, 0x12, 0x43, 0x00, 0x03, 0x00, 0x00, 0x7d, 0x20, 0x07,
};

static uint8_t ble_mcu_bootload[11] = {0x7b, 0x10, 0x51, 0x10, 0x03, 0x00, 0x00, 0x7d, 0x02, 0x01, 0x01};

static host_driver_t           *last_host_driver = NULL;
ble_capslock_t                  ble_capslock = {._dummy = {0}, .caps_lock = false};
static ap2_ble_state_t          ble_state;
#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
static ap2_ble_213_slot_state_t ble_213_slot_state;
#endif
static annepro2_ble_parser_t    ble_rx_parser;
static led_t                    ble_led_state;
#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
static uint8_t  ble_debug_keyboard_reports;
static bool     ble_debug_build_log_pending;
static uint32_t ble_debug_build_log_timer;
#endif
#ifdef NKRO_ENABLE
static bool lastNkroStatus = false;
#endif // NKRO_ENABLE

__attribute__((weak)) void annepro2_ble_status_changed_user(annepro2_ble_status_t status, uint8_t slot) {}

static void ap2_ble_begin_route_request(void) {
    /* Do not leave reports routed to an old BLE link while selecting a slot. */
    ble_led_state.raw = 0;
    if (host_get_driver() == &ap2_ble_driver) {
        clear_keyboard();
#ifdef NKRO_ENABLE
        keymap_config.nkro = lastNkroStatus;
#endif
        host_set_driver(last_host_driver);
        AP2_BLE_LOG("route pending");
    }
}

/* -------------------- Public Function Implementation ---------------------- */

void annepro2_ble_init(void) {
    sdStart(&SD1, &ble_uart_config);
    annepro2_ble_startup();
    wait_ms(100);
    ap2_ble_drain_rx();
}

bool annepro2_ble_process_record(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= KC_AP2_BT1 && keycode <= KC_AP2_BT4) {
        const uint8_t slot = keycode - KC_AP2_BT1;
        if (record->event.pressed) {
            annepro2_ble_slot_press(slot);
#ifdef ANNEPRO2_LED_MCU_ENABLE
            const ap2_led_t blue = {
                .p.blue  = 0xff,
                .p.red   = 0x00,
                .p.green = 0x00,
                .p.alpha = 0xff,
            };
            ap2_led_blink(record->event.key.row, record->event.key.col, blue, 8, 50);
#endif
        } else {
            annepro2_ble_slot_release(slot);
        }
        return false;
    }

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case KC_AP2_USB:
            annepro2_ble_disconnect();
            return false;
        case KC_AP2_BT_UNPAIR:
            annepro2_ble_unpair();
            return false;
        default:
            return true;
    }
}

void annepro2_ble_bootload(void) {
    sdWrite(&SD1, ble_mcu_bootload, sizeof(ble_mcu_bootload));
}

void annepro2_ble_startup(void) {
    const int8_t saved_slot = ap2_ble_read_saved_slot();
#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
    ap2_ble_213_slot_reset(&ble_213_slot_state);
#endif
#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
    ap2_ble_log_build();
    ble_debug_build_log_pending = true;
    ble_debug_build_log_timer   = timer_read32();
#endif
    AP2_BLE_LOG("wake %d", saved_slot);
    ap2_ble_execute_actions(ap2_ble_state_startup(&ble_state, saved_slot, timer_read32()));
}

void annepro2_ble_broadcast(uint8_t port) {
    AP2_BLE_LOG("broadcast request slot=%u", port > 3 ? 3 : port);
    ap2_ble_execute_actions(ap2_ble_state_broadcast(&ble_state, port, timer_read32()));
}

void annepro2_ble_connect(uint8_t port) {
    AP2_BLE_LOG("connect request slot=%u", port > 3 ? 3 : port);
    ap2_ble_execute_actions(ap2_ble_state_connect(&ble_state, port, timer_read32()));
}

void annepro2_ble_slot_press(uint8_t port) {
    /*
     * Match the official keyboard MCU: a tap connects on key release, while a
     * 500 ms hold starts pairing/advertising and does nothing on release.
     */
    AP2_BLE_LOG("slot %u press", port > 3 ? 3 : port);
    ap2_ble_execute_actions(ap2_ble_state_slot_press(&ble_state, port, timer_read32()));
}

void annepro2_ble_slot_release(uint8_t port) {
    AP2_BLE_LOG("slot %u release", port > 3 ? 3 : port);
    ap2_ble_execute_actions(ap2_ble_state_slot_release(&ble_state, port, timer_read32()));
}

void annepro2_ble_disconnect(void) {
    AP2_BLE_LOG("disconnect");
#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
    ap2_ble_213_slot_reset(&ble_213_slot_state);
#endif
    ap2_ble_execute_actions(ap2_ble_state_disconnect(&ble_state));
    ap2_ble_notify_status(ANNEPRO2_BLE_STATUS_IDLE);
    ap2_ble_reset_rx_parser();
}

void annepro2_ble_unpair(void) {
    AP2_BLE_LOG("tx unpair");
#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
    ap2_ble_213_slot_reset(&ble_213_slot_state);
#endif
    ap2_ble_execute_actions(ap2_ble_state_unpair(&ble_state));
    ap2_ble_notify_status(ANNEPRO2_BLE_STATUS_IDLE);
    ap2_ble_reset_rx_parser();
}

void annepro2_ble_task(void) {
    ap2_ble_drain_rx();
    const uint32_t now = timer_read32();
#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
    if (ble_debug_build_log_pending && timer_elapsed32(ble_debug_build_log_timer) >= AP2_BLE_BUILD_LOG_DELAY) {
        ble_debug_build_log_pending = false;
        ap2_ble_log_build();
    }
#endif
    if (annepro2_ble_parser_expire(&ble_rx_parser, now)) {
        AP2_BLE_LOG("rx partial timeout");
    }
    ap2_ble_execute_actions(ap2_ble_state_task(&ble_state, now));

#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
    uint16_t deferred_actions;
    const ap2_ble_213_slot_actions_t slot_actions = ap2_ble_213_slot_task(&ble_213_slot_state, now, &deferred_actions);
    ap2_ble_execute_213_slot_actions(slot_actions);
    if (slot_actions & AP2_BLE_213_SLOT_ACTION_DISPATCH) {
        ap2_ble_execute_actions_now((ap2_ble_actions_t)deferred_actions);
    }
#endif
}

void annepro2_ble_rx_byte(uint8_t byte) {
    const uint8_t                   *frame;
    uint8_t                          size;
    const annepro2_ble_parse_event_t event = annepro2_ble_parser_feed(&ble_rx_parser, byte, timer_read32(), &frame, &size);

    switch (event) {
        case ANNEPRO2_BLE_PARSE_FRAME:
            ap2_ble_handle_rx_frame(frame, size);
            break;
        case ANNEPRO2_BLE_PARSE_TIMEOUT:
            AP2_BLE_LOG("rx partial timeout");
            break;
        case ANNEPRO2_BLE_PARSE_INVALID_LENGTH:
            AP2_BLE_LOG("rx invalid length");
            break;
        case ANNEPRO2_BLE_PARSE_INVALID_DELIMITER:
            AP2_BLE_LOG("rx invalid delimiter");
            break;
        case ANNEPRO2_BLE_PARSE_NONE:
            break;
    }
}

/* ------------------- Static Function Implementation ----------------------- */
static void ap2_ble_execute_actions(ap2_ble_actions_t actions) {
    const ap2_ble_actions_t command_actions = actions & (AP2_BLE_ACTION_SEND_BROADCAST | AP2_BLE_ACTION_SEND_CONNECT);

#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
    if (ap2_ble_213_slot_active(&ble_213_slot_state) && (actions & AP2_BLE_ACTION_ROUTE_USB) && command_actions == 0) {
        AP2_BLE_LOG("cancel 213 slot prepare");
        ap2_ble_213_slot_reset(&ble_213_slot_state);
    }

    if (command_actions != 0 && ap2_ble_213_slot_should_prepare(ble_state.command_retries)) {
        const ap2_ble_actions_t deferred_actions = actions & (AP2_BLE_ACTION_SEND_SLOT_STATE | AP2_BLE_ACTION_SEND_BROADCAST | AP2_BLE_ACTION_SEND_CONNECT);
        ap2_ble_execute_actions_now(actions & ~deferred_actions);
        ap2_ble_execute_213_slot_actions(ap2_ble_213_slot_begin(&ble_213_slot_state, ble_state.selected_slot, deferred_actions, timer_read32()));
        return;
    }
#else
    (void)command_actions;
#endif

    ap2_ble_execute_actions_now(actions);
}

static void ap2_ble_execute_actions_now(ap2_ble_actions_t actions) {
    if (actions != AP2_BLE_ACTION_NONE) {
        AP2_BLE_LOG("actions=%03X state=%u slot=%u retries=%u", actions, (unsigned)ble_state.state, ble_state.selected_slot, ble_state.command_retries);
    }

    if (actions & AP2_BLE_ACTION_SEND_UNPAIR) {
        sdWrite(&SD1, ble_mcu_unpair, sizeof(ble_mcu_unpair));
    }
    if (actions & AP2_BLE_ACTION_ROUTE_USB) {
        ap2_ble_begin_route_request();
    }
    if (actions & AP2_BLE_ACTION_SEND_WAKEUP) {
        sdWrite(&SD1, ble_mcu_wakeup, sizeof(ble_mcu_wakeup));
    }
    if (actions & AP2_BLE_ACTION_SEND_SLOT_STATE) {
        ap2_ble_send_slot_state();
    }
    if (actions & AP2_BLE_ACTION_SEND_BROADCAST) {
        if (ble_state.command_retries == 0) {
            ap2_ble_notify_status(ble_state.command_slot_broadcast ? ANNEPRO2_BLE_STATUS_ADVERTISING : ANNEPRO2_BLE_STATUS_CONNECTING);
        }
        ap2_ble_send_broadcast();
    }
    if (actions & AP2_BLE_ACTION_SEND_CONNECT) {
        if (ble_state.command_retries == 0) {
            ap2_ble_notify_status(ANNEPRO2_BLE_STATUS_CONNECTING);
        }
        ap2_ble_send_connect();
    }
    if (actions & AP2_BLE_ACTION_CLEAR_SLOT) {
        ap2_ble_save_slot(-1);
    }
    if (actions & AP2_BLE_ACTION_ROUTE_BLE) {
        ap2_ble_switch_ble_driver();
        ap2_ble_notify_status(ANNEPRO2_BLE_STATUS_CONNECTED);
    }
    if (actions & AP2_BLE_ACTION_SAVE_SLOT) {
        ap2_ble_save_slot((int8_t)ble_state.selected_slot);
    }
    if (actions & AP2_BLE_ACTION_NOTIFY_FAILURE) {
        ap2_ble_notify_status(ANNEPRO2_BLE_STATUS_FAILED);
    }
}

#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
static void ap2_ble_execute_213_slot_actions(ap2_ble_213_slot_actions_t actions) {
    uint8_t frame[AP2_BLE_213_SLOT_FRAME_MAX_SIZE];
    uint8_t size;

    if (actions & AP2_BLE_213_SLOT_ACTION_QUERY) {
        AP2_BLE_LOG("tx 213 slot query target=%u", ble_213_slot_state.target_slot);
        size = ap2_ble_213_slot_encode_query(frame);
        sdWrite(&SD1, frame, size);
    }
    if (actions & AP2_BLE_213_SLOT_ACTION_SELECT) {
        AP2_BLE_LOG("tx 213 slot select=%u", ble_213_slot_state.target_slot);
        size = ap2_ble_213_slot_encode_select(ble_213_slot_state.target_slot, frame);
        sdWrite(&SD1, frame, size);
    }
    if (actions & AP2_BLE_213_SLOT_ACTION_PREPARE_1) {
        AP2_BLE_LOG("tx 213 slot prepare=1");
        size = ap2_ble_213_slot_encode_prepare(1, frame);
        sdWrite(&SD1, frame, size);
    }
    if (actions & AP2_BLE_213_SLOT_ACTION_PREPARE_2) {
        AP2_BLE_LOG("tx 213 slot prepare=2");
        size = ap2_ble_213_slot_encode_prepare(2, frame);
        sdWrite(&SD1, frame, size);
    }
}
#endif

static void ap2_ble_send_broadcast(void) {
    AP2_BLE_LOG("tx broadcast slot=%u attempt=%u", ble_state.selected_slot, ble_state.command_retries + 1);
    sdWrite(&SD1, ble_mcu_start_broadcast, sizeof(ble_mcu_start_broadcast));
    sdPut(&SD1, ble_state.selected_slot);
}

static void ap2_ble_send_connect(void) {
    AP2_BLE_LOG("tx connect slot=%u attempt=%u", ble_state.selected_slot, ble_state.command_retries + 1);
    sdWrite(&SD1, ble_mcu_connect, sizeof(ble_mcu_connect));
    sdPut(&SD1, ble_state.selected_slot);
}

static void ap2_ble_send_slot_state(void) {
    annepro2_ble_slot_state_t slot_state;
    annepro2_ble_encode_slot_state(ble_state.command_slot_broadcast, &slot_state);

    AP2_BLE_LOG("tx slot state command=%02X action=%u", slot_state.command, slot_state.action);
    ble_mcu_slot_state[9] = slot_state.command;
    sdWrite(&SD1, ble_mcu_slot_state, sizeof(ble_mcu_slot_state));
    sdPut(&SD1, ble_state.selected_slot);
    sdPut(&SD1, slot_state.action);
}

static void ap2_ble_handle_command_ack(uint8_t command, uint8_t value) {
    const ap2_ble_state_id_t before = ble_state.state;
    AP2_BLE_LOG("rx command ack=%02X value=%02X state=%u", command, value, (unsigned)before);
    ap2_ble_execute_actions(ap2_ble_state_command_ack(&ble_state, command, timer_read32()));
    if (before == ble_state.state) {
        AP2_BLE_LOG("ignore stale command ack=%02X", command);
    }
}

static void ap2_ble_notify_status(annepro2_ble_status_t status) {
    AP2_BLE_LOG("status=%u slot=%u", (unsigned)status, ble_state.selected_slot);
    annepro2_ble_status_changed_user(status, ble_state.selected_slot);
}

#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
static void ap2_ble_log_build(void) {
#    if defined(QMK_USERSPACE_VERSION)
    AP2_BLE_LOG("build qmk=%s userspace=%s", QMK_GIT_HASH, QMK_USERSPACE_VERSION);
#    else
    AP2_BLE_LOG("build qmk=%s", QMK_GIT_HASH);
#    endif
}
#endif

static void ap2_ble_switch_ble_driver(void) {
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
#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
    ble_debug_keyboard_reports = 0;
#endif
    AP2_BLE_LOG("route ble");
}

static void ap2_ble_handle_rx_frame(const uint8_t *frame, uint8_t size) {
#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
    ap2_ble_log_rx_frame(frame, size);
#endif

    if (size >= 11 && frame[1] == 0x12 && frame[2] == 0x35) {
        AP2_BLE_LOG("rx decoded group=%02X command=%02X value=%02X state=%u", frame[8], frame[9], frame[10], (unsigned)ble_state.state);

#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
        uint8_t current_slot;
        if (ap2_ble_213_slot_decode_response(frame, size, &current_slot)) {
            AP2_BLE_LOG("rx 213 current slot=%u", current_slot);
            ap2_ble_213_slot_response(&ble_213_slot_state, current_slot);
        }
#endif

        if (frame[4] == 0x03 && frame[5] == 0x00 && frame[8] == 0x40 && (frame[9] == 0x01 || frame[9] == 0x04)) {
            ap2_ble_handle_command_ack(frame[9], frame[10]);
        }

        /*
         * The official keyboard MCU preserves the value and reverses the
         * routing field when replying to this state-sync request.
         */
        if (frame[4] == 0x03 && frame[5] == 0x00 && frame[8] == 0x20 && frame[9] == 0x07) {
            bool caps_lock;
            if (annepro2_ble_decode_caps_lock(frame, size, &caps_lock)) {
                ble_capslock.caps_lock   = caps_lock;
                ble_led_state.caps_lock = caps_lock;
                AP2_BLE_LOG("rx caps lock=%u leds=%02X", caps_lock, ble_led_state.raw);
            } else {
                AP2_BLE_LOG("ignore invalid caps lock value=%02X", frame[10]);
            }
            AP2_BLE_LOG("tx state sync response value=%02X", frame[10]);
            sdWrite(&SD1, ble_mcu_state_sync_response, sizeof(ble_mcu_state_sync_response));
            sdPut(&SD1, frame[10]);
        }

        /*
         * The official keyboard firmware answers an incoming 0x20/0x0c with
         * a 0x20/0x0c response before continuing. Hardware traces show this
         * handshake only after macOS has completed the BLE/HID setup.
         * 0x40/0x01 and 0x40/0x04 are command acknowledgements and must not
         * change QMK's host driver.
         */
        if (frame[4] == 0x03 && frame[5] == 0x00 && frame[8] == 0x20 && frame[9] == 0x0c) {
            AP2_BLE_LOG("tx hid handshake response");
            sdWrite(&SD1, ble_mcu_hid_handshake_response, sizeof(ble_mcu_hid_handshake_response));
            const ap2_ble_actions_t actions = ap2_ble_state_handshake(&ble_state);
            if (actions & AP2_BLE_ACTION_ROUTE_BLE) {
                AP2_BLE_LOG("rx hid handshake ready");
            }
            ap2_ble_execute_actions(actions);
        }
    } else {
        AP2_BLE_LOG("rx frame len=%u type=%02X/%02X", size, frame[1], frame[2]);
    }
}

#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
static void ap2_ble_log_rx_frame(const uint8_t *frame, uint8_t size) {
    uprintf("AP2 BLE %08lX rx%u", (unsigned long)timer_read32(), size);
    for (uint8_t i = 0; i < size; i++) {
        uprintf(" %02X", frame[i]);
    }
    uprintf("\n");
}
#endif

static void ap2_ble_reset_rx_parser(void) {
    annepro2_ble_parser_reset(&ble_rx_parser);
}

static void ap2_ble_drain_rx(void) {
    while (!sdGetWouldBlock(&SD1)) {
        annepro2_ble_rx_byte((uint8_t)sdGet(&SD1));
    }
}

static int8_t ap2_ble_read_saved_slot(void) {
    int8_t slot;
    return annepro2_ble_decode_config(eeconfig_read_kb(), &slot) ? slot : -1;
}

static void ap2_ble_save_slot(int8_t slot) {
    if (slot < -1 || slot > 3) {
        return;
    }

    uint32_t config;
    if (!annepro2_ble_encode_config(slot, &config)) {
        return;
    }
    if (eeconfig_read_kb() != config) {
        eeconfig_update_kb(config);
    }
}

static uint8_t ap2_ble_leds(void) {
    return ble_led_state.raw;
}

static void ap2_ble_mouse(report_mouse_t *report) {}

static void ap2_ble_extra(report_extra_t *report) {
    if (report->report_id == REPORT_ID_CONSUMER) {
        const uint16_t usage       = report->usage;
        const size_t   usage_count = usage == 0 ? 0 : 1;
        uint8_t        payload[ANNEPRO2_BLE_CONSUMER_REPORT_SIZE];

        if (!annepro2_ble_encode_consumer(&usage, usage_count, payload)) {
            annepro2_ble_encode_consumer(&usage, 0, payload);
        }

        /* UART payload includes the 0x10/0x08 group and command bytes. */
        ble_mcu_send_consumer_report[4] = sizeof(payload) + 2;
        sdPut(&SD1, 0x0);
        sdWrite(&SD1, ble_mcu_send_consumer_report, sizeof(ble_mcu_send_consumer_report));
        sdWrite(&SD1, payload, sizeof(payload));
        AP2_BLE_LOG("tx consumer usage=%04X bytes=%u", usage, (unsigned)sizeof(payload));
    }
}

/*!
 * @brief  Send keyboard HID report for Bluetooth driver
 */
static void ap2_ble_keyboard(report_keyboard_t *report) {
    sdPut(&SD1, 0x0);
    sdWrite(&SD1, ble_mcu_send_report, sizeof(ble_mcu_send_report));
    sdWrite(&SD1, (uint8_t *)report, KEYBOARD_REPORT_SIZE);
#if defined(CONSOLE_ENABLE) && defined(ANNEPRO2_BLE_DEBUG)
    if (ble_debug_keyboard_reports < 3) {
        ble_debug_keyboard_reports++;
        AP2_BLE_LOG("tx keyboard report=%u", ble_debug_keyboard_reports);
    }
#endif
}
