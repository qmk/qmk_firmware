/**
 * \file
 *
 * \brief SAM USB Driver.
 *
 * Copyright (C) 2014-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#define DEVICE_MODE_ONLY true
#define SAMD11 DEVICE_MODE_ONLY

#ifndef ARM_MATH_CM4
  #define ARM_MATH_CM4
#endif

#include "compiler.h"
#undef LITTLE_ENDIAN  //redefined in samd51j18a.h
#include "samd51j18a.h"
#include <stdbool.h>
#include <string.h>
#include "arm_math.h"
#include "status_codes.h"
#include "usb.h"

/** Fields definition from a LPM TOKEN  */
#define  USB_LPM_ATTRIBUT_BLINKSTATE_MASK      (0xF << 0)
#define  USB_LPM_ATTRIBUT_HIRD_MASK            (0xF << 4)
#define  USB_LPM_ATTRIBUT_REMOTEWAKE_MASK      (1 << 8)
#define  USB_LPM_ATTRIBUT_BLINKSTATE(value)    ((value & 0xF) << 0)
#define  USB_LPM_ATTRIBUT_HIRD(value)          ((value & 0xF) << 4)
#define  USB_LPM_ATTRIBUT_REMOTEWAKE(value)    ((value & 1) << 8)
#define  USB_LPM_ATTRIBUT_BLINKSTATE_L1        USB_LPM_ATTRIBUT_BLINKSTATE(1)

/**
 * \brief Mask selecting the index part of an endpoint address
 */
#define  USB_EP_ADDR_MASK     0x0f

/**
 * \brief Endpoint transfer direction is IN
 */
#define  USB_EP_DIR_IN        0x80

/**
 * \brief Endpoint transfer direction is OUT
 */
#define  USB_EP_DIR_OUT       0x00

/**
 * \name USB SRAM data containing pipe descriptor table
 * The content of the USB SRAM can be :
 * - modified by USB hardware interface to update pipe status.
 *   Thereby, it is read by software.
 * - modified by USB software to control pipe.
 *   Thereby, it is read by hardware.
 * This data section is volatile.
 *
 * @{
 */
COMPILER_PACK_SET(1)
COMPILER_WORD_ALIGNED
union {
    UsbDeviceDescriptor usb_endpoint_table[USB_EPT_NUM];
} usb_descriptor_table;
COMPILER_PACK_RESET()
/** @} */

/**
 * \brief Local USB module instance
 */
static struct usb_module *_usb_instances;

/* Device LPM callback variable */
static uint32_t device_callback_lpm_wakeup_enable;

/**
 * \brief Device endpoint callback parameter variable, used to transfer info to UDD wrapper layer
 */
static struct usb_endpoint_callback_parameter ep_callback_para;

/**
 * \internal USB Device IRQ Mask Bits Map
 */
static const uint16_t _usb_device_irq_bits[USB_DEVICE_CALLBACK_N] = {
    USB_DEVICE_INTFLAG_SOF,
    USB_DEVICE_INTFLAG_EORST,
    USB_DEVICE_INTFLAG_WAKEUP | USB_DEVICE_INTFLAG_EORSM | USB_DEVICE_INTFLAG_UPRSM,
    USB_DEVICE_INTFLAG_RAMACER,
    USB_DEVICE_INTFLAG_SUSPEND,
    USB_DEVICE_INTFLAG_LPMNYET,
    USB_DEVICE_INTFLAG_LPMSUSP,
};

/**
 * \internal USB Device IRQ Mask Bits Map
 */
static const uint8_t _usb_endpoint_irq_bits[USB_DEVICE_EP_CALLBACK_N] = {
    USB_DEVICE_EPINTFLAG_TRCPT_Msk,
    USB_DEVICE_EPINTFLAG_TRFAIL_Msk,
    USB_DEVICE_EPINTFLAG_RXSTP,
    USB_DEVICE_EPINTFLAG_STALL_Msk
};

/**
 * \brief Registers a USB device callback
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref usb_device_enable_callback,
 * in order for the interrupt handler to call it when the conditions for the
 * callback type is met.
 *
 * \param[in]     module_inst   Pointer to USB software instance struct
 * \param[in]     callback_type Callback type given by an enum
 * \param[in]     callback_func Pointer to callback function
 *
 * \return Status of the registration operation.
 * \retval STATUS_OK    The callback was registered successfully.
 */
enum status_code usb_device_register_callback(struct usb_module *module_inst,
        enum usb_device_callback callback_type,
        usb_device_callback_t callback_func)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(callback_func);

    /* Register callback function */
    module_inst->device_callback[callback_type] = callback_func;

    /* Set the bit corresponding to the callback_type */
    module_inst->device_registered_callback_mask |= _usb_device_irq_bits[callback_type];

    return STATUS_OK;
}

/**
 * \brief Unregisters a USB device callback
 *
 * Unregisters an asynchronous callback implemented by the user. Removing it
 * from the internal callback registration table.
 *
 * \param[in]     module_inst   Pointer to USB software instance struct
 * \param[in]     callback_type Callback type given by an enum
 *
 * \return Status of the de-registration operation.
 * \retval STATUS_OK    The callback was unregistered successfully.
 */
