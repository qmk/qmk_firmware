/**
  ******************************************************************************
  * @file    stm32f30x_spi.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Serial peripheral interface (SPI):
  *           + Initialization and Configuration
  *           + Data transfers functions
  *           + Hardware CRC Calculation
  *           + DMA transfers management
  *           + Interrupts and flags management
  *
  *  @verbatim
  
  
 ===============================================================================
                      ##### How to use this driver #####
 ===============================================================================
    [..]
        (#) Enable peripheral clock using RCC_APBPeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE)
            function for SPI1 or using RCC_APBPeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE)
            function for SPI2.
        (#) Enable SCK, MOSI, MISO and NSS GPIO clocks using RCC_AHBPeriphClockCmd()
            function. 
        (#) Peripherals alternate function: 
            (++) Connect the pin to the desired peripherals' Alternate 
                 Function (AF) using GPIO_PinAFConfig() function.
            (++) Configure the desired pin in alternate function by:
                 GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF.
            (++) Select the type, pull-up/pull-down and output speed via 
                 GPIO_PuPd, GPIO_OType and GPIO_Speed members.
            (++) Call GPIO_Init() function.
        (#) Program the Polarity, Phase, First Data, Baud Rate Prescaler, Slave 
            Management, Peripheral Mode and CRC Polynomial values using the SPI_Init()
            function in SPI mode. In I2S mode, program the Mode, Standard, Data Format,
            MCLK Output, Audio frequency and Polarity using I2S_Init() function.
        (#) Configure the FIFO threshold using SPI_RxFIFOThresholdConfig() to select 
            at which threshold the RXNE event is generated.     
        (#) Enable the NVIC and the corresponding interrupt using the function 
            SPI_I2S_ITConfig() if you need to use interrupt mode. 
        (#) When using the DMA mode 
            (++) Configure the DMA using DMA_Init() function.
            (++) Active the needed channel Request using SPI_I2S_DMACmd() function.
        (#) Enable the SPI using the SPI_Cmd() function or enable the I2S using
            I2S_Cmd().
        (#) Enable the DMA using the DMA_Cmd() function when using DMA mode. 
        (#) Optionally you can enable/configure the following parameters without
            re-initialization (i.e there is no need to call again SPI_Init() function):
            (++) When bidirectional mode (SPI_Direction_1Line_Rx or SPI_Direction_1Line_Tx)
                 is programmed as Data direction parameter using the SPI_Init() function
                 it can be possible to switch between SPI_Direction_Tx or SPI_Direction_Rx
                 using the SPI_BiDirectionalLineConfig() function.
            (++) When SPI_NSS_Soft is selected as Slave Select Management parameter 
                 using the SPI_Init() function it can be possible to manage the 
                 NSS internal signal using the SPI_NSSInternalSoftwareConfig() function.
            (++) Reconfigure the data size using the SPI_DataSizeConfig() function.  
            (++) Enable or disable the SS output using the SPI_SSOutputCmd() function.
        (#) To use the CRC Hardware calculation feature refer to the Peripheral 
            CRC hardware Calculation subsection.
    [..] It is possible to use SPI in I2S full duplex mode, in this case, each SPI 
         peripheral is able to manage sending and receiving data simultaneously
         using two data lines. Each SPI peripheral has an extended block called I2Sxext
         (ie. I2S2ext for SPI2 and I2S3ext for SPI3).
         The extension block is not a full SPI IP, it is used only as I2S slave to
         implement full duplex mode. The extension block uses the same clock sources
         as its master.          
         To configure I2S full duplex you have to:
        (#) Configure SPIx in I2S mode (I2S_Init() function) as described above. 
        (#) Call the I2S_FullDuplexConfig() function using the same strucutre passed to  
            I2S_Init() function.
        (#) Call I2S_Cmd() for SPIx then for its extended block.
        (#) Configure interrupts or DMA requests and to get/clear flag status, 
            use I2Sxext instance for the extension block.
        [..] Functions that can be called with I2Sxext instances are:
             I2S_Cmd(), I2S_FullDuplexConfig(), SPI_I2S_ReceiveData16(), SPI_I2S_SendData16(), 
             SPI_I2S_DMACmd(), SPI_I2S_ITConfig(), SPI_I2S_GetFlagStatus(), SPI_I2S_ClearFlag(),
             SPI_I2S_GetITStatus() and SPI_I2S_ClearITPendingBit().
        [..] Example: To use SPI3 in Full duplex mode (SPI3 is Master Tx, I2S3ext is Slave Rx):
        [..] RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);   
             I2S_StructInit(&I2SInitStruct);
             I2SInitStruct.Mode = I2S_Mode_MasterTx;     
             I2S_Init(SPI3, &I2SInitStruct);
             I2S_FullDuplexConfig(SPI3ext, &I2SInitStruct)
             I2S_Cmd(SPI3, ENABLE);
             I2S_Cmd(SPI3ext, ENABLE);
             ...
             while (SPI_I2S_GetFlagStatus(SPI2, SPI_FLAG_TXE) == RESET)
             {}
             SPI_I2S_SendData16(SPI3, txdata[i]);
             ...  
             while (SPI_I2S_GetFlagStatus(I2S3ext, SPI_FLAG_RXNE) == RESET)
             {}
             rxdata[i] = SPI_I2S_ReceiveData16(I2S3ext);
             ...          
    [..]
    (@) In SPI mode: To use the SPI TI mode, call the function SPI_TIModeCmd() 
        just after calling the function SPI_Init().  
              
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
#include "stm32f30x_spi.h"
#include "stm32f30x_rcc.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup SPI
  * @brief SPI driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* SPI registers Masks */
#define CR1_CLEAR_MASK       ((uint16_t)0x3040)
#define CR2_LDMA_MASK        ((uint16_t)0x9FFF)

