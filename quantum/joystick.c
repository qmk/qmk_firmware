#include "joystick.h"

// clang-format off
joystick_t joystick_status = {
    .buttons = {0},
    .axes = {
#if JOYSTICK_AXES_COUNT > 0
        0
#endif
    },
    .status = 0
};
// clang-format on

// array defining the reading of analog values for each axis
__attribute__((weak)) joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {};

// to be implemented in the hid protocol library
void send_joystick_packet(joystick_t *joystick);

void joystick_flush(void) {
    if ((joystick_status.status & JS_UPDATED) > 0) {
        send_joystick_packet(&joystick_status);
        joystick_status.status &= ~JS_UPDATED;
    }
}

void register_joystick_button(uint8_t button) {
    joystick_status.buttons[button / 8] |= 1 << (button % 8);
    joystick_status.status |= JS_UPDATED;
    joystick_flush();
}

void unregister_joystick_button(uint8_t button) {
    joystick_status.buttons[button / 8] &= ~(1 << (button % 8));
    joystick_status.status |= JS_UPDATED;
    joystick_flush();
}
