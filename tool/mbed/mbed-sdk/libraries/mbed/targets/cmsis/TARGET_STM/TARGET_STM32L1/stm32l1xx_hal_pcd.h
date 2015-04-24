/**
  ******************************************************************************
  * @file    stm32l1xx_hal_pcd.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file of PCD HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_HAL_PCD_H
#define __STM32L1xx_HAL_PCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup PCD
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup PCD_Exported_Types PCD Exported Types
  * @{
  */

   /** 
  * @brief  PCD State structures definition  
  */  
typedef enum 
{
  PCD_READY    = 0x00,
  PCD_ERROR    = 0x01,
  PCD_BUSY     = 0x02,
  PCD_TIMEOUT  = 0x03
} PCD_StateTypeDef;

typedef enum
{
  /* double buffered endpoint direction */
  PCD_EP_DBUF_OUT,
  PCD_EP_DBUF_IN,
  PCD_EP_DBUF_ERR,
}PCD_EP_DBUF_DIR;

/* endpoint buffer number */
typedef enum 
{
  PCD_EP_NOBUF,
  PCD_EP_BUF0,
  PCD_EP_BUF1
}PCD_EP_BUF_NUM;  

/** 
  * @brief  PCD Initialization Structure definition  
  */
typedef struct
{
  uint32_t dev_endpoints;        /*!< Device Endpoints number.
                                      This parameter depends on the used USB core.   
                                      This parameter must be a number between Min_Data = 1 and Max_Data = 15 */    

  uint32_t speed;                /*!< USB Core speed.
                                      This parameter can be any value of @ref USB_Core_Speed                 */        
                             
  uint32_t ep0_mps;              /*!< Set the Endpoint 0 Max Packet size. 
                                      This parameter can be any value of @ref USB_EP0_MPS                    */              
                       
  uint32_t phy_itface;           /*!< Select the used PHY interface.
                                      This parameter can be any value of @ref USB_Core_PHY                   */ 
                                
  uint32_t Sof_enable;           /*!< Enable or disable the output of the SOF signal.                        */  
  
  uint32_t low_power_enable;       /*!< Enable or disable Low Power mode                                      */ 
  
  uint32_t lpm_enable;             /*!< Enable or disable Battery charging.                                  */    

  uint32_t battery_charging_enable; /*!< Enable or disable Battery charging.                                  */    
                                
}PCD_InitTypeDef;

typedef struct
{
  uint8_t   num;            /*!< Endpoint number
                                This parameter must be a number between Min_Data = 1 and Max_Data = 15    */ 
                                
  uint8_t   is_in;          /*!< Endpoint direction
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1     */ 
  
  uint8_t   is_stall;       /*!< Endpoint stall condition
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1     */ 
  
  uint8_t   type;           /*!< Endpoint type
                                 This parameter can be any value of @ref USB_EP_Type                      */ 
                                
  uint16_t  pmaadress;      /*!< PMA Address
                                 This parameter can be any value between Min_addr = 0 and Max_addr = 1K   */ 
  
  
  uint16_t  pmaaddr0;       /*!< PMA Address0
                                 This parameter can be any value between Min_addr = 0 and Max_addr = 1K   */   
  
  
  uint16_t  pmaaddr1;        /*!< PMA Address1
                                 This parameter can be any value between Min_addr = 0 and Max_addr = 1K   */   
  
  
  uint8_t   doublebuffer;    /*!< Double buffer enable
                                 This parameter can be 0 or 1                                             */    
                                
  uint32_t  maxpacket;      /*!< Endpoint Max packet size
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 64KB */

  uint8_t   *xfer_buff;     /*!< Pointer to transfer buffer                                               */
                                
  
  uint32_t  xfer_len;       /*!< Current transfer length                                                  */
  
  uint32_t  xfer_count;     /*!< Partial transfer length in case of multi packet transfer                 */

}PCD_EPTypeDef;

typedef   USB_TypeDef PCD_TypeDef; 

/** 
  * @brief  PCD Handle Structure definition  
  */ 