#define I2SCFGR_CLEAR_MASK   ((uint16_t)0xF040)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SPI_Private_Functions
  * @{
  */

/** @defgroup SPI_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
           ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..] This section provides a set of functions allowing to initialize the SPI Direction,
         SPI Mode, SPI Data Size, SPI Polarity, SPI Phase, SPI NSS Management, SPI Baud
         Rate Prescaler, SPI First Bit and SPI CRC Polynomial.
    [..] The SPI_Init() function follows the SPI configuration procedures for Master mode
         and Slave mode (details for these procedures are available in reference manual).
    [..] When the Software NSS management (SPI_InitStruct->SPI_NSS = SPI_NSS_Soft) is selected,
         use the following function to manage the NSS bit:
         void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
    [..] In Master mode, when the Hardware NSS management (SPI_InitStruct->SPI_NSS = SPI_NSS_Hard)
         is selected, use the follwoing function to enable the NSS output feature.
         void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
    [..] The NSS pulse mode can be managed by the SPI TI mode when enabling it using the 
         following function: void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
         And it can be managed by software in the SPI Motorola mode using this function: 
         void SPI_NSSPulseModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
    [..] This section provides also functions to initialize the I2S Mode, Standard, 
         Data Format, MCLK Output, Audio frequency and Polarity.
    [..] The I2S_Init() function follows the I2S configuration procedures for Master mode
         and Slave mode.
  
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the SPIx peripheral registers to their default
  *         reset values.
  * @param  SPIx: To select the SPIx peripheral, where x can be: 1, 2 or 3 
  *         in SPI mode.
  * @retval None
  */
void SPI_I2S_DeInit(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  if (SPIx == SPI1)
  {
    /* Enable SPI1 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
    /* Release SPI1 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
  }
  else if (SPIx == SPI2)
  {
    /* Enable SPI2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
    /* Release SPI2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
  }
  else
  {
    if (SPIx == SPI3)
    {
      /* Enable SPI3 reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
      /* Release SPI3 from reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
    }
  }
}

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
/*--------------- Reset SPI init structure parameters values -----------------*/
  /* Initialize the SPI_Direction member */
  SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  /* Initialize the SPI_Mode member */
  SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
  /* Initialize the SPI_DataSize member */
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
  /* Initialize the SPI_CPOL member */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  /* Initialize the SPI_CPHA member */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  /* Initialize the SPI_NSS member */
  SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
  /* Initialize the SPI_BaudRatePrescaler member */
  SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  /* Initialize the SPI_FirstBit member */
  SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
  /* Initialize the SPI_CRCPolynomial member */
  SPI_InitStruct->SPI_CRCPolynomial = 7;
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *         parameters in the SPI_InitStruct.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
  *         contains the configuration information for the specified SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
  uint16_t tmpreg = 0;

  /* check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Check the SPI parameters */
  assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_DATA_SIZE(SPI_InitStruct->SPI_DataSize));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));

  /* Configuring the SPI in master mode */
  if(SPI_InitStruct->SPI_Mode == SPI_Mode_Master)
  {
/*---------------------------- SPIx CR1 Configuration ------------------------*/
    /* Get the SPIx CR1 value */
    tmpreg = SPIx->CR1;
    /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
    tmpreg &= CR1_CLEAR_MASK;
    /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
       master/slave mode, CPOL and CPHA */
    /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
    /* Set SSM, SSI and MSTR bits according to SPI_Mode and SPI_NSS values */
    /* Set LSBFirst bit according to SPI_FirstBit value */
    /* Set BR bits according to SPI_BaudRatePrescaler value */
    /* Set CPOL bit according to SPI_CPOL value */
    /* Set CPHA bit according to SPI_CPHA value */
    tmpreg |= (uint16_t)((uint16_t)(SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode) |
                         (uint16_t)((uint16_t)(SPI_InitStruct->SPI_CPOL | SPI_InitStruct->SPI_CPHA) |
                         (uint16_t)((uint16_t)(SPI_InitStruct->SPI_NSS | SPI_InitStruct->SPI_BaudRatePrescaler) | 
                         SPI_InitStruct->SPI_FirstBit)));
    /* Write to SPIx CR1 */
    SPIx->CR1 = tmpreg;
    /*-------------------------Data Size Configuration -----------------------*/
    /* Get the SPIx CR2 value */
    tmpreg = SPIx->CR2;
    /* Clear DS[3:0] bits */
    tmpreg &= (uint16_t)~SPI_CR2_DS;
    /* Configure SPIx: Data Size */
    tmpreg |= (uint16_t)(SPI_InitStruct->SPI_DataSize);
    /* Write to SPIx CR2 */
    SPIx->CR2 = tmpreg;
  }
  /* Configuring the SPI in slave mode */
  else
  {
/*---------------------------- Data size Configuration -----------------------*/
    /* Get the SPIx CR2 value */
    tmpreg = SPIx->CR2;
    /* Clear DS[3:0] bits */
    tmpreg &= (uint16_t)~SPI_CR2_DS;
    /* Configure SPIx: Data Size */
    tmpreg |= (uint16_t)(SPI_InitStruct->SPI_DataSize);
    /* Write to SPIx CR2 */
    SPIx->CR2 = tmpreg;
/*---------------------------- SPIx CR1 Configuration ------------------------*/
    /* Get the SPIx CR1 value */
    tmpreg = SPIx->CR1;
    /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
    tmpreg &= CR1_CLEAR_MASK;
    /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
       master/salve mode, CPOL and CPHA */
    /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
    /* Set SSM, SSI and MSTR bits according to SPI_Mode and SPI_NSS values */
    /* Set LSBFirst bit according to SPI_FirstBit value */
    /* Set BR bits according to SPI_BaudRatePrescaler value */
    /* Set CPOL bit according to SPI_CPOL value */
    /* Set CPHA bit according to SPI_CPHA value */
    tmpreg |= (uint16_t)((uint16_t)(SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode) | 
                         (uint16_t)((uint16_t)(SPI_InitStruct->SPI_CPOL | SPI_InitStruct->SPI_CPHA) | 
                         (uint16_t)((uint16_t)(SPI_InitStruct->SPI_NSS | SPI_InitStruct->SPI_BaudRatePrescaler) | 
                         SPI_InitStruct->SPI_FirstBit)));

    /* Write to SPIx CR1 */
    SPIx->CR1 = tmpreg;
  }

  /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
  SPIx->I2SCFGR &= (uint16_t)~((uint16_t)SPI_I2SCFGR_I2SMOD);

