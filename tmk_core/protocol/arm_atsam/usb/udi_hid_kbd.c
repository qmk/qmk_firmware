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

#include "samd51j18a.h"
#include "d51_util.h"
#include "conf_usb.h"
#include "usb_protocol.h"
#include "udd.h"
#include "udc.h"
#include "udi_device_conf.h"
#include "udi_hid.h"
#include "udi_hid_kbd.h"
#include <string.h>
#include "report.h"
#include "usb_descriptor_common.h"

//***************************************************************************
// KBD
//***************************************************************************
bool    udi_hid_kbd_enable(void);
void    udi_hid_kbd_disable(void);
bool    udi_hid_kbd_setup(void);
uint8_t udi_hid_kbd_getsetting(void);

UDC_DESC_STORAGE udi_api_t udi_api_hid_kbd = {
    .enable     = (bool (*)(void))udi_hid_kbd_enable,
    .disable    = (void (*)(void))udi_hid_kbd_disable,
    .setup      = (bool (*)(void))udi_hid_kbd_setup,
    .getsetting = (uint8_t(*)(void))udi_hid_kbd_getsetting,
    .sof_notify = NULL,
};

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_kbd_rate;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_kbd_protocol;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_kbd_report_set;

bool udi_hid_kbd_b_report_valid;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_kbd_report[UDI_HID_KBD_REPORT_SIZE];

volatile bool udi_hid_kbd_b_report_trans_ongoing;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_kbd_report_trans[UDI_HID_KBD_REPORT_SIZE];

COMPILER_WORD_ALIGNED
UDC_DESC_STORAGE udi_hid_kbd_report_desc_t udi_hid_kbd_report_desc = {{
    0x05, 0x01, // Usage Page (Generic Desktop)
    0x09, 0x06, // Usage (Keyboard)
    0xA1, 0x01, // Collection (Application)
    // Modifiers (8 bits)
    0x05, 0x07, //   Usage Page (Keyboard)
    0x19, 0xE0, //   Usage Minimum (Keyboard Left Control)
    0x29, 0xE7, //   Usage Maximum (Keyboard Right GUI)
    0x15, 0x00, //   Logical Minimum (0)
    0x25, 0x01, //   Logical Maximum (1)
    0x95, 0x08, //   Report Count (8)
    0x75, 0x01, //   Report Size (1)
    0x81, 0x02, //   Input (Data, Variable, Absolute)
    // Reserved (1 byte)
    0x81, 0x01, //   Input (Constant)
    // Keycodes (6 bytes)
    0x19, 0x00, //   Usage Minimum (0)
    0x29, 0xFF, //   Usage Maximum (255)
    0x15, 0x00, //   Logical Minimum (0)
    0x25, 0xFF, //   Logical Maximum (255)
    0x95, 0x06, //   Report Count (6)
    0x75, 0x08, //   Report Size (8)
    0x81, 0x00, //   Input (Data, Array, Absolute)

    // Status LEDs (5 bits)
    0x05, 0x08, //   Usage Page (LED)
    0x19, 0x01, //   Usage Minimum (Num Lock)
    0x29, 0x05, //   Usage Maximum (Kana)
    0x15, 0x00, //   Logical Minimum (0)
    0x25, 0x01, //   Logical Maximum (1)
    0x95, 0x05, //   Report Count (5)
    0x75, 0x01, //   Report Size (1)
    0x91, 0x02, //   Output (Data, Variable, Absolute)
    // LED padding (3 bits)
    0x95, 0x03, //   Report Count (3)
    0x91, 0x01, //   Output (Constant)
    0xC0        // End Collection
}};

static bool udi_hid_kbd_setreport(void);

static void udi_hid_kbd_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep);

static void udi_hid_kbd_setreport_valid(void);

bool udi_hid_kbd_enable(void) {
    // Initialize internal values
    udi_hid_kbd_rate                   = 0;
    udi_hid_kbd_protocol               = 0;
    udi_hid_kbd_b_report_trans_ongoing = false;
    memset(udi_hid_kbd_report, 0, UDI_HID_KBD_REPORT_SIZE);
    udi_hid_kbd_b_report_valid = false;
    return UDI_HID_KBD_ENABLE_EXT();
}

void udi_hid_kbd_disable(void) {
    UDI_HID_KBD_DISABLE_EXT();
}

