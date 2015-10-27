/**
  ******************************************************************************
  * @file    stm32l1xx_hal_opamp.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   OPAMP HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities of the operational amplifiers (OPAMP1 ,... ,OPAMP3) 
  *          peripheral: 
  *           + OPAMP configuration
  *           + OPAMP calibration
  *
  *          Thanks to
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *         
  @verbatim
================================================================================
          ##### OPAMP Peripheral Features #####
================================================================================
           
  [..] The device integrates up to 3 operational amplifiers OPAMP1, OPAMP2,
       OPAMP3 (OPAMP3 availability depends on device category)
       
       (#) The OPAMP(s) provides several exclusive running modes.
       (+) Standalone mode
       (+) Follower mode

       (#) The OPAMP(s) provide(s) calibration capabilities.  
       (+) Calibration aims at correcting some offset for running mode.
       (+) The OPAMP uses either factory calibration settings OR user defined 
           calibration (trimming) settings (i.e. trimming mode).
       (+) The user defined settings can be figured out using self calibration 
           handled by HAL_OPAMP_SelfCalibrate, HAL_OPAMPEx_SelfCalibrateAll
       (+) HAL_OPAMP_SelfCalibrate:
       (++) Runs automatically the calibration in 2 steps: for transistors 
            differential pair high (PMOS) or low (NMOS)
       (++) Enables the user trimming mode
       (++) Updates the init structure with trimming values with fresh calibration 
            results.
            The user may store the calibration results for larger 
            (ex monitoring the trimming as a function of temperature 
            for instance)
       (++) for devices having several OPAMPs, HAL_OPAMPEx_SelfCalibrateAll
            runs calibration of all OPAMPs in parallel to save trimming search
            wait time.
             
       (#) Running mode: Standalone mode 
       (+) Gain is set externally (gain depends on external loads).
       (+) Follower mode also possible externally by connecting the inverting input to
           the output.
       
       (#) Running mode: Follower mode
       (+) No Inverting Input is connected.
       (+) The OPAMP(s) output(s) are internally connected to inverting input
        
       (#) The OPAMPs inverting input can be selected among the list shown
           in table below.
       
       (#) The OPAMPs non inverting input can be selected among the list shown
           in table below.
       
   [..] Table 1.  OPAMPs inverting/non-inverting inputs for STM32L1 devices:
     
    +--------------------------------------------------------------------------+
    |                | HAL param  |    OPAMP1    |    OPAMP2    |   OPAMP3(4)  |
    |                |   name     |              |              |              |
    |----------------|------------|--------------|--------------|--------------|
    |   Inverting    |    VM0     |     PA2      |     PA7      |     PC2      |
    |    input (1)   |    VM1     | VINM pin (2) | VINM pin (2) | VINM pin (2) |
    |----------------|------------|--------------|--------------|--------------|
    |  Non Inverting |    VP0     |     PA1      |     PA6      |     PC1      |
    |    input       | DAC_CH1 (3)|   DAC_CH1    |   DAC_CH1    |     ---      |
    |                | DAC_CH2 (3)|     ---      |   DAC_CH2    |   DAC_CH2    |
    +--------------------------------------------------------------------------+
    (1): NA in follower mode.
    (2): OPAMP input OPAMPx_VINM are dedicated OPAMP pins, their availability
         depends on device package.
    (3): DAC channels 1 and 2 are connected internally to OPAMP. Nevertheless,
         I/O pins connected to DAC can still be used as DAC output (pins PA4 
         and PA5).
    (4): OPAMP3 availability depends on device category.


   [..] Table 2.  OPAMPs outputs for STM32L1 devices:

    +--------------------------------------------------------+
    |                 |   OPAMP1   |   OPAMP2   |  OPAMP3(4) | 
    |-----------------|------------|------------|------------|
    | Output          |    PA3     |    PB0     |    PC3     |
    +--------------------------------------------------------+
    (4) : OPAMP3 availability depends on device category


            ##### How to use this driver #####
================================================================================
  [..] 
     
    *** Calibration ***
    ============================================
      To run the opamp calibration self calibration:

      (#) Start calibration using HAL_OPAMP_SelfCalibrate. 
           Store the calibration results.

    *** Running mode ***
    ============================================
      
      To use the opamp, perform the following steps:
            
      (#) Fill in the HAL_OPAMP_MspInit() to
      (+) Enable the OPAMP Peripheral clock using macro "__OPAMP_CLK_ENABLE()"
      (++) Configure the opamp input AND output in analog mode using 
           HAL_GPIO_Init() to map the opamp output to the GPIO pin.
  
      (#) Configure the opamp using HAL_OPAMP_Init() function:
      (+) Select the mode
      (+) Select the inverting input
      (+) Select the non-inverting input 
      (+) Select either factory or user defined trimming mode.
      (+) If the user defined trimming mode is enabled, select PMOS & NMOS trimming values
          (typ. settings returned by HAL_OPAMP_SelfCalibrate function).
      
      (#) Enable the opamp using HAL_OPAMP_Start() function.
           
      (#) Disable the opamp using HAL_OPAMP_Stop() function.
      
      (#) Lock the opamp in running mode using HAL_OPAMP_Lock() function.
          Caution: On STM32L1, HAL OPAMP lock is software lock only (not 
          hardware lock as on some other STM32 devices)

      (#) If needed, unlock the opamp using HAL_OPAMPEx_Unlock() function.

    *** Running mode: change of configuration while OPAMP ON  ***
    ============================================
    To Re-configure OPAMP when OPAMP is ON (change on the fly)
      (#) If needed, Fill in the HAL_OPAMP_MspInit()
      (+) This is the case for instance if you wish to use new OPAMP I/O

      (#) Configure the opamp using HAL_OPAMP_Init() function:
      (+) As in configure case, selects first the parameters you wish to modify.
      
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

/** @defgroup OPAMP OPAMP
  * @brief OPAMP HAL module driver
  * @{
  */

