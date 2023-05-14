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

/** \ingroup group_class
 *  \defgroup ClassDriver_Hub Hub (Host only)
 *  \details  Like most PC's OS, Hub support is completely hidden from Application. In fact, application cannot determine whether
 *            a device is mounted directly via roothub or via a hub's port. All Hub-related procedures are performed and managed
 *            by tinyusb stack. Unless you are trying to develop the stack itself, there are nothing else can be used by Application.
 *  \note     Due to my laziness, only 1-level of Hub is supported. In other way, the stack cannot mount a hub via another hub.
 *  @{
 */

#ifndef _TUSB_HUB_H_
#define _TUSB_HUB_H_

#include "common/tusb_common.h"

#ifdef __cplusplus
 extern "C" {
#endif

//D1...D0: Logical Power Switching Mode
//00:  Ganged power switching (all ports’power at
//once)
//01:  Individual port power switching
//1X:  Reserved. Used only on 1.0 compliant hubs
//that implement no power switching
//D2:  Identifies a Compound Device
//0: Hub is not part of a compound device.
//1: Hub is part of a compound device.
//D4...D3: Over-current Protection Mode
//00: Global Over-current Protection. The hub
//reports over-current as a summation of all
//ports’current draw, without a breakdown of
//individual port over-current status.
//01: Individual Port Over-current Protection. The
//hub reports over-current on a per-port basis.
//Each port has an over-current status.
//1X: No Over-current Protection. This option is
//allowed only for bus-powered hubs that do not
//implement over-current protection.
//
//D6...D5: TT Think TIme
//00:  TT requires at most 8 FS bit times of inter
//transaction gap on a full-/low-speed
//downstream bus.
//01:  TT requires at most 16 FS bit times.
//10:  TT requires at most 24 FS bit times.
//11:  TT requires at most 32 FS bit times.
//D7: Port Indicators Supported
//0:  Port Indicators are not supported on its
//downstream facing ports and the
//PORT_INDICATOR request has no effect.
//1:  Port Indicators are supported on its
//downstream facing ports and the
//PORT_INDICATOR request controls the
//indicators. See Section 11.5.3.
//D15...D8: Reserved

typedef struct TU_ATTR_PACKED{
  uint8_t  bLength           ; ///< Size of descriptor
  uint8_t  bDescriptorType   ; ///< Other_speed_Configuration Type
  uint8_t  bNbrPorts;
  uint16_t wHubCharacteristics;
  uint8_t  bPwrOn2PwrGood;
  uint8_t  bHubContrCurrent;
  uint8_t  DeviceRemovable; // bitmap each bit for a port (from bit1)
  uint8_t  PortPwrCtrlMask; // just for compatibility, should be 0xff
} descriptor_hub_desc_t;

TU_VERIFY_STATIC( sizeof(descriptor_hub_desc_t) == 9, "size is not correct");

enum {
  HUB_REQUEST_GET_STATUS      = 0  ,
  HUB_REQUEST_CLEAR_FEATURE   = 1  ,

  HUB_REQUEST_SET_FEATURE     = 3  ,

  HUB_REQUEST_GET_DESCRIPTOR  = 6  ,
  HUB_REQUEST_SET_DESCRIPTOR  = 7  ,
  HUB_REQUEST_CLEAR_TT_BUFFER = 8  ,
  HUB_REQUEST_RESET_TT        = 9  ,
  HUB_REQUEST_GET_TT_STATE    = 10 ,
  HUB_REQUEST_STOP_TT         = 11
};

enum {
  HUB_FEATURE_HUB_LOCAL_POWER_CHANGE = 0,
  HUB_FEATURE_HUB_OVER_CURRENT_CHANGE
};

enum{
  HUB_FEATURE_PORT_CONNECTION          = 0,
  HUB_FEATURE_PORT_ENABLE              = 1,
  HUB_FEATURE_PORT_SUSPEND             = 2,
  HUB_FEATURE_PORT_OVER_CURRENT        = 3,
  HUB_FEATURE_PORT_RESET               = 4,

  HUB_FEATURE_PORT_POWER               = 8,
  HUB_FEATURE_PORT_LOW_SPEED           = 9,

  HUB_FEATURE_PORT_CONNECTION_CHANGE   = 16,
  HUB_FEATURE_PORT_ENABLE_CHANGE       = 17,
  HUB_FEATURE_PORT_SUSPEND_CHANGE      = 18,
  HUB_FEATURE_PORT_OVER_CURRENT_CHANGE = 19,
  HUB_FEATURE_PORT_RESET_CHANGE        = 20,
  HUB_FEATURE_PORT_TEST                = 21,
  HUB_FEATURE_PORT_INDICATOR           = 22
};

// data in response of HUB_REQUEST_GET_STATUS, wIndex = 0 (hub)
typedef struct {
  union{
    struct TU_ATTR_PACKED {
      uint16_t local_power_source : 1;
      uint16_t over_current       : 1;
      uint16_t : 14;
    };

    uint16_t value;
  } status, change;
} hub_status_response_t;

TU_VERIFY_STATIC( sizeof(hub_status_response_t) == 4, "size is not correct");

// data in response of HUB_REQUEST_GET_STATUS, wIndex = Port num
typedef struct {
  union {
    struct TU_ATTR_PACKED {
      uint16_t connection             : 1;
      uint16_t port_enable            : 1;
      uint16_t suspend                : 1;
      uint16_t over_current           : 1;
      uint16_t reset                  : 1;

      uint16_t                        : 3;
      uint16_t port_power             : 1;
      uint16_t low_speed              : 1;
      uint16_t high_speed             : 1;
      uint16_t port_test_mode         : 1;
      uint16_t port_indicator_control : 1;
      uint16_t TU_RESERVED            : 3;
    };

    uint16_t value;
  } status, change;
} hub_port_status_response_t;

TU_VERIFY_STATIC( sizeof(hub_port_status_response_t) == 4, "size is not correct");

// Clear feature
bool hub_port_clear_feature (uint8_t hub_addr, uint8_t hub_port, uint8_t feature,
                             tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Set feature
bool hub_port_set_feature   (uint8_t hub_addr, uint8_t hub_port, uint8_t feature,
                             tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Get port status
bool hub_port_get_status    (uint8_t hub_addr, uint8_t hub_port, void* resp,
                             tuh_xfer_cb_t complete_cb, uintptr_t user_data);

// Get status from Interrupt endpoint
bool hub_edpt_status_xfer(uint8_t dev_addr);

// Reset a port
static inline bool hub_port_reset(uint8_t hub_addr, uint8_t hub_port,
                                  tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  return hub_port_set_feature(hub_addr, hub_port, HUB_FEATURE_PORT_RESET, complete_cb, user_data);
}

// Clear Reset Change
static inline bool hub_port_clear_reset_change(uint8_t hub_addr, uint8_t hub_port,
                                               tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  return hub_port_clear_feature(hub_addr, hub_port, HUB_FEATURE_PORT_RESET_CHANGE, complete_cb, user_data);
}


//--------------------------------------------------------------------+
// Internal Class Driver API
//--------------------------------------------------------------------+
void hub_init       (void);
bool hub_open       (uint8_t rhport, uint8_t dev_addr, tusb_desc_interface_t const *itf_desc, uint16_t max_len);
bool hub_set_config (uint8_t dev_addr, uint8_t itf_num);
bool hub_xfer_cb    (uint8_t dev_addr, uint8_t ep_addr, xfer_result_t event, uint32_t xferred_bytes);
void hub_close      (uint8_t dev_addr);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_HUB_H_ */

/** @} */
