/**
 * @file
 * User Datagram Protocol module
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */


/* udp.c
 *
 * The code for the User Datagram Protocol UDP & UDPLite (RFC 3828).
 *
 */

/* @todo Check the use of '(struct udp_pcb).chksum_len_rx'!
 */

#include "lwip/opt.h"

#if LWIP_UDP /* don't build if not configured for use in lwipopts.h */

#include "lwip/udp.h"
#include "lwip/def.h"
#include "lwip/memp.h"
#include "lwip/inet_chksum.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/icmp.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "arch/perf.h"
#include "lwip/dhcp.h"

#include <string.h>

/* The list of UDP PCBs */
/* exported in udp.h (was static) */
struct udp_pcb *udp_pcbs;

/**
 * Process an incoming UDP datagram.
 *
 * Given an incoming UDP datagram (as a chain of pbufs) this function
 * finds a corresponding UDP PCB and hands over the pbuf to the pcbs
 * recv function. If no pcb is found or the datagram is incorrect, the
 * pbuf is freed.
 *
 * @param p pbuf to be demultiplexed to a UDP PCB.
 * @param inp network interface on which the datagram was received.
 *
 */
void
udp_input(struct pbuf *p, struct netif *inp)
{
  struct udp_hdr *udphdr;
  struct udp_pcb *pcb, *prev;
  struct udp_pcb *uncon_pcb;
  struct ip_hdr *iphdr;
  u16_t src, dest;
  u8_t local_match;
  u8_t broadcast;

  PERF_START;

  UDP_STATS_INC(udp.recv);

  iphdr = (struct ip_hdr *)p->payload;

  /* Check minimum length (IP header + UDP header)
   * and move payload pointer to UDP header */
  if (p->tot_len < (IPH_HL(iphdr) * 4 + UDP_HLEN) || pbuf_header(p, -(s16_t)(IPH_HL(iphdr) * 4))) {
    /* drop short packets */
    LWIP_DEBUGF(UDP_DEBUG,
                ("udp_input: short UDP datagram (%"U16_F" bytes) discarded\n", p->tot_len));
    UDP_STATS_INC(udp.lenerr);
    UDP_STATS_INC(udp.drop);
    snmp_inc_udpinerrors();
    pbuf_free(p);
    goto end;
  }

  udphdr = (struct udp_hdr *)p->payload;

  /* is broadcast packet ? */
  broadcast = ip_addr_isbroadcast(&current_iphdr_dest, inp);

  LWIP_DEBUGF(UDP_DEBUG, ("udp_input: received datagram of length %"U16_F"\n", p->tot_len));

  /* convert src and dest ports to host byte order */
  src = ntohs(udphdr->src);
  dest = ntohs(udphdr->dest);

  udp_debug_print(udphdr);

  /* print the UDP source and destination */
  LWIP_DEBUGF(UDP_DEBUG,
              ("udp (%"U16_F".%"U16_F".%"U16_F".%"U16_F", %"U16_F") <-- "
               "(%"U16_F".%"U16_F".%"U16_F".%"U16_F", %"U16_F")\n",
               ip4_addr1_16(&iphdr->dest), ip4_addr2_16(&iphdr->dest),
               ip4_addr3_16(&iphdr->dest), ip4_addr4_16(&iphdr->dest), ntohs(udphdr->dest),
               ip4_addr1_16(&iphdr->src), ip4_addr2_16(&iphdr->src),
               ip4_addr3_16(&iphdr->src), ip4_addr4_16(&iphdr->src), ntohs(udphdr->src)));

#if LWIP_DHCP
  pcb = NULL;
  /* when LWIP_DHCP is active, packets to DHCP_CLIENT_PORT may only be processed by
     the dhcp module, no other UDP pcb may use the local UDP port DHCP_CLIENT_PORT */
  if (dest == DHCP_CLIENT_PORT) {
    /* all packets for DHCP_CLIENT_PORT not coming from DHCP_SERVER_PORT are dropped! */
    if (src == DHCP_SERVER_PORT) {
      if ((inp->dhcp != NULL) && (inp->dhcp->pcb != NULL)) {
        /* accept the packe if 
           (- broadcast or directed to us) -> DHCP is link-layer-addressed, local ip is always ANY!
           - inp->dhcp->pcb->remote == ANY or iphdr->src */
        if ((ip_addr_isany(&inp->dhcp->pcb->remote_ip) ||
           ip_addr_cmp(&(inp->dhcp->pcb->remote_ip), &current_iphdr_src))) {
          pcb = inp->dhcp->pcb;
        }
      }
    }
  } else
#endif /* LWIP_DHCP */
  {
    prev = NULL;
    local_match = 0;
    uncon_pcb = NULL;
    /* Iterate through the UDP pcb list for a matching pcb.
     * 'Perfect match' pcbs (connected to the remote port & ip address) are
     * preferred. If no perfect match is found, the first unconnected pcb that
     * matches the local port and ip address gets the datagram. */
    for (pcb = udp_pcbs; pcb != NULL; pcb = pcb->next) {
      local_match = 0;
      /* print the PCB local and remote address */
      LWIP_DEBUGF(UDP_DEBUG,
                  ("pcb (%"U16_F".%"U16_F".%"U16_F".%"U16_F", %"U16_F") --- "
                   "(%"U16_F".%"U16_F".%"U16_F".%"U16_F", %"U16_F")\n",
                   ip4_addr1_16(&pcb->local_ip), ip4_addr2_16(&pcb->local_ip),
                   ip4_addr3_16(&pcb->local_ip), ip4_addr4_16(&pcb->local_ip), pcb->local_port,
                   ip4_addr1_16(&pcb->remote_ip), ip4_addr2_16(&pcb->remote_ip),
                   ip4_addr3_16(&pcb->remote_ip), ip4_addr4_16(&pcb->remote_ip), pcb->remote_port));

      /* compare PCB local addr+port to UDP destination addr+port */
      if ((pcb->local_port == dest) &&
          ((!broadcast && ip_addr_isany(&pcb->local_ip)) ||
           ip_addr_cmp(&(pcb->local_ip), &current_iphdr_dest) ||
#if LWIP_IGMP
           ip_addr_ismulticast(&current_iphdr_dest) ||
#endif /* LWIP_IGMP */
#if IP_SOF_BROADCAST_RECV
           (broadcast && (pcb->so_options & SOF_BROADCAST)))) {
#else  /* IP_SOF_BROADCAST_RECV */
           (broadcast))) {
#endif /* IP_SOF_BROADCAST_RECV */
        local_match = 1;
        if ((uncon_pcb == NULL) && 
            ((pcb->flags & UDP_FLAGS_CONNECTED) == 0)) {
          /* the first unconnected matching PCB */
          uncon_pcb = pcb;
        }
      }
      /* compare PCB remote addr+port to UDP source addr+port */
      if ((local_match != 0) &&
          (pcb->remote_port == src) &&
          (ip_addr_isany(&pcb->remote_ip) ||
           ip_addr_cmp(&(pcb->remote_ip), &current_iphdr_src))) {
        /* the first fully matching PCB */
        if (prev != NULL) {
          /* move the pcb to the front of udp_pcbs so that is
             found faster next time */
          prev->next = pcb->next;
          pcb->next = udp_pcbs;
          udp_pcbs = pcb;
        } else {
          UDP_STATS_INC(udp.cachehit);
        }
        break;
      }
      prev = pcb;
    }
    /* no fully matching pcb found? then look for an unconnected pcb */
    if (pcb == NULL) {
      pcb = uncon_pcb;
    }
  }

  /* Check checksum if this is a match or if it was directed at us. */
  if (pcb != NULL || ip_addr_cmp(&inp->ip_addr, &current_iphdr_dest)) {
    LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE, ("udp_input: calculating checksum\n"));
