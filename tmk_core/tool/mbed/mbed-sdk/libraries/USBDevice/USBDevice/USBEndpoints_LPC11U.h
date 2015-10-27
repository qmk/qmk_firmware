/* Copyright (c) 2010-2011 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#define NUMBER_OF_LOGICAL_ENDPOINTS (5)
#define NUMBER_OF_PHYSICAL_ENDPOINTS (NUMBER_OF_LOGICAL_ENDPOINTS * 2)

/* Define physical endpoint numbers */

/*      Endpoint    No.     Type(s)       MaxPacket   DoubleBuffer  */
/*      ----------------    ------------  ----------  ---           */
#define EP0OUT      (0)  /* Control       64          No            */
#define EP0IN       (1)  /* Control       64          No            */
#define EP1OUT      (2)  /* Int/Bulk/Iso  64/64/1023  Yes           */
#define EP1IN       (3)  /* Int/Bulk/Iso  64/64/1023  Yes           */
#define EP2OUT      (4)  /* Int/Bulk/Iso  64/64/1023  Yes           */
#define EP2IN       (5)  /* Int/Bulk/Iso  64/64/1023  Yes           */
#define EP3OUT      (6)  /* Int/Bulk/Iso  64/64/1023  Yes           */
#define EP3IN       (7)  /* Int/Bulk/Iso  64/64/1023  Yes           */
#define EP4OUT      (8)  /* Int/Bulk/Iso  64/64/1023  Yes           */
#define EP4IN       (9)  /* Int/Bulk/Iso  64/64/1023  Yes           */

/* Maximum Packet sizes */

#define MAX_PACKET_SIZE_EP0 (64)
#define MAX_PACKET_SIZE_EP1 (64) /* Int/Bulk */
#define MAX_PACKET_SIZE_EP2 (64) /* Int/Bulk */
#define MAX_PACKET_SIZE_EP3 (64) /* Int/Bulk */
#define MAX_PACKET_SIZE_EP4 (64) /* Int/Bulk */

#define MAX_PACKET_SIZE_EP1_ISO (1023) /* Isochronous */
#define MAX_PACKET_SIZE_EP2_ISO (1023) /* Isochronous */
#define MAX_PACKET_SIZE_EP3_ISO (1023) /* Isochronous */
#define MAX_PACKET_SIZE_EP4_ISO (1023) /* Isochronous */

/* Generic endpoints - intended to be portable accross devices */
/* and be suitable for simple USB devices. */

/* Bulk endpoint */
#define EPBULK_OUT  (EP2OUT)
#define EPBULK_IN   (EP2IN)
#define EPBULK_OUT_callback   EP2_OUT_callback
#define EPBULK_IN_callback    EP2_IN_callback
/* Interrupt endpoint */
#define EPINT_OUT   (EP1OUT)
#define EPINT_IN    (EP1IN)
#define EPINT_OUT_callback    EP1_OUT_callback
#define EPINT_IN_callback     EP1_IN_callback
/* Isochronous endpoint */
#define EPISO_OUT   (EP3OUT)
#define EPISO_IN    (EP3IN)
#define EPISO_OUT_callback    EP3_OUT_callback
#define EPISO_IN_callback     EP3_IN_callback

#define MAX_PACKET_SIZE_EPBULK  (MAX_PACKET_SIZE_EP2)
#define MAX_PACKET_SIZE_EPINT   (MAX_PACKET_SIZE_EP1)
#define MAX_PACKET_SIZE_EPISO   (MAX_PACKET_SIZE_EP3_ISO)
