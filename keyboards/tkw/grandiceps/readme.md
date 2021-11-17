# grandiceps

![grandiceps](https://i.imgur.com/FMtsboVl.jpg)

ARM split keyboard with RGB underglow and encoders.

* Keyboard Maintainer: [vattern](https://github.com/vattern)
* Hardware Supported: f411 blackpill
* Hardware Availability: [grandiceps](https://github.com/vattern/grandiceps)

There are two versions of the Grandiceps. Please use the appropriate firmware for your board.

* Revision 2 has I2C eeprom and support for a Pimoroni trackball.

Make example for this keyboard (after setting up your build environment):

    make tkw/grandiceps:default
    make tkw/grandiceps/rev2:default

Flashing example for this keyboard:

    make tkw/grandiceps:default:flash
    make tkw/grandiceps/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset buttons**: Hold down the BOOT0 button and then briefly press the NRST button on the BlackPill PCB.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
