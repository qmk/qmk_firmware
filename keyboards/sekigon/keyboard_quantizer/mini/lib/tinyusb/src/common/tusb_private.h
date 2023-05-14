/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022, Ha Thach (tinyusb.org)
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


#ifndef _TUSB_PRIVATE_H_
#define _TUSB_PRIVATE_H_

// Internal Helper used by Host and Device Stack

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct TU_ATTR_PACKED
{
  volatile uint8_t busy    : 1;
  volatile uint8_t stalled : 1;
  volatile uint8_t claimed : 1;
}tu_edpt_state_t;

typedef struct {
  bool is_host; // host or device most
  union {
      uint8_t daddr;
      uint8_t rhport;
      uint8_t hwid;
  };
  uint8_t ep_addr;
  uint8_t ep_speed;

  uint16_t ep_packetsize;
  uint16_t ep_bufsize;

  // TODO xfer_fifo can skip this buffer
  uint8_t* ep_buf;

  tu_fifo_t ff;

  // mutex: read if ep rx, write if e tx
  OSAL_MUTEX_DEF(ff_mutex);

}tu_edpt_stream_t;

//--------------------------------------------------------------------+
// Endpoint
//--------------------------------------------------------------------+

// Check if endpoint descriptor is valid per USB specs
bool tu_edpt_validate(tusb_desc_endpoint_t const * desc_ep, tusb_speed_t speed);

// Bind all endpoint of a interface descriptor to class driver
void tu_edpt_bind_driver(uint8_t ep2drv[][2], tusb_desc_interface_t const* p_desc, uint16_t desc_len, uint8_t driver_id);

// Calculate total length of n interfaces (depending on IAD)
uint16_t tu_desc_get_interface_total_len(tusb_desc_interface_t const* desc_itf, uint8_t itf_count, uint16_t max_len);

// Claim an endpoint with provided mutex
bool tu_edpt_claim(tu_edpt_state_t* ep_state, osal_mutex_t mutex);

// Release an endpoint with provided mutex
bool tu_edpt_release(tu_edpt_state_t* ep_state, osal_mutex_t mutex);

//--------------------------------------------------------------------+
// Endpoint Stream
//--------------------------------------------------------------------+

// Init an stream, should only be called once
bool tu_edpt_stream_init(tu_edpt_stream_t* s, bool is_host, bool is_tx, bool overwritable,
                         void* ff_buf, uint16_t ff_bufsize, uint8_t* ep_buf, uint16_t ep_bufsize);

// Open an stream for an endpoint
// hwid is either device address (host mode) or rhport (device mode)
TU_ATTR_ALWAYS_INLINE static inline
void tu_edpt_stream_open(tu_edpt_stream_t* s, uint8_t hwid, tusb_desc_endpoint_t const *desc_ep)
{
  tu_fifo_clear(&s->ff);
  s->hwid = hwid;
  s->ep_addr = desc_ep->bEndpointAddress;
  s->ep_packetsize = tu_edpt_packet_size(desc_ep);
}

TU_ATTR_ALWAYS_INLINE static inline
void tu_edpt_stream_close(tu_edpt_stream_t* s)
{
  s->hwid = 0;
  s->ep_addr = 0;
}

// Clear fifo
TU_ATTR_ALWAYS_INLINE static inline
bool tu_edpt_stream_clear(tu_edpt_stream_t* s)
{
  return tu_fifo_clear(&s->ff);
}

//--------------------------------------------------------------------+
// Stream Write
//--------------------------------------------------------------------+

// Write to stream
uint32_t tu_edpt_stream_write(tu_edpt_stream_t* s, void const *buffer, uint32_t bufsize);

// Start an usb transfer if endpoint is not busy
uint32_t tu_edpt_stream_write_xfer(tu_edpt_stream_t* s);

// Start an zero-length packet if needed
bool tu_edpt_stream_write_zlp_if_needed(tu_edpt_stream_t* s, uint32_t last_xferred_bytes);

// Get the number of bytes available for writing
TU_ATTR_ALWAYS_INLINE static inline
uint32_t tu_edpt_stream_write_available(tu_edpt_stream_t* s)
{
  return (uint32_t) tu_fifo_remaining(&s->ff);
}

//--------------------------------------------------------------------+
// Stream Read
//--------------------------------------------------------------------+

// Read from stream
uint32_t tu_edpt_stream_read(tu_edpt_stream_t* s, void* buffer, uint32_t bufsize);

// Start an usb transfer if endpoint is not busy
uint32_t tu_edpt_stream_read_xfer(tu_edpt_stream_t* s);

// Must be called in the transfer complete callback
TU_ATTR_ALWAYS_INLINE static inline
void tu_edpt_stream_read_xfer_complete(tu_edpt_stream_t* s, uint32_t xferred_bytes)
{
  tu_fifo_write_n(&s->ff, s->ep_buf, (uint16_t) xferred_bytes);
}

// Get the number of bytes available for reading
TU_ATTR_ALWAYS_INLINE static inline
uint32_t tu_edpt_stream_read_available(tu_edpt_stream_t* s)
{
  return (uint32_t) tu_fifo_count(&s->ff);
}

TU_ATTR_ALWAYS_INLINE static inline
bool tu_edpt_stream_peek(tu_edpt_stream_t* s, uint8_t* ch)
{
  return tu_fifo_peek(&s->ff, ch);
}

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_PRIVATE_H_ */