#if LWIP_UDPLITE
    if (IPH_PROTO(iphdr) == IP_PROTO_UDPLITE) {
      /* Do the UDP Lite checksum */
#if CHECKSUM_CHECK_UDP
      u16_t chklen = ntohs(udphdr->len);
      if (chklen < sizeof(struct udp_hdr)) {
        if (chklen == 0) {
          /* For UDP-Lite, checksum length of 0 means checksum
             over the complete packet (See RFC 3828 chap. 3.1) */
          chklen = p->tot_len;
        } else {
          /* At least the UDP-Lite header must be covered by the
             checksum! (Again, see RFC 3828 chap. 3.1) */
          UDP_STATS_INC(udp.chkerr);
          UDP_STATS_INC(udp.drop);
          snmp_inc_udpinerrors();
          pbuf_free(p);
          goto end;
        }
      }
      if (inet_chksum_pseudo_partial(p, &current_iphdr_src, &current_iphdr_dest,
                             IP_PROTO_UDPLITE, p->tot_len, chklen) != 0) {
       LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_LEVEL_SERIOUS,
                   ("udp_input: UDP Lite datagram discarded due to failing checksum\n"));
        UDP_STATS_INC(udp.chkerr);
        UDP_STATS_INC(udp.drop);
        snmp_inc_udpinerrors();
        pbuf_free(p);
        goto end;
      }
#endif /* CHECKSUM_CHECK_UDP */
    } else
#endif /* LWIP_UDPLITE */
    {
#if CHECKSUM_CHECK_UDP
      if (udphdr->chksum != 0) {
        if (inet_chksum_pseudo(p, ip_current_src_addr(), ip_current_dest_addr(),
                               IP_PROTO_UDP, p->tot_len) != 0) {
          LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_LEVEL_SERIOUS,
                      ("udp_input: UDP datagram discarded due to failing checksum\n"));
          UDP_STATS_INC(udp.chkerr);
          UDP_STATS_INC(udp.drop);
          snmp_inc_udpinerrors();
          pbuf_free(p);
          goto end;
        }
      }
