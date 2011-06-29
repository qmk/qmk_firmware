/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#ifndef _CLOCK_MANAGEMENT_H_
#define _CLOCK_MANAGEMENT_H_

	/* Includes: */
		#include <avr32/io.h>
		#include <stdbool.h>
		#include <stdint.h>

		#include <LUFA/Common/Common.h>

	/* Macros: */
		enum Extern_OSC_ClockStartup_t
		{
			EXOSC_START_0CLK         = 0,
			EXOSC_START_64CLK        = 1,
			EXOSC_START_128CLK       = 2,
			EXOSC_START_2048CLK      = 3,
			EXOSC_START_4096CLK      = 4,
			EXOSC_START_8192CLK      = 5,
			EXOSC_START_16384CLK     = 6,
		};
		
		enum Extern_OSC_ClockMode_t
		{
			EXOSC_MODE_CLOCK         = 0,
			EXOSC_MODE_900KHZ_MAX    = 1,
			EXOSC_MODE_3MHZ_MAX      = 2,
			EXOSC_MODE_8MHZ_MAX      = 3,
			EXOSC_MODE_8MHZ_OR_MORE  = 4,			
		};
		
		enum
		{
			CLOCK_SRC_SLOW_CLK       = 0,
			CLOCK_SRC_OSC0           = 1,
			CLOCK_SRC_OSC1           = 2,
			CLOCK_SRC_PLL0           = 3,
			CLOCK_SRC_PLL1           = 4,
		};

	/* Inline Functions: */
		static inline bool AVR32CLK_StartExternalOscillator(const uint8_t Channel,
		                                                    const uint8_t Type,
		                                                    const uint8_t Startup)
		{
			AVR32_PM.OSCCTRL0.startup       = Startup;
			AVR32_PM.OSCCTRL0.mode          = Type;
			AVR32_PM.mcctrl                |= (1 << (AVR32_PM_MCCTRL_OSC0EN_OFFSET + Channel));

			while (!(AVR32_PM.poscsr & (1 << (AVR32_PM_POSCSR_OSC0RDY_OFFSET + Channel))));
			return true;
		}

		static inline void AVR32CLK_StopExternalOscillator(const uint8_t Channel)
		{
			AVR32_PM.mcctrl                &= ~(1 << (AVR32_PM_MCCTRL_OSC0EN_OFFSET + Channel));
		}

		static inline bool AVR32CLK_StartPLL(const uint8_t Channel,
		                                     const uint8_t Source,
		                                     const uint32_t SourceFreq,
		                                     const uint32_t Frequency)
		{
			switch (Source)
			{
				case CLOCK_SRC_OSC0:
					AVR32_PM.PLL[Channel].pllosc = 0;
					break;
				case CLOCK_SRC_OSC1:
					AVR32_PM.PLL[Channel].pllosc = 1;
					break;
				default:
					return false;
			}

			AVR32_PM.PLL[Channel].pllmul    = (Frequency / SourceFreq) ? (((Frequency / SourceFreq) - 1) / 2) : 0;
			AVR32_PM.PLL[Channel].plldiv    = 0;
			AVR32_PM.PLL[Channel].pllen     = true;

			while (!(AVR32_PM.poscsr & (1 << (AVR32_PM_POSCSR_LOCK0_OFFSET + Channel))));
			return true;
		}

		static inline void AVR32CLK_StopPLL(const uint8_t Channel)
		{
			AVR32_PM.PLL[Channel].pllen     = false;
		}
		
		static inline bool AVR32CLK_StartGenericClock(const uint8_t Channel,
		                                              const uint8_t Source,
		                                              const uint32_t SourceFreq,
		                                              const uint32_t Frequency)
		{
			switch (Source)
			{
				case CLOCK_SRC_OSC0:
					AVR32_PM.GCCTRL[Channel].pllsel = 0;
					AVR32_PM.GCCTRL[Channel].oscsel = 0;
					break;
				case CLOCK_SRC_OSC1:
					AVR32_PM.GCCTRL[Channel].pllsel = 0;
					AVR32_PM.GCCTRL[Channel].oscsel = 1;
					break;
				case CLOCK_SRC_PLL0:
					AVR32_PM.GCCTRL[Channel].pllsel = 1;
					AVR32_PM.GCCTRL[Channel].oscsel = 0;
					break;
				case CLOCK_SRC_PLL1:
					AVR32_PM.GCCTRL[Channel].pllsel = 1;
					AVR32_PM.GCCTRL[Channel].oscsel = 1;
					break;
				default:
					return false;
			}

			AVR32_PM.GCCTRL[Channel].diven  = (SourceFreq > Frequency) ? true : false;
			AVR32_PM.GCCTRL[Channel].div    = (((SourceFreq / Frequency) - 1) / 2);
			AVR32_PM.GCCTRL[Channel].cen    = true;
			
			return true;
		}
		
		static inline void AVR32CLK_StopGenericClock(const uint8_t Channel)
		{
			AVR32_PM.GCCTRL[Channel].cen    = false;
		}

		static inline bool AVR32CLK_SetCPUClockSource(const uint8_t Source,
		                                              const uint32_t SourceFreq)
		{
			AVR32_FLASHC.FCR.fws            = (SourceFreq > 30000000) ? true : false;

			switch (Source)
			{
				case CLOCK_SRC_SLOW_CLK:
					AVR32_PM.MCCTRL.mcsel   = 0;
					break;
				case CLOCK_SRC_OSC0:
					AVR32_PM.MCCTRL.mcsel   = 1;
					break;
				case CLOCK_SRC_PLL0:
					AVR32_PM.MCCTRL.mcsel   = 2;
					break;
				default:
					return false;
			}
			
			return true;
		}

#endif
