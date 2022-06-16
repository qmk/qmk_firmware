/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/ginput/ginput_dial.c
 * @brief   GINPUT dial code.
 *
 * @defgroup Dial Dial
 * @ingroup GINPUT
 * @{
 */
#include "../../gfx.h"

#if GFX_USE_GINPUT && GINPUT_NEED_DIAL

#include "ginput_driver_dial.h"

static GTIMER_DECL(DialTimer);
static struct DialStatus_t {
	gU16	sensitivity;
	gU16	lastvalue;
	gU16	max;
} DialStatus[GINPUT_DIAL_NUM_PORTS];

// The reading callback function
static void DialCallback(gU16 instance, gU16 rawvalue) {
	struct DialStatus_t *pds;
	GSourceListener		*psl;
	GEventDial			*pe;

	/* Get the information we need */
	pds = DialStatus+instance;

	/* Range scale - if needed */
	if (pds->max != GINPUT_DIAL_MAX_VALUE)
		rawvalue = (gU16)((gU32)rawvalue * pds->max / GINPUT_DIAL_MAX_VALUE);

	/* Forget about changes below our sensitivity threshold */
	if (rawvalue >= pds->lastvalue) {
		if (rawvalue - pds->lastvalue < pds->sensitivity) return;
	} else {
		if (pds->lastvalue - rawvalue < pds->sensitivity) return;
	}

	/* Save the value */
	pds->lastvalue = rawvalue;

	// Send the event to the listeners that are interested.
	psl = 0;
	while ((psl = geventGetSourceListener((GSourceHandle)(DialStatus+instance), psl))) {
		if (!(pe = (GEventDial *)geventGetEventBuffer(psl)))
			continue;
		pe->type = GEVENT_DIAL;
		pe->instance = instance;
		pe->value = pds->lastvalue;
		pe->maxvalue = pds->max;
		geventSendEvent(psl);
	}
}

GSourceHandle ginputGetDial(gU16 instance) {
	struct DialStatus_t *pds;

	if (instance >= GINPUT_DIAL_NUM_PORTS)
		return 0;

	// Do we need to initialise the dial subsystem?
	if (!gtimerIsActive(&DialTimer)) {
		for(pds = DialStatus; pds < DialStatus+GINPUT_DIAL_NUM_PORTS; pds++) {
			pds->max = GINPUT_DIAL_MAX_VALUE;
#if GINPUT_DIAL_MAX_VALUE < 100
			pds->sensitivity = 1;
#else
			pds->sensitivity = GINPUT_DIAL_MAX_VALUE/100;
#endif
			pds->lastvalue = 0;
		}
		ginput_lld_dial_init();
		gtimerStart(&DialTimer, (GTimerFunction)ginput_lld_dial_poll, DialCallback, gTrue, GINPUT_DIAL_POLL_PERIOD);
	}

	// OK - return this input
	return (GSourceHandle)(DialStatus+instance);
}

void ginputResetDialRange(gU16 instance) {
	if (instance >= GINPUT_DIAL_NUM_PORTS)
		return;

	ginputSetDialRange(instance, GINPUT_DIAL_MAX_VALUE);
}

gU16 ginputGetDialRange(gU16 instance) {
	if (instance >= GINPUT_DIAL_NUM_PORTS)
		return 0;

	return DialStatus[instance].max;
}

void ginputSetDialRange(gU16 instance, gU16 max) {
	struct DialStatus_t *pds;

	if (instance >= GINPUT_DIAL_NUM_PORTS)
		return;

	pds = DialStatus+instance;

	// Rescale the last value and the sensitivity
	if (max != pds->max) {
		pds->lastvalue = (gU16)((gU32)pds->lastvalue * max / pds->max);
		pds->sensitivity = (gU16)((gU32)pds->sensitivity * max / pds->max);
		pds->max = max;
	}
}

/**
 * @brief	Set the level change required before a dial even is generated (threshold)
 * @note	This is done after range scaling
 *
 * @param[in] instance	The ID of the dial input instance
 * @param[in] diff		The amount of level changes
 */
void ginputSetDialSensitivity(gU16 instance, gU16 diff) {
	if (instance >= GINPUT_DIAL_NUM_PORTS)
		return;

	DialStatus[instance].sensitivity = diff;
}

/**
 * @brief	Get the current dial status
 *
 * @param[in] instance	The ID of the dial input instance
 * @param[in] pdial		The dial event struct
 *
 * @return	Returns gFalse on an error (eg invalid instance)
 */
gBool ginputGetDialStatus(gU16 instance, GEventDial *pdial) {
	if (instance >= GINPUT_DIAL_NUM_PORTS)
		return gFalse;
	pdial->type = GEVENT_DIAL;
	pdial->instance = instance;
	pdial->value = DialStatus[instance].lastvalue;
	pdial->maxvalue = DialStatus[instance].max;
	return gTrue;
}

#endif /* GFX_USE_GINPUT && GINPUT_NEED_DIAL */
/** @} */
