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

#if defined(TARGET_LPC4088) || defined(TARGET_LPC4088_DM)

#include "USBHAL.h"


// Get endpoint direction
#define IN_EP(endpoint)     ((endpoint) & 1U ? true : false)
#define OUT_EP(endpoint)    ((endpoint) & 1U ? false : true)

// Convert physical endpoint number to register bit
#define EP(endpoint) (1UL<<endpoint)

// Power Control for Peripherals register
#define PCUSB      (1UL<<31)

// USB Clock Control register
#define DEV_CLK_EN  (1UL<<1)
#define PORT_CLK_EN (1UL<<3)
#define AHB_CLK_EN  (1UL<<4)

// USB Clock Status register
#define DEV_CLK_ON (1UL<<1)
#define AHB_CLK_ON (1UL<<4)

// USB Device Interupt registers
#define FRAME      (1UL<<0)
#define EP_FAST    (1UL<<1)
#define EP_SLOW    (1UL<<2)
#define DEV_STAT   (1UL<<3)
#define CCEMPTY    (1UL<<4)
#define CDFULL     (1UL<<5)
#define RxENDPKT   (1UL<<6)
#define TxENDPKT   (1UL<<7)
#define EP_RLZED   (1UL<<8)
#define ERR_INT    (1UL<<9)

// USB Control register
#define RD_EN (1<<0)
#define WR_EN (1<<1)
#define LOG_ENDPOINT(endpoint) ((endpoint>>1)<<2)

// USB Receive Packet Length register
#define DV      (1UL<<10)
#define PKT_RDY (1UL<<11)
#define PKT_LNGTH_MASK (0x3ff)

// Serial Interface Engine (SIE)
#define SIE_WRITE   (0x01)
#define SIE_READ    (0x02)
#define SIE_COMMAND (0x05)
#define SIE_CMD_CODE(phase, data) ((phase<<8)|(data<<16))

// SIE Command codes
#define SIE_CMD_SET_ADDRESS        (0xD0)
#define SIE_CMD_CONFIGURE_DEVICE   (0xD8)
#define SIE_CMD_SET_MODE           (0xF3)
#define SIE_CMD_READ_FRAME_NUMBER  (0xF5)
#define SIE_CMD_READ_TEST_REGISTER (0xFD)
#define SIE_CMD_SET_DEVICE_STATUS  (0xFE)
#define SIE_CMD_GET_DEVICE_STATUS  (0xFE)
#define SIE_CMD_GET_ERROR_CODE     (0xFF)
#define SIE_CMD_READ_ERROR_STATUS  (0xFB)

#define SIE_CMD_SELECT_ENDPOINT(endpoint)                 (0x00+endpoint)
#define SIE_CMD_SELECT_ENDPOINT_CLEAR_INTERRUPT(endpoint) (0x40+endpoint)
#define SIE_CMD_SET_ENDPOINT_STATUS(endpoint)             (0x40+endpoint)

#define SIE_CMD_CLEAR_BUFFER    (0xF2)
#define SIE_CMD_VALIDATE_BUFFER (0xFA)

// SIE Device Status register
#define SIE_DS_CON    (1<<0)
#define SIE_DS_CON_CH (1<<1)
#define SIE_DS_SUS    (1<<2)
#define SIE_DS_SUS_CH (1<<3)
#define SIE_DS_RST    (1<<4)

// SIE Device Set Address register
#define SIE_DSA_DEV_EN  (1<<7)

// SIE Configue Device register
#define SIE_CONF_DEVICE (1<<0)

// Select Endpoint register
#define SIE_SE_FE       (1<<0)
#define SIE_SE_ST       (1<<1)
#define SIE_SE_STP      (1<<2)
#define SIE_SE_PO       (1<<3)
#define SIE_SE_EPN      (1<<4)
#define SIE_SE_B_1_FULL (1<<5)
#define SIE_SE_B_2_FULL (1<<6)

// Set Endpoint Status command
#define SIE_SES_ST      (1<<0)
#define SIE_SES_DA      (1<<5)
#define SIE_SES_RF_MO   (1<<6)
#define SIE_SES_CND_ST  (1<<7)


USBHAL * USBHAL::instance;

static volatile int epComplete;
static uint32_t endpointStallState;

