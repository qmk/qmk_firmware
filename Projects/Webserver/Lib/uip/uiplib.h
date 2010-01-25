/**
 * \file
 * Various uIP library functions.
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

/*
 * Copyright (c) 2002, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack
 *
 * $Id: uiplib.h,v 1.1 2006/06/07 09:15:19 adam Exp $
 *
 */
#ifndef __UIPLIB_H__
#define __UIPLIB_H__

/**
 * \addtogroup uipconvfunc
 * @{
 */

/**
 * Convert a textual representation of an IP address to a numerical representation.
 *
 * This function takes a textual representation of an IP address in
 * the form a.b.c.d and converts it into a 4-byte array that can be
 * used by other uIP functions.
 *
 * \param addrstr A pointer to a string containing the IP address in
 * textual form.
 *
 * \param addr A pointer to a 4-byte array that will be filled in with
 * the numerical representation of the address.
 *
 * \retval 0 If the IP address could not be parsed.
 * \retval Non-zero If the IP address was parsed.
 */
unsigned char uiplib_ipaddrconv(char *addrstr, unsigned char *addr);

/** @} */

#endif /* __UIPLIB_H__ */
