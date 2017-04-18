/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "../../../Common/Common.h"
#if (ARCH == ARCH_XMEGA)

#define  __INCLUDE_FROM_TWI_C
#include "../TWI.h"

uint8_t TWI_StartTransmission(TWI_t* const TWI,
                              const uint8_t SlaveAddress,
                              const uint8_t TimeoutMS)
{
	uint16_t TimeoutRemaining;

	TWI->MASTER.ADDR = SlaveAddress;

	TimeoutRemaining = (TimeoutMS * 100);
	while (TimeoutRemaining)
	{
		uint8_t status = TWI->MASTER.STATUS;

		if ((status & (TWI_MASTER_WIF_bm | TWI_MASTER_ARBLOST_bm)) == (TWI_MASTER_WIF_bm | TWI_MASTER_ARBLOST_bm))
		{
			TWI->MASTER.ADDR = SlaveAddress;
		}
		else if ((status & (TWI_MASTER_WIF_bm | TWI_MASTER_RXACK_bm)) == (TWI_MASTER_WIF_bm | TWI_MASTER_RXACK_bm))
		{
			TWI_StopTransmission(TWI);
			return TWI_ERROR_SlaveResponseTimeout;
		}
		else if (status & (TWI_MASTER_WIF_bm | TWI_MASTER_RIF_bm))
		{
			return TWI_ERROR_NoError;
		}

		_delay_us(10);
		TimeoutRemaining--;
	}

	if (!(TimeoutRemaining)) {
		if (TWI->MASTER.STATUS & TWI_MASTER_CLKHOLD_bm) {
			TWI_StopTransmission(TWI);
		}
	}

	return TWI_ERROR_BusCaptureTimeout;
}

bool TWI_SendByte(TWI_t* const TWI,
                  const uint8_t Byte)
{
	TWI->MASTER.DATA = Byte;

	while (!(TWI->MASTER.STATUS & TWI_MASTER_WIF_bm));

	return (TWI->MASTER.STATUS & TWI_MASTER_WIF_bm) && !(TWI->MASTER.STATUS & TWI_MASTER_RXACK_bm);
}

bool TWI_ReceiveByte(TWI_t* const TWI,
                     uint8_t* const Byte,
                     const bool LastByte)
{
	if ((TWI->MASTER.STATUS & (TWI_MASTER_BUSERR_bm | TWI_MASTER_ARBLOST_bm)) == (TWI_MASTER_BUSERR_bm | TWI_MASTER_ARBLOST_bm)) {
		return false;
	}

	while (!(TWI->MASTER.STATUS & TWI_MASTER_RIF_bm));

	*Byte = TWI->MASTER.DATA;

	if (LastByte)
	  TWI->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
	else
	  TWI->MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;

	return true;
}

uint8_t TWI_ReadPacket(TWI_t* const TWI,
                       const uint8_t SlaveAddress,
                       const uint8_t TimeoutMS,
                       const uint8_t* InternalAddress,
                       uint8_t InternalAddressLen,
                       uint8_t* Buffer,
                       uint16_t Length)
{
	uint8_t ErrorCode;

	if ((ErrorCode = TWI_StartTransmission(TWI, (SlaveAddress & TWI_DEVICE_ADDRESS_MASK) | TWI_ADDRESS_WRITE,
	                                       TimeoutMS)) == TWI_ERROR_NoError)
	{
		while (InternalAddressLen--)
		{
			if (!(TWI_SendByte(TWI, *(InternalAddress++))))
			{
				ErrorCode = TWI_ERROR_SlaveNAK;
				break;
			}
		}

		if ((ErrorCode = TWI_StartTransmission(TWI, (SlaveAddress & TWI_DEVICE_ADDRESS_MASK) | TWI_ADDRESS_READ,
		                                       TimeoutMS)) == TWI_ERROR_NoError)
		{
			while (Length--)
			{
				if (!(TWI_ReceiveByte(TWI, Buffer++, (Length == 0))))
				{
					ErrorCode = TWI_ERROR_SlaveNAK;
					break;
				}
			}
		}

		TWI_StopTransmission(TWI);
	}

	return ErrorCode;
}

uint8_t TWI_WritePacket(TWI_t* const TWI,
                        const uint8_t SlaveAddress,
                        const uint8_t TimeoutMS,
                        const uint8_t* InternalAddress,
                        uint8_t InternalAddressLen,
                        const uint8_t* Buffer,
                        uint16_t Length)
{
	uint8_t ErrorCode;

	if ((ErrorCode = TWI_StartTransmission(TWI, (SlaveAddress & TWI_DEVICE_ADDRESS_MASK) | TWI_ADDRESS_WRITE,
	                                       TimeoutMS)) == TWI_ERROR_NoError)
	{
		while (InternalAddressLen--)
		{
			if (!(TWI_SendByte(TWI, *(InternalAddress++))))
			{
				ErrorCode = TWI_ERROR_SlaveNAK;
				break;
			}
		}

		while (Length--)
		{
			if (!(TWI_SendByte(TWI, *(Buffer++))))
			{
				ErrorCode = TWI_ERROR_SlaveNAK;
				break;
			}
		}

		TWI_StopTransmission(TWI);
	}

	return ErrorCode;
}

#endif
