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

#if defined(TARGET_LPC11UXX) || defined(TARGET_LPC11U6X) || defined(TARGET_LPC1347) || defined(TARGET_LPC1549)

#if defined(TARGET_LPC1347) || defined(TARGET_LPC1549)
#define USB_IRQ USB_IRQ_IRQn
#else
#define USB_IRQ USB_IRQn
#endif

#include "USBHAL.h"

USBHAL * USBHAL::instance;
#if defined(TARGET_LPC1549)
static uint8_t usbmem[2048] __attribute__((aligned(2048)));
#endif

// Valid physical endpoint numbers are 0 to (NUMBER_OF_PHYSICAL_ENDPOINTS-1)
#define LAST_PHYSICAL_ENDPOINT (NUMBER_OF_PHYSICAL_ENDPOINTS-1)

// Convert physical endpoint number to register bit
#define EP(endpoint) (1UL<<endpoint)

// Convert physical to logical
#define PHY_TO_LOG(endpoint)    ((endpoint)>>1)

// Get endpoint direction
#define IN_EP(endpoint)     ((endpoint) & 1U ? true : false)
#define OUT_EP(endpoint)    ((endpoint) & 1U ? false : true)

// USB RAM
#if defined(TARGET_LPC1549)
#define USB_RAM_START ((uint32_t)usbmem)
#define USB_RAM_SIZE  sizeof(usbmem)
#else
#define USB_RAM_START (0x20004000)
#define USB_RAM_SIZE  (0x00000800)
#endif

// SYSAHBCLKCTRL
#if defined(TARGET_LPC1549)
#define CLK_USB     (1UL<<23)
#else
#define CLK_USB     (1UL<<14)
#define CLK_USBRAM  (1UL<<27)
#endif

// USB Information register
#define FRAME_NR(a)     ((a) & 0x7ff)   // Frame number

// USB Device Command/Status register
#define DEV_ADDR_MASK   (0x7f)          // Device address
#define DEV_ADDR(a)     ((a) & DEV_ADDR_MASK)
#define DEV_EN          (1UL<<7)        // Device enable
#define SETUP           (1UL<<8)        // SETUP token received
#define PLL_ON          (1UL<<9)        // PLL enabled in suspend
#define DCON            (1UL<<16)       // Device status - connect
#define DSUS            (1UL<<17)       // Device status - suspend
#define DCON_C          (1UL<<24)       // Connect change
#define DSUS_C          (1UL<<25)       // Suspend change
#define DRES_C          (1UL<<26)       // Reset change
#define VBUSDEBOUNCED   (1UL<<28)       // Vbus detected

// Endpoint Command/Status list
#define CMDSTS_A                 (1UL<<31)          // Active
#define CMDSTS_D                 (1UL<<30)          // Disable
#define CMDSTS_S                 (1UL<<29)          // Stall
#define CMDSTS_TR                (1UL<<28)          // Toggle Reset
#define CMDSTS_RF                (1UL<<27)          // Rate Feedback mode
#define CMDSTS_TV                (1UL<<27)          // Toggle Value
#define CMDSTS_T                 (1UL<<26)          // Endpoint Type
#define CMDSTS_NBYTES(n)         (((n)&0x3ff)<<16)  // Number of bytes
#define CMDSTS_ADDRESS_OFFSET(a) (((a)>>6)&0xffff)  // Buffer start address

#define BYTES_REMAINING(s)       (((s)>>16)&0x3ff)  // Bytes remaining after transfer

// USB Non-endpoint interrupt sources
#define FRAME_INT   (1UL<<30)
#define DEV_INT     (1UL<<31)

static volatile int epComplete = 0;

// One entry for a double-buffered logical endpoint in the endpoint
// command/status list. Endpoint 0 is single buffered, out[1] is used
// for the SETUP packet and in[1] is not used
typedef struct {
    uint32_t out[2];
    uint32_t in[2];
} PACKED EP_COMMAND_STATUS;

typedef struct {
    uint8_t out[MAX_PACKET_SIZE_EP0];
    uint8_t in[MAX_PACKET_SIZE_EP0];
    uint8_t setup[SETUP_PACKET_SIZE];
} PACKED CONTROL_TRANSFER;

typedef struct {
    uint32_t    maxPacket;
    uint32_t    buffer[2];
    uint32_t    options;
} PACKED EP_STATE;

static volatile EP_STATE endpointState[NUMBER_OF_PHYSICAL_ENDPOINTS];

