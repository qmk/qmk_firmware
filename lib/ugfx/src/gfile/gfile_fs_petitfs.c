/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/********************************************************
 * The PETITFS file-system
 ********************************************************/

#include "../../gfx.h"

#if GFX_USE_GFILE && GFILE_NEED_PETITFS

#include "gfile_fs.h"
#include "gfile_petitfs_wrapper.h"

static gBool petitfsExists(const char* fname);
static gBool petitfsOpen(GFILE* f, const char* fname);
static int petitfsRead(GFILE* f, void* buf, int size);
static gBool petitfsSetPos(GFILE* f, gFileSize pos);
#if GFILE_NEED_FILELISTS && _FS_MINIMIZE <= 1
	static gfileList *petitfsFlOpen(const char *path, gBool dirs);
	static const char *petitfsFlRead(gfileList *pfl);
	static void petitfsFlClose(gfileList *pfl);
#endif

const GFILEVMT FsPetitFSVMT = {
	GFSFLG_WRITEABLE | GFSFLG_SEEKABLE,
	'F',
	0,
	petitfsExists,
	0,					// No Filesize
	0,
	petitfsOpen,
	0,					// No Close
	petitfsRead,
	0,					// No Write
	petitfsSetPos,
	0,					// No Getsize
	0,					// No EOF
	0, 0, 0,			// No Mount, UnMount or Sync
	#if GFILE_NEED_FILELISTS
		#if _USE_DIR
			petitfsFlOpen, petitfsFlRead, petitfsFlClose
		#else
			0, 0, 0
		#endif
	#endif
};

// Our directory list structure
typedef struct petitfsList {
	gfileList	fl;					// This must be the first element.
	DIR			dir;
	FILINFO		fno;
} petitfsList;

// optimize these later on. Use an array to have multiple
static gBool petitfs_mounted = gFalse;
static FATFS petitfs_fs;

static gBool petitfsExists(const char* fname)
{
	// Mount first
	if (!petitfs_mounted && pf_mount(&petitfs_fs) != FR_OK)
		return gFalse;

	// Open
	if (pf_open(fname) != FR_OK)
		return gFalse;

	return gTrue;
}

static gBool petitfsOpen(GFILE* f, const char* fname)
{
	// No writing
	if ((f->flags & GFILEFLG_WRITE))
		return gFalse;

	// Mount first
	if (!petitfs_mounted && pf_mount(&petitfs_fs) != FR_OK)
		return gFalse;

	// Open
	if (pf_open(fname) != FR_OK)
		return gFalse;

	f->obj = &petitfs_fs;
	return gTrue;	
}

static int petitfsRead(GFILE* f, void* buf, int size)
{
	int		br;
	(void)	f;

	if (pf_read(buf, size, (UINT*)&br) != FR_OK)
		return 0;

	return br;
}

static gBool petitfsSetPos(GFILE* f, gFileSize pos)
{
	(void)	f;
	return pf_lseek((DWORD)pos) == FR_OK;
}

#if GFILE_NEED_FILELISTS
	static gfileList *petitfsFlOpen(const char *path, gBool dirs) {
		petitfsList	*p;
		(void) dirs;

		if (!(p = gfxAlloc(sizeof(petitfsList))))
			return 0;

		if (pf_opendir(&p->dir, path) != FR_OK) {
			gfxFree(p);
			return 0;
		}
		return &p->fl;
	}

	static const char *petitfsFlRead(gfileList *pfl) {
		#define ffl		((petitfsList *)pfl)

		while(1) {
			// Read the next entry
			if (pf_readdir(&ffl->dir, &ffl->fno) != FR_OK || !ffl->fno.fname[0])
				return 0;

			/* Ignore dot entries */
			if (ffl->fno.fname[0] == '.') continue;

			/* Is it a directory */
			if (ffl->fl.dirs) {
				if ((ffl->fno.fattrib & AM_DIR))
					break;
			} else {
				if (!(ffl->fno.fattrib & (AM_DIR|AM_HID|AM_SYS)))
					break;
			}
		}

		return ffl->fno.fname;
	}

	static void petitfsFlClose(gfileList *pfl) {
		gfxFree(pfl);
	}

#endif

#endif //GFX_USE_GFILE && GFILE_NEED_PETITFS
