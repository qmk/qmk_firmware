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

#include "tusb_option.h"

#if (CFG_TUH_ENABLED && CFG_TUH_HUB)

#include "hcd.h"
#include "usbh.h"
#include "usbh_classdriver.h"
#include "hub.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+
typedef struct
{
  uint8_t itf_num;
  uint8_t ep_in;
  uint8_t port_count;
  uint8_t status_change; // data from status change interrupt endpoint

  hub_port_status_response_t port_status;
  hub_status_response_t hub_status;
} hub_interface_t;

CFG_TUSB_MEM_SECTION static hub_interface_t hub_data[CFG_TUH_HUB];
CFG_TUSB_MEM_SECTION TU_ATTR_ALIGNED(4) static uint8_t _hub_buffer[sizeof(descriptor_hub_desc_t)];

TU_ATTR_ALWAYS_INLINE
static inline hub_interface_t* get_itf(uint8_t dev_addr)
{
  return &hub_data[dev_addr-1-CFG_TUH_DEVICE_MAX];
}

#if CFG_TUSB_DEBUG >= 2
static char const* const _hub_feature_str[] =
{
  [HUB_FEATURE_PORT_CONNECTION          ] = "PORT_CONNECTION",
  [HUB_FEATURE_PORT_ENABLE              ] = "PORT_ENABLE",
  [HUB_FEATURE_PORT_SUSPEND             ] = "PORT_SUSPEND",
  [HUB_FEATURE_PORT_OVER_CURRENT        ] = "PORT_OVER_CURRENT",
  [HUB_FEATURE_PORT_RESET               ] = "PORT_RESET",
  [HUB_FEATURE_PORT_POWER               ] = "PORT_POWER",
  [HUB_FEATURE_PORT_LOW_SPEED           ] = "PORT_LOW_SPEED",
  [HUB_FEATURE_PORT_CONNECTION_CHANGE   ] = "PORT_CONNECTION_CHANGE",
  [HUB_FEATURE_PORT_ENABLE_CHANGE       ] = "PORT_ENABLE_CHANGE",
  [HUB_FEATURE_PORT_SUSPEND_CHANGE      ] = "PORT_SUSPEND_CHANGE",
  [HUB_FEATURE_PORT_OVER_CURRENT_CHANGE ] = "PORT_OVER_CURRENT_CHANGE",
  [HUB_FEATURE_PORT_RESET_CHANGE        ] = "PORT_RESET_CHANGE",
  [HUB_FEATURE_PORT_TEST                ] = "PORT_TEST",
  [HUB_FEATURE_PORT_INDICATOR           ] = "PORT_INDICATOR",
};
#endif

//--------------------------------------------------------------------+
// HUB
//--------------------------------------------------------------------+
bool hub_port_clear_feature(uint8_t hub_addr, uint8_t hub_port, uint8_t feature,
                            tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  tusb_control_request_t const request =
  {
    .bmRequestType_bit =
    {
      .recipient = (hub_port == 0) ? TUSB_REQ_RCPT_DEVICE : TUSB_REQ_RCPT_OTHER,
      .type      = TUSB_REQ_TYPE_CLASS,
      .direction = TUSB_DIR_OUT
    },
    .bRequest = HUB_REQUEST_CLEAR_FEATURE,
    .wValue   = feature,
    .wIndex   = hub_port,
    .wLength  = 0
  };

  tuh_xfer_t xfer =
  {
    .daddr       = hub_addr,
    .ep_addr     = 0,
    .setup       = &request,
    .buffer      = NULL,
    .complete_cb = complete_cb,
    .user_data   = user_data
  };

  TU_LOG2("HUB Clear Feature: %s, addr = %u port = %u\r\n", _hub_feature_str[feature], hub_addr, hub_port);
  TU_ASSERT( tuh_control_xfer(&xfer) );
  return true;
}

bool hub_port_set_feature(uint8_t hub_addr, uint8_t hub_port, uint8_t feature,
                          tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  tusb_control_request_t const request =
  {
    .bmRequestType_bit =
    {
      .recipient = (hub_port == 0) ? TUSB_REQ_RCPT_DEVICE : TUSB_REQ_RCPT_OTHER,
      .type      = TUSB_REQ_TYPE_CLASS,
      .direction = TUSB_DIR_OUT
    },
    .bRequest = HUB_REQUEST_SET_FEATURE,
    .wValue   = feature,
    .wIndex   = hub_port,
    .wLength  = 0
  };

  tuh_xfer_t xfer =
  {
    .daddr       = hub_addr,
    .ep_addr     = 0,
    .setup       = &request,
    .buffer      = NULL,
    .complete_cb = complete_cb,
    .user_data   = user_data
  };

  TU_LOG2("HUB Set Feature: %s, addr = %u port = %u\r\n", _hub_feature_str[feature], hub_addr, hub_port);
  TU_ASSERT( tuh_control_xfer(&xfer) );
  return true;
}