// Pointer to the endpoint command/status list
static EP_COMMAND_STATUS *ep = NULL;

// Pointer to endpoint 0 data (IN/OUT and SETUP)
static CONTROL_TRANSFER *ct = NULL;

// Shadow DEVCMDSTAT register to avoid accidentally clearing flags or
// initiating a remote wakeup event.
static volatile uint32_t devCmdStat;

// Pointers used to allocate USB RAM
static uint32_t usbRamPtr = USB_RAM_START;
static uint32_t epRamPtr = 0; // Buffers for endpoints > 0 start here

#define ROUND_UP_TO_MULTIPLE(x, m) ((((x)+((m)-1))/(m))*(m))

void USBMemCopy(uint8_t *dst, uint8_t *src, uint32_t size);
void USBMemCopy(uint8_t *dst, uint8_t *src, uint32_t size) {
    if (size > 0) {
        do {
            *dst++ = *src++;
        } while (--size > 0);
    }
}


USBHAL::USBHAL(void) {
    NVIC_DisableIRQ(USB_IRQ);

    // fill in callback array
    epCallback[0] = &USBHAL::EP1_OUT_callback;
    epCallback[1] = &USBHAL::EP1_IN_callback;
    epCallback[2] = &USBHAL::EP2_OUT_callback;
    epCallback[3] = &USBHAL::EP2_IN_callback;
    epCallback[4] = &USBHAL::EP3_OUT_callback;
    epCallback[5] = &USBHAL::EP3_IN_callback;
    epCallback[6] = &USBHAL::EP4_OUT_callback;
    epCallback[7] = &USBHAL::EP4_IN_callback;

#if defined(TARGET_LPC1549)
    /* Set USB PLL input to system oscillator */
    LPC_SYSCON->USBPLLCLKSEL = 0x01;

    /* Setup USB PLL  (FCLKIN = 12MHz) * 4 = 48MHz
       MSEL = 3 (this is pre-decremented), PSEL = 1 (for P = 2)
       FCLKOUT = FCLKIN * (MSEL + 1) = 12MHz * 4 = 48MHz
       FCCO = FCLKOUT * 2 * P = 48MHz * 2 * 2 = 192MHz (within FCCO range) */
    LPC_SYSCON->USBPLLCTRL = (0x3 | (1UL << 6));

    /* Powerup USB PLL */
    LPC_SYSCON->PDRUNCFG &= ~(CLK_USB);

    /* Wait for PLL to lock */
    while(!(LPC_SYSCON->USBPLLSTAT & 0x01));

    /* enable USB main clock */
    LPC_SYSCON->USBCLKSEL = 0x02;
    LPC_SYSCON->USBCLKDIV = 1;

    /* Enable AHB clock to the USB block. */
    LPC_SYSCON->SYSAHBCLKCTRL1 |= CLK_USB;

    /* power UP USB Phy */
    LPC_SYSCON->PDRUNCFG &= ~(1UL << 9);

    /* Reset USB block */
    LPC_SYSCON->PRESETCTRL1 |= (CLK_USB);
    LPC_SYSCON->PRESETCTRL1 &= ~(CLK_USB);

#else
    #if defined(TARGET_LPC11U35_401) || defined(TARGET_LPC11U35_501)
    // USB_VBUS input with pull-down
    LPC_IOCON->PIO0_3 = 0x00000009;
    #endif

    // nUSB_CONNECT output
    LPC_IOCON->PIO0_6 = 0x00000001;

    // Enable clocks (USB registers, USB RAM)
    LPC_SYSCON->SYSAHBCLKCTRL |= CLK_USB | CLK_USBRAM;

    // Ensure device disconnected (DCON not set)
    LPC_USB->DEVCMDSTAT = 0;
#endif
    // to ensure that the USB host sees the device as
    // disconnected if the target CPU is reset.
    wait(0.3);

    // Reserve space in USB RAM for endpoint command/status list
    // Must be 256 byte aligned
    usbRamPtr = ROUND_UP_TO_MULTIPLE(usbRamPtr, 256);
    ep = (EP_COMMAND_STATUS *)usbRamPtr;
    usbRamPtr += (sizeof(EP_COMMAND_STATUS) * NUMBER_OF_LOGICAL_ENDPOINTS);
    LPC_USB->EPLISTSTART = (uint32_t)(ep) & 0xffffff00;

    // Reserve space in USB RAM for Endpoint 0
    // Must be 64 byte aligned
    usbRamPtr = ROUND_UP_TO_MULTIPLE(usbRamPtr, 64);
    ct = (CONTROL_TRANSFER *)usbRamPtr;
    usbRamPtr += sizeof(CONTROL_TRANSFER);
    LPC_USB->DATABUFSTART =(uint32_t)(ct) & 0xffc00000;

    // Setup command/status list for EP0
    ep[0].out[0] = 0;
    ep[0].in[0] =  0;
    ep[0].out[1] = CMDSTS_ADDRESS_OFFSET((uint32_t)ct->setup);

    // Route all interrupts to IRQ, some can be routed to
    // USB_FIQ if you wish.
    LPC_USB->INTROUTING = 0;

    // Set device address 0, enable USB device, no remote wakeup
    devCmdStat = DEV_ADDR(0) | DEV_EN | DSUS;
    LPC_USB->DEVCMDSTAT = devCmdStat;

    // Enable interrupts for device events and EP0
    LPC_USB->INTEN = DEV_INT | EP(EP0IN) | EP(EP0OUT) | FRAME_INT;
    instance = this;

    //attach IRQ handler and enable interrupts
    NVIC_SetVector(USB_IRQ, (uint32_t)&_usbisr);
}

