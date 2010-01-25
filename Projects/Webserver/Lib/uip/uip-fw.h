/**
 * \addtogroup uipfw
 * @{
 */

/**
 * \file
 * uIP packet forwarding header file.
 * \author Adam Dunkels <adam@sics.se>
 */

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
 * This file is part of the uIP TCP/IP stack
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: uip-fw.h,v 1.2 2006/06/12 08:00:30 adam Exp $
 */
#ifndef __UIP_FW_H__
#define __UIP_FW_H__

#include "uip.h"

/**
 * Representation of a uIP network interface.
 */
struct uip_fw_netif {
  struct uip_fw_netif *next;  /**< Pointer to the next interface when
				 linked in a list. */
  u16_t ipaddr[2];            /**< The IP address of this interface. */
  u16_t netmask[2];           /**< The netmask of the interface. */
  u8_t (* output)(void);
                              /**< A pointer to the function that
				 sends a packet. */
};

/**
 * Intantiating macro for a uIP network interface.
 *
 * Example:
 \code
 struct uip_fw_netif slipnetif =
   {UIP_FW_NETIF(192,168,76,1, 255,255,255,0, slip_output)};
 \endcode
 * \param ip1,ip2,ip3,ip4 The IP address of the network interface.
 *
 * \param nm1,nm2,nm3,nm4 The netmask of the network interface.
 *
 * \param outputfunc A pointer to the output function of the network interface.
 *
 * \hideinitializer
 */
#define UIP_FW_NETIF(ip1,ip2,ip3,ip4, nm1,nm2,nm3,nm4, outputfunc) \
        NULL, \
	{HTONS((ip1 << 8) | ip2), HTONS((ip3 << 8) | ip4)}, \
	{HTONS((nm1 << 8) | nm2), HTONS((nm3 << 8) | nm4)}, \
        outputfunc

/**
 * Set the IP address of a network interface.
 *
 * \param netif A pointer to the uip_fw_netif structure for the network interface.
 *
 * \param addr A pointer to an IP address.
 *
 * \hideinitializer
 */
#define uip_fw_setipaddr(netif, addr) \
        do { (netif)->ipaddr[0] = ((u16_t *)(addr))[0]; \
             (netif)->ipaddr[1] = ((u16_t *)(addr))[1]; } while(0)
/**
 * Set the netmask of a network interface.
 *
 * \param netif A pointer to the uip_fw_netif structure for the network interface.
 *
 * \param addr A pointer to an IP address representing the netmask.
 *
 * \hideinitializer
 */
#define uip_fw_setnetmask(netif, addr) \
        do { (netif)->netmask[0] = ((u16_t *)(addr))[0]; \
             (netif)->netmask[1] = ((u16_t *)(addr))[1]; } while(0)

void uip_fw_init(void);
u8_t uip_fw_forward(void);
u8_t uip_fw_output(void);
void uip_fw_register(struct uip_fw_netif *netif);
void uip_fw_default(struct uip_fw_netif *netif);
void uip_fw_periodic(void);


/**
 * A non-error message that indicates that a packet should be
 * processed locally.
 *
 * \hideinitializer
 */
#define UIP_FW_LOCAL     0

/**
 * A non-error message that indicates that something went OK.
 *
 * \hideinitializer
 */
#define UIP_FW_OK        0

/**
 * A non-error message that indicates that a packet was forwarded.
 *
 * \hideinitializer
 */
#define UIP_FW_FORWARDED 1

/**
 * A non-error message that indicates that a zero-length packet
 * transmission was attempted, and that no packet was sent.
 *
 * \hideinitializer
 */
#define UIP_FW_ZEROLEN   2

/**
 * An error message that indicates that a packet that was too large
 * for the outbound network interface was detected.
 *
 * \hideinitializer
 */
#define UIP_FW_TOOLARGE  3

/**
 * An error message that indicates that no suitable interface could be
 * found for an outbound packet.
 *
 * \hideinitializer
 */
#define UIP_FW_NOROUTE   4

/**
 * An error message that indicates that a packet that should be
 * forwarded or output was dropped.
 *
 * \hideinitializer
 */
#define UIP_FW_DROPPED   5


#endif /* __UIP_FW_H__ */

/** @} */