#endif /* CHECKSUM_CHECK_UDP */
    }
    if(pbuf_header(p, -UDP_HLEN)) {
      /* Can we cope with this failing? Just assert for now */
      LWIP_ASSERT("pbuf_header failed\n", 0);
      UDP_STATS_INC(udp.drop);
      snmp_inc_udpinerrors();
      pbuf_free(p);
      goto end;
    }
    if (pcb != NULL) {
      snmp_inc_udpindatagrams();
#if SO_REUSE && SO_REUSE_RXTOALL
      if ((broadcast || ip_addr_ismulticast(&current_iphdr_dest)) &&
          ((pcb->so_options & SOF_REUSEADDR) != 0)) {
        /* pass broadcast- or multicast packets to all multicast pcbs
           if SOF_REUSEADDR is set on the first match */
        struct udp_pcb *mpcb;
        u8_t p_header_changed = 0;
        for (mpcb = udp_pcbs; mpcb != NULL; mpcb = mpcb->next) {
          if (mpcb != pcb) {
            /* compare PCB local addr+port to UDP destination addr+port */
            if ((mpcb->local_port == dest) &&
                ((!broadcast && ip_addr_isany(&mpcb->local_ip)) ||
                 ip_addr_cmp(&(mpcb->local_ip), &current_iphdr_dest) ||
#if LWIP_IGMP
                 ip_addr_ismulticast(&current_iphdr_dest) ||
#endif /* LWIP_IGMP */
#if IP_SOF_BROADCAST_RECV
                 (broadcast && (mpcb->so_options & SOF_BROADCAST)))) {
#else  /* IP_SOF_BROADCAST_RECV */
                 (broadcast))) {
#endif /* IP_SOF_BROADCAST_RECV */
              /* pass a copy of the packet to all local matches */
              if (mpcb->recv != NULL) {
                struct pbuf *q;
                /* for that, move payload to IP header again */
                if (p_header_changed == 0) {
                  pbuf_header(p, (s16_t)((IPH_HL(iphdr) * 4) + UDP_HLEN));
                  p_header_changed = 1;
                }
                q = pbuf_alloc(PBUF_RAW, p->tot_len, PBUF_RAM);
                if (q != NULL) {
                  err_t err = pbuf_copy(q, p);
                  if (err == ERR_OK) {
                    /* move payload to UDP data */
                    pbuf_header(q, -(s16_t)((IPH_HL(iphdr) * 4) + UDP_HLEN));
                    mpcb->recv(mpcb->recv_arg, mpcb, q, ip_current_src_addr(), src);
                  }
                }
              }
            }
          }
        }
        if (p_header_changed) {
          /* and move payload to UDP data again */
          pbuf_header(p, -(s16_t)((IPH_HL(iphdr) * 4) + UDP_HLEN));
        }
      }
#endif /* SO_REUSE && SO_REUSE_RXTOALL */
      /* callback */
      if (pcb->recv != NULL) {
        /* now the recv function is responsible for freeing p */
        pcb->recv(pcb->recv_arg, pcb, p, ip_current_src_addr(), src);
      } else {
        /* no recv function registered? then we have to free the pbuf! */
        pbuf_free(p);
        goto end;
      }
    } else {
      LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE, ("udp_input: not for us.\n"));

#if LWIP_ICMP
      /* No match was found, send ICMP destination port unreachable unless
         destination address was broadcast/multicast. */
      if (!broadcast &&
          !ip_addr_ismulticast(&current_iphdr_dest)) {
        /* move payload pointer back to ip header */
        pbuf_header(p, (IPH_HL(iphdr) * 4) + UDP_HLEN);
        LWIP_ASSERT("p->payload == iphdr", (p->payload == iphdr));
        icmp_dest_unreach(p, ICMP_DUR_PORT);
      }
#endif /* LWIP_ICMP */
      UDP_STATS_INC(udp.proterr);
      UDP_STATS_INC(udp.drop);
      snmp_inc_udpnoports();
      pbuf_free(p);
    }
  } else {
    pbuf_free(p);
  }
end:
  PERF_STOP("udp_input");
}

/**
 * Send data using UDP.
 *
 * @param pcb UDP PCB used to send the data.
 * @param p chain of pbuf's to be sent.
 *
 * The datagram will be sent to the current remote_ip & remote_port
 * stored in pcb. If the pcb is not bound to a port, it will
 * automatically be bound to a random port.
 *
 * @return lwIP error code.
 * - ERR_OK. Successful. No error occured.
 * - ERR_MEM. Out of memory.
 * - ERR_RTE. Could not find route to destination address.
 * - More errors could be returned by lower protocol layers.
 *
 * @see udp_disconnect() udp_sendto()
 */
