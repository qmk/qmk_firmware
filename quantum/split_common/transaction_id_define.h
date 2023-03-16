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
#ifdef USE_I2C
    I2C_EXECUTE_CALLBACK,
#endif // USE_I2C

    GET_SLAVE_MATRIX_CHECKSUM,
    GET_SLAVE_MATRIX_DATA,

#ifdef SPLIT_TRANSPORT_MIRROR
    PUT_MASTER_MATRIX,
#endif // SPLIT_TRANSPORT_MIRROR

#ifdef ENCODER_ENABLE
    GET_ENCODERS_CHECKSUM,
    GET_ENCODERS_DATA,
#endif // ENCODER_ENABLE

#ifndef DISABLE_SYNC_TIMER
    PUT_SYNC_TIMER,
#endif // DISABLE_SYNC_TIMER

#if !defined(NO_ACTION_LAYER) && defined(SPLIT_LAYER_STATE_ENABLE)
    PUT_LAYER_STATE,
    PUT_DEFAULT_LAYER_STATE,
#endif // !defined(NO_ACTION_LAYER) && defined(SPLIT_LAYER_STATE_ENABLE)

#ifdef SPLIT_LED_STATE_ENABLE
    PUT_LED_STATE,
#endif // SPLIT_LED_STATE_ENABLE

#ifdef SPLIT_MODS_ENABLE
    PUT_MODS,
#endif // SPLIT_MODS_ENABLE

#ifdef BACKLIGHT_ENABLE
    PUT_BACKLIGHT,
#endif // BACKLIGHT_ENABLE

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    PUT_RGBLIGHT,
#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

#if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
    PUT_LED_MATRIX,
#endif // defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    PUT_RGB_MATRIX,
#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

#if defined(WPM_ENABLE) && defined(SPLIT_WPM_ENABLE)
    PUT_WPM,
#endif // defined(WPM_ENABLE) && defined(SPLIT_WPM_ENABLE)

#if defined(OLED_ENABLE) && defined(SPLIT_OLED_ENABLE)
    PUT_OLED,
#endif // defined(OLED_ENABLE) && defined(SPLIT_OLED_ENABLE)

#if defined(ST7565_ENABLE) && defined(SPLIT_ST7565_ENABLE)
    PUT_ST7565,
#endif // defined(ST7565_ENABLE) && defined(SPLIT_ST7565_ENABLE)

#if defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)
    GET_POINTING_CHECKSUM,
    GET_POINTING_DATA,
    PUT_POINTING_CPI,
#endif // defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)

#if defined(SPLIT_WATCHDOG_ENABLE)
    PUT_WATCHDOG,
#endif // defined(SPLIT_WATCHDOG_ENABLE)

#if defined(HAPTIC_ENABLE) && defined(SPLIT_HAPTIC_ENABLE)
    PUT_HAPTIC,
#endif // defined(HAPTIC_ENABLE) && defined(SPLIT_HAPTIC_ENABLE)

#if defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)
    PUT_RPC_INFO,
    PUT_RPC_REQ_DATA,
    EXECUTE_RPC,
    GET_RPC_RESP_DATA,
#endif // defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)

// keyboard-specific
#ifdef SPLIT_TRANSACTION_IDS_KB
    SPLIT_TRANSACTION_IDS_KB,
#endif // SPLIT_TRANSACTION_IDS_KB

// user/keymap-specific
#ifdef SPLIT_TRANSACTION_IDS_USER
    SPLIT_TRANSACTION_IDS_USER,
#endif // SPLIT_TRANSACTION_IDS_USER

    NUM_TOTAL_TRANSACTIONS
};

// Ensure we only use 5 bits for transaction
_Static_assert(NUM_TOTAL_TRANSACTIONS <= (1 << 5), "Max number of usable transactions exceeded");
