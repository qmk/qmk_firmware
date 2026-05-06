/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "tractyl_manuform.h"

#ifdef USB_VBUS_PIN
bool usb_vbus_state(void) {
    gpio_set_pin_input_low(USB_VBUS_PIN);
    wait_us(5);
    return gpio_read_pin(USB_VBUS_PIN);
}
#endif

#ifdef USER_BUTTON_PIN
void user_button_init(void) {
    // Pin needs to be configured as input low
    gpio_set_pin_input_low(USER_BUTTON_PIN);
}

bool check_user_button_state(void) {
    return gpio_read_pin(USER_BUTTON_PIN);
}
#endif // USER_BUTTON_PIN

void board_init(void) {
    // Board setup sets these pins as SPI, but we aren't using them as such.
    // So to prevent them from misbehaving, we need to set them to a different, non-spi mode.
    // This is a bit of a hack, but nothing else runs soon enough, without re-implementing spi_init().
    gpio_set_pin_input(A5);
    gpio_set_pin_input(A6);
    gpio_set_pin_input(A7);

    // If using USB_OTG_HS, we need to set the data pins since they're set wrong for our needs by default.
    // We set it here by default, in case it's bridged with A11/A12, as to reduce the chance of issues.
    palSetLineMode(
        B14, PAL_MODE_ALTERNATE(12) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING);
    palSetLineMode(
        B15, PAL_MODE_ALTERNATE(12) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING);
}
