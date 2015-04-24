/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

#include "device.h"
#include "PeripheralPins.h"
#include "ioman_regs.h"

/*
 * To select a peripheral function on Maxim microcontrollers, multiple
 * configurations must be made. The mbed PinMap structure only includes one
 * data member to hold this information. To extend the configuration storage,
 * the "function" data member is used as a pointer to a pin_function_t
 * structure. This structure is defined in objects.h. The definitions below
 * include the creation of the pin_function_t structures and the assignment of
 * the pointers to the "function" data members.
 */

#ifdef TOOLCHAIN_ARM_STD
#pragma diag_suppress 1296
#endif

/************I2C***************/
const PinMap PinMap_I2C_SDA[] = {
    { P0_4,  I2C_0, (int)&((pin_function_t){&MXC_IOMAN->i2cm0_req, &MXC_IOMAN->i2cm0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_D | MXC_F_IOMAN_I2CM_CORE_IO), (MXC_F_IOMAN_I2CM_MAPPING | MXC_F_IOMAN_I2CM_CORE_IO)}) },
    { P0_6,  I2C_1, (int)&((pin_function_t){&MXC_IOMAN->i2cm1_req, &MXC_IOMAN->i2cm1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_H | MXC_F_IOMAN_I2CM_CORE_IO), (MXC_F_IOMAN_I2CM_MAPPING | MXC_F_IOMAN_I2CM_CORE_IO)}) },
    { NC,    NC,    0 }
};

const PinMap PinMap_I2C_SCL[] = {
    { P0_5,  I2C_0, (int)&((pin_function_t){&MXC_IOMAN->i2cm0_req, &MXC_IOMAN->i2cm0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_D | MXC_F_IOMAN_I2CM_CORE_IO), (MXC_F_IOMAN_I2CM_MAPPING | MXC_F_IOMAN_I2CM_CORE_IO)}) },
    { P0_7,  I2C_1, (int)&((pin_function_t){&MXC_IOMAN->i2cm1_req, &MXC_IOMAN->i2cm1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_H | MXC_F_IOMAN_I2CM_CORE_IO), (MXC_F_IOMAN_I2CM_MAPPING | MXC_F_IOMAN_I2CM_CORE_IO)}) },
    { NC,    NC,    0 }
};

/************UART***************/
const PinMap PinMap_UART_TX[] = {
    { P1_1, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P1_3, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P2_1, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P2_5, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P0_1, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_D | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P1_7, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_D | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { NC,   NC,     0 }
};

const PinMap PinMap_UART_RX[] = {
    { P1_0, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P1_2, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P2_0, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P2_4, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P0_0, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_D | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { P1_6, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_D | MXC_F_IOMAN_UART_CORE_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CORE_IO)}) },
    { NC,   NC,     0 }
};

const PinMap PinMap_UART_CTS[] = {
    { P1_2, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_UART_CTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CTS_IO)}) },
    { P1_6, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_UART_CTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CTS_IO)}) },
    { P2_4, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_UART_CTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CTS_IO)}) },
    { P2_6, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_UART_CTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CTS_IO)}) },
    { P0_2, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_D | MXC_F_IOMAN_UART_CTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_CTS_IO)}) },
    { NC,   NC,     0 }
};

const PinMap PinMap_UART_RTS[] = {
    { P1_3, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_UART_RTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_RTS_IO)}) },
    { P1_7, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_UART_RTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_RTS_IO)}) },
    { P2_5, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_UART_RTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_RTS_IO)}) },
    { P2_7, UART_1, (int)&((pin_function_t){&MXC_IOMAN->uart1_req, &MXC_IOMAN->uart1_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_UART_RTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_RTS_IO)}) },
    { P0_3, UART_0, (int)&((pin_function_t){&MXC_IOMAN->uart0_req, &MXC_IOMAN->uart0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_D | MXC_F_IOMAN_UART_RTS_IO), (MXC_F_IOMAN_UART_MAPPING | MXC_F_IOMAN_UART_RTS_IO)}) },
    { NC,   NC,     0 }
};

/************SPI***************/
const PinMap PinMap_SPI_SCLK[] = {
    { P0_0, SPI_0, (int)&((pin_function_t){&MXC_IOMAN->spi0_req, &MXC_IOMAN->spi0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_SPI_CORE_IO), (MXC_F_IOMAN_SPI_MAPPING | MXC_F_IOMAN_SPI_CORE_IO)}) },
    { P2_0, SPI_2, (int)&((pin_function_t){&MXC_IOMAN->spi2_req, &MXC_IOMAN->spi2_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_SPI_CORE_IO), (MXC_F_IOMAN_SPI_MAPPING | MXC_F_IOMAN_SPI_CORE_IO)}) },
    { NC,   NC,    0}
};

const PinMap PinMap_SPI_MOSI[] = {
    { P0_1, SPI_0, (int)&((pin_function_t){&MXC_IOMAN->spi0_req, &MXC_IOMAN->spi0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_SPI_CORE_IO), (MXC_F_IOMAN_SPI_MAPPING | MXC_F_IOMAN_SPI_CORE_IO)}) },
    { P2_1, SPI_2, (int)&((pin_function_t){&MXC_IOMAN->spi2_req, &MXC_IOMAN->spi2_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_SPI_CORE_IO), (MXC_F_IOMAN_SPI_MAPPING | MXC_F_IOMAN_SPI_CORE_IO)}) },
    { NC,   NC,    0}
};

