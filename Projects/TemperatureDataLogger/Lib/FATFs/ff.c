/*----------------------------------------------------------------------------/
/  FatFs - FAT file system module  R0.07e                    (C)ChaN, 2010
/-----------------------------------------------------------------------------/
/ FatFs module is a generic FAT file system module for small embedded systems.
/ This is a free software that opened for education, research and commercial
/ developments under license policy of following trems.
/
/  Copyright (C) 2010, ChaN, all right reserved.
/
/ * The FatFs module is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-----------------------------------------------------------------------------/
/ Feb 26,'06 R0.00  Prototype.
/
/ Apr 29,'06 R0.01  First stable version.
/
/ Jun 01,'06 R0.02  Added FAT12 support.
/                   Removed unbuffered mode.
/                   Fixed a problem on small (<32M) patition.
/ Jun 10,'06 R0.02a Added a configuration option (_FS_MINIMUM).
/
/ Sep 22,'06 R0.03  Added f_rename().
/                   Changed option _FS_MINIMUM to _FS_MINIMIZE.
/ Dec 11,'06 R0.03a Improved cluster scan algolithm to write files fast.
/                   Fixed f_mkdir() creates incorrect directory on FAT32.
/
/ Feb 04,'07 R0.04  Supported multiple drive system.
/                   Changed some interfaces for multiple drive system.
/                   Changed f_mountdrv() to f_mount().
/                   Added f_mkfs().
/ Apr 01,'07 R0.04a Supported multiple partitions on a plysical drive.
/                   Added a capability of extending file size to f_lseek().
/                   Added minimization level 3.
/                   Fixed an endian sensitive code in f_mkfs().
/ May 05,'07 R0.04b Added a configuration option _USE_NTFLAG.
/                   Added FSInfo support.
/                   Fixed DBCS name can result FR_INVALID_NAME.
/                   Fixed short seek (<= csize) collapses the file object.
/
/ Aug 25,'07 R0.05  Changed arguments of f_read(), f_write() and f_mkfs().
/                   Fixed f_mkfs() on FAT32 creates incorrect FSInfo.
/                   Fixed f_mkdir() on FAT32 creates incorrect directory.
/ Feb 03,'08 R0.05a Added f_truncate() and f_utime().
/                   Fixed off by one error at FAT sub-type determination.
/                   Fixed btr in f_read() can be mistruncated.
/                   Fixed cached sector is not flushed when create and close
/                   without write.
/
/ Apr 01,'08 R0.06  Added fputc(), fputs(), fprintf() and fgets().
/                   Improved performance of f_lseek() on moving to the same
/                   or following cluster.
/
/ Apr 01,'09 R0.07  Merged Tiny-FatFs as a buffer configuration option.
/                   Added long file name support.
/                   Added multiple code page support.
/                   Added re-entrancy for multitask operation.
/                   Added auto cluster size selection to f_mkfs().
/                   Added rewind option to f_readdir().
/                   Changed result code of critical errors.
/                   Renamed string functions to avoid name collision.
/ Apr 14,'09 R0.07a Separated out OS dependent code on reentrant cfg.
/                   Added multiple sector size support.
/ Jun 21,'09 R0.07c Fixed f_unlink() can return FR_OK on error.
/                   Fixed wrong cache control in f_lseek().
/                   Added relative path feature.
/                   Added f_chdir() and f_chdrive().
/                   Added proper case conversion to extended char.
/ Nov 03,'09 R0.07e Separated out configuration options from ff.h to ffconf.h.
/                   Fixed f_unlink() fails to remove a sub-dir on _FS_RPATH.
/                   Fixed name matching error on the 13 char boundary.
/                   Added a configuration option, _LFN_UNICODE.
/                   Changed f_readdir() to return the SFN with always upper
/                   case on non-LFN cfg.
/---------------------------------------------------------------------------*/

#include "ff.h"			/* FatFs configurations and declarations */
#include "diskio.h"		/* Declarations of low level disk I/O functions */

/*--------------------------------------------------------------------------

   Module Private Definitions

---------------------------------------------------------------------------*/

#if _FATFS != 0x007E
#error Wrong include file (ff.h).
#endif

#if _FS_REENTRANT
#if _USE_LFN == 1
#error Static LFN work area must not be used in re-entrant configuration.
#endif
#define	ENTER_FF(fs)		{ if (!lock_fs(fs)) return FR_TIMEOUT; }
#define	LEAVE_FF(fs, res)	{ unlock_fs(fs, res); return res; }

#else
#define	ENTER_FF(fs)
#define LEAVE_FF(fs, res)	return res

#endif

#define	ABORT(fs, res)		{ fp->flag |= FA__ERROR; LEAVE_FF(fs, res); }

#ifndef NULL
#define	NULL	0
#endif

/* Name status flags */
#define NS			11		/* Offset of name status byte */
#define NS_LOSS		0x01	/* Out of 8.3 format */
#define NS_LFN		0x02	/* Force to create LFN entry */
#define NS_LAST		0x04	/* Last segment */
#define NS_BODY		0x08	/* Lower case flag (body) */
#define NS_EXT		0x10	/* Lower case flag (ext) */
#define NS_DOT		0x20	/* Dot entry */




/*--------------------------------------------------------------------------

   Private Work Area

---------------------------------------------------------------------------*/

#if _DRIVES < 1 || _DRIVES > 9
#error Number of drives must be 1-9.
#endif
static
FATFS *FatFs[_DRIVES];	/* Pointer to the file system objects (logical drives) */

static
WORD Fsid;				/* File system mount ID */

#if _FS_RPATH
static
BYTE Drive;				/* Current drive */
#endif


#if _USE_LFN == 1	/* LFN with static LFN working buffer */
static
WCHAR LfnBuf[_MAX_LFN + 1];
#define	NAMEBUF(sp,lp)	BYTE sp[12]; WCHAR *lp = LfnBuf
#define INITBUF(dj,sp,lp)	dj.fn = sp; dj.lfn = lp

#elif _USE_LFN > 1	/* LFN with dynamic LFN working buffer */
#define	NAMEBUF(sp,lp)	BYTE sp[12]; WCHAR lbuf[_MAX_LFN + 1], *lp = lbuf
#define INITBUF(dj,sp,lp)	dj.fn = sp; dj.lfn = lp

#else				/* No LFN */
#define	NAMEBUF(sp,lp)	BYTE sp[12]
#define INITBUF(dj,sp,lp)	dj.fn = sp

#endif




/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* String functions                                                      */
/*-----------------------------------------------------------------------*/

/* Copy memory to memory */
static
void mem_cpy (void* dst, const void* src, int cnt) {
	char *d = (char*)dst;
	const char *s = (const char *)src;
	while (cnt--) *d++ = *s++;
}

/* Fill memory */
static
void mem_set (void* dst, int val, int cnt) {
	char *d = (char*)dst;
	while (cnt--) *d++ = (char)val;
}

/* Compare memory to memory */
static
int mem_cmp (const void* dst, const void* src, int cnt) {
	const char *d = (const char *)dst, *s = (const char *)src;
	int r = 0;
	while (cnt-- && (r = *d++ - *s++) == 0) ;
	return r;
}

/* Check if chr is contained in the string */
static
int chk_chr (const char* str, int chr) {
	while (*str && *str != chr) str++;
	return *str;
}



/*-----------------------------------------------------------------------*/
/* Request/Release grant to access the volume                            */
/*-----------------------------------------------------------------------*/
#if _FS_REENTRANT

static
BOOL lock_fs (
	FATFS *fs		/* File system object */
)
{
	return ff_req_grant(fs->sobj);
}


static
void unlock_fs (
	FATFS *fs,		/* File system object */
	FRESULT res		/* Result code to be returned */
)
{
	if (res != FR_NOT_ENABLED &&
		res != FR_INVALID_DRIVE &&
		res != FR_INVALID_OBJECT &&
		res != FR_TIMEOUT) {
		ff_rel_grant(fs->sobj);
	}
}
#endif



/*-----------------------------------------------------------------------*/
/* Change window offset                                                  */
/*-----------------------------------------------------------------------*/

