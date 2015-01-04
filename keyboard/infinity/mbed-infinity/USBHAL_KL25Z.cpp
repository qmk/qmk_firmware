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

#if defined(TARGET_KL25Z) | defined(TARGET_KL43Z) | defined(TARGET_KL46Z) | defined(TARGET_K20D50M) | defined(TARGET_K64F) | defined(TARGET_K22F)

#include "USBHAL.h"

USBHAL * USBHAL::instance;

static volatile int epComplete = 0;

// Convert physical endpoint number to register bit
#define EP(endpoint) (1<<(endpoint))

// Convert physical to logical
#define PHY_TO_LOG(endpoint)    ((endpoint)>>1)

// Get endpoint direction
#define IN_EP(endpoint)     ((endpoint) & 1U ? true : false)
#define OUT_EP(endpoint)    ((endpoint) & 1U ? false : true)

#define BD_OWN_MASK        (1<<7)
#define BD_DATA01_MASK     (1<<6)
#define BD_KEEP_MASK       (1<<5)
#define BD_NINC_MASK       (1<<4)
#define BD_DTS_MASK        (1<<3)
#define BD_STALL_MASK      (1<<2)

#define TX    1
#define RX    0
#define ODD   0
#define EVEN  1
// this macro waits a physical endpoint number
#define EP_BDT_IDX(ep, dir, odd) (((ep * 4) + (2 * dir) + (1 *  odd)))

#define SETUP_TOKEN    0x0D
#define IN_TOKEN       0x09
#define OUT_TOKEN      0x01
#define TOK_PID(idx)   ((bdt[idx].info >> 2) & 0x0F)

// for each endpt: 8 bytes
typedef struct BDT {
    uint8_t   info;       // BD[0:7]
    uint8_t   dummy;      // RSVD: BD[8:15]
    uint16_t  byte_count; // BD[16:32]
    uint32_t  address;    // Addr
} BDT;


// there are:
//    * 16 bidirectionnal endpt -> 32 physical endpt
//    * as there are ODD and EVEN buffer -> 32*2 bdt
__attribute__((__aligned__(512))) BDT bdt[NUMBER_OF_PHYSICAL_ENDPOINTS * 2];
uint8_t * endpoint_buffer[(NUMBER_OF_PHYSICAL_ENDPOINTS - 2) * 2];
uint8_t * endpoint_buffer_iso[2*2];

static uint8_t set_addr = 0;
static uint8_t addr = 0;

static uint32_t Data1  = 0x55555555;

static uint32_t frameNumber() {
    return((USB0->FRMNUML | (USB0->FRMNUMH << 8)) & 0x07FF);
}

uint32_t USBHAL::endpointReadcore(uint8_t endpoint, uint8_t *buffer) {
    return 0;
}

