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

/** \file
 *  \brief Module Clock Driver for the AVR USB XMEGA microcontrollers.
 *
 *  Clock management driver for the AVR USB XMEGA microcontrollers. This driver allows for the configuration
 *  of the various clocks within the device to clock the various peripherals.
 */

/** \ingroup Group_PlatformDrivers
 *  \defgroup Group_PlatformDrivers_XMEGAClocks AVR USB XMEGA Clock Management Driver - LUFA/Platform/XMEGA/ClockManagement.h
 *  \brief Module Clock Driver for the AVR USB XMEGA microcontrollers.
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_ModDescription Module Description
 *  Clock management driver for the AVR USB XMEGA microcontrollers. This driver allows for the configuration
 *  of the various clocks within the device to clock the various peripherals.
 *
 *  Usage Example:
 *  \code
 *		#include <LUFA/Platform/XMEGA/ClockManagement.h>
 *
 *		void main(void)
 *		{
 *			[TODO]
 *		}
 *  \endcode
 *
 *  @{
 */

#ifndef _XMEGA_CLOCK_MANAGEMENT_H_
#define _XMEGA_CLOCK_MANAGEMENT_H_

	/* Includes: */
		#include <LUFA/Common/Common.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Enum for the possible external oscillator types. */
			enum XMEGA_Extern_OSC_ClockTypes_t
			{
				EXOSC_MODE_2MHZ_MAX      = OSC_FRQRANGE_04TO2_gc,  /**< External crystal oscillator equal to or slower than 2MHz. */
				EXOSC_MODE_9MHZ_MAX      = OSC_FRQRANGE_2TO9_gc,   /**< External crystal oscillator equal to or slower than 9MHz. */
				EXOSC_MODE_12MHZ_MAX     = OSC_FRQRANGE_9TO12_gc,  /**< External crystal oscillator equal to or slower than 12MHz. */
				EXOSC_MODE_16MHZ_MAX     = OSC_FRQRANGE_12TO16_gc, /**< External crystal oscillator equal to or slower than 16MHz. */	
			};

			/** Enum for the possible external oscillator statup times. */
			enum XMEGA_Extern_OSC_ClockStartup_t
			{
				EXOSC_START_6CLK         = OSC_XOSCSEL_EXTCLK_gc,      /**< Wait 6 clock cycles before startup (external clock). */
				EXOSC_START_32KCLK       = OSC_XOSCSEL_32KHz_gc,       /**< Wait 32K clock cycles before startup (32.768KHz crystal). */
				EXOSC_START_256CLK       = OSC_XOSCSEL_XTAL_256CLK_gc, /**< Wait 256 clock cycles before startup. */
				EXOSC_START_1KCLK        = OSC_XOSCSEL_XTAL_1KCLK_gc,  /**< Wait 1K clock cycles before startup. */
				EXOSC_START_16KCLK       = OSC_XOSCSEL_XTAL_16KCLK_gc, /**< Wait 16K clock cycles before startup. */
			};
			
			/** Enum for the possible module clock sources. */
			enum XMEGA_System_ClockSource_t
			{
				CLOCK_SRC_INT_RC2MHZ    = 0, /**< Clock sourced from the Internal 2MHz RC Oscillator clock. */
				CLOCK_SRC_INT_RC32MHZ   = 1, /**< Clock sourced from the Internal 32MHz RC Oscillator clock. */
				CLOCK_SRC_INT_RC32KHZ   = 2, /**< Clock sourced from the Internal 32KHz RC Oscillator clock. */
				CLOCK_SRC_XOSC          = 3, /**< Clock sourced from the External Oscillator clock. */
				CLOCK_SRC_PLL           = 4, /**< Clock sourced from the Internal PLL clock. */
			};

		/* Inline Functions: */
			/** Starts the given external oscillator of the UC3 microcontroller, with the given options. This routine blocks until
			 *  the oscillator is ready for use.
			 *
			 *  \param[in] Channel  Index of the external oscillator to start.
			 *  \param[in] Type     Type of clock attached to the given oscillator channel, a value from \ref XMEGA_Extern_OSC_ClockTypes_t.
			 *  \param[in] Startup  Statup time of the external oscillator, a value from \ref XMEGA_Extern_OSC_ClockStartup_t.
			 *
			 *  \return Boolean \c true if the external oscillator was successfully started, \c false if invalid parameters specified.
			 */
			static inline uint8_t AVR32CLK_StartExternalOscillator(const uint8_t Channel,
			                                                       const uint8_t Type,
			                                                       const uint8_t Startup) ATTR_ALWAYS_INLINE;
			static inline uint8_t AVR32CLK_StartExternalOscillator(const uint8_t Channel,
			                                                       const uint8_t Type,
			                                                       const uint8_t Startup)
			{
				return false; // TODO
			}

			/** Stops the given external oscillator of the UC3 microcontroller.
			 *
			 *  \param[in] Channel  Index of the external oscillator to stop.
			 */
			static inline void AVR32CLK_StopExternalOscillator(const uint8_t Channel) ATTR_ALWAYS_INLINE;
			static inline void AVR32CLK_StopExternalOscillator(const uint8_t Channel)
			{
				return; // TODO
			}

			/** Starts the given PLL of the UC3 microcontroller, with the given options. This routine blocks until the PLL is ready for use.
			 *
			 *  \param[in] Channel     Index of the PLL to start.
			 *  \param[in] Source      Clock source for the PLL, a value from \ref XMEGA_System_ClockSource_t.
			 *  \param[in] SourceFreq  Frequency of the PLL's clock source, in Hz.
			 *  \param[in] Frequency   Target frequency of the PLL's output.
			 *
			 *  \return Boolean \c true if the PLL was successfully started, \c false if invalid parameters specified.
			 */
			static inline bool AVR32CLK_StartPLL(const uint8_t Channel,
			                                     const uint8_t Source,
			                                     const uint32_t SourceFreq,
			                                     const uint32_t Frequency) ATTR_ALWAYS_INLINE;
			static inline bool AVR32CLK_StartPLL(const uint8_t Channel,
			                                     const uint8_t Source,
			                                     const uint32_t SourceFreq,
			                                     const uint32_t Frequency)
			{
				return false; // TODO
			}

			/** Stops the given PLL of the UC3 microcontroller.
			 *
			 *  \param[in] Channel  Index of the PLL to stop.
			 */
			static inline void AVR32CLK_StopPLL(const uint8_t Channel) ATTR_ALWAYS_INLINE;
			static inline void AVR32CLK_StopPLL(const uint8_t Channel)
			{
				// TODO
			}
			
			/** Starts the given Generic Clock of the UC3 microcontroller, with the given options.
			 *
			 *  \param[in] Channel     Index of the Generic Clock to start.
			 *  \param[in] Source      Clock source for the Generic Clock, a value from \ref XMEGA_System_ClockSource_t.
			 *  \param[in] SourceFreq  Frequency of the Generic Clock's clock source, in Hz.
			 *  \param[in] Frequency   Target frequency of the Generic Clock's output.
			 *
			 *  \return Boolean \c true if the Generic Clock was successfully started, \c false if invalid parameters specified.
			 */
			static inline bool AVR32CLK_StartGenericClock(const uint8_t Channel,
			                                              const uint8_t Source,
			                                              const uint32_t SourceFreq,
			                                              const uint32_t Frequency) ATTR_ALWAYS_INLINE;
			static inline bool AVR32CLK_StartGenericClock(const uint8_t Channel,
			                                              const uint8_t Source,
			                                              const uint32_t SourceFreq,
			                                              const uint32_t Frequency)
			{
				return false; // TODO
			}
			
			/** Stops the given generic clock of the UC3 microcontroller.
			 *
			 *  \param[in] Channel  Index of the generic clock to stop.
			 */
			static inline void AVR32CLK_StopGenericClock(const uint8_t Channel) ATTR_ALWAYS_INLINE;
			static inline void AVR32CLK_StopGenericClock(const uint8_t Channel)
			{
				// TODO
			}
			
			/** Sets the clock source for the main microcontroller core. The given clock source should be configured
			 *  and ready for use before this function is called.
			 *
			 *  This function will configure the FLASH controller's wait states automatically to suit the given clock source.
			 *
			 *  \param[in] Source      Clock source for the CPU core, a value from \ref XMEGA_System_ClockSource_t.
			 *  \param[in] SourceFreq  Frequency of the CPU core's clock source, in Hz.
			 *
			 *  \return Boolean \c true if the CPU core clock was sucessfully altered, \c false if invalid parameters specified.
			 */
			static inline bool AVR32CLK_SetCPUClockSource(const uint8_t Source,
			                                              const uint32_t SourceFreq) ATTR_ALWAYS_INLINE;
			static inline bool AVR32CLK_SetCPUClockSource(const uint8_t Source,
			                                              const uint32_t SourceFreq)
			{
				return false // TODO
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
