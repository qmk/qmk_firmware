#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "config.h"
#include "timer.h"
#include "transport.h"
#include "quantum.h"

#ifdef PROTOCOL_LUFA
#    include <LUFA/Drivers/USB/USB.h>
#endif

#ifdef PROTOCOL_VUSB
#    include "usbdrv.h"
#endif

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

#ifdef PROTOCOL_CHIBIOS
#    define SPLIT_USB_DETECT  // Force this on for now
#endif

volatile bool isLeftHand = true;

#if defined(SPLIT_USB_DETECT)
#    if defined(PROTOCOL_LUFA)
static inline bool usbHasActiveConnection(void) { return USB_Device_IsAddressSet(); }
static inline void usbDisable(void) {
    USB_Disable();
    USB_DeviceState = DEVICE_STATE_Unattached;
}
#    elif defined(PROTOCOL_CHIBIOS)
static inline bool usbHasActiveConnection(void) { return usbGetDriverStateI(&USBD1) == USB_ACTIVE; }
static inline void usbDisable(void) { usbStop(&USBD1); }
#    elif defined(PROTOCOL_VUSB)
static inline bool usbHasActiveConnection(void) {
    usbPoll();
    return usbConfiguration;
}
static inline void usbDisable(void) { usbDeviceDisconnect(); }
#    else
static inline bool usbHasActiveConnection(void) { return true; }
static inline void usbDisable(void) {}
#    endif

bool usbIsActive(void) {
    for (uint8_t i = 0; i < (SPLIT_USB_TIMEOUT / SPLIT_USB_TIMEOUT_POLL); i++) {
        // This will return true if a USB connection has been established
        if (usbHasActiveConnection()) {
            return true;
        }
        wait_ms(SPLIT_USB_TIMEOUT_POLL);
    }

    // Avoid NO_USB_STARTUP_CHECK - Disable USB as the previous checks seem to enable it somehow
    usbDisable();

    return false;
}
#elif defined(PROTOCOL_LUFA)
static inline bool usbIsActive(void) {
    USB_OTGPAD_On();  // enables VBUS pad
    wait_us(5);

    return USB_VBUS_GetStatus();  // checks state of VBUS
}
#else
static inline bool usbIsActive(void) { return true; }
#endif

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
        usbstate = usbIsActive() ? MASTER : SLAVE;
    }

    return (usbstate == MASTER);
}

// this code runs before the keyboard is fully initialized
void split_pre_init(void) {
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
#if defined(USE_I2C) && defined(SSD1306OLED)
        matrix_master_OLED_init();
#endif
        transport_master_init();
    }
}

// this code runs after the keyboard is fully initialized
//   - avoids race condition during matrix_init_quantum where slave can start
//     receiving before the init process has completed
void split_post_init(void) {
    if (!is_keyboard_master()) {
        transport_slave_init();
    }
}
