# Coffeevan

![Coffeevan](https://imgur.com/1VDxDmp.jpeg)

Coffeevan is a drop-in replacement PCB for MiniVan cases. Coffeevan supports the Minisub split-space and JetVan 6.25u spacebar layout.

* Keyboard Maintainer: [Coffee Break Keyboards](https://github.com/CoffeeBreakKeyboards)
* Hardware Supported: Coffeevan
* Hardware Availability: [Coffee Break Keyboards](https://www.cbkbd.com/product/minivan-kits)

Make example for this keyboard (after setting up your build environment):

    make cbkbd/coffeevan:default

Flashing example for this keyboard:

    make cbkbd/coffeevan:default:flash

See the [build environment setup](getting_started_build_tools) and the [make instructions](getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available