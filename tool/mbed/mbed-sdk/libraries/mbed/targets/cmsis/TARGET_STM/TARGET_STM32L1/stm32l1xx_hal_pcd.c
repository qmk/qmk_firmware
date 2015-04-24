/**
  ******************************************************************************
  * @file    stm32l1xx_hal_pcd.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   PCD HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions 
  *           + Peripheral State functions
  *         
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      The PCD HAL driver can be used as follows:

     (#) Declare a PCD_HandleTypeDef handle structure, for example:
         PCD_HandleTypeDef  hpcd;
        
     (#) Fill parameters of Init structure in HCD handle
  
     (#) Call HAL_PCD_Init() API to initialize the HCD peripheral (Core, Device core, ...) 

     (#) Initialize the PCD low level resources through the HAL_PCD_MspInit() API:
         (##) Enable the PCD/USB Low Level interface clock using 
              (+++) __USB_CLK_ENABLE);
           
         (##) Initialize the related GPIO clocks
         (##) Configure PCD pin-out
         (##) Configure PCD NVIC interrupt
    
     (#)Associate the Upper USB device stack to the HAL PCD Driver:
         (##) hpcd.pData = pdev;

     (#)Enable HCD transmission and reception:
         (##) HAL_PCD_Start();

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup PCD PCD
  * @brief PCD HAL module driver
  * @{
  */

#ifdef HAL_PCD_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup PCD_Private_Constants PCD Private Constants
  * @{
  */ 
#define BTABLE_ADDRESS                  (0x000)  
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup PCD_Private_Functions PCD Private Functions
  * @{
  */
static HAL_StatusTypeDef PCD_EP_ISR_Handler(PCD_HandleTypeDef *hpcd);
static void PCD_WritePMA(USB_TypeDef  *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);
static void PCD_ReadPMA(USB_TypeDef  *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);

/**
  * @}
  */


/** @defgroup PCD_Exported_Functions PCD Exported Functions
  * @{
  */

/** @defgroup PCD_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim
 ===============================================================================
            ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
 
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the PCD according to the specified
  *         parameters in the PCD_InitTypeDef and create the associated handle.
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Init(PCD_HandleTypeDef *hpcd)
{ 
  uint32_t i = 0;

  uint32_t wInterrupt_Mask = 0;
  
  /* Check the PCD handle allocation */
  if(hpcd == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_PCD_ALL_INSTANCE(hpcd->Instance));

  hpcd->State = PCD_BUSY;
  
  /* Init the low level hardware : GPIO, CLOCK, NVIC... */
  HAL_PCD_MspInit(hpcd);

 /* Init endpoints structures */
 for (i = 0; i < hpcd->Init.dev_endpoints ; i++)
 {
   /* Init ep structure */
   hpcd->IN_ep[i].is_in = 1;
   hpcd->IN_ep[i].num = i;
   /* Control until ep is actvated */
   hpcd->IN_ep[i].type = PCD_EP_TYPE_CTRL;
   hpcd->IN_ep[i].maxpacket =  0;
   hpcd->IN_ep[i].xfer_buff = 0;
   hpcd->IN_ep[i].xfer_len = 0;
 }
 
 for (i = 0; i < hpcd->Init.dev_endpoints ; i++)
 {
   hpcd->OUT_ep[i].is_in = 0;
   hpcd->OUT_ep[i].num = i;
   /* Control until ep is activated */
   hpcd->OUT_ep[i].type = PCD_EP_TYPE_CTRL;
   hpcd->OUT_ep[i].maxpacket = 0;
   hpcd->OUT_ep[i].xfer_buff = 0;
   hpcd->OUT_ep[i].xfer_len = 0;
 }
  
 /* Init Device */
 /*CNTR_FRES = 1*/
 hpcd->Instance->CNTR = USB_CNTR_FRES;
 
 /*CNTR_FRES = 0*/
 hpcd->Instance->CNTR = 0;
 
 /*Clear pending interrupts*/
 hpcd->Instance->ISTR = 0;
 
  /*Set Btable Adress*/
 hpcd->Instance->BTABLE = BTABLE_ADDRESS;
  
  /*set wInterrupt_Mask global variable*/
  wInterrupt_Mask = USB_CNTR_CTRM  | USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_ERRM \
    | USB_CNTR_ESOFM | USB_CNTR_RESETM;
  
  /*Set interrupt mask*/
  hpcd->Instance->CNTR = wInterrupt_Mask;
  
  hpcd->USB_Address = 0;
  hpcd->State= PCD_READY;

 return HAL_OK;
}

/**
  * @brief  DeInitializes the PCD peripheral 
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DeInit(PCD_HandleTypeDef *hpcd)
{
  /* Check the PCD handle allocation */
  if(hpcd == HAL_NULL)
  {
    return HAL_ERROR;
  }

  hpcd->State = PCD_BUSY;
  
  /* Stop Device */
  HAL_PCD_Stop(hpcd);
    
  /* DeInit the low level hardware */
  HAL_PCD_MspDeInit(hpcd);
  
  hpcd->State = PCD_READY; 
  
  return HAL_OK;
}

