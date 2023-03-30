/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_INTERP_H
#define _HARDWARE_INTERP_H

#include "pico.h"
#include "hardware/structs/interp.h"
#include "hardware/regs/sio.h"

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_INTERP, Enable/disable assertions in the interpolation module, type=bool, default=0, group=hardware_interp
#ifndef PARAM_ASSERTIONS_ENABLED_INTERP
#define PARAM_ASSERTIONS_ENABLED_INTERP 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** \file hardware/interp.h
 *  \defgroup hardware_interp hardware_interp
 *
 * Hardware Interpolator API
 *
 * Each core is equipped with two interpolators (INTERP0 and INTERP1) which can be used to accelerate
 * tasks by combining certain pre-configured simple operations into a single processor cycle. Intended
 * for cases where the pre-configured operation is repeated a large number of times, this results in
 * code which uses both fewer CPU cycles and fewer CPU registers in the time critical sections of the
 * code.
 *
 * The interpolators are used heavily to accelerate audio operations within the SDK, but their
 * flexible configuration make it possible to optimise many other tasks such as quantization and
 * dithering, table lookup address generation, affine texture mapping, decompression and linear feedback.
 *
 * Please refer to the RP2040 datasheet for more information on the HW interpolators and how they work.
 */

#define interp0 interp0_hw
#define interp1 interp1_hw

/** \brief Interpolator configuration
 *  \defgroup interp_config interp_config
 *  \ingroup hardware_interp
 *
 * Each interpolator needs to be configured, these functions provide handy helpers to set up configuration
 * structures.
 *
 */

typedef struct {
    uint32_t ctrl;
} interp_config;

static inline uint interp_index(interp_hw_t *interp) {
    valid_params_if(INTERP, interp == interp0 || interp == interp1);
    return interp == interp1 ? 1 : 0;
}

/*! \brief Claim the interpolator lane specified
 *  \ingroup hardware_interp
 *
 * Use this function to claim exclusive access to the specified interpolator lane.
 *
 * This function will panic if the lane is already claimed.
 *
 * \param interp Interpolator on which to claim a lane. interp0 or interp1
 * \param lane The lane number, 0 or 1.
 */
void interp_claim_lane(interp_hw_t *interp, uint lane);
// The above really should be called this for consistency
#define interp_lane_claim interp_claim_lane

/*! \brief Claim the interpolator lanes specified in the mask
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator on which to claim lanes. interp0 or interp1
 * \param lane_mask Bit pattern of lanes to claim (only bits 0 and 1 are valid)
 */
void interp_claim_lane_mask(interp_hw_t *interp, uint lane_mask);

/*! \brief Release a previously claimed interpolator lane
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator on which to release a lane. interp0 or interp1
 * \param lane The lane number, 0 or 1
 */
void interp_unclaim_lane(interp_hw_t *interp, uint lane);
// The above really should be called this for consistency
#define interp_lane_unclaim interp_unclaim_lane

/*! \brief Determine if an interpolator lane is claimed
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator whose lane to check
 * \param lane The lane number, 0 or 1
 * \return true if claimed, false otherwise
 * \see interp_claim_lane
 * \see interp_claim_lane_mask
 */
bool interp_lane_is_claimed(interp_hw_t *interp, uint lane);

/*! \brief Release previously claimed interpolator lanes \see interp_claim_lane_mask
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator on which to release lanes. interp0 or interp1
 * \param lane_mask Bit pattern of lanes to unclaim (only bits 0 and 1 are valid)
 */
void interp_unclaim_lane_mask(interp_hw_t *interp, uint lane_mask);

/*! \brief Set the interpolator shift value
 *  \ingroup interp_config
 *
 * Sets the number of bits the accumulator is shifted before masking, on each iteration.
 *
 * \param c Pointer to an interpolator config
 * \param shift Number of bits
 */
static inline void interp_config_set_shift(interp_config *c, uint shift) {
    valid_params_if(INTERP, shift < 32);
    c->ctrl = (c->ctrl & ~SIO_INTERP0_CTRL_LANE0_SHIFT_BITS) |
              ((shift << SIO_INTERP0_CTRL_LANE0_SHIFT_LSB) & SIO_INTERP0_CTRL_LANE0_SHIFT_BITS);
}

