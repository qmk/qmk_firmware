/*
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

#define  __INCLUDE_FROM_TWI_C
#include "../TWI.h"

uint8_t TWI_StartTransmission(const uint8_t SlaveAddress,
                              const uint8_t TimeoutMS)
{
	for (;;)
	{
		bool     BusCaptured = false;
		uint16_t TimeoutRemaining;

		TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));

		TimeoutRemaining = (TimeoutMS * 100);
		while (TimeoutRemaining-- && !(BusCaptured))
		{
			if (TWCR & (1 << TWINT))
			{
				switch (TWSR & TW_STATUS_MASK)
				{
					case TW_START:
					case TW_REP_START:
						BusCaptured = true;
						break;
					case TW_MT_ARB_LOST:
						TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));
						continue;
					default:
						TWCR = (1 << TWEN);
						return TWI_ERROR_BusFault;
				}
			}

			_delay_us(10);
		}

		if (!(TimeoutRemaining))
		{
			TWCR = (1 << TWEN);
			return TWI_ERROR_BusCaptureTimeout;
		}

		TWDR = SlaveAddress;
		TWCR = ((1 << TWINT) | (1 << TWEN));

		TimeoutRemaining = (TimeoutMS * 100);
		while (TimeoutRemaining--)
		{
			if (TWCR & (1 << TWINT))
			  break;

			_delay_us(10);
		}

		if (!(TimeoutRemaining))
		  return TWI_ERROR_SlaveResponseTimeout;

		switch (TWSR & TW_STATUS_MASK)
		{
			case TW_MT_SLA_ACK:
			case TW_MR_SLA_ACK:
				return TWI_ERROR_NoError;
			default:
				TWCR = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
				return TWI_ERROR_SlaveNotReady;
		}
	}
}

uint8_t TWI_ReadPacket(const uint8_t SlaveAddress,
                       const uint8_t TimeoutMS,
                       const uint8_t* InternalAddress,
                       uint8_t InternalAddressLen,
                       uint8_t* Buffer,
                       uint8_t Length)
{
	uint8_t ErrorCode;
	
	if ((ErrorCode = TWI_WritePacket(SlaveAddress, TimeoutMS, InternalAddress, InternalAddressLen,
	                                 NULL, 0)) != TWI_ERROR_NoError)
	{
		return ErrorCode;
	}

	if ((ErrorCode = TWI_StartTransmission((SlaveAddress & TWI_DEVICE_ADDRESS_MASK) | TWI_ADDRESS_READ,
										   TimeoutMS)) == TWI_ERROR_NoError)
	{
		while (Length--)
		{
			if (!(TWI_ReceiveByte(Buffer++, (Length == 0))))
			{
				ErrorCode = TWI_ERROR_SlaveNAK;
				break;
			}
		}
		
		TWI_StopTransmission();
	}
	
	return ErrorCode;
}

uint8_t TWI_WritePacket(const uint8_t SlaveAddress,
                        const uint8_t TimeoutMS,
                        const uint8_t* InternalAddress,
                        uint8_t InternalAddressLen,
                        const uint8_t* Buffer,
                        uint8_t Length)
{
	uint8_t ErrorCode;

	if ((ErrorCode = TWI_StartTransmission((SlaveAddress & TWI_DEVICE_ADDRESS_MASK) | TWI_ADDRESS_WRITE,
	                                       TimeoutMS)) == TWI_ERROR_NoError)
	{
		while (InternalAddressLen--)
		{
			if (!(TWI_SendByte(*(InternalAddress++))))
			{
				ErrorCode = TWI_ERROR_SlaveNAK;
				break;
			}
		}

		while (Length--)
		{
			if (!(TWI_SendByte(*(Buffer++))))
			{
				ErrorCode = TWI_ERROR_SlaveNAK;
				break;
			}
		}
		
		TWI_StopTransmission();
	}
	
	return ErrorCode;
}
