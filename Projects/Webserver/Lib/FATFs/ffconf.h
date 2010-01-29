/*---------------------------------------------------------------------------/
/  FatFs - FAT file system module configuration file  R0.07e  (C)ChaN, 2010
/----------------------------------------------------------------------------/
/
/ CAUTION! Do not forget to make clean the project after any changes to
/ the configuration options.
/
/----------------------------------------------------------------------------*/
#ifndef _FFCONFIG
#define _FFCONFIG 0x007E


/*---------------------------------------------------------------------------/
/ Function and Buffer Configurations
/----------------------------------------------------------------------------*/

#define	_FS_TINY	0		/* 0 or 1 */
/* When _FS_TINY is set to 1, FatFs uses the sector buffer in the file system
/  object instead of the sector buffer in the individual file object for file
/  data transfer. This reduces memory consumption 512 bytes each file object. */


#define _FS_READONLY	1	/* 0 or 1 */
/* Setting _FS_READONLY to 1 defines read only configuration. This removes
/  writing functions, f_write, f_sync, f_unlink, f_mkdir, f_chmod, f_rename,
/  f_truncate and useless f_getfree. */


#define _FS_MINIMIZE	2	/* 0, 1, 2 or 3 */
/* The _FS_MINIMIZE option defines minimization level to remove some functions.
/
/   0: Full function.
/   1: f_stat, f_getfree, f_unlink, f_mkdir, f_chmod, f_truncate and f_rename
/      are removed.
/   2: f_opendir and f_readdir are removed in addition to level 1.
/   3: f_lseek is removed in addition to level 2. */


#define	_USE_STRFUNC	0	/* 0, 1 or 2 */
/* To enable string functions, set _USE_STRFUNC to 1 or 2. */


#define	_USE_MKFS	0		/* 0 or 1 */
/* To enable f_mkfs function, set _USE_MKFS to 1 and set _FS_READONLY to 0 */


#define	_USE_FORWARD	0	/* 0 or 1 */
/* To enable f_forward function, set _USE_FORWARD to 1 and set _FS_TINY to 1. */



/*---------------------------------------------------------------------------/
/ Locale and Namespace Configurations
/----------------------------------------------------------------------------*/

#define _CODE_PAGE	932
/* The _CODE_PAGE specifies the OEM code page to be used on the target system.
/  Incorrect setting of the code page can cause a file open failure.
/
/   932  - Japanese Shift-JIS (DBCS, OEM, Windows)
/   936  - Simplified Chinese GBK (DBCS, OEM, Windows)
/   949  - Korean (DBCS, OEM, Windows)
/   950  - Traditional Chinese Big5 (DBCS, OEM, Windows)
/   1250 - Central Europe (Windows)
/   1251 - Cyrillic (Windows)
/   1252 - Latin 1 (Windows)
/   1253 - Greek (Windows)
/   1254 - Turkish (Windows)
/   1255 - Hebrew (Windows)
/   1256 - Arabic (Windows)
/   1257 - Baltic (Windows)
/   1258 - Vietnam (OEM, Windows)
/   437  - U.S. (OEM)
/   720  - Arabic (OEM)
/   737  - Greek (OEM)
/   775  - Baltic (OEM)
/   850  - Multilingual Latin 1 (OEM)
/   858  - Multilingual Latin 1 + Euro (OEM)
/   852  - Latin 2 (OEM)
/   855  - Cyrillic (OEM)
/   866  - Russian (OEM)
/   857  - Turkish (OEM)
/   862  - Hebrew (OEM)
/   874  - Thai (OEM, Windows)
/	1    - ASCII only (Valid for non LFN cfg.)
*/


#define	_USE_LFN	0		/* 0, 1 or 2 */
#define	_MAX_LFN	255		/* Maximum LFN length to handle (12 to 255) */
/* The _USE_LFN option switches the LFN support.
/
/   0: Disable LFN. _MAX_LFN and _LFN_UNICODE have no effect.
/   1: Enable LFN with static working buffer on the bss. NOT REENTRANT.
/   2: Enable LFN with dynamic working buffer on the STACK.
/
/  The LFN working buffer occupies (_MAX_LFN + 1) * 2 bytes. When enable LFN,
/  two Unicode handling functions ff_convert() and ff_wtoupper() must be added
/  to the project. */


#define	_LFN_UNICODE	0	/* 0 or 1 */
/* To switch the character code set on FatFs API to Unicode,
/  enable LFN feature and set _LFN_UNICODE to 1.
*/


#define _FS_RPATH	0		/* 0 or 1 */
/* When _FS_RPATH is set to 1, relative path feature is enabled and f_chdir,
/  f_chdrive function are available.
/  Note that output of the f_readdir fnction is affected by this option. */



/*---------------------------------------------------------------------------/
/ Physical Drive Configurations
/----------------------------------------------------------------------------*/

#define _DRIVES		1
/* Number of volumes (logical drives) to be used. */


#define	_MAX_SS		512		/* 512, 1024, 2048 or 4096 */
/* Maximum sector size to be handled.
/  Always set 512 for memory card and hard disk but a larger value may be
/  required for floppy disk (512/1024) and optical disk (512/2048).
/  When _MAX_SS is larger than 512, GET_SECTOR_SIZE command must be implememted
/  to the disk_ioctl function. */


#define	_MULTI_PARTITION	0	/* 0 or 1 */
/* When _MULTI_PARTITION is set to 0, each volume is bound to the same physical
/ drive number and can mount only first primaly partition. When it is set to 1,
/ each volume is tied to the partitions listed in Drives[]. */



/*---------------------------------------------------------------------------/
/ System Configurations
/----------------------------------------------------------------------------*/

#define _WORD_ACCESS	1	/* 0 or 1 */
/* The _WORD_ACCESS option defines which access method is used to the word
/  data on the FAT volume.
/
/   0: Byte-by-byte access. Always compatible with all platforms.
/   1: Word access. Do not choose this unless following condition is met.
/
/  When the byte order on the memory is big-endian or address miss-aligned
/  word access results incorrect behavior, the _WORD_ACCESS must be set to 0.
/  If it is not the case, the value can also be set to 1 to improve the
/  performance and code size. */


#define _FS_REENTRANT	0		/* 0 or 1 */
#define _FS_TIMEOUT		1000	/* Timeout period in unit of time ticks */
#define	_SYNC_t			HANDLE	/* O/S dependent type of sync object. e.g. HANDLE, OS_EVENT*, ID and etc.. */
/* The _FS_REENTRANT option switches the reentrancy of the FatFs module.
/
/   0: Disable reentrancy. _SYNC_t and _FS_TIMEOUT have no effect.
/   1: Enable reentrancy. Also user provided synchronization handlers,
/      ff_req_grant, ff_rel_grant, ff_del_syncobj and ff_cre_syncobj
/      function must be added to the project. */


#endif /* _FFCONFIG */
