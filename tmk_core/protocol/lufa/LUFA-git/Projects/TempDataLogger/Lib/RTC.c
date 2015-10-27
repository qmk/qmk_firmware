/*
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

#include "RTC.h"

#if defined(DUMMY_RTC)

/** Current dummy RTC time and date */
static volatile TimeDate_t DummyRTC_Count;

void RTC_Init(void)
{
	DummyRTC_Count.Hour   = 0;
	DummyRTC_Count.Minute = 0;
	DummyRTC_Count.Second = 0;
	DummyRTC_Count.Day    = 1;
	DummyRTC_Count.Month  = 1;
	DummyRTC_Count.Year   = 00;
}

void RTC_Tick500ms(void)
{
	static bool HalfSecondElapsed = false;

	HalfSecondElapsed = !HalfSecondElapsed;
	if (HalfSecondElapsed == false)
	  return;

	if (++DummyRTC_Count.Second < 60)
	  return;

	DummyRTC_Count.Second = 0;

	if (++DummyRTC_Count.Minute < 60)
	  return;

	DummyRTC_Count.Minute = 0;

	if (++DummyRTC_Count.Hour < 24)
	  return;

	DummyRTC_Count.Hour = 0;

	static const char MonthLength[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	uint8_t DaysInMonth = MonthLength[DummyRTC_Count.Month - 1];

	/* Check if we need to account for a leap year */
	if ((DummyRTC_Count.Month == 2) &&
	    ((!(DummyRTC_Count.Year % 400)) || ((DummyRTC_Count.Year % 100) && !(DummyRTC_Count.Year % 4))))
	{
		DaysInMonth++;
	}

	if (++DummyRTC_Count.Day <= DaysInMonth)
	  return;

	DummyRTC_Count.Day = 1;

	if (++DummyRTC_Count.Month <= 12)
	  return;

	DummyRTC_Count.Month = 1;
	DummyRTC_Count.Year++;
}

bool RTC_SetTimeDate(const TimeDate_t* NewTimeDate)
{
	GlobalInterruptDisable();
	DummyRTC_Count = *NewTimeDate;
	GlobalInterruptEnable();

	return true;
}

bool RTC_GetTimeDate(TimeDate_t* const TimeDate)
{
	GlobalInterruptDisable();
	*TimeDate = DummyRTC_Count;
	GlobalInterruptEnable();

	return true;
}

#else

void RTC_Init(void)
{
	/* Unused for a real external DS1307 RTC device */
}

void RTC_Tick500ms(void)
{
	/* Unused for a real external DS1307 RTC device */
}

bool RTC_SetTimeDate(const TimeDate_t* NewTimeDate)
{
	DS1307_DateTimeRegs_t NewRegValues;
	const uint8_t         WriteAddress = 0;

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

	// Write the new Time and Date into the DS1307
	if (TWI_WritePacket(DS1307_ADDRESS, 10, &WriteAddress, sizeof(WriteAddress),
	                   (uint8_t*)&NewRegValues, sizeof(DS1307_DateTimeRegs_t)) != TWI_ERROR_NoError)
	{
		return false;
	}

	return true;
}

bool RTC_GetTimeDate(TimeDate_t* const TimeDate)
{
	DS1307_DateTimeRegs_t CurrentRegValues;
	const uint8_t         ReadAddress = 0;

	// Read in the stored Time and Date from the DS1307
	if (TWI_ReadPacket(DS1307_ADDRESS, 10, &ReadAddress, sizeof(ReadAddress),
	                   (uint8_t*)&CurrentRegValues, sizeof(DS1307_DateTimeRegs_t)) != TWI_ERROR_NoError)
	{
		return false;
	}

	// Convert stored time value into decimal
	TimeDate->Second  = (CurrentRegValues.Byte1.Fields.TenSec  * 10) + CurrentRegValues.Byte1.Fields.Sec;
	TimeDate->Minute  = (CurrentRegValues.Byte2.Fields.TenMin  * 10) + CurrentRegValues.Byte2.Fields.Min;
	TimeDate->Hour    = (CurrentRegValues.Byte3.Fields.TenHour * 10) + CurrentRegValues.Byte3.Fields.Hour;

	// Convert stored date value into decimal
	TimeDate->Day    = (CurrentRegValues.Byte5.Fields.TenDay   * 10) + CurrentRegValues.Byte5.Fields.Day;
	TimeDate->Month  = (CurrentRegValues.Byte6.Fields.TenMonth * 10) + CurrentRegValues.Byte6.Fields.Month;
	TimeDate->Year   = (CurrentRegValues.Byte7.Fields.TenYear  * 10) + CurrentRegValues.Byte7.Fields.Year;

	return true;
}

#endif