bool hub_port_get_status(uint8_t hub_addr, uint8_t hub_port, void* resp,
                         tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  tusb_control_request_t const request =
  {
    .bmRequestType_bit =
    {
      .recipient = (hub_port == 0) ? TUSB_REQ_RCPT_DEVICE : TUSB_REQ_RCPT_OTHER,
      .type      = TUSB_REQ_TYPE_CLASS,
      .direction = TUSB_DIR_IN
    },
    .bRequest = HUB_REQUEST_GET_STATUS,
    .wValue   = 0,
    .wIndex   = hub_port,
    .wLength  = 4
  };

  tuh_xfer_t xfer =
  {
    .daddr       = hub_addr,
    .ep_addr     = 0,
    .setup       = &request,
    .buffer      = resp,
    .complete_cb = complete_cb,
    .user_data   = user_data
  };

  TU_LOG2("HUB Get Port Status: addr = %u port = %u\r\n", hub_addr, hub_port);
  TU_VERIFY( tuh_control_xfer(&xfer) );
  return true;
}

//--------------------------------------------------------------------+
// CLASS-USBH API (don't require to verify parameters)
//--------------------------------------------------------------------+
void hub_init(void)
{
  tu_memclr(hub_data, sizeof(hub_data));
}

bool hub_open(uint8_t rhport, uint8_t dev_addr, tusb_desc_interface_t const *itf_desc, uint16_t max_len)
{
  (void) rhport;

  TU_VERIFY(TUSB_CLASS_HUB == itf_desc->bInterfaceClass &&
            0              == itf_desc->bInterfaceSubClass);

  // hub driver does not support multiple TT yet
  TU_VERIFY(itf_desc->bInterfaceProtocol <= 1);

  // msc driver length is fixed
  uint16_t const drv_len = sizeof(tusb_desc_interface_t) + sizeof(tusb_desc_endpoint_t);
  TU_ASSERT(drv_len <= max_len);

  //------------- Interrupt Status endpoint -------------//
  tusb_desc_endpoint_t const *desc_ep = (tusb_desc_endpoint_t const *) tu_desc_next(itf_desc);

  TU_ASSERT(TUSB_DESC_ENDPOINT  == desc_ep->bDescriptorType &&
            TUSB_XFER_INTERRUPT == desc_ep->bmAttributes.xfer, 0);
  
  TU_ASSERT(tuh_edpt_open(dev_addr, desc_ep));

  hub_interface_t* p_hub = get_itf(dev_addr);

  p_hub->itf_num = itf_desc->bInterfaceNumber;
  p_hub->ep_in   = desc_ep->bEndpointAddress;

  return true;
}

void hub_close(uint8_t dev_addr)
{
  TU_VERIFY(dev_addr > CFG_TUH_DEVICE_MAX, );
  hub_interface_t* p_hub = get_itf(dev_addr);

  if (p_hub->ep_in) tu_memclr(p_hub, sizeof( hub_interface_t));
}

bool hub_edpt_status_xfer(uint8_t dev_addr)
{
  hub_interface_t* hub_itf = get_itf(dev_addr);
  return usbh_edpt_xfer(dev_addr, hub_itf->ep_in, &hub_itf->status_change, 1);
}


//--------------------------------------------------------------------+
// Set Configure
//--------------------------------------------------------------------+

static void config_set_port_power (tuh_xfer_t* xfer);
static void config_port_power_complete (tuh_xfer_t* xfer);

bool hub_set_config(uint8_t dev_addr, uint8_t itf_num)
{
  hub_interface_t* p_hub = get_itf(dev_addr);
  TU_ASSERT(itf_num == p_hub->itf_num);

  // Get Hub Descriptor
  tusb_control_request_t const request =
  {
    .bmRequestType_bit =
    {
      .recipient = TUSB_REQ_RCPT_DEVICE,
      .type      = TUSB_REQ_TYPE_CLASS,
      .direction = TUSB_DIR_IN
    },
    .bRequest = HUB_REQUEST_GET_DESCRIPTOR,
    .wValue   = 0,
    .wIndex   = 0,
    .wLength  = sizeof(descriptor_hub_desc_t)
  };

  tuh_xfer_t xfer =
  {
    .daddr       = dev_addr,
    .ep_addr     = 0,
    .setup       = &request,
    .buffer      = _hub_buffer,
    .complete_cb = config_set_port_power,
    .user_data    = 0
  };

  TU_ASSERT( tuh_control_xfer(&xfer) );

  return true;
}

