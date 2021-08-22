# TypeTheory Keyboard

![Picture of TypeTheory Keyboard](https://typetheory.co.uk/thumb/front.jpg)

The [TypeTheory Keyboard](https://typetheory.co.uk/) is a split ergonomic keyboard inspired by the [Dactyl-Manuform](https://github.com/tshort/dactyl-keyboard) and the Kinesis Advantage2. It uses two Puchi-C microcontrollers, with physical reset buttons.

* Keyboard Maintainer: Marius Gavrilescu
* Hardware Supported: TypeTheory Keyboard
* Hardware Availability: https://typetheory.co.uk

Make example for this keyboard (after setting up your build environment):

    make typetheory:default

Flashing example for this keyboard:

    make typetheory:default:dfu-split-left
    make typetheory:default:dfu-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the Puchi-C
* **Keycode in layout**: Press the key mapped to `RESET` (`RAISE`+Right Shift on the default keymap)
