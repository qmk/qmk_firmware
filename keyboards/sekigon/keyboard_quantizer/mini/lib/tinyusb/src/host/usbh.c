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

#if CFG_TUH_ENABLED

#include "host/hcd.h"
#include "tusb.h"
#include "host/usbh_classdriver.h"
#include "hub.h"

//--------------------------------------------------------------------+
// USBH Configuration
//--------------------------------------------------------------------+

#ifndef CFG_TUH_TASK_QUEUE_SZ
#define CFG_TUH_TASK_QUEUE_SZ   16
#endif

#ifndef CFG_TUH_INTERFACE_MAX
#define CFG_TUH_INTERFACE_MAX   8
#endif

// Debug level, TUSB_CFG_DEBUG must be at least this level for debug message
#define USBH_DEBUG   2

#define TU_LOG_USBH(...)   TU_LOG(USBH_DEBUG, __VA_ARGS__)

//--------------------------------------------------------------------+
// USBH-HCD common data structure
//--------------------------------------------------------------------+

// device0 struct must be strictly a subset of normal device struct
// TODO refactor later
typedef struct
{
  // port
  uint8_t rhport;
  uint8_t hub_addr;
  uint8_t hub_port;
  uint8_t speed;

  struct TU_ATTR_PACKED
  {
    volatile uint8_t connected  : 1;
    volatile uint8_t addressed  : 1;
    volatile uint8_t configured : 1;
    volatile uint8_t suspended  : 1;
  };

} usbh_dev0_t;

typedef struct {
  // port, must be same layout as usbh_dev0_t
  uint8_t rhport;
  uint8_t hub_addr;
  uint8_t hub_port;
  uint8_t speed;

  // Device State
  struct TU_ATTR_PACKED {
    volatile uint8_t connected  : 1;
    volatile uint8_t addressed  : 1;
    volatile uint8_t configured : 1;
    volatile uint8_t suspended  : 1;
  };

  // Device Descriptor
  uint8_t  ep0_size;

  uint16_t vid;
  uint16_t pid;

  uint8_t  i_manufacturer;
  uint8_t  i_product;
  uint8_t  i_serial;

  // Configuration Descriptor
  // uint8_t interface_count; // bNumInterfaces alias

  // Endpoint & Interface
  uint8_t itf2drv[CFG_TUH_INTERFACE_MAX];  // map interface number to driver (0xff is invalid)
  uint8_t ep2drv[CFG_TUH_ENDPOINT_MAX][2]; // map endpoint to driver ( 0xff is invalid ), can use only 4-bit each

  tu_edpt_state_t ep_status[CFG_TUH_ENDPOINT_MAX][2];

#if CFG_TUH_API_EDPT_XFER
  // TODO array can be CFG_TUH_ENDPOINT_MAX-1
  struct {
    tuh_xfer_cb_t complete_cb;
    uintptr_t user_data;
  }ep_callback[CFG_TUH_ENDPOINT_MAX][2];
#endif

} usbh_device_t;

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+

// Invalid driver ID in itf2drv[] ep2drv[][] mapping
enum { DRVID_INVALID = 0xFFu };
enum { CONTROLLER_INVALID = 0xFFu };

#if CFG_TUSB_DEBUG >= 2
  #define DRIVER_NAME(_name)    .name = _name,
#else
  #define DRIVER_NAME(_name)
#endif

static usbh_class_driver_t const usbh_class_drivers[] =
{
  #if CFG_TUH_CDC
    {
      DRIVER_NAME("CDC")
      .init       = cdch_init,
      .open       = cdch_open,
      .set_config = cdch_set_config,
      .xfer_cb    = cdch_xfer_cb,
      .close      = cdch_close
    },
  #endif

  #if CFG_TUH_MSC
    {
      DRIVER_NAME("MSC")
      .init       = msch_init,
      .open       = msch_open,
      .set_config = msch_set_config,
      .xfer_cb    = msch_xfer_cb,
      .close      = msch_close
    },
  #endif

  #if CFG_TUH_HID
    {
      DRIVER_NAME("HID")
      .init       = hidh_init,
      .open       = hidh_open,
      .set_config = hidh_set_config,
      .xfer_cb    = hidh_xfer_cb,
      .close      = hidh_close
    },
  #endif

  #if CFG_TUH_HUB
    {
      DRIVER_NAME("HUB")
      .init       = hub_init,
      .open       = hub_open,
      .set_config = hub_set_config,
      .xfer_cb    = hub_xfer_cb,
      .close      = hub_close
    },
  #endif

  #if CFG_TUH_VENDOR
    {
      DRIVER_NAME("VENDOR")
      .init       = cush_init,
      .open       = cush_open_subtask,
      .xfer_cb    = cush_isr,
      .close      = cush_close
    }
  #endif
};

enum { USBH_CLASS_DRIVER_COUNT = TU_ARRAY_SIZE(usbh_class_drivers) };

enum { RESET_DELAY = 500 };  // 200 USB specs say only 50ms but many devices require much longer

enum { CONFIG_NUM = 1 }; // default to use configuration 1


//--------------------------------------------------------------------+
// INTERNAL OBJECT & FUNCTION DECLARATION
//--------------------------------------------------------------------+

// sum of end device + hub
#define TOTAL_DEVICES   (CFG_TUH_DEVICE_MAX + CFG_TUH_HUB)

static uint8_t _usbh_controller = CONTROLLER_INVALID;

// Device with address = 0 for enumeration
static usbh_dev0_t _dev0;

// all devices excluding zero-address
// hub address start from CFG_TUH_DEVICE_MAX+1
// TODO: hub can has its own simpler struct to save memory
CFG_TUSB_MEM_SECTION usbh_device_t _usbh_devices[TOTAL_DEVICES];

// Mutex for claiming endpoint
#if OSAL_MUTEX_REQUIRED
  static osal_mutex_def_t _usbh_mutexdef;
  static osal_mutex_t _usbh_mutex;
#else
  #define _usbh_mutex   NULL
#endif

// Event queue
// usbh_int_set is used as mutex in OS NONE config
OSAL_QUEUE_DEF(usbh_int_set, _usbh_qdef, CFG_TUH_TASK_QUEUE_SZ, hcd_event_t);
static osal_queue_t _usbh_q;

CFG_TUSB_MEM_SECTION CFG_TUSB_MEM_ALIGN
static uint8_t _usbh_ctrl_buf[CFG_TUH_ENUMERATION_BUFSIZE];

// Control transfers: since most controllers do not support multiple control transfers
// on multiple devices concurrently and control transfers are not used much except for
// enumeration, we will only execute control transfers one at a time.
CFG_TUSB_MEM_SECTION struct
{
  tusb_control_request_t request TU_ATTR_ALIGNED(4);
  uint8_t* buffer;
  tuh_xfer_cb_t complete_cb;
  uintptr_t user_data;

  uint8_t daddr;
  volatile uint8_t stage;
  volatile uint16_t actual_len;
}_ctrl_xfer;

//------------- Helper Function -------------//

TU_ATTR_ALWAYS_INLINE
static inline usbh_device_t* get_device(uint8_t dev_addr)
{
  TU_VERIFY(dev_addr > 0 && dev_addr <= TOTAL_DEVICES, NULL);
  return &_usbh_devices[dev_addr-1];
}