bool udi_hid_kbd_setup(void) {
    return udi_hid_setup(&udi_hid_kbd_rate, &udi_hid_kbd_protocol, (uint8_t *)&udi_hid_kbd_report_desc, udi_hid_kbd_setreport);
}

uint8_t udi_hid_kbd_getsetting(void) {
    return 0;
}

static bool udi_hid_kbd_setreport(void) {
    if ((USB_HID_REPORT_TYPE_OUTPUT == (udd_g_ctrlreq.req.wValue >> 8)) && (0 == (0xFF & udd_g_ctrlreq.req.wValue)) && (1 == udd_g_ctrlreq.req.wLength)) {
        // Report OUT type on report ID 0 from USB Host
        udd_g_ctrlreq.payload      = &udi_hid_kbd_report_set;
        udd_g_ctrlreq.callback     = udi_hid_kbd_setreport_valid;
        udd_g_ctrlreq.payload_size = 1;
        return true;
    }
    return false;
}

bool udi_hid_kbd_send_report(void) {
    if (!main_b_kbd_enable) {
        return false;
    }

    if (udi_hid_kbd_b_report_trans_ongoing) {
        return false;
    }

    memcpy(udi_hid_kbd_report_trans, udi_hid_kbd_report, UDI_HID_KBD_REPORT_SIZE);
    udi_hid_kbd_b_report_valid         = false;
    udi_hid_kbd_b_report_trans_ongoing = udd_ep_run(UDI_HID_KBD_EP_IN | USB_EP_DIR_IN, false, udi_hid_kbd_report_trans, UDI_HID_KBD_REPORT_SIZE, udi_hid_kbd_report_sent);

    return udi_hid_kbd_b_report_trans_ongoing;
}

static void udi_hid_kbd_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep) {
    UNUSED(status);
    UNUSED(nb_sent);
    UNUSED(ep);
    udi_hid_kbd_b_report_trans_ongoing = false;
    if (udi_hid_kbd_b_report_valid) {
        udi_hid_kbd_send_report();
    }
}

static void udi_hid_kbd_setreport_valid(void) {
    // UDI_HID_KBD_CHANGE_LED(udi_hid_kbd_report_set);
}

//********************************************************************************************
// NKRO Keyboard
//********************************************************************************************
#ifdef NKRO_ENABLE

bool    udi_hid_nkro_enable(void);
void    udi_hid_nkro_disable(void);
bool    udi_hid_nkro_setup(void);
uint8_t udi_hid_nkro_getsetting(void);

UDC_DESC_STORAGE udi_api_t udi_api_hid_nkro = {
    .enable     = (bool (*)(void))udi_hid_nkro_enable,
    .disable    = (void (*)(void))udi_hid_nkro_disable,
    .setup      = (bool (*)(void))udi_hid_nkro_setup,
    .getsetting = (uint8_t(*)(void))udi_hid_nkro_getsetting,
    .sof_notify = NULL,
};

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_nkro_rate;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_nkro_protocol;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_nkro_report_set;

bool udi_hid_nkro_b_report_valid;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_nkro_report[UDI_HID_NKRO_REPORT_SIZE];

volatile bool udi_hid_nkro_b_report_trans_ongoing;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_nkro_report_trans[UDI_HID_NKRO_REPORT_SIZE];

COMPILER_WORD_ALIGNED
UDC_DESC_STORAGE udi_hid_nkro_report_desc_t udi_hid_nkro_report_desc = {{
    0x05, 0x01, // Usage Page (Generic Desktop)
    0x09, 0x06, // Usage (Keyboard)
    0xA1, 0x01, // Collection (Application)

    // Modifiers (8 bits)
    0x05, 0x07, //   Usage Page (Keyboard/Keypad)
    0x19, 0xE0, //   Usage Minimum (Keyboard Left Control)
    0x29, 0xE7, //   Usage Maximum (Keyboard Right GUI)
    0x15, 0x00, //   Logical Minimum (0)
    0x25, 0x01, //   Logical Maximum (1)
    0x95, 0x08, //   Report Count (8)
    0x75, 0x01, //   Report Size (1)
    0x81, 0x02, //   Input (Data, Variable, Absolute)
    // Keycodes
    0x05, 0x07, //   Usage Page (Keyboard/Keypad)
    0x19, 0x00, //   Usage Minimum (0)
    0x29, 0xF7, //   Usage Maximum (247)
    0x15, 0x00, //   Logical Minimum (0)
    0x25, 0x01, //   Logical Maximum (1)
    0x95, 0xF8, //   Report Count (248)
    0x75, 0x01, //   Report Size (1)
    0x81, 0x02, //   Input (Data, Variable, Absolute, Bitfield)

    // Status LEDs (5 bits)
    0x05, 0x08, //   Usage Page (LED)
    0x19, 0x01, //   Usage Minimum (Num Lock)
    0x29, 0x05, //   Usage Maximum (Kana)
    0x95, 0x05, //   Report Count (5)
    0x75, 0x01, //   Report Size (1)
    0x91, 0x02, //   Output (Data, Variable, Absolute)
    // LED padding (3 bits)
    0x95, 0x01, //   Report Count (1)
    0x75, 0x03, //   Report Size (3)
    0x91, 0x03, //   Output (Constant)
    0xC0        // End Collection
}};

