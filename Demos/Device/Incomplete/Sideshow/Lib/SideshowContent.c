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

#define  INCLUDE_FROM_SIDESHOWCONTENT_C
#include "SideshowContent.h"

bool SideShow_AddSimpleContent(SideShow_PacketHeader_t* const PacketHeader, SideShow_Application_t* const Application)
{
	uint32_t ContentSize;
	uint32_t ContentID;
		
	Endpoint_Read_Stream_LE(&ContentID, sizeof(uint32_t));

	PacketHeader->Length -= sizeof(uint32_t);

	if (Application->CurrentContentID != ContentID)
	{
		Endpoint_Discard_Stream(PacketHeader->Length);

		return false;
	}
	
	Endpoint_Read_Stream_LE(&ContentSize, sizeof(uint32_t));
	Endpoint_Read_Stream_LE(&Application->CurrentContent, sizeof(XML_START_TAG) - 1);
	
	PacketHeader->Length -= sizeof(uint32_t) + (sizeof(XML_START_TAG) - 1);

	if (!(memcmp(&Application->CurrentContent, XML_START_TAG, (sizeof(XML_START_TAG) - 1))))
	{
		SideShow_ProcessXMLContent(&Application->CurrentContent, (ContentSize - (sizeof(XML_END_TAG) - 1)));
		
		Endpoint_Discard_Stream(sizeof(XML_END_TAG) - 1);

		Application->HaveContent = true;
	}
	else
	{
		printf(" BINARY");
		Endpoint_Discard_Stream(ContentSize);
	}
	
	return true;
}

static void SideShow_ProcessXMLContent(void* ContentData, uint32_t ContentSize)
{
	printf(" XML");
	Endpoint_Discard_Stream(ContentSize);
}