static
FRESULT move_window (
	FATFS *fs,		/* File system object */
	DWORD sector	/* Sector number to make apperance in the fs->win[] */
)					/* Move to zero only writes back dirty window */
{
	DWORD wsect;


	wsect = fs->winsect;
	if (wsect != sector) {	/* Changed current window */
#if !_FS_READONLY
		if (fs->wflag) {	/* Write back dirty window if needed */
			if (disk_write(fs->drive, fs->win, wsect, 1) != RES_OK)
				return FR_DISK_ERR;
			fs->wflag = 0;
			if (wsect < (fs->fatbase + fs->sects_fat)) {	/* In FAT area */
				BYTE nf;
				for (nf = fs->n_fats; nf > 1; nf--) {	/* Refrect the change to all FAT copies */
					wsect += fs->sects_fat;
					disk_write(fs->drive, fs->win, wsect, 1);
				}
			}
		}
#endif
		if (sector) {
			if (disk_read(fs->drive, fs->win, sector, 1) != RES_OK)
				return FR_DISK_ERR;
			fs->winsect = sector;
		}
	}

	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Clean-up cached data                                                  */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY
static
FRESULT sync (	/* FR_OK: successful, FR_DISK_ERR: failed */
	FATFS *fs	/* File system object */
)
{
	FRESULT res;


	res = move_window(fs, 0);
	if (res == FR_OK) {
		/* Update FSInfo sector if needed */
		if (fs->fs_type == FS_FAT32 && fs->fsi_flag) {
			fs->winsect = 0;
			mem_set(fs->win, 0, 512);
			ST_WORD(fs->win+BS_55AA, 0xAA55);
			ST_DWORD(fs->win+FSI_LeadSig, 0x41615252);
			ST_DWORD(fs->win+FSI_StrucSig, 0x61417272);
			ST_DWORD(fs->win+FSI_Free_Count, fs->free_clust);
			ST_DWORD(fs->win+FSI_Nxt_Free, fs->last_clust);
			disk_write(fs->drive, fs->win, fs->fsi_sector, 1);
			fs->fsi_flag = 0;
		}
		/* Make sure that no pending write process in the physical drive */
		if (disk_ioctl(fs->drive, CTRL_SYNC, (void*)NULL) != RES_OK)
			res = FR_DISK_ERR;
	}

	return res;
}
#endif




/*-----------------------------------------------------------------------*/
/* FAT access - Read value of a FAT entry                                */
/*-----------------------------------------------------------------------*/


DWORD get_fat (	/* 0xFFFFFFFF:Disk error, 1:Interal error, Else:Cluster status */
	FATFS *fs,	/* File system object */
	DWORD clst	/* Cluster# to get the link information */
)
{
	UINT wc, bc;
	DWORD fsect;


	if (clst < 2 || clst >= fs->max_clust)	/* Range check */
		return 1;

	fsect = fs->fatbase;
	switch (fs->fs_type) {
	case FS_FAT12 :
		bc = clst; bc += bc / 2;
		if (move_window(fs, fsect + (bc / SS(fs)))) break;
		wc = fs->win[bc & (SS(fs) - 1)]; bc++;
		if (move_window(fs, fsect + (bc / SS(fs)))) break;
		wc |= (WORD)fs->win[bc & (SS(fs) - 1)] << 8;
		return (clst & 1) ? (wc >> 4) : (wc & 0xFFF);

	case FS_FAT16 :
		if (move_window(fs, fsect + (clst / (SS(fs) / 2)))) break;
		return LD_WORD(&fs->win[((WORD)clst * 2) & (SS(fs) - 1)]);

	case FS_FAT32 :
		if (move_window(fs, fsect + (clst / (SS(fs) / 4)))) break;
		return LD_DWORD(&fs->win[((WORD)clst * 4) & (SS(fs) - 1)]) & 0x0FFFFFFF;
	}

	return 0xFFFFFFFF;	/* An error occured at the disk I/O layer */
}




/*-----------------------------------------------------------------------*/
/* FAT access - Change value of a FAT entry                              */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY

FRESULT put_fat (
	FATFS *fs,	/* File system object */
	DWORD clst,	/* Cluster# to be changed in range of 2 to fs->max_clust - 1 */
	DWORD val	/* New value to mark the cluster */
)
{
	UINT bc;
	BYTE *p;
	DWORD fsect;
	FRESULT res;


	if (clst < 2 || clst >= fs->max_clust) {	/* Range check */
		res = FR_INT_ERR;

	} else {
		fsect = fs->fatbase;
		switch (fs->fs_type) {
		case FS_FAT12 :
			bc = clst; bc += bc / 2;
			res = move_window(fs, fsect + (bc / SS(fs)));
			if (res != FR_OK) break;
			p = &fs->win[bc & (SS(fs) - 1)];
			*p = (clst & 1) ? ((*p & 0x0F) | ((BYTE)val << 4)) : (BYTE)val;
			bc++;
			fs->wflag = 1;
			res = move_window(fs, fsect + (bc / SS(fs)));
			if (res != FR_OK) break;
			p = &fs->win[bc & (SS(fs) - 1)];
			*p = (clst & 1) ? (BYTE)(val >> 4) : ((*p & 0xF0) | ((BYTE)(val >> 8) & 0x0F));
			break;

		case FS_FAT16 :
			res = move_window(fs, fsect + (clst / (SS(fs) / 2)));
			if (res != FR_OK) break;
			ST_WORD(&fs->win[((WORD)clst * 2) & (SS(fs) - 1)], (WORD)val);
			break;

		case FS_FAT32 :
			res = move_window(fs, fsect + (clst / (SS(fs) / 4)));
			if (res != FR_OK) break;
			ST_DWORD(&fs->win[((WORD)clst * 4) & (SS(fs) - 1)], val);
			break;

		default :
			res = FR_INT_ERR;
		}
		fs->wflag = 1;
	}

	return res;
}
#endif /* !_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* FAT handling - Remove a cluster chain                                 */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY
static
FRESULT remove_chain (
	FATFS *fs,			/* File system object */
	DWORD clst			/* Cluster# to remove a chain from */
)
{
	FRESULT res;
	DWORD nxt;


	if (clst < 2 || clst >= fs->max_clust) {	/* Check the range of cluster# */
		res = FR_INT_ERR;

	} else {
		res = FR_OK;
		while (clst < fs->max_clust) {			/* Not a last link? */
			nxt = get_fat(fs, clst);			/* Get cluster status */
			if (nxt == 0) break;				/* Empty cluster? */
			if (nxt == 1) { res = FR_INT_ERR; break; }	/* Internal error? */
			if (nxt == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }	/* Disk error? */
			res = put_fat(fs, clst, 0);			/* Mark the cluster "empty" */
			if (res != FR_OK) break;
			if (fs->free_clust != 0xFFFFFFFF) {	/* Update FSInfo */
				fs->free_clust++;
				fs->fsi_flag = 1;
			}
			clst = nxt;	/* Next cluster */
		}
	}

	return res;
}
#endif




/*-----------------------------------------------------------------------*/
/* FAT handling - Stretch or Create a cluster chain                      */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY
static
DWORD create_chain (	/* 0:No free cluster, 1:Internal error, 0xFFFFFFFF:Disk error, >=2:New cluster# */
	FATFS *fs,			/* File system object */
	DWORD clst			/* Cluster# to stretch. 0 means create a new chain. */
)
{
	DWORD cs, ncl, scl, mcl;


	mcl = fs->max_clust;
	if (clst == 0) {		/* Create new chain */
		scl = fs->last_clust;			/* Get suggested start point */
		if (scl == 0 || scl >= mcl) scl = 1;
	}
	else {					/* Stretch existing chain */
		cs = get_fat(fs, clst);			/* Check the cluster status */
		if (cs < 2) return 1;			/* It is an invalid cluster */
		if (cs < mcl) return cs;		/* It is already followed by next cluster */
		scl = clst;
	}

	ncl = scl;				/* Start cluster */
	for (;;) {
		ncl++;							/* Next cluster */
		if (ncl >= mcl) {				/* Wrap around */
			ncl = 2;
			if (ncl > scl) return 0;	/* No free custer */
		}
		cs = get_fat(fs, ncl);			/* Get the cluster status */
		if (cs == 0) break;				/* Found a free cluster */
		if (cs == 0xFFFFFFFF || cs == 1)/* An error occured */
			return cs;
		if (ncl == scl) return 0;		/* No free custer */
	}

	if (put_fat(fs, ncl, 0x0FFFFFFF))	/* Mark the new cluster "in use" */
		return 0xFFFFFFFF;
	if (clst != 0) {					/* Link it to the previous one if needed */
		if (put_fat(fs, clst, ncl))
			return 0xFFFFFFFF;
	}

	fs->last_clust = ncl;				/* Update FSINFO */
	if (fs->free_clust != 0xFFFFFFFF) {
		fs->free_clust--;
		fs->fsi_flag = 1;
	}

	return ncl;		/* Return new cluster number */
}
#endif /* !_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Get sector# from cluster#                                             */
/*-----------------------------------------------------------------------*/


DWORD clust2sect (	/* !=0: Sector number, 0: Failed - invalid cluster# */
	FATFS *fs,		/* File system object */
	DWORD clst		/* Cluster# to be converted */
)
{
	clst -= 2;
	if (clst >= (fs->max_clust - 2)) return 0;		/* Invalid cluster# */
	return clst * fs->csize + fs->database;
}




/*-----------------------------------------------------------------------*/
/* Directory handling - Seek directory index                             */
/*-----------------------------------------------------------------------*/

static
FRESULT dir_seek (
	DIR *dj,		/* Pointer to directory object */
	WORD idx		/* Directory index number */
)
{
	DWORD clst;
	WORD ic;


	dj->index = idx;
	clst = dj->sclust;
	if (clst == 1 || clst >= dj->fs->max_clust)	/* Check start cluster range */
		return FR_INT_ERR;
	if (!clst && dj->fs->fs_type == FS_FAT32)	/* Replace cluster# 0 with root cluster# if in FAT32 */
		clst = dj->fs->dirbase;

	if (clst == 0) {	/* Static table */
		dj->clust = clst;
		if (idx >= dj->fs->n_rootdir)		/* Index is out of range */
			return FR_INT_ERR;
		dj->sect = dj->fs->dirbase + idx / (SS(dj->fs) / 32);	/* Sector# */
	}
	else {				/* Dynamic table */
		ic = SS(dj->fs) / 32 * dj->fs->csize;	/* Entries per cluster */
		while (idx >= ic) {	/* Follow cluster chain */
			clst = get_fat(dj->fs, clst);				/* Get next cluster */
			if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	/* Disk error */
			if (clst < 2 || clst >= dj->fs->max_clust)	/* Reached to end of table or int error */
				return FR_INT_ERR;
			idx -= ic;
		}
		dj->clust = clst;
		dj->sect = clust2sect(dj->fs, clst) + idx / (SS(dj->fs) / 32);	/* Sector# */
	}

	dj->dir = dj->fs->win + (idx % (SS(dj->fs) / 32)) * 32;	/* Ptr to the entry in the sector */

	return FR_OK;	/* Seek succeeded */
}




/*-----------------------------------------------------------------------*/
/* Directory handling - Move directory index next                        */
/*-----------------------------------------------------------------------*/

static
FRESULT dir_next (	/* FR_OK:Succeeded, FR_NO_FILE:End of table, FR_DENIED:EOT and could not streach */
	DIR *dj,		/* Pointer to directory object */
	BOOL streach	/* FALSE: Do not streach table, TRUE: Streach table if needed */
)
{
	DWORD clst;
	WORD i;


	i = dj->index + 1;
	if (!i || !dj->sect)	/* Report EOT when index has reached 65535 */
		return FR_NO_FILE;

	if (!(i % (SS(dj->fs) / 32))) {	/* Sector changed? */
		dj->sect++;					/* Next sector */

		if (dj->clust == 0) {	/* Static table */
			if (i >= dj->fs->n_rootdir)	/* Report EOT when end of table */
				return FR_NO_FILE;
		}
		else {					/* Dynamic table */
			if (((i / (SS(dj->fs) / 32)) & (dj->fs->csize - 1)) == 0) {	/* Cluster changed? */
				clst = get_fat(dj->fs, dj->clust);				/* Get next cluster */
				if (clst <= 1) return FR_INT_ERR;
				if (clst == 0xFFFFFFFF) return FR_DISK_ERR;
				if (clst >= dj->fs->max_clust) {				/* When it reached end of dynamic table */
#if !_FS_READONLY
					BYTE c;
					if (!streach) return FR_NO_FILE;			/* When do not streach, report EOT */
					clst = create_chain(dj->fs, dj->clust);		/* Streach cluster chain */
					if (clst == 0) return FR_DENIED;			/* No free cluster */
					if (clst == 1) return FR_INT_ERR;
					if (clst == 0xFFFFFFFF) return FR_DISK_ERR;
					/* Clean-up streached table */
					if (move_window(dj->fs, 0)) return FR_DISK_ERR;	/* Flush active window */
					mem_set(dj->fs->win, 0, SS(dj->fs));			/* Clear window buffer */
					dj->fs->winsect = clust2sect(dj->fs, clst);	/* Cluster start sector */
					for (c = 0; c < dj->fs->csize; c++) {		/* Fill the new cluster with 0 */
						dj->fs->wflag = 1;
						if (move_window(dj->fs, 0)) return FR_DISK_ERR;
						dj->fs->winsect++;
					}
					dj->fs->winsect -= c;						/* Rewind window address */
#else
					return FR_NO_FILE;			/* Report EOT */
#endif
				}
				dj->clust = clst;				/* Initialize data for new cluster */
				dj->sect = clust2sect(dj->fs, clst);
			}
		}
	}

	dj->index = i;
	dj->dir = dj->fs->win + (i % (SS(dj->fs) / 32)) * 32;

	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* LFN handling - Test/Pick/Fit an LFN segment from/to directory entry   */
/*-----------------------------------------------------------------------*/
#if _USE_LFN
static
const BYTE LfnOfs[] = {1,3,5,7,9,14,16,18,20,22,24,28,30};	/* Offset of LFN chars in the directory entry */


static
BOOL cmp_lfn (			/* TRUE:Matched, FALSE:Not matched */
	WCHAR *lfnbuf,		/* Pointer to the LFN to be compared */
	BYTE *dir			/* Pointer to the directory entry containing a part of LFN */
)
{
	int i, s;
	WCHAR wc, uc;


	i = ((dir[LDIR_Ord] & 0xBF) - 1) * 13;	/* Get offset in the LFN buffer */
	s = 0; wc = 1;
	do {
		uc = LD_WORD(dir+LfnOfs[s]);	/* Pick an LFN character from the entry */
		if (wc) {	/* Last char has not been processed */
			wc = ff_wtoupper(uc);		/* Convert it to upper case */
			if (i >= _MAX_LFN || wc != ff_wtoupper(lfnbuf[i++]))	/* Compare it */
				return FALSE;			/* Not matched */
		} else {
			if (uc != 0xFFFF) return FALSE;	/* Check filler */
		}
	} while (++s < 13);				/* Repeat until all chars in the entry are checked */

	if ((dir[LDIR_Ord] & 0x40) && wc && lfnbuf[i])	/* Last segment matched but different length */
		return FALSE;

	return TRUE;					/* The part of LFN matched */
}



static
BOOL pick_lfn (			/* TRUE:Succeeded, FALSE:Buffer overflow */
	WCHAR *lfnbuf,		/* Pointer to the Unicode-LFN buffer */
	BYTE *dir			/* Pointer to the directory entry */
)
{
	int i, s;
	WCHAR wc, uc;


	i = ((dir[LDIR_Ord] & 0x3F) - 1) * 13;	/* Offset in the LFN buffer */

	s = 0; wc = 1;
	do {
		uc = LD_WORD(dir+LfnOfs[s]);			/* Pick an LFN character from the entry */
		if (wc) {	/* Last char has not been processed */
			if (i >= _MAX_LFN) return FALSE;	/* Buffer overflow? */
			lfnbuf[i++] = wc = uc;				/* Store it */
		} else {
			if (uc != 0xFFFF) return FALSE;		/* Check filler */
		}
	} while (++s < 13);						/* Read all character in the entry */

	if (dir[LDIR_Ord] & 0x40) {				/* Put terminator if it is the last LFN part */
		if (i >= _MAX_LFN) return FALSE;	/* Buffer overflow? */
		lfnbuf[i] = 0;
	}

	return TRUE;
}


#if !_FS_READONLY
static
void fit_lfn (
	const WCHAR *lfnbuf,	/* Pointer to the LFN buffer */
	BYTE *dir,				/* Pointer to the directory entry */
	BYTE ord,				/* LFN order (1-20) */
	BYTE sum				/* SFN sum */
)
{
	int i, s;
	WCHAR wc;


	dir[LDIR_Chksum] = sum;			/* Set check sum */
	dir[LDIR_Attr] = AM_LFN;		/* Set attribute. LFN entry */
	dir[LDIR_Type] = 0;
	ST_WORD(dir+LDIR_FstClusLO, 0);

	i = (ord - 1) * 13;				/* Get offset in the LFN buffer */
	s = wc = 0;
	do {
		if (wc != 0xFFFF) wc = lfnbuf[i++];	/* Get an effective char */
		ST_WORD(dir+LfnOfs[s], wc);	/* Put it */
		if (!wc) wc = 0xFFFF;		/* Padding chars following last char */
	} while (++s < 13);
	if (wc == 0xFFFF || !lfnbuf[i]) ord |= 0x40;	/* Bottom LFN part is the start of LFN sequence */
	dir[LDIR_Ord] = ord;			/* Set the LFN order */
}

#endif
#endif



/*-----------------------------------------------------------------------*/
/* Create numbered name                                                  */
/*-----------------------------------------------------------------------*/
#if _USE_LFN
void gen_numname (
	BYTE *dst,			/* Pointer to genartated SFN */
	const BYTE *src,	/* Pointer to source SFN to be modified */
	const WCHAR *lfn,	/* Pointer to LFN */
	WORD num			/* Sequense number */
)
{
	char ns[8];
	int i, j;


	mem_cpy(dst, src, 11);

	if (num > 5) {	/* On many collisions, generate a hash number instead of sequencial number */
		do num = (num >> 1) + (num << 15) + (WORD)*lfn++; while (*lfn);
	}

	/* itoa */
	i = 7;
	do {
		ns[i--] = (num % 10) + '0';
		num /= 10;
	} while (num);
	ns[i] = '~';

	/* Append the number */
	for (j = 0; j < i && dst[j] != ' '; j++) {
		if (IsDBCS1(dst[j])) {
			if (j == i - 1) break;
			j++;
		}
	}
	do {
		dst[j++] = (i < 8) ? ns[i++] : ' ';
	} while (j < 8);
}
#endif




/*-----------------------------------------------------------------------*/
/* Calculate sum of an SFN                                               */
/*-----------------------------------------------------------------------*/
#if _USE_LFN
static
BYTE sum_sfn (
	const BYTE *dir		/* Ptr to directory entry */
)
{
	BYTE sum = 0;
	int n = 11;

	do sum = (sum >> 1) + (sum << 7) + *dir++; while (--n);
	return sum;
}
#endif




/*-----------------------------------------------------------------------*/
/* Directory handling - Find an object in the directory                  */
/*-----------------------------------------------------------------------*/

static
FRESULT dir_find (
	DIR *dj			/* Pointer to the directory object linked to the file name */
)
{
	FRESULT res;
	BYTE c, *dir;
#if _USE_LFN
	BYTE a, ord, sum;
#endif

	res = dir_seek(dj, 0);			/* Rewind directory object */
	if (res != FR_OK) return res;

#if _USE_LFN
	ord = sum = 0xFF;
#endif
	do {
		res = move_window(dj->fs, dj->sect);
		if (res != FR_OK) break;
		dir = dj->dir;					/* Ptr to the directory entry of current index */
		c = dir[DIR_Name];
		if (c == 0) { res = FR_NO_FILE; break; }	/* Reached to end of table */
#if _USE_LFN	/* LFN configuration */
		a = dir[DIR_Attr] & AM_MASK;
		if (c == 0xE5 || ((a & AM_VOL) && a != AM_LFN)) {	/* An entry without valid data */
			ord = 0xFF;
		} else {
			if (a == AM_LFN) {			/* An LFN entry is found */
				if (dj->lfn) {
					if (c & 0x40) {		/* Is it start of LFN sequence? */
						sum = dir[LDIR_Chksum];
						c &= 0xBF; ord = c;	/* LFN start order */
						dj->lfn_idx = dj->index;
					}
					/* Check validity of the LFN entry and compare it with given name */
					ord = (c == ord && sum == dir[LDIR_Chksum] && cmp_lfn(dj->lfn, dir)) ? ord - 1 : 0xFF;
				}
			} else {					/* An SFN entry is found */
				if (!ord && sum == sum_sfn(dir)) break;	/* LFN matched? */
				ord = 0xFF; dj->lfn_idx = 0xFFFF;	/* Reset LFN sequence */
				if (!(dj->fn[NS] & NS_LOSS) && !mem_cmp(dir, dj->fn, 11)) break;	/* SFN matched? */
			}
		}
#else		/* Non LFN configuration */
		if (!(dir[DIR_Attr] & AM_VOL) && !mem_cmp(dir, dj->fn, 11)) /* Is it a valid entry? */
			break;
#endif
		res = dir_next(dj, FALSE);		/* Next entry */
	} while (res == FR_OK);

	return res;
}




/*-----------------------------------------------------------------------*/
/* Read an object from the directory                                     */
/*-----------------------------------------------------------------------*/
#if _FS_MINIMIZE <= 1
static
FRESULT dir_read (
	DIR *dj			/* Pointer to the directory object that pointing the entry to be read */
)
{
	FRESULT res;
	BYTE c, *dir;
#if _USE_LFN
	BYTE a, ord = 0xFF, sum = 0xFF;
#endif

	res = FR_NO_FILE;
	while (dj->sect) {
		res = move_window(dj->fs, dj->sect);
		if (res != FR_OK) break;
		dir = dj->dir;					/* Ptr to the directory entry of current index */
		c = dir[DIR_Name];
		if (c == 0) { res = FR_NO_FILE; break; }	/* Reached to end of table */
#if _USE_LFN	/* LFN configuration */
		a = dir[DIR_Attr] & AM_MASK;
		if (c == 0xE5 || (!_FS_RPATH && c == '.') || ((a & AM_VOL) && a != AM_LFN)) {	/* An entry without valid data */
			ord = 0xFF;
		} else {
			if (a == AM_LFN) {			/* An LFN entry is found */
				if (c & 0x40) {			/* Is it start of LFN sequence? */
					sum = dir[LDIR_Chksum];
					c &= 0xBF; ord = c;
					dj->lfn_idx = dj->index;
				}
				/* Check LFN validity and capture it */
				ord = (c == ord && sum == dir[LDIR_Chksum] && pick_lfn(dj->lfn, dir)) ? ord - 1 : 0xFF;
			} else {					/* An SFN entry is found */
				if (ord || sum != sum_sfn(dir))	/* Is there a valid LFN? */
					dj->lfn_idx = 0xFFFF;		/* It has no LFN. */
				break;
			}
		}
#else		/* Non LFN configuration */
		if (c != 0xE5 && (_FS_RPATH || c != '.') && !(dir[DIR_Attr] & AM_VOL))	/* Is it a valid entry? */
			break;
#endif
		res = dir_next(dj, FALSE);				/* Next entry */
		if (res != FR_OK) break;
	}

	if (res != FR_OK) dj->sect = 0;

	return res;
}
#endif



/*-----------------------------------------------------------------------*/
/* Register an object to the directory                                   */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY
static
FRESULT dir_register (	/* FR_OK:Successful, FR_DENIED:No free entry or too many SFN collision, FR_DISK_ERR:Disk error */
	DIR *dj				/* Target directory with object name to be created */
)
{
	FRESULT res;
	BYTE c, *dir;
#if _USE_LFN	/* LFN configuration */
	WORD n, ne, is;
	BYTE sn[12], *fn, sum;
	WCHAR *lfn;


	fn = dj->fn; lfn = dj->lfn;
	mem_cpy(sn, fn, 12);

	if (_FS_RPATH && (sn[NS] & NS_DOT)) return FR_INVALID_NAME;	/* Cannot create dot entry */

	if (sn[NS] & NS_LOSS) {			/* When LFN is out of 8.3 format, generate a numbered name */
		fn[NS] = 0; dj->lfn = NULL;			/* Find only SFN */
		for (n = 1; n < 100; n++) {
			gen_numname(fn, sn, lfn, n);	/* Generate a numbered name */
			res = dir_find(dj);				/* Check if the name collides with existing SFN */
			if (res != FR_OK) break;
		}
		if (n == 100) return FR_DENIED;		/* Abort if too many collisions */
		if (res != FR_NO_FILE) return res;	/* Abort if the result is other than 'not collided' */
		fn[NS] = sn[NS]; dj->lfn = lfn;
	}

	if (sn[NS] & NS_LFN) {			/* When LFN is to be created, reserve reserve an SFN + LFN entries. */
		for (ne = 0; lfn[ne]; ne++) ;
		ne = (ne + 25) / 13;
	} else {						/* Otherwise reserve only an SFN entry. */
		ne = 1;
	}

	/* Reserve contiguous entries */
	res = dir_seek(dj, 0);
	if (res != FR_OK) return res;
	n = is = 0;
	do {
		res = move_window(dj->fs, dj->sect);
		if (res != FR_OK) break;
		c = *dj->dir;				/* Check the entry status */
		if (c == 0xE5 || c == 0) {	/* Is it a blank entry? */
			if (n == 0) is = dj->index;	/* First index of the contigulus entry */
			if (++n == ne) break;	/* A contiguous entry that requiered count is found */
		} else {
			n = 0;					/* Not a blank entry. Restart to search */
		}
		res = dir_next(dj, TRUE);	/* Next entry with table streach */
	} while (res == FR_OK);

	if (res == FR_OK && ne > 1) {	/* Initialize LFN entry if needed */
		res = dir_seek(dj, is);
		if (res == FR_OK) {
			sum = sum_sfn(dj->fn);	/* Sum of the SFN tied to the LFN */
			ne--;
			do {					/* Store LFN entries in bottom first */
				res = move_window(dj->fs, dj->sect);
				if (res != FR_OK) break;
				fit_lfn(dj->lfn, dj->dir, (BYTE)ne, sum);
				dj->fs->wflag = 1;
				res = dir_next(dj, FALSE);	/* Next entry */
			} while (res == FR_OK && --ne);
		}
	}

#else	/* Non LFN configuration */
	res = dir_seek(dj, 0);
	if (res == FR_OK) {
		do {	/* Find a blank entry for the SFN */
			res = move_window(dj->fs, dj->sect);
			if (res != FR_OK) break;
			c = *dj->dir;
			if (c == 0xE5 || c == 0) break;	/* Is it a blank entry? */
			res = dir_next(dj, TRUE);		/* Next entry with table streach */
		} while (res == FR_OK);
	}
#endif

	if (res == FR_OK) {		/* Initialize the SFN entry */
		res = move_window(dj->fs, dj->sect);
		if (res == FR_OK) {
			dir = dj->dir;
			mem_set(dir, 0, 32);		/* Clean the entry */
			mem_cpy(dir, dj->fn, 11);	/* Put SFN */
			dir[DIR_NTres] = *(dj->fn+NS) & (NS_BODY | NS_EXT);	/* Put NT flag */
			dj->fs->wflag = 1;
		}
	}

	return res;
}
#endif /* !_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Remove an object from the directory                                   */
/*-----------------------------------------------------------------------*/
#if !_FS_READONLY && !_FS_MINIMIZE
static
FRESULT dir_remove (	/* FR_OK: Successful, FR_DISK_ERR: A disk error */
	DIR *dj				/* Directory object pointing the entry to be removed */
)
{
	FRESULT res;
#if _USE_LFN	/* LFN configuration */
	WORD i;

	i = dj->index;	/* SFN index */
	res = dir_seek(dj, (WORD)((dj->lfn_idx == 0xFFFF) ? i : dj->lfn_idx));	/* Goto the SFN or top of the LFN entries */
	if (res == FR_OK) {
		do {
			res = move_window(dj->fs, dj->sect);
			if (res != FR_OK) break;
			*dj->dir = 0xE5;			/* Mark the entry "deleted" */
			dj->fs->wflag = 1;
			if (dj->index >= i) break;	/* When reached SFN, all entries of the object has been deleted. */
			res = dir_next(dj, FALSE);	/* Next entry */
		} while (res == FR_OK);
		if (res == FR_NO_FILE) res = FR_INT_ERR;
	}

#else			/* Non LFN configuration */
	res = dir_seek(dj, dj->index);
	if (res == FR_OK) {
		res = move_window(dj->fs, dj->sect);
		if (res == FR_OK) {
			*dj->dir = 0xE5;			/* Mark the entry "deleted" */
			dj->fs->wflag = 1;
		}
	}
#endif

	return res;
}
#endif /* !_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Pick a segment and create the object name in directory form           */
/*-----------------------------------------------------------------------*/

static
FRESULT create_name (
	DIR *dj,			/* Pointer to the directory object */
	const XCHAR **path	/* Pointer to pointer to the segment in the path string */
)
{
#ifdef _EXCVT
	static const BYTE cvt[] = _EXCVT;
#endif

#if _USE_LFN	/* LFN configuration */
	BYTE b, cf;
	WCHAR w, *lfn;
	int i, ni, si, di;
	const XCHAR *p;

	/* Create LFN in Unicode */
	si = di = 0;
	p = *path;
	lfn = dj->lfn;
	for (;;) {
		w = p[si++];					/* Get a character */
		if (w < ' ' || w == '/' || w == '\\') break;	/* Break on end of segment */
		if (di >= _MAX_LFN)				/* Reject too long name */
			return FR_INVALID_NAME;
#if !_LFN_UNICODE
		w &= 0xFF;
		if (IsDBCS1(w)) {				/* If it is a DBC 1st byte */
			b = p[si++];				/* Get 2nd byte */
			if (!IsDBCS2(b))			/* Reject invalid code for DBC */
				return FR_INVALID_NAME;
			w = (w << 8) + b;
		}
		w = ff_convert(w, 1);			/* Convert OEM to Unicode */
		if (!w) return FR_INVALID_NAME;	/* Reject invalid code */
#endif
		if (w < 0x80 && chk_chr("\"*:<>\?|\x7F", w)) /* Reject illegal chars for LFN */
			return FR_INVALID_NAME;
		lfn[di++] = w;					/* Store the Unicode char */
	}
	*path = &p[si];						/* Rerurn pointer to the next segment */
	cf = (w < ' ') ? NS_LAST : 0;		/* Set last segment flag if end of path */
#if _FS_RPATH
	if ((di == 1 && lfn[di - 1] == '.') || /* Is this a dot entry? */
		(di == 2 && lfn[di - 1] == '.' && lfn[di - 2] == '.')) {
		lfn[di] = 0;
		for (i = 0; i < 11; i++)
			dj->fn[i] = (i < di) ? '.' : ' ';
		dj->fn[i] = cf | NS_DOT;		/* This is a dot entry */
		return FR_OK;
	}
#endif
	while (di) {						/* Strip trailing spaces and dots */
		w = lfn[di - 1];
		if (w != ' ' && w != '.') break;
		di--;
	}
	if (!di) return FR_INVALID_NAME;	/* Reject null string */

	lfn[di] = 0;						/* LFN is created */

	/* Create SFN in directory form */
	mem_set(dj->fn, ' ', 11);
	for (si = 0; lfn[si] == ' ' || lfn[si] == '.'; si++) ;	/* Strip leading spaces and dots */
	if (si) cf |= NS_LOSS | NS_LFN;
	while (di && lfn[di - 1] != '.') di--;	/* Find extension (di<=si: no extension) */

	b = i = 0; ni = 8;
	for (;;) {
		w = lfn[si++];					/* Get an LFN char */
		if (!w) break;					/* Break on enf of the LFN */
		if (w == ' ' || (w == '.' && si != di)) {	/* Remove spaces and dots */
			cf |= NS_LOSS | NS_LFN; continue;
		}

		if (i >= ni || si == di) {		/* Extension or end of SFN */
			if (ni == 11) {				/* Long extension */
				cf |= NS_LOSS | NS_LFN; break;
			}
			if (si != di) cf |= NS_LOSS | NS_LFN;	/* Out of 8.3 format */
			if (si > di) break;			/* No extension */
			si = di; i = 8; ni = 11;	/* Enter extension section */
			b <<= 2; continue;
		}

		if (w >= 0x80) {				/* Non ASCII char */
#ifdef _EXCVT
			w = ff_convert(w, 0);		/* Unicode -> OEM code */
			if (w) w = cvt[w - 0x80];	/* Convert extended char to upper (SBCS) */
#else
			w = ff_convert(ff_wtoupper(w), 0);	/* Upper converted Unicode -> OEM code */
#endif
			cf |= NS_LFN;				/* Force create LFN entry */
		}

		if (_DF1S && w >= 0x100) {		/* Double byte char */
			if (i >= ni - 1) {
				cf |= NS_LOSS | NS_LFN; i = ni; continue;
			}
			dj->fn[i++] = (BYTE)(w >> 8);
		} else {						/* Single byte char */
			if (!w || chk_chr("+,;[=]", w)) {		/* Replace illegal chars for SFN */
				w = '_'; cf |= NS_LOSS | NS_LFN;	/* Lossy conversion */
			} else {
				if (IsUpper(w)) {		/* ASCII large capital */
					b |= 2;
				} else {
					if (IsLower(w)) {	/* ASCII small capital */
						b |= 1; w -= 0x20;
					}
				}
			}
		}
		dj->fn[i++] = (BYTE)w;
	}

	if (dj->fn[0] == 0xE5) dj->fn[0] = 0x05;	/* If the first char collides with deleted mark, replace it with 0x05 */

	if (ni == 8) b <<= 2;
	if ((b & 0x0C) == 0x0C || (b & 0x03) == 0x03)	/* Create LFN entry when there are composite capitals */
		cf |= NS_LFN;
	if (!(cf & NS_LFN)) {						/* When LFN is in 8.3 format without extended char, NT flags are created */
		if ((b & 0x03) == 0x01) cf |= NS_EXT;	/* NT flag (Extension has only small capital) */
		if ((b & 0x0C) == 0x04) cf |= NS_BODY;	/* NT flag (Filename has only small capital) */
	}

	dj->fn[NS] = cf;	/* SFN is created */

	return FR_OK;


#else	/* Non-LFN configuration */
	BYTE b, c, d, *sfn;
	int ni, si, i;
	const char *p;

	/* Create file name in directory form */
	sfn = dj->fn;
	mem_set(sfn, ' ', 11);
	si = i = b = 0; ni = 8;
	p = *path;
#if _FS_RPATH
	if (p[si] == '.') { /* Is this a dot entry? */
		for (;;) {
			c = p[si++];
			if (c != '.' || si >= 3) break;
			sfn[i++] = c;
		}
		if (c != '/' && c != '\\' && c > ' ') return FR_INVALID_NAME;
		*path = &p[si];									/* Rerurn pointer to the next segment */
		sfn[NS] = (c <= ' ') ? NS_LAST | NS_DOT : NS_DOT;	/* Set last segment flag if end of path */
		return FR_OK;
	}
#endif
	for (;;) {
		c = p[si++];
		if (c <= ' ' || c == '/' || c == '\\') break;	/* Break on end of segment */
		if (c == '.' || i >= ni) {
			if (ni != 8 || c != '.') return FR_INVALID_NAME;
			i = 8; ni = 11;
			b <<= 2; continue;
		}
		if (c >= 0x80) {				/* Extended char */
#ifdef _EXCVT
			c = cvt[c - 0x80];			/* Convert extend char (SBCS) */
#else
			b |= 3;						/* Eliminate NT flag if ext char is exist */
#if !_DF1S	/* ASCII only cfg */
			return FR_INVALID_NAME;
#endif
#endif
		}
		if (IsDBCS1(c)) {				/* DBC 1st byte? */
			d = p[si++];				/* Get 2nd byte */
			if (!IsDBCS2(d) || i >= ni - 1)	/* Reject invalid DBC */
				return FR_INVALID_NAME;
			sfn[i++] = c;
			sfn[i++] = d;
		} else {						/* Single byte code */
			if (chk_chr(" \"*+,[=]|\x7F", c))	/* Reject illegal chrs for SFN */
				return FR_INVALID_NAME;
			if (IsUpper(c)) {			/* ASCII large capital? */
				b |= 2;
			} else {
				if (IsLower(c)) {		/* ASCII small capital? */
					b |= 1; c -= 0x20;
				}
			}
			sfn[i++] = c;
		}
	}
	*path = &p[si];						/* Rerurn pointer to the next segment */
	c = (c <= ' ') ? NS_LAST : 0;		/* Set last segment flag if end of path */

	if (!i) return FR_INVALID_NAME;		/* Reject null string */
	if (sfn[0] == 0xE5) sfn[0] = 0x05;	/* When first char collides with 0xE5, replace it with 0x05 */

	if (ni == 8) b <<= 2;
	if ((b & 0x03) == 0x01) c |= NS_EXT;	/* NT flag (Extension has only small capital) */
	if ((b & 0x0C) == 0x04) c |= NS_BODY;	/* NT flag (Filename has only small capital) */

	sfn[NS] = c;		/* Store NT flag, File name is created */

	return FR_OK;
#endif
}




/*-----------------------------------------------------------------------*/
/* Get file information from directory entry                             */
/*-----------------------------------------------------------------------*/
#if _FS_MINIMIZE <= 1
static
void get_fileinfo (		/* No return code */
	DIR *dj,			/* Pointer to the directory object */
	FILINFO *fno	 	/* Pointer to the file information to be filled */
)
{
	int i;
	BYTE c, nt, *dir;
	char *p;


	p = fno->fname;
	if (dj->sect) {
		dir = dj->dir;
		nt = dir[DIR_NTres];		/* NT flag */
		for (i = 0; i < 8; i++) {	/* Copy name body */
			c = dir[i];
			if (c == ' ') break;
			if (c == 0x05) c = 0xE5;
			if (_USE_LFN && (nt & NS_BODY) && IsUpper(c)) c += 0x20;
			*p++ = c;
		}
		if (dir[8] != ' ') {		/* Copy name extension */
			*p++ = '.';
			for (i = 8; i < 11; i++) {
				c = dir[i];
				if (c == ' ') break;
				if (_USE_LFN && (nt & NS_EXT) && IsUpper(c)) c += 0x20;
				*p++ = c;
			}
		}
		fno->fattrib = dir[DIR_Attr];				/* Attribute */
		fno->fsize = LD_DWORD(dir+DIR_FileSize);	/* Size */
		fno->fdate = LD_WORD(dir+DIR_WrtDate);		/* Date */
		fno->ftime = LD_WORD(dir+DIR_WrtTime);		/* Time */
	}
	*p = 0;

#if _USE_LFN
	if (fno->lfname) {
		XCHAR *tp = fno->lfname;
		WCHAR w, *lfn;

		i = 0;
		if (dj->sect && dj->lfn_idx != 0xFFFF) {/* Get LFN if available */
			lfn = dj->lfn;
			while ((w = *lfn++) != 0) {			/* Get an LFN char */
#if !_LFN_UNICODE
				w = ff_convert(w, 0);			/* Unicode -> OEM conversion */
				if (!w) { i = 0; break; }		/* Could not convert, no LFN */
				if (_DF1S && w >= 0x100)		/* Put 1st byte if it is a DBC */
					tp[i++] = (XCHAR)(w >> 8);
#endif
				if (i >= fno->lfsize - 1) { i = 0; break; }	/* Buffer overrun, no LFN */
				tp[i++] = (XCHAR)w;
			}
		}
		tp[i] = 0;	/* Terminator */
	}
#endif
}
#endif /* _FS_MINIMIZE <= 1 */




/*-----------------------------------------------------------------------*/
/* Follow a file path                                                    */
/*-----------------------------------------------------------------------*/

static
FRESULT follow_path (	/* FR_OK(0): successful, !=0: error code */
	DIR *dj,			/* Directory object to return last directory and found object */
	const XCHAR *path	/* Full-path string to find a file or directory */
)
{
	FRESULT res;
	BYTE *dir, last;


	while (!_USE_LFN && *path == ' ') path++;	/* Skip leading spaces */
#if _FS_RPATH
	if (*path == '/' || *path == '\\') { /* There is a heading separator */
		path++;	dj->sclust = 0;		/* Strip it and start from the root dir */
	} else {							/* No heading saparator */
		dj->sclust = dj->fs->cdir;	/* Start from the current dir */
	}
#else
	if (*path == '/' || *path == '\\')	/* Strip heading separator if exist */
		path++;
	dj->sclust = 0;						/* Start from the root dir */
#endif

	if ((UINT)*path < ' ') {			/* Null path means the start directory itself */
		res = dir_seek(dj, 0);
		dj->dir = NULL;

	} else {							/* Follow path */
		for (;;) {
			res = create_name(dj, &path);	/* Get a segment */
			if (res != FR_OK) break;
			res = dir_find(dj);				/* Find it */
			last = *(dj->fn+NS) & NS_LAST;
			if (res != FR_OK) {				/* Could not find the object */
				if (res == FR_NO_FILE && !last)
					res = FR_NO_PATH;
				break;
			}
			if (last) break;				/* Last segment match. Function completed. */
			dir = dj->dir;					/* There is next segment. Follow the sub directory */
			if (!(dir[DIR_Attr] & AM_DIR)) { /* Cannot follow because it is a file */
				res = FR_NO_PATH; break;
			}
			dj->sclust = ((DWORD)LD_WORD(dir+DIR_FstClusHI) << 16) | LD_WORD(dir+DIR_FstClusLO);
		}
	}

	return res;
}




/*-----------------------------------------------------------------------*/
/* Load boot record and check if it is an FAT boot record                */
/*-----------------------------------------------------------------------*/

static
BYTE check_fs (	/* 0:The FAT boot record, 1:Valid boot record but not an FAT, 2:Not a boot record, 3:Error */
	FATFS *fs,	/* File system object */
	DWORD sect	/* Sector# (lba) to check if it is an FAT boot record or not */
)
{
	if (disk_read(fs->drive, fs->win, sect, 1) != RES_OK)	/* Load boot record */
		return 3;
	if (LD_WORD(&fs->win[BS_55AA]) != 0xAA55)		/* Check record signature (always placed at offset 510 even if the sector size is >512) */
		return 2;

	if ((LD_DWORD(&fs->win[BS_FilSysType]) & 0xFFFFFF) == 0x544146)	/* Check "FAT" string */
		return 0;
	if ((LD_DWORD(&fs->win[BS_FilSysType32]) & 0xFFFFFF) == 0x544146)
		return 0;

	return 1;
}




/*-----------------------------------------------------------------------*/
/* Make sure that the file system is valid                               */
/*-----------------------------------------------------------------------*/


FRESULT chk_mounted (	/* FR_OK(0): successful, !=0: any error occured */
	const XCHAR **path,	/* Pointer to pointer to the path name (drive number) */
	FATFS **rfs,		/* Pointer to pointer to the found file system object */
	BYTE chk_wp			/* !=0: Check media write protection for write access */
)
{
	BYTE fmt, *tbl;
	UINT vol;
	DSTATUS stat;
	DWORD bsect, fsize, tsect, mclst;
	const XCHAR *p = *path;
	FATFS *fs;

	/* Get logical drive number from the path name */
	vol = p[0] - '0';				/* Is there a drive number? */
	if (vol <= 9 && p[1] == ':') {	/* Found a drive number, get and strip it */
		p += 2; *path = p;			/* Return pointer to the path name */
	} else {						/* No drive number is given */
#if _FS_RPATH
		vol = Drive;				/* Use current drive */
#else
		vol = 0;					/* Use drive 0 */
#endif
	}

	/* Check if the logical drive is valid or not */
	if (vol >= _DRIVES) 			/* Is the drive number valid? */
		return FR_INVALID_DRIVE;
	*rfs = fs = FatFs[vol];			/* Returen pointer to the corresponding file system object */
	if (!fs) return FR_NOT_ENABLED;	/* Is the file system object available? */

	ENTER_FF(fs);					/* Lock file system */

	if (fs->fs_type) {				/* If the logical drive has been mounted */
		stat = disk_status(fs->drive);
		if (!(stat & STA_NOINIT)) {	/* and the physical drive is kept initialized (has not been changed), */
#if !_FS_READONLY
			if (chk_wp && (stat & STA_PROTECT))	/* Check write protection if needed */
				return FR_WRITE_PROTECTED;
#endif
			return FR_OK;			/* The file system object is valid */
		}
	}

	/* The logical drive must be mounted. Following code attempts to mount the volume */

	fs->fs_type = 0;					/* Clear the file system object */
	fs->drive = (BYTE)LD2PD(vol);		/* Bind the logical drive and a physical drive */
	stat = disk_initialize(fs->drive);	/* Initialize low level disk I/O layer */
	if (stat & STA_NOINIT)				/* Check if the drive is ready */
		return FR_NOT_READY;
#if _MAX_SS != 512						/* Get disk sector size if needed */
	if (disk_ioctl(fs->drive, GET_SECTOR_SIZE, &SS(fs)) != RES_OK || SS(fs) > _MAX_SS)
		return FR_NO_FILESYSTEM;
#endif
#if !_FS_READONLY
	if (chk_wp && (stat & STA_PROTECT))	/* Check disk write protection if needed */
		return FR_WRITE_PROTECTED;
#endif
	/* Search FAT partition on the drive */
	fmt = check_fs(fs, bsect = 0);		/* Check sector 0 as an SFD format */
	if (fmt == 1) {						/* Not an FAT boot record, it may be patitioned */
		/* Check a partition listed in top of the partition table */
		tbl = &fs->win[MBR_Table + LD2PT(vol) * 16];	/* Partition table */
		if (tbl[4]) {									/* Is the partition existing? */
			bsect = LD_DWORD(&tbl[8]);					/* Partition offset in LBA */
			fmt = check_fs(fs, bsect);					/* Check the partition */
		}
	}
	if (fmt == 3) return FR_DISK_ERR;
	if (fmt || LD_WORD(fs->win+BPB_BytsPerSec) != SS(fs))	/* No valid FAT patition is found */
		return FR_NO_FILESYSTEM;

	/* Initialize the file system object */
	fsize = LD_WORD(fs->win+BPB_FATSz16);				/* Number of sectors per FAT */
	if (!fsize) fsize = LD_DWORD(fs->win+BPB_FATSz32);
	fs->sects_fat = fsize;
	fs->n_fats = fs->win[BPB_NumFATs];					/* Number of FAT copies */
	fsize *= fs->n_fats;								/* (Number of sectors in FAT area) */
	fs->fatbase = bsect + LD_WORD(fs->win+BPB_RsvdSecCnt); /* FAT start sector (lba) */
	fs->csize = fs->win[BPB_SecPerClus];				/* Number of sectors per cluster */
	fs->n_rootdir = LD_WORD(fs->win+BPB_RootEntCnt);	/* Nmuber of root directory entries */
	tsect = LD_WORD(fs->win+BPB_TotSec16);				/* Number of sectors on the volume */
	if (!tsect) tsect = LD_DWORD(fs->win+BPB_TotSec32);
	fs->max_clust = mclst = (tsect						/* Last cluster# + 1 (Number of clusters + 2) */
		- LD_WORD(fs->win+BPB_RsvdSecCnt) - fsize - fs->n_rootdir / (SS(fs)/32)
		) / fs->csize + 2;

	fmt = FS_FAT12;										/* Determine the FAT sub type */
	if (mclst >= 0xFF7) fmt = FS_FAT16;					/* Number of clusters >= 0xFF5 */
	if (mclst >= 0xFFF7) fmt = FS_FAT32;				/* Number of clusters >= 0xFFF5 */

	if (fmt == FS_FAT32)
		fs->dirbase = LD_DWORD(fs->win+BPB_RootClus);	/* Root directory start cluster */
	else
		fs->dirbase = fs->fatbase + fsize;				/* Root directory start sector (lba) */
	fs->database = fs->fatbase + fsize + fs->n_rootdir / (SS(fs)/32);	/* Data start sector (lba) */

#if !_FS_READONLY
	/* Initialize allocation information */
	fs->free_clust = 0xFFFFFFFF;
	fs->wflag = 0;
	/* Get fsinfo if needed */
	if (fmt == FS_FAT32) {
	 	fs->fsi_flag = 0;
		fs->fsi_sector = bsect + LD_WORD(fs->win+BPB_FSInfo);
		if (disk_read(fs->drive, fs->win, fs->fsi_sector, 1) == RES_OK &&
			LD_WORD(fs->win+BS_55AA) == 0xAA55 &&
			LD_DWORD(fs->win+FSI_LeadSig) == 0x41615252 &&
			LD_DWORD(fs->win+FSI_StrucSig) == 0x61417272) {
			fs->last_clust = LD_DWORD(fs->win+FSI_Nxt_Free);
			fs->free_clust = LD_DWORD(fs->win+FSI_Free_Count);
		}
	}
#endif
	fs->fs_type = fmt;		/* FAT sub-type */
	fs->winsect = 0;		/* Invalidate sector cache */
#if _FS_RPATH
	fs->cdir = 0;			/* Current directory (root dir) */
#endif
	fs->id = ++Fsid;		/* File system mount ID */

	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Check if the file/dir object is valid or not                          */
/*-----------------------------------------------------------------------*/

static
FRESULT validate (	/* FR_OK(0): The object is valid, !=0: Invalid */
	FATFS *fs,		/* Pointer to the file system object */
	WORD id			/* Member id of the target object to be checked */
)
{
	if (!fs || !fs->fs_type || fs->id != id)
		return FR_INVALID_OBJECT;

	ENTER_FF(fs);		/* Lock file system */

	if (disk_status(fs->drive) & STA_NOINIT)
		return FR_NOT_READY;

	return FR_OK;
}




/*--------------------------------------------------------------------------

   Public Functions

--------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*/
/* Mount/Unmount a Locical Drive                                         */
/*-----------------------------------------------------------------------*/

FRESULT f_mount (
	BYTE vol,		/* Logical drive number to be mounted/unmounted */
	FATFS *fs		/* Pointer to new file system object (NULL for unmount)*/
)
{
	FATFS *rfs;


	if (vol >= _DRIVES)				/* Check if the drive number is valid */
		return FR_INVALID_DRIVE;
	rfs = FatFs[vol];				/* Get current fs object */

	if (rfs) {
#if _FS_REENTRANT					/* Discard sync object of the current volume */
		if (!ff_del_syncobj(rfs->sobj)) return FR_INT_ERR;
#endif
		rfs->fs_type = 0;			/* Clear old fs object */
	}

	if (fs) {
		fs->fs_type = 0;			/* Clear new fs object */
#if _FS_REENTRANT					/* Create sync object for the new volume */
		if (!ff_cre_syncobj(vol, &fs->sobj)) return FR_INT_ERR;
#endif
	}
	FatFs[vol] = fs;				/* Register new fs object */

	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Open or Create a File                                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_open (
	FIL *fp,			/* Pointer to the blank file object */
	const XCHAR *path,	/* Pointer to the file name */
	BYTE mode			/* Access mode and file open mode flags */
)
{
	FRESULT res;
	DIR dj;
	NAMEBUF(sfn, lfn);
	BYTE *dir;


	fp->fs = NULL;		/* Clear file object */
#if !_FS_READONLY
	mode &= (FA_READ | FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW);
	res = chk_mounted(&path, &dj.fs, (BYTE)(mode & (FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW)));
#else
	mode &= FA_READ;
	res = chk_mounted(&path, &dj.fs, 0);
#endif
	if (res != FR_OK) LEAVE_FF(dj.fs, res);
	INITBUF(dj, sfn, lfn);
	res = follow_path(&dj, path);	/* Follow the file path */

#if !_FS_READONLY
	/* Create or Open a file */
	if (mode & (FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW)) {
		DWORD ps, cl;

		if (res != FR_OK) {			/* No file, create new */
			if (res == FR_NO_FILE)	/* There is no file to open, create a new entry */
				res = dir_register(&dj);
			if (res != FR_OK) LEAVE_FF(dj.fs, res);
			mode |= FA_CREATE_ALWAYS;
			dir = dj.dir;			/* Created entry (SFN entry) */
		}
		else {						/* Any object is already existing */
			if (mode & FA_CREATE_NEW)			/* Cannot create new */
				LEAVE_FF(dj.fs, FR_EXIST);
			dir = dj.dir;
			if (!dir || (dir[DIR_Attr] & (AM_RDO | AM_DIR)))	/* Cannot overwrite it (R/O or DIR) */
				LEAVE_FF(dj.fs, FR_DENIED);
			if (mode & FA_CREATE_ALWAYS) {		/* Resize it to zero on over write mode */
				cl = ((DWORD)LD_WORD(dir+DIR_FstClusHI) << 16) | LD_WORD(dir+DIR_FstClusLO);	/* Get start cluster */
				ST_WORD(dir+DIR_FstClusHI, 0);	/* cluster = 0 */
				ST_WORD(dir+DIR_FstClusLO, 0);
				ST_DWORD(dir+DIR_FileSize, 0);	/* size = 0 */
				dj.fs->wflag = 1;
				ps = dj.fs->winsect;			/* Remove the cluster chain */
				if (cl) {
					res = remove_chain(dj.fs, cl);
					if (res) LEAVE_FF(dj.fs, res);
					dj.fs->last_clust = cl - 1;	/* Reuse the cluster hole */
				}
				res = move_window(dj.fs, ps);
				if (res != FR_OK) LEAVE_FF(dj.fs, res);
			}
		}
		if (mode & FA_CREATE_ALWAYS) {
			dir[DIR_Attr] = 0;					/* Reset attribute */
			ps = get_fattime();
			ST_DWORD(dir+DIR_CrtTime, ps);		/* Created time */
			dj.fs->wflag = 1;
			mode |= FA__WRITTEN;				/* Set file changed flag */
		}
	}
	/* Open an existing file */
	else {
#endif /* !_FS_READONLY */
		if (res != FR_OK) LEAVE_FF(dj.fs, res);	/* Follow failed */
		dir = dj.dir;
		if (!dir || (dir[DIR_Attr] & AM_DIR))	/* It is a directory */
			LEAVE_FF(dj.fs, FR_NO_FILE);
#if !_FS_READONLY
		if ((mode & FA_WRITE) && (dir[DIR_Attr] & AM_RDO)) /* R/O violation */
			LEAVE_FF(dj.fs, FR_DENIED);
	}
	fp->dir_sect = dj.fs->winsect;		/* Pointer to the directory entry */
	fp->dir_ptr = dj.dir;
#endif
	fp->flag = mode;					/* File access mode */
	fp->org_clust =						/* File start cluster */
		((DWORD)LD_WORD(dir+DIR_FstClusHI) << 16) | LD_WORD(dir+DIR_FstClusLO);
	fp->fsize = LD_DWORD(dir+DIR_FileSize);	/* File size */
	fp->fptr = 0; fp->csect = 255;		/* File pointer */
	fp->dsect = 0;
	fp->fs = dj.fs; fp->id = dj.fs->id;	/* Owner file system object of the file */

	LEAVE_FF(dj.fs, FR_OK);
}




/*-----------------------------------------------------------------------*/
/* Read File                                                             */
/*-----------------------------------------------------------------------*/

FRESULT f_read (
	FIL *fp, 		/* Pointer to the file object */
	void *buff,		/* Pointer to data buffer */
	UINT btr,		/* Number of bytes to read */
	UINT *br		/* Pointer to number of bytes read */
)
{
	FRESULT res;
	DWORD clst, sect, remain;
	UINT rcnt, cc;
	BYTE *rbuff = buff;


	*br = 0;	/* Initialize bytes read */

	res = validate(fp->fs, fp->id);					/* Check validity of the object */
	if (res != FR_OK) LEAVE_FF(fp->fs, res);
	if (fp->flag & FA__ERROR)						/* Check abort flag */
		LEAVE_FF(fp->fs, FR_INT_ERR);
	if (!(fp->flag & FA_READ)) 						/* Check access mode */
		LEAVE_FF(fp->fs, FR_DENIED);
	remain = fp->fsize - fp->fptr;
	if (btr > remain) btr = (UINT)remain;			/* Truncate btr by remaining bytes */

	for ( ;  btr;									/* Repeat until all data transferred */
		rbuff += rcnt, fp->fptr += rcnt, *br += rcnt, btr -= rcnt) {
		if ((fp->fptr % SS(fp->fs)) == 0) {			/* On the sector boundary? */
			if (fp->csect >= fp->fs->csize) {		/* On the cluster boundary? */
				clst = (fp->fptr == 0) ?			/* On the top of the file? */
					fp->org_clust : get_fat(fp->fs, fp->curr_clust);
				if (clst <= 1) ABORT(fp->fs, FR_INT_ERR);
				if (clst == 0xFFFFFFFF) ABORT(fp->fs, FR_DISK_ERR);
				fp->curr_clust = clst;				/* Update current cluster */
				fp->csect = 0;						/* Reset sector offset in the cluster */
			}
			sect = clust2sect(fp->fs, fp->curr_clust);	/* Get current sector */
			if (!sect) ABORT(fp->fs, FR_INT_ERR);
			sect += fp->csect;
			cc = btr / SS(fp->fs);					/* When remaining bytes >= sector size, */
			if (cc) {								/* Read maximum contiguous sectors directly */
				if (fp->csect + cc > fp->fs->csize)	/* Clip at cluster boundary */
					cc = fp->fs->csize - fp->csect;
				if (disk_read(fp->fs->drive, rbuff, sect, (BYTE)cc) != RES_OK)
					ABORT(fp->fs, FR_DISK_ERR);
#if !_FS_READONLY && _FS_MINIMIZE <= 2
#if _FS_TINY
				if (fp->fs->wflag && fp->fs->winsect - sect < cc)		/* Replace one of the read sectors with cached data if it contains a dirty sector */
					mem_cpy(rbuff + ((fp->fs->winsect - sect) * SS(fp->fs)), fp->fs->win, SS(fp->fs));
#else
				if ((fp->flag & FA__DIRTY) && fp->dsect - sect < cc)	/* Replace one of the read sectors with cached data if it contains a dirty sector */
					mem_cpy(rbuff + ((fp->dsect - sect) * SS(fp->fs)), fp->buf, SS(fp->fs));
#endif
#endif
				fp->csect += (BYTE)cc;				/* Next sector address in the cluster */
				rcnt = SS(fp->fs) * cc;				/* Number of bytes transferred */
				continue;
			}
#if !_FS_TINY
#if !_FS_READONLY
			if (fp->flag & FA__DIRTY) {			/* Write sector I/O buffer if needed */
				if (disk_write(fp->fs->drive, fp->buf, fp->dsect, 1) != RES_OK)
					ABORT(fp->fs, FR_DISK_ERR);
				fp->flag &= ~FA__DIRTY;
			}
#endif
			if (fp->dsect != sect) {			/* Fill sector buffer with file data */
				if (disk_read(fp->fs->drive, fp->buf, sect, 1) != RES_OK)
					ABORT(fp->fs, FR_DISK_ERR);
			}
#endif
			fp->dsect = sect;
			fp->csect++;							/* Next sector address in the cluster */
		}
		rcnt = SS(fp->fs) - (fp->fptr % SS(fp->fs));	/* Get partial sector data from sector buffer */
		if (rcnt > btr) rcnt = btr;
#if _FS_TINY
		if (move_window(fp->fs, fp->dsect))			/* Move sector window */
			ABORT(fp->fs, FR_DISK_ERR);
		mem_cpy(rbuff, &fp->fs->win[fp->fptr % SS(fp->fs)], rcnt);	/* Pick partial sector */
#else
		mem_cpy(rbuff, &fp->buf[fp->fptr % SS(fp->fs)], rcnt);	/* Pick partial sector */
#endif
	}

	LEAVE_FF(fp->fs, FR_OK);
}




#if !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Write File                                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_write (
	FIL *fp,			/* Pointer to the file object */
	const void *buff,	/* Pointer to the data to be written */
	UINT btw,			/* Number of bytes to write */
	UINT *bw			/* Pointer to number of bytes written */
)
{
	FRESULT res;
	DWORD clst, sect;
	UINT wcnt, cc;
	const BYTE *wbuff = buff;


	*bw = 0;	/* Initialize bytes written */

	res = validate(fp->fs, fp->id);					/* Check validity of the object */
	if (res != FR_OK) LEAVE_FF(fp->fs, res);
	if (fp->flag & FA__ERROR)						/* Check abort flag */
		LEAVE_FF(fp->fs, FR_INT_ERR);
	if (!(fp->flag & FA_WRITE))						/* Check access mode */
		LEAVE_FF(fp->fs, FR_DENIED);
	if (fp->fsize + btw < fp->fsize) btw = 0;		/* File size cannot reach 4GB */

	for ( ;  btw;									/* Repeat until all data transferred */
		wbuff += wcnt, fp->fptr += wcnt, *bw += wcnt, btw -= wcnt) {
		if ((fp->fptr % SS(fp->fs)) == 0) {			/* On the sector boundary? */
			if (fp->csect >= fp->fs->csize) {		/* On the cluster boundary? */
				if (fp->fptr == 0) {				/* On the top of the file? */
					clst = fp->org_clust;			/* Follow from the origin */
					if (clst == 0)					/* When there is no cluster chain, */
						fp->org_clust = clst = create_chain(fp->fs, 0);	/* Create a new cluster chain */
				} else {							/* Middle or end of the file */
					clst = create_chain(fp->fs, fp->curr_clust);			/* Follow or streach cluster chain */
				}
				if (clst == 0) break;				/* Could not allocate a new cluster (disk full) */
				if (clst == 1) ABORT(fp->fs, FR_INT_ERR);
				if (clst == 0xFFFFFFFF) ABORT(fp->fs, FR_DISK_ERR);
				fp->curr_clust = clst;				/* Update current cluster */
				fp->csect = 0;						/* Reset sector address in the cluster */
			}
#if _FS_TINY
			if (fp->fs->winsect == fp->dsect && move_window(fp->fs, 0))	/* Write back data buffer prior to following direct transfer */
				ABORT(fp->fs, FR_DISK_ERR);
#else
			if (fp->flag & FA__DIRTY) {		/* Write back data buffer prior to following direct transfer */
				if (disk_write(fp->fs->drive, fp->buf, fp->dsect, 1) != RES_OK)
					ABORT(fp->fs, FR_DISK_ERR);
				fp->flag &= ~FA__DIRTY;
			}
#endif
			sect = clust2sect(fp->fs, fp->curr_clust);	/* Get current sector */
			if (!sect) ABORT(fp->fs, FR_INT_ERR);
			sect += fp->csect;
			cc = btw / SS(fp->fs);					/* When remaining bytes >= sector size, */
			if (cc) {								/* Write maximum contiguous sectors directly */
				if (fp->csect + cc > fp->fs->csize)	/* Clip at cluster boundary */
					cc = fp->fs->csize - fp->csect;
				if (disk_write(fp->fs->drive, wbuff, sect, (BYTE)cc) != RES_OK)
					ABORT(fp->fs, FR_DISK_ERR);
#if _FS_TINY
				if (fp->fs->winsect - sect < cc) {	/* Refill sector cache if it gets dirty by the direct write */
					mem_cpy(fp->fs->win, wbuff + ((fp->fs->winsect - sect) * SS(fp->fs)), SS(fp->fs));
					fp->fs->wflag = 0;
				}
#else
				if (fp->dsect - sect < cc) {		/* Refill sector cache if it gets dirty by the direct write */
					mem_cpy(fp->buf, wbuff + ((fp->dsect - sect) * SS(fp->fs)), SS(fp->fs));
					fp->flag &= ~FA__DIRTY;
				}
#endif
				fp->csect += (BYTE)cc;				/* Next sector address in the cluster */
				wcnt = SS(fp->fs) * cc;				/* Number of bytes transferred */
				continue;
			}
#if _FS_TINY
			if (fp->fptr >= fp->fsize) {			/* Avoid silly buffer filling at growing edge */
				if (move_window(fp->fs, 0)) ABORT(fp->fs, FR_DISK_ERR);
				fp->fs->winsect = sect;
			}
#else
			if (fp->dsect != sect) {				/* Fill sector buffer with file data */
				if (fp->fptr < fp->fsize &&
					disk_read(fp->fs->drive, fp->buf, sect, 1) != RES_OK)
						ABORT(fp->fs, FR_DISK_ERR);
			}
#endif
			fp->dsect = sect;
			fp->csect++;							/* Next sector address in the cluster */
		}
		wcnt = SS(fp->fs) - (fp->fptr % SS(fp->fs));	/* Put partial sector into file I/O buffer */
		if (wcnt > btw) wcnt = btw;
#if _FS_TINY
		if (move_window(fp->fs, fp->dsect))			/* Move sector window */
			ABORT(fp->fs, FR_DISK_ERR);
		mem_cpy(&fp->fs->win[fp->fptr % SS(fp->fs)], wbuff, wcnt);	/* Fit partial sector */
		fp->fs->wflag = 1;
#else
		mem_cpy(&fp->buf[fp->fptr % SS(fp->fs)], wbuff, wcnt);	/* Fit partial sector */
		fp->flag |= FA__DIRTY;
#endif
	}

	if (fp->fptr > fp->fsize) fp->fsize = fp->fptr;	/* Update file size if needed */
	fp->flag |= FA__WRITTEN;						/* Set file changed flag */

	LEAVE_FF(fp->fs, FR_OK);
}




/*-----------------------------------------------------------------------*/
/* Synchronize the File Object                                           */
/*-----------------------------------------------------------------------*/

FRESULT f_sync (
	FIL *fp		/* Pointer to the file object */
)
{
	FRESULT res;
	DWORD tim;
	BYTE *dir;


	res = validate(fp->fs, fp->id);		/* Check validity of the object */
	if (res == FR_OK) {
		if (fp->flag & FA__WRITTEN) {	/* Has the file been written? */
#if !_FS_TINY	/* Write-back dirty buffer */
			if (fp->flag & FA__DIRTY) {
				if (disk_write(fp->fs->drive, fp->buf, fp->dsect, 1) != RES_OK)
					LEAVE_FF(fp->fs, FR_DISK_ERR);
				fp->flag &= ~FA__DIRTY;
			}
#endif
			/* Update the directory entry */
			res = move_window(fp->fs, fp->dir_sect);
			if (res == FR_OK) {
				dir = fp->dir_ptr;
				dir[DIR_Attr] |= AM_ARC;					/* Set archive bit */
				ST_DWORD(dir+DIR_FileSize, fp->fsize);		/* Update file size */
				ST_WORD(dir+DIR_FstClusLO, fp->org_clust);	/* Update start cluster */
				ST_WORD(dir+DIR_FstClusHI, fp->org_clust >> 16);
				tim = get_fattime();			/* Updated time */
				ST_DWORD(dir+DIR_WrtTime, tim);
				fp->flag &= ~FA__WRITTEN;
				fp->fs->wflag = 1;
				res = sync(fp->fs);
			}
		}
	}

	LEAVE_FF(fp->fs, res);
}

#endif /* !_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Close File                                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_close (
	FIL *fp		/* Pointer to the file object to be closed */
)
{
	FRESULT res;


#if _FS_READONLY
	res = validate(fp->fs, fp->id);
	if (res == FR_OK) fp->fs = NULL;
	LEAVE_FF(fp->fs, res);
#else
	res = f_sync(fp);
	if (res == FR_OK) fp->fs = NULL;
	return res;
#endif
}




/*-----------------------------------------------------------------------*/
/* Change Current Drive/Directory                                        */
/*-----------------------------------------------------------------------*/

#if _FS_RPATH

FRESULT f_chdrive (
	BYTE drv		/* Drive number */
)
{
	if (drv >= _DRIVES) return FR_INVALID_DRIVE;

	Drive = drv;

	return FR_OK;
}




FRESULT f_chdir (
	const XCHAR *path	/* Pointer to the directory path */
)
{
	FRESULT res;
	DIR dj;
	NAMEBUF(sfn, lfn);
	BYTE *dir;


	res = chk_mounted(&path, &dj.fs, 0);
	if (res == FR_OK) {
		INITBUF(dj, sfn, lfn);
		res = follow_path(&dj, path);		/* Follow the file path */
		if (res == FR_OK) {					/* Follow completed */
			dir = dj.dir;					/* Pointer to the entry */
			if (!dir) {
				dj.fs->cdir = 0;			/* No entry (root dir) */
			} else {
				if (dir[DIR_Attr] & AM_DIR)	/* Reached to the dir */
					dj.fs->cdir = ((DWORD)LD_WORD(dir+DIR_FstClusHI) << 16) | LD_WORD(dir+DIR_FstClusLO);
				else
					res = FR_NO_PATH;		/* Could not reach the dir (it is a file) */
			}
		}
		if (res == FR_NO_FILE) res = FR_NO_PATH;
	}

	LEAVE_FF(dj.fs, res);
}

#endif



#if _FS_MINIMIZE <= 2
/*-----------------------------------------------------------------------*/
/* Seek File R/W Pointer                                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_lseek (
	FIL *fp,		/* Pointer to the file object */
	DWORD ofs		/* File pointer from top of file */
)
{
	FRESULT res;
	DWORD clst, bcs, nsect, ifptr;


	res = validate(fp->fs, fp->id);		/* Check validity of the object */
	if (res != FR_OK) LEAVE_FF(fp->fs, res);
	if (fp->flag & FA__ERROR)			/* Check abort flag */
		LEAVE_FF(fp->fs, FR_INT_ERR);
	if (ofs > fp->fsize					/* In read-only mode, clip offset with the file size */
#if !_FS_READONLY
		 && !(fp->flag & FA_WRITE)
#endif
		) ofs = fp->fsize;

	ifptr = fp->fptr;
	fp->fptr = nsect = 0; fp->csect = 255;
	if (ofs > 0) {
		bcs = (DWORD)fp->fs->csize * SS(fp->fs);	/* Cluster size (byte) */
		if (ifptr > 0 &&
			(ofs - 1) / bcs >= (ifptr - 1) / bcs) {	/* When seek to same or following cluster, */
			fp->fptr = (ifptr - 1) & ~(bcs - 1);	/* start from the current cluster */
			ofs -= fp->fptr;
			clst = fp->curr_clust;
		} else {									/* When seek to back cluster, */
			clst = fp->org_clust;					/* start from the first cluster */
#if !_FS_READONLY
			if (clst == 0) {						/* If no cluster chain, create a new chain */
				clst = create_chain(fp->fs, 0);
				if (clst == 1) ABORT(fp->fs, FR_INT_ERR);
				if (clst == 0xFFFFFFFF) ABORT(fp->fs, FR_DISK_ERR);
				fp->org_clust = clst;
			}
#endif
			fp->curr_clust = clst;
		}
		if (clst != 0) {
			while (ofs > bcs) {						/* Cluster following loop */
#if !_FS_READONLY
				if (fp->flag & FA_WRITE) {			/* Check if in write mode or not */
					clst = create_chain(fp->fs, clst);	/* Force streached if in write mode */
					if (clst == 0) {				/* When disk gets full, clip file size */
						ofs = bcs; break;
					}
				} else
#endif
					clst = get_fat(fp->fs, clst);	/* Follow cluster chain if not in write mode */
				if (clst == 0xFFFFFFFF) ABORT(fp->fs, FR_DISK_ERR);
				if (clst <= 1 || clst >= fp->fs->max_clust) ABORT(fp->fs, FR_INT_ERR);
				fp->curr_clust = clst;
				fp->fptr += bcs;
				ofs -= bcs;
			}
			fp->fptr += ofs;
			fp->csect = (BYTE)(ofs / SS(fp->fs));	/* Sector offset in the cluster */
			if (ofs % SS(fp->fs)) {
				nsect = clust2sect(fp->fs, clst);	/* Current sector */
				if (!nsect) ABORT(fp->fs, FR_INT_ERR);
				nsect += fp->csect;
				fp->csect++;
			}
		}
	}
	if (fp->fptr % SS(fp->fs) && nsect != fp->dsect) {
#if !_FS_TINY
#if !_FS_READONLY
		if (fp->flag & FA__DIRTY) {			/* Write-back dirty buffer if needed */
			if (disk_write(fp->fs->drive, fp->buf, fp->dsect, 1) != RES_OK)
				ABORT(fp->fs, FR_DISK_ERR);
			fp->flag &= ~FA__DIRTY;
		}
#endif
		if (disk_read(fp->fs->drive, fp->buf, nsect, 1) != RES_OK)
			ABORT(fp->fs, FR_DISK_ERR);
#endif
		fp->dsect = nsect;
	}
#if !_FS_READONLY
	if (fp->fptr > fp->fsize) {			/* Set changed flag if the file size is extended */
		fp->fsize = fp->fptr;
		fp->flag |= FA__WRITTEN;
	}
#endif

	LEAVE_FF(fp->fs, res);
}




#if _FS_MINIMIZE <= 1
/*-----------------------------------------------------------------------*/
/* Create a Directroy Object                                             */
/*-----------------------------------------------------------------------*/

FRESULT f_opendir (
	DIR *dj,			/* Pointer to directory object to create */
	const XCHAR *path	/* Pointer to the directory path */
)
{
	FRESULT res;
	NAMEBUF(sfn, lfn);
	BYTE *dir;


	res = chk_mounted(&path, &dj->fs, 0);
	if (res == FR_OK) {
		INITBUF((*dj), sfn, lfn);
		res = follow_path(dj, path);			/* Follow the path to the directory */
		if (res == FR_OK) {						/* Follow completed */
			dir = dj->dir;
			if (dir) {							/* It is not the root dir */
				if (dir[DIR_Attr] & AM_DIR) {	/* The object is a directory */
					dj->sclust = ((DWORD)LD_WORD(dir+DIR_FstClusHI) << 16) | LD_WORD(dir+DIR_FstClusLO);
				} else {						/* The object is not a directory */
					res = FR_NO_PATH;
				}
			}
			if (res == FR_OK) {
				dj->id = dj->fs->id;
				res = dir_seek(dj, 0);			/* Rewind dir */
			}
		}
		if (res == FR_NO_FILE) res = FR_NO_PATH;
	}

	LEAVE_FF(dj->fs, res);
}




/*-----------------------------------------------------------------------*/
/* Read Directory Entry in Sequense                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_readdir (
	DIR *dj,			/* Pointer to the open directory object */
	FILINFO *fno		/* Pointer to file information to return */
)
{
	FRESULT res;
	NAMEBUF(sfn, lfn);


	res = validate(dj->fs, dj->id);			/* Check validity of the object */
	if (res == FR_OK) {
		INITBUF((*dj), sfn, lfn);
		if (!fno) {
			res = dir_seek(dj, 0);
		} else {
			res = dir_read(dj);
			if (res == FR_NO_FILE) {
				dj->sect = 0;
				res = FR_OK;
			}
			if (res == FR_OK) {				/* A valid entry is found */
				get_fileinfo(dj, fno);		/* Get the object information */
				res = dir_next(dj, FALSE);	/* Increment index for next */
				if (res == FR_NO_FILE) {
					dj->sect = 0;
					res = FR_OK;
				}
			}
		}
	}

	LEAVE_FF(dj->fs, res);
}



