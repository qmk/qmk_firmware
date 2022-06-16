/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/********************************************************
 * The FATFS file-system
 ********************************************************/

#include "../../gfx.h"

#if GFX_USE_GFILE && GFILE_NEED_FATFS

#include "gfile_fs.h"
#include "gfile_fatfs_wrapper.h"

/********************************************************
 * The FAT file-system VMT
 ********************************************************/

static gBool fatfsDel(const char* fname);
static gBool fatfsExists(const char* fname);
static gFileSize fatfsFileSize(const char* fname);
static gBool fatfsRename(const char* oldname, const char* newname);
static gBool fatfsOpen(GFILE* f, const char* fname);
static void fatfsClose(GFILE* f);
static int fatfsRead(GFILE* f, void* buf, int size);
static int fatfsWrite(GFILE* f, const void* buf, int size);
static gBool fatfsSetPos(GFILE* f, gFileSize pos);
static gFileSize fatfsGetSize(GFILE* f);
static gBool fatfsEOF(GFILE* f);
static gBool fatfsMount(const char* drive);
static gBool fatfsUnmount(const char* drive);
static gBool fatfsSync(GFILE* f);
#if GFILE_NEED_FILELISTS && _FS_MINIMIZE <= 1
	static gfileList *fatfsFlOpen(const char *path, gBool dirs);
	static const char *fatfsFlRead(gfileList *pfl);
	static void fatfsFlClose(gfileList *pfl);
#endif

const GFILEVMT FsFatFSVMT = {
	GFSFLG_WRITEABLE | GFSFLG_SEEKABLE,
	'F',
	fatfsDel,
	fatfsExists,
	fatfsFileSize,
	fatfsRename,
	fatfsOpen,
	fatfsClose,
	fatfsRead,
	fatfsWrite,
	fatfsSetPos,
	fatfsGetSize,
	fatfsEOF,
	fatfsMount, fatfsUnmount, fatfsSync,
	#if GFILE_NEED_FILELISTS
		#if _FS_MINIMIZE <= 1
			fatfsFlOpen, fatfsFlRead, fatfsFlClose
		#else
			0, 0, 0
		#endif
	#endif
};

// Our directory list structure
typedef struct fatfsList {
	gfileList	fl;					// This must be the first element.
	DIR			dir;
	FILINFO		fno;
	#if _USE_LFN
		char	lfn[_MAX_LFN + 1];   /* Buffer to store the LFN */
	#endif
} fatfsList;

// optimize these later on. Use an array to have multiple FatFS
static gBool fatfs_mounted = gFalse;
static FATFS fatfs_fs;

static BYTE fatfs_flags2mode(GFILE* f)
{
	BYTE mode = 0;

	if (f->flags & GFILEFLG_READ)
		mode |= FA_READ;
	if (f->flags & GFILEFLG_WRITE)
		mode |= FA_WRITE;
	if (f->flags & GFILEFLG_APPEND)
		mode |= FA_OPEN_APPEND;
	if (f->flags & GFILEFLG_TRUNC)
		mode |= FA_CREATE_ALWAYS;

	/* ToDo - Complete */
	return mode;
}

static gBool fatfsDel(const char* fname)
{
	FRESULT ferr;

	ferr = f_unlink( (const TCHAR*)fname );
	if (ferr != FR_OK)
		return gFalse;

	return gTrue;
}

static gBool fatfsExists(const char* fname)
{
	FRESULT ferr;
	FILINFO fno;

	ferr = f_stat( (const TCHAR*)fname, &fno);
	if (ferr != FR_OK)
		return gFalse;

	return gTrue;
}

static gFileSize fatfsFileSize(const char* fname)
{
	FRESULT ferr;
	FILINFO fno;

	ferr = f_stat( (const TCHAR*)fname, &fno );
	if (ferr != FR_OK)
		return 0;

	return (gFileSize)fno.fsize;
}

static gBool fatfsRename(const char* oldname, const char* newname)
{
	FRESULT ferr;

	ferr = f_rename( (const TCHAR*)oldname, (const TCHAR*)newname );
	if (ferr != FR_OK)
		return gFalse;

	return gTrue;
}

