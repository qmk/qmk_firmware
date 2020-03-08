/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2019  Filipe Rodrigues (filipepazrodrigues [at] gmail [dot] com)

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
 *  Main source file for the CCID demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 *
 *  \warning
 *  LUFA is not a secure USB stack, and has not undergone, not is it expected to pass, any
 *  form of security audit. The CCID class here is presented as-is and is intended for
 *  research purposes only, and *should not* be used in a security critical application
 *  under any circumstances.
 *
 *  \warning
 *  This code is not production ready and should not by any means be considered safe.
 *  If you plan to integrate it into your application, you should seriously consider strong
 *  encryption algorithms or a secure microprocessor. Since Atmel AVR microprocessors do not
 *  have any security requirement (therefore they don't offer any known protection against
 *  side channel attacks or fault injection) a secure microprocessor is the best option.
 */

#include "CCID.h"

static bool    Aborted;
static uint8_t AbortedSeq;

static USB_CCID_ProtocolData_T0_t ProtocolData =
	{
		.FindexDindex     = 0x11,
		.TCCKST0          = 0x00,
		.GuardTimeT0      = 0x00,
		.WaitingIntegerT0 = 0x0A,
		.ClockStop        = 0x00,
	};

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		USB_USBTask();
		CCID_Task();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#elif (ARCH == ARCH_XMEGA)
	/* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
	XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
	XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

	/* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
	XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
	XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#endif

	/* Hardware Initialization */
	LEDs_Init();
	USB_Init();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs. */
void EVENT_USB_Device_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs.
 */
void EVENT_USB_Device_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	/* Setup CCID Data Endpoints */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(CCID_IN_EPADDR,  EP_TYPE_BULK, CCID_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(CCID_OUT_EPADDR, EP_TYPE_BULK, CCID_EPSIZE, 1);

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
	switch (USB_ControlRequest.bRequest)
	{
		case CCID_ABORT:
		{
			// Initiates the abort process
			// The host should send 2 messages in the following order:
			//  - CCID_ABORT control request
			//  - CCID_PC_t_PCo_RDR_Abort command
			//
			// If the device is still processing a message, it should fail it until receiving a CCIRPC_to_RDR_Abort
			// command.
			//
			// When the device receives the CCIRPC_to_RDR_Abort message, it replies with  RDR_to_PC_SlotStatus
			// and the abort process ends

			// The  wValue  field  contains the slot number (bSlot) in the low byte and the sequence number (bSeq) in
			// the high  byte
			uint8_t Slot = USB_ControlRequest.wValue & 0xFF;
			uint8_t Seq  = USB_ControlRequest.wValue >> 8;

			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE) && Slot == 0)
			{
				Endpoint_ClearSETUP();

				Aborted    = true;
				AbortedSeq = Seq;

				Endpoint_ClearOUT();
			}

			break;
		}

		case CCID_GET_CLOCK_FREQUENCIES:
		{
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_Write_8(0); // Not supported
				Endpoint_ClearOUT();
			}

			break;
		}

		case CCID_GET_DATA_RATES:
		{
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_Write_8(0); // Not supported
				Endpoint_ClearOUT();
			}

			break;
		}
	}
}

/** Event handler for the CCID_PC_to_RDR_IccPowerOn message. This message is sent to the device
 *  whenever an application at the host wants to send a power off signal to a slot.
 *  THe slot must reply back with a recognizable ATR (answer to reset)
 */