enum status_code usb_device_unregister_callback(struct usb_module *module_inst,
        enum usb_device_callback callback_type)
{
    /* Sanity check arguments */
    Assert(module_inst);

    /* Unregister callback function */
    module_inst->device_callback[callback_type] = NULL;

    /* Clear the bit corresponding to the callback_type */
    module_inst->device_registered_callback_mask &= ~_usb_device_irq_bits[callback_type];

    return STATUS_OK;
}

/**
 * \brief Enables USB device callback generation for a given type.
 *
 * Enables asynchronous callbacks for a given logical type.
 * This must be called before USB device generate callback events.
 *
 * \param[in]     module_inst   Pointer to USB software instance struct
 * \param[in]     callback_type Callback type given by an enum
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK    The callback was enabled successfully.
 */
enum status_code usb_device_enable_callback(struct usb_module *module_inst,
        enum usb_device_callback callback_type)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);

    /* clear related flag */
    module_inst->hw->DEVICE.INTFLAG.reg = _usb_device_irq_bits[callback_type];

    /* Enable callback */
    module_inst->device_enabled_callback_mask |= _usb_device_irq_bits[callback_type];

    module_inst->hw->DEVICE.INTENSET.reg = _usb_device_irq_bits[callback_type];

    return STATUS_OK;
}

/**
 * \brief Disables USB device callback generation for a given type.
 *
 * Disables asynchronous callbacks for a given logical type.
 *
 * \param[in]     module_inst   Pointer to USB software instance struct
 * \param[in]     callback_type Callback type given by an enum
 *
 * \return Status of the callback disable operation.
 * \retval STATUS_OK    The callback was disabled successfully.
 */
enum status_code usb_device_disable_callback(struct usb_module *module_inst,
        enum usb_device_callback callback_type)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);

    /* Disable callback */
    module_inst->device_enabled_callback_mask &= ~_usb_device_irq_bits[callback_type];

    module_inst->hw->DEVICE.INTENCLR.reg = _usb_device_irq_bits[callback_type];

    return STATUS_OK;
}

/**
 * \brief Registers a USB device endpoint callback
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref usb_device_endpoint_enable_callback,
 * in order for the interrupt handler to call it when the conditions for the
 * callback type is met.
 *
 * \param[in]     module_inst   Pointer to USB software instance struct
 * \param[in]     ep_num        Endpoint to configure
 * \param[in]     callback_type Callback type given by an enum
 * \param[in]     callback_func Pointer to callback function
 *
 * \return Status of the registration operation.
 * \retval STATUS_OK    The callback was registered successfully.
 */
enum status_code usb_device_endpoint_register_callback(
        struct usb_module *module_inst, uint8_t ep_num,
        enum usb_device_endpoint_callback callback_type,
        usb_device_endpoint_callback_t callback_func)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(ep_num < USB_EPT_NUM);
    Assert(callback_func);

    /* Register callback function */
    module_inst->device_endpoint_callback[ep_num][callback_type] = callback_func;

    /* Set the bit corresponding to the callback_type */
    module_inst->device_endpoint_registered_callback_mask[ep_num] |= _usb_endpoint_irq_bits[callback_type];

    return STATUS_OK;
}

/**
 * \brief Unregisters a USB device endpoint callback
 *
 * Unregisters an callback implemented by the user. Removing it
 * from the internal callback registration table.
 *
 * \param[in]     module_inst   Pointer to USB software instance struct
 * \param[in]     ep_num        Endpoint to configure
 * \param[in]     callback_type Callback type given by an enum
 *
 * \return Status of the de-registration operation.
 * \retval STATUS_OK    The callback was unregistered successfully.
 */
enum status_code usb_device_endpoint_unregister_callback(
        struct usb_module *module_inst, uint8_t ep_num,
        enum usb_device_endpoint_callback callback_type)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(ep_num < USB_EPT_NUM);

    /* Unregister callback function */
    module_inst->device_endpoint_callback[ep_num][callback_type] = NULL;

    /* Clear the bit corresponding to the callback_type */
    module_inst->device_endpoint_registered_callback_mask[ep_num] &= ~_usb_endpoint_irq_bits[callback_type];

    return STATUS_OK;
}

/**
 * \brief Enables USB device endpoint callback generation for a given type.
 *
 * Enables callbacks for a given logical type.
 * This must be called before USB device pipe generate callback events.
 *
 * \param[in]     module_inst   Pointer to USB software instance struct
 * \param[in]     ep            Endpoint to configure
 * \param[in]     callback_type Callback type given by an enum
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK    The callback was enabled successfully.
 */
