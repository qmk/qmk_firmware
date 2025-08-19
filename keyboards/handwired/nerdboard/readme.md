# Nerdboard

![Nerdboard](https://imgur.com/a/96ViqlI)

*Nerdboard is a custom 29 key split ergonomic keyboard with a built in mouse.*

* Keyboard Maintainer: [Jon Hull](https://github.com/thelowprokill)
* Hardware Supported: handwired Arduino Pro Micro
* Hardware Availability: https://github.com/thelowprokill/nerdboard

Make example for this keyboard (after setting up your build environment):

    make %KEYBOARD%:default

Flashing example for this keyboard:

    make %KEYBOARD%:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
