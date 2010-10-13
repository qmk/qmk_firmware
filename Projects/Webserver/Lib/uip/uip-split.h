/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
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
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: uip-split.h,v 1.1 2006/06/17 22:41:19 adamdunkels Exp $
 */
/**
 * \addtogroup uip
 * @{
 */

/**
 * \defgroup uipsplit uIP TCP throughput booster hack
 * @{
 *
 * The basic uIP TCP implementation only allows each TCP connection to
 * have a single TCP segment in flight at any given time. Because of
 * the delayed ACK algorithm employed by most TCP receivers, uIP's
 * limit on the amount of in-flight TCP segments seriously reduces the
 * maximum achievable throughput for sending data from uIP.
 *
 * The uip-split module is a hack which tries to remedy this
 * situation. By splitting maximum sized outgoing TCP segments into
 * two, the delayed ACK algorithm is not invoked at TCP
 * receivers. This improves the throughput when sending data from uIP
 * by orders of magnitude.
 *
 * The uip-split module uses the uip-fw module (uIP IP packet
 * forwarding) for sending packets. Therefore, the uip-fw module must
 * be set up with the appropriate network interfaces for this module
 * to work.
 */


/**
 * \file
 * Module for splitting outbound TCP segments in two to avoid the
 * delayed ACK throughput degradation.
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __UIP_SPLIT_H__
#define __UIP_SPLIT_H__

#include <string.h>
#include <uip.h>

#include "../../USBHostMode.h"

#include <LUFA/Drivers/USB/Class/RNDIS.h>

/**
 * Handle outgoing packets.
 *
 * This function inspects an outgoing packet in the uip_buf buffer and
 * sends it out using the uip_fw_output() function. If the packet is a
 * full-sized TCP segment it will be split into two segments and
 * transmitted separately. This function should be called instead of
 * the actual device driver output function, or the uip_fw_output()
 * function.
 *
 * The headers of the outgoing packet is assumed to be in the uip_buf
 * buffer and the payload is assumed to be wherever uip_appdata
 * points. The length of the outgoing packet is assumed to be in the
 * uip_len variable.
 *
 */
void uip_split_output(void);
void uip_add32(u8_t *op32, u16_t op16);
#endif /* __UIP_SPLIT_H__ */

/** @} */
/** @} */

