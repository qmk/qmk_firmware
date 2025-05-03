# pi50

The pi40 is a 5x12 ortholinear keyboard with options for a 1u or 2u spacebar using a Raspberry Pi Pico for the controller.

It includes options for a rotary encoder, SSD1306 oled, and per-key in-switch RGB LEDs.

All unused GPIO pins are broken out on the main pcb, as well as the available voltage pins.

This firmware also includes the option for VIA which includes configuration options for the rotary encoder, matrix lighting, and up to 10 layers.

Default oled configuration displays:
   - current layer
   - caps lock status
   - num lock status
   - scroll lock status
   - current RGB lighting mode

* Keyboard Maintainer: [ziptyze](https://github.com/ziptyze)
* Hardware Availability: (https://1upkeyboards.com/shop/keyboard-kits/diy-40-kits/pi50-keyboard-kit/#pcb-color)

Make example for this keyboard (after setting up your build environment):

    make 1upkeyboards/pi50:default

Flashing example for this keyboard:

    make 1upkeyboards/pi50:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix, the top left key, and plug in the keyboard
* **BOOTSEL button**: Hold down the BOOTSEL button on the pico, and plug in the keyboard
