# ctrl-M

![ctrl-M PCB](https://brain4free.org/wiki/lib/exe/fetch.php/elektronik:modelm:img_20221218_200726.jpg?w=400&tok=05657d)

This is a configuration of QMK intended to be used with the [ctrl-M controller](https://github.com/nuess0r/ctrl-M). Many thanks to iw0rm3r, ashpil, mschwingen and all QMK contributors for working on similar projects and providing the foundation for this!

* Keyboard Maintainer: [nuess0r](https://github.com/nuess0r)
* Hardware Supported: [ctrl-M](https://github.com/nuess0r/ctrl-m)

Example how to compile for this keyboard (after setting up your build environment):

    make ibm/model_m/ctrl_m:default

Flashing example for this keyboard:

    make ibm/model_m/ctrl_m:default:flash

Or if you use the QMK tool:

    qmk compile -kb ibm/model_m/ctrl_m -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Escape key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