/*---------------------------- SPIx CRCPOLY Configuration --------------------*/
  /* Write to SPIx CRCPOLY */
  SPIx->CRCPR = SPI_InitStruct->SPI_CRCPolynomial;
}

/**
  * @brief  Fills each I2S_InitStruct member with its default value.
  * @param  I2S_InitStruct : pointer to a I2S_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct)
{
/*--------------- Reset I2S init structure parameters values -----------------*/
  /* Initialize the I2S_Mode member */
  I2S_InitStruct->I2S_Mode = I2S_Mode_SlaveTx;

  /* Initialize the I2S_Standard member */
  I2S_InitStruct->I2S_Standard = I2S_Standard_Phillips;

  /* Initialize the I2S_DataFormat member */
  I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16b;

  /* Initialize the I2S_MCLKOutput member */
  I2S_InitStruct->I2S_MCLKOutput = I2S_MCLKOutput_Disable;

  /* Initialize the I2S_AudioFreq member */
  I2S_InitStruct->I2S_AudioFreq = I2S_AudioFreq_Default;

  /* Initialize the I2S_CPOL member */
  I2S_InitStruct->I2S_CPOL = I2S_CPOL_Low;
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *   parameters in the I2S_InitStruct.
  * @param  SPIx:To select the SPIx peripheral, where x can be: 2 or 3 
  *         in I2S mode. 
  * @param  I2S_InitStruct: pointer to an I2S_InitTypeDef structure that
  *   contains the configuration information for the specified SPI peripheral
  *   configured in I2S mode.
  * @note
  *  The function calculates the optimal prescaler needed to obtain the most 
  *  accurate audio frequency (depending on the I2S clock source, the PLL values 
  *  and the product configuration). But in case the prescaler value is greater 
  *  than 511, the default value (0x02) will be configured instead.     
  * @retval None
  */
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct)
{
  uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
  uint32_t tmp = 0;
  RCC_ClocksTypeDef RCC_Clocks;
  uint32_t sourceclock = 0;

  /* Check the I2S parameters */
  assert_param(IS_SPI_23_PERIPH(SPIx));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
  assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
  assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
  assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));  

/*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
  /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
  SPIx->I2SCFGR &= I2SCFGR_CLEAR_MASK; 
  SPIx->I2SPR = 0x0002;

  /* Get the I2SCFGR register value */
  tmpreg = SPIx->I2SCFGR;

  /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
  if(I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default)
  {
    i2sodd = (uint16_t)0;
    i2sdiv = (uint16_t)2;   
  }
  /* If the requested audio frequency is not the default, compute the prescaler */
  else
  {
    /* Check the frame length (For the Prescaler computing) */
    if(I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b)
    {
      /* Packet length is 16 bits */
      packetlength = 1;
    }
    else
    {
      /* Packet length is 32 bits */
      packetlength = 2;
    }

    /* I2S Clock source is System clock: Get System Clock frequency */
    RCC_GetClocksFreq(&RCC_Clocks);      

    /* Get the source clock value: based on System Clock value */
    sourceclock = RCC_Clocks.SYSCLK_Frequency;    

    /* Compute the Real divider depending on the MCLK output state with a floating point */
    if(I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable)
    {
      /* MCLK output is enabled */
      tmp = (uint16_t)(((((sourceclock / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    else
    {
      /* MCLK output is disabled */
      tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) *10 ) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    
    /* Remove the floating point */
    tmp = tmp / 10;

    /* Check the parity of the divider */
    i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

    /* Compute the i2sdiv prescaler */
    i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

    /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
    i2sodd = (uint16_t) (i2sodd << 8);
  }

  /* Test if the divider is 1 or 0 or greater than 0xFF */
  if ((i2sdiv < 2) || (i2sdiv > 0xFF))
  {
    /* Set the default values */
    i2sdiv = 2;
    i2sodd = 0;
  }

  /* Write to SPIx I2SPR register the computed value */
  SPIx->I2SPR = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->I2S_MCLKOutput));

  /* Configure the I2S with the SPI_InitStruct values */
  tmpreg |= (uint16_t)((uint16_t)(SPI_I2SCFGR_I2SMOD | I2S_InitStruct->I2S_Mode) | \
                       (uint16_t)((uint16_t)((uint16_t)(I2S_InitStruct->I2S_Standard |I2S_InitStruct->I2S_DataFormat) |\
                       I2S_InitStruct->I2S_CPOL)));

  /* Write to SPIx I2SCFGR */
  SPIx->I2SCFGR = tmpreg;
}

/**
  * @brief  Enables or disables the specified SPI peripheral.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx peripheral. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral */
    SPIx->CR1 |= SPI_CR1_SPE;
  }
  else
  {
    /* Disable the selected SPI peripheral */
    SPIx->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_SPE);
  }
}