#ifdef HAL_OPAMP_MODULE_ENABLED

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup OPAMP_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_Exported_Functions_Group1 Initialization and de-initialization functions 
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
  * @brief  Initializes the OPAMP according to the specified
  *         parameters in the OPAMP_InitTypeDef and create the associated handle.
  * @note   If the selected opamp is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  hopamp: OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Init(OPAMP_HandleTypeDef* hopamp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmp_csr = 0;       /* Temporary variable to update register CSR, except bits ANAWSSELx, S7SEL2, OPA_RANGE, OPAxCALOUT */
  
  /* Check the OPAMP handle allocation and lock status */
  /* Init not allowed if calibration is ongoing */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
                      || (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY) )
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
       
    /* Set OPAMP parameters */
    assert_param(IS_OPAMP_FUNCTIONAL_NORMALMODE(hopamp->Init.Mode));
    assert_param(IS_OPAMP_NONINVERTING_INPUT(hopamp->Init.NonInvertingInput));       
    assert_param(IS_OPAMP_POWERMODE(hopamp->Init.PowerMode));
    assert_param(IS_OPAMP_POWER_SUPPLY_RANGE(hopamp->Init.PowerSupplyRange));
    assert_param(IS_OPAMP_TRIMMING(hopamp->Init.UserTrimming));
    
    if (hopamp->Init.Mode != OPAMP_FOLLOWER_MODE)
    {
      assert_param(IS_OPAMP_INVERTING_INPUT(hopamp->Init.InvertingInput));
    }
    
    if (hopamp->Init.UserTrimming == OPAMP_TRIMMING_USER)
    {
      if (hopamp->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueP));
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueN));
      }
      else
      {
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValuePLowPower));
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueNLowPower));
      }
    }
    
    /* Call MSP init function */
    HAL_OPAMP_MspInit(hopamp);
    
    
    /* Set OPAMP parameters                                                   */
    /* - Set internal switches in function of:                                */
    /*   - OPAMP selected mode: standalone or follower.                       */
    /*   - Non-inverting input connection                                     */
    /*   - Inverting input connection                                         */
    /* - Set power supply range                                               */
    /* - Set power mode and associated calibration parameters                 */
    
    /* Get OPAMP CSR register into temporary variable */
    tmp_csr = OPAMP->CSR;
    
    /* Open all switches on non-inverting input, inverting input and output   */
    /* feedback.                                                              */
    CLEAR_BIT(tmp_csr, __OPAMP_CSR_ALL_SWITCHES(hopamp));
    
    /* Set internal switches in function of OPAMP mode selected: standalone   */
    /* or follower.                                                           */
    /* If follower mode is selected, feedback switch S3 is closed and         */
    /* inverting inputs switches are let opened.                              */
    /* If standalone mode is selected, feedback switch S3 is let opened and   */
    /* the selected inverting inputs switch is closed.                        */
    if (hopamp->Init.Mode == OPAMP_FOLLOWER_MODE)
    {
      /* Follower mode: Close switches S3 and SanB */
      SET_BIT(tmp_csr, __OPAMP_CSR_S3SELX(hopamp));
    }
    else
    {
      /* Set internal switches in function of inverting input selected:       */
      /* Close switch to connect comparator inverting input to the selected   */
      /* input: dedicated IO pin or alternative IO pin available on some      */
      /* device packages.                                                     */
      if (hopamp->Init.InvertingInput == OPAMP_INVERTINGINPUT_VM0)
      {
        /* Close switch to connect comparator non-inverting input to          */
        /* dedicated IO pin low-leakage.                                      */
        SET_BIT(tmp_csr, __OPAMP_CSR_S4SELX(hopamp));
      }
      else
      {
        /* Close switch to connect comparator inverting input to alternative  */
        /* IO pin available on some device packages.                          */
        SET_BIT(tmp_csr, __OPAMP_CSR_ANAWSELX(hopamp));
      }
    }
    
    /* Set internal switches in function of non-inverting input selected:     */
    /* Close switch to connect comparator non-inverting input to the selected */
    /* input: dedicated IO pin or DAC channel.                                */
    if (hopamp->Init.NonInvertingInput == OPAMP_NONINVERTINGINPUT_VP0)
    {
      /* Close switch to connect comparator non-inverting input to            */
      /* dedicated IO pin low-leakage.                                        */
      SET_BIT(tmp_csr, __OPAMP_CSR_S5SELX(hopamp));
    }
    else if (hopamp->Init.NonInvertingInput == OPAMP_NONINVERTINGINPUT_DAC_CH1)
    {
      
      /* Particular case for connection to DAC channel 1:                     */
      /* OPAMP_NONINVERTINGINPUT_DAC_CH1 available on OPAMP1 and OPAMP2 only  */
      /* (OPAMP3 availability depends on device category).                    */
      if ((hopamp->Instance == OPAMP1) || (hopamp->Instance == OPAMP2))
      {
        /* Close switch to connect comparator non-inverting input to          */
        /* DAC channel 1.                                                     */
        SET_BIT(tmp_csr, __OPAMP_CSR_S6SELX(hopamp));
      }
      else
      {
        /* Set HAL status to error if another OPAMP instance as OPAMP1 or     */
        /* OPAMP2 is intended to be connected to DAC channel 2.               */
        status = HAL_ERROR;
      }
    }
    else /* if (hopamp->Init.NonInvertingInput ==                             */
         /*     OPAMP_NONINVERTINGINPUT_DAC_CH2  )                            */
    {
      /* Particular case for connection to DAC channel 2:                     */
      /* OPAMP_NONINVERTINGINPUT_DAC_CH2 available on OPAMP2 and OPAMP3 only  */
      /* (OPAMP3 availability depends on device category).                    */
      if (hopamp->Instance == OPAMP2)
      {
        /* Close switch to connect comparator non-inverting input to          */
        /* DAC channel 2.                                                     */
        SET_BIT(tmp_csr, OPAMP_CSR_S7SEL2);
      }
      /* If OPAMP3 is selected (if available) */
      else if (hopamp->Instance != OPAMP1)
      {
        /* Close switch to connect comparator non-inverting input to          */
        /* DAC channel 2.                                                     */
        SET_BIT(tmp_csr, __OPAMP_CSR_S6SELX(hopamp));
      }
      else
      {
        /* Set HAL status to error if another OPAMP instance as OPAMP2 or     */
        /* OPAMP3 (if available) is intended to be connected to DAC channel 2.*/
        status = HAL_ERROR;
      }
    }
    
    /* Continue OPAMP configuration if settings of switches are correct */
    if (status != HAL_ERROR)
    {
      /* Set power mode and associated calibration parameters */
      if (hopamp->Init.PowerMode != OPAMP_POWERMODE_LOWPOWER)
      {
        /* Set normal mode */
        CLEAR_BIT(tmp_csr, __OPAMP_CSR_OPAXLPM(hopamp));
        
        if (hopamp->Init.UserTrimming == OPAMP_TRIMMING_USER)
        {
          /* Set calibration mode (factory or user) and values for            */
          /* transistors differential pair high (PMOS) and low (NMOS) for     */
          /* normal mode.                                                     */
          MODIFY_REG(OPAMP->OTR, OPAMP_OTR_OT_USER                                                                     |
                                 __OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_N, OPAMP_TRIM_VALUE_MASK)       |
                                 __OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_P, OPAMP_TRIM_VALUE_MASK)        ,
                                 hopamp->Init.UserTrimming                                                             |
                                 __OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_N, hopamp->Init.TrimmingValueN) |
                                 __OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_P, hopamp->Init.TrimmingValueP)  );
        }
        else
        {
          /* Set calibration mode to factory */
          CLEAR_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);
        }
        
      }
      else
      {
        /* Set low power mode */
        SET_BIT(tmp_csr, __OPAMP_CSR_OPAXLPM(hopamp));
        
        if (hopamp->Init.UserTrimming == OPAMP_TRIMMING_USER)
        {
          /* Set calibration mode to user trimming */
          SET_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);
          
          /* Set values for transistors differential pair high (PMOS) and low */
          /* (NMOS) for low power mode.                                       */
          MODIFY_REG(OPAMP->LPOTR, __OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_N, OPAMP_TRIM_VALUE_MASK)               |
                                   __OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_P, OPAMP_TRIM_VALUE_MASK)                ,
                                   __OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_N, hopamp->Init.TrimmingValueNLowPower) |
                                   __OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_P, hopamp->Init.TrimmingValuePLowPower)  );
        }
        else
        {
          /* Set calibration mode to factory trimming */
          CLEAR_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);
        }
        
      }
      
      
      /* Configure the power supply range */
      MODIFY_REG(tmp_csr, OPAMP_CSR_AOP_RANGE,
                          hopamp->Init.PowerSupplyRange);
      
      /* Set OPAMP CSR register from temporary variable */
      /* This allows to apply all changes on one time, in case of update on   */
      /* the fly with OPAMP previously set and running:                       */
      /*  - to avoid hazardous transient switches settings (risk of short     */
      /*    circuit)                                                          */
      /*  - to avoid interruption of input signal                             */
      OPAMP->CSR = tmp_csr;

                
      /* Update the OPAMP state */
      /* If coming from state reset: Update from state RESET to state READY */
      /* else: remain in state READY or BUSY (no update) */
      if (hopamp->State == HAL_OPAMP_STATE_RESET)
      {
        hopamp->State = HAL_OPAMP_STATE_READY;
      }
    }
  }
  
  return status;
}


