/**
 * @file
 * SLIP Interface
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
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
 * This file is built upon the file: src/arch/rtxc/netif/sioslip.c
 *
 * Author: Magnus Ivarsson <magnus.ivarsson(at)volvo.com> 
 */

/* 
 * This is an arch independent SLIP netif. The specific serial hooks must be
 * provided by another file. They are sio_open, sio_read/sio_tryread and sio_send
 */

#include "netif/slipif.h"
#include "lwip/opt.h"

#if LWIP_HAVE_SLIPIF

#include "lwip/def.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/sio.h"

#define SLIP_BLOCK     1
#define SLIP_DONTBLOCK 0

#define SLIP_END     0300 /* 0xC0 */
#define SLIP_ESC     0333 /* 0xDB */
#define SLIP_ESC_END 0334 /* 0xDC */
#define SLIP_ESC_ESC 0335 /* 0xDD */

#define SLIP_MAX_SIZE 1500

enum slipif_recv_state {
    SLIP_RECV_NORMAL,
    SLIP_RECV_ESCAPE,
};

struct slipif_priv {
  sio_fd_t sd;
  /* q is the whole pbuf chain for a packet, p is the current pbuf in the chain */
  struct pbuf *p, *q;
  enum slipif_recv_state state;
  u16_t i, recved;
};

/**
 * Send a pbuf doing the necessary SLIP encapsulation
 *
 * Uses the serial layer's sio_send()
 *
 * @param netif the lwip network interface structure for this slipif
 * @param p the pbuf chaing packet to send
 * @param ipaddr the ip address to send the packet to (not used for slipif)
 * @return always returns ERR_OK since the serial layer does not provide return values
 */
err_t
slipif_output(struct netif *netif, struct pbuf *p, ip_addr_t *ipaddr)
{
  struct slipif_priv *priv;
  struct pbuf *q;
  u16_t i;
  u8_t c;

  LWIP_ASSERT("netif != NULL", (netif != NULL));
  LWIP_ASSERT("netif->state != NULL", (netif->state != NULL));
  LWIP_ASSERT("p != NULL", (p != NULL));

  LWIP_UNUSED_ARG(ipaddr);

  priv = netif->state;

  /* Send pbuf out on the serial I/O device. */
  sio_send(SLIP_END, priv->sd);

  for (q = p; q != NULL; q = q->next) {
    for (i = 0; i < q->len; i++) {
      c = ((u8_t *)q->payload)[i];
      switch (c) {
      case SLIP_END:
        sio_send(SLIP_ESC, priv->sd);
        sio_send(SLIP_ESC_END, priv->sd);
        break;
      case SLIP_ESC:
        sio_send(SLIP_ESC, priv->sd);
        sio_send(SLIP_ESC_ESC, priv->sd);
        break;
      default:
        sio_send(c, priv->sd);
        break;
      }
    }
  }
  sio_send(SLIP_END, priv->sd);
  return ERR_OK;
}

/**
 * Static function for easy use of blockig or non-blocking
 * sio_read
 *
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @param block if 1, call sio_read; if 0, call sio_tryread
 * @return return value of sio_read of sio_tryread
 */
static u32_t
slip_sio_read(sio_fd_t fd, u8_t* data, u32_t len, u8_t block)
{
  if (block) {
    return sio_read(fd, data, len);
  } else {
    return sio_tryread(fd, data, len);
  }
}

/**
 * Handle the incoming SLIP stream character by character
 *
 * Poll the serial layer by calling sio_read() or sio_tryread().
 *
 * @param netif the lwip network interface structure for this slipif
 * @param block if 1, block until data is received; if 0, return when all data
 *        from the buffer is received (multiple calls to this function will
 *        return a complete packet, NULL is returned before - used for polling)
 * @return The IP packet when SLIP_END is received
 */
