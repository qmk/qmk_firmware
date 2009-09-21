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

#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_HOST)

#include "HIDParser.h"

uint8_t USB_ProcessHIDReport(const uint8_t* ReportData, uint16_t ReportSize, HID_ReportInfo_t* const ParserData)
{
	HID_StateTable_t      StateTable[HID_STATETABLE_STACK_DEPTH];
	HID_StateTable_t*     CurrStateTable          = &StateTable[0];
	HID_CollectionPath_t* CurrCollectionPath      = NULL;
	HID_ReportSizeInfo_t* CurrReportIDInfo        = &ParserData->ReportIDSizes[0];			
	uint16_t              UsageStack[HID_USAGE_STACK_DEPTH];
	uint8_t               UsageStackSize          = 0;

	ParserData->TotalReportItems   = 0;
	ParserData->TotalDeviceReports = 1;
	ParserData->UsingReportIDs     = false;
	
	for (uint8_t CurrCollection = 0; CurrCollection < HID_MAX_COLLECTIONS; CurrCollection++)
	  ParserData->CollectionPaths[CurrCollection].Parent = NULL;

	memset(CurrStateTable,   0x00, sizeof(HID_StateTable_t));
	memset(CurrReportIDInfo, 0x00, sizeof(HID_ReportSizeInfo_t));

	while (ReportSize)
	{
		uint8_t  HIDReportItem  = *ReportData;
		uint32_t ReportItemData = 0;
		
		ReportData++;
		ReportSize--;
		
		switch (HIDReportItem & DATA_SIZE_MASK)
		{
			case DATA_SIZE_4:
				ReportItemData  = *((uint32_t*)ReportData);
				ReportSize     -= 4;
				ReportData     += 4;
				break;
			case DATA_SIZE_2:
				ReportItemData  = *((uint16_t*)ReportData);
				ReportSize     -= 2;
				ReportData     += 2;
				break;
			case DATA_SIZE_1:
				ReportItemData  = *((uint8_t*)ReportData);
				ReportSize     -= 1;
				ReportData     += 1;
				break;
		}

		switch (HIDReportItem & (TYPE_MASK | TAG_MASK))
		{
			case (TYPE_GLOBAL | TAG_GLOBAL_PUSH):
				if (CurrStateTable == &StateTable[HID_STATETABLE_STACK_DEPTH - 1])
				  return HID_PARSE_HIDStackOverflow;
	
				memcpy((CurrStateTable + 1),
				       CurrStateTable,
				       sizeof(HID_ReportItem_t));

				CurrStateTable++;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_POP):
				if (CurrStateTable == &StateTable[0])
				  return HID_PARSE_HIDStackUnderflow;
				  
				CurrStateTable--;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_USAGEPAGE):
				CurrStateTable->Attributes.Usage.Page       = ReportItemData;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_LOGICALMIN):
				CurrStateTable->Attributes.Logical.Minimum  = ReportItemData;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_LOGICALMAX):
				CurrStateTable->Attributes.Logical.Maximum  = ReportItemData;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_PHYSMIN):
				CurrStateTable->Attributes.Physical.Minimum = ReportItemData;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_PHYSMAX):
				CurrStateTable->Attributes.Physical.Maximum = ReportItemData;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_UNITEXP):
				CurrStateTable->Attributes.Unit.Exponent    = ReportItemData;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_UNIT):
				CurrStateTable->Attributes.Unit.Type        = ReportItemData;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_REPORTSIZE):
				CurrStateTable->Attributes.BitSize          = ReportItemData;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_REPORTCOUNT):
				CurrStateTable->ReportCount                 = ReportItemData;
				break;
			case (TYPE_GLOBAL | TAG_GLOBAL_REPORTID):
				CurrStateTable->ReportID                    = ReportItemData;

				if (ParserData->UsingReportIDs)
				{
					CurrReportIDInfo = NULL;

					for (uint8_t i = 0; i < ParserData->TotalDeviceReports; i++)
					{
						if (ParserData->ReportIDSizes[i].ReportID == CurrStateTable->ReportID)
						{
							CurrReportIDInfo = &ParserData->ReportIDSizes[i];
							break;
						}
					}
					
					if (CurrReportIDInfo == NULL)
					{
						if (ParserData->TotalDeviceReports++ > HID_MAX_REPORT_IDS)
						  return HID_PARSE_InsufficientReportIDItems;
					
						CurrReportIDInfo = &ParserData->ReportIDSizes[ParserData->TotalDeviceReports - 1];
						memset(CurrReportIDInfo, 0x00, sizeof(HID_ReportSizeInfo_t));
					}
				}

				ParserData->UsingReportIDs = true;				

				CurrReportIDInfo->ReportID     = CurrStateTable->ReportID;
				break;
			case (TYPE_LOCAL | TAG_LOCAL_USAGE):
				if (UsageStackSize == HID_USAGE_STACK_DEPTH)
				  return HID_PARSE_UsageStackOverflow;
			
				UsageStack[UsageStackSize++] = ReportItemData;
				break;
			case (TYPE_LOCAL | TAG_LOCAL_USAGEMIN):
				CurrStateTable->Attributes.Usage.MinMax.Minimum = ReportItemData;
				break;
			case (TYPE_LOCAL | TAG_LOCAL_USAGEMAX):
				CurrStateTable->Attributes.Usage.MinMax.Maximum = ReportItemData;
				break;
			case (TYPE_MAIN | TAG_MAIN_COLLECTION):
				if (CurrCollectionPath == NULL)
				{
					CurrCollectionPath = &ParserData->CollectionPaths[0];
				}
				else
				{
					HID_CollectionPath_t* ParentCollectionPath = CurrCollectionPath;
			
					CurrCollectionPath = &ParserData->CollectionPaths[1];

					while (CurrCollectionPath->Parent != NULL);
					{
						if (CurrCollectionPath == &ParserData->CollectionPaths[HID_MAX_COLLECTIONS - 1])
						  return HID_PARSE_InsufficientCollectionPaths;
					
						CurrCollectionPath++;
					}

					CurrCollectionPath->Parent = ParentCollectionPath;
				}
				
				CurrCollectionPath->Type = ReportItemData;
				CurrCollectionPath->Usage.Page = CurrStateTable->Attributes.Usage.Page;
				
				if (UsageStackSize)
				{
					CurrCollectionPath->Usage.Usage = UsageStack[0];

					for (uint8_t i = 0; i < UsageStackSize; i++)
					  UsageStack[i] = UsageStack[i + 1];
					  
					UsageStackSize--;
				}
				else
				{
					CurrCollectionPath->Usage.Usage = 0;
				}
				
				break;
			case (TYPE_MAIN | TAG_MAIN_ENDCOLLECTION):
				if (CurrCollectionPath == NULL)
				  return HID_PARSE_UnexpectedEndCollection;
		
				CurrCollectionPath = CurrCollectionPath->Parent;

				break;
			case (TYPE_MAIN | TAG_MAIN_INPUT):
			case (TYPE_MAIN | TAG_MAIN_OUTPUT):
			case (TYPE_MAIN | TAG_MAIN_FEATURE):
				for (uint8_t ReportItemNum = 0; ReportItemNum < CurrStateTable->ReportCount; ReportItemNum++)
				{
					HID_ReportItem_t NewReportItem;
				  
					memcpy(&NewReportItem.Attributes,
					       &CurrStateTable->Attributes,
					       sizeof(HID_ReportItem_Attributes_t));

					NewReportItem.ItemFlags      = ReportItemData;
					NewReportItem.CollectionPath = CurrCollectionPath;
					NewReportItem.ReportID       = CurrStateTable->ReportID;

					if (UsageStackSize)
					{
						NewReportItem.Attributes.Usage.Usage = UsageStack[0];

						for (uint8_t i = 0; i < UsageStackSize; i++)
						  UsageStack[i] = UsageStack[i + 1];
						  
						UsageStackSize--;
					}
					else
					{
						NewReportItem.Attributes.Usage.Usage = 0;
					}

					uint8_t ReportSizeIndex = 0;

					switch (HIDReportItem & TAG_MASK)
					{
						case TAG_MAIN_INPUT:
							NewReportItem.ItemType  = REPORT_ITEM_TYPE_In;
							NewReportItem.BitOffset = CurrReportIDInfo->ReportSizeBits[REPORT_ITEM_TYPE_In];
								
							ReportSizeIndex = REPORT_ITEM_TYPE_In;
							break;
						case TAG_MAIN_OUTPUT:
							NewReportItem.ItemType  = REPORT_ITEM_TYPE_Out;
							NewReportItem.BitOffset = CurrReportIDInfo->ReportSizeBits[REPORT_ITEM_TYPE_Out];
								
							ReportSizeIndex = REPORT_ITEM_TYPE_Out;
							break;
						case TAG_MAIN_FEATURE:
							NewReportItem.ItemType  = REPORT_ITEM_TYPE_Feature;						
							NewReportItem.BitOffset = CurrReportIDInfo->ReportSizeBits[REPORT_ITEM_TYPE_Feature];
								
							ReportSizeIndex = REPORT_ITEM_TYPE_Feature;
							break;
					}
					
					CurrReportIDInfo->ReportSizeBits[ReportSizeIndex] += CurrStateTable->Attributes.BitSize;

					if (ParserData->LargestReportSizeBits < CurrReportIDInfo->ReportSizeBits[ReportSizeIndex])
					  ParserData->LargestReportSizeBits = CurrReportIDInfo->ReportSizeBits[ReportSizeIndex];
					
					if (!(ReportItemData & IOF_CONSTANT) && CALLBACK_HIDParser_FilterHIDReportItem(&CurrStateTable->Attributes))
					{					
						if (ParserData->TotalReportItems == HID_MAX_REPORTITEMS)
						  return HID_PARSE_InsufficientReportItems;
					
						memcpy(&ParserData->ReportItems[ParserData->TotalReportItems],
						       &NewReportItem, sizeof(HID_ReportItem_t));
					
						ParserData->TotalReportItems++;
					}
				}
				
				UsageStackSize = 0;
				
				break;
		}
	  
		if ((HIDReportItem & TYPE_MASK) == TYPE_MAIN)
		{
			CurrStateTable->Attributes.Usage.MinMax.Minimum = 0;
			CurrStateTable->Attributes.Usage.MinMax.Maximum = 0;
			UsageStackSize = 0;
		}
	}
	
	return HID_PARSE_Successful;
}

