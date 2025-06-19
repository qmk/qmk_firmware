#pragma once

// WS2812配置
#define WS2812_PWM_DRIVER      PWMD2
#define WS2812_PWM_CHANNEL     3
#define WS2812_PWM_PAL_MODE    1
#define WS2812_DMA_STREAM      STM32_DMA1_STREAM1
#define WS2812_DMA_CHANNEL     3
#define RGB_POWER_ENABLED_PIN  A15

// 串口通信
#define BHQ_IQR_PIN              B8
#define BHQ_INT_PIN              B9

#define UART_DRIVER             SD1
#define UART_TX_PIN             B6
#define UART_TX_PAL_MODE        7
#define UART_RX_PIN             B7
#define UART_RX_PAL_MODE        7

// STM32使用到的高速晶振引脚号，做低功耗需要用户配置，每款芯片有可能不一样的
#define LPM_STM32_HSE_PIN_IN     H0
#define LPM_STM32_HSE_PIN_OUT    H1

// 电池电压读取的引脚
#define BATTER_ADC_PIN     B1
#define BATTER_ADC_DRIVER  ADCD1

#define REPORT_BUFFER_QUEUE_SIZE 68

// USB检测引脚，默认1，高电平有效
#define USB_POWER_SENSE_PIN        B0
#define USB_POWER_CONNECTED_LEVEL  1