static bool enum_new_device(hcd_event_t* event);
static void process_device_unplugged(uint8_t rhport, uint8_t hub_addr, uint8_t hub_port);
static bool usbh_edpt_control_open(uint8_t dev_addr, uint8_t max_packet_size);
static bool usbh_control_xfer_cb (uint8_t daddr, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes);

#if CFG_TUSB_OS == OPT_OS_NONE
// TODO rework time-related function later
void osal_task_delay(uint32_t msec)
{
  const uint32_t start = hcd_frame_number(_usbh_controller);
  while ( ( hcd_frame_number(_usbh_controller) - start ) < msec ) {}
}
#endif

//--------------------------------------------------------------------+
// PUBLIC API (Parameter Verification is required)
//--------------------------------------------------------------------+

bool tuh_configure(uint8_t rhport, uint32_t cfg_id, const void* cfg_param)
{
  if (hcd_configure)
  {
    return hcd_configure(rhport, cfg_id, cfg_param);
  }else
  {
    return false;
  }
}

bool tuh_mounted(uint8_t dev_addr)
{
  usbh_device_t* dev = get_device(dev_addr);
  TU_VERIFY(dev);
  return dev->configured;
}

bool tuh_vid_pid_get(uint8_t dev_addr, uint16_t* vid, uint16_t* pid)
{
  *vid = *pid = 0;

  usbh_device_t const* dev = get_device(dev_addr);
  TU_VERIFY(dev && dev->configured);

  *vid = dev->vid;
  *pid = dev->pid;

  return true;
}

tusb_speed_t tuh_speed_get (uint8_t dev_addr)
{
  usbh_device_t* dev = get_device(dev_addr);
  return (tusb_speed_t) (dev ? get_device(dev_addr)->speed : _dev0.speed);
}

static void clear_device(usbh_device_t* dev)
{
  tu_memclr(dev, sizeof(usbh_device_t));
  memset(dev->itf2drv, DRVID_INVALID, sizeof(dev->itf2drv)); // invalid mapping
  memset(dev->ep2drv , DRVID_INVALID, sizeof(dev->ep2drv )); // invalid mapping
}

bool tuh_inited(void)
{
  return _usbh_controller != CONTROLLER_INVALID;
}

bool tuh_init(uint8_t controller_id)
{
  // skip if already initialized
  if ( tuh_inited() ) return true;

  TU_LOG_USBH("USBH init on controller %u\r\n", controller_id);
  TU_LOG_INT(USBH_DEBUG, sizeof(usbh_device_t));
  TU_LOG_INT(USBH_DEBUG, sizeof(hcd_event_t));
  TU_LOG_INT(USBH_DEBUG, sizeof(_ctrl_xfer));
  TU_LOG_INT(USBH_DEBUG, sizeof(tuh_xfer_t));
  TU_LOG_INT(USBH_DEBUG, sizeof(tu_fifo_t));
  TU_LOG_INT(USBH_DEBUG, sizeof(tu_edpt_stream_t));

  // Event queue
  _usbh_q = osal_queue_create( &_usbh_qdef );
  TU_ASSERT(_usbh_q != NULL);

#if OSAL_MUTEX_REQUIRED
  // Init mutex
  _usbh_mutex = osal_mutex_create(&_usbh_mutexdef);
  TU_ASSERT(_usbh_mutex);
#endif

  // Device
  tu_memclr(&_dev0, sizeof(_dev0));
  tu_memclr(_usbh_devices, sizeof(_usbh_devices));
  tu_memclr(&_ctrl_xfer, sizeof(_ctrl_xfer));

  for(uint8_t i=0; i<TOTAL_DEVICES; i++)
  {
    clear_device(&_usbh_devices[i]);
  }

  // Class drivers
  for (uint8_t drv_id = 0; drv_id < USBH_CLASS_DRIVER_COUNT; drv_id++)
  {
    TU_LOG_USBH("%s init\r\n", usbh_class_drivers[drv_id].name);
    usbh_class_drivers[drv_id].init();
  }

  _usbh_controller = controller_id;;

  TU_ASSERT(hcd_init(controller_id));
  hcd_int_enable(controller_id);

  return true;
}

/* USB Host Driver task
 * This top level thread manages all host controller event and delegates events to class-specific drivers.
 * This should be called periodically within the mainloop or rtos thread.
 *
   @code
    int main(void)
    {
      application_init();
      tusb_init();

      while(1) // the mainloop
      {
        application_code();
        tuh_task(); // tinyusb host task
      }
    }
    @endcode
 */
void tuh_task_ext(uint32_t timeout_ms, bool in_isr)
{
  (void) in_isr; // not implemented yet

  // Skip if stack is not initialized
  if ( !tusb_inited() ) return;

  // Loop until there is no more events in the queue
  while (1)
  {
    hcd_event_t event;
    if ( !osal_queue_receive(_usbh_q, &event, timeout_ms) ) return;

    switch (event.event_id)
    {
      case HCD_EVENT_DEVICE_ATTACH:
        // TODO due to the shared _usbh_ctrl_buf, we must complete enumerating
        // one device before enumerating another one.
        TU_LOG_USBH("[%u:] USBH DEVICE ATTACH\r\n", event.rhport);
        enum_new_device(&event);
      break;

      case HCD_EVENT_DEVICE_REMOVE:
        TU_LOG_USBH("[%u:%u:%u] USBH DEVICE REMOVED\r\n", event.rhport, event.connection.hub_addr, event.connection.hub_port);
        process_device_unplugged(event.rhport, event.connection.hub_addr, event.connection.hub_port);

        #if CFG_TUH_HUB
        // TODO remove
        if ( event.connection.hub_addr != 0)
        {
          // done with hub, waiting for next data on status pipe
          (void) hub_edpt_status_xfer( event.connection.hub_addr );
        }
        #endif
      break;

      case HCD_EVENT_XFER_COMPLETE:
      {
        uint8_t const ep_addr = event.xfer_complete.ep_addr;
        uint8_t const epnum   = tu_edpt_number(ep_addr);
        uint8_t const ep_dir  = tu_edpt_dir(ep_addr);

        TU_LOG_USBH("on EP %02X with %u bytes\r\n", ep_addr, (unsigned int) event.xfer_complete.len);

        if (event.dev_addr == 0)
        {
          // device 0 only has control endpoint
          TU_ASSERT(epnum == 0, );
          usbh_control_xfer_cb(event.dev_addr, ep_addr, event.xfer_complete.result, event.xfer_complete.len);
        }
        else
        {
          usbh_device_t* dev = get_device(event.dev_addr);
          TU_ASSERT(dev, );

          dev->ep_status[epnum][ep_dir].busy    = 0;
          dev->ep_status[epnum][ep_dir].claimed = 0;

          if ( 0 == epnum )
          {
            usbh_control_xfer_cb(event.dev_addr, ep_addr, event.xfer_complete.result, event.xfer_complete.len);
          }else
          {
            uint8_t drv_id = dev->ep2drv[epnum][ep_dir];
            if(drv_id < USBH_CLASS_DRIVER_COUNT)
            {
              TU_LOG_USBH("%s xfer callback\r\n", usbh_class_drivers[drv_id].name);
              usbh_class_drivers[drv_id].xfer_cb(event.dev_addr, ep_addr, event.xfer_complete.result, event.xfer_complete.len);
            }
            else
            {
#if CFG_TUH_API_EDPT_XFER
              tuh_xfer_cb_t complete_cb = dev->ep_callback[epnum][ep_dir].complete_cb;
              if ( complete_cb )
              {
                tuh_xfer_t xfer =
                {
                  .daddr       = event.dev_addr,
                  .ep_addr     = ep_addr,
                  .result      = event.xfer_complete.result,
                  .actual_len  = event.xfer_complete.len,
                  .buflen      = 0,    // not available
                  .buffer      = NULL, // not available
                  .complete_cb = complete_cb,
                  .user_data   = dev->ep_callback[epnum][ep_dir].user_data
                };

                complete_cb(&xfer);
              }else
#endif
              {
                // no driver/callback responsible for this transfer
                TU_ASSERT(false, );
              }

            }
          }
        }
      }
      break;

      case USBH_EVENT_FUNC_CALL:
        if ( event.func_call.func ) event.func_call.func(event.func_call.param);
      break;

      default: break;
    }

#if CFG_TUSB_OS != OPT_OS_NONE && CFG_TUSB_OS != OPT_OS_PICO
    // return if there is no more events, for application to run other background
    if (osal_queue_empty(_usbh_q)) return;
#endif
  }
}

