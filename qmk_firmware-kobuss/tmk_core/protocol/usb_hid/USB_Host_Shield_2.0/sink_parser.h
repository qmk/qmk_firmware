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
#if !defined(_usb_h_) || defined(__SINK_PARSER_H__)
#error "Never include hexdump.h directly; include Usb.h instead"
#else
#define __SINK_PARSER_H__

extern int UsbDEBUGlvl;

// This parser does absolutely nothing with the data, just swallows it.

template <class BASE_CLASS, class LEN_TYPE, class OFFSET_TYPE>
class SinkParser : public BASE_CLASS {
public:

        SinkParser() {
        };

        void Initialize() {
        };

        void Parse(const LEN_TYPE len, const uint8_t *pbuf, const OFFSET_TYPE &offset) {
        };
};


#endif // __HEXDUMP_H__
