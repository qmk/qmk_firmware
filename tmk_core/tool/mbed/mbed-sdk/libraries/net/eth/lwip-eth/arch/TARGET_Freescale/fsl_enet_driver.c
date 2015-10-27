/*
* Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Modified by mbed for the lwIP port */

#include "fsl_enet_driver.h"
#include "fsl_enet_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#include <string.h>

#include "sys_arch.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Define ENET's IRQ list */

void *enetIfHandle;

/*! @brief Define MAC driver API structure and for application of stack adaptor layer*/
const enet_mac_api_t g_enetMacApi =
{
    enet_mac_init,
    NULL, // enet_mac_deinit,
    NULL, // enet_mac_send,
#if !ENET_RECEIVE_ALL_INTERRUPT
    NULL, // enet_mac_receive,
#endif
    enet_mii_read,
    enet_mii_write,
    NULL, // enet_mac_add_multicast_group,
    NULL, //enet_mac_leave_multicast_group,
};
/*******************************************************************************
 * Code
 ******************************************************************************/

// NOTE: we need these functions to be non-blocking fpr the PHY task, hence the
// osDelay() below

/*FUNCTION****************************************************************
 *
 * Function Name: enet_mii_read
 * Return Value: The execution status.
 * Description: Read function.
 * This interface read data over the (R)MII bus from the specified PHY register,
 * This function is called by all PHY interfaces.
 *END*********************************************************************/