enum status_code usb_device_endpoint_enable_callback(
        struct usb_module *module_inst, uint8_t ep,
        enum usb_device_endpoint_callback callback_type)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);

    uint8_t ep_num = ep & USB_EP_ADDR_MASK;
    Assert(ep_num < USB_EPT_NUM);

    /* Enable callback */
    module_inst->device_endpoint_enabled_callback_mask[ep_num] |= _usb_endpoint_irq_bits[callback_type];

    if (callback_type == USB_DEVICE_ENDPOINT_CALLBACK_TRCPT) {
        if (ep_num == 0) { // control endpoint
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRCPT0 | USB_DEVICE_EPINTENSET_TRCPT1;
        } else if (ep & USB_EP_DIR_IN) {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRCPT1;
        } else {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRCPT0;
        }
    }

    if (callback_type == USB_DEVICE_ENDPOINT_CALLBACK_TRFAIL) {
        if (ep_num == 0) { // control endpoint
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRFAIL0 | USB_DEVICE_EPINTENSET_TRFAIL1;
        } else if (ep & USB_EP_DIR_IN) {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRFAIL1;
        } else {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRFAIL0;
        }
    }

    if (callback_type == USB_DEVICE_ENDPOINT_CALLBACK_RXSTP) {
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENSET.reg = USB_DEVICE_EPINTENSET_RXSTP;
    }

    if (callback_type == USB_DEVICE_ENDPOINT_CALLBACK_STALL) {
        if (ep & USB_EP_DIR_IN) {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENSET.reg = USB_DEVICE_EPINTENSET_STALL1;
        } else {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENSET.reg = USB_DEVICE_EPINTENSET_STALL0;
        }
    }

    return STATUS_OK;
}

/**
 * \brief Disables USB device endpoint callback generation for a given type.
 *
 * Disables callbacks for a given logical type.
 *
 * \param[in]     module_inst   Pointer to USB software instance struct
 * \param[in]     ep            Endpoint to configure
 * \param[in]     callback_type Callback type given by an enum
 *
 * \return Status of the callback disable operation.
 * \retval STATUS_OK    The callback was disabled successfully.
 */
enum status_code usb_device_endpoint_disable_callback(
        struct usb_module *module_inst, uint8_t ep,
        enum usb_device_endpoint_callback callback_type)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);

    uint8_t ep_num = ep & USB_EP_ADDR_MASK;
    Assert(ep_num < USB_EPT_NUM);

    /* Enable callback */
    module_inst->device_endpoint_enabled_callback_mask[ep_num] &= ~_usb_endpoint_irq_bits[callback_type];

    if (callback_type == USB_DEVICE_ENDPOINT_CALLBACK_TRCPT) {
        if (ep_num == 0) { // control endpoint
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENCLR.reg =  USB_DEVICE_EPINTENCLR_TRCPT0 | USB_DEVICE_EPINTENCLR_TRCPT1;
        } else if (ep & USB_EP_DIR_IN) {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENCLR.reg =  USB_DEVICE_EPINTENCLR_TRCPT1;
        } else {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENCLR.reg =  USB_DEVICE_EPINTENCLR_TRCPT0;
        }
    }

    if (callback_type == USB_DEVICE_ENDPOINT_CALLBACK_TRFAIL) {
        if (ep_num == 0) { // control endpoint
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENCLR.reg = USB_DEVICE_EPINTENCLR_TRFAIL0 | USB_DEVICE_EPINTENCLR_TRFAIL1;
        } else if (ep & USB_EP_DIR_IN) {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENCLR.reg = USB_DEVICE_EPINTENCLR_TRFAIL1;
        } else {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENCLR.reg = USB_DEVICE_EPINTENCLR_TRFAIL0;
        }
    }

    if (callback_type == USB_DEVICE_ENDPOINT_CALLBACK_RXSTP) {
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENCLR.reg = USB_DEVICE_EPINTENCLR_RXSTP;
    }

    if (callback_type == USB_DEVICE_ENDPOINT_CALLBACK_STALL) {
        if (ep & USB_EP_DIR_IN) {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENCLR.reg = USB_DEVICE_EPINTENCLR_STALL1;
        } else {
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTENCLR.reg = USB_DEVICE_EPINTENCLR_STALL0;
        }
    }

    return STATUS_OK;
}

/**
 * \brief Initializes an USB device endpoint configuration structure to defaults.
 *
 * Initializes a given USB device endpoint configuration structure to a
 * set of known default values. This function should be called on all new
 * instances of these configuration structures before being modified by the
 * user application.
 *
 * The default configuration is as follows:
 * \li endpoint address is 0
 * \li endpoint size is 8 bytes
 * \li auto_zlp is false
 * \li endpoint type is control
 *
 * \param[out] ep_config  Configuration structure to initialize to default values
 */
void usb_device_endpoint_get_config_defaults(struct usb_device_endpoint_config *ep_config)
{
    /* Sanity check arguments */
    Assert(ep_config);

    /* Write default config to config struct */
    ep_config->ep_address = 0;
    ep_config->ep_size = USB_ENDPOINT_8_BYTE;
    ep_config->auto_zlp = false;
    ep_config->ep_type = USB_DEVICE_ENDPOINT_TYPE_CONTROL;
}

/**
 * \brief Writes an USB device endpoint configuration to the hardware module.
 *
 * Writes out a given configuration of an USB device endpoint
 * configuration to the hardware module. If the pipe is already configured,
 * the new configuration will replace the existing one.
 *
 * \param[in] module_inst    Pointer to USB software instance struct
 * \param[in] ep_config      Configuration settings for the endpoint
 *
 * \return Status of the device endpoint configuration operation
 * \retval STATUS_OK         The device endpoint was configured successfully
 * \retval STATUS_ERR_DENIED The endpoint address is already configured
 */
