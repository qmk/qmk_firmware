# Shisaku

![shisaku](https://i.imgur.com/42H1h1dh.jpg)

A 40% alice-like keyboard assembled only with THT components, including the option for a solenoid.

## General info

* Keyboard Maintainer: [Arturo Avila](https://github.com/ADPenrose)
* Hardware Supported: Shisaku v1 PCB
* Hardware Availability: [Arturo Avila](https://github.com/ADPenrose)

Make example for this keyboard (after setting up your build environment):

    make adpenrose/shisaku:default

Flashing example for this keyboard:

    make adpenrose/shisaku:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold down the button labeled "BOOT" and briefly press the button labeled "RESET" on the back of the PCB. To exit the bootloader mode, briefly press the button labeled "RESET" once more.
* **Keycode in layout**: Press the key mapped to "QK BOOT" if it is available
