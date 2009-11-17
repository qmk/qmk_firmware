/*----------------------------------------------------------------------------/
/  Petit FatFs - FAT file system module  R0.01a                (C)ChaN, 2009
/-----------------------------------------------------------------------------/
/ Petit FatFs module is an open source software to implement FAT file system to
/ small embedded systems. This is a free software and is opened for education,
/ research and commercial developments under license policy of following trems.
/
/  Copyright (C) 2009, ChaN, all right reserved.
/
/ * The Petit FatFs module is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial use UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-----------------------------------------------------------------------------/
/ Jun 15,'09 R0.01a  Branched from FatFs R0.07b
/----------------------------------------------------------------------------*/

#include "pff.h"		/* Petit FatFs configurations and declarations */
#include "diskio.h"		/* Declarations of low level disk I/O functions */


/*--------------------------------------------------------------------------

   Private Work Area

---------------------------------------------------------------------------*/

static
FATFS *FatFs;	/* Pointer to the file system object (logical drive) */


/*--------------------------------------------------------------------------

   Private Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* String functions                                                      */
/*-----------------------------------------------------------------------*/

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
/* FAT access - Read value of a FAT entry                                */
/*-----------------------------------------------------------------------*/

static
CLUST get_fat (	/* 1:IO error, Else:Cluster status */
	CLUST clst	/* Cluster# to get the link information */
)
{
	WORD wc, bc, ofs;
	BYTE buf[4];
	FATFS *fs = FatFs;


	if (clst < 2 || clst >= fs->max_clust)	/* Range check */
		return 1;

	switch (fs->fs_type) {
	case FS_FAT12 :
		bc = (WORD)clst; bc += bc / 2;
		ofs = bc % 512; bc /= 512;
		if (ofs != 511) {
			if (disk_readp(buf, fs->fatbase + bc, ofs, 2)) break;
		} else {
			if (disk_readp(buf, fs->fatbase + bc, 511, 1)) break;
			if (disk_readp(buf+1, fs->fatbase + bc + 1, 0, 1)) break;
		}
		wc = LD_WORD(buf);
		return (clst & 1) ? (wc >> 4) : (wc & 0xFFF);

	case FS_FAT16 :
		if (disk_readp(buf, fs->fatbase + clst / 256, (WORD)(((WORD)clst % 256) * 2), 2)) break;
		return LD_WORD(buf);
#if _FS_FAT32
	case FS_FAT32 :
		if (disk_readp(buf, fs->fatbase + clst / 128, (WORD)(((WORD)clst % 128) * 4), 4)) break;
		return LD_DWORD(buf) & 0x0FFFFFFF;
#endif
	}

	return 1;	/* An error occured at the disk I/O layer */
}




/*-----------------------------------------------------------------------*/
/* Get sector# from cluster#                                             */
/*-----------------------------------------------------------------------*/

static
DWORD clust2sect (	/* !=0: Sector number, 0: Failed - invalid cluster# */
	CLUST clst		/* Cluster# to be converted */
)
{
	FATFS *fs = FatFs;


	clst -= 2;
	if (clst >= (fs->max_clust - 2)) return 0;		/* Invalid cluster# */
	return (DWORD)clst * fs->csize + fs->database;
}




/*-----------------------------------------------------------------------*/
/* Directory handling - Rewind directory index                           */
/*-----------------------------------------------------------------------*/

static
FRESULT dir_rewind (
	DIR *dj			/* Pointer to directory object */
)
{
	CLUST clst;
	FATFS *fs = FatFs;


	dj->index = 0;
	clst = dj->sclust;
	if (clst == 1 || clst >= fs->max_clust)	/* Check start cluster range */
		return FR_DISK_ERR;
#if _FS_FAT32
	if (!clst && fs->fs_type == FS_FAT32)	/* Replace cluster# 0 with root cluster# if in FAT32 */
		clst = fs->dirbase;
#endif
	dj->clust = clst;						/* Current cluster */
	dj->sect = clst ? clust2sect(clst) : fs->dirbase;	/* Current sector */

	return FR_OK;	/* Seek succeeded */
}




