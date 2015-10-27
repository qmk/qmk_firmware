/**
  ******************************************************************************
  * @file    stm32f3xx_hal_opamp.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   OPAMP HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities of the operational amplifiers (OPAMP1,...OPAMP4) 
  *          peripheral: 
  *           + OPAMP Configuration
  *           + OPAMP calibration
  *
  *          Thanks to
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *         
  @verbatim
================================================================================
          ##### OPAMP Peripheral Features #####
================================================================================
           
  [..] The device integrates up to 4 operational amplifiers OPAMP1, OPAMP2,
       OPAMP3 and OPAMP4:
       
       (#) The OPAMP(s) provides several exclusive running modes.
       (+) Standalone mode
       (+) Programmable Gain Amplifier (PGA) mode (Resistor feedback output)
       (+) Follower mode

       (#) The OPAMP(s) provide(s) calibration capabilities.  
       (+) Calibration aims at correcting some offset for running mode.
       (+) The OPAMP uses either factory calibration settings OR user defined 
           calibration (trimming) settings (i.e. trimming mode).
       (+) The user defined settings can be figured out using self calibration 
           handled by HAL_OPAMP_SelfCalibrate, HAL_OPAMPEx_SelfCalibrateAll
       (+) HAL_OPAMP_SelfCalibrate:
       (++) Runs automatically the calibration in 2 steps. 
            (90% of VDDA for NMOS transistors, 10% of VDDA for PMOS transistors).
            (As OPAMP is Rail-to-rail input/output, these 2 steps calibration is 
            appropriate and enough in most cases).
       (++) Enables the user trimming mode
       (++) Updates the init structure with trimming values with fresh calibration 
            results. 
            The user may store the calibration results for larger 
            (ex monitoring the trimming as a function of temperature 
            for instance)
       (++) for STM32F3 devices having 2 or 4 OPAMPs
            HAL_OPAMPEx_SelfCalibrateAll
            runs calibration of 2 or 4 OPAMPs in parallel. 
       
       (#) For any running mode, an additional Timer-controlled Mux (multiplexer) 
           mode can be set on top.
       (+) Timer-controlled Mux mode allows Automatic switching between inverting
           and non-inverting input. 
       (+) Hence on top of defaults (primary) inverting and non-inverting inputs,
           the user shall select secondary inverting and non inverting inputs.
       (+) TIM1 CC6 provides the alternate switching tempo between defaults 
           (primary) and secondary inputs. 
             
       (#) Running mode: Standalone mode 
       (+) Gain is set externally (gain depends on external loads).
       (+) Follower mode also possible externally by connecting the inverting input to
           the output.
       
       (#) Running mode: Follower mode
       (+) No Inverting Input is connected.
       
       (#) Running mode: Programmable Gain Amplifier (PGA) mode 
           (Resistor feedback output)
       (+) The OPAMP(s) output(s) can be internally connected to resistor feedback
           output.
       (+) OPAMP gain is either 2, 4, 8 or 16.
        
       (#) The OPAMPs non inverting input (both default and secondary) can be 
           selected among the list shown by table below.
       
       (#) The OPAMPs non inverting input (both default and secondary) can be 
           selected among the list shown by table below.
       
   [..] Table 1.  OPAMPs inverting/non-inverting inputs for the STM32F3 devices:
     
    +--------------------------------------------------------------+     
    |                 |        | OPAMP1 | OPAMP2 | OPAMP3 | OPAMP4 |
    |-----------------|--------|--------|--------|--------|--------|
    |                 | No conn|   X    |   X    |   X    |   X    |
    | Inverting Input | VM0    |  PC5   |  PC5   |  PB10  |  PB10  |
    | (1)             | VM1    |  PA3   |  PA5   |  PB2   |  PD8   |
    |-----------------|--------|--------|--------|--------|--------|
    |                 | VP0    |  PA1   |  PA7   |  PB0   |  PB13  |
    |  Non Inverting  | VP1    |  PA7   |  PD14  |  PB13  |  PD11  |
    |    Input        | VP2    |  PA3   |  PB0   |  PA1   |  PA4   |
    |                 | VP3    |  PA5   |  PB14  |  PA5   |  PB11  |
    +--------------------------------------------------------------+  
    (1): NA in follower mode.
           
   [..] Table 2.  OPAMPs outputs for the STM32F3 devices:

    +--------------------------------------------------------------+     
    |                 |        | OPAMP1 | OPAMP2 | OPAMP3 | OPAMP4 |
    |-----------------|--------|--------|--------|--------|--------|
    | Output          |        |  PA2   |  PA6   |  PB1   |  PB12  |
    |-----------------|--------|--------|--------|--------|--------|

      
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
      (+) Configure the opamp input AND output in analog mode using 
          HAL_GPIO_Init() to map the opamp output to the GPIO pin.
  
      (#) Configure the opamp using HAL_OPAMP_Init() function:
      (+) Select the mode
      (+) Select the inverting input
      (+) Select the non-inverting input 
      (+) Select if the Timer controlled Mux mode is enabled/disabled
      (+) If the Timer controlled Mux mode is enabled, select the secondary inverting input
      (+) If the Timer controlled Mux mode is enabled, Select the secondary non-inverting input 
      (+) If PGA mode is enabled, Select if inverting input is connected.
      (+) Select either factory or user defined trimming mode.
      (+) If the user defined trimming mode is enabled, select PMOS & NMOS trimming values
          (typ. settings returned by HAL_OPAMP_SelfCalibrate function).
      
      (#) Enable the opamp using HAL_OPAMP_Start() function.
           
      (#) Disable the opamp using HAL_OPAMP_Stop() function.
      
      (#) Lock the opamp in running mode using HAL_OPAMP_Lock() function. From then The configuration 
          can only be modified after HW reset.

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
#include "stm32f3xx_hal.h"
    
/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @defgroup OPAMP OPAMP HAL module driver
  * @brief OPAMP HAL module driver
  * @{
  */

