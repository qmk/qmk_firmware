/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include "keyboard.h"
#include "keycode.h"
#include "host.h"
#include "util.h"
#include "debug.h"

#ifdef DIGITIZER_ENABLE
#    include "digitizer.h"
#endif

#ifdef JOYSTICK_ENABLE
#    include "joystick.h"
#endif

#ifdef NKRO_ENABLE
#    include "keycode_config.h"
extern keymap_config_t keymap_config;
#endif

static host_driver_t *driver              = NULL;
static uint16_t       last_system_usage   = 0;
static uint16_t       last_consumer_usage = 0;

void host_set_driver(host_driver_t *d) {
    // Disconnect if necessary
    if (driver && driver->disconnect) {
        driver->disconnect();
    }

    // Update the driver instance
    driver = d;

    // Init the driver if it's not done so already
    if (driver && !driver->has_init_executed) {
        if (driver->init) {
            driver->init();
        }
        driver->has_init_executed = true;
    }

    // Connect the driver
    if (driver && driver->connect) {
        driver->connect();
    }
}

host_driver_t *host_get_driver(void) {
    return driver;
}

__attribute__((weak)) host_driver_t *host_usb_driver(void) {
    return NULL;
}
__attribute__((weak)) host_driver_t *host_bluetooth_driver(void) {
    return NULL;
}
__attribute__((weak)) host_driver_t *host_2pt4Ghz_driver(void) {
    return NULL;
}

#ifdef SPLIT_KEYBOARD
uint8_t split_led_state = 0;
void    set_split_host_keyboard_leds(uint8_t led_state) {
    split_led_state = led_state;
}
#endif

uint8_t host_keyboard_leds(void) {
#ifdef SPLIT_KEYBOARD
    if (!is_keyboard_master()) return split_led_state;
#endif
    if (!driver || !driver->keyboard_leds) return 0;
    return (*driver->keyboard_leds)();
}

led_t host_keyboard_led_state(void) {
    return (led_t)host_keyboard_leds();
}

/* send report */
void host_keyboard_send(report_keyboard_t *report) {
    if (!driver || !driver->send_keyboard) return;
#ifdef KEYBOARD_SHARED_EP
    report->report_id = REPORT_ID_KEYBOARD;
#endif
    (*driver->send_keyboard)(report);

    if (debug_keyboard) {
        dprintf("keyboard_report: %02X | ", report->mods);
        for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            dprintf("%02X ", report->keys[i]);
        }
        dprint("\n");
    }
}

void host_nkro_send(report_nkro_t *report) {
    if (!driver || !driver->send_nkro) return;
    report->report_id = REPORT_ID_NKRO;
    (*driver->send_nkro)(report);

    if (debug_keyboard) {
        dprintf("nkro_report: %02X | ", report->mods);
        for (uint8_t i = 0; i < NKRO_REPORT_BITS; i++) {
            dprintf("%02X ", report->bits[i]);
        }
        dprint("\n");
    }
}

void host_mouse_send(report_mouse_t *report) {
    if (!driver || !driver->send_mouse) return;
#ifdef MOUSE_SHARED_EP
    report->report_id = REPORT_ID_MOUSE;
#endif
#ifdef MOUSE_EXTENDED_REPORT
    // clip and copy to Boot protocol XY
    report->boot_x = (report->x > 127) ? 127 : ((report->x < -127) ? -127 : report->x);
    report->boot_y = (report->y > 127) ? 127 : ((report->y < -127) ? -127 : report->y);
#endif
    (*driver->send_mouse)(report);
}

void host_system_send(uint16_t usage) {
    if (usage == last_system_usage) return;
    last_system_usage = usage;

    if (!driver || !driver->send_extra) return;

    report_extra_t report = {
        .report_id = REPORT_ID_SYSTEM,
        .usage     = usage,
    };
    (*driver->send_extra)(&report);
}