/**
  * @brief  Enables or disables the TI Mode.
  * @note    This function can be called only after the SPI_Init() function has 
  *          been called. 
  * @note    When TI mode is selected, the control bits SSM, SSI, CPOL and CPHA 
  *          are not taken into consideration and are configured by hardware 
  *          respectively to the TI mode requirements.  
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.  
  * @param  NewState: new state of the selected SPI TI communication mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the TI mode for the selected SPI peripheral */
    SPIx->CR2 |= SPI_CR2_FRF;
  }
  else
  {
    /* Disable the TI mode for the selected SPI peripheral */
    SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_FRF);
  }
}

/**
  * @brief  Enables or disables the specified SPI peripheral (in I2S mode).
  * @param  SPIx:To select the SPIx peripheral, where x can be: 2 or 3 in 
  *         I2S mode or I2Sxext for I2S full duplex mode. 
  * @param  NewState: new state of the SPIx peripheral. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_23_PERIPH_EXT(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral in I2S mode */
    SPIx->I2SCFGR |= SPI_I2SCFGR_I2SE;
  }
  else
  {
    /* Disable the selected SPI peripheral in I2S mode */
    SPIx->I2SCFGR &= (uint16_t)~((uint16_t)SPI_I2SCFGR_I2SE);
  }
}

/**
  * @brief  Configures the data size for the selected SPI.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral. 
  * @param  SPI_DataSize: specifies the SPI data size.
  *   For the SPIx peripheral this parameter can be one of the following values:
  *     @arg SPI_DataSize_4b: Set data size to 4 bits
  *     @arg SPI_DataSize_5b: Set data size to 5 bits
  *     @arg SPI_DataSize_6b: Set data size to 6 bits
  *     @arg SPI_DataSize_7b: Set data size to 7 bits
  *     @arg SPI_DataSize_8b: Set data size to 8 bits
  *     @arg SPI_DataSize_9b: Set data size to 9 bits
  *     @arg SPI_DataSize_10b: Set data size to 10 bits
  *     @arg SPI_DataSize_11b: Set data size to 11 bits
  *     @arg SPI_DataSize_12b: Set data size to 12 bits
  *     @arg SPI_DataSize_13b: Set data size to 13 bits
  *     @arg SPI_DataSize_14b: Set data size to 14 bits
  *     @arg SPI_DataSize_15b: Set data size to 15 bits
  *     @arg SPI_DataSize_16b: Set data size to 16 bits
  * @retval None
  */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize)
{
  uint16_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DATA_SIZE(SPI_DataSize));
  /* Read the CR2 register */
  tmpreg = SPIx->CR2;
  /* Clear DS[3:0] bits */
  tmpreg &= (uint16_t)~SPI_CR2_DS;
  /* Set new DS[3:0] bits value */
  tmpreg |= SPI_DataSize;
  SPIx->CR2 = tmpreg;
}

/**
  * @brief  Configures the FIFO reception threshold for the selected SPI.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral. 
  * @param  SPI_RxFIFOThreshold: specifies the FIFO reception threshold.
  *   This parameter can be one of the following values:
  *     @arg SPI_RxFIFOThreshold_HF: RXNE event is generated if the FIFO 
  *          level is greater or equal to 1/2. 
  *     @arg SPI_RxFIFOThreshold_QF: RXNE event is generated if the FIFO 
  *          level is greater or equal to 1/4. 
  * @retval None
  */
void SPI_RxFIFOThresholdConfig(SPI_TypeDef* SPIx, uint16_t SPI_RxFIFOThreshold)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_RX_FIFO_THRESHOLD(SPI_RxFIFOThreshold));

  /* Clear FRXTH bit */
  SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_FRXTH);

  /* Set new FRXTH bit value */
  SPIx->CR2 |= SPI_RxFIFOThreshold;
}

/**
  * @brief  Selects the data transfer direction in bidirectional mode for the specified SPI.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral. 
  * @param  SPI_Direction: specifies the data transfer direction in bidirectional mode. 
  *   This parameter can be one of the following values:
  *     @arg SPI_Direction_Tx: Selects Tx transmission direction
  *     @arg SPI_Direction_Rx: Selects Rx receive direction
  * @retval None
  */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DIRECTION(SPI_Direction));
  if (SPI_Direction == SPI_Direction_Tx)
  {
    /* Set the Tx only mode */
    SPIx->CR1 |= SPI_Direction_Tx;
  }
  else
  {
    /* Set the Rx only mode */
    SPIx->CR1 &= SPI_Direction_Rx;
  }
}

/**
  * @brief  Configures internally by software the NSS pin for the selected SPI.
  * @note    This function can be called only after the SPI_Init() function has 
  *          been called.  
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  SPI_NSSInternalSoft: specifies the SPI NSS internal state.
  *   This parameter can be one of the following values:
  *     @arg SPI_NSSInternalSoft_Set: Set NSS pin internally
  *     @arg SPI_NSSInternalSoft_Reset: Reset NSS pin internally
  * @retval None
  */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));

  if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset)
  {
    /* Set NSS pin internally by software */
    SPIx->CR1 |= SPI_NSSInternalSoft_Set;
  }
  else
  {
    /* Reset NSS pin internally by software */
    SPIx->CR1 &= SPI_NSSInternalSoft_Reset;
  }
}

/**
  * @brief  Configures the full duplex mode for the I2Sx peripheral using its
  *         extension I2Sxext according to the specified parameters in the 
  *         I2S_InitStruct.
  * @param  I2Sxext: where x can be  2 or 3 to select the I2S peripheral extension block.
  * @param  I2S_InitStruct: pointer to an I2S_InitTypeDef structure that
  *         contains the configuration information for the specified I2S peripheral
  *         extension.
  * 
  * @note   The structure pointed by I2S_InitStruct parameter should be the same
  *         used for the master I2S peripheral. In this case, if the master is 
  *         configured as transmitter, the slave will be receiver and vice versa.
  *         Or you can force a different mode by modifying the field I2S_Mode to the
  *         value I2S_SlaveRx or I2S_SlaveTx indepedently of the master configuration.    
  *         
  * @note   The I2S full duplex extension can be configured in slave mode only.    
  *  
  * @retval None
  */
