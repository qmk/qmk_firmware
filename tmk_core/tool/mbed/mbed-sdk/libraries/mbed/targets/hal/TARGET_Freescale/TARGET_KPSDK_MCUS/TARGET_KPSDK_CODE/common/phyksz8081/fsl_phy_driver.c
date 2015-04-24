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

#include "fsl_phy_driver.h"

#ifndef MBED_NO_ENET

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Define Phy API structure for MAC application*/
const enet_phy_api_t g_enetPhyApi = 
{
    phy_auto_discover,
    phy_init,
    phy_get_link_speed,
    phy_get_link_status,
    phy_get_link_duplex,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION****************************************************************
 *
 * Function Name: phy_init
 * Return Value: The execution status.
 * Description: Initialize Phy.
 * This interface provides initialize functions for Phy, This is called by enet  
 * initialize function. Phy is usually deault auto-negotiation. so there is no 
 * need to do the intialize about this. we just need to check the loop mode.
 *END*********************************************************************/
uint32_t phy_init(enet_dev_if_t * enetIfPtr)
{
    uint32_t data;
    uint32_t counter;
    uint32_t result;
   
    /* Check input parameters*/
    if (!enetIfPtr)
    {
        return kStatus_PHY_InvaildInput;
    }

    /* Reset Phy*/
    if ((result = (enetIfPtr->macApiPtr->enet_mii_read(enetIfPtr->deviceNumber, 
            enetIfPtr->phyCfgPtr->phyAddr,kEnetPhySR,&data))) == kStatus_PHY_Success)
    {
        if ((data & kEnetPhyAutoNegAble) != 0)
        {
            /* Set Autonegotiation*/
            enetIfPtr->macApiPtr->enet_mii_write(enetIfPtr->deviceNumber, 
                enetIfPtr->phyCfgPtr->phyAddr, kEnetPhyCR, kEnetPhyAutoNeg);
            for (counter = 0; counter < kPhyTimeout; counter++)
            {
                if (enetIfPtr->macApiPtr->enet_mii_read(enetIfPtr->deviceNumber, 
                       enetIfPtr->phyCfgPtr->phyAddr,kEnetPhySR,&data)== kStatus_PHY_Success)
                {
                    if ((data & kEnetPhyAutoNegComplete) != 0)
                    {
                        break;
                    }
                }		  	            
            }

            if (counter == kPhyTimeout)
            {
                return kStatus_PHY_TimeOut;
            }
        }
    }

    if (enetIfPtr->phyCfgPtr->isLoopEnabled)
    {
        /* First read the current status in control register*/ 
        if (enetIfPtr->macApiPtr->enet_mii_read(enetIfPtr->deviceNumber, 
            enetIfPtr->phyCfgPtr->phyAddr,kEnetPhyCR,&data))
        {
            result = enetIfPtr->macApiPtr->enet_mii_write(enetIfPtr->deviceNumber, 
                enetIfPtr->phyCfgPtr->phyAddr,kEnetPhyCR,(data|kEnetPhyLoop));
        }		
    }

    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: phy_auto_discover
 * Return Value: The execution status.
 * Description: Phy address auto discover.
 * This function provides a interface to get phy address using phy address auto 
 * discovering, this interface is used when the phy address is unknown.
 *END*********************************************************************/
uint32_t phy_auto_discover(enet_dev_if_t * enetIfPtr)
{
    uint32_t addrIdx,data;
    uint32_t result = kStatus_PHY_Fail;
	
    /* Check input parameters*/
    if (!enetIfPtr)
    {
        return kStatus_PHY_InvaildInput;
    }

    for (addrIdx = 0; addrIdx < 32; addrIdx++)
    {
        enetIfPtr->phyCfgPtr->phyAddr = addrIdx;
        result = enetIfPtr->macApiPtr->enet_mii_read(enetIfPtr->deviceNumber,
            enetIfPtr->phyCfgPtr->phyAddr,kEnetPhyId1,&data);
        if ((result == kStatus_PHY_Success) && (data != 0) && (data != 0xffff) )
        {
            return kStatus_PHY_Success;
        }
    }

    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: phy_get_link_speed
 * Return Value: The execution status.
 * Description: Get phy link speed.
 * This function provides a interface to get link speed.
 *END*********************************************************************/
uint32_t phy_get_link_speed(enet_dev_if_t * enetIfPtr, enet_phy_speed_t *status)
{
    uint32_t result = kStatus_PHY_Success;
    uint32_t data;
	
    /* Check input parameters*/
    if ((!enetIfPtr) || (!status))
    {
        return kStatus_PHY_InvaildInput;
    }

    result = enetIfPtr->macApiPtr->enet_mii_read(enetIfPtr->deviceNumber, 
        enetIfPtr->phyCfgPtr->phyAddr, kEnetPhyCt2,&data);
    if (result == kStatus_PHY_Success)
    {
        data &= kEnetPhySpeedDulpexMask; 
        if ((kEnetPhy100HalfDuplex == data) || (kEnetPhy100FullDuplex == data))
        {
            *status = kEnetSpeed100M;
        }
        else
        {
            *status = kEnetSpeed10M;
        }
    }

    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: phy_get_link_status
 * Return Value: The execution status.
 * Description: Get phy link status.
 * This function provides a interface to get link status to see if the link 
 * status is on or off.
 *END*********************************************************************/
 uint32_t phy_get_link_status(enet_dev_if_t * enetIfPtr, bool *status)
{
    uint32_t result = kStatus_PHY_Success;
    uint32_t data;
	
    /* Check input parameters*/
    if ((!enetIfPtr) || (!status))
    {
        return kStatus_PHY_InvaildInput;
    }

    result = enetIfPtr->macApiPtr->enet_mii_read(enetIfPtr->deviceNumber, 
        enetIfPtr->phyCfgPtr->phyAddr,kEnetPhyCR,&data);
    if ((result == kStatus_PHY_Success) && (!(data & kEnetPhyReset)))
    {
        data = 0;
        result = enetIfPtr->macApiPtr->enet_mii_read(enetIfPtr->deviceNumber, 
            enetIfPtr->phyCfgPtr->phyAddr,kEnetPhySR, &data);
        if (result == kStatus_PHY_Success)
        {
            if (!(kEnetPhyLinkStatus & data))
            {
                *status = false;
            }
            else
            {
                *status = true;
            }
        }
    }

    return result;     
}

/*FUNCTION****************************************************************
 *
 * Function Name: phy_get_link_duplex
 * Return Value: The execution status.
 * Description: Get phy link duplex.
 * This function provides a interface to get link duplex to see if the link 
 * duplex is full or half.
 *END*********************************************************************/
uint32_t phy_get_link_duplex(enet_dev_if_t * enetIfPtr, enet_phy_duplex_t *status)
{
    uint32_t result = kStatus_PHY_Success;
    uint32_t data;
	
    /* Check input parameters*/
    if ((!enetIfPtr) || (!status))
    {
        return kStatus_PHY_InvaildInput;
    }

    result = enetIfPtr->macApiPtr->enet_mii_read(enetIfPtr->deviceNumber, 
        enetIfPtr->phyCfgPtr->phyAddr,kEnetPhyCt2,&data);
    if (result == kStatus_PHY_Success)
    {
        data &= kEnetPhySpeedDulpexMask; 
        if ((kEnetPhy10FullDuplex == data) || (kEnetPhy100FullDuplex == data))
        {
            *status = kEnetFullDuplex;
        }
        else
        {
            *status = kEnetHalfDuplex;
        }
    }

    return result;
}

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

