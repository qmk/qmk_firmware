/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief Module Clock Driver for the AVR32 UC3 microcontrollers.
 *
 *  Clock management driver for the AVR32 UC3 microcontrollers. This driver allows for the configuration
 *  of the various clocks within the device to clock the various peripherals.
 */

/** \ingroup Group_PlatformDrivers_UC3
 *  \defgroup Group_PlatformDrivers_UC3Clocks Clock Management Driver - LUFA/Platform/UC3/ClockManagement.h
 *  \brief Module Clock Driver for the AVR32 UC3 microcontrollers.
 *
 *  \section Sec_PlatformDrivers_UC3Clocks_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_PlatformDrivers_UC3Clocks_ModDescription Module Description
 *  Clock management driver for the AVR32 UC3 microcontrollers. This driver allows for the configuration
 *  of the various clocks within the device to clock the various peripherals.
 *
 *  Usage Example:
 *  \code
 *		#include <LUFA/Platform/UC3/ClockManagement.h>
 *
 *		void main(void)
 *		{
 *			// Start the master external oscillator which will be used as the main clock reference
 *			UC3CLK_StartExternalOscillator(0, EXOSC_MODE_8MHZ_OR_MORE, EXOSC_START_0CLK);
 *
 *			// Start the PLL for the CPU clock, switch CPU to it
 *			UC3CLK_StartPLL(0, CLOCK_SRC_OSC0, 12000000, F_CPU);
 *			UC3CLK_SetCPUClockSource(CLOCK_SRC_PLL0, F_CPU);
 *
 *			// Start the PLL for the USB Generic Clock module
 *			UC3CLK_StartPLL(1, CLOCK_SRC_OSC0, 12000000, 48000000);
 *		}
 *  \endcode
 *
 *  @{
 */