static void SIECommand(uint32_t command) {
    // The command phase of a SIE transaction
    LPC_USB->DevIntClr = CCEMPTY;
    LPC_USB->CmdCode = SIE_CMD_CODE(SIE_COMMAND, command);
    while (!(LPC_USB->DevIntSt & CCEMPTY));
}

static void SIEWriteData(uint8_t data) {
    // The data write phase of a SIE transaction
    LPC_USB->DevIntClr = CCEMPTY;
    LPC_USB->CmdCode = SIE_CMD_CODE(SIE_WRITE, data);
    while (!(LPC_USB->DevIntSt & CCEMPTY));
}

static uint8_t SIEReadData(uint32_t command) {
    // The data read phase of a SIE transaction
    LPC_USB->DevIntClr = CDFULL;
    LPC_USB->CmdCode = SIE_CMD_CODE(SIE_READ, command);
    while (!(LPC_USB->DevIntSt & CDFULL));
    return (uint8_t)LPC_USB->CmdData;
}

static void SIEsetDeviceStatus(uint8_t status) {
    // Write SIE device status register
    SIECommand(SIE_CMD_SET_DEVICE_STATUS);
    SIEWriteData(status);
}

static uint8_t SIEgetDeviceStatus(void) {
    // Read SIE device status register
    SIECommand(SIE_CMD_GET_DEVICE_STATUS);
    return SIEReadData(SIE_CMD_GET_DEVICE_STATUS);
}

void SIEsetAddress(uint8_t address) {
    // Write SIE device address register
    SIECommand(SIE_CMD_SET_ADDRESS);
    SIEWriteData((address & 0x7f) | SIE_DSA_DEV_EN);
}

static uint8_t SIEselectEndpoint(uint8_t endpoint) {
    // SIE select endpoint command
    SIECommand(SIE_CMD_SELECT_ENDPOINT(endpoint));
    return SIEReadData(SIE_CMD_SELECT_ENDPOINT(endpoint));
}

static uint8_t SIEclearBuffer(void) {
    // SIE clear buffer command
    SIECommand(SIE_CMD_CLEAR_BUFFER);
    return SIEReadData(SIE_CMD_CLEAR_BUFFER);
}

static void SIEvalidateBuffer(void) {
    // SIE validate buffer command
    SIECommand(SIE_CMD_VALIDATE_BUFFER);
}

static void SIEsetEndpointStatus(uint8_t endpoint, uint8_t status) {
    // SIE set endpoint status command
    SIECommand(SIE_CMD_SET_ENDPOINT_STATUS(endpoint));
    SIEWriteData(status);
}

static uint16_t SIEgetFrameNumber(void) __attribute__ ((unused));
static uint16_t SIEgetFrameNumber(void) {
    // Read current frame number
    uint16_t lowByte;
    uint16_t highByte;

    SIECommand(SIE_CMD_READ_FRAME_NUMBER);
    lowByte = SIEReadData(SIE_CMD_READ_FRAME_NUMBER);
    highByte = SIEReadData(SIE_CMD_READ_FRAME_NUMBER);

    return (highByte << 8) | lowByte;
}

static void SIEconfigureDevice(void) {
    // SIE Configure device command
    SIECommand(SIE_CMD_CONFIGURE_DEVICE);
    SIEWriteData(SIE_CONF_DEVICE);
}

static void SIEunconfigureDevice(void) {
    // SIE Configure device command
    SIECommand(SIE_CMD_CONFIGURE_DEVICE);
    SIEWriteData(0);
}

static void SIEconnect(void) {
    // Connect USB device
    uint8_t status = SIEgetDeviceStatus();
    SIEsetDeviceStatus(status | SIE_DS_CON);
}


static void SIEdisconnect(void) {
    // Disconnect USB device
    uint8_t status = SIEgetDeviceStatus();
    SIEsetDeviceStatus(status & ~SIE_DS_CON);
}


static uint8_t selectEndpointClearInterrupt(uint8_t endpoint) {
    // Implemented using using EP_INT_CLR.
    LPC_USB->EpIntClr = EP(endpoint);
    while (!(LPC_USB->DevIntSt & CDFULL));
    return (uint8_t)LPC_USB->CmdData;
}


static void enableEndpointEvent(uint8_t endpoint) {
    // Enable an endpoint interrupt
    LPC_USB->EpIntEn |= EP(endpoint);
}

