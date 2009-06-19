/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
         USB Missile Launcher Demo
	 Copyright (C) Dave Fletcher, 2009.
	  fletch at fletchtronics dot net
	  
	 Based on research by Scott Weston at
	  http://code.google.com/p/pymissile
 */

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2009  Dave Fletcher (fletch [at] fletchtronics [dot] net)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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
uint8_t CMD_INITA[8]     = {  85, 83, 66, 67,  0,  0,  4,  0  };

/** Launcher second init command report data sequence */
uint8_t CMD_INITB[8]     = {  85, 83, 66, 67,  0, 64,  2,  0  };

/** Launcher command report data sequence to stop all movement */
uint8_t CMD_STOP[8]      = {   0,  0,  0,  0,  0,  0,  8,  8  };

/** Launcher command report data sequence to move left */
uint8_t CMD_LEFT[8]      = {   0,  1,  0,  0,  0,  0,  8,  8  };

/** Launcher command report data sequence to move right */
uint8_t CMD_RIGHT[8]     = {   0,  0,  1,  0,  0,  0,  8,  8  };

/** Launcher command report data sequence to move up */
uint8_t CMD_UP[8]        = {   0,  0,  0,  1,  0,  0,  8,  8  };

/** Launcher command report data sequence to move down */
uint8_t CMD_DOWN[8]      = {   0,  0,  0,  0,  1,  0,  8,  8  };

/** Launcher command report data sequence to move left and up */
uint8_t CMD_LEFTUP[8]    = {   0,  1,  0,  1,  0,  0,  8,  8  };

/** Launcher command report data sequence to move right and up */
uint8_t CMD_RIGHTUP[8]   = {   0,  0,  1,  1,  0,  0,  8,  8  };

/** Launcher command report data sequence to move left and down */
uint8_t CMD_LEFTDOWN[8]  = {   0,  1,  0,  0,  1,  0,  8,  8  };

/** Launcher command report data sequence to move right and down */
uint8_t CMD_RIGHTDOWN[8] = {   0,  0,  1,  0,  1,  0,  8,  8  };

/** Launcher command report data sequence to fire a missile */
uint8_t CMD_FIRE[8]      = {   0,  0,  0,  0,  0,  1,  8,  8  };

/** Last command sent to the launcher, to determine what new command (if any) must be sent */
uint8_t* CmdState;

/** Buffer to hold a command to send to the launcher */
uint8_t  CmdBuffer[LAUNCHER_CMD_BUFFER_SIZE];


/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	
	CmdState = CMD_STOP;

	for (;;)
	{
		Read_Joystick_Status();
	
		HID_Host_Task();
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

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

	if (BUTTONS_BUTTON1 && Buttons_GetStatus())
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
 *  \param Report  Report data to send.
 *  \param ReportSize  Report length in bytes.
 */
void Send_Command_Report(uint8_t *Report, uint16_t ReportSize)
{
	memcpy(CmdBuffer, Report, 8);
	WriteNextReport(CmdBuffer, ReportSize);
}

/** Send one of the CMD_* command constants listed above.
 *
 *  \param Command  One of the command constants.
 */
void Send_Command(uint8_t* Command)
{
	if ((CmdState == CMD_STOP && Command != CMD_STOP) ||
		(CmdState != CMD_STOP && Command == CMD_STOP))
	{
		LEDs_ChangeLEDs(LEDS_LED4, ~LEDs_GetLEDs() & LEDS_LED4);

		Send_Command_Report(CMD_INITA, 8);
		Send_Command_Report(CMD_INITB, 8);
		Send_Command_Report(Command, LAUNCHER_CMD_BUFFER_SIZE);
	}
	
	CmdState = Command;
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_DeviceAttached(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_DeviceUnattached(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_DeviceEnumerationComplete(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_HostError(const uint8_t ErrorCode)
{
	USB_ShutDown();

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Reads in and discards the next report from the attached device. */
void DiscardNextReport(void)
{
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
 *  \param ReportOUTData  Buffer containing the report to send to the device
 *  \param ReportLength  Length of the report to send
 */
void WriteNextReport(uint8_t* ReportOUTData, uint16_t ReportLength)
{
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
		Pipe_Write_Stream_LE(ReportOUTData, ReportLength);				
			
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
				.bmRequestType = 0x21,
				.bRequest      = 0x09,
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

/** Task to set the configuration of the attached device after it has been enumerated, and to read and process
 *  HID reports from the device and to send reports if desired.
 */
void HID_Host_Task(void)
{
	uint8_t ErrorCode;

	/* Switch to determine what user-application handled host state the host state machine is in */
	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			/* Get and process the configuration descriptor data */
			if ((ErrorCode = ProcessConfigurationDescriptor()) != SuccessfulConfigRead)
			{
				/* Indicate error status */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}

			/* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
			if ((ErrorCode = USB_Host_SetDeviceConfiguration(1)) != HOST_SENDCONTROL_Successful)
			{
				/* Indicate error status */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
				
				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}
			
			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			USB_HostState = HOST_STATE_Ready;
			break;
		case HOST_STATE_Ready:
			DiscardNextReport();

			break;
	}
}