USBHAL::USBHAL(void) {
    // Disable IRQ
    NVIC_DisableIRQ(USB0_IRQn);

#if defined(TARGET_K64F)
    MPU->CESR=0;
#endif
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

#if defined(TARGET_KL43Z)
    // enable USBFS clock
    SIM->SCGC4 |= SIM_SCGC4_USBFS_MASK;

    // enable the IRC48M clock
    USB0->CLK_RECOVER_IRC_EN |= USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK;

    // enable the USB clock recovery tuning
    USB0->CLK_RECOVER_CTRL |= USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK;

    // choose usb src clock
    SIM->SOPT2 |= SIM_SOPT2_USBSRC_MASK;
#elif defined(TARGET_INFINITY)
    // USB clock source: FLL
    SIM->SOPT2 |= SIM_SOPT2_USBSRC_MASK;

    // enable OTG clock
    SIM->SCGC4 |= SIM_SCGC4_USBOTG_MASK;
#else
    // choose usb src as PLL
    SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
    SIM->SOPT2 |= (SIM_SOPT2_USBSRC_MASK | (1 << SIM_SOPT2_PLLFLLSEL_SHIFT));

    // enable OTG clock
    SIM->SCGC4 |= SIM_SCGC4_USBOTG_MASK;
#endif

    // Attach IRQ
    instance = this;
    NVIC_SetVector(USB0_IRQn, (uint32_t)&_usbisr);
    NVIC_EnableIRQ(USB0_IRQn);

    // USB Module Configuration
    // Reset USB Module
    USB0->USBTRC0 |= USB_USBTRC0_USBRESET_MASK;
    while(USB0->USBTRC0 & USB_USBTRC0_USBRESET_MASK);

    // Set BDT Base Register
    USB0->BDTPAGE1 = (uint8_t)((uint32_t)bdt>>8);
    USB0->BDTPAGE2 = (uint8_t)((uint32_t)bdt>>16);
    USB0->BDTPAGE3 = (uint8_t)((uint32_t)bdt>>24);

    // Clear interrupt flag
    USB0->ISTAT = 0xff;

    // USB Interrupt Enablers
    USB0->INTEN |= USB_INTEN_TOKDNEEN_MASK |
                   USB_INTEN_SOFTOKEN_MASK |
                   USB_INTEN_ERROREN_MASK  |
                   USB_INTEN_USBRSTEN_MASK;

    // Disable weak pull downs
    USB0->USBCTRL &= ~(USB_USBCTRL_PDE_MASK | USB_USBCTRL_SUSP_MASK);

    USB0->USBTRC0 |= 0x40;
}

USBHAL::~USBHAL(void) { }

void USBHAL::connect(void) {
    // enable USB
    USB0->CTL |= USB_CTL_USBENSOFEN_MASK;
    // Pull up enable
    USB0->CONTROL |= USB_CONTROL_DPPULLUPNONOTG_MASK;
}

void USBHAL::disconnect(void) {
    // disable USB
    USB0->CTL &= ~USB_CTL_USBENSOFEN_MASK;
    // Pull up disable
    USB0->CONTROL &= ~USB_CONTROL_DPPULLUPNONOTG_MASK;

    //Free buffers if required:
    for (int i = 0; i<(NUMBER_OF_PHYSICAL_ENDPOINTS - 2) * 2; i++) {
        free(endpoint_buffer[i]);
        endpoint_buffer[i] = NULL;
    }
    free(endpoint_buffer_iso[2]);
    endpoint_buffer_iso[2] = NULL;
    free(endpoint_buffer_iso[0]);
    endpoint_buffer_iso[0] = NULL;
}

void USBHAL::configureDevice(void) {
    // not needed
}

void USBHAL::unconfigureDevice(void) {
    // not needed
}

void USBHAL::setAddress(uint8_t address) {
    // we don't set the address now otherwise the usb controller does not ack
    // we set a flag instead
    // see usbisr when an IN token is received
    set_addr = 1;
    addr = address;
}

