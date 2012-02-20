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

#define  __INCLUDE_FROM_USB_DRIVER
#define  __INCLUDE_FROM_HID_DRIVER
#include "HIDParser.h"

uint8_t USB_ProcessHIDReport(const uint8_t* ReportData,
                             uint16_t ReportSize,
                             HID_ReportInfo_t* const ParserData)
{
	HID_StateTable_t      StateTable[HID_STATETABLE_STACK_DEPTH];
	HID_StateTable_t*     CurrStateTable          = &StateTable[0];
	HID_CollectionPath_t* CurrCollectionPath      = NULL;
	HID_ReportSizeInfo_t* CurrReportIDInfo        = &ParserData->ReportIDSizes[0];
	uint16_t              UsageList[HID_USAGE_STACK_DEPTH];
	uint8_t               UsageListSize           = 0;
	HID_MinMax_t          UsageMinMax             = {0, 0};

	memset(ParserData,       0x00, sizeof(HID_ReportInfo_t));
	memset(CurrStateTable,   0x00, sizeof(HID_StateTable_t));
	memset(CurrReportIDInfo, 0x00, sizeof(HID_ReportSizeInfo_t));

	ParserData->TotalDeviceReports = 1;

	while (ReportSize)
	{
		uint8_t  HIDReportItem  = *ReportData;
		uint32_t ReportItemData = 0;

		ReportData++;
		ReportSize--;

		switch (HIDReportItem & HID_RI_DATA_SIZE_MASK)
		{
			case HID_RI_DATA_BITS_32:
				ReportItemData  = (((uint32_t)ReportData[3] << 24) | ((uint32_t)ReportData[2] << 16) |
			                       ((uint16_t)ReportData[1] << 8)  | ReportData[0]);
				ReportSize     -= 4;
				ReportData     += 4;
				break;
			case HID_RI_DATA_BITS_16:
				ReportItemData  = (((uint16_t)ReportData[1] << 8) | (ReportData[0]));
				ReportSize     -= 2;
				ReportData     += 2;
				break;
			case HID_RI_DATA_BITS_8:
				ReportItemData  = ReportData[0];
				ReportSize     -= 1;
				ReportData     += 1;
				break;
		}

		switch (HIDReportItem & (HID_RI_TYPE_MASK | HID_RI_TAG_MASK))
		{
			case HID_RI_PUSH(0):
				if (CurrStateTable == &StateTable[HID_STATETABLE_STACK_DEPTH - 1])
				  return HID_PARSE_HIDStackOverflow;

				memcpy((CurrStateTable + 1),
				       CurrStateTable,
				       sizeof(HID_ReportItem_t));

				CurrStateTable++;
				break;
			case HID_RI_POP(0):
				if (CurrStateTable == &StateTable[0])
				  return HID_PARSE_HIDStackUnderflow;

				CurrStateTable--;
				break;
			case HID_RI_USAGE_PAGE(0):
				if ((HIDReportItem & HID_RI_DATA_SIZE_MASK) == HID_RI_DATA_BITS_32)
				  CurrStateTable->Attributes.Usage.Page = (ReportItemData >> 16);

				CurrStateTable->Attributes.Usage.Page       = ReportItemData;
				break;
			case HID_RI_LOGICAL_MINIMUM(0):
				CurrStateTable->Attributes.Logical.Minimum  = ReportItemData;
				break;
			case HID_RI_LOGICAL_MAXIMUM(0):
				CurrStateTable->Attributes.Logical.Maximum  = ReportItemData;
				break;
			case HID_RI_PHYSICAL_MINIMUM(0):
				CurrStateTable->Attributes.Physical.Minimum = ReportItemData;
				break;
			case HID_RI_PHYSICAL_MAXIMUM(0):
				CurrStateTable->Attributes.Physical.Maximum = ReportItemData;
				break;
			case HID_RI_UNIT_EXPONENT(0):
				CurrStateTable->Attributes.Unit.Exponent    = ReportItemData;
				break;
			case HID_RI_UNIT(0):
				CurrStateTable->Attributes.Unit.Type        = ReportItemData;
				break;
			case HID_RI_REPORT_SIZE(0):
				CurrStateTable->Attributes.BitSize          = ReportItemData;
				break;
			case HID_RI_REPORT_COUNT(0):
				CurrStateTable->ReportCount                 = ReportItemData;
				break;
			case HID_RI_REPORT_ID(0):
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
						if (ParserData->TotalDeviceReports == HID_MAX_REPORT_IDS)
						  return HID_PARSE_InsufficientReportIDItems;

						CurrReportIDInfo = &ParserData->ReportIDSizes[ParserData->TotalDeviceReports++];
						memset(CurrReportIDInfo, 0x00, sizeof(HID_ReportSizeInfo_t));
					}
				}

				ParserData->UsingReportIDs = true;

				CurrReportIDInfo->ReportID = CurrStateTable->ReportID;
				break;
			case HID_RI_USAGE(0):
				if (UsageListSize == HID_USAGE_STACK_DEPTH)
				  return HID_PARSE_UsageListOverflow;

				UsageList[UsageListSize++] = ReportItemData;
				break;
			case HID_RI_USAGE_MINIMUM(0):
				UsageMinMax.Minimum = ReportItemData;
				break;
			case HID_RI_USAGE_MAXIMUM(0):
				UsageMinMax.Maximum = ReportItemData;
				break;
			case HID_RI_COLLECTION(0):
				if (CurrCollectionPath == NULL)
				{
					CurrCollectionPath = &ParserData->CollectionPaths[0];
				}
				else
				{
					HID_CollectionPath_t* ParentCollectionPath = CurrCollectionPath;

					CurrCollectionPath = &ParserData->CollectionPaths[1];

					while (CurrCollectionPath->Parent != NULL)
					{
						if (CurrCollectionPath == &ParserData->CollectionPaths[HID_MAX_COLLECTIONS - 1])
						  return HID_PARSE_InsufficientCollectionPaths;

						CurrCollectionPath++;
					}

					CurrCollectionPath->Parent = ParentCollectionPath;
				}

				CurrCollectionPath->Type       = ReportItemData;
				CurrCollectionPath->Usage.Page = CurrStateTable->Attributes.Usage.Page;

				if (UsageListSize)
				{
					CurrCollectionPath->Usage.Usage = UsageList[0];

					for (uint8_t i = 0; i < UsageListSize; i++)
					  UsageList[i] = UsageList[i + 1];

					UsageListSize--;
				}
				else if (UsageMinMax.Minimum <= UsageMinMax.Maximum)
				{
					CurrCollectionPath->Usage.Usage = UsageMinMax.Minimum++;
				}

				break;
			case HID_RI_END_COLLECTION(0):
				if (CurrCollectionPath == NULL)
				  return HID_PARSE_UnexpectedEndCollection;

				CurrCollectionPath = CurrCollectionPath->Parent;
				break;
			case HID_RI_INPUT(0):
			case HID_RI_OUTPUT(0):
			case HID_RI_FEATURE(0):
				for (uint8_t ReportItemNum = 0; ReportItemNum < CurrStateTable->ReportCount; ReportItemNum++)
				{
					HID_ReportItem_t NewReportItem;

					memcpy(&NewReportItem.Attributes,
					       &CurrStateTable->Attributes,
					       sizeof(HID_ReportItem_Attributes_t));

					NewReportItem.ItemFlags      = ReportItemData;
					NewReportItem.CollectionPath = CurrCollectionPath;
					NewReportItem.ReportID       = CurrStateTable->ReportID;

					if (UsageListSize)
					{
						NewReportItem.Attributes.Usage.Usage = UsageList[0];

						for (uint8_t i = 0; i < UsageListSize; i++)
						  UsageList[i] = UsageList[i + 1];

						UsageListSize--;
					}
					else if (UsageMinMax.Minimum <= UsageMinMax.Maximum)
					{
						NewReportItem.Attributes.Usage.Usage = UsageMinMax.Minimum++;
					}

					uint8_t ItemTypeTag = (HIDReportItem & (HID_RI_TYPE_MASK | HID_RI_TAG_MASK));

					if (ItemTypeTag == HID_RI_INPUT(0))
					  NewReportItem.ItemType = HID_REPORT_ITEM_In;
					else if (ItemTypeTag == HID_RI_OUTPUT(0))
					  NewReportItem.ItemType = HID_REPORT_ITEM_Out;
					else
					  NewReportItem.ItemType = HID_REPORT_ITEM_Feature;

					NewReportItem.BitOffset = CurrReportIDInfo->ReportSizeBits[NewReportItem.ItemType];

					CurrReportIDInfo->ReportSizeBits[NewReportItem.ItemType] += CurrStateTable->Attributes.BitSize;

					ParserData->LargestReportSizeBits = MAX(ParserData->LargestReportSizeBits, CurrReportIDInfo->ReportSizeBits[NewReportItem.ItemType]);

					if (ParserData->TotalReportItems == HID_MAX_REPORTITEMS)
					  return HID_PARSE_InsufficientReportItems;

					memcpy(&ParserData->ReportItems[ParserData->TotalReportItems],
					       &NewReportItem, sizeof(HID_ReportItem_t));

					if (!(ReportItemData & HID_IOF_CONSTANT) && CALLBACK_HIDParser_FilterHIDReportItem(&NewReportItem))
					  ParserData->TotalReportItems++;
				}

				break;
		}

		if ((HIDReportItem & HID_RI_TYPE_MASK) == HID_RI_TYPE_MAIN)
		{
			UsageMinMax.Minimum = 0;
			UsageMinMax.Maximum = 0;
			UsageListSize       = 0;
		}
	}

	if (!(ParserData->TotalReportItems))
	  return HID_PARSE_NoUnfilteredReportItems;

	return HID_PARSE_Successful;
}