#if _FS_MINIMIZE == 0
/*-----------------------------------------------------------------------*/
/* Get File Status                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_stat (
	const XCHAR *path,	/* Pointer to the file path */
	FILINFO *fno		/* Pointer to file information to return */
)
{
	FRESULT res;
	DIR dj;
	NAMEBUF(sfn, lfn);


	res = chk_mounted(&path, &dj.fs, 0);
	if (res == FR_OK) {
		INITBUF(dj, sfn, lfn);
		res = follow_path(&dj, path);	/* Follow the file path */
		if (res == FR_OK) {				/* Follwo completed */
			if (dj.dir)	/* Found an object */
				get_fileinfo(&dj, fno);
			else		/* It is root dir */
				res = FR_INVALID_NAME;
		}
	}

	LEAVE_FF(dj.fs, res);
}



#if !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Get Number of Free Clusters                                           */
/*-----------------------------------------------------------------------*/

FRESULT f_getfree (
	const XCHAR *path,	/* Pointer to the logical drive number (root dir) */
	DWORD *nclst,		/* Pointer to the variable to return number of free clusters */
	FATFS **fatfs		/* Pointer to pointer to corresponding file system object to return */
)
{
	FRESULT res;
	DWORD n, clst, sect, stat;
	UINT i;
	BYTE fat, *p;


	/* Get drive number */
	res = chk_mounted(&path, fatfs, 0);
	if (res != FR_OK) LEAVE_FF(*fatfs, res);

	/* If number of free cluster is valid, return it without cluster scan. */
	if ((*fatfs)->free_clust <= (*fatfs)->max_clust - 2) {
		*nclst = (*fatfs)->free_clust;
		LEAVE_FF(*fatfs, FR_OK);
	}

	/* Get number of free clusters */
	fat = (*fatfs)->fs_type;
	n = 0;
	if (fat == FS_FAT12) {
		clst = 2;
		do {
			stat = get_fat(*fatfs, clst);
			if (stat == 0xFFFFFFFF) LEAVE_FF(*fatfs, FR_DISK_ERR);
			if (stat == 1) LEAVE_FF(*fatfs, FR_INT_ERR);
			if (stat == 0) n++;
		} while (++clst < (*fatfs)->max_clust);
	} else {
		clst = (*fatfs)->max_clust;
		sect = (*fatfs)->fatbase;
		i = 0; p = 0;
		do {
			if (!i) {
				res = move_window(*fatfs, sect++);
				if (res != FR_OK)
					LEAVE_FF(*fatfs, res);
				p = (*fatfs)->win;
				i = SS(*fatfs);
			}
			if (fat == FS_FAT16) {
				if (LD_WORD(p) == 0) n++;
				p += 2; i -= 2;
			} else {
				if ((LD_DWORD(p) & 0x0FFFFFFF) == 0) n++;
				p += 4; i -= 4;
			}
		} while (--clst);
	}
	(*fatfs)->free_clust = n;
	if (fat == FS_FAT32) (*fatfs)->fsi_flag = 1;
	*nclst = n;

	LEAVE_FF(*fatfs, FR_OK);
}




