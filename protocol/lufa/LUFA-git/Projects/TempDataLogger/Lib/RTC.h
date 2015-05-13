/*
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

#ifndef _RTC_H_
#define _RTC_H_

	/* Includes: */
		#include <avr/io.h>

		#include <LUFA/Drivers/Peripheral/TWI.h>

		#include "Config/AppConfig.h"

	/* Type Defines: */
		typedef struct
		{
			uint8_t Hour;
			uint8_t Minute;
			uint8_t Second;
			uint8_t Day;
			uint8_t Month;
			uint8_t Year;
		} TimeDate_t;

		typedef struct
		{
			union
			{
				struct
				{
					unsigned Sec            : 4;
					unsigned TenSec         : 3;
					unsigned CH             : 1;
				} Fields;

				uint8_t IntVal;
			} Byte1;

			union
			{
				struct
				{
					unsigned Min            : 4;
					unsigned TenMin         : 3;
					unsigned Reserved       : 1;
				} Fields;

				uint8_t IntVal;
			} Byte2;

			union
			{
				struct
				{
					unsigned Hour            : 4;
					unsigned TenHour         : 2;
					unsigned TwelveHourMode  : 1;
					unsigned Reserved        : 1;
				} Fields;

				uint8_t IntVal;
			} Byte3;

			union
			{
				struct
				{
					unsigned DayOfWeek       : 3;
					unsigned Reserved        : 5;
				} Fields;

				uint8_t IntVal;
			} Byte4;

			union
			{
				struct
				{
					unsigned Day             : 4;
					unsigned TenDay          : 2;
					unsigned Reserved        : 2;
				} Fields;

				uint8_t IntVal;
			} Byte5;

			union
			{
				struct
				{
					unsigned Month           : 4;
					unsigned TenMonth        : 1;
					unsigned Reserved        : 3;
				} Fields;

				uint8_t IntVal;
			} Byte6;

			union
			{
				struct
				{
					unsigned Year            : 4;
					unsigned TenYear         : 4;
				} Fields;

				uint8_t IntVal;
			} Byte7;
		} DS1307_DateTimeRegs_t;

	/* Macros: */
		/** TWI address of the DS1307 device on the bus. */
		#define DS1307_ADDRESS       0xD0

	/* Function Prototypes: */
		void RTC_Init(void);
		void RTC_Tick500ms(void);
		bool RTC_SetTimeDate(const TimeDate_t* NewTimeDate);
		bool RTC_GetTimeDate(TimeDate_t* const TimeDate);

#endif

