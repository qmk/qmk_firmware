#pragma once
#include_next <mcuconf.h>

// SPI Trackball
#undef  RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE

// UART Split
#undef  RP_SERIAL_USE_UART0
#define RP_SERIAL_USE_UART0 TRUE

//I2C OLED
#undef  RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE
