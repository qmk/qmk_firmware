/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief ADC Peripheral Driver (AVR8)
 *
 *  On-chip Analogue-to-Digital converter (ADC) driver for supported U4, U6 and U7 model AVRs that contain an ADC
 *  peripheral internally.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the ADC driver
 *        dispatch header located in LUFA/Drivers/Peripheral/ADC.h.
 */

/** \ingroup Group_ADC
 *  \defgroup Group_ADC_AVR8 ADC Peripheral Driver (AVR8)
 *
 *  \section Sec_ModDescription Module Description
 *  On-chip Analogue-to-Digital converter (ADC) driver for supported U4, U6 and U7 model AVRs that contain an ADC
 *  peripheral internally.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the ADC driver
 *        dispatch header located in LUFA/Drivers/Peripheral/ADC.h.
 *
 *  \section Sec_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Initialize the ADC driver before first use
 *      ADC_Init(ADC_FREE_RUNNING | ADC_PRESCALE_32);
 *
 *      // Must setup the ADC channel to read beforehand
 *      ADC_SetupChannel(1);
 *
 *      // Perform a single conversion of the ADC channel 1
 *      ADC_GetChannelReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL1);
 *      printf("Conversion Result: %d\r\n", ADC_GetResult());
 *
 *      // Start reading ADC channel 1 in free running (continuous conversion) mode
 *      ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_CHANNEL1);
 *      for (;;)
 *      {
 *           while (!(ADC_IsReadingComplete())) {};
 *           printf("Conversion Result: %d\r\n", ADC_GetResult());
 *      }
 *  \endcode
 *
 *  @{
 */