/*-----------------------------------------------------------------------*/
/* Truncate File                                                         */
/*-----------------------------------------------------------------------*/

FRESULT f_truncate (
	FIL *fp		/* Pointer to the file object */
)
{
	FRESULT res;
	DWORD ncl;


	res = validate(fp->fs, fp->id);		/* Check validity of the object */
	if (res != FR_OK) LEAVE_FF(fp->fs, res);
	if (fp->flag & FA__ERROR)			/* Check abort flag */
		LEAVE_FF(fp->fs, FR_INT_ERR);
	if (!(fp->flag & FA_WRITE))			/* Check access mode */
		LEAVE_FF(fp->fs, FR_DENIED);

	if (fp->fsize > fp->fptr) {
		fp->fsize = fp->fptr;	/* Set file size to current R/W point */
		fp->flag |= FA__WRITTEN;
		if (fp->fptr == 0) {	/* When set file size to zero, remove entire cluster chain */
			res = remove_chain(fp->fs, fp->org_clust);
			fp->org_clust = 0;
		} else {				/* When truncate a part of the file, remove remaining clusters */
			ncl = get_fat(fp->fs, fp->curr_clust);
			res = FR_OK;
			if (ncl == 0xFFFFFFFF) res = FR_DISK_ERR;
			if (ncl == 1) res = FR_INT_ERR;
			if (res == FR_OK && ncl < fp->fs->max_clust) {
				res = put_fat(fp->fs, fp->curr_clust, 0x0FFFFFFF);
				if (res == FR_OK) res = remove_chain(fp->fs, ncl);
			}
		}
	}
	if (res != FR_OK) fp->flag |= FA__ERROR;

	LEAVE_FF(fp->fs, res);
}




