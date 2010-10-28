/*
     Copyright (C) Dean Camera, 2010.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

#include "DS1307.h"

void DS1307_SetDate(const uint8_t Day,
                    const uint8_t Month,
                    const uint8_t Year)
{
#if defined(DUMMY_RTC)
	return;
#endif

	DS1307_DateRegs_t CurrentRTCDate;
	CurrentRTCDate.Byte1.Fields.TenDay   = (Day / 10);
	CurrentRTCDate.Byte1.Fields.Day      = (Day % 10);
	CurrentRTCDate.Byte2.Fields.TenMonth = (Month / 10);
	CurrentRTCDate.Byte2.Fields.Month    = (Month % 10);
	CurrentRTCDate.Byte3.Fields.TenYear  = (Year / 10);
	CurrentRTCDate.Byte3.Fields.Year     = (Year % 10);

	if (TWI_StartTransmission(DS1307_ADDRESS_WRITE, 10))
	{
		TWI_SendByte(DS1307_DATEREG_START);
		TWI_SendByte(CurrentRTCDate.Byte1.IntVal);
		TWI_SendByte(CurrentRTCDate.Byte2.IntVal);
		TWI_SendByte(CurrentRTCDate.Byte3.IntVal);

		TWI_StopTransmission();
	}
}

void DS1307_SetTime(const uint8_t Hour,
                    const uint8_t Minute,
                    const uint8_t Second)
{
#if defined(DUMMY_RTC)
	return;
#endif

	DS1307_TimeRegs_t CurrentRTCTime;
	CurrentRTCTime.Byte1.Fields.TenSec  = (Second / 10);
	CurrentRTCTime.Byte1.Fields.Sec     = (Second % 10);
	CurrentRTCTime.Byte1.Fields.CH      = false;
	CurrentRTCTime.Byte2.Fields.TenMin  = (Minute / 10);
	CurrentRTCTime.Byte2.Fields.Min     = (Minute % 10);
	CurrentRTCTime.Byte3.Fields.TenHour = (Hour / 10);
	CurrentRTCTime.Byte3.Fields.Hour    = (Hour % 10);
	CurrentRTCTime.Byte3.Fields.TwelveHourMode = false;

	if (TWI_StartTransmission(DS1307_ADDRESS_WRITE, 10))
	{
		TWI_SendByte(DS1307_TIMEREG_START);
		TWI_SendByte(CurrentRTCTime.Byte1.IntVal);
		TWI_SendByte(CurrentRTCTime.Byte2.IntVal);
		TWI_SendByte(CurrentRTCTime.Byte3.IntVal);

		TWI_StopTransmission();
	}
}

void DS1307_GetDate(uint8_t* const Day,
                    uint8_t* const Month,
                    uint8_t* const Year)
{
#if defined(DUMMY_RTC)
	*Day   = 1;
	*Month = 1;
	*Year  = 1;
	return;
#endif

	if (TWI_StartTransmission(DS1307_ADDRESS_WRITE, 10))
	{
		TWI_SendByte(DS1307_DATEREG_START);

		TWI_StopTransmission();
	}

	DS1307_DateRegs_t CurrentRTCDate;

	if (TWI_StartTransmission(DS1307_ADDRESS_READ, 10))
	{
		TWI_ReceiveByte(&CurrentRTCDate.Byte1.IntVal, false);
		TWI_ReceiveByte(&CurrentRTCDate.Byte2.IntVal, false);
		TWI_ReceiveByte(&CurrentRTCDate.Byte3.IntVal, true);

		TWI_StopTransmission();
	}

	*Day    = (CurrentRTCDate.Byte1.Fields.TenDay   * 10) + CurrentRTCDate.Byte1.Fields.Day;
	*Month  = (CurrentRTCDate.Byte2.Fields.TenMonth * 10) + CurrentRTCDate.Byte2.Fields.Month;
	*Year   = (CurrentRTCDate.Byte3.Fields.TenYear  * 10) + CurrentRTCDate.Byte3.Fields.Year;
}

void DS1307_GetTime(uint8_t* const Hour,
                    uint8_t* const Minute,
                    uint8_t* const Second)
{
#if defined(DUMMY_RTC)
	*Hour   = 1;
	*Minute = 1;
	*Second = 1;
	return;
#endif

	if (TWI_StartTransmission(DS1307_ADDRESS_WRITE, 10))
	{
		TWI_SendByte(DS1307_TIMEREG_START);

		TWI_StopTransmission();
	}

	DS1307_TimeRegs_t CurrentRTCTime;

	if (TWI_StartTransmission(DS1307_ADDRESS_READ, 10))
	{
		TWI_ReceiveByte(&CurrentRTCTime.Byte1.IntVal, false);
		TWI_ReceiveByte(&CurrentRTCTime.Byte2.IntVal, false);
		TWI_ReceiveByte(&CurrentRTCTime.Byte3.IntVal, true);

		TWI_StopTransmission();
	}

	*Second  = (CurrentRTCTime.Byte1.Fields.TenSec  * 10) + CurrentRTCTime.Byte1.Fields.Sec;
	*Minute  = (CurrentRTCTime.Byte2.Fields.TenMin  * 10) + CurrentRTCTime.Byte2.Fields.Min;
	*Hour    = (CurrentRTCTime.Byte3.Fields.TenHour * 10) + CurrentRTCTime.Byte3.Fields.Hour;
}