/**
  * @brief  Initializes the PCD MSP.
  * @param  hpcd: PCD handle
  * @retval None
  */
__weak void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_MspInit could be implenetd in the user file
   */
}

/**
  * @brief  DeInitializes PCD MSP.
  * @param  hpcd: PCD handle
  * @retval None
  */
__weak void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_MspDeInit could be implenetd in the user file
   */
}

/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group2 IO operation functions 
 *  @brief   Data transfers functions 
 *
@verbatim   
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the PCD data 
    transfers.

@endverbatim
  * @{
  */
  
/**
  * @brief  Start The USB OTG Device.
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Start(PCD_HandleTypeDef *hpcd)
{ 
  HAL_PCDEx_SetConnectionState (hpcd, 1);
  return HAL_OK;
}

/**
  * @brief  Stop The USB OTG Device.
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Stop(PCD_HandleTypeDef *hpcd)
{ 
  __HAL_LOCK(hpcd); 
  
    /* disable all interrupts and force USB reset */
  hpcd->Instance->CNTR = USB_CNTR_FRES;
  
  /* clear interrupt status register */
  hpcd->Instance->ISTR = 0;
  
  /* switch-off device */
  hpcd->Instance->CNTR = (USB_CNTR_FRES | USB_CNTR_PDWN);
  
  __HAL_UNLOCK(hpcd); 
  return HAL_OK;
}

/**
  * @brief  This function handles PCD interrupt request.
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
void HAL_PCD_IRQHandler(PCD_HandleTypeDef *hpcd)
{
  uint32_t wInterrupt_Mask = 0;
  
  if (__HAL_PCD_GET_FLAG (hpcd, USB_ISTR_CTR))
  {
    /* servicing of the endpoint correct transfer interrupt */
    /* clear of the CTR flag into the sub */
    PCD_EP_ISR_Handler(hpcd);
  }

  if (__HAL_PCD_GET_FLAG (hpcd, USB_ISTR_RESET))
  {
    __HAL_PCD_CLEAR_FLAG(hpcd, USB_ISTR_RESET);
    HAL_PCD_ResetCallback(hpcd);
    HAL_PCD_SetAddress(hpcd, 0);
  }

  if (__HAL_PCD_GET_FLAG (hpcd, USB_ISTR_PMAOVRM))
  {
    __HAL_PCD_CLEAR_FLAG(hpcd, USB_ISTR_PMAOVRM);    
  }
  if (__HAL_PCD_GET_FLAG (hpcd, USB_ISTR_ERR))
  {
    __HAL_PCD_CLEAR_FLAG(hpcd, USB_ISTR_ERR); 
  }

  if (__HAL_PCD_GET_FLAG (hpcd, USB_ISTR_WKUP))
  {  
    hpcd->Instance->CNTR &= ~(USB_CNTR_LP_MODE);
    
    /*set wInterrupt_Mask global variable*/
    wInterrupt_Mask = USB_CNTR_CTRM  | USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_ERRM \
      | USB_CNTR_ESOFM | USB_CNTR_RESETM;
    
    /*Set interrupt mask*/
    hpcd->Instance->CNTR = wInterrupt_Mask;
    
    HAL_PCD_ResumeCallback(hpcd);
    
    __HAL_PCD_CLEAR_FLAG(hpcd, USB_ISTR_WKUP);     
  }

  if (__HAL_PCD_GET_FLAG (hpcd, USB_ISTR_SUSP))
  {    
    /* clear of the ISTR bit must be done after setting of CNTR_FSUSP */
    __HAL_PCD_CLEAR_FLAG(hpcd, USB_ISTR_SUSP);  
    
    /* Force low-power mode in the macrocell */
    hpcd->Instance->CNTR |= USB_CNTR_FSUSP;
    hpcd->Instance->CNTR |= USB_CNTR_LP_MODE;
    if (__HAL_PCD_GET_FLAG (hpcd, USB_ISTR_WKUP) == 0)
    {
      HAL_PCD_SuspendCallback(hpcd);
    }
  }

  if (__HAL_PCD_GET_FLAG (hpcd, USB_ISTR_SOF))
  {
    __HAL_PCD_CLEAR_FLAG(hpcd, USB_ISTR_SOF); 
    HAL_PCD_SOFCallback(hpcd);
  }

  if (__HAL_PCD_GET_FLAG (hpcd, USB_ISTR_ESOF))
  {
    /* clear ESOF flag in ISTR */
    __HAL_PCD_CLEAR_FLAG(hpcd, USB_ISTR_ESOF); 
  }
}