static void disableEndpointEvent(uint8_t endpoint) __attribute__ ((unused));
static void disableEndpointEvent(uint8_t endpoint) {
    // Disable an endpoint interrupt
    LPC_USB->EpIntEn &= ~EP(endpoint);
}

static volatile uint32_t __attribute__((used)) dummyRead;
uint32_t USBHAL::endpointReadcore(uint8_t endpoint, uint8_t *buffer) {
    // Read from an OUT endpoint
    uint32_t size;
    uint32_t i;
    uint32_t data = 0;
    uint8_t offset;

    LPC_USB->Ctrl = LOG_ENDPOINT(endpoint) | RD_EN;
    while (!(LPC_USB->RxPLen & PKT_RDY));

    size = LPC_USB->RxPLen & PKT_LNGTH_MASK;

    offset = 0;

    if (size > 0) {
        for (i=0; i<size; i++) {
            if (offset==0) {
                // Fetch up to four bytes of data as a word
                data = LPC_USB->RxData;
            }

            // extract a byte
            *buffer = (data>>offset) & 0xff;
            buffer++;

            // move on to the next byte
            offset = (offset + 8) % 32;
        }
    } else {
        dummyRead = LPC_USB->RxData;
    }

    LPC_USB->Ctrl = 0;

    if ((endpoint >> 1) % 3 || (endpoint >> 1) == 0) {
        SIEselectEndpoint(endpoint);
        SIEclearBuffer();
    }

    return size;
}

static void endpointWritecore(uint8_t endpoint, uint8_t *buffer, uint32_t size) {
    // Write to an IN endpoint
    uint32_t temp, data;
    uint8_t offset;

    LPC_USB->Ctrl = LOG_ENDPOINT(endpoint) | WR_EN;

    LPC_USB->TxPLen = size;
    offset = 0;
    data = 0;

    if (size>0) {
        do {
            // Fetch next data byte into a word-sized temporary variable
            temp = *buffer++;

            // Add to current data word
            temp = temp << offset;
            data = data | temp;

            // move on to the next byte
            offset = (offset + 8) % 32;
            size--;

            if ((offset==0) || (size==0)) {
                // Write the word to the endpoint
                LPC_USB->TxData = data;
                data = 0;
            }
        } while (size>0);
    } else {
        LPC_USB->TxData = 0;
    }

    // Clear WR_EN to cover zero length packet case
    LPC_USB->Ctrl=0;

    SIEselectEndpoint(endpoint);
    SIEvalidateBuffer();
}

USBHAL::USBHAL(void) {
    // Disable IRQ
    NVIC_DisableIRQ(USB_IRQn);

    // fill in callback array
    epCallback[0] = &USBHAL::EP1_OUT_callback;
    epCallback[1] = &USBHAL::EP1_IN_callback;
    epCallback[2] = &USBHAL::EP2_OUT_callback;
    epCallback[3] = &USBHAL::EP2_IN_callback;
    epCallback[4] = &USBHAL::EP3_OUT_callback;
    epCallback[5] = &USBHAL::EP3_IN_callback;
    epCallback[6] = &USBHAL::EP4_OUT_callback;
    epCallback[7] = &USBHAL::EP4_IN_callback;
    epCallback[8] = &USBHAL::EP5_OUT_callback;
    epCallback[9] = &USBHAL::EP5_IN_callback;
    epCallback[10] = &USBHAL::EP6_OUT_callback;
    epCallback[11] = &USBHAL::EP6_IN_callback;
    epCallback[12] = &USBHAL::EP7_OUT_callback;
    epCallback[13] = &USBHAL::EP7_IN_callback;
    epCallback[14] = &USBHAL::EP8_OUT_callback;
    epCallback[15] = &USBHAL::EP8_IN_callback;
    epCallback[16] = &USBHAL::EP9_OUT_callback;
    epCallback[17] = &USBHAL::EP9_IN_callback;
    epCallback[18] = &USBHAL::EP10_OUT_callback;
    epCallback[19] = &USBHAL::EP10_IN_callback;
    epCallback[20] = &USBHAL::EP11_OUT_callback;
    epCallback[21] = &USBHAL::EP11_IN_callback;
    epCallback[22] = &USBHAL::EP12_OUT_callback;
    epCallback[23] = &USBHAL::EP12_IN_callback;
    epCallback[24] = &USBHAL::EP13_OUT_callback;
    epCallback[25] = &USBHAL::EP13_IN_callback;
    epCallback[26] = &USBHAL::EP14_OUT_callback;
    epCallback[27] = &USBHAL::EP14_IN_callback;
    epCallback[28] = &USBHAL::EP15_OUT_callback;
    epCallback[29] = &USBHAL::EP15_IN_callback;

    // Enable power to USB device controller
    LPC_SC->PCONP |= PCUSB;

    // Enable USB clocks
    LPC_USB->USBClkCtrl |= DEV_CLK_EN | AHB_CLK_EN | PORT_CLK_EN;
    while ((LPC_USB->USBClkSt & (DEV_CLK_EN | AHB_CLK_EN | PORT_CLK_EN)) != (DEV_CLK_ON | AHB_CLK_ON | PORT_CLK_EN));

    // Select port USB2
    LPC_USB->StCtrl |= 3;


    // Configure pin P0.31 to be USB2
    LPC_IOCON->P0_31 &= ~0x07;
    LPC_IOCON->P0_31 |= 0x01;

    // Disconnect USB device
    SIEdisconnect();

    // Configure pin P0.14 to be Connect
    LPC_IOCON->P0_14 &= ~0x07;
    LPC_IOCON->P0_14 |= 0x03;

    // Connect must be low for at least 2.5uS
    wait(0.3);

    // Set the maximum packet size for the control endpoints
    realiseEndpoint(EP0IN, MAX_PACKET_SIZE_EP0, 0);
    realiseEndpoint(EP0OUT, MAX_PACKET_SIZE_EP0, 0);

    // Attach IRQ
    instance = this;
    NVIC_SetVector(USB_IRQn, (uint32_t)&_usbisr);

    // Enable interrupts for device events and EP0
    LPC_USB->DevIntEn = EP_SLOW | DEV_STAT | FRAME;
    enableEndpointEvent(EP0IN);
    enableEndpointEvent(EP0OUT);
}

