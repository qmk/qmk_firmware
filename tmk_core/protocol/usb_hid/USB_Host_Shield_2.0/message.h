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
#if !defined(_usb_h_) || defined(__MESSAGE_H__)
#error "Never include message.h directly; include Usb.h instead"
#else
#define __MESSAGE_H__

extern int UsbDEBUGlvl;

void E_Notify(char const * msg, int lvl);
void E_Notify(uint8_t b, int lvl);
void E_NotifyStr(char const * msg, int lvl);
void E_Notifyc(char c, int lvl);

#ifdef DEBUG_USB_HOST
#define Notify E_Notify
#define NotifyStr E_NotifyStr
#define Notifyc E_Notifyc
void NotifyFailGetDevDescr(uint8_t reason);
void NotifyFailSetDevTblEntry(uint8_t reason);
void NotifyFailGetConfDescr(uint8_t reason);
void NotifyFailSetConfDescr(uint8_t reason);
void NotifyFailGetDevDescr(void);
void NotifyFailSetDevTblEntry(void);
void NotifyFailGetConfDescr(void);
void NotifyFailSetConfDescr(void);
void NotifyFailUnknownDevice(uint16_t VID, uint16_t PID);
void NotifyFail(uint8_t rcode);
#else
#define Notify(...) ((void)0)
#define NotifyStr(...) ((void)0)
#define Notifyc(...) ((void)0)
#define NotifyFailGetDevDescr(...) ((void)0)
#define NotifyFailSetDevTblEntry(...) ((void)0)
#define NotifyFailGetConfDescr(...) ((void)0)
#define NotifyFailGetDevDescr(...) ((void)0)
#define NotifyFailSetDevTblEntry(...) ((void)0)
#define NotifyFailGetConfDescr(...) ((void)0)
#define NotifyFailSetConfDescr(...) ((void)0)
#define NotifyFailUnknownDevice(...) ((void)0)
#define NotifyFail(...) ((void)0)
#endif

template <class ERROR_TYPE>
void ErrorMessage(uint8_t level, char const * msg, ERROR_TYPE rcode = 0) {
#ifdef DEBUG_USB_HOST
        Notify(msg, level);
        Notify(PSTR(": "), level);
        D_PrintHex<ERROR_TYPE > (rcode, level);
        Notify(PSTR("\r\n"), level);
#endif
}

template <class ERROR_TYPE>
void ErrorMessage(char const * msg, ERROR_TYPE rcode = 0) {
#ifdef DEBUG_USB_HOST
        Notify(msg, 0x80);
        Notify(PSTR(": "), 0x80);
        D_PrintHex<ERROR_TYPE > (rcode, 0x80);
        Notify(PSTR("\r\n"), 0x80);
#endif
}

#endif // __MESSAGE_H__