typedef struct
{
  PCD_TypeDef             *Instance;   /*!< Register base address              */ 
  PCD_InitTypeDef         Init;       /*!< PCD required parameters            */
  __IO uint8_t            USB_Address; /*!< USB Address            */  
  PCD_EPTypeDef           IN_ep[8];  /*!< IN endpoint parameters             */
  PCD_EPTypeDef           OUT_ep[8]; /*!< OUT endpoint parameters            */ 
  HAL_LockTypeDef         Lock;       /*!< PCD peripheral status              */
  __IO PCD_StateTypeDef   State;      /*!< PCD communication state            */
  uint32_t                Setup[12];  /*!< Setup packet buffer                */
  void                    *pData;      /*!< Pointer to upper stack Handler     */    
  
} PCD_HandleTypeDef;

/**
  * @}
  */

#include "stm32l1xx_hal_pcd_ex.h"    
/* Exported constants --------------------------------------------------------*/
/** @defgroup PCD_Exported_Constants PCD Exported Constants
  * @{
  */

/** @defgroup USB_Exti_Line_Wakeup USB_Exti_Line_Wakeup
  * @{
  */

#define  USB_EXTI_LINE_WAKEUP              ((uint32_t)0x00040000)  /*!< External interrupt line 18 Connected to the USB FS EXTI Line */
/**
  * @}
  */


/** @defgroup USB_Core_Speed USB Core Speed
  * @{
  */
#define PCD_SPEED_HIGH               0 /* Not Supported */
#define PCD_SPEED_FULL               2
/**
  * @}
  */
  
  /** @defgroup USB_Core_PHY USB Core PHY
  * @{
  */
#define PCD_PHY_EMBEDDED             2
/**
  * @}
  */

/** @defgroup USB_EP0_MPS USB EP0 MPS
  * @{
  */
#define DEP0CTL_MPS_64                         0
#define DEP0CTL_MPS_32                         1
#define DEP0CTL_MPS_16                         2
#define DEP0CTL_MPS_8                          3

#define PCD_EP0MPS_64                          DEP0CTL_MPS_64
#define PCD_EP0MPS_32                          DEP0CTL_MPS_32
#define PCD_EP0MPS_16                          DEP0CTL_MPS_16
#define PCD_EP0MPS_08                          DEP0CTL_MPS_8 
/**
  * @}
  */ 

/** @defgroup USB_EP_Type USB EP Type
  * @{
  */
#define PCD_EP_TYPE_CTRL                                 0
#define PCD_EP_TYPE_ISOC                                 1
#define PCD_EP_TYPE_BULK                                 2
#define PCD_EP_TYPE_INTR                                 3
/**
  * @}
  */ 

/** @defgroup USB_ENDP_Type USB_ENDP_Type
  * @{
  */

#define PCD_ENDP0                             ((uint8_t)0)
#define PCD_ENDP1                             ((uint8_t)1)
#define PCD_ENDP2                             ((uint8_t)2)
#define PCD_ENDP3                             ((uint8_t)3)
#define PCD_ENDP4                             ((uint8_t)4)
#define PCD_ENDP5                             ((uint8_t)5)
#define PCD_ENDP6                             ((uint8_t)6)
#define PCD_ENDP7                             ((uint8_t)7)

/*  Endpoint Kind */
#define PCD_SNG_BUF                                      0
#define PCD_DBL_BUF                                      1

#define IS_PCD_ALL_INSTANCE                              IS_USB_ALL_INSTANCE                          

/**
  * @}
  */ 


/**
  * @}
  */ 
  
/* Exported macros -----------------------------------------------------------*/

/** @defgroup PCD_Exported_Macros PCD Exported Macros
 *  @brief macros to handle interrupts and specific clock configurations
 * @{
 */
#define __HAL_PCD_GET_FLAG(__HANDLE__, __INTERRUPT__)      ((((__HANDLE__)->Instance->ISTR) & (__INTERRUPT__)) == (__INTERRUPT__))
#define __HAL_PCD_CLEAR_FLAG(__HANDLE__, __INTERRUPT__)    (((__HANDLE__)->Instance->ISTR) &= ~(__INTERRUPT__))