const PinMap PinMap_SPI_MISO[] = {
    { P0_2, SPI_0, (int)&((pin_function_t){&MXC_IOMAN->spi0_req, &MXC_IOMAN->spi0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_SPI_CORE_IO), (MXC_F_IOMAN_SPI_MAPPING | MXC_F_IOMAN_SPI_CORE_IO)}) },
    { P2_2, SPI_2, (int)&((pin_function_t){&MXC_IOMAN->spi2_req, &MXC_IOMAN->spi2_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_SPI_CORE_IO), (MXC_F_IOMAN_SPI_MAPPING | MXC_F_IOMAN_SPI_CORE_IO)}) },
    { NC,   NC,    0}
};

const PinMap PinMap_SPI_SSEL[] = {
    { P0_3, SPI_0, (int)&((pin_function_t){&MXC_IOMAN->spi0_req, &MXC_IOMAN->spi0_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_A | MXC_F_IOMAN_SPI_SS0_IO), (MXC_F_IOMAN_SPI_MAPPING | MXC_F_IOMAN_SPI_SS0_IO)}) },
    { P2_3, SPI_2, (int)&((pin_function_t){&MXC_IOMAN->spi2_req, &MXC_IOMAN->spi2_ack, ((uint32_t)MXC_E_IOMAN_MAPPING_B | MXC_F_IOMAN_SPI_SS0_IO | MXC_F_IOMAN_SPI_SR0_IO), (MXC_F_IOMAN_SPI_MAPPING | MXC_F_IOMAN_SPI_SS0_IO | MXC_F_IOMAN_SPI_SR0_IO)}) },
    { NC,   NC,    0}
};

/************PWM***************/
const PinMap PinMap_PWM[] = {
    {P0_0, PWM_0, 1}, {P0_0, PWM_0, 2}, {P0_0, PWM_4, 3},
    {P0_1, PWM_0, 3}, {P0_1, PWM_1, 1}, {P0_1, PWM_4, 2},
    {P0_2, PWM_1, 2}, {P0_2, PWM_2, 1}, {P0_2, PWM_5, 3},
    {P0_3, PWM_1, 3}, {P0_3, PWM_3, 1}, {P0_3, PWM_5, 2},
    {P0_4, PWM_2, 2}, {P0_4, PWM_4, 1}, {P0_4, PWM_6, 3},
    {P0_5, PWM_2, 3}, {P0_5, PWM_5, 1}, {P0_5, PWM_6, 2},
    {P0_6, PWM_3, 2}, {P0_6, PWM_6, 1}, {P0_6, PWM_7, 3},
    {P0_7, PWM_3, 3}, {P0_7, PWM_7, 1}, {P0_7, PWM_7, 2},

    {P1_0, PWM_0, 1}, {P1_0, PWM_0, 2}, {P1_0, PWM_4, 3},
    {P1_1, PWM_0, 3}, {P1_1, PWM_1, 1}, {P1_1, PWM_4, 2},
    {P1_2, PWM_1, 2}, {P1_2, PWM_2, 1}, {P1_2, PWM_5, 3},
    {P1_3, PWM_1, 3}, {P1_3, PWM_3, 1}, {P1_3, PWM_5, 2},
    {P1_4, PWM_2, 2}, {P1_4, PWM_4, 1}, {P1_4, PWM_6, 3},
    {P1_5, PWM_2, 3}, {P1_5, PWM_5, 1}, {P1_5, PWM_6, 2},
    {P1_6, PWM_3, 2}, {P1_6, PWM_6, 1}, {P1_6, PWM_7, 3},
    {P1_7, PWM_3, 3}, {P1_7, PWM_7, 1}, {P1_7, PWM_7, 2},

    {P2_0, PWM_0, 1}, {P2_0, PWM_0, 2}, {P2_0, PWM_4, 3},
    {P2_1, PWM_0, 3}, {P2_1, PWM_1, 1}, {P2_1, PWM_4, 2},
    {P2_2, PWM_1, 2}, {P2_2, PWM_2, 1}, {P2_2, PWM_5, 3},
    {P2_3, PWM_1, 3}, {P2_3, PWM_3, 1}, {P2_3, PWM_5, 2},
    {P2_4, PWM_2, 2}, {P2_4, PWM_4, 1}, {P2_4, PWM_6, 3},
    {P2_5, PWM_2, 3}, {P2_5, PWM_5, 1}, {P2_5, PWM_6, 2},
    {P2_6, PWM_3, 2}, {P2_6, PWM_6, 1}, {P2_6, PWM_7, 3},
    {P2_7, PWM_3, 3}, {P2_7, PWM_7, 1}, {P2_7, PWM_7, 2},
    {NC,   NC,    0}
};

/************ADC***************/
const PinMap PinMap_ADC[] = {
    {AIN_0P, ADC, 0},
    {AIN_1P, ADC, 0},
    {AIN_2P, ADC, 0},
    {AIN_3P, ADC, 0},
    {AIN_4P, ADC, 0},
    {AIN_5P, ADC, 0},
    {AIN_0N, ADC, 0},
    {AIN_1N, ADC, 0},
    {AIN_2N, ADC, 0},
    {AIN_3N, ADC, 0},
    {AIN_4N, ADC, 0},
    {AIN_5N, ADC, 0},
    {AIN_0D, ADC, 1},
    {AIN_1D, ADC, 1},
    {AIN_2D, ADC, 1},
    {AIN_3D, ADC, 1},
    {AIN_4D, ADC, 1},
    {AIN_5D, ADC, 1},
    {NC,     NC,  0}
};

/************DAC***************/
const PinMap PinMap_DAC[] = {
    {AOUT_AO, DAC0, 0},
    {AOUT_BO, DAC1, 0},
    {AOUT_CO, DAC2, 0},
    {AOUT_DO, DAC3, 0},
    {NC,      NC,   0}
};