bool USBHAL::realiseEndpoint(uint8_t endpoint, uint32_t maxPacket, uint32_t flags) {
    uint32_t handshake_flag = 0;
    uint8_t * buf;

    if (endpoint > NUMBER_OF_PHYSICAL_ENDPOINTS - 1) {
        return false;
    }

    uint32_t log_endpoint = PHY_TO_LOG(endpoint);

    if ((flags & ISOCHRONOUS) == 0) {
        handshake_flag = USB_ENDPT_EPHSHK_MASK;
        if (IN_EP(endpoint)) {
            if (endpoint_buffer[EP_BDT_IDX(log_endpoint, TX, ODD)] == NULL)
                endpoint_buffer[EP_BDT_IDX(log_endpoint, TX, ODD)] = (uint8_t *) malloc (64*2);
            buf = &endpoint_buffer[EP_BDT_IDX(log_endpoint, TX, ODD)][0];
        } else {
            if (endpoint_buffer[EP_BDT_IDX(log_endpoint, RX, ODD)] == NULL)
                endpoint_buffer[EP_BDT_IDX(log_endpoint, RX, ODD)] = (uint8_t *) malloc (64*2);
            buf = &endpoint_buffer[EP_BDT_IDX(log_endpoint, RX, ODD)][0];
        }
    } else {
        if (IN_EP(endpoint)) {
            if (endpoint_buffer_iso[2] == NULL)
                endpoint_buffer_iso[2] = (uint8_t *) malloc (1023*2);
            buf = &endpoint_buffer_iso[2][0];
        } else {
            if (endpoint_buffer_iso[0] == NULL)
                endpoint_buffer_iso[0] = (uint8_t *) malloc (1023*2);
            buf = &endpoint_buffer_iso[0][0];
        }
    }

    // IN endpt -> device to host (TX)
    if (IN_EP(endpoint)) {
        USB0->ENDPOINT[log_endpoint].ENDPT |= handshake_flag |        // ep handshaking (not if iso endpoint)
                                              USB_ENDPT_EPTXEN_MASK;  // en TX (IN) tran
        bdt[EP_BDT_IDX(log_endpoint, TX, ODD )].address = (uint32_t) buf;
        bdt[EP_BDT_IDX(log_endpoint, TX, EVEN)].address = 0;
    }
    // OUT endpt -> host to device (RX)
    else {
        USB0->ENDPOINT[log_endpoint].ENDPT |= handshake_flag |        // ep handshaking (not if iso endpoint)
                                              USB_ENDPT_EPRXEN_MASK;  // en RX (OUT) tran.
        bdt[EP_BDT_IDX(log_endpoint, RX, ODD )].byte_count = maxPacket;
        bdt[EP_BDT_IDX(log_endpoint, RX, ODD )].address    = (uint32_t) buf;
        bdt[EP_BDT_IDX(log_endpoint, RX, ODD )].info       = BD_OWN_MASK | BD_DTS_MASK;
        bdt[EP_BDT_IDX(log_endpoint, RX, EVEN)].info       = 0;
    }

    Data1 |= (1 << endpoint);

    return true;
}

// read setup packet
void USBHAL::EP0setup(uint8_t *buffer) {
    uint32_t sz;
    endpointReadResult(EP0OUT, buffer, &sz);
}

void USBHAL::EP0readStage(void) {
    Data1 &= ~1UL;  // set DATA0
    bdt[0].info = (BD_DTS_MASK | BD_OWN_MASK);
}

void USBHAL::EP0read(void) {
    uint32_t idx = EP_BDT_IDX(PHY_TO_LOG(EP0OUT), RX, 0);
    bdt[idx].byte_count = MAX_PACKET_SIZE_EP0;
}

uint32_t USBHAL::EP0getReadResult(uint8_t *buffer) {
    uint32_t sz;
    endpointReadResult(EP0OUT, buffer, &sz);
    return sz;
}

void USBHAL::EP0write(uint8_t *buffer, uint32_t size) {
    endpointWrite(EP0IN, buffer, size);
}

void USBHAL::EP0getWriteResult(void) {
}

void USBHAL::EP0stall(void) {
    stallEndpoint(EP0OUT);
}

EP_STATUS USBHAL::endpointRead(uint8_t endpoint, uint32_t maximumSize) {
    endpoint = PHY_TO_LOG(endpoint);
    uint32_t idx = EP_BDT_IDX(endpoint, RX, 0);
    bdt[idx].byte_count = maximumSize;
    return EP_PENDING;
}

