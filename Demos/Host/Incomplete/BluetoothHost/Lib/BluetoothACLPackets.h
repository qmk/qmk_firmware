/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for BluetoothACLPackets.c.
 */

#ifndef _BLUETOOTH_ACLPACKETS_
#define _BLUETOOTH_ACLPACKETS_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>
		#include <stdbool.h>
		#include <stdio.h>

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Peripheral/Serial.h>

		#include "BluetoothStack.h"

	/* Macros: */
		#define BT_ACL_DEBUG(l, s, ...)           do { if (ACL_DEBUG_LEVEL >= l) printf_P(PSTR("(ACL) " s "\r\n"), ##__VA_ARGS__); } while (0)
		#define ACL_DEBUG_LEVEL                   0

		/** Lowest possible channel number for L2CAP data channels. */
		#define BT_CHANNELNUMBER_BASEOFFSET       0x0040

		/** Bluetooth specification defined channel number for signaling commands. */
		#define BT_CHANNEL_SIGNALING              0x0001

		/** Bluetooth specification defined channel number for connectionless data. */
		#define BT_CHANNEL_CONNECTIONLESS         0x0002

		#define BT_ACL_FIRST_AUTOFLUSH            (1 << 13)

		#define BT_SIGNAL_COMMAND_REJECT          0x01
		#define BT_SIGNAL_CONNECTION_REQUEST      0x02
		#define BT_SIGNAL_CONNECTION_RESPONSE     0x03
		#define BT_SIGNAL_CONFIGURATION_REQUEST   0x04
		#define BT_SIGNAL_CONFIGURATION_RESPONSE  0x05
		#define BT_SIGNAL_DISCONNECTION_REQUEST   0x06
		#define BT_SIGNAL_DISCONNECTION_RESPONSE  0x07
		#define BT_SIGNAL_ECHO_REQUEST            0x08
		#define BT_SIGNAL_ECHO_RESPONSE           0x09
		#define BT_SIGNAL_INFORMATION_REQUEST     0x0A
		#define BT_SIGNAL_INFORMATION_RESPONSE    0x0B

		#define BT_INFOREQ_MTU                    0x0001
		#define BT_INFOREQ_EXTENDEDFEATURES       0x0002

		#define BT_INFORMATION_SUCCESSFUL         0x0000
		#define BT_INFORMATION_NOTSUPPORTED       0x0001

		#define BT_CONNECTION_SUCCESSFUL          0x0000
		#define BT_CONNECTION_REFUSED_PSM         0x0002
		#define BT_CONNECTION_REFUSED_RESOURCES   0x0004

		#define BT_CONFIGURATION_SUCCESSFUL       0x0000
		#define BT_CONFIGURATION_REJECTED         0x0002
		#define BT_CONFIGURATION_UNKNOWNOPTIONS   0x0003

		#define BT_CONFIG_OPTION_MTU              1

	/* Type Defines: */
		/** Bluetooth ACL header structure, common to all ACL data packets. */
		typedef struct
		{
			uint16_t ConnectionHandle; /**< Unique device connection handle of the ACL packet */
			uint16_t DataLength; /**< Length of the packet payload, in bytes */
		} BT_ACL_Header_t;

		/** Bluetooth ACL data packet header structure, for ACL packets containing L2CAP data. */
		typedef struct
		{
			uint16_t PayloadLength; /**< Size of the data payload, in bytes */
			uint16_t DestinationChannel; /**< Destination channel in the device the data is directed to */
		} BT_DataPacket_Header_t;

		/** Bluetooth signaling command header structure, for all ACL packets containing a signaling command. */
		typedef struct
		{
			uint8_t  Code; /**< Signal code, a BT_SIGNAL_* mask value */
			uint8_t  Identifier; /**< Unique signal command identifier to link requests and responses */
			uint16_t Length; /**< Length of the signaling command data, in bytes */
		} BT_Signal_Header_t;

		/** Connection Request signaling command structure, for channel connection requests. */
		typedef struct
		{
			uint16_t PSM; /**< Type of data the channel will carry, a CHANNEL_PSM_* mask value */
			uint16_t SourceChannel; /**< Channel source on the sending device this channel will link to */
		} BT_Signal_ConnectionReq_t;

		/** Connection response signaling command structure, for responses to channel connection requests. */
		typedef struct
		{
			uint16_t DestinationChannel; /**< Destination device channel that the connection request was processed on */
			uint16_t SourceChannel; /**< Source device channel address that the connection request came from */
			uint16_t Result; /**< Connection result, a BT_CONNECTION_* mask value */
			uint16_t Status; /**< Status of the request if the result was set to the Pending value */
		} BT_Signal_ConnectionResp_t;

		/** Disconnection request signaling command structure, for channel disconnection requests. */
		typedef struct
		{
			uint16_t DestinationChannel; /**< Destination channel address which is to be disconnected */
			uint16_t SourceChannel; /**< Source channel address which is to be disconnected */
		} BT_Signal_DisconnectionReq_t;

		/** Disconnection response signaling command structure, for responses to channel disconnection requests. */
		typedef struct
		{
			uint16_t DestinationChannel; /**< Destination channel address which was disconnected */
			uint16_t SourceChannel; /**< Source channel address which was disconnected */
		} BT_Signal_DisconnectionResp_t;

		/** Configuration Request signaling command structure, for channel configuration requests. */
		typedef struct
		{
			uint16_t DestinationChannel; /**< Destination channel address which is to be disconnected */
			uint16_t Flags; /**< Configuration flags for the request, including command continuation */
		} BT_Signal_ConfigurationReq_t;

		/** Configuration Response signaling command structure, for responses to channel configuration requests. */
		typedef struct
		{
			uint16_t SourceChannel; /**< Source channel that the configuration request was directed at */
			uint16_t Flags; /**< Configuration flags for the response, including response continuation */
			uint16_t Result; /**< Configuration result, a BT_CONFIGURATION_* mask value */
		} BT_Signal_ConfigurationResp_t;

		/** Information Request signaling command structure, for device information requests. */
		typedef struct
		{
			uint16_t InfoType; /**< Data type that is being requested, a BT_INFOREQ_* mask value */
		} BT_Signal_InformationReq_t;

		/** Information Response signaling command structure, for responses to information requests. */
		typedef struct
		{
			uint16_t InfoType; /**< Data type that was requested, a BT_INFOREQ_* mask value */
			uint16_t Result; /**< Result of the request, a BT_INFORMATION_* mask value */
		} BT_Signal_InformationResp_t;

		/** Configuration Option header structure, placed at the start of each option in a Channel Configuration
		 *  request's options list.
		 */
		typedef struct
		{
			uint8_t Type; /**< Option type, a BT_CONFIG_OPTION_* mask value */
			uint8_t Length; /**< Length of the option's value, in bytes */
		} BT_Config_Option_Header_t;

	/* Function Prototypes: */
		void Bluetooth_ACLTask(void);

		#if defined(INCLUDE_FROM_BLUETOOTH_ACLPACKETS_C)
			static void Bluetooth_ProcessIncomingACLPackets(void);

			static inline void Bluetooth_Signal_ConnectionReq(const BT_Signal_Header_t* const SignalCommandHeader);
			static inline void Bluetooth_Signal_ConnectionResp(const BT_Signal_Header_t* const SignalCommandHeader);
			static inline void Bluetooth_Signal_ConfigurationReq(const BT_Signal_Header_t* const SignalCommandHeader);
			static inline void Bluetooth_Signal_ConfigurationResp(const BT_Signal_Header_t* const SignalCommandHeader);
			static inline void Bluetooth_Signal_DisconnectionReq(const BT_Signal_Header_t* const SignalCommandHeader);
			static inline void Bluetooth_Signal_DisconnectionResp(const BT_Signal_Header_t* const SignalCommandHeader);
			static inline void Bluetooth_Signal_EchoReq(const BT_Signal_Header_t* const SignalCommandHeader);
			static inline void Bluetooth_Signal_InformationReq(const BT_Signal_Header_t* const SignalCommandHeader);
		#endif

#endif

