/*
            USB Missile Launcher Demo
        Copyright (C) Dave Fletcher, 2010.
         fletch at fletchtronics dot net

       Based on research by Scott Weston at
        http://code.google.com/p/pymissile
 */

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Dave Fletcher (fletch [at] fletchtronics [dot] net)

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
 *  Missile Launcher host. This is a host driver for the popular USB-controller table top toy missile launchers,
 *  which can typically aim and fire small foam "missiles" from a spring-loaded turret. This project controls the
 *  launcher via a joystick and button to aim and fire missiles at targets without a PC.
 */

/** \file
 *
 *  Main source file for the MissileLauncher application. This file contains the main tasks of
 *  the application and is responsible for the initial application hardware configuration as well
 *  as the sending of commands to the attached launcher toy.
 */

#include "MissileLauncher.h"

/** Launcher first init command report data sequence */
static const uint8_t CMD_INITA[8]     = {  85, 83, 66, 67,  0,  0,  4,  0  };

/** Launcher second init command report data sequence */
static const uint8_t CMD_INITB[8]     = {  85, 83, 66, 67,  0, 64,  2,  0  };

/** Launcher command report data sequence to stop all movement */
static const uint8_t CMD_STOP[8]      = {   0,  0,  0,  0,  0,  0,  8,  8  };

/** Launcher command report data sequence to move left */
static const uint8_t CMD_LEFT[8]      = {   0,  1,  0,  0,  0,  0,  8,  8  };

/** Launcher command report data sequence to move right */
static const uint8_t CMD_RIGHT[8]     = {   0,  0,  1,  0,  0,  0,  8,  8  };

/** Launcher command report data sequence to move up */
static const uint8_t CMD_UP[8]        = {   0,  0,  0,  1,  0,  0,  8,  8  };

/** Launcher command report data sequence to move down */
static const uint8_t CMD_DOWN[8]      = {   0,  0,  0,  0,  1,  0,  8,  8  };

/** Launcher command report data sequence to move left and up */
static const uint8_t CMD_LEFTUP[8]    = {   0,  1,  0,  1,  0,  0,  8,  8  };

/** Launcher command report data sequence to move right and up */
static const uint8_t CMD_RIGHTUP[8]   = {   0,  0,  1,  1,  0,  0,  8,  8  };

/** Launcher command report data sequence to move left and down */
static const uint8_t CMD_LEFTDOWN[8]  = {   0,  1,  0,  0,  1,  0,  8,  8  };

/** Launcher command report data sequence to move right and down */
static const uint8_t CMD_RIGHTDOWN[8] = {   0,  0,  1,  0,  1,  0,  8,  8  };

/** Launcher command report data sequence to fire a missile */
static const uint8_t CMD_FIRE[8]      = {   0,  0,  0,  0,  0,  1,  8,  8  };

/** Last command sent to the launcher, to determine what new command (if any) must be sent */
static const uint8_t* CmdState;

/** Buffer to hold a command to send to the launcher */
static uint8_t CmdBuffer[LAUNCHER_CMD_BUFFER_SIZE];


/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	CmdState = CMD_STOP;

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		Read_Joystick_Status();
		DiscardNextReport();

		USB_USBTask();
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
#endif

	/* Hardware Initialization */
	LEDs_Init();
	USB_Init();
	Joystick_Init();
	Buttons_Init();
}

/** Reads the joystick and button status, sending commands to the launcher as needed. */
void Read_Joystick_Status(void)
{
	uint8_t JoyStatus_LCL = Joystick_GetStatus();
	uint8_t Buttons_LCL   = Buttons_GetStatus();

	if (Buttons_LCL & BUTTONS_BUTTON1)
	  Send_Command(CMD_FIRE);
	else if (JoyStatus_LCL & JOY_UP)
	  Send_Command(CMD_UP);
	else if (JoyStatus_LCL & JOY_DOWN)
	  Send_Command(CMD_DOWN);
	else if (JoyStatus_LCL & JOY_LEFT)
	  Send_Command(CMD_LEFT);
	else if (JoyStatus_LCL & JOY_RIGHT)
	  Send_Command(CMD_RIGHT);
	else if (CmdState != CMD_STOP)
	  Send_Command(CMD_STOP);
}

