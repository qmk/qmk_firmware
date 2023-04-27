# phantagom/baragon

[Baragon](https://en.wikipedia.org/wiki/Baragon) is a fictional monster, or kaiju, which first appeared in Ishirō Honda's 1965 film Frankenstein vs. Baragon.

![phantagom/baragon](https://i.imgur.com/17RkGUPh.jpeg)

A macro pad, 3x3 with rgb ring and rotary encoder, via compatible. Keys can be rotated, so macropad is usable at different angles.

* Keyboard Maintainer: [Dennis Kruyt](https://github.com/dkruyt)
* Project page: [baragon](https://github.com/dkruyt/mk/tree/main/baragon)
* Hardware Supported: *RP2040-Zero*

Make example for this keyboard (after setting up your build environment):

    make phantagom/baragon:default

Flashing example for this keyboard:

    Copy the uf2 file to the rp2040 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader mode  in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the top of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