#ifdef HAL_OPAMP_MODULE_ENABLED

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup OPAMP_Private_Define OPAMP Private Define
 * @{
 */
/* CSR register reset value */ 
#define OPAMP_CSR_RESET_VALUE             ((uint32_t)0x00000000)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup OPAMP_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization/de-initialization  functions #####
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
HAL_StatusTypeDef HAL_OPAMP_Init(OPAMP_HandleTypeDef *hopamp)

{ 
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation and lock status */
  /* Init not allowed if calibration is ongoing */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED) \
                      || (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY))
  {
    return HAL_ERROR;
  }
  else
  {
      
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
       
    /* Set OPAMP parameters */
    assert_param(IS_OPAMP_FUNCTIONAL_NORMALMODE(hopamp->Init.Mode));
    assert_param(IS_OPAMP_NONINVERTING_INPUT(hopamp->Init.NonInvertingInput));
    if ((hopamp->Init.Mode) == OPAMP_STANDALONE_MODE)
    {
      assert_param(IS_OPAMP_INVERTING_INPUT(hopamp->Init.InvertingInput));
    }
  
    assert_param(IS_OPAMP_TIMERCONTROLLED_MUXMODE(hopamp->Init.TimerControlledMuxmode));

    if ((hopamp->Init.TimerControlledMuxmode) == OPAMP_TIMERCONTROLLEDMUXMODE_ENABLE)
    {
      assert_param(IS_OPAMP_SEC_NONINVERTINGINPUT(hopamp->Init.NonInvertingInputSecondary));
      if ((hopamp->Init.Mode) == OPAMP_STANDALONE_MODE)
      {
        assert_param(IS_OPAMP_SEC_INVERTINGINPUT(hopamp->Init.InvertingInputSecondary));
      }
    }
    
    if ((hopamp->Init.Mode) == OPAMP_PGA_MODE)
    {
      assert_param(IS_OPAMP_PGACONNECT(hopamp->Init.PgaConnect));
      assert_param(IS_OPAMP_PGA_GAIN(hopamp->Init.PgaGain));
    }
    
    assert_param(IS_OPAMP_TRIMMING(hopamp->Init.UserTrimming)); 
    if ((hopamp->Init.UserTrimming) == OPAMP_TRIMMING_USER)
    {
      assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueP));
      assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueN));
    }
 
    /* Init SYSCFG and the low level hardware to access opamp */
    __SYSCFG_CLK_ENABLE();
    
    /* Call MSP init function */
    HAL_OPAMP_MspInit(hopamp);
                                          
    /* Set OPAMP parameters */
    /*     Set  bits according to hopamp->hopamp->Init.Mode value                                 */
    /*     Set  bits according to hopamp->hopamp->Init.InvertingInput value                       */
    /*     Set  bits according to hopamp->hopamp->Init.NonInvertingInput value                    */
    /*     Set  bits according to hopamp->hopamp->Init.TimerControlledMuxmode value               */
    /*     Set  bits according to hopamp->hopamp->Init.InvertingInputSecondary  value             */
    /*     Set  bits according to hopamp->hopamp->Init.NonInvertingInputSecondary value           */
    /*     Set  bits according to hopamp->hopamp->Init.PgaConnect value                           */
    /*     Set  bits according to hopamp->hopamp->Init.PgaGain value                              */
    /*     Set  bits according to hopamp->hopamp->Init.UserTrimming value                         */
    /*     Set  bits according to hopamp->hopamp->Init.TrimmingValueP value                       */
    /*     Set  bits according to hopamp->hopamp->Init.TrimmingValueN value                       */
    
    
    /* check if OPAMP_PGA_MODE & in Follower mode */
    /*   - InvertingInput                         */
    /*   - InvertingInputSecondary                */
    /* are Not Applicable                         */
    
    if ((hopamp->Init.Mode == OPAMP_PGA_MODE) || (hopamp->Init.Mode == OPAMP_FOLLOWER_MODE))
    {
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_UPDATE_PARAMETERS_INIT_MASK, \
                                        hopamp->Init.Mode | \
                                        hopamp->Init.NonInvertingInput | \
                                        hopamp->Init.TimerControlledMuxmode | \
                                        hopamp->Init.NonInvertingInputSecondary  | \
                                        hopamp->Init.PgaConnect | \
                                        hopamp->Init.PgaGain | \
                                        hopamp->Init.UserTrimming | \
                                        (hopamp->Init.TrimmingValueP << OPAMP_INPUT_NONINVERTING) | \
                                        (hopamp->Init.TrimmingValueN << OPAMP_INPUT_INVERTING));  
    }    
    else /* OPAMP_STANDALONE_MODE */
    {
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_UPDATE_PARAMETERS_INIT_MASK, \
                                        hopamp->Init.Mode | \
                                        hopamp->Init.InvertingInput    | \
                                        hopamp->Init.NonInvertingInput | \
                                        hopamp->Init.TimerControlledMuxmode | \
                                        hopamp->Init.InvertingInputSecondary  | \
                                        hopamp->Init.NonInvertingInputSecondary  | \
                                        hopamp->Init.PgaConnect | \
                                        hopamp->Init.PgaGain | \
                                        hopamp->Init.UserTrimming | \
                                        (hopamp->Init.TrimmingValueP << OPAMP_INPUT_NONINVERTING) | \
                                        (hopamp->Init.TrimmingValueN << OPAMP_INPUT_INVERTING));     
    } 
    
    /* Update the OPAMP state*/
    if (hopamp->State == HAL_OPAMP_STATE_RESET)
    {
      /* From RESET state to READY State */
    hopamp->State = HAL_OPAMP_STATE_READY;
    }
    /* else: remain in READY or BUSY state (no update) */
  
    return status;
    }
}


