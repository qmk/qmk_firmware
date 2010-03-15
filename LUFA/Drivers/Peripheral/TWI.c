/*
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

#include "TWI.h"

bool TWI_StartTransmission(uint8_t SlaveAddress, uint8_t TimeoutMS)
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
						return false;
				}
			}
			
			_delay_us(10);
		}
		
		if (!(BusCaptured))
		{
			TWCR = (1 << TWEN);
			return false;
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
		  return false;

		switch (TWSR & TW_STATUS_MASK)
		{
			case TW_MT_SLA_ACK:
			case TW_MR_SLA_ACK:
				return true;
			default:
				TWCR = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
				return false;
		}
	}
}