/**
  * @brief  DeInitializes the OPAMP peripheral 
  * @note   Deinitialization can't be performed if the OPAMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  hopamp: OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_DeInit(OPAMP_HandleTypeDef* hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  /* DeInit not allowed if calibration is ongoing */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED) \
                      || (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY))
  {
    status = HAL_ERROR;
  }
  else
  {

    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
    
    /* Open all switches on non-inverting input, inverting input and output   */
    /* feedback.                                                              */
    CLEAR_BIT(OPAMP->CSR, __OPAMP_CSR_ALL_SWITCHES(hopamp));

    /* DeInit the low level hardware */
    HAL_OPAMP_MspDeInit(hopamp);

  /* Update the OPAMP state*/
    hopamp->State = HAL_OPAMP_STATE_RESET;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hopamp);
  
  return status;
}


/**
  * @brief  Initializes the OPAMP MSP.
  * @param  hopamp: OPAMP handle
  * @retval None
  */
__weak void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef* hopamp)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the function "HAL_OPAMP_MspInit()" must be implemented in the user file.
  */
}

/**
  * @brief  DeInitializes OPAMP MSP.
  * @param  hopamp: OPAMP handle
  * @retval None
  */
__weak void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef* hopamp)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the function "HAL_OPAMP_MspDeInit()" must be implemented in the user file.
  */
}