/**
  * @brief  Data out stage callbacks
  * @param  hpcd: PCD handle
  * @param  epnum: endpoint number
  * @retval None
  */
 __weak void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_DataOutStageCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Data IN stage callbacks
  * @param  hpcd: PCD handle
  * @param  epnum: endpoint number
  * @retval None
  */
 __weak void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_DataInStageCallback could be implenetd in the user file
   */ 
}
/**
  * @brief  Setup stage callback
  * @param  hpcd: ppp handle
  * @retval None
  */
 __weak void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_SetupStageCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  USB Start Of Frame callbacks
  * @param  hpcd: PCD handle
  * @retval None
  */
 __weak void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_SOFCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  USB Reset callbacks
  * @param  hpcd: PCD handle
  * @retval None
  */
 __weak void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ResetCallback could be implenetd in the user file
   */ 
}


/**
  * @brief  Suspend event callbacks
  * @param  hpcd: PCD handle
  * @retval None
  */
 __weak void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_SuspendCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Resume event callbacks
  * @param  hpcd: PCD handle
  * @retval None
  */
 __weak void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ResumeCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Incomplete ISO OUT callbacks
  * @param  hpcd: PCD handle
  * @param  epnum: endpoint number
  * @retval None
  */
 __weak void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ISOOUTIncompleteCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Incomplete ISO IN  callbacks
  * @param  hpcd: PCD handle
  * @param  epnum: endpoint number
  * @retval None
  */
 __weak void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ISOINIncompleteCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Connection event callbacks
  * @param  hpcd: PCD handle
  * @retval None
  */
 __weak void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ConnectCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Disconnection event callbacks
  * @param  hpcd: ppp handle
  * @retval None
  */
 __weak void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_DisconnectCallback could be implenetd in the user file
   */ 
}

/**
  * @}
  */
  
/** @defgroup PCD_Exported_Functions_Group3 Peripheral Control functions 
 *  @brief   management functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the PCD data 
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Connect the USB device 
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DevConnect(PCD_HandleTypeDef *hpcd)
{
  __HAL_LOCK(hpcd); 
  
  /* Enabling DP Pull-Down bit to Connect internal pull-up on USB DP line */
   HAL_PCDEx_SetConnectionState (hpcd, 1);
  
  __HAL_UNLOCK(hpcd); 
  return HAL_OK;
}

/**
  * @brief  Disconnect the USB device 
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DevDisconnect(PCD_HandleTypeDef *hpcd)
{
  __HAL_LOCK(hpcd); 
  
  /* Disable DP Pull-Down bit*/
  HAL_PCDEx_SetConnectionState (hpcd, 0);
  
  __HAL_UNLOCK(hpcd); 
  return HAL_OK;
}