/** Lower level send routine, copies report into a larger buffer and sends.
 *
 *  \param[in] Report  Report data to send.
 *  \param[in] ReportSize  Report length in bytes.
 */
void Send_Command_Report(const uint8_t* const Report,
                         const uint16_t ReportSize)
{
	memcpy(CmdBuffer, Report, 8);
	WriteNextReport(CmdBuffer, ReportSize);
}

/** Sends one of the \c CMD_* command constants to the attached device.
 *
 *  \param[in] Command  One of the command constants.
 */
void Send_Command(const uint8_t* const Command)
{
	if ((CmdState == CMD_STOP && Command != CMD_STOP) ||
		(CmdState != CMD_STOP && Command == CMD_STOP))
	{
		LEDs_ToggleLEDs(LEDS_LED4);

		Send_Command_Report(CMD_INITA, 8);
		Send_Command_Report(CMD_INITB, 8);
		Send_Command_Report(Command, LAUNCHER_CMD_BUFFER_SIZE);
	}

	CmdState = Command;
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Host_DeviceAttached(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_Host_DeviceUnattached(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_Host_DeviceEnumerationComplete(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);

	/* Get and process the configuration descriptor data */
	if (ProcessConfigurationDescriptor() != SuccessfulConfigRead)
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	/* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
	if (USB_Host_SetDeviceConfiguration(1) != HOST_SENDCONTROL_Successful)
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_Host_HostError(const uint8_t ErrorCode)
{
	USB_Disable();

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,
                                            const uint8_t SubErrorCode)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Reads in and discards the next report from the attached device. */
void DiscardNextReport(void)
{
	if (USB_HostState != HOST_STATE_Configured)
	  return;

	/* Select and unfreeze HID data IN pipe */
	Pipe_SelectPipe(HID_DATA_IN_PIPE);
	Pipe_Unfreeze();

	/* Check to see if a packet has been received */
	if (!(Pipe_IsINReceived()))
	{
		/* Refreeze HID data IN pipe */
		Pipe_Freeze();

		return;
	}

	/* Clear the IN endpoint, ready for next data packet */
	Pipe_ClearIN();

	/* Refreeze HID data IN pipe */
	Pipe_Freeze();
}

/** Writes a report to the attached device.
 *
 *  \param[in] ReportOUTData  Buffer containing the report to send to the device
 *  \param[in] ReportLength  Length of the report to send
 */
void WriteNextReport(uint8_t* const ReportOUTData,
                     const uint16_t ReportLength)
{
	if (USB_HostState != HOST_STATE_Configured)
	  return;

	/* Select and unfreeze HID data OUT pipe */
	Pipe_SelectPipe(HID_DATA_OUT_PIPE);

	/* Not all HID devices have an OUT endpoint (some require OUT reports to be sent over the
	 * control endpoint instead) - check to see if the OUT endpoint has been initialized */
	if (Pipe_IsConfigured())
	{
		Pipe_Unfreeze();

		/* Ensure pipe is ready to be written to before continuing */
		if (!(Pipe_IsOUTReady()))
		{
			/* Refreeze the data OUT pipe */
			Pipe_Freeze();

			return;
		}

		/* Write out HID report data */
		Pipe_Write_Stream_LE(ReportOUTData, ReportLength, NULL);

		/* Clear the OUT endpoint, send last data packet */
		Pipe_ClearOUT();

		/* Refreeze the data OUT pipe */
		Pipe_Freeze();
	}
	else
	{
		/* Class specific request to send a HID report to the device */
		USB_ControlRequest = (USB_Request_Header_t)
			{
				.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
				.bRequest      = HID_REQ_SetReport,
				.wValue        = 0x02,
				.wIndex        = 0x01,
				.wLength       = ReportLength,
			};

		/* Select the control pipe for the request transfer */
		Pipe_SelectPipe(PIPE_CONTROLPIPE);

		/* Send the request to the device */
		USB_Host_SendControlRequest(ReportOUTData);
	}
}

