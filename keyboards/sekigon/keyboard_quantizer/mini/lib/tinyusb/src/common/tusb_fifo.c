/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 * Copyright (c) 2020 Reinhard Panhuber - rework to unmasked pointers
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

#include "osal/osal.h"
#include "tusb_fifo.h"

#define TU_FIFO_DBG   0

// Suppress IAR warning
// Warning[Pa082]: undefined behavior: the order of volatile accesses is undefined in this statement
#if defined(__ICCARM__)
#pragma diag_suppress = Pa082
#endif

#if OSAL_MUTEX_REQUIRED

TU_ATTR_ALWAYS_INLINE static inline void _ff_lock(osal_mutex_t mutex)
{
  if (mutex) osal_mutex_lock(mutex, OSAL_TIMEOUT_WAIT_FOREVER);
}

TU_ATTR_ALWAYS_INLINE static inline void _ff_unlock(osal_mutex_t mutex)
{
  if (mutex) osal_mutex_unlock(mutex);
}

#else

#define _ff_lock(_mutex)
#define _ff_unlock(_mutex)

#endif

/** \enum tu_fifo_copy_mode_t
 * \brief Write modes intended to allow special read and write functions to be able to
 *        copy data to and from USB hardware FIFOs as needed for e.g. STM32s and others
 */
typedef enum
{
  TU_FIFO_COPY_INC,            ///< Copy from/to an increasing source/destination address - default mode
  TU_FIFO_COPY_CST_FULL_WORDS, ///< Copy from/to a constant source/destination address - required for e.g. STM32 to write into USB hardware FIFO
} tu_fifo_copy_mode_t;

bool tu_fifo_config(tu_fifo_t *f, void* buffer, uint16_t depth, uint16_t item_size, bool overwritable)
{
  // Limit index space to 2*depth - this allows for a fast "modulo" calculation
  // but limits the maximum depth to 2^16/2 = 2^15 and buffer overflows are detectable
  // only if overflow happens once (important for unsupervised DMA applications)
  if (depth > 0x8000) return false;

  _ff_lock(f->mutex_wr);
  _ff_lock(f->mutex_rd);

  f->buffer       = (uint8_t*) buffer;
  f->depth        = depth;
  f->item_size    = (uint16_t) (item_size & 0x7FFF);
  f->overwritable = overwritable;
  f->rd_idx       = 0;
  f->wr_idx       = 0;

  _ff_unlock(f->mutex_wr);
  _ff_unlock(f->mutex_rd);

  return true;
}

//--------------------------------------------------------------------+
// Pull & Push
//--------------------------------------------------------------------+

// Intended to be used to read from hardware USB FIFO in e.g. STM32 where all data is read from a constant address
// Code adapted from dcd_synopsys.c
// TODO generalize with configurable 1 byte or 4 byte each read
static void _ff_push_const_addr(uint8_t * ff_buf, const void * app_buf, uint16_t len)
{
  volatile const uint32_t * reg_rx = (volatile const uint32_t *) app_buf;

  // Reading full available 32 bit words from const app address
  uint16_t full_words = len >> 2;
  while(full_words--)
  {
    tu_unaligned_write32(ff_buf, *reg_rx);
    ff_buf += 4;
  }

  // Read the remaining 1-3 bytes from const app address
  uint8_t const bytes_rem = len & 0x03;
  if ( bytes_rem )
  {
    uint32_t tmp32 = *reg_rx;
    memcpy(ff_buf, &tmp32, bytes_rem);
  }
}

// Intended to be used to write to hardware USB FIFO in e.g. STM32
// where all data is written to a constant address in full word copies
static void _ff_pull_const_addr(void * app_buf, const uint8_t * ff_buf, uint16_t len)
{
  volatile uint32_t * reg_tx = (volatile uint32_t *) app_buf;

  // Write full available 32 bit words to const address
  uint16_t full_words = len >> 2;
  while(full_words--)
  {
    *reg_tx = tu_unaligned_read32(ff_buf);
    ff_buf += 4;
  }

  // Write the remaining 1-3 bytes into const address
  uint8_t const bytes_rem = len & 0x03;
  if ( bytes_rem )
  {
    uint32_t tmp32 = 0;
    memcpy(&tmp32, ff_buf, bytes_rem);

    *reg_tx = tmp32;
  }
}

