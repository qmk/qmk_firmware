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

#if defined(TARGET_STM32F4)

#include "USBHAL.h"
#include "USBRegs_STM32.h"
#include "pinmap.h"

USBHAL * USBHAL::instance;

static volatile int epComplete = 0;

static uint32_t bufferEnd = 0;
static const uint32_t rxFifoSize = 512;
static uint32_t rxFifoCount = 0;

static uint32_t setupBuffer[MAX_PACKET_SIZE_EP0 >> 2];

uint32_t USBHAL::endpointReadcore(uint8_t endpoint, uint8_t *buffer) {
    return 0;
}

USBHAL::USBHAL(void) {
    NVIC_DisableIRQ(OTG_FS_IRQn);
    epCallback[0] = &USBHAL::EP1_OUT_callback;
    epCallback[1] = &USBHAL::EP1_IN_callback;
    epCallback[2] = &USBHAL::EP2_OUT_callback;
    epCallback[3] = &USBHAL::EP2_IN_callback;
    epCallback[4] = &USBHAL::EP3_OUT_callback;
    epCallback[5] = &USBHAL::EP3_IN_callback;

    // Enable power and clocking
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

#if defined(TARGET_STM32F407VG) || defined(TARGET_STM32F401RE) || defined(TARGET_STM32F411RE)
    pin_function(PA_8, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF10_OTG_FS));
    pin_function(PA_9, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLDOWN, GPIO_AF10_OTG_FS));
    pin_function(PA_10, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_PULLUP, GPIO_AF10_OTG_FS));
    pin_function(PA_11, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF10_OTG_FS));
    pin_function(PA_12, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF10_OTG_FS));
#else
    pin_function(PA_8, STM_PIN_DATA(2, 10));
    pin_function(PA_9, STM_PIN_DATA(0, 0));
    pin_function(PA_10, STM_PIN_DATA(2, 10));
    pin_function(PA_11, STM_PIN_DATA(2, 10));
    pin_function(PA_12, STM_PIN_DATA(2, 10));

    // Set ID pin to open drain with pull-up resistor
    pin_mode(PA_10, OpenDrain);
    GPIOA->PUPDR &= ~(0x3 << 20);
    GPIOA->PUPDR |= 1 << 20;

    // Set VBUS pin to open drain
    pin_mode(PA_9, OpenDrain);
#endif

    RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;

    // Enable interrupts
    OTG_FS->GREGS.GAHBCFG |= (1 << 0);

    // Turnaround time to maximum value - too small causes packet loss
    OTG_FS->GREGS.GUSBCFG |= (0xF << 10);

    // Unmask global interrupts
    OTG_FS->GREGS.GINTMSK |= (1 << 3) | // SOF
                             (1 << 4) | // RX FIFO not empty
                             (1 << 12); // USB reset

    OTG_FS->DREGS.DCFG |= (0x3 << 0) | // Full speed
                          (1 << 2); // Non-zero-length status OUT handshake

    OTG_FS->GREGS.GCCFG |= (1 << 19) | // Enable VBUS sensing
                           (1 << 16); // Power Up

    instance = this;
    NVIC_SetVector(OTG_FS_IRQn, (uint32_t)&_usbisr);
    NVIC_SetPriority(OTG_FS_IRQn, 1);
}

USBHAL::~USBHAL(void) {
}

void USBHAL::connect(void) {
    NVIC_EnableIRQ(OTG_FS_IRQn);
}

void USBHAL::disconnect(void) {
    NVIC_DisableIRQ(OTG_FS_IRQn);
}

void USBHAL::configureDevice(void) {
    // Not needed
}

void USBHAL::unconfigureDevice(void) {
    // Not needed
}

void USBHAL::setAddress(uint8_t address) {
    OTG_FS->DREGS.DCFG |= (address << 4);
    EP0write(0, 0);
}

