# Keybow 2040

The [Pimoroni Keybow 2040][keybow2040] is a 16 key mechanical macropad
controlled by a Raspberry Pi RP2040, with Kailh hot swap sockets and
per key RGB lighting, in a decorative FR4 sandwich. The Keybow 2040 is
also known by its codename Venus Dust, or its product codes of the
form PIM56x.

* Keyboard Maintainer: [Tony Finch](https://github.com/fanf2)
* Hardware Supported: Keybow 2040
* Hardware Availability: [Pimoroni][keybow2040]

[keybow2040]: https://shop.pimoroni.com/products/keybow-2040

Make example for this keyboard (after setting up your build environment):

    make pimoroni/keybow2040:default

Flashing example for this keyboard:

    make pimoroni/keybow2040:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information. Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## bootloader

The procedure to flash the firmware is similar to other RP2040
devices. You can enter the bootloader in two ways:

  * **Vulcan nerve pinch**: hold down BOOTSEL while pressing RESET
    (not so great if you have configured BOOTSEL to do something)

  * **Mr Resetti double-tap**: press RESET twice quickly
    (only works when running the QMK firmware)

The Pimoroni web site has [instructions for reinstalling CircuitPython
on the Keybow 2040](https://learn.pimoroni.com/article/circuitpython-and-keybow-2040)


## notes

  * The BOOTSEL button doubles as a 17th configurable key. The
    RP2040's ROM firmware implements the BOOTSEL feature, so there's
    no need for QMK's bootmagic feature.

  * The default keymap has F13 - F20 on the top half of the board
    (nearest the USB socket), and a navigation cluster (arrows, home,
    end, page up/down) on the bottom half. The BOOTSEL button changes
    the RGB matrix mode.

  * The Keybow 2040 CircuitPython firmware uses VID = 0x16D0, PID = 0x08C6,
    but this QMK firmware has different USB IDs to avoid confusing drivers:
    VID = 0x5069 ('Pi'), PID = 0x4784 (4 'x' 4)


## resources

Here are some links to the information I used when configuring QMK for the Keybow 2040.

  * [Piomoroni Keybow 2040 product page](https://shop.pimoroni.com/products/keybow-2040)
  * [Keybow 2040 assembly instructions](https://learn.pimoroni.com/article/assembling-keybow-2040)

Places to find information about the Keybow 2040 hardware:

  * [schematic](https://cdn.shopify.com/s/files/1/0174/1800/files/keybow_2040_schematic.pdf)
      * contains most of the information that can also be gleaned from the CircuitPython support

  * Pimoroni user-friendly CircuitPython libraries
      * [old](https://github.com/pimoroni/keybow2040-circuitpython) and [new](https://github.com/pimoroni/pmk-circuitpython)
      * these are wrappers around the low-level support below

  * [CircuitPython hardware support](https://github.com/adafruit/circuitpython/blob/main/ports/raspberrypi/boards/pimoroni_keybow2040/)
      * defines map from hardware feature names (e.g. `SW15`) to the way they are accessed (e.g. GPIO6)

  * [CircuitPython IS31FL3731 driver](https://github.com/adafruit/Adafruit_CircuitPython_IS31FL3731/blob/main/adafruit_is31fl3731/keybow2040.py)
      * defines the RGB matrix layout
