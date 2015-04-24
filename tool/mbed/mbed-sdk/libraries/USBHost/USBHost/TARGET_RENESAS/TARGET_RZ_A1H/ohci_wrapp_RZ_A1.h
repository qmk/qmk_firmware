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

#ifndef OHCI_WRAPP_RZ_A1_H
#define OHCI_WRAPP_RZ_A1_H

#ifdef __cplusplus
extern "C" {
#endif

#define OHCI_REG_REVISION           (0x00)    /* HcRevision         */
#define OHCI_REG_CONTROL            (0x04)    /* HcControl          */
#define OHCI_REG_COMMANDSTATUS      (0x08)    /* HcCommandStatus    */
#define OHCI_REG_INTERRUPTSTATUS    (0x0C)    /* HcInterruptStatus  */
#define OHCI_REG_INTERRUPTENABLE    (0x10)    /* HcInterruptEnable  */
#define OHCI_REG_INTERRUPTDISABLE   (0x14)    /* HcInterruptDisable */
#define OHCI_REG_HCCA               (0x18)    /* HcHCCA             */
#define OHCI_REG_PERIODCURRENTED    (0x1C)    /* HcPeriodCurrentED  */
#define OHCI_REG_CONTROLHEADED      (0x20)    /* HcControlHeadED    */
#define OHCI_REG_CONTROLCURRENTED   (0x24)    /* HcControlCurrentED */
#define OHCI_REG_BULKHEADED         (0x28)    /* HcBulkHeadED       */
#define OHCI_REG_BULKCURRENTED      (0x2C)    /* HcBulkCurrentED    */
#define OHCI_REG_DONEHEADED         (0x30)    /* HcDoneHead         */
#define OHCI_REG_FMINTERVAL         (0x34)    /* HcFmInterval       */
#define OHCI_REG_FMREMAINING        (0x38)    /* HcFmRemaining      */
#define OHCI_REG_FMNUMBER           (0x3C)    /* HcFmNumber         */
#define OHCI_REG_PERIODICSTART      (0x40)    /* HcPeriodicStart    */
#define OHCI_REG_LSTHRESHOLD        (0x44)    /* HcLSThreshold      */
#define OHCI_REG_RHDESCRIPTORA      (0x48)    /* HcRhDescriptorA    */
#define OHCI_REG_RHDESCRIPTORB      (0x4C)    /* HcRhDescriptorB    */
#define OHCI_REG_RHSTATUS           (0x50)    /* HcRhStatus         */
#define OHCI_REG_RHPORTSTATUS1      (0x54)    /* HcRhPortStatus1    */

typedef void (usbisr_fnc_t)(void);

extern void ohciwrapp_init(usbisr_fnc_t *p_usbisr_fnc);
extern uint32_t ohciwrapp_reg_r(uint32_t reg_ofs);
extern void ohciwrapp_reg_w(uint32_t reg_ofs, uint32_t set_data);
extern void ohciwrapp_interrupt(uint32_t int_sense);

#ifdef __cplusplus
}
#endif

#endif  /* OHCI_WRAPP_RZ_A1_H */
