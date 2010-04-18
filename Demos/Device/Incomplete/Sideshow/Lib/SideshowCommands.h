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

#ifndef _SIDESHOW_COMMANDS_H_
#define _SIDESHOW_COMMANDS_H_

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		#include <string.h>
	
		#include "Sideshow.h"
		#include "SideshowCommon.h"
		#include "SideshowApplications.h"
		#include "SideshowContent.h"

	/* Enumerations: */
		enum SideShow_PropertyKey_Types_t
		{
			VT_EMPTY             = 0,
			VT_NULL              = 1,
			VT_I2                = 2,
			VT_I4                = 3,
			VT_R4                = 4,
			VT_R8                = 5,
			VT_CY                = 6,
			VT_DATE              = 7,
			VT_BSTR              = 8,
			VT_DISPATCH          = 9,
			VT_ERROR             = 10,
			VT_BOOL              = 11,
			VT_VARIANT           = 12,
			VT_UNKNOWN           = 13,
			VT_UI1               = 17,
			VT_UI2               = 18,
			VT_UI4               = 19,
			VT_LPWSTR            = 31,
		};
		
		enum SideShow_ScreenTypeText_t
		{
			ScreenBitmap         = 0,
			ScreenText           = 1,
		};
		
		enum SideShow_ColorTypes_t
		{
			ColorDisplay         = 0,
			GrayscaleDisplay     = 1,
			BlackAndWhiteDisplay = 2, 		
		};

		enum SideShow_DeviceTypes_t
		{ 
			GenericDevice = 0, 
			CameraDevice = 1, 
			MediaPlayerDevice = 2, 
			PhoneDevice = 3,
			VideoDevice = 4,
			PIMDevice = 5,
			AudioRecorderDevice = 6
		};

	/* Type Defines: */
		typedef struct
		{
			GUID_t   PropertyGUID;
			uint32_t PropertyID;
		} SideShow_PropertyKey_t;
		
		typedef struct
		{
			uint32_t DataType;
			
			union
			{
				void*    DataPointer;
				uint8_t  Data8;
				uint16_t Data16;
				uint32_t Data32;
			} Data;
		} SideShow_PropertyData_t;
		
	/* Macros: */
		#define SIDESHOW_CMD_PING                     0x001
		#define SIDESHOW_CMD_SET_CURRENT_USER         0x100
		#define SIDESHOW_CMD_GET_CURRENT_USER         0x101
		#define SIDESHOW_CMD_GET_CAPABILITIES         0x103		
		#define SIDESHOW_CMD_GET_APPLICATION_ORDER    0x104
		#define SIDESHOW_CMD_ADD_APPLICATION          0x10D
		#define SIDESHOW_CMD_DELETE_APPLICATION       0x10E
		#define SIDESHOW_CMD_DELETE_ALL_APPLICATIONS  0x10F
		#define SIDESHOW_CMD_ADD_CONTENT              0x114
		#define SIDESHOW_CMD_DELETE_CONTENT           0x115
		#define SIDESHOW_CMD_DELETE_ALL_CONTENT       0x116
		#define SIDESHOW_CMD_GET_SUPPORTED_ENDPOINTS  0x117
		#define SIDESHOW_CMD_GET_DEVICE_NAME          0x500
		#define SIDESHOW_CMD_GET_MANUFACTURER         0x501
		#define SIDESHOW_CMD_SYNC                     0x502

		#define PROPERTY_SIDESHOW_DEVICEID            1
		#define PROPERTY_SIDESHOW_SCREENTYPE          2
		#define PROPERTY_SIDESHOW_SCREENWIDTH         3
		#define PROPERTY_SIDESHOW_SCREENHEIGHT        4
		#define PROPERTY_SIDESHOW_COLORDEPTH          5
		#define PROPERTY_SIDESHOW_COLORTYPE           6
		#define PROPERTY_SIDESHOW_DATACACHE           7
		#define PROPERTY_SIDESHOW_SUPPORTEDLANGS      8
		#define PROPERTY_SIDESHOW_CURRENTLANG         9
		#define PROPERTY_SIDESHOW_SUPPORTEDTHEMES     10
		#define PROPERTY_SIDESHOW_IMAGEFORMAT         14
		#define PROPERTY_SIDESHOW_CLIENTWIDTH         15
		#define PROPERTY_SIDESHOW_CLIENTHEIGHT        16
		#define PROPERTY_SIDESHOW_DEVICEICON          17
		
		#define PROPERTY_DEVICE_DEVICETYPE            15
				
	/* Function Prototypes: */
		void Sideshow_ProcessCommandPacket(void);
		
		#if defined(INCLUDE_FROM_SIDESHOWCOMMANDS_H)
			static void SideShow_Ping(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_Sync(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_GetCurrentUser(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_SetCurrentUser(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_GetCapabilities(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_GetString(SideShow_PacketHeader_t* const PacketHeader, void* const UnicodeStruct);
			static void SideShow_GetApplicationOrder(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_GetSupportedEndpoints(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_AddApplication(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_DeleteApplication(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_DeleteAllApplications(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_AddContent(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_DeleteContent(SideShow_PacketHeader_t* const PacketHeader);
			static void SideShow_DeleteAllContent(SideShow_PacketHeader_t* const PacketHeader);
		#endif

#endif
