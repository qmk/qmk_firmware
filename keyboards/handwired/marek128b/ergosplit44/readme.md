# ergosplit44

![ergosplit44](https://i.imgur.com/RhRIe2ah.png)

This is a handdwired split 44 key keyboard. the two sides are connectd via a custom 2x8P pin header cable.

* Keyboard Maintainer: [Marek128b](https://github.com/Marek128b)
* Hardware Supported: WaveShare RP2040-Zero
* Hardware Availability: [Open Source](https://github.com/Marek128b/Split40)

Make example for this keyboard (after setting up your build environment):

    make handwired/marek128b/ergosplit44:default

Flashing example for this keyboard:

    make handwired/marek128b/ergosplit44:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard.
* **Physical reset button**: Hold down the `BOOT` button on the RP2040-Zero, then press the `RESET` button.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.