// send one item to fifo WITHOUT updating write pointer
static inline void _ff_push(tu_fifo_t* f, void const * app_buf, uint16_t rel)
{
  memcpy(f->buffer + (rel * f->item_size), app_buf, f->item_size);
}

// send n items to fifo WITHOUT updating write pointer
static void _ff_push_n(tu_fifo_t* f, void const * app_buf, uint16_t n, uint16_t wr_ptr, tu_fifo_copy_mode_t copy_mode)
{
  uint16_t const lin_count = f->depth - wr_ptr;
  uint16_t const wrap_count = n - lin_count;

  uint16_t lin_bytes = lin_count * f->item_size;
  uint16_t wrap_bytes = wrap_count * f->item_size;

  // current buffer of fifo
  uint8_t* ff_buf = f->buffer + (wr_ptr * f->item_size);

  switch (copy_mode)
  {
    case TU_FIFO_COPY_INC:
      if(n <= lin_count)
      {
        // Linear only
        memcpy(ff_buf, app_buf, n*f->item_size);
      }
      else
      {
        // Wrap around

        // Write data to linear part of buffer
        memcpy(ff_buf, app_buf, lin_bytes);

        // Write data wrapped around
        // TU_ASSERT(nWrap_bytes <= f->depth, );
        memcpy(f->buffer, ((uint8_t const*) app_buf) + lin_bytes, wrap_bytes);
      }
      break;

    case TU_FIFO_COPY_CST_FULL_WORDS:
      // Intended for hardware buffers from which it can be read word by word only
      if(n <= lin_count)
      {
        // Linear only
        _ff_push_const_addr(ff_buf, app_buf, n*f->item_size);
      }
      else
      {
        // Wrap around case

        // Write full words to linear part of buffer
        uint16_t nLin_4n_bytes = lin_bytes & 0xFFFC;
        _ff_push_const_addr(ff_buf, app_buf, nLin_4n_bytes);
        ff_buf += nLin_4n_bytes;

        // There could be odd 1-3 bytes before the wrap-around boundary
        uint8_t rem = lin_bytes & 0x03;
        if (rem > 0)
        {
          volatile const uint32_t * rx_fifo = (volatile const uint32_t *) app_buf;

          uint8_t remrem = (uint8_t) tu_min16(wrap_bytes, 4-rem);
          wrap_bytes -= remrem;

          uint32_t tmp32 = *rx_fifo;
          uint8_t * src_u8 = ((uint8_t *) &tmp32);

          // Write 1-3 bytes before wrapped boundary
          while(rem--) *ff_buf++ = *src_u8++;

          // Read more bytes to beginning to complete a word
          ff_buf = f->buffer;
          while(remrem--) *ff_buf++ = *src_u8++;
        }
        else
        {
          ff_buf = f->buffer; // wrap around to beginning
        }

        // Write data wrapped part
        if (wrap_bytes > 0) _ff_push_const_addr(ff_buf, app_buf, wrap_bytes);
      }
      break;
  }
}

// get one item from fifo WITHOUT updating read pointer
static inline void _ff_pull(tu_fifo_t* f, void * app_buf, uint16_t rel)
{
  memcpy(app_buf, f->buffer + (rel * f->item_size), f->item_size);
}

