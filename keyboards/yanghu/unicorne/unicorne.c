/* Copyright 2021 Yang Hu
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
#include "unicorne.h"


// Custom i2c init to enable internal pull up resistor for i2c.
void i2c_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_INPUT);
        palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_INPUT);

        chThdSleepMilliseconds(10);
        // Use internal pull up since we do not have pull up on i2c pins in v1 design.
        palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_ALTERNATE(I2C1_SCL_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);
        palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_ALTERNATE(I2C1_SDA_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);
    }
}

// LED matrix
// physical location
// 2      3   4       5
//
// 1                  6
//        0   7
#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = {{
    // Key Matrix to LED Index
    // Since we only have 8 LEDs, map the keys near them to the same LED.
    {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5},
    {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5},
    {1, 1, 1, 0, 0, 0, 7, 7, 7, 6, 6, 6},
    {NO_LED, NO_LED, NO_LED, 0, 0, 0, 7, 7, 7, NO_LED, NO_LED, NO_LED},
}, {// LED Index to Physical Position
  {94, 60},
  {18, 44},
  {8, 10},
  {94, 10},
  {130,10},
  {216, 10},
  {208, 44},
  {130, 60}
}, {// LED Index to Flag
  LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, 
  LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
}};
// clang-format on
#endif

#ifdef OLED_ENABLE
// OLED shared code
// The oled is vertical. Need to rotate 270 degrees.
__attribute__((weak)) oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

// Render layer status on OLED. To be re-implemented by keymaps since layers are
// defined there.
__attribute__((weak)) void oled_render_layer(void) { return; }

// Oneshot mods status
uint8_t osmods;

__attribute__((weak)) void oled_render_mods(void) {
    static const char PROGMEM ctrl[]     = {0xb6, 0xb7, 10, 0xd6, 0xd7, 10, 0x20, 0x20, 10, 0};
    static const char PROGMEM shift[]    = {0x87, 0x88, 0x89, 10, 0xa7, 0xa8, 0xa9, 10, 0xc7, 0xc8, 0xc9, 10, 0};
    static const char PROGMEM alt[]      = {0x84, 0x85, 0x86, 10, 0xa4, 0xa5, 0xa6, 10, 0xc4, 0xc5, 0xc6, 10, 0};
    static const char PROGMEM ctrl_alt[] = {0xb6, 0xb7, 0x84, 0x85, 0x86, 0xd6, 0xd7, 0xa4, 0xa5, 0xa6, 0x20, 0x20, 0xc4, 0xc5, 0xc6, 0};

    static const char PROGMEM ctrl_shift[] = {0xb6, 0xb7, 0x87, 0x88, 0x89, 0xd6, 0xd7, 0xa7, 0xa8, 0xa9, 0x20, 0x20, 0xc7, 0xc8, 0xc9, 0};
    static const char PROGMEM c_a_shift[]  = {0xb6, 0xb7, 0x84, 0x85, 0x86, 0xd6, 0xd7, 0xa4, 0xa5, 0xa6, 0x20, 0x20, 0xc4, 0xc5, 0xc6, 0x87, 0x88, 0x89, 10, 0xa7, 0xa8, 0xa9, 10, 0xc7, 0xc8, 0xc9, 10, 0};
    // Now check mod status and render.
    static uint8_t mods;
    mods = get_mods() | osmods;
    if ((mods & MOD_MASK_CTRL) && (mods & MOD_MASK_ALT) && (mods & MOD_MASK_SHIFT)) {
        oled_write_P(c_a_shift, false);
    } else if ((mods & MOD_MASK_CTRL) && (mods & MOD_MASK_ALT)) {
        oled_write_P(ctrl_alt, false);
    } else if ((mods & MOD_MASK_CTRL) && (mods & MOD_MASK_SHIFT)) {
        oled_write_P(ctrl_shift, false);
    } else if ((mods & MOD_MASK_SHIFT) && (mods & MOD_MASK_ALT)) {
        oled_write_P(alt, false);
        oled_write_P(shift, false);
    } else if (mods & MOD_MASK_CTRL) {
        oled_write_P(ctrl, false);
    } else if (mods & MOD_MASK_ALT) {
        oled_write_P(alt, false);
    } else if (mods & MOD_MASK_SHIFT) {
        oled_write_P(shift, false);
    } else {
        for (int i = 0; i < 6; ++i) {
            oled_write_ln(" ", false);
        }
    }
    return;
}

void oneshot_mods_changed_user(uint8_t mods) { osmods = mods; }

// Call this from "led_update_user" and use `led_state.caps_lock` to check
// the status of capslock.
__attribute__((weak)) void oled_render_capslock(bool caps_on) {
    static const char PROGMEM capslock_logo[] = {0x9c, 0x9d, 0x9e, 0x9f, 10, 0xbc, 0xbd, 0xbe, 0xbf, 10, 0xdc, 0xdd, 0xde, 0xdf, 10, 0};
    if (caps_on) {
        oled_write_P(capslock_logo, false);
    } else {
        for (int i = 0; i < 3; ++i) {
            oled_write_ln(" ", false);
        }
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }
}

__attribute__((weak)) void oled_render_keylog(void) { oled_write(keylog_str, false); }

// Keymaps can override this function
__attribute__((weak)) void oled_task_user(void) {
    /* oled_render_keylog(); */
    oled_render_layer();
    oled_render_mods();
    led_t led_state = host_keyboard_led_state();
    oled_render_capslock(led_state.caps_lock);
}
#endif
