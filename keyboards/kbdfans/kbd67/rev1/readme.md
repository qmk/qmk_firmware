# KBD67 rev1

65% keyboard with RGB underglow originally sold for the Tofu 65 and Tada 68 keyboards.

* Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)
* Hardware Supported: KBD67 PCB (Sometimes sold under the name "KBD65")
* Hardware Availability: KBDFans [Keyboard Kit](https://kbdfans.cn/products/coming-soon-kbd67-mechanical-keyboard-diy-kit), [PCB](https://kbdfans.cn/collections/65/products/kbd65-65-custom-mechanical-keyboard-pcb)

Make example for this keyboard (after setting up your build environment):

    make kbdfans/kbd67/rev1:default

Flashing example for this keyboard:

    make kbdfans/kbd67/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
