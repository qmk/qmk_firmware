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
#if !defined(_usb_h_) || defined(__HEXDUMP_H__)
#error "Never include hexdump.h directly; include Usb.h instead"
#else
#define __HEXDUMP_H__

extern int UsbDEBUGlvl;

template <class BASE_CLASS, class LEN_TYPE, class OFFSET_TYPE>
class HexDumper : public BASE_CLASS {
        uint8_t byteCount;
        OFFSET_TYPE byteTotal;

public:

        HexDumper() : byteCount(0), byteTotal(0) {
        };

        void Initialize() {
                byteCount = 0;
                byteTotal = 0;
        };

        void Parse(const LEN_TYPE len, const uint8_t *pbuf, const OFFSET_TYPE &offset);
};

template <class BASE_CLASS, class LEN_TYPE, class OFFSET_TYPE>
void HexDumper<BASE_CLASS, LEN_TYPE, OFFSET_TYPE>::Parse(const LEN_TYPE len, const uint8_t *pbuf, const OFFSET_TYPE &offset) {
        if(UsbDEBUGlvl >= 0x80) { // Fully bypass this block of code if we do not debug.
                for(LEN_TYPE j = 0; j < len; j++, byteCount++, byteTotal++) {
                        if(!byteCount) {
                                PrintHex<OFFSET_TYPE > (byteTotal, 0x80);
                                E_Notify(PSTR(": "), 0x80);
                        }
                        PrintHex<uint8_t > (pbuf[j], 0x80);
                        E_Notify(PSTR(" "), 0x80);

                        if(byteCount == 15) {
                                E_Notify(PSTR("\r\n"), 0x80);
                                byteCount = 0xFF;
                        }
                }
        }
}

#endif // __HEXDUMP_H__