// get n items from fifo WITHOUT updating read pointer
static void _ff_pull_n(tu_fifo_t* f, void* app_buf, uint16_t n, uint16_t rd_ptr, tu_fifo_copy_mode_t copy_mode)
{
  uint16_t const lin_count = f->depth - rd_ptr;
  uint16_t const wrap_count = n - lin_count; // only used if wrapped

  uint16_t lin_bytes = lin_count * f->item_size;
  uint16_t wrap_bytes = wrap_count * f->item_size;

  // current buffer of fifo
  uint8_t* ff_buf = f->buffer + (rd_ptr * f->item_size);

  switch (copy_mode)
  {
    case TU_FIFO_COPY_INC:
      if ( n <= lin_count )
      {
        // Linear only
        memcpy(app_buf, ff_buf, n*f->item_size);
      }
      else
      {
        // Wrap around

        // Read data from linear part of buffer
        memcpy(app_buf, ff_buf, lin_bytes);

        // Read data wrapped part
        memcpy((uint8_t*) app_buf + lin_bytes, f->buffer, wrap_bytes);
      }
    break;

    case TU_FIFO_COPY_CST_FULL_WORDS:
      if ( n <= lin_count )
      {
        // Linear only
        _ff_pull_const_addr(app_buf, ff_buf, n*f->item_size);
      }
      else
      {
        // Wrap around case

        // Read full words from linear part of buffer
        uint16_t lin_4n_bytes = lin_bytes & 0xFFFC;
        _ff_pull_const_addr(app_buf, ff_buf, lin_4n_bytes);
        ff_buf += lin_4n_bytes;

        // There could be odd 1-3 bytes before the wrap-around boundary
        uint8_t rem = lin_bytes & 0x03;
        if (rem > 0)
        {
          volatile uint32_t * reg_tx = (volatile uint32_t *) app_buf;

          uint8_t remrem = (uint8_t) tu_min16(wrap_bytes, 4-rem);
          wrap_bytes -= remrem;

          uint32_t tmp32=0;
          uint8_t * dst_u8 = (uint8_t *)&tmp32;

          // Read 1-3 bytes before wrapped boundary
          while(rem--) *dst_u8++ = *ff_buf++;

          // Read more bytes from beginning to complete a word
          ff_buf = f->buffer;
          while(remrem--) *dst_u8++ = *ff_buf++;

          *reg_tx = tmp32;
        }
        else
        {
          ff_buf = f->buffer; // wrap around to beginning
        }

        // Read data wrapped part
        if (wrap_bytes > 0) _ff_pull_const_addr(app_buf, ff_buf, wrap_bytes);
      }
    break;

    default: break;
  }
}

//--------------------------------------------------------------------+
// Helper
//--------------------------------------------------------------------+

// return only the index difference and as such can be used to determine an overflow i.e overflowable count
TU_ATTR_ALWAYS_INLINE static inline
uint16_t _ff_count(uint16_t depth, uint16_t wr_idx, uint16_t rd_idx)
{
  // In case we have non-power of two depth we need a further modification
  if (wr_idx >= rd_idx)
  {
    return (uint16_t) (wr_idx - rd_idx);
  } else
  {
    return (uint16_t) (2*depth - (rd_idx - wr_idx));
  }
}

// return remaining slot in fifo
TU_ATTR_ALWAYS_INLINE static inline
uint16_t _ff_remaining(uint16_t depth, uint16_t wr_idx, uint16_t rd_idx)
{
  uint16_t const count = _ff_count(depth, wr_idx, rd_idx);
  return (depth > count) ? (depth - count) : 0;
}

//--------------------------------------------------------------------+
// Index Helper
//--------------------------------------------------------------------+

// Advance an absolute index
// "absolute" index is only in the range of [0..2*depth)
static uint16_t advance_index(uint16_t depth, uint16_t idx, uint16_t offset)
{
  // We limit the index space of p such that a correct wrap around happens
  // Check for a wrap around or if we are in unused index space - This has to be checked first!!
  // We are exploiting the wrap around to the correct index
  uint16_t new_idx = (uint16_t) (idx + offset);
  if ( (idx > new_idx) || (new_idx >= 2*depth) )
  {
    uint16_t const non_used_index_space = (uint16_t) (UINT16_MAX - (2*depth-1));
    new_idx = (uint16_t) (new_idx + non_used_index_space);
  }

  return new_idx;
}

#if 0 // not used but
// Backward an absolute index
static uint16_t backward_index(uint16_t depth, uint16_t idx, uint16_t offset)
{
  // We limit the index space of p such that a correct wrap around happens
  // Check for a wrap around or if we are in unused index space - This has to be checked first!!
  // We are exploiting the wrap around to the correct index
  uint16_t new_idx = (uint16_t) (idx - offset);
  if ( (idx < new_idx) || (new_idx >= 2*depth) )
  {
    uint16_t const non_used_index_space = (uint16_t) (UINT16_MAX - (2*depth-1));
    new_idx = (uint16_t) (new_idx - non_used_index_space);
  }

  return new_idx;
}
#endif