/**
  * @brief  Set the USB Device address 
  * @param  hpcd: PCD handle
  * @param  address: new device address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_SetAddress(PCD_HandleTypeDef *hpcd, uint8_t address)
{
   __HAL_LOCK(hpcd); 

   if(address == 0) 
   {
     /* set device address and enable function */
     hpcd->Instance->DADDR = USB_DADDR_EF;
   }
   else /* USB Address will be applied later */
   {
     hpcd->USB_Address = address;
   }

  __HAL_UNLOCK(hpcd);   
  return HAL_OK;
}
/**
  * @brief  Open and configure an endpoint
  * @param  hpcd: PCD handle
  * @param  ep_addr: endpoint address
  * @param  ep_mps: endpoint max packert size
  * @param  ep_type: endpoint type   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Open(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type)
{
  HAL_StatusTypeDef  ret = HAL_OK;
  PCD_EPTypeDef *ep;
  
  if ((ep_addr & 0x80) == 0x80)
  {
    ep = &hpcd->IN_ep[ep_addr & 0x7F];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & 0x7F];
  }
  ep->num   = ep_addr & 0x7F;
  
  ep->is_in = (0x80 & ep_addr) != 0;
  ep->maxpacket = ep_mps;
  ep->type = ep_type;
  
  __HAL_LOCK(hpcd); 

/* initialize Endpoint */
  switch (ep->type)
  {
  case PCD_EP_TYPE_CTRL:
    PCD_SET_EPTYPE(hpcd->Instance, ep->num, USB_EP_CONTROL);
    break;
  case PCD_EP_TYPE_BULK:
    PCD_SET_EPTYPE(hpcd->Instance, ep->num, USB_EP_BULK);
    break;
  case PCD_EP_TYPE_INTR:
    PCD_SET_EPTYPE(hpcd->Instance, ep->num, USB_EP_INTERRUPT);
    break;
  case PCD_EP_TYPE_ISOC:
    PCD_SET_EPTYPE(hpcd->Instance, ep->num, USB_EP_ISOCHRONOUS);
    break;
  default:
      break;
  } 
  
  PCD_SET_EP_ADDRESS(hpcd->Instance, ep->num, ep->num);
  
  if (ep->doublebuffer == 0) 
  {
    if (ep->is_in)
    {
      /*Set the endpoint Transmit buffer address */
      PCD_SET_EP_TX_ADDRESS(hpcd->Instance, ep->num, ep->pmaadress);
      PCD_CLEAR_TX_DTOG(hpcd->Instance, ep->num);
      /* Configure NAK status for the Endpoint*/
      PCD_SET_EP_TX_STATUS(hpcd->Instance, ep->num, USB_EP_TX_NAK); 
    }
    else
    {
      /*Set the endpoint Receive buffer address */
      PCD_SET_EP_RX_ADDRESS(hpcd->Instance, ep->num, ep->pmaadress);
      /*Set the endpoint Receive buffer counter*/
      PCD_SET_EP_RX_CNT(hpcd->Instance, ep->num, ep->maxpacket);
      PCD_CLEAR_RX_DTOG(hpcd->Instance, ep->num);
      /* Configure VALID status for the Endpoint*/
      PCD_SET_EP_RX_STATUS(hpcd->Instance, ep->num, USB_EP_RX_VALID);
    }
  }
  /*Double Buffer*/
  else
  {
    /*Set the endpoint as double buffered*/
    PCD_SET_EP_DBUF(hpcd->Instance, ep->num);
    /*Set buffer address for double buffered mode*/
    PCD_SET_EP_DBUF_ADDR(hpcd->Instance, ep->num,ep->pmaaddr0, ep->pmaaddr1);
    
    if (ep->is_in==0)
    {
      /* Clear the data toggle bits for the endpoint IN/OUT*/
      PCD_CLEAR_RX_DTOG(hpcd->Instance, ep->num);
      PCD_CLEAR_TX_DTOG(hpcd->Instance, ep->num);
      
      /* Reset value of the data toggle bits for the endpoint out*/
      PCD_TX_DTOG(hpcd->Instance, ep->num);
      
      PCD_SET_EP_RX_STATUS(hpcd->Instance, ep->num, USB_EP_RX_VALID);
      PCD_SET_EP_TX_STATUS(hpcd->Instance, ep->num, USB_EP_TX_DIS);
    }
    else
    {
      /* Clear the data toggle bits for the endpoint IN/OUT*/
      PCD_CLEAR_RX_DTOG(hpcd->Instance, ep->num);
      PCD_CLEAR_TX_DTOG(hpcd->Instance, ep->num);
      PCD_RX_DTOG(hpcd->Instance, ep->num);
      /* Configure DISABLE status for the Endpoint*/
      PCD_SET_EP_TX_STATUS(hpcd->Instance, ep->num, USB_EP_TX_DIS);
      PCD_SET_EP_RX_STATUS(hpcd->Instance, ep->num, USB_EP_RX_DIS);
    }
  } 
  
  __HAL_UNLOCK(hpcd);   
  return ret;
}


/**
  * @brief  Deactivate an endpoint
  * @param  hpcd: PCD handle
  * @param  ep_addr: endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Close(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{  
  PCD_EPTypeDef *ep;
  
  if ((ep_addr & 0x80) == 0x80)
  {
    ep = &hpcd->IN_ep[ep_addr & 0x7F];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & 0x7F];
  }
  ep->num   = ep_addr & 0x7F;
  
  ep->is_in = (0x80 & ep_addr) != 0;
  
  __HAL_LOCK(hpcd); 

  if (ep->doublebuffer == 0) 
  {
    if (ep->is_in)
    {
      PCD_CLEAR_TX_DTOG(hpcd->Instance, ep->num);
      /* Configure DISABLE status for the Endpoint*/
      PCD_SET_EP_TX_STATUS(hpcd->Instance, ep->num, USB_EP_TX_DIS); 
    }
    else
    {
      PCD_CLEAR_RX_DTOG(hpcd->Instance, ep->num);
      /* Configure DISABLE status for the Endpoint*/
      PCD_SET_EP_RX_STATUS(hpcd->Instance, ep->num, USB_EP_RX_DIS);
    }
  }
  /*Double Buffer*/
  else
  { 
    if (ep->is_in==0)
    {
      /* Clear the data toggle bits for the endpoint IN/OUT*/
      PCD_CLEAR_RX_DTOG(hpcd->Instance, ep->num);
      PCD_CLEAR_TX_DTOG(hpcd->Instance, ep->num);
      
      /* Reset value of the data toggle bits for the endpoint out*/
      PCD_TX_DTOG(hpcd->Instance, ep->num);
      
      PCD_SET_EP_RX_STATUS(hpcd->Instance, ep->num, USB_EP_RX_DIS);
      PCD_SET_EP_TX_STATUS(hpcd->Instance, ep->num, USB_EP_TX_DIS);
    }
    else
    {
      /* Clear the data toggle bits for the endpoint IN/OUT*/
      PCD_CLEAR_RX_DTOG(hpcd->Instance, ep->num);
      PCD_CLEAR_TX_DTOG(hpcd->Instance, ep->num);
      PCD_RX_DTOG(hpcd->Instance, ep->num);
      /* Configure DISABLE status for the Endpoint*/
      PCD_SET_EP_TX_STATUS(hpcd->Instance, ep->num, USB_EP_TX_DIS);
      PCD_SET_EP_RX_STATUS(hpcd->Instance, ep->num, USB_EP_RX_DIS);
    }
  } 
  
  __HAL_UNLOCK(hpcd);   
  return HAL_OK;
}


