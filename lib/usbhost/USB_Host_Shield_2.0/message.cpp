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
// 0x80 is the default (i.e. trace) to turn off set this global to something lower.
// this allows for 126 other debugging levels.
// TO-DO: Allow assignment to a different serial port by software
int UsbDEBUGlvl = 0x80;

void E_Notifyc(char c, int lvl) {
        if(UsbDEBUGlvl < lvl) return;
#if defined(ARDUINO) && ARDUINO >=100
        USB_HOST_SERIAL.print(c);
#else
        USB_HOST_SERIAL.print(c, BYTE);
#endif
        //USB_HOST_SERIAL.flush();
}

void E_Notify(char const * msg, int lvl) {
        if(UsbDEBUGlvl < lvl) return;
        if(!msg) return;
        char c;

        while((c = pgm_read_byte(msg++))) E_Notifyc(c, lvl);
}

void E_NotifyStr(char const * msg, int lvl) {
        if(UsbDEBUGlvl < lvl) return;
        if(!msg) return;
        char c;

        while((c = *msg++)) E_Notifyc(c, lvl);
}

void E_Notify(uint8_t b, int lvl) {
        if(UsbDEBUGlvl < lvl) return;
#if defined(ARDUINO) && ARDUINO >=100
        USB_HOST_SERIAL.print(b);
#else
        USB_HOST_SERIAL.print(b, DEC);
#endif
        //USB_HOST_SERIAL.flush();
}

void E_Notify(double d, int lvl) {
        if(UsbDEBUGlvl < lvl) return;
        USB_HOST_SERIAL.print(d);
        //USB_HOST_SERIAL.flush();
}

#ifdef DEBUG_USB_HOST

void NotifyFailGetDevDescr(void) {
        Notify(PSTR("\r\ngetDevDescr "), 0x80);
}

void NotifyFailSetDevTblEntry(void) {
        Notify(PSTR("\r\nsetDevTblEn "), 0x80);
}

void NotifyFailGetConfDescr(void) {
        Notify(PSTR("\r\ngetConf "), 0x80);
}

void NotifyFailSetConfDescr(void) {
        Notify(PSTR("\r\nsetConf "), 0x80);
}

void NotifyFailGetDevDescr(uint8_t reason) {
        NotifyFailGetDevDescr();
        NotifyFail(reason);
}

void NotifyFailSetDevTblEntry(uint8_t reason) {
        NotifyFailSetDevTblEntry();
        NotifyFail(reason);

}

void NotifyFailGetConfDescr(uint8_t reason) {
        NotifyFailGetConfDescr();
        NotifyFail(reason);
}

void NotifyFailSetConfDescr(uint8_t reason) {
        NotifyFailSetConfDescr();
        NotifyFail(reason);
}

void NotifyFailUnknownDevice(uint16_t VID, uint16_t PID) {
        Notify(PSTR("\r\nUnknown Device Connected - VID: "), 0x80);
        D_PrintHex<uint16_t > (VID, 0x80);
        Notify(PSTR(" PID: "), 0x80);
        D_PrintHex<uint16_t > (PID, 0x80);
}

void NotifyFail(uint8_t rcode) {
        D_PrintHex<uint8_t > (rcode, 0x80);
        Notify(PSTR("\r\n"), 0x80);
}
#endif
