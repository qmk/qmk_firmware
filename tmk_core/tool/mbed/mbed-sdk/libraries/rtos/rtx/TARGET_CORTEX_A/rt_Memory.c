/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    RT_MEMORY.C
 *      Purpose: Interface functions for Dynamic Memory Management System
 *      Rev.:    V4.60
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 1999-2009 KEIL, 2009-2012 ARM Germany GmbH
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of ARM  nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/

#include "rt_TypeDef.h"
#include "rt_Memory.h"


/* Functions */

// Initialize Dynamic Memory pool
//   Parameters:
//     pool:    Pointer to memory pool
//     size:    Size of memory pool in bytes
//   Return:    0 - OK, 1 - Error

int rt_init_mem (void *pool, U32 size) {
  MEMP *ptr;

  if ((pool == NULL) || (size < sizeof(MEMP))) return (1);

  ptr = (MEMP *)pool;
  ptr->next = (MEMP *)((U32)pool + size - sizeof(MEMP *));
  ptr->next->next = NULL;
  ptr->len = 0;

  return (0);
}

// Allocate Memory from Memory pool
//   Parameters:
//     pool:    Pointer to memory pool
//     size:    Size of memory in bytes to allocate
//   Return:    Pointer to allocated memory

void *rt_alloc_mem (void *pool, U32 size) {
  MEMP *p, *p_search, *p_new;
  U32   hole_size;

  if ((pool == NULL) || (size == 0)) return NULL;

  /* Add header offset to 'size' */
  size += sizeof(MEMP);
  /* Make sure that block is 4-byte aligned  */
  size = (size + 3) & ~3;

  p_search = (MEMP *)pool;
  while (1) {
    hole_size  = (U32)p_search->next - (U32)p_search;
    hole_size -= p_search->len;
    /* Check if hole size is big enough */
    if (hole_size >= size) break;
    p_search = p_search->next;
    if (p_search->next == NULL) {
      /* Failed, we are at the end of the list */
      return NULL;
    }
  }

  if (p_search->len == 0) {
    /* No block is allocated, set the Length of the first element */
    p_search->len = size;
    p = (MEMP *)(((U32)p_search) + sizeof(MEMP));
  } else {
    /* Insert new list element into the memory list */
    p_new       = (MEMP *)((U32)p_search + p_search->len);
    p_new->next = p_search->next;
    p_new->len  = size;
    p_search->next = p_new;
    p = (MEMP *)(((U32)p_new) + sizeof(MEMP));
  }

  return (p);
}

// Free Memory and return it to Memory pool
//   Parameters:
//     pool:    Pointer to memory pool
//     mem:     Pointer to memory to free
//   Return:    0 - OK, 1 - Error

int rt_free_mem (void *pool, void *mem) {
  MEMP *p_search, *p_prev, *p_return;

  if ((pool == NULL) || (mem == NULL)) return (1);

  p_return = (MEMP *)((U32)mem - sizeof(MEMP));

  /* Set list header */
  p_prev = NULL;
  p_search = (MEMP *)pool;
  while (p_search != p_return) {
    p_prev   = p_search;
    p_search = p_search->next;
    if (p_search == NULL) {
      /* Valid Memory block not found */
      return (1);
    }
  }

  if (p_prev == NULL) {
    /* First block to be released, only set length to 0 */
    p_search->len = 0;
  } else {
    /* Discard block from chain list */
    p_prev->next = p_search->next;
  }

  return (0);
}
