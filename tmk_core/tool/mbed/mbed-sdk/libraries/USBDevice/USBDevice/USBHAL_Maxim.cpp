/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

#if defined(TARGET_Maxim)

#include "USBHAL.h"
#include "usb_regs.h"
#include "clkman_regs.h"

#define CONNECT_INTS    (MXC_F_USB_DEV_INTEN_BRST | MXC_F_USB_DEV_INTEN_SETUP | MXC_F_USB_DEV_INTEN_EP_IN | MXC_F_USB_DEV_INTEN_EP_OUT | MXC_F_USB_DEV_INTEN_DMA_ERR)

USBHAL *USBHAL::instance;

typedef struct {
    volatile uint32_t buf0_desc;
    volatile uint32_t buf0_address;
    volatile uint32_t buf1_desc;
    volatile uint32_t buf1_address;
} ep_buffer_t;

typedef struct {
    ep_buffer_t out_buffer;
    ep_buffer_t in_buffer;
} ep0_buffer_t;

typedef struct {
    ep0_buffer_t ep0;
    ep_buffer_t ep[MXC_USB_NUM_EP - 1];
} ep_buffer_descriptor_t;

// Static storage for endpoint buffer descriptor table. Must be 512 byte alligned for DMA.
#ifdef __IAR_SYSTEMS_ICC__
#pragma data_alignment = 512
#else
__attribute__ ((aligned (512))) 
#endif
ep_buffer_descriptor_t ep_buffer_descriptor;

// static storage for temporary data buffers. Must be 32 byte alligned.
#ifdef __IAR_SYSTEMS_ICC__
#pragma data_alignment = 4
#else
__attribute__ ((aligned (4))) 
#endif
static uint8_t aligned_buffer[NUMBER_OF_LOGICAL_ENDPOINTS][MXC_USB_MAX_PACKET];

// contorl packet state
static enum {
    CTRL_NONE = 0,
    CTRL_SETUP,
    CTRL_OUT,
    CTRL_IN,
} control_state;

USBHAL::USBHAL(void)
{
    NVIC_DisableIRQ(USB_IRQn);

    // The PLL must be enabled for USB
    MBED_ASSERT(MXC_CLKMAN->clk_config & MXC_F_CLKMAN_CLK_CONFIG_PLL_ENABLE);

    // Enable the USB clock
    MXC_CLKMAN->clk_ctrl |= MXC_F_CLKMAN_CLK_CTRL_USB_GATE_N;

    // reset the device
    MXC_USB->cn = 0;
    MXC_USB->cn = 1;
    MXC_USB->dev_inten = 0;
    MXC_USB->dev_cn = 0;
    MXC_USB->dev_cn = MXC_F_USB_DEV_CN_URST;
    MXC_USB->dev_cn = 0;

    // fill in callback arrays
    epCallback[EP0OUT] = NULL;
    epCallback[EP0IN]  = NULL;
    epCallback[EP1OUT] = &USBHAL::EP1_OUT_callback;
    epCallback[EP1IN ] = &USBHAL::EP1_IN_callback;
    epCallback[EP2OUT] = &USBHAL::EP2_OUT_callback;
    epCallback[EP2IN ] = &USBHAL::EP2_IN_callback;
    epCallback[EP3OUT] = &USBHAL::EP3_OUT_callback;
    epCallback[EP3IN ] = &USBHAL::EP3_IN_callback;
    epCallback[EP4OUT] = &USBHAL::EP4_OUT_callback;
    epCallback[EP4IN ] = &USBHAL::EP4_IN_callback;
    epCallback[EP5OUT] = &USBHAL::EP5_OUT_callback;
    epCallback[EP5IN ] = &USBHAL::EP5_IN_callback;
    epCallback[EP6OUT] = &USBHAL::EP6_OUT_callback;
    epCallback[EP6IN ] = &USBHAL::EP6_IN_callback;
    epCallback[EP7OUT] = &USBHAL::EP7_OUT_callback;
    epCallback[EP7IN ] = &USBHAL::EP7_IN_callback;

    // clear driver state
    control_state = CTRL_NONE;

    // set the descriptor location
    MXC_USB->ep_base = (uint32_t)&ep_buffer_descriptor;

    // attach IRQ handler and enable interrupts
    instance = this;
    NVIC_SetVector(USB_IRQn, (uint32_t)&_usbisr);
    NVIC_EnableIRQ(USB_IRQn);
}

USBHAL::~USBHAL(void)
{
    MXC_USB->dev_cn = MXC_F_USB_DEV_CN_URST;
    MXC_USB->dev_cn = 0;
    MXC_USB->cn = 0;
}

void USBHAL::connect(void)
{
    // enable interrupts
    MXC_USB->dev_inten |= CONNECT_INTS;

    // allow interrupts on ep0
    MXC_USB->ep[0] |= MXC_F_USB_EP_INT_EN;

    // pullup enable
    MXC_USB->dev_cn |= (MXC_F_USB_DEV_CN_CONNECT | MXC_F_USB_DEV_CN_FIFO_MODE);
}

