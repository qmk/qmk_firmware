/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "hal.h"
#include "ffconf.h"
#include "diskio.h"

#if HAL_USE_MMC_SPI && HAL_USE_SDC
#error "cannot specify both MMC_SPI and SDC drivers"
#endif

#if HAL_USE_MMC_SPI
extern MMCDriver MMCD1;
#elif HAL_USE_SDC
extern SDCDriver SDCD1;
#else
#error "MMC_SPI or SDC driver must be specified"
#endif

#if HAL_USE_RTC
extern RTCDriver RTCD1;
#endif

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */

#define MMC     0
#define SDC     0



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize (
    BYTE pdrv         /* Physical drive number (0..) */
)
{
  DSTATUS stat;

  switch (pdrv) {
#if HAL_USE_MMC_SPI
  case MMC:
    stat = 0;
    /* It is initialized externally, just reads the status.*/
    if (blkGetDriverState(&MMCD1) != BLK_READY)
      stat |= STA_NOINIT;
    if (mmcIsWriteProtected(&MMCD1))
      stat |=  STA_PROTECT;
    return stat;
#else
  case SDC:
    stat = 0;
    /* It is initialized externally, just reads the status.*/
    if (blkGetDriverState(&SDCD1) != BLK_READY)
      stat |= STA_NOINIT;
    if (sdcIsWriteProtected(&SDCD1))
      stat |=  STA_PROTECT;
    return stat;
#endif
  }
  return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
    BYTE pdrv         /* Physical drive number (0..) */
)
{
  DSTATUS stat;

  switch (pdrv) {
#if HAL_USE_MMC_SPI
  case MMC:
    stat = 0;
    /* It is initialized externally, just reads the status.*/
    if (blkGetDriverState(&MMCD1) != BLK_READY)
      stat |= STA_NOINIT;
    if (mmcIsWriteProtected(&MMCD1))
      stat |= STA_PROTECT;
    return stat;
#else
  case SDC:
    stat = 0;
    /* It is initialized externally, just reads the status.*/
    if (blkGetDriverState(&SDCD1) != BLK_READY)
      stat |= STA_NOINIT;
    if (sdcIsWriteProtected(&SDCD1))
      stat |= STA_PROTECT;
    return stat;
#endif
  }
  return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
    BYTE pdrv,        /* Physical drive number (0..) */
    BYTE *buff,       /* Data buffer to store read data */
    DWORD sector,     /* Sector address (LBA) */
    UINT count        /* Number of sectors to read (1..255) */
)
{
  switch (pdrv) {
#if HAL_USE_MMC_SPI
  case MMC:
    if (blkGetDriverState(&MMCD1) != BLK_READY)
      return RES_NOTRDY;
    if (mmcStartSequentialRead(&MMCD1, sector))
      return RES_ERROR;
    while (count > 0) {
      if (mmcSequentialRead(&MMCD1, buff))
        return RES_ERROR;
      buff += MMCSD_BLOCK_SIZE;
      count--;
    }
    if (mmcStopSequentialRead(&MMCD1))
        return RES_ERROR;
    return RES_OK;
#else
  case SDC:
    if (blkGetDriverState(&SDCD1) != BLK_READY)
      return RES_NOTRDY;
    if (sdcRead(&SDCD1, sector, buff, count))
      return RES_ERROR;
    return RES_OK;
#endif
  }
  return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if !FF_FS_READONLY
DRESULT disk_write (
    BYTE pdrv,        /* Physical drive number (0..) */
    const BYTE *buff, /* Data to be written */
    DWORD sector,     /* Sector address (LBA) */
    UINT count        /* Number of sectors to write (1..255) */
)
{
  switch (pdrv) {
#if HAL_USE_MMC_SPI
  case MMC:
    if (blkGetDriverState(&MMCD1) != BLK_READY)
        return RES_NOTRDY;
    if (mmcIsWriteProtected(&MMCD1))
        return RES_WRPRT;
    if (mmcStartSequentialWrite(&MMCD1, sector))
        return RES_ERROR;
    while (count > 0) {
        if (mmcSequentialWrite(&MMCD1, buff))
            return RES_ERROR;
        buff += MMCSD_BLOCK_SIZE;
        count--;
    }
    if (mmcStopSequentialWrite(&MMCD1))
        return RES_ERROR;
    return RES_OK;
#else
  case SDC:
    if (blkGetDriverState(&SDCD1) != BLK_READY)
      return RES_NOTRDY;
    if (sdcWrite(&SDCD1, sector, buff, count))
      return RES_ERROR;
    return RES_OK;
#endif
  }
  return RES_PARERR;
}
#endif /* _FS_READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
    BYTE pdrv,        /* Physical drive number (0..) */
    BYTE cmd,         /* Control code */
    void *buff        /* Buffer to send/receive control data */
)
{
  (void)buff;

  switch (pdrv) {
#if HAL_USE_MMC_SPI
  case MMC:
    switch (cmd) {
    case CTRL_SYNC:
        return RES_OK;
#if FF_MAX_SS > FF_MIN_SS
    case GET_SECTOR_SIZE:
        *((WORD *)buff) = MMCSD_BLOCK_SIZE;
        return RES_OK;
#endif
#if FF_USE_TRIM
    case CTRL_TRIM:
        mmcErase(&MMCD1, *((DWORD *)buff), *((DWORD *)buff + 1));
        return RES_OK;
#endif
    default:
        return RES_PARERR;
    }
#else
  case SDC:
    switch (cmd) {
    case CTRL_SYNC:
        return RES_OK;
    case GET_SECTOR_COUNT:
        *((DWORD *)buff) = mmcsdGetCardCapacity(&SDCD1);
        return RES_OK;
#if FF_MAX_SS > FF_MIN_SS
    case GET_SECTOR_SIZE:
        *((WORD *)buff) = MMCSD_BLOCK_SIZE;
        return RES_OK;
#endif
    case GET_BLOCK_SIZE:
        *((DWORD *)buff) = 256; /* 512b blocks in one erase block */
        return RES_OK;
#if FF_USE_TRIM
    case CTRL_TRIM:
        sdcErase(&SDCD1, *((DWORD *)buff), *((DWORD *)buff + 1));
        return RES_OK;
#endif
    default:
        return RES_PARERR;
    }
#endif
  }
  return RES_PARERR;
}

DWORD get_fattime(void) {
#if HAL_USE_RTC
    RTCDateTime timespec;

    rtcGetTime(&RTCD1, &timespec);
    return rtcConvertDateTimeToFAT(&timespec);
#else
    return ((uint32_t)0 | (1 << 16)) | (1 << 21); /* wrong but valid time */
#endif
}
