/* Copyright 2026 NUTWANG
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

#pragma once
/*qmk compile -kb sk32/ld7_oled -km default*/

/* LD7_OLED: 7 keys wired one GPIO per key, plus a 128x32 SSD1306 OLED and a
 * 7 LED WS2812 strip on the SK32F077.
 *
 * KEY1..KEY7 = PB12 PB11 PB10 PB2 PB1 PB0 PC5
 * The direct pin matrix (DIRECT_PINS / MATRIX_ROWS / MATRIX_COLS) is generated
 * from keyboard.json ("matrix_pins.direct" + "matrix_size"), column 0..6 in
 * the order above.
 */

/* Per-key eager debounce: KEY1..KEY7 are one-GPIO-per-key (DIRECT_PINS), so a
 * press is reported immediately and only the re-trigger guard uses the delay.
 * sym_eager_pk gives the shortest press latency for this wiring. */
#define DEBOUNCE_TYPE sym_eager_pk
#define DEBOUNCE 1

/*BOOTMAGIC KEY (KEY1)*/
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* SSD1306 128x32 OLED on I2C1: SDA = PA3, SCL = PA2 (alternate function 13).
 * The I2C lines have NO external pull-ups on the LD7, so the pads are
 * configured in AF13 mode WITH the internal pull-up resistor enabled
 * (PAL_SK32_PUPDR_PULLUP OR-ed into the PAL mode). */
#define I2C1_SCL_PIN A2
#define I2C1_SDA_PIN A3
#define I2C1_SCL_PAL_MODE (PAL_MODE_ALTERNATE(13) | PAL_SK32_PUPDR_PULLUP)
#define I2C1_SDA_PAL_MODE (PAL_MODE_ALTERNATE(13) | PAL_SK32_PUPDR_PULLUP)

/* Run the OLED I2C bus at fast mode (400 kHz) instead of the SK32 platform
 * default 100 kHz, to cut per-frame refresh latency.  Fast mode needs a fast
 * duty cycle (2/1); the SK32 I2C LLD enforces a non-STD duty above 100 kHz. */
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE  FAST_DUTY_CYCLE_2

/* The OLED is the default 128x32 (oled_driver.h falls back to it when no
 * OLED_DISPLAY_* size macro is defined) at address 0x3C on I2C1. */

/* USB suspend/wakeup: the controller enters the bus suspend state by itself
 * (POWER.ENSUS) and its PHY is left powered so it can still see the host
 * resume, while the SUSPEND/RESUME interrupts stay armed.  That is what
 * makes the keyboard wake the PC on a key press (remote wakeup) and resume
 * cleanly when the host wakes.  The PHY must NOT be held in the software
 * SUSMOD suspend state: in that state the controller can neither report a
 * bus resume nor drive the resume signalling, i.e. both directions break.
 * QMK still runs its suspend path (RGB_MATRIX_SLEEP turns the LEDs off) on
 * top of it. */

/* REAL CPU low power: while the bus is suspended, enter the Cortex-M0 STOP
 * (deep sleep) instead of the default wait_ms(17) busy loop.  The core halts
 * until the armed USB RESUME / an EXTI wakes it; on wakeup the low power
 * driver (hal_low_power_lld) rebuilds the PLL/HSI clocks torn down by STOP. */
#define SK32_HAL_USE_LOWPOWER TRUE

/* Render offload: the whole OLED draw + blocking SSD1306 I2C render runs in a
 * dedicated ChibiOS thread (see ld7_oled.c).  OLED_TASK_EXTERNAL_LOOP makes
 * oled_task() (drivers/oled) return immediately, so the main keyboard loop
 * never touches oled_buffer at all.  The buffer is then accessed by only the
 * thread (oled_set_cursor + oled_task_kb to redraw + oled_render_dirty to send
 * I2C), which closes the old/new tearing race that previously corrupted a block
 * while it was in flight on the bus.  OLED_UPDATE_INTERVAL paces the thread's
 * redraw cadence. */
#define OLED_TASK_EXTERNAL_LOOP
#define OLED_UPDATE_INTERVAL 100

/*RGB MATRIX*/
/* 7 LED WS2812 string driven by the SK32F077 SLED peripheral
 * (WS2812_DRIVER=sled).  The data pad is PC0 in alternate function 14, served
 * by the SLED2 channel registers (see platforms/chibios/drivers/ws2812_sled.c). */
#define WS2812_SLED_GROUP SLED2
#define SK32_SLED_USE_SLED2 TRUE
#define WS2812_SLED_PORT GPIOC
#define WS2812_SLED_PIN 0U
#define RGB_MATRIX_LED_COUNT 7

#define RGB_MATRIX_TIMEOUT 0 // number of milliseconds to wait until rgb automatically turns off
#define RGB_MATRIX_SLEEP    // turn off effects when suspended
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180 // limits maximum brightness of LEDs to 180 out of 255
#define RGB_MATRIX_DEFAULT_VAL 180        // Sets the default brightness value, if none has been set
#define RGB_MATRIX_DEFAULT_SPD 127        // Sets the default animation speed, if none has been set
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR // Sets the default mode, if none has been set

/*other rgb set*/
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)

/*RGB MATRIX EFFECTS ON*/
/* The enabled set must be a superset of what KB17 configures: QMK persists
 * rgb_matrix mode/enable in the shared EEPROM.  When a board that saved e.g.
 * RGB_MATRIX_DUAL_BEACON is re-flashed with a firmware that does NOT enable
 * that effect, the switch(effect) in rgb_task_render has no case for it ->
 * rendering stays false -> every LED stays off.  Keeping the KB17 effect set
 * (plus SOLID_REACTIVE_SIMPLE) guarantees any previously saved mode still
 * resolves to a renderable case. */
#define ENABLE_RGB_MATRIX_BREATHING              //Enables RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_ALL              //Enables RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT       //Enables RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN          //Enables RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON //Enables RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN           //Enables RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL      //Enables RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL         //Enables RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL           //Enables RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON            //Enables RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON         //Enables RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS      //Enables RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_HUE_BREATHING          //Enables RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_SPLASH                 //Enables RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE  //Enables RGB_MATRIX_SOLID_REACTIVE_SIMPLE
