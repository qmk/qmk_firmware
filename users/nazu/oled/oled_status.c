#include <stdio.h>
#include "nazu.h"

int   current_wpm = 0;
led_t led_usb_state;


/* 32 * 14 os logos */
static const char PROGMEM windows_logo[] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xbc,
    0xbc, 0xbe, 0xbe, 0x00,
    0xbe, 0xbe, 0xbf, 0xbf,
    0xbf, 0xbf, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07,
    0x07, 0x0f, 0x0f, 0x00,
    0x0f, 0x0f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

static const char PROGMEM mac_logo[] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0,
    0xf0, 0xf8, 0xf8, 0xf8,
    0xf0, 0xf6, 0xfb, 0xfb,
    0x38, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01,
    0x07, 0x0f, 0x1f, 0x1f,
    0x0f, 0x0f, 0x1f, 0x1f,
    0x0f, 0x06, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

static void print_status_narrow(void) {
    /* Print current mode */
    oled_set_cursor(0, 0);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_raw_P(mac_logo, sizeof(mac_logo));
    } else {
        oled_write_raw_P(windows_logo, sizeof(windows_logo));
    }

    oled_set_cursor(0, 3);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        case _COLEMAK_DH:
            oled_write("CLMAK", false);
            break;
        default:
            oled_write("UNDEF", false);
    }

    oled_set_cursor(0, 5);

    /* Print current layer */
    oled_write("LAYER", false);

    oled_set_cursor(0, 6);

    switch (get_highest_layer(layer_state)) {
        // case _QWERTY:
            // oled_write("QWRTY", false);
            // break;
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        case _COLEMAK_DH:
            oled_write("Clmak ", false);
            break;
        case _RAISE:
            oled_write("Raise", false);
            break;
        case _LOWER:
            oled_write("Lower", false);
            break;
        case _ADJUST:
            oled_write("Adj  ", false);
            break;
        default:
            oled_write("Undef", false);
    }

    /* caps lock */
    oled_set_cursor(0, 8);
    oled_write("CPSLK", led_usb_state.caps_lock);

}

/**
 * @brief Keycode handler for oled display.
 *
 * This adds pressed keys to buffer, but also resets the oled timer
 *
 * @param keycode Keycode from matrix
 * @param record keyrecord data struture
 * @return true
 * @return false
 */
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    // switch (keycode) {
    //     case KC_SPACE:
    //         if (record->event.pressed) {
    //             isJumping  = true;
    //             showedJump = false;
    //         } else {
    //             isJumping = false;
    //         }
    //         break;
    //     case KC_RCTL:
    //         if (record->event.pressed) {
    //             isSneaking = true;
    //         } else {
    //             isSneaking = false;
    //         }
    //         break;
    // }
    return true;
}