#define __HAL_USB_EXTI_ENABLE_IT()    EXTI->IMR |= USB_EXTI_LINE_WAKEUP
#define __HAL_USB_EXTI_DISABLE_IT()   EXTI->IMR &= ~(USB_EXTI_LINE_WAKEUP)
#define __HAL_USB_EXTI_GET_FLAG()     EXTI->PR & (USB_EXTI_LINE_WAKEUP)
#define __HAL_USB_EXTI_CLEAR_FLAG()   EXTI->PR = USB_EXTI_LINE_WAKEUP

#define __HAL_USB_EXTI_SET_RISING_EDGE_TRIGGER() EXTI->FTSR &= ~(USB_EXTI_LINE_WAKEUP);\
                                                    EXTI->RTSR |= USB_EXTI_LINE_WAKEUP

                                                      
#define __HAL_USB_EXTI_SET_FALLING_EDGE_TRIGGER()  EXTI->FTSR |= (USB_EXTI_LINE_WAKEUP);\
                                                      EXTI->RTSR &= ~(USB_EXTI_LINE_WAKEUP)


#define __HAL_USB_EXTI_SET_FALLINGRISING_TRIGGER()  EXTI->RTSR &= ~(USB_EXTI_LINE_WAKEUP);\
                                                       EXTI->FTSR &= ~(USB_EXTI_LINE_WAKEUP);\
                                                       EXTI->RTSR |= USB_EXTI_LINE_WAKEUP;\
                                                       EXTI->FTSR |= USB_EXTI_LINE_WAKEUP                                                  

/**
  * @}
  */

/* Internal macros -----------------------------------------------------------*/

/** @defgroup PCD_Private_Macros PCD Private Macros
 *  @brief macros to handle interrupts and specific clock configurations
 * @{
 */

/* SetENDPOINT */
#define PCD_SET_ENDPOINT(USBx, bEpNum,wRegValue)  (*(&(USBx)->EP0R + (bEpNum) * 2)= (uint16_t)(wRegValue))

/* GetENDPOINT */
#define PCD_GET_ENDPOINT(USBx, bEpNum)        (*(&(USBx)->EP0R + (bEpNum) * 2))



/**
  * @brief  sets the type in the endpoint register(bits EP_TYPE[1:0])
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  wType: Endpoint Type.
  * @retval None
  */
#define PCD_SET_EPTYPE(USBx, bEpNum,wType) (PCD_SET_ENDPOINT((USBx), (bEpNum),\
                                  ((PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EP_T_MASK) | (wType) )))

/**
  * @brief  gets the type in the endpoint register(bits EP_TYPE[1:0])
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval Endpoint Type
  */
#define PCD_GET_EPTYPE(USBx, bEpNum) (PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EP_T_FIELD)


/**
  * @brief free buffer used from the application realizing it to the line
          toggles bit SW_BUF in the double buffered endpoint register
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  bDir: Direction
  * @retval None
  */
#define PCD_FreeUserBuffer(USBx, bEpNum, bDir)\
{\
  if ((bDir) == PCD_EP_DBUF_OUT)\
  { /* OUT double buffered endpoint */\
    PCD_TX_DTOG((USBx), (bEpNum));\
  }\
  else if ((bDir) == PCD_EP_DBUF_IN)\
  { /* IN double buffered endpoint */\
    PCD_RX_DTOG((USBx), (bEpNum));\
  }\
}

/**
  * @brief gets direction of the double buffered endpoint
  * @param   USBx: USB peripheral instance register address.
  * @param   bEpNum: Endpoint Number.
  * @retval EP_DBUF_OUT, EP_DBUF_IN,
  *         EP_DBUF_ERR if the endpoint counter not yet programmed.
  */