/**
  * @brief  Receive an amount of data  
  * @param  hpcd: PCD handle
  * @param  ep_addr: endpoint address
  * @param  pBuf: pointer to the reception buffer   
  * @param  len: amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Receive(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  
 PCD_EPTypeDef *ep;
  
  ep = &hpcd->OUT_ep[ep_addr & 0x7F];
  
  /*setup and start the Xfer */
  ep->xfer_buff = pBuf;  
  ep->xfer_len = len;
  ep->xfer_count = 0;
  ep->is_in = 0;
  ep->num = ep_addr & 0x7F;
   
  __HAL_LOCK(hpcd); 
   
  /* Multi packet transfer*/
  if (ep->xfer_len > ep->maxpacket)
  {
    len=ep->maxpacket;
    ep->xfer_len-=len; 
  }
  else
  {
    len=ep->xfer_len;
    ep->xfer_len =0;
  }
  
  /* configure and validate Rx endpoint */
  if (ep->doublebuffer == 0) 
  {
    /*Set RX buffer count*/
    PCD_SET_EP_RX_CNT(hpcd->Instance, ep->num, len);
  }
  else
  {
    /*Set the Double buffer counter*/
    PCD_SET_EP_DBUF1_CNT(hpcd->Instance, ep->num, ep->is_in, len);
  } 
  
  PCD_SET_EP_RX_STATUS(hpcd->Instance, ep->num, USB_EP_RX_VALID);
  
  __HAL_UNLOCK(hpcd); 
  
  return HAL_OK;
}

/**
  * @brief  Get Received Data Size
  * @param  hpcd: PCD handle
  * @param  ep_addr: endpoint address
  * @retval Data Size
  */
uint16_t HAL_PCD_EP_GetRxCount(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  return hpcd->OUT_ep[ep_addr & 0x7F].xfer_count;
}
/**
  * @brief  Send an amount of data  
  * @param  hpcd: PCD handle
  * @param  ep_addr: endpoint address
  * @param  pBuf: pointer to the transmission buffer   
  * @param  len: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Transmit(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  PCD_EPTypeDef *ep;
  uint16_t pmabuffer = 0;
    
  ep = &hpcd->IN_ep[ep_addr & 0x7F];
  
  /*setup and start the Xfer */
  ep->xfer_buff = pBuf;  
  ep->xfer_len = len;
  ep->xfer_count = 0;
  ep->is_in = 1;
  ep->num = ep_addr & 0x7F;
  
  __HAL_LOCK(hpcd); 
  
  /*Multi packet transfer*/
  if (ep->xfer_len > ep->maxpacket)
  {
    len=ep->maxpacket;
    ep->xfer_len-=len; 
  }
  else
  {  
    len=ep->xfer_len;
    ep->xfer_len =0;
  }
  
  /* configure and validate Tx endpoint */
  if (ep->doublebuffer == 0) 
  {
    PCD_WritePMA(hpcd->Instance, ep->xfer_buff, ep->pmaadress, len);
    PCD_SET_EP_TX_CNT(hpcd->Instance, ep->num, len);
  }
  else
  {
    /*Set the Double buffer counter*/
    PCD_SET_EP_DBUF1_CNT(hpcd->Instance, ep->num, ep->is_in, len);
    
    /*Write the data to the USB endpoint*/
    if (PCD_GET_ENDPOINT(hpcd->Instance, ep->num)& USB_EP_DTOG_TX)
    {
      pmabuffer = ep->pmaaddr1;
    }
    else
    {
      pmabuffer = ep->pmaaddr0;
    }
    PCD_WritePMA(hpcd->Instance, ep->xfer_buff, pmabuffer, len);
    PCD_FreeUserBuffer(hpcd->Instance, ep->num, ep->is_in);
  }

  PCD_SET_EP_TX_STATUS(hpcd->Instance, ep->num, USB_EP_TX_VALID);
  
  __HAL_UNLOCK(hpcd);
     
  return HAL_OK;
}

