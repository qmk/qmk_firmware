/* Copyright 2018 Jumail Mundekkat / MxBlue
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
 
#include QMK_KEYBOARD_H
#include "tmk_core/common/eeprom.h"
#include "tmk_core/common/action_layer.h"
#include "rgblight.h"

// Variables for controlling front LED application
uint8_t fled_mode;  // Mode for front LEDs
uint8_t fled_val;   // Brightness for front leds (0 - 255)
LED_TYPE fleds[2];  // Front LED rgb values for indicator mode use

// Predefined colors for layers
// Format: {hue, saturation}
// {0, 0} to turn off the LED
// Add additional rows to handle more layers
__attribute__ ((weak))
const hs_set layer_colors[] = {
    [0] = {0,     0},  // Color for Layer 0
    [1] = {86,    255},  // Color for Layer 1
    [2] = {36,    255},  // Color for Layer 2
    [3] = {185,   255},  // Color for Layer 3
};

__attribute__ ((weak))
const size_t lc_size = sizeof(layer_colors) / sizeof(uint16_t);

void matrix_init_kb(void) {
    // If EEPROM config exists, load it
    if (eeprom_is_valid()) {
        fled_config fled_conf;
        fled_conf.raw = eeprom_read_byte(EEPROM_FRONTLED_ADDR);
        fled_mode = fled_conf.mode;
        fled_val = fled_conf.val * FLED_VAL_STEP;
    // Else, default config
    } else {
        fled_mode = FLED_RGB;
        fled_val = 10 * FLED_VAL_STEP;
        eeprom_update_conf();   // Store default config to EEPROM
    }
    
    // Set default values for leds
    setrgb(0, 0, 0, &fleds[0]);
    setrgb(0, 0, 0, &fleds[1]);
    
    // Handle lighting for indicator mode
    if (fled_mode == FLED_INDI) {
        // Enable capslock led if enabled on host
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))
            sethsv(FLED_CAPS_H, FLED_CAPS_S, fled_val, &fleds[0]);
        
        // Determine and set colour of layer LED according to current layer
        // if hue = sat = 0, leave LED off
        uint8_t layer = biton32(layer_state);
        if (layer < lc_size && !(layer_colors[layer].hue == 0 && layer_colors[layer].hue == 0))
            sethsv(layer_colors[layer].hue, layer_colors[layer].sat, fled_val, &fleds[1]);
    }

	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Handle custom keycodes for front LED operation
    switch (keycode) {
        case FLED_MOD: // Change between front LED operation modes (off, indicator, RGB)
        if (record->event.pressed)
            fled_mode_cycle();
        break;
        
        case FLED_VAI: // Increase the brightness of the front LEDs by FLED_VAL_STEP
        if (record->event.pressed)
            fled_val_increase();
        break;
        
        case FLED_VAD: // Decrease the brightness of the front LEDs by FLED_VAL_STEP
        if (record->event.pressed)
            fled_val_decrease();
        break;
        
        default:
        break; // Process all other keycodes normally
      }

	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    // Set indicator LED appropriately, whether it is used or not
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        sethsv(FLED_CAPS_H, FLED_CAPS_S, fled_val, &fleds[0]);
    } else {
        setrgb(0, 0, 0, &fleds[0]);
    }

    rgblight_set();
	led_set_user(usb_led);
}

uint32_t layer_state_set_kb(uint32_t state) {
    // Determine and set colour of layer LED according to current layer
    // if hue = sat = 0, leave LED off
    uint8_t layer = biton32(state);
    
    if (layer < lc_size && !(layer_colors[layer].hue == 0 && layer_colors[layer].hue == 0))
        sethsv(layer_colors[layer].hue, layer_colors[layer].sat, fled_val, &fleds[1]);
    else
        setrgb(0, 0, 0, &fleds[1]);
    
    return state;
}

// EEPROM Management

// Test if magic value is present at expected location
bool eeprom_is_valid(void)
{
	return (eeprom_read_word(EEPROM_MAGIC_ADDR) == EEPROM_MAGIC);
}

// Set magic value at expected location
void eeprom_set_valid(bool valid)
{
	eeprom_update_word(EEPROM_MAGIC_ADDR, valid ? EEPROM_MAGIC : 0xFFFF);
}

// Store current front led config in EEPROM
void eeprom_update_conf(void)
{
    // Create storage struct and set values
    fled_config conf;
    conf.mode = fled_mode;
    
    // Small hack to ensure max value is stored correctly
    if (fled_val == 255)
        conf.val = 256 / FLED_VAL_STEP;
    else
        conf.val = fled_val / FLED_VAL_STEP;
    
    // Set magic value and store config
    eeprom_set_valid(true);
	eeprom_update_byte(EEPROM_FRONTLED_ADDR, conf.raw);
}

// Custom keycode functions

void fled_mode_cycle(void)
{
    // FLED -> FLED_RGB -> FLED_INDI
    switch (fled_mode) {
        case FLED_OFF:
        fled_mode = FLED_RGB;
        break;
        
        case FLED_RGB:
        fled_mode = FLED_INDI;
        break;
        
        case FLED_INDI:
        fled_mode = FLED_OFF;
        break;
    }
    
    // Update stored config
    eeprom_update_conf();
    rgblight_set();
}

void fled_val_increase(void)
{
    // Increase val by FLED_VAL_STEP, handling the upper edge case
    if (fled_val + FLED_VAL_STEP > 255)
        fled_val = 255;
    else
        fled_val += FLED_VAL_STEP;
    
    // Update stored config
    eeprom_update_conf();
    rgblight_set();
}

void fled_val_decrease(void)
{
    // Decrease val by FLED_VAL_STEP, handling the lower edge case
    if (fled_val - FLED_VAL_STEP > 255)
        fled_val = 255;
    else
        fled_val -= FLED_VAL_STEP;
    
    // Update stored config
    eeprom_update_conf();
    rgblight_set();
}