USBHAL::~USBHAL(void) {
    // Ensure device disconnected (DCON not set)
    LPC_USB->DEVCMDSTAT = 0;
    // Disable USB interrupts
    NVIC_DisableIRQ(USB_IRQ);
}

void USBHAL::connect(void) {
    NVIC_EnableIRQ(USB_IRQ);
    devCmdStat |= DCON;
    LPC_USB->DEVCMDSTAT = devCmdStat;
}

void USBHAL::disconnect(void) {
    NVIC_DisableIRQ(USB_IRQ);
    devCmdStat &= ~DCON;
    LPC_USB->DEVCMDSTAT = devCmdStat;
}

void USBHAL::configureDevice(void) {
    // Not required
}

void USBHAL::unconfigureDevice(void) {
    // Not required
}

void USBHAL::EP0setup(uint8_t *buffer) {
    // Copy setup packet data
    USBMemCopy(buffer, ct->setup, SETUP_PACKET_SIZE);
}

void USBHAL::EP0read(void) {
    // Start an endpoint 0 read

    // The USB ISR will call USBDevice_EP0out() when a packet has been read,
    // the USBDevice layer then calls USBBusInterface_EP0getReadResult() to
    // read the data.

    ep[0].out[0] = CMDSTS_A |CMDSTS_NBYTES(MAX_PACKET_SIZE_EP0) \
                   | CMDSTS_ADDRESS_OFFSET((uint32_t)ct->out);
}

uint32_t USBHAL::EP0getReadResult(uint8_t *buffer) {
    // Complete an endpoint 0 read
    uint32_t bytesRead;

    // Find how many bytes were read
    bytesRead = MAX_PACKET_SIZE_EP0 - BYTES_REMAINING(ep[0].out[0]);

    // Copy data
    USBMemCopy(buffer, ct->out, bytesRead);
    return bytesRead;
}


void USBHAL::EP0readStage(void) {
    // Not required
}

void USBHAL::EP0write(uint8_t *buffer, uint32_t size) {
    // Start and endpoint 0 write

    // The USB ISR will call USBDevice_EP0in() when the data has
    // been written, the USBDevice layer then calls
    // USBBusInterface_EP0getWriteResult() to complete the transaction.

    // Copy data
    USBMemCopy(ct->in, buffer, size);

    // Start transfer
    ep[0].in[0] = CMDSTS_A | CMDSTS_NBYTES(size) \
                  | CMDSTS_ADDRESS_OFFSET((uint32_t)ct->in);
}


EP_STATUS USBHAL::endpointRead(uint8_t endpoint, uint32_t maximumSize) {
    uint8_t bf = 0;
    uint32_t flags = 0;

    //check which buffer must be filled
    if (LPC_USB->EPBUFCFG & EP(endpoint)) {
        // Double buffered
        if (LPC_USB->EPINUSE & EP(endpoint)) {
            bf = 1;
        } else {
            bf = 0;
        }
    }

    // if isochronous endpoint, T = 1
    if(endpointState[endpoint].options & ISOCHRONOUS)
    {
        flags |= CMDSTS_T;
    }

    //Active the endpoint for reading
    ep[PHY_TO_LOG(endpoint)].out[bf] = CMDSTS_A | CMDSTS_NBYTES(maximumSize) \
                                       | CMDSTS_ADDRESS_OFFSET((uint32_t)ct->out) | flags;
    return EP_PENDING;
}

