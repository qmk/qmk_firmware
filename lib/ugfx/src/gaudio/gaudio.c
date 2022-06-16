/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_GAUDIO

#if GAUDIO_NEED_PLAY
	#include "gaudio_driver_play.h"

	static gfxQueueASync	playList;
	static gSem				playComplete;
	static gU16				playFlags;
		#define PLAYFLG_USEEVENTS	0x0001
		#define PLAYFLG_PLAYING		0x0002
		#define PLAYFLG_ISINIT		0x0004
	#if GFX_USE_GEVENT
		static GTimer playTimer;
		static void PlayTimerCallback(void *param);
	#endif
#endif

#if GAUDIO_NEED_RECORD
	#include "gaudio_driver_record.h"

	static gfxQueueGSync	recordList;
	static gU16			recordFlags;
		#define RECORDFLG_USEEVENTS		0x0001
		#define RECORDFLG_RECORDING		0x0002
		#define RECORDFLG_STALLED		0x0004
		#define RECORDFLG_ISINIT		0x0008
	#if GFX_USE_GEVENT
		static GTimer recordTimer;
		static void RecordTimerCallback(void *param);
	#endif
#endif


void _gaudioInit(void)
{
	#if GAUDIO_NEED_PLAY
		gfxQueueASyncInit(&playList);
		#if GFX_USE_GEVENT
			gtimerInit(&playTimer);
		#endif
		gfxSemInit(&playComplete, 0, 0);
	#endif
	#if GAUDIO_NEED_RECORD
		gfxQueueGSyncInit(&recordList);
		#if GFX_USE_GEVENT
			gtimerInit(&recordTimer);
		#endif
	#endif
}

void _gaudioDeinit(void)
{
	#if GAUDIO_NEED_PLAY
		gfxQueueASyncDeinit(&playList);
		#if GFX_USE_GEVENT
			gtimerDeinit(&playTimer);
		#endif
		gfxSemDestroy(&playComplete);
	#endif
	#if GAUDIO_NEED_RECORD
		gfxQueueGSyncDeinit(&recordList);
		#if GFX_USE_GEVENT
			gtimerDeinit(&recordTimer);
		#endif
	#endif
}

#if GAUDIO_NEED_PLAY

	gBool gaudioPlayInit(gU16 channel, gU32 frequency, ArrayDataFormat format) {
		gaudioPlayStop();
		playFlags &= ~PLAYFLG_ISINIT;
		if (!gaudio_play_lld_init(channel, frequency, format))
			return gFalse;
		playFlags |= PLAYFLG_ISINIT;
		return gTrue;
	}

	void gaudioPlay(GDataBuffer *pd) {
		if (!(playFlags & PLAYFLG_ISINIT)) {
			// Oops - init failed - return it directly to the free-list
			if (pd) {
				gfxBufferRelease(pd);
				gfxYield();				// Make sure we get no endless cpu hogging loops
			}
			return;
		}

		if (pd)
			gfxQueueASyncPut(&playList, (gfxQueueASyncItem *)pd);
		playFlags |= PLAYFLG_PLAYING;
		gaudio_play_lld_start();
	}

	void gaudioPlayPause(void) {
		if ((playFlags & (PLAYFLG_ISINIT|PLAYFLG_PLAYING)) == (PLAYFLG_ISINIT|PLAYFLG_PLAYING))
			gaudio_play_lld_stop();
	}

	void gaudioPlayStop(void) {
		GDataBuffer	*pd;

		if (playFlags & PLAYFLG_PLAYING)
			gaudio_play_lld_stop();
		while((pd = (GDataBuffer *)gfxQueueASyncGet(&playList)))
			gfxBufferRelease(pd);
	}

	gBool gaudioPlaySetVolume(gU8 vol) {
		return gaudio_play_lld_set_volume(vol);
	}

	gBool gaudioPlayWait(gDelay ms) {
		if (!(playFlags & PLAYFLG_PLAYING))
			return gTrue;
		return gfxSemWait(&playComplete, ms);
	}

	#if GFX_USE_GEVENT
		static void PlayTimerCallback(void *param) {
			(void) param;
			GSourceListener	*psl;
			GEventAudioPlay	*pe;

			psl = 0;
			while ((psl = geventGetSourceListener((GSourceHandle)&playTimer, psl))) {
				if (!(pe = (GEventAudioPlay *)geventGetEventBuffer(psl))) {
					// This listener is missing - save this.
					psl->srcflags |= GAUDIO_PLAY_LOSTEVENT;
					continue;
				}

				pe->type = GEVENT_AUDIO_PLAY;
				pe->flags = psl->srcflags;
				psl->srcflags = 0;
				if ((playFlags & PLAYFLG_PLAYING))
					pe->flags |= GAUDIO_PLAY_PLAYING;
				if (gfxBufferIsAvailable())
					pe->flags |= GAUDIO_PLAY_FREEBLOCK;
				geventSendEvent(psl);
			}
		}

		GSourceHandle gaudioPlayGetSource(void) {
			if (!gtimerIsActive(&playTimer))
				gtimerStart(&playTimer, PlayTimerCallback, 0, gTrue, gDelayForever);
			playFlags |= PLAYFLG_USEEVENTS;
			return (GSourceHandle)&playTimer;
		}
	#endif

	/**
	 * Routines provided for use by drivers.
	 */

	GDataBuffer *gaudioPlayGetDataBlockI(void) {
		return (GDataBuffer *)gfxQueueASyncGetI(&playList);
	}

	void gaudioPlayReleaseDataBlockI(GDataBuffer *pd) {
		gfxBufferReleaseI(pd);
		#if GFX_USE_GEVENT
			if (playFlags & PLAYFLG_USEEVENTS)
				gtimerJabI(&playTimer);
		#endif
	}

	void gaudioPlayDoneI(void) {
		playFlags &= ~PLAYFLG_PLAYING;
		#if GFX_USE_GEVENT
			if (playFlags & PLAYFLG_USEEVENTS)
				gtimerJabI(&playTimer);
		#endif
		gfxSemSignalI(&playComplete);			// This should really be gfxSemSignalAllI(&playComplete);
	}
