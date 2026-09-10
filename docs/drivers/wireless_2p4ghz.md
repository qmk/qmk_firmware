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

Driver selection can be configured in `rules.mk` as `WIRELESS_2P4GHZ_DRIVER`. Valid values are `custom` and `fr800x`.

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

### FR800x Driver {#fr800x-driver}

Driver for Freqchip FR8003A and other FR800x-family UART chips paired with a USB dongle running matching firmware. The chip handles the 2.4 GHz radio and HID transport; the host MCU sends length-prefixed framed UART packets over the framed UART driver.

```make
WIRELESS_2P4GHZ_ENABLE = yes
WIRELESS_2P4GHZ_DRIVER = fr800x
```

Or in `keyboard.json`:

```json
"features": {
    "wireless_2p4ghz": true
},
"wireless_2p4ghz": {
    "driver": "fr800x"
}
```

`UART_FRAME` is pulled in automatically. The driver shares its protocol core with the matching Bluetooth driver (`BLUETOOTH_DRIVER = fr800x`); on boards that enable both, the shared core is linked once.

Boards must call `fr800x_post_init()` from `keyboard_post_init_kb()`, and advertise their dongle identity by calling `fr800x_dongle_send_descriptor()` and `fr800x_dongle_send_vendor_product_id()` during post-init.