/**
  * @brief  Set a STALL condition over an endpoint
  * @param  hpcd: PCD handle
  * @param  ep_addr: endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_SetStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_EPTypeDef *ep;
   
  __HAL_LOCK(hpcd); 
   
  if ((0x80 & ep_addr) == 0x80)
  {
    ep = &hpcd->IN_ep[ep_addr & 0x7F];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr];
  }
  
  ep->is_stall = 1;
  ep->num   = ep_addr & 0x7F;
  ep->is_in = ((ep_addr & 0x80) == 0x80);
  
  if (ep->num == 0)
  {
    /* This macro sets STALL status for RX & TX*/ 
    PCD_SET_EP_TXRX_STATUS(hpcd->Instance, ep->num, USB_EP_RX_STALL, USB_EP_TX_STALL); 
  }
  else
  {
    if (ep->is_in)
    {
      PCD_SET_EP_TX_STATUS(hpcd->Instance, ep->num , USB_EP_TX_STALL); 
    }
    else
    {
      PCD_SET_EP_RX_STATUS(hpcd->Instance, ep->num , USB_EP_RX_STALL);
    }
  }
  __HAL_UNLOCK(hpcd); 
  
  return HAL_OK;
}

/**
  * @brief  Clear a STALL condition over in an endpoint
  * @param  hpcd: PCD handle
  * @param  ep_addr: endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_ClrStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_EPTypeDef *ep;
  
  if ((0x80 & ep_addr) == 0x80)
  {
    ep = &hpcd->IN_ep[ep_addr & 0x7F];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr];
  }
  
  ep->is_stall = 0;
  ep->num   = ep_addr & 0x7F;
  ep->is_in = ((ep_addr & 0x80) == 0x80);
  
  __HAL_LOCK(hpcd); 
  
  if (ep->is_in)
  {
    PCD_CLEAR_TX_DTOG(hpcd->Instance, ep->num);
    PCD_SET_EP_TX_STATUS(hpcd->Instance, ep->num, USB_EP_TX_VALID);
  }
  else
  {
    PCD_CLEAR_RX_DTOG(hpcd->Instance, ep->num);
    PCD_SET_EP_RX_STATUS(hpcd->Instance, ep->num, USB_EP_RX_VALID);
  }
  __HAL_UNLOCK(hpcd); 
    
  return HAL_OK;
}

/**
  * @brief  Flush an endpoint
  * @param  hpcd: PCD handle
  * @param  ep_addr: endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Flush(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{ 
  return HAL_OK;
}

/**
  * @brief  HAL_PCD_ActiveRemoteWakeup : active remote wakeup signalling
  * @param  hpcd: PCD handle
  * @retval status
  */
HAL_StatusTypeDef HAL_PCD_ActiveRemoteWakeup(PCD_HandleTypeDef *hpcd)
{
  hpcd->Instance->CNTR |= USB_CNTR_RESUME;
  return HAL_OK;  
}

/**
  * @brief  HAL_PCD_DeActiveRemoteWakeup : de-active remote wakeup signalling
  * @param  hpcd: PCD handle
  * @retval status
  */
HAL_StatusTypeDef HAL_PCD_DeActiveRemoteWakeup(PCD_HandleTypeDef *hpcd)
{
  hpcd->Instance->CNTR &= ~(USB_CNTR_RESUME);
  return HAL_OK;  
}

/**
  * @}
  */
  
/** @defgroup PCD_Exported_Functions_Group4 Peripheral State functions 
 *  @brief   Peripheral State functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================  
    [..]
    This subsection permit to get in run-time the status of the peripheral 
    and the data flow.

@endverbatim
  * @{
  */


/**
  * @brief  Return the PCD state
  * @param  hpcd : PCD handle
  * @retval HAL state
  */
PCD_StateTypeDef HAL_PCD_GetState(PCD_HandleTypeDef *hpcd)
{
  return hpcd->State;
}