#define PCD_GET_DB_DIR(USBx, bEpNum)\
{\
  if ((uint16_t)(*PCD_EP_RX_CNT((USBx), (bEpNum)) & 0xFC00) != 0)\
    return(PCD_EP_DBUF_OUT);\
  else if (((uint16_t)(*PCD_EP_TX_CNT((USBx), (bEpNum))) & 0x03FF) != 0)\
    return(PCD_EP_DBUF_IN);\
  else\
    return(PCD_EP_DBUF_ERR);\
}

/**
  * @brief  sets the status for tx transfer (bits STAT_TX[1:0]).
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  wState: new state
  * @retval None
  */
#define PCD_SET_EP_TX_STATUS(USBx, bEpNum, wState) { register uint16_t _wRegVal;\
   \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPTX_DTOGMASK;\
   /* toggle first bit ? */     \
   if((USB_EPTX_DTOG1 & (wState))!= 0)      \
   {                                                                            \
     _wRegVal ^= USB_EPTX_DTOG1;        \
   }                                                                            \
   /* toggle second bit ?  */         \
   if((USB_EPTX_DTOG2 & (wState))!= 0)      \
   {                                                                            \
     _wRegVal ^= USB_EPTX_DTOG2;        \
   }                                                                            \
   PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_RX|USB_EP_CTR_TX));    \
  } /* PCD_SET_EP_TX_STATUS */

/**
  * @brief  sets the status for rx transfer (bits STAT_TX[1:0])
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  wState: new state
  * @retval None
  */
#define PCD_SET_EP_RX_STATUS(USBx, bEpNum,wState) {\
    register uint16_t _wRegVal;   \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPRX_DTOGMASK;\
    /* toggle first bit ? */  \
    if((USB_EPRX_DTOG1 & (wState))!= 0) \
    {                                                                             \
      _wRegVal ^= USB_EPRX_DTOG1;  \
    }                                                                             \
    /* toggle second bit ? */  \
    if((USB_EPRX_DTOG2 & (wState))!= 0) \
    {                                                                             \
      _wRegVal ^= USB_EPRX_DTOG2;  \
    }                                                                             \
    PCD_SET_ENDPOINT((USBx), (bEpNum), (_wRegVal | USB_EP_CTR_RX|USB_EP_CTR_TX)); \
  } /* PCD_SET_EP_RX_STATUS */

/**
  * @brief  sets the status for rx & tx (bits STAT_TX[1:0] & STAT_RX[1:0])
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  wStaterx: new state.
  * @param  wStatetx: new state.
  * @retval None
  */
#define PCD_SET_EP_TXRX_STATUS(USBx,bEpNum,wStaterx,wStatetx) {\
    register uint32_t _wRegVal;   \
    \
    _wRegVal = PCD_GET_ENDPOINT((USBx), (bEpNum)) & (USB_EPRX_DTOGMASK |USB_EPTX_STAT) ;\
    /* toggle first bit ? */  \
    if((USB_EPRX_DTOG1 & ((wStaterx)))!= 0) \
    {                                                                                    \
      _wRegVal ^= USB_EPRX_DTOG1;  \
    }                                                                                    \
    /* toggle second bit ? */  \
    if((USB_EPRX_DTOG2 & (wStaterx))!= 0) \
    {                                                                                    \
      _wRegVal ^= USB_EPRX_DTOG2;  \
    }                                                                                    \
    /* toggle first bit ? */     \
    if((USB_EPTX_DTOG1 & (wStatetx))!= 0)      \
    {                                                                                    \
      _wRegVal ^= USB_EPTX_DTOG1;        \
    }                                                                                    \
    /* toggle second bit ?  */         \
    if((USB_EPTX_DTOG2 & (wStatetx))!= 0)      \
    {                                                                                    \
      _wRegVal ^= USB_EPTX_DTOG2;        \
    }                                                                                    \
    PCD_SET_ENDPOINT((USBx), (bEpNum), _wRegVal | USB_EP_CTR_RX|USB_EP_CTR_TX);    \
  } /* PCD_SET_EP_TXRX_STATUS */

/**
  * @brief  gets the status for tx/rx transfer (bits STAT_TX[1:0]
  *         /STAT_RX[1:0])
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval status
  */