void I2S_FullDuplexConfig(SPI_TypeDef* I2Sxext, I2S_InitTypeDef* I2S_InitStruct)
{
  uint16_t tmpreg = 0, tmp = 0;
  
  /* Check the I2S parameters */
  assert_param(IS_I2S_EXT_PERIPH(I2Sxext));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
  assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));  

/*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
  /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
  I2Sxext->I2SCFGR &= I2SCFGR_CLEAR_MASK; 
  I2Sxext->I2SPR = 0x0002;
  
  /* Get the I2SCFGR register value */
  tmpreg = I2Sxext->I2SCFGR;
  
  /* Get the mode to be configured for the extended I2S */
  if ((I2S_InitStruct->I2S_Mode == I2S_Mode_MasterTx) || (I2S_InitStruct->I2S_Mode == I2S_Mode_SlaveTx))
  {
    tmp = I2S_Mode_SlaveRx;
  }
  else
  {
    if ((I2S_InitStruct->I2S_Mode == I2S_Mode_MasterRx) || (I2S_InitStruct->I2S_Mode == I2S_Mode_SlaveRx))
    {
      tmp = I2S_Mode_SlaveTx;
    }
  }

 
  /* Configure the I2S with the SPI_InitStruct values */
  tmpreg |= (uint16_t)((uint16_t)SPI_I2SCFGR_I2SMOD | (uint16_t)(tmp | \
                  (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat | \
                  (uint16_t)I2S_InitStruct->I2S_CPOL))));
 
  /* Write to SPIx I2SCFGR */  
  I2Sxext->I2SCFGR = tmpreg;
}

/**
  * @brief  Enables or disables the SS output for the selected SPI.
  * @note    This function can be called only after the SPI_Init() function has 
  *          been called and the NSS hardware management mode is selected. 
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx SS output. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI SS output */
    SPIx->CR2 |= (uint16_t)SPI_CR2_SSOE;
  }
  else
  {
    /* Disable the selected SPI SS output */
    SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_SSOE);
  }
}

/**
  * @brief  Enables or disables the NSS pulse management mode.
  * @note    This function can be called only after the SPI_Init() function has 
  *          been called. 
  * @note    When TI mode is selected, the control bits NSSP is not taken into 
  *          consideration and are configured by hardware respectively to the 
  *          TI mode requirements. 
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral. 
  * @param  NewState: new state of the NSS pulse management mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_NSSPulseModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the NSS pulse management mode */
    SPIx->CR2 |= SPI_CR2_NSSP;
  }
  else
  {
    /* Disable the NSS pulse management mode */
    SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_NSSP);    
  }
}

/**
  * @}
  */

/** @defgroup SPI_Group2 Data transfers functions
 *  @brief   Data transfers functions
 *
@verbatim
 ===============================================================================
                    ##### Data transfers functions #####
 ===============================================================================  
    [..] This section provides a set of functions allowing to manage the SPI or I2S 
         data transfers.
    [..] In reception, data are received and then stored into an internal Rx buffer while 
         In transmission, data are first stored into an internal Tx buffer before being 
         transmitted.
    [..] The read access of the SPI_DR register can be done using the SPI_I2S_ReceiveData()
         function and returns the Rx buffered value. Whereas a write access to the SPI_DR 
         can be done using SPI_I2S_SendData() function and stores the written data into 
         Tx buffer.

@endverbatim
  * @{
  */

/**
  * @brief  Transmits a Data through the SPIx peripheral.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void SPI_SendData8(SPI_TypeDef* SPIx, uint8_t Data)
{
  uint32_t spixbase = 0x00;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  spixbase = (uint32_t)SPIx; 
  spixbase += 0x0C;
  
  *(__IO uint8_t *) spixbase = Data;
}

/**
  * @brief  Transmits a Data through the SPIx/I2Sx peripheral.
  * @param  SPIx: To select the SPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
  *         in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.  
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void SPI_I2S_SendData16(SPI_TypeDef* SPIx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
  
  SPIx->DR = (uint16_t)Data;
}

/**
  * @brief  Returns the most recent received data by the SPIx peripheral. 
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @retval The value of the received data.
  */
uint8_t SPI_ReceiveData8(SPI_TypeDef* SPIx)
{
  uint32_t spixbase = 0x00;
  
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
  
  spixbase = (uint32_t)SPIx; 
  spixbase += 0x0C;
  
  return *(__IO uint8_t *) spixbase;
}

/**
  * @brief  Returns the most recent received data by the SPIx peripheral. 
  * @param  SPIx: To select the SPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
  *         in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
  * @retval The value of the received data.
  */
uint16_t SPI_I2S_ReceiveData16(SPI_TypeDef* SPIx)
{  
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
  
  return SPIx->DR;
}
/**
  * @}
  */