//--------------------------------------------------------------------+
// Control transfer
//--------------------------------------------------------------------+

static void _control_blocking_complete_cb(tuh_xfer_t* xfer)
{
  // update result
  *((xfer_result_t*) xfer->user_data) = xfer->result;
}

// TODO timeout_ms is not supported yet
bool tuh_control_xfer (tuh_xfer_t* xfer)
{
  // EP0 with setup packet
  TU_VERIFY(xfer->ep_addr == 0 && xfer->setup);

  // pre-check to help reducing mutex lock
  TU_VERIFY(_ctrl_xfer.stage == CONTROL_STAGE_IDLE);

  uint8_t const daddr = xfer->daddr;

  (void) osal_mutex_lock(_usbh_mutex, OSAL_TIMEOUT_WAIT_FOREVER);

  bool const is_idle = (_ctrl_xfer.stage == CONTROL_STAGE_IDLE);
  if (is_idle)
  {
    _ctrl_xfer.stage       = CONTROL_STAGE_SETUP;
    _ctrl_xfer.daddr       = daddr;
    _ctrl_xfer.actual_len  = 0;

    _ctrl_xfer.request     = (*xfer->setup);
    _ctrl_xfer.buffer      = xfer->buffer;
    _ctrl_xfer.complete_cb = xfer->complete_cb;
    _ctrl_xfer.user_data   = xfer->user_data;
  }

  (void) osal_mutex_unlock(_usbh_mutex);

  TU_VERIFY(is_idle);
  const uint8_t rhport = usbh_get_rhport(daddr);

  TU_LOG_USBH("[%u:%u] %s: ", rhport, daddr,
              (xfer->setup->bmRequestType_bit.type == TUSB_REQ_TYPE_STANDARD && xfer->setup->bRequest <= TUSB_REQ_SYNCH_FRAME) ?
                  tu_str_std_request[xfer->setup->bRequest] : "Class Request");
  TU_LOG_PTR(USBH_DEBUG, xfer->setup);
  TU_LOG_USBH("\r\n");

  if (xfer->complete_cb)
  {
    TU_ASSERT( hcd_setup_send(rhport, daddr, (uint8_t const*) &_ctrl_xfer.request) );
  }else
  {
    // blocking if complete callback is not provided
    // change callback to internal blocking, and result as user argument
    volatile xfer_result_t result = XFER_RESULT_INVALID;

    // use user_data to point to xfer_result_t
    _ctrl_xfer.user_data   = (uintptr_t) &result;
    _ctrl_xfer.complete_cb = _control_blocking_complete_cb;

    TU_ASSERT( hcd_setup_send(rhport, daddr, (uint8_t*) &_ctrl_xfer.request) );

    while (result == XFER_RESULT_INVALID)
    {
      // only need to call task if not preempted RTOS
      #if CFG_TUSB_OS == OPT_OS_NONE || CFG_TUSB_OS == OPT_OS_PICO
      tuh_task();
      #endif

      // TODO probably some timeout to prevent hanged
    }

    // update transfer result
    xfer->result     = result;
    xfer->actual_len = _ctrl_xfer.actual_len;
  }

  return true;
}

TU_ATTR_ALWAYS_INLINE static inline void _set_control_xfer_stage(uint8_t stage)
{
  (void) osal_mutex_lock(_usbh_mutex, OSAL_TIMEOUT_WAIT_FOREVER);
  _ctrl_xfer.stage = stage;
  (void) osal_mutex_unlock(_usbh_mutex);
}

static void _xfer_complete(uint8_t daddr, xfer_result_t result)
{
  TU_LOG_USBH("\r\n");

  // duplicate xfer since user can execute control transfer within callback
  tusb_control_request_t const request = _ctrl_xfer.request;
  tuh_xfer_t xfer_temp =
  {
    .daddr       = daddr,
    .ep_addr     = 0,
    .result      = result,
    .setup       = &request,
    .actual_len  = (uint32_t) _ctrl_xfer.actual_len,
    .buffer      = _ctrl_xfer.buffer,
    .complete_cb = _ctrl_xfer.complete_cb,
    .user_data   = _ctrl_xfer.user_data
  };

  _set_control_xfer_stage(CONTROL_STAGE_IDLE);

  if (xfer_temp.complete_cb)
  {
    xfer_temp.complete_cb(&xfer_temp);
  }
}

static bool usbh_control_xfer_cb (uint8_t dev_addr, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes)
{
  (void) ep_addr;

  const uint8_t rhport = usbh_get_rhport(dev_addr);
  tusb_control_request_t const * request = &_ctrl_xfer.request;

  if (XFER_RESULT_SUCCESS != result)
  {
    TU_LOG1("[%u:%u] Control %s, xferred_bytes = %lu\r\n", rhport, dev_addr, result == XFER_RESULT_STALLED ? "STALLED" : "FAILED", xferred_bytes);
    #if CFG_TUSB_DEBUG == 1
    TU_LOG1_PTR(request);
    TU_LOG1("\r\n");
    #endif

    // terminate transfer if any stage failed
    _xfer_complete(dev_addr, result);
  }else
  {
    switch(_ctrl_xfer.stage)
    {
      case CONTROL_STAGE_SETUP:
        if (request->wLength)
        {
          // DATA stage: initial data toggle is always 1
          _set_control_xfer_stage(CONTROL_STAGE_DATA);
          TU_ASSERT( hcd_edpt_xfer(rhport, dev_addr, tu_edpt_addr(0, request->bmRequestType_bit.direction), _ctrl_xfer.buffer, request->wLength) );
          return true;
        }
        TU_ATTR_FALLTHROUGH;

      case CONTROL_STAGE_DATA:
        if (request->wLength)
        {
          TU_LOG_USBH("[%u:%u] Control data:\r\n", rhport, dev_addr);
          TU_LOG_MEM(USBH_DEBUG, _ctrl_xfer.buffer, xferred_bytes, 2);
        }

        _ctrl_xfer.actual_len = (uint16_t) xferred_bytes;

        // ACK stage: toggle is always 1
        _set_control_xfer_stage(CONTROL_STAGE_ACK);
        TU_ASSERT( hcd_edpt_xfer(rhport, dev_addr, tu_edpt_addr(0, 1-request->bmRequestType_bit.direction), NULL, 0) );
      break;

      case CONTROL_STAGE_ACK:
        _xfer_complete(dev_addr, result);
      break;

      default: return false;
    }
  }

  return true;
}

//--------------------------------------------------------------------+
//
//--------------------------------------------------------------------+

bool tuh_edpt_xfer(tuh_xfer_t* xfer)
{
  uint8_t const daddr   = xfer->daddr;
  uint8_t const ep_addr = xfer->ep_addr;

  TU_VERIFY(daddr && ep_addr);

  TU_VERIFY(usbh_edpt_claim(daddr, ep_addr));

  if ( !usbh_edpt_xfer_with_callback(daddr, ep_addr, xfer->buffer, (uint16_t) xfer->buflen, xfer->complete_cb, xfer->user_data) )
  {
    usbh_edpt_release(daddr, ep_addr);
    return false;
  }

  return true;
}

//--------------------------------------------------------------------+
// USBH API For Class Driver
//--------------------------------------------------------------------+

uint8_t usbh_get_rhport(uint8_t dev_addr)
{
  usbh_device_t* dev = get_device(dev_addr);
  return dev ? dev->rhport : _dev0.rhport;
}

uint8_t* usbh_get_enum_buf(void)
{
  return _usbh_ctrl_buf;
}

void usbh_int_set(bool enabled)
{
  // TODO all host controller if multiple is used
  if (enabled)
  {
    hcd_int_enable(_usbh_controller);
  }else
  {
    hcd_int_disable(_usbh_controller);
  }
}

//--------------------------------------------------------------------+
// Endpoint API
//--------------------------------------------------------------------+

// TODO has some duplication code with device, refactor later
bool usbh_edpt_claim(uint8_t dev_addr, uint8_t ep_addr)
{
  usbh_device_t* dev = get_device(dev_addr);

  // addr0 only use tuh_control_xfer
  TU_ASSERT(dev);

  uint8_t const epnum = tu_edpt_number(ep_addr);
  uint8_t const dir   = tu_edpt_dir(ep_addr);

  return tu_edpt_claim(&dev->ep_status[epnum][dir], _usbh_mutex);
}

// TODO has some duplication code with device, refactor later
bool usbh_edpt_release(uint8_t dev_addr, uint8_t ep_addr)
{
  usbh_device_t* dev = get_device(dev_addr);

  // addr0 only use tuh_control_xfer
  TU_ASSERT(dev);

  uint8_t const epnum = tu_edpt_number(ep_addr);
  uint8_t const dir   = tu_edpt_dir(ep_addr);

  return tu_edpt_release(&dev->ep_status[epnum][dir], _usbh_mutex);
}

// TODO has some duplication code with device, refactor later
bool usbh_edpt_xfer_with_callback(uint8_t dev_addr, uint8_t ep_addr, uint8_t * buffer, uint16_t total_bytes,
                                  tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  (void) complete_cb;
  (void) user_data;

  usbh_device_t* dev = get_device(dev_addr);
  TU_VERIFY(dev);

  uint8_t const epnum = tu_edpt_number(ep_addr);
  uint8_t const dir   = tu_edpt_dir(ep_addr);
  tu_edpt_state_t* ep_state = &dev->ep_status[epnum][dir];

  TU_LOG_USBH("  Queue EP %02X with %u bytes ... ", ep_addr, total_bytes);

  // Attempt to transfer on a busy endpoint, sound like an race condition !
  TU_ASSERT(ep_state->busy == 0);

  // Set busy first since the actual transfer can be complete before hcd_edpt_xfer()
  // could return and USBH task can preempt and clear the busy
  ep_state->busy = 1;

#if CFG_TUH_API_EDPT_XFER
  dev->ep_callback[epnum][dir].complete_cb = complete_cb;
  dev->ep_callback[epnum][dir].user_data   = user_data;
#endif

  if ( hcd_edpt_xfer(dev->rhport, dev_addr, ep_addr, buffer, total_bytes) )
  {
    TU_LOG_USBH("OK\r\n");
    return true;
  }else
  {
    // HCD error, mark endpoint as ready to allow next transfer
    ep_state->busy    = 0;
    ep_state->claimed = 0;
    TU_LOG1("Failed\r\n");
    TU_BREAKPOINT();
    return false;
  }
}

static bool usbh_edpt_control_open(uint8_t dev_addr, uint8_t max_packet_size)
{
  TU_LOG_USBH("[%u:%u] Open EP0 with Size = %u\r\n", usbh_get_rhport(dev_addr), dev_addr, max_packet_size);

  tusb_desc_endpoint_t ep0_desc =
  {
    .bLength          = sizeof(tusb_desc_endpoint_t),
    .bDescriptorType  = TUSB_DESC_ENDPOINT,
    .bEndpointAddress = 0,
    .bmAttributes     = { .xfer = TUSB_XFER_CONTROL },
    .wMaxPacketSize   = max_packet_size,
    .bInterval        = 0
  };

  return hcd_edpt_open(usbh_get_rhport(dev_addr), dev_addr, &ep0_desc);
}

bool tuh_edpt_open(uint8_t dev_addr, tusb_desc_endpoint_t const * desc_ep)
{
  TU_ASSERT( tu_edpt_validate(desc_ep, tuh_speed_get(dev_addr)) );

  return hcd_edpt_open(usbh_get_rhport(dev_addr), dev_addr, desc_ep);
}

bool usbh_edpt_busy(uint8_t dev_addr, uint8_t ep_addr)
{
  uint8_t const epnum = tu_edpt_number(ep_addr);
  uint8_t const dir   = tu_edpt_dir(ep_addr);

  usbh_device_t* dev = get_device(dev_addr);
  TU_VERIFY(dev);

  return dev->ep_status[epnum][dir].busy;
}

//--------------------------------------------------------------------+
// HCD Event Handler
//--------------------------------------------------------------------+

void hcd_devtree_get_info(uint8_t dev_addr, hcd_devtree_info_t* devtree_info)
{
  usbh_device_t const* dev = get_device(dev_addr);

  if (dev)
  {
    devtree_info->rhport   = dev->rhport;
    devtree_info->hub_addr = dev->hub_addr;
    devtree_info->hub_port = dev->hub_port;
    devtree_info->speed    = dev->speed;
  }else
  {
    devtree_info->rhport   = _dev0.rhport;
    devtree_info->hub_addr = _dev0.hub_addr;
    devtree_info->hub_port = _dev0.hub_port;
    devtree_info->speed    = _dev0.speed;
  }
}

TU_ATTR_FAST_FUNC void hcd_event_handler(hcd_event_t const* event, bool in_isr)
{
  switch (event->event_id)
  {
    default:
      osal_queue_send(_usbh_q, event, in_isr);
    break;
  }
}

//--------------------------------------------------------------------+
// Descriptors Async
//--------------------------------------------------------------------+