err_t
udp_send(struct udp_pcb *pcb, struct pbuf *p)
{
  /* send to the packet using remote ip and port stored in the pcb */
  return udp_sendto(pcb, p, &pcb->remote_ip, pcb->remote_port);
}

#if LWIP_CHECKSUM_ON_COPY
/** Same as udp_send() but with checksum
 */
err_t
udp_send_chksum(struct udp_pcb *pcb, struct pbuf *p,
                u8_t have_chksum, u16_t chksum)
{
  /* send to the packet using remote ip and port stored in the pcb */
  return udp_sendto_chksum(pcb, p, &pcb->remote_ip, pcb->remote_port,
    have_chksum, chksum);
}
#endif /* LWIP_CHECKSUM_ON_COPY */

/**
 * Send data to a specified address using UDP.
 *
 * @param pcb UDP PCB used to send the data.
 * @param p chain of pbuf's to be sent.
 * @param dst_ip Destination IP address.
 * @param dst_port Destination UDP port.
 *
 * dst_ip & dst_port are expected to be in the same byte order as in the pcb.
 *
 * If the PCB already has a remote address association, it will
 * be restored after the data is sent.
 * 
 * @return lwIP error code (@see udp_send for possible error codes)
 *
 * @see udp_disconnect() udp_send()
 */
err_t
udp_sendto(struct udp_pcb *pcb, struct pbuf *p,
  ip_addr_t *dst_ip, u16_t dst_port)
{
#if LWIP_CHECKSUM_ON_COPY
  return udp_sendto_chksum(pcb, p, dst_ip, dst_port, 0, 0);
}

/** Same as udp_sendto(), but with checksum */
err_t
udp_sendto_chksum(struct udp_pcb *pcb, struct pbuf *p, ip_addr_t *dst_ip,
                  u16_t dst_port, u8_t have_chksum, u16_t chksum)
{
#endif /* LWIP_CHECKSUM_ON_COPY */
  struct netif *netif;

  LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE, ("udp_send\n"));

  /* find the outgoing network interface for this packet */
#if LWIP_IGMP
  netif = ip_route((ip_addr_ismulticast(dst_ip))?(&(pcb->multicast_ip)):(dst_ip));
#else
  netif = ip_route(dst_ip);
#endif /* LWIP_IGMP */

  /* no outgoing network interface could be found? */
  if (netif == NULL) {
    LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_LEVEL_SERIOUS, ("udp_send: No route to %"U16_F".%"U16_F".%"U16_F".%"U16_F"\n",
      ip4_addr1_16(dst_ip), ip4_addr2_16(dst_ip), ip4_addr3_16(dst_ip), ip4_addr4_16(dst_ip)));
    UDP_STATS_INC(udp.rterr);
    return ERR_RTE;
  }
#if LWIP_CHECKSUM_ON_COPY
  return udp_sendto_if_chksum(pcb, p, dst_ip, dst_port, netif, have_chksum, chksum);
#else /* LWIP_CHECKSUM_ON_COPY */
  return udp_sendto_if(pcb, p, dst_ip, dst_port, netif);
#endif /* LWIP_CHECKSUM_ON_COPY */
}

/**
 * Send data to a specified address using UDP.
 * The netif used for sending can be specified.
 *
 * This function exists mainly for DHCP, to be able to send UDP packets
 * on a netif that is still down.
 *
 * @param pcb UDP PCB used to send the data.
 * @param p chain of pbuf's to be sent.
 * @param dst_ip Destination IP address.
 * @param dst_port Destination UDP port.
 * @param netif the netif used for sending.
 *
 * dst_ip & dst_port are expected to be in the same byte order as in the pcb.
 *
 * @return lwIP error code (@see udp_send for possible error codes)
 *
 * @see udp_disconnect() udp_send()
 */
err_t
udp_sendto_if(struct udp_pcb *pcb, struct pbuf *p,
  ip_addr_t *dst_ip, u16_t dst_port, struct netif *netif)
{
#if LWIP_CHECKSUM_ON_COPY
  return udp_sendto_if_chksum(pcb, p, dst_ip, dst_port, netif, 0, 0);
}

/** Same as udp_sendto_if(), but with checksum */
err_t
udp_sendto_if_chksum(struct udp_pcb *pcb, struct pbuf *p, ip_addr_t *dst_ip,
                     u16_t dst_port, struct netif *netif, u8_t have_chksum,
                     u16_t chksum)
{
#endif /* LWIP_CHECKSUM_ON_COPY */
  struct udp_hdr *udphdr;
  ip_addr_t *src_ip;
  err_t err;
  struct pbuf *q; /* q will be sent down the stack */

#if IP_SOF_BROADCAST
  /* broadcast filter? */
  if ( ((pcb->so_options & SOF_BROADCAST) == 0) && ip_addr_isbroadcast(dst_ip, netif) ) {
    LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_LEVEL_SERIOUS,
      ("udp_sendto_if: SOF_BROADCAST not enabled on pcb %p\n", (void *)pcb));
    return ERR_VAL;
  }
