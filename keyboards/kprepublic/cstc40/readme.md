# cstc40

A 40% hotswap ortholinear RGB keyboard from KP Republic.

* Keyboard Maintainer: [Var](https://github.com/itsvar8)
* Hardware Supported: CSTC40
* Hardware Availability: kprepublic.com

The differences between the two versions are just the rows and columns pins and the additional small pcb for the daughterboard version.

Make example for this keyboard (after setting up your build environment):

    for daughterboard version: make kprepublic/cstc40/daughterboard:default
    for single pcb version: make kprepublic/cstc40/single_pcb:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

The single_pcb uses pin A10, which apparently is a design flaw that prevent the bootloader to start every time - https://docs.qmk.fm/#/platformdev_blackpill_f4x1?id=pins-to-be-avoided. There is a simple workaround that works most of the time - press the pin key (generally the letter R) during the boot.
