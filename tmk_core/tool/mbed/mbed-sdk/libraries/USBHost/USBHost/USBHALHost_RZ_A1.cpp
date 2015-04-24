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

#if defined(TARGET_RZ_A1H)

#include "mbed.h"
#include "USBHALHost.h"
#include "dbg.h"

#include "ohci_wrapp_RZ_A1.h"


#define HCCA_SIZE sizeof(HCCA)
#define ED_SIZE sizeof(HCED)
#define TD_SIZE sizeof(HCTD)

#define TOTAL_SIZE (HCCA_SIZE + (MAX_ENDPOINT*ED_SIZE) + (MAX_TD*TD_SIZE))
#define ALIGNE_MSK (0x0000000F)

static volatile uint8_t usb_buf[TOTAL_SIZE + ALIGNE_MSK];  //16 bytes aligned!

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
    ohciwrapp_init(&_usbisr);

    ohciwrapp_reg_w(OHCI_REG_CONTROL, 1);       // HARDWARE RESET
    ohciwrapp_reg_w(OHCI_REG_CONTROLHEADED, 0); // Initialize Control list head to Zero
    ohciwrapp_reg_w(OHCI_REG_BULKHEADED, 0);    // Initialize Bulk list head to Zero

    // Wait 100 ms before apply reset
    wait_ms(100);

    // software reset
    ohciwrapp_reg_w(OHCI_REG_COMMANDSTATUS, OR_CMD_STATUS_HCR);

    // Write Fm Interval and Largest Data Packet Counter
    ohciwrapp_reg_w(OHCI_REG_FMINTERVAL, DEFAULT_FMINTERVAL);
    ohciwrapp_reg_w(OHCI_REG_PERIODICSTART,  FI * 90 / 100);

    // Put HC in operational state
    ohciwrapp_reg_w(OHCI_REG_CONTROL, (ohciwrapp_reg_r(OHCI_REG_CONTROL) & (~OR_CONTROL_HCFS)) | OR_CONTROL_HC_OPER);
    // Set Global Power
    ohciwrapp_reg_w(OHCI_REG_RHSTATUS, OR_RH_STATUS_LPSC);

    ohciwrapp_reg_w(OHCI_REG_HCCA, (uint32_t)(usb_hcca));

    // Clear Interrrupt Status
    ohciwrapp_reg_w(OHCI_REG_INTERRUPTSTATUS, ohciwrapp_reg_r(OHCI_REG_INTERRUPTSTATUS));

    ohciwrapp_reg_w(OHCI_REG_INTERRUPTENABLE, OR_INTR_ENABLE_MIE | OR_INTR_ENABLE_WDH | OR_INTR_ENABLE_RHSC);

    // Enable the USB Interrupt
    ohciwrapp_reg_w(OHCI_REG_RHPORTSTATUS1, OR_RH_PORT_CSC);
    ohciwrapp_reg_w(OHCI_REG_RHPORTSTATUS1, OR_RH_PORT_PRSC);

    // Check for any connected devices
    if (ohciwrapp_reg_r(OHCI_REG_RHPORTSTATUS1) & OR_RH_PORT_CCS) {
        //Device connected
        wait_ms(150);
        USB_DBG("Device connected (%08x)\n\r", ohciwrapp_reg_r(OHCI_REG_RHPORTSTATUS1));
        deviceConnected(0, 1, ohciwrapp_reg_r(OHCI_REG_RHPORTSTATUS1) & OR_RH_PORT_LSDA);
    }
}

uint32_t USBHALHost::controlHeadED() {
    return ohciwrapp_reg_r(OHCI_REG_CONTROLHEADED);
}

uint32_t USBHALHost::bulkHeadED() {
    return ohciwrapp_reg_r(OHCI_REG_BULKHEADED);
}

uint32_t USBHALHost::interruptHeadED() {
    return usb_hcca->IntTable[0];
}

void USBHALHost::updateBulkHeadED(uint32_t addr) {
    ohciwrapp_reg_w(OHCI_REG_BULKHEADED, addr);
}


void USBHALHost::updateControlHeadED(uint32_t addr) {
    ohciwrapp_reg_w(OHCI_REG_CONTROLHEADED, addr);
}

void USBHALHost::updateInterruptHeadED(uint32_t addr) {
    usb_hcca->IntTable[0] = addr;
}


void USBHALHost::enableList(ENDPOINT_TYPE type) {
    uint32_t wk_data;

    switch(type) {
        case CONTROL_ENDPOINT:
            ohciwrapp_reg_w(OHCI_REG_COMMANDSTATUS, OR_CMD_STATUS_CLF);
            wk_data = (ohciwrapp_reg_r(OHCI_REG_CONTROL) | OR_CONTROL_CLE);
            ohciwrapp_reg_w(OHCI_REG_CONTROL, wk_data);
            break;
        case ISOCHRONOUS_ENDPOINT:
            break;
        case BULK_ENDPOINT:
            ohciwrapp_reg_w(OHCI_REG_COMMANDSTATUS, OR_CMD_STATUS_BLF);
            wk_data = (ohciwrapp_reg_r(OHCI_REG_CONTROL) | OR_CONTROL_BLE);
            ohciwrapp_reg_w(OHCI_REG_CONTROL, wk_data);
            break;
        case INTERRUPT_ENDPOINT:
            wk_data = (ohciwrapp_reg_r(OHCI_REG_CONTROL) | OR_CONTROL_PLE);
            ohciwrapp_reg_w(OHCI_REG_CONTROL, wk_data);
            break;
    }
}