uint32_t enet_mii_read(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr)
{
    uint32_t  counter;
	
    /* Check the input parameters*/
    if (!dataPtr)
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Check if the mii is enabled*/
    if (!enet_hal_is_mii_enabled(instance))
    {
        return kStatus_ENET_Miiuninitialized;
    }

    /* Clear the MII interrupt event*/
    enet_hal_clear_interrupt(instance, kEnetMiiInterrupt);

    /* Read command operation*/
    enet_hal_set_mii_command(instance, phyAddr, phyReg, kEnetReadValidFrame, 0);

    /* Poll for MII complete*/
    for (counter = 0; counter < kEnetMaxTimeout; counter++)
    {
        if (enet_hal_get_interrupt_status(instance, kEnetMiiInterrupt))
        {
            break;
        }
        osDelay(1);
    }

    /* Check for timeout*/
    if (counter == kEnetMaxTimeout)
    {
        return kStatus_ENET_TimeOut;
    }

    /* Get data from mii register*/
    *dataPtr = enet_hal_get_mii_data(instance);

    /* Clear MII interrupt event*/
    enet_hal_clear_interrupt(instance, kEnetMiiInterrupt);
	
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_mii_write
 * Return Value: The execution status.
 * Description: Write function.
 * This interface write data over the (R)MII bus to the specified PHY register.
 * This function is called by all PHY interfaces.
 *END*********************************************************************/
uint32_t enet_mii_write(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t counter;

    /* Check if the mii is enabled*/
    if (!enet_hal_is_mii_enabled(instance))
    {
        return kStatus_ENET_Miiuninitialized;
    }

    /* Clear the MII interrupt event*/
    enet_hal_clear_interrupt(instance, kEnetMiiInterrupt);

    /* Read command operation*/
    enet_hal_set_mii_command(instance, phyAddr, phyReg, kEnetWriteValidFrame, data);

    /* Poll for MII complete*/
    for (counter = 0; counter < kEnetMaxTimeout; counter++)
    {
        if (enet_hal_get_interrupt_status(instance, kEnetMiiInterrupt))
        {
            break;
        }
        osDelay(1);
    }

    /* Check for timeout*/
    if (counter == kEnetMaxTimeout)
    {
        return kStatus_ENET_TimeOut;
    }

    /* Clear MII intrrupt event*/
    enet_hal_clear_interrupt(instance, kEnetMiiInterrupt);
	
    return kStatus_ENET_Success;
}
/*FUNCTION****************************************************************
 *
 * Function Name: enet_mac_mii_init
 * Return Value: The execution status.
 * Description:Initialize the ENET Mac mii(mdc/mdio)interface.
 *END*********************************************************************/
uint32_t enet_mac_mii_init(enet_dev_if_t * enetIfPtr)
{
    uint32_t frequency;
	
    /* Check the input parameters*/
    if (enetIfPtr == NULL)
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Configure mii speed*/
    CLOCK_SYS_GetFreq(kSystemClock, &frequency);
    enet_hal_config_mii(enetIfPtr->deviceNumber, (frequency/(2 * enetIfPtr->macCfgPtr->miiClock) + 1),
                 kEnetMdioHoldOneClkCycle, false);

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_mac_rxbd_init
 * Return Value: The execution status.
 * Description:Initialize the ENET receive buffer descriptors.
 * Note: If you do receive on receive interrupt handler the receive
 * data buffer number can be the same as the receive descriptor numbers.
 * But if you are polling receive frames please make sure the receive data
 * buffers are more than buffer descriptors to guarantee a good performance.
 *END*********************************************************************/
uint32_t enet_mac_rxbd_init(enet_dev_if_t * enetIfPtr, enet_rxbd_config_t *rxbdCfg)
{
    /* Check the input parameters*/
    if ((!enetIfPtr) || (!rxbdCfg))
    {
        return kStatus_ENET_InvalidInput;
    }

    enetIfPtr->macContextPtr->bufferdescSize = enet_hal_get_bd_size();

    /* Initialize the bd status*/
    enetIfPtr->macContextPtr->isRxFull = false;
		
    /* Initialize receive bd base address and current address*/
    enetIfPtr->macContextPtr->rxBdBasePtr = rxbdCfg->rxBdPtrAlign;
    enetIfPtr->macContextPtr->rxBdCurPtr = enetIfPtr->macContextPtr->rxBdBasePtr;
    enetIfPtr->macContextPtr->rxBdDirtyPtr = enetIfPtr->macContextPtr->rxBdBasePtr;
    enet_hal_set_rxbd_address(enetIfPtr->deviceNumber, (uint32_t)(enetIfPtr->macContextPtr->rxBdBasePtr));
	
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_mac_txbd_init
 * Return Value: The execution status.
 * Description:Initialize the ENET transmit buffer descriptors.
 * This function prepare all of the transmit buffer descriptors.
 *END*********************************************************************/
uint32_t enet_mac_txbd_init(enet_dev_if_t * enetIfPtr, enet_txbd_config_t *txbdCfg)
{
    /* Check the input parameters*/
    if ((!enetIfPtr) || (!txbdCfg))
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Initialize the bd status*/
    enetIfPtr->macContextPtr->isTxFull = false;

    /* Initialize transmit bd base address and current address*/
    enetIfPtr->macContextPtr->txBdBasePtr = txbdCfg->txBdPtrAlign;
    enetIfPtr->macContextPtr->txBdCurPtr = enetIfPtr->macContextPtr->txBdBasePtr;
    enetIfPtr->macContextPtr->txBdDirtyPtr = enetIfPtr->macContextPtr->txBdBasePtr;
    enet_hal_set_txbd_address(enetIfPtr->deviceNumber, (uint32_t)(enetIfPtr->macContextPtr->txBdBasePtr));
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_mac_configure_fifo_accel
 * Return Value: The execution status.
 * Description: Configure the ENET FIFO and Accelerator.
 *END*********************************************************************/
uint32_t enet_mac_configure_fifo_accel(enet_dev_if_t * enetIfPtr)
{
    enet_config_rx_fifo_t rxFifo;
    enet_config_tx_fifo_t txFifo;
	
    /* Check the input parameters*/
    if (!enetIfPtr)
    {
        return kStatus_ENET_InvalidInput;
    }
		
		/* Initialize values that will not be initialized later on */
    rxFifo.rxEmpty = 0;
    rxFifo.rxFull = 0;
    txFifo.isStoreForwardEnabled = 0;
    txFifo.txFifoWrite = 0;
    txFifo.txEmpty = 0;

    /* Configure tx/rx accelerator*/
    if (enetIfPtr->macCfgPtr->isRxAccelEnabled)
    {
        enet_hal_config_rx_accelerator(enetIfPtr->deviceNumber,
           (enet_config_rx_accelerator_t *)&(enetIfPtr->macCfgPtr->rxAcceler));
        if ((enetIfPtr->macCfgPtr->rxAcceler.isIpcheckEnabled) || (enetIfPtr->macCfgPtr->rxAcceler.isProtocolCheckEnabled))
        {
            rxFifo.rxFull = 0;
        }
    }
    if (enetIfPtr->macCfgPtr->isTxAccelEnabled)
    {
        enet_hal_config_tx_accelerator(enetIfPtr->deviceNumber,
            (enet_config_tx_accelerator_t *)&(enetIfPtr->macCfgPtr->txAcceler));
        if ((enetIfPtr->macCfgPtr->txAcceler.isIpCheckEnabled) || (enetIfPtr->macCfgPtr->txAcceler.isProtocolCheckEnabled))
        {
            txFifo.isStoreForwardEnabled = 1;
        }
    }
    if (enetIfPtr->macCfgPtr->isStoreAndFwEnabled)
    {
          rxFifo.rxFull = 0;
          txFifo.isStoreForwardEnabled = 1;
    }


    /* Set TFWR value if STRFWD is not being used  */
    if (txFifo.isStoreForwardEnabled == 1)
          txFifo.txFifoWrite = 0;
    else
          /* TFWR value is a trade-off between transmit latency and risk of transmit FIFO underrun due to contention for the system bus
		      TFWR = 15 means transmission will begin once 960 bytes has been written to the Tx FIFO (for frames larger than 960 bytes)
          See Section 45.4.18 - Transmit FIFO Watermark Register of the K64F Reference Manual for details		*/
          txFifo.txFifoWrite = 15;
		
    /* Configure tx/rx FIFO with default value*/
    rxFifo.rxAlmostEmpty = 4;
    rxFifo.rxAlmostFull = 4;
    txFifo.txAlmostEmpty = 4;
    txFifo.txAlmostFull = 8;
    enet_hal_config_rx_fifo(enetIfPtr->deviceNumber, &rxFifo);
    enet_hal_config_tx_fifo(enetIfPtr->deviceNumber, &txFifo);

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_mac_configure_controller
 * Return Value: The execution status.
 * Description: Configure the ENET controller with the basic configuration.
 *END*********************************************************************/
uint32_t enet_mac_configure_controller(enet_dev_if_t * enetIfPtr)
{
    uint32_t macCtlCfg;

    /* Check the input parameters*/
    if (enetIfPtr == NULL)
    {
        return kStatus_ENET_InvalidInput;
    }

    macCtlCfg = enetIfPtr->macCfgPtr->macCtlConfigure;
    /* Configure rmii/mii interface*/
    enet_hal_config_rmii(enetIfPtr->deviceNumber, enetIfPtr->macCfgPtr->rmiiCfgMode,
        enetIfPtr->macCfgPtr->speed, enetIfPtr->macCfgPtr->duplex, false,
        (macCtlCfg & kEnetRxMiiLoopback));
     /* Configure receive buffer size*/
    if (enetIfPtr->macCfgPtr->isVlanEnabled)
    {
        enetIfPtr->maxFrameSize = kEnetMaxFrameVlanSize;
        enet_hal_set_rx_max_size(enetIfPtr->deviceNumber,
              enetIfPtr->macContextPtr->rxBufferSizeAligned, kEnetMaxFrameVlanSize);
    }
    else
    {
        enetIfPtr->maxFrameSize = kEnetMaxFrameSize;
        enet_hal_set_rx_max_size(enetIfPtr->deviceNumber,
              enetIfPtr->macContextPtr->rxBufferSizeAligned, kEnetMaxFrameSize);
    }

	/* Set receive controller promiscuous */
    enet_hal_config_promiscuous(enetIfPtr->deviceNumber, macCtlCfg & kEnetRxPromiscuousEnable);
    /* Set receive flow control*/
    enet_hal_enable_flowcontrol(enetIfPtr->deviceNumber, (macCtlCfg & kEnetRxFlowControlEnable));
    /* Set received PAUSE frames are forwarded/terminated*/
    enet_hal_enable_pauseforward(enetIfPtr->deviceNumber, (macCtlCfg & kEnetRxPauseFwdEnable));
    /* Set receive broadcast frame reject*/
    enet_hal_enable_broadcastreject(enetIfPtr->deviceNumber, (macCtlCfg & kEnetRxBcRejectEnable));
    /* Set padding is removed from the received frame*/
    enet_hal_enable_padremove(enetIfPtr->deviceNumber, (macCtlCfg & kEnetRxPadRemoveEnable));
    /* Set the crc of the received frame is stripped from the frame*/
    enet_hal_enable_rxcrcforward(enetIfPtr->deviceNumber, (macCtlCfg & kEnetRxCrcFwdEnable));
    /* Set receive payload length check*/
    enet_hal_enable_payloadcheck(enetIfPtr->deviceNumber, (macCtlCfg & kEnetPayloadlenCheckEnable));
    /* Set control sleep mode*/
    enet_hal_enable_sleep(enetIfPtr->deviceNumber, (macCtlCfg & kEnetSleepModeEnable));
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_mac_init
 * Return Value: The execution status.
 * Description:Initialize the ENET device with the basic configuration
 * When ENET is used, this function need to be called by the NET initialize
 * interface.
 *END*********************************************************************/
uint32_t enet_mac_init(enet_dev_if_t * enetIfPtr, enet_rxbd_config_t *rxbdCfg,
                            enet_txbd_config_t *txbdCfg)
{
    uint32_t timeOut = 0;
    uint32_t devNumber, result = 0;
	
    /* Check the input parameters*/
    if (enetIfPtr == NULL)
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Get device number and check the parameter*/
    devNumber = enetIfPtr->deviceNumber;

    /* Store the global ENET structure for ISR input parameters */
    enetIfHandle = enetIfPtr;

    /* Turn on ENET module clock gate */
    CLOCK_SYS_EnableEnetClock(0U);

    /* Reset ENET mac*/
    enet_hal_reset_ethernet(devNumber);
    while ((!enet_hal_is_reset_completed(devNumber)) && (timeOut < kEnetMaxTimeout))
    {
        time_delay(1);
        timeOut++;
    }

    /* Check out if timeout*/
    if (timeOut == kEnetMaxTimeout)
    {
        return kStatus_ENET_TimeOut;
    }
	
    /* Disable all ENET mac interrupt and Clear all interrupt events*/
    enet_hal_config_interrupt(devNumber, kEnetAllInterrupt, false);
    enet_hal_clear_interrupt(devNumber, kEnetAllInterrupt);
	
    /* Program this station's physical address*/
    enet_hal_set_mac_address(devNumber, enetIfPtr->macCfgPtr->macAddr);

    /* Clear group and individual hash register*/
    enet_hal_set_group_hashtable(devNumber, 0, kEnetSpecialAddressInit);
    enet_hal_set_individual_hashtable(devNumber, 0, kEnetSpecialAddressInit);

	  /* Configure mac controller*/
    result = enet_mac_configure_controller(enetIfPtr);
    if(result != kStatus_ENET_Success)
    {
        return result;
    }
    /* Clear mib zero counters*/
    enet_hal_clear_mib(devNumber, true);

    /* Initialize FIFO and accelerator*/
    result = enet_mac_configure_fifo_accel(enetIfPtr);
    if(result != kStatus_ENET_Success)
    {
        return result;
    }
    /* Initialize receive buffer descriptors*/
    result = enet_mac_rxbd_init(enetIfPtr, rxbdCfg);
    if(result != kStatus_ENET_Success)
    {
        return result;
    }
    /* Initialize transmit buffer descriptors*/
	  result = enet_mac_txbd_init(enetIfPtr, txbdCfg);
    if(result != kStatus_ENET_Success)
    {
        return result;
    }
    /* Initialize rmii/mii interface*/
    result = enet_mac_mii_init(enetIfPtr);
    if (result != kStatus_ENET_Success)
    {
        return result;
    }
    
    return kStatus_ENET_Success;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