static void config_set_port_power (tuh_xfer_t* xfer)
{
  TU_ASSERT(XFER_RESULT_SUCCESS == xfer->result, );

  uint8_t const daddr = xfer->daddr;
  hub_interface_t* p_hub = get_itf(daddr);

  // only use number of ports in hub descriptor
  descriptor_hub_desc_t const* desc_hub = (descriptor_hub_desc_t const*) _hub_buffer;
  p_hub->port_count = desc_hub->bNbrPorts;

  // May need to GET_STATUS

  // Set Port Power to be able to detect connection, starting with port 1
  uint8_t const hub_port = 1;
  hub_port_set_feature(daddr, hub_port, HUB_FEATURE_PORT_POWER, config_port_power_complete, 0);
}

static void config_port_power_complete (tuh_xfer_t* xfer)
{
  TU_ASSERT(XFER_RESULT_SUCCESS == xfer->result, );

  uint8_t const daddr = xfer->daddr;
  hub_interface_t* p_hub = get_itf(daddr);

  if (xfer->setup->wIndex == p_hub->port_count)
  {
    // All ports are power -> queue notification status endpoint and
    // complete the SET CONFIGURATION
    TU_ASSERT( usbh_edpt_xfer(daddr, p_hub->ep_in, &p_hub->status_change, 1), );

    usbh_driver_set_config_complete(daddr, p_hub->itf_num);
  }else
  {
    // power next port
    uint8_t const hub_port = (uint8_t) (xfer->setup->wIndex + 1);
    hub_port_set_feature(daddr, hub_port, HUB_FEATURE_PORT_POWER, config_port_power_complete, 0);
  }
}

//--------------------------------------------------------------------+
// Connection Changes
//--------------------------------------------------------------------+

static void hub_port_get_status_complete (tuh_xfer_t* xfer);
static void hub_get_status_complete (tuh_xfer_t* xfer);
static void connection_clear_conn_change_complete (tuh_xfer_t* xfer);
static void connection_port_reset_complete (tuh_xfer_t* xfer);

// callback as response of interrupt endpoint polling
bool hub_xfer_cb(uint8_t dev_addr, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes)
{
  (void) xferred_bytes; // TODO can be more than 1 for hub with lots of ports
  (void) ep_addr;
  TU_ASSERT(result == XFER_RESULT_SUCCESS);

  hub_interface_t* p_hub = get_itf(dev_addr);

  TU_LOG2("  Hub Status Change = 0x%02X\r\n", p_hub->status_change);

  // Hub bit 0 is for the hub device events
  if (tu_bit_test(p_hub->status_change, 0))
  {
    if (hub_port_get_status(dev_addr, 0, &p_hub->hub_status, hub_get_status_complete, 0) == false)
    {
      //Hub status control transfer failed, retry
      hub_edpt_status_xfer(dev_addr);
    }
  }
  else
  {
    // Hub bits 1 to n are hub port events
    for (uint8_t port=1; port <= p_hub->port_count; port++)
    {
      if ( tu_bit_test(p_hub->status_change, port) )
      {
        if (hub_port_get_status(dev_addr, port, &p_hub->port_status, hub_port_get_status_complete, 0) == false)
        {
          //Hub status control transfer failed, retry
          hub_edpt_status_xfer(dev_addr);
        }
        break;
      }
    }
  }

  // NOTE: next status transfer is queued by usbh.c after handling this request

  return true;
}

static void hub_clear_feature_complete_stub(tuh_xfer_t* xfer)
{
  TU_ASSERT(xfer->result == XFER_RESULT_SUCCESS, );
  hub_edpt_status_xfer(xfer->daddr);
}