bool USBHAL::realiseEndpoint(uint8_t endpoint, uint32_t maxPacket,
                             uint32_t flags) {
    uint32_t epIndex = endpoint >> 1;

    uint32_t type;
    switch (endpoint) {
        case EP0IN:
        case EP0OUT:
            type = 0;
            break;
        case EPISO_IN:
        case EPISO_OUT:
            type = 1;
        case EPBULK_IN:
        case EPBULK_OUT:
            type = 2;
            break;
        case EPINT_IN:
        case EPINT_OUT:
            type = 3;
            break;
    }

    // Generic in or out EP controls
    uint32_t control = (maxPacket << 0) | // Packet size
                       (1 << 15) | // Active endpoint
                       (type << 18); // Endpoint type

    if (endpoint & 0x1) { // In Endpoint
        // Set up the Tx FIFO
        if (endpoint == EP0IN) {
            OTG_FS->GREGS.DIEPTXF0_HNPTXFSIZ = ((maxPacket >> 2) << 16) |
                                               (bufferEnd << 0);
        }
        else {
            OTG_FS->GREGS.DIEPTXF[epIndex - 1] = ((maxPacket >> 2) << 16) |
                                                 (bufferEnd << 0);
        }
        bufferEnd += maxPacket >> 2;

        // Set the In EP specific control settings
        if (endpoint != EP0IN) {
            control |= (1 << 28); // SD0PID
        }

        control |= (epIndex << 22) | // TxFIFO index
                   (1 << 27); // SNAK
        OTG_FS->INEP_REGS[epIndex].DIEPCTL = control;

        // Unmask the interrupt
        OTG_FS->DREGS.DAINTMSK |= (1 << epIndex);
    }
    else { // Out endpoint
        // Set the out EP specific control settings
        control |= (1 << 26); // CNAK
        OTG_FS->OUTEP_REGS[epIndex].DOEPCTL = control;

        // Unmask the interrupt
        OTG_FS->DREGS.DAINTMSK |= (1 << (epIndex + 16));
    }
    return true;
}

// read setup packet
void USBHAL::EP0setup(uint8_t *buffer) {
    memcpy(buffer, setupBuffer, MAX_PACKET_SIZE_EP0);
}

void USBHAL::EP0readStage(void) {
}

void USBHAL::EP0read(void) {
}

uint32_t USBHAL::EP0getReadResult(uint8_t *buffer) {
    uint32_t* buffer32 = (uint32_t *) buffer;
    uint32_t length = rxFifoCount;
    for (uint32_t i = 0; i < length; i += 4) {
        buffer32[i >> 2] = OTG_FS->FIFO[0][0];
    }

    rxFifoCount = 0;
    return length;
}

void USBHAL::EP0write(uint8_t *buffer, uint32_t size) {
    endpointWrite(0, buffer, size);
}

void USBHAL::EP0getWriteResult(void) {
}

void USBHAL::EP0stall(void) {
    // If we stall the out endpoint here then we have problems transferring
    // and setup requests after the (stalled) get device qualifier requests.
    // TODO: Find out if this is correct behavior, or whether we are doing
    // something else wrong
    stallEndpoint(EP0IN);
//    stallEndpoint(EP0OUT);
}

EP_STATUS USBHAL::endpointRead(uint8_t endpoint, uint32_t maximumSize) {
    uint32_t epIndex = endpoint >> 1;
    uint32_t size = (1 << 19) | // 1 packet
                    (maximumSize << 0); // Packet size
//    if (endpoint == EP0OUT) {
        size |= (1 << 29); // 1 setup packet
//    }
    OTG_FS->OUTEP_REGS[epIndex].DOEPTSIZ = size;
    OTG_FS->OUTEP_REGS[epIndex].DOEPCTL |= (1 << 31) | // Enable endpoint
                                           (1 << 26); // Clear NAK

    epComplete &= ~(1 << endpoint);
    return EP_PENDING;
}

EP_STATUS USBHAL::endpointReadResult(uint8_t endpoint, uint8_t * buffer, uint32_t *bytesRead) {
    if (!(epComplete & (1 << endpoint))) {
        return EP_PENDING;
    }

    uint32_t* buffer32 = (uint32_t *) buffer;
    uint32_t length = rxFifoCount;
    for (uint32_t i = 0; i < length; i += 4) {
        buffer32[i >> 2] = OTG_FS->FIFO[endpoint >> 1][0];
    }
    rxFifoCount = 0;
    *bytesRead = length;
    return EP_COMPLETED;
}

EP_STATUS USBHAL::endpointWrite(uint8_t endpoint, uint8_t *data, uint32_t size) {
    uint32_t epIndex = endpoint >> 1;
    OTG_FS->INEP_REGS[epIndex].DIEPTSIZ = (1 << 19) | // 1 packet
                                          (size << 0); // Size of packet
    OTG_FS->INEP_REGS[epIndex].DIEPCTL |= (1 << 31) | // Enable endpoint
                                          (1 << 26); // CNAK
    OTG_FS->DREGS.DIEPEMPMSK = (1 << epIndex);

    while ((OTG_FS->INEP_REGS[epIndex].DTXFSTS & 0XFFFF) < ((size + 3) >> 2));

    for (uint32_t i=0; i<(size + 3) >> 2; i++, data+=4) {
        OTG_FS->FIFO[epIndex][0] = *(uint32_t *)data;
    }

    epComplete &= ~(1 << endpoint);

    return EP_PENDING;
}

EP_STATUS USBHAL::endpointWriteResult(uint8_t endpoint) {
    if (epComplete & (1 << endpoint)) {
        epComplete &= ~(1 << endpoint);
        return EP_COMPLETED;
    }

    return EP_PENDING;
}

