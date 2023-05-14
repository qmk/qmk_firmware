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

#if CFG_TUH_ENABLED || CFG_TUD_ENABLED

#include "tusb.h"
#include "common/tusb_private.h"

#if CFG_TUD_ENABLED
#include "device/usbd_pvt.h"
#endif

#if CFG_TUH_ENABLED
#include "host/usbh_classdriver.h"
#endif

//--------------------------------------------------------------------+
// Public API
//--------------------------------------------------------------------+

bool tusb_init(void)
{
#if CFG_TUD_ENABLED && defined(TUD_OPT_RHPORT)
  // init device stack CFG_TUSB_RHPORTx_MODE must be defined
  TU_ASSERT ( tud_init(TUD_OPT_RHPORT) );
#endif

#if CFG_TUH_ENABLED && defined(TUH_OPT_RHPORT)
  // init host stack CFG_TUSB_RHPORTx_MODE must be defined
  TU_ASSERT( tuh_init(TUH_OPT_RHPORT) );
#endif

  return true;
}

bool tusb_inited(void)
{
  bool ret = false;

#if CFG_TUD_ENABLED
  ret = ret || tud_inited();
#endif

#if CFG_TUH_ENABLED
  ret = ret || tuh_inited();
#endif

  return ret;
}

//--------------------------------------------------------------------+
// Descriptor helper
//--------------------------------------------------------------------+

uint8_t const * tu_desc_find(uint8_t const* desc, uint8_t const* end, uint8_t byte1)
{
  while(desc+1 < end)
  {
    if ( desc[1] == byte1 ) return desc;
    desc += desc[DESC_OFFSET_LEN];
  }
  return NULL;
}

uint8_t const * tu_desc_find2(uint8_t const* desc, uint8_t const* end, uint8_t byte1, uint8_t byte2)
{
  while(desc+2 < end)
  {
    if ( desc[1] == byte1 && desc[2] == byte2) return desc;
    desc += desc[DESC_OFFSET_LEN];
  }
  return NULL;
}

uint8_t const * tu_desc_find3(uint8_t const* desc, uint8_t const* end, uint8_t byte1, uint8_t byte2, uint8_t byte3)
{
  while(desc+3 < end)
  {
    if (desc[1] == byte1 && desc[2] == byte2 && desc[3] == byte3) return desc;
    desc += desc[DESC_OFFSET_LEN];
  }
  return NULL;
}


//--------------------------------------------------------------------+
// Endpoint Helper for both Host and Device stack
//--------------------------------------------------------------------+

bool tu_edpt_claim(tu_edpt_state_t* ep_state, osal_mutex_t mutex)
{
  (void) mutex;

  // pre-check to help reducing mutex lock
  TU_VERIFY((ep_state->busy == 0) && (ep_state->claimed == 0));
  (void) osal_mutex_lock(mutex, OSAL_TIMEOUT_WAIT_FOREVER);

  // can only claim the endpoint if it is not busy and not claimed yet.
  bool const available = (ep_state->busy == 0) && (ep_state->claimed == 0);
  if (available)
  {
    ep_state->claimed = 1;
  }

  (void) osal_mutex_unlock(mutex);

  return available;
}

bool tu_edpt_release(tu_edpt_state_t* ep_state, osal_mutex_t mutex)
{
  (void) mutex;

  (void) osal_mutex_lock(mutex, OSAL_TIMEOUT_WAIT_FOREVER);

  // can only release the endpoint if it is claimed and not busy
  bool const ret = (ep_state->claimed == 1) && (ep_state->busy == 0);
  if (ret)
  {
    ep_state->claimed = 0;
  }

  (void) osal_mutex_unlock(mutex);

  return ret;
}

bool tu_edpt_validate(tusb_desc_endpoint_t const * desc_ep, tusb_speed_t speed)
{
  uint16_t const max_packet_size = tu_edpt_packet_size(desc_ep);
  TU_LOG2("  Open EP %02X with Size = %u\r\n", desc_ep->bEndpointAddress, max_packet_size);

  switch (desc_ep->bmAttributes.xfer)
  {
    case TUSB_XFER_ISOCHRONOUS:
    {
      uint16_t const spec_size = (speed == TUSB_SPEED_HIGH ? 1024 : 1023);
      TU_ASSERT(max_packet_size <= spec_size);
    }
    break;

    case TUSB_XFER_BULK:
      if (speed == TUSB_SPEED_HIGH)
      {
        // Bulk highspeed must be EXACTLY 512
        TU_ASSERT(max_packet_size == 512);
      }else
      {
        // TODO Bulk fullspeed can only be 8, 16, 32, 64
        TU_ASSERT(max_packet_size <= 64);
      }
    break;

    case TUSB_XFER_INTERRUPT:
    {
      uint16_t const spec_size = (speed == TUSB_SPEED_HIGH ? 1024 : 64);
      TU_ASSERT(max_packet_size <= spec_size);
    }
    break;

    default: return false;
  }

  return true;
}

