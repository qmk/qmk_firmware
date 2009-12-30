/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2010      */
/*-----------------------------------------------------------------------*/

#include "diskio.h"

#include <string.h>
#include <LUFA/Drivers/USB/Class/MassStorage.h>
#include "../DataflashManager.h"
#include "../../DiskHost.h"

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	void* dest,			/* Pointer to the destination object */
	DWORD sector,		/* Sector number (LBA) */
	WORD sofs,			/* Offset in the sector */
	WORD count			/* Byte count (bit15:destination) */
)
{
	DRESULT ErrorCode = RES_OK;
	uint8_t BlockTemp[512];

	if (USB_CurrentMode == USB_MODE_HOST)
	{
		#if defined(USB_CAN_BE_HOST)
		if (USB_HostState != HOST_STATE_Configured)
		  ErrorCode = RES_NOTRDY;
		else if (MS_Host_ReadDeviceBlocks(&DiskHost_MS_Interface, 0, sector, 1, 512, BlockTemp))
		  ErrorCode = RES_ERROR;

		MS_Host_ReadDeviceBlocks(&DiskHost_MS_Interface, 0, sector, 1, 512, BlockTemp);
		#endif
	}
	else
	{
		#if defined(USB_CAN_BE_DEVICE)
		DataflashManager_ReadBlocks_RAM(sector, 1, BlockTemp);
		#endif
	}

	memcpy(dest, &BlockTemp[sofs], count);

	return ErrorCode;
}