bool USBHALHost::disableList(ENDPOINT_TYPE type) {
    uint32_t wk_data;

    switch(type) {
        case CONTROL_ENDPOINT:
            wk_data = ohciwrapp_reg_r(OHCI_REG_CONTROL);
            if(wk_data & OR_CONTROL_CLE) {
                wk_data &= ~OR_CONTROL_CLE;
                ohciwrapp_reg_w(OHCI_REG_CONTROL, wk_data);
                return true;
            }
            return false;
        case ISOCHRONOUS_ENDPOINT:
            return false;
        case BULK_ENDPOINT:
            wk_data = ohciwrapp_reg_r(OHCI_REG_CONTROL);
            if(wk_data & OR_CONTROL_BLE) {
                wk_data &= ~OR_CONTROL_BLE;
                ohciwrapp_reg_w(OHCI_REG_CONTROL, wk_data);
                return true;
            }
            return false;
        case INTERRUPT_ENDPOINT:
            wk_data = ohciwrapp_reg_r(OHCI_REG_CONTROL);
            if(wk_data & OR_CONTROL_PLE) {
                wk_data &= ~OR_CONTROL_PLE;
                ohciwrapp_reg_w(OHCI_REG_CONTROL, wk_data);
                return true;
            }
            return false;
    }
    return false;
}


void USBHALHost::memInit() {
    volatile uint8_t *p_wk_buf = (uint8_t *)(((uint32_t)usb_buf + ALIGNE_MSK) & ~ALIGNE_MSK);

    usb_hcca = (volatile HCCA *)p_wk_buf;
    usb_edBuf = (volatile uint8_t *)(p_wk_buf + HCCA_SIZE);
    usb_tdBuf = (volatile uint8_t *)(p_wk_buf + HCCA_SIZE + (MAX_ENDPOINT*ED_SIZE));
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
    ohciwrapp_reg_w(OHCI_REG_RHPORTSTATUS1, OR_RH_PORT_PRS);

    while (ohciwrapp_reg_r(OHCI_REG_RHPORTSTATUS1) & OR_RH_PORT_PRS);

    // ...and clear port reset signal
    ohciwrapp_reg_w(OHCI_REG_RHPORTSTATUS1, OR_RH_PORT_PRSC);
}


void USBHALHost::_usbisr(void) {
    if (instHost) {
        instHost->UsbIrqhandler();
    }
}

void USBHALHost::UsbIrqhandler() {
    uint32_t int_status = ohciwrapp_reg_r(OHCI_REG_INTERRUPTSTATUS) & ohciwrapp_reg_r(OHCI_REG_INTERRUPTENABLE);
    uint32_t data;

    if (int_status != 0) { //Is there something to actually process?
        // Root hub status change interrupt
        if (int_status & OR_INTR_STATUS_RHSC) {
            if (ohciwrapp_reg_r(OHCI_REG_RHPORTSTATUS1) & OR_RH_PORT_CSC) {
                if (ohciwrapp_reg_r(OHCI_REG_RHSTATUS) & OR_RH_STATUS_DRWE) {
                    // When DRWE is on, Connect Status Change
                    // means a remote wakeup event.
                } else {

                    //Root device connected
                    if (ohciwrapp_reg_r(OHCI_REG_RHPORTSTATUS1) & OR_RH_PORT_CCS) {

                        // wait 150ms to avoid bounce
                        wait_ms(150);

                        //Hub 0 (root hub), Port 1 (count starts at 1), Low or High speed
                        data = ohciwrapp_reg_r(OHCI_REG_RHPORTSTATUS1) & OR_RH_PORT_LSDA;
                        deviceConnected(0, 1, data);
                    }

                    //Root device disconnected
                    else {

                        if (!(int_status & OR_INTR_STATUS_WDH)) {
                            usb_hcca->DoneHead = 0;
                        }

                        deviceDisconnected(0, 1, NULL, usb_hcca->DoneHead & 0xFFFFFFFE);

                        if (int_status & OR_INTR_STATUS_WDH) {
                            usb_hcca->DoneHead = 0;
                            ohciwrapp_reg_w(OHCI_REG_INTERRUPTSTATUS, OR_INTR_STATUS_WDH);
                        }
                    }
                }
                ohciwrapp_reg_w(OHCI_REG_RHPORTSTATUS1, OR_RH_PORT_CSC);
            }
            if (ohciwrapp_reg_r(OHCI_REG_RHPORTSTATUS1) & OR_RH_PORT_PRSC) {
                ohciwrapp_reg_w(OHCI_REG_RHPORTSTATUS1, OR_RH_PORT_PRSC);
            }
            ohciwrapp_reg_w(OHCI_REG_INTERRUPTSTATUS, OR_INTR_STATUS_RHSC);
        }

        // Writeback Done Head interrupt
        if (int_status & OR_INTR_STATUS_WDH) {
            transferCompleted(usb_hcca->DoneHead & 0xFFFFFFFE);
            ohciwrapp_reg_w(OHCI_REG_INTERRUPTSTATUS, OR_INTR_STATUS_WDH);
        }
    }
}
#endif
