/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *
 *  Target-related functions for the ISP Protocol decoder.
 */

#include "ISPTarget.h"

#if defined(ENABLE_ISP_PROTOCOL) || defined(__DOXYGEN__)

/** List of hardware SPI prescaler masks for possible AVRStudio ISP programming speeds.
 *
 *  \hideinitializer
 */
static const uint8_t SPIMaskFromSCKDuration[] PROGMEM =
{
#if (F_CPU == 8000000)
	SPI_SPEED_FCPU_DIV_2,    // AVRStudio =   8MHz SPI, Actual =   4MHz SPI
	SPI_SPEED_FCPU_DIV_2,    // AVRStudio =   4MHz SPI, Actual =   4MHz SPI
	SPI_SPEED_FCPU_DIV_4,    // AVRStudio =   2MHz SPI, Actual =   2MHz SPI
	SPI_SPEED_FCPU_DIV_8,    // AVRStudio =   1MHz SPI, Actual =   1MHz SPI
	SPI_SPEED_FCPU_DIV_16,   // AVRStudio = 500KHz SPI, Actual = 500KHz SPI
	SPI_SPEED_FCPU_DIV_32,   // AVRStudio = 250KHz SPI, Actual = 250KHz SPI
	SPI_SPEED_FCPU_DIV_64,   // AVRStudio = 125KHz SPI, Actual = 125KHz SPI
#elif (F_CPU == 16000000)
	SPI_SPEED_FCPU_DIV_2,    // AVRStudio =   8MHz SPI, Actual =   8MHz SPI
	SPI_SPEED_FCPU_DIV_4,    // AVRStudio =   4MHz SPI, Actual =   4MHz SPI
	SPI_SPEED_FCPU_DIV_8,    // AVRStudio =   2MHz SPI, Actual =   2MHz SPI
	SPI_SPEED_FCPU_DIV_16,   // AVRStudio =   1MHz SPI, Actual =   1MHz SPI
	SPI_SPEED_FCPU_DIV_32,   // AVRStudio = 500KHz SPI, Actual = 500KHz SPI
	SPI_SPEED_FCPU_DIV_64,   // AVRStudio = 250KHz SPI, Actual = 250KHz SPI
	SPI_SPEED_FCPU_DIV_128   // AVRStudio = 125KHz SPI, Actual = 125KHz SPI
#else
	#error No SPI prescaler masks for chosen F_CPU speed.
#endif
};

/** Lookup table to convert the slower ISP speeds into a compare value for the software SPI driver.
 *
 *  \hideinitializer
 */
