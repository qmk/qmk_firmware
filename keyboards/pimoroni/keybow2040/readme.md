# Keybow 2040

The [Pimoroni Keybow 2040][keybow2040] is a 16 key mechanical macropad
controlled by a Raspberry Pi RP2040, with Kailh hot swap sockets and
per key RGB lighting, in a decorative FR4 sandwich. The Keybow 2040 is
also known by its codename Venus Dust, or its product codes of the
form PIM56x.

* Original Keyboard Maintainer: [Tony Finch](https://github.com/fanf2)
* Keyboard Maintainer: [Wilfried Jeanniard](https://github.com/willoucom)
* Hardware Supported: Keybow 2040
* Hardware Availability: [Pimoroni](https://shop.pimoroni.com/products/keybow-2040)

Make example for this keyboard (after setting up your build environment):

    make pimoroni/keybow2040:default

Flashing example for this keyboard:

    make pimoroni/keybow2040:default:flash


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information. Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Hold down BOOTSEL while pressing RESET
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