// index to pointer, simply an modulo with minus.
TU_ATTR_ALWAYS_INLINE static inline
uint16_t idx2ptr(uint16_t depth, uint16_t idx)
{
  // Only run at most 3 times since index is limit in the range of [0..2*depth)
  while ( idx >= depth ) idx -= depth;
  return idx;
}

// Works on local copies of w
// When an overwritable fifo is overflowed, rd_idx will be re-index so that it forms
// an full fifo i.e _ff_count() = depth
TU_ATTR_ALWAYS_INLINE static inline
uint16_t _ff_correct_read_index(tu_fifo_t* f, uint16_t wr_idx)
{
  uint16_t rd_idx;
  if ( wr_idx >= f->depth )
  {
    rd_idx = wr_idx - f->depth;
  }else
  {
    rd_idx = wr_idx + f->depth;
  }

  f->rd_idx = rd_idx;

  return rd_idx;
}

// Works on local copies of w and r
// Must be protected by mutexes since in case of an overflow read pointer gets modified
static bool _tu_fifo_peek(tu_fifo_t* f, void * p_buffer, uint16_t wr_idx, uint16_t rd_idx)
{
  uint16_t cnt = _ff_count(f->depth, wr_idx, rd_idx);

  // nothing to peek
  if ( cnt == 0 ) return false;

  // Check overflow and correct if required
  if ( cnt > f->depth )
  {
    rd_idx = _ff_correct_read_index(f, wr_idx);
    cnt = f->depth;
  }

  uint16_t rd_ptr = idx2ptr(f->depth, rd_idx);

  // Peek data
  _ff_pull(f, p_buffer, rd_ptr);

  return true;
}

// Works on local copies of w and r
// Must be protected by mutexes since in case of an overflow read pointer gets modified
static uint16_t _tu_fifo_peek_n(tu_fifo_t* f, void * p_buffer, uint16_t n, uint16_t wr_idx, uint16_t rd_idx, tu_fifo_copy_mode_t copy_mode)
{
  uint16_t cnt = _ff_count(f->depth, wr_idx, rd_idx);

  // nothing to peek
  if ( cnt == 0 ) return 0;

  // Check overflow and correct if required
  if ( cnt > f->depth )
  {
    rd_idx = _ff_correct_read_index(f, wr_idx);
    cnt = f->depth;
  }

  // Check if we can read something at and after offset - if too less is available we read what remains
  if ( cnt < n ) n = cnt;

  uint16_t rd_ptr = idx2ptr(f->depth, rd_idx);

  // Peek data
  _ff_pull_n(f, p_buffer, n, rd_ptr, copy_mode);

  return n;
}

static uint16_t _tu_fifo_write_n(tu_fifo_t* f, const void * data, uint16_t n, tu_fifo_copy_mode_t copy_mode)
{
  if ( n == 0 ) return 0;

  _ff_lock(f->mutex_wr);

  uint16_t wr_idx = f->wr_idx;
  uint16_t rd_idx = f->rd_idx;

  uint8_t const* buf8 = (uint8_t const*) data;

  TU_LOG(TU_FIFO_DBG, "rd = %3u, wr = %3u, count = %3u, remain = %3u, n = %3u:  ",
                       rd_idx, wr_idx, _ff_count(f->depth, wr_idx, rd_idx), _ff_remaining(f->depth, wr_idx, rd_idx), n);

  if ( !f->overwritable )
  {
    // limit up to full
    uint16_t const remain = _ff_remaining(f->depth, wr_idx, rd_idx);
    n = tu_min16(n, remain);
  }
  else
  {
    // In over-writable mode, fifo_write() is allowed even when fifo is full. In such case,
    // oldest data in fifo i.e at read pointer data will be overwritten
    // Note: we can modify read buffer contents but we must not modify the read index itself within a write function!
    // Since it would end up in a race condition with read functions!
    if ( n >= f->depth )
    {
      // Only copy last part
      if ( copy_mode == TU_FIFO_COPY_INC )
      {
        buf8 += (n - f->depth) * f->item_size;
      }else
      {
        // TODO should read from hw fifo to discard data, however reading an odd number could
        // accidentally discard data.
      }

      n = f->depth;

      // We start writing at the read pointer's position since we fill the whole buffer
      wr_idx = rd_idx;
    }
    else
    {
      uint16_t const overflowable_count = _ff_count(f->depth, wr_idx, rd_idx);
      if (overflowable_count + n >= 2*f->depth)
      {
        // Double overflowed
        // Index is bigger than the allowed range [0,2*depth)
        // re-position write index to have a full fifo after pushed
        wr_idx = advance_index(f->depth, rd_idx, f->depth - n);

        // TODO we should also shift out n bytes from read index since we avoid changing rd index !!
        // However memmove() is expensive due to actual copying + wrapping consideration.
        // Also race condition could happen anyway if read() is invoke while moving result in corrupted memory
        // currently deliberately not implemented --> result in incorrect data read back
      }else
      {
        // normal + single overflowed:
        // Index is in the range of [0,2*depth) and thus detect and recoverable. Recovering is handled in read()
        // Therefore we just increase write index
        // we will correct (re-position) read index later on in fifo_read() function
      }
    }
  }

  if (n)
  {
    uint16_t wr_ptr = idx2ptr(f->depth, wr_idx);

    TU_LOG(TU_FIFO_DBG, "actual_n = %u, wr_ptr = %u", n, wr_ptr);

    // Write data
    _ff_push_n(f, buf8, n, wr_ptr, copy_mode);

    // Advance index
    f->wr_idx = advance_index(f->depth, wr_idx, n);

    TU_LOG(TU_FIFO_DBG, "\tnew_wr = %u\n", f->wr_idx);
  }

  _ff_unlock(f->mutex_wr);

  return n;
}

