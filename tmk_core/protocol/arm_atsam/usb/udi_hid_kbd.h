/**
 * \file
 *
 * \brief USB Device Human Interface Device (HID) keyboard interface.
 *
 * Copyright (c) 2009-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _UDC_HID_KBD_H_
#define _UDC_HID_KBD_H_

#include "udc_desc.h"
#include "udi.h"

#ifdef __cplusplus
extern "C" {
#endif

//******************************************************************************
// Keyboard interface definitions
//******************************************************************************
extern UDC_DESC_STORAGE udi_api_t udi_api_hid_kbd;
extern bool                       udi_hid_kbd_b_report_valid;
extern volatile bool              udi_hid_kbd_b_report_trans_ongoing;
extern uint8_t                    udi_hid_kbd_report_set;
bool                              udi_hid_kbd_send_report(void);

//********************************************************************************************
// NKRO Keyboard
//********************************************************************************************
#ifdef NKRO_ENABLE
extern UDC_DESC_STORAGE udi_api_t udi_api_hid_nkro;
extern bool                       udi_hid_nkro_b_report_valid;
extern volatile bool              udi_hid_nkro_b_report_trans_ongoing;
bool                              udi_hid_nkro_send_report(void);
#endif // NKRO_ENABLE

//********************************************************************************************
// SYS-CTRL interface
//********************************************************************************************
#ifdef EXTRAKEY_ENABLE
extern UDC_DESC_STORAGE udi_api_t udi_api_hid_exk;
extern bool                       udi_hid_exk_b_report_valid;
bool                              udi_hid_exk_send_report(void);
#endif // EXTRAKEY_ENABLE

//********************************************************************************************
// CON Console
//********************************************************************************************
#ifdef CONSOLE_ENABLE
extern UDC_DESC_STORAGE udi_api_t udi_api_hid_con;
extern bool                       udi_hid_con_b_report_valid;
extern uint8_t                    udi_hid_con_report_set[UDI_HID_CON_REPORT_SIZE];
extern volatile bool              udi_hid_con_b_report_trans_ongoing;
bool                              udi_hid_con_send_report(void);
#endif // CONSOLE_ENABLE

//********************************************************************************************
// MOU Mouse
//********************************************************************************************
#ifdef MOUSE_ENABLE
extern UDC_DESC_STORAGE udi_api_t udi_api_hid_mou;
extern bool                       udi_hid_mou_b_report_valid;
bool                              udi_hid_mou_send_report(void);
#endif // MOUSE_ENABLE

//********************************************************************************************
// RAW Raw
//********************************************************************************************
#ifdef RAW_ENABLE
extern UDC_DESC_STORAGE udi_api_t udi_api_hid_raw;
bool                              udi_hid_raw_send_report(void);
bool                              udi_hid_raw_receive_report(void);
#endif // RAW_ENABLE

//@}

#ifdef __cplusplus
}
#endif

#endif // _UDC_HID_KBD_H_
