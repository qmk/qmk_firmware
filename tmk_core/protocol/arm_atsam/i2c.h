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

#ifndef _I2C_H_
#define _I2C_H_

#include "issi3733_driver.h"
#include "config.h"

__attribute__((__aligned__(16)))
DmacDescriptor dmac_desc;
__attribute__((__aligned__(16)))
DmacDescriptor dmac_desc_wb;

void I2C0_init(void);
uint32_t I2C0_write(int ic_addr, unsigned char * buf, uint32_t count);
void I2C1_init(void);
uint32_t I2C1_write(int ic_addr, unsigned char * buf, uint32_t count);

uint8_t I2C3733_Init_Control(void);
uint8_t I2C3733_Init_Drivers(void);

#define I2C_Q_SIZE              100

#define I2C_Q_NA                100
#define I2C_Q_CRWL              101
#define I2C_Q_PAGE_SELECT       102
#define I2C_Q_PWM               103
#define I2C_Q_GCR               104
#define I2C_Q_ONOFF             105

#define I2C_DMA_MAX_SEND        255

extern volatile uint8_t i2c_led_q_running;

#define I2C_LED_Q_PWM(a)    { \
                                if (i2c_led_q_request_room(7)) \
                                { \
                                    i2c_led_q_add(I2C_Q_CRWL); \
                                    i2c_led_q_add(a); \
                                    i2c_led_q_add(I2C_Q_PAGE_SELECT); \
                                    i2c_led_q_add(a); \
                                    i2c_led_q_add(ISSI3733_PG_PWM); \
                                    i2c_led_q_add(I2C_Q_PWM); \
                                    i2c_led_q_add(a); \
                                } \
                            }

#define I2C_LED_Q_GCR(a)    { \
                                if (i2c_led_q_request_room(7)) \
                                { \
                                    i2c_led_q_add(I2C_Q_CRWL); \
                                    i2c_led_q_add(a); \
                                    i2c_led_q_add(I2C_Q_PAGE_SELECT); \
                                    i2c_led_q_add(a); \
                                    i2c_led_q_add(ISSI3733_PG_FN); \
                                    i2c_led_q_add(I2C_Q_GCR); \
                                    i2c_led_q_add(a); \
                                } \
                            }

#define I2C_LED_Q_ONOFF(a)  { \
                                if (i2c_led_q_request_room(7)) \
                                { \
                                    i2c_led_q_add(I2C_Q_CRWL); \
                                    i2c_led_q_add(a); \
                                    i2c_led_q_add(I2C_Q_PAGE_SELECT); \
                                    i2c_led_q_add(a); \
                                    i2c_led_q_add(ISSI3733_PG_ONOFF); \
                                    i2c_led_q_add(I2C_Q_ONOFF); \
                                    i2c_led_q_add(a); \
                                } \
                            }

void I2C_DMAC_LED_Init(void);
void i2c_led_desc_defaults(void);
void dma_prepare_send(uint8_t *data, uint8_t len);
void i2c_led_begin(uint8_t drvid);
void i2c_led_send_CRWL_dma(uint8_t drvid);
void i2c_led_select_page_dma(uint8_t drvid, uint8_t pageno);
void i2c_led_send_GCR_dma(uint8_t drvid);
void i2c_led_send_pwm_dma(uint8_t drvid);
void i2c_led_send_onoff_dma(uint8_t drvid);
void i2c_led_q_init(void);
void i2c_led_q_add(uint8_t cmd);
void i2c_led_q_s_advance(void);
uint8_t i2c_led_q_size(void);
uint8_t i2c_led_q_request_room(uint8_t request_size);
uint8_t i2c_led_q_run(void);
void I2C3733_Control_Set(uint8_t state);

void  i2c_led_send_onoff(uint8_t drvid);

void sc1stop(void);

#endif // _I2C_H_