#ifndef _UC3_CLOCK_MANAGEMENT_H_
#define _UC3_CLOCK_MANAGEMENT_H_

	/* Includes: */
		#include "../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Enum for the possible external oscillator types. */
			enum UC3_Extern_OSC_ClockTypes_t
			{
				EXOSC_MODE_CLOCK         = AVR32_PM_OSCCTRL0_MODE_EXT_CLOCK,  /**< External clock (non-crystal) mode. */
				EXOSC_MODE_900KHZ_MAX    = AVR32_PM_OSCCTRL0_MODE_CRYSTAL_G0, /**< External crystal oscillator equal to or slower than 900KHz. */
				EXOSC_MODE_3MHZ_MAX      = AVR32_PM_OSCCTRL0_MODE_CRYSTAL_G1, /**< External crystal oscillator equal to or slower than 3MHz. */
				EXOSC_MODE_8MHZ_MAX      = AVR32_PM_OSCCTRL0_MODE_CRYSTAL_G2, /**< External crystal oscillator equal to or slower than 8MHz. */
				EXOSC_MODE_8MHZ_OR_MORE  = AVR32_PM_OSCCTRL0_MODE_CRYSTAL_G3, /**< External crystal oscillator equal to or faster than 8MHz. */
			};

			/** Enum for the possible external oscillator startup times. */
			enum UC3_Extern_OSC_ClockStartup_t
			{
				EXOSC_START_0CLK         = AVR32_PM_OSCCTRL0_STARTUP_0_RCOSC,     /**< Immediate startup, no delay. */
				EXOSC_START_64CLK        = AVR32_PM_OSCCTRL0_STARTUP_64_RCOSC,    /**< Wait 64 clock cycles before startup for stability. */
				EXOSC_START_128CLK       = AVR32_PM_OSCCTRL0_STARTUP_128_RCOSC,   /**< Wait 128 clock cycles before startup for stability. */
				EXOSC_START_2048CLK      = AVR32_PM_OSCCTRL0_STARTUP_2048_RCOSC,  /**< Wait 2048 clock cycles before startup for stability. */
				EXOSC_START_4096CLK      = AVR32_PM_OSCCTRL0_STARTUP_4096_RCOSC,  /**< Wait 4096 clock cycles before startup for stability. */
				EXOSC_START_8192CLK      = AVR32_PM_OSCCTRL0_STARTUP_8192_RCOSC,  /**< Wait 8192 clock cycles before startup for stability. */
				EXOSC_START_16384CLK     = AVR32_PM_OSCCTRL0_STARTUP_16384_RCOSC, /**< Wait 16384 clock cycles before startup for stability. */
			};

			/** Enum for the possible module clock sources. */
			enum UC3_System_ClockSource_t
			{
				CLOCK_SRC_SLOW_CLK       = 0, /**< Clock sourced from the internal slow clock. */
				CLOCK_SRC_OSC0           = 1, /**< Clock sourced from the Oscillator 0 clock. */
				CLOCK_SRC_OSC1           = 2, /**< Clock sourced from the Oscillator 1 clock. */
				CLOCK_SRC_PLL0           = 3, /**< Clock sourced from the PLL 0 clock. */
				CLOCK_SRC_PLL1           = 4, /**< Clock sourced from the PLL 1 clock. */
			};

		/* Inline Functions: */
			/** Starts the given external oscillator of the UC3 microcontroller, with the given options. This routine blocks until
			 *  the oscillator is ready for use.
			 *
			 *  \param[in] Channel  Index of the external oscillator to start.
			 *  \param[in] Type     Type of clock attached to the given oscillator channel, a value from \ref UC3_Extern_OSC_ClockTypes_t.
			 *  \param[in] Startup  Startup time of the external oscillator, a value from \ref UC3_Extern_OSC_ClockStartup_t.
			 *
			 *  \return Boolean \c true if the external oscillator was successfully started, \c false if invalid parameters specified.
			 */
			static inline bool UC3CLK_StartExternalOscillator(const uint8_t Channel,
			                                                  const uint8_t Type,
			                                                  const uint8_t Startup) ATTR_ALWAYS_INLINE;
			static inline bool UC3CLK_StartExternalOscillator(const uint8_t Channel,
			                                                  const uint8_t Type,
			                                                  const uint8_t Startup)
			{
				switch (Channel)
				{
					case 0:
						AVR32_PM.OSCCTRL0.startup = Startup;
						AVR32_PM.OSCCTRL0.mode    = Type;
						break;
					case 1:
						AVR32_PM.OSCCTRL1.startup = Startup;
						AVR32_PM.OSCCTRL1.mode    = Type;
						break;
					default:
						return false;
				}

				AVR32_PM.mcctrl |= (1 << (AVR32_PM_MCCTRL_OSC0EN_OFFSET + Channel));

				while (!(AVR32_PM.poscsr & (1 << (AVR32_PM_POSCSR_OSC0RDY_OFFSET + Channel))));
				return true;
			}

			/** Stops the given external oscillator of the UC3 microcontroller.
			 *
			 *  \param[in] Channel  Index of the external oscillator to stop.
			 */
			static inline void UC3CLK_StopExternalOscillator(const uint8_t Channel) ATTR_ALWAYS_INLINE;
			static inline void UC3CLK_StopExternalOscillator(const uint8_t Channel)
			{
				AVR32_PM.mcctrl &= ~(1 << (AVR32_PM_MCCTRL_OSC0EN_OFFSET + Channel));
			}

			/** Starts the given PLL of the UC3 microcontroller, with the given options. This routine blocks until the PLL is ready for use.
			 *
			 *  \attention The output frequency must be equal to or greater than the source frequency.
			 *
			 *  \param[in] Channel     Index of the PLL to start.
			 *  \param[in] Source      Clock source for the PLL, a value from \ref UC3_System_ClockSource_t.
			 *  \param[in] SourceFreq  Frequency of the PLL's clock source, in Hz.
			 *  \param[in] Frequency   Target frequency of the PLL's output.
			 *
			 *  \return Boolean \c true if the PLL was successfully started, \c false if invalid parameters specified.
			 */
			static inline bool UC3CLK_StartPLL(const uint8_t Channel,
			                                   const uint8_t Source,
			                                   const uint32_t SourceFreq,
			                                   const uint32_t Frequency) ATTR_ALWAYS_INLINE;
			static inline bool UC3CLK_StartPLL(const uint8_t Channel,
			                                   const uint8_t Source,
			                                   const uint32_t SourceFreq,
			                                   const uint32_t Frequency)
			{
				if (SourceFreq > Frequency)
				  return false;

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

				AVR32_PM.PLL[Channel].pllmul = (Frequency / SourceFreq) ? (((Frequency / SourceFreq) - 1) / 2) : 0;
				AVR32_PM.PLL[Channel].plldiv = 0;
				AVR32_PM.PLL[Channel].pllen  = true;

				while (!(AVR32_PM.poscsr & (1 << (AVR32_PM_POSCSR_LOCK0_OFFSET + Channel))));
				return true;
			}

			/** Stops the given PLL of the UC3 microcontroller.
			 *
			 *  \param[in] Channel  Index of the PLL to stop.
			 */
			static inline void UC3CLK_StopPLL(const uint8_t Channel) ATTR_ALWAYS_INLINE;
			static inline void UC3CLK_StopPLL(const uint8_t Channel)
			{
				AVR32_PM.PLL[Channel].pllen = false;
			}

			/** Starts the given Generic Clock of the UC3 microcontroller, with the given options.
			 *
			 *  \param[in] Channel     Index of the Generic Clock to start.
			 *  \param[in] Source      Clock source for the Generic Clock, a value from \ref UC3_System_ClockSource_t.
			 *  \param[in] SourceFreq  Frequency of the Generic Clock's clock source, in Hz.
			 *  \param[in] Frequency   Target frequency of the Generic Clock's output.
			 *
			 *  \return Boolean \c true if the Generic Clock was successfully started, \c false if invalid parameters specified.
			 */
			static inline bool UC3CLK_StartGenericClock(const uint8_t Channel,
			                                            const uint8_t Source,
			                                            const uint32_t SourceFreq,
			                                            const uint32_t Frequency) ATTR_ALWAYS_INLINE;
			static inline bool UC3CLK_StartGenericClock(const uint8_t Channel,
			                                            const uint8_t Source,
			                                            const uint32_t SourceFreq,
			                                            const uint32_t Frequency)
			{
				if (Channel >= AVR32_PM_GCLK_NUM)
				  return false;

				if (SourceFreq < Frequency)
				  return false;

				switch (Source)
				{
					case CLOCK_SRC_OSC0:
						AVR32_PM.GCCTRL[Channel].pllsel = false;
						AVR32_PM.GCCTRL[Channel].oscsel = 0;
						break;
					case CLOCK_SRC_OSC1:
						AVR32_PM.GCCTRL[Channel].pllsel = false;
						AVR32_PM.GCCTRL[Channel].oscsel = 1;
						break;
					case CLOCK_SRC_PLL0:
						AVR32_PM.GCCTRL[Channel].pllsel = true;
						AVR32_PM.GCCTRL[Channel].oscsel = 0;
						break;
					case CLOCK_SRC_PLL1:
						AVR32_PM.GCCTRL[Channel].pllsel = true;
						AVR32_PM.GCCTRL[Channel].oscsel = 1;
						break;
					default:
						return false;
				}

				AVR32_PM.GCCTRL[Channel].diven = (SourceFreq > Frequency) ? true : false;
				AVR32_PM.GCCTRL[Channel].div   = (((SourceFreq / Frequency) - 1) / 2);
				AVR32_PM.GCCTRL[Channel].cen   = true;

				return true;
			}

			/** Stops the given generic clock of the UC3 microcontroller.
			 *
			 *  \param[in] Channel  Index of the generic clock to stop.
			 *
			 *  \return Boolean \c true if the generic clock was successfully stopped, \c false if invalid parameters specified.
			 */
			static inline bool UC3CLK_StopGenericClock(const uint8_t Channel) ATTR_ALWAYS_INLINE;
			static inline bool UC3CLK_StopGenericClock(const uint8_t Channel)
			{
				if (Channel >= AVR32_PM_GCLK_NUM)
				  return false;

				AVR32_PM.GCCTRL[Channel].cen = false;

				return true;
			}

			/** Sets the clock source for the main microcontroller core. The given clock source should be configured
			 *  and ready for use before this function is called.
			 *
			 *  This function will configure the FLASH controller's wait states automatically to suit the given clock source.
			 *
			 *  \param[in] Source      Clock source for the CPU core, a value from \ref UC3_System_ClockSource_t.
			 *  \param[in] SourceFreq  Frequency of the CPU core's clock source, in Hz.
			 *
			 *  \return Boolean \c true if the CPU core clock was successfully altered, \c false if invalid parameters specified.
			 */
			static inline bool UC3CLK_SetCPUClockSource(const uint8_t Source,
			                                            const uint32_t SourceFreq) ATTR_ALWAYS_INLINE;
			static inline bool UC3CLK_SetCPUClockSource(const uint8_t Source,
			                                            const uint32_t SourceFreq)
			{
				if (SourceFreq > AVR32_PM_CPU_MAX_FREQ)
				  return false;

				AVR32_FLASHC.FCR.fws = (SourceFreq > AVR32_FLASHC_FWS_0_MAX_FREQ) ? true : false;

				switch (Source)
				{
					#if defined(AVR32_PM_MCCTRL_MCSEL_SLOW)
					case CLOCK_SRC_SLOW_CLK:
						AVR32_PM.MCCTRL.mcsel = AVR32_PM_MCCTRL_MCSEL_SLOW;
						break;
					#endif
					#if defined(AVR32_PM_MCCTRL_MCSEL_OSC0)
					case CLOCK_SRC_OSC0:
						AVR32_PM.MCCTRL.mcsel = AVR32_PM_MCCTRL_MCSEL_OSC0;
						break;
					#endif
					#if defined(AVR32_PM_MCCTRL_MCSEL_PLL0)
					case CLOCK_SRC_PLL0:
						AVR32_PM.MCCTRL.mcsel = AVR32_PM_MCCTRL_MCSEL_PLL0;
						break;
					#endif
					default:
						return false;
				}

				return true;
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

