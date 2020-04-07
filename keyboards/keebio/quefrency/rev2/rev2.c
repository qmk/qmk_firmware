#include "quefrency.h"
#include "split_util.h"

void matrix_init_kb(void) {
    setPinOutput(CAPS_LOCK_LED_PIN);
    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    // Only update if left half
    if (isLeftHand && led_update_user(led_state)) {
        writePin(CAPS_LOCK_LED_PIN, !led_state.caps_lock);
    }
    return true;
}

void eeconfig_init_kb(void) {
    backlight_enable();
    backlight_level(3);
    rgblight_enable(); // Enable RGB by default
    rgblight_sethsv(0, 255, 128);  // Set default HSV - red hue, full saturation, medium brightness
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // set to RGB_RAINBOW_SWIRL by default

    eeconfig_update_kb(0);
    eeconfig_init_user();
}
