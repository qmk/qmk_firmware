#include QMK_KEYBOARD_H
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

// Das Display kann 11 Zeichen
static void render_status(void) {
    // QMK Logo and version information
    //render_qmk_logo();
    oled_write_P(PSTR("SepiDre 2.0\n\n"), false);

    oled_write_P(PSTR("Default: "), false);
    switch (get_highest_layer(default_layer_state)) {
        case _NEO2:
            oled_write_P(PSTR("NEO 2\n"), false);
            break;
        case _SHOOT:
            oled_write_P(PSTR("Shooter\n"), false);
            break;
    }

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _NUMBER:
        case _NUMLEFT:
            oled_write_P(PSTR("Numbers"), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("Symbols"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust"), false);
            break;
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
         render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    }
}
