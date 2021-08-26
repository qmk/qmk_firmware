/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#ifndef MD_BOOTLOADER

#    include "samd51j18a.h"
#    include "issi3733_driver.h"
#    include "config.h"

extern __attribute__((__aligned__(16))) DmacDescriptor dmac_desc;
extern __attribute__((__aligned__(16))) DmacDescriptor dmac_desc_wb;

uint8_t I2C3733_Init_Control(void);
uint8_t I2C3733_Init_Drivers(void);
void    I2C3733_Control_Set(uint8_t state);
void    I2C_DMAC_LED_Init(void);

#    define I2C_Q_SIZE 100

#    define I2C_Q_NA 100
#    define I2C_Q_CRWL 101
#    define I2C_Q_PAGE_SELECT 102
#    define I2C_Q_PWM 103
#    define I2C_Q_GCR 104
#    define I2C_Q_ONOFF 105

#    define I2C_DMA_MAX_SEND 255

extern volatile uint8_t i2c_led_q_running;

#    define I2C_LED_Q_PWM(a)                      \
        {                                         \
            if (i2c_led_q_request_room(7)) {      \
                i2c_led_q_add(I2C_Q_CRWL);        \
                i2c_led_q_add(a);                 \
                i2c_led_q_add(I2C_Q_PAGE_SELECT); \
                i2c_led_q_add(a);                 \
                i2c_led_q_add(ISSI3733_PG_PWM);   \
                i2c_led_q_add(I2C_Q_PWM);         \
                i2c_led_q_add(a);                 \
            }                                     \
        }

#    define I2C_LED_Q_GCR(a)                      \
        {                                         \
            if (i2c_led_q_request_room(7)) {      \
                i2c_led_q_add(I2C_Q_CRWL);        \
                i2c_led_q_add(a);                 \
                i2c_led_q_add(I2C_Q_PAGE_SELECT); \
                i2c_led_q_add(a);                 \
                i2c_led_q_add(ISSI3733_PG_FN);    \
                i2c_led_q_add(I2C_Q_GCR);         \
                i2c_led_q_add(a);                 \
            }                                     \
        }

#    define I2C_LED_Q_ONOFF(a)                    \
        {                                         \
            if (i2c_led_q_request_room(7)) {      \
                i2c_led_q_add(I2C_Q_CRWL);        \
                i2c_led_q_add(a);                 \
                i2c_led_q_add(I2C_Q_PAGE_SELECT); \
                i2c_led_q_add(a);                 \
                i2c_led_q_add(ISSI3733_PG_ONOFF); \
                i2c_led_q_add(I2C_Q_ONOFF);       \
                i2c_led_q_add(a);                 \
            }                                     \
        }

void    i2c_led_q_init(void);
void    i2c_led_q_add(uint8_t cmd);
void    i2c_led_q_s_advance(void);
uint8_t i2c_led_q_size(void);
uint8_t i2c_led_q_request_room(uint8_t request_size);
uint8_t i2c_led_q_run(void);

void    i2c1_init(void);
uint8_t i2c1_transmit(uint8_t address, uint8_t *data, uint16_t length, uint16_t timeout);
void    i2c1_stop(void);

#endif  // MD_BOOTLOADER

void    i2c0_init(void);
uint8_t i2c0_transmit(uint8_t address, uint8_t *data, uint16_t length, uint16_t timeout);
void    i2c0_stop(void);

#endif  // _I2C_MASTER_H_
