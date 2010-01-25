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
 * $Id: psock.c,v 1.2 2006/06/12 08:00:30 adam Exp $
 */

#include <stdio.h>
#include <string.h>

#include "uipopt.h"
#include "psock.h"
#include "uip.h"

#define STATE_NONE 0
#define STATE_ACKED 1
#define STATE_READ 2
#define STATE_BLOCKED_NEWDATA 3
#define STATE_BLOCKED_CLOSE 4
#define STATE_BLOCKED_SEND 5
#define STATE_DATA_SENT 6

/*
 * Return value of the buffering functions that indicates that a
 * buffer was not filled by incoming data.
 *
 */
#define BUF_NOT_FULL 0
#define BUF_NOT_FOUND 0

/*
 * Return value of the buffering functions that indicates that a
 * buffer was completely filled by incoming data.
 *
 */
#define BUF_FULL 1

/*
 * Return value of the buffering functions that indicates that an
 * end-marker byte was found.
 *
 */
#define BUF_FOUND 2

/*---------------------------------------------------------------------------*/
static void
buf_setup(struct psock_buf *buf,
	  u8_t *bufptr, u16_t bufsize)
{
  buf->ptr = bufptr;
  buf->left = bufsize;
}
/*---------------------------------------------------------------------------*/
static u8_t
buf_bufdata(struct psock_buf *buf, u16_t len,
	    u8_t **dataptr, u16_t *datalen)
{
  if(*datalen < buf->left) {
    memcpy(buf->ptr, *dataptr, *datalen);
    buf->ptr += *datalen;
    buf->left -= *datalen;
    *dataptr += *datalen;
    *datalen = 0;
    return BUF_NOT_FULL;
  } else if(*datalen == buf->left) {
    memcpy(buf->ptr, *dataptr, *datalen);
    buf->ptr += *datalen;
    buf->left = 0;
    *dataptr += *datalen;
    *datalen = 0;
    return BUF_FULL;
  } else {
    memcpy(buf->ptr, *dataptr, buf->left);
    buf->ptr += buf->left;
    *datalen -= buf->left;
    *dataptr += buf->left;
    buf->left = 0;
    return BUF_FULL;
  }
}
/*---------------------------------------------------------------------------*/
static u8_t
buf_bufto(register struct psock_buf *buf, u8_t endmarker,
	  register u8_t **dataptr, register u16_t *datalen)
{
  u8_t c;
  while(buf->left > 0 && *datalen > 0) {
    c = *buf->ptr = **dataptr;
    ++*dataptr;
    ++buf->ptr;
    --*datalen;
    --buf->left;
    
    if(c == endmarker) {
      return BUF_FOUND;
    }
  }

  if(*datalen == 0) {
    return BUF_NOT_FOUND;
  }

  while(*datalen > 0) {
    c = **dataptr;
    --*datalen;
    ++*dataptr;
    
    if(c == endmarker) {
      return BUF_FOUND | BUF_FULL;
    }
  }
  
  return BUF_FULL;
}
/*---------------------------------------------------------------------------*/
static char
send_data(register struct psock *s)
{
  if(s->state != STATE_DATA_SENT || uip_rexmit()) {
    if(s->sendlen > uip_mss()) {
      uip_send(s->sendptr, uip_mss());
    } else {
      uip_send(s->sendptr, s->sendlen);
    }
    s->state = STATE_DATA_SENT;
    return 1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static char
data_acked(register struct psock *s)
{
  if(s->state == STATE_DATA_SENT && uip_acked()) {
    if(s->sendlen > uip_mss()) {
      s->sendlen -= uip_mss();
      s->sendptr += uip_mss();
    } else {
      s->sendptr += s->sendlen;
      s->sendlen = 0;
    }
    s->state = STATE_ACKED;
    return 1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
PT_THREAD(psock_send(register struct psock *s, const char *buf,
		     unsigned int len))
{
  PT_BEGIN(&s->psockpt);

  /* If there is no data to send, we exit immediately. */
  if(len == 0) {
    PT_EXIT(&s->psockpt);
  }

  /* Save the length of and a pointer to the data that is to be
     sent. */
  s->sendptr = buf;
  s->sendlen = len;

  s->state = STATE_NONE;

  /* We loop here until all data is sent. The s->sendlen variable is
     updated by the data_sent() function. */
  while(s->sendlen > 0) {

    /*
     * The condition for this PT_WAIT_UNTIL is a little tricky: the
     * protothread will wait here until all data has been acknowledged
     * (data_acked() returns true) and until all data has been sent
     * (send_data() returns true). The two functions data_acked() and
     * send_data() must be called in succession to ensure that all
     * data is sent. Therefore the & operator is used instead of the
     * && operator, which would cause only the data_acked() function
     * to be called when it returns false.
     */
    PT_WAIT_UNTIL(&s->psockpt, data_acked(s) & send_data(s));
  }

  s->state = STATE_NONE;
  
  PT_END(&s->psockpt);
}
/*---------------------------------------------------------------------------*/
PT_THREAD(psock_generator_send(register struct psock *s,
			       unsigned short (*generate)(void *), void *arg))
{
  PT_BEGIN(&s->psockpt);

  /* Ensure that there is a generator function to call. */
  if(generate == NULL) {
    PT_EXIT(&s->psockpt);
  }

  /* Call the generator function to generate the data in the
     uip_appdata buffer. */
  s->sendlen = generate(arg);
  s->sendptr = uip_appdata;

  s->state = STATE_NONE;  
  do {
    /* Call the generator function again if we are called to perform a
       retransmission. */
    if(uip_rexmit()) {
      generate(arg);
    }
    /* Wait until all data is sent and acknowledged. */
    PT_WAIT_UNTIL(&s->psockpt, data_acked(s) & send_data(s));
  } while(s->sendlen > 0);
  
  s->state = STATE_NONE;
  
  PT_END(&s->psockpt);
}
/*---------------------------------------------------------------------------*/
u16_t
psock_datalen(struct psock *psock)
{
  return psock->bufsize - psock->buf.left;
}
/*---------------------------------------------------------------------------*/
char
psock_newdata(struct psock *s)
{
  if(s->readlen > 0) {
    /* There is data in the uip_appdata buffer that has not yet been
       read with the PSOCK_READ functions. */
    return 1;
  } else if(s->state == STATE_READ) {
    /* All data in uip_appdata buffer already consumed. */
    s->state = STATE_BLOCKED_NEWDATA;
    return 0;
  } else if(uip_newdata()) {
    /* There is new data that has not been consumed. */
    return 1;
  } else {
    /* There is no new data. */
    return 0;
  }
}
/*---------------------------------------------------------------------------*/
PT_THREAD(psock_readto(register struct psock *psock, unsigned char c))
{
  PT_BEGIN(&psock->psockpt);

  buf_setup(&psock->buf, psock->bufptr, psock->bufsize);
  
  /* XXX: Should add buf_checkmarker() before do{} loop, if
     incoming data has been handled while waiting for a write. */

  do {
    if(psock->readlen == 0) {
      PT_WAIT_UNTIL(&psock->psockpt, psock_newdata(psock));
      psock->state = STATE_READ;
      psock->readptr = (u8_t *)uip_appdata;
      psock->readlen = uip_datalen();
    }
  } while((buf_bufto(&psock->buf, c,
		     &psock->readptr,
		     &psock->readlen) & BUF_FOUND) == 0);
  
  if(psock_datalen(psock) == 0) {
    psock->state = STATE_NONE;
    PT_RESTART(&psock->psockpt);
  }
  PT_END(&psock->psockpt);
}
/*---------------------------------------------------------------------------*/
PT_THREAD(psock_readbuf(register struct psock *psock))
{
  PT_BEGIN(&psock->psockpt);

  buf_setup(&psock->buf, psock->bufptr, psock->bufsize);
  
  /* XXX: Should add buf_checkmarker() before do{} loop, if
     incoming data has been handled while waiting for a write. */

  do {
    if(psock->readlen == 0) {
      PT_WAIT_UNTIL(&psock->psockpt, psock_newdata(psock));
      printf("Waited for newdata\n");
      psock->state = STATE_READ;
      psock->readptr = (u8_t *)uip_appdata;
      psock->readlen = uip_datalen();
    }
  } while(buf_bufdata(&psock->buf, psock->bufsize,
			 &psock->readptr,
			 &psock->readlen) != BUF_FULL);

  if(psock_datalen(psock) == 0) {
    psock->state = STATE_NONE;
    PT_RESTART(&psock->psockpt);
  }
  PT_END(&psock->psockpt);
}
/*---------------------------------------------------------------------------*/
void
psock_init(register struct psock *psock, char *buffer, unsigned int buffersize)
{
  psock->state = STATE_NONE;
  psock->readlen = 0;
  psock->bufptr = buffer;
  psock->bufsize = buffersize;
  buf_setup(&psock->buf, buffer, buffersize);
  PT_INIT(&psock->pt);
  PT_INIT(&psock->psockpt);
}
/*---------------------------------------------------------------------------*/
