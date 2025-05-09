// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "connection.h"
#include "eeconfig.h"
#include "usb_util.h"
#include "util.h"

#ifdef BLUETOOTH_ENABLE
#    include "bluetooth.h"
#endif

// ======== DEPRECATED DEFINES - DO NOT USE ========
#ifdef OUTPUT_DEFAULT
#    undef CONNECTION_HOST_DEFAULT
#    define CONNECTION_HOST_DEFAULT OUTPUT_DEFAULT
#endif

__attribute__((weak)) void set_output_user(uint8_t output) {}
// ========

#define CONNECTION_HOST_INVALID 0xFF

#ifndef CONNECTION_HOST_DEFAULT
#    define CONNECTION_HOST_DEFAULT CONNECTION_HOST_AUTO
#endif

static const connection_host_t host_candidates[] = {
    CONNECTION_HOST_AUTO,
    CONNECTION_HOST_USB,
#ifdef BLUETOOTH_ENABLE
    CONNECTION_HOST_BLUETOOTH,
#endif
#if 0
    CONNECTION_HOST_2P4GHZ,
#endif
};

#define HOST_CANDIDATES_COUNT ARRAY_SIZE(host_candidates)

static connection_config_t config = {.desired_host = CONNECTION_HOST_INVALID};

void eeconfig_update_connection_default(void) {
    config.desired_host = CONNECTION_HOST_DEFAULT;

    eeconfig_update_connection(&config);
}

void connection_init(void) {
    eeconfig_read_connection(&config);
    if (config.desired_host == CONNECTION_HOST_INVALID) {
        eeconfig_update_connection_default();
    }
}

__attribute__((weak)) void connection_host_changed_user(connection_host_t host) {}
__attribute__((weak)) void connection_host_changed_kb(connection_host_t host) {}

static void handle_host_changed(void) {
    connection_host_changed_user(config.desired_host);
    connection_host_changed_kb(config.desired_host);

    // TODO: Remove deprecated callback
    set_output_user(config.desired_host);
}

void connection_set_host_noeeprom(connection_host_t host) {
    if (config.desired_host == host) {
        return;
    }

    config.desired_host = host;

    handle_host_changed();
}

void connection_set_host(connection_host_t host) {
    connection_set_host_noeeprom(host);

    eeconfig_update_connection(&config);
}

void connection_next_host_noeeprom(void) {
    uint8_t next = 0;
    for (uint8_t i = 0; i < HOST_CANDIDATES_COUNT; i++) {
        if (host_candidates[i] == config.desired_host) {
            next = i == HOST_CANDIDATES_COUNT - 1 ? 0 : i + 1;
            break;
        }
    }

    connection_set_host_noeeprom(host_candidates[next]);
}

void connection_next_host(void) {
    connection_next_host_noeeprom();

    eeconfig_update_connection(&config);
}

void connection_prev_host_noeeprom(void) {
    uint8_t next = 0;
    for (uint8_t i = 0; i < HOST_CANDIDATES_COUNT; i++) {
        if (host_candidates[i] == config.desired_host) {
            next = i == 0 ? HOST_CANDIDATES_COUNT - 1 : i - 1;
            break;
        }
    }

    connection_set_host_noeeprom(host_candidates[next]);
}

void connection_prev_host(void) {
    connection_prev_host_noeeprom();

    eeconfig_update_connection(&config);
}

connection_host_t connection_get_host_raw(void) {
    return config.desired_host;
}

connection_host_t connection_auto_detect_host(void) {
    if (usb_connected_state()) {
        return CONNECTION_HOST_USB;
    }

#ifdef BLUETOOTH_ENABLE
    if (bluetooth_is_connected()) {
        return CONNECTION_HOST_BLUETOOTH;
    }
#endif

    return CONNECTION_HOST_NONE;
}

connection_host_t connection_get_host(void) {
    if (config.desired_host == CONNECTION_HOST_AUTO) {
        return connection_auto_detect_host();
    }
    return config.desired_host;
}
