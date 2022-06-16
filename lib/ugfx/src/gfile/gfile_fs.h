/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gfile/gfile_fs.h
 * @brief   GFILE file system header.
 *
 */

#ifndef _GFILE_FS_H
#define _GFILE_FS_H

struct GFILE {
	const struct GFILEVMT *	vmt;
	gU16				flags;
		#define	GFILEFLG_OPEN			0x0001		// File is open
		#define	GFILEFLG_READ			0x0002		// Read the file
		#define	GFILEFLG_WRITE			0x0004		// Write the file
		#define	GFILEFLG_APPEND			0x0008		// Append on each write
		#define GFILEFLG_BINARY			0x0010		// Treat as a binary file
		#define	GFILEFLG_DELONCLOSE		0x0020		// Delete on close
		#define	GFILEFLG_CANSEEK		0x0040		// Seek operations are valid
		#define GFILEFLG_FAILONBLOCK	0x0080		// Fail on a blocking call
		#define GFILEFLG_MUSTEXIST		0x0100		// On open file must exist
		#define GFILEFLG_MUSTNOTEXIST	0x0200		// On open file must not exist
		#define GFILEFLG_TRUNC			0x0400		// On open truncate the file
	void *					obj;
	gFileSize				pos;
};

struct gfileList {
	const struct GFILEVMT *	vmt;
	gBool					dirs;
};

typedef struct GFILEVMT {
	gU8					flags;
		#define GFSFLG_WRITEABLE		0x0001
		#define GFSFLG_CASESENSITIVE	0x0002
		#define GFSFLG_SEEKABLE			0x0004
		#define GFSFLG_FAST				0x0010
		#define GFSFLG_SMALL			0x0020
		#define GFSFLG_TEXTMODES		0x0040
	char					prefix;
	gBool		(*del)		(const char *fname);
	gBool		(*exists)	(const char *fname);
	gFileSize	(*filesize)	(const char *fname);
	gBool		(*ren)		(const char *oldname, const char *newname);
	gBool		(*open)		(GFILE *f, const char *fname);
	void		(*close)	(GFILE *f);
	int			(*read)		(GFILE *f, void *buf, int size);
	int			(*write)	(GFILE *f, const void *buf, int size);
	gBool		(*setpos)	(GFILE *f, gFileSize pos);
	gFileSize	(*getsize)	(GFILE *f);
	gBool		(*eof)		(GFILE *f);
	gBool		(*mount)	(const char *drive);
	gBool		(*unmount)	(const char *drive);
	gBool		(*sync)		(GFILE *f);
	#if GFILE_NEED_FILELISTS
		gfileList *	(*flopen)	(const char *path, gBool dirs);
		const char *(*flread)	(gfileList *pfl);
		void		(*flclose)	(gfileList *pfl);
	#endif
} GFILEVMT;

GFILE *_gfileFindSlot(const char *mode);

#endif //_GFILE_FS_H