static bool udi_hid_nkro_setreport(void);
static void udi_hid_nkro_setreport_valid(void);
static void udi_hid_nkro_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep);

bool udi_hid_nkro_enable(void) {
    // Initialize internal values
    udi_hid_nkro_rate                   = 0;
    udi_hid_nkro_protocol               = 0;
    udi_hid_nkro_b_report_trans_ongoing = false;
    memset(udi_hid_nkro_report, 0, UDI_HID_NKRO_REPORT_SIZE);
    udi_hid_nkro_b_report_valid = false;
    return UDI_HID_NKRO_ENABLE_EXT();
}

void udi_hid_nkro_disable(void) {
    UDI_HID_NKRO_DISABLE_EXT();
}

bool udi_hid_nkro_setup(void) {
    return udi_hid_setup(&udi_hid_nkro_rate, &udi_hid_nkro_protocol, (uint8_t *)&udi_hid_nkro_report_desc, udi_hid_nkro_setreport);
}

uint8_t udi_hid_nkro_getsetting(void) {
    return 0;
}

// keyboard receives LED report here
static bool udi_hid_nkro_setreport(void) {
    if ((USB_HID_REPORT_TYPE_OUTPUT == (udd_g_ctrlreq.req.wValue >> 8)) && (0 == (0xFF & udd_g_ctrlreq.req.wValue)) && (1 == udd_g_ctrlreq.req.wLength)) {
        // Report OUT type on report ID 0 from USB Host
        udd_g_ctrlreq.payload      = &udi_hid_nkro_report_set;
        udd_g_ctrlreq.callback     = udi_hid_nkro_setreport_valid; // must call routine to transform setreport to LED state
        udd_g_ctrlreq.payload_size = 1;
        return true;
    }
    return false;
}

bool udi_hid_nkro_send_report(void) {
    if (!main_b_nkro_enable) {
        return false;
    }

    if (udi_hid_nkro_b_report_trans_ongoing) {
        return false;
    }

    memcpy(udi_hid_nkro_report_trans, udi_hid_nkro_report, UDI_HID_NKRO_REPORT_SIZE);
    udi_hid_nkro_b_report_valid         = false;
    udi_hid_nkro_b_report_trans_ongoing = udd_ep_run(UDI_HID_NKRO_EP_IN | USB_EP_DIR_IN, false, udi_hid_nkro_report_trans, UDI_HID_NKRO_REPORT_SIZE, udi_hid_nkro_report_sent);

    return udi_hid_nkro_b_report_trans_ongoing;
}

static void udi_hid_nkro_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep) {
    UNUSED(status);
    UNUSED(nb_sent);
    UNUSED(ep);
    udi_hid_nkro_b_report_trans_ongoing = false;
    if (udi_hid_nkro_b_report_valid) {
        udi_hid_nkro_send_report();
    }
}

static void udi_hid_nkro_setreport_valid(void) {
    // UDI_HID_NKRO_CHANGE_LED(udi_hid_nkro_report_set);
}

#endif // NKRO_ENABLE

//********************************************************************************************
// EXK (extra-keys) SYS-CTRL  Keyboard
//********************************************************************************************
#ifdef EXTRAKEY_ENABLE

bool    udi_hid_exk_enable(void);
void    udi_hid_exk_disable(void);
bool    udi_hid_exk_setup(void);
uint8_t udi_hid_exk_getsetting(void);

