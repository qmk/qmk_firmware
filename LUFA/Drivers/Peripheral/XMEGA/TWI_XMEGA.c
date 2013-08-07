/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

static inline bool bitmask_is_set(uint8_t byte, uint8_t mask) {
  return (byte & mask) == mask;
}

uint8_t TWI_StartTransmission(TWI_t *twi,
                              const uint8_t SlaveAddress,
                              const uint8_t TimeoutMS)
{
  uint16_t TimeoutRemaining;

  twi->MASTER.ADDR = SlaveAddress;

  TimeoutRemaining = (TimeoutMS * 100);
  while (TimeoutRemaining)
  {
    uint8_t status = twi->MASTER.STATUS;
    if (bitmask_is_set(status, TWI_MASTER_WIF_bm | TWI_MASTER_ARBLOST_bm))
    {
      // Case 1: Arbitration lost.  Try again. (or error)
      twi->MASTER.ADDR = SlaveAddress;
    }
    else if (bitmask_is_set(status, TWI_MASTER_WIF_bm | TWI_MASTER_RXACK_bm))
    {
      // Case 2: No response from slave.
      // We need to release the bus.
      TWI_StopTransmission(twi);
      return TWI_ERROR_SlaveResponseTimeout;
    }
    else if (status & TWI_MASTER_WIF_bm)
    {
      // Case 3: Slave ACK the Write. Ready!
      return TWI_ERROR_NoError;
    }
    else if (status & TWI_MASTER_RIF_bm)
    {
      // Case 4: Slave ACK the Read. Ready! (a byte will be read)
      return TWI_ERROR_NoError;
    }
    // Still waiting..
    _delay_us(10);
    TimeoutRemaining--;
  }

  if (!(TimeoutRemaining)) {
    if (twi->MASTER.STATUS & TWI_MASTER_CLKHOLD_bm) {
      // Release the bus if we're holding it.
      TWI_StopTransmission(twi);
    }
  }
  return TWI_ERROR_BusCaptureTimeout;
}

bool TWI_SendByte(TWI_t *twi, const uint8_t Byte)
{
  // We assume we're ready to write!
  twi->MASTER.DATA = Byte;
  while (!(twi->MASTER.STATUS & TWI_MASTER_WIF_bm));
  return (twi->MASTER.STATUS & TWI_MASTER_WIF_bm) && !(twi->MASTER.STATUS & TWI_MASTER_RXACK_bm);
}

bool TWI_ReceiveByte(TWI_t *twi, uint8_t* const Byte,
					 const bool LastByte)
{
  // If we're here, we should already be reading.  Wait if we haven't read yet.
  if (bitmask_is_set(twi->MASTER.STATUS, TWI_MASTER_BUSERR_bm | TWI_MASTER_ARBLOST_bm)) {
    return false;
  }
  while (!(twi->MASTER.STATUS & TWI_MASTER_RIF_bm));
  *Byte = twi->MASTER.DATA;
  if (LastByte)
    twi->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
  else
    twi->MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
  return true;
}

uint8_t TWI_ReadPacket(TWI_t *twi,
                       const uint8_t SlaveAddress,
                       const uint8_t TimeoutMS,
                       const uint8_t* InternalAddress,
                       uint8_t InternalAddressLen,
                       uint8_t* Buffer,
                       uint8_t Length)
{
	uint8_t ErrorCode;

	if ((ErrorCode = TWI_StartTransmission(twi, (SlaveAddress & TWI_DEVICE_ADDRESS_MASK) | TWI_ADDRESS_WRITE,
	                                       TimeoutMS)) == TWI_ERROR_NoError)
	{
		while (InternalAddressLen--)
		{
			if (!(TWI_SendByte(twi, *(InternalAddress++))))
			{
				ErrorCode = TWI_ERROR_SlaveNAK;
				break;
			}
		}

		if ((ErrorCode = TWI_StartTransmission(twi, (SlaveAddress & TWI_DEVICE_ADDRESS_MASK) | TWI_ADDRESS_READ,
											   TimeoutMS)) == TWI_ERROR_NoError)
		{
			while (Length--)
			{
				if (!(TWI_ReceiveByte(twi, Buffer++, (Length == 0))))
				{
					ErrorCode = TWI_ERROR_SlaveNAK;
					break;
				}
			}

		}
    TWI_StopTransmission(twi);
	}

	return ErrorCode;
}

uint8_t TWI_WritePacket(TWI_t *twi,
                        const uint8_t SlaveAddress,
                        const uint8_t TimeoutMS,
                        const uint8_t* InternalAddress,
                        uint8_t InternalAddressLen,
                        const uint8_t* Buffer,
                        uint8_t Length)
{
	uint8_t ErrorCode;
	if ((ErrorCode = TWI_StartTransmission(twi, (SlaveAddress & TWI_DEVICE_ADDRESS_MASK) | TWI_ADDRESS_WRITE,
	                                       TimeoutMS)) == TWI_ERROR_NoError)
	{
		while (InternalAddressLen--)
		{
			if (!(TWI_SendByte(twi, *(InternalAddress++))))
			{
				ErrorCode = TWI_ERROR_SlaveNAK;
				break;
			}
		}

		while (Length--)
		{
			if (!(TWI_SendByte(twi, *(Buffer++))))
			{
				ErrorCode = TWI_ERROR_SlaveNAK;
				break;
			}
		}

		TWI_StopTransmission(twi);
	}

	return ErrorCode;
}

#endif
