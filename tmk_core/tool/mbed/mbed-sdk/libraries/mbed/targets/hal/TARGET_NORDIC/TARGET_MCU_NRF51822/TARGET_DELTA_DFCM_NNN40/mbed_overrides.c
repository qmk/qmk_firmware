/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "cmsis.h"


#define SPIM1_SCK_PIN       11u     /**< SPI clock GPIO pin number. */
#define SPIM1_MOSI_PIN      15u     /**< SPI Master Out Slave In GPIO pin number. */
#define SPIM1_MISO_PIN      9u     /**< SPI Master In Slave Out GPIO pin number. */
#define SPIM1_SS_PIN        28u     /**< SPI Slave Select GPIO pin number. */

#define CMD_POWER_UP (0xAB)
#define CMD_POWER_DOWN (0xB9)

void spi_flash_init(void)
{   
	NRF_GPIO->PIN_CNF[SPIM1_MOSI_PIN] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
									| (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
    NRF_GPIO->PIN_CNF[SPIM1_MISO_PIN] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                    | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
    NRF_GPIO->PIN_CNF[SPIM1_SCK_PIN] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                    | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
									
    NRF_GPIO->PIN_CNF[SPIM1_SS_PIN] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                        | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                        | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                        | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                        | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
	//cs = 1;									
	NRF_GPIO->OUTSET 		= 	(GPIO_OUTSET_PIN28_High << GPIO_OUTSET_PIN28_Pos);
	
	NRF_SPI1->ENABLE = 1;
	NRF_SPI1->PSELSCK = SPIM1_SCK_PIN;
	NRF_SPI1->PSELMOSI = SPIM1_MISO_PIN;
	NRF_SPI1->PSELMISO = SPIM1_MOSI_PIN;
	//spi.frequency(1000000);
	NRF_SPI1->FREQUENCY = 0x10000000; //1MHz     
	 
    //spi.format(8,0);
	uint32_t config_mode = 0;
	config_mode = (SPI_CONFIG_CPHA_Leading << SPI_CONFIG_CPHA_Pos) | (SPI_CONFIG_CPOL_ActiveHigh << SPI_CONFIG_CPOL_Pos); //mode 0
	NRF_SPI1->CONFIG = (config_mode | (SPI_CONFIG_ORDER_MsbFirst << SPI_CONFIG_ORDER_Pos));
    //cs = 0;
	NRF_GPIO->OUTCLR 		= 	(GPIO_OUTCLR_PIN28_Clear << GPIO_OUTCLR_PIN28_Pos);
    //spi.write(CMD_POWER_UP);
		 while (!NRF_SPI1->EVENTS_READY == 0) {
    }
	NRF_SPI1->TXD = (uint32_t)CMD_POWER_UP;
	while (!NRF_SPI1->EVENTS_READY == 1) {
    }
	NRF_SPI1->EVENTS_READY = 0;
    NRF_SPI1->RXD;
    //wait_ms(30);    
    // Deselect the device
    //cs = 1;
	NRF_GPIO->OUTSET 		= 	(GPIO_OUTSET_PIN28_High << GPIO_OUTSET_PIN28_Pos);

}

void spi_flash_powerDown(void)
{
    NRF_GPIO->OUTCLR 		= 	(GPIO_OUTCLR_PIN28_Clear << GPIO_OUTCLR_PIN28_Pos);
    //spi.write(CMD_POWER_DOWN);
	 while (!NRF_SPI1->EVENTS_READY == 0) {
    }
	NRF_SPI1->TXD = (uint32_t)CMD_POWER_DOWN;
	while (!NRF_SPI1->EVENTS_READY == 1) {
    }
	NRF_SPI1->EVENTS_READY = 0;
    NRF_SPI1->RXD;
    NRF_GPIO->OUTSET 		= 	(GPIO_OUTSET_PIN28_High << GPIO_OUTSET_PIN28_Pos);
        
    //wait for sleep
    //wait_us(3);
}

void mbed_sdk_init()
{
	// Default SWIO setting, pull SWIO(p19) to low for turning antenna switch to BLE radiated path
	NRF_GPIO->PIN_CNF[19] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                        | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                        | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                        | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                                        | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);

	NRF_GPIO->OUTCLR 		= 	(GPIO_OUTCLR_PIN19_Clear << GPIO_OUTCLR_PIN19_Pos);
	
	// Config External Crystal to 32MHz
	NRF_CLOCK->XTALFREQ = 0x00;
	NRF_CLOCK->EVENTS_HFCLKSTARTED  = 0;
    NRF_CLOCK->TASKS_HFCLKSTART     = 1;
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0) 
    {// Do nothing.
    }
	
	spi_flash_init();
	
	//nrf_delay_ms(10);
	spi_flash_powerDown();
	
}
