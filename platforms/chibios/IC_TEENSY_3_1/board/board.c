/*
    ChibiOS - Copyright (C) 2015 RedoX https://github.com/RedoXyde

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#include "hal.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)
/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config = {
    .ports =
        {
            {
                /*
                 * PORTA setup.
                 *
                 * PTA4  - PIN33
                 * PTA5  - PIN24
                 * PTA12 - PIN3
                 * PTA13 - PIN4
                 *
                 * PTA18/19 crystal
                 * PTA0/3 SWD
                 */
                .port = IOPORT1,
                .pads =
                    {
                        PAL_MODE_ALTERNATIVE_7, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_ALTERNATIVE_7, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_INPUT_ANALOG, PAL_MODE_INPUT_ANALOG, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED,
                    },
            },
            {
                /*
                 * PORTB setup.
                 *
                 * PTB0  - PIN16
                 * PTB1  - PIN17
                 * PTB2  - PIN19
                 * PTB3  - PIN18
                 * PTB16 - PIN0 - UART0_TX
                 * PTB17 - PIN1 - UART0_RX
                 * PTB18 - PIN32
                 * PTB19 - PIN25
                 */
                .port = IOPORT2,
                .pads =
                    {
                        PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_ALTERNATIVE_3, PAL_MODE_ALTERNATIVE_3, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED,
                    },
            },
            {
                /*
                 * PORTC setup.
                 *
                 * PTC0  - PIN15
                 * PTC1  - PIN22
                 * PTC2  - PIN23
                 * PTC3  - PIN9
                 * PTC4  - PIN10
                 * PTC5  - PIN13
                 * PTC6  - PIN11
                 * PTC7  - PIN12
                 * PTC8  - PIN28
                 * PTC9  - PIN27
                 * PTC10 - PIN29
                 * PTC11 - PIN30
                 */
                .port = IOPORT3,
                .pads =
                    {
                        PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED,
                    },
            },
            {
                /*
                 * PORTD setup.
                 *
                 * PTD0  - PIN2
                 * PTD1  - PIN14
                 * PTD2  - PIN7
                 * PTD3  - PIN8
                 * PTD4  - PIN6
                 * PTD5  - PIN20
                 * PTD6  - PIN21
                 * PTD7  - PIN5
                 */
                .port = IOPORT4,
                .pads =
                    {
                        PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED,
                    },
            },
            {
                /*
                 * PORTE setup.
                 *
                 * PTE0  - PIN31
                 * PTE1  - PIN26
                 */
                .port = IOPORT5,
                .pads =
                    {
                        PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_OUTPUT_PUSHPULL, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED, PAL_MODE_UNCONNECTED,
                    },
            },
        },
};
#endif

// NOTE: This value comes from kiibohd/controller and is the location of a value
// which needs to be checked before disabling the watchdog (which happens in
// k20x_clock_init)
#define WDOG_TMROUTL *(volatile uint16_t *)0x40052012

/**
 * @brief   Early initialization code.
 * @details This initialization must be performed just after stack setup
 *          and before any other initialization.
 */
void __early_init(void) {
    // This is a dirty hack and should only be used as a temporary fix until this
    // is upstreamed.
    while (WDOG_TMROUTL < 2)
        ;  // Must wait for WDOG timer if already running, before jumping

    k20x_clock_init();
}

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {}