UDC_DESC_STORAGE udi_api_t udi_api_hid_exk = {
    .enable     = (bool (*)(void))udi_hid_exk_enable,
    .disable    = (void (*)(void))udi_hid_exk_disable,
    .setup      = (bool (*)(void))udi_hid_exk_setup,
    .getsetting = (uint8_t(*)(void))udi_hid_exk_getsetting,
    .sof_notify = NULL,
};

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_exk_rate;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_exk_protocol;

// COMPILER_WORD_ALIGNED
// uint8_t udi_hid_exk_report_set;

bool udi_hid_exk_b_report_valid;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_exk_report[UDI_HID_EXK_REPORT_SIZE];

static bool udi_hid_exk_b_report_trans_ongoing;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_exk_report_trans[UDI_HID_EXK_REPORT_SIZE];

COMPILER_WORD_ALIGNED
UDC_DESC_STORAGE udi_hid_exk_report_desc_t udi_hid_exk_report_desc = {{
    // clang-format off
    0x05, 0x01,              // Usage Page (Generic Desktop)
    0x09, 0x80,              // Usage (System Control)
    0xA1, 0x01,              // Collection (Application)
    0x85, REPORT_ID_SYSTEM,  //   Report ID
    0x19, 0x01,              //   Usage Minimum (Pointer)
    0x2A, 0xB7, 0x00,        //   Usage Maximum (System Display LCD Autoscale)
    0x15, 0x01,              //   Logical Minimum
    0x26, 0xB7, 0x00,        //   Logical Maximum
    0x95, 0x01,              //   Report Count (1)
    0x75, 0x10,              //   Report Size (16)
    0x81, 0x00,              //   Input (Data, Array, Absolute)
    0xC0,                    // End Collection

    0x05, 0x0C,                // Usage Page (Consumer)
    0x09, 0x01,                // Usage (Consumer Control)
    0xA1, 0x01,                // Collection (Application)
    0x85, REPORT_ID_CONSUMER,  //   Report ID
    0x19, 0x01,                //   Usage Minimum (Consumer Control)
    0x2A, 0xA0, 0x02,          //   Usage Maximum (AC Desktop Show All Applications)
    0x15, 0x01,                //   Logical Minimum
    0x26, 0xA0, 0x02,          //   Logical Maximum
    0x95, 0x01,                //   Report Count (1)
    0x75, 0x10,                //   Report Size (16)
    0x81, 0x00,                //   Input (Data, Array, Absolute)
    0xC0                       // End Collection
    //clang-format on
}};

static void udi_hid_exk_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep);

bool udi_hid_exk_enable(void) {
    // Initialize internal values
    udi_hid_exk_rate                   = 0;
    udi_hid_exk_protocol               = 0;
    udi_hid_exk_b_report_trans_ongoing = false;
    memset(udi_hid_exk_report, 0, UDI_HID_EXK_REPORT_SIZE);
    udi_hid_exk_b_report_valid = false;
    return UDI_HID_EXK_ENABLE_EXT();
}

void udi_hid_exk_disable(void) { UDI_HID_EXK_DISABLE_EXT(); }

bool udi_hid_exk_setup(void) { return udi_hid_setup(&udi_hid_exk_rate, &udi_hid_exk_protocol, (uint8_t *)&udi_hid_exk_report_desc, NULL); }

uint8_t udi_hid_exk_getsetting(void) { return 0; }

bool udi_hid_exk_send_report(void) {
    if (!main_b_exk_enable) {
        return false;
    }

    if (udi_hid_exk_b_report_trans_ongoing) {
        return false;
    }

    memcpy(udi_hid_exk_report_trans, udi_hid_exk_report, UDI_HID_EXK_REPORT_SIZE);
    udi_hid_exk_b_report_valid         = false;
    udi_hid_exk_b_report_trans_ongoing = udd_ep_run(UDI_HID_EXK_EP_IN | USB_EP_DIR_IN, false, udi_hid_exk_report_trans, UDI_HID_EXK_REPORT_SIZE, udi_hid_exk_report_sent);

    return udi_hid_exk_b_report_trans_ongoing;
}

static void udi_hid_exk_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep) {
    UNUSED(status);
    UNUSED(nb_sent);
    UNUSED(ep);
    udi_hid_exk_b_report_trans_ongoing = false;
    if (udi_hid_exk_b_report_valid) {
        udi_hid_exk_send_report();
    }
}