bool USB_GetHIDReportItemInfo(const uint8_t* ReportData,
                              HID_ReportItem_t* const ReportItem)
{
	if (ReportItem == NULL)
	  return false;

	uint16_t DataBitsRem  = ReportItem->Attributes.BitSize;
	uint16_t CurrentBit   = ReportItem->BitOffset;
	uint32_t BitMask      = (1 << 0);

	if (ReportItem->ReportID)
	{
		if (ReportItem->ReportID != ReportData[0])
		  return false;

		ReportData++;
	}

	ReportItem->PreviousValue = ReportItem->Value;
	ReportItem->Value = 0;

	while (DataBitsRem--)
	{
		if (ReportData[CurrentBit / 8] & (1 << (CurrentBit % 8)))
		  ReportItem->Value |= BitMask;

		CurrentBit++;
		BitMask <<= 1;
	}

	return true;
}

void USB_SetHIDReportItemInfo(uint8_t* ReportData,
                              HID_ReportItem_t* const ReportItem)
{
	if (ReportItem == NULL)
	  return;

	uint16_t DataBitsRem  = ReportItem->Attributes.BitSize;
	uint16_t CurrentBit   = ReportItem->BitOffset;
	uint32_t BitMask      = (1 << 0);

	if (ReportItem->ReportID)
	{
		ReportData[0] = ReportItem->ReportID;
		ReportData++;
	}

	ReportItem->PreviousValue = ReportItem->Value;

	while (DataBitsRem--)
	{
		if (ReportItem->Value & (1 << (CurrentBit % 8)))
		  ReportData[CurrentBit / 8] |= BitMask;

		CurrentBit++;
		BitMask <<= 1;
	}
}

uint16_t USB_GetHIDReportSize(HID_ReportInfo_t* const ParserData,
                              const uint8_t ReportID,
                              const uint8_t ReportType)
{
	for (uint8_t i = 0; i < HID_MAX_REPORT_IDS; i++)
	{
		uint16_t ReportSizeBits = ParserData->ReportIDSizes[i].ReportSizeBits[ReportType];

		if (ParserData->ReportIDSizes[i].ReportID == ReportID)
		  return (ReportSizeBits / 8) + ((ReportSizeBits % 8) ? 1 : 0);
	}

	return 0;
}