#define PCD_GET_EP_TX_STATUS(USBx, bEpNum) ((uint16_t)PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPTX_STAT)

#define PCD_GET_EP_RX_STATUS(USBx, bEpNum) ((uint16_t)PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPRX_STAT)

/**
  * @brief  sets directly the VALID tx/rx-status into the endpoint register
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
#define PCD_SET_EP_TX_VALID(USBx, bEpNum)     (PCD_SET_EP_TX_STATUS((USBx), (bEpNum), USB_EP_TX_VALID))

#define PCD_SET_EP_RX_VALID(USBx, bEpNum)     (PCD_SET_EP_RX_STATUS((USBx), (bEpNum), USB_EP_RX_VALID))

/**
  * @brief  checks stall condition in an endpoint.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval TRUE = endpoint in stall condition.
  */
#define PCD_GET_EP_TX_STALL_STATUS(USBx, bEpNum) (PCD_GET_EP_TX_STATUS((USBx), (bEpNum)) \
                                   == USB_EP_TX_STALL)
#define PCD_GET_EP_RX_STALL_STATUS(USBx, bEpNum) (PCD_GET_EP_RX_STATUS((USBx), (bEpNum)) \
                                   == USB_EP_RX_STALL)

/**
  * @brief  set & clear EP_KIND bit.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
#define PCD_SET_EP_KIND(USBx, bEpNum)    (PCD_SET_ENDPOINT((USBx), (bEpNum), \
                                (USB_EP_CTR_RX|USB_EP_CTR_TX|((PCD_GET_ENDPOINT((USBx), (bEpNum)) | USB_EP_KIND) & USB_EPREG_MASK))))
#define PCD_CLEAR_EP_KIND(USBx, bEpNum)  (PCD_SET_ENDPOINT((USBx), (bEpNum), \
                                (USB_EP_CTR_RX|USB_EP_CTR_TX|(PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPKIND_MASK))))

/**
  * @brief  Sets/clears directly STATUS_OUT bit in the endpoint register.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
#define PCD_SET_OUT_STATUS(USBx, bEpNum)    PCD_SET_EP_KIND((USBx), (bEpNum))
#define PCD_CLEAR_OUT_STATUS(USBx, bEpNum)  PCD_CLEAR_EP_KIND((USBx), (bEpNum))

/**
  * @brief  Sets/clears directly EP_KIND bit in the endpoint register.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
#define PCD_SET_EP_DBUF(USBx, bEpNum)   PCD_SET_EP_KIND((USBx), (bEpNum))
#define PCD_CLEAR_EP_DBUF(USBx, bEpNum) PCD_CLEAR_EP_KIND((USBx), (bEpNum))

/**
  * @brief  Clears bit CTR_RX / CTR_TX in the endpoint register.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
#define PCD_CLEAR_RX_EP_CTR(USBx, bEpNum)   (PCD_SET_ENDPOINT((USBx), (bEpNum),\
                                   PCD_GET_ENDPOINT((USBx), (bEpNum)) & 0x7FFF & USB_EPREG_MASK))
#define PCD_CLEAR_TX_EP_CTR(USBx, bEpNum)   (PCD_SET_ENDPOINT((USBx), (bEpNum),\
                                   PCD_GET_ENDPOINT((USBx), (bEpNum)) & 0xFF7F & USB_EPREG_MASK))

/**
  * @brief  Toggles DTOG_RX / DTOG_TX bit in the endpoint register.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
#define PCD_RX_DTOG(USBx, bEpNum)    (PCD_SET_ENDPOINT((USBx), (bEpNum), \
                                   USB_EP_CTR_RX|USB_EP_CTR_TX|USB_EP_DTOG_RX | (PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPREG_MASK)))
#define PCD_TX_DTOG(USBx, bEpNum)    (PCD_SET_ENDPOINT((USBx), (bEpNum), \
                                   USB_EP_CTR_RX|USB_EP_CTR_TX|USB_EP_DTOG_TX | (PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPREG_MASK)))

/**
  * @brief  Clears DTOG_RX / DTOG_TX bit in the endpoint register.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
#define PCD_CLEAR_RX_DTOG(USBx, bEpNum)  if((PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EP_DTOG_RX) != 0)\
                                         {                                                              \
                                           PCD_RX_DTOG((USBx), (bEpNum));                               \
                                         }
#define PCD_CLEAR_TX_DTOG(USBx, bEpNum)  if((PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EP_DTOG_TX) != 0)\
                                         {                                                              \
                                            PCD_TX_DTOG((USBx), (bEpNum));                              \
                                         }
      
/**
  * @brief  Sets address in an endpoint register.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  bAddr: Address.
  * @retval None
  */
