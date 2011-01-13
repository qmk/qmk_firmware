/*
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

#include "DS1307.h"

void DS1307_SetTimeDate(const TimeDate_t* NewTimeDate)
{
#if defined(DUMMY_RTC)
	return;
#endif

	DS1307_DateTimeRegs_t NewRegValues;

	// Convert new time data to the DS1307's time register layout
	NewRegValues.Byte1.Fields.TenSec    = (NewTimeDate->Second / 10);
	NewRegValues.Byte1.Fields.Sec       = (NewTimeDate->Second % 10);
	NewRegValues.Byte1.Fields.CH        = false;
	NewRegValues.Byte2.Fields.TenMin    = (NewTimeDate->Minute / 10);
	NewRegValues.Byte2.Fields.Min       = (NewTimeDate->Minute % 10);
	NewRegValues.Byte3.Fields.TenHour   = (NewTimeDate->Hour / 10);
	NewRegValues.Byte3.Fields.Hour      = (NewTimeDate->Hour % 10);
	NewRegValues.Byte3.Fields.TwelveHourMode = false;

	// Convert new date data to the DS1307's date register layout
	NewRegValues.Byte4.Fields.DayOfWeek = 0;
	NewRegValues.Byte5.Fields.TenDay    = (NewTimeDate->Day / 10);
	NewRegValues.Byte5.Fields.Day       = (NewTimeDate->Day % 10);
	NewRegValues.Byte6.Fields.TenMonth  = (NewTimeDate->Month / 10);
	NewRegValues.Byte6.Fields.Month     = (NewTimeDate->Month % 10);
	NewRegValues.Byte7.Fields.TenYear   = (NewTimeDate->Year / 10);
	NewRegValues.Byte7.Fields.Year      = (NewTimeDate->Year % 10);
	
	if (TWI_StartTransmission(DS1307_ADDRESS_WRITE, 10))
	{
		// Must start writing to the first address within the device		
		TWI_SendByte(0);

		// Write time data to the first set of device registers
		TWI_SendByte(NewRegValues.Byte1.IntVal);
		TWI_SendByte(NewRegValues.Byte2.IntVal);
		TWI_SendByte(NewRegValues.Byte3.IntVal);

		// Write date data to the second set of device registers
		TWI_SendByte(NewRegValues.Byte4.IntVal);
		TWI_SendByte(NewRegValues.Byte5.IntVal);
		TWI_SendByte(NewRegValues.Byte6.IntVal);
		TWI_SendByte(NewRegValues.Byte7.IntVal);
		
		TWI_StopTransmission();
	}
}

void DS1307_GetTimeDate(TimeDate_t* const TimeDate)
{
#if defined(DUMMY_RTC)
	TimeDate->Hour   = 1;
	TimeDate->Minute = 1;
	TimeDate->Second = 1;
	
	TimeDate->Day    = 1;
	TimeDate->Month  = 1;
	TimeDate->Year   = 1;
	
	return;
#endif

	if (TWI_StartTransmission(DS1307_ADDRESS_WRITE, 10))
	{
		// Must start reading from the first address within the device
		TWI_SendByte(0);
		TWI_StopTransmission();
	}

	DS1307_DateTimeRegs_t CurrentRegValues;
	
	if (TWI_StartTransmission(DS1307_ADDRESS_READ, 10))
	{
		// First set of registers store the current time
		TWI_ReceiveByte(&CurrentRegValues.Byte1.IntVal, false);
		TWI_ReceiveByte(&CurrentRegValues.Byte2.IntVal, false);
		TWI_ReceiveByte(&CurrentRegValues.Byte3.IntVal, false);

		// Second set of registers store the current date
		TWI_ReceiveByte(&CurrentRegValues.Byte4.IntVal, false);
		TWI_ReceiveByte(&CurrentRegValues.Byte5.IntVal, false);
		TWI_ReceiveByte(&CurrentRegValues.Byte6.IntVal, false);
		TWI_ReceiveByte(&CurrentRegValues.Byte7.IntVal, true);
		
		TWI_StopTransmission();
	}

	// Convert stored time value into decimal
	TimeDate->Second  = (CurrentRegValues.Byte1.Fields.TenSec  * 10) + CurrentRegValues.Byte1.Fields.Sec;
	TimeDate->Minute  = (CurrentRegValues.Byte2.Fields.TenMin  * 10) + CurrentRegValues.Byte2.Fields.Min;
	TimeDate->Hour    = (CurrentRegValues.Byte3.Fields.TenHour * 10) + CurrentRegValues.Byte3.Fields.Hour;

	// Convert stored date value into decimal
	TimeDate->Day    = (CurrentRegValues.Byte5.Fields.TenDay   * 10) + CurrentRegValues.Byte5.Fields.Day;
	TimeDate->Month  = (CurrentRegValues.Byte6.Fields.TenMonth * 10) + CurrentRegValues.Byte6.Fields.Month;
	TimeDate->Year   = (CurrentRegValues.Byte7.Fields.TenYear  * 10) + CurrentRegValues.Byte7.Fields.Year;
}

