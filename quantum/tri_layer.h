// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>

#ifndef TRI_LAYER_LOWER_LAYER
#    define TRI_LAYER_LOWER_LAYER 1
#endif
#ifndef TRI_LAYER_RAISE_LAYER
#    define TRI_LAYER_RAISE_LAYER 2
#endif
#ifndef TRI_LAYER_ADJUST_LAYER
#    define TRI_LAYER_ADJUST_LAYER 3
#endif

/**
 * @brief Set the tri layer lower layer layer value
 *
 * @param layer
 */
void set_tri_layer_lower_layer(uint8_t layer);
/**
 * @brief Set the tri layer raise layer layer value
 *
 * @param layer
 */
void set_tri_layer_raise_layer(uint8_t layer);
/**
 * @brief Set the tri layer adjust layer object
 *
 * @param layer
 */
void set_tri_layer_adjust_layer(uint8_t layer);
/**
 * @brief Set the tri layer layers object
 *
 * @param lower
 * @param raise
 * @param adjust
 */
void set_tri_layer_layers(uint8_t lower, uint8_t raise, uint8_t adjust);
/**
 * @brief Get the tri layer lower layer object
 *
 * @return uint8_t
 */
uint8_t get_tri_layer_lower_layer(void);
/**
 * @brief Get the tri layer raise layer object
 *
 * @return uint8_t
 */
uint8_t get_tri_layer_raise_layer(void);
/**
 * @brief Get the tri layer adjust layer object
 *
 * @return uint8_t
 */
uint8_t get_tri_layer_adjust_layer(void);
