# FancyAlice66

![FancyAlice66](https://i.imgur.com/kg0TUlIh.jpeg)

FancyAlice66 is a Alice layout mechanical keyboard produced by FancyTech, powered by ATM32U4.

* Keyboard Maintainer: [Adophoxia](https://github.com/Adophoxia)
* Hardware Supported: FancyAlice66 PCB (Atmega32U4)
* Hardware Availability: [AliExpress](https://www.aliexpress.com/item/1005004272392611.html) [TaoBao](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.13892e8dGQ8r0o&id=674705234595)

Make example for this keyboard (after setting up your build environment):

    make fancytech/fancyalice66:default

Flashing example for this keyboard:

    make fancytech/fancyalice66:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
