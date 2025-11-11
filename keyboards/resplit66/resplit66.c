/* Copyright 2025 David Girault
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

#include "board.h"
#include "hal.h"
#include "quantum.h"
#include "split_util.h"

/* V1 board has wrap to PH1 GPIO pin to select right side, but need pulldow because on
 * left side, the pin is floating. So activate pulldown while reading and deactivate it
 * afterward to avoid current leakage.
 */
static bool isRightSide(void)
{
  bool right;
  // Activate pulldown for unconnected side.
  palSetLineMode(LINE_SIDE_SEL, PAL_MODE_INPUT_PULLDOWN);
  chSysPolledDelayX(20);
  // Read the LINE_SIDE_SEL pin.
  right = palReadLine(LINE_SIDE_SEL);
  // Now remove pulldown to avoid current leakage.
  palSetLineMode(LINE_SIDE_SEL, PAL_MODE_INPUT);
  return right;
}

bool is_keyboard_left_impl(void) {
  return !isRightSide();
}

/* Nothing to do as GPIOs/AF are already configured __early_init() in board.c. */
void i2c_init(void) {}
void spi_init(void) {}
void matrix_init_pins(void) {}
void led_init_ports(void) {}

/* There is three leds per-side. */
void led_update_ports(led_t led_state)
{
  if (isLeftHand) {
    if (led_state.compose)
      palSetLine(LINE_LED1);
    else
      palClearLine(LINE_LED1);
  } else {
    if (led_state.caps_lock)
      palSetLine(LINE_LED3);
    else
      palClearLine(LINE_LED3);

    if (led_state.scroll_lock)
      palSetLine(LINE_LED2);
    else
      palClearLine(LINE_LED2);

    if (led_state.num_lock)
      palSetLine(LINE_LED1);
    else
      palClearLine(LINE_LED1);
  }
}
