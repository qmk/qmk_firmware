/**
  ******************************************************************************
  * @file    hal_tick.c
  * @author  MCD Application Team
  * @brief   Initialization of HAL tick
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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
#include "hal_tick.h"

TIM_HandleTypeDef TimMasterHandle;
uint32_t PreviousVal = 0;

void us_ticker_irq_handler(void);
void set_compare(uint16_t count);

extern volatile uint32_t SlaveCounter;
extern volatile uint32_t oc_int_part;
extern volatile uint16_t oc_rem_part;

void timer_irq_handler(void) {
    uint16_t cval = TIM_MST->CNT;

    TimMasterHandle.Instance = TIM_MST;

    // Clear Update interrupt flag
    if (__HAL_TIM_GET_FLAG(&TimMasterHandle, TIM_FLAG_UPDATE) == SET) {
        __HAL_TIM_CLEAR_FLAG(&TimMasterHandle, TIM_FLAG_UPDATE);
        SlaveCounter++;
    }

    // Channel 1 for mbed timeout
    if (__HAL_TIM_GET_FLAG(&TimMasterHandle, TIM_FLAG_CC1) == SET) {
        __HAL_TIM_CLEAR_FLAG(&TimMasterHandle, TIM_FLAG_CC1);
        if (oc_rem_part > 0) {
            set_compare(oc_rem_part); // Finish the remaining time left
            oc_rem_part = 0;
        } else {
            if (oc_int_part > 0) {
                set_compare(0xFFFF);
                oc_rem_part = cval; // To finish the counter loop the next time
                oc_int_part--;
            } else {
                us_ticker_irq_handler();
            }
        }
    }

    // Channel 2 for HAL tick
    if (__HAL_TIM_GET_FLAG(&TimMasterHandle, TIM_FLAG_CC2) == SET) {
        __HAL_TIM_CLEAR_FLAG(&TimMasterHandle, TIM_FLAG_CC2);
        uint32_t val = __HAL_TIM_GetCounter(&TimMasterHandle);
        if ((val - PreviousVal) >= HAL_TICK_DELAY) {
            // Increment HAL variable
            HAL_IncTick();
            // Prepare next interrupt
            __HAL_TIM_SetCompare(&TimMasterHandle, TIM_CHANNEL_2, val + HAL_TICK_DELAY);
            PreviousVal = val;
        }
    }
}

// Reconfigure the HAL tick using a standard timer instead of systick.
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority) {
    // Enable timer clock
    TIM_MST_RCC;

    // Reset timer
    TIM_MST_RESET_ON;
    TIM_MST_RESET_OFF;

    // Update the SystemCoreClock variable
    SystemCoreClockUpdate();

    // Configure time base
    TimMasterHandle.Instance = TIM_MST;
    TimMasterHandle.Init.Period        = 0xFFFFFFFF;
    TimMasterHandle.Init.Prescaler     = (uint32_t)(SystemCoreClock / 1000000) - 1; // 1 us tick
    TimMasterHandle.Init.ClockDivision = 0;
    TimMasterHandle.Init.CounterMode   = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&TimMasterHandle);

    // Configure output compare channel 1 for mbed timeout (enabled later when used)
    HAL_TIM_OC_Start(&TimMasterHandle, TIM_CHANNEL_1);

    // Configure output compare channel 2 for HAL tick
    HAL_TIM_OC_Start(&TimMasterHandle, TIM_CHANNEL_2);
    PreviousVal = __HAL_TIM_GetCounter(&TimMasterHandle);
    __HAL_TIM_SetCompare(&TimMasterHandle, TIM_CHANNEL_2, PreviousVal + HAL_TICK_DELAY);

    // Configure interrupts
    // Update interrupt used for 32-bit counter
    // Output compare channel 1 interrupt for mbed timeout
    // Output compare channel 2 interrupt for HAL tick
    NVIC_SetVector(TIM_MST_IRQ, (uint32_t)timer_irq_handler);
    NVIC_EnableIRQ(TIM_MST_IRQ);

    // Enable interrupts
    __HAL_TIM_ENABLE_IT(&TimMasterHandle, TIM_IT_UPDATE); // For 32-bit counter
    __HAL_TIM_ENABLE_IT(&TimMasterHandle, TIM_IT_CC2); // For HAL tick

    // Enable timer
    HAL_TIM_Base_Start(&TimMasterHandle);

    return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */    
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
