/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/ginput/ginput_toggle.h
 *
 * @defgroup Toggle Toggle
 * @ingroup GINPUT
 *
 * @brief   Sub-Module to handle physical controls that provide provide a digital value (on/off, pressed/released, 1/0, ...).
 *
 * @details	GINPUT allows it to interface toggle buttons easily to your
 *			application.
 *
 * @pre		GFX_USE_GINPUT must be set to GFXON in your gfxconf.h
 * @pre		GINPUT_NEED_TOGGLE must be set to GFXON in your gfxconf.h
 *
 * @{
 */

#ifndef _GINPUT_TOGGLE_H
#define _GINPUT_TOGGLE_H

#if GINPUT_NEED_TOGGLE || defined(__DOXYGEN__)

/*===========================================================================*/
/* Low Level Driver details and error checks.                                */
/*===========================================================================*/

// Get the hardware definitions - Number of instances etc.
#include "ginput_lld_toggle_config.h"

#ifndef GINPUT_TOGGLE_POLL_PERIOD
	#define GINPUT_TOGGLE_POLL_PERIOD 200
#endif

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

// Event types for various ginput sources
#define GEVENT_TOGGLE		(GEVENT_GINPUT_FIRST+3)

typedef struct GEventToggle_t {
	GEventType		type;				// The type of this event (GEVENT_TOGGLE)
	gU16		instance;			// The toggle instance
	gBool			on;					// True if the toggle/button is on
	} GEventToggle;

// Toggle Listen Flags - passed to geventAddSourceToListener()
#define GLISTEN_TOGGLE_ON		0x0001			// Return an event when the toggle turns on
#define GLISTEN_TOGGLE_OFF		0x0002			// Return an event when the toggle turns off

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/**
 * @brief	Create a toggle input instance
 *
 * @param[in] instance	The ID of the toggle input instance (from 0 to 9999)
 *
 * @return	The source handle of the created instance
 */
GSourceHandle ginputGetToggle(gU16 instance);	

/** 
 * @brief	Can be used to invert the sense of a toggle
 *
 * @param[in] instance	The ID of the toggle input instance
 * @param[in] invert	If gTrue, will be inverted
 */
void ginputInvertToggle(gU16 instance, gBool invert);

/**
 * @brief	Get the current toggle status
 *
 * @param[in] instance	The ID of the toggle input instance
 * @param[in] ptoggle	The toggle event struct
 *
 * @return Returns gFalse on an error (eg invalid instance)
 */
gBool ginputGetToggleStatus(gU16 instance, GEventToggle *ptoggle);

#endif /* GINPUT_NEED_TOGGLE */

#endif /* _GINPUT_TOGGLE_H */
/** @} */