/*-----------------------------------------------------------------------*/
/* Delete a File or Directory                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_unlink (
	const XCHAR *path		/* Pointer to the file or directory path */
)
{
	FRESULT res;
	DIR dj, sdj;
	NAMEBUF(sfn, lfn);
	BYTE *dir;
	DWORD dclst;


	res = chk_mounted(&path, &dj.fs, 1);
	if (res != FR_OK) LEAVE_FF(dj.fs, res);

	INITBUF(dj, sfn, lfn);
	res = follow_path(&dj, path);			/* Follow the file path */
	if (_FS_RPATH && res == FR_OK && (dj.fn[NS] & NS_DOT))
		res = FR_INVALID_NAME;
	if (res != FR_OK) LEAVE_FF(dj.fs, res); /* Follow failed */

	dir = dj.dir;
	if (!dir)								/* Is it the root directory? */
		LEAVE_FF(dj.fs, FR_INVALID_NAME);
	if (dir[DIR_Attr] & AM_RDO)				/* Is it a R/O object? */
		LEAVE_FF(dj.fs, FR_DENIED);
	dclst = ((DWORD)LD_WORD(dir+DIR_FstClusHI) << 16) | LD_WORD(dir+DIR_FstClusLO);

	if (dir[DIR_Attr] & AM_DIR) {			/* It is a sub-directory */
		if (dclst < 2) LEAVE_FF(dj.fs, FR_INT_ERR);
		mem_cpy(&sdj, &dj, sizeof(DIR));	/* Check if the sub-dir is empty or not */
		sdj.sclust = dclst;
		res = dir_seek(&sdj, 2);
		if (res != FR_OK) LEAVE_FF(dj.fs, res);
		res = dir_read(&sdj);
		if (res == FR_OK) res = FR_DENIED;	/* Not empty sub-dir */
		if (res != FR_NO_FILE) LEAVE_FF(dj.fs, res);
	}

	res = dir_remove(&dj);					/* Remove directory entry */
	if (res == FR_OK) {
		if (dclst)
			res = remove_chain(dj.fs, dclst);	/* Remove the cluster chain */
		if (res == FR_OK) res = sync(dj.fs);
	}

	LEAVE_FF(dj.fs, res);
}




