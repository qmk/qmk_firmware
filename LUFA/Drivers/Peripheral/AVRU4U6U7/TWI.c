/*
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

#include "../TWI.h"

bool TWI_StartTransmission(uint8_t SlaveAddress)
{
	for (;;)
	{
		uint8_t IterationsRemaining = 50;
		bool    BusCaptured = false;

		while (IterationsRemaining-- && !BusCaptured)
		{
			TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));	
			while (!(TWCR & (1 << TWINT)));
				
			switch (TWSR & TW_STATUS_MASK)
			{
				case TW_START:
				case TW_REP_START:
					BusCaptured = true;
					break;
				case TW_MT_ARB_LOST:
					continue;
				default:
					return false;
			}
		}
		
		if (!(BusCaptured))
		  return false;
		  
		TWDR = SlaveAddress;
		TWCR = ((1 << TWINT) | (1 << TWEN));
		while (!(TWCR & (1 << TWINT)));
		
		GPIOR0 = (TWSR & TW_STATUS_MASK);

		switch (TWSR & TW_STATUS_MASK)
		{
			case TW_MT_SLA_ACK:
			case TW_MR_SLA_ACK:
				return true;
			default:
				TWI_StopTransmission();
				break;
		}		  
	}
}
