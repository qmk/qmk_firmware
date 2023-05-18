# phantagom/varan

[Varan](https://en.wikipedia.org/wiki/Varan) is a fictional monster, or kaiju, which first appeared in the 1958 film Varan the Unbelievable

![phantagom/varan](https://i.imgur.com/EuGAMyeh.jpeg)
![phantagom/varan](https://i.imgur.com/zO2ju9Ah.jpeg)

A numpad with RGB strip based on a RP2040 controller.

* Keyboard Maintainer: [Dennis Kruyt](https://github.com/dkruyt)
* Project page: [varan](https://github.com/dkruyt/mk/tree/main/varan)
* Hardware Supported: *RP2040-Zero*

Make example for this keyboard (after setting up your build environment):

    make phantagom/varan:default

Flashing example for this keyboard:

    make phantagom/varan:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