/**
  * @}
  */


/** @defgroup OPAMP_Exported_Functions_Group2 IO operation functions 
  * @brief   IO operation functions 
  *
@verbatim   
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the OPAMP
    start, stop and calibration actions.

@endverbatim
  * @{
  */

/**
  * @brief  Start the opamp
  * @param  hopamp: OPAMP handle
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_OPAMP_Start(OPAMP_HandleTypeDef* hopamp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
    
    if(hopamp->State == HAL_OPAMP_STATE_READY)
    {
      /* Enable the selected opamp */
      CLEAR_BIT (OPAMP->CSR, __OPAMP_CSR_OPAXPD(hopamp));
      
      /* Update the OPAMP state */
      /* From HAL_OPAMP_STATE_READY to HAL_OPAMP_STATE_BUSY */
      hopamp->State = HAL_OPAMP_STATE_BUSY;   
    }
    else
    {
      status = HAL_ERROR;
    }
    
   }
  return status;
}

/**
  * @brief  Stop the opamp 
  * @param  hopamp: OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Stop(OPAMP_HandleTypeDef* hopamp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
    
  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  /* Check if OPAMP calibration ongoing */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED) \
                      || (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY))  
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    if(hopamp->State == HAL_OPAMP_STATE_BUSY)
    {
      /* Disable the selected opamp */
      SET_BIT (OPAMP->CSR, __OPAMP_CSR_OPAXPD(hopamp)); 
      
      /* Update the OPAMP state*/     
      /* From  HAL_OPAMP_STATE_BUSY to HAL_OPAMP_STATE_READY*/
      hopamp->State = HAL_OPAMP_STATE_READY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  return status;
}