#endif /* IP_SOF_BROADCAST */

  /* if the PCB is not yet bound to a port, bind it here */
  if (pcb->local_port == 0) {
    LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE, ("udp_send: not yet bound to a port, binding now\n"));
    err = udp_bind(pcb, &pcb->local_ip, pcb->local_port);
    if (err != ERR_OK) {
      LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_SERIOUS, ("udp_send: forced port bind failed\n"));
      return err;
    }
  }

  /* not enough space to add an UDP header to first pbuf in given p chain? */
  if (pbuf_header(p, UDP_HLEN)) {
    /* allocate header in a separate new pbuf */
    q = pbuf_alloc(PBUF_IP, UDP_HLEN, PBUF_RAM);
    /* new header pbuf could not be allocated? */
    if (q == NULL) {
      LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_SERIOUS, ("udp_send: could not allocate header\n"));
      return ERR_MEM;
    }
    if (p->tot_len != 0) {
      /* chain header q in front of given pbuf p (only if p contains data) */
      pbuf_chain(q, p);
    }
    /* first pbuf q points to header pbuf */
    LWIP_DEBUGF(UDP_DEBUG,
                ("udp_send: added header pbuf %p before given pbuf %p\n", (void *)q, (void *)p));
  } else {
    /* adding space for header within p succeeded */
    /* first pbuf q equals given pbuf */
    q = p;
    LWIP_DEBUGF(UDP_DEBUG, ("udp_send: added header in given pbuf %p\n", (void *)p));
  }
  LWIP_ASSERT("check that first pbuf can hold struct udp_hdr",
              (q->len >= sizeof(struct udp_hdr)));
  /* q now represents the packet to be sent */
  udphdr = (struct udp_hdr *)q->payload;
  udphdr->src = htons(pcb->local_port);
  udphdr->dest = htons(dst_port);
  /* in UDP, 0 checksum means 'no checksum' */
  udphdr->chksum = 0x0000; 

  /* Multicast Loop? */
#if LWIP_IGMP
  if (ip_addr_ismulticast(dst_ip) && ((pcb->flags & UDP_FLAGS_MULTICAST_LOOP) != 0)) {
    q->flags |= PBUF_FLAG_MCASTLOOP;
  }
#endif /* LWIP_IGMP */


  /* PCB local address is IP_ANY_ADDR? */
  if (ip_addr_isany(&pcb->local_ip)) {
    /* use outgoing network interface IP address as source address */
    src_ip = &(netif->ip_addr);
  } else {
    /* check if UDP PCB local IP address is correct
     * this could be an old address if netif->ip_addr has changed */
    if (!ip_addr_cmp(&(pcb->local_ip), &(netif->ip_addr))) {
      /* local_ip doesn't match, drop the packet */
      if (q != p) {
        /* free the header pbuf */
        pbuf_free(q);
        q = NULL;
        /* p is still referenced by the caller, and will live on */
      }
      return ERR_VAL;
    }
    /* use UDP PCB local IP address as source address */
    src_ip = &(pcb->local_ip);
  }

  LWIP_DEBUGF(UDP_DEBUG, ("udp_send: sending datagram of length %"U16_F"\n", q->tot_len));

#if LWIP_UDPLITE
  /* UDP Lite protocol? */
  if (pcb->flags & UDP_FLAGS_UDPLITE) {
    u16_t chklen, chklen_hdr;
    LWIP_DEBUGF(UDP_DEBUG, ("udp_send: UDP LITE packet length %"U16_F"\n", q->tot_len));
    /* set UDP message length in UDP header */
    chklen_hdr = chklen = pcb->chksum_len_tx;
    if ((chklen < sizeof(struct udp_hdr)) || (chklen > q->tot_len)) {
      if (chklen != 0) {
        LWIP_DEBUGF(UDP_DEBUG, ("udp_send: UDP LITE pcb->chksum_len is illegal: %"U16_F"\n", chklen));
      }
      /* For UDP-Lite, checksum length of 0 means checksum
         over the complete packet. (See RFC 3828 chap. 3.1)
         At least the UDP-Lite header must be covered by the
         checksum, therefore, if chksum_len has an illegal
         value, we generate the checksum over the complete
         packet to be safe. */
      chklen_hdr = 0;
      chklen = q->tot_len;
    }
    udphdr->len = htons(chklen_hdr);
    /* calculate checksum */
#if CHECKSUM_GEN_UDP
    udphdr->chksum = inet_chksum_pseudo_partial(q, src_ip, dst_ip,
      IP_PROTO_UDPLITE, q->tot_len,
#if !LWIP_CHECKSUM_ON_COPY
      chklen);
#else /* !LWIP_CHECKSUM_ON_COPY */
      (have_chksum ? UDP_HLEN : chklen));
    if (have_chksum) {
      u32_t acc;
      acc = udphdr->chksum + (u16_t)~(chksum);
      udphdr->chksum = FOLD_U32T(acc);
    }
