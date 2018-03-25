/*

  WS2812B CPU and memory efficient library

  Date: 28.9.2016

  Author: Martin Hubacek
  	  	  http://www.martinhubacek.cz
  	  	  @hubmartin

  Licence: MIT License

*/

#ifndef WS2812B_H_
#define WS2812B_H_
#include "ws2812.h"

// GPIO enable command
#define WS2812B_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
// LED output port
#define WS2812B_PORT GPIOC
// LED output pins
#define WS2812B_PINS (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3)
// How many LEDs are in the series
#define WS2812B_NUMBER_OF_LEDS 60

// Number of output LED strips. Each has its own buffer.
#define WS2812_BUFFER_COUNT 2

// Choose one of the bit-juggling setpixel implementation
// *******************************************************
//#define SETPIX_1	// For loop, works everywhere, slow
//#define SETPIX_2	// Bit band in a loop
//#define SETPIX_3	// Like SETPIX_1 but with unrolled loop
#define SETPIX_4	// Fastest copying using bit-banding


// DEBUG OUTPUT
// ********************
#define LED4_PORT GPIOC
#define LED4_PIN GPIO_PIN_10

#define LED5_PORT GPIOC
#define LED5_PIN GPIO_PIN_10


// Public functions
// ****************
void ws2812b_init();
void ws2812b_handle();

// Library structures
// ******************
// This value sets number of periods to generate 50uS Treset signal
#define WS2812_RESET_PERIOD 12

typedef struct WS2812_BufferItem {
	uint8_t* frameBufferPointer;
	uint32_t frameBufferSize;
	uint32_t frameBufferCounter;
	uint8_t channel;	// digital output pin/channel
} WS2812_BufferItem;



typedef struct WS2812_Struct
{
	WS2812_BufferItem item[WS2812_BUFFER_COUNT];
	uint8_t transferComplete;
	uint8_t startTransfer;
	uint32_t timerPeriodCounter;
	uint32_t repeatCounter;
} WS2812_Struct;

WS2812_Struct ws2812b;

// Bit band stuff
#define RAM_BASE 0x20000000
#define RAM_BB_BASE 0x22000000
#define Var_ResetBit_BB(VarAddr, BitNumber) (*(volatile uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)
#define Var_SetBit_BB(VarAddr, BitNumber) (*(volatile uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)
#define Var_GetBit_BB(VarAddr, BitNumber) (*(volatile uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))
#define BITBAND_SRAM(address, bit) ( (__IO uint32_t *) (RAM_BB_BASE + (((uint32_t)address) - RAM_BASE) * 32 + (bit) * 4))

#define varSetBit(var,bit) (Var_SetBit_BB((uint32_t)&var,bit))
#define varResetBit(var,bit) (Var_ResetBit_BB((uint32_t)&var,bit))
#define varGetBit(var,bit) (Var_GetBit_BB((uint32_t)&var,bit))

static void ws2812b_set_pixel(uint8_t row, uint16_t column, uint8_t red, uint8_t green, uint8_t blue);
void DMA_TransferCompleteHandler(DMA_HandleTypeDef *DmaHandle);
void DMA_TransferHalfHandler(DMA_HandleTypeDef *DmaHandle);

#endif /* WS2812B_H_ */