#include "mxss_frontled.h"
#include "tmk_core/common/eeprom.h"
#include "rgblight.h"
#include "via.h"
#include "version.h" // for QMK_BUILDDATE used in EEPROM magic

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

void fled_init(void) {
    // If EEPROM config exists, load it
    // If VIA EEPROM exists, FLED config should too
    if (via_eeprom_is_valid()) {
        fled_config fled_conf;
        fled_conf.raw = eeprom_read_byte(EEPROM_FRONTLED_ADDR);
        fled_mode = fled_conf.mode;
        fled_val = fled_conf.val * FLED_VAL_STEP;
    // Else, default config
    } else {
        fled_mode = FLED_RGB;
        fled_val = 10 * FLED_VAL_STEP;
        fled_update_conf();   // Store default config to EEPROM
    }

    // Set default values for leds
    setrgb(0, 0, 0, &fleds[0]);
    setrgb(0, 0, 0, &fleds[1]);

    // Handle lighting for indicator mode
    if (fled_mode == FLED_INDI) {
        fled_lock_update(host_keyboard_leds());
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
	eeprom_update_byte(EEPROM_FRONTLED_ADDR, conf.raw);
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
    fled_update_conf();
    rgblight_set();
}

void fled_layer_update(uint32_t state) {
    // Determine and set colour of layer LED according to current layer
    // if hue = sat = 0, leave LED off
    uint8_t layer = biton32(state);

    if (layer < lc_size && !(layer_colors[layer].hue == 0 && layer_colors[layer].hue == 0))
        sethsv(layer_colors[layer].hue, layer_colors[layer].sat, fled_val, &fleds[1]);
    else
        setrgb(0, 0, 0, &fleds[1]);
}

void fled_lock_update(uint8_t usb_led) {
    // Set indicator LED appropriately, whether it is used or not
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        sethsv(FLED_CAPS_H, FLED_CAPS_S, fled_val, &fleds[0]);
    } else {
        setrgb(0, 0, 0, &fleds[0]);
    }

    rgblight_set();
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
