HHKB Alternate Controller (YANG BLE ver.)
===

An alternative controler for the HHKB designed by YANG (yangdigi) based on hasu controller.

Keyboard Maintainer: QMK Community  
Hardware Supported: YANG HHKB BLE Alternate Controller  
Hardware Availability: https://kbdfans.com/products/hhkb-ble-mod-upgrade-module

Make example for this keyboard (after setting up your build environment):

    make hhkb_yang:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

To flash on Linux, first boot your keyboard into bootloader (hold ESC and attach usb cable):

    make hhkb_yang:default:flash

Features planned:

- [x] QMK (via USB)
- [ ] Bluetooth (BLE)
- [ ] Power saving mode
- [ ] LEDs
- [ ] Special commands