/*! \brief Set the interpolator mask range
 *  \ingroup interp_config
 *
 * Sets the range of bits (least to most) that are allowed to pass through the interpolator
 *
 * \param c Pointer to interpolation config
 * \param mask_lsb The least significant bit allowed to pass
 * \param mask_msb The most significant bit allowed to pass
 */
static inline void interp_config_set_mask(interp_config *c, uint mask_lsb, uint mask_msb) {
    valid_params_if(INTERP, mask_msb < 32);
    valid_params_if(INTERP, mask_lsb <= mask_msb);
    c->ctrl = (c->ctrl & ~(SIO_INTERP0_CTRL_LANE0_MASK_LSB_BITS | SIO_INTERP0_CTRL_LANE0_MASK_MSB_BITS)) |
              ((mask_lsb << SIO_INTERP0_CTRL_LANE0_MASK_LSB_LSB) & SIO_INTERP0_CTRL_LANE0_MASK_LSB_BITS) |
              ((mask_msb << SIO_INTERP0_CTRL_LANE0_MASK_MSB_LSB) & SIO_INTERP0_CTRL_LANE0_MASK_MSB_BITS);
}

/*! \brief Enable cross input
 *  \ingroup interp_config
 *
 *  Allows feeding of the accumulator content from the other lane back in to this lanes shift+mask hardware.
 *  This will take effect even if the interp_config_set_add_raw option is set as the cross input mux is before the
 *  shift+mask bypass
 *
 * \param c Pointer to interpolation config
 * \param cross_input If true, enable the cross input.
 */
static inline void interp_config_set_cross_input(interp_config *c, bool cross_input) {
    c->ctrl = (c->ctrl & ~SIO_INTERP0_CTRL_LANE0_CROSS_INPUT_BITS) |
              (cross_input ? SIO_INTERP0_CTRL_LANE0_CROSS_INPUT_BITS : 0);
}

/*! \brief Enable cross results
 *  \ingroup interp_config
 *
 *  Allows feeding of the other lane’s result into this lane’s accumulator on a POP operation.
 *
 * \param c Pointer to interpolation config
 * \param cross_result If true, enables the cross result
 */
static inline void interp_config_set_cross_result(interp_config *c, bool cross_result) {
    c->ctrl = (c->ctrl & ~SIO_INTERP0_CTRL_LANE0_CROSS_RESULT_BITS) |
              (cross_result ? SIO_INTERP0_CTRL_LANE0_CROSS_RESULT_BITS : 0);
}

/*! \brief Set sign extension
 *  \ingroup interp_config
 *
 * Enables signed mode, where the shifted and masked accumulator value is sign-extended to 32 bits
 * before adding to BASE1, and LANE1 PEEK/POP results appear extended to 32 bits when read by processor.
 *
 * \param c Pointer to interpolation config
 * \param  _signed If true, enables sign extension
 */
static inline void interp_config_set_signed(interp_config *c, bool _signed) {
    c->ctrl = (c->ctrl & ~SIO_INTERP0_CTRL_LANE0_SIGNED_BITS) |
              (_signed ? SIO_INTERP0_CTRL_LANE0_SIGNED_BITS : 0);
}

/*! \brief Set raw add option
 *  \ingroup interp_config
 *
 * When enabled, mask + shift is bypassed for LANE0 result. This does not affect the FULL result.
 *
 * \param c Pointer to interpolation config
 * \param add_raw If true, enable raw add option.
 */
static inline void interp_config_set_add_raw(interp_config *c, bool add_raw) {
    c->ctrl = (c->ctrl & ~SIO_INTERP0_CTRL_LANE0_ADD_RAW_BITS) |
              (add_raw ? SIO_INTERP0_CTRL_LANE0_ADD_RAW_BITS : 0);
}