/**
  * @brief  Software Device Connection
  * @param  hpcd: PCD handle
  * @param  state: Device state
  * @retval None
  */
 __weak void HAL_PCDEx_SetConnectionState(PCD_HandleTypeDef *hpcd, uint8_t state)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCDEx_SetConnectionState could be implenetd in the user file
   */ 
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup PCD_Private_Functions
  * @{
  */


/**
  * @brief  This function handles PCD Endpoint interrupt request.
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
static HAL_StatusTypeDef PCD_EP_ISR_Handler(PCD_HandleTypeDef *hpcd)
{
  PCD_EPTypeDef *ep;
  uint16_t count=0;
  uint8_t EPindex;
  __IO uint16_t wIstr;  
  __IO uint16_t wEPVal = 0;
  
  /* stay in loop while pending interrupts */
  while (((wIstr = hpcd->Instance->ISTR) & USB_ISTR_CTR) != 0)
  {
    /* extract highest priority endpoint number */
    EPindex = (uint8_t)(wIstr & USB_ISTR_EP_ID);
    
    if (EPindex == 0)
    {
      /* Decode and service control endpoint interrupt */
      
      /* DIR bit = origin of the interrupt */   
      if ((wIstr & USB_ISTR_DIR) == 0)
      {
        /* DIR = 0 */
        
        /* DIR = 0      => IN  int */
        /* DIR = 0 implies that (EP_CTR_TX = 1) always  */
        PCD_CLEAR_TX_EP_CTR(hpcd->Instance, PCD_ENDP0);
        ep = &hpcd->IN_ep[0];
        
        ep->xfer_count = PCD_GET_EP_TX_CNT(hpcd->Instance, ep->num);
        ep->xfer_buff += ep->xfer_count;
 
        /* TX COMPLETE */
        HAL_PCD_DataInStageCallback(hpcd, 0);
        
        
        if((hpcd->USB_Address > 0)&& ( ep->xfer_len == 0))
        {
          hpcd->Instance->DADDR = (hpcd->USB_Address | USB_DADDR_EF);
          hpcd->USB_Address = 0;
        }
        
      }
      else
      {
        /* DIR = 1 */
        
        /* DIR = 1 & CTR_RX       => SETUP or OUT int */
        /* DIR = 1 & (CTR_TX | CTR_RX) => 2 int pending */
        ep = &hpcd->OUT_ep[0];
        wEPVal = PCD_GET_ENDPOINT(hpcd->Instance, PCD_ENDP0);
        
        if ((wEPVal & USB_EP_SETUP) != 0)
        {
          /* Get SETUP Packet*/
          ep->xfer_count = PCD_GET_EP_RX_CNT(hpcd->Instance, ep->num);
          PCD_ReadPMA(hpcd->Instance, (uint8_t*)hpcd->Setup ,ep->pmaadress , ep->xfer_count);       
          /* SETUP bit kept frozen while CTR_RX = 1*/ 
          PCD_CLEAR_RX_EP_CTR(hpcd->Instance, PCD_ENDP0); 
          
          /* Process SETUP Packet*/
          HAL_PCD_SetupStageCallback(hpcd);
        }
        
        else if ((wEPVal & USB_EP_CTR_RX) != 0)
        {
          PCD_CLEAR_RX_EP_CTR(hpcd->Instance, PCD_ENDP0);
          /* Get Control Data OUT Packet*/
          ep->xfer_count = PCD_GET_EP_RX_CNT(hpcd->Instance, ep->num);
          
          if (ep->xfer_count != 0)
          {
            PCD_ReadPMA(hpcd->Instance, ep->xfer_buff, ep->pmaadress, ep->xfer_count);
            ep->xfer_buff+=ep->xfer_count;
          }
          
          /* Process Control Data OUT Packet*/
           HAL_PCD_DataOutStageCallback(hpcd, 0);
          
          PCD_SET_EP_RX_CNT(hpcd->Instance, PCD_ENDP0, ep->maxpacket);
          PCD_SET_EP_RX_STATUS(hpcd->Instance, PCD_ENDP0, USB_EP_RX_VALID);
        }
      }
    }
    else
    {
      
      /* Decode and service non control endpoints interrupt  */
      
      /* process related endpoint register */
      wEPVal = PCD_GET_ENDPOINT(hpcd->Instance, EPindex);
      if ((wEPVal & USB_EP_CTR_RX) != 0)
      {  
        /* clear int flag */
        PCD_CLEAR_RX_EP_CTR(hpcd->Instance, EPindex);
        ep = &hpcd->OUT_ep[EPindex];
        
        /* OUT double Buffering*/
        if (ep->doublebuffer == 0)
        {
          count = PCD_GET_EP_RX_CNT(hpcd->Instance, ep->num);
          if (count != 0)
          {
            PCD_ReadPMA(hpcd->Instance, ep->xfer_buff, ep->pmaadress, count);
          }
        }
        else
        {
          if (PCD_GET_ENDPOINT(hpcd->Instance, ep->num) & USB_EP_DTOG_RX)
          {
            /*read from endpoint BUF0Addr buffer*/
            count = PCD_GET_EP_DBUF0_CNT(hpcd->Instance, ep->num);
            if (count != 0)
            {
              PCD_ReadPMA(hpcd->Instance, ep->xfer_buff, ep->pmaaddr0, count);
            }
          }
          else
          {
            /*read from endpoint BUF1Addr buffer*/
            count = PCD_GET_EP_DBUF1_CNT(hpcd->Instance, ep->num);
            if (count != 0)
            {
              PCD_ReadPMA(hpcd->Instance, ep->xfer_buff, ep->pmaaddr1, count);
            }
          }
          PCD_FreeUserBuffer(hpcd->Instance, ep->num, PCD_EP_DBUF_OUT);  
        }
        /*multi-packet on the NON control OUT endpoint*/
        ep->xfer_count+=count;
        ep->xfer_buff+=count;
       
        if ((ep->xfer_len == 0) || (count < ep->maxpacket))
        {
          /* RX COMPLETE */
          HAL_PCD_DataOutStageCallback(hpcd, ep->num);
        }
        else
        {
          HAL_PCD_EP_Receive(hpcd, ep->num, ep->xfer_buff, ep->xfer_len);
        }
        
      } /* if((wEPVal & EP_CTR_RX) */
      
      if ((wEPVal & USB_EP_CTR_TX) != 0)
      {
        ep = &hpcd->IN_ep[EPindex];
        
        /* clear int flag */
        PCD_CLEAR_TX_EP_CTR(hpcd->Instance, EPindex);
        
        /* IN double Buffering*/
        if (ep->doublebuffer == 0)
        {
          ep->xfer_count = PCD_GET_EP_TX_CNT(hpcd->Instance, ep->num);
          if (ep->xfer_count != 0)
          {
            PCD_WritePMA(hpcd->Instance, ep->xfer_buff, ep->pmaadress, ep->xfer_count);
          }
        }
        else
        {
          if (PCD_GET_ENDPOINT(hpcd->Instance, ep->num) & USB_EP_DTOG_TX)
          {
            /*read from endpoint BUF0Addr buffer*/
            ep->xfer_count = PCD_GET_EP_DBUF0_CNT(hpcd->Instance, ep->num);
            if (ep->xfer_count != 0)
            {
              PCD_WritePMA(hpcd->Instance, ep->xfer_buff, ep->pmaaddr0, ep->xfer_count);
            }
          }
          else
          {
            /*read from endpoint BUF1Addr buffer*/
            ep->xfer_count = PCD_GET_EP_DBUF1_CNT(hpcd->Instance, ep->num);
            if (ep->xfer_count != 0)
            {
              PCD_WritePMA(hpcd->Instance, ep->xfer_buff, ep->pmaaddr1, ep->xfer_count);
            }
          }
          PCD_FreeUserBuffer(hpcd->Instance, ep->num, PCD_EP_DBUF_IN);  
        }
        /*multi-packet on the NON control IN endpoint*/
        ep->xfer_count = PCD_GET_EP_TX_CNT(hpcd->Instance, ep->num);
        ep->xfer_buff+=ep->xfer_count;
       
        /* Zero Length Packet? */
        if (ep->xfer_len == 0)
        {
          /* TX COMPLETE */
          HAL_PCD_DataInStageCallback(hpcd, ep->num);
        }
        else
        {
          HAL_PCD_EP_Transmit(hpcd, ep->num, ep->xfer_buff, ep->xfer_len);
        }
      } 
    }
  }
  return HAL_OK;
}