void host_consumer_send(uint16_t usage) {
    if (usage == last_consumer_usage) return;
    last_consumer_usage = usage;

    if (!driver || !driver->send_extra) return;

    report_extra_t report = {
        .report_id = REPORT_ID_CONSUMER,
        .usage     = usage,
    };
    (*driver->send_extra)(&report);
}

#ifdef JOYSTICK_ENABLE
void host_joystick_send(joystick_t *joystick) {
    if (!driver || !driver->send_joystick) return;

    report_joystick_t report = {
#    ifdef JOYSTICK_SHARED_EP
        .report_id = REPORT_ID_JOYSTICK,
#    endif
#    if JOYSTICK_AXIS_COUNT > 0
        .axes =
            {
                joystick->axes[0],

#        if JOYSTICK_AXIS_COUNT >= 2
                joystick->axes[1],
#        endif
#        if JOYSTICK_AXIS_COUNT >= 3
                joystick->axes[2],
#        endif
#        if JOYSTICK_AXIS_COUNT >= 4
                joystick->axes[3],
#        endif
#        if JOYSTICK_AXIS_COUNT >= 5
                joystick->axes[4],
#        endif
#        if JOYSTICK_AXIS_COUNT >= 6
                joystick->axes[5],
#        endif
            },
#    endif

#    ifdef JOYSTICK_HAS_HAT
        .hat = joystick->hat,
#    endif

#    if JOYSTICK_BUTTON_COUNT > 0
        .buttons =
            {
                joystick->buttons[0],

#        if JOYSTICK_BUTTON_COUNT > 8
                joystick->buttons[1],
#        endif
#        if JOYSTICK_BUTTON_COUNT > 16
                joystick->buttons[2],
#        endif
#        if JOYSTICK_BUTTON_COUNT > 24
                joystick->buttons[3],
#        endif
            },
#    endif
    };

    (*driver->send_joystick)(&report);
}
#endif

#ifdef DIGITIZER_ENABLE
void host_digitizer_send(digitizer_t *digitizer) {
    if (!driver || !driver->send_digitizer) return;

    report_digitizer_t report = {
#    ifdef DIGITIZER_SHARED_EP
        .report_id = REPORT_ID_DIGITIZER,
#    endif
        .in_range = digitizer->in_range,
        .tip      = digitizer->tip,
        .barrel   = digitizer->barrel,
        .x        = (uint16_t)(digitizer->x * 0x7FFF),
        .y        = (uint16_t)(digitizer->y * 0x7FFF),
    };

    (*driver->send_digitizer)(&report);
}
#endif

#ifdef PROGRAMMABLE_BUTTON_ENABLE
void host_programmable_button_send(uint32_t data) {
    if (!driver || !driver->send_programmable_button) return;

    report_programmable_button_t report = {
        .report_id = REPORT_ID_PROGRAMMABLE_BUTTON,
        .usage     = data,
    };

    (*driver->send_programmable_button)(&report);
}
#endif

#ifdef CONSOLE_ENABLE
int8_t host_console_send(uint8_t c) {
    if (!driver || !driver->send_console) return -1;
    return (*driver->send_console)(c);
}

// Original API
int8_t sendchar(uint8_t c) {
    return host_console_send(c);
}
#endif // CONSOLE_ENABLE

#ifdef VIRTSER_ENABLE
void host_virtser_send(const uint8_t c) {
    if (!driver || !driver->send_virtser) return;
    (*driver->send_virtser)(c);
}

// Original API
void virtser_send(const uint8_t c) {
    host_virtser_send(c);
}
#endif // VIRTSER_ENABLE

#ifdef RAW_ENABLE
void host_raw_hid_send(uint8_t *data, uint8_t length) {
    if (!driver || !driver->send_raw_hid) return;
    (*driver->send_raw_hid)(data, length);
}

// Original API
void raw_hid_send(uint8_t *data, uint8_t length) {
    host_raw_hid_send(data, length);
}
#endif // RAW_ENABLE

uint16_t host_last_system_usage(void) {
    return last_system_usage;
}

uint16_t host_last_consumer_usage(void) {
    return last_consumer_usage;
}
