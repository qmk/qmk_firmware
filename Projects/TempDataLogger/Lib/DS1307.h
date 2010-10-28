/*
     Copyright (C) Dean Camera, 2010.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

#ifndef _DS1307_H_
#define _DS1307_H_

	/* Includes: */
		#include <avr/io.h>

		#include <LUFA/Drivers/Peripheral/TWI.h>

	/* Type Defines: */
		typedef struct
		{
			union
			{
				struct
				{
					unsigned int Sec            : 4;
					unsigned int TenSec         : 3;
					unsigned int CH             : 1;
				} Fields;

				uint8_t IntVal;
			} Byte1;

			union
			{
				struct
				{
					unsigned int Min            : 4;
					unsigned int TenMin         : 3;
					unsigned int Reserved       : 1;
				} Fields;

				uint8_t IntVal;
			} Byte2;

			union
			{
				struct
				{
					unsigned int Hour            : 4;
					unsigned int TenHour         : 2;
					unsigned int TwelveHourMode  : 1;
					unsigned int Reserved        : 1;
				} Fields;

				uint8_t IntVal;
			} Byte3;
		} DS1307_TimeRegs_t;

		typedef struct
		{
			union
			{
				struct
				{
					unsigned int Day             : 4;
					unsigned int TenDay          : 2;
					unsigned int Reserved        : 2;
				} Fields;

				uint8_t IntVal;
			} Byte1;

			union
			{
				struct
				{
					unsigned int Month           : 4;
					unsigned int TenMonth        : 1;
					unsigned int Reserved        : 3;
				} Fields;

				uint8_t IntVal;
			} Byte2;

			union
			{
				struct
				{
					unsigned int Year            : 4;
					unsigned int TenYear         : 4;
				} Fields;

				uint8_t IntVal;
			} Byte3;
		} DS1307_DateRegs_t;

	/* Macros: */
		#define DS1307_TIMEREG_START  0x00
		#define DS1307_DATEREG_START  0x04

		#define DS1307_ADDRESS_READ   0b11010001
		#define DS1307_ADDRESS_WRITE  0b11010000

	/* Function Prototypes: */
		void DS1307_SetDate(const uint8_t Day,
		                    const uint8_t Month,
		                    const uint8_t Year);
		void DS1307_SetTime(const uint8_t Hour,
		                    const uint8_t Minute,
		                    const uint8_t Second);
		void DS1307_GetDate(uint8_t* const Day,
		                    uint8_t* const Month,
		                    uint8_t* const Year);
		void DS1307_GetTime(uint8_t* const Hour,
		                    uint8_t* const Minute,
		                    uint8_t* const Second);

#endif