void tu_edpt_bind_driver(uint8_t ep2drv[][2], tusb_desc_interface_t const* desc_itf, uint16_t desc_len, uint8_t driver_id)
{
  uint8_t const* p_desc = (uint8_t const*) desc_itf;
  uint8_t const* desc_end = p_desc + desc_len;

  while( p_desc < desc_end )
  {
    if ( TUSB_DESC_ENDPOINT == tu_desc_type(p_desc) )
    {
      uint8_t const ep_addr = ((tusb_desc_endpoint_t const*) p_desc)->bEndpointAddress;

      TU_LOG(2, "  Bind EP %02x to driver id %u\r\n", ep_addr, driver_id);
      ep2drv[tu_edpt_number(ep_addr)][tu_edpt_dir(ep_addr)] = driver_id;
    }

    p_desc = tu_desc_next(p_desc);
  }
}

uint16_t tu_desc_get_interface_total_len(tusb_desc_interface_t const* desc_itf, uint8_t itf_count, uint16_t max_len)
{
  uint8_t const* p_desc = (uint8_t const*) desc_itf;
  uint16_t len = 0;

  while (itf_count--)
  {
    // Next on interface desc
    len += tu_desc_len(desc_itf);
    p_desc = tu_desc_next(p_desc);

    while (len < max_len)
    {
      // return on IAD regardless of itf count
      if ( tu_desc_type(p_desc) == TUSB_DESC_INTERFACE_ASSOCIATION ) return len;

      if ( (tu_desc_type(p_desc) == TUSB_DESC_INTERFACE) &&
           ((tusb_desc_interface_t const*) p_desc)->bAlternateSetting == 0 )
      {
        break;
      }

      len += tu_desc_len(p_desc);
      p_desc = tu_desc_next(p_desc);
    }
  }

  return len;
}

//--------------------------------------------------------------------+
// Endpoint Stream Helper for both Host and Device stack
//--------------------------------------------------------------------+

bool tu_edpt_stream_init(tu_edpt_stream_t* s, bool is_host, bool is_tx, bool overwritable,
                         void* ff_buf, uint16_t ff_bufsize, uint8_t* ep_buf, uint16_t ep_bufsize)
{
  osal_mutex_t new_mutex = osal_mutex_create(&s->ff_mutex);
  (void) new_mutex;
  (void) is_tx;

  s->is_host = is_host;
  tu_fifo_config(&s->ff, ff_buf, ff_bufsize, 1, overwritable);
  tu_fifo_config_mutex(&s->ff, is_tx ? new_mutex : NULL, is_tx ? NULL : new_mutex);

  s->ep_buf = ep_buf;
  s->ep_bufsize = ep_bufsize;

  return true;
}

TU_ATTR_ALWAYS_INLINE static inline
bool stream_claim(tu_edpt_stream_t* s)
{
  if (s->is_host)
  {
    #if CFG_TUH_ENABLED
    return usbh_edpt_claim(s->daddr, s->ep_addr);
    #endif
  }else
  {
    #if CFG_TUD_ENABLED
    return usbd_edpt_claim(s->rhport, s->ep_addr);
    #endif
  }

  return false;
}

TU_ATTR_ALWAYS_INLINE static inline
bool stream_xfer(tu_edpt_stream_t* s, uint16_t count)
{
  if (s->is_host)
  {
    #if CFG_TUH_ENABLED
    return usbh_edpt_xfer(s->daddr, s->ep_addr, count ? s->ep_buf : NULL, count);
    #endif
  }else
  {
    #if CFG_TUD_ENABLED
    return usbd_edpt_xfer(s->rhport, s->ep_addr, count ? s->ep_buf : NULL, count);
    #endif
  }

  return false;
}

TU_ATTR_ALWAYS_INLINE static inline
bool stream_release(tu_edpt_stream_t* s)
{
  if (s->is_host)
  {
    #if CFG_TUH_ENABLED
    return usbh_edpt_release(s->daddr, s->ep_addr);
    #endif
  }else
  {
    #if CFG_TUD_ENABLED
    return usbd_edpt_release(s->rhport, s->ep_addr);
    #endif
  }

  return false;
}

//--------------------------------------------------------------------+
// Stream Write
//--------------------------------------------------------------------+

bool tu_edpt_stream_write_zlp_if_needed(tu_edpt_stream_t* s, uint32_t last_xferred_bytes)
{
  // ZLP condition: no pending data, last transferred bytes is multiple of packet size
  TU_VERIFY( !tu_fifo_count(&s->ff) && last_xferred_bytes && (0 == (last_xferred_bytes & (s->ep_packetsize-1))) );

  TU_VERIFY( stream_claim(s) );
  TU_ASSERT( stream_xfer(s, 0) );

  return true;
}

uint32_t tu_edpt_stream_write_xfer(tu_edpt_stream_t* s)
{
  // skip if no data
  TU_VERIFY( tu_fifo_count(&s->ff), 0 );

  // Claim the endpoint
  TU_VERIFY( stream_claim(s), 0 );

  // Pull data from FIFO -> EP buf
  uint16_t const count = tu_fifo_read_n(&s->ff, s->ep_buf, s->ep_bufsize);

  if ( count )
  {
    TU_ASSERT( stream_xfer(s, count), 0 );
    return count;
  }else
  {
    // Release endpoint since we don't make any transfer
    // Note: data is dropped if terminal is not connected
    stream_release(s);
    return 0;
  }
}

