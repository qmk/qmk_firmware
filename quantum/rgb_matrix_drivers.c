/* Copyright 2018 James Laird-Wah
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

#include "rgb_matrix.h"

/* Each driver needs to define the struct
 *    const rgb_matrix_driver_t rgb_matrix_driver;
 * All members must be provided.
 * Keyboard custom drivers can define this in their own files, it should only
 * be here if shared between boards.
 */

#if defined(IS31FL3731) || defined(IS31FL3733) || defined(IS31FL3737)

#include "i2c_master.h"

static void init( void )
{
    i2c_init();
#ifdef IS31FL3731
    IS31FL3731_init( DRIVER_ADDR_1 );
    IS31FL3731_init( DRIVER_ADDR_2 );
#elif defined(IS31FL3733)
    IS31FL3733_init( DRIVER_ADDR_1, 0 );
#else
    IS31FL3737_init( DRIVER_ADDR_1 );
#endif
    for ( int index = 0; index < DRIVER_LED_TOTAL; index++ ) {
        bool enabled = true;
        // This only caches it for later
#ifdef IS31FL3731
        IS31FL3731_set_led_control_register( index, enabled, enabled, enabled );
#elif defined(IS31FL3733)
        IS31FL3733_set_led_control_register( index, enabled, enabled, enabled );
#else
        IS31FL3737_set_led_control_register( index, enabled, enabled, enabled );
#endif
    }
    // This actually updates the LED drivers
#ifdef IS31FL3731
    IS31FL3731_update_led_control_registers( DRIVER_ADDR_1, DRIVER_ADDR_2 );
#elif defined(IS31FL3733)
    IS31FL3733_update_led_control_registers( DRIVER_ADDR_1, 0 );
    IS31FL3733_update_led_control_registers( DRIVER_ADDR_2, 1 );
#else
    IS31FL3737_update_led_control_registers( DRIVER_ADDR_1, DRIVER_ADDR_2 );
#endif
}

#ifdef IS31FL3731
static void flush( void )
{
    IS31FL3731_update_pwm_buffers( DRIVER_ADDR_1, DRIVER_ADDR_2 );
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL3731_set_color,
    .set_color_all = IS31FL3731_set_color_all,
};
#elif defined(IS31FL3733)
static void flush( void )
{
    IS31FL3733_update_pwm_buffers( DRIVER_ADDR_1, 0);
    IS31FL3733_update_pwm_buffers( DRIVER_ADDR_2, 1);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL3733_set_color,
    .set_color_all = IS31FL3733_set_color_all,
};
#else
static void flush( void )
{
    IS31FL3737_update_pwm_buffers( DRIVER_ADDR_1, DRIVER_ADDR_2 );
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL3737_set_color,
    .set_color_all = IS31FL3737_set_color_all,
};
#endif

#elif defined(WS2812)

extern LED_TYPE led[DRIVER_LED_TOTAL];

  static void flush( void )
  {
    // Assumes use of RGB_DI_PIN
    ws2812_setleds(led, DRIVER_LED_TOTAL);
  }

  static void init( void )
  {

  }

  const rgb_matrix_driver_t rgb_matrix_driver = {
      .init = init,
      .flush = flush,
      .set_color = ws2812_setled,
      .set_color_all = ws2812_setled_all,
  };
#endif
