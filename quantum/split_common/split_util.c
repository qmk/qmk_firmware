#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "config.h"
#include "timer.h"
#include "transport.h"
#include "quantum.h"

#ifdef EE_HANDS
#    include "eeconfig.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
#    include "rgblight.h"
#endif

#ifndef SPLIT_USB_TIMEOUT
#    define SPLIT_USB_TIMEOUT 2000
#endif

#ifndef SPLIT_USB_TIMEOUT_POLL
#    define SPLIT_USB_TIMEOUT_POLL 10
#endif

volatile bool isLeftHand = true;

bool waitForUsb(void) {
    for (uint8_t i = 0; i < (SPLIT_USB_TIMEOUT / SPLIT_USB_TIMEOUT_POLL); i++) {
        // This will return true if a USB connection has been established
#if defined(__AVR__)
        if (UDADDR & _BV(ADDEN)) {
#else
        if (usbGetDriverStateI(&USBD1) == USB_ACTIVE) {
#endif
            return true;
        }
        wait_ms(SPLIT_USB_TIMEOUT_POLL);
    }

    // Avoid NO_USB_STARTUP_CHECK - Disable USB as the previous checks seem to enable it somehow
#if defined(__AVR__)
    (USBCON &= ~(_BV(USBE) | _BV(OTGPADE)));
#else
    usbStop(&USBD1);
#endif

    return false;
}

__attribute__((weak)) bool is_keyboard_left(void) {
#if defined(SPLIT_HAND_PIN)
    // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
    setPinInput(SPLIT_HAND_PIN);
    return readPin(SPLIT_HAND_PIN);
#elif defined(EE_HANDS)
    return eeconfig_read_handedness();
#elif defined(MASTER_RIGHT)
    return !is_keyboard_master();
#endif

    return is_keyboard_master();
}

__attribute__((weak)) bool is_keyboard_master(void) {
    static enum { UNKNOWN, MASTER, SLAVE } usbstate = UNKNOWN;

    // only check once, as this is called often
    if (usbstate == UNKNOWN) {
#if defined(SPLIT_USB_DETECT) || defined(PROTOCOL_CHIBIOS)
        usbstate = waitForUsb() ? MASTER : SLAVE;
#elif defined(__AVR__)
        USBCON |= (1 << OTGPADE);  // enables VBUS pad
        wait_us(5);

        usbstate = (USBSTA & (1 << VBUS)) ? MASTER : SLAVE;  // checks state of VBUS
#else
        usbstate = MASTER;
#endif
    }

    return (usbstate == MASTER);
}

static void keyboard_master_setup(void) {
#if defined(USE_I2C) || defined(EH)
#    ifdef SSD1306OLED
    matrix_master_OLED_init();
#    endif
#endif
    transport_master_init();
}

static void keyboard_slave_setup(void) { transport_slave_init(); }

// this code runs before the keyboard is fully initialized
void keyboard_split_setup(void) {
    isLeftHand = is_keyboard_left();

#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
    uint8_t num_rgb_leds_split[2] = RGBLED_SPLIT;
    if (isLeftHand) {
        rgblight_set_clipping_range(0, num_rgb_leds_split[0]);
    } else {
        rgblight_set_clipping_range(num_rgb_leds_split[0], num_rgb_leds_split[1]);
    }
#endif

    if (is_keyboard_master()) {
        keyboard_master_setup();
    } else {
        keyboard_slave_setup();
    }
}
