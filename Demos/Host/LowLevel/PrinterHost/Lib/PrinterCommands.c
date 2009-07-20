/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \file
 *
 *  Printer Device commands, to send/recieve data to and from an attached USB
 *  printer, and to send and receive Printer Class control requests.
 */

#include "PrinterCommands.h"

/** Sends the given data directly to the printer via the data endpoints, for the sending of print commands in printer
 *  languages accepted by the attached printer (e.g. PCL).
 *
 *  \param[in] PrinterCommands  Pointer to a structure containing the commands and length of the data to send
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
uint8_t Printer_SendData(Printer_Data_t* PrinterCommands)
{
	uint8_t ErrorCode;

	Pipe_SelectPipe(PRINTER_DATA_OUT_PIPE);
	Pipe_Unfreeze();
	
	if ((ErrorCode = Pipe_Write_Stream_LE(PrinterCommands->Data, PrinterCommands->Length)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	Pipe_ClearOUT();
	while (!(Pipe_IsOUTReady()));
	
	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

/** Issues a Printer class Get Device ID command to the attached device, to retrieve the device ID string (which indicates
 *  the accepted printer languages, the printer's model and other pertinent information).
 *
 *  \param[out] DeviceIDString Pointer to the destination where the returned string should be stored
 *  \param[in] BufferSize  Size in bytes of the allocated buffer for the returned Device ID string
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t Printer_GetDeviceID(char* DeviceIDString, uint16_t BufferSize)
{
	uint8_t  ErrorCode = HOST_SENDCONTROL_Successful;
	uint16_t DeviceIDStringLength;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			bmRequestType: (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			bRequest:      GET_DEVICE_ID,
			wValue:        0,
			wIndex:        0,
			wLength:       sizeof(DeviceIDStringLength),
		};

	if ((ErrorCode = USB_Host_SendControlRequest(&DeviceIDStringLength)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;
	
	DeviceIDStringLength = SwapEndian_16(DeviceIDStringLength);

	if (DeviceIDStringLength > BufferSize)
	  DeviceIDStringLength = BufferSize;

	USB_ControlRequest.wLength = DeviceIDStringLength;
	
	if ((ErrorCode = USB_Host_SendControlRequest(DeviceIDString)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;
	  
	/* Move string back two characters to remove the string length value from the start of the array */
	memmove(&DeviceIDString[0], &DeviceIDString[2], DeviceIDStringLength - 2);

	DeviceIDString[DeviceIDStringLength - 2] = 0x00;
	
	return HOST_SENDCONTROL_Successful;
}

/** Issues a Printer class Get Port Status command to the attached device, to retrieve the current status flags of the
 *  printer.
 *
 *  \param[out] PortStatus  Pointer to the destination where the printer's status flag values should be stored
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t Printer_GetPortStatus(uint8_t* PortStatus)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			bmRequestType: (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			bRequest:      GET_PORT_STATUS,
			wValue:        0,
			wIndex:        0,
			wLength:       sizeof(uint8_t),
		};

	return USB_Host_SendControlRequest(PortStatus);
}

/** Issues a Printer class Soft Reset command to the attached device, to reset the printer ready for new input without
 *  physically cycling the printer's power.
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t Printer_SoftReset(void)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			bmRequestType: (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			bRequest:      SOFT_RESET,
			wValue:        0,
			wIndex:        0,
			wLength:       0,
		};

	return USB_Host_SendControlRequest(NULL);
}

