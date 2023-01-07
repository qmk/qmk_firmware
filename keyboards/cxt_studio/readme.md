# cxt_studio

![cxt_studio](https://gist.githubusercontent.com/ColinKinloch/cb49a8b42fcd07445232a26f562f3b9d/raw/ff9ac62884d724811f634c07e44c737a148181cc/cxt_studio.jpg)

3x4 ortho rgb lighting 4 knobs.

* Keyboard Maintainer: [Colin Kinloch](https://github.com/ColinKinloch)
* Hardware Supported: CXT-Studio
* Hardware Availability: AliExpress. I think the manufacturer is on Taobao.

Make example for this keyboard (after setting up your build environment):

    make cxt_studio:default

Flashing example for this keyboard:

    make cxt_studio:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