static struct pbuf *
slipif_input(struct netif *netif, u8_t block)
{
  struct slipif_priv *priv;
  u8_t c;
  struct pbuf *t;

  LWIP_ASSERT("netif != NULL", (netif != NULL));
  LWIP_ASSERT("netif->state != NULL", (netif->state != NULL));

  priv = netif->state;

  while (slip_sio_read(priv->sd, &c, 1, block) > 0) {
    switch (priv->state) {
    case SLIP_RECV_NORMAL:
      switch (c) {
      case SLIP_END:
        if (priv->recved > 0) {
          /* Received whole packet. */
          /* Trim the pbuf to the size of the received packet. */
          pbuf_realloc(priv->q, priv->recved);

          LINK_STATS_INC(link.recv);

          LWIP_DEBUGF(SLIP_DEBUG, ("slipif: Got packet\n"));
          t = priv->q;
          priv->p = priv->q = NULL;
          priv->i = priv->recved = 0;
          return t;
        }
        continue;
      case SLIP_ESC:
        priv->state = SLIP_RECV_ESCAPE;
        continue;
      }
      break;
    case SLIP_RECV_ESCAPE:
      switch (c) {
      case SLIP_ESC_END:
        c = SLIP_END;
        break;
      case SLIP_ESC_ESC:
        c = SLIP_ESC;
        break;
      }
      priv->state = SLIP_RECV_NORMAL;
      /* FALLTHROUGH */
    }

    /* byte received, packet not yet completely received */
    if (priv->p == NULL) {
      /* allocate a new pbuf */
      LWIP_DEBUGF(SLIP_DEBUG, ("slipif_input: alloc\n"));
      priv->p = pbuf_alloc(PBUF_LINK, (PBUF_POOL_BUFSIZE - PBUF_LINK_HLEN), PBUF_POOL);

      if (priv->p == NULL) {
        LINK_STATS_INC(link.drop);
        LWIP_DEBUGF(SLIP_DEBUG, ("slipif_input: no new pbuf! (DROP)\n"));
        /* don't process any further since we got no pbuf to receive to */
        break;
      }

      if (priv->q != NULL) {
        /* 'chain' the pbuf to the existing chain */
        pbuf_cat(priv->q, priv->p);
      } else {
        /* p is the first pbuf in the chain */
        priv->q = priv->p;
      }
    }

    /* this automatically drops bytes if > SLIP_MAX_SIZE */
    if ((priv->p != NULL) && (priv->recved <= SLIP_MAX_SIZE)) {
      ((u8_t *)priv->p->payload)[priv->i] = c;
      priv->recved++;
      priv->i++;
      if (priv->i >= priv->p->len) {
        /* on to the next pbuf */
        priv->i = 0;
        if (priv->p->next != NULL && priv->p->next->len > 0) {
          /* p is a chain, on to the next in the chain */
            priv->p = priv->p->next;
        } else {
          /* p is a single pbuf, set it to NULL so next time a new
           * pbuf is allocated */
            priv->p = NULL;
        }
      }
    }
  }

  return NULL;
}

#if !NO_SYS
/**
 * The SLIP input thread.
 *
 * Feed the IP layer with incoming packets
 *
 * @param nf the lwip network interface structure for this slipif
 */
static void
slipif_loop_thread(void *nf)
{
  struct pbuf *p;
  struct netif *netif = (struct netif *)nf;

  while (1) {
    p = slipif_input(netif, SLIP_BLOCK);
    if (p != NULL) {
      if (netif->input(p, netif) != ERR_OK) {
        pbuf_free(p);
        p = NULL;
      }
    }
  }
}
#endif /* !NO_SYS */

/**
 * SLIP netif initialization
 *
 * Call the arch specific sio_open and remember
 * the opened device in the state field of the netif.
 *
 * @param netif the lwip network interface structure for this slipif
 * @return ERR_OK if serial line could be opened,
 *         ERR_MEM if no memory could be allocated,
 *         ERR_IF is serial line couldn't be opened
 *
 * @note netif->num must contain the number of the serial port to open
 *       (0 by default)
 */
err_t
slipif_init(struct netif *netif)
{
  struct slipif_priv *priv;

  LWIP_DEBUGF(SLIP_DEBUG, ("slipif_init: netif->num=%"U16_F"\n", (u16_t)netif->num));

  /* Allocate private data */
  priv = mem_malloc(sizeof(struct slipif_priv));
  if (!priv) {
    return ERR_MEM;
  }

  netif->name[0] = 's';
  netif->name[1] = 'l';
  netif->output = slipif_output;
  netif->mtu = SLIP_MAX_SIZE;
  netif->flags |= NETIF_FLAG_POINTTOPOINT;

  /* Try to open the serial port (netif->num contains the port number). */
  priv->sd = sio_open(netif->num);
  if (!priv->sd) {
    /* Opening the serial port failed. */
    mem_free(priv);
    return ERR_IF;
  }

  /* Initialize private data */
  priv->p = NULL;
  priv->q = NULL;
  priv->state = SLIP_RECV_NORMAL;
  priv->i = 0;
  priv->recved = 0;

  netif->state = priv;

  /* initialize the snmp variables and counters inside the struct netif
   * ifSpeed: no assumption can be made without knowing more about the
   * serial line!
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_slip, 0);

  /* Create a thread to poll the serial line. */
  sys_thread_new(SLIPIF_THREAD_NAME, slipif_loop_thread, netif,
    SLIPIF_THREAD_STACKSIZE, SLIPIF_THREAD_PRIO);
  return ERR_OK;
}

/**
 * Polls the serial device and feeds the IP layer with incoming packets.
 *
 * @param netif The lwip network interface structure for this slipif
 */
void
slipif_poll(struct netif *netif)
{
  struct pbuf *p;
  struct slipif_priv *priv;

  LWIP_ASSERT("netif != NULL", (netif != NULL));
  LWIP_ASSERT("netif->state != NULL", (netif->state != NULL));

  priv = netif->state;

  while ((p = slipif_input(netif, SLIP_DONTBLOCK)) != NULL) {
    if (netif->input(p, netif) != ERR_OK) {
      pbuf_free(p);
    }
  }
}

#endif /* LWIP_HAVE_SLIPIF */
