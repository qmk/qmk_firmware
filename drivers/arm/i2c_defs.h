#pragma once

#if defined(STM32F1XX) || defined(STM32F1xx) || defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32L0xx) || defined(STM32L1xx)
    #define USE_I2CV1
#endif

#ifdef I2C1_BANK
    #define I2C1_SCL_BANK I2C1_BANK
    #define I2C1_SDA_BANK I2C1_BANK
#endif

#ifndef I2C1_SCL_BANK
    #define I2C1_SCL_BANK GPIOB
#endif

#ifndef I2C1_SDA_BANK
    #define I2C1_SDA_BANK GPIOB
#endif

#ifndef I2C1_SCL
    #define I2C1_SCL 6
#endif
#ifndef I2C1_SDA
    #define I2C1_SDA 7
#endif

#ifdef USE_I2CV1
    #ifndef I2C1_OPMODE
        #define I2C1_OPMODE OPMODE_I2C
    #endif
    #ifndef I2C1_CLOCK_SPEED
        #define I2C1_CLOCK_SPEED 100000 /* 400000 */
    #endif
    #ifndef I2C1_DUTY_CYCLE
        #define I2C1_DUTY_CYCLE STD_DUTY_CYCLE /* FAST_DUTY_CYCLE_2 */
    #endif
#else
    // The default PAL alternate modes are used to signal that the pins are used for I2C
    #ifndef I2C1_SCL_PAL_MODE
        #define I2C1_SCL_PAL_MODE 4
    #endif
    #ifndef I2C1_SDA_PAL_MODE
        #define I2C1_SDA_PAL_MODE 4
    #endif

    // The default timing values below configures the I2C clock to 400khz assuming a 72Mhz clock
    // For more info : https://www.st.com/en/embedded-software/stsw-stm32126.html
    #ifndef I2C1_TIMINGR_PRESC
        #define I2C1_TIMINGR_PRESC 15U
    #endif
    #ifndef I2C1_TIMINGR_SCLDEL
        #define I2C1_TIMINGR_SCLDEL 4U
    #endif
    #ifndef I2C1_TIMINGR_SDADEL
        #define I2C1_TIMINGR_SDADEL 2U
    #endif
    #ifndef I2C1_TIMINGR_SCLH
        #define I2C1_TIMINGR_SCLH 15U
    #endif
    #ifndef I2C1_TIMINGR_SCLL
        #define I2C1_TIMINGR_SCLL 21U
    #endif
#endif

#ifndef I2C_DRIVER
  #define I2C_DRIVER I2CD1
#endif