// generic helper to get a descriptor
// if blocking, user_data could be pointed to xfer_result
static bool _get_descriptor(uint8_t daddr, uint8_t type, uint8_t index, uint16_t language_id, void* buffer, uint16_t len,
                            tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  tusb_control_request_t const request =
  {
    .bmRequestType_bit =
    {
      .recipient = TUSB_REQ_RCPT_DEVICE,
      .type      = TUSB_REQ_TYPE_STANDARD,
      .direction = TUSB_DIR_IN
    },
    .bRequest = TUSB_REQ_GET_DESCRIPTOR,
    .wValue   = tu_htole16( TU_U16(type, index) ),
    .wIndex   = tu_htole16(language_id),
    .wLength  = tu_htole16(len)
  };

  tuh_xfer_t xfer =
  {
    .daddr       = daddr,
    .ep_addr     = 0,
    .setup       = &request,
    .buffer      = buffer,
    .complete_cb = complete_cb,
    .user_data   = user_data
  };

  bool const ret = tuh_control_xfer(&xfer);

  // if blocking, user_data could be pointed to xfer_result
  if ( !complete_cb && user_data )
  {
    *((xfer_result_t*) user_data) = xfer.result;
  }

  return ret;
}

bool tuh_descriptor_get(uint8_t daddr, uint8_t type, uint8_t index, void* buffer, uint16_t len,
                        tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  return _get_descriptor(daddr, type, index, 0x0000, buffer, len, complete_cb, user_data);
}

bool tuh_descriptor_get_device(uint8_t daddr, void* buffer, uint16_t len,
                               tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  len = tu_min16(len, sizeof(tusb_desc_device_t));
  return tuh_descriptor_get(daddr, TUSB_DESC_DEVICE, 0, buffer, len, complete_cb, user_data);
}

bool tuh_descriptor_get_configuration(uint8_t daddr, uint8_t index, void* buffer, uint16_t len,
                                      tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  return tuh_descriptor_get(daddr, TUSB_DESC_CONFIGURATION, index, buffer, len, complete_cb, user_data);
}

//------------- String Descriptor -------------//

bool tuh_descriptor_get_string(uint8_t daddr, uint8_t index, uint16_t language_id, void* buffer, uint16_t len,
                               tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  return _get_descriptor(daddr, TUSB_DESC_STRING, index, language_id, buffer, len, complete_cb, user_data);
}

// Get manufacturer string descriptor
bool tuh_descriptor_get_manufacturer_string(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len,
                                            tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  usbh_device_t const* dev = get_device(daddr);
  TU_VERIFY(dev && dev->i_manufacturer);
  return tuh_descriptor_get_string(daddr, dev->i_manufacturer, language_id, buffer, len, complete_cb, user_data);
}

// Get product string descriptor
bool tuh_descriptor_get_product_string(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len,
                                       tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  usbh_device_t const* dev = get_device(daddr);
  TU_VERIFY(dev && dev->i_product);
  return tuh_descriptor_get_string(daddr, dev->i_product, language_id, buffer, len, complete_cb, user_data);
}

// Get serial string descriptor
bool tuh_descriptor_get_serial_string(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len,
                                      tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  usbh_device_t const* dev = get_device(daddr);
  TU_VERIFY(dev && dev->i_serial);
  return tuh_descriptor_get_string(daddr, dev->i_serial, language_id, buffer, len, complete_cb, user_data);
}

// Get HID report descriptor
// if blocking, user_data could be pointed to xfer_result
bool tuh_descriptor_get_hid_report(uint8_t daddr, uint8_t itf_num, uint8_t desc_type, uint8_t index, void* buffer, uint16_t len,
                                   tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  TU_LOG_USBH("HID Get Report Descriptor\r\n");
  tusb_control_request_t const request =
  {
    .bmRequestType_bit =
    {
      .recipient = TUSB_REQ_RCPT_INTERFACE,
      .type      = TUSB_REQ_TYPE_STANDARD,
      .direction = TUSB_DIR_IN
    },
    .bRequest = TUSB_REQ_GET_DESCRIPTOR,
    .wValue   = tu_htole16(TU_U16(desc_type, index)),
    .wIndex   = tu_htole16((uint16_t) itf_num),
    .wLength  = len
  };

  tuh_xfer_t xfer =
  {
    .daddr       = daddr,
    .ep_addr     = 0,
    .setup       = &request,
    .buffer      = buffer,
    .complete_cb = complete_cb,
    .user_data   = user_data
  };

  bool const ret = tuh_control_xfer(&xfer);

  // if blocking, user_data could be pointed to xfer_result
  if ( !complete_cb && user_data )
  {
    *((xfer_result_t*) user_data) = xfer.result;
  }

  return ret;
}

bool tuh_configuration_set(uint8_t daddr, uint8_t config_num,
                           tuh_xfer_cb_t complete_cb, uintptr_t user_data)
{
  TU_LOG_USBH("Set Configuration = %d\r\n", config_num);

  tusb_control_request_t const request =
  {
    .bmRequestType_bit =
    {
      .recipient = TUSB_REQ_RCPT_DEVICE,
      .type      = TUSB_REQ_TYPE_STANDARD,
      .direction = TUSB_DIR_OUT
    },
    .bRequest = TUSB_REQ_SET_CONFIGURATION,
    .wValue   = tu_htole16(config_num),
    .wIndex   = 0,
    .wLength  = 0
  };

  tuh_xfer_t xfer =
  {
    .daddr       = daddr,
    .ep_addr     = 0,
    .setup       = &request,
    .buffer      = NULL,
    .complete_cb = complete_cb,
    .user_data   = user_data
  };

  return tuh_control_xfer(&xfer);
}

//--------------------------------------------------------------------+
// Descriptor Sync
//--------------------------------------------------------------------+

#define _CONTROL_SYNC_API(_async_func, ...) \
  xfer_result_t result = XFER_RESULT_INVALID;\
  TU_VERIFY(_async_func(__VA_ARGS__, NULL, (uintptr_t) &result), XFER_RESULT_TIMEOUT); \
  return (uint8_t) result

uint8_t tuh_descriptor_get_sync(uint8_t daddr, uint8_t type, uint8_t index, void* buffer, uint16_t len)
{
  _CONTROL_SYNC_API(tuh_descriptor_get, daddr, type, index, buffer, len);
}

uint8_t tuh_descriptor_get_device_sync(uint8_t daddr, void* buffer, uint16_t len)
{
  _CONTROL_SYNC_API(tuh_descriptor_get_device, daddr, buffer, len);
}

uint8_t tuh_descriptor_get_configuration_sync(uint8_t daddr, uint8_t index, void* buffer, uint16_t len)
{
  _CONTROL_SYNC_API(tuh_descriptor_get_configuration, daddr, index, buffer, len);
}

uint8_t tuh_descriptor_get_hid_report_sync(uint8_t daddr, uint8_t itf_num, uint8_t desc_type, uint8_t index, void* buffer, uint16_t len)
{
  _CONTROL_SYNC_API(tuh_descriptor_get_hid_report, daddr, itf_num, desc_type, index, buffer, len);
}

uint8_t tuh_descriptor_get_string_sync(uint8_t daddr, uint8_t index, uint16_t language_id, void* buffer, uint16_t len)
{
  _CONTROL_SYNC_API(tuh_descriptor_get_string, daddr, index, language_id, buffer, len);
}

uint8_t tuh_descriptor_get_manufacturer_string_sync(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len)
{
  _CONTROL_SYNC_API(tuh_descriptor_get_manufacturer_string, daddr, language_id, buffer, len);
}