#endif /* !LWIP_CHECKSUM_ON_COPY */

    /* chksum zero must become 0xffff, as zero means 'no checksum' */
    if (udphdr->chksum == 0x0000) {
      udphdr->chksum = 0xffff;
    }
#endif /* CHECKSUM_GEN_UDP */
    /* output to IP */
    LWIP_DEBUGF(UDP_DEBUG, ("udp_send: ip_output_if (,,,,IP_PROTO_UDPLITE,)\n"));
#if LWIP_NETIF_HWADDRHINT
    netif->addr_hint = &(pcb->addr_hint);
#endif /* LWIP_NETIF_HWADDRHINT*/
    err = ip_output_if(q, src_ip, dst_ip, pcb->ttl, pcb->tos, IP_PROTO_UDPLITE, netif);
#if LWIP_NETIF_HWADDRHINT
    netif->addr_hint = NULL;
#endif /* LWIP_NETIF_HWADDRHINT*/
  } else
#endif /* LWIP_UDPLITE */
  {      /* UDP */
    LWIP_DEBUGF(UDP_DEBUG, ("udp_send: UDP packet length %"U16_F"\n", q->tot_len));
    udphdr->len = htons(q->tot_len);
    /* calculate checksum */
#if CHECKSUM_GEN_UDP
    if ((pcb->flags & UDP_FLAGS_NOCHKSUM) == 0) {
      u16_t udpchksum;
#if LWIP_CHECKSUM_ON_COPY
      if (have_chksum) {
        u32_t acc;
        udpchksum = inet_chksum_pseudo_partial(q, src_ip, dst_ip, IP_PROTO_UDP,
          q->tot_len, UDP_HLEN);
        acc = udpchksum + (u16_t)~(chksum);
        udpchksum = FOLD_U32T(acc);
      } else
#endif /* LWIP_CHECKSUM_ON_COPY */
      {
        udpchksum = inet_chksum_pseudo(q, src_ip, dst_ip, IP_PROTO_UDP, q->tot_len);
      }

      /* chksum zero must become 0xffff, as zero means 'no checksum' */
      if (udpchksum == 0x0000) {
        udpchksum = 0xffff;
      }
      udphdr->chksum = udpchksum;
    }
#endif /* CHECKSUM_GEN_UDP */
    LWIP_DEBUGF(UDP_DEBUG, ("udp_send: UDP checksum 0x%04"X16_F"\n", udphdr->chksum));
    LWIP_DEBUGF(UDP_DEBUG, ("udp_send: ip_output_if (,,,,IP_PROTO_UDP,)\n"));
    /* output to IP */
#if LWIP_NETIF_HWADDRHINT
    netif->addr_hint = &(pcb->addr_hint);
#endif /* LWIP_NETIF_HWADDRHINT*/
    err = ip_output_if(q, src_ip, dst_ip, pcb->ttl, pcb->tos, IP_PROTO_UDP, netif);
#if LWIP_NETIF_HWADDRHINT
    netif->addr_hint = NULL;
#endif /* LWIP_NETIF_HWADDRHINT*/
  }
  /* TODO: must this be increased even if error occured? */
  snmp_inc_udpoutdatagrams();

  /* did we chain a separate header pbuf earlier? */
  if (q != p) {
    /* free the header pbuf */
    pbuf_free(q);
    q = NULL;
    /* p is still referenced by the caller, and will live on */
  }

  UDP_STATS_INC(udp.xmit);
  return err;
}

/**
 * Bind an UDP PCB.
 *
 * @param pcb UDP PCB to be bound with a local address ipaddr and port.
 * @param ipaddr local IP address to bind with. Use IP_ADDR_ANY to
 * bind to all local interfaces.
 * @param port local UDP port to bind with. Use 0 to automatically bind
 * to a random port between UDP_LOCAL_PORT_RANGE_START and
 * UDP_LOCAL_PORT_RANGE_END.
 *
 * ipaddr & port are expected to be in the same byte order as in the pcb.
 *
 * @return lwIP error code.
 * - ERR_OK. Successful. No error occured.
 * - ERR_USE. The specified ipaddr and port are already bound to by
 * another UDP PCB.
 *
 * @see udp_disconnect()
 */
