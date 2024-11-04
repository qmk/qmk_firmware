# mao ds 17r2

* Keyboard Maintainer: [CZMAO](https://github.com/smollchungus)
* Hardware Supported: DS17R2 PCB
* Hardware Availability: [Taobao](https://item.taobao.com/item.htm?ft=t&id=819874589305&sku_properties=5919063:3266779;122216346:21959;122216808:10491261)

Make example for this keyboard (after setting up your build environment):

    make czmao/ds17r2:default

Flashing example for this keyboard:

    make czmao/ds17r2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