uint8_t tuh_descriptor_get_product_string_sync(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len)
{
  _CONTROL_SYNC_API(tuh_descriptor_get_product_string, daddr, language_id, buffer, len);
}

uint8_t tuh_descriptor_get_serial_string_sync(uint8_t daddr, uint16_t language_id, void* buffer, uint16_t len)
{
  _CONTROL_SYNC_API(tuh_descriptor_get_serial_string, daddr, language_id, buffer, len);
}

//--------------------------------------------------------------------+
//
//--------------------------------------------------------------------+

TU_ATTR_ALWAYS_INLINE
static inline bool is_hub_addr(uint8_t daddr)
{
  return (CFG_TUH_HUB > 0) && (daddr > CFG_TUH_DEVICE_MAX);
}

// a device unplugged from rhport:hub_addr:hub_port
static void process_device_unplugged(uint8_t rhport, uint8_t hub_addr, uint8_t hub_port)
{
  //------------- find the all devices (star-network) under port that is unplugged -------------//
  // TODO mark as disconnected in ISR, also handle dev0
  for ( uint8_t dev_id = 0; dev_id < TU_ARRAY_SIZE(_usbh_devices); dev_id++ )
  {
    usbh_device_t* dev = &_usbh_devices[dev_id];
    uint8_t const dev_addr = dev_id+1;

    // TODO Hub multiple level
    if (dev->rhport == rhport   &&
        (hub_addr == 0 || dev->hub_addr == hub_addr) && // hub_addr = 0 means roothub
        (hub_port == 0 || dev->hub_port == hub_port) && // hub_port = 0 means all devices of downstream hub
        dev->connected)
    {
      TU_LOG_USBH("  Address = %u\r\n", dev_addr);

      if (is_hub_addr(dev_addr))
      {
        TU_LOG(USBH_DEBUG, "HUB address = %u is unmounted\r\n", dev_addr);
        // If the device itself is a usb hub, unplug downstream devices.
        // FIXME un-roll recursive calls to prevent potential stack overflow
        process_device_unplugged(rhport, dev_addr, 0);
      }else
      {
        // Invoke callback before closing driver
        if (tuh_umount_cb) tuh_umount_cb(dev_addr);
      }

      // Close class driver
      for (uint8_t drv_id = 0; drv_id < USBH_CLASS_DRIVER_COUNT; drv_id++)
      {
        TU_LOG_USBH("%s close\r\n", usbh_class_drivers[drv_id].name);
        usbh_class_drivers[drv_id].close(dev_addr);
      }

      hcd_device_close(rhport, dev_addr);
      clear_device(dev);
      // abort on-going control xfer if any
      if (_ctrl_xfer.daddr == dev_addr) _set_control_xfer_stage(CONTROL_STAGE_IDLE);
    }
  }
}

//--------------------------------------------------------------------+
// Enumeration Process
// is a lengthy process with a series of control transfer to configure
// newly attached device.
// NOTE: due to the shared _usbh_ctrl_buf, we must complete enumerating
// one device before enumerating another one.
//--------------------------------------------------------------------+

enum {
  ENUM_IDLE,
  ENUM_RESET_1,         // 1st reset when attached
  //ENUM_HUB_GET_STATUS_1,
  ENUM_HUB_CLEAR_RESET_1,
  ENUM_ADDR0_DEVICE_DESC,
  ENUM_RESET_2,         // 2nd reset before set address (not used)
  ENUM_HUB_GET_STATUS_2,
  ENUM_HUB_CLEAR_RESET_2,
  ENUM_SET_ADDR,

  ENUM_GET_DEVICE_DESC,
  ENUM_GET_9BYTE_CONFIG_DESC,
  ENUM_GET_FULL_CONFIG_DESC,
  ENUM_SET_CONFIG,
  ENUM_CONFIG_DRIVER
};

static bool enum_request_set_addr(void);
static bool _parse_configuration_descriptor (uint8_t dev_addr, tusb_desc_configuration_t const* desc_cfg);
static void enum_full_complete(void);