uint32_t tu_edpt_stream_write(tu_edpt_stream_t* s, void const *buffer, uint32_t bufsize)
{
  TU_VERIFY(bufsize); // TODO support ZLP

  uint16_t ret = tu_fifo_write_n(&s->ff, buffer, (uint16_t) bufsize);

  // flush if fifo has more than packet size or
  // in rare case: fifo depth is configured too small (which never reach packet size)
  if ( (tu_fifo_count(&s->ff) >= s->ep_packetsize) || (tu_fifo_depth(&s->ff) < s->ep_packetsize) )
  {
    tu_edpt_stream_write_xfer(s);
  }

  return ret;
}

//--------------------------------------------------------------------+
// Stream Read
//--------------------------------------------------------------------+

uint32_t tu_edpt_stream_read_xfer(tu_edpt_stream_t* s)
{
  uint16_t available = tu_fifo_remaining(&s->ff);

  // Prepare for incoming data but only allow what we can store in the ring buffer.
  // TODO Actually we can still carry out the transfer, keeping count of received bytes
  // and slowly move it to the FIFO when read().
  // This pre-check reduces endpoint claiming
  TU_VERIFY(available >= s->ep_packetsize);

  // claim endpoint
  TU_VERIFY(stream_claim(s), 0);

  // get available again since fifo can be changed before endpoint is claimed
  available = tu_fifo_remaining(&s->ff);

  if ( available >= s->ep_packetsize )
  {
    // multiple of packet size limit by ep bufsize
    uint16_t count = (uint16_t) (available & ~(s->ep_packetsize -1));
    count = tu_min16(count, s->ep_bufsize);

    TU_ASSERT( stream_xfer(s, count), 0 );

    return count;
  }else
  {
    // Release endpoint since we don't make any transfer
    stream_release(s);
    return 0;
  }
}

uint32_t tu_edpt_stream_read(tu_edpt_stream_t* s, void* buffer, uint32_t bufsize)
{
  uint32_t num_read = tu_fifo_read_n(&s->ff, buffer, (uint16_t) bufsize);
  tu_edpt_stream_read_xfer(s);
  return num_read;
}

//--------------------------------------------------------------------+
// Debug
//--------------------------------------------------------------------+

#if CFG_TUSB_DEBUG
#include <ctype.h>

#if CFG_TUSB_DEBUG >= 2

char const* const tu_str_speed[] = { "Full", "Low", "High" };
char const* const tu_str_std_request[] =
{
  "Get Status"        ,
  "Clear Feature"     ,
  "Reserved"          ,
  "Set Feature"       ,
  "Reserved"          ,
  "Set Address"       ,
  "Get Descriptor"    ,
  "Set Descriptor"    ,
  "Get Configuration" ,
  "Set Configuration" ,
  "Get Interface"     ,
  "Set Interface"     ,
  "Synch Frame"
};

#endif

static void dump_str_line(uint8_t const* buf, uint16_t count)
{
  tu_printf("  |");

  // each line is 16 bytes
  for(uint16_t i=0; i<count; i++)
  {
    const char ch = buf[i];
    tu_printf("%c", isprint(ch) ? ch : '.');
  }

  tu_printf("|\r\n");
}

/* Print out memory contents
 *  - buf   : buffer
 *  - count : number of item
 *  - indent: prefix spaces on every line
 */
void tu_print_mem(void const *buf, uint32_t count, uint8_t indent)
{
  uint8_t const size = 1; // fixed 1 byte for now

  if ( !buf || !count )
  {
    tu_printf("NULL\r\n");
    return;
  }

  uint8_t const *buf8 = (uint8_t const *) buf;

  char format[] = "%00X";
  format[2] += 2*size;

  const uint8_t item_per_line  = 16 / size;

  for(unsigned int i=0; i<count; i++)
  {
    unsigned int value=0;

    if ( i%item_per_line == 0 )
    {
      // Print Ascii
      if ( i != 0 )
      {
        dump_str_line(buf8-16, 16);
      }

      for(uint8_t s=0; s < indent; s++) tu_printf(" ");

      // print offset or absolute address
      tu_printf("%04X: ", 16*i/item_per_line);
    }

    memcpy(&value, buf8, size);
    buf8 += size;

    tu_printf(" ");
    tu_printf(format, value);
  }

  // fill up last row to 16 for printing ascii
  const uint32_t remain = count%16;
  uint8_t nback = (uint8_t)(remain ? remain : 16);

  if ( remain )
  {
    for(uint32_t i=0; i< 16-remain; i++)
    {
      tu_printf(" ");
      for(int j=0; j<2*size; j++) tu_printf(" ");
    }
  }

  dump_str_line(buf8-nback, nback);
}

#endif

#endif // host or device enabled