/*-----------------------------------------------------------------------*/
/* Directory handling - Move directory index next                        */
/*-----------------------------------------------------------------------*/

static
FRESULT dir_next (	/* FR_OK:Succeeded, FR_NO_FILE:End of table, FR_DENIED:EOT and could not streach */
	DIR *dj			/* Pointer to directory object */
)
{
	CLUST clst;
	WORD i;
	FATFS *fs = FatFs;


	i = dj->index + 1;
	if (!i || !dj->sect)	/* Report EOT when index has reached 65535 */
		return FR_NO_FILE;

	if (!(i & (16-1))) {	/* Sector changed? */
		dj->sect++;			/* Next sector */

		if (dj->clust == 0) {	/* Static table */
			if (i >= fs->n_rootdir)	/* Report EOT when end of table */
				return FR_NO_FILE;
		}
		else {					/* Dynamic table */
			if (((i / 16) & (fs->csize-1)) == 0) {	/* Cluster changed? */
				clst = get_fat(dj->clust);		/* Get next cluster */
				if (clst <= 1) return FR_DISK_ERR;
				if (clst >= fs->max_clust)		/* When it reached end of dynamic table */
					return FR_NO_FILE;			/* Report EOT */
				dj->clust = clst;				/* Initialize data for new cluster */
				dj->sect = clust2sect(clst);
			}
		}
	}

	dj->index = i;

	return FR_OK;
}




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


	res = dir_rewind(dj);			/* Rewind directory object */
	if (res != FR_OK) return res;

	dir = FatFs->buf;
	do {
		res = disk_readp(dir, dj->sect, (WORD)((dj->index % 16) * 32), 32)	/* Read an entry */
			? FR_DISK_ERR : FR_OK;
		if (res != FR_OK) break;
		c = dir[DIR_Name];	/* First character */
		if (c == 0) { res = FR_NO_FILE; break; }	/* Reached to end of table */
		if (!(dir[DIR_Attr] & AM_VOL) && !mem_cmp(dir, dj->fn, 11)) /* Is it a valid entry? */
			break;
		res = dir_next(dj);							/* Next entry */
	} while (res == FR_OK);

	return res;
}




/*-----------------------------------------------------------------------*/
/* Read an object from the directory                                     */
/*-----------------------------------------------------------------------*/
#if _USE_DIR
static
FRESULT dir_read (
	DIR *dj			/* Pointer to the directory object to store read object name */
)
{
	FRESULT res;
	BYTE a, c, *dir;


	res = FR_NO_FILE;
	while (dj->sect) {
		dir = FatFs->buf;
		res = disk_readp(dir, dj->sect, (WORD)((dj->index % 16) * 32), 32)	/* Read an entry */
			? FR_DISK_ERR : FR_OK;
		if (res != FR_OK) break;
		c = dir[DIR_Name];
		if (c == 0) { res = FR_NO_FILE; break; }	/* Reached to end of table */
		a = dir[DIR_Attr] & AM_MASK;
		if (c != 0xE5 && c != '.' && !(a & AM_VOL))	/* Is it a valid entry? */
			break;
		res = dir_next(dj);				/* Next entry */
		if (res != FR_OK) break;
	}

	if (res != FR_OK) dj->sect = 0;

	return res;
}
#endif



/*-----------------------------------------------------------------------*/
/* Pick a segment and create the object name in directory form           */
/*-----------------------------------------------------------------------*/