/**
  * @brief  DeInitializes the OPAMP peripheral 
  * @note   Deinitialization can't be performed if the OPAMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  hopamp: OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_DeInit(OPAMP_HandleTypeDef *hopamp)
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

    /* Set OPAMP_CSR register to reset value */
    WRITE_REG(hopamp->Instance->CSR, OPAMP_CSR_RESET_VALUE);

    /* DeInit the low level hardware: GPIO, CLOCK and NVIC */
    HAL_OPAMP_MspDeInit(hopamp);

    /* Update the OPAMP state*/
    hopamp->State = HAL_OPAMP_STATE_RESET;
  }
  return status;
}

/**
  * @brief  Initializes the OPAMP MSP.
  * @param  hopamp: OPAMP handle
  * @retval None
  */
__weak void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef *hopamp)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_OPAMP_MspInit could be implemented in the user file
   */

   /* Example */ 
}

/**
  * @brief  DeInitializes OPAMP MSP.
  * @param  hopamp: OPAMP handle
  * @retval None
  */
__weak void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef *hopamp)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_OPAMP_MspDeInit could be implemented in the user file
   */

}

/**
  * @}
  */


/** @defgroup OPAMP_Exported_Functions_Group2 Input and Output operation functions 
 *  @brief   Data transfers functions 
 *
@verbatim   
 ===============================================================================
                      ##### IO operation  functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the OPAMP data 
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start the opamp
  * @param  hopamp: OPAMP handle
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_OPAMP_Start(OPAMP_HandleTypeDef *hopamp)
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
      SET_BIT (hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);

      /* Update the OPAMP state*/     
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
HAL_StatusTypeDef HAL_OPAMP_Stop(OPAMP_HandleTypeDef *hopamp)
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
      CLEAR_BIT (hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN); 
    
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
  * @param  hopamp handle
  * @retval Updated offset trimming values (PMOS & NMOS), user trimming is enabled
  * @retval HAL status
  * @note   Calibration runs about 25 ms.
  */