/**
  * @brief Copy a buffer from user memory area to packet memory area (PMA)
  * @param   USBx    = pointer to USB register.
  * @param   pbUsrBuf: pointer to user memory area.
  * @param   wPMABufAddr: address into PMA.
  * @param   wNBytes: no. of bytes to be copied.
  * @retval None
  */
static void PCD_WritePMA(USB_TypeDef  *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
  uint32_t n = (wNBytes + 1) >> 1;   /* n = (wNBytes + 1) / 2 */
  uint32_t i, temp1, temp2;
  uint16_t *pdwVal;
  pdwVal = (uint16_t *)(wPMABufAddr * 2 + (uint32_t)USBx + 0x400);
  for (i = n; i != 0; i--)
  {
    temp1 = (uint16_t) * pbUsrBuf;
    pbUsrBuf++;
    temp2 = temp1 | (uint16_t) * pbUsrBuf << 8;
    *pdwVal++ = temp2;
    pdwVal++;
    pbUsrBuf++;
  }
}

/**
  * @brief Copy a buffer from user memory area to packet memory area (PMA)
  * @param   USBx    = pointer to USB register.
  * @param   pbUsrBuf    = pointer to user memory area.
  * @param   wPMABufAddr: address into PMA.
  * @param   wNBytes: no. of bytes to be copied.
  * @retval None
  */
static void PCD_ReadPMA(USB_TypeDef  *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
  uint32_t n = (wNBytes + 1) >> 1;/* /2*/
  uint32_t i;
  uint32_t *pdwVal;
  pdwVal = (uint32_t *)(wPMABufAddr * 2 + (uint32_t)USBx + 0x400);
  for (i = n; i != 0; i--)
  {
    *(uint16_t*)pbUsrBuf++ = *pdwVal++;
    pbUsrBuf++;
  }
}

/**
  * @}
  */

#endif /* HAL_PCD_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
