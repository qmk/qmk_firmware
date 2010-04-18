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

#ifndef _SIDESHOW_CONTENT_H_
#define _SIDESHOW_CONTENT_H_

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		#include <string.h>
		#include <stdio.h>

		#include "SideshowCommon.h"
		#include "SideshowApplications.h"
	
	/* Enums: */
		enum SideShow_ContentTypes_t
		{
			Content_Menu            = 0,
			Content_Content         = 1,
			Content_MenuItem        = 2,
			Content_Button          = 3,
			Content_Text            = 4,
			Content_EndOfContent    = 5
		};
		
		enum SideShow_ActionTypes_t
		{
			TODO
		};
		
		enum SideShow_AlignmentTypes_t
		{
			TODO2
		};
	
	/* Type Defines: */
		typedef struct
		{
			uint8_t ContentType;
			uint8_t ContentSize;	
		} SideShow_Content_Header_t;
	
		typedef struct
		{
			SideShow_Content_Header_t Header;

			uint32_t ItemID;
			uint8_t  ActionType;
			char     Title[];
		} SideShow_Content_Menu_t;

		typedef struct
		{
			SideShow_Content_Header_t Header;

			uint32_t ItemID;
			uint32_t Target;
			bool     IsSelected;
			char     Text[];
		} SideShow_Content_MenuItem_t;
		
		typedef struct
		{
			SideShow_Content_Header_t Header;

			uint8_t  Key;
			uint32_t Target;
		} SideShow_Content_Button_t;
		
		typedef struct
		{
			SideShow_Content_Header_t Header;

			uint32_t ItemID;
			uint32_t AssociatedMenuID;
			char     Title[];
		} SideShow_Content_Content_t;

		typedef struct
		{
			SideShow_Content_Header_t Header;

			char     Text[];		
		} SideShow_Content_Text_t;
		
	/* Defines: */
		#define XML_START_TAG         "<body>"
		#define XML_END_TAG           "</body>"
	
	/* Function Prototypes: */
		bool SideShow_AddSimpleContent(SideShow_PacketHeader_t* const PacketHeader, SideShow_Application_t* const Application);

		#if defined(INCLUDE_FROM_SIDESHOWCONTENT_C)
			static void SideShow_ProcessXMLContent(void* ContentData, uint32_t ContentSize);
		#endif
		
#endif