#endif  // EXTRAKEY_ENABLE

//********************************************************************************************
// MOU Mouse
//********************************************************************************************
#ifdef MOUSE_ENABLE

bool    udi_hid_mou_enable(void);
void    udi_hid_mou_disable(void);
bool    udi_hid_mou_setup(void);
uint8_t udi_hid_mou_getsetting(void);

UDC_DESC_STORAGE udi_api_t udi_api_hid_mou = {
    .enable     = (bool (*)(void))udi_hid_mou_enable,
    .disable    = (void (*)(void))udi_hid_mou_disable,
    .setup      = (bool (*)(void))udi_hid_mou_setup,
    .getsetting = (uint8_t(*)(void))udi_hid_mou_getsetting,
    .sof_notify = NULL,
};

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_mou_rate;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_mou_protocol;

// COMPILER_WORD_ALIGNED
// uint8_t udi_hid_mou_report_set; //No set report

bool udi_hid_mou_b_report_valid;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_mou_report[UDI_HID_MOU_REPORT_SIZE];

static bool udi_hid_mou_b_report_trans_ongoing;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_mou_report_trans[UDI_HID_MOU_REPORT_SIZE];

COMPILER_WORD_ALIGNED
UDC_DESC_STORAGE udi_hid_mou_report_desc_t udi_hid_mou_report_desc = {{
    0x05, 0x01,  // Usage Page (Generic Desktop)
    0x09, 0x02,  // Usage (Mouse)
    0xA1, 0x01,  // Collection (Application)
    0x09, 0x01,  //   Usage (Pointer)
    0xA1, 0x00,  //   Collection (Physical)
    // Buttons (5 bits)
    0x05, 0x09,  //     Usage Page (Button)
    0x19, 0x01,  //     Usage Minimum (Button 1)
    0x29, 0x05,  //     Usage Maximun (Button 5)
    0x15, 0x00,  //     Logical Minimum (0)
    0x25, 0x01,  //     Logical Maximum (1)
    0x95, 0x05,  //     Report Count (5)
    0x75, 0x01,  //     Report Size (1)
    0x81, 0x02,  //     Input (Data, Variable, Absolute)
    // Button padding (3 bits)
    0x95, 0x01,  //     Report Count (1)
    0x75, 0x03,  //     Report Size (3)
    0x81, 0x01,  //     Input (Constant)

    // X/Y position (2 bytes)
    0x05, 0x01,  //     Usage Page (Generic Desktop)
    0x09, 0x30,  //     Usage (X)
    0x09, 0x31,  //     Usage (Y)
    0x15, 0x81,  //     Logical Minimum (-127)
    0x25, 0x7F,  //     Logical Maximum (127)
    0x95, 0x02,  //     Report Count (2)
    0x75, 0x08,  //     Report Size (8)
    0x81, 0x06,  //     Input (Data, Variable, Relative)

    // Vertical wheel (1 byte)
    0x09, 0x38,  //     Usage (Wheel)
    0x15, 0x81,  //     Logical Minimum (-127)
    0x25, 0x7F,  //     Logical Maximum (127)
    0x95, 0x01,  //     Report Count (1)
    0x75, 0x08,  //     Report Size (8)
    0x81, 0x06,  //     Input (Data, Variable, Relative)

    // Horizontal wheel (1 byte)
    0x05, 0x0C,        //     Usage Page (Consumer)
    0x0A, 0x38, 0x02,  //     Usage (AC Pan)
    0x15, 0x81,        //     Logical Minimum (-127)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x95, 0x01,        //     Report Count (1)
    0x75, 0x08,        //     Report Size (8)
    0x81, 0x06,        //     Input (Data, Variable, Relative)
    0xC0,              //   End Collection
    0xC0               // End Collection
}};

static void udi_hid_mou_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep);

bool udi_hid_mou_enable(void) {
    // Initialize internal values
    udi_hid_mou_rate                   = 0;
    udi_hid_mou_protocol               = 0;
    udi_hid_mou_b_report_trans_ongoing = false;
    memset(udi_hid_mou_report, 0, UDI_HID_MOU_REPORT_SIZE);
    udi_hid_mou_b_report_valid = false;
    return UDI_HID_MOU_ENABLE_EXT();
}

void udi_hid_mou_disable(void) { UDI_HID_MOU_DISABLE_EXT(); }

