# 2.4 GHz Wireless Driver

This driver provides the upstream contract for 2.4 GHz proprietary wireless transports (USB dongles paired to a coprocessor on the keyboard).

## Usage

To use this driver, add the following to your `rules.mk`:

```make
WIRELESS_2P4GHZ_ENABLE = yes
WIRELESS_2P4GHZ_DRIVER = custom
```

Or in `keyboard.json`:

```json
"features": {
    "wireless_2p4ghz": true
},
"wireless_2p4ghz": {
    "driver": "custom"
}
```

## Driver Configuration {#driver-configuration}

Driver selection can be configured in `rules.mk` as `WIRELESS_2P4GHZ_DRIVER`. The only valid value today is `custom`. Chip-specific drivers may be added in the future.

### Custom Driver {#custom-driver}

A custom driver is expected to implement the following interface:

```c
void wireless_2p4ghz_init(void) {
    // Perform any initialisation here
}

void wireless_2p4ghz_task(void) {
    // Per-loop housekeeping
}

bool wireless_2p4ghz_is_connected(void) {
    // Return true when the dongle reports an active link to its host
    return false;
}

bool wireless_2p4ghz_can_send_nkro(void) {
    return false;
}

uint8_t wireless_2p4ghz_keyboard_leds(void) {
    return 0;
}

void wireless_2p4ghz_send_keyboard(report_keyboard_t *report) {}
void wireless_2p4ghz_send_nkro(report_nkro_t *report) {}
void wireless_2p4ghz_send_mouse(report_mouse_t *report) {}
void wireless_2p4ghz_send_consumer(uint16_t usage) {}
void wireless_2p4ghz_send_system(uint16_t usage) {}
void wireless_2p4ghz_send_raw_hid(uint8_t *data, uint8_t length) {}

void wireless_2p4ghz_unpair(void) {
    // Drop the dongle's bond
}
```

All hooks have weak no-op defaults; only override the ones the driver actually implements.
