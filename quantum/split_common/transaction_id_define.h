/* Copyright 2021 QMK
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

#pragma once

enum serial_transaction_id {
    GET_SLAVE_MATRIX_CHECKSUM = 0,
    GET_SLAVE_MATRIX_DATA,

#ifdef SPLIT_TRANSPORT_MIRROR
    PUT_MASTER_MATRIX,
#endif  // SPLIT_TRANSPORT_MIRROR

#ifdef ENCODER_ENABLE
    GET_ENCODERS_CHECKSUM,
    GET_ENCODERS_DATA,
#endif  // ENCODER_ENABLE

#ifndef DISABLE_SYNC_TIMER
    PUT_SYNC_TIMER,
#endif  // DISABLE_SYNC_TIMER

#ifdef SPLIT_MODS_ENABLE
    PUT_MODS,
#endif  // SPLIT_MODS_ENABLE

#ifdef BACKLIGHT_ENABLE
    PUT_BACKLIGHT,
#endif  // BACKLIGHT_ENABLE

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    PUT_RGBLIGHT,
#endif  // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    PUT_RGB_MATRIX,
#endif  // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

#ifdef WPM_ENABLE
    PUT_WPM,
#endif  // WPM_ENABLE

// keyboard-specific
#ifdef SPLIT_TRANSACTION_IDS_KB
    SPLIT_TRANSACTION_IDS_KB,
#endif  // SPLIT_TRANSACTION_IDS_KB

// user/keymap-specific
#ifdef SPLIT_TRANSACTION_IDS_USER
    SPLIT_TRANSACTION_IDS_USER,
#endif  // SPLIT_TRANSACTION_IDS_USER

    NUM_TOTAL_TRANSACTIONS
};