enum status_code usb_device_endpoint_set_config(struct usb_module *module_inst,
        struct usb_device_endpoint_config *ep_config)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(ep_config);

    uint8_t ep_num = ep_config->ep_address & USB_EP_ADDR_MASK;
    uint8_t ep_bank = (ep_config->ep_address & USB_EP_DIR_IN) ? 1 : 0;

    switch (ep_config->ep_type) {
        case USB_DEVICE_ENDPOINT_TYPE_DISABLE:
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg = USB_DEVICE_EPCFG_EPTYPE0(0) |  USB_DEVICE_EPCFG_EPTYPE1(0);
            return STATUS_OK;

        case USB_DEVICE_ENDPOINT_TYPE_CONTROL:
            if ((module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg & USB_DEVICE_EPCFG_EPTYPE0_Msk) == 0 && \
                (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg & USB_DEVICE_EPCFG_EPTYPE1_Msk) == 0) {
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg = USB_DEVICE_EPCFG_EPTYPE0(1) | USB_DEVICE_EPCFG_EPTYPE1(1);
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK0RDY;
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK1RDY;
            } else {
                return STATUS_ERR_DENIED;
            }
            if (true == ep_config->auto_zlp) {
                usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[0].PCKSIZE.reg |= USB_DEVICE_PCKSIZE_AUTO_ZLP;
                usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[1].PCKSIZE.reg |= USB_DEVICE_PCKSIZE_AUTO_ZLP;
            } else {
                usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[0].PCKSIZE.reg &= ~USB_DEVICE_PCKSIZE_AUTO_ZLP;
                usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[1].PCKSIZE.reg &= ~USB_DEVICE_PCKSIZE_AUTO_ZLP;
            }
            usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[0].PCKSIZE.bit.SIZE = ep_config->ep_size;
            usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[1].PCKSIZE.bit.SIZE = ep_config->ep_size;
            return STATUS_OK;

        case USB_DEVICE_ENDPOINT_TYPE_ISOCHRONOUS:
            if (ep_bank) {
                if ((module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg & USB_DEVICE_EPCFG_EPTYPE1_Msk) == 0){
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg |= USB_DEVICE_EPCFG_EPTYPE1(2);
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK1RDY;
                } else {
                    return STATUS_ERR_DENIED;
                }
            } else {
                if ((module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg & USB_DEVICE_EPCFG_EPTYPE0_Msk) == 0){
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg |= USB_DEVICE_EPCFG_EPTYPE0(2);
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK0RDY;
                } else {
                    return STATUS_ERR_DENIED;
                }
            }
            break;

        case USB_DEVICE_ENDPOINT_TYPE_BULK:
            if (ep_bank) {
                if ((module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg & USB_DEVICE_EPCFG_EPTYPE1_Msk) == 0){
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg |= USB_DEVICE_EPCFG_EPTYPE1(3);
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK1RDY;
                } else {
                    return STATUS_ERR_DENIED;
                }
            } else {
                if ((module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg & USB_DEVICE_EPCFG_EPTYPE0_Msk) == 0){
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg |= USB_DEVICE_EPCFG_EPTYPE0(3);
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK0RDY;
                } else {
                    return STATUS_ERR_DENIED;
                }
            }
            break;

        case USB_DEVICE_ENDPOINT_TYPE_INTERRUPT:
            if (ep_bank) {
                if ((module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg & USB_DEVICE_EPCFG_EPTYPE1_Msk) == 0){
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg |= USB_DEVICE_EPCFG_EPTYPE1(4);
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK1RDY;
                } else {
                    return STATUS_ERR_DENIED;
                }
            } else {
                if ((module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg & USB_DEVICE_EPCFG_EPTYPE0_Msk) == 0){
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.reg |= USB_DEVICE_EPCFG_EPTYPE0(4);
                    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK0RDY;
                } else {
                    return STATUS_ERR_DENIED;
                }
            }
            break;

        default:
            break;
    }

    usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[ep_bank].PCKSIZE.bit.SIZE = ep_config->ep_size;

    if (true == ep_config->auto_zlp) {
        usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[ep_bank].PCKSIZE.reg |= USB_DEVICE_PCKSIZE_AUTO_ZLP;
        } else {
        usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[ep_bank].PCKSIZE.reg &= ~USB_DEVICE_PCKSIZE_AUTO_ZLP;
    }

    return STATUS_OK;
}

/**
 * \brief Check if current endpoint is configured
 *
 * \param module_inst   Pointer to USB software instance struct
 * \param ep            Endpoint address (direction & number)
 *
 * \return \c true if endpoint is configured and ready to use
 */
bool usb_device_endpoint_is_configured(struct usb_module *module_inst, uint8_t ep)
{
    uint8_t ep_num = ep & USB_EP_ADDR_MASK;
    uint8_t flag;

    if (ep & USB_EP_DIR_IN) {
        flag = (uint8_t)(module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.bit.EPTYPE1);
    } else {
        flag = (uint8_t)(module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.bit.EPTYPE0);
    }
    return ((enum usb_device_endpoint_type)(flag) != USB_DEVICE_ENDPOINT_TYPE_DISABLE);
}


/**
 * \brief Abort ongoing job on the endpoint
 *
 * \param module_inst Pointer to USB software instance struct
 * \param ep          Endpoint address
 */