static gBool fatfsOpen(GFILE* f, const char* fname)
{
	FIL* fd;

	#if !GFILE_NEED_NOAUTOMOUNT
		if (!fatfs_mounted && !fatfsMount(""))
			return gFalse;
	#endif

	if (!(fd = gfxAlloc(sizeof(FIL))))
		return gFalse;

	if (f_open(fd, fname, fatfs_flags2mode(f)) != FR_OK) {
		gfxFree(fd);
		f->obj = 0;

		return gFalse;
	}

	f->obj = (void*)fd;

	#if !GFILE_NEED_NOAUTOSYNC
		// no need to sync when not opening for write
		if (f->flags & GFILEFLG_WRITE) {
			f_sync( (FIL*)f->obj );
		}
	#endif

	return gTrue;	
}

static void fatfsClose(GFILE* f)
{
	if ((FIL*)f->obj != 0) { 
		f_close( (FIL*)f->obj );
		gfxFree( (FIL*)f->obj );
	}
}

static int fatfsRead(GFILE* f, void* buf, int size)
{
	int br;

	f_read( (FIL*)f->obj, buf, size, (UINT*)&br);

	return br;
}

static int fatfsWrite(GFILE* f, const void* buf, int size)
{
	int wr;

	f_write( (FIL*)f->obj, buf, size, (UINT*)&wr);
	#if !GFILE_NEED_NOAUTOSYNC
		f_sync( (FIL*)f->obj );
	#endif

	return wr;
}

static gBool fatfsSetPos(GFILE* f, gFileSize pos)
{
	FRESULT ferr;

	ferr = f_lseek( (FIL*)f->obj, (DWORD)pos );
	if (ferr != FR_OK)
		return gFalse;

	return gTrue;
}

static gFileSize fatfsGetSize(GFILE* f)
{
	return (gFileSize)f_size( (FIL*)f->obj );
}

static gBool fatfsEOF(GFILE* f)
{
	if ( f_eof( (FIL*)f->obj ) != 0)
		return gTrue;
	else
		return gFalse;
}

static gBool fatfsMount(const char* drive)
{
	FRESULT ferr;

	if (!fatfs_mounted) {
		ferr = f_mount(&fatfs_fs, drive, 1);
		if (ferr !=  FR_OK)
			return gFalse;
		fatfs_mounted = gTrue;
		return gTrue;
	}

	return gFalse;
}

static gBool fatfsUnmount(const char* drive)
{
	(void)drive;

	if (fatfs_mounted) {
		// FatFS does not provide an unmount routine.
		fatfs_mounted = gFalse;
		return gTrue;
	}

	return gFalse;
}

static gBool fatfsSync(GFILE *f)
{
	FRESULT ferr;

	ferr = f_sync( (FIL*)f->obj );
	if (ferr != FR_OK) {
		return gFalse;
	}

	return gTrue;
}

#if GFILE_NEED_FILELISTS && _FS_MINIMIZE <= 1
	static gfileList *fatfsFlOpen(const char *path, gBool dirs) {
		fatfsList	*p;
		(void) dirs;

		if (!(p = gfxAlloc(sizeof(fatfsList))))
			return 0;

		if (f_opendir(&p->dir, path) != FR_OK) {
			gfxFree(p);
			return 0;
		}
		return &p->fl;
	}

	static const char *fatfsFlRead(gfileList *pfl) {
		#define ffl		((fatfsList *)pfl)

		while(1) {
			#if _USE_LFN
				ffl->fno.lfname = ffl->lfn;
				ffl->fno.lfsize = sizeof(ffl->lfn);
			#endif

			// Read the next entry
			if (f_readdir(&ffl->dir, &ffl->fno) != FR_OK || !ffl->fno.fname[0])
				return 0;

			/* Ignore dot entries */
			if (ffl->fno.fname[0] == '.') continue;

			/* Is it a directory */
			if (ffl->fl.dirs) {
				if ((ffl->fno.fattrib & AM_DIR))
					break;
			} else {
				if (!(ffl->fno.fattrib & AM_DIR))
					break;
			}
		}

		#if _USE_LFN
			return ffl->fno.lfname[0] ? ffl->fno.lfname : ffl->fno.fname;
		#else
			return ffl->fno.fname;
		#endif
		#undef ffl
	}

	static void fatfsFlClose(gfileList *pfl) {
		f_closedir(&((fatfsList *)pfl)->dir);
		gfxFree(pfl);
	}

#endif

#endif //GFX_USE_GFILE && GFILE_NEED_FATFS