/*! \brief Set blend mode
 *  \ingroup interp_config
 *
 * If enabled, LANE1 result is a linear interpolation between BASE0 and BASE1, controlled
 * by the 8 LSBs of lane 1 shift and mask value (a fractional number between 0 and 255/256ths)
 *
 * LANE0 result does not have BASE0 added (yields only the 8 LSBs of lane 1 shift+mask value)
 *
 * FULL result does not have lane 1 shift+mask value added (BASE2 + lane 0 shift+mask)
 *
 * LANE1 SIGNED flag controls whether the interpolation is signed or unsig
 *
 * \param c Pointer to interpolation config
 * \param blend Set true to enable blend mode.
*/
static inline void interp_config_set_blend(interp_config *c, bool blend) {
    c->ctrl = (c->ctrl & ~SIO_INTERP0_CTRL_LANE0_BLEND_BITS) |
              (blend ? SIO_INTERP0_CTRL_LANE0_BLEND_BITS : 0);
}

/*! \brief Set interpolator clamp mode (Interpolator 1 only)
 *  \ingroup interp_config
 *
 * Only present on INTERP1 on each core. If CLAMP mode is enabled:
 * - LANE0 result is a shifted and masked ACCUM0, clamped by a lower bound of BASE0 and an upper bound of BASE1.
 * - Signedness of these comparisons is determined by LANE0_CTRL_SIGNED
 *
 * \param c Pointer to interpolation config
 * \param clamp Set true to enable clamp mode
 */
static inline void interp_config_set_clamp(interp_config *c, bool clamp) {
    c->ctrl = (c->ctrl & ~SIO_INTERP1_CTRL_LANE0_CLAMP_BITS) |
              (clamp ? SIO_INTERP1_CTRL_LANE0_CLAMP_BITS : 0);
}

/*! \brief Set interpolator Force bits
 *  \ingroup interp_config
 *
 * ORed into bits 29:28 of the lane result presented to the processor on the bus.
 *
 * No effect on the internal 32-bit datapath. Handy for using a lane to generate sequence
 * of pointers into flash or SRAM
 *
 * \param c Pointer to interpolation config
 * \param bits Sets the force bits to that specified. Range 0-3 (two bits)
 */
static inline void interp_config_set_force_bits(interp_config *c, uint bits) {
    invalid_params_if(INTERP, bits > 3);
    // note cannot use hw_set_bits on SIO
    c->ctrl = (c->ctrl & ~SIO_INTERP0_CTRL_LANE0_FORCE_MSB_BITS) |
              (bits << SIO_INTERP0_CTRL_LANE0_FORCE_MSB_LSB);
}

/*! \brief Get a default configuration
 *  \ingroup interp_config
 *
 * \return A default interpolation configuration
 */
static inline interp_config interp_default_config(void) {
    interp_config c = {0};
    // Just pass through everything
    interp_config_set_mask(&c, 0, 31);
    return c;
}

/*! \brief Send configuration to a lane
 *  \ingroup interp_config
 *
 * If an invalid configuration is specified (ie a lane specific item is set on wrong lane),
 * depending on setup this function can panic.
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane to set
 * \param config Pointer to interpolation config
 */

static inline void interp_set_config(interp_hw_t *interp, uint lane, interp_config *config) {
    invalid_params_if(INTERP, lane > 1);
    invalid_params_if(INTERP, config->ctrl & SIO_INTERP1_CTRL_LANE0_CLAMP_BITS &&
                              (!interp_index(interp) || lane)); // only interp1 lane 0 has clamp bit
    invalid_params_if(INTERP, config->ctrl & SIO_INTERP0_CTRL_LANE0_BLEND_BITS &&
                              (interp_index(interp) || lane)); // only interp0 lane 0 has blend bit
    interp->ctrl[lane] = config->ctrl;
}

/*! \brief Directly set the force bits on a specified lane
 *  \ingroup hardware_interp
 *
 * These bits are ORed into bits 29:28 of the lane result presented to the processor on the bus.
 * There is no effect on the internal 32-bit datapath.
 *
 * Useful for using a lane to generate sequence of pointers into flash or SRAM, saving a subsequent
 * OR or add operation.
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane to set
 * \param bits The bits to set (bits 0 and 1, value range 0-3)
 */
