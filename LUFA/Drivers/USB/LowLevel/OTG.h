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
 *  Macros for embedded USB hosts with dual role On The Go capabilities, for managing role exchange. OTG
 *  is a way for two USB dual role devices to talk to one another directly without fixed device/host roles.
 *
 *  \note These macros are only for AVRs which support the OTG protocol, and do not exist for device-only AVRs.
 */

#ifndef __USBOTG_H__
#define __USBOTG_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		
		#include "../../../Common/Common.h"

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Initiate a Host Negotiation Protocol request. This indicates to the other connected device
			 *  that the device wishes to change device/host roles.
			 */
			#define USB_OTG_DEV_Request_HNP()          MACROS{ OTGCON |=  (1 << HNPREQ); }MACROE

			/** Cancel a Host Negotiation Protocol request. This stops a pending HNP request to the other
			 *  connected device.
			 */
			#define USB_OTG_DEV_Cancel_HNP_Request()   MACROS{ OTGCON &= ~(1 << HNPREQ); }MACROE

			/** Returns boolean false if not currently sending a HNP to the other connected device, or true
			 *  if a HNP is currently being issued.
			 */
			#define USB_OTG_DEV_IsSendingHNP()               ((OTGCON &   (1 << HNPREQ)) ? true : false)
			
			/** Accepts a HNP from a connected device, indicating that both devices should exchange
			 *  device/host roles.
			 */
			#define USB_OTG_HOST_Accept_HNP()          USB_OTG_DEV_Request_HNP()

			/** Rejects a HNP from a connected device, indicating that both devices should remain in their
			 *  current device/host roles.
			 */
			#define USB_OTG_HOST_Reject_HNP()          USB_OTG_DEV_Cancel_HNP_Request()
			
			/** Returns boolean false if the connected device is not currently sending a HNP request, or true
			 *  if a HNP is currently being issued by the connected device.
			 */
			#define USB_OTG_HOST_IsHNPReceived()             ((OTGCON &   (1 << HNPREQ)) ? true : false)
			
			/** Initiates a Session Request Protocol request. Most OTG devices turn off VBUS when the USB
			 *  interface is not in use, to conserve power. Sending a SRP to a USB OTG device running in
			 *  host mode indicates that VBUS should be applied and a session started.
			 *
			 *  There are two different methods of sending a SRP - either pulses on the VBUS line, or by
			 *  pulsing the Data + line via the internal pullup resistor. The SRP mode is given as the
			 *  "type" parameter, and can be either USB_OTG_SRP_VBUS or USB_OTG_STP_DATA.
			 */
			#define USB_OTG_DEV_Initiate_SRP(type)     MACROS{ OTGCON = ((OTGCON & ~(1 << SRPSEL)) | (type | (1 << SRPREQ))); }MACROE

			/** Mask for the VBUS pulsing method of SRP, supported by some OTG devices.
			 *
			 *  \see USB_OTG_DEV_Initiate_SRP()
			 */			 
			#define USB_OTG_SRP_VBUS                   (1 << SRPSEL)

			/** Mask for the Data + pulsing method of SRP, supported by some OTG devices.
			 *
			 *  \see USB_OTG_DEV_Initiate_SRP()
			 */			 
			#define USB_OTG_STP_DATA                   0

#endif
