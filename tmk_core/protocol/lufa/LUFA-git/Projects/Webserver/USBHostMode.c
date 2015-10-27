/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  USB Host Mode management functions and variables. This file contains the LUFA code required to
 *  manage the USB RNDIS host mode.
 */

#include "USBHostMode.h"

/** LUFA RNDIS Class driver interface configuration and state information. This structure is
 *  passed to all RNDIS Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_RNDIS_Host_t Ethernet_RNDIS_Interface_Host =
	{
		.Config =
			{
				.DataINPipe             =
					{
						.Address        = (PIPE_DIR_IN  | 1),
						.Banks          = 1,
					},
				.DataOUTPipe            =
					{
						.Address        = (PIPE_DIR_OUT | 2),
						.Banks          = 1,
					},
				.NotificationPipe       =
					{
						.Address        = (PIPE_DIR_IN  | 3),
						.Banks          = 1,
					},
				.HostMaxPacketSize      = UIP_CONF_BUFFER_SIZE,
			},
	};


/** USB host mode management task. This function manages the RNDIS Host class driver and uIP stack when the device is
 *  initialized in USB host mode.
 */
void USBHostMode_USBTask(void)
{
	if (USB_CurrentMode != USB_MODE_Host)
	  return;

	uIPManagement_ManageNetwork();

	RNDIS_Host_USBTask(&Ethernet_RNDIS_Interface_Host);
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

	uint16_t ConfigDescriptorSize;
	uint8_t  ConfigDescriptorData[512];

	if (USB_Host_GetDeviceConfigDescriptor(1, &ConfigDescriptorSize, ConfigDescriptorData,
	                                       sizeof(ConfigDescriptorData)) != HOST_GETCONFIG_Successful)
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	if (RNDIS_Host_ConfigurePipes(&Ethernet_RNDIS_Interface_Host,
	                              ConfigDescriptorSize, ConfigDescriptorData) != RNDIS_ENUMERROR_NoError)
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	if (USB_Host_SetDeviceConfiguration(1) != HOST_SENDCONTROL_Successful)
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	if (RNDIS_Host_InitializeDevice(&Ethernet_RNDIS_Interface_Host) != HOST_SENDCONTROL_Successful)
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		USB_Host_SetDeviceConfiguration(0);
		return;
	}

	uint32_t PacketFilter = (REMOTE_NDIS_PACKET_DIRECTED | REMOTE_NDIS_PACKET_BROADCAST);
	if (RNDIS_Host_SetRNDISProperty(&Ethernet_RNDIS_Interface_Host, OID_GEN_CURRENT_PACKET_FILTER,
	                                &PacketFilter, sizeof(PacketFilter)) != HOST_SENDCONTROL_Successful)
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		USB_Host_SetDeviceConfiguration(0);
		return;
	}

	if (RNDIS_Host_QueryRNDISProperty(&Ethernet_RNDIS_Interface_Host, OID_802_3_CURRENT_ADDRESS,
	                                  &MACAddress, sizeof(MACAddress)) != HOST_SENDCONTROL_Successful)
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		USB_Host_SetDeviceConfiguration(0);
		return;
	}

	/* Initialize uIP stack */
	uIPManagement_Init();

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
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