#endif

#if GAUDIO_NEED_RECORD
	gBool gaudioRecordInit(gU16 channel, gU32 frequency, ArrayDataFormat format) {
		gaudioRecordStop();
		recordFlags &= ~RECORDFLG_ISINIT;
		if (!gaudio_record_lld_init(channel, frequency, format))
			return gFalse;
		recordFlags |= RECORDFLG_ISINIT;
		return gTrue;
	}

	void gaudioRecordStart(void) {
		if (!(recordFlags & RECORDFLG_ISINIT))
			return;							// Oops - init failed

		recordFlags |= RECORDFLG_RECORDING;
		recordFlags &= ~RECORDFLG_STALLED;
		gaudio_record_lld_start();
	}

	void gaudioRecordStop(void) {
		GDataBuffer	*pd;

		if ((recordFlags & (RECORDFLG_RECORDING|RECORDFLG_STALLED)) == RECORDFLG_RECORDING)
			gaudio_record_lld_stop();
		recordFlags &= ~(RECORDFLG_RECORDING|RECORDFLG_STALLED);
		while((pd = (GDataBuffer *)gfxQueueGSyncGet(&recordList, gDelayNone)))
			gfxBufferRelease(pd);
	}

	GDataBuffer *gaudioRecordGetData(gDelay ms) {
		return (GDataBuffer *)gfxQueueGSyncGet(&recordList, ms);
	}

	#if GFX_USE_GEVENT
		static void RecordTimerCallback(void *param) {
			(void) param;
			GSourceListener		*psl;
			GEventAudioRecord	*pe;

			psl = 0;
			while ((psl = geventGetSourceListener((GSourceHandle)&recordTimer, psl))) {
				if (!(pe = (GEventAudioRecord *)geventGetEventBuffer(psl))) {
					// This listener is missing - save this.
					psl->srcflags |= GAUDIO_RECORD_LOSTEVENT;
					continue;
				}
				pe->type = GEVENT_AUDIO_RECORD;
				pe->flags = psl->srcflags;
				psl->srcflags = 0;
				if ((recordFlags & RECORDFLG_RECORDING))
					pe->flags |= GAUDIO_RECORD_RECORDING;
				if ((recordFlags & RECORDFLG_STALLED))
					pe->flags |= GAUDIO_RECORD_STALL;
				if (!gfxQueueGSyncIsEmpty(&recordList))
					pe->flags |= GAUDIO_RECORD_GOTBUFFER;
				geventSendEvent(psl);
			}
		}

		GSourceHandle gaudioRecordGetSource(void) {
			if (!gtimerIsActive(&recordTimer))
				gtimerStart(&recordTimer, RecordTimerCallback, 0, gTrue, gDelayForever);
			recordFlags |= RECORDFLG_USEEVENTS;
			return (GSourceHandle)&recordTimer;
		}
	#endif

	/**
	 * Routines provided for use by drivers.
	 */

	void gaudioRecordSaveDataBlockI(GDataBuffer *paud) {
		gfxQueueGSyncPutI(&recordList, (gfxQueueGSyncItem *)paud);
		#if GFX_USE_GEVENT
			if (recordFlags & RECORDFLG_USEEVENTS)
				gtimerJabI(&recordTimer);
		#endif
	}

	void gaudioRecordDoneI(void) {
		recordFlags |= RECORDFLG_STALLED;
		#if GFX_USE_GEVENT
			if (recordFlags & RECORDFLG_USEEVENTS)
				gtimerJabI(&recordTimer);
		#endif
	}
#endif

#endif /* GFX_USE_GAUDIO */