uint8_t CCID_IccPowerOn(uint8_t Slot,
						uint8_t* const Atr,
						uint8_t* const AtrLength,
                        uint8_t* const Error)
{
	if (Slot == 0)
	{
		Iso7816_CreateSimpleAtr(Atr, AtrLength);

		*Error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else
	{
		*Error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}

/** Event handler for the CCID_PC_to_RDR_IccPowerOff message. This message is sent to the device
 *  whenever an application at the host wants to send a power off signal to a slot.
 */
uint8_t CCID_IccPowerOff(uint8_t Slot,
                         uint8_t* const Error)
{
	if (Slot == 0)
	{
		*Error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_NOICCPRESENT;
	}
	else
	{
		*Error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}

/** Event handler for the CCID_PC_to_RDR_GetSlotStatus. THis message is sent to
 *  the device whenever an application at the host wants to get the current
 *  slot status.
 */
uint8_t CCID_GetSlotStatus(uint8_t Slot,
                           uint8_t* const Error)
{
	if (Slot == 0)
	{
		*Error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else
	{
		*Error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}

/** Event handler for the CCID_PC_to_RDR_SetParameters when T=0. This message is sent to
 *  the device whenever an application at the host wants to set the
 *  parameters for a given slot.
 */
uint8_t CCID_SetParameters_T0(uint8_t Slot,
                              uint8_t* const Error,
                              USB_CCID_ProtocolData_T0_t* const T0)
{
	if (Slot == 0)
	{
		// Set parameters
		memcpy(&ProtocolData, T0, sizeof(USB_CCID_ProtocolData_T0_t));

		*Error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else
	{
		*Error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}

/** Event handler for the CCID_PC_to_RDR_GetParameters when T=0. This message is sent to
 *  the device whenever an application at the host wants to get the current
 *  parameters for a given slot.
 */
uint8_t CCID_GetParameters_T0(uint8_t Slot,
                              uint8_t* const Error,
                              uint8_t* ProtocolNum,
                              USB_CCID_ProtocolData_T0_t* const T0)
{
	if (Slot == 0)
	{

		*ProtocolNum = CCID_PROTOCOLNUM_T0;
		memcpy(T0, &ProtocolData, sizeof(USB_CCID_ProtocolData_T0_t));

		*Error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else
	{
		*Error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}

/** Event handler for the CCID_PC_to_RDR_XfrBlock. This message is sent to the device
 *  whenever an application at the host wants to send a block of bytes to the device
 *  THe device reply back with an array of bytes
 */
uint8_t CCID_XfrBlock(uint8_t Slot,
					  uint8_t* const ReceivedBuffer,
					  uint8_t ReceivedBufferSize,
					  uint8_t* const SendBuffer,
					  uint8_t* const SentBufferSize,
					  uint8_t* const Error)
{
	if (Slot == 0)
	{
		uint8_t OkResponse[2] = {0x90, 0x00};

		memcpy(SendBuffer, OkResponse, sizeof(OkResponse));
		*SentBufferSize = sizeof(OkResponse);

		*Error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_NOICCPRESENT;
	}
	else
	{
		 *Error = CCID_ERROR_SLOT_NOT_FOUND;
         return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}

/** Event handler for the CCID_PC_to_RDR_ABort message. This message is sent to the device
 *  whenever an application wants to abort the current operation. A previous CCID_ABORT
 *  control message has to be sent before this one in order to start the abort operation.
 */
uint8_t CCID_Abort(uint8_t Slot,
                   uint8_t Seq,
                   uint8_t* const Error)
{
	if (Aborted && Slot == 0 && AbortedSeq == Seq)
	{
		Aborted    = false;
		AbortedSeq = -1;

		*Error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else if (!Aborted)
	{
		*Error = CCID_ERROR_CMD_NOT_ABORTED;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else if (Slot != 0)
	{
		*Error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}

	*Error = CCID_ERROR_NOT_SUPPORTED;
	return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
}

/** Gets and status and verifies whether an error occurred. */
bool CCID_CheckStatusNoError(uint8_t Status)
{
	return (Status & 0xC0) == 0x0;
}

/** Function to manage CCID request parsing and responses back to the host. */
void CCID_Task(void)
{
	Endpoint_SelectEndpoint(CCID_OUT_EPADDR);

	uint8_t RequestBuffer[CCID_EPSIZE - sizeof(USB_CCID_BulkMessage_Header_t)];
	uint8_t ResponseBuffer[CCID_EPSIZE];
	Aborted = false;
	AbortedSeq = -1;

	if (Endpoint_IsOUTReceived())
	{
		USB_CCID_BulkMessage_Header_t CCIDHeader;
		CCIDHeader.MessageType = Endpoint_Read_8();
		CCIDHeader.Length      = Endpoint_Read_32_LE();
		CCIDHeader.Slot        = Endpoint_Read_8();
		CCIDHeader.Seq         = Endpoint_Read_8();

		uint8_t Status;
		uint8_t Error = CCID_ERROR_NO_ERROR;

		switch (CCIDHeader.MessageType)
		{
			case CCID_PC_to_RDR_IccPowerOn:
			{
				uint8_t  AtrLength;
				USB_CCID_RDR_to_PC_DataBlock_t* ResponseATR = (USB_CCID_RDR_to_PC_DataBlock_t*)&ResponseBuffer;

				ResponseATR->CCIDHeader.MessageType = CCID_RDR_to_PC_DataBlock;
				ResponseATR->CCIDHeader.Slot        = CCIDHeader.Slot;
				ResponseATR->CCIDHeader.Seq         = CCIDHeader.Seq;
				ResponseATR->ChainParam             = 0;

				Status = CCID_IccPowerOn(ResponseATR->CCIDHeader.Slot, (uint8_t* )ResponseATR->Data, &AtrLength, &Error);

				if (CCID_CheckStatusNoError(Status) && !Aborted)
				{
					ResponseATR->CCIDHeader.Length = AtrLength;
				}
				else if (Aborted)
				{
					Status = CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_PRESENTANDACTIVE;
					Error =  CCID_ERROR_CMD_ABORTED;
					AtrLength = 0;
				}
				else
				{
					AtrLength = 0;
				}

				ResponseATR->Status = Status;
				ResponseATR->Error  = Error;

				Endpoint_ClearOUT();

				Endpoint_SelectEndpoint(CCID_IN_EPADDR);
				Endpoint_Write_Stream_LE(ResponseATR, sizeof(USB_CCID_RDR_to_PC_DataBlock_t) + AtrLength, NULL);
				Endpoint_ClearIN();
				break;
			}

			case CCID_PC_to_RDR_IccPowerOff:
			{
				USB_CCID_RDR_to_PC_SlotStatus_t* ResponsePowerOff =  (USB_CCID_RDR_to_PC_SlotStatus_t*)&ResponseBuffer;
				ResponsePowerOff->CCIDHeader.MessageType = CCID_RDR_to_PC_SlotStatus;
				ResponsePowerOff->CCIDHeader.Length      = 0;
				ResponsePowerOff->CCIDHeader.Slot        = CCIDHeader.Slot;
				ResponsePowerOff->CCIDHeader.Seq         = CCIDHeader.Seq;

				ResponsePowerOff->ClockStatus = 0;

				Status = CCID_IccPowerOff(CCIDHeader.Slot, &Error);

				ResponsePowerOff->Status = Status;
				ResponsePowerOff->Error  = Error;

				Endpoint_ClearOUT();

				Endpoint_SelectEndpoint(CCID_IN_EPADDR);
				Endpoint_Write_Stream_LE(ResponsePowerOff, sizeof(USB_CCID_RDR_to_PC_SlotStatus_t), NULL);
				Endpoint_ClearIN();
				break;
			}

			case CCID_PC_to_RDR_GetSlotStatus:
			{
				USB_CCID_RDR_to_PC_SlotStatus_t* ResponseSlotStatus = (USB_CCID_RDR_to_PC_SlotStatus_t*)&ResponseBuffer;
				ResponseSlotStatus->CCIDHeader.MessageType = CCID_RDR_to_PC_SlotStatus;
				ResponseSlotStatus->CCIDHeader.Length      = 0;
				ResponseSlotStatus->CCIDHeader.Slot        = CCIDHeader.Slot;
				ResponseSlotStatus->CCIDHeader.Seq         = CCIDHeader.Seq;

				ResponseSlotStatus->ClockStatus = 0;

				Status = CCID_GetSlotStatus(CCIDHeader.Slot, &Error);

				ResponseSlotStatus->Status = Status;
				ResponseSlotStatus->Error  = Error;

				Endpoint_ClearOUT();

				Endpoint_SelectEndpoint(CCID_IN_EPADDR);
				Endpoint_Write_Stream_LE(ResponseSlotStatus, sizeof(USB_CCID_RDR_to_PC_SlotStatus_t), NULL);
				Endpoint_ClearIN();
				break;
			}

			case CCID_PC_to_RDR_SetParameters:
			{
				uint8_t ProtocolNum = Endpoint_Read_8();
				uint8_t RFU = Endpoint_Read_16_LE();

				(void)RFU;

				USB_CCID_RDR_to_PC_Parameters_t* ResponseParametersStatus = (USB_CCID_RDR_to_PC_Parameters_t*)&ResponseBuffer;
				ResponseParametersStatus->CCIDHeader.MessageType = CCID_RDR_to_PC_Parameters;
				ResponseParametersStatus->CCIDHeader.Length      = 0;
				ResponseParametersStatus->CCIDHeader.Slot        = CCIDHeader.Slot;
				ResponseParametersStatus->CCIDHeader.Seq         = CCIDHeader.Seq;

				if (ProtocolNum == CCID_PROTOCOLNUM_T0)
				{
					if ((CCIDHeader.Length * sizeof(uint8_t)) == sizeof(USB_CCID_ProtocolData_T0_t))
					{
						Endpoint_Read_Stream_LE(RequestBuffer, CCIDHeader.Length * sizeof(uint8_t), NULL);

						Status = CCID_SetParameters_T0(CCIDHeader.Slot, &Error, (USB_CCID_ProtocolData_T0_t*)RequestBuffer);
						if (CCID_CheckStatusNoError(Status))
						{
							ResponseParametersStatus->CCIDHeader.Length = CCIDHeader.Length;
							Status = CCID_GetParameters_T0(CCIDHeader.Slot, &Error, &ResponseParametersStatus->ProtocolNum, (USB_CCID_ProtocolData_T0_t*) &ResponseParametersStatus->ProtocolData);
						}
					}
					else
					{
						// Unexpected length
						Status = CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_PRESENTANDACTIVE;
					}
				}
				else
				{
					ResponseParametersStatus->ProtocolNum = CCID_PROTOCOLNUM_T0;

					// For now, we don't support T=1 protocol
					Error  = CCID_ERROR_PARAMETERS_PROTOCOL_NOT_SUPPORTED;
					Status = CCID_COMMANDSTATUS_ERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
				}

				ResponseParametersStatus->Status = Status;
				ResponseParametersStatus->Error  = Error;

				Endpoint_ClearOUT();

				Endpoint_SelectEndpoint(CCID_IN_EPADDR);
				Endpoint_Write_Stream_LE(ResponseParametersStatus, sizeof(USB_CCID_BulkMessage_Header_t) + 3 + ResponseParametersStatus->CCIDHeader.Length, NULL);
				Endpoint_ClearIN();
				break;
			}

			case CCID_PC_to_RDR_GetParameters:
			{
				USB_CCID_RDR_to_PC_Parameters_t* ResponseParametersStatus = (USB_CCID_RDR_to_PC_Parameters_t*)&ResponseBuffer;
				ResponseParametersStatus->CCIDHeader.MessageType = CCID_RDR_to_PC_Parameters;
				ResponseParametersStatus->CCIDHeader.Length      = sizeof(USB_CCID_ProtocolData_T0_t);
				ResponseParametersStatus->CCIDHeader.Slot        = CCIDHeader.Slot;
				ResponseParametersStatus->CCIDHeader.Seq         = CCIDHeader.Seq;

				Status = CCID_GetParameters_T0(CCIDHeader.Slot, &Error, &ResponseParametersStatus->ProtocolNum, (USB_CCID_ProtocolData_T0_t*) &ResponseParametersStatus->ProtocolData);

				ResponseParametersStatus->Status = Status;
				ResponseParametersStatus->Error  = Error;

				Endpoint_ClearOUT();

				Endpoint_SelectEndpoint(CCID_IN_EPADDR);
				Endpoint_Write_Stream_LE(ResponseParametersStatus, sizeof(USB_CCID_BulkMessage_Header_t) + 3 + ResponseParametersStatus->CCIDHeader.Length, NULL);
				Endpoint_ClearIN();
				break;
			}

			case CCID_PC_to_RDR_XfrBlock:
			{
				uint8_t  Bwi            = Endpoint_Read_8();
				uint16_t LevelParameter = Endpoint_Read_16_LE();

				(void)Bwi;
				(void)LevelParameter;

				Endpoint_Read_Stream_LE(RequestBuffer, CCIDHeader.Length * sizeof(uint8_t), NULL);

				uint8_t  ResponseDataLength = 0;

				USB_CCID_RDR_to_PC_DataBlock_t* ResponseBlock = (USB_CCID_RDR_to_PC_DataBlock_t*)&ResponseBuffer;
				ResponseBlock->CCIDHeader.MessageType = CCID_RDR_to_PC_DataBlock;
				ResponseBlock->CCIDHeader.Slot        = CCIDHeader.Slot;
				ResponseBlock->CCIDHeader.Seq         = CCIDHeader.Seq;

				ResponseBlock->ChainParam = 0;

				Status = CCID_XfrBlock(CCIDHeader.Slot, RequestBuffer, CCIDHeader.Length, (uint8_t*) &ResponseBlock->Data, &ResponseDataLength, &Error);

				if (CCID_CheckStatusNoError(Status) && !Aborted)
				{
					ResponseBlock->CCIDHeader.Length = ResponseDataLength;
				}
				else if (Aborted)
				{
					Status = CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_PRESENTANDACTIVE;
					Error  = CCID_ERROR_CMD_ABORTED;
					ResponseDataLength = 0;
				}
				else
				{
					ResponseDataLength = 0;
				}

				ResponseBlock->Status = Status;
				ResponseBlock->Error  = Error;

				Endpoint_ClearOUT();

				Endpoint_SelectEndpoint(CCID_IN_EPADDR);
				Endpoint_Write_Stream_LE(ResponseBlock, sizeof(USB_CCID_RDR_to_PC_DataBlock_t) + ResponseDataLength, NULL);
				Endpoint_ClearIN();
				break;
			}

			case CCID_PC_to_RDR_Abort:
			{
				USB_CCID_RDR_to_PC_SlotStatus_t* ResponseAbort =  (USB_CCID_RDR_to_PC_SlotStatus_t*)&ResponseBuffer;
				ResponseAbort->CCIDHeader.MessageType = CCID_RDR_to_PC_SlotStatus;
				ResponseAbort->CCIDHeader.Length      = 0;
				ResponseAbort->CCIDHeader.Slot        = CCIDHeader.Slot;
				ResponseAbort->CCIDHeader.Seq         = CCIDHeader.Seq;

				ResponseAbort->ClockStatus = 0;

				Status = CCID_Abort(CCIDHeader.Slot, CCIDHeader.Seq, &Error);

				ResponseAbort->Status = Status;
				ResponseAbort->Error  = Error;

				Endpoint_ClearOUT();

				Endpoint_SelectEndpoint(CCID_IN_EPADDR);
				Endpoint_Write_Stream_LE(ResponseAbort, sizeof(USB_CCID_RDR_to_PC_SlotStatus_t), NULL);
				Endpoint_ClearIN();
				break;
			}

			default:
			{
				memset(ResponseBuffer, 0x00, sizeof(ResponseBuffer));

				Endpoint_SelectEndpoint(CCID_IN_EPADDR);
				Endpoint_Write_Stream_LE(ResponseBuffer, sizeof(ResponseBuffer), NULL);
				Endpoint_ClearIN();
			}
		}
	}
}