HAL_StatusTypeDef HAL_OPAMP_SelfCalibrate(OPAMP_HandleTypeDef *hopamp)
{ 

  HAL_StatusTypeDef status = HAL_OK;
  
  uint32_t trimmingvaluen = 0;
  uint32_t trimmingvaluep = 0;
  uint32_t delta;
  
  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED))
  {
    status = HAL_ERROR;
  }
  else
  {
  
    /* Check if OPAMP in calibration mode and calibration not yet enable */
    if(hopamp->State ==  HAL_OPAMP_STATE_READY)
    {
      /* Check the parameter */
      assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

      /* Set Calibration mode */
      /* Non-inverting input connected to calibration reference voltage. */
      SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_FORCEVP);

      /*  user trimming values are used for offset calibration */
      SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_USERTRIM);
      
      /* Enable calibration */
      SET_BIT (hopamp->Instance->CSR, OPAMP_CSR_CALON);
  
      /* 1st calibration - N */
      /* Select 90% VREF */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
      
      /* Enable the selected opamp */
      SET_BIT (hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);
      
      /* Init trimming counter */    
      /* Medium value */
      trimmingvaluen = 16; 
      delta = 8;
      
      while (delta != 0)
      {
        /* Set candidate trimming */
        MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen<<OPAMP_INPUT_INVERTING);
              
        /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */ 
        /* Offset trim time: during calibration, minimum time needed between */
        /* two steps to have 1 mV accuracy */
        HAL_Delay(2);

        if ((hopamp->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
        { 
          /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
          trimmingvaluen += delta;
        }
        else
        {
          /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
          trimmingvaluen -= delta;
        }
                      
        delta >>= 1;
      }

      /* Still need to check if righ calibration is current value or un step below */
      /* Indeed the first value that causes the OUTCAL bit to change from 1 to 0  */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen<<OPAMP_INPUT_INVERTING);
      
       /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */ 
       /* Offset trim time: during calibration, minimum time needed between */
       /* two steps to have 1 mV accuracy */
       HAL_Delay(2);
      
      if ((hopamp->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET) 
      { 
        /* OPAMP_CSR_OUTCAL is actually one value more */
        trimmingvaluen++;
        /* Set right trimming */
        MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen<<OPAMP_INPUT_INVERTING);
      }
       
      /* 2nd calibration - P */
      /* Select 10% VREF */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
      
      /* Init trimming counter */    
      /* Medium value */
      trimmingvaluep = 16; 
      delta = 8;
      
      while (delta != 0)
      {
        /* Set candidate trimming */
        MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep<<OPAMP_INPUT_NONINVERTING);
               
        /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */ 
        /* Offset trim time: during calibration, minimum time needed between */
        /* two steps to have 1 mV accuracy */
        HAL_Delay(2);

        if ((hopamp->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET) 
        { 
          /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
          trimmingvaluep += delta;
        }
        else
        {
          trimmingvaluep -= delta;
        }
                      
        delta >>= 1;
      }
      
      /* Still need to check if righ calibration is current value or un step below */
      /* Indeed the first value that causes the OUTCAL bit to change from 1 to 0 */
      /* Set candidate trimming */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep<<OPAMP_INPUT_NONINVERTING);

       /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */ 
       /* Offset trim time: during calibration, minimum time needed between */
       /* two steps to have 1 mV accuracy */
       HAL_Delay(2);
      
      if ((hopamp->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
      { 
        /* OPAMP_CSR_OUTCAL is actually one value more */
        trimmingvaluep++;
        /* Set right trimming */
        MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep<<OPAMP_INPUT_NONINVERTING);
      }
           
      /* Disable calibration */
      CLEAR_BIT (hopamp->Instance->CSR, OPAMP_CSR_CALON);

      /* Disable the OPAMP */
      CLEAR_BIT (hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);
      
      /* Set normale operating mode  */
      /* Non-inverting input connected to calibration reference voltage. */
      CLEAR_BIT(hopamp->Instance->CSR, OPAMP_CSR_FORCEVP);
            
      /* Self calibration is successful  */
      /* Store calibration(user timming) results in init structure. */

      /* Write calibration result N */
      hopamp->Init.TrimmingValueN = trimmingvaluen;
     
      /* Write calibration result P */
      hopamp->Init.TrimmingValueP = trimmingvaluep;

      /* Select user timming mode */      
      /* And updated with calibrated settings */
      hopamp->Init.UserTrimming = OPAMP_TRIMMING_USER;
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep<<OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen<<OPAMP_INPUT_INVERTING);
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
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group3 Peripheral Control functions 
 *  @brief   management functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the OPAMP data 
    transfers.