/*-----------------------------------------------------------------------*/
/* Create a Directory                                                    */
/*-----------------------------------------------------------------------*/

FRESULT f_mkdir (
	const XCHAR *path		/* Pointer to the directory path */
)
{
	FRESULT res;
	DIR dj;
	NAMEBUF(sfn, lfn);
	BYTE *dir, n;
	DWORD dsect, dclst, pclst, tim;


	res = chk_mounted(&path, &dj.fs, 1);
	if (res != FR_OK) LEAVE_FF(dj.fs, res);

	INITBUF(dj, sfn, lfn);
	res = follow_path(&dj, path);			/* Follow the file path */
	if (res == FR_OK) res = FR_EXIST;		/* Any file or directory is already existing */
	if (_FS_RPATH && res == FR_NO_FILE && (dj.fn[NS] & NS_DOT))
		res = FR_INVALID_NAME;
	if (res != FR_NO_FILE)					/* Any error occured */
		LEAVE_FF(dj.fs, res);

	dclst = create_chain(dj.fs, 0);			/* Allocate a new cluster for new directory table */
	res = FR_OK;
	if (dclst == 0) res = FR_DENIED;
	if (dclst == 1) res = FR_INT_ERR;
	if (dclst == 0xFFFFFFFF) res = FR_DISK_ERR;
	if (res == FR_OK)
		res = move_window(dj.fs, 0);
	if (res != FR_OK) LEAVE_FF(dj.fs, res);
	dsect = clust2sect(dj.fs, dclst);

	dir = dj.fs->win;						/* Initialize the new directory table */
	mem_set(dir, 0, SS(dj.fs));
	mem_set(dir+DIR_Name, ' ', 8+3);		/* Create "." entry */
	dir[DIR_Name] = '.';
	dir[DIR_Attr] = AM_DIR;
	tim = get_fattime();
	ST_DWORD(dir+DIR_WrtTime, tim);
	ST_WORD(dir+DIR_FstClusLO, dclst);
	ST_WORD(dir+DIR_FstClusHI, dclst >> 16);
	mem_cpy(dir+32, dir, 32); 			/* Create ".." entry */
	dir[33] = '.';
	pclst = dj.sclust;
	if (dj.fs->fs_type == FS_FAT32 && pclst == dj.fs->dirbase)
		pclst = 0;
	ST_WORD(dir+32+DIR_FstClusLO, pclst);
	ST_WORD(dir+32+DIR_FstClusHI, pclst >> 16);
	for (n = 0; n < dj.fs->csize; n++) {	/* Write dot entries and clear left sectors */
		dj.fs->winsect = dsect++;
		dj.fs->wflag = 1;
		res = move_window(dj.fs, 0);
		if (res) LEAVE_FF(dj.fs, res);
		mem_set(dir, 0, SS(dj.fs));
	}

	res = dir_register(&dj);
	if (res != FR_OK) {
		remove_chain(dj.fs, dclst);
	} else {
		dir = dj.dir;
		dir[DIR_Attr] = AM_DIR;					/* Attribute */
		ST_DWORD(dir+DIR_WrtTime, tim);			/* Crated time */
		ST_WORD(dir+DIR_FstClusLO, dclst);		/* Table start cluster */
		ST_WORD(dir+DIR_FstClusHI, dclst >> 16);
		dj.fs->wflag = 1;
		res = sync(dj.fs);
	}

	LEAVE_FF(dj.fs, res);
}