#define PCD_SET_EP_ADDRESS(USBx, bEpNum,bAddr) PCD_SET_ENDPOINT((USBx), (bEpNum),\
    USB_EP_CTR_RX|USB_EP_CTR_TX|(PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPREG_MASK) | (bAddr))

#define PCD_GET_EP_ADDRESS(USBx, bEpNum) ((uint8_t)(PCD_GET_ENDPOINT((USBx), (bEpNum)) & USB_EPADDR_FIELD))

#define PCD_EP_TX_ADDRESS(USBx, bEpNum) ((uint32_t *)(((USBx)->BTABLE+(bEpNum)*8)*2+     ((uint32_t)(USBx) + 0x400)))
#define PCD_EP_TX_CNT(USBx, bEpNum) ((uint32_t *)(((USBx)->BTABLE+(bEpNum)*8+2)*2+  ((uint32_t)(USBx) + 0x400)))
#define PCD_EP_RX_ADDRESS(USBx, bEpNum) ((uint32_t *)(((USBx)->BTABLE+(bEpNum)*8+4)*2+  ((uint32_t)(USBx) + 0x400)))
#define PCD_EP_RX_CNT(USBx, bEpNum) ((uint32_t *)(((USBx)->BTABLE+(bEpNum)*8+6)*2+  ((uint32_t)(USBx) + 0x400)))
      
#define PCD_SET_EP_RX_CNT(USBx, bEpNum,wCount) {\
    uint32_t *pdwReg = PCD_EP_RX_CNT((USBx), (bEpNum)); \
    PCD_SET_EP_CNT_RX_REG(pdwReg, (wCount));\
  }

/**
  * @brief  sets address of the tx/rx buffer.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  wAddr: address to be set (must be word aligned).
  * @retval None
  */
#define PCD_SET_EP_TX_ADDRESS(USBx, bEpNum,wAddr) (*PCD_EP_TX_ADDRESS((USBx), (bEpNum)) = (((wAddr) >> 1) << 1))
#define PCD_SET_EP_RX_ADDRESS(USBx, bEpNum,wAddr) (*PCD_EP_RX_ADDRESS((USBx), (bEpNum)) = (((wAddr) >> 1) << 1))

/**
  * @brief  Gets address of the tx/rx buffer.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval address of the buffer.
  */
#define PCD_GET_EP_TX_ADDRESS(USBx, bEpNum) ((uint16_t)*PCD_EP_TX_ADDRESS((USBx), (bEpNum)))
#define PCD_GET_EP_RX_ADDRESS(USBx, bEpNum) ((uint16_t)*PCD_EP_RX_ADDRESS((USBx), (bEpNum)))

/**
  * @brief  Sets counter of rx buffer with no. of blocks.
  * @param  dwReg: Register
  * @param  wCount: Counter.
  * @param  wNBlocks: no. of Blocks.
  * @retval None
  */
#define PCD_CALC_BLK32(dwReg,wCount,wNBlocks) {\
    (wNBlocks) = (wCount) >> 5;\
    if(((wCount) & 0x1f) == 0)\
    {                                                  \
      (wNBlocks)--;\
    }                                                  \
    *pdwReg = (uint16_t)((uint16_t)((wNBlocks) << 10) | 0x8000); \
  }/* PCD_CALC_BLK32 */

