/*
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

#include "DS1307.h"

void DS1307_SetDate(uint8_t Day, uint8_t Month, uint8_t Year)
{
#if defined(DUMMY_RTC)
	return;
#endif

	DS1307_DateRegs_t CurrentRTCDate;		
	CurrentRTCDate.Byte1.TenDay   = (Day / 10);
	CurrentRTCDate.Byte1.Day      = (Day % 10);
	CurrentRTCDate.Byte2.TenMonth = (Month / 10);
	CurrentRTCDate.Byte2.Month    = (Month % 10);
	CurrentRTCDate.Byte3.TenYear  = (Year / 10);
	CurrentRTCDate.Byte3.Year     = (Year % 10);

	if (TWI_StartTransmission(DS1307_ADDRESS_WRITE, 10))
	{
		TWI_SendByte(DS1307_DATEREG_START);
		TWI_SendByte(CurrentRTCDate.Byte1.IntVal);
		TWI_SendByte(CurrentRTCDate.Byte2.IntVal);
		TWI_SendByte(CurrentRTCDate.Byte3.IntVal);
		
		TWI_StopTransmission();
	}
}

void DS1307_SetTime(uint8_t Hour, uint8_t Minute, uint8_t Second)
{
#if defined(DUMMY_RTC)
	return;
#endif

	DS1307_TimeRegs_t CurrentRTCTime;
	CurrentRTCTime.Byte1.TenSec  = (Second / 10);
	CurrentRTCTime.Byte1.Sec     = (Second % 10);
	CurrentRTCTime.Byte1.CH      = false;
	CurrentRTCTime.Byte2.TenMin  = (Minute / 10);
	CurrentRTCTime.Byte2.Min     = (Minute % 10);
	CurrentRTCTime.Byte3.TenHour = (Hour / 10);
	CurrentRTCTime.Byte3.Hour    = (Hour % 10);
	CurrentRTCTime.Byte3.TwelveHourMode = false;
	
	if (TWI_StartTransmission(DS1307_ADDRESS_WRITE, 10))
	{
		TWI_SendByte(DS1307_TIMEREG_START);
		TWI_SendByte(CurrentRTCTime.Byte1.IntVal);
		TWI_SendByte(CurrentRTCTime.Byte2.IntVal);
		TWI_SendByte(CurrentRTCTime.Byte3.IntVal);
		
		TWI_StopTransmission();
	}
}
		
void DS1307_GetDate(uint8_t* Day, uint8_t* Month, uint8_t* Year)
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

	*Day    = (CurrentRTCDate.Byte1.TenDay   * 10) + CurrentRTCDate.Byte1.Day;
	*Month  = (CurrentRTCDate.Byte2.TenMonth * 10) + CurrentRTCDate.Byte2.Month;
	*Year   = (CurrentRTCDate.Byte3.TenYear  * 10) + CurrentRTCDate.Byte3.Year;
}

void DS1307_GetTime(uint8_t* Hour, uint8_t* Minute, uint8_t* Second)
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

	*Second  = (CurrentRTCTime.Byte1.TenSec  * 10) + CurrentRTCTime.Byte1.Sec;
	*Minute  = (CurrentRTCTime.Byte2.TenMin  * 10) + CurrentRTCTime.Byte2.Min;
	*Hour    = (CurrentRTCTime.Byte3.TenHour * 10) + CurrentRTCTime.Byte3.Hour;
}
