# Vega Hotswap Aftermarket Replacement by FJLaboratories

The following is the QMK Firmware for the Vega Hotswap aftermarket replacement PCB by FJLaboratories.
* Keyboard Maintainer: FJLaboratories
* Hardware Supported: Vega

Make example for this keyboard (after setting up your build environment):

    make fjlabs/vega:default

Flashing example for this keyboard:

    make fjlabs/vega:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard.
* **Physical reset button**: Press the reset button at the back of the PCB near the microcontroller.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available. In the pre-supplied keymaps it is on the second layer, replacing the right bracket.