bool udi_hid_mou_setup(void) { return udi_hid_setup(&udi_hid_mou_rate, &udi_hid_mou_protocol, (uint8_t *)&udi_hid_mou_report_desc, NULL); }

uint8_t udi_hid_mou_getsetting(void) { return 0; }

bool udi_hid_mou_send_report(void) {
    if (!main_b_mou_enable) {
        return false;
    }

    if (udi_hid_mou_b_report_trans_ongoing) {
        return false;
    }

    memcpy(udi_hid_mou_report_trans, udi_hid_mou_report, UDI_HID_MOU_REPORT_SIZE);
    udi_hid_mou_b_report_valid         = false;
    udi_hid_mou_b_report_trans_ongoing = udd_ep_run(UDI_HID_MOU_EP_IN | USB_EP_DIR_IN, false, udi_hid_mou_report_trans, UDI_HID_MOU_REPORT_SIZE, udi_hid_mou_report_sent);

    return udi_hid_mou_b_report_trans_ongoing;
}

static void udi_hid_mou_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep) {
    UNUSED(status);
    UNUSED(nb_sent);
    UNUSED(ep);
    udi_hid_mou_b_report_trans_ongoing = false;
    if (udi_hid_mou_b_report_valid) {
        udi_hid_mou_send_report();
    }
}

#endif  // MOUSE_ENABLE

//********************************************************************************************
// RAW
//********************************************************************************************
#ifdef RAW_ENABLE

bool    udi_hid_raw_enable(void);
void    udi_hid_raw_disable(void);
bool    udi_hid_raw_setup(void);
uint8_t udi_hid_raw_getsetting(void);

UDC_DESC_STORAGE udi_api_t udi_api_hid_raw = {
    .enable     = (bool (*)(void))udi_hid_raw_enable,
    .disable    = (void (*)(void))udi_hid_raw_disable,
    .setup      = (bool (*)(void))udi_hid_raw_setup,
    .getsetting = (uint8_t(*)(void))udi_hid_raw_getsetting,
    .sof_notify = NULL,
};

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_raw_rate;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_raw_protocol;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_raw_report_set[UDI_HID_RAW_REPORT_SIZE];

static bool udi_hid_raw_b_report_valid;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_raw_report[UDI_HID_RAW_REPORT_SIZE];

static bool udi_hid_raw_b_report_trans_ongoing;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_raw_report_trans[UDI_HID_RAW_REPORT_SIZE];

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_raw_report_recv[UDI_HID_RAW_REPORT_SIZE];

COMPILER_WORD_ALIGNED
UDC_DESC_STORAGE udi_hid_raw_report_desc_t udi_hid_raw_report_desc = {{
    0x06, HID_VALUE_16(RAW_USAGE_PAGE),  // Usage Page (Vendor Defined)
    0x09, RAW_USAGE_ID,                  // Usage (Vendor Defined)
    0xA1, 0x01,                          // Collection (Application)
    0x75, 0x08,                          //   Report Size (8)
    0x15, 0x00,                          //   Logical Minimum (0)
    0x25, 0xFF,                          //   Logical Maximum (255)
    // Data to host
    0x09, 0x62,        //   Usage (Vendor Defined)
    0x95, RAW_EPSIZE,  //   Report Count
    0x81, 0x02,        //   Input (Data, Variable, Absolute)
    // Data from host
    0x09, 0x63,        //   Usage (Vendor Defined)
    0x95, RAW_EPSIZE,  //   Report Count
    0x91, 0x02,        //   Output (Data, Variable, Absolute)
    0xC0               // End Collection
}};

static bool udi_hid_raw_setreport(void);
static void udi_hid_raw_setreport_valid(void);

static void udi_hid_raw_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep);
static void udi_hid_raw_report_rcvd(udd_ep_status_t status, iram_size_t nb_rcvd, udd_ep_id_t ep);

bool udi_hid_raw_enable(void) {
    // Initialize internal values
    udi_hid_raw_rate                   = 0;
    udi_hid_raw_protocol               = 0;
    udi_hid_raw_b_report_trans_ongoing = false;
    memset(udi_hid_raw_report, 0, UDI_HID_RAW_REPORT_SIZE);
    udi_hid_raw_b_report_valid = false;
    return UDI_HID_RAW_ENABLE_EXT();
}