#ifndef __ADC_AVR8_H__
#define __ADC_AVR8_H__

	/* Includes: */
		#include "../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_ADC_H)
			#error Do not include this file directly. Include LUFA/Drivers/Peripheral/ADC.h instead.
		#endif

		#if !(defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) || \
		      defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB647__) || \
			  defined(__AVR_ATmega16U4__)  || defined(__AVR_ATmega32U4__))
			#error The ADC peripheral driver is not currently available for your selected microcontroller model.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** \name ADC Reference Configuration Masks */
			//@{
			/** Reference mask, for using the voltage present at the AVR's AREF pin for the ADC reference. */
			#define ADC_REFERENCE_AREF              0

			/** Reference mask, for using the voltage present at the AVR's AVCC pin for the ADC reference. */
			#define ADC_REFERENCE_AVCC              (1 << REFS0)

			/** Reference mask, for using the internally generated 2.56V reference voltage as the ADC reference. */
			#define ADC_REFERENCE_INT2560MV         ((1 << REFS1) | (1 << REFS0))
			//@}

			/** \name ADC Result Adjustment Configuration Masks */
			//@{
			/** Left-adjusts the 10-bit ADC result, so that the upper 8 bits of the value returned by the
			 *  \ref ADC_GetResult() macro contain the 8 most significant bits of the result.
			 */
			#define ADC_LEFT_ADJUSTED               (1 << ADLAR)

			/** Right-adjusts the 10-bit ADC result, so that the lower 8 bits of the value returned by the
			 *  \ref ADC_GetResult() macro contain the 8 least significant bits of the result.
			 */
			#define ADC_RIGHT_ADJUSTED              (0 << ADLAR)
			//@}

			/** \name ADC Mode Configuration Masks */
			//@{
			/** Sets the ADC mode to free running, so that conversions take place continuously as fast as the ADC
			 *  is capable of at the given input clock speed.
			 */
			#define ADC_FREE_RUNNING                (1 << ADATE)

			/** Sets the ADC mode to single conversion, so that only a single conversion will take place before
			 *  the ADC returns to idle.
			 */
			#define ADC_SINGLE_CONVERSION           (0 << ADATE)
			//@}

			/** \name ADC Prescaler Configuration Masks */
			//@{
			/** Sets the ADC input clock to prescale by a factor of 2 the AVR's system clock. */
			#define ADC_PRESCALE_2                  (1 << ADPS0)

			/** Sets the ADC input clock to prescale by a factor of 4 the AVR's system clock. */
			#define ADC_PRESCALE_4                  (1 << ADPS1)

			/** Sets the ADC input clock to prescale by a factor of 8 the AVR's system clock. */
			#define ADC_PRESCALE_8                  ((1 << ADPS0) | (1 << ADPS1))

			/** Sets the ADC input clock to prescale by a factor of 16 the AVR's system clock. */
			#define ADC_PRESCALE_16                 (1 << ADPS2)

			/** Sets the ADC input clock to prescale by a factor of 32 the AVR's system clock. */
			#define ADC_PRESCALE_32                 ((1 << ADPS2) | (1 << ADPS0))

			/** Sets the ADC input clock to prescale by a factor of 64 the AVR's system clock. */
			#define ADC_PRESCALE_64                 ((1 << ADPS2) | (1 << ADPS1))

			/** Sets the ADC input clock to prescale by a factor of 128 the AVR's system clock. */
			#define ADC_PRESCALE_128                ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))
			//@}

			/** \name ADC MUX Masks */
			//@{
			/** MUX mask define for the ADC0 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading(). */
			#define ADC_CHANNEL0                    (0x00 << MUX0)

			/** MUX mask define for the ADC1 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading(). */
			#define ADC_CHANNEL1                    (0x01 << MUX0)

			#if (!(defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)) || defined(__DOXYGEN__))
				/** MUX mask define for the ADC2 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading().
				 *
				 *  \note Not available on all AVR models.
				 */
				#define ADC_CHANNEL2                (0x02 << MUX0)

				/** MUX mask define for the ADC3 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading().
				 *
				 *  \note Not available on all AVR models.
				 */
				#define ADC_CHANNEL3                (0x03 << MUX0)
			#endif

			/** MUX mask define for the ADC4 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading(). */
			#define ADC_CHANNEL4                    (0x04 << MUX0)

			/** MUX mask define for the ADC5 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading(). */
			#define ADC_CHANNEL5                    (0x05 << MUX0)

			/** MUX mask define for the ADC6 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading(). */
			#define ADC_CHANNEL6                    (0x06 << MUX0)

			/** MUX mask define for the ADC7 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading. */
			#define ADC_CHANNEL7                    (0x07 << MUX0)

			#if (defined(__AVR_ATmega16U4__)  || defined(__AVR_ATmega32U4__) || defined(__DOXYGEN__))
				/** MUX mask define for the ADC8 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading().
				 *
				 *  \note Not available on all AVR models.
				 */
				#define ADC_CHANNEL8                ((1 << 8) | (0x00 << MUX0))

				/** MUX mask define for the ADC9 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading().
				 *
				 *  \note Not available on all AVR models.
				 */
				#define ADC_CHANNEL9                ((1 << 8) | (0x01 << MUX0))

				/** MUX mask define for the ADC10 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading().
				 *
				 *  \note Not available on all AVR models.
				 */
				#define ADC_CHANNEL10               ((1 << 8) | (0x02 << MUX0))

				/** MUX mask define for the ADC11 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading().
				 *
				 *  \note Not available on all AVR models.
				 */
				#define ADC_CHANNEL11               ((1 << 8) | (0x03 << MUX0))

				/** MUX mask define for the ADC12 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading().
				 *
				 *  \note Not available on all AVR models.
				 */
				#define ADC_CHANNEL12               ((1 << 8) | (0x04 << MUX0))

				/** MUX mask define for the ADC13 channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading().
				 *
				 *  \note Not available on all AVR models.
				 */
				#define ADC_CHANNEL13               ((1 << 8) | (0x05 << MUX0))

				/** MUX mask define for the internal temperature sensor channel of the ADC. See \ref ADC_StartReading() and
				 *  \ref ADC_GetChannelReading().
				 *
				 *  \note Not available on all AVR models.
				 */
				#define ADC_INT_TEMP_SENS           ((1 << 8) | (0x07 << MUX0))
			#endif

			/** MUX mask define for the internal 1.1V band-gap channel of the ADC. See \ref ADC_StartReading() and \ref ADC_GetChannelReading(). */
			#define ADC_1100MV_BANDGAP              (0x1E << MUX0)

			/** Retrieves the ADC MUX mask for the given ADC channel number.
			 *
			 *  \attention This macro will only work correctly on channel numbers that are compile-time
			 *             constants defined by the preprocessor.
			 *
			 *  \param[in] Channel  Index of the ADC channel whose MUX mask is to be retrieved.
			 */
			#define ADC_GET_CHANNEL_MASK(Channel)   CONCAT_EXPANDED(ADC_CHANNEL, Channel)
			//@}

		/* Inline Functions: */
			/** Configures the given ADC channel, ready for ADC conversions. This function sets the
			 *  associated port pin as an input and disables the digital portion of the I/O to reduce
			 *  power consumption.
			 *
			 *  \note This must only be called for ADC channels with are connected to a physical port
			 *        pin of the AVR, denoted by its special alternative function ADCx.
			 *
			 *  \warning The channel number must be specified as an integer, and <b>not</b> a \c ADC_CHANNEL* mask.
			 *
			 *  \param[in] ChannelIndex  ADC channel number to set up for conversions.
			 */
			static inline void ADC_SetupChannel(const uint8_t ChannelIndex)
			{
				#if (defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) || \
					 defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB647__))
				DDRF  &= ~(1 << ChannelIndex);
				DIDR0 |=  (1 << ChannelIndex);
				#elif (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
				if (ChannelIndex < 8)
				{
					DDRF  &= ~(1 << ChannelIndex);
					DIDR0 |=  (1 << ChannelIndex);
				}
				else if (ChannelIndex == 8)
				{
					DDRD  &= ~(1 << 4);
					DIDR2 |=  (1 << 0);
				}
				else if (ChannelIndex < 11)
				{
					DDRD  &= ~(1 << (ChannelIndex - 3));
					DIDR2 |=  (1 << (ChannelIndex - 8));
				}
				else
				{
					DDRB  &= ~(1 << (ChannelIndex - 7));
					DIDR2 |=  (1 << (ChannelIndex - 8));
				}
				#endif
			}

			/** De-configures the given ADC channel, re-enabling digital I/O mode instead of analog. This
			 *  function sets the associated port pin as an input and re-enabled the digital portion of
			 *  the I/O.
			 *
			 *  \note This must only be called for ADC channels with are connected to a physical port
			 *        pin of the AVR, denoted by its special alternative function ADCx.
			 *
			 *  \warning The channel number must be specified as an integer, and <b>not</b> a \c ADC_CHANNEL* mask.
			 *
			 *  \param[in] ChannelIndex  ADC channel number to set up for conversions.
			 */
			static inline void ADC_DisableChannel(const uint8_t ChannelIndex)
			{
				#if (defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) || \
					 defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB647__))
				DDRF  &= ~(1 << ChannelIndex);
				DIDR0 &= ~(1 << ChannelIndex);
				#elif (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
				if (ChannelIndex < 8)
				{
					DDRF  &= ~(1 << ChannelIndex);
					DIDR0 &= ~(1 << ChannelIndex);
				}
				else if (ChannelIndex == 8)
				{
					DDRD  &= ~(1 << 4);
					DIDR2 &= ~(1 << 0);
				}
				else if (ChannelIndex < 11)
				{
					DDRD  &= ~(1 << (ChannelIndex - 3));
					DIDR2 &= ~(1 << (ChannelIndex - 8));
				}
				else
				{
					DDRB  &= ~(1 << (ChannelIndex - 7));
					DIDR2 &= ~(1 << (ChannelIndex - 8));
				}
				#endif
			}

			/** Starts the reading of the given channel, but does not wait until the conversion has completed.
			 *  Once executed, the conversion status can be determined via the \ref ADC_IsReadingComplete() macro and
			 *  the result read via the \ref ADC_GetResult() macro.
			 *
			 *  If the ADC has been initialized in free running mode, calling this function once will begin the repeated
			 *  conversions. If the ADC is in single conversion mode (or the channel to convert from is to be changed),
			 *  this function must be called each time a conversion is to take place.
			 *
			 *  \param[in] MUXMask  ADC channel mask, reference mask and adjustment mask.
			 */
			static inline void ADC_StartReading(const uint16_t MUXMask)
			{
				ADMUX = MUXMask;

				#if (defined(__AVR_ATmega16U4__)  || defined(__AVR_ATmega32U4__) || defined(__DOXYGEN__))
				if (MUXMask & (1 << 8))
				  ADCSRB |=  (1 << MUX5);
				else
				  ADCSRB &= ~(1 << MUX5);
				#endif

				ADCSRA |= (1 << ADSC);
			}

			/** Indicates if the current ADC conversion is completed, or still in progress.
			 *
			 *  \return Boolean \c false if the reading is still taking place, or true if the conversion is
			 *          complete and ready to be read out with \ref ADC_GetResult().
			 */
			static inline bool ADC_IsReadingComplete(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool ADC_IsReadingComplete(void)
			{
				return ((ADCSRA & (1 << ADIF)) ? true : false);
			}

			/** Retrieves the conversion value of the last completed ADC conversion and clears the reading
			 *  completion flag.
			 *
			 *  \return The result of the last ADC conversion as an unsigned value.
			 */
			static inline uint16_t ADC_GetResult(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint16_t ADC_GetResult(void)
			{
				ADCSRA |= (1 << ADIF);
				return ADC;
			}

			/** Performs a complete single reading from channel, including a polling spin-loop to wait for the
			 *  conversion to complete, and the returning of the converted value.
			 *
			 *  \note For free running mode, the automated conversions should be initialized with a single call
			 *        to \ref ADC_StartReading() to select the channel and begin the automated conversions, and
			 *        the results read directly from the \ref ADC_GetResult() instead to reduce overhead.
			 *
			 *  \param[in] MUXMask  Mask comprising of an ADC channel mask, reference mask and adjustment mask.
			 *
			 *  \return Converted ADC result for the given ADC channel.
			 */
			static inline uint16_t ADC_GetChannelReading(const uint16_t MUXMask) ATTR_WARN_UNUSED_RESULT;
			static inline uint16_t ADC_GetChannelReading(const uint16_t MUXMask)
			{
				ADC_StartReading(MUXMask);

				while (!(ADC_IsReadingComplete()));

				return ADC_GetResult();
			}

			/** Initializes the ADC, ready for conversions. This must be called before any other ADC operations.
			 *  The "mode" parameter should be a mask comprised of a conversion mode (free running or single) and
			 *  prescaler masks.
			 *
			 *  \param[in] Mode  Mask of ADC prescale and mode settings.
			 */
			static inline void ADC_Init(const uint8_t Mode) ATTR_ALWAYS_INLINE;
			static inline void ADC_Init(const uint8_t Mode)
			{
				ADCSRA = ((1 << ADEN) | Mode);
			}

			/** Turns off the ADC. If this is called, any further ADC operations will require a call to
			 *  \ref ADC_Init() before the ADC can be used again.
			 */
			static inline void ADC_Disable(void) ATTR_ALWAYS_INLINE;
			static inline void ADC_Disable(void)
			{
				ADCSRA = 0;
			}

			/** Indicates if the ADC is currently enabled.
			 *
			 *  \return Boolean \c true if the ADC subsystem is currently enabled, \c false otherwise.
			 */
			static inline bool ADC_GetStatus(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool ADC_GetStatus(void)
			{
				return ((ADCSRA & (1 << ADEN)) ? true : false);
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

