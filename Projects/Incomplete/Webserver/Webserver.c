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
 *  Main source file for the Webserver project. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
 
#include "Webserver.h"

/** LUFA RNDIS Class driver interface configuration and state information. This structure is
 *  passed to all RNDIS Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_RNDIS_Host_t Ethernet_RNDIS_Interface =
	{
		.Config =
			{
				.DataINPipeNumber           = 1,
				.DataINPipeDoubleBank       = false,

				.DataOUTPipeNumber          = 2,
				.DataOUTPipeDoubleBank      = false,

				.NotificationPipeNumber     = 3,
				.NotificationPipeDoubleBank = false,
				
				.HostMaxPacketSize          = UIP_CONF_BUFFER_SIZE,
			},
	};

volatile uint8_t uIPManagementTimeout;

/** ISR for the management of the connection management timeout counter */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	if (uIPManagementTimeout)
	  uIPManagementTimeout--;
}

void TCPCallback(void)
{
	printf("Callback!\r\n");
}
	
/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "RNDIS Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		switch (USB_HostState)
		{
			case HOST_STATE_Addressed:
				LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
			
				uint16_t ConfigDescriptorSize;
				uint8_t  ConfigDescriptorData[512];

				if (USB_Host_GetDeviceConfigDescriptor(1, &ConfigDescriptorSize, ConfigDescriptorData,
				                                       sizeof(ConfigDescriptorData)) != HOST_GETCONFIG_Successful)
				{
					printf("Error Retrieving Configuration Descriptor.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}

				if (RNDIS_Host_ConfigurePipes(&Ethernet_RNDIS_Interface,
				                              ConfigDescriptorSize, ConfigDescriptorData) != RNDIS_ENUMERROR_NoError)
				{
					printf("Attached Device Not a Valid RNDIS Class Device.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}
				
				if (USB_Host_SetDeviceConfiguration(1) != HOST_SENDCONTROL_Successful)
				{
					printf("Error Setting Device Configuration.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}
				
				if (RNDIS_Host_InitializeDevice(&Ethernet_RNDIS_Interface) != HOST_SENDCONTROL_Successful)
				{
					printf("Error Initializing Device.\r\n");

					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;			
				}
				
				printf("Device Max Transfer Size: %lu bytes.\r\n", Ethernet_RNDIS_Interface.State.DeviceMaxPacketSize);
				
				uint32_t PacketFilter = (REMOTE_NDIS_PACKET_DIRECTED | REMOTE_NDIS_PACKET_BROADCAST | REMOTE_NDIS_PACKET_ALL_MULTICAST);
				if (RNDIS_Host_SetRNDISProperty(&Ethernet_RNDIS_Interface, OID_GEN_CURRENT_PACKET_FILTER,
				                                &PacketFilter, sizeof(PacketFilter)) != HOST_SENDCONTROL_Successful)
				{
					printf("Error Setting Device Packet Filter.\r\n");

					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}
				
				struct uip_eth_addr MACAddress;
				if (RNDIS_Host_QueryRNDISProperty(&Ethernet_RNDIS_Interface, OID_802_3_CURRENT_ADDRESS,
				                                  &MACAddress, sizeof(MACAddress)) != HOST_SENDCONTROL_Successful)
				{
					printf("Error Getting MAC Address.\r\n");

					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}

				printf("MAC Address: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n",
				        MACAddress.addr[0], MACAddress.addr[1], MACAddress.addr[2],
				        MACAddress.addr[3], MACAddress.addr[4], MACAddress.addr[5]);

				uip_setethaddr(MACAddress);
				
				printf("RNDIS Device Enumerated.\r\n");
				USB_HostState = HOST_STATE_Configured;
				break;
			case HOST_STATE_Configured:
				ProcessIncommingPacket();
				ManageConnections();
			
				break;
		}
	
		RNDIS_Host_USBTask(&Ethernet_RNDIS_Interface);
		USB_USBTask();
	}
}

void ProcessIncommingPacket(void)
{
	if (RNDIS_Host_IsPacketReceived(&Ethernet_RNDIS_Interface))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

		/* Read the incomming packet straight into the UIP packet buffer */
		RNDIS_Host_ReadPacket(&Ethernet_RNDIS_Interface, &uip_buf, &uip_len);
		
		printf("RECEIVED PACKET (%d):\r\n", uip_len);
		for (uint16_t i = 0; i < uip_len; i++)
		  printf("0x%02X ", uip_buf[i]);
		printf("\r\n\r\n");

		#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

		if (BUF->type == HTONS(UIP_ETHTYPE_IP))
		{
			/* Filter packet by MAC destination */
			uip_arp_ipin();

			/* Process incomming packet */
			uip_input();

			/* Add destination MAC to outgoing packet */
			if (uip_len > 0)
			  uip_arp_out();
		}
		else if (BUF->type == HTONS(UIP_ETHTYPE_ARP))
		{
			/* Process ARP packet */
			uip_arp_arpin();
		}

		/* If a response was generated, send it */
		if (uip_len > 0)
		  RNDIS_Host_SendPacket(&Ethernet_RNDIS_Interface, &uip_buf, uip_len);

		printf("SENT PACKET (%d):\r\n", uip_len);
		for (uint16_t i = 0; i < uip_len; i++)
		  printf("0x%02X ", uip_buf[i]);
		printf("\r\n\r\n");

		LEDs_SetAllLEDs(LEDMASK_USB_READY);
	}
}

void ManageConnections(void)
{
	if (!(uIPManagementTimeout))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
		
		for (uint8_t i = 0; i < UIP_CONNS; i++)
		{
			/* Run periodic connection management for each connection */
			uip_periodic(i);

			/* If a response was generated, send it */
			if (uip_len > 0)
			  RNDIS_Host_SendPacket(&Ethernet_RNDIS_Interface, &uip_buf, uip_len);
		}
		
		uip_arp_timer();
		
		uIPManagementTimeout = 250;

		LEDs_SetAllLEDs(LEDMASK_USB_READY);
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
	SerialStream_Init(9600, false);
	LEDs_Init();
	USB_Init();

	/* Millisecond timer initialization for managing the command timeout counter */
	OCR0A  = ((F_CPU / 64) / 1000);
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
	
	/* uIP Stack Initialization */
	uip_init();

	uip_ipaddr_t IPAddress, Netmask, GatewayIPAddress;
	uip_ipaddr(&IPAddress, 192, 168, 1, 10);
	uip_ipaddr(&Netmask, 0xFF, 0xFF, 0xFF, 0x00);
	uip_ipaddr(&GatewayIPAddress, 192, 168, 1, 1);
	uip_sethostaddr(&IPAddress);
	uip_setnetmask(&Netmask);
	uip_setdraddr(&GatewayIPAddress);
	
	/* HTTP Webserver Initialization */
	uip_listen(HTONS(80));
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Host_DeviceAttached(void)
{
	puts_P(PSTR("Device Attached.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_Host_DeviceUnattached(void)
{
	puts_P(PSTR("\r\nDevice Unattached.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_Host_DeviceEnumerationComplete(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_Host_HostError(const uint8_t ErrorCode)
{
	USB_ShutDown();

	printf_P(PSTR(ESC_FG_RED "Host Mode Error\r\n"
	                         " -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	printf_P(PSTR(ESC_FG_RED "Dev Enum Error\r\n"
	                         " -- Error Code %d\r\n"
	                         " -- Sub Error Code %d\r\n"
	                         " -- In State %d\r\n" ESC_FG_WHITE), ErrorCode, SubErrorCode, USB_HostState);
	
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}
