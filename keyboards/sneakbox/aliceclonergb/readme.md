# Sneakbox Alice Clone RGB PCB

![Sneakbox Alice Clone RGB PCB](https://i.imgur.com/pMZNqLXl.jpg)

An Alice-compatible PCB with hotswap with pushbutton rotary encoder socket placed at the top left key position. This PCB is the successor to the v3 AliceClone PCB and features RGB underglow lighting along with revised hardware components.

* Keyboard Maintainer: [mujimanic](https://github.com/mujimanic)
* Hardware Supported: Any Alice-layout case.
* Hardware Availability: [sneakbox.design](https://sneakbox.design/products/sneakbox-alice-hotswap-pcbs)

Make example for this keyboard (after setting up your build environment):

    make sneakbox/aliceclonergb:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key in the nevigation cluster (Escape key) and plug in the keyboard
* **Physical reset button**: Briefly press the small metal button on the back of the PCB
* **Keycode in layout**: Press and hold the key next to the right split spacebar (to the right of the spacebar) and then press the End key (located on the bottom of the four-key navigation cluster)
