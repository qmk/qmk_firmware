// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>

#include "compiler_support.h"
#include "util.h"

/**
 * \enum connection_host_t
 *
 * An enumeration of the possible hosts.
 */
typedef enum connection_host_t {
    CONNECTION_HOST_AUTO,

    CONNECTION_HOST_NONE,
    CONNECTION_HOST_USB,
    CONNECTION_HOST_BLUETOOTH,
    CONNECTION_HOST_2P4GHZ
} connection_host_t;

/**
 * \union connection_config_t
 *
 * Configuration structure for the connection subsystem.
 */
typedef union connection_config_t {
    uint8_t raw;
    struct {
        connection_host_t desired_host : 4;
        uint8_t           bluetooth_profile : 4;
    } PACKED;
} PACKED connection_config_t;

STATIC_ASSERT(sizeof(connection_config_t) == sizeof(uint8_t), "Connection EECONFIG out of spec.");

/**
 * \brief Initialize the subsystem.
 *
 * This function must be called only once, before any of the below functions can be called.
 */
void connection_init(void);

/**
 * \brief Get currently configured host. Does not resolve 'CONNECTION_HOST_AUTO'.
 *
 * \return 'connection_host_t' of the configured host.
 */
connection_host_t connection_get_host_raw(void);

/**
 * \brief Get current active host.
 *
 * \return 'connection_host_t' of the configured host.
 */
connection_host_t connection_auto_detect_host(void);

/**
 * \brief Get currently configured host. Resolves 'CONNECTION_HOST_AUTO' using 'connection_auto_detect_host()'.
 *
 * \return 'connection_host_t' of the configured host.
 */
connection_host_t connection_get_host(void);

/**
 * \brief Get current host. New state is not written to EEPROM.
 *
 * \param host The host to configure.
 */
void connection_set_host_noeeprom(connection_host_t host);

/**
 * \brief Get current host.
 *
 * \param host The host to configure.
 */
void connection_set_host(connection_host_t host);

/**
 * \brief Move to the next potential host. New state is not written to EEPROM.
 *
 */
void connection_next_host_noeeprom(void);

/**
 * \brief Move to the next potential host.
 *
 */
void connection_next_host(void);

/**
 * \brief Move to the previous potential host. New state is not written to EEPROM.
 *
 */
void connection_prev_host_noeeprom(void);

/**
 * \brief Move to the previous potential host.
 *
 */
void connection_prev_host(void);

/**
 * \brief user hook called when changing configured host
 *
 */
void connection_host_changed_user(connection_host_t host);

/**
 * \brief keyboard hook called when changing configured host
 *
 */
void connection_host_changed_kb(connection_host_t host);

/**
 * \brief Set the active Bluetooth profile (0-indexed).
 *
 * Clamped to the active driver's `bluetooth_get_max_profile() - 1`.
 *
 * \param profile The profile index to activate.
 */
void connection_set_bluetooth_profile(uint8_t profile);

/**
 * \brief Get the currently configured Bluetooth profile.
 *
 * \return Zero-based profile index.
 */
uint8_t connection_get_bluetooth_profile(void);

/**
 * \brief Move to the next Bluetooth profile.
 */
void connection_next_bluetooth_profile(void);

/**
 * \brief Move to the previous Bluetooth profile.
 */
void connection_prev_bluetooth_profile(void);

/**
 * \brief user hook called when changing the Bluetooth profile.
 */
void connection_bluetooth_profile_changed_user(uint8_t profile);

/**
 * \brief keyboard hook called when changing the Bluetooth profile.
 */
void connection_bluetooth_profile_changed_kb(uint8_t profile);