/** @defgroup SPI_Group3 Hardware CRC Calculation functions
 *  @brief   Hardware CRC Calculation functions
 *
@verbatim   
 ===============================================================================
                  ##### Hardware CRC Calculation functions #####
 ===============================================================================  
    [..] This section provides a set of functions allowing to manage the SPI CRC hardware 
         calculation.
    [..] SPI communication using CRC is possible through the following procedure:
         (#) Program the Data direction, Polarity, Phase, First Data, Baud Rate Prescaler, 
             Slave Management, Peripheral Mode and CRC Polynomial values using the SPI_Init()
             function.
         (#) Enable the CRC calculation using the SPI_CalculateCRC() function.
         (#) Enable the SPI using the SPI_Cmd() function
         (#) Before writing the last data to the TX buffer, set the CRCNext bit using the 
             SPI_TransmitCRC() function to indicate that after transmission of the last 
             data, the CRC should be transmitted.
         (#) After transmitting the last data, the SPI transmits the CRC. The SPI_CR1_CRCNEXT
             bit is reset. The CRC is also received and compared against the SPI_RXCRCR 
             value. 
             If the value does not match, the SPI_FLAG_CRCERR flag is set and an interrupt
             can be generated when the SPI_I2S_IT_ERR interrupt is enabled.
    [..]
    (@)
         (+@) It is advised to don't read the calculate CRC values during the communication.
         (+@) When the SPI is in slave mode, be careful to enable CRC calculation only 
              when the clock is stable, that is, when the clock is in the steady state. 
              If not, a wrong CRC calculation may be done. In fact, the CRC is sensitive 
              to the SCK slave input clock as soon as CRCEN is set, and this, whatever 
              the value of the SPE bit.
         (+@) With high bitrate frequencies, be careful when transmitting the CRC.
              As the number of used CPU cycles has to be as low as possible in the CRC 
              transfer phase, it is forbidden to call software functions in the CRC 
              transmission sequence to avoid errors in the last data and CRC reception. 
              In fact, CRCNEXT bit has to be written before the end of the transmission/reception 
              of the last data.
         (+@) For high bit rate frequencies, it is advised to use the DMA mode to avoid the
              degradation of the SPI speed performance due to CPU accesses impacting the 
              SPI bandwidth.
         (+@) When the STM32F30x are configured as slaves and the NSS hardware mode is 
              used, the NSS pin needs to be kept low between the data phase and the CRC 
              phase.
         (+@) When the SPI is configured in slave mode with the CRC feature enabled, CRC
              calculation takes place even if a high level is applied on the NSS pin. 
              This may happen for example in case of a multislave environment where the 
              communication master addresses slaves alternately.
         (+@) Between a slave deselection (high level on NSS) and a new slave selection 
              (low level on NSS), the CRC value should be cleared on both master and slave
              sides in order to resynchronize the master and slave for their respective 
              CRC calculation.
    [..]          
    (@) To clear the CRC, follow the procedure below:
         (#@) Disable SPI using the SPI_Cmd() function.
         (#@) Disable the CRC calculation using the SPI_CalculateCRC() function.
         (#@) Enable the CRC calculation using the SPI_CalculateCRC() function.
         (#@) Enable SPI using the SPI_Cmd() function.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the CRC calculation length for the selected SPI.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  SPI_CRCLength: specifies the SPI CRC calculation length.
  *   This parameter can be one of the following values:
  *     @arg SPI_CRCLength_8b: Set CRC Calculation to 8 bits
  *     @arg SPI_CRCLength_16b: Set CRC Calculation to 16 bits
  * @retval None
  */
void SPI_CRCLengthConfig(SPI_TypeDef* SPIx, uint16_t SPI_CRCLength)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC_LENGTH(SPI_CRCLength));

  /* Clear CRCL bit */
  SPIx->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_CRCL);

  /* Set new CRCL bit value */
  SPIx->CR1 |= SPI_CRCLength;
}

/**
  * @brief  Enables or disables the CRC value calculation of the transferred bytes.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx CRC value calculation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI CRC calculation */
    SPIx->CR1 |= SPI_CR1_CRCEN;
  }
  else
  {
    /* Disable the selected SPI CRC calculation */
    SPIx->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_CRCEN);
  }
}

/**
  * @brief  Transmits the SPIx CRC value.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @retval None
  */
void SPI_TransmitCRC(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Enable the selected SPI CRC transmission */
  SPIx->CR1 |= SPI_CR1_CRCNEXT;
}

/**
  * @brief  Returns the transmit or the receive CRC register value for the specified SPI.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  SPI_CRC: specifies the CRC register to be read.
  *   This parameter can be one of the following values:
  *     @arg SPI_CRC_Tx: Selects Tx CRC register
  *     @arg SPI_CRC_Rx: Selects Rx CRC register
  * @retval The selected CRC register value..
  */
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC)
{
  uint16_t crcreg = 0;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC(SPI_CRC));

  if (SPI_CRC != SPI_CRC_Rx)
  {
    /* Get the Tx CRC register */
    crcreg = SPIx->TXCRCR;
  }
  else
  {
    /* Get the Rx CRC register */
    crcreg = SPIx->RXCRCR;
  }
  /* Return the selected CRC register */
  return crcreg;
}

/**
  * @brief  Returns the CRC Polynomial register value for the specified SPI.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @retval The CRC Polynomial register value.
  */
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Return the CRC polynomial register */
  return SPIx->CRCPR;
}

/**
  * @}
  */

/** @defgroup SPI_Group4 DMA transfers management functions
 *  @brief   DMA transfers management functions
  *
@verbatim   
 ===============================================================================
                  ##### DMA transfers management functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the SPIx/I2Sx DMA interface.
  * @param  SPIx:To select the SPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
  *         in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode. 
  * @param  SPI_I2S_DMAReq: specifies the SPI DMA transfer request to be enabled or disabled. 
  *   This parameter can be any combination of the following values:
  *     @arg SPI_I2S_DMAReq_Tx: Tx buffer DMA transfer request
  *     @arg SPI_I2S_DMAReq_Rx: Rx buffer DMA transfer request
  * @param  NewState: new state of the selected SPI DMA transfer request.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_DMA_REQ(SPI_I2S_DMAReq));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI DMA requests */
    SPIx->CR2 |= SPI_I2S_DMAReq;
  }
  else
  {
    /* Disable the selected SPI DMA requests */
    SPIx->CR2 &= (uint16_t)~SPI_I2S_DMAReq;
  }
}

