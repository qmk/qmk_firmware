/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gadc/gadc_driver.h
 * @brief   GADC - Periodic ADC driver header file.
 *
 * @defgroup GADC_Driver Driver
 * @ingroup GADC
 *
 * @brief Driver interface for the GADC module.
 *
 * @{
 */

#ifndef _GADC_LLD_H
#define _GADC_LLD_H

#include "../../gfx.h"

#if GFX_USE_GADC || defined(__DOXYGEN__)

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

/**
 * @brief				The structure passed to start a timer conversion
 * @{
 */
typedef struct GadcTimerJob_t {
	gU32		physdev;					// @< The physical device/s. The exact meaning of physdev is hardware dependent.
	gU32		frequency;					// @< The frequency to sample
	adcsample_t		*buffer;					// @< Where to put the samples
	gMemSize		todo;						// @< How many conversions to do
	gMemSize		done;						// @< How many conversions have already been done
} GadcTimerJob;
/** @} */

/**
 * @brief				The structure passed to do a single conversion
 * @{
 */
typedef struct GadcNonTimerJob_t {
	gU32				physdev;			// @< The physical device/s. The exact meaning of physdev is hardware dependent.
	adcsample_t				*buffer;			// @< Where to put the samples.
	} GadcNonTimerJob;
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief				These routines are the callbacks that the driver uses.
 * @details				Defined in the high level GADC code.
 *
 * @notapi
 * @{
 */
	/**
	 * @brief	Indicate that some data has been placed into the buffer for the current job
	 *
	 * @param[in] n		The number of samples placed in the buffer
	 *
	 * @note		Calling this with n = 0 causes the current job to be terminated early or aborted.
	 * 				It can be called in this mode on an ADC conversion error. Any job will then be
	 * 				restarted by the high level code as appropriate.
	 */
	void gadcGotDataI(gMemSize n);
/**
 * @}
 */

/**
 * @brief				Initialise the driver
 *
 * @api
 */
void gadc_lld_init(void);

/**
 * @brief				Using the hardware dependant "physdev", return the number of samples for each conversion
 *
 * @param[in] physdev	The hardware dependent physical device descriptor
 *
 * @return				The number of samples per conversion
 *
 * @api
 */
gMemSize gadc_lld_samplesperconversion(gU32 physdev);

/**
 * @brief				Start a periodic timer for high frequency conversions.
 *
 * @param[in] freq		The frequency for the timer
 *
 * @note				This will only be called if the timer is currently stopped.
 *
 * @api
 * @iclass
 */
void gadc_lld_start_timerI(gU32 freq);

/**
 * @brief				Stop the periodic timer for high frequency conversions.
 *
 * @note				This will only be called if the timer is currently running and all timer jobs
 * 						have been completed/aborted.
 *
 * @api
 * @iclass
 */
void gadc_lld_stop_timerI(void);

/**
 * @brief				Start a set of high frequency conversions.
 *
 * @note				This will only be called if the timer is currently running and the ADC should be ready for
 * 						a new job.
 *
 * @param[in] pjob		The job to be started.
 *
 * @api
 * @iclass
 */
void gadc_lld_timerjobI(GadcTimerJob *pjob);

/**
 * @brief				Start a non-timer conversion.
 *
 * @note				This will only be called if the ADC should be ready for a new job.
 *
 * @param[in] pjob		The job to be started
 *
 * @api
 * @iclass
 */
void gadc_lld_nontimerjobI(GadcNonTimerJob *pjob);

#ifdef __cplusplus
}
#endif

#endif /* GFX_USE_GADC */

#endif /* _GADC_LLD_H */
/** @} */