// process device enumeration
static void process_enumeration(tuh_xfer_t* xfer)
{
  // Retry a few times with transfers in enumeration since device can be unstable when starting up
  enum {
    ATTEMPT_COUNT_MAX = 3,
    ATTEMPT_DELAY_MS = 100
  };
  static uint8_t failed_count = 0;

  if (XFER_RESULT_SUCCESS != xfer->result)
  {
    // retry if not reaching max attempt
    if ( failed_count < ATTEMPT_COUNT_MAX )
    {
      failed_count++;
      osal_task_delay(ATTEMPT_DELAY_MS); // delay a bit
      TU_ASSERT(tuh_control_xfer(xfer), );
    }else
    {
      enum_full_complete();
    }
    return;
  }
  failed_count = 0;

  uint8_t const daddr = xfer->daddr;
  uintptr_t const state = xfer->user_data;

  switch(state)
  {
#if CFG_TUH_HUB
    //case ENUM_HUB_GET_STATUS_1: break;

    case ENUM_HUB_CLEAR_RESET_1:
    {
      hub_port_status_response_t port_status;
      memcpy(&port_status, _usbh_ctrl_buf, sizeof(hub_port_status_response_t));

      if ( !port_status.status.connection )
      {
        // device unplugged while delaying, nothing else to do
        enum_full_complete();
        return;
      }

      _dev0.speed = (port_status.status.high_speed) ? TUSB_SPEED_HIGH :
                    (port_status.status.low_speed ) ? TUSB_SPEED_LOW  : TUSB_SPEED_FULL;

      // Acknowledge Port Reset Change
      if (port_status.change.reset)
      {
        hub_port_clear_reset_change(_dev0.hub_addr, _dev0.hub_port, process_enumeration, ENUM_ADDR0_DEVICE_DESC);
      }
    }
    break;

    case ENUM_HUB_GET_STATUS_2:
      osal_task_delay(RESET_DELAY);
      TU_ASSERT( hub_port_get_status(_dev0.hub_addr, _dev0.hub_port, _usbh_ctrl_buf, process_enumeration, ENUM_HUB_CLEAR_RESET_2), );
    break;

    case ENUM_HUB_CLEAR_RESET_2:
    {
      hub_port_status_response_t port_status;
      memcpy(&port_status, _usbh_ctrl_buf, sizeof(hub_port_status_response_t));

      // Acknowledge Port Reset Change if Reset Successful
      if (port_status.change.reset)
      {
        TU_ASSERT( hub_port_clear_reset_change(_dev0.hub_addr, _dev0.hub_port, process_enumeration, ENUM_SET_ADDR), );
      }
    }
    break;
#endif

    case ENUM_ADDR0_DEVICE_DESC:
    {
      // TODO probably doesn't need to open/close each enumeration
      uint8_t const addr0 = 0;
      TU_ASSERT( usbh_edpt_control_open(addr0, 8), );

      // Get first 8 bytes of device descriptor for Control Endpoint size
      TU_LOG_USBH("Get 8 byte of Device Descriptor\r\n");
      TU_ASSERT(tuh_descriptor_get_device(addr0, _usbh_ctrl_buf, 8, process_enumeration, ENUM_SET_ADDR), );
    }
    break;

#if 0
    case ENUM_RESET_2:
      // TODO not used by now, but may be needed for some devices !?
      // Reset device again before Set Address
      TU_LOG_USBH("Port reset2 \r\n");
      if (_dev0.hub_addr == 0)
      {
        // connected directly to roothub
        hcd_port_reset( _dev0.rhport );
        osal_task_delay(RESET_DELAY); // TODO may not work for no-OS on MCU that require reset_end() since
                                      // sof of controller may not running while resetting
        hcd_port_reset_end(_dev0.rhport);
        // TODO: fall through to SET ADDRESS, refactor later
      }
      #if CFG_TUH_HUB
      else
      {
        // after RESET_DELAY the hub_port_reset() already complete
        TU_ASSERT( hub_port_reset(_dev0.hub_addr, _dev0.hub_port, process_enumeration, ENUM_HUB_GET_STATUS_2), );
        break;
      }
      #endif
      TU_ATTR_FALLTHROUGH;
#endif

    case ENUM_SET_ADDR:
      enum_request_set_addr();
    break;

    case ENUM_GET_DEVICE_DESC:
    {
      uint8_t const new_addr = (uint8_t) tu_le16toh(xfer->setup->wValue);

      usbh_device_t* new_dev = get_device(new_addr);
      TU_ASSERT(new_dev, );
      new_dev->addressed = 1;

      // Close device 0
      hcd_device_close(_dev0.rhport, 0);

      // open control pipe for new address
      TU_ASSERT( usbh_edpt_control_open(new_addr, new_dev->ep0_size), );

      // Get full device descriptor
      TU_LOG_USBH("Get Device Descriptor\r\n");
      TU_ASSERT(tuh_descriptor_get_device(new_addr, _usbh_ctrl_buf, sizeof(tusb_desc_device_t), process_enumeration, ENUM_GET_9BYTE_CONFIG_DESC), );
    }
    break;

    case ENUM_GET_9BYTE_CONFIG_DESC:
    {
      tusb_desc_device_t const * desc_device = (tusb_desc_device_t const*) _usbh_ctrl_buf;
      usbh_device_t* dev = get_device(daddr);
      TU_ASSERT(dev, );

      dev->vid            = desc_device->idVendor;
      dev->pid            = desc_device->idProduct;
      dev->i_manufacturer = desc_device->iManufacturer;
      dev->i_product      = desc_device->iProduct;
      dev->i_serial       = desc_device->iSerialNumber;

    //  if (tuh_attach_cb) tuh_attach_cb((tusb_desc_device_t*) _usbh_ctrl_buf);

      // Get 9-byte for total length
      uint8_t const config_idx = CONFIG_NUM - 1;
      TU_LOG_USBH("Get Configuration[0] Descriptor (9 bytes)\r\n");
      TU_ASSERT( tuh_descriptor_get_configuration(daddr, config_idx, _usbh_ctrl_buf, 9, process_enumeration, ENUM_GET_FULL_CONFIG_DESC), );
    }
    break;

    case ENUM_GET_FULL_CONFIG_DESC:
    {
      uint8_t const * desc_config = _usbh_ctrl_buf;

      // Use offsetof to avoid pointer to the odd/misaligned address
      uint16_t const total_len = tu_le16toh( tu_unaligned_read16(desc_config + offsetof(tusb_desc_configuration_t, wTotalLength)) );

      // TODO not enough buffer to hold configuration descriptor
      TU_ASSERT(total_len <= CFG_TUH_ENUMERATION_BUFSIZE, );

      // Get full configuration descriptor
      uint8_t const config_idx = CONFIG_NUM - 1;
      TU_LOG_USBH("Get Configuration[0] Descriptor\r\n");
      TU_ASSERT( tuh_descriptor_get_configuration(daddr, config_idx, _usbh_ctrl_buf, total_len, process_enumeration, ENUM_SET_CONFIG), );
    }
    break;

    case ENUM_SET_CONFIG:
      // Parse configuration & set up drivers
      // Driver open aren't allowed to make any usb transfer yet
      TU_ASSERT( _parse_configuration_descriptor(daddr, (tusb_desc_configuration_t*) _usbh_ctrl_buf), );

      TU_ASSERT( tuh_configuration_set(daddr, CONFIG_NUM, process_enumeration, ENUM_CONFIG_DRIVER), );
    break;

    case ENUM_CONFIG_DRIVER:
    {
      TU_LOG_USBH("Device configured\r\n");
      usbh_device_t* dev = get_device(daddr);
      TU_ASSERT(dev, );

      dev->configured = 1;

      // Start the Set Configuration process for interfaces (itf = DRVID_INVALID)
      // Since driver can perform control transfer within its set_config, this is done asynchronously.
      // The process continue with next interface when class driver complete its sequence with usbh_driver_set_config_complete()
      // TODO use separated API instead of using DRVID_INVALID
      usbh_driver_set_config_complete(daddr, DRVID_INVALID);
    }
    break;

    default:
      // stop enumeration if unknown state
      enum_full_complete();
    break;
  }
}

static bool enum_new_device(hcd_event_t* event)
{
  _dev0.rhport   = event->rhport;
  _dev0.hub_addr = event->connection.hub_addr;
  _dev0.hub_port = event->connection.hub_port;

  if (_dev0.hub_addr == 0)
  {
    // connected/disconnected directly with roothub
    // wait until device is stable TODO non blocking
    hcd_port_reset(_dev0.rhport);
    osal_task_delay(RESET_DELAY); // TODO may not work for no-OS on MCU that require reset_end() since
                                  // sof of controller may not running while resetting
    hcd_port_reset_end( _dev0.rhport);

    // device unplugged while delaying
    if ( !hcd_port_connect_status(_dev0.rhport) ) return true;

    _dev0.speed = hcd_port_speed_get(_dev0.rhport );
    TU_LOG_USBH("%s Speed\r\n", tu_str_speed[_dev0.speed]);

    // fake transfer to kick-off the enumeration process
    tuh_xfer_t xfer;
    xfer.daddr     = 0;
    xfer.result    = XFER_RESULT_SUCCESS;
    xfer.user_data = ENUM_ADDR0_DEVICE_DESC;

    process_enumeration(&xfer);

  }
#if CFG_TUH_HUB
  else
  {
    // connected/disconnected via external hub
    // wait until device is stable
    osal_task_delay(RESET_DELAY);

    // ENUM_HUB_GET_STATUS
    //TU_ASSERT( hub_port_get_status(_dev0.hub_addr, _dev0.hub_port, _usbh_ctrl_buf, enum_hub_get_status0_complete, 0) );
    TU_ASSERT( hub_port_get_status(_dev0.hub_addr, _dev0.hub_port, _usbh_ctrl_buf, process_enumeration, ENUM_HUB_CLEAR_RESET_1) );
  }
#endif // hub

  return true;
}

static uint8_t get_new_address(bool is_hub)
{
  uint8_t start;
  uint8_t end;
  if ( is_hub )
  {
    start = CFG_TUH_DEVICE_MAX;
    end   = start + CFG_TUH_HUB;
  }else
  {
    start = 0;
    end   = start + CFG_TUH_DEVICE_MAX;
  }

  for ( uint8_t idx = start; idx < end; idx++)
  {
    if (!_usbh_devices[idx].connected) return (idx+1);
  }

  return 0; // invalid address
}