static uint16_t _tu_fifo_read_n(tu_fifo_t* f, void * buffer, uint16_t n, tu_fifo_copy_mode_t copy_mode)
{
  _ff_lock(f->mutex_rd);

  // Peek the data
  // f->rd_idx might get modified in case of an overflow so we can not use a local variable
  n = _tu_fifo_peek_n(f, buffer, n, f->wr_idx, f->rd_idx, copy_mode);

  // Advance read pointer
  f->rd_idx = advance_index(f->depth, f->rd_idx, n);

  _ff_unlock(f->mutex_rd);
  return n;
}

//--------------------------------------------------------------------+
// Application API
//--------------------------------------------------------------------+

/******************************************************************************/
/*!
    @brief Get number of items in FIFO.

    As this function only reads the read and write pointers once, this function is
    reentrant and thus thread and ISR save without any mutexes. In case an
    overflow occurred, this function return f.depth at maximum. Overflows are
    checked and corrected for in the read functions!

    @param[in]  f
                Pointer to the FIFO buffer to manipulate

    @returns Number of items in FIFO
 */
/******************************************************************************/
uint16_t tu_fifo_count(tu_fifo_t* f)
{
  return tu_min16(_ff_count(f->depth, f->wr_idx, f->rd_idx), f->depth);
}

/******************************************************************************/
/*!
    @brief Check if FIFO is empty.

    As this function only reads the read and write pointers once, this function is
    reentrant and thus thread and ISR save without any mutexes.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate

    @returns Number of items in FIFO
 */
/******************************************************************************/
bool tu_fifo_empty(tu_fifo_t* f)
{
  return f->wr_idx == f->rd_idx;
}

/******************************************************************************/
/*!
    @brief Check if FIFO is full.

    As this function only reads the read and write pointers once, this function is
    reentrant and thus thread and ISR save without any mutexes.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate

    @returns Number of items in FIFO
 */
/******************************************************************************/
bool tu_fifo_full(tu_fifo_t* f)
{
  return _ff_count(f->depth, f->wr_idx, f->rd_idx) >= f->depth;
}

/******************************************************************************/
/*!
    @brief Get remaining space in FIFO.

    As this function only reads the read and write pointers once, this function is
    reentrant and thus thread and ISR save without any mutexes.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate

    @returns Number of items in FIFO
 */
/******************************************************************************/
uint16_t tu_fifo_remaining(tu_fifo_t* f)
{
  return _ff_remaining(f->depth, f->wr_idx, f->rd_idx);
}

