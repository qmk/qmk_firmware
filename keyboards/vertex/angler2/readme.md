# angler2
A customizable soldering 80% keyboard.

* Keyboard Maintainer: [Vertex](https://github.com/Vertex-kb)
* Hardware Supported: AngleR2
* Hardware Availability: [Vertex](https://github.com/Vertex-kb)

Make example for this keyboard (after setting up your build environment):

    make Vertex/AngleR2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down esc in the keyboard then replug
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
