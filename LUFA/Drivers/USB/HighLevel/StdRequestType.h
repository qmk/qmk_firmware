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
 *  Contains definitions for the various control request parameters, so that the request details (such as data
 *  direction, request recipient, etc.) can be extracted via masking.
 */
 
/** \ingroup Group_USB
 *  @defgroup Group_StdRequest Standard USB Requests
 *
 *  Functions, macros, variables, enums and types related to standard USB requests to USB devices.
 *
 *  @{
 */

#ifndef __STDREQTYPE_H__
#define __STDREQTYPE_H__

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Mask for the request type parameter, to indicate the direction of the request data (Host to Device
			 *  or Device to Host). The result of this mask should then be compared to the request direction masks.
			 *
			 *  \see REQDIR_* macros for masks indicating the request data direction.
			 */
			#define CONTROL_REQTYPE_DIRECTION  0x80

			/** Mask for the request type parameter, to indicate the type of request (Device, Class or Vendor
			 *  Specific). The result of this mask should then be compared to the request type masks.
			 *
			 *  \see REQTYPE_* macros for masks indicating the request type.
			 */
			#define CONTROL_REQTYPE_TYPE       0x60

			/** Mask for the request type parameter, to indicate the recipient of the request (Standard, Class
			 *  or Vendor Specific). The result of this mask should then be compared to the request recipient
			 *  masks.
			 *
			 *  \see REQREC_* macros for masks indicating the request recipient.
			 */
			#define CONTROL_REQTYPE_RECIPIENT  0x1F

			/** Request data direction mask, indicating that the request data will flow from host to device.
			 *
			 *  \see CONTROL_REQTYPE_DIRECTION macro.
			 */
			#define REQDIR_HOSTTODEVICE        (0 << 7)

			/** Request data direction mask, indicating that the request data will flow from device to host.
			 *
			 *  \see CONTROL_REQTYPE_DIRECTION macro.
			 */
			#define REQDIR_DEVICETOHOST        (1 << 7)

			/** Request type mask, indicating that the request is a standard request.
			 *
			 *  \see CONTROL_REQTYPE_TYPE macro.
			 */
			#define REQTYPE_STANDARD           (0 << 5)

			/** Request type mask, indicating that the request is a class-specific request.
			 *
			 *  \see CONTROL_REQTYPE_TYPE macro.
			 */
			#define REQTYPE_CLASS              (1 << 5)

			/** Request type mask, indicating that the request is a vendor specific request.
			 *
			 *  \see CONTROL_REQTYPE_TYPE macro.
			 */
			#define REQTYPE_VENDOR             (2 << 5)

			/** Request recipient mask, indicating that the request is to be issued to the device as a whole.
			 *
			 *  \see CONTROL_REQTYPE_RECIPIENT macro.
			 */
			#define REQREC_DEVICE              (0 << 0)

			/** Request recipient mask, indicating that the request is to be issued to an interface in the
			 *  currently selected configuration.
			 *
			 *  \see CONTROL_REQTYPE_RECIPIENT macro.
			 */
			#define REQREC_INTERFACE           (1 << 0)

			/** Request recipient mask, indicating that the request is to be issued to an endpoint in the
			 *  currently selected configuration.
			 *
			 *  \see CONTROL_REQTYPE_RECIPIENT macro.
			 */
			#define REQREC_ENDPOINT            (2 << 0)

			/** Request recipient mask, indicating that the request is to be issued to an unspecified element
			 *  in the currently selected configuration.
			 *
			 *  \see CONTROL_REQTYPE_RECIPIENT macro.
			 */
			#define REQREC_OTHER               (3 << 0)
			
			/** Feature indicator for Clear Feature or Set Feature commands. When used in a Clear Feature
			 *  request this indicates that an endpoint (whose address is given elsewhere in the request
			 *  should have its stall condition cleared. If used in a similar manner inside a Set Feature
			 *  request, this stalls an endpoint.
			 */
			#define FEATURE_ENDPOINT_HALT           0x00

			/** Feature indicator for Clear Feature or Set Feature commands. When used in a Clear Feature
			 *  request this indicates that the remote wakeup enabled device should not issue remote
			 *  wakeup requests until further notice. If used in a similar manner inside a Set Feature
			 *  request, this re-enabled the remote wakeup feature on the device.
			 */
			#define FEATURE_REMOTE_WAKEUP           0x01

		/* Enums: */
			/** Enumeration for the various standard request commands. These commands are applicable when the
			 *  request type is REQTYPE_STANDARD (with the exception of REQ_GetDescriptor, which is always
			 *  handled regardless of the request type value).
			 *
			 *  \see Chapter 9 of the USB 2.0 Specification.
			 */
			enum USB_Control_Request_t
			{
				REQ_GetStatus           = 0, /**< Implemented in the library for device, endpoint and interface
				                              *   recipients. Passed to the user application for other recipients
				                              *   via the USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
				REQ_ClearFeature        = 1, /**< Implemented in the library for device, endpoint and interface
				                              *   recipients. Passed to the user application for other recipients
				                              *   via the USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
				REQ_SetFeature          = 3, /**< Implemented in the library for device, endpoint and interface
				                              *   recipients. Passed to the user application for other recipients
				                              *   via the USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
				REQ_SetAddress          = 5, /**< Implemented in the library for the device recipient. Passed
				                              *   to the user application for other recipients via the
				                              *   USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
				REQ_GetDescriptor       = 6, /**< Implemented in the library for all recipients and all request
				                              *   types. */
				REQ_SetDescriptor       = 7, /**< Not implemented in the library, passed to the user application
				                              *   via the USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
				REQ_GetConfiguration    = 8, /**< Implemented in the library for the device recipient. Passed
				                              *   to the user application for other recipients via the
				                              *   USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
				REQ_SetConfiguration    = 9, /**< Implemented in the library for the device recipient. Passed
				                              *   to the user application for other recipients via the
				                              *   USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
				REQ_GetInterface        = 10, /**< Not implemented in the library, passed to the user application
				                              *   via the USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
				REQ_SetInterface        = 11, /**< Not implemented in the library, passed to the user application
				                              *   via the USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
				REQ_SynchFrame          = 12, /**< Not implemented in the library, passed to the user application
				                              *   via the USB_UnhandledControlPacket() event when received in
				                              *   device mode. */
			};

	/* Private Interface - For use in library only: */
		#if !defined(__DOXYGEN__)
			/* Macros: */
				#define FEATURE_SELFPOWERED_ENABLED     (1 << 0)
				#define FEATURE_REMOTE_WAKEUP_ENABLED   (1 << 1)
		#endif

#endif

/** @} */