static void hub_get_status_complete (tuh_xfer_t* xfer)
{
  TU_ASSERT(xfer->result == XFER_RESULT_SUCCESS, );

  uint8_t const daddr = xfer->daddr;
  hub_interface_t* p_hub = get_itf(daddr);
  uint8_t const port_num = (uint8_t) tu_le16toh(xfer->setup->wIndex);
  TU_ASSERT(port_num == 0 , );

  TU_LOG2("HUB Got hub status, addr = %u, status = %04x\r\n", daddr, p_hub->hub_status.change.value);

  if (p_hub->hub_status.change.local_power_source)
  {
    TU_LOG2("HUB Local Power Change, addr = %u\r\n", daddr);
    hub_port_clear_feature(daddr, port_num, HUB_FEATURE_HUB_LOCAL_POWER_CHANGE, hub_clear_feature_complete_stub, 0);
  }
  else if (p_hub->hub_status.change.over_current)
  {
    TU_LOG1("HUB Over Current, addr = %u\r\n", daddr);
    hub_port_clear_feature(daddr, port_num, HUB_FEATURE_HUB_OVER_CURRENT_CHANGE, hub_clear_feature_complete_stub, 0);
  }
}

static void hub_port_get_status_complete (tuh_xfer_t* xfer)
{
  TU_ASSERT(xfer->result == XFER_RESULT_SUCCESS, );

  uint8_t const daddr = xfer->daddr;
  hub_interface_t* p_hub = get_itf(daddr);
  uint8_t const port_num = (uint8_t) tu_le16toh(xfer->setup->wIndex);

  // Connection change
  if (p_hub->port_status.change.connection)
  {
    // Port is powered and enabled
    //TU_VERIFY(port_status.status_current.port_power && port_status.status_current.port_enable, );

    // Acknowledge Port Connection Change
    hub_port_clear_feature(daddr, port_num, HUB_FEATURE_PORT_CONNECTION_CHANGE, connection_clear_conn_change_complete, 0);
  }else
  {
    // Clear other port status change interrupts. TODO Not currently handled - just cleared.
    if (p_hub->port_status.change.port_enable)
    {
      hub_port_clear_feature(daddr, port_num, HUB_FEATURE_PORT_ENABLE_CHANGE, hub_clear_feature_complete_stub, 0);
    }
    else if (p_hub->port_status.change.suspend)
    {
      hub_port_clear_feature(daddr, port_num, HUB_FEATURE_PORT_SUSPEND_CHANGE, hub_clear_feature_complete_stub, 0);
    }
    else if (p_hub->port_status.change.over_current)
    {
      hub_port_clear_feature(daddr, port_num, HUB_FEATURE_PORT_OVER_CURRENT_CHANGE, hub_clear_feature_complete_stub, 0);
    }
    else if (p_hub->port_status.change.reset)
    {
      hub_port_clear_feature(daddr, port_num, HUB_FEATURE_PORT_RESET_CHANGE, hub_clear_feature_complete_stub, 0);
    }
    // Other changes are: L1 state
    // TODO clear change

    // prepare for next hub status
    // TODO continue with status_change, or maybe we can do it again with status
    hub_edpt_status_xfer(daddr);
  }
}

static void connection_clear_conn_change_complete (tuh_xfer_t* xfer)
{
  TU_ASSERT(xfer->result == XFER_RESULT_SUCCESS, );

  uint8_t const daddr = xfer->daddr;
  hub_interface_t* p_hub = get_itf(daddr);
  uint8_t const port_num = (uint8_t) tu_le16toh(xfer->setup->wIndex);

  if ( p_hub->port_status.status.connection )
  {
    // Reset port if attach event
    hub_port_reset(daddr, port_num, connection_port_reset_complete, 0);
  }else
  {
    // submit detach event
    hcd_event_t event =
    {
      .rhport     = usbh_get_rhport(daddr),
      .event_id   = HCD_EVENT_DEVICE_REMOVE,
      .connection =
       {
         .hub_addr = daddr,
         .hub_port = port_num
       }
    };

    hcd_event_handler(&event, false);
  }
}

static void connection_port_reset_complete (tuh_xfer_t* xfer)
{
  TU_ASSERT(xfer->result == XFER_RESULT_SUCCESS, );

  uint8_t const daddr = xfer->daddr;
  // hub_interface_t* p_hub = get_itf(daddr);
  uint8_t const port_num = (uint8_t) tu_le16toh(xfer->setup->wIndex);

  // submit attach event
  hcd_event_t event =
  {
    .rhport     = usbh_get_rhport(daddr),
    .event_id   = HCD_EVENT_DEVICE_ATTACH,
    .connection =
    {
      .hub_addr = daddr,
      .hub_port = port_num
    }
  };

  hcd_event_handler(&event, false);
}

#endif