static const uint16_t TimerCompareFromSCKDuration[] PROGMEM =
{
	ISP_TIMER_COMP(96386), ISP_TIMER_COMP(89888), ISP_TIMER_COMP(84211), ISP_TIMER_COMP(79208), ISP_TIMER_COMP(74767),
	ISP_TIMER_COMP(70797), ISP_TIMER_COMP(67227), ISP_TIMER_COMP(64000), ISP_TIMER_COMP(61069), ISP_TIMER_COMP(58395),
	ISP_TIMER_COMP(55945), ISP_TIMER_COMP(51613), ISP_TIMER_COMP(49690), ISP_TIMER_COMP(47905), ISP_TIMER_COMP(46243),
	ISP_TIMER_COMP(43244), ISP_TIMER_COMP(41885), ISP_TIMER_COMP(39409), ISP_TIMER_COMP(38278), ISP_TIMER_COMP(36200),
	ISP_TIMER_COMP(34335), ISP_TIMER_COMP(32654), ISP_TIMER_COMP(31129), ISP_TIMER_COMP(29740), ISP_TIMER_COMP(28470),
	ISP_TIMER_COMP(27304), ISP_TIMER_COMP(25724), ISP_TIMER_COMP(24768), ISP_TIMER_COMP(23461), ISP_TIMER_COMP(22285),
	ISP_TIMER_COMP(21221), ISP_TIMER_COMP(20254), ISP_TIMER_COMP(19371), ISP_TIMER_COMP(18562), ISP_TIMER_COMP(17583),
	ISP_TIMER_COMP(16914), ISP_TIMER_COMP(16097), ISP_TIMER_COMP(15356), ISP_TIMER_COMP(14520), ISP_TIMER_COMP(13914),
	ISP_TIMER_COMP(13224), ISP_TIMER_COMP(12599), ISP_TIMER_COMP(12031), ISP_TIMER_COMP(11511), ISP_TIMER_COMP(10944),
	ISP_TIMER_COMP(10431), ISP_TIMER_COMP(9963),  ISP_TIMER_COMP(9468),  ISP_TIMER_COMP(9081),  ISP_TIMER_COMP(8612),
	ISP_TIMER_COMP(8239),  ISP_TIMER_COMP(7851),  ISP_TIMER_COMP(7498),  ISP_TIMER_COMP(7137),  ISP_TIMER_COMP(6809),
	ISP_TIMER_COMP(6478),  ISP_TIMER_COMP(6178),  ISP_TIMER_COMP(5879),  ISP_TIMER_COMP(5607),  ISP_TIMER_COMP(5359),
	ISP_TIMER_COMP(5093),  ISP_TIMER_COMP(4870),  ISP_TIMER_COMP(4633),  ISP_TIMER_COMP(4418),  ISP_TIMER_COMP(4209),
	ISP_TIMER_COMP(4019),  ISP_TIMER_COMP(3823),  ISP_TIMER_COMP(3645),  ISP_TIMER_COMP(3474),  ISP_TIMER_COMP(3310),
	ISP_TIMER_COMP(3161),  ISP_TIMER_COMP(3011),  ISP_TIMER_COMP(2869),  ISP_TIMER_COMP(2734),  ISP_TIMER_COMP(2611),
	ISP_TIMER_COMP(2484),  ISP_TIMER_COMP(2369),  ISP_TIMER_COMP(2257),  ISP_TIMER_COMP(2152),  ISP_TIMER_COMP(2052),
	ISP_TIMER_COMP(1956),  ISP_TIMER_COMP(1866),  ISP_TIMER_COMP(1779),  ISP_TIMER_COMP(1695),  ISP_TIMER_COMP(1615),
	ISP_TIMER_COMP(1539),  ISP_TIMER_COMP(1468),  ISP_TIMER_COMP(1398),  ISP_TIMER_COMP(1333),  ISP_TIMER_COMP(1271),
	ISP_TIMER_COMP(1212),  ISP_TIMER_COMP(1155),  ISP_TIMER_COMP(1101),  ISP_TIMER_COMP(1049),  ISP_TIMER_COMP(1000),
	ISP_TIMER_COMP(953),   ISP_TIMER_COMP(909),   ISP_TIMER_COMP(866),   ISP_TIMER_COMP(826),   ISP_TIMER_COMP(787),
	ISP_TIMER_COMP(750),   ISP_TIMER_COMP(715),   ISP_TIMER_COMP(682),   ISP_TIMER_COMP(650),   ISP_TIMER_COMP(619),
	ISP_TIMER_COMP(590),   ISP_TIMER_COMP(563),   ISP_TIMER_COMP(536),   ISP_TIMER_COMP(511),   ISP_TIMER_COMP(487),
	ISP_TIMER_COMP(465),   ISP_TIMER_COMP(443),   ISP_TIMER_COMP(422),   ISP_TIMER_COMP(402),   ISP_TIMER_COMP(384),
	ISP_TIMER_COMP(366),   ISP_TIMER_COMP(349),   ISP_TIMER_COMP(332),   ISP_TIMER_COMP(317),   ISP_TIMER_COMP(302),
	ISP_TIMER_COMP(288),   ISP_TIMER_COMP(274),   ISP_TIMER_COMP(261),   ISP_TIMER_COMP(249),   ISP_TIMER_COMP(238),
	ISP_TIMER_COMP(226),   ISP_TIMER_COMP(216),   ISP_TIMER_COMP(206),   ISP_TIMER_COMP(196),   ISP_TIMER_COMP(187),
	ISP_TIMER_COMP(178),   ISP_TIMER_COMP(170),   ISP_TIMER_COMP(162),   ISP_TIMER_COMP(154),   ISP_TIMER_COMP(147),
	ISP_TIMER_COMP(140),   ISP_TIMER_COMP(134),   ISP_TIMER_COMP(128),   ISP_TIMER_COMP(122),   ISP_TIMER_COMP(116),
	ISP_TIMER_COMP(111),   ISP_TIMER_COMP(105),   ISP_TIMER_COMP(100),   ISP_TIMER_COMP(95.4),  ISP_TIMER_COMP(90.9),
	ISP_TIMER_COMP(86.6),  ISP_TIMER_COMP(82.6),  ISP_TIMER_COMP(78.7),  ISP_TIMER_COMP(75.0),  ISP_TIMER_COMP(71.5),
	ISP_TIMER_COMP(68.2),  ISP_TIMER_COMP(65.0),  ISP_TIMER_COMP(61.9),  ISP_TIMER_COMP(59.0),  ISP_TIMER_COMP(56.3),
	ISP_TIMER_COMP(53.6),  ISP_TIMER_COMP(51.1)
};

