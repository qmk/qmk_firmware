/*-----------------------------------------------------------------------
/  PFF - Low level disk interface modlue include file    (C)ChaN, 2010
/-----------------------------------------------------------------------*/

#ifndef _DISKIO

#include "integer.h"


/* Status of Disk Functions */
typedef BYTE	DSTATUS;


/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Function succeeded */
	RES_ERROR,		/* 1: Disk error */
	RES_STRERR,		/* 2: Seream error */
	RES_NOTRDY,		/* 3: Not ready */
	RES_PARERR		/* 4: Invalid parameter */
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */

DSTATUS disk_initialize (void);
DRESULT disk_readp (void*, DWORD, WORD, WORD);

BOOL assign_drives (int argc, char *argv[]);

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */

#define _DISKIO
#endif