/******************************************************************************/
/*!
    @brief Check if overflow happened.

     BE AWARE - THIS FUNCTION MIGHT NOT GIVE A CORRECT ANSWERE IN CASE WRITE POINTER "OVERFLOWS"
     Only one overflow is allowed for this function to work e.g. if depth = 100, you must not
     write more than 2*depth-1 items in one rush without updating write pointer. Otherwise
     write pointer wraps and your pointer states are messed up. This can only happen if you
     use DMAs, write functions do not allow such an error. Avoid such nasty things!

     All reading functions (read, peek) check for overflows and correct read pointer on their own such
     that latest items are read.
     If required (e.g. for DMA use) you can also correct the read pointer by
     tu_fifo_correct_read_pointer().

    @param[in]  f
                Pointer to the FIFO buffer to manipulate

    @returns True if overflow happened
 */
/******************************************************************************/
bool tu_fifo_overflowed(tu_fifo_t* f)
{
  return _ff_count(f->depth, f->wr_idx, f->rd_idx) > f->depth;
}

// Only use in case tu_fifo_overflow() returned true!
void tu_fifo_correct_read_pointer(tu_fifo_t* f)
{
  _ff_lock(f->mutex_rd);
  _ff_correct_read_index(f, f->wr_idx);
  _ff_unlock(f->mutex_rd);
}

/******************************************************************************/
/*!
    @brief Read one element out of the buffer.

    This function will return the element located at the array index of the
    read pointer, and then increment the read pointer index.
    This function checks for an overflow and corrects read pointer if required.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  buffer
                Pointer to the place holder for data read from the buffer

    @returns TRUE if the queue is not empty
 */
/******************************************************************************/
bool tu_fifo_read(tu_fifo_t* f, void * buffer)
{
  _ff_lock(f->mutex_rd);

  // Peek the data
  // f->rd_idx might get modified in case of an overflow so we can not use a local variable
  bool ret = _tu_fifo_peek(f, buffer, f->wr_idx, f->rd_idx);

  // Advance pointer
  f->rd_idx = advance_index(f->depth, f->rd_idx, ret);

  _ff_unlock(f->mutex_rd);
  return ret;
}

/******************************************************************************/
/*!
    @brief This function will read n elements from the array index specified by
    the read pointer and increment the read index.
    This function checks for an overflow and corrects read pointer if required.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  buffer
                The pointer to data location
    @param[in]  n
                Number of element that buffer can afford

    @returns number of items read from the FIFO
 */
/******************************************************************************/
uint16_t tu_fifo_read_n(tu_fifo_t* f, void * buffer, uint16_t n)
{
  return _tu_fifo_read_n(f, buffer, n, TU_FIFO_COPY_INC);
}

uint16_t tu_fifo_read_n_const_addr_full_words(tu_fifo_t* f, void * buffer, uint16_t n)
{
  return _tu_fifo_read_n(f, buffer, n, TU_FIFO_COPY_CST_FULL_WORDS);
}

/******************************************************************************/
/*!
    @brief Read one item without removing it from the FIFO.
    This function checks for an overflow and corrects read pointer if required.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  p_buffer
                Pointer to the place holder for data read from the buffer

    @returns TRUE if the queue is not empty
 */
/******************************************************************************/
bool tu_fifo_peek(tu_fifo_t* f, void * p_buffer)
{
  _ff_lock(f->mutex_rd);
  bool ret = _tu_fifo_peek(f, p_buffer, f->wr_idx, f->rd_idx);
  _ff_unlock(f->mutex_rd);
  return ret;
}

/******************************************************************************/
/*!
    @brief Read n items without removing it from the FIFO
    This function checks for an overflow and corrects read pointer if required.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  p_buffer
                Pointer to the place holder for data read from the buffer
    @param[in]  n
                Number of items to peek

    @returns Number of bytes written to p_buffer
 */
/******************************************************************************/
uint16_t tu_fifo_peek_n(tu_fifo_t* f, void * p_buffer, uint16_t n)
{
  _ff_lock(f->mutex_rd);
  uint16_t ret = _tu_fifo_peek_n(f, p_buffer, n, f->wr_idx, f->rd_idx, TU_FIFO_COPY_INC);
  _ff_unlock(f->mutex_rd);
  return ret;
}