/** Currently selected SPI driver, either hardware (for fast ISP speeds) or software (for slower ISP speeds). */
bool ISPTarget_HardwareSPIMode = true;

/** Software SPI data register for sending and receiving */
static volatile uint8_t ISPTarget_SoftSPI_Data;

/** Number of bits left to transfer in the software SPI driver */
static volatile uint8_t ISPTarget_SoftSPI_BitsRemaining;


/** ISR to handle software SPI transmission and reception */
ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	/* Check if rising edge (output next bit) or falling edge (read in next bit) */
	if (!(PINB & (1 << 1)))
	{
		if (ISPTarget_SoftSPI_Data & (1 << 7))
		  PORTB |=  (1 << 2);
		else
		  PORTB &= ~(1 << 2);
	}
	else
	{
		ISPTarget_SoftSPI_Data <<= 1;

		if (!(--ISPTarget_SoftSPI_BitsRemaining))
		{
			TCCR1B = 0;
			TIFR1  = (1 << OCF1A);
		}

		if (PINB & (1 << 3))
		  ISPTarget_SoftSPI_Data |= (1 << 0);
	}

	/* Fast toggle of PORTB.1 via the PIN register (see datasheet) */
	PINB |= (1 << 1);
}

/** Initializes the appropriate SPI driver (hardware or software, depending on the selected ISP speed) ready for
 *  communication with the attached target.
 */
void ISPTarget_EnableTargetISP(void)
{
	uint8_t SCKDuration = V2Params_GetParameterValue(PARAM_SCK_DURATION);

	if (SCKDuration < sizeof(SPIMaskFromSCKDuration))
	{
		ISPTarget_HardwareSPIMode = true;

		SPI_Init(pgm_read_byte(&SPIMaskFromSCKDuration[SCKDuration]) | SPI_ORDER_MSB_FIRST |
		                       SPI_SCK_LEAD_RISING | SPI_SAMPLE_LEADING | SPI_MODE_MASTER);
	}
	else
	{
		ISPTarget_HardwareSPIMode = false;

		DDRB  |= ((1 << 1) | (1 << 2));
		PORTB |= ((1 << 0) | (1 << 3));

		ISPTarget_ConfigureSoftwareSPI(SCKDuration);
	}
}

/** Shuts down the current selected SPI driver (hardware or software, depending on the selected ISP speed) so that no
 *  further communications can occur until the driver is re-initialized.
 */
void ISPTarget_DisableTargetISP(void)
{
	if (ISPTarget_HardwareSPIMode)
	{
		SPI_Disable();
	}
	else
	{
		DDRB  &= ~((1 << 1) | (1 << 2));
		PORTB &= ~((1 << 0) | (1 << 3));

		/* Must re-enable rescue clock once software ISP has exited, as the timer for the rescue clock is
		 * re-purposed for software SPI */
		ISPTarget_ConfigureRescueClock();
	}
}

