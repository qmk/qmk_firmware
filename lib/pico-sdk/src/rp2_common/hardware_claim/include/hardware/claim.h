/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_CLAIM_H
#define _HARDWARE_CLAIM_H

#include "pico.h"
#include "hardware/sync.h"

/** \file claim.h
 *  \defgroup hardware_claim hardware_claim
 *
 *  Lightweight hardware resource management
 *
 * `hardware_claim` provides a simple API for management of hardware resources at runtime.
 *
 * This API is usually called by other hardware specific _claiming_ APIs and provides simple
 * multi-core safe methods to manipulate compact bit-sets representing hardware resources.
 *
 * This API allows any other library to cooperatively participate in a scheme by which
 * both compile time and runtime allocation of resources can co-exist, and conflicts
 * can be avoided or detected (depending on the use case) without the libraries having
 * any other knowledge of each other.
 *
 * Facilities are providing for:
 *
 * 1. Claiming resources (and asserting if they are already claimed)
 * 2. Freeing (unclaiming) resources
 * 3. Finding unused resources
 */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Atomically claim a resource, panicking if it is already in use
 *  \ingroup hardware_claim
 *
 * The resource ownership is indicated by the bit_index bit in an array of bits.
 *
 * \param bits pointer to an array of bits (8 bits per byte)
 * \param bit_index resource to claim (bit index into array of bits)
 * \param message string to display if the bit cannot be claimed; note this may have a single printf format "%d" for the bit
 */
void hw_claim_or_assert(uint8_t *bits, uint bit_index, const char *message);

/*! \brief Atomically claim one resource out of a range of resources, optionally asserting if none are free
 *  \ingroup hardware_claim
 *
 * \param bits pointer to an array of bits (8 bits per byte)
 * \param required true if this method should panic if the resource is not free
 * \param bit_lsb the lower bound (inclusive) of the resource range to claim from
 * \param bit_msb the upper bound (inclusive) of the resource range to claim from
 * \param message string to display if the bit cannot be claimed
 * \return the bit index representing the claimed or -1 if none are available in the range, and required = false
 */
int hw_claim_unused_from_range(uint8_t *bits, bool required, uint bit_lsb, uint bit_msb, const char *message);

/*! \brief Determine if a resource is claimed at the time of the call
 *  \ingroup hardware_claim
 *
 * The resource ownership is indicated by the bit_index bit in an array of bits.
 *
 * \param bits pointer to an array of bits (8 bits per byte)
 * \param bit_index resource to check (bit index into array of bits)
 * \return true if the resource is claimed
 */
bool hw_is_claimed(const uint8_t *bits, uint bit_index);

/*! \brief Atomically unclaim a resource
 *  \ingroup hardware_claim
 *
 * The resource ownership is indicated by the bit_index bit in an array of bits.
 *
 * \param bits pointer to an array of bits (8 bits per byte)
 * \param bit_index resource to unclaim (bit index into array of bits)
 */
void hw_claim_clear(uint8_t *bits, uint bit_index);

/*! \brief Acquire the runtime mutual exclusion lock provided by the `hardware_claim` library
 *  \ingroup hardware_claim
 *
 * This method is called automatically by the other `hw_claim_` methods, however it is provided as a convenience
 * to code that might want to protect other hardware initialization code from concurrent use.
 *
 * \note hw_claim_lock() uses a spin lock internally, so disables interrupts on the calling core, and will deadlock
 * if the calling core already owns the lock.
 *
 * \return a token to pass to hw_claim_unlock()
 */
uint32_t hw_claim_lock(void);

/*! \brief Release the runtime mutual exclusion lock provided by the `hardware_claim` library
 *  \ingroup hardware_claim
 *
 * \note This method MUST be called from the same core that call hw_claim_lock()
 *
 * \param token the token returned by the corresponding call to hw_claim_lock()
 */
void hw_claim_unlock(uint32_t token);

#ifdef __cplusplus
}
#endif

#endif