/**
  * @brief  Run the self calibration of one OPAMP
  * @note   Trimming values (PMOS & NMOS) are updated and user trimming is 
  *         enabled is calibration is succesful.
  * @note   Calibration is performed in the mode specified in OPAMP init
  *         structure (mode normal or low-power). To perform calibration for
  *         both modes, repeat this function twice after OPAMP init structure
  *         accordingly updated.
  * @note   Calibration runs about 10 ms (5 dichotmy steps, repeated for P  
  *         and N transistors: 10 steps with 1 ms for each step).
  * @param  hopamp: handle
  * @retval Updated offset trimming values (PMOS & NMOS), user trimming is enabled
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_SelfCalibrate(OPAMP_HandleTypeDef* hopamp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  
  uint32_t* opamp_trimmingvalue = 0;
  uint32_t opamp_trimmingvaluen = 0;
  uint32_t opamp_trimmingvaluep = 0;
  
  uint32_t trimming_diff_pair = 0;           /* Selection of differential transistors pair high or low */

  __IO uint32_t* tmp_opamp_reg_trimming;     /* Selection of register of trimming depending on power mode: OTR or LPOTR */
  uint32_t tmp_opamp_otr_otuser = 0;         /* Selection of bit OPAMP_OTR_OT_USER depending on trimming register pointed: OTR or LPOTR */

  uint32_t tmp_Opaxcalout_DefaultSate = 0;   /* Bit OPAMP_CSR_OPAXCALOUT default state when trimming value is 00000b. Used to detect the bit toggling */

  uint32_t tmp_OpaxSwitchesContextBackup = 0;
  
  uint8_t trimming_diff_pair_iteration_count = 0;
  uint8_t delta = 0;

  
  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED))
  {
    status = HAL_ERROR;
  }
  else
  {
  
    /* Check if OPAMP in calibration mode and calibration not yet enable */
    if(hopamp->State == HAL_OPAMP_STATE_READY)
    {
      /* Check the parameter */
      assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
      assert_param(IS_OPAMP_POWERMODE(hopamp->Init.PowerMode));
      
      /* Update OPAMP state */
      hopamp->State = HAL_OPAMP_STATE_CALIBBUSY;
      
      /* Backup of switches configuration to restore it at the end of the     */
      /* calibration.                                                         */
      tmp_OpaxSwitchesContextBackup = READ_BIT(OPAMP->CSR, __OPAMP_CSR_ALL_SWITCHES(hopamp));
  
      /* Open all switches on non-inverting input, inverting input and output */
      /* feedback.                                                            */
      CLEAR_BIT(OPAMP->CSR, __OPAMP_CSR_ALL_SWITCHES(hopamp));

      /* Set calibration mode to user programmed trimming values */
      SET_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);

      
      /* Select trimming settings depending on power mode */
      if (hopamp->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        tmp_opamp_otr_otuser = OPAMP_OTR_OT_USER;
        tmp_opamp_reg_trimming = &OPAMP->OTR;
      }
      else
      {
        tmp_opamp_otr_otuser = 0x00000000;
        tmp_opamp_reg_trimming = &OPAMP->LPOTR;
      }

      
      /* Enable the selected opamp */
      CLEAR_BIT (OPAMP->CSR, __OPAMP_CSR_OPAXPD(hopamp));

      /* Perform trimming for both differential transistors pair high and low */
      for (trimming_diff_pair_iteration_count = 0; trimming_diff_pair_iteration_count <=1; trimming_diff_pair_iteration_count++)
      {
        if (trimming_diff_pair_iteration_count == 0)
        {
          /* Calibration of transistors differential pair high (NMOS) */
          trimming_diff_pair = OPAMP_FACTORYTRIMMING_N;
          opamp_trimmingvalue = &opamp_trimmingvaluen;
          
          /* Set bit OPAMP_CSR_OPAXCALOUT default state when trimming value   */
          /* is 00000b. Used to detect the bit toggling during trimming.      */
          tmp_Opaxcalout_DefaultSate = RESET;

          /* Enable calibration for N differential pair */
          MODIFY_REG(OPAMP->CSR, __OPAMP_CSR_OPAXCAL_L(hopamp),
                                 __OPAMP_CSR_OPAXCAL_H(hopamp) );
        }
        else /* (trimming_diff_pair_iteration_count == 1) */
        {
          /* Calibration of transistors differential pair low (PMOS) */
          trimming_diff_pair = OPAMP_FACTORYTRIMMING_P;
          opamp_trimmingvalue = &opamp_trimmingvaluep;
          
          /* Set bit OPAMP_CSR_OPAXCALOUT default state when trimming value   */
          /* is 00000b. Used to detect the bit toggling during trimming.      */
          tmp_Opaxcalout_DefaultSate = __OPAMP_CSR_OPAXCALOUT(hopamp);
          
          /* Enable calibration for P differential pair */
          MODIFY_REG(OPAMP->CSR, __OPAMP_CSR_OPAXCAL_H(hopamp),
                                 __OPAMP_CSR_OPAXCAL_L(hopamp) );
        }
        
      
        /* Perform calibration parameter search by dichotomy sweep */
        /*  - Delta initial value 16: for 5 dichotomy steps: 16 for the       */
        /*    initial range, then successive delta sweeps (8, 4, 2, 1).       */
        /*    can extend the search range to +/- 15 units.                    */
        /*  - Trimming initial value 15: search range will go from 0 to 30    */
        /*    (Trimming value 31 is forbidden).                               */
        *opamp_trimmingvalue = 15;
        delta = 16;

        while (delta != 0)
        {
          /* Set candidate trimming */               
          MODIFY_REG(*tmp_opamp_reg_trimming, __OPAMP_OFFSET_TRIM_SET(hopamp, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                              __OPAMP_OFFSET_TRIM_SET(hopamp, trimming_diff_pair, *opamp_trimmingvalue) | tmp_opamp_otr_otuser);
          
          /* Offset trimming time: during calibration, minimum time needed    */
          /* between two steps to have 1 mV accuracy.                         */
          HAL_Delay(OPAMP_TRIMMING_DELAY);

          /* Divide range by 2 to continue dichotomy sweep */
          delta >>= 1;
            
          /* Set trimming values for next iteration in function of trimming   */
          /* result toggle (versus initial state).                            */
          if (READ_BIT(OPAMP->CSR, __OPAMP_CSR_OPAXCALOUT(hopamp)) != tmp_Opaxcalout_DefaultSate)
          {
            /* If calibration output is has toggled, try lower trimming */
            *opamp_trimmingvalue -= delta;
          }
          else
          {
            /* If calibration output is has not toggled, try higher trimming */
            *opamp_trimmingvalue += delta;
          }
        }
        
      }
       
      /* Disable calibration for P and N differential pairs */
      /* Disable the selected opamp */
      CLEAR_BIT (OPAMP->CSR, (__OPAMP_CSR_OPAXCAL_H(hopamp) | 
                              __OPAMP_CSR_OPAXCAL_L(hopamp) |
                              __OPAMP_CSR_OPAXPD(hopamp))    );

      /* Backup of switches configuration to restore it at the end of the     */
      /* calibration.                                                         */
      SET_BIT(OPAMP->CSR, tmp_OpaxSwitchesContextBackup);
      
      /* Self calibration is successful */
      /* Store calibration (user trimming) results in init structure. */
      
      /* Set user trimming mode */  
      hopamp->Init.UserTrimming = OPAMP_TRIMMING_USER;
      
      /* Affect calibration parameters depending on mode normal/low power */
      if (hopamp->Init.PowerMode != OPAMP_POWERMODE_LOWPOWER)
      {
        /* Write calibration result N */
        hopamp->Init.TrimmingValueN = opamp_trimmingvaluen;
        /* Write calibration result P */
        hopamp->Init.TrimmingValueP = opamp_trimmingvaluep;
      }
      else
      {
        /* Write calibration result N */
        hopamp->Init.TrimmingValueNLowPower = opamp_trimmingvaluen;
        /* Write calibration result P */
        hopamp->Init.TrimmingValuePLowPower = opamp_trimmingvaluep;
      }
      
      /* Update OPAMP state */
      hopamp->State = HAL_OPAMP_STATE_READY;

    }
    else
    {
      /* OPAMP can not be calibrated from this mode */ 
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Return the OPAMP factory trimming value
  *         Caution: On STM32L1 OPAMP, user can retrieve factory trimming if 
  *                  OPAMP has never been set to user trimming before.
  *                  Therefore, this fonction must be called when OPAMP init  
  *                  parameter "UserTrimming" is set to trimming factory, 
  *                  and before OPAMP  calibration (function 
  *                  "HAL_OPAMP_SelfCalibrate()").
  *                  Otherwise, factory triming value cannot be retrieved and 
  *                  error status is returned.
  * @param  hopamp : OPAMP handle
  * @param  trimmingoffset : Trimming offset (P or N)
  *         This parameter must be a value of @ref OPAMP_FactoryTrimming
  * @note   Calibration parameter retrieved is corresponding to the mode 
  *         specified in OPAMP init structure (mode normal or low-power). 
  *         To retrieve calibration parameters for both modes, repeat this 
  *         function after OPAMP init structure accordingly updated.
  * @retval Trimming value (P or N): range: 0->31
  *         or OPAMP_FACTORYTRIMMING_DUMMY if trimming value is not available
  * @{
  */
OPAMP_TrimmingValueTypeDef HAL_OPAMP_GetTrimOffset (OPAMP_HandleTypeDef *hopamp, uint32_t trimmingoffset)
{ 
  OPAMP_TrimmingValueTypeDef trimmingvalue;
  __IO uint32_t* tmp_opamp_reg_trimming;  /* Selection of register of trimming depending on power mode: OTR or LPOTR */
  
  /* Check the OPAMP handle allocation */
  /* Value can be retrieved in HAL_OPAMP_STATE_READY state */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_RESET)
                      || (hopamp->State == HAL_OPAMP_STATE_BUSY)
                      || (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY)
                      || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED))
  {
    trimmingvalue = OPAMP_FACTORYTRIMMING_DUMMY;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
    assert_param(IS_OPAMP_FACTORYTRIMMING(trimmingoffset));
    assert_param(IS_OPAMP_POWERMODE(hopamp->Init.PowerMode));
    
    /* Check the trimming mode */
    if (hopamp->Init.UserTrimming == OPAMP_TRIMMING_USER) 
    {
      /* This fonction must called when OPAMP init parameter "UserTrimming"   */
      /* is set to trimming factory, and before OPAMP calibration (function   */
      /* "HAL_OPAMP_SelfCalibrate()").                                        */
      /* Otherwise, factory triming value cannot be retrieved and error       */
      /* status is returned.                                                  */
      trimmingvalue = OPAMP_FACTORYTRIMMING_DUMMY;
    }
    else
    {
      /* Select trimming settings depending on power mode */
      if (hopamp->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        tmp_opamp_reg_trimming = &OPAMP->OTR;
      }
      else
      {
        tmp_opamp_reg_trimming = &OPAMP->LPOTR;
      }
        
      /* Get factory trimming  */
      trimmingvalue = ((*tmp_opamp_reg_trimming >> __OPAMP_OFFSET_TRIM_BITSPOSITION(hopamp, trimmingoffset)) & OPAMP_TRIM_VALUE_MASK);
      }
  }
  
  return trimmingvalue;
}

