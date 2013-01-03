/*
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)
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

/*
	NOTE: The user of this include file MUST define the following macros
	prior to including the file:

	MAG_T1_CLOCK_PIN   Pin connected to Track 1 clock wire (i.e.. PORTC1)
	MAG_T1_DATA_PIN    Pin connected to Track 1 data wire (i.e.. PORTC2)
	MAG_T2_CLOCK_PIN   Pin connected to Track 2 clock wire (i.e.. PORTC3)
	MAG_T2_DATA_PIN    Pin connected to Track 2 data wire (i.e.. PORTC0)
	MAG_T3_CLOCK_PIN   Pin connected to Track 3 clock wire (i.e.. PORTC5)
	MAG_T3_DATA_PIN    Pin connected to Track 3 data wire (i.e.. PORTC6)
	MAG_CLS_PIN        Pin connected to card loaded wire (i.e.. PORTC4)
	MAG_PIN            PIN macro for the reader's port (i.e.. PINC)
	MAG_DDR            DDR macro for the reader's port (i.e.. DDRC)
	MAG_PORT           PORT macro for the reader's port (i.e.. PORTC)

	The example macros listed above assume that the Track 2 data wire is
	connected to pin 0 on port C, the Track 2 clock wire is connected to
	pin 3 on port C (similarly for Tracks 1 and 3), and the card loaded
	wire is connected to pin 4 on port C.

	If the mag-stripe reader you are using only reads one or two tracks,
	then set the clock and data pins for the tracks it doesn't read to a
	pin that is unused.  For example, on the AT90USBKey, any of the pins on
	port C that do not have wires attached will be unused since they are
	not connected to any onboard devices (such as the joystick or
	temperature sensor).

	Connecting wires to pins on different ports (i.e.. a data wire to pin 0
	on port C and a clock wire to pin 0 on port D) is currently
	unsupported.  All pins specified above must be on the same port.
*/

/** \file
 *
 *  Driver header for a TTL Magnetic Card reader device (such as the Omron V3B-4K).
 */

#ifndef _MAGSTRIPEHW_H_
#define _MAGSTRIPEHW_H_

	/* Includes: */
		#include <avr/io.h>

		#include <LUFA/Common/Common.h>
		#include "Config/AppConfig.h"

	/* Private Interface - For use in library only: */
		/* Macros: */
			/** Mask of the track data, clock and card detection pins. */
			#define MAG_MASK    (MAG_T1_DATA | MAG_T1_CLOCK | \
			                     MAG_T2_DATA | MAG_T2_CLOCK | \
			                     MAG_T3_DATA | MAG_T3_CLOCK | \
			                     MAG_CARDPRESENT)

	/* Public Interface - May be used in end-application: */
		/* Inline Functions: */
			/** Initializes the magnetic stripe card reader ports and pins so that the card reader
			 *  device can be controlled and read by the card reader driver. This must be called before
			 *  trying to read any of the card reader's status lines.
			 */
			static inline void Magstripe_Init(void)
			{
				MAG_DDR  &= ~MAG_MASK;
				MAG_PORT |=  MAG_MASK;
			};

			/** Returns the status of all the magnetic card reader's outputs.
			 *
			 *  \return A mask indicating which card lines are high or low
			 */
			static inline uint8_t Magstripe_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Magstripe_GetStatus(void)
			{
				/* Mag-stripe IOs are active low and must be inverted when read */
				return ((uint8_t)~MAG_PIN & MAG_MASK);
			}

#endif