void udi_hid_raw_disable(void) { UDI_HID_RAW_DISABLE_EXT(); }

bool udi_hid_raw_setup(void) { return udi_hid_setup(&udi_hid_raw_rate, &udi_hid_raw_protocol, (uint8_t *)&udi_hid_raw_report_desc, udi_hid_raw_setreport); }

uint8_t udi_hid_raw_getsetting(void) { return 0; }

static bool udi_hid_raw_setreport(void) {
    if ((USB_HID_REPORT_TYPE_OUTPUT == (udd_g_ctrlreq.req.wValue >> 8)) && (0 == (0xFF & udd_g_ctrlreq.req.wValue)) && (UDI_HID_RAW_REPORT_SIZE == udd_g_ctrlreq.req.wLength)) {
        // Report OUT type on report ID 0 from USB Host
        udd_g_ctrlreq.payload      = udi_hid_raw_report_set;
        udd_g_ctrlreq.callback     = udi_hid_raw_setreport_valid;  // must call routine to transform setreport to LED state
        udd_g_ctrlreq.payload_size = UDI_HID_RAW_REPORT_SIZE;
        return true;
    }
    return false;
}

bool udi_hid_raw_send_report(void) {
    if (!main_b_raw_enable) {
        return false;
    }

    if (udi_hid_raw_b_report_trans_ongoing) {
        return false;
    }

    memcpy(udi_hid_raw_report_trans, udi_hid_raw_report, UDI_HID_RAW_REPORT_SIZE);
    udi_hid_raw_b_report_valid         = false;
    udi_hid_raw_b_report_trans_ongoing = udd_ep_run(UDI_HID_RAW_EP_IN | USB_EP_DIR_IN, false, udi_hid_raw_report_trans, UDI_HID_RAW_REPORT_SIZE, udi_hid_raw_report_sent);

    return udi_hid_raw_b_report_trans_ongoing;
}

static void udi_hid_raw_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep) {
    UNUSED(status);
    UNUSED(nb_sent);
    UNUSED(ep);
    udi_hid_raw_b_report_trans_ongoing = false;
    if (udi_hid_raw_b_report_valid) {
        udi_hid_raw_send_report();
    }
}

static void udi_hid_raw_setreport_valid(void) {}

void raw_hid_send(uint8_t *data, uint8_t length) {
    if (main_b_raw_enable && !udi_hid_raw_b_report_trans_ongoing && length == UDI_HID_RAW_REPORT_SIZE) {
        memcpy(udi_hid_raw_report, data, UDI_HID_RAW_REPORT_SIZE);
        udi_hid_raw_send_report();
    }
}

bool udi_hid_raw_receive_report(void) {
    if (!main_b_raw_enable) {
        return false;
    }

    return udd_ep_run(UDI_HID_RAW_EP_OUT | USB_EP_DIR_OUT, false, udi_hid_raw_report_recv, UDI_HID_RAW_REPORT_SIZE, udi_hid_raw_report_rcvd);
}

static void udi_hid_raw_report_rcvd(udd_ep_status_t status, iram_size_t nb_rcvd, udd_ep_id_t ep) {
    UNUSED(ep);

    if (status == UDD_EP_TRANSFER_OK && nb_rcvd == UDI_HID_RAW_REPORT_SIZE) {
        UDI_HID_RAW_RECEIVE(udi_hid_raw_report_recv, UDI_HID_RAW_REPORT_SIZE);
    }
}

#endif // RAW_ENABLE

//********************************************************************************************
// CON
//********************************************************************************************
#ifdef CONSOLE_ENABLE

bool    udi_hid_con_enable(void);
void    udi_hid_con_disable(void);
bool    udi_hid_con_setup(void);
uint8_t udi_hid_con_getsetting(void);

UDC_DESC_STORAGE udi_api_t udi_api_hid_con = {
    .enable     = (bool (*)(void))udi_hid_con_enable,
    .disable    = (void (*)(void))udi_hid_con_disable,
    .setup      = (bool (*)(void))udi_hid_con_setup,
    .getsetting = (uint8_t(*)(void))udi_hid_con_getsetting,
    .sof_notify = NULL,
};

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_con_rate;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_con_protocol;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_con_report_set[UDI_HID_CON_REPORT_SIZE];

bool udi_hid_con_b_report_valid;

