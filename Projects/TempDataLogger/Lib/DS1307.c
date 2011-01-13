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

	DS1307_TimeRegs_t CurrentRTCTime;
	DS1307_DateRegs_t CurrentRTCDate;

	// Convert new time data to the DS1307's time register layout
	CurrentRTCTime.Byte1.Fields.TenSec  = (NewTimeDate->Second / 10);
	CurrentRTCTime.Byte1.Fields.Sec     = (NewTimeDate->Second % 10);
	CurrentRTCTime.Byte1.Fields.CH      = false;
	CurrentRTCTime.Byte2.Fields.TenMin  = (NewTimeDate->Minute / 10);
	CurrentRTCTime.Byte2.Fields.Min     = (NewTimeDate->Minute % 10);
	CurrentRTCTime.Byte3.Fields.TenHour = (NewTimeDate->Hour / 10);
	CurrentRTCTime.Byte3.Fields.Hour    = (NewTimeDate->Hour % 10);
	CurrentRTCTime.Byte3.Fields.TwelveHourMode = false;

	// Convert new date data to the DS1307's date register layout
	CurrentRTCDate.Byte1.Fields.TenDay   = (NewTimeDate->Day / 10);
	CurrentRTCDate.Byte1.Fields.Day      = (NewTimeDate->Day % 10);
	CurrentRTCDate.Byte2.Fields.TenMonth = (NewTimeDate->Month / 10);
	CurrentRTCDate.Byte2.Fields.Month    = (NewTimeDate->Month % 10);
	CurrentRTCDate.Byte3.Fields.TenYear  = (NewTimeDate->Year / 10);
	CurrentRTCDate.Byte3.Fields.Year     = (NewTimeDate->Year % 10);
	
	if (TWI_StartTransmission(DS1307_ADDRESS_WRITE, 10))
	{
		// Must start writing to the first address within the device		
		TWI_SendByte(0);

		// Write time data to the first set of device registers
		TWI_SendByte(CurrentRTCTime.Byte1.IntVal);
		TWI_SendByte(CurrentRTCTime.Byte2.IntVal);
		TWI_SendByte(CurrentRTCTime.Byte3.IntVal);

		// Write date data to the second set of device registers
		TWI_SendByte(CurrentRTCDate.Byte1.IntVal);
		TWI_SendByte(CurrentRTCDate.Byte2.IntVal);
		TWI_SendByte(CurrentRTCDate.Byte3.IntVal);
		
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

	DS1307_TimeRegs_t CurrentRTCTime;
	DS1307_DateRegs_t CurrentRTCDate;
	
	if (TWI_StartTransmission(DS1307_ADDRESS_READ, 10))
	{
		// First set of registers store the current time
		TWI_ReceiveByte(&CurrentRTCTime.Byte1.IntVal, false);
		TWI_ReceiveByte(&CurrentRTCTime.Byte2.IntVal, false);
		TWI_ReceiveByte(&CurrentRTCTime.Byte3.IntVal, false);

		// Second set of registers store the current date
		TWI_ReceiveByte(&CurrentRTCDate.Byte1.IntVal, false);
		TWI_ReceiveByte(&CurrentRTCDate.Byte2.IntVal, false);
		TWI_ReceiveByte(&CurrentRTCDate.Byte3.IntVal, true);
		
		TWI_StopTransmission();
	}

	// Convert stored time value into decimal
	TimeDate->Second  = (CurrentRTCTime.Byte1.Fields.TenSec  * 10) + CurrentRTCTime.Byte1.Fields.Sec;
	TimeDate->Minute  = (CurrentRTCTime.Byte2.Fields.TenMin  * 10) + CurrentRTCTime.Byte2.Fields.Min;
	TimeDate->Hour    = (CurrentRTCTime.Byte3.Fields.TenHour * 10) + CurrentRTCTime.Byte3.Fields.Hour;

	// Convert stored date value into decimal
	TimeDate->Day    = (CurrentRTCDate.Byte1.Fields.TenDay   * 10) + CurrentRTCDate.Byte1.Fields.Day;
	TimeDate->Month  = (CurrentRTCDate.Byte2.Fields.TenMonth * 10) + CurrentRTCDate.Byte2.Fields.Month;
	TimeDate->Year   = (CurrentRTCDate.Byte3.Fields.TenYear  * 10) + CurrentRTCDate.Byte3.Fields.Year;
}