EP_STATUS USBHAL::endpointReadResult(uint8_t endpoint, uint8_t * buffer, uint32_t *bytesRead) {
    uint32_t n, sz, idx, setup = 0;
    uint8_t not_iso;
    uint8_t * ep_buf;

    uint32_t log_endpoint = PHY_TO_LOG(endpoint);

    if (endpoint > NUMBER_OF_PHYSICAL_ENDPOINTS - 1) {
        return EP_INVALID;
    }

    // if read on a IN endpoint -> error
    if (IN_EP(endpoint)) {
        return EP_INVALID;
    }

    idx = EP_BDT_IDX(log_endpoint, RX, 0);
    sz  = bdt[idx].byte_count;
    not_iso = USB0->ENDPOINT[log_endpoint].ENDPT & USB_ENDPT_EPHSHK_MASK;

    //for isochronous endpoint, we don't wait an interrupt
    if ((log_endpoint != 0) && not_iso && !(epComplete & EP(endpoint))) {
        return EP_PENDING;
    }

    if ((log_endpoint == 0) && (TOK_PID(idx) == SETUP_TOKEN)) {
        setup = 1;
    }

    // non iso endpoint
    if (not_iso) {
        ep_buf = endpoint_buffer[idx];
    } else {
        ep_buf = endpoint_buffer_iso[0];
    }

    for (n = 0; n < sz; n++) {
        buffer[n] = ep_buf[n];
    }

    if (((Data1 >> endpoint) & 1) == ((bdt[idx].info >> 6) & 1)) {
        if (setup && (buffer[6] == 0))  // if no setup data stage,
            Data1 &= ~1UL;              // set DATA0
        else
            Data1 ^= (1 << endpoint);
    }

    if (((Data1 >> endpoint) & 1)) {
        bdt[idx].info = BD_DTS_MASK | BD_DATA01_MASK | BD_OWN_MASK;
    }
    else {
        bdt[idx].info = BD_DTS_MASK | BD_OWN_MASK;
    }

    USB0->CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
    *bytesRead = sz;

    epComplete &= ~EP(endpoint);
    return EP_COMPLETED;
}

EP_STATUS USBHAL::endpointWrite(uint8_t endpoint, uint8_t *data, uint32_t size) {
    uint32_t idx, n;
    uint8_t * ep_buf;

    if (endpoint > NUMBER_OF_PHYSICAL_ENDPOINTS - 1) {
        return EP_INVALID;
    }

    // if write on a OUT endpoint -> error
    if (OUT_EP(endpoint)) {
        return EP_INVALID;
    }

    idx = EP_BDT_IDX(PHY_TO_LOG(endpoint), TX, 0);
    bdt[idx].byte_count = size;


    // non iso endpoint
    if (USB0->ENDPOINT[PHY_TO_LOG(endpoint)].ENDPT & USB_ENDPT_EPHSHK_MASK) {
        ep_buf = endpoint_buffer[idx];
    } else {
        ep_buf = endpoint_buffer_iso[2];
    }

    for (n = 0; n < size; n++) {
        ep_buf[n] = data[n];
    }

    if ((Data1 >> endpoint) & 1) {
        bdt[idx].info = BD_OWN_MASK | BD_DTS_MASK;
    } else {
        bdt[idx].info = BD_OWN_MASK | BD_DTS_MASK | BD_DATA01_MASK;
    }

    Data1 ^= (1 << endpoint);

    return EP_PENDING;
}

EP_STATUS USBHAL::endpointWriteResult(uint8_t endpoint) {
    if (epComplete & EP(endpoint)) {
        epComplete &= ~EP(endpoint);
        return EP_COMPLETED;
    }

    return EP_PENDING;
}

void USBHAL::stallEndpoint(uint8_t endpoint) {
    USB0->ENDPOINT[PHY_TO_LOG(endpoint)].ENDPT |= USB_ENDPT_EPSTALL_MASK;
}

void USBHAL::unstallEndpoint(uint8_t endpoint) {
    USB0->ENDPOINT[PHY_TO_LOG(endpoint)].ENDPT &= ~USB_ENDPT_EPSTALL_MASK;
}

bool USBHAL::getEndpointStallState(uint8_t endpoint) {
    uint8_t stall = (USB0->ENDPOINT[PHY_TO_LOG(endpoint)].ENDPT & USB_ENDPT_EPSTALL_MASK);
    return (stall) ? true : false;
}

void USBHAL::remoteWakeup(void) {
    // [TODO]
}


void USBHAL::_usbisr(void) {
    instance->usbisr();
}


