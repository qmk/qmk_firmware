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
    uint8_t           raw;
    connection_host_t desired_host : 8;
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
