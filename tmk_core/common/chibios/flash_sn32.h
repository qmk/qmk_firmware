#ifndef __SN32F240_FLASH_H
#define __SN32F240_FLASH_H

/*_____ I N C L U D E S ____________________________________________________*/
#include "SN32F240B.h"
#include "SN32F200_Def.h"


/*_____ D E F I N I T I O N S ______________________________________________*/
//FLASH HW
#define	FLASH_PAGE_SIZE					1024
#define	FLASH_F240_MAX_ROM_SIZE			0xFFFF
#define	FLASH_F230_MAX_ROM_SIZE			0x7FFF
#define	FLASH_F220_MAX_ROM_SIZE			0x3FFF


// Flash Control Register definitions
#define FLASH_PG										0x00000001
#define FLASH_PER										0x00000002
#define FLASH_STARTE									0x00000040

// Flash Status Register definitions
#define FLASH_OKAY									0x00000000
#define FLASH_BUSY									0x00000001
#define FLASH_PGERR									0x00000002
#define FLASH_TIMEOUT							    0x00000003


/*_____ M A C R O S ________________________________________________________*/

//Flash Low Power Mode
#define	__FLASH_LPM_DISABLE					SN_FLASH->LPCTRL = 0x5AFA0000
#define	__FLASH_LPM_SLOW_MODE				SN_FLASH->LPCTRL = 0x5AFA0002

//Flash Status
#define	__FLASH_CLEAR_ERROR_STATUS	SN_FLASH->STATUS &= ~FLASH_PGERR


/*_____ D E C L A R A T I O N S ____________________________________________*/
extern	uint32_t wFLASH_PGRAM[2];

uint32_t FLASH_EraseSector(uint32_t);
uint32_t FLASH_ProgramHalfWord(uint32_t, uint8_t *);
uint32_t FLASH_ProgramPage (uint32_t, uint32_t, uint8_t *);


#endif	/* __SN32F240_FLASH_H */