void usb_device_endpoint_abort_job(struct usb_module *module_inst, uint8_t ep)
{
    uint8_t ep_num;
    ep_num = ep & USB_EP_ADDR_MASK;

    // Stop transfer
    if (ep & USB_EP_DIR_IN) {
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK1RDY;
        // Eventually ack a transfer occur during abort
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
    } else {
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK0RDY;
        // Eventually ack a transfer occur during abort
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT0;
    }
}

/**
 * \brief Check if endpoint is halted
 *
 * \param module_inst Pointer to USB software instance struct
 * \param ep          Endpoint address
 *
 * \return \c true if the endpoint is halted
 */
bool usb_device_endpoint_is_halted(struct usb_module *module_inst, uint8_t ep)
{
    uint8_t ep_num = ep & USB_EP_ADDR_MASK;

    if (ep & USB_EP_DIR_IN) {
        return (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUS.reg & USB_DEVICE_EPSTATUSSET_STALLRQ1);
    } else {
        return (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUS.reg & USB_DEVICE_EPSTATUSSET_STALLRQ0);
    }
}

/**
 * \brief Halt the endpoint (send STALL)
 *
 * \param module_inst Pointer to USB software instance struct
 * \param ep          Endpoint address
 */
void usb_device_endpoint_set_halt(struct usb_module *module_inst, uint8_t ep)
{
    uint8_t ep_num = ep & USB_EP_ADDR_MASK;

    // Stall endpoint
    if (ep & USB_EP_DIR_IN) {
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_STALLRQ1;
    } else {
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_STALLRQ0;
    }
}

/**
 * \brief Clear endpoint halt state
 *
 * \param module_inst Pointer to USB software instance struct
 * \param ep          Endpoint address
 */
void usb_device_endpoint_clear_halt(struct usb_module *module_inst, uint8_t ep)
{
    uint8_t ep_num = ep & USB_EP_ADDR_MASK;

    if (ep & USB_EP_DIR_IN) {
        if (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUS.reg & USB_DEVICE_EPSTATUSSET_STALLRQ1) {
            // Remove stall request
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_STALLRQ1;
            if (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_STALL1) {
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL1;
                // The Stall has occurred, then reset data toggle
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSSET_DTGLIN;
            }
        }
    } else {
        if (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUS.reg & USB_DEVICE_EPSTATUSSET_STALLRQ0) {
            // Remove stall request
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_STALLRQ0;
            if (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_STALL0) {
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL0;
                // The Stall has occurred, then reset data toggle
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSSET_DTGLOUT;
            }
        }
    }
}

/**
 * \brief Start write buffer job on a endpoint
 *
 * \param module_inst Pointer to USB module instance
 * \param ep_num      Endpoint number
 * \param pbuf        Pointer to buffer
 * \param buf_size    Size of buffer
 *
 * \return Status of procedure
 * \retval STATUS_OK Job started successfully
 * \retval STATUS_ERR_DENIED Endpoint is not ready
 */
enum status_code usb_device_endpoint_write_buffer_job(struct usb_module *module_inst,uint8_t ep_num,
        uint8_t* pbuf, uint32_t buf_size)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);
    Assert(ep_num < USB_EPT_NUM);

    uint8_t flag;
    flag = (uint8_t)(module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.bit.EPTYPE1);
    if ((enum usb_device_endpoint_type)(flag) == USB_DEVICE_ENDPOINT_TYPE_DISABLE) {
        return STATUS_ERR_DENIED;
    };

    /* get endpoint configuration from setting register */
    usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[1].ADDR.reg = (uint32_t)pbuf;
    usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[1].PCKSIZE.bit.MULTI_PACKET_SIZE = 0;
    usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[1].PCKSIZE.bit.BYTE_COUNT = buf_size;
    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK1RDY;

    return STATUS_OK;
}

/**
 * \brief Start read buffer job on a endpoint
 *
 * \param module_inst Pointer to USB module instance
 * \param ep_num      Endpoint number
 * \param pbuf        Pointer to buffer
 * \param buf_size    Size of buffer
 *
 * \return Status of procedure
 * \retval STATUS_OK Job started successfully
 * \retval STATUS_ERR_DENIED Endpoint is not ready
 */
enum status_code usb_device_endpoint_read_buffer_job(struct usb_module *module_inst,uint8_t ep_num,
        uint8_t* pbuf, uint32_t buf_size)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);
    Assert(ep_num < USB_EPT_NUM);

    uint8_t flag;
    flag = (uint8_t)(module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPCFG.bit.EPTYPE0);
    if ((enum usb_device_endpoint_type)(flag) == USB_DEVICE_ENDPOINT_TYPE_DISABLE) {
        return STATUS_ERR_DENIED;
    };

    /* get endpoint configuration from setting register */
    usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[0].ADDR.reg = (uint32_t)pbuf;
    usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[0].PCKSIZE.bit.MULTI_PACKET_SIZE = buf_size;
    usb_descriptor_table.usb_endpoint_table[ep_num].DeviceDescBank[0].PCKSIZE.bit.BYTE_COUNT = 0;
    module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK0RDY;

    return STATUS_OK;
}

/**
 * \brief Start setup packet read job on a endpoint
 *
 * \param module_inst Pointer to USB device module instance
 * \param pbuf        Pointer to buffer
 *
 * \return Status of procedure
 * \retval STATUS_OK Job started successfully
 * \retval STATUS_ERR_DENIED Endpoint is not ready
 */