void USBHAL::stallEndpoint(uint8_t endpoint) {
    if (endpoint & 0x1) { // In EP
        OTG_FS->INEP_REGS[endpoint >> 1].DIEPCTL |= (1 << 30) | // Disable
                                                    (1 << 21); // Stall
    }
    else {  // Out EP
        OTG_FS->DREGS.DCTL |= (1 << 9); // Set global out NAK
        OTG_FS->OUTEP_REGS[endpoint >> 1].DOEPCTL |= (1 << 30) | // Disable
                                                     (1 << 21); // Stall
    }
}

void USBHAL::unstallEndpoint(uint8_t endpoint) {

}

bool USBHAL::getEndpointStallState(uint8_t endpoint) {
    return false;
}

void USBHAL::remoteWakeup(void) {
}


void USBHAL::_usbisr(void) {
    instance->usbisr();
}


void USBHAL::usbisr(void) {
    if (OTG_FS->GREGS.GINTSTS & (1 << 12)) { // USB Reset
        // Set SNAK bits
        OTG_FS->OUTEP_REGS[0].DOEPCTL |= (1 << 27);
        OTG_FS->OUTEP_REGS[1].DOEPCTL |= (1 << 27);
        OTG_FS->OUTEP_REGS[2].DOEPCTL |= (1 << 27);
        OTG_FS->OUTEP_REGS[3].DOEPCTL |= (1 << 27);

        OTG_FS->DREGS.DIEPMSK = (1 << 0);

        bufferEnd = 0;

        // Set the receive FIFO size
        OTG_FS->GREGS.GRXFSIZ = rxFifoSize >> 2;
        bufferEnd += rxFifoSize >> 2;

        // Create the endpoints, and wait for setup packets on out EP0
        realiseEndpoint(EP0IN, MAX_PACKET_SIZE_EP0, 0);
        realiseEndpoint(EP0OUT, MAX_PACKET_SIZE_EP0, 0);
        endpointRead(EP0OUT, MAX_PACKET_SIZE_EP0);

        OTG_FS->GREGS.GINTSTS = (1 << 12);
    }

    if (OTG_FS->GREGS.GINTSTS & (1 << 4)) { // RX FIFO not empty
        uint32_t status = OTG_FS->GREGS.GRXSTSP;

        uint32_t endpoint = (status & 0xF) << 1;
        uint32_t length = (status >> 4) & 0x7FF;
        uint32_t type = (status >> 17) & 0xF;

        rxFifoCount = length;

        if (type == 0x6) {
            // Setup packet
            for (uint32_t i=0; i<length; i+=4) {
                setupBuffer[i >> 2] = OTG_FS->FIFO[0][i >> 2];
            }
            rxFifoCount = 0;
        }

        if (type == 0x4) {
            // Setup complete
            EP0setupCallback();
            endpointRead(EP0OUT, MAX_PACKET_SIZE_EP0);
        }

        if (type == 0x2) {
            // Out packet
            if (endpoint == EP0OUT) {
                EP0out();
            }
            else {
                epComplete |= (1 << endpoint);
                if ((instance->*(epCallback[endpoint - 2]))()) {
                    epComplete &= (1 << endpoint);
                }
            }
        }

        for (uint32_t i=0; i<rxFifoCount; i+=4) {
            (void) OTG_FS->FIFO[0][0];
        }
        OTG_FS->GREGS.GINTSTS = (1 << 4);
    }

    if (OTG_FS->GREGS.GINTSTS & (1 << 18)) { // In endpoint interrupt
        // Loop through the in endpoints
        for (uint32_t i=0; i<4; i++) {
            if (OTG_FS->DREGS.DAINT & (1 << i)) { // Interrupt is on endpoint

                if (OTG_FS->INEP_REGS[i].DIEPINT & (1 << 7)) {// Tx FIFO empty
                    // If the Tx FIFO is empty on EP0 we need to send a further
                    // packet, so call EP0in()
                    if (i == 0) {
                        EP0in();
                    }
                    // Clear the interrupt
                    OTG_FS->INEP_REGS[i].DIEPINT = (1 << 7);
                    // Stop firing Tx empty interrupts
                    // Will get turned on again if another write is called
                    OTG_FS->DREGS.DIEPEMPMSK &= ~(1 << i);
                }

                // If the transfer is complete
                if (OTG_FS->INEP_REGS[i].DIEPINT & (1 << 0)) { // Tx Complete
                    epComplete |= (1 << (1 + (i << 1)));
                    OTG_FS->INEP_REGS[i].DIEPINT = (1 << 0);
                }
            }
        }
        OTG_FS->GREGS.GINTSTS = (1 << 18);
    }

    if (OTG_FS->GREGS.GINTSTS & (1 << 3)) { // Start of frame
        SOF((OTG_FS->GREGS.GRXSTSR >> 17) & 0xF);
        OTG_FS->GREGS.GINTSTS = (1 << 3);
    }
}


#endif
