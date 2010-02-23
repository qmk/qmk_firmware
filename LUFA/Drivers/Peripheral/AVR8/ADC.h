/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *
 *  ADC driver for the 8-Bit AVRs containing a hardware ADC module.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the ADC driver
 *        dispatch header located in LUFA/Drivers/Peripheral/ADC.h.
 */

/** \ingroup Group_ADC
 *  @defgroup Group_ADC_AVR8 8-Bit AVR ADC Driver
 *
 *  ADC driver for 8-Bit AVRs containing a hardware ADC module.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the ADC driver
 *        dispatch header located in LUFA/Drivers/Peripheral/ADC.h.
 *
 *  @{
 */
 
#ifndef __ADC_AVR8_H__
#define __ADC_AVR8_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_ADC_H)
			#error Do not include this file directly. Include LUFA/Drivers/Peripheral/ADC.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */			
			/** Reference mask, for using the voltage present at the AVR's AREF pin for the ADC reference. */
			#define  ADC_REFERENCE_AREF              0

			/** Reference mask, for using the voltage present at the AVR's AVCC pin for the ADC reference. */
			#define  ADC_REFERENCE_AVCC              (1 << REFS0)

			/** Reference mask, for using the internally generated 2.56V reference voltage as the ADC reference. */
			#define  ADC_REFERENCE_INT2560MV         ((1 << REFS1)| (1 << REFS0))
			
			/** Left-adjusts the 10-bit ADC result, so that the upper 8 bits of the value returned by the
			 *  ADC_GetResult() macro contain the 8 most significant bits of the result. */
			#define  ADC_LEFT_ADJUSTED               (1 << ADLAR)

			/** Right-adjusts the 10-bit ADC result, so that the lower 8 bits of the value returned by the
			 *  ADC_GetResult() macro contain the 8 least significant bits of the result. */
			#define  ADC_RIGHT_ADJUSTED              (0 << ADLAR)
			
			/** Sets the ADC mode to free running, so that conversions take place continuously as fast as the ADC
			 *  is capable of at the given input clock speed. */
			#define  ADC_FREE_RUNNING                (1 << ADATE)

			/** Sets the ADC mode to single conversion, so that only a single conversion will take place before
			 *  the ADC returns to idle. */
			#define  ADC_SINGLE_CONVERSION           (0 << ADATE)
			
			/** Sets the ADC input clock to prescale by a factor of 2 the AVR's system clock. */
			#define  ADC_PRESCALE_2                  (1 << ADPS0)

			/** Sets the ADC input clock to prescale by a factor of 4 the AVR's system clock. */
			#define  ADC_PRESCALE_4                  (1 << ADPS1)

			/** Sets the ADC input clock to prescale by a factor of 8 the AVR's system clock. */
			#define  ADC_PRESCALE_8                  ((1 << ADPS0) | (1 << ADPS1))

			/** Sets the ADC input clock to prescale by a factor of 16 the AVR's system clock. */
			#define  ADC_PRESCALE_16                 (1 << ADPS2)

			/** Sets the ADC input clock to prescale by a factor of 32 the AVR's system clock. */
			#define  ADC_PRESCALE_32                 ((1 << ADPS2) | (1 << ADPS0))

			/** Sets the ADC input clock to prescale by a factor of 64 the AVR's system clock. */
			#define  ADC_PRESCALE_64                 ((1 << ADPS2) | (1 << ADPS1))

			/** Sets the ADC input clock to prescale by a factor of 128 the AVR's system clock. */
			#define  ADC_PRESCALE_128                ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))
			
			//@{
			/** MUX mask define for the ADC0 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading. */
			#define  ADC_CHANNEL0                    0x00

			/** MUX mask define for the ADC1 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading. */
			#define  ADC_CHANNEL1                    0x01

			#if !(defined(__AVR_ATmega16U4__)  || defined(__AVR_ATmega32U4__) || defined(__DOXYGEN__))
				/** MUX mask define for the ADC2 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading.
				 *
				 *  \note Note available on all AVR models.
				 */
				#define  ADC_CHANNEL2                    0x02

				/** MUX mask define for the ADC3 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading.
				 *
				 *  \note Note available on all AVR models.
				 */
				#define  ADC_CHANNEL3                    0x03
			#endif

			/** MUX mask define for the ADC4 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading. */
			#define  ADC_CHANNEL4                    0x04

			/** MUX mask define for the ADC5 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading. */
			#define  ADC_CHANNEL5                    0x05

			/** MUX mask define for the ADC6 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading. */
			#define  ADC_CHANNEL6                    0x06

			/** MUX mask define for the ADC7 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading. */
			#define  ADC_CHANNEL7                    0x07

			/** MUX mask define for the internal 1.1V bandgap channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading. */
			#define  ADC_1100MV_BANDGAP              0x1E
			
			#if (defined(__AVR_ATmega16U4__)  || defined(__AVR_ATmega32U4__) || defined(__DOXYGEN__))
				/** MUX mask define for the ADC8 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading.
				 *
				 *  \note Note available on all AVR models.
				 */
				#define  ADC_CHANNEL8                0x20

				/** MUX mask define for the ADC9 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading.
				 *
				 *  \note Note available on all AVR models.
				 */
				#define  ADC_CHANNEL9                0x21

				/** MUX mask define for the ADC10 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading.
				 *
				 *  \note Note available on all AVR models.
				 */
				#define  ADC_CHANNEL10               0x22

				/** MUX mask define for the ADC11 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading.
				 *
				 *  \note Note available on all AVR models.
				 */
				#define  ADC_CHANNEL11               0x23

				/** MUX mask define for the ADC12 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading.
				 *
				 *  \note Note available on all AVR models.
				 */
				#define  ADC_CHANNEL12               0x24

				/** MUX mask define for the ADC13 channel of the ADC. See \ref ADC_StartReading and \ref ADC_GetChannelReading.
				 *
				 *  \note Note available on all AVR models.
				 */
				#define  ADC_CHANNEL13               0x25

				/** MUX mask define for the internal temperature sensor channel of the ADC. See \ref ADC_StartReading and
				 *  \ref ADC_GetChannelReading.
				 *
				 *  \note Note available on all AVR models.
				 */
				#define  ADC_INT_TEMP_SENS           0x27			
			#endif
			//@}
		
		/* Pseudo-Function Macros: */
			#if defined(__DOXYGEN__)
				/** Initializes the ADC, ready for conversions. This must be called before any other ADC operations.
				 *  The "mode" parameter should be a mask comprised of a conversion mode (free running or single) and
				 *  prescaler masks.
				 *
				 *  \param[in] Mode  Mask of ADC settings, including adjustment, prescale, mode and reference
				 */
				static inline void ADC_Init(uint8_t Mode);

				/** Turns off the ADC. If this is called, any further ADC operations will require a call to
				 *  \ref ADC_Init() before the ADC can be used again.
				 */
				static inline void ADC_ShutDown(void);
				
				/** Indicates if the ADC is currently enabled.
				 *
				 *  \return Boolean true if the ADC subsystem is currently enabled, false otherwise.
				 */
				static inline bool ADC_GetStatus(void);
				
				/** Indicates if the current ADC conversion is completed, or still in progress.
				 *
				 *  \return Boolean false if the reading is still taking place, or true if the conversion is
				 *          complete and ready to be read out with \ref ADC_GetResult()
				 */
				static inline bool ADC_IsReadingComplete(void);
				
				/** Retrieves the conversion value of the last completed ADC conversion.
				 *
				 *  \return The result of the last ADC conversion
				 */
				static inline uint16_t ADC_GetResult(void);
			#else
				#define  ADC_Init(mode)          MACROS{ ADCSRA = ((1 << ADEN) | mode);         }MACROE

				#define  ADC_ShutDown()          MACROS{ ADCSRA = 0;                            }MACROE
				
				#define  ADC_GetStatus()               ((ADCSRA & (1 << ADEN)) ? true : false)

				#define  ADC_IsReadingComplete()        (ADCSRA & (1 << ADSC))
				
				#define  ADC_GetResult()                 ADC			
			#endif
			
		/* Inline Functions: */
			/** Configures the given ADC channel, ready for ADC conversions. This function sets the
			 *  associated port pin as an input and disables the digital portion of the I/O to reduce
			 *  power consumption.
			 *
			 *  \note This must only be called for ADC channels with are connected to a physical port
			 *        pin of the AVR, denoted by its special alternative function ADCx.
			 *
			 *  \note The channel number must be specified as an integer, and NOT a ADC_CHANNELx mask.
			 *
			 *  \param[in] Channel  ADC channel number to set up for conversions
			 */
			static inline void ADC_SetupChannel(const uint8_t Channel)
			{
				#if (defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) || \
					 defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB647__) || \
					 defined(__AVR_ATmega32U6__))				
				DDRF  &= ~(1 << Channel);
				DIDR0 |=  (1 << Channel);
				#elif (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
				if (Channel < 8)
				{
					DDRF  &= ~(1 << Channel);
					DIDR0 |=  (1 << Channel);
				}
				else if (Channel == 8)
				{
					DDRD  &= ~(1 << 4);
					DIDR2 |=  (1 << 0);
				}
				else if (Channel < 11)
				{
					DDRD  &= ~(1 << (Channel - 3));
					DIDR2 |=  (1 << (Channel - 8));
				}
				else
				{
					DDRB  &= ~(1 << (Channel - 7));
					DIDR2 |=  (1 << (Channel - 8));
				}
				#endif
			}
			
			/** Starts the reading of the given channel, but does not wait until the conversion has completed.
			 *  Once executed, the conversion status can be determined via the \ref ADC_IsReadingComplete() macro and
			 *  the result read via the \ref ADC_GetResult() macro.
			 *
			 *  \param[in] MUXMask  Mask comprising of an ADC channel mask, reference mask and adjustment mask
			 */
			static inline void ADC_StartReading(const uint8_t MUXMask)
			{
				ADMUX = MUXMask;
			
				ADCSRA |= (1 << ADSC);
			}

			/** Performs a complete single reading from channel, including a polling spin-loop to wait for the
			 *  conversion to complete, and the returning of the converted value.
			 *
			 *  \param[in] MUXMask  Mask comprising of an ADC channel mask, reference mask and adjustment mask
			 */
			static inline uint16_t ADC_GetChannelReading(const uint8_t MUXMask) ATTR_WARN_UNUSED_RESULT;
			static inline uint16_t ADC_GetChannelReading(const uint8_t MUXMask)
			{
				ADC_StartReading(MUXMask);
	
				while (!(ADC_IsReadingComplete()));
	
				return ADC_GetResult();
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
