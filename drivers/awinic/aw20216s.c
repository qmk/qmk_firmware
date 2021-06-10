/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "spi_master.h"
#include "aw20216s.h"
#include <ch.h>
#include <hal.h>


#define COMMAND_CHIP_ID             0xA0
#define US_POR_DELAY                5000    //Min is 2000 us
#define US_ENABLE_DELAY              500    //Min is  100 us
#define PAGE_0                      0    
#define PAGE_1                      1    
#define PAGE_2                      2    
#define PAGE_3                      3    
#define PAGE_0_REG_GCR              0x00
#define REG_GCR_BIT_CHIPEN_MASK     0x01
#define PAGE_0_REG_GCCR             0x01
#define US_BETWEEN_REG_WRITE_DELAY  100
#define PWM_REGISTER_COUNT          216

#define SPI_CLOCK_SPEED             2000000
#define SPI_MODE                    3
//#define SPI_DIVISOR               (F_CPU / SPI_CLOCK_SPEED)
#define SPI_DIVISOR                 4   //around 8 MHz (smooth transitions)

// These buffers match the AW20216S PWM registers 0x00-0xD7.
uint8_t g_pwm_buffer[DRIVER_COUNT][PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

void AW20216S_spi_start( int32_t csPin ){
    spi_start(csPin, false, SPI_MODE, SPI_DIVISOR);
}

void AW20216S_write_register(   int32_t csPin, 
                                uint8_t page, 
                                uint8_t reg, 
                                uint8_t data) {
    uint8_t cmd =   COMMAND_CHIP_ID | ( (page & 0x07) << 1);

    AW20216S_spi_start(csPin);
    spi_write(cmd);
    spi_write(reg);
    spi_write(data);
    spi_stop();
}

void AW20216S_write_pwm_buffer( int32_t   csPin, 
                                uint8_t *pwm_buffer) {
    
    uint8_t cmd =   COMMAND_CHIP_ID | (PAGE_1 << 1);

    AW20216S_spi_start(csPin);
    spi_write(cmd);
    spi_write(0);
    
    for (int i = 0; i < PWM_REGISTER_COUNT; i ++) {
        spi_write( pwm_buffer[i] );
    }

    spi_stop();
}

void AW20216S_enable(   int32_t csPin,
                        int32_t enablePin ) {
                            
    //Configure chip select pin as output and set high level.
    palSetLineMode(csPin, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(csPin);
    
    //Delay for POR to complete
    wait_us(US_POR_DELAY);
    
    //Configure enable pin as output and set high level.
    palSetLineMode(enablePin, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(enablePin);
    
    //Delay for enable to complete
    wait_us(US_ENABLE_DELAY);
}

void AW20216S_init( int32_t csPin, 
                    uint8_t swLinesEnabled ) {

    //Enable SW lines and chip
    uint8_t valueGCR    =   (swLinesEnabled << 4) | REG_GCR_BIT_CHIPEN_MASK;
    AW20216S_write_register(csPin, PAGE_0, PAGE_0_REG_GCR, valueGCR);
    
    wait_us(US_BETWEEN_REG_WRITE_DELAY);
    
    //Maximum sink current
    uint8_t valueGCCR   =   RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    AW20216S_write_register(csPin, PAGE_0, PAGE_0_REG_GCCR, valueGCCR);
    
    wait_us(US_BETWEEN_REG_WRITE_DELAY);

    //Set Constant Current for LEDs (Registers SL)
    for (uint8_t i = 0; i < PWM_REGISTER_COUNT; i++) {
        AW20216S_write_register(csPin, PAGE_2, i, 0xFF);
        wait_us(US_BETWEEN_REG_WRITE_DELAY);
    }

    //Turn off all LEDs (Registers PWM)
    for (uint8_t i = 0; i < PWM_REGISTER_COUNT; i++) {
        AW20216S_write_register(csPin, PAGE_1, i, 0x00);
        wait_us(US_BETWEEN_REG_WRITE_DELAY);
    }
}

void AW20216S_set_color(int     indexLED, 
                        uint8_t red, 
                        uint8_t green, 
                        uint8_t blue) {
    if (indexLED >= 0 && indexLED < DRIVER_LED_TOTAL) {
        aw_led led                                  =   g_aw_leds[indexLED];

        g_pwm_buffer[led.driver][led.r]             =   red;
        g_pwm_buffer[led.driver][led.g]             =   green;
        g_pwm_buffer[led.driver][led.b]             =   blue;
        g_pwm_buffer_update_required[led.driver]    =   true;
    }
}

void AW20216S_set_color_all(uint8_t red, 
                            uint8_t green, 
                            uint8_t blue) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        AW20216S_set_color(i, red, green, blue);
    }
}

void AW20216S_update_pwm_buffers(   int32_t csPin, 
                                    uint8_t driver) {
    if (g_pwm_buffer_update_required[driver]) {
        AW20216S_write_pwm_buffer(csPin, g_pwm_buffer[driver]);
    }
    g_pwm_buffer_update_required[driver] = false;
}
