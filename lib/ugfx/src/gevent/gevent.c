/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_GEVENT || defined(__DOXYGEN__)

#if GEVENT_ASSERT_NO_RESOURCE
	#define GEVENT_ASSERT(x)		assert(x)
#else
	#define GEVENT_ASSERT(x)
#endif

/* Flags in the listener structure */
#define GLISTENER_WITHLISTENER		0x0001			// The listener is current using the buffer
#define GLISTENER_WITHSOURCE		0x0002			// The source is currently using the buffer

/* This mutex protects access to our tables */
static gMutex	geventMutex;

/* Our table of listener/source pairs */
static GSourceListener		Assignments[GEVENT_MAX_SOURCE_LISTENERS];

/* Send an exit event if possible. */
/* We already have the geventMutex */
static void doExitEvent(GListener *pl) {
	// Don't do the exit if someone else currently is using the buffer
	if (!(pl->flags & GLISTENER_WITHLISTENER)) {
		pl->event.type = GEVENT_EXIT;								// Set up the EXIT event
		pl->flags = GLISTENER_WITHLISTENER;							// Event buffer is now in use by the listener
		gfxSemSignal(&pl->waitqueue);
	}
}

/* Loop through the assignment table deleting this listener/source pair. */
/*	Null is treated as a wildcard. */
/* We already have the geventMutex */
static void deleteAssignments(GListener *pl, GSourceHandle gsh) {
	GSourceListener *psl;

	for(psl = Assignments; psl < Assignments+GEVENT_MAX_SOURCE_LISTENERS; psl++) {
		if ((!pl || psl->pListener == pl) && (!gsh || psl->pSource == gsh)) {
			doExitEvent(psl->pListener);
			psl->pListener = 0;
			psl->pSource = 0;
		}
	}
}

void _geventInit(void)
{
	gfxMutexInit(&geventMutex);
}

void _geventDeinit(void)
{
	gfxMutexDestroy(&geventMutex);	
}

void geventListenerInit(GListener *pl) {
	gfxSemInit(&pl->waitqueue, 0, gSemMaxCount);		// Next wait'er will block
	pl->callback = 0;									// No callback active
	pl->event.type = GEVENT_NULL;						// Always safety
	pl->flags = 0;
}

gBool geventAttachSource(GListener *pl, GSourceHandle gsh, gU32 flags) {
	GSourceListener *psl, *pslfree;

	// Safety first
	if (!pl || !gsh) {
		GEVENT_ASSERT(gFalse);
		return gFalse;
	}

	gfxMutexEnter(&geventMutex);

	// Check if this pair is already in the table (scan for a free slot at the same time)
	pslfree = 0;
	for(psl = Assignments; psl < Assignments+GEVENT_MAX_SOURCE_LISTENERS; psl++) {
		
		if (pl == psl->pListener && gsh == psl->pSource) {
			// Just update the flags
			psl->listenflags = flags;
			gfxMutexExit(&geventMutex);
			return gTrue;
		}
		if (!pslfree && !psl->pListener)
			pslfree = psl;
	}
	
	// A free slot was found - allocate it
	if (pslfree) {
		pslfree->pListener = pl;
		pslfree->pSource = gsh;
		pslfree->listenflags = flags;
		pslfree->srcflags = 0;
	}
	gfxMutexExit(&geventMutex);
	GEVENT_ASSERT(pslfree != 0);
	return pslfree != 0;
}

void geventDetachSource(GListener *pl, GSourceHandle gsh) {
	if (pl) {
		gfxMutexEnter(&geventMutex);
		deleteAssignments(pl, gsh);
		if (!gsh)
			doExitEvent(pl);
		gfxMutexExit(&geventMutex);
	}
}

GEvent *geventEventWait(GListener *pl, gDelay timeout) {
	/* NOTE:
		We no longer try to protect against two threads trying to listen on the
		one listener. This was never allowed, it makes little sense to try to do so,
		and the testing caused strange multi-thread windows of opportunity.
		
		In practice it is probably safer than it used to be - the only potential
		issue is that the buffer may be prematurely marked as not in use by the listener.
		If the calling code can guarantee that the event buffer is free when either thread
		calls the event wait - it is now safe for them to do so.
		ie. it is the implicit geventEventComplete() that is the only thing that now raises
		possible multi-thread issues.
	*/

	// Don't allow waiting if we are on callbacks
	if (pl->callback)
		return 0;
		
	// Event buffer is not in use by the listener - this is an implicit geventEventComplete() call
	pl->flags &= ~GLISTENER_WITHLISTENER;

	// Wait for an event
	if (!gfxSemWait(&pl->waitqueue, timeout))
		return 0;				// Timeout

	return &pl->event;
}

void geventEventComplete(GListener *pl) {
	// The listener is done with the buffer
	pl->flags &= ~GLISTENER_WITHLISTENER;
}

void geventRegisterCallback(GListener *pl, GEventCallbackFn fn, void *param) {
	if (pl) {
		gfxMutexEnter(&geventMutex);
		doExitEvent(pl);
		pl->param = param;						// Set the param
		pl->callback = fn;						// Set the callback function
		if (fn)
			pl->flags &= ~GLISTENER_WITHLISTENER;	// The event buffer is immediately available
		gfxMutexExit(&geventMutex);
	}
}

GSourceListener *geventGetSourceListener(GSourceHandle gsh, GSourceListener *lastlr) {
	GSourceListener *psl;

	// Safety first
	if (!gsh)
		return 0;

	gfxMutexEnter(&geventMutex);

	// Unlock the last listener event buffer if it wasn't used.
	if (lastlr && lastlr->pListener && (lastlr->pListener->flags & GLISTENER_WITHSOURCE))
		lastlr->pListener->flags &= ~GLISTENER_WITHSOURCE;
		
	// Loop through the table looking for attachments to this source
	for(psl = lastlr ? (lastlr+1) : Assignments; psl < Assignments+GEVENT_MAX_SOURCE_LISTENERS; psl++) {
		if (gsh == psl->pSource) {
			gfxMutexExit(&geventMutex);
			return psl;
		}
	}
	gfxMutexExit(&geventMutex);
	return 0;
}

GEvent *geventGetEventBuffer(GSourceListener *psl) {
	gfxMutexEnter(&geventMutex);
	if ((psl->pListener->flags & (GLISTENER_WITHLISTENER|GLISTENER_WITHSOURCE))) {
		gfxMutexExit(&geventMutex);
		return 0;
	}

	// Allocate the event buffer to the source
	psl->pListener->flags |= GLISTENER_WITHSOURCE;
	gfxMutexExit(&geventMutex);
	return &psl->pListener->event;
}

void geventSendEvent(GSourceListener *psl) {
	gfxMutexEnter(&geventMutex);
	if (psl->pListener->callback) {

		// Mark it back as free and as sent. This is early to be marking as free but it protects
		//	if the callback alters the listener in any way
		psl->pListener->flags = 0;
		gfxMutexExit(&geventMutex);

		// Do the callback
		psl->pListener->callback(psl->pListener->param, &psl->pListener->event);

	} else {
		// Wake up the listener
		psl->pListener->flags = GLISTENER_WITHLISTENER;
		gfxSemSignal(&psl->pListener->waitqueue);
		gfxMutexExit(&geventMutex);
	}
}

void geventDetachSourceListeners(GSourceHandle gsh) {
	gfxMutexEnter(&geventMutex);
	deleteAssignments(0, gsh);
	gfxMutexExit(&geventMutex);
}

#endif /* GFX_USE_GEVENT */