/**
  * @brief  Configures the number of data to transfer type(Even/Odd) for the DMA
  *         last transfers and for the selected SPI.
  * @note   This function have a meaning only if DMA mode is selected and if 
  *         the packing mode is used (data length <= 8 and DMA transfer size halfword)  
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @param  SPI_LastDMATransfer: specifies the SPI last DMA transfers state.
  *   This parameter can be one of the following values:
  *     @arg SPI_LastDMATransfer_TxEvenRxEven: Number of data for transmission Even
  *          and number of data for reception Even.
  *     @arg SPI_LastDMATransfer_TxOddRxEven: Number of data for transmission Odd
  *          and number of data for reception Even.
  *     @arg SPI_LastDMATransfer_TxEvenRxOdd: Number of data for transmission Even
  *          and number of data for reception Odd.
  *     @arg SPI_LastDMATransfer_TxOddRxOdd: RNumber of data for transmission Odd
  *          and number of data for reception Odd.
  * @retval None
  */
void SPI_LastDMATransferCmd(SPI_TypeDef* SPIx, uint16_t SPI_LastDMATransfer)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_LAST_DMA_TRANSFER(SPI_LastDMATransfer));

  /* Clear LDMA_TX and LDMA_RX bits */
  SPIx->CR2 &= CR2_LDMA_MASK;

  /* Set new LDMA_TX and LDMA_RX bits value */
  SPIx->CR2 |= SPI_LastDMATransfer; 
}

/**
  * @}
  */

/** @defgroup SPI_Group5 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
  *
@verbatim   
 ===============================================================================
              ##### Interrupts and flags management functions #####
 ===============================================================================  
    [..] This section provides a set of functions allowing to configure the SPI/I2S 
         Interrupts sources and check or clear the flags or pending bits status.
         The user should identify which mode will be used in his application to manage 
         the communication: Polling mode, Interrupt mode or DMA mode. 
    
  *** Polling Mode ***
  ====================
    [..] In Polling Mode, the SPI/I2S communication can be managed by 9 flags:
         (#) SPI_I2S_FLAG_TXE : to indicate the status of the transmit buffer register.
         (#) SPI_I2S_FLAG_RXNE : to indicate the status of the receive buffer register.
         (#) SPI_I2S_FLAG_BSY : to indicate the state of the communication layer of the SPI.
         (#) SPI_FLAG_CRCERR : to indicate if a CRC Calculation error occur.              
         (#) SPI_FLAG_MODF : to indicate if a Mode Fault error occur.
         (#) SPI_I2S_FLAG_OVR : to indicate if an Overrun error occur.
         (#) SPI_I2S_FLAG_FRE: to indicate a Frame Format error occurs.
         (#) I2S_FLAG_UDR: to indicate an Underrun error occurs.
         (#) I2S_FLAG_CHSIDE: to indicate Channel Side.
    [..]
         (@) Do not use the BSY flag to handle each data transmission or reception.
             It is better to use the TXE and RXNE flags instead.
    [..] In this Mode it is advised to use the following functions:
         (+) FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
         (+) void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);

  *** Interrupt Mode ***
  ======================
    [..] In Interrupt Mode, the SPI/I2S communication can be managed by 3 interrupt sources
         and 5 pending bits: 
    [..] Pending Bits:
         (#) SPI_I2S_IT_TXE : to indicate the status of the transmit buffer register.
         (#) SPI_I2S_IT_RXNE : to indicate the status of the receive buffer register.
         (#) SPI_I2S_IT_OVR : to indicate if an Overrun error occur.
         (#) I2S_IT_UDR : to indicate an Underrun Error occurs.
         (#) SPI_I2S_FLAG_FRE : to indicate a Frame Format error occurs.
    [..] Interrupt Source:
         (#) SPI_I2S_IT_TXE: specifies the interrupt source for the Tx buffer empty 
             interrupt.  
         (#) SPI_I2S_IT_RXNE : specifies the interrupt source for the Rx buffer not 
             empty interrupt.
         (#) SPI_I2S_IT_ERR : specifies the interrupt source for the errors interrupt.
    [..] In this Mode it is advised to use the following functions:
         (+) void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
         (+) ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);

  *** FIFO Status ***
  ===================
    [..] It is possible to monitor the FIFO status when a transfer is ongoing using the
         following function:
         (+) uint32_t SPI_GetFIFOStatus(uint8_t SPI_FIFO_Direction); 

  *** DMA Mode ***
  ================
    [..] In DMA Mode, the SPI communication can be managed by 2 DMA Channel requests:
         (#) SPI_I2S_DMAReq_Tx: specifies the Tx buffer DMA transfer request.
         (#) SPI_I2S_DMAReq_Rx: specifies the Rx buffer DMA transfer request.
    [..] In this Mode it is advised to use the following function:
         (+) void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified SPI/I2S interrupts.
  * @param  SPIx: To select the SPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
  *         in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.  
  * @param  SPI_I2S_IT: specifies the SPI interrupt source to be enabled or disabled. 
  *   This parameter can be one of the following values:
  *     @arg SPI_I2S_IT_TXE: Tx buffer empty interrupt mask
  *     @arg SPI_I2S_IT_RXNE: Rx buffer not empty interrupt mask
  *     @arg SPI_I2S_IT_ERR: Error interrupt mask
  * @param  NewState: new state of the specified SPI interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState)
{
  uint16_t itpos = 0, itmask = 0 ;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_CONFIG_IT(SPI_I2S_IT));

  /* Get the SPI IT index */
  itpos = SPI_I2S_IT >> 4;

  /* Set the IT mask */
  itmask = (uint16_t)1 << (uint16_t)itpos;

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI interrupt */
    SPIx->CR2 |= itmask;
  }
  else
  {
    /* Disable the selected SPI interrupt */
    SPIx->CR2 &= (uint16_t)~itmask;
  }
}