err_t
udp_bind(struct udp_pcb *pcb, ip_addr_t *ipaddr, u16_t port)
{
  struct udp_pcb *ipcb;
  u8_t rebind;

  LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE, ("udp_bind(ipaddr = "));
  ip_addr_debug_print(UDP_DEBUG, ipaddr);
  LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE, (", port = %"U16_F")\n", port));

  rebind = 0;
  /* Check for double bind and rebind of the same pcb */
  for (ipcb = udp_pcbs; ipcb != NULL; ipcb = ipcb->next) {
    /* is this UDP PCB already on active list? */
    if (pcb == ipcb) {
      /* pcb may occur at most once in active list */
      LWIP_ASSERT("rebind == 0", rebind == 0);
      /* pcb already in list, just rebind */
      rebind = 1;
    }

    /* By default, we don't allow to bind to a port that any other udp
       PCB is alread bound to, unless *all* PCBs with that port have tha
       REUSEADDR flag set. */
#if SO_REUSE
    else if (((pcb->so_options & SOF_REUSEADDR) == 0) &&
             ((ipcb->so_options & SOF_REUSEADDR) == 0)) {
#else /* SO_REUSE */
    /* port matches that of PCB in list and REUSEADDR not set -> reject */
    else {
#endif /* SO_REUSE */
      if ((ipcb->local_port == port) &&
          /* IP address matches, or one is IP_ADDR_ANY? */
          (ip_addr_isany(&(ipcb->local_ip)) ||
           ip_addr_isany(ipaddr) ||
           ip_addr_cmp(&(ipcb->local_ip), ipaddr))) {
        /* other PCB already binds to this local IP and port */
        LWIP_DEBUGF(UDP_DEBUG,
                    ("udp_bind: local port %"U16_F" already bound by another pcb\n", port));
        return ERR_USE;
      }
    }
  }

  ip_addr_set(&pcb->local_ip, ipaddr);

  /* no port specified? */
  if (port == 0) {
#ifndef UDP_LOCAL_PORT_RANGE_START
/* From http://www.iana.org/assignments/port-numbers:
   "The Dynamic and/or Private Ports are those from 49152 through 65535" */
#define UDP_LOCAL_PORT_RANGE_START  0xc000
#define UDP_LOCAL_PORT_RANGE_END    0xffff
#endif
    port = UDP_LOCAL_PORT_RANGE_START;
    ipcb = udp_pcbs;
    while ((ipcb != NULL) && (port != UDP_LOCAL_PORT_RANGE_END)) {
      if (ipcb->local_port == port) {
        /* port is already used by another udp_pcb */
        port++;
        /* restart scanning all udp pcbs */
        ipcb = udp_pcbs;
      } else {
        /* go on with next udp pcb */
        ipcb = ipcb->next;
      }
    }
    if (ipcb != NULL) {
      /* no more ports available in local range */
      LWIP_DEBUGF(UDP_DEBUG, ("udp_bind: out of free UDP ports\n"));
      return ERR_USE;
    }
  }
  pcb->local_port = port;
  snmp_insert_udpidx_tree(pcb);
  /* pcb not active yet? */
  if (rebind == 0) {
    /* place the PCB on the active list if not already there */
    pcb->next = udp_pcbs;
    udp_pcbs = pcb;
  }
  LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
              ("udp_bind: bound to %"U16_F".%"U16_F".%"U16_F".%"U16_F", port %"U16_F"\n",
               ip4_addr1_16(&pcb->local_ip), ip4_addr2_16(&pcb->local_ip),
               ip4_addr3_16(&pcb->local_ip), ip4_addr4_16(&pcb->local_ip),
               pcb->local_port));
  return ERR_OK;
}
/**
 * Connect an UDP PCB.
 *
 * This will associate the UDP PCB with the remote address.
 *
 * @param pcb UDP PCB to be connected with remote address ipaddr and port.
 * @param ipaddr remote IP address to connect with.
 * @param port remote UDP port to connect with.
 *
 * @return lwIP error code
 *
 * ipaddr & port are expected to be in the same byte order as in the pcb.
 *
 * The udp pcb is bound to a random local port if not already bound.
 *
 * @see udp_disconnect()
 */
err_t
udp_connect(struct udp_pcb *pcb, ip_addr_t *ipaddr, u16_t port)
{
  struct udp_pcb *ipcb;

  if (pcb->local_port == 0) {
    err_t err = udp_bind(pcb, &pcb->local_ip, pcb->local_port);
    if (err != ERR_OK) {
      return err;
    }
  }

  ip_addr_set(&pcb->remote_ip, ipaddr);
  pcb->remote_port = port;
  pcb->flags |= UDP_FLAGS_CONNECTED;
/** TODO: this functionality belongs in upper layers */
#ifdef LWIP_UDP_TODO
  /* Nail down local IP for netconn_addr()/getsockname() */
  if (ip_addr_isany(&pcb->local_ip) && !ip_addr_isany(&pcb->remote_ip)) {
    struct netif *netif;

    if ((netif = ip_route(&(pcb->remote_ip))) == NULL) {
      LWIP_DEBUGF(UDP_DEBUG, ("udp_connect: No route to 0x%lx\n", pcb->remote_ip.addr));
      UDP_STATS_INC(udp.rterr);
      return ERR_RTE;
    }
    /** TODO: this will bind the udp pcb locally, to the interface which
        is used to route output packets to the remote address. However, we
        might want to accept incoming packets on any interface! */
    pcb->local_ip = netif->ip_addr;
  } else if (ip_addr_isany(&pcb->remote_ip)) {
    pcb->local_ip.addr = 0;
  }
#endif
  LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
              ("udp_connect: connected to %"U16_F".%"U16_F".%"U16_F".%"U16_F",port %"U16_F"\n",
               ip4_addr1_16(&pcb->local_ip), ip4_addr2_16(&pcb->local_ip),
               ip4_addr3_16(&pcb->local_ip), ip4_addr4_16(&pcb->local_ip),
               pcb->local_port));

  /* Insert UDP PCB into the list of active UDP PCBs. */
  for (ipcb = udp_pcbs; ipcb != NULL; ipcb = ipcb->next) {
    if (pcb == ipcb) {
      /* already on the list, just return */
      return ERR_OK;
    }
  }
  /* PCB not yet on the list, add PCB now */
  pcb->next = udp_pcbs;
  udp_pcbs = pcb;
  return ERR_OK;
}

