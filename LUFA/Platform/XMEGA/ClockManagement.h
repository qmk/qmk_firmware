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
 *  \brief Module Clock Driver for the AVR USB XMEGA microcontrollers.
 *
 *  Clock management driver for the AVR USB XMEGA microcontrollers. This driver allows for the configuration
 *  of the various clocks within the device to clock the various peripherals.
 */

/** \ingroup Group_PlatformDrivers_XMEGA
 *  \defgroup Group_PlatformDrivers_XMEGAClocks Clock Management Driver - LUFA/Platform/XMEGA/ClockManagement.h
 *  \brief Module Clock Driver for the AVR USB XMEGA microcontrollers.
 *
 *  \section Sec_PlatformDrivers_XMEGAClocks_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_PlatformDrivers_XMEGAClocks_ModDescription Module Description
 *  Clock management driver for the AVR USB XMEGA microcontrollers. This driver allows for the configuration
 *  of the various clocks within the device to clock the various peripherals.
 *
 *  Usage Example:
 *  \code
 *   	#include <LUFA/Platform/XMEGA/ClockManagement.h>
 *
 *   	void main(void)
 *   	{
 *   		// Start the PLL to multiply the 2MHz RC oscillator to F_CPU and switch the CPU core to run from it
 *   		XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
 *   		XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);
 *
 *   		// Start the 32MHz internal RC oscillator and start the DFLL to increase it to F_USB using the USB SOF as a reference
 *   		XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
 *   		XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);
 *   	}
 *  \endcode
 *
 *  @{
 */

