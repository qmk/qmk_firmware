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
 *  Target-related functions for the ISP Protocol decoder.
 */

#include "ISPTarget.h"

#if defined(ENABLE_ISP_PROTOCOL) || defined(__DOXYGEN__)

/** Converts the given AVR Studio SCK duration parameter (set by a SET PARAM command from the host) to the nearest
 *  possible SPI clock prescaler mask for passing to the SPI_Init() routine.
 *
 *  \return Nearest SPI prescaler mask for the given SCK frequency
 */
uint8_t ISPTarget_GetSPIPrescalerMask(void)
{
	static const uint8_t SPIMaskFromSCKDuration[] =
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

	uint8_t SCKDuration = V2Params_GetParameterValue(PARAM_SCK_DURATION);

	if (SCKDuration >= sizeof(SPIMaskFromSCKDuration))
	  SCKDuration = (sizeof(SPIMaskFromSCKDuration) - 1);
	  
	return SPIMaskFromSCKDuration[SCKDuration];
}

/** Asserts or deasserts the target's reset line, using the correct polarity as set by the host using a SET PARAM command.
 *  When not asserted, the line is tristated so as not to interfere with normal device operation.
 *
 *  \param[in] ResetTarget Boolean true when the target should be held in reset, false otherwise
 */
void ISPTarget_ChangeTargetResetLine(const bool ResetTarget)
{
	if (ResetTarget)
	{
		AUX_LINE_DDR |= AUX_LINE_MASK;
		
		if (!(V2Params_GetParameterValue(PARAM_RESET_POLARITY)))
		  AUX_LINE_PORT |= AUX_LINE_MASK;
	}
	else
	{
		AUX_LINE_DDR  &= ~AUX_LINE_MASK;
		AUX_LINE_PORT &= ~AUX_LINE_MASK;
	}
}

/** Waits until the last issued target memory programming command has completed, via the check mode given and using
 *  the given parameters.
 *
 *  \param[in] ProgrammingMode  Programming mode used and completion check to use, a mask of PROG_MODE_* constants
 *  \param[in] PollAddress  Memory address to poll for completion if polling check mode used
 *  \param[in] PollValue  Poll value to check against if polling check mode used
 *  \param[in] DelayMS  Milliseconds to delay before returning if delay check mode used
 *  \param[in] ReadMemCommand  Device low-level READ MEMORY command to send if value check mode used
 *
 *  \return V2 Protocol status \ref STATUS_CMD_OK if the no timeout occurred, \ref STATUS_RDY_BSY_TOUT or
 *          \ref STATUS_CMD_TOUT otherwise
 */
uint8_t ISPTarget_WaitForProgComplete(const uint8_t ProgrammingMode, const uint16_t PollAddress, const uint8_t PollValue,
                                      const uint8_t DelayMS, const uint8_t ReadMemCommand)
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
				SPI_SendByte(ReadMemCommand);
				SPI_SendByte(PollAddress >> 8);
				SPI_SendByte(PollAddress & 0xFF);
			}
			while ((SPI_TransferByte(0x00) == PollValue) && TimeoutMSRemaining);

			if (!(TimeoutMSRemaining))
			 ProgrammingStatus = STATUS_CMD_TOUT;
			
			break;		
		case PROG_MODE_WORD_READYBUSY_MASK:
		case PROG_MODE_PAGED_READYBUSY_MASK:
			ProgrammingStatus = ISPTarget_WaitWhileTargetBusy();
			break;
	}

	return ProgrammingStatus;
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
		SPI_SendByte(0xF0);
		SPI_SendByte(0x00);

		SPI_SendByte(0x00);
	}
	while ((SPI_ReceiveByte() & 0x01) && TimeoutMSRemaining);

	if (!(TimeoutMSRemaining))
	  return STATUS_RDY_BSY_TOUT;
	else
	  return STATUS_CMD_OK;
}

/** Sends a low-level LOAD EXTENDED ADDRESS command to the target, for addressing of memory beyond the
 *  64KB boundary. This sends the command with the correct address as indicated by the current address
 *  pointer variable set by the host when a SET ADDRESS command is issued.
 */
void ISPTarget_LoadExtendedAddress(void)
{
	SPI_SendByte(LOAD_EXTENDED_ADDRESS_CMD);
	SPI_SendByte(0x00);
	SPI_SendByte((CurrentAddress & 0x00FF0000) >> 16);
	SPI_SendByte(0x00);	
}

#endif