#define PCD_CALC_BLK2(dwReg,wCount,wNBlocks) {\
    (wNBlocks) = (wCount) >> 1;\
    if(((wCount) & 0x1) != 0)\
    {                                                  \
      (wNBlocks)++;\
    }                                                  \
    *pdwReg = (uint16_t)((wNBlocks) << 10);\
  }/* PCD_CALC_BLK2 */

#define PCD_SET_EP_CNT_RX_REG(dwReg,wCount)  {\
    uint16_t wNBlocks;\
    if((wCount) > 62)                                \
    {                                                \
      PCD_CALC_BLK32((dwReg),(wCount),wNBlocks);     \
    }                                                \
    else                                             \
    {                                                \
      PCD_CALC_BLK2((dwReg),(wCount),wNBlocks);      \
    }                                                \
  }/* PCD_SET_EP_CNT_RX_REG */

#define PCD_SET_EP_RX_DBUF0_CNT(USBx, bEpNum,wCount) {\
    uint16_t *pdwReg = PCD_EP_TX_CNT((USBx), (bEpNum)); \
    PCD_SET_EP_CNT_RX_REG(pdwReg, (wCount));\
  }
/**
  * @brief  sets counter for the tx/rx buffer.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  wCount: Counter value.
  * @retval None
  */
#define PCD_SET_EP_TX_CNT(USBx, bEpNum,wCount) (*PCD_EP_TX_CNT((USBx), (bEpNum)) = (wCount))


/**
  * @brief  gets counter of the tx buffer.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval Counter value
  */
#define PCD_GET_EP_TX_CNT(USBx, bEpNum)((uint16_t)(*PCD_EP_TX_CNT((USBx), (bEpNum))) & 0x3ff)
#define PCD_GET_EP_RX_CNT(USBx, bEpNum)((uint16_t)(*PCD_EP_RX_CNT((USBx), (bEpNum))) & 0x3ff)

/**
  * @brief  Sets buffer 0/1 address in a double buffer endpoint.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  wBuf0Addr: buffer 0 address.
  * @retval Counter value
  */
#define PCD_SET_EP_DBUF0_ADDR(USBx, bEpNum,wBuf0Addr) {PCD_SET_EP_TX_ADDRESS((USBx), (bEpNum), (wBuf0Addr));}
#define PCD_SET_EP_DBUF1_ADDR(USBx, bEpNum,wBuf1Addr) {PCD_SET_EP_RX_ADDRESS((USBx), (bEpNum), (wBuf1Addr));}

/**
  * @brief  Sets addresses in a double buffer endpoint.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  wBuf0Addr: buffer 0 address.
  * @param  wBuf1Addr = buffer 1 address.
  * @retval None
  */
#define PCD_SET_EP_DBUF_ADDR(USBx, bEpNum,wBuf0Addr,wBuf1Addr) { \
    PCD_SET_EP_DBUF0_ADDR((USBx), (bEpNum), (wBuf0Addr));\
    PCD_SET_EP_DBUF1_ADDR((USBx), (bEpNum), (wBuf1Addr));\
  } /* PCD_SET_EP_DBUF_ADDR */

/**
  * @brief  Gets buffer 0/1 address of a double buffer endpoint.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
#define PCD_GET_EP_DBUF0_ADDR(USBx, bEpNum) (PCD_GET_EP_TX_ADDRESS((USBx), (bEpNum)))
#define PCD_GET_EP_DBUF1_ADDR(USBx, bEpNum) (PCD_GET_EP_RX_ADDRESS((USBx), (bEpNum)))

/**
  * @brief  Gets buffer 0/1 address of a double buffer endpoint.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @param  bDir: endpoint dir  EP_DBUF_OUT = OUT 
  *         EP_DBUF_IN  = IN 
  * @param  wCount: Counter value 
  * @retval None
  */