USBHAL::~USBHAL(void) {
    // Ensure device disconnected
    SIEdisconnect();
    // Disable USB interrupts
    NVIC_DisableIRQ(USB_IRQn);
}

void USBHAL::connect(void) {
    NVIC_EnableIRQ(USB_IRQn);
    // Connect USB device
    SIEconnect();
}

void USBHAL::disconnect(void) {
    NVIC_DisableIRQ(USB_IRQn);
    // Disconnect USB device
    SIEdisconnect();
}

void USBHAL::configureDevice(void) {
    SIEconfigureDevice();
}

void USBHAL::unconfigureDevice(void) {
    SIEunconfigureDevice();
}

void USBHAL::setAddress(uint8_t address) {
    SIEsetAddress(address);
}

void USBHAL::EP0setup(uint8_t *buffer) {
    endpointReadcore(EP0OUT, buffer);
}

void USBHAL::EP0read(void) {
    // Not required
}

void USBHAL::EP0readStage(void) {
    // Not required
}

uint32_t USBHAL::EP0getReadResult(uint8_t *buffer) {
    return endpointReadcore(EP0OUT, buffer);
}

void USBHAL::EP0write(uint8_t *buffer, uint32_t size) {
    endpointWritecore(EP0IN, buffer, size);
}

void USBHAL::EP0getWriteResult(void) {
    // Not required
}

void USBHAL::EP0stall(void) {
    // This will stall both control endpoints
    stallEndpoint(EP0OUT);
}

EP_STATUS USBHAL::endpointRead(uint8_t endpoint, uint32_t maximumSize) {
    return EP_PENDING;
}

EP_STATUS USBHAL::endpointReadResult(uint8_t endpoint, uint8_t * buffer, uint32_t *bytesRead) {

    //for isochronous endpoint, we don't wait an interrupt
    if ((endpoint >> 1) % 3 || (endpoint >> 1) == 0) {
        if (!(epComplete & EP(endpoint)))
            return EP_PENDING;
    }

    *bytesRead = endpointReadcore(endpoint, buffer);
    epComplete &= ~EP(endpoint);
    return EP_COMPLETED;
}

EP_STATUS USBHAL::endpointWrite(uint8_t endpoint, uint8_t *data, uint32_t size) {
    if (getEndpointStallState(endpoint)) {
        return EP_STALLED;
    }

    epComplete &= ~EP(endpoint);

    endpointWritecore(endpoint, data, size);
    return EP_PENDING;
}

