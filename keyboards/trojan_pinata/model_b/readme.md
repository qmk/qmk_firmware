# Model-B

A 75% keyboard based on the RP2040.

* Keyboard Maintainer: [Brian Hill](https://github.com/TrojanPinata)
* Hardware Supported: [GitHub](https://github.com/TrojanPinata/Model-B)

## Revisions

At the current moment there is only one variant of the Model-B, the rev-0 (aka the prototype board). Any others are clones and may not have the exact firmware requirements.

## Building and Flashing

Make example for this keyboard (after setting up your build environment):

    make trojan_pinata/model-b/rev0:default
    
Flashing example for this keyboard:

    make trojan_pinata/model-b/rev0:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear the emulated EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Hold down the `BOOTSEL` button on the Pi Pico, then either plug the board in or press the `RESET` button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. In the pre-supplied keymaps it is on the second layer, replacing the Esc key.

After entering the bootloader through one of the three methods above, the keyboard will appear as a USB mass storage device named `RPI-RP2`. If the CLI is unable to find this device, the compiled `.uf2` file can be manually copied to it. The keyboard will reboot on completion with the new firmware loaded.
