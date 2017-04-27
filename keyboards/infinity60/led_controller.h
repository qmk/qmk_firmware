/*
Copyright 2016 flabbergast <s3+flabbergast@sdfeu.org>

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

#ifndef _LED_CONTROLLER_H_
#define _LED_CONTROLLER_H_

/* =========================
 *  communication functions
 * ========================= */

msg_t is31_write_data(uint8_t page, uint8_t *buffer, uint8_t size);
msg_t is31_write_register(uint8_t page, uint8_t reg, uint8_t data);
msg_t is31_read_register(uint8_t page, uint8_t reg, uint8_t *result);

/* ============================
 *  init functions/definitions
 * ============================*/

void led_controller_init(void);

#define CAPS_LOCK_LED_ADDRESS 46 //pin matrix location
#define NUM_LOCK_LED_ADDRESS 85
#define BACKLIGHT_OFF_LOCK_LED_OFF 0 //set to 0 to show lock leds even if backlight off

/* =============================
 * IS31 chip related definitions
 * ============================= */

#define IS31_ADDR_DEFAULT 0x74

#define IS31_REG_CONFIG  0x00
// bits in reg
#define IS31_REG_CONFIG_PICTUREMODE 0x00
#define IS31_REG_CONFIG_AUTOPLAYMODE 0x08
#define IS31_REG_CONFIG_AUDIOPLAYMODE 0x18
// D2:D0 bits are starting frame for autoplay mode

#define IS31_REG_PICTDISP 0x01 // D2:D0 frame select for picture mode

#define IS31_REG_AUTOPLAYCTRL1 0x02
// D6:D4 number of loops (000=infty)
// D2:D0 number of frames to be used

#define IS31_REG_AUTOPLAYCTRL2 0x03 // D5:D0 delay time (*11ms)

#define IS31_REG_DISPLAYOPT 0x05
#define IS31_REG_DISPLAYOPT_INTENSITY_SAME 0x20 // same intensity for all frames
#define IS31_REG_DISPLAYOPT_BLINK_ENABLE 0x8
// D2:D0 bits blink period time (*0.27s)

#define IS31_REG_AUDIOSYNC 0x06
#define IS31_REG_AUDIOSYNC_ENABLE 0x1

#define IS31_REG_FRAMESTATE 0x07

#define IS31_REG_BREATHCTRL1 0x08
// D6:D4 fade out time (26ms*2^i)
// D2:D0 fade in time (26ms*2^i)

#define IS31_REG_BREATHCTRL2 0x09
#define IS31_REG_BREATHCTRL2_ENABLE 0x10
// D2:D0 extinguish time (3.5ms*2^i)

#define IS31_REG_SHUTDOWN 0x0A
#define IS31_REG_SHUTDOWN_ON 0x1

#define IS31_REG_AGCCTRL 0x0B
#define IS31_REG_ADCRATE 0x0C

#define IS31_COMMANDREGISTER 0xFD
#define IS31_FUNCTIONREG 0x0B    // helpfully called 'page nine'

#define IS31_TIMEOUT 10000 // needs to be long enough to write a whole page

/* ========================================
 * LED Thread related functions/definitions
 * ========================================*/

extern mailbox_t led_mailbox;

void set_led_bit (uint8_t page, uint8_t *led_control_reg, uint8_t led_addr, uint8_t action);
void set_lock_leds (uint8_t lock_type, uint8_t led_on);
void write_led_page (uint8_t page, uint8_t *led_array, uint8_t led_count);

// constants for signaling the LED controller thread
enum led_msg_t {
    KEY_LIGHT,
    OFF_LED,
    ON_LED,
    TOGGLE_LED,
    TOGGLE_ALL,
    TOGGLE_BACKLIGHT,
    DISPLAY_PAGE,
    RESET_PAGE,
    TOGGLE_NUM_LOCK,
    TOGGLE_CAPS_LOCK,
    MODE_BREATH,
    STEP_BRIGHTNESS
};

#endif /* _LED_CONTROLLER_H_ */
