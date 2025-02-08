// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/**
 * \file
 *
 * \defgroup secure Secure API
 *
 * \brief Exposes a set of functionality to act as a virtual padlock for your device
 * ...as long as that padlock is made of paper and it's currently raining.
 *
 * \{
 */

#include <stdint.h>
#include <stdbool.h>

/** \brief Available secure states
 */
typedef enum {
    SECURE_LOCKED,
    SECURE_PENDING,
    SECURE_UNLOCKED,
} secure_status_t;

/** \brief Query current secure state
 */
secure_status_t secure_get_status(void);

/** \brief Helper to check if unlocking is currently locked
 */
#define secure_is_locked() (secure_get_status() == SECURE_LOCKED)

/** \brief Helper to check if unlocking is currently in progress
 */
#define secure_is_unlocking() (secure_get_status() == SECURE_PENDING)

/** \brief Helper to check if unlocking is currently unlocked
 */
#define secure_is_unlocked() (secure_get_status() == SECURE_UNLOCKED)

/** \brief Lock down the device
 */
void secure_lock(void);

/** \brief Force unlock the device
 *
 * \warning bypasses user unlock sequence
 */
void secure_unlock(void);

/** \brief Begin listening for an unlock sequence
 */
void secure_request_unlock(void);

/** \brief Flag to the secure subsystem that user activity has happened
 *
 * Call when some user activity has happened and the device should remain unlocked
 */
void secure_activity_event(void);

/** \brief Flag to the secure subsystem that user has triggered a keypress
 *
 * Call to trigger processing of the unlock sequence
 */
void secure_keypress_event(uint8_t row, uint8_t col);

/** \brief Handle various secure subsystem background tasks
 */
void secure_task(void);

/** \brief quantum hook called when changing secure status device
 */
void secure_hook_quantum(secure_status_t secure_status);

/** \brief user hook called when changing secure status device
 */
bool secure_hook_user(secure_status_t secure_status);

/** \brief keyboard hook called when changing secure status device
 */
bool secure_hook_kb(secure_status_t secure_status);

/** \} */