enum status_code usb_device_endpoint_setup_buffer_job(struct usb_module *module_inst,
        uint8_t* pbuf)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);

    /* get endpoint configuration from setting register */
    usb_descriptor_table.usb_endpoint_table[0].DeviceDescBank[0].ADDR.reg = (uint32_t)pbuf;
    usb_descriptor_table.usb_endpoint_table[0].DeviceDescBank[0].PCKSIZE.bit.MULTI_PACKET_SIZE = 8;
    usb_descriptor_table.usb_endpoint_table[0].DeviceDescBank[0].PCKSIZE.bit.BYTE_COUNT = 0;
    module_inst->hw->DEVICE.DeviceEndpoint[0].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK0RDY;

    return STATUS_OK;
}

static void _usb_device_interrupt_handler(void)
{
    uint16_t ep_inst;
    uint16_t flags, flags_run;
    ep_inst = _usb_instances->hw->DEVICE.EPINTSMRY.reg;

    /* device interrupt */
    if (0 == ep_inst) {
        int i;

        /* get interrupt flags */
        flags = _usb_instances->hw->DEVICE.INTFLAG.reg;
        flags_run = flags &
                _usb_instances->device_enabled_callback_mask &
                _usb_instances->device_registered_callback_mask;

        for (i = 0; i < USB_DEVICE_CALLBACK_N; i ++) {
            if (flags & _usb_device_irq_bits[i]) {
                _usb_instances->hw->DEVICE.INTFLAG.reg =
                        _usb_device_irq_bits[i];
            }
            if (flags_run & _usb_device_irq_bits[i]) {
                if (i == USB_DEVICE_CALLBACK_LPMSUSP) {
                    device_callback_lpm_wakeup_enable =
                            usb_descriptor_table.usb_endpoint_table[0].DeviceDescBank[0].EXTREG.bit.VARIABLE
                            & USB_LPM_ATTRIBUT_REMOTEWAKE_MASK;
                }
                (_usb_instances->device_callback[i])(_usb_instances, &device_callback_lpm_wakeup_enable);
            }
        }

    } else {
        /* endpoint interrupt */

        for (uint8_t i = 0; i < USB_EPT_NUM; i++) {

            if (ep_inst & (1 << i)) {
                flags = _usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg;
                flags_run = flags &
                        _usb_instances->device_endpoint_enabled_callback_mask[i] &
                        _usb_instances->device_endpoint_registered_callback_mask[i];

                // endpoint transfer stall interrupt
                if (flags & USB_DEVICE_EPINTFLAG_STALL_Msk) {
                    if (_usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_STALL1) {
                        _usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL1;
                        ep_callback_para.endpoint_address = USB_EP_DIR_IN | i;
                    } else if (_usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_STALL0) {
                        _usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL0;
                        ep_callback_para.endpoint_address = USB_EP_DIR_OUT | i;
                    }

                    if (flags_run & USB_DEVICE_EPINTFLAG_STALL_Msk) {
                        (_usb_instances->device_endpoint_callback[i][USB_DEVICE_ENDPOINT_CALLBACK_STALL])(_usb_instances,&ep_callback_para);
                    }
                    return;
                }

                // endpoint received setup interrupt
                if (flags & USB_DEVICE_EPINTFLAG_RXSTP) {
                    _usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_RXSTP;
                    if(_usb_instances->device_endpoint_enabled_callback_mask[i] & _usb_endpoint_irq_bits[USB_DEVICE_ENDPOINT_CALLBACK_RXSTP]) {
                        ep_callback_para.received_bytes = (uint16_t)(usb_descriptor_table.usb_endpoint_table[i].DeviceDescBank[0].PCKSIZE.bit.BYTE_COUNT);
                        (_usb_instances->device_endpoint_callback[i][USB_DEVICE_ENDPOINT_CALLBACK_RXSTP])(_usb_instances,&ep_callback_para);
                    }
                    return;
                }

                // endpoint transfer complete interrupt
                if (flags & USB_DEVICE_EPINTFLAG_TRCPT_Msk) {
                    if (_usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_TRCPT1) {
                        _usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
                        ep_callback_para.endpoint_address = USB_EP_DIR_IN | i;
                        ep_callback_para.sent_bytes = (uint16_t)(usb_descriptor_table.usb_endpoint_table[i].DeviceDescBank[1].PCKSIZE.bit.BYTE_COUNT);

                    } else if (_usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_TRCPT0) {
                        _usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT0;
                        ep_callback_para.endpoint_address = USB_EP_DIR_OUT | i;
                        ep_callback_para.received_bytes = (uint16_t)(usb_descriptor_table.usb_endpoint_table[i].DeviceDescBank[0].PCKSIZE.bit.BYTE_COUNT);
                        ep_callback_para.out_buffer_size = (uint16_t)(usb_descriptor_table.usb_endpoint_table[i].DeviceDescBank[0].PCKSIZE.bit.MULTI_PACKET_SIZE);
                    }
                    if(flags_run & USB_DEVICE_EPINTFLAG_TRCPT_Msk) {
                        (_usb_instances->device_endpoint_callback[i][USB_DEVICE_ENDPOINT_CALLBACK_TRCPT])(_usb_instances,&ep_callback_para);
                    }
                    return;
                }

                // endpoint transfer fail interrupt
                if (flags & USB_DEVICE_EPINTFLAG_TRFAIL_Msk) {
                    if (_usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_TRFAIL1) {
                        _usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRFAIL1;
                        if (usb_descriptor_table.usb_endpoint_table[i].DeviceDescBank[1].STATUS_BK.reg & USB_DEVICE_STATUS_BK_ERRORFLOW) {
                            usb_descriptor_table.usb_endpoint_table[i].DeviceDescBank[1].STATUS_BK.reg &= ~USB_DEVICE_STATUS_BK_ERRORFLOW;
                        }
                        ep_callback_para.endpoint_address = USB_EP_DIR_IN | i;
                        if (_usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_TRCPT1) {
                            return;
                        }
                    } else if(_usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_TRFAIL0) {
                        _usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRFAIL0;
                        if (usb_descriptor_table.usb_endpoint_table[i].DeviceDescBank[0].STATUS_BK.reg & USB_DEVICE_STATUS_BK_ERRORFLOW) {
                            usb_descriptor_table.usb_endpoint_table[i].DeviceDescBank[0].STATUS_BK.reg &= ~USB_DEVICE_STATUS_BK_ERRORFLOW;
                        }
                        ep_callback_para.endpoint_address = USB_EP_DIR_OUT | i;
                        if (_usb_instances->hw->DEVICE.DeviceEndpoint[i].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_TRCPT0) {
                            return;
                        }
                    }

                    if(flags_run & USB_DEVICE_EPINTFLAG_TRFAIL_Msk) {
                        (_usb_instances->device_endpoint_callback[i][USB_DEVICE_ENDPOINT_CALLBACK_TRFAIL])(_usb_instances,&ep_callback_para);
                    }
                    return;
                }
            }
        }
    }
}