/*-----------------------------------------------------------------------*/
/* Change File Attribute                                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_chmod (
	const XCHAR *path,	/* Pointer to the file path */
	BYTE value,			/* Attribute bits */
	BYTE mask			/* Attribute mask to change */
)
{
	FRESULT res;
	DIR dj;
	NAMEBUF(sfn, lfn);
	BYTE *dir;


	res = chk_mounted(&path, &dj.fs, 1);
	if (res == FR_OK) {
		INITBUF(dj, sfn, lfn);
		res = follow_path(&dj, path);		/* Follow the file path */
		if (_FS_RPATH && res == FR_OK && (dj.fn[NS] & NS_DOT))
			res = FR_INVALID_NAME;
		if (res == FR_OK) {
			dir = dj.dir;
			if (!dir) {						/* Is it a root directory? */
				res = FR_INVALID_NAME;
			} else {						/* File or sub directory */
				mask &= AM_RDO|AM_HID|AM_SYS|AM_ARC;	/* Valid attribute mask */
				dir[DIR_Attr] = (value & mask) | (dir[DIR_Attr] & (BYTE)~mask);	/* Apply attribute change */
				dj.fs->wflag = 1;
				res = sync(dj.fs);
			}
		}
	}

	LEAVE_FF(dj.fs, res);
}




/*-----------------------------------------------------------------------*/
/* Change Timestamp                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_utime (
	const XCHAR *path,	/* Pointer to the file/directory name */
	const FILINFO *fno	/* Pointer to the timestamp to be set */
)
{
	FRESULT res;
	DIR dj;
	NAMEBUF(sfn, lfn);
	BYTE *dir;


	res = chk_mounted(&path, &dj.fs, 1);
	if (res == FR_OK) {
		INITBUF(dj, sfn, lfn);
		res = follow_path(&dj, path);	/* Follow the file path */
		if (_FS_RPATH && res == FR_OK && (dj.fn[NS] & NS_DOT))
			res = FR_INVALID_NAME;
		if (res == FR_OK) {
			dir = dj.dir;
			if (!dir) {				/* Root directory */
				res = FR_INVALID_NAME;
			} else {				/* File or sub-directory */
				ST_WORD(dir+DIR_WrtTime, fno->ftime);
				ST_WORD(dir+DIR_WrtDate, fno->fdate);
				dj.fs->wflag = 1;
				res = sync(dj.fs);
			}
		}
	}

	LEAVE_FF(dj.fs, res);
}




/*-----------------------------------------------------------------------*/
/* Rename File/Directory                                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_rename (
	const XCHAR *path_old,	/* Pointer to the old name */
	const XCHAR *path_new	/* Pointer to the new name */
)
{
	FRESULT res;
	DIR dj_old, dj_new;
	NAMEBUF(sfn, lfn);
	BYTE buf[21], *dir;
	DWORD dw;


	INITBUF(dj_old, sfn, lfn);
	res = chk_mounted(&path_old, &dj_old.fs, 1);
	if (res == FR_OK) {
		dj_new.fs = dj_old.fs;
		res = follow_path(&dj_old, path_old);	/* Check old object */
		if (_FS_RPATH && res == FR_OK && (dj_old.fn[NS] & NS_DOT))
			res = FR_INVALID_NAME;
	}
	if (res != FR_OK) LEAVE_FF(dj_old.fs, res);	/* The old object is not found */

	if (!dj_old.dir) LEAVE_FF(dj_old.fs, FR_NO_FILE);	/* Is root dir? */
	mem_cpy(buf, dj_old.dir+DIR_Attr, 21);		/* Save the object information */

	mem_cpy(&dj_new, &dj_old, sizeof(DIR));
	res = follow_path(&dj_new, path_new);		/* Check new object */
	if (res == FR_OK) res = FR_EXIST;			/* The new object name is already existing */
	if (res == FR_NO_FILE) { 					/* Is it a valid path and no name collision? */
		res = dir_register(&dj_new);			/* Register the new object */
		if (res == FR_OK) {
			dir = dj_new.dir;					/* Copy object information into new entry */
			mem_cpy(dir+13, buf+2, 19);
			dir[DIR_Attr] = buf[0] | AM_ARC;
			dj_old.fs->wflag = 1;
			if (dir[DIR_Attr] & AM_DIR) {		/* Update .. entry in the directory if needed */
				dw = clust2sect(dj_new.fs, (DWORD)LD_WORD(dir+DIR_FstClusHI) | LD_WORD(dir+DIR_FstClusLO));
				if (!dw) {
					res = FR_INT_ERR;
				} else {
					res = move_window(dj_new.fs, dw);
					dir = dj_new.fs->win+32;
					if (res == FR_OK && dir[1] == '.') {
						dw = (dj_new.fs->fs_type == FS_FAT32 && dj_new.sclust == dj_new.fs->dirbase) ? 0 : dj_new.sclust;
						ST_WORD(dir+DIR_FstClusLO, dw);
						ST_WORD(dir+DIR_FstClusHI, dw >> 16);
						dj_new.fs->wflag = 1;
					}
				}
			}
			if (res == FR_OK) {
				res = dir_remove(&dj_old);			/* Remove old entry */
				if (res == FR_OK)
					res = sync(dj_old.fs);
			}
		}
	}

	LEAVE_FF(dj_old.fs, res);
}

#endif /* !_FS_READONLY */
#endif /* _FS_MINIMIZE == 0 */
#endif /* _FS_MINIMIZE <= 1 */
#endif /* _FS_MINIMIZE <= 2 */



/*-----------------------------------------------------------------------*/
/* Forward data to the stream directly (Available on only _FS_TINY cfg)  */
/*-----------------------------------------------------------------------*/
#if _USE_FORWARD && _FS_TINY

FRESULT f_forward (
	FIL *fp, 						/* Pointer to the file object */
	UINT (*func)(const BYTE*,UINT),	/* Pointer to the streaming function */
	UINT btr,						/* Number of bytes to forward */
	UINT *bf						/* Pointer to number of bytes forwarded */
)
{
	FRESULT res;
	DWORD remain, clst, sect;
	UINT rcnt;


	*bf = 0;

	res = validate(fp->fs, fp->id);					/* Check validity of the object */
	if (res != FR_OK) LEAVE_FF(fp->fs, res);
	if (fp->flag & FA__ERROR)						/* Check error flag */
		LEAVE_FF(fp->fs, FR_INT_ERR);
	if (!(fp->flag & FA_READ))						/* Check access mode */
		LEAVE_FF(fp->fs, FR_DENIED);

	remain = fp->fsize - fp->fptr;
	if (btr > remain) btr = (UINT)remain;			/* Truncate btr by remaining bytes */

	for ( ;  btr && (*func)(NULL, 0);				/* Repeat until all data transferred or stream becomes busy */
		fp->fptr += rcnt, *bf += rcnt, btr -= rcnt) {
		if ((fp->fptr % SS(fp->fs)) == 0) {			/* On the sector boundary? */
			if (fp->csect >= fp->fs->csize) {		/* On the cluster boundary? */
				clst = (fp->fptr == 0) ?			/* On the top of the file? */
					fp->org_clust : get_fat(fp->fs, fp->curr_clust);
				if (clst <= 1) ABORT(fp->fs, FR_INT_ERR);
				if (clst == 0xFFFFFFFF) ABORT(fp->fs, FR_DISK_ERR);
				fp->curr_clust = clst;				/* Update current cluster */
				fp->csect = 0;						/* Reset sector address in the cluster */
			}
			fp->csect++;							/* Next sector address in the cluster */
		}
		sect = clust2sect(fp->fs, fp->curr_clust);	/* Get current data sector */
		if (!sect) ABORT(fp->fs, FR_INT_ERR);
		sect += fp->csect - 1;
		if (move_window(fp->fs, sect))				/* Move sector window */
			ABORT(fp->fs, FR_DISK_ERR);
		fp->dsect = sect;
		rcnt = SS(fp->fs) - (WORD)(fp->fptr % SS(fp->fs));	/* Forward data from sector window */
		if (rcnt > btr) rcnt = btr;
		rcnt = (*func)(&fp->fs->win[(WORD)fp->fptr % SS(fp->fs)], rcnt);
		if (!rcnt) ABORT(fp->fs, FR_INT_ERR);
	}

	LEAVE_FF(fp->fs, FR_OK);
}
#endif /* _USE_FORWARD */



#if _USE_MKFS && !_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Create File System on the Drive                                       */
/*-----------------------------------------------------------------------*/
#define N_ROOTDIR	512			/* Multiple of 32 and <= 2048 */
#define N_FATS		1			/* 1 or 2 */
#define MAX_SECTOR	131072000UL	/* Maximum partition size */
#define MIN_SECTOR	2000UL		/* Minimum partition size */