#ifndef _XMEGA_CLOCK_MANAGEMENT_H_
#define _XMEGA_CLOCK_MANAGEMENT_H_

	/* Includes: */
		#include "../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Enum for the possible external oscillator frequency ranges. */
			enum XMEGA_Extern_OSC_ClockFrequency_t
			{
				EXOSC_FREQ_2MHZ_MAX      = OSC_FRQRANGE_04TO2_gc,  /**< External crystal oscillator equal to or slower than 2MHz. */
				EXOSC_FREQ_9MHZ_MAX      = OSC_FRQRANGE_2TO9_gc,   /**< External crystal oscillator equal to or slower than 9MHz. */
				EXOSC_FREQ_12MHZ_MAX     = OSC_FRQRANGE_9TO12_gc,  /**< External crystal oscillator equal to or slower than 12MHz. */
				EXOSC_FREQ_16MHZ_MAX     = OSC_FRQRANGE_12TO16_gc, /**< External crystal oscillator equal to or slower than 16MHz. */
			};

			/** Enum for the possible external oscillator startup times. */
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

			/** Enum for the possible DFLL clock reference sources. */
			enum XMEGA_System_DFLLReference_t
			{
				DFLL_REF_INT_RC32KHZ   = 0, /**< Reference clock sourced from the Internal 32KHz RC Oscillator clock. */
				DFLL_REF_EXT_RC32KHZ   = 1, /**< Reference clock sourced from the External 32KHz RC Oscillator clock connected to TOSC pins. */
				DFLL_REF_INT_USBSOF    = 2, /**< Reference clock sourced from the USB Start Of Frame packets. */
			};

		/* Inline Functions: */
			/** Write a value to a location protected by the XMEGA CCP protection mechanism. This function uses inline assembly to ensure that
			 *  the protected address is written to within four clock cycles of the CCP key being written.
			 *
			 *  \param[in] Address  Address to write to, a memory address protected by the CCP mechanism
			 *  \param[in] Value    Value to write to the protected location
			 */
			static inline void XMEGACLK_CCP_Write(volatile void* Address, const uint8_t Value) ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline void XMEGACLK_CCP_Write(volatile void* Address, const uint8_t Value)
			{
				__asm__ __volatile__ (
					"out %0, __zero_reg__" "\n\t" /* Zero RAMPZ using fixed zero value register */
					"movw r30, %1"         "\n\t" /* Copy address to Z register pair */
					"out %2, %3"           "\n\t" /* Write key to CCP register */
					"st Z, %4"             "\n\t" /* Indirectly write value to address */
					: /* No output operands */
					: /* Input operands: */ "m" (RAMPZ), "e" (Address), "m" (CCP), "r" (CCP_IOREG_gc), "r" (Value)
					: /* Clobbered registers: */ "r30", "r31"
				);
			}

			/** Starts the external oscillator of the XMEGA microcontroller, with the given options. This routine blocks until
			 *  the oscillator is ready for use.
			 *
			 *  \param[in] FreqRange  Frequency range of the external oscillator, a value from \ref XMEGA_Extern_OSC_ClockFrequency_t.
			 *  \param[in] Startup    Startup time of the external oscillator, a value from \ref XMEGA_Extern_OSC_ClockStartup_t.
			 *
			 *  \return Boolean \c true if the external oscillator was successfully started, \c false if invalid parameters specified.
			 */
			static inline bool XMEGACLK_StartExternalOscillator(const uint8_t FreqRange,
			                                                    const uint8_t Startup) ATTR_ALWAYS_INLINE;
			static inline bool XMEGACLK_StartExternalOscillator(const uint8_t FreqRange,
			                                                    const uint8_t Startup)
			{
				OSC.XOSCCTRL  = (FreqRange | ((Startup == EXOSC_START_32KCLK) ? OSC_X32KLPM_bm : 0) | Startup);
				OSC.CTRL     |= OSC_XOSCEN_bm;

				while (!(OSC.STATUS & OSC_XOSCRDY_bm));
				return true;
			}

			/** Stops the external oscillator of the XMEGA microcontroller. */
			static inline void XMEGACLK_StopExternalOscillator(void) ATTR_ALWAYS_INLINE;
			static inline void XMEGACLK_StopExternalOscillator(void)
			{
				OSC.CTRL     &= ~OSC_XOSCEN_bm;
			}

			/** Starts the given internal oscillator of the XMEGA microcontroller, with the given options. This routine blocks until
			 *  the oscillator is ready for use.
			 *
			 *  \param[in] Source  Internal oscillator to start, a value from \ref XMEGA_System_ClockSource_t.
			 *
			 *  \return Boolean \c true if the internal oscillator was successfully started, \c false if invalid parameters specified.
			 */
			static inline bool XMEGACLK_StartInternalOscillator(const uint8_t Source) ATTR_ALWAYS_INLINE;
			static inline bool XMEGACLK_StartInternalOscillator(const uint8_t Source)
			{
				switch (Source)
				{
					case CLOCK_SRC_INT_RC2MHZ:
						OSC.CTRL |= OSC_RC2MEN_bm;
						while (!(OSC.STATUS & OSC_RC2MRDY_bm));
						return true;
					case CLOCK_SRC_INT_RC32MHZ:
						OSC.CTRL |= OSC_RC32MEN_bm;
						while (!(OSC.STATUS & OSC_RC32MRDY_bm));
						return true;
					case CLOCK_SRC_INT_RC32KHZ:
						OSC.CTRL |= OSC_RC32KEN_bm;
						while (!(OSC.STATUS & OSC_RC32KRDY_bm));
						return true;
					default:
						return false;
				}
			}

			/** Stops the given internal oscillator of the XMEGA microcontroller.
			 *
			 *  \param[in] Source  Internal oscillator to stop, a value from \ref XMEGA_System_ClockSource_t.
			 *
			 *  \return Boolean \c true if the internal oscillator was successfully stopped, \c false if invalid parameters specified.
			 */
			static inline bool XMEGACLK_StopInternalOscillator(const uint8_t Source) ATTR_ALWAYS_INLINE;
			static inline bool XMEGACLK_StopInternalOscillator(const uint8_t Source)
			{
				switch (Source)
				{
					case CLOCK_SRC_INT_RC2MHZ:
						OSC.CTRL &= ~OSC_RC2MEN_bm;
						return true;
					case CLOCK_SRC_INT_RC32MHZ:
						OSC.CTRL &= ~OSC_RC32MEN_bm;
						return true;
					case CLOCK_SRC_INT_RC32KHZ:
						OSC.CTRL &= ~OSC_RC32KEN_bm;
						return true;
					default:
						return false;
				}
			}

			/** Starts the PLL of the XMEGA microcontroller, with the given options. This routine blocks until the PLL is ready for use.
			 *
			 *  \attention The output frequency must be equal to or greater than the source frequency.
			 *
			 *  \param[in] Source       Clock source for the PLL, a value from \ref XMEGA_System_ClockSource_t.
			 *  \param[in] SourceFreq   Frequency of the PLL's clock source, in Hz.
			 *  \param[in] Frequency    Target frequency of the PLL's output.
			 *
			 *  \return Boolean \c true if the PLL was successfully started, \c false if invalid parameters specified.
			 */
			static inline bool XMEGACLK_StartPLL(const uint8_t Source,
			                                     const uint32_t SourceFreq,
			                                     const uint32_t Frequency) ATTR_ALWAYS_INLINE;
			static inline bool XMEGACLK_StartPLL(const uint8_t Source,
			                                     const uint32_t SourceFreq,
			                                     const uint32_t Frequency)
			{
				uint8_t MulFactor = (Frequency / SourceFreq);

				if (SourceFreq > Frequency)
				  return false;

				if (MulFactor > 31)
				  return false;

				switch (Source)
				{
					case CLOCK_SRC_INT_RC2MHZ:
						OSC.PLLCTRL = (OSC_PLLSRC_RC2M_gc  | MulFactor);
						break;
					case CLOCK_SRC_INT_RC32MHZ:
						OSC.PLLCTRL = (OSC_PLLSRC_RC32M_gc | MulFactor);
						break;
					case CLOCK_SRC_XOSC:
						OSC.PLLCTRL = (OSC_PLLSRC_XOSC_gc  | MulFactor);
						break;
					default:
						return false;
				}

				OSC.CTRL |= OSC_PLLEN_bm;

				while (!(OSC.STATUS & OSC_PLLRDY_bm));
				return true;
			}

			/** Stops the PLL of the XMEGA microcontroller. */
			static inline void XMEGACLK_StopPLL(void) ATTR_ALWAYS_INLINE;
			static inline void XMEGACLK_StopPLL(void)
			{
				OSC.CTRL &= ~OSC_PLLEN_bm;
			}

			/** Starts the DFLL of the XMEGA microcontroller, with the given options.
			 *
			 *  \param[in] Source     RC Clock source for the DFLL, a value from \ref XMEGA_System_ClockSource_t.
			 *  \param[in] Reference  Reference clock source for the DFLL, an value from \ref XMEGA_System_DFLLReference_t.
			 *  \param[in] Frequency  Target frequency of the DFLL's output.
			 *
			 *  \return Boolean \c true if the DFLL was successfully started, \c false if invalid parameters specified.
			 */
			static inline bool XMEGACLK_StartDFLL(const uint8_t Source,
			                                      const uint8_t Reference,
			                                      const uint32_t Frequency) ATTR_ALWAYS_INLINE;
			static inline bool XMEGACLK_StartDFLL(const uint8_t Source,
			                                      const uint8_t Reference,
			                                      const uint32_t Frequency)
			{
				uint16_t DFLLCompare = (Frequency / 1024);

				switch (Source)
				{
					case CLOCK_SRC_INT_RC2MHZ:
						OSC.DFLLCTRL   |= (Reference << OSC_RC2MCREF_bp);
						DFLLRC2M.COMP1  = (DFLLCompare & 0xFF);
						DFLLRC2M.COMP2  = (DFLLCompare >> 8);
						DFLLRC2M.CTRL   = DFLL_ENABLE_bm;
						break;
					case CLOCK_SRC_INT_RC32MHZ:
						OSC.DFLLCTRL   |= (Reference << OSC_RC32MCREF_gp);
						DFLLRC32M.COMP1 = (DFLLCompare & 0xFF);
						DFLLRC32M.COMP2 = (DFLLCompare >> 8);

						if (Reference == DFLL_REF_INT_USBSOF)
						{
							NVM.CMD        = NVM_CMD_READ_CALIB_ROW_gc;
							DFLLRC32M.CALA = pgm_read_byte(offsetof(NVM_PROD_SIGNATURES_t, USBRCOSCA));
							DFLLRC32M.CALB = pgm_read_byte(offsetof(NVM_PROD_SIGNATURES_t, USBRCOSC));
							NVM.CMD        = 0;
						}

						DFLLRC32M.CTRL  = DFLL_ENABLE_bm;
						break;
					default:
						return false;
				}

				return true;
			}

			/** Stops the given DFLL of the XMEGA microcontroller.
			 *
			 *  \param[in] Source  RC Clock source for the DFLL to be stopped, a value from \ref XMEGA_System_ClockSource_t.
			 *
			 *  \return Boolean \c true if the DFLL was successfully stopped, \c false if invalid parameters specified.
			 */
			static inline bool XMEGACLK_StopDFLL(const uint8_t Source) ATTR_ALWAYS_INLINE;
			static inline bool XMEGACLK_StopDFLL(const uint8_t Source)
			{
				switch (Source)
				{
					case CLOCK_SRC_INT_RC2MHZ:
						DFLLRC2M.CTRL = 0;
						break;
					case CLOCK_SRC_INT_RC32MHZ:
						DFLLRC32M.CTRL = 0;
						break;
					default:
						return false;
				}

				return true;
			}

			/** Sets the clock source for the main microcontroller core. The given clock source should be configured
			 *  and ready for use before this function is called.
			 *
			 *  \param[in] Source      Clock source for the CPU core, a value from \ref XMEGA_System_ClockSource_t.
			 *
			 *  \return Boolean \c true if the CPU core clock was successfully altered, \c false if invalid parameters specified.
			 */
			static inline bool XMEGACLK_SetCPUClockSource(const uint8_t Source) ATTR_ALWAYS_INLINE;
			static inline bool XMEGACLK_SetCPUClockSource(const uint8_t Source)
			{
				uint8_t ClockSourceMask = 0;

				switch (Source)
				{
					case CLOCK_SRC_INT_RC2MHZ:
						ClockSourceMask = CLK_SCLKSEL_RC2M_gc;
						break;
					case CLOCK_SRC_INT_RC32MHZ:
						ClockSourceMask = CLK_SCLKSEL_RC32M_gc;
						break;
					case CLOCK_SRC_INT_RC32KHZ:
						ClockSourceMask = CLK_SCLKSEL_RC32K_gc;
						break;
					case CLOCK_SRC_XOSC:
						ClockSourceMask = CLK_SCLKSEL_XOSC_gc;
						break;
					case CLOCK_SRC_PLL:
						ClockSourceMask = CLK_SCLKSEL_PLL_gc;
						break;
					default:
						return false;
				}

				uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
				GlobalInterruptDisable();

				XMEGACLK_CCP_Write(&CLK.CTRL, ClockSourceMask);

				SetGlobalInterruptMask(CurrentGlobalInt);

				Delay_MS(1);
				return (CLK.CTRL == ClockSourceMask);
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