static inline void interp_set_force_bits(interp_hw_t *interp, uint lane, uint bits) {
    // note cannot use hw_set_bits on SIO
    interp->ctrl[lane] = interp->ctrl[lane] | (bits << SIO_INTERP0_CTRL_LANE0_FORCE_MSB_LSB);
}

typedef struct {
    uint32_t accum[2];
    uint32_t base[3];
    uint32_t ctrl[2];
} interp_hw_save_t;

/*! \brief Save the specified interpolator state
 *  \ingroup hardware_interp
 *
 * Can be used to save state if you need an interpolator for another purpose, state
 * can then be recovered afterwards and continue from that point
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param saver Pointer to the save structure to fill in
 */
void interp_save(interp_hw_t *interp, interp_hw_save_t *saver);

/*! \brief Restore an interpolator state
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param saver Pointer to save structure to reapply to the specified interpolator
 */
void interp_restore(interp_hw_t *interp, interp_hw_save_t *saver);

/*! \brief Sets the interpolator base register by lane
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane number, 0 or 1 or 2
 * \param val The value to apply to the register
 */
static inline void interp_set_base(interp_hw_t *interp, uint lane, uint32_t val) {
    interp->base[lane] = val;
}

/*! \brief Gets the content of interpolator base register by lane
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane number, 0 or 1 or 2
 * \return  The current content of the lane base register
 */
static inline uint32_t interp_get_base(interp_hw_t *interp, uint lane) {
    return interp->base[lane];
}

/*! \brief Sets the interpolator base registers simultaneously
 *  \ingroup hardware_interp
 *
 *  The lower 16 bits go to BASE0, upper bits to BASE1 simultaneously.
 *  Each half is sign-extended to 32 bits if that lane’s SIGNED flag is set.
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param val The value to apply to the register
 */
static inline void interp_set_base_both(interp_hw_t *interp, uint32_t val) {
    interp->base01 = val;
}


/*! \brief Sets the interpolator accumulator register by lane
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane number, 0 or 1
 * \param val The value to apply to the register
 */
static inline void interp_set_accumulator(interp_hw_t *interp, uint lane, uint32_t val) {
    interp->accum[lane] = val;
}

/*! \brief Gets the content of the interpolator accumulator register by lane
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane number, 0 or 1
 * \return The current content of the register
 */
static inline uint32_t interp_get_accumulator(interp_hw_t *interp, uint lane) {
    return interp->accum[lane];
}

/*! \brief Read lane result, and write lane results to both accumulators to update the interpolator
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane number, 0 or 1
 * \return The content of the lane result register
 */
static inline uint32_t interp_pop_lane_result(interp_hw_t *interp, uint lane) {
    return interp->pop[lane];
}

/*! \brief Read lane result
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane number, 0 or 1
 * \return The content of the lane result register
 */
static inline uint32_t interp_peek_lane_result(interp_hw_t *interp, uint lane) {
    return interp->peek[lane];
}

/*! \brief Read lane result, and write lane results to both accumulators to update the interpolator
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \return The content of the FULL register
 */
static inline uint32_t interp_pop_full_result(interp_hw_t *interp) {
    return interp->pop[2];
}

/*! \brief Read lane result
 *  \ingroup hardware_interp
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \return The content of the FULL register
 */
static inline uint32_t interp_peek_full_result(interp_hw_t *interp) {
    return interp->peek[2];
}

/*! \brief Add to accumulator
 *  \ingroup hardware_interp
 *
 * Atomically add the specified value to the accumulator on the specified lane
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane number, 0 or 1
 * \param val Value to add
 * \return The content of the FULL register
 */
static inline void interp_add_accumulater(interp_hw_t *interp, uint lane, uint32_t val) {
    interp->add_raw[lane] = val;
}

/*! \brief Get raw lane value
 *  \ingroup hardware_interp
 *
 * Returns the raw shift and mask value from the specified lane, BASE0 is NOT added
 *
 * \param interp Interpolator instance, interp0 or interp1.
 * \param lane The lane number, 0 or 1
 * \return The raw shift/mask value
 */
static inline uint32_t interp_get_raw(interp_hw_t *interp, uint lane) {
    return interp->add_raw[lane];
}

#ifdef __cplusplus
}
#endif

#endif
