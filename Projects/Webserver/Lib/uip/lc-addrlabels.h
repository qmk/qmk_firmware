/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: lc-addrlabels.h,v 1.3 2006/06/12 08:00:30 adam Exp $
 */

/**
 * \addtogroup lc
 * @{
 */

/**
 * \file
 * Implementation of local continuations based on the "Labels as
 * values" feature of gcc
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 * This implementation of local continuations is based on a special
 * feature of the GCC C compiler called "labels as values". This
 * feature allows assigning pointers with the address of the code
 * corresponding to a particular C label.
 *
 * For more information, see the GCC documentation:
 * http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
 *
 * Thanks to dividuum for finding the nice local scope label
 * implementation.
 */

#ifndef __LC_ADDRLABELS_H__
#define __LC_ADDRLABELS_H__

/** \hideinitializer */
typedef void * lc_t;

#define LC_INIT(s) s = NULL


#define LC_RESUME(s)                            \
  do {                                          \
    if(s != NULL) {                             \
      goto *s;                                  \
    }                                           \
  } while(0)

#define LC_SET(s)                               \
  do { ({ __label__ resume; resume: (s) = &&resume; }); }while(0)

#define LC_END(s)

#endif /* __LC_ADDRLABELS_H__ */

/**  @} */
