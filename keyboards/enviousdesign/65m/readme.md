# EnvKB 65M

![image of EnvKB 65M PCB](https://i.imgur.com/3d76sz9h.png)

A low cost 65% kit featuring split space and an attempt at fitting a standard keycap set.

* Keyboard Maintainer: [Envious-Data](https://github.com/envious-data)
* Hardware Supported: EnvKB 65M (Pi Pico)
* Hardware Availability: [Mechboards](https://mechboards.co.uk/products/envkb-65-kit), [GitHub](https://github.com/Envious-Data/Env-KB65M)

Make example for this keyboard (after setting up your build environment):

    make enviousdesign/65m:default

Flashing example for this keyboard:

    make enviousdesign/65m:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear the emulated EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset**: Hold down the `BOOTSEL` button on the Pi Pico, then either plug the board in or press the `RESET` button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. In the pre-supplied keymaps it is on the second layer, replacing the Control key in the bottom-left.

After entering the bootloader through one of the three methods above, the keyboard will appear as a USB mass storage device named `RPI-RP2`. If the CLI is unable to find this device, the compiled `.uf2` file can be manually copied to it. The keyboard will reboot on completion with the new firmware loaded.