FRESULT f_mkfs (
	BYTE drv,			/* Logical drive number */
	BYTE partition,		/* Partitioning rule 0:FDISK, 1:SFD */
	WORD allocsize		/* Allocation unit size [bytes] */
)
{
	static const DWORD sstbl[] = { 2048000, 1024000, 512000, 256000, 128000, 64000, 32000, 16000, 8000, 4000,   0 };
	static const WORD cstbl[] =  {   32768,   16384,   8192,   4096,   2048, 16384,  8192,  4096, 2048, 1024, 512 };
	BYTE fmt, m, *tbl;
	DWORD b_part, b_fat, b_dir, b_data;		/* Area offset (LBA) */
	DWORD n_part, n_rsv, n_fat, n_dir;		/* Area size */
	DWORD n_clst, d, n;
	WORD as;
	FATFS *fs;
	DSTATUS stat;


	/* Check validity of the parameters */
	if (drv >= _DRIVES) return FR_INVALID_DRIVE;
	if (partition >= 2) return FR_MKFS_ABORTED;

	/* Check mounted drive and clear work area */
	fs = FatFs[drv];
	if (!fs) return FR_NOT_ENABLED;
	fs->fs_type = 0;
	drv = LD2PD(drv);

	/* Get disk statics */
	stat = disk_initialize(drv);
	if (stat & STA_NOINIT) return FR_NOT_READY;
	if (stat & STA_PROTECT) return FR_WRITE_PROTECTED;
#if _MAX_SS != 512						/* Get disk sector size */
	if (disk_ioctl(drv, GET_SECTOR_SIZE, &SS(fs)) != RES_OK
		|| SS(fs) > _MAX_SS)
		return FR_MKFS_ABORTED;
#endif
	if (disk_ioctl(drv, GET_SECTOR_COUNT, &n_part) != RES_OK || n_part < MIN_SECTOR)
		return FR_MKFS_ABORTED;
	if (n_part > MAX_SECTOR) n_part = MAX_SECTOR;
	b_part = (!partition) ? 63 : 0;		/* Boot sector */
	n_part -= b_part;
	for (d = 512; d <= 32768U && d != allocsize; d <<= 1) ;	/* Check validity of the allocation unit size */
	if (d != allocsize) allocsize = 0;
	if (!allocsize) {					/* Auto selection of cluster size */
		d = n_part;
		for (as = SS(fs); as > 512U; as >>= 1) d >>= 1;
		for (n = 0; d < sstbl[n]; n++) ;
		allocsize = cstbl[n];
	}
	if (allocsize < SS(fs)) allocsize = SS(fs);

	allocsize /= SS(fs);		/* Number of sectors per cluster */

	/* Pre-compute number of clusters and FAT type */
	n_clst = n_part / allocsize;
	fmt = FS_FAT12;
	if (n_clst >= 0xFF5) fmt = FS_FAT16;
	if (n_clst >= 0xFFF5) fmt = FS_FAT32;

	/* Determine offset and size of FAT structure */
	switch (fmt) {
	case FS_FAT12:
		n_fat = ((n_clst * 3 + 1) / 2 + 3 + SS(fs) - 1) / SS(fs);
		n_rsv = 1 + partition;
		n_dir = N_ROOTDIR * 32 / SS(fs);
		break;
	case FS_FAT16:
		n_fat = ((n_clst * 2) + 4 + SS(fs) - 1) / SS(fs);
		n_rsv = 1 + partition;
		n_dir = N_ROOTDIR * 32 / SS(fs);
		break;
	default:
		n_fat = ((n_clst * 4) + 8 + SS(fs) - 1) / SS(fs);
		n_rsv = 33 - partition;
		n_dir = 0;
	}
	b_fat = b_part + n_rsv;			/* FATs start sector */
	b_dir = b_fat + n_fat * N_FATS;	/* Directory start sector */
	b_data = b_dir + n_dir;			/* Data start sector */

	/* Align data start sector to erase block boundary (for flash memory media) */
	if (disk_ioctl(drv, GET_BLOCK_SIZE, &n) != RES_OK) return FR_MKFS_ABORTED;
	n = (b_data + n - 1) & ~(n - 1);
	n_fat += (n - b_data) / N_FATS;
	/* b_dir and b_data are no longer used below */

	/* Determine number of cluster and final check of validity of the FAT type */
	n_clst = (n_part - n_rsv - n_fat * N_FATS - n_dir) / allocsize;
	if (   (fmt == FS_FAT16 && n_clst < 0xFF5)
		|| (fmt == FS_FAT32 && n_clst < 0xFFF5))
		return FR_MKFS_ABORTED;

	/* Create partition table if needed */
	if (!partition) {
		DWORD n_disk = b_part + n_part;

		mem_set(fs->win, 0, SS(fs));
		tbl = fs->win+MBR_Table;
		ST_DWORD(tbl, 0x00010180);		/* Partition start in CHS */
		if (n_disk < 63UL * 255 * 1024) {	/* Partition end in CHS */
			n_disk = n_disk / 63 / 255;
			tbl[7] = (BYTE)n_disk;
			tbl[6] = (BYTE)((n_disk >> 2) | 63);
		} else {
			ST_WORD(&tbl[6], 0xFFFF);
		}
		tbl[5] = 254;
		if (fmt != FS_FAT32)			/* System ID */
			tbl[4] = (n_part < 0x10000) ? 0x04 : 0x06;
		else
			tbl[4] = 0x0c;
		ST_DWORD(tbl+8, 63);			/* Partition start in LBA */
		ST_DWORD(tbl+12, n_part);		/* Partition size in LBA */
		ST_WORD(tbl+64, 0xAA55);		/* Signature */
		if (disk_write(drv, fs->win, 0, 1) != RES_OK)
			return FR_DISK_ERR;
		partition = 0xF8;
	} else {
		partition = 0xF0;
	}

	/* Create boot record */
	tbl = fs->win;								/* Clear buffer */
	mem_set(tbl, 0, SS(fs));
	ST_DWORD(tbl+BS_jmpBoot, 0x90FEEB);			/* Boot code (jmp $, nop) */
	ST_WORD(tbl+BPB_BytsPerSec, SS(fs));		/* Sector size */
	tbl[BPB_SecPerClus] = (BYTE)allocsize;		/* Sectors per cluster */
	ST_WORD(tbl+BPB_RsvdSecCnt, n_rsv);			/* Reserved sectors */
	tbl[BPB_NumFATs] = N_FATS;					/* Number of FATs */
	ST_WORD(tbl+BPB_RootEntCnt, SS(fs) / 32 * n_dir); /* Number of rootdir entries */
	if (n_part < 0x10000) {						/* Number of total sectors */
		ST_WORD(tbl+BPB_TotSec16, n_part);
	} else {
		ST_DWORD(tbl+BPB_TotSec32, n_part);
	}
	tbl[BPB_Media] = partition;					/* Media descripter */
	ST_WORD(tbl+BPB_SecPerTrk, 63);				/* Number of sectors per track */
	ST_WORD(tbl+BPB_NumHeads, 255);				/* Number of heads */
	ST_DWORD(tbl+BPB_HiddSec, b_part);			/* Hidden sectors */
	n = get_fattime();							/* Use current time as a VSN */
	if (fmt != FS_FAT32) {
		ST_DWORD(tbl+BS_VolID, n);				/* Volume serial number */
		ST_WORD(tbl+BPB_FATSz16, n_fat);		/* Number of secters per FAT */
		tbl[BS_DrvNum] = 0x80;					/* Drive number */
		tbl[BS_BootSig] = 0x29;					/* Extended boot signature */
		mem_cpy(tbl+BS_VolLab, "NO NAME    FAT     ", 19);	/* Volume lavel, FAT signature */
	} else {
		ST_DWORD(tbl+BS_VolID32, n);			/* Volume serial number */
		ST_DWORD(tbl+BPB_FATSz32, n_fat);		/* Number of secters per FAT */
		ST_DWORD(tbl+BPB_RootClus, 2);			/* Root directory cluster (2) */
		ST_WORD(tbl+BPB_FSInfo, 1);				/* FSInfo record offset (bs+1) */
		ST_WORD(tbl+BPB_BkBootSec, 6);			/* Backup boot record offset (bs+6) */
		tbl[BS_DrvNum32] = 0x80;				/* Drive number */
		tbl[BS_BootSig32] = 0x29;				/* Extended boot signature */
		mem_cpy(tbl+BS_VolLab32, "NO NAME    FAT32   ", 19);	/* Volume lavel, FAT signature */
	}
	ST_WORD(tbl+BS_55AA, 0xAA55);				/* Signature */
	if (SS(fs) > 512U) {
		ST_WORD(tbl+SS(fs)-2, 0xAA55);
	}
	if (disk_write(drv, tbl, b_part+0, 1) != RES_OK)
		return FR_DISK_ERR;
	if (fmt == FS_FAT32)
		disk_write(drv, tbl, b_part+6, 1);

	/* Initialize FAT area */
	for (m = 0; m < N_FATS; m++) {
		mem_set(tbl, 0, SS(fs));		/* 1st sector of the FAT  */
		if (fmt != FS_FAT32) {
			n = (fmt == FS_FAT12) ? 0x00FFFF00 : 0xFFFFFF00;
			n |= partition;
			ST_DWORD(tbl, n);				/* Reserve cluster #0-1 (FAT12/16) */
		} else {
			ST_DWORD(tbl+0, 0xFFFFFFF8);	/* Reserve cluster #0-1 (FAT32) */
			ST_DWORD(tbl+4, 0xFFFFFFFF);
			ST_DWORD(tbl+8, 0x0FFFFFFF);	/* Reserve cluster #2 for root dir */
		}
		if (disk_write(drv, tbl, b_fat++, 1) != RES_OK)
			return FR_DISK_ERR;
		mem_set(tbl, 0, SS(fs));		/* Following FAT entries are filled by zero */
		for (n = 1; n < n_fat; n++) {
			if (disk_write(drv, tbl, b_fat++, 1) != RES_OK)
				return FR_DISK_ERR;
		}
	}

	/* Initialize Root directory */
	m = (BYTE)((fmt == FS_FAT32) ? allocsize : n_dir);
	do {
		if (disk_write(drv, tbl, b_fat++, 1) != RES_OK)
			return FR_DISK_ERR;
	} while (--m);

	/* Create FSInfo record if needed */
	if (fmt == FS_FAT32) {
		ST_WORD(tbl+BS_55AA, 0xAA55);
		ST_DWORD(tbl+FSI_LeadSig, 0x41615252);
		ST_DWORD(tbl+FSI_StrucSig, 0x61417272);
		ST_DWORD(tbl+FSI_Free_Count, n_clst - 1);
		ST_DWORD(tbl+FSI_Nxt_Free, 0xFFFFFFFF);
		disk_write(drv, tbl, b_part+1, 1);
		disk_write(drv, tbl, b_part+7, 1);
	}

	return (disk_ioctl(drv, CTRL_SYNC, (void*)NULL) == RES_OK) ? FR_OK : FR_DISK_ERR;
}

#endif /* _USE_MKFS && !_FS_READONLY */




#if _USE_STRFUNC
/*-----------------------------------------------------------------------*/
/* Get a string from the file                                            */
/*-----------------------------------------------------------------------*/
char* f_gets (
	char* buff,	/* Pointer to the string buffer to read */
	int len,	/* Size of string buffer */
	FIL* fil	/* Pointer to the file object */
)
{
	int i = 0;
	char *p = buff;
	UINT rc;


	while (i < len - 1) {			/* Read bytes until buffer gets filled */
		f_read(fil, p, 1, &rc);
		if (rc != 1) break;			/* Break when no data to read */
#if _USE_STRFUNC >= 2
		if (*p == '\r') continue;	/* Strip '\r' */
#endif
		i++;
		if (*p++ == '\n') break;	/* Break when reached end of line */
	}
	*p = 0;
	return i ? buff : NULL;			/* When no data read (eof or error), return with error. */
}



#if !_FS_READONLY
#include <stdarg.h>
/*-----------------------------------------------------------------------*/
/* Put a character to the file                                           */
/*-----------------------------------------------------------------------*/
int f_putc (
	int chr,	/* A character to be output */
	FIL* fil	/* Ponter to the file object */
)
{
	UINT bw;
	char c;


#if _USE_STRFUNC >= 2
	if (chr == '\n') f_putc ('\r', fil);	/* LF -> CRLF conversion */
#endif
	if (!fil) {	/* Special value may be used to switch the destination to any other device */
	/*	put_console(chr);	*/
		return chr;
	}
	c = (char)chr;
	f_write(fil, &c, 1, &bw);	/* Write a byte to the file */
	return bw ? chr : EOF;		/* Return the result */
}




/*-----------------------------------------------------------------------*/
/* Put a string to the file                                              */
/*-----------------------------------------------------------------------*/
int f_puts (
	const char* str,	/* Pointer to the string to be output */
	FIL* fil			/* Pointer to the file object */
)
{
	int n;


	for (n = 0; *str; str++, n++) {
		if (f_putc(*str, fil) == EOF) return EOF;
	}
	return n;
}




/*-----------------------------------------------------------------------*/
/* Put a formatted string to the file                                    */
/*-----------------------------------------------------------------------*/
int f_printf (
	FIL* fil,			/* Pointer to the file object */
	const char* str,	/* Pointer to the format string */
	...					/* Optional arguments... */
)
{
	va_list arp;
	UCHAR c, f, r;
	ULONG val;
	char s[16];
	int i, w, res, cc;


	va_start(arp, str);

	for (cc = res = 0; cc != EOF; res += cc) {
		c = *str++;
		if (c == 0) break;			/* End of string */
		if (c != '%') {				/* Non escape cahracter */
			cc = f_putc(c, fil);
			if (cc != EOF) cc = 1;
			continue;
		}
		w = f = 0;
		c = *str++;
		if (c == '0') {				/* Flag: '0' padding */
			f = 1; c = *str++;
		}
		while (c >= '0' && c <= '9') {	/* Precision */
			w = w * 10 + (c - '0');
			c = *str++;
		}
		if (c == 'l') {				/* Prefix: Size is long int */
			f |= 2; c = *str++;
		}
		if (c == 's') {				/* Type is string */
			cc = f_puts(va_arg(arp, char*), fil);
			continue;
		}
		if (c == 'c') {				/* Type is character */
			cc = f_putc(va_arg(arp, int), fil);
			if (cc != EOF) cc = 1;
			continue;
		}
		r = 0;
		if (c == 'd') r = 10;		/* Type is signed decimal */
		if (c == 'u') r = 10;		/* Type is unsigned decimal */
		if (c == 'X') r = 16;		/* Type is unsigned hexdecimal */
		if (r == 0) break;			/* Unknown type */
		if (f & 2) {				/* Get the value */
			val = (ULONG)va_arg(arp, long);
		} else {
			val = (c == 'd') ? (ULONG)(long)va_arg(arp, int) : (ULONG)va_arg(arp, unsigned int);
		}
		/* Put numeral string */
		if (c == 'd') {
			if (val & 0x80000000) {
				val = 0 - val;
				f |= 4;
			}
		}
		i = sizeof(s) - 1; s[i] = 0;
		do {
			c = (UCHAR)(val % r + '0');
			if (c > '9') c += 7;
			s[--i] = c;
			val /= r;
		} while (i && val);
		if (i && (f & 4)) s[--i] = '-';
		w = sizeof(s) - 1 - w;
		while (i && i > w) s[--i] = (f & 1) ? '0' : ' ';
		cc = f_puts(&s[i], fil);
	}

	va_end(arp);
	return (cc == EOF) ? cc : res;
}

#endif /* !_FS_READONLY */
#endif /* _USE_STRFUNC */