#define PCD_SET_EP_DBUF0_CNT(USBx, bEpNum, bDir, wCount)  { \
    if((bDir) == PCD_EP_DBUF_OUT)\
      /* OUT endpoint */ \
    {PCD_SET_EP_RX_DBUF0_CNT((USBx), (bEpNum),(wCount));} \
    else if((bDir) == PCD_EP_DBUF_IN)\
      /* IN endpoint */ \
      *PCD_EP_TX_CNT((USBx), (bEpNum)) = (uint32_t)(wCount);  \
  } /* SetEPDblBuf0Count*/

#define PCD_SET_EP_DBUF1_CNT(USBx, bEpNum, bDir, wCount)  { \
    if((bDir) == PCD_EP_DBUF_OUT)\
    {/* OUT endpoint */                                       \
      PCD_SET_EP_RX_CNT((USBx), (bEpNum),(wCount));           \
    }                                                         \
    else if((bDir) == PCD_EP_DBUF_IN)\
    {/* IN endpoint */                                        \
      *PCD_EP_RX_CNT((USBx), (bEpNum)) = (uint32_t)(wCount); \
    }                                                         \
  } /* SetEPDblBuf1Count */

#define PCD_SET_EP_DBUF_CNT(USBx, bEpNum, bDir, wCount) {\
    PCD_SET_EP_DBUF0_CNT((USBx), (bEpNum), (bDir), (wCount)); \
    PCD_SET_EP_DBUF1_CNT((USBx), (bEpNum), (bDir), (wCount)); \
  } /* PCD_SET_EP_DBUF_CNT  */

/**
  * @brief  Gets buffer 0/1 rx/tx counter for double buffering.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
#define PCD_GET_EP_DBUF0_CNT(USBx, bEpNum) (PCD_GET_EP_TX_CNT((USBx), (bEpNum)))
#define PCD_GET_EP_DBUF1_CNT(USBx, bEpNum) (PCD_GET_EP_RX_CNT((USBx), (bEpNum)))


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup PCD_Exported_Functions
  * @{
  */

/* Initialization/de-initialization functions  **********************************/


/** @addtogroup PCD_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_PCD_Init(PCD_HandleTypeDef *hpcd);
HAL_StatusTypeDef HAL_PCD_DeInit (PCD_HandleTypeDef *hpcd);
void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd);
void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd);

/**
  * @}
  */

/* I/O operation functions  *****************************************************/
/* Non-Blocking mode: Interrupt */
/** @addtogroup PCD_Exported_Functions_Group2
  * @{
  */

HAL_StatusTypeDef HAL_PCD_Start(PCD_HandleTypeDef *hpcd);
HAL_StatusTypeDef HAL_PCD_Stop(PCD_HandleTypeDef *hpcd);
void HAL_PCD_IRQHandler(PCD_HandleTypeDef *hpcd);

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd);

/**
  * @}
  */

/* Peripheral Control functions  ************************************************/
/** @addtogroup PCD_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_PCD_DevConnect(PCD_HandleTypeDef *hpcd);
HAL_StatusTypeDef HAL_PCD_DevDisconnect(PCD_HandleTypeDef *hpcd);
HAL_StatusTypeDef HAL_PCD_SetAddress(PCD_HandleTypeDef *hpcd, uint8_t address);
HAL_StatusTypeDef HAL_PCD_EP_Open(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type);
HAL_StatusTypeDef HAL_PCD_EP_Close(PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_EP_Receive(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
HAL_StatusTypeDef HAL_PCD_EP_Transmit(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
uint16_t          HAL_PCD_EP_GetRxCount(PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_EP_SetStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_EP_ClrStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_EP_Flush(PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_ActiveRemoteWakeup(PCD_HandleTypeDef *hpcd);
HAL_StatusTypeDef HAL_PCD_DeActiveRemoteWakeup(PCD_HandleTypeDef *hpcd);
/**
  * @}
  */


/* Peripheral State functions  **************************************************/
/** @addtogroup PCD_Exported_Functions_Group4
  * @{
  */
PCD_StateTypeDef HAL_PCD_GetState(PCD_HandleTypeDef *hpcd);
void HAL_PCDEx_SetConnectionState(PCD_HandleTypeDef *hpcd, uint8_t state);
/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* __STM32L1xx_HAL_PCD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