bool USB_GetHIDReportItemInfo(const uint8_t* ReportData, HID_ReportItem_t* const ReportItem)
{
	uint16_t DataBitsRem  = ReportItem->Attributes.BitSize;
	uint16_t CurrentBit   = ReportItem->BitOffset;
	uint32_t BitMask      = (1 << 0);

	ReportItem->Value = 0;
	
	if (ReportItem->ReportID)
	{
		if (ReportItem->ReportID != ReportData[0])
		  return false;

		ReportData++;
	}

	while (DataBitsRem--)
	{
		if (ReportData[CurrentBit / 8] & (1 << (CurrentBit % 8)))
		  ReportItem->Value |= BitMask;
		
		CurrentBit++;
		BitMask <<= 1;
	}
	
	return true;
}

void USB_SetHIDReportItemInfo(uint8_t* ReportData, const HID_ReportItem_t* ReportItem)
{
	uint16_t DataBitsRem  = ReportItem->Attributes.BitSize;
	uint16_t CurrentBit   = ReportItem->BitOffset;
	uint32_t BitMask      = (1 << 0);

	if (ReportItem->ReportID)
	{
		ReportData[0] = ReportItem->ReportID;
		ReportData++;
	}

	while (DataBitsRem--)
	{
		if (ReportItem->Value & (1 << (CurrentBit % 8)))
		  ReportData[CurrentBit / 8] |= BitMask;

		CurrentBit++;
		BitMask <<= 1;
	}
}

uint16_t USB_GetHIDReportSize(HID_ReportInfo_t* const ParserData, const uint8_t ReportID, const uint8_t ReportType)
{
	for (uint8_t i = 0; i < HID_MAX_REPORT_IDS; i++)
	{
		if (ParserData->ReportIDSizes[i].ReportID == ReportID)
		  return ParserData->ReportIDSizes[i].ReportSizeBits[ReportType];
	}

	return 0;
}

#endif
