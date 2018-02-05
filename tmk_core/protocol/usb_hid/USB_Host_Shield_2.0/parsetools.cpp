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
#include "Usb.h"

bool MultiByteValueParser::Parse(uint8_t **pp, uint16_t *pcntdn) {
        if(!pBuf) {
                Notify(PSTR("Buffer pointer is NULL!\r\n"), 0x80);
                return false;
        }
        for(; countDown && (*pcntdn); countDown--, (*pcntdn)--, (*pp)++)
                pBuf[valueSize - countDown] = (**pp);

        if(countDown)
                return false;

        countDown = valueSize;
        return true;
}

bool PTPListParser::Parse(uint8_t **pp, uint16_t *pcntdn, PTP_ARRAY_EL_FUNC pf, const void *me) {
        switch(nStage) {
                case 0:
                        pBuf->valueSize = lenSize;
                        theParser.Initialize(pBuf);
                        nStage = 1;

                case 1:
                        if(!theParser.Parse(pp, pcntdn))
                                return false;

                        arLen = 0;
                        arLen = (pBuf->valueSize >= 4) ? *((uint32_t*)pBuf->pValue) : (uint32_t)(*((uint16_t*)pBuf->pValue));
                        arLenCntdn = arLen;
                        nStage = 2;

                case 2:
                        pBuf->valueSize = valSize;
                        theParser.Initialize(pBuf);
                        nStage = 3;

                case 3:
                        for(; arLenCntdn; arLenCntdn--) {
                                if(!theParser.Parse(pp, pcntdn))
                                        return false;

                                if(pf)
                                        pf(pBuf, (arLen - arLenCntdn), me);
                        }

                        nStage = 0;
        }
        return true;
}
