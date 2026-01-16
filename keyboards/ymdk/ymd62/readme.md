# YMDK YMD62 ISO

A 60% PCB supporting the ISO layout, with hotswap sockets, backlit keys and underglow.

* Keyboard Maintainer: [Richard Dawe](https://github.com/richdawe)
* Hardware Supported: YMD62 PCB
* Hardware Availability: [YMDK](https://ymdkey.com/products/ymd62-iso-rgb-hot-swap-pcb-fully-programmable-support-via-vial)

Make example for this keyboard (after setting up your build environment):

    make ymdk/ymd62:default

Flashing example for this keyboard:

    make ymdk/ymd62:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Double-tap the reset button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Note: The device does not reconnect automatically after the QMK firmware has been flashed.
Wait for the USB device to disappear after writing firmware, then unplug and re-plug it.