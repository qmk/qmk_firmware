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

#define NUMBER_OF_LOGICAL_ENDPOINTS (16)
#define NUMBER_OF_PHYSICAL_ENDPOINTS (NUMBER_OF_LOGICAL_ENDPOINTS * 2)

/* Define physical endpoint numbers */

/*      Endpoint    No.     Type(s)   MaxSiz  DoubleBuf  pipe */
/*      ----------------    --------- ------  ---------  ---- */
#define EP0OUT      (0)  /* Control    256    No           0  */
#define EP0IN       (1)  /* Control    256    No           0  */
#define EP1OUT      (2)  /* Int         64    No           6  */
#define EP1IN       (3)  /* Int         64    No           7  */
#define EP2OUT      (4)  /* Bulk      2048    Yes          3  */
#define EP2IN       (5)  /* Bulk      2048    Yes          4  */
#define EP3OUT      (6)  /* Bulk/Iso  2048    Yes          1  */
#define EP3IN       (7)  /* Bulk/Iso  2048    Yes          2  */
/*following EP is not configured in sample program*/
#define EP6IN       (8)  /* Bulk      2048    Yes          5  */
#define EP8IN       (9)  /* Int        64     No           8  */
#define EP9IN       (10) /* Bulk       512    Bulk         9  */
#define EP10IN      (11) /* Int/Bulk  2048    Bulk        10  */
#define EP11IN      (12) /* Bulk      2048    Yes         11  */
#define EP12IN      (13) /* Bulk      2048    Yes         12  */
#define EP13IN      (14) /* Bulk      2048    Yes         13  */
#define EP14IN      (15) /* Bulk      2048    Yes         14  */
#define EP15IN      (16) /* Bulk      2048    Yes         15  */

/* Maximum Packet sizes */
#define MAX_PACKET_SIZE_EP0   (64)      /*pipe0/pipe0: control      */
#define MAX_PACKET_SIZE_EP1   (64)      /*pipe6/pipe7: interrupt    */
#define MAX_PACKET_SIZE_EP2  (512)      /*pipe3/pipe4: bulk         */
#define MAX_PACKET_SIZE_EP3  (512)      /*pipe1/pipe2: isochronous  */
#define MAX_PACKET_SIZE_EP6   (64)      /*pipe5:    Note *1 */
#define MAX_PACKET_SIZE_EP8   (64)      /*pipe7:    Note *1 */
#define MAX_PACKET_SIZE_EP9  (512)      /*pipe8:    Note *1 */
#define MAX_PACKET_SIZE_EP10 (512)      /*pipe9:    Note *1 */
#define MAX_PACKET_SIZE_EP11 (512)      /*pipe10:   Note *1 */
#define MAX_PACKET_SIZE_EP12 (512)      /*pipe11:   Note *1 */
#define MAX_PACKET_SIZE_EP13 (512)      /*pipe12:   Note *1 */
#define MAX_PACKET_SIZE_EP14 (512)      /*pipe13:   Note *1 */
#define MAX_PACKET_SIZE_EP15 (512)      /*pipe14:   Note *1 */
/* Note *1: This pipe is not configure in sample program */


/* Generic endpoints - intended to be portable accross devices */
/* and be suitable for simple USB devices. */

/* Bulk endpoints */
#define EPBULK_OUT  (EP2OUT)
#define EPBULK_IN   (EP2IN)
#define EPBULK_OUT_callback   EP2_OUT_callback
#define EPBULK_IN_callback    EP2_IN_callback
/* Interrupt endpoints */
#define EPINT_OUT   (EP1OUT)
#define EPINT_IN    (EP1IN)
#define EPINT_OUT_callback    EP1_OUT_callback
#define EPINT_IN_callback     EP1_IN_callback
/* Isochronous endpoints */
#define EPISO_OUT   (EP3OUT)
#define EPISO_IN    (EP3IN)
#define EPISO_OUT_callback    EP3_OUT_callback
#define EPISO_IN_callback     EP3_IN_callback

#define MAX_PACKET_SIZE_EPBULK  (MAX_PACKET_SIZE_EP2)
#define MAX_PACKET_SIZE_EPINT   (MAX_PACKET_SIZE_EP1)
#define MAX_PACKET_SIZE_EPISO   (MAX_PACKET_SIZE_EP3)

/*EOF*/
