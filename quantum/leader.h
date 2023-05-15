// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdbool.h>
#include <stdint.h>

/**
 * \defgroup leader
 *
 * Leader Key
 * \{
 */

/**
 * \brief User callback, invoked when the leader sequence begins.
 */
void leader_start_user(void);

/**
 * \brief User callback, invoked when the leader sequence ends.
 */
void leader_end_user(void);

/**
 * Begin the leader sequence, resetting the buffer and timer.
 */
void leader_start(void);

/**
 * End the leader sequence.
 */
void leader_end(void);

void leader_task(void);

/**
 * Whether the leader sequence is active.
 */
bool leader_sequence_active(void);

/**
 * Add the given keycode to the sequence buffer.
 *
 * If `LEADER_NO_TIMEOUT` is defined, the timer is reset if the buffer is empty.
 *
 * \param keycode The keycode to add.
 *
 * \return `true` if the keycode was added, `false` if the buffer is full.
 */
bool leader_sequence_add(uint16_t keycode);

/**
 * Whether the leader sequence has reached the timeout.
 *
 * If `LEADER_NO_TIMEOUT` is defined, the buffer must also contain at least one key.
 */
bool leader_sequence_timed_out(void);

/**
 * Reset the leader sequence timer.
 */
void leader_reset_timer(void);

/**
 * Check the sequence buffer for the given keycode.
 *
 * \param kc The keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_sequence_one_key(uint16_t kc);

/**
 * Check the sequence buffer for the given keycodes.
 *
 * \param kc1 The first keycode to check.
 * \param kc2 The second keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_sequence_two_keys(uint16_t kc1, uint16_t kc2);

/**
 * Check the sequence buffer for the given keycodes.
 *
 * \param kc1 The first keycode to check.
 * \param kc2 The second keycode to check.
 * \param kc3 The third keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_sequence_three_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3);

/**
 * Check the sequence buffer for the given keycodes.
 *
 * \param kc1 The first keycode to check.
 * \param kc2 The second keycode to check.
 * \param kc3 The third keycode to check.
 * \param kc4 The fourth keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_sequence_four_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4);

/**
 * Check the sequence buffer for the given keycodes.
 *
 * \param kc1 The first keycode to check.
 * \param kc2 The second keycode to check.
 * \param kc3 The third keycode to check.
 * \param kc4 The fourth keycode to check.
 * \param kc5 The fifth keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_sequence_five_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4, uint16_t kc5);

/** \} */
