/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief LUFA Library Configuration Header File (Template)
 *
 *  This is a header file which can be used to configure LUFA's
 *  compile time options, as an alternative to the compile time
 *  constants supplied through a makefile. To use this configuration
 *  header, copy this into your project's root directory and supply
 *  the \c USE_LUFA_CONFIG_HEADER token to the compiler so that it is
 *  defined in all compiled source files.
 *
 *  For information on what each token does, refer to the LUFA
 *  manual section "Summary of Compile Tokens".
 */

#ifndef __LUFA_CONFIG_H__
#define __LUFA_CONFIG_H__

	#if (ARCH == ARCH_AVR8)

		/* Non-USB Related Configuration Tokens: */
//		#define DISABLE_TERMINAL_CODES

		/* USB Class Driver Related Tokens: */
//		#define HID_HOST_BOOT_PROTOCOL_ONLY
//		#define HID_STATETABLE_STACK_DEPTH       {Insert Value Here}
//		#define HID_USAGE_STACK_DEPTH            {Insert Value Here}
//		#define HID_MAX_COLLECTIONS              {Insert Value Here}
//		#define HID_MAX_REPORTITEMS              {Insert Value Here}
//		#define HID_MAX_REPORT_IDS               {Insert Value Here}
//		#define NO_CLASS_DRIVER_AUTOFLUSH

		/* General USB Driver Related Tokens: */
//		#define ORDERED_EP_CONFIG
//		#define USE_STATIC_OPTIONS               {Insert Value Here}
//		#define USB_DEVICE_ONLY
//		#define USB_HOST_ONLY
//		#define USB_STREAM_TIMEOUT_MS            {Insert Value Here}
//		#define NO_LIMITED_CONTROLLER_CONNECT
//		#define NO_SOF_EVENTS

		/* USB Device Mode Driver Related Tokens: */
//		#define USE_RAM_DESCRIPTORS
//		#define USE_FLASH_DESCRIPTORS
//		#define USE_EEPROM_DESCRIPTORS
//		#define NO_INTERNAL_SERIAL
//		#define FIXED_CONTROL_ENDPOINT_SIZE      {Insert Value Here}
//		#define DEVICE_STATE_AS_GPIOR            {Insert Value Here}
//		#define FIXED_NUM_CONFIGURATIONS         {Insert Value Here}
//		#define CONTROL_ONLY_DEVICE
//		#define INTERRUPT_CONTROL_ENDPOINT
//		#define NO_DEVICE_REMOTE_WAKEUP
//		#define NO_DEVICE_SELF_POWER

		/* USB Host Mode Driver Related Tokens: */
//		#define HOST_STATE_AS_GPIOR              {Insert Value Here}
//		#define USB_HOST_TIMEOUT_MS              {Insert Value Here}
//		#define HOST_DEVICE_SETTLE_DELAY_MS	     {Insert Value Here}
//      #define NO_AUTO_VBUS_MANAGEMENT
//      #define INVERTED_VBUS_ENABLE_LINE

	#elif (ARCH == ARCH_XMEGA)

		/* Non-USB Related Configuration Tokens: */
//		#define DISABLE_TERMINAL_CODES

		/* USB Class Driver Related Tokens: */
//		#define HID_HOST_BOOT_PROTOCOL_ONLY
//		#define HID_STATETABLE_STACK_DEPTH       {Insert Value Here}
//		#define HID_USAGE_STACK_DEPTH            {Insert Value Here}
//		#define HID_MAX_COLLECTIONS              {Insert Value Here}
//		#define HID_MAX_REPORTITEMS              {Insert Value Here}
//		#define HID_MAX_REPORT_IDS               {Insert Value Here}
//		#define NO_CLASS_DRIVER_AUTOFLUSH

		/* General USB Driver Related Tokens: */
//		#define USE_STATIC_OPTIONS               {Insert Value Here}
//		#define USB_STREAM_TIMEOUT_MS            {Insert Value Here}
//		#define NO_LIMITED_CONTROLLER_CONNECT
//		#define NO_SOF_EVENTS

		/* USB Device Mode Driver Related Tokens: */
//		#define USE_RAM_DESCRIPTORS
//		#define USE_FLASH_DESCRIPTORS
//		#define USE_EEPROM_DESCRIPTORS
//		#define NO_INTERNAL_SERIAL
//		#define FIXED_CONTROL_ENDPOINT_SIZE      {Insert Value Here}
//		#define DEVICE_STATE_AS_GPIOR            {Insert Value Here}
//		#define FIXED_NUM_CONFIGURATIONS         {Insert Value Here}
//		#define CONTROL_ONLY_DEVICE
// 		#define MAX_ENDPOINT_INDEX               {Insert Value Here}
//		#define NO_DEVICE_REMOTE_WAKEUP
//		#define NO_DEVICE_SELF_POWER

	#elif (ARCH == ARCH_UC3)

		/* Non-USB Related Configuration Tokens: */
//		#define DISABLE_TERMINAL_CODES

		/* USB Class Driver Related Tokens: */
//		#define HID_HOST_BOOT_PROTOCOL_ONLY
//		#define HID_STATETABLE_STACK_DEPTH       {Insert Value Here}
//		#define HID_USAGE_STACK_DEPTH            {Insert Value Here}
//		#define HID_MAX_COLLECTIONS              {Insert Value Here}
//		#define HID_MAX_REPORTITEMS              {Insert Value Here}
//		#define HID_MAX_REPORT_IDS               {Insert Value Here}
//		#define NO_CLASS_DRIVER_AUTOFLUSH

		/* General USB Driver Related Tokens: */
//		#define ORDERED_EP_CONFIG
//		#define USE_STATIC_OPTIONS               {Insert Value Here}
//		#define USB_DEVICE_ONLY
//		#define USB_HOST_ONLY
//		#define USB_STREAM_TIMEOUT_MS            {Insert Value Here}
//		#define NO_SOF_EVENTS

		/* USB Device Mode Driver Related Tokens: */
//		#define NO_INTERNAL_SERIAL
//		#define FIXED_CONTROL_ENDPOINT_SIZE      {Insert Value Here}
//		#define FIXED_NUM_CONFIGURATIONS         {Insert Value Here}
//		#define CONTROL_ONLY_DEVICE
//		#define INTERRUPT_CONTROL_ENDPOINT
//		#define NO_DEVICE_REMOTE_WAKEUP
//		#define NO_DEVICE_SELF_POWER

		/* USB Host Mode Driver Related Tokens: */
//		#define USB_HOST_TIMEOUT_MS              {Insert Value Here}
//		#define HOST_DEVICE_SETTLE_DELAY_MS	     {Insert Value Here}
//      #define NO_AUTO_VBUS_MANAGEMENT
//      #define INVERTED_VBUS_ENABLE_LINE

	#else

		#error Unsupported architecture for this LUFA configuration file.

	#endif
#endif

