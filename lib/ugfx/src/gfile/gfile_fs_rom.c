/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/********************************************************
 * The ROM file-system
 ********************************************************/

#include "../../gfx.h"

#if GFX_USE_GFILE && GFILE_NEED_ROMFS

#include "gfile_fs.h"

#include <string.h>

// What directory file formats do we understand
#define ROMFS_DIR_VER_MAX			0x0000

// Compression Formats
#define ROMFS_CMP_UNCOMPRESSED		0

typedef struct ROMFS_DIRENTRY {
	gU16						ver;			// Directory Entry Version
	gU16						cmp;			// Compression format
	const struct ROMFS_DIRENTRY *	next;			// The next entry
	const char *					name;			// The file name
	gFileSize						size;			// The file size
	const char *					file;			// The file data
} ROMFS_DIRENTRY;

#define ROMFS_DIRENTRY_HEAD		0
#include "romfs_files.h"
static const ROMFS_DIRENTRY const *FsROMHead = ROMFS_DIRENTRY_HEAD;

typedef struct ROMFileList {
	gfileList				fl;
	const ROMFS_DIRENTRY	*pdir;
} ROMFileList;


static gBool ROMExists(const char *fname);
static gFileSize	ROMFilesize(const char *fname);
static gBool ROMOpen(GFILE *f, const char *fname);
static void ROMClose(GFILE *f);
static int ROMRead(GFILE *f, void *buf, int size);
static gBool ROMSetpos(GFILE *f, gFileSize pos);
static gFileSize ROMGetsize(GFILE *f);
static gBool ROMEof(GFILE *f);
#if GFILE_NEED_FILELISTS
	static gfileList *ROMFlOpen(const char *path, gBool dirs);
	static const char *ROMFlRead(gfileList *pfl);
	static void ROMFlClose(gfileList *pfl);
#endif

const GFILEVMT FsROMVMT = {
	GFSFLG_CASESENSITIVE|GFSFLG_SEEKABLE|GFSFLG_FAST,	// flags
	'S',												// prefix
	0, ROMExists, ROMFilesize, 0,
	ROMOpen, ROMClose, ROMRead, 0,
	ROMSetpos, ROMGetsize, ROMEof,
	0, 0, 0,
	#if GFILE_NEED_FILELISTS
		ROMFlOpen, ROMFlRead, ROMFlClose
	#endif
};

static const ROMFS_DIRENTRY *ROMFindFile(const char *fname)
{
	const ROMFS_DIRENTRY *p;

	for(p = FsROMHead; p; p = p->next) {
		if (p->ver <= ROMFS_DIR_VER_MAX && p->cmp == ROMFS_CMP_UNCOMPRESSED && !strcmp(p->name, fname))
			break;
	}
	return p;
}

static gBool ROMExists(const char *fname)
{
	return ROMFindFile(fname) != 0;
}

static gFileSize	ROMFilesize(const char *fname)
{
	const ROMFS_DIRENTRY *p;

	if (!(p = ROMFindFile(fname))) return (gFileSize)-1;
	return p->size;
}

static gBool ROMOpen(GFILE *f, const char *fname)
{
	const ROMFS_DIRENTRY *p;

	if (!(p = ROMFindFile(fname))) return gFalse;
	f->obj = (void *)p;
	return gTrue;
}

static void ROMClose(GFILE *f)
{
	(void)f;
}

static int ROMRead(GFILE *f, void *buf, int size)
{
	const ROMFS_DIRENTRY *p;

	p = (const ROMFS_DIRENTRY *)f->obj;
	if (p->size - f->pos < size)
		size = p->size - f->pos;
	if (size <= 0)	return 0;
	memcpy(buf, p->file+f->pos, size);
	return size;
}

static gBool ROMSetpos(GFILE *f, gFileSize pos)
{
	return pos <= ((const ROMFS_DIRENTRY *)f->obj)->size;
}

static gFileSize ROMGetsize(GFILE *f)
{
	return ((const ROMFS_DIRENTRY *)f->obj)->size;
}

static gBool ROMEof(GFILE *f)
{
	return f->pos >= ((const ROMFS_DIRENTRY *)f->obj)->size;
}

#if GFILE_NEED_FILELISTS
	static gfileList *ROMFlOpen(const char *path, gBool dirs) {
		ROMFileList *	p;
		(void)			path;

		// We don't support directories or path searching
		if (dirs)
			return 0;

		// Allocate the list buffer
		if (!(p = gfxAlloc(sizeof(ROMFileList))))
			return 0;

		// Initialize it and return it.
		p->pdir = 0;
		return &p->fl;
	}

	static const char *ROMFlRead(gfileList *pfl) {
		#define rfl		((ROMFileList *)pfl)

		// Is it the first entry
		if (!rfl->pdir) {
			rfl->pdir = FsROMHead;
			return FsROMHead->name;
		}

		// Is it not the last entry
		if (rfl->pdir->next) {
			rfl->pdir = rfl->pdir->next;
			return rfl->pdir->name;
		}

		return 0;
		#undef rfl
	}

	static void ROMFlClose(gfileList *pfl) {
		gfxFree(pfl);
	}
#endif

#endif //GFX_USE_GFILE && GFILE_NEED_ROMFS