/** Configures the AVR to produce a 4MHz rescue clock out of the OCR1A pin of the AVR, so
 *  that it can be fed into the XTAL1 pin of an AVR whose fuses have been mis-configured for
 *  an external clock rather than a crystal. When used, the ISP speed must be 125KHz for this
 *  functionality to work correctly.
 */
void ISPTarget_ConfigureRescueClock(void)
{
	#if defined(XCK_RESCUE_CLOCK_ENABLE)
		/* Configure XCK as an output for the specified AVR model */
		DDRD  |= (1 << 5);

		/* Start USART to generate a 4MHz clock on the XCK pin */
		UBRR1  = ((F_CPU / 2 / ISP_RESCUE_CLOCK_SPEED) - 1);
		UCSR1B = (1 << TXEN1);
		UCSR1C = (1 << UMSEL10) | (1 << UPM11) | (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10) | (1 << UCPOL1);
	#else
		/* Configure OCR1A as an output for the specified AVR model */
		#if defined(USB_SERIES_2_AVR)
		DDRC |= (1 << 6);
		#else
		DDRB |= (1 << 5);
		#endif

		/* Start Timer 1 to generate a 4MHz clock on the OCR1A pin */
		TIMSK1 = 0;
		TCNT1  = 0;
		OCR1A  = ((F_CPU / 2 / ISP_RESCUE_CLOCK_SPEED) - 1);
		TCCR1A = (1 << COM1A0);
		TCCR1B = ((1 << WGM12) | (1 << CS10));
	#endif
}

/** Configures the AVR's timer ready to produce software SPI for the slower ISP speeds that
 *  cannot be obtained when using the AVR's hardware SPI module.
 *
 *  \param[in] SCKDuration  Duration of the desired software ISP SCK clock
 */
void ISPTarget_ConfigureSoftwareSPI(const uint8_t SCKDuration)
{
	/* Configure Timer 1 for software SPI using the specified SCK duration */
	TIMSK1 = (1 << OCIE1A);
	TCNT1  = 0;
	OCR1A  = pgm_read_word(&TimerCompareFromSCKDuration[SCKDuration - sizeof(SPIMaskFromSCKDuration)]);
	TCCR1A = 0;
	TCCR1B = 0;
}

/** Sends and receives a single byte of data to and from the attached target via software SPI.
 *
 *  \param[in] Byte  Byte of data to send to the attached target
 *
 *  \return Received byte of data from the attached target
 */
uint8_t ISPTarget_TransferSoftSPIByte(const uint8_t Byte)
{
	ISPTarget_SoftSPI_Data          = Byte;
	ISPTarget_SoftSPI_BitsRemaining = 8;

	/* Set initial MOSI pin state according to the byte to be transferred */
	if (ISPTarget_SoftSPI_Data & (1 << 7))
	  PORTB |=  (1 << 2);
	else
	  PORTB &= ~(1 << 2);

	TCNT1  = 0;
	TCCR1B = ((1 << WGM12) | (1 << CS11));
	while (ISPTarget_SoftSPI_BitsRemaining && TimeoutTicksRemaining);
	TCCR1B = 0;

	return ISPTarget_SoftSPI_Data;
}

/** Asserts or deasserts the target's reset line, using the correct polarity as set by the host using a SET PARAM command.
 *  When not asserted, the line is tristated so as not to interfere with normal device operation.
 *
 *  \param[in] ResetTarget  Boolean true when the target should be held in reset, \c false otherwise
 */
void ISPTarget_ChangeTargetResetLine(const bool ResetTarget)
{
	if (ResetTarget)
	{
		AUX_LINE_DDR |= AUX_LINE_MASK;

		if (!(V2Params_GetParameterValue(PARAM_RESET_POLARITY)))
		  AUX_LINE_PORT |=  AUX_LINE_MASK;
		else
		  AUX_LINE_PORT &= ~AUX_LINE_MASK;
	}
	else
	{
		AUX_LINE_DDR  &= ~AUX_LINE_MASK;
		AUX_LINE_PORT &= ~AUX_LINE_MASK;
	}
}

