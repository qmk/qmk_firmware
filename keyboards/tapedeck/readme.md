# Gowla Tapedeck

![Image of Tapedeck](https://i.ibb.co/R3JVMjM/tapedeck.jpg)

4x4 12 Key Macro Board with 60MM Slider, RGB and 2 X Rotary Encoders. For use with QMK, designed and sold by Gowla.

* Keyboard Maintainer: [Gowla](https://github.com/SamGowland/)
* Hardware Supported: Pro Micro ATmega32U4, Cherry MX Switches, Alps 60MM Slider
* Hardware Availability: [Repo](https://github.com/SamGowland/Gowla-Macro-Boards)

Make example for this keyboard (after setting up your build environment):

    make tapedeck:default
    
Flashing example for this keyboard:

    make tapedeck:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top-left key (underneath the Pro Micro) and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset**: Remove the back plate and short the `RST` and `GND` pins on the Pro Micro.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.

As a Pro Micro-compatible board, the Gowla Tapedeck uses `caterina` as its bootloader by default. Many popular Pro Micro alternatives like the Elite-C, Bit-C, Sea-Micro, Puchi-C etc should be flashed with a different bootloader such as `atmel-dfu`.

If the incorrect bootloader is specified, bootmagic reset and the `QK_BOOT` keycode will not work.

To avoid this problem, set the correct bootloader in your custom keymap's `rules.mk` file before compiling, or flash using an appropriate target (e.g. `make tapedeck:default:dfu`). See [flashing instructions and bootloader information](https://docs.qmk.fm/#/flashing) for more details.