/**
  * @brief  Returns the current SPIx Transmission FIFO filled level.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @retval The Transmission FIFO filling state.
  *   - SPI_TransmissionFIFOStatus_Empty: when FIFO is empty
  *   - SPI_TransmissionFIFOStatus_1QuarterFull: if more than 1 quarter-full.
  *   - SPI_TransmissionFIFOStatus_HalfFull: if more than 1 half-full.
  *   - SPI_TransmissionFIFOStatus_Full: when FIFO is full.
  */
uint16_t SPI_GetTransmissionFIFOStatus(SPI_TypeDef* SPIx)
{
  /* Get the SPIx Transmission FIFO level bits */
  return (uint16_t)((SPIx->SR & SPI_SR_FTLVL));
}

/**
  * @brief  Returns the current SPIx Reception FIFO filled level.
  * @param  SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
  * @retval The Reception FIFO filling state.
  *   - SPI_ReceptionFIFOStatus_Empty: when FIFO is empty
  *   - SPI_ReceptionFIFOStatus_1QuarterFull: if more than 1 quarter-full.
  *   - SPI_ReceptionFIFOStatus_HalfFull: if more than 1 half-full.
  *   - SPI_ReceptionFIFOStatus_Full: when FIFO is full.
  */
uint16_t SPI_GetReceptionFIFOStatus(SPI_TypeDef* SPIx)
{
  /* Get the SPIx Reception FIFO level bits */
  return (uint16_t)((SPIx->SR & SPI_SR_FRLVL));
}

/**
  * @brief  Checks whether the specified SPI flag is set or not.
  * @param  SPIx: To select the SPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
  *         in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.  
  * @param  SPI_I2S_FLAG: specifies the SPI flag to check. 
  *   This parameter can be one of the following values:
  *     @arg SPI_I2S_FLAG_TXE: Transmit buffer empty flag.
  *     @arg SPI_I2S_FLAG_RXNE: Receive buffer not empty flag.
  *     @arg SPI_I2S_FLAG_BSY: Busy flag.
  *     @arg SPI_I2S_FLAG_OVR: Overrun flag.
  *     @arg SPI_I2S_FLAG_MODF: Mode Fault flag.
  *     @arg SPI_I2S_FLAG_CRCERR: CRC Error flag.
  *     @arg SPI_I2S_FLAG_FRE: TI frame format error flag.
  *     @arg I2S_FLAG_UDR: Underrun Error flag.
  *     @arg I2S_FLAG_CHSIDE: Channel Side flag.   
  * @retval The new state of SPI_I2S_FLAG (SET or RESET).
  */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
  assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));

  /* Check the status of the specified SPI flag */
  if ((SPIx->SR & SPI_I2S_FLAG) != (uint16_t)RESET)
  {
    /* SPI_I2S_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_I2S_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the SPIx CRC Error (CRCERR) flag.
  * @param  SPIx: To select the SPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
  *         in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode. 
  * @param  SPI_I2S_FLAG: specifies the SPI flag to clear. 
  *   This function clears only CRCERR flag.
  * @note OVR (OverRun error) flag is cleared by software sequence: a read 
  *       operation to SPI_DR register (SPI_I2S_ReceiveData()) followed by a read 
  *       operation to SPI_SR register (SPI_I2S_GetFlagStatus()).
  * @note MODF (Mode Fault) flag is cleared by software sequence: a read/write 
  *       operation to SPI_SR register (SPI_I2S_GetFlagStatus()) followed by a 
  *       write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
  * @retval None
  */
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
  assert_param(IS_SPI_CLEAR_FLAG(SPI_I2S_FLAG));

  /* Clear the selected SPI CRC Error (CRCERR) flag */
  SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
}

/**
  * @brief  Checks whether the specified SPI/I2S interrupt has occurred or not.
  * @param  SPIx: To select the SPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
  *         in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.  
  * @param  SPI_I2S_IT: specifies the SPI interrupt source to check. 
  *   This parameter can be one of the following values:
  *     @arg SPI_I2S_IT_TXE: Transmit buffer empty interrupt.
  *     @arg SPI_I2S_IT_RXNE: Receive buffer not empty interrupt.
  *     @arg SPI_IT_MODF: Mode Fault interrupt.
  *     @arg SPI_I2S_IT_OVR: Overrun interrupt.
  *     @arg I2S_IT_UDR: Underrun interrupt.  
  *     @arg SPI_I2S_IT_FRE: Format Error interrupt.  
  * @retval The new state of SPI_I2S_IT (SET or RESET).
  */
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT)
{
  ITStatus bitstatus = RESET;
  uint16_t itpos = 0, itmask = 0, enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
  assert_param(IS_SPI_I2S_GET_IT(SPI_I2S_IT));

  /* Get the SPI_I2S_IT index */
  itpos = 0x01 << (SPI_I2S_IT & 0x0F);

  /* Get the SPI_I2S_IT IT mask */
  itmask = SPI_I2S_IT >> 4;

  /* Set the IT mask */
  itmask = 0x01 << itmask;

  /* Get the SPI_I2S_IT enable bit status */
  enablestatus = (SPIx->CR2 & itmask) ;

  /* Check the status of the specified SPI interrupt */
  if (((SPIx->SR & itpos) != (uint16_t)RESET) && enablestatus)
  {
    /* SPI_I2S_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_IT is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_I2S_IT status */
  return bitstatus;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