/**
 * Disconnect a UDP PCB
 *
 * @param pcb the udp pcb to disconnect.
 */
void
udp_disconnect(struct udp_pcb *pcb)
{
  /* reset remote address association */
  ip_addr_set_any(&pcb->remote_ip);
  pcb->remote_port = 0;
  /* mark PCB as unconnected */
  pcb->flags &= ~UDP_FLAGS_CONNECTED;
}

/**
 * Set a receive callback for a UDP PCB
 *
 * This callback will be called when receiving a datagram for the pcb.
 *
 * @param pcb the pcb for wich to set the recv callback
 * @param recv function pointer of the callback function
 * @param recv_arg additional argument to pass to the callback function
 */
void
udp_recv(struct udp_pcb *pcb, udp_recv_fn recv, void *recv_arg)
{
  /* remember recv() callback and user data */
  pcb->recv = recv;
  pcb->recv_arg = recv_arg;
}

/**
 * Remove an UDP PCB.
 *
 * @param pcb UDP PCB to be removed. The PCB is removed from the list of
 * UDP PCB's and the data structure is freed from memory.
 *
 * @see udp_new()
 */
void
udp_remove(struct udp_pcb *pcb)
{
  struct udp_pcb *pcb2;

  snmp_delete_udpidx_tree(pcb);
  /* pcb to be removed is first in list? */
  if (udp_pcbs == pcb) {
    /* make list start at 2nd pcb */
    udp_pcbs = udp_pcbs->next;
    /* pcb not 1st in list */
  } else {
    for (pcb2 = udp_pcbs; pcb2 != NULL; pcb2 = pcb2->next) {
      /* find pcb in udp_pcbs list */
      if (pcb2->next != NULL && pcb2->next == pcb) {
        /* remove pcb from list */
        pcb2->next = pcb->next;
      }
    }
  }
  memp_free(MEMP_UDP_PCB, pcb);
}

/**
 * Create a UDP PCB.
 *
 * @return The UDP PCB which was created. NULL if the PCB data structure
 * could not be allocated.
 *
 * @see udp_remove()
 */
struct udp_pcb *
udp_new(void)
{
  struct udp_pcb *pcb;
  pcb = (struct udp_pcb *)memp_malloc(MEMP_UDP_PCB);
  /* could allocate UDP PCB? */
  if (pcb != NULL) {
    /* UDP Lite: by initializing to all zeroes, chksum_len is set to 0
     * which means checksum is generated over the whole datagram per default
     * (recommended as default by RFC 3828). */
    /* initialize PCB to all zeroes */
    memset(pcb, 0, sizeof(struct udp_pcb));
    pcb->ttl = UDP_TTL;
  }
  return pcb;
}

#if UDP_DEBUG
/**
 * Print UDP header information for debug purposes.
 *
 * @param udphdr pointer to the udp header in memory.
 */
void
udp_debug_print(struct udp_hdr *udphdr)
{
  LWIP_DEBUGF(UDP_DEBUG, ("UDP header:\n"));
  LWIP_DEBUGF(UDP_DEBUG, ("+-------------------------------+\n"));
  LWIP_DEBUGF(UDP_DEBUG, ("|     %5"U16_F"     |     %5"U16_F"     | (src port, dest port)\n",
                          ntohs(udphdr->src), ntohs(udphdr->dest)));
  LWIP_DEBUGF(UDP_DEBUG, ("+-------------------------------+\n"));
  LWIP_DEBUGF(UDP_DEBUG, ("|     %5"U16_F"     |     0x%04"X16_F"    | (len, chksum)\n",
                          ntohs(udphdr->len), ntohs(udphdr->chksum)));
  LWIP_DEBUGF(UDP_DEBUG, ("+-------------------------------+\n"));
}
#endif /* UDP_DEBUG */

#endif /* LWIP_UDP */