EP_STATUS USBHAL::endpointReadResult(uint8_t endpoint, uint8_t *data, uint32_t *bytesRead) {

    uint8_t bf = 0;

    if (!(epComplete & EP(endpoint)))
        return EP_PENDING;
    else {
        epComplete &= ~EP(endpoint);

        //check which buffer has been filled
        if (LPC_USB->EPBUFCFG & EP(endpoint)) {
            // Double buffered (here we read the previous buffer which was used)
            if (LPC_USB->EPINUSE & EP(endpoint)) {
                bf = 0;
            } else {
                bf = 1;
            }
        }

        // Find how many bytes were read
        *bytesRead = (uint32_t) (endpointState[endpoint].maxPacket - BYTES_REMAINING(ep[PHY_TO_LOG(endpoint)].out[bf]));

        // Copy data
        USBMemCopy(data, ct->out, *bytesRead);
        return EP_COMPLETED;
    }
}

void USBHAL::EP0getWriteResult(void) {
    // Not required
}

void USBHAL::EP0stall(void) {
    ep[0].in[0] = CMDSTS_S;
    ep[0].out[0] = CMDSTS_S;
}

void USBHAL::setAddress(uint8_t address) {
    devCmdStat &= ~DEV_ADDR_MASK;
    devCmdStat |= DEV_ADDR(address);
    LPC_USB->DEVCMDSTAT = devCmdStat;
}

EP_STATUS USBHAL::endpointWrite(uint8_t endpoint, uint8_t *data, uint32_t size) {
    uint32_t flags = 0;
    uint32_t bf;

    // Validate parameters
    if (data == NULL) {
        return EP_INVALID;
    }

    if (endpoint > LAST_PHYSICAL_ENDPOINT) {
        return EP_INVALID;
    }

    if ((endpoint==EP0IN) || (endpoint==EP0OUT)) {
        return EP_INVALID;
    }

    if (size > endpointState[endpoint].maxPacket) {
        return EP_INVALID;
    }

    if (LPC_USB->EPBUFCFG & EP(endpoint)) {
        // Double buffered
        if (LPC_USB->EPINUSE & EP(endpoint)) {
            bf = 1;
        } else {
            bf = 0;
        }
    } else {
        // Single buffered
        bf = 0;
    }

    // Check if already active
    if (ep[PHY_TO_LOG(endpoint)].in[bf] & CMDSTS_A) {
        return EP_INVALID;
    }

    // Check if stalled
    if (ep[PHY_TO_LOG(endpoint)].in[bf] & CMDSTS_S) {
        return EP_STALLED;
    }

    // Copy data to USB RAM
    USBMemCopy((uint8_t *)endpointState[endpoint].buffer[bf], data, size);

    // Add options
    if (endpointState[endpoint].options & RATE_FEEDBACK_MODE) {
        flags |= CMDSTS_RF;
    }

    if (endpointState[endpoint].options & ISOCHRONOUS) {
        flags |= CMDSTS_T;
    }

    // Add transfer
    ep[PHY_TO_LOG(endpoint)].in[bf] = CMDSTS_ADDRESS_OFFSET( \
                                      endpointState[endpoint].buffer[bf]) \
                                      | CMDSTS_NBYTES(size) | CMDSTS_A | flags;

    return EP_PENDING;
}

EP_STATUS USBHAL::endpointWriteResult(uint8_t endpoint) {
    uint32_t bf;

    // Validate parameters
    if (endpoint > LAST_PHYSICAL_ENDPOINT) {
        return EP_INVALID;
    }

    if (OUT_EP(endpoint)) {
        return EP_INVALID;
    }

    if (LPC_USB->EPBUFCFG & EP(endpoint)) {
        // Double buffered     // TODO: FIX THIS
        if (LPC_USB->EPINUSE & EP(endpoint)) {
            bf = 1;
        } else {
            bf = 0;
        }
    } else {
        // Single buffered
        bf = 0;
    }

    // Check if endpoint still active
    if (ep[PHY_TO_LOG(endpoint)].in[bf] & CMDSTS_A) {
        return EP_PENDING;
    }

    // Check if stalled
    if (ep[PHY_TO_LOG(endpoint)].in[bf] & CMDSTS_S) {
        return EP_STALLED;
    }

    return EP_COMPLETED;
}

