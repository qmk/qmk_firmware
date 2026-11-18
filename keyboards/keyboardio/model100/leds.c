/* Copyright 2018 James Laird-Wah
 * Copyright 2025 QMK
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

#include "leds.h"
#include "rgb_matrix.h"
#include <string.h>
#include "model100.h"

/* LED writes go over the SAME I2C1 bus as the key scanners. QMK's ChibiOS DMA
 * i2c_transmit does not work on the GD32F303 and mixing it with the polled key
 * reads corrupts the bus, so use the shared polled i2c_poll_write (matrix.c). */

void set_all_leds_to(uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ALL_TO,
    b, g, r
  };
  i2c_poll_write(I2C_ADDR(LEFT), buf, sizeof(buf));
  i2c_poll_write(I2C_ADDR(RIGHT), buf, sizeof(buf));
}

void set_led_to(int led, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ONE_TO,
    led & 0x1f,
    b, g, r
  };
  int hand = (led >= 32) ? RIGHT : LEFT;
  i2c_poll_write(I2C_ADDR(hand), buf, sizeof(buf));
}

#ifdef RGB_MATRIX_ENABLE

static struct {
  uint8_t b;
  uint8_t g;
  uint8_t r;
} __attribute__((packed)) led_state[64];

static void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
  /* No gamma here: with USE_CIE1931_CURVE the CIE curve is already applied to
   * the value in hsv_to_rgb (quantum/color.c) before rgb_matrix hands us these
   * channels. Correcting again crushed the mids (over-contrast, e.g. digital
   * rain trails dropping to black too fast). Match the Model 01 driver. */
  led_state[index].r = r;
  led_state[index].g = g;
  led_state[index].b = b;
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
  for (int i=0; i<RGB_MATRIX_LED_COUNT; i++)
    set_color(i, r, g, b);
}

static void init(void) {
  /* The Model 100 gates power to the two 5V scanner/LED nets via B9, which is
   * enabled in matrix_init(). Unlike the Model 01 there is no separate
   * high-current LED enable line to drive here. B14/B15 are power-sense inputs. */
  gpio_set_pin_input(B14);
  gpio_set_pin_input(B15);
}

/* Each hand's 32 LEDs are sent as 4 banks of 8 LEDs (8 * 3 = 24 bytes). We
 * interleave the two hands bank-by-bank (L0, R0, L1, R1, ...) rather than
 * sending all of one hand then the other: back-to-back writes to the same
 * ATtiny outrun it (it is still committing the previous bank to memory) and
 * later banks get dropped. Interleaving gives each scanner time between its
 * bank writes. (Kaleidoscope documents this exact race.) led_state[0..31] is
 * the left hand, [32..63] the right. */
#define LEDS_PER_HAND   32
#define LED_BANKS       4
#define LEDS_PER_BANK   (LEDS_PER_HAND / LED_BANKS)   /* 8 */

static void flush(void) {
  uint8_t command[1 + LEDS_PER_BANK * 3];
  for (int bank = 0; bank < LED_BANKS; bank++) {
    command[0] = TWI_CMD_LED_BASE + bank;
    for (int hand = 0; hand < 2; hand++) {
      int first = hand * LEDS_PER_HAND + bank * LEDS_PER_BANK;
      memcpy(&command[1], &led_state[first], LEDS_PER_BANK * 3);
      i2c_poll_write(I2C_ADDR(hand), command, sizeof(command));
    }
  }
}

const rgb_matrix_driver_t rgb_matrix_driver = {
  .init = init,
  .flush = flush,
  .set_color = set_color,
  .set_color_all = set_color_all
};

#endif

/* vim: set ts=2 sw=2 et: */
