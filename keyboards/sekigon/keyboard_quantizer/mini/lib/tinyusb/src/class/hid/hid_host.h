/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#ifndef _TUSB_HID_HOST_H_
#define _TUSB_HID_HOST_H_

#include "hid.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// Class Driver Configuration
//--------------------------------------------------------------------+

// TODO Highspeed interrupt can be up to 512 bytes
#ifndef CFG_TUH_HID_EPIN_BUFSIZE
#define CFG_TUH_HID_EPIN_BUFSIZE 64
#endif

#ifndef CFG_TUH_HID_EPOUT_BUFSIZE
#define CFG_TUH_HID_EPOUT_BUFSIZE 64
#endif


typedef struct
{
  uint8_t  report_id;
  uint8_t  usage;
  uint16_t usage_page;

  // TODO still use the endpoint size for now
//  uint8_t in_len;      // length of IN report
//  uint8_t out_len;     // length of OUT report
} tuh_hid_report_info_t;

//--------------------------------------------------------------------+
// Interface API
//--------------------------------------------------------------------+

// Get the number of HID instances
uint8_t tuh_hid_instance_count(uint8_t dev_addr);

// Check if HID instance is mounted
bool tuh_hid_mounted(uint8_t dev_addr, uint8_t instance);

// Get interface supported protocol (bInterfaceProtocol) check out hid_interface_protocol_enum_t for possible values
uint8_t tuh_hid_interface_protocol(uint8_t dev_addr, uint8_t instance);

// Parse report descriptor into array of report_info struct and return number of reports.
// For complicated report, application should write its own parser.
uint8_t tuh_hid_parse_report_descriptor(tuh_hid_report_info_t* reports_info_arr, uint8_t arr_count, uint8_t const* desc_report, uint16_t desc_len) TU_ATTR_UNUSED;

//--------------------------------------------------------------------+
// Control Endpoint API
//--------------------------------------------------------------------+

// Get current protocol: HID_PROTOCOL_BOOT (0) or HID_PROTOCOL_REPORT (1)
// Note: Device will be initialized in Boot protocol for simplicity.
//       Application can use set_protocol() to switch back to Report protocol.
uint8_t tuh_hid_get_protocol(uint8_t dev_addr, uint8_t instance);

// Set protocol to HID_PROTOCOL_BOOT (0) or HID_PROTOCOL_REPORT (1)
// This function is only supported by Boot interface (tuh_n_hid_interface_protocol() != NONE)
bool tuh_hid_set_protocol(uint8_t dev_addr, uint8_t instance, uint8_t protocol);

// Set Report using control endpoint
// report_type is either Input, Output or Feature, (value from hid_report_type_t)
bool tuh_hid_set_report(uint8_t dev_addr, uint8_t instance, uint8_t report_id, uint8_t report_type, void* report, uint16_t len);

//--------------------------------------------------------------------+
// Interrupt Endpoint API
//--------------------------------------------------------------------+

// Check if the interface is ready to use
//bool tuh_n_hid_n_ready(uint8_t dev_addr, uint8_t instance);

// Try to receive next report on Interrupt Endpoint. Immediately return
// - true If succeeded, tuh_hid_report_received_cb() callback will be invoked when report is available
// - false if failed to queue the transfer e.g endpoint is busy
bool tuh_hid_receive_report(uint8_t dev_addr, uint8_t instance);

// Send report using interrupt endpoint
// If report_id > 0 (composite), it will be sent as 1st byte, then report contents. Otherwise only report content is sent.
//void tuh_hid_send_report(uint8_t dev_addr, uint8_t instance, uint8_t report_id, uint8_t const* report, uint16_t len);

//--------------------------------------------------------------------+
// Callbacks (Weak is optional)
//--------------------------------------------------------------------+

// Invoked when device with hid interface is mounted
// Report descriptor is also available for use. tuh_hid_parse_report_descriptor()
// can be used to parse common/simple enough descriptor.
// Note: if report descriptor length > CFG_TUH_ENUMERATION_BUFSIZE, it will be skipped
// therefore report_desc = NULL, desc_len = 0
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report_desc, uint16_t desc_len);

// Invoked when device with hid interface is un-mounted
TU_ATTR_WEAK void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance);

// Invoked when received report from device via interrupt endpoint
// Note: if there is report ID (composite), it is 1st byte of report
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len);

// Invoked when sent report to device successfully via interrupt endpoint
TU_ATTR_WEAK void tuh_hid_report_sent_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len);

// Invoked when Sent Report to device via either control endpoint
// len = 0 indicate there is error in the transfer e.g stalled response
TU_ATTR_WEAK void tuh_hid_set_report_complete_cb(uint8_t dev_addr, uint8_t instance, uint8_t report_id, uint8_t report_type, uint16_t len);

// Invoked when Set Protocol request is complete
TU_ATTR_WEAK void tuh_hid_set_protocol_complete_cb(uint8_t dev_addr, uint8_t instance, uint8_t protocol);

//--------------------------------------------------------------------+
// Internal Class Driver API
//--------------------------------------------------------------------+
void hidh_init       (void);
bool hidh_open       (uint8_t rhport, uint8_t dev_addr, tusb_desc_interface_t const *desc_itf, uint16_t max_len);
bool hidh_set_config (uint8_t dev_addr, uint8_t itf_num);
bool hidh_xfer_cb    (uint8_t dev_addr, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes);
void hidh_close      (uint8_t dev_addr);

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_HID_HOST_H_ */