void USBHAL::stallEndpoint(uint8_t endpoint) {

    // FIX: should this clear active bit?
    if (IN_EP(endpoint)) {
        ep[PHY_TO_LOG(endpoint)].in[0] |= CMDSTS_S;
        ep[PHY_TO_LOG(endpoint)].in[1] |= CMDSTS_S;
    } else {
        ep[PHY_TO_LOG(endpoint)].out[0] |= CMDSTS_S;
        ep[PHY_TO_LOG(endpoint)].out[1] |= CMDSTS_S;
    }
}

void USBHAL::unstallEndpoint(uint8_t endpoint) {
    if (LPC_USB->EPBUFCFG & EP(endpoint)) {
        // Double buffered
        if (IN_EP(endpoint)) {
            ep[PHY_TO_LOG(endpoint)].in[0] = 0; // S = 0
            ep[PHY_TO_LOG(endpoint)].in[1] = 0; // S = 0

            if (LPC_USB->EPINUSE & EP(endpoint)) {
                ep[PHY_TO_LOG(endpoint)].in[1] = CMDSTS_TR; // S = 0, TR = 1, TV = 0
            } else {
                ep[PHY_TO_LOG(endpoint)].in[0] = CMDSTS_TR; // S = 0, TR = 1, TV = 0
            }
        } else {
            ep[PHY_TO_LOG(endpoint)].out[0] = 0; // S = 0
            ep[PHY_TO_LOG(endpoint)].out[1] = 0; // S = 0

            if (LPC_USB->EPINUSE & EP(endpoint)) {
                ep[PHY_TO_LOG(endpoint)].out[1] = CMDSTS_TR; // S = 0, TR = 1, TV = 0
            } else {
                ep[PHY_TO_LOG(endpoint)].out[0] = CMDSTS_TR; // S = 0, TR = 1, TV = 0
            }
        }
    } else {
        // Single buffered
        if (IN_EP(endpoint)) {
            ep[PHY_TO_LOG(endpoint)].in[0] = CMDSTS_TR;     // S = 0, TR = 1, TV = 0
        } else {
            ep[PHY_TO_LOG(endpoint)].out[0] = CMDSTS_TR;    // S = 0, TR = 1, TV = 0
        }
    }
}

bool USBHAL::getEndpointStallState(unsigned char endpoint) {
    if (IN_EP(endpoint)) {
        if (LPC_USB->EPINUSE & EP(endpoint)) {
            if (ep[PHY_TO_LOG(endpoint)].in[1] & CMDSTS_S) {
                return true;
            }
        } else {
            if (ep[PHY_TO_LOG(endpoint)].in[0] & CMDSTS_S) {
                return true;
            }
        }
    } else {
        if (LPC_USB->EPINUSE & EP(endpoint)) {
            if (ep[PHY_TO_LOG(endpoint)].out[1] & CMDSTS_S) {
                return true;
            }
        } else {
            if (ep[PHY_TO_LOG(endpoint)].out[0] & CMDSTS_S) {
                return true;
            }
        }
    }

    return false;
}

bool USBHAL::realiseEndpoint(uint8_t endpoint, uint32_t maxPacket, uint32_t options) {
    uint32_t tmpEpRamPtr;

    if (endpoint > LAST_PHYSICAL_ENDPOINT) {
        return false;
    }

    // Not applicable to the control endpoints
    if ((endpoint==EP0IN) || (endpoint==EP0OUT)) {
        return false;
    }

    // Allocate buffers in USB RAM
    tmpEpRamPtr = epRamPtr;

    // Must be 64 byte aligned
    tmpEpRamPtr = ROUND_UP_TO_MULTIPLE(tmpEpRamPtr, 64);

    if ((tmpEpRamPtr + maxPacket) > (USB_RAM_START + USB_RAM_SIZE)) {
        // Out of memory
        return false;
    }

    // Allocate first buffer
    endpointState[endpoint].buffer[0] = tmpEpRamPtr;
    tmpEpRamPtr += maxPacket;

    if (!(options & SINGLE_BUFFERED)) {
        // Must be 64 byte aligned
        tmpEpRamPtr = ROUND_UP_TO_MULTIPLE(tmpEpRamPtr, 64);

        if ((tmpEpRamPtr + maxPacket) > (USB_RAM_START + USB_RAM_SIZE)) {
            // Out of memory
            return false;
        }

        // Allocate second buffer
        endpointState[endpoint].buffer[1] = tmpEpRamPtr;
        tmpEpRamPtr += maxPacket;
    }

    // Commit to this USB RAM allocation
    epRamPtr = tmpEpRamPtr;

    // Remaining endpoint state values
    endpointState[endpoint].maxPacket = maxPacket;
    endpointState[endpoint].options = options;

    // Enable double buffering if required
    if (options & SINGLE_BUFFERED) {
        LPC_USB->EPBUFCFG &= ~EP(endpoint);
    } else {
        // Double buffered
        LPC_USB->EPBUFCFG |= EP(endpoint);
    }

    // Enable interrupt
    LPC_USB->INTEN |= EP(endpoint);

    // Enable endpoint
    unstallEndpoint(endpoint);
    return true;
}