/**
 * \brief Enable the USB module peripheral
 *
 * \param module_inst pointer to USB module instance
 */
void usb_enable(struct usb_module *module_inst)
{
    Assert(module_inst);
    Assert(module_inst->hw);

    module_inst->hw->DEVICE.CTRLA.reg |= USB_CTRLA_ENABLE;
    while (module_inst->hw->DEVICE.SYNCBUSY.reg == USB_SYNCBUSY_ENABLE);
}

/**
 * \brief Disable the USB module peripheral
 *
 * \param module_inst pointer to USB module instance
 */
void usb_disable(struct usb_module *module_inst)
{
    Assert(module_inst);
    Assert(module_inst->hw);

    module_inst->hw->DEVICE.INTENCLR.reg = USB_DEVICE_INTENCLR_MASK;
    module_inst->hw->DEVICE.INTFLAG.reg = USB_DEVICE_INTFLAG_MASK;
    module_inst->hw->DEVICE.CTRLA.reg &= ~USB_CTRLA_ENABLE;
    while (module_inst->hw->DEVICE.SYNCBUSY.reg == USB_SYNCBUSY_ENABLE);
}

/**
 * \brief Interrupt handler for the USB module.
 */
void USB_0_Handler(void)
{
    if (_usb_instances->hw->DEVICE.CTRLA.bit.MODE) {

    } else {
        /*device mode ISR */
        _usb_device_interrupt_handler();
    }
}

void USB_1_Handler(void)
{
    _usb_device_interrupt_handler();
}

void USB_2_Handler(void)
{
    _usb_device_interrupt_handler();
}

void USB_3_Handler(void)
{
    _usb_device_interrupt_handler();
}

/**
 * \brief Get the default USB module settings
 *
 * \param[out] module_config  Configuration structure to initialize to default values
 */
void usb_get_config_defaults(struct usb_config *module_config)
{
    Assert(module_config);

    /* Sanity check arguments */
    Assert(module_config);
    /* Write default configuration to config struct */
    module_config->select_host_mode = 0;
    module_config->run_in_standby = 1;
    module_config->source_generator = 0;
    module_config->speed_mode = USB_SPEED_FULL;
}

#define NVM_USB_PAD_TRANSN_POS  45
#define NVM_USB_PAD_TRANSN_SIZE 5
#define NVM_USB_PAD_TRANSP_POS  50
#define NVM_USB_PAD_TRANSP_SIZE 5
#define NVM_USB_PAD_TRIM_POS  55
#define NVM_USB_PAD_TRIM_SIZE 3

/**
 * \brief Initializes USB module instance
 *
 * Enables the clock and initializes the USB module, based on the given
 * configuration values.
 *
 * \param[in,out] module_inst   Pointer to the software module instance struct
 * \param[in]     hw            Pointer to the USB hardware module
 * \param[in]     module_config Pointer to the USB configuration options struct
 *
 * \return Status of the initialization procedure.
 *
 * \retval STATUS_OK           The module was initialized successfully
 */

#define GCLK_USB 10

enum status_code usb_init(struct usb_module *module_inst, Usb *const hw,
        struct usb_config *module_config)
{
    /* Sanity check arguments */
    Assert(hw);
    Assert(module_inst);
    Assert(module_config);

    uint32_t i,j;
    uint32_t pad_transn, pad_transp, pad_trim;

    Gclk *pgclk = GCLK;
    Mclk *pmclk = MCLK;
    Port *pport = PORT;
    Oscctrl *posc = OSCCTRL;