EP_STATUS USBHAL::endpointWriteResult(uint8_t endpoint) {
    if (epComplete & EP(endpoint)) {
        epComplete &= ~EP(endpoint);
        return EP_COMPLETED;
    }

    return EP_PENDING;
}

bool USBHAL::realiseEndpoint(uint8_t endpoint, uint32_t maxPacket, uint32_t flags) {
    // Realise an endpoint
    LPC_USB->DevIntClr = EP_RLZED;
    LPC_USB->ReEp |= EP(endpoint);
    LPC_USB->EpInd = endpoint;
    LPC_USB->MaxPSize = maxPacket;

    while (!(LPC_USB->DevIntSt & EP_RLZED));
    LPC_USB->DevIntClr = EP_RLZED;

    // Clear stall state
    endpointStallState &= ~EP(endpoint);

    enableEndpointEvent(endpoint);
    return true;
}

void USBHAL::stallEndpoint(uint8_t endpoint) {
    // Stall an endpoint
    if ( (endpoint==EP0IN) || (endpoint==EP0OUT) ) {
        // Conditionally stall both control endpoints
        SIEsetEndpointStatus(EP0OUT, SIE_SES_CND_ST);
    } else {
        SIEsetEndpointStatus(endpoint, SIE_SES_ST);

        // Update stall state
        endpointStallState |= EP(endpoint);
    }
}

void USBHAL::unstallEndpoint(uint8_t endpoint) {
    // Unstall an endpoint. The endpoint will also be reinitialised
    SIEsetEndpointStatus(endpoint, 0);

    // Update stall state
    endpointStallState &= ~EP(endpoint);
}

bool USBHAL::getEndpointStallState(uint8_t endpoint) {
    // Returns true if endpoint stalled
    return endpointStallState & EP(endpoint);
}

void USBHAL::remoteWakeup(void) {
    // Remote wakeup
    uint8_t status;

    // Enable USB clocks
    LPC_USB->USBClkCtrl |= DEV_CLK_EN | AHB_CLK_EN;
    while (LPC_USB->USBClkSt != (DEV_CLK_ON | AHB_CLK_ON));

    status = SIEgetDeviceStatus();
    SIEsetDeviceStatus(status & ~SIE_DS_SUS);
}

void USBHAL::_usbisr(void) {
    instance->usbisr();
}


void USBHAL::usbisr(void) {
    uint8_t devStat;

    if (LPC_USB->DevIntSt & FRAME) {
        // Start of frame event
        SOF(SIEgetFrameNumber());
        // Clear interrupt status flag
        LPC_USB->DevIntClr = FRAME;
    }

    if (LPC_USB->DevIntSt & DEV_STAT) {
        // Device Status interrupt
        // Must clear the interrupt status flag before reading the device status from the SIE
        LPC_USB->DevIntClr = DEV_STAT;

        // Read device status from SIE
        devStat = SIEgetDeviceStatus();
        //printf("devStat: %d\r\n", devStat);

        if (devStat & SIE_DS_SUS_CH) {
            // Suspend status changed
            if((devStat & SIE_DS_SUS) != 0) {
                suspendStateChanged(0);
            }
        }

        if (devStat & SIE_DS_RST) {
            // Bus reset
            if((devStat & SIE_DS_SUS) == 0) {
                suspendStateChanged(1);
            }
            busReset();
        }
    }

    if (LPC_USB->DevIntSt & EP_SLOW) {
        // (Slow) Endpoint Interrupt

        // Process each endpoint interrupt
        if (LPC_USB->EpIntSt & EP(EP0OUT)) {
            if (selectEndpointClearInterrupt(EP0OUT) & SIE_SE_STP) {
                // this is a setup packet
                EP0setupCallback();
            } else {
                EP0out();
            }
            LPC_USB->DevIntClr = EP_SLOW;
        }

        if (LPC_USB->EpIntSt & EP(EP0IN)) {
            selectEndpointClearInterrupt(EP0IN);
            LPC_USB->DevIntClr = EP_SLOW;
            EP0in();
        }

        for (uint8_t num = 2; num < 16*2; num++) {
            if (LPC_USB->EpIntSt & EP(num)) {
                selectEndpointClearInterrupt(num);
                epComplete |= EP(num);
                LPC_USB->DevIntClr = EP_SLOW;
                if ((instance->*(epCallback[num - 2]))()) {
                    epComplete &= ~EP(num);
                }
            }
        }
    }
}

#endif
