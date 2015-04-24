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

#ifndef OHCI_WRAPP_RZ_A1_LOCAL_H
#define OHCI_WRAPP_RZ_A1_LOCAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* ConditionCode */
#define TD_CC_NOERROR             (0)
#define TD_CC_CRC                 (1)
#define TD_CC_BITSTUFFING         (2)
#define TD_CC_DATATOGGLEMISMATCH  (3)
#define TD_CC_STALL               (4)
#define TD_CC_DEVICENOTRESPONDING (5)
#define TD_CC_PIDCHECKFAILURE     (6)
#define TD_CC_UNEXPECTEDPID       (7)
#define TD_CC_DATAOVERRUN         (8)
#define TD_CC_DATAUNDERRUN        (9)
#define TD_CC_BUFFEROVERRUN       (12)
#define TD_CC_BUFFERUNDERRUN      (13)
#define TD_CC_NOT_ACCESSED_1      (14)
#define TD_CC_NOT_ACCESSED_2      (15)

extern void ohciwrapp_loc_Connect(uint32_t type);
extern void ohciwrapp_loc_TransEnd(uint32_t pipe, uint32_t ConditionCode);

#ifdef __cplusplus
}
#endif

#endif  /* OHCI_WRAPP_RZ_A1_LOCAL_H */