/******************************************************************************/
/*!
    @brief Write one element into the buffer.

    This function will write one element into the array index specified by
    the write pointer and increment the write index.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  data
                The byte to add to the FIFO

    @returns TRUE if the data was written to the FIFO (overwrittable
             FIFO will always return TRUE)
 */
/******************************************************************************/
bool tu_fifo_write(tu_fifo_t* f, const void * data)
{
  _ff_lock(f->mutex_wr);

  bool ret;
  uint16_t const wr_idx = f->wr_idx;

  if ( tu_fifo_full(f) && !f->overwritable )
  {
    ret = false;
  }else
  {
    uint16_t wr_ptr = idx2ptr(f->depth, wr_idx);

    // Write data
    _ff_push(f, data, wr_ptr);

    // Advance pointer
    f->wr_idx = advance_index(f->depth, wr_idx, 1);

    ret = true;
  }

  _ff_unlock(f->mutex_wr);

  return ret;
}

/******************************************************************************/
/*!
    @brief This function will write n elements into the array index specified by
    the write pointer and increment the write index.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  data
                The pointer to data to add to the FIFO
    @param[in]  count
                Number of element
    @return Number of written elements
 */
/******************************************************************************/
uint16_t tu_fifo_write_n(tu_fifo_t* f, const void * data, uint16_t n)
{
  return _tu_fifo_write_n(f, data, n, TU_FIFO_COPY_INC);
}

/******************************************************************************/
/*!
    @brief This function will write n elements into the array index specified by
    the write pointer and increment the write index. The source address will
    not be incremented which is useful for reading from registers.

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  data
                The pointer to data to add to the FIFO
    @param[in]  count
                Number of element
    @return Number of written elements
 */
/******************************************************************************/
uint16_t tu_fifo_write_n_const_addr_full_words(tu_fifo_t* f, const void * data, uint16_t n)
{
  return _tu_fifo_write_n(f, data, n, TU_FIFO_COPY_CST_FULL_WORDS);
}

/******************************************************************************/
/*!
    @brief Clear the fifo read and write pointers

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
 */
/******************************************************************************/
bool tu_fifo_clear(tu_fifo_t *f)
{
  _ff_lock(f->mutex_wr);
  _ff_lock(f->mutex_rd);

  f->rd_idx = 0;
  f->wr_idx = 0;

  _ff_unlock(f->mutex_wr);
  _ff_unlock(f->mutex_rd);
  return true;
}

/******************************************************************************/
/*!
    @brief Change the fifo mode to overwritable or not overwritable

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  overwritable
                Overwritable mode the fifo is set to
 */
/******************************************************************************/
bool tu_fifo_set_overwritable(tu_fifo_t *f, bool overwritable)
{
  _ff_lock(f->mutex_wr);
  _ff_lock(f->mutex_rd);

  f->overwritable = overwritable;

  _ff_unlock(f->mutex_wr);
  _ff_unlock(f->mutex_rd);

  return true;
}

/******************************************************************************/
/*!
    @brief Advance write pointer - intended to be used in combination with DMA.
    It is possible to fill the FIFO by use of a DMA in circular mode. Within
    DMA ISRs you may update the write pointer to be able to read from the FIFO.
    As long as the DMA is the only process writing into the FIFO this is safe
    to use.

    USE WITH CARE - WE DO NOT CONDUCT SAFETY CHECKS HERE!

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  n
                Number of items the write pointer moves forward
 */
/******************************************************************************/
void tu_fifo_advance_write_pointer(tu_fifo_t *f, uint16_t n)
{
  f->wr_idx = advance_index(f->depth, f->wr_idx, n);
}

/******************************************************************************/
/*!
    @brief Advance read pointer - intended to be used in combination with DMA.
    It is possible to read from the FIFO by use of a DMA in linear mode. Within
    DMA ISRs you may update the read pointer to be able to again write into the
    FIFO. As long as the DMA is the only process reading from the FIFO this is
    safe to use.

    USE WITH CARE - WE DO NOT CONDUCT SAFETY CHECKS HERE!

    @param[in]  f
                Pointer to the FIFO buffer to manipulate
    @param[in]  n
                Number of items the read pointer moves forward
 */
/******************************************************************************/
void tu_fifo_advance_read_pointer(tu_fifo_t *f, uint16_t n)
{
  f->rd_idx = advance_index(f->depth, f->rd_idx, n);
}