@endverbatim
  * @{
  */

/**
  * @brief  Lock the selected opamp configuration. 
  * @param  hopamp: OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Lock(OPAMP_HandleTypeDef *hopamp)
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
    
   /* Lock OPAMP */
    SET_BIT (hopamp->Instance->CSR, OPAMP_CSR_LOCK);
  
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
    This subsection permit to get in run-time the status of the peripheral 
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the OPAMP state
  * @param  hopamp : OPAMP handle
  * @retval HAL state
  */
HAL_OPAMP_StateTypeDef HAL_OPAMP_GetState(OPAMP_HandleTypeDef *hopamp)
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
  * @brief  Return the OPAMP factory trimming value
  * @param  hopamp : OPAMP handle
  * @param  trimmingoffset : Trimming offset (P or N)
  * @retval Trimming value (P or N): range: 0->31
  *         or OPAMP_FACTORYTRIMMING_DUMMY if trimming value is not available
 */

OPAMP_TrimmingValueTypeDef HAL_OPAMP_GetTrimOffset (OPAMP_HandleTypeDef *hopamp, uint32_t trimmingoffset)
{
  uint32_t oldusertrimming = 0;
  OPAMP_TrimmingValueTypeDef  oldtrimmingvaluep = 0, oldtrimmingvaluen = 0, trimmingvalue = 0;
  
  /* Check the OPAMP handle allocation */
  /* Value can be retrieved in HAL_OPAMP_STATE_READY state */
  if((hopamp == HAL_NULL) || (hopamp->State == HAL_OPAMP_STATE_RESET) \
                      || (hopamp->State == HAL_OPAMP_STATE_BUSY) \
                      || (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY)\
                      || (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED))
  {
    return OPAMP_FACTORYTRIMMING_DUMMY;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
    assert_param(IS_OPAMP_FACTORYTRIMMING(trimmingoffset));
    
    /* Check the trimming mode */
    if ((READ_BIT(hopamp->Instance->CSR,OPAMP_CSR_USERTRIM)) != RESET) 
    {
      /* User trimming is used */
      oldusertrimming = OPAMP_TRIMMING_USER;
      /* Store the TrimmingValueP & TrimmingValueN */
      oldtrimmingvaluep = (hopamp->Instance->CSR & OPAMP_CSR_TRIMOFFSETP) >> OPAMP_INPUT_NONINVERTING;
      oldtrimmingvaluen = (hopamp->Instance->CSR & OPAMP_CSR_TRIMOFFSETN) >> OPAMP_INPUT_INVERTING;
    }
    
    /* Set factory timming mode */
    CLEAR_BIT (hopamp->Instance->CSR, OPAMP_CSR_USERTRIM);
    
    /* Get factory trimming  */
    if (trimmingoffset == OPAMP_FACTORYTRIMMING_P)
    {
      /* Return TrimOffsetP */
     trimmingvalue = ((hopamp->Instance->CSR & OPAMP_CSR_TRIMOFFSETP) >> OPAMP_INPUT_NONINVERTING);
    }
    else 
    {
      /* Return TrimOffsetN */
      trimmingvalue = ((hopamp->Instance->CSR & OPAMP_CSR_TRIMOFFSETN) >> OPAMP_INPUT_INVERTING);
    }
    
    /* Restore user trimming configuration if it was formerly set */
    /* Check if user trimming was used */
    if (oldusertrimming == OPAMP_TRIMMING_USER) 
    {
      /* Restore user trimming */
      SET_BIT(hopamp->Instance->CSR,OPAMP_CSR_USERTRIM);
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, oldtrimmingvaluep<<OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, oldtrimmingvaluen<<OPAMP_INPUT_INVERTING);
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
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#endif /* HAL_OPAMP_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
