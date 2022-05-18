/* Copyright 2020 Jumail Mundekkat / MxBlue
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
 *
 * Extended from the work done by fcoury: https://github.com/qmk/qmk_firmware/pull/4915
 */

#include "mxss_frontled.h"
#include "eeprom.h"
#include "rgblight.h"
#include "via.h"
#include "version.h" // for QMK_BUILDDATE used in EEPROM magic

// Variables for controlling front LED application
uint8_t fled_mode;  // Mode for front LEDs
uint8_t fled_val;   // Brightness for front leds (0 - 255)
LED_TYPE fleds[2];  // Front LED rgb values for indicator mode use

// Layer indicator colors
__attribute__ ((weak))
hs_set layer_colors[FRONTLED_COLOR_MAXCNT];

// Caps lock indicator color
__attribute__ ((weak))
hs_set caps_color;

__attribute__ ((weak))
size_t lc_size = sizeof(layer_colors) / sizeof(hs_set);

void fled_init(void) {
    // If EEPROM config exists, load it
    // If VIA EEPROM exists, FLED config should too
    if (via_eeprom_is_valid()) {
        fled_load_conf();
    // Else, default config
    } else {
        // Default mode/brightness
        fled_mode = FLED_RGB;
        fled_val = 10 * FLED_VAL_STEP;

        // Default colors
        caps_color.hue = 0;
        caps_color.sat = 255;
        layer_colors[0].hue = 0;
        layer_colors[0].sat = 0;
        layer_colors[1].hue = 86;
        layer_colors[1].sat = 255;
        layer_colors[2].hue = 36;
        layer_colors[2].sat = 255;
        layer_colors[3].hue = 185;
        layer_colors[3].sat = 255;

        fled_update_conf();   // Store default config to EEPROM
    }

    // Set default values for leds
    setrgb(0, 0, 0, &fleds[0]);
    setrgb(0, 0, 0, &fleds[1]);

    // Handle lighting for indicator mode
    if (fled_mode == FLED_INDI) {
        fled_lock_update(host_keyboard_led_state());
        fled_layer_update(layer_state);
    }
}

void  process_record_fled(uint16_t keycode, keyrecord_t *record) {
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

	return;
}

void fled_load_conf(void) {
    // Load config
    fled_config fled_conf;
    fled_conf.raw = eeprom_read_byte(FRONTLED_CONF_ADDR);
    fled_mode = fled_conf.mode;
    fled_val = fled_conf.val * FLED_VAL_STEP;

    // Load color data
    uint8_t stored_cnt = eeprom_read_byte(FRONTLED_COLOR_CNT_ADDR);
    uint16_t *color_ptr = FRONTLED_COLOR_ADDR;
    caps_color.raw = eeprom_read_word(color_ptr); // Should always store at least 1 color
    for (uint8_t i = 1; i < stored_cnt; i++) {
        if (i == lc_size) // Can't load more layers than we have available
            break;
        layer_colors[i].raw = eeprom_read_word(&color_ptr[i]);
    }
    layer_colors[0].raw = 0; // hue = sat = 0 for layer 0
}

// Store current front led config in EEPROM
void fled_update_conf(void)
{
    // Create storage struct and set values
    fled_config conf;
    conf.mode = fled_mode;

    // Small hack to ensure max value is stored correctly
    if (fled_val == 255)
        conf.val = 256 / FLED_VAL_STEP;
    else
        conf.val = fled_val / FLED_VAL_STEP;

    // Store config
    eeprom_update_byte(FRONTLED_CONF_ADDR, conf.raw);

    // Store color data
    uint16_t *color_ptr = FRONTLED_COLOR_ADDR;
    eeprom_update_word(color_ptr, caps_color.raw);
    // Start from 1, layer 0 is not modifiable and therefore not persisted
    uint8_t i = 1;
    for (; i < lc_size; i++) {
        if (i == FRONTLED_COLOR_MAXCNT) // Can't store more than the EEPROM we have available
            break;
        eeprom_update_word(&color_ptr[i], layer_colors[i].raw);
    }
    eeprom_update_byte(FRONTLED_COLOR_CNT_ADDR, i); // For safety, store the count of colors stored
}

// Custom keycode functions

void fled_mode_cycle(void)
{
    // FLED -> FLED_RGB -> FLED_INDI
    switch (fled_mode) {
        case FLED_OFF:
        fled_mode = FLED_RGB;
        rgblight_timer_enable();
        break;

        case FLED_RGB:
        fled_mode = FLED_INDI;
        break;

        case FLED_INDI:
        fled_mode = FLED_OFF;
        break;
    }

    // Update stored config
    fled_update_conf();
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
    fled_update_conf();

    // Update and set LED state
    if (fled_mode == FLED_INDI) {
        fled_layer_update(layer_state);
        fled_lock_update(host_keyboard_led_state());
    } else {
        rgblight_set();
    }
}

void fled_val_decrease(void)
{
    // Decrease val by FLED_VAL_STEP, handling the lower edge case
    if (fled_val - FLED_VAL_STEP > 255)
        fled_val = 255;
    else
        fled_val -= FLED_VAL_STEP;

    // Update stored config
    fled_update_conf();

    // Update and set LED state
    if (fled_mode == FLED_INDI) {
        fled_layer_update(layer_state);
        fled_lock_update(host_keyboard_led_state());
    } else {
        rgblight_set();
    }
}

void fled_layer_update(layer_state_t state) {
    // Determine and set colour of layer LED according to current layer
    // if hue = sat = 0, leave LED off
    uint8_t layer = get_highest_layer(state);

    if (layer < lc_size && !(layer_colors[layer].hue == 0 && layer_colors[layer].sat == 0)) {
        sethsv(layer_colors[layer].hue, layer_colors[layer].sat, fled_val, &fleds[1]);
    } else {
        setrgb(0, 0, 0, &fleds[1]);
    }
}

void fled_lock_update(led_t led_state) {
    // Set indicator LED appropriately, whether it is used or not
    if (led_state.caps_lock) {
        sethsv(caps_color.hue, caps_color.sat, fled_val, &fleds[0]);
    } else {
        setrgb(0, 0, 0, &fleds[0]);
    }

    rgblight_set();
}

void set_fled_layer_color(uint8_t layer, hs_set hs) {
    // Update layer colors and refresh LEDs
    layer_colors[layer] = hs;
    fled_layer_update(layer_state);
    fled_update_conf();
}

hs_set get_fled_layer_color(uint8_t layer) {
    return layer_colors[layer];
}

void set_fled_caps_color(hs_set hs) {
    // Update caplock color and refresh LEDs
    caps_color = hs;
    fled_lock_update(host_keyboard_led_state());
    fled_update_conf();
}

hs_set get_fled_caps_color(void) {
    return caps_color;
}

// Fallback eeprom functions if VIA is not enabled
#ifndef VIA_ENABLE

// Can be called in an overriding via_init_kb() to test if keyboard level code usage of
// EEPROM is invalid and use/save defaults.
bool via_eeprom_is_valid(void)
{
    char *p = QMK_BUILDDATE; // e.g. "2019-11-05-11:29:54"
    uint8_t magic0 = ( ( p[2] & 0x0F ) << 4 ) | ( p[3]  & 0x0F );
    uint8_t magic1 = ( ( p[5] & 0x0F ) << 4 ) | ( p[6]  & 0x0F );
    uint8_t magic2 = ( ( p[8] & 0x0F ) << 4 ) | ( p[9]  & 0x0F );

    return (eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+0 ) == magic0 &&
            eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+1 ) == magic1 &&
            eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+2 ) == magic2 );
}

#endif
