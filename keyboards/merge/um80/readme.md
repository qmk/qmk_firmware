# UM-80

![UM-80](https://i.imgur.com/JVEC4Ntl.jpeg)

UM-80 is a split keyboard in 75% layout with RGB, macro keys, OLED screen and encoder housed in PLA 3D printed cases sold by Merge. [Product page](https://mergedesign.store/products/um-80)

* Keyboard Maintainer: [duoshock](https://github.com/duoshock)
* Hardware Availability: [Merge Store](https://mergedesign.store/products/um-80)

Make example for this keyboard (after setting up your build environment):

    make merge/um80:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Esc key on the left side or '7' key on the right side and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.