static bool enum_request_set_addr(void)
{
  tusb_desc_device_t const * desc_device = (tusb_desc_device_t const*) _usbh_ctrl_buf;

  // Get new address
  uint8_t const new_addr = get_new_address(desc_device->bDeviceClass == TUSB_CLASS_HUB);
  TU_ASSERT(new_addr != 0);

  TU_LOG_USBH("Set Address = %d\r\n", new_addr);

  usbh_device_t* new_dev = get_device(new_addr);

  new_dev->rhport    = _dev0.rhport;
  new_dev->hub_addr  = _dev0.hub_addr;
  new_dev->hub_port  = _dev0.hub_port;
  new_dev->speed     = _dev0.speed;
  new_dev->connected = 1;
  new_dev->ep0_size  = desc_device->bMaxPacketSize0;

  tusb_control_request_t const request =
  {
    .bmRequestType_bit =
    {
      .recipient = TUSB_REQ_RCPT_DEVICE,
      .type      = TUSB_REQ_TYPE_STANDARD,
      .direction = TUSB_DIR_OUT
    },
    .bRequest = TUSB_REQ_SET_ADDRESS,
    .wValue   = tu_htole16(new_addr),
    .wIndex   = 0,
    .wLength  = 0
  };

  tuh_xfer_t xfer =
  {
    .daddr       = 0, // dev0
    .ep_addr     = 0,
    .setup       = &request,
    .buffer      = NULL,
    .complete_cb = process_enumeration,
    .user_data   = ENUM_GET_DEVICE_DESC
  };

  TU_ASSERT( tuh_control_xfer(&xfer) );

  return true;
}

static bool _parse_configuration_descriptor(uint8_t dev_addr, tusb_desc_configuration_t const* desc_cfg)
{
  usbh_device_t* dev = get_device(dev_addr);

  uint16_t const total_len = tu_le16toh(desc_cfg->wTotalLength);
  uint8_t const* desc_end = ((uint8_t const*) desc_cfg) + total_len;
  uint8_t const* p_desc   = tu_desc_next(desc_cfg);

  TU_LOG_USBH("Parsing Configuration descriptor (wTotalLength = %u)\r\n", total_len);

  // parse each interfaces
  while( p_desc < desc_end )
  {
    uint8_t assoc_itf_count = 1;

    // Class will always starts with Interface Association (if any) and then Interface descriptor
    if ( TUSB_DESC_INTERFACE_ASSOCIATION == tu_desc_type(p_desc) )
    {
      tusb_desc_interface_assoc_t const * desc_iad = (tusb_desc_interface_assoc_t const *) p_desc;
      assoc_itf_count = desc_iad->bInterfaceCount;

      p_desc = tu_desc_next(p_desc); // next to Interface

      // IAD's first interface number and class should match with opened interface
      //TU_ASSERT(desc_iad->bFirstInterface == desc_itf->bInterfaceNumber &&
      //          desc_iad->bFunctionClass  == desc_itf->bInterfaceClass);
    }

    TU_ASSERT( TUSB_DESC_INTERFACE == tu_desc_type(p_desc) );
    tusb_desc_interface_t const* desc_itf = (tusb_desc_interface_t const*) p_desc;

#if CFG_TUH_MIDI
    // MIDI has 2 interfaces (Audio Control v1 + MIDIStreaming) but does not have IAD
    // manually force associated count = 2
    if (1                              == assoc_itf_count              &&
        TUSB_CLASS_AUDIO               == desc_itf->bInterfaceClass    &&
        AUDIO_SUBCLASS_CONTROL         == desc_itf->bInterfaceSubClass &&
        AUDIO_FUNC_PROTOCOL_CODE_UNDEF == desc_itf->bInterfaceProtocol)
    {
      assoc_itf_count = 2;
    }
#endif

#if CFG_TUH_CDC
    // Some legacy CDC device does not use IAD but rather use device class as hint to combine 2 interfaces
    // manually force associated count = 2
    if (1                                        == assoc_itf_count              &&
        TUSB_CLASS_CDC                           == desc_itf->bInterfaceClass    &&
        CDC_COMM_SUBCLASS_ABSTRACT_CONTROL_MODEL == desc_itf->bInterfaceSubClass)
    {
      assoc_itf_count = 2;
    }
#endif

    uint16_t const drv_len = tu_desc_get_interface_total_len(desc_itf, assoc_itf_count, (uint16_t) (desc_end-p_desc));
    TU_ASSERT(drv_len >= sizeof(tusb_desc_interface_t));

    // Find driver for this interface
    for (uint8_t drv_id = 0; drv_id < USBH_CLASS_DRIVER_COUNT; drv_id++)
    {
      usbh_class_driver_t const * driver = &usbh_class_drivers[drv_id];

      if ( driver->open(dev->rhport, dev_addr, desc_itf, drv_len) )
      {
        // open successfully
        TU_LOG_USBH("  %s opened\r\n", driver->name);

        // bind (associated) interfaces to found driver
        for(uint8_t i=0; i<assoc_itf_count; i++)
        {
          uint8_t const itf_num = desc_itf->bInterfaceNumber+i;

          // Interface number must not be used already
          TU_ASSERT( DRVID_INVALID == dev->itf2drv[itf_num] );
          dev->itf2drv[itf_num] = drv_id;
        }

        // bind all endpoints to found driver
        tu_edpt_bind_driver(dev->ep2drv, desc_itf, drv_len, drv_id);

        break; // exit driver find loop
      }

      if( drv_id >= USBH_CLASS_DRIVER_COUNT )
      {
        TU_LOG(USBH_DEBUG, "Interface %u: class = %u subclass = %u protocol = %u is not supported\r\n",
               desc_itf->bInterfaceNumber, desc_itf->bInterfaceClass, desc_itf->bInterfaceSubClass, desc_itf->bInterfaceProtocol);
      }
    }

    // next Interface or IAD descriptor
    p_desc += drv_len;
  }

  return true;
}

void usbh_driver_set_config_complete(uint8_t dev_addr, uint8_t itf_num)
{
  usbh_device_t* dev = get_device(dev_addr);

  for(itf_num++; itf_num < CFG_TUH_INTERFACE_MAX; itf_num++)
  {
    // continue with next valid interface
    // IAD binding interface such as CDCs should return itf_num + 1 when complete
    // with usbh_driver_set_config_complete()
    uint8_t const drv_id = dev->itf2drv[itf_num];
    if (drv_id != DRVID_INVALID)
    {
      usbh_class_driver_t const * driver = &usbh_class_drivers[drv_id];
      TU_LOG_USBH("%s set config: itf = %u\r\n", driver->name, itf_num);
      driver->set_config(dev_addr, itf_num);
      break;
    }
  }

  // all interface are configured
  if (itf_num == CFG_TUH_INTERFACE_MAX)
  {
    enum_full_complete();

    if (is_hub_addr(dev_addr))
    {
      TU_LOG(USBH_DEBUG, "HUB address = %u is mounted\r\n", dev_addr);
    }else
    {
      // Invoke callback if available
      if (tuh_mount_cb) tuh_mount_cb(dev_addr);
    }
  }
}

static void enum_full_complete(void)
{
#if CFG_TUH_HUB
  // get next hub status
  if (_dev0.hub_addr) hub_edpt_status_xfer(_dev0.hub_addr);
#endif

}

#endif
