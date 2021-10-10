/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */
#if !defined(__HIDDESCRIPTORPARSER_H__)
#define __HIDDESCRIPTORPARSER_H__

#include "hid.h"

class ReportDescParserBase : public USBReadParser {
public:
        typedef void (*UsagePageFunc)(uint16_t usage);

        static void PrintGenericDesktopPageUsage(uint16_t usage);
        static void PrintSimulationControlsPageUsage(uint16_t usage);
        static void PrintVRControlsPageUsage(uint16_t usage);
        static void PrintSportsControlsPageUsage(uint16_t usage);
        static void PrintGameControlsPageUsage(uint16_t usage);
        static void PrintGenericDeviceControlsPageUsage(uint16_t usage);
        static void PrintLEDPageUsage(uint16_t usage);
        static void PrintButtonPageUsage(uint16_t usage);
        static void PrintOrdinalPageUsage(uint16_t usage);
        static void PrintTelephonyPageUsage(uint16_t usage);
        static void PrintConsumerPageUsage(uint16_t usage);
        static void PrintDigitizerPageUsage(uint16_t usage);
        static void PrintAlphanumDisplayPageUsage(uint16_t usage);
        static void PrintMedicalInstrumentPageUsage(uint16_t usage);

        static void PrintValue(uint8_t *p, uint8_t len);
        static void PrintByteValue(uint8_t data);

        static void PrintItemTitle(uint8_t prefix);

        static const char * const usagePageTitles0[];
        static const char * const usagePageTitles1[];
        static const char * const genDesktopTitles0[];
        static const char * const genDesktopTitles1[];
        static const char * const genDesktopTitles2[];
        static const char * const genDesktopTitles3[];
        static const char * const genDesktopTitles4[];
        static const char * const simuTitles0[];
        static const char * const simuTitles1[];
        static const char * const simuTitles2[];
        static const char * const vrTitles0[];
        static const char * const vrTitles1[];
        static const char * const sportsCtrlTitles0[];
        static const char * const sportsCtrlTitles1[];
        static const char * const sportsCtrlTitles2[];
        static const char * const gameTitles0[];
        static const char * const gameTitles1[];
        static const char * const genDevCtrlTitles[];
        static const char * const ledTitles[];
        static const char * const telTitles0[];
        static const char * const telTitles1[];
        static const char * const telTitles2[];
        static const char * const telTitles3[];
        static const char * const telTitles4[];
        static const char * const telTitles5[];
        static const char * const consTitles0[];
        static const char * const consTitles1[];
        static const char * const consTitles2[];
        static const char * const consTitles3[];
        static const char * const consTitles4[];
        static const char * const consTitles5[];
        static const char * const consTitles6[];
        static const char * const consTitles7[];
        static const char * const consTitles8[];
        static const char * const consTitles9[];
        static const char * const consTitlesA[];
        static const char * const consTitlesB[];
        static const char * const consTitlesC[];
        static const char * const consTitlesD[];
        static const char * const consTitlesE[];
        static const char * const digitTitles0[];
        static const char * const digitTitles1[];
        static const char * const digitTitles2[];
        static const char * const aplphanumTitles0[];
        static const char * const aplphanumTitles1[];
        static const char * const aplphanumTitles2[];
        static const char * const medInstrTitles0[];
        static const char * const medInstrTitles1[];
        static const char * const medInstrTitles2[];
        static const char * const medInstrTitles3[];
        static const char * const medInstrTitles4[];

protected:
        static UsagePageFunc usagePageFunctions[];

        MultiValueBuffer theBuffer;
        MultiByteValueParser valParser;
        ByteSkipper theSkipper;
        uint8_t varBuffer[sizeof (USB_CONFIGURATION_DESCRIPTOR)];

        uint8_t itemParseState; // Item parser state variable
        uint8_t itemSize; // Item size
        uint8_t itemPrefix; // Item prefix (first byte)
        uint8_t rptSize; // Report Size
        uint8_t rptCount; // Report Count

        uint16_t totalSize; // Report size in bits

        // Method should be defined here if virtual.
        virtual uint8_t ParseItem(uint8_t **pp, uint16_t *pcntdn);

        UsagePageFunc pfUsage;

        static void PrintUsagePage(uint16_t page);
        void SetUsagePage(uint16_t page);

public:

        ReportDescParserBase() :
        itemParseState(0),
        itemSize(0),
        itemPrefix(0),
        rptSize(0),
        rptCount(0),
        pfUsage(NULL) {
                theBuffer.pValue = varBuffer;
                valParser.Initialize(&theBuffer);
                theSkipper.Initialize(&theBuffer);
        };

        void Parse(const uint16_t len, const uint8_t *pbuf, const uint16_t &offset);

        enum {
                enErrorSuccess = 0
                , enErrorIncomplete // value or record is partialy read in buffer
                , enErrorBufferTooSmall
        };
};

class ReportDescParser : public ReportDescParserBase {
};

class ReportDescParser2 : public ReportDescParserBase {
        uint8_t rptId; // Report ID
        uint8_t useMin; // Usage Minimum
        uint8_t useMax; // Usage Maximum
        uint8_t fieldCount; // Number of field being currently processed

        void OnInputItem(uint8_t itm); // Method which is called every time Input item is found

        uint8_t *pBuf; // Report buffer pointer
        uint8_t bLen; // Report length

protected:
        // Method should be defined here if virtual.
        virtual uint8_t ParseItem(uint8_t **pp, uint16_t *pcntdn);

public:

        ReportDescParser2(uint16_t len, uint8_t *pbuf) :
        ReportDescParserBase(), rptId(0), useMin(0), useMax(0), fieldCount(0), pBuf(pbuf), bLen(len) {
        };
};

class UniversalReportParser : public HIDReportParser {
public:
        // Method should be defined here if virtual.
        virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif // __HIDDESCRIPTORPARSER_H__