/** Waits until the target has completed the last operation, by continuously polling the device's
 *  BUSY flag until it is cleared, or until the command timeout period has expired.
 *
 *  \return V2 Protocol status \ref STATUS_CMD_OK if the no timeout occurred, \ref STATUS_RDY_BSY_TOUT otherwise
 */
uint8_t ISPTarget_WaitWhileTargetBusy(void)
{
	do
	{
		ISPTarget_SendByte(0xF0);
		ISPTarget_SendByte(0x00);
		ISPTarget_SendByte(0x00);
	}
	while ((ISPTarget_ReceiveByte() & 0x01) && TimeoutTicksRemaining);

	return (TimeoutTicksRemaining > 0) ? STATUS_CMD_OK : STATUS_RDY_BSY_TOUT;
}

/** Sends a low-level LOAD EXTENDED ADDRESS command to the target, for addressing of memory beyond the
 *  64KB boundary. This sends the command with the correct address as indicated by the current address
 *  pointer variable set by the host when a SET ADDRESS command is issued.
 */
void ISPTarget_LoadExtendedAddress(void)
{
	ISPTarget_SendByte(LOAD_EXTENDED_ADDRESS_CMD);
	ISPTarget_SendByte(0x00);
	ISPTarget_SendByte(CurrentAddress >> 16);
	ISPTarget_SendByte(0x00);
}

/** Waits until the last issued target memory programming command has completed, via the check mode given and using
 *  the given parameters.
 *
 *  \param[in] ProgrammingMode  Programming mode used and completion check to use, a mask of \c PROG_MODE_* constants
 *  \param[in] PollAddress      Memory address to poll for completion if polling check mode used
 *  \param[in] PollValue        Poll value to check against if polling check mode used
 *  \param[in] DelayMS          Milliseconds to delay before returning if delay check mode used
 *  \param[in] ReadMemCommand   Device low-level READ MEMORY command to send if value check mode used
 *
 *  \return V2 Protocol status \ref STATUS_CMD_OK if the no timeout occurred, \ref STATUS_RDY_BSY_TOUT or
 *          \ref STATUS_CMD_TOUT otherwise
 */
uint8_t ISPTarget_WaitForProgComplete(const uint8_t ProgrammingMode,
                                      const uint16_t PollAddress,
                                      const uint8_t PollValue,
                                      const uint8_t DelayMS,
                                      const uint8_t ReadMemCommand)
{
	uint8_t ProgrammingStatus = STATUS_CMD_OK;

	/* Determine method of Programming Complete check */
	switch (ProgrammingMode & ~(PROG_MODE_PAGED_WRITES_MASK | PROG_MODE_COMMIT_PAGE_MASK))
	{
		case PROG_MODE_WORD_TIMEDELAY_MASK:
		case PROG_MODE_PAGED_TIMEDELAY_MASK:
			ISPProtocol_DelayMS(DelayMS);
			break;
		case PROG_MODE_WORD_VALUE_MASK:
		case PROG_MODE_PAGED_VALUE_MASK:
			do
			{
				ISPTarget_SendByte(ReadMemCommand);
				ISPTarget_SendByte(PollAddress >> 8);
				ISPTarget_SendByte(PollAddress & 0xFF);
			}
			while ((ISPTarget_TransferByte(0x00) == PollValue) && TimeoutTicksRemaining);

			if (!(TimeoutTicksRemaining))
			  ProgrammingStatus = STATUS_CMD_TOUT;

			break;
		case PROG_MODE_WORD_READYBUSY_MASK:
		case PROG_MODE_PAGED_READYBUSY_MASK:
			ProgrammingStatus = ISPTarget_WaitWhileTargetBusy();
			break;
	}

	/* Program complete - reset timeout */
	TimeoutTicksRemaining = COMMAND_TIMEOUT_TICKS;

	return ProgrammingStatus;
}

#endif

