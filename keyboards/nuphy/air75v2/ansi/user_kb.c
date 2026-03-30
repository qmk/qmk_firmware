/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "user_kb.h"
#include <stdbool.h>
#include <stdint.h>
#include "ansi.h"
#include "config.h"
#include "eeconfig.h"
#include "color.h"
#include "host.h"
#include "common/config.h"
#include "common/rf_driver.h"
#include "common/links.h"

/**
 * @brief gpio initial.
 */
void gpio_init(void) {
    /* power on all LEDs */
    pwr_rgb_led_on();
    pwr_side_led_on();

    /* set side led pin output low */
    setPinOutput(DRIVER_SIDE_DI_PIN);
    writePinLow(DRIVER_SIDE_DI_PIN);

#if (WORK_MODE == THREE_MODE)
    /* config RF module pin */
    setPinOutput(NRF_WAKEUP_PIN);
    writePinHigh(NRF_WAKEUP_PIN);

    setPinInputHigh(NRF_TEST_PIN);

    /* reset RF module */
    setPinOutput(NRF_RESET_PIN);
    writePinLow(NRF_RESET_PIN);
    wait_ms(50);
    writePinHigh(NRF_RESET_PIN);

    /* connection mode switch pin */
    setPinInputHigh(DEVICE_MODE_PIN);
#endif
}