void USBHAL::remoteWakeup(void) {
    // Clearing DSUS bit initiates a remote wakeup if the
    // device is currently enabled and suspended - otherwise
    // it has no effect.
    LPC_USB->DEVCMDSTAT = devCmdStat & ~DSUS;
}


static void disableEndpoints(void) {
    uint32_t logEp;

    // Ref. Table 158 "When a bus reset is received, software
    // must set the disable bit of all endpoints to 1".

    for (logEp = 1; logEp < NUMBER_OF_LOGICAL_ENDPOINTS; logEp++) {
        ep[logEp].out[0] = CMDSTS_D;
        ep[logEp].out[1] = CMDSTS_D;
        ep[logEp].in[0] =  CMDSTS_D;
        ep[logEp].in[1] =  CMDSTS_D;
    }

    // Start of USB RAM for endpoints > 0
    epRamPtr = usbRamPtr;
}



void USBHAL::_usbisr(void) {
    instance->usbisr();
}

void USBHAL::usbisr(void) {
    // Start of frame
    if (LPC_USB->INTSTAT & FRAME_INT) {
        // Clear SOF interrupt
        LPC_USB->INTSTAT = FRAME_INT;

        // SOF event, read frame number
        SOF(FRAME_NR(LPC_USB->INFO));
    }

    // Device state
    if (LPC_USB->INTSTAT & DEV_INT) {
        LPC_USB->INTSTAT = DEV_INT;

        if (LPC_USB->DEVCMDSTAT & DSUS_C) {
            // Suspend status changed
            LPC_USB->DEVCMDSTAT = devCmdStat | DSUS_C;
            if((LPC_USB->DEVCMDSTAT & DSUS) != 0) {
                suspendStateChanged(1);
            }
        }

        if (LPC_USB->DEVCMDSTAT & DRES_C) {
            // Bus reset
            LPC_USB->DEVCMDSTAT = devCmdStat | DRES_C;

            suspendStateChanged(0);

            // Disable endpoints > 0
            disableEndpoints();

            // Bus reset event
            busReset();
        }
    }

    // Endpoint 0
    if (LPC_USB->INTSTAT & EP(EP0OUT)) {
        // Clear EP0OUT/SETUP interrupt
        LPC_USB->INTSTAT = EP(EP0OUT);

        // Check if SETUP
        if (LPC_USB->DEVCMDSTAT & SETUP) {
            // Clear Active and Stall bits for EP0
            // Documentation does not make it clear if we must use the
            // EPSKIP register to achieve this, Fig. 16 and NXP reference
            // code suggests we can just clear the Active bits - check with
            // NXP to be sure.
            ep[0].in[0] = 0;
            ep[0].out[0] = 0;

            // Clear EP0IN interrupt
            LPC_USB->INTSTAT = EP(EP0IN);

            // Clear SETUP (and INTONNAK_CI/O) in device status register
            LPC_USB->DEVCMDSTAT = devCmdStat | SETUP;

            // EP0 SETUP event (SETUP data received)
            EP0setupCallback();
        } else {
            // EP0OUT ACK event (OUT data received)
            EP0out();
        }
    }

    if (LPC_USB->INTSTAT & EP(EP0IN)) {
        // Clear EP0IN interrupt
        LPC_USB->INTSTAT = EP(EP0IN);

        // EP0IN ACK event (IN data sent)
        EP0in();
    }

    for (uint8_t num = 2; num < 5*2; num++) {
        if (LPC_USB->INTSTAT & EP(num)) {
            LPC_USB->INTSTAT = EP(num);
            epComplete |= EP(num);
            if ((instance->*(epCallback[num - 2]))()) {
                epComplete &= ~EP(num);
            }
        }
    }
}

#endif
