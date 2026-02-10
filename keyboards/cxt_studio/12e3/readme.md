# cxt_studio/12e3

![cxt_studio/12e3](https://i.postimg.cc/NFK8rY8N/M5rtTSP.png)

3x4 ortho layout, with 3 encoders.

* Keyboard Maintainer: [muge](https://github.com/muge)
* Hardware Supported: CXT Studio 12E3
* Hardware Availability: AliExpress, Taobao

Make example for this keyboard (after setting up your build environment):

    make cxt_studio/12e3:default

Flashing example for this keyboard:

    make cxt_studio/12e3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB, located under the large encoder, on the right side
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available. It is included in the default layout