static
FRESULT create_name (
	DIR *dj,			/* Pointer to the directory object */
	const char **path	/* Pointer to pointer to the segment in the path string */
)
{
	BYTE c, ni, si, i, *sfn;
	const char *p;

	/* Create file name in directory form */
	sfn = dj->fn;
	mem_set(sfn, ' ', 11);
	si = i = 0; ni = 8;
	p = *path;
	for (;;) {
		c = p[si++];
		if (c < ' ' || c == '/') break;	/* Break on end of segment */
		if (c == '.' || i >= ni) {
			if (ni != 8 || c != '.') return FR_INVALID_NAME;
			i = 8; ni = 11;
			continue;
		}
		if (c >= 0x7F || chk_chr(" +,;[=\\]\"*:<>\?|", c))	/* Reject unallowable chrs for SFN */
			return FR_INVALID_NAME;
		if (c >='a' && c <= 'z') c -= 0x20;
		sfn[i++] = c;
	}
	if (!i) return FR_INVALID_NAME;		/* Reject null string */
	*path = &p[si];						/* Rerurn pointer to the next segment */

	sfn[11] = (c < ' ') ? 1 : 0;		/* Set last segment flag if end of path */

	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Get file information from directory entry                             */
/*-----------------------------------------------------------------------*/
#if _USE_DIR
static
void get_fileinfo (		/* No return code */
	DIR *dj,			/* Pointer to the directory object */
	FILINFO *fno	 	/* Pointer to store the file information */
)
{
	BYTE i, c, *dir;
	char *p;


	p = fno->fname;
	if (dj->sect) {
		dir = FatFs->buf;
		for (i = 0; i < 8; i++) {	/* Copy file name body */
			c = dir[i];
			if (c == ' ') break;
			if (c == 0x05) c = 0xE5;
			*p++ = c;
		}
		if (dir[8] != ' ') {		/* Copy file name extension */
			*p++ = '.';
			for (i = 8; i < 11; i++) {
				c = dir[i];
				if (c == ' ') break;
				*p++ = c;
			}
		}
		fno->fattrib = dir[DIR_Attr];				/* Attribute */
		fno->fsize = LD_DWORD(dir+DIR_FileSize);	/* Size */
		fno->fdate = LD_WORD(dir+DIR_WrtDate);		/* Date */
		fno->ftime = LD_WORD(dir+DIR_WrtTime);		/* Time */
	}
	*p = 0;
}
#endif /* _USE_DIR */



/*-----------------------------------------------------------------------*/
/* Follow a file path                                                    */
/*-----------------------------------------------------------------------*/

static
FRESULT follow_path (	/* FR_OK(0): successful, !=0: error code */
	DIR *dj,			/* Directory object to return last directory and found object */
	const char *path	/* Full-path string to find a file or directory */
)
{
	FRESULT res;
	BYTE *dir;


	if (*path == '/') path++;			/* Strip heading separator */
	dj->sclust = 0;						/* Set start directory (always root dir) */

	if ((BYTE)*path < ' ') {			/* Null path means the root directory */
		res = dir_rewind(dj);
		FatFs->buf[0] = 0;

	} else {							/* Follow path */
		for (;;) {
			res = create_name(dj, &path);	/* Get a segment */
			if (res != FR_OK) break;
			res = dir_find(dj);				/* Find it */
			if (res != FR_OK) {				/* Could not find the object */
				if (res == FR_NO_FILE && !*(dj->fn+11))
					res = FR_NO_PATH;
				break;
			}
			if (*(dj->fn+11)) break;		/* Last segment match. Function completed. */
			dir = FatFs->buf;				/* There is next segment. Follow the sub directory */
			if (!(dir[DIR_Attr] & AM_DIR)) { /* Cannot follow because it is a file */
				res = FR_NO_PATH; break;
			}
			dj->sclust =
#if _FS_FAT32
				((DWORD)LD_WORD(dir+DIR_FstClusHI) << 16) | 
#endif
				LD_WORD(dir+DIR_FstClusLO);
		}
	}

	return res;
}




/*-----------------------------------------------------------------------*/
/* Check a sector if it is an FAT boot record                            */
/*-----------------------------------------------------------------------*/

static
BYTE check_fs (	/* 0:The FAT boot record, 1:Valid boot record but not an FAT, 2:Not a boot record, 3:Error */
	BYTE *buf,	/* Working buffer */
	DWORD sect	/* Sector# (lba) to check if it is an FAT boot record or not */
)
{
	if (disk_readp(buf, sect, 510, 2))		/* Read the boot sector */
		return 3;
	if (LD_WORD(buf) != 0xAA55)				/* Check record signature */
		return 2;

	if (!disk_readp(buf, sect, BS_FilSysType, 2) && LD_WORD(buf) == 0x4146)	/* Check FAT12/16 */
		return 0;
#if _FS_FAT32
	if (!disk_readp(buf, sect, BS_FilSysType32, 2) && LD_WORD(buf) == 0x4146)	/* Check FAT32 */
		return 0;
#endif
	return 1;
}




/*--------------------------------------------------------------------------

   Public Functions

--------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*/
/* Mount/Unmount a Locical Drive                                         */
/*-----------------------------------------------------------------------*/

FRESULT pf_mount (
	FATFS *fs		/* Pointer to new file system object (NULL: Unmount) */
)
{
	BYTE fmt, buf[36];
	DWORD bsect, fsize, tsect, mclst;


	FatFs = 0;
	if (!fs) return FR_OK;				/* Unregister fs object */

	if (disk_initialize() & STA_NOINIT)	/* Check if the drive is ready or not */
		return FR_NOT_READY;

	/* Search FAT partition on the drive */
	bsect = 0;
	fmt = check_fs(buf, bsect);			/* Check sector 0 as an SFD format */
	if (fmt == 1) {						/* Not an FAT boot record, it may be FDISK format */
		/* Check a partition listed in top of the partition table */
		if (disk_readp(buf, bsect, MBR_Table, 16)) {	/* 1st partition entry */
			fmt = 3;
		} else {
			if (buf[4]) {					/* Is the partition existing? */
				bsect = LD_DWORD(&buf[8]);	/* Partition offset in LBA */
				fmt = check_fs(buf, bsect);	/* Check the partition */
			}
		}
	}
	if (fmt == 3) return FR_DISK_ERR;
	if (fmt) return FR_NO_FILESYSTEM;	/* No valid FAT patition is found */

	/* Initialize the file system object */
	if (disk_readp(buf, bsect, 13, sizeof(buf))) return FR_DISK_ERR;

	fsize = LD_WORD(buf+BPB_FATSz16-13);				/* Number of sectors per FAT */
	if (!fsize) fsize = LD_DWORD(buf+BPB_FATSz32-13);

	fsize *= buf[BPB_NumFATs-13];						/* Number of sectors in FAT area */
	fs->fatbase = bsect + LD_WORD(buf+BPB_RsvdSecCnt-13); /* FAT start sector (lba) */
	fs->csize = buf[BPB_SecPerClus-13];					/* Number of sectors per cluster */
	fs->n_rootdir = LD_WORD(buf+BPB_RootEntCnt-13);		/* Nmuber of root directory entries */
	tsect = LD_WORD(buf+BPB_TotSec16-13);				/* Number of sectors on the file system */
	if (!tsect) tsect = LD_DWORD(buf+BPB_TotSec32-13);
	mclst = (tsect						/* Last cluster# + 1 */
		- LD_WORD(buf+BPB_RsvdSecCnt-13) - fsize - fs->n_rootdir / 16
		) / fs->csize + 2;
	fs->max_clust = (CLUST)mclst;

	fmt = FS_FAT12;							/* Determine the FAT sub type */
	if (mclst >= 0xFF7) fmt = FS_FAT16;		/* Number of clusters >= 0xFF5 */
	if (mclst >= 0xFFF7)					/* Number of clusters >= 0xFFF5 */
#if _FS_FAT32
		fmt = FS_FAT32;
#else
		return FR_NO_FILESYSTEM;
#endif

	fs->fs_type = fmt;		/* FAT sub-type */
#if _FS_FAT32
	if (fmt == FS_FAT32)
		fs->dirbase = LD_DWORD(buf+(BPB_RootClus-13));	/* Root directory start cluster */
	else
#endif
		fs->dirbase = fs->fatbase + fsize;				/* Root directory start sector (lba) */
	fs->database = fs->fatbase + fsize + fs->n_rootdir / 16;	/* Data start sector (lba) */

	fs->flag = 0;
	FatFs = fs;

	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Open or Create a File                                                 */
/*-----------------------------------------------------------------------*/

FRESULT pf_open (
	const char *path	/* Pointer to the file name */
)
{
	FRESULT res;
	DIR dj;
	BYTE sp[12], dir[32];
	FATFS *fs = FatFs;


	if (!fs)						/* Check file system */
		return FR_NOT_ENABLED;

	fs->flag = 0;
	fs->buf = dir;
	dj.fn = sp;
	res = follow_path(&dj, path);	/* Follow the file path */
	if (res != FR_OK) return res;	/* Follow failed */
	if (!dir[0] || (dir[DIR_Attr] & AM_DIR))	/* It is a directory */
		return FR_NO_FILE;

	fs->org_clust =						/* File start cluster */
#if _FS_FAT32
		((DWORD)LD_WORD(dir+DIR_FstClusHI) << 16) |
#endif
		LD_WORD(dir+DIR_FstClusLO);
	fs->fsize = LD_DWORD(dir+DIR_FileSize);	/* File size */
	fs->fptr = 0;						/* File pointer */
	fs->flag = FA_READ;

	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Read File                                                             */
/*-----------------------------------------------------------------------*/

FRESULT pf_read (
	void* dest,		/* Pointer to the destination object */
	WORD btr,		/* Number of bytes to read (bit15:destination) */
	WORD* br		/* Pointer to number of bytes read */
)
{
	DRESULT dr;
	CLUST clst;
	DWORD sect, remain;
	WORD rcnt;
	BYTE *rbuff = dest;
	FATFS *fs = FatFs;


	*br = 0;
	if (!fs) return FR_NOT_ENABLED;		/* Check file system */
	if (!(fs->flag & FA_READ))
			return FR_INVALID_OBJECT;

	remain = fs->fsize - fs->fptr;
	if (btr > remain) btr = (UINT)remain;			/* Truncate btr by remaining bytes */

	for ( ;  btr;									/* Repeat until all data transferred */
		rbuff += rcnt, fs->fptr += rcnt, *br += rcnt, btr -= rcnt) {
		if ((fs->fptr % 512) == 0) {				/* On the sector boundary? */
			if ((fs->fptr / 512 % fs->csize) == 0) {	/* On the cluster boundary? */
				clst = (fs->fptr == 0) ?			/* On the top of the file? */
					fs->org_clust : get_fat(fs->curr_clust);
				if (clst <= 1) {
					fs->flag = 0; return FR_DISK_ERR;
				}
				fs->curr_clust = clst;				/* Update current cluster */
				fs->csect = 0;						/* Reset sector offset in the cluster */
			}
			sect = clust2sect(fs->curr_clust);		/* Get current sector */
			if (!sect) {
				fs->flag = 0; return FR_DISK_ERR;
			}
			sect += fs->csect;
			fs->dsect = sect;
			fs->csect++;							/* Next sector address in the cluster */
		}
		rcnt = 512 - ((WORD)fs->fptr % 512);		/* Get partial sector data from sector buffer */
		if (rcnt > btr) rcnt = btr;
		if (fs->flag & FA_STREAM) {
			dr = disk_readp(dest, fs->dsect, (WORD)(fs->fptr % 512), (WORD)(rcnt | 0x8000));
		} else {
			dr = disk_readp(rbuff, fs->dsect, (WORD)(fs->fptr % 512), rcnt);
		}
		if (dr) {
			fs->flag = 0;
			return (dr == RES_STRERR) ? FR_STREAM_ERR : FR_DISK_ERR;
		}
	}

	return FR_OK;
}




#if _USE_LSEEK
/*-----------------------------------------------------------------------*/
/* Seek File R/W Pointer                                                 */
/*-----------------------------------------------------------------------*/

FRESULT pf_lseek (
	DWORD ofs		/* File pointer from top of file */
)
{
	CLUST clst;
	DWORD bcs, nsect, ifptr;
	FATFS *fs = FatFs;


	if (!fs) return FR_NOT_ENABLED;		/* Check file system */
	if (!(fs->flag & FA_READ))
			return FR_INVALID_OBJECT;

	if (ofs > fs->fsize) ofs = fs->fsize;	/* Clip offset with the file size */
	ifptr = fs->fptr;
	fs->fptr = 0;
	if (ofs > 0) {
		bcs = (DWORD)fs->csize * 512;	/* Cluster size (byte) */
		if (ifptr > 0 &&
			(ofs - 1) / bcs >= (ifptr - 1) / bcs) {	/* When seek to same or following cluster, */
			fs->fptr = (ifptr - 1) & ~(bcs - 1);	/* start from the current cluster */
			ofs -= fs->fptr;
			clst = fs->curr_clust;
		} else {							/* When seek to back cluster, */
			clst = fs->org_clust;			/* start from the first cluster */
			fs->curr_clust = clst;
		}
		while (ofs > bcs) {				/* Cluster following loop */
				clst = get_fat(clst);	/* Follow cluster chain if not in write mode */
			if (clst <= 1 || clst >= fs->max_clust) {
				fs->flag = 0; return FR_DISK_ERR;
			}
			fs->curr_clust = clst;
			fs->fptr += bcs;
			ofs -= bcs;
		}
		fs->fptr += ofs;
		fs->csect = (BYTE)(ofs / 512) + 1;	/* Sector offset in the cluster */
		nsect = clust2sect(clst);	/* Current sector */
		if (!nsect) {
			fs->flag = 0; return FR_DISK_ERR;
		}
		fs->dsect = nsect + fs->csect - 1;
	}

	return FR_OK;
}
#endif


#if _USE_DIR
/*-----------------------------------------------------------------------*/
/* Create a Directroy Object                                             */
/*-----------------------------------------------------------------------*/

FRESULT pf_opendir (
	DIR *dj,			/* Pointer to directory object to create */
	const char *path	/* Pointer to the directory path */
)
{
	FRESULT res;
	BYTE sp[12], dir[32];
	FATFS *fs = FatFs;


	if (!fs) {				/* Check file system */
		res = FR_NOT_ENABLED;
	} else {
		fs->buf = dir;
		dj->fn = sp;
		res = follow_path(dj, path);			/* Follow the path to the directory */
		if (res == FR_OK) {						/* Follow completed */
			if (dir[0]) {						/* It is not the root dir */
				if (dir[DIR_Attr] & AM_DIR) {	/* The object is a directory */
					dj->sclust =
#if _FS_FAT32
					((DWORD)LD_WORD(dir+DIR_FstClusHI) << 16) |
#endif
					LD_WORD(dir+DIR_FstClusLO);
				} else {						/* The object is not a directory */
					res = FR_NO_PATH;
				}
			}
			if (res == FR_OK) {
				res = dir_rewind(dj);			/* Rewind dir */
			}
		}
		if (res == FR_NO_FILE) res = FR_NO_PATH;
	}

	return res;
}




/*-----------------------------------------------------------------------*/
/* Read Directory Entry in Sequense                                      */
/*-----------------------------------------------------------------------*/

FRESULT pf_readdir (
	DIR *dj,			/* Pointer to the open directory object */
	FILINFO *fno		/* Pointer to file information to return */
)
{
	FRESULT res;
	BYTE sp[12], dir[32];
	FATFS *fs = FatFs;


	if (!fs) {				/* Check file system */
		res = FR_NOT_ENABLED;
	} else {
		fs->buf = dir;
		dj->fn = sp;
		if (!fno) {
			res = dir_rewind(dj);
		} else {
			res = dir_read(dj);
			if (res == FR_NO_FILE) {
				dj->sect = 0;
				res = FR_OK;
			}
			if (res == FR_OK) {				/* A valid entry is found */
				get_fileinfo(dj, fno);		/* Get the object information */
				res = dir_next(dj);			/* Increment index for next */
				if (res == FR_NO_FILE) {
					dj->sect = 0;
					res = FR_OK;
				}
			}
		}
	}

	return res;
}

#endif /* _FS_DIR */

