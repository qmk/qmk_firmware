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

#ifndef _TUSB_USBH_H_
#define _TUSB_USBH_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "common/tusb_common.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+

// forward declaration
struct tuh_xfer_s;
typedef struct tuh_xfer_s tuh_xfer_t;

typedef void (*tuh_xfer_cb_t)(tuh_xfer_t* xfer);

// Note1: layout and order of this will be changed in near future
// it is advised to initialize it using member name
// Note2: not all field is available/meaningful in callback,
// some info is not saved by usbh to save SRAM
struct tuh_xfer_s
{
  uint8_t daddr;
  uint8_t ep_addr;
  uint8_t TU_RESERVED;      // reserved
  xfer_result_t result;

  uint32_t actual_len;      // excluding setup packet

  union
  {
    tusb_control_request_t const* setup; // setup packet pointer if control transfer
    uint32_t buflen;                     // expected length if not control transfer (not available in callback)
  };

  uint8_t* buffer;           // not available in callback if not control transfer
  tuh_xfer_cb_t complete_cb;
  uintptr_t user_data;

  // uint32_t timeout_ms;    // place holder, not supported yet
};

// ConfigID for tuh_config()
enum
{
  TUH_CFGID_RPI_PIO_USB_CONFIGURATION = OPT_MCU_RP2040 << 8 // cfg_param: pio_usb_configuration_t
};

//--------------------------------------------------------------------+
// APPLICATION CALLBACK
//--------------------------------------------------------------------+

//TU_ATTR_WEAK uint8_t tuh_attach_cb (tusb_desc_device_t const *desc_device);

// Invoked when a device is mounted (configured)
TU_ATTR_WEAK void tuh_mount_cb (uint8_t daddr);

// Invoked when a device failed to mount during enumeration process
// TU_ATTR_WEAK void tuh_mount_failed_cb (uint8_t daddr);

/// Invoked when a device is unmounted (detached)
TU_ATTR_WEAK void tuh_umount_cb(uint8_t daddr);

//--------------------------------------------------------------------+
// APPLICATION API
//--------------------------------------------------------------------+

// Configure host stack behavior with dynamic or port-specific parameters.
// Should be called before tuh_init()
// - cfg_id   : configure ID (TBD)
// - cfg_param: configure data, structure depends on the ID
bool tuh_configure(uint8_t controller_id, uint32_t cfg_id, const void* cfg_param);

// Init host stack
bool tuh_init(uint8_t controller_id);

// Check if host stack is already initialized
bool tuh_inited(void);

// Task function should be called in main/rtos loop, extended version of tuh_task()
// - timeout_ms: millisecond to wait, zero = no wait, 0xFFFFFFFF = wait forever
// - in_isr: if function is called in ISR
void tuh_task_ext(uint32_t timeout_ms, bool in_isr);

// Task function should be called in main/rtos loop
TU_ATTR_ALWAYS_INLINE static inline
void tuh_task(void)
{
  tuh_task_ext(UINT32_MAX, false);
}

#ifndef _TUSB_HCD_H_
extern void hcd_int_handler(uint8_t rhport);
#endif

// Interrupt handler, name alias to HCD
#define tuh_int_handler   hcd_int_handler

bool tuh_vid_pid_get(uint8_t daddr, uint16_t* vid, uint16_t* pid);

tusb_speed_t tuh_speed_get(uint8_t daddr);

// Check if device is connected and configured
bool tuh_mounted(uint8_t daddr);

// Check if device is suspended
TU_ATTR_ALWAYS_INLINE static inline
bool tuh_suspended(uint8_t daddr)
{
  // TODO implement suspend & resume on host
  (void) daddr;
  return false;
}

// Check if device is ready to communicate with
TU_ATTR_ALWAYS_INLINE static inline
bool tuh_ready(uint8_t daddr)
{
  return tuh_mounted(daddr) && !tuh_suspended(daddr);
}

//--------------------------------------------------------------------+
// Transfer API
//--------------------------------------------------------------------+

// Submit a control transfer
//  - async: complete callback invoked when finished.
//  - sync : blocking if complete callback is NULL.
bool tuh_control_xfer(tuh_xfer_t* xfer);

// Submit a bulk/interrupt transfer
//  - async: complete callback invoked when finished.
//  - sync : blocking if complete callback is NULL.
bool tuh_edpt_xfer(tuh_xfer_t* xfer);

