/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
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
 * $Id: uip-neighbor.h,v 1.2 2006/06/12 08:00:30 adam Exp $
 */

/**
 * \file
 *         Header file for database of link-local neighbors, used by
 *         IPv6 code and to be used by future ARP code.
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#ifndef __UIP_NEIGHBOR_H__
#define __UIP_NEIGHBOR_H__

#include "uip.h"

struct uip_neighbor_addr {
#if UIP_NEIGHBOR_CONF_ADDRTYPE
  UIP_NEIGHBOR_CONF_ADDRTYPE addr;
#else
  struct uip_eth_addr addr;
#endif
};

void uip_neighbor_init(void);
void uip_neighbor_add(uip_ipaddr_t ipaddr, struct uip_neighbor_addr *addr);
void uip_neighbor_update(uip_ipaddr_t ipaddr);
struct uip_neighbor_addr *uip_neighbor_lookup(uip_ipaddr_t ipaddr);
void uip_neighbor_periodic(void);

#endif /* __UIP-NEIGHBOR_H__ */