void USBHAL::disconnect(void)
{
    // disable interrupts
    MXC_USB->dev_inten &= ~CONNECT_INTS;

    // disable pullup
    MXC_USB->dev_cn &= ~MXC_F_USB_DEV_CN_CONNECT;
}

void USBHAL::configureDevice(void)
{
    // do nothing
}

void USBHAL::unconfigureDevice(void)
{
    // reset endpoints
    for (int i = 0; i < MXC_USB_NUM_EP; i++) {
        // Disable endpoint and clear the data toggle
        MXC_USB->ep[i] &= ~MXC_F_USB_EP_DIR;
        MXC_USB->ep[i] |= MXC_F_USB_EP_DT;
    }
}

void USBHAL::setAddress(uint8_t address)
{
    // do nothing
}

void USBHAL::remoteWakeup(void)
{
    // do nothing
}

static ep_buffer_t *get_desc(uint8_t endpoint)
{
    uint8_t epnum = EP_NUM(endpoint);
    ep_buffer_t *desc;

    if (epnum == 0) {
        if (IN_EP(endpoint)) {
            desc = &ep_buffer_descriptor.ep0.in_buffer;
        } else {
            desc = &ep_buffer_descriptor.ep0.out_buffer;
        }
    } else {
        desc = &ep_buffer_descriptor.ep[epnum - 1];
    }

    return desc;
}

void USBHAL::EP0setup(uint8_t *buffer)
{
    memcpy(buffer, (void*)&MXC_USB->setup0, 8); // setup packet is fixed at 8 bytes
}

void USBHAL::EP0read(void)
{
    if (control_state == CTRL_IN) {
        // This is the status stage. ACK.
        MXC_USB->ep[0] |= MXC_F_USB_EP_ST_ACK;
        control_state = CTRL_NONE;
        return;
    }

    control_state = CTRL_OUT;

    endpointRead(EP0OUT, MAX_PACKET_SIZE_EP0);
}

void USBHAL::EP0readStage(void)
{
    // do nothing
}

uint32_t USBHAL::EP0getReadResult(uint8_t *buffer)
{
    uint32_t size;

    if (MXC_USB->out_owner & 1) {
        return 0;
    }

    // get the packet length and contents
    ep_buffer_t *desc = get_desc(EP0OUT);
    size = desc->buf0_desc;
    memcpy(buffer, aligned_buffer[0], size);

    return size;
}

void USBHAL::EP0write(uint8_t *buffer, uint32_t size)
{
    if ((size == 0) && (control_state != CTRL_IN)) {
        // This is a status stage ACK. Handle in hardware.
        MXC_USB->ep[0] |= MXC_F_USB_EP_ST_ACK;
        control_state = CTRL_NONE;
        return;
    }

    control_state = CTRL_IN;

    endpointWrite(EP0IN, buffer, size);
}

void USBHAL::EP0stall(void)
{
    stallEndpoint(0);
}

EP_STATUS USBHAL::endpointRead(uint8_t endpoint, uint32_t maximumSize)
{
    uint8_t epnum = EP_NUM(endpoint);

    if ((endpoint >= NUMBER_OF_PHYSICAL_ENDPOINTS) || IN_EP(endpoint)) {
        return EP_INVALID;
    }

    if (maximumSize > MXC_USB_MAX_PACKET) {
        return EP_INVALID;
    }
    
    uint32_t mask = (1 << epnum);
    if (MXC_USB->out_owner & mask) {
        return EP_INVALID;
    }

    ep_buffer_t *desc = get_desc(endpoint);
    desc->buf0_desc = maximumSize;
    desc->buf0_address = (uint32_t)aligned_buffer[epnum];

    MXC_USB->out_owner = mask;

    return EP_PENDING;
}

EP_STATUS USBHAL::endpointReadResult(uint8_t endpoint, uint8_t *data, uint32_t *bytesRead)
{
    if ((endpoint >= NUMBER_OF_PHYSICAL_ENDPOINTS) || IN_EP(endpoint)) {
        return EP_INVALID;
    }

    uint32_t mask = (1 << EP_NUM(endpoint));
    if (MXC_USB->out_owner & mask) {
        return EP_PENDING;
    }

    // get the packet length and contents
    ep_buffer_t *desc = get_desc(endpoint);
    *bytesRead = desc->buf0_desc;
    memcpy(data, aligned_buffer[EP_NUM(endpoint)], *bytesRead);

    return EP_COMPLETED;
}