// Open an non-control endpoint
bool tuh_edpt_open(uint8_t dev_addr, tusb_desc_endpoint_t const * desc_ep);

// Set Configuration (control transfer)
// config_num = 0 will un-configure device. Note: config_num = config_descriptor_index + 1
// true on success, false if there is on-going control transfer or incorrect parameters
bool tuh_configuration_set(uint8_t daddr, uint8_t config_num,
                           tuh_xfer_cb_t complete_cb, uintptr_t user_data);

//--------------------------------------------------------------------+
// Descriptors Asynchronous (non-blocking)
//--------------------------------------------------------------------+

// Get an descriptor (control transfer)
// true on success, false if there is on-going control transfer or incorrect parameters
bool tuh_descriptor_get(uint8_t daddr, uint8_t type, uint8_t index, void* buffer, uint16_t len,
                        tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Get device descriptor (control transfer)
// true on success, false if there is on-going control transfer or incorrect parameters
bool tuh_descriptor_get_device(uint8_t daddr, void* buffer, uint16_t len,
                               tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Get configuration descriptor (control transfer)
// true on success, false if there is on-going control transfer or incorrect parameters
bool tuh_descriptor_get_configuration(uint8_t daddr, uint8_t index, void* buffer, uint16_t len,
                                      tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Get HID report descriptor (control transfer)
// true on success, false if there is on-going control transfer or incorrect parameters
bool tuh_descriptor_get_hid_report(uint8_t daddr, uint8_t itf_num, uint8_t desc_type, uint8_t index, void* buffer, uint16_t len,
                                   tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Get string descriptor (control transfer)
// true on success, false if there is on-going control transfer or incorrect parameters
// Blocking if complete callback is NULL, in this case 'user_data' must contain xfer_result_t variable
bool tuh_descriptor_get_string(uint8_t daddr, uint8_t index, uint16_t language_id, void* buffer, uint16_t len,
                               tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Get manufacturer string descriptor (control transfer)
// true on success, false if there is on-going control transfer or incorrect parameters
bool tuh_descriptor_get_manufacturer_string(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len,
                                            tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Get product string descriptor (control transfer)
// true on success, false if there is on-going control transfer or incorrect parameters
bool tuh_descriptor_get_product_string(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len,
                                       tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Get serial string descriptor (control transfer)
// true on success, false if there is on-going control transfer or incorrect parameters
bool tuh_descriptor_get_serial_string(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len,
                                      tuh_xfer_cb_t complete_cb, uintptr_t user_data);

//--------------------------------------------------------------------+
// Descriptors Synchronous (blocking)
//--------------------------------------------------------------------+

// Sync (blocking) version of tuh_descriptor_get()
// return transfer result
uint8_t tuh_descriptor_get_sync(uint8_t daddr, uint8_t type, uint8_t index, void* buffer, uint16_t len);

// Sync (blocking) version of tuh_descriptor_get_device()
// return transfer result
uint8_t tuh_descriptor_get_device_sync(uint8_t daddr, void* buffer, uint16_t len);

// Sync (blocking) version of tuh_descriptor_get_configuration()
// return transfer result
uint8_t tuh_descriptor_get_configuration_sync(uint8_t daddr, uint8_t index, void* buffer, uint16_t len);

// Sync (blocking) version of tuh_descriptor_get_hid_report()
// return transfer result
uint8_t tuh_descriptor_get_hid_report_sync(uint8_t daddr, uint8_t itf_num, uint8_t desc_type, uint8_t index, void* buffer, uint16_t len);

// Sync (blocking) version of tuh_descriptor_get_string()
// return transfer result
uint8_t tuh_descriptor_get_string_sync(uint8_t daddr, uint8_t index, uint16_t language_id, void* buffer, uint16_t len);

// Sync (blocking) version of tuh_descriptor_get_manufacturer_string()
// return transfer result
uint8_t tuh_descriptor_get_manufacturer_string_sync(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len);

// Sync (blocking) version of tuh_descriptor_get_product_string()
// return transfer result
uint8_t tuh_descriptor_get_product_string_sync(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len);

// Sync (blocking) version of tuh_descriptor_get_serial_string()
// return transfer result
uint8_t tuh_descriptor_get_serial_string_sync(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len);

#ifdef __cplusplus
 }
#endif

#endif
