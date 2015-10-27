/* mbed USBHost Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined(TARGET_LPC1768)

#include "mbed.h"
#include "USBHALHost.h"
#include "dbg.h"

// bits of the USB/OTG clock control register
#define HOST_CLK_EN     (1<<0)
#define DEV_CLK_EN      (1<<1)
#define PORTSEL_CLK_EN  (1<<3)
#define AHB_CLK_EN      (1<<4)

// bits of the USB/OTG clock status register
#define HOST_CLK_ON     (1<<0)
#define DEV_CLK_ON      (1<<1)
#define PORTSEL_CLK_ON  (1<<3)
#define AHB_CLK_ON      (1<<4)

// we need host clock, OTG/portsel clock and AHB clock
#define CLOCK_MASK (HOST_CLK_EN | PORTSEL_CLK_EN | AHB_CLK_EN)

#define HCCA_SIZE sizeof(HCCA)
#define ED_SIZE sizeof(HCED)
#define TD_SIZE sizeof(HCTD)

#define TOTAL_SIZE (HCCA_SIZE + (MAX_ENDPOINT*ED_SIZE) + (MAX_TD*TD_SIZE))

static volatile uint8_t usb_buf[TOTAL_SIZE] __attribute((section("AHBSRAM1"),aligned(256)));  //256 bytes aligned!

USBHALHost * USBHALHost::instHost;

USBHALHost::USBHALHost() {
    instHost = this;
    memInit();
    memset((void*)usb_hcca, 0, HCCA_SIZE);
    for (int i = 0; i < MAX_ENDPOINT; i++) {
        edBufAlloc[i] = false;
    }
    for (int i = 0; i < MAX_TD; i++) {
        tdBufAlloc[i] = false;
    }
}

void USBHALHost::init() {
    NVIC_DisableIRQ(USB_IRQn);

    //Cut power
    LPC_SC->PCONP &= ~(1UL<<31);
    wait_ms(100);

    // turn on power for USB
    LPC_SC->PCONP       |= (1UL<<31);

    // Enable USB host clock, port selection and AHB clock
    LPC_USB->USBClkCtrl |= CLOCK_MASK;

    // Wait for clocks to become available
    while ((LPC_USB->USBClkSt & CLOCK_MASK) != CLOCK_MASK);

    // it seems the bits[0:1] mean the following
    // 0: U1=device, U2=host
    // 1: U1=host, U2=host
    // 2: reserved
    // 3: U1=host, U2=device
    // NB: this register is only available if OTG clock (aka "port select") is enabled!!
    // since we don't care about port 2, set just bit 0 to 1 (U1=host)
    LPC_USB->OTGStCtrl |= 1;

    // now that we've configured the ports, we can turn off the portsel clock
    LPC_USB->USBClkCtrl &= ~PORTSEL_CLK_EN;

    // configure USB D+/D- pins
    // P0[29] = USB_D+, 01
    // P0[30] = USB_D-, 01
    LPC_PINCON->PINSEL1 &= ~((3<<26) | (3<<28));
    LPC_PINCON->PINSEL1 |=  ((1<<26) | (1<<28));

    LPC_USB->HcControl       = 0; // HARDWARE RESET
    LPC_USB->HcControlHeadED = 0; // Initialize Control list head to Zero
    LPC_USB->HcBulkHeadED    = 0; // Initialize Bulk list head to Zero

    // Wait 100 ms before apply reset
    wait_ms(100);

    // software reset
    LPC_USB->HcCommandStatus = OR_CMD_STATUS_HCR;

    // Write Fm Interval and Largest Data Packet Counter
    LPC_USB->HcFmInterval    = DEFAULT_FMINTERVAL;
    LPC_USB->HcPeriodicStart = FI * 90 / 100;

    // Put HC in operational state
    LPC_USB->HcControl  = (LPC_USB->HcControl & (~OR_CONTROL_HCFS)) | OR_CONTROL_HC_OPER;
    // Set Global Power
    LPC_USB->HcRhStatus = OR_RH_STATUS_LPSC;

    LPC_USB->HcHCCA = (uint32_t)(usb_hcca);

    // Clear Interrrupt Status
    LPC_USB->HcInterruptStatus |= LPC_USB->HcInterruptStatus;

    LPC_USB->HcInterruptEnable  = OR_INTR_ENABLE_MIE | OR_INTR_ENABLE_WDH | OR_INTR_ENABLE_RHSC;

    // Enable the USB Interrupt
    NVIC_SetVector(USB_IRQn, (uint32_t)(_usbisr));
    LPC_USB->HcRhPortStatus1 = OR_RH_PORT_CSC;
    LPC_USB->HcRhPortStatus1 = OR_RH_PORT_PRSC;

    NVIC_EnableIRQ(USB_IRQn);

    // Check for any connected devices
    if (LPC_USB->HcRhPortStatus1 & OR_RH_PORT_CCS) {
        //Device connected
        wait_ms(150);
        USB_DBG("Device connected (%08x)\n\r", LPC_USB->HcRhPortStatus1);
        deviceConnected(0, 1, LPC_USB->HcRhPortStatus1 & OR_RH_PORT_LSDA);
    }
}

uint32_t USBHALHost::controlHeadED() {
    return LPC_USB->HcControlHeadED;
}

uint32_t USBHALHost::bulkHeadED() {
    return LPC_USB->HcBulkHeadED;
}

uint32_t USBHALHost::interruptHeadED() {
    return usb_hcca->IntTable[0];
}

void USBHALHost::updateBulkHeadED(uint32_t addr) {
    LPC_USB->HcBulkHeadED = addr;
}


void USBHALHost::updateControlHeadED(uint32_t addr) {
    LPC_USB->HcControlHeadED = addr;
}

void USBHALHost::updateInterruptHeadED(uint32_t addr) {
    usb_hcca->IntTable[0] = addr;
}


void USBHALHost::enableList(ENDPOINT_TYPE type) {
    switch(type) {
        case CONTROL_ENDPOINT:
            LPC_USB->HcCommandStatus = OR_CMD_STATUS_CLF;
            LPC_USB->HcControl |= OR_CONTROL_CLE;
            break;
        case ISOCHRONOUS_ENDPOINT:
            break;
        case BULK_ENDPOINT:
            LPC_USB->HcCommandStatus = OR_CMD_STATUS_BLF;
            LPC_USB->HcControl |= OR_CONTROL_BLE;
            break;
        case INTERRUPT_ENDPOINT:
            LPC_USB->HcControl |= OR_CONTROL_PLE;
            break;
    }
}


bool USBHALHost::disableList(ENDPOINT_TYPE type) {
    switch(type) {
        case CONTROL_ENDPOINT:
            if(LPC_USB->HcControl & OR_CONTROL_CLE) {
                LPC_USB->HcControl &= ~OR_CONTROL_CLE;
                return true;
            }
            return false;
        case ISOCHRONOUS_ENDPOINT:
            return false;
        case BULK_ENDPOINT:
            if(LPC_USB->HcControl & OR_CONTROL_BLE){
                LPC_USB->HcControl &= ~OR_CONTROL_BLE;
                return true;
            }
            return false;
        case INTERRUPT_ENDPOINT:
            if(LPC_USB->HcControl & OR_CONTROL_PLE) {
                LPC_USB->HcControl &= ~OR_CONTROL_PLE;
                return true;
            }
            return false;
    }
    return false;
}


void USBHALHost::memInit() {
    usb_hcca = (volatile HCCA *)usb_buf;
    usb_edBuf = usb_buf + HCCA_SIZE;
    usb_tdBuf = usb_buf + HCCA_SIZE + (MAX_ENDPOINT*ED_SIZE);
}

volatile uint8_t * USBHALHost::getED() {
    for (int i = 0; i < MAX_ENDPOINT; i++) {
        if ( !edBufAlloc[i] ) {
            edBufAlloc[i] = true;
            return (volatile uint8_t *)(usb_edBuf + i*ED_SIZE);
        }
    }
    perror("Could not allocate ED\r\n");
    return NULL; //Could not alloc ED
}

volatile uint8_t * USBHALHost::getTD() {
    int i;
    for (i = 0; i < MAX_TD; i++) {
        if ( !tdBufAlloc[i] ) {
            tdBufAlloc[i] = true;
            return (volatile uint8_t *)(usb_tdBuf + i*TD_SIZE);
        }
    }
    perror("Could not allocate TD\r\n");
    return NULL; //Could not alloc TD
}


void USBHALHost::freeED(volatile uint8_t * ed) {
    int i;
    i = (ed - usb_edBuf) / ED_SIZE;
    edBufAlloc[i] = false;
}

void USBHALHost::freeTD(volatile uint8_t * td) {
    int i;
    i = (td - usb_tdBuf) / TD_SIZE;
    tdBufAlloc[i] = false;
}


void USBHALHost::resetRootHub() {
    // Initiate port reset
    LPC_USB->HcRhPortStatus1 = OR_RH_PORT_PRS;

    while (LPC_USB->HcRhPortStatus1 & OR_RH_PORT_PRS);

    // ...and clear port reset signal
    LPC_USB->HcRhPortStatus1 = OR_RH_PORT_PRSC;
}


void USBHALHost::_usbisr(void) {
    if (instHost) {
        instHost->UsbIrqhandler();
    }
}

void USBHALHost::UsbIrqhandler() {
    if( LPC_USB->HcInterruptStatus & LPC_USB->HcInterruptEnable ) //Is there something to actually process?
    {

        uint32_t int_status = LPC_USB->HcInterruptStatus & LPC_USB->HcInterruptEnable;

        // Root hub status change interrupt
        if (int_status & OR_INTR_STATUS_RHSC) {
            if (LPC_USB->HcRhPortStatus1 & OR_RH_PORT_CSC) {
                if (LPC_USB->HcRhStatus & OR_RH_STATUS_DRWE) {
                    // When DRWE is on, Connect Status Change
                    // means a remote wakeup event.
                } else {

                    //Root device connected
                    if (LPC_USB->HcRhPortStatus1 & OR_RH_PORT_CCS) {

                        // wait 150ms to avoid bounce
                        wait_ms(150);

                        //Hub 0 (root hub), Port 1 (count starts at 1), Low or High speed
                        deviceConnected(0, 1, LPC_USB->HcRhPortStatus1 & OR_RH_PORT_LSDA);
                    }

                    //Root device disconnected
                    else {

                        if (!(int_status & OR_INTR_STATUS_WDH)) {
                            usb_hcca->DoneHead = 0;
                        }

                        // wait 200ms to avoid bounce
                        wait_ms(200);

                        deviceDisconnected(0, 1, NULL, usb_hcca->DoneHead & 0xFFFFFFFE);

                        if (int_status & OR_INTR_STATUS_WDH) {
                            usb_hcca->DoneHead = 0;
                            LPC_USB->HcInterruptStatus = OR_INTR_STATUS_WDH;
                        }
                    }
                }
                LPC_USB->HcRhPortStatus1 = OR_RH_PORT_CSC;
            }
            if (LPC_USB->HcRhPortStatus1 & OR_RH_PORT_PRSC) {
                LPC_USB->HcRhPortStatus1 = OR_RH_PORT_PRSC;
            }
            LPC_USB->HcInterruptStatus = OR_INTR_STATUS_RHSC;
        }

        // Writeback Done Head interrupt
        if (int_status & OR_INTR_STATUS_WDH) {
            transferCompleted(usb_hcca->DoneHead & 0xFFFFFFFE);
            LPC_USB->HcInterruptStatus = OR_INTR_STATUS_WDH;
        }
    }
}
#endif