    _usb_instances = module_inst;

    /* Associate the software module instance with the hardware module */
    module_inst->hw = hw;

    //setup peripheral and synchronous bus clocks to USB
    pmclk->AHBMASK.bit.USB_ = 1;
    pmclk->APBBMASK.bit.USB_ = 1;

    /* Set up the USB DP/DN pins */
    pport->Group[0].PMUX[12].reg = 0x77; //PA24, PA25, function column H for USB D-, D+
    pport->Group[0].PINCFG[24].bit.PMUXEN = 1;
    pport->Group[0].PINCFG[25].bit.PMUXEN = 1;
    pport->Group[1].PMUX[11].bit.PMUXE = 7; //PB22, function column H for USB SOF_1KHz output
    pport->Group[1].PINCFG[22].bit.PMUXEN = 1;

    //configure and enable DFLL for USB clock recovery mode at 48MHz
    posc->DFLLCTRLA.bit.ENABLE = 0;
    while (posc->DFLLSYNC.bit.ENABLE);
    while (posc->DFLLSYNC.bit.DFLLCTRLB);
    posc->DFLLCTRLB.bit.USBCRM = 1;
    while (posc->DFLLSYNC.bit.DFLLCTRLB);
    posc->DFLLCTRLB.bit.MODE = 1;
    while (posc->DFLLSYNC.bit.DFLLCTRLB);
    posc->DFLLCTRLB.bit.QLDIS = 0;
    while (posc->DFLLSYNC.bit.DFLLCTRLB);
    posc->DFLLCTRLB.bit.CCDIS = 1;
    posc->DFLLMUL.bit.MUL = 0xbb80;   //4800 x 1KHz
    while (posc->DFLLSYNC.bit.DFLLMUL);
    posc->DFLLCTRLA.bit.ENABLE = 1;
    while (posc->DFLLSYNC.bit.ENABLE);

    /* Setup clock for module */
    pgclk->PCHCTRL[GCLK_USB].bit.GEN = 0;
    pgclk->PCHCTRL[GCLK_USB].bit.CHEN = 1;

    /* Reset */
    hw->DEVICE.CTRLA.bit.SWRST = 1;
    while (hw->DEVICE.SYNCBUSY.bit.SWRST) {
        /* Sync wait */
    }

    /* Change QOS values to have the best performance and correct USB behaviour */
    USB->DEVICE.QOSCTRL.bit.CQOS = 2;
    USB->DEVICE.QOSCTRL.bit.DQOS = 2;

    /* Load Pad Calibration */

    pad_transn = (USB_FUSES_TRANSN_ADDR >>  USB_FUSES_TRANSN_Pos) & USB_FUSES_TRANSN_Msk;
    if (pad_transn == 0x1F) {
        pad_transn = 5;
    }

    hw->DEVICE.PADCAL.bit.TRANSN = pad_transn;

    pad_transp = (USB_FUSES_TRANSP_ADDR >>  USB_FUSES_TRANSP_Pos) & USB_FUSES_TRANSP_Msk;
    if (pad_transp == 0x1F) {
        pad_transp = 29;
    }

    hw->DEVICE.PADCAL.bit.TRANSP = pad_transp;

    pad_trim = (USB_FUSES_TRIM_ADDR >>  USB_FUSES_TRIM_Pos) & USB_FUSES_TRIM_Msk;
    if (pad_trim == 0x07) {
        pad_trim = 3;
    }

    hw->DEVICE.PADCAL.bit.TRIM = pad_trim;

    /* Set the configuration */
    hw->DEVICE.CTRLA.bit.MODE = module_config->select_host_mode;
    hw->DEVICE.CTRLA.bit.RUNSTDBY = module_config->run_in_standby;
    hw->DEVICE.DESCADD.reg = (uint32_t)(&usb_descriptor_table.usb_endpoint_table[0]);
    if (USB_SPEED_FULL == module_config->speed_mode) {
        module_inst->hw->DEVICE.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_FS_Val;
    } else if(USB_SPEED_LOW == module_config->speed_mode) {
        module_inst->hw->DEVICE.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_LS_Val;
    }

    memset((uint8_t *)(&usb_descriptor_table.usb_endpoint_table[0]), 0,
            sizeof(usb_descriptor_table.usb_endpoint_table));

    /*  device callback related */
    for (i = 0; i < USB_DEVICE_CALLBACK_N; i++) {
        module_inst->device_callback[i] = NULL;
    }
    for (i = 0; i < USB_EPT_NUM; i++) {
        for(j = 0; j < USB_DEVICE_EP_CALLBACK_N; j++) {
            module_inst->device_endpoint_callback[i][j] = NULL;
        }
    }
    module_inst->device_registered_callback_mask = 0;
    module_inst->device_enabled_callback_mask = 0;
    for (j = 0; j < USB_EPT_NUM; j++) {
        module_inst->device_endpoint_registered_callback_mask[j] = 0;
        module_inst->device_endpoint_enabled_callback_mask[j] = 0;
    }

    /* Enable interrupts for this USB module */
    NVIC_EnableIRQ(USB_0_IRQn);
    NVIC_EnableIRQ(USB_2_IRQn);
    NVIC_EnableIRQ(USB_3_IRQn);

    return STATUS_OK;
}