/******************************************************************************/
/*!
   @brief Get read info

   Returns the length and pointer from which bytes can be read in a linear manner.
   This is of major interest for DMA transmissions. If returned length is zero the
   corresponding pointer is invalid.
   The read pointer does NOT get advanced, use tu_fifo_advance_read_pointer() to
   do so!
   @param[in]       f
                    Pointer to FIFO
   @param[out]      *info
                    Pointer to struct which holds the desired infos
 */
/******************************************************************************/
void tu_fifo_get_read_info(tu_fifo_t *f, tu_fifo_buffer_info_t *info)
{
  // Operate on temporary values in case they change in between
  uint16_t wr_idx = f->wr_idx;
  uint16_t rd_idx = f->rd_idx;

  uint16_t cnt = _ff_count(f->depth, wr_idx, rd_idx);

  // Check overflow and correct if required - may happen in case a DMA wrote too fast
  if (cnt > f->depth)
  {
    _ff_lock(f->mutex_rd);
    rd_idx = _ff_correct_read_index(f, wr_idx);
    _ff_unlock(f->mutex_rd);

    cnt = f->depth;
  }

  // Check if fifo is empty
  if (cnt == 0)
  {
    info->len_lin  = 0;
    info->len_wrap = 0;
    info->ptr_lin  = NULL;
    info->ptr_wrap = NULL;
    return;
  }

  // Get relative pointers
  uint16_t wr_ptr = idx2ptr(f->depth, wr_idx);
  uint16_t rd_ptr = idx2ptr(f->depth, rd_idx);

  // Copy pointer to buffer to start reading from
  info->ptr_lin = &f->buffer[rd_ptr];

  // Check if there is a wrap around necessary
  if (wr_ptr > rd_ptr)
  {
    // Non wrapping case
    info->len_lin  = cnt;

    info->len_wrap = 0;
    info->ptr_wrap = NULL;
  }
  else
  {
    info->len_lin  = f->depth - rd_ptr;   // Also the case if FIFO was full

    info->len_wrap = cnt - info->len_lin;
    info->ptr_wrap = f->buffer;
  }
}

/******************************************************************************/
/*!
   @brief Get linear write info

   Returns the length and pointer to which bytes can be written into FIFO in a linear manner.
   This is of major interest for DMA transmissions not using circular mode. If a returned length is zero the
   corresponding pointer is invalid. The returned lengths summed up are the currently free space in the FIFO.
   The write pointer does NOT get advanced, use tu_fifo_advance_write_pointer() to do so!
   TAKE CARE TO NOT OVERFLOW THE BUFFER MORE THAN TWO TIMES THE FIFO DEPTH - IT CAN NOT RECOVERE OTHERWISE!
   @param[in]       f
                    Pointer to FIFO
   @param[out]      *info
                    Pointer to struct which holds the desired infos
 */
/******************************************************************************/
void tu_fifo_get_write_info(tu_fifo_t *f, tu_fifo_buffer_info_t *info)
{
  uint16_t wr_idx = f->wr_idx;
  uint16_t rd_idx = f->rd_idx;
  uint16_t remain = _ff_remaining(f->depth, wr_idx, rd_idx);

  if (remain == 0)
  {
    info->len_lin  = 0;
    info->len_wrap = 0;
    info->ptr_lin  = NULL;
    info->ptr_wrap = NULL;
    return;
  }

  // Get relative pointers
  uint16_t wr_ptr = idx2ptr(f->depth, wr_idx);
  uint16_t rd_ptr = idx2ptr(f->depth, rd_idx);

  // Copy pointer to buffer to start writing to
  info->ptr_lin = &f->buffer[wr_ptr];

  if (wr_ptr < rd_ptr)
  {
    // Non wrapping case
    info->len_lin  = rd_ptr-wr_ptr;
    info->len_wrap = 0;
    info->ptr_wrap = NULL;
  }
  else
  {
    info->len_lin  = f->depth - wr_ptr;
    info->len_wrap = remain - info->len_lin; // Remaining length - n already was limited to remain or FIFO depth
    info->ptr_wrap = f->buffer;              // Always start of buffer
  }
}