void USBHAL::usbisr(void) {
    uint8_t i;
    uint8_t istat = USB0->ISTAT;

    // reset interrupt
    if (istat & USB_ISTAT_USBRST_MASK) {
        // disable all endpt
        for(i = 0; i < 16; i++) {
            USB0->ENDPOINT[i].ENDPT = 0x00;
        }

        // enable control endpoint
        realiseEndpoint(EP0OUT, MAX_PACKET_SIZE_EP0, 0);
        realiseEndpoint(EP0IN, MAX_PACKET_SIZE_EP0, 0);

        Data1 = 0x55555555;
        USB0->CTL |=  USB_CTL_ODDRST_MASK;

        USB0->ISTAT   =  0xFF;  // clear all interrupt status flags
        USB0->ERRSTAT =  0xFF;  // clear all error flags
        USB0->ERREN   =  0xFF;  // enable error interrupt sources
        USB0->ADDR    =  0x00;  // set default address

        return;
    }

    // resume interrupt
    if (istat & USB_ISTAT_RESUME_MASK) {
        USB0->ISTAT = USB_ISTAT_RESUME_MASK;
    }

    // SOF interrupt
    if (istat & USB_ISTAT_SOFTOK_MASK) {
        USB0->ISTAT = USB_ISTAT_SOFTOK_MASK;
        // SOF event, read frame number
        SOF(frameNumber());
    }

    // stall interrupt
    if (istat & 1<<7) {
        if (USB0->ENDPOINT[0].ENDPT & USB_ENDPT_EPSTALL_MASK)
            USB0->ENDPOINT[0].ENDPT &= ~USB_ENDPT_EPSTALL_MASK;
        USB0->ISTAT |= USB_ISTAT_STALL_MASK;
    }

    // token interrupt
    if (istat & 1<<3) {
        uint32_t num  = (USB0->STAT >> 4) & 0x0F;
        uint32_t dir  = (USB0->STAT >> 3) & 0x01;
        uint32_t ev_odd = (USB0->STAT >> 2) & 0x01;

        // setup packet
        if ((num == 0) && (TOK_PID((EP_BDT_IDX(num, dir, ev_odd))) == SETUP_TOKEN)) {
            Data1 &= ~0x02;
            bdt[EP_BDT_IDX(0, TX, EVEN)].info &= ~BD_OWN_MASK;
            bdt[EP_BDT_IDX(0, TX, ODD)].info  &= ~BD_OWN_MASK;

            // EP0 SETUP event (SETUP data received)
            EP0setupCallback();

        } else {
            // OUT packet
            if (TOK_PID((EP_BDT_IDX(num, dir, ev_odd))) == OUT_TOKEN) {
                if (num == 0)
                    EP0out();
                else {
                    epComplete |= (1 << EP(num));
                    if ((instance->*(epCallback[EP(num) - 2]))()) {
                        epComplete &= ~(1 << EP(num));
                    }
                }
            }

            // IN packet
            if (TOK_PID((EP_BDT_IDX(num, dir, ev_odd))) == IN_TOKEN) {
                if (num == 0) {
                    EP0in();
                    if (set_addr == 1) {
                        USB0->ADDR = addr & 0x7F;
                        set_addr = 0;
                    }
                }
                else {
                    epComplete |= (1 << (EP(num) + 1));
                    if ((instance->*(epCallback[EP(num) + 1 - 2]))()) {
                        epComplete &= ~(1 << (EP(num) + 1));
                    }
                }
            }
        }

        USB0->ISTAT = USB_ISTAT_TOKDNE_MASK;
    }

    // sleep interrupt
    if (istat & 1<<4) {
        USB0->ISTAT |= USB_ISTAT_SLEEP_MASK;
    }

    // error interrupt
    if (istat & USB_ISTAT_ERROR_MASK) {
        USB0->ERRSTAT = 0xFF;
        USB0->ISTAT |= USB_ISTAT_ERROR_MASK;
    }
}


#endif
