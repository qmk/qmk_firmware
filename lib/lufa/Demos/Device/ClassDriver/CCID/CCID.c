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
 *  Main source file for the CCID demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
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

/** LUFA CCID Class driver interface configuration and state information. This structure is
 *  passed to all CCID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CCID_Device_t CCID_Interface =
	{
		.Config =
			{
				.InterfaceNumber              = INTERFACE_ID_CCID,
				.TotalSlots                   = 1,
				.DataINEndpoint               =
					{
						.Address              = CCID_IN_EPADDR,
						.Size                 = CCID_EPSIZE,
						.Banks                = 1,
					},
				.DataOUTEndpoint              =
					{
						.Address              = CCID_OUT_EPADDR,
						.Size                 = CCID_EPSIZE,
						.Banks                = 1,
					},
			},
	};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		USB_USBTask();
		CCID_Device_USBTask(&CCID_Interface);
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

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= CCID_Device_ConfigureEndpoints(&CCID_Interface);

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	CCID_Device_ProcessControlRequest(&CCID_Interface);
}

/** Event handler for the CCID_PC_to_RDR_IccPowerOn message. This message is sent to the device
 *  whenever an application at the host wants to send a power off signal to a slot.
 *  THe slot must reply back with a recognizable ATR (answer to reset)
 */
uint8_t CALLBACK_CCID_IccPowerOn(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
                                 const uint8_t slot,
								 uint8_t* const atr,
								 uint8_t* const attrSize,
								 uint8_t* const error)
{
	if (slot < CCID_Interface.Config.TotalSlots)
	{
		Iso7816_CreateSimpleAtr(atr, attrSize);
		*error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else
	{
		*error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}

/** Event handler for the CCID_PC_to_RDR_IccPowerOff message. This message is sent to the device
 *  whenever an application at the host wants to send a power off signal to a slot.
 */
uint8_t CALLBACK_CCID_IccPowerOff(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
                                  const uint8_t slot,
                                  uint8_t* const error)
{
	if (slot < CCID_Interface.Config.TotalSlots)
	{
		*error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_NOICCPRESENT;
	}
	else
	{
		*error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}

/** Event handler for the CCID_PC_to_RDR_GetSlotStatus. This message is sent to the device
 *  whenever an application at the host wants to the get the current slot status
 *
 */
uint8_t CALLBACK_CCID_GetSlotStatus(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
                                    const uint8_t slot,
                                    uint8_t* const error)
{
	if (slot < CCID_Interface.Config.TotalSlots)
	{
		*error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else
	{
		*error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}

/** Event handler for the CCID_PC_to_RDR_SetParameters when T=0. This message is sent to
 *  the device whenever an application at the host wants to set the parameters for a
 *  given slot.
 */
uint8_t CALLBACK_CCID_SetParameters_T0(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
									   const uint8_t Slot,
									   uint8_t* const Error,
									   USB_CCID_ProtocolData_T0_t* const T0)
{
	if (Slot == 0)
	{
		// Set parameters
		memcpy(&CCIDInterfaceInfo->ProtocolData, T0, sizeof(USB_CCID_ProtocolData_T0_t));

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
 *  the device whenever an application at the host wants to get the current parameters for
 *  a given slot.
 */
uint8_t CALLBACK_CCID_GetParameters_T0(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
									   const uint8_t Slot,
									   uint8_t* const Error,
									   uint8_t* const ProtocolNum,
									   USB_CCID_ProtocolData_T0_t* const T0)
{
	if (Slot == 0)
	{
		*ProtocolNum = CCID_PROTOCOLNUM_T0;
		memcpy(T0, &CCIDInterfaceInfo->ProtocolData, sizeof(USB_CCID_ProtocolData_T0_t));

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
uint8_t CALLBACK_CCID_XfrBlock(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
							   const uint8_t Slot,
							   const uint8_t* ReceivedBuffer,
							   const uint8_t ReceivedBufferSize,
							   uint8_t* const SendBuffer,
							   uint8_t* const SentBufferSize,
							   uint8_t* const Error)
{
	if (Slot < CCID_Interface.Config.TotalSlots)
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

uint8_t CALLBACK_CCID_Abort(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
                            const uint8_t Slot,
							const uint8_t Seq,
							uint8_t* const Error)
{
	if (CCID_Interface.State.Aborted && Slot == 0 && CCID_Interface.State.AbortedSeq == Seq)
	{
		CCID_Interface.State.Aborted    = false;
		CCID_Interface.State.AbortedSeq = -1;

		*Error = CCID_ERROR_NO_ERROR;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else if (!CCID_Interface.State.Aborted)
	{
		*Error = CCID_ERROR_CMD_NOT_ABORTED;
		return CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR | CCID_ICCSTATUS_PRESENTANDACTIVE;
	}
	else if (Slot != 0)
	{
		*Error = CCID_ERROR_SLOT_NOT_FOUND;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
	else
	{
		*Error = CCID_ERROR_NOT_SUPPORTED;
		return CCID_COMMANDSTATUS_FAILED | CCID_ICCSTATUS_NOICCPRESENT;
	}
}