COMPILER_WORD_ALIGNED
uint8_t udi_hid_con_report[UDI_HID_CON_REPORT_SIZE];

volatile bool udi_hid_con_b_report_trans_ongoing;

COMPILER_WORD_ALIGNED
static uint8_t udi_hid_con_report_trans[UDI_HID_CON_REPORT_SIZE];

COMPILER_WORD_ALIGNED
UDC_DESC_STORAGE udi_hid_con_report_desc_t udi_hid_con_report_desc = {{
    0x06, 0x31, 0xFF,  // Usage Page (Vendor Defined - PJRC Teensy compatible)
    0x09, 0x74,        // Usage (Vendor Defined - PJRC Teensy compatible)
    0xA1, 0x01,        // Collection (Application)
    // Data to host
    0x09, 0x75,            //   Usage (Vendor Defined)
    0x15, 0x00,            //   Logical Minimum (0x00)
    0x26, 0xFF, 0x00,      //   Logical Maximum (0x00FF)
    0x95, CONSOLE_EPSIZE,  //   Report Count
    0x75, 0x08,            //   Report Size (8)
    0x81, 0x02,            //   Input (Data, Variable, Absolute)
    // Data from host
    0x09, 0x76,            //   Usage (Vendor Defined)
    0x15, 0x00,            //   Logical Minimum (0x00)
    0x26, 0xFF, 0x00,      //   Logical Maximum (0x00FF)
    0x95, CONSOLE_EPSIZE,  //   Report Count
    0x75, 0x08,            //   Report Size (8)
    0x91, 0x02,            //   Output (Data)
    0xC0                   // End Collection
}};

static bool udi_hid_con_setreport(void);
static void udi_hid_con_setreport_valid(void);

static void udi_hid_con_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep);

bool udi_hid_con_enable(void) {
    // Initialize internal values
    udi_hid_con_rate                   = 0;
    udi_hid_con_protocol               = 0;
    udi_hid_con_b_report_trans_ongoing = false;
    memset(udi_hid_con_report, 0, UDI_HID_CON_REPORT_SIZE);
    udi_hid_con_b_report_valid = false;
    return UDI_HID_CON_ENABLE_EXT();
}

void udi_hid_con_disable(void) { UDI_HID_CON_DISABLE_EXT(); }

bool udi_hid_con_setup(void) { return udi_hid_setup(&udi_hid_con_rate, &udi_hid_con_protocol, (uint8_t *)&udi_hid_con_report_desc, udi_hid_con_setreport); }

uint8_t udi_hid_con_getsetting(void) { return 0; }

static bool udi_hid_con_setreport(void) {
    if ((USB_HID_REPORT_TYPE_OUTPUT == (udd_g_ctrlreq.req.wValue >> 8)) && (0 == (0xFF & udd_g_ctrlreq.req.wValue)) && (UDI_HID_CON_REPORT_SIZE == udd_g_ctrlreq.req.wLength)) {
        udd_g_ctrlreq.payload      = udi_hid_con_report_set;
        udd_g_ctrlreq.callback     = udi_hid_con_setreport_valid;
        udd_g_ctrlreq.payload_size = UDI_HID_CON_REPORT_SIZE;
        return true;
    }
    return false;
}

bool udi_hid_con_send_report(void) {
    if (!main_b_con_enable) {
        return false;
    }

    if (udi_hid_con_b_report_trans_ongoing) {
        return false;
    }

    memcpy(udi_hid_con_report_trans, udi_hid_con_report, UDI_HID_CON_REPORT_SIZE);
    udi_hid_con_b_report_valid         = false;
    udi_hid_con_b_report_trans_ongoing = udd_ep_run(UDI_HID_CON_EP_IN | USB_EP_DIR_IN, false, udi_hid_con_report_trans, UDI_HID_CON_REPORT_SIZE, udi_hid_con_report_sent);

    return udi_hid_con_b_report_trans_ongoing;
}

static void udi_hid_con_report_sent(udd_ep_status_t status, iram_size_t nb_sent, udd_ep_id_t ep) {
    UNUSED(status);
    UNUSED(nb_sent);
    UNUSED(ep);
    udi_hid_con_b_report_trans_ongoing = false;
    if (udi_hid_con_b_report_valid) {
        udi_hid_con_send_report();
    }
}

static void udi_hid_con_setreport_valid(void) {}

#endif  // CONSOLE_ENABLE