EP_STATUS USBHAL::endpointWrite(uint8_t endpoint, uint8_t *data, uint32_t size)
{
    uint8_t epnum = EP_NUM(endpoint);

    if ((endpoint >= NUMBER_OF_PHYSICAL_ENDPOINTS) || OUT_EP(endpoint)) {
        return EP_INVALID;
    }

    if (size > MXC_USB_MAX_PACKET) {
        return EP_INVALID;
    }

    uint32_t mask = (1 << epnum);
    if (MXC_USB->in_owner & mask) {
        return EP_INVALID;
    }

    memcpy(aligned_buffer[epnum], data, size);

    ep_buffer_t *desc = get_desc(endpoint);
    desc->buf0_desc = size;
    desc->buf0_address = (uint32_t)aligned_buffer[epnum];

    // start the DMA
    MXC_USB->in_owner = mask;

    return EP_PENDING;
}

EP_STATUS USBHAL::endpointWriteResult(uint8_t endpoint)
{
    uint32_t mask = (1 << EP_NUM(endpoint));
    if (MXC_USB->in_owner & mask) {
        return EP_PENDING;
    }

    return EP_COMPLETED;
}

void USBHAL::stallEndpoint(uint8_t endpoint)
{
    uint8_t epnum = EP_NUM(endpoint);

    if (epnum == 0) {
        MXC_USB->ep[epnum] |= MXC_F_USB_EP_ST_STALL;
    }

    MXC_USB->ep[epnum] |= MXC_F_USB_EP_STALL;
}

void USBHAL::unstallEndpoint(uint8_t endpoint)
{
    MXC_USB->ep[EP_NUM(endpoint)] &= ~MXC_F_USB_EP_STALL;
}

bool USBHAL::realiseEndpoint(uint8_t endpoint, uint32_t maxPacket, uint32_t options)
{
    uint8_t epnum = EP_NUM(endpoint);
    uint32_t ep_ctrl;

    if (epnum >= NUMBER_OF_PHYSICAL_ENDPOINTS) {
        return false;
    }

    if (IN_EP(endpoint)) {
        ep_ctrl = (MXC_V_USB_EP_DIR_IN << MXC_F_USB_EP_DIR_POS);
    } else {
        ep_ctrl = (MXC_S_USB_EP_DIR_OUT << MXC_F_USB_EP_DIR_POS);
    }

    ep_ctrl |= (MXC_F_USB_EP_DT | MXC_F_USB_EP_INT_EN);

    MXC_USB->ep[epnum] = ep_ctrl;

    return true;
}

bool USBHAL::getEndpointStallState(unsigned char endpoint)
{
    return !!(MXC_USB->ep[endpoint] & MXC_F_USB_EP_STALL);
}

void USBHAL::_usbisr(void)
{
    instance->usbisr();
}

void USBHAL::usbisr(void)
{
    // get and clear irqs
    uint32_t irq_flags = MXC_USB->dev_intfl;
    MXC_USB->dev_intfl = irq_flags;

    // process only enabled interrupts
    irq_flags &= MXC_USB->dev_inten;

    // suspend 
    if (irq_flags & MXC_F_USB_DEV_INTFL_SUSP) {
        suspendStateChanged(1);
    }

    // bus reset
    if (irq_flags & MXC_F_USB_DEV_INTFL_BRST) {

        // reset endpoints
        for (int i = 0; i < MXC_USB_NUM_EP; i++) {
            // Disable endpoint and clear the data toggle
            MXC_USB->ep[i] &= ~MXC_F_USB_EP_DIR;
            MXC_USB->ep[i] |= MXC_F_USB_EP_DT;
        }

        // clear driver state
        control_state = CTRL_NONE;

        busReset();

        // no need to process events after reset
        return;
    }

    // Setup packet
    if (irq_flags & MXC_F_USB_DEV_INTFL_SETUP) {
        control_state = CTRL_SETUP;
        EP0setupCallback();
    }

    // IN packets
    if (irq_flags & MXC_F_USB_DEV_INTFL_EP_IN) {
        // get and clear IN irqs
        uint32_t in_irqs = MXC_USB->in_int;
        MXC_USB->in_int = in_irqs;

        if (in_irqs & 1) {
            EP0in();
        }

        for (uint8_t epnum = 1; epnum < NUMBER_OF_LOGICAL_ENDPOINTS; epnum++) {
            uint32_t irq_mask = (1 << epnum);
            if (in_irqs & irq_mask) {
                uint8_t endpoint = (epnum << 1) | DIR_IN;
                (instance->*(epCallback[endpoint]))();
            }
        }
    }

    // OUT packets
    if (irq_flags & MXC_F_USB_DEV_INTFL_EP_OUT) {
        // get and clear OUT irqs
        uint32_t out_irqs = MXC_USB->out_int;
        MXC_USB->out_int = out_irqs;

        if (out_irqs & 1) {
            EP0out();
        }

        for (uint8_t epnum = 1; epnum < NUMBER_OF_LOGICAL_ENDPOINTS; epnum++) {
            uint32_t irq_mask = (1 << epnum);
            if (out_irqs & irq_mask) {
                uint8_t endpoint = (epnum << 1) | DIR_OUT;
                (instance->*(epCallback[endpoint]))();
            }
        }
    }
}

#endif
