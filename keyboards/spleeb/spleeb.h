// Copyright 2022 Chris Hoage (@chrishoage)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#if defined(SPLEEB_ENCODER_MODE_MAP_ENABLE) && !defined(ENCODER_ENABLE)
#    error "Encoder must be enabled to use encoder mode map"
#endif

#if defined(SPLEEB_ENCODER_MODE_MAP_ENABLE) && defined(ENCODER_MAP_ENABLE)
#    error "Encoder mode map can not be used with encoder map"
#endif

enum spleeb_keycodes {
    POINTER_DEFAULT_DPI_FORWARD = QK_KB,
    POINTER_DEFAULT_DPI_REVERSE,
    POINTER_SNIPING_DPI_FORWARD,
    POINTER_SNIPING_DPI_REVERSE,
    SNIPING_MODE,
    SNIPING_MODE_TOGGLE,
    DRAGSCROLL_MODE,
    DRAGSCROLL_MODE_TOGGLE,
    ENC_MODE_STEP_LEFT,
    ENC_MODE_STEP_RIGHT,
};

#define DF_MOD POINTER_DEFAULT_DPI_FORWARD
#define DF_RMOD POINTER_DEFAULT_DPI_REVERSE
#define SP_MOD POINTER_SNIPING_DPI_FORWARD
#define SP_RMOD POINTER_SNIPING_DPI_REVERSE
#define SNIPING SNIPING_MODE
#define SNP_TOG SNIPING_MODE_TOGGLE
#define DRGSCRL DRAGSCROLL_MODE
#define DRG_TOG DRAGSCROLL_MODE_TOGGLE
#define ENC_STL ENC_MODE_STEP_LEFT
#define ENC_STR ENC_MODE_STEP_RIGHT

#ifdef POINTING_DEVICE_ENABLE
#    ifndef SPLEEB_MINIMUM_DEFAULT_DPI
#        define SPLEEB_MINIMUM_DEFAULT_DPI 300
#    endif // SPLEEB_MINIMUM_DEFAULT_DPI

#    ifndef SPLEEB_DEFAULT_DPI_CONFIG_STEP
#        define SPLEEB_DEFAULT_DPI_CONFIG_STEP 100
#    endif // SPLEEB_DEFAULT_DPI_CONFIG_STEP

#    ifndef SPLEEB_MINIMUM_SNIPING_DPI
#        define SPLEEB_MINIMUM_SNIPING_DPI 100
#    endif // SPLEEB_MINIMUM_SNIPING_DPI

#    ifndef SPLEEB_SNIPING_DPI_CONFIG_STEP
#        define SPLEEB_SNIPING_DPI_CONFIG_STEP 100
#    endif // SPLEEB_SNIPING_DPI_CONFIG_STEP

#    ifndef SPLEEB_DRAGSCROLL_DIVISOR
#        define SPLEEB_DRAGSCROLL_DIVISOR 64
#    endif // !SPLEEB_DRAGSCROLL_DIVISOR
#endif     // POINTING_DEVICE_ENABLE

#ifdef SPLEEB_ENCODER_MODE_MAP_ENABLE
#    ifndef SPLEEB_ENCODER_MODE_COUNT
#        define SPLEEB_ENCODER_MODE_COUNT 4
#    endif

typedef struct {
    uint8_t mode;
    // Discriminate between array members which are (un)initialized
    bool initalized;
} const spleeb_enc_mode_t;

const spleeb_enc_mode_t spleeb_encoder_mode_map[NUM_ENCODERS][SPLEEB_ENCODER_MODE_COUNT];

// SPLEEB_ENC_MODE initializes the spleeb_enc_mode_t struct such that
// uninitialized mode_map members can be discriminated against when looking up
// mapped encoder modes.
#    define SPLEEB_ENC_MODE(mode) \
        { mode, true }
#endif // SPLEEB_ENCODER_MODE_MAP_ENABLE

#ifdef POINTING_DEVICE_ENABLE

/** \brief Return the current DPI value for the pointer's default mode. */
uint16_t spleeb_get_pointer_default_dpi(void);

/**
 * \brief Update the pointer's default DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to SPLEEB_DEFAULT_DPI_CONFIG_STEP.
 *
 * The new value is persisted in EEPROM.
 */
void spleeb_cycle_pointer_default_dpi(bool forward);

/**
 * \brief Same as `spleeb_cycle_pointer_default_dpi`, but do not write to
 * EEPROM.
 *
 * This means that reseting the board will revert the value to the last
 * persisted one.
 */
void spleeb_cycle_pointer_default_dpi_noeeprom(bool forward);

/** \brief Return the current DPI value for the pointer's sniper-mode. */
uint16_t spleeb_get_pointer_sniping_dpi(void);

/**
 * \brief Update the pointer's sniper-mode DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to SPLEEB_SNIPING_DPI_CONFIG_STEP.
 *
 * The new value is persisted in EEPROM.
 */
void spleeb_cycle_pointer_sniping_dpi(bool forward);

/**
 * \brief Same as `spleeb_cycle_pointer_sniping_dpi`, but do not write to
 * EEPROM.
 *
 * This means that reseting the board will revert the value to the last
 * persisted one.
 */
void spleeb_cycle_pointer_sniping_dpi_noeeprom(bool forward);

/** \brief Whether sniper-mode is enabled. */
bool spleeb_get_pointer_sniping_enabled(void);

/**
 * \brief Enable/disable sniper mode.
 *
 * When sniper mode is enabled the dpi is reduced to slow down the pointer for
 * more accurate movements.
 */
void spleeb_set_pointer_sniping_enabled(bool enable);

/** \brief Whether drag-scroll is enabled. */
bool spleeb_get_pointer_dragscroll_enabled(void);

/**
 * \brief Enable/disable drag-scroll mode.
 *
 * When drag-scroll mode is enabled, horizontal and vertical pointer movements
 * are translated into horizontal and vertical scroll movements.
 */
void spleeb_set_pointer_dragscroll_enabled(bool enable);
#endif // POINTING_DEVICE_ENABLE