/**
  * @}
  */

/**
  * @}
  */
      
/** @defgroup OPAMP_Exported_Functions_Group3 Peripheral Control functions 
 *  @brief   Peripheral Control functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]

@endverbatim
  * @{
  */

/**
  * @brief  Lock the selected opamp configuration.
  *         Caution: On STM32L1, HAL OPAMP lock is software lock only (not 
  *         hardware lock as on some other STM32 devices)
  * @param  hopamp: OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Lock(OPAMP_HandleTypeDef* hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  /* OPAMP can be locked when enabled and running in normal mode */ 
  /*   It is meaningless otherwise */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_RESET) \
                      || (hopamp->State == HAL_OPAMP_STATE_READY) \
                      || (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY)\
                      || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED))
  
  {
    status = HAL_ERROR;
  }
  
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
  
   /* OPAMP state changed to locked */
    hopamp->State = HAL_OPAMP_STATE_BUSYLOCKED;
  }
  return status; 
}

/**
  * @}
  */


/** @defgroup OPAMP_Exported_Functions_Group4 Peripheral State functions 
 *  @brief   Peripheral State functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================  
    [..]
    This subsection permit to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Return the OPAMP state
  * @param  hopamp : OPAMP handle
  * @retval HAL state
  */
HAL_OPAMP_StateTypeDef HAL_OPAMP_GetState(OPAMP_HandleTypeDef* hopamp)
{
  /* Check the OPAMP handle allocation */
  if(hopamp == HAL_NULL)
  {
    return HAL_OPAMP_STATE_RESET;
  }

  /* Check the parameter */
  assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

  return hopamp->State;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE || STM32L162xC || STM32L152xC || STM32L151xC */

#endif /* HAL_OPAMP_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
