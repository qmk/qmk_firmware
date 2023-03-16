# atlantis/ps17

![atlantis/ps17](https://i.imgur.com/5qGIv2Kh.jpg)

A 17-key hot-swap numpad/macropad with an EC11 clickable rotary encoder (knob) and RGB backlight and underglow

* Keyboard Maintainer: [mjbogusz](https://github.com/mjbogusz)
* Hardware Supported: Atlantis PS17
* Hardware Availability: [AliExpress, SpiderIsland Tech Co., Ltd Store](https://www.aliexpress.com/item/1005003058226085.html)
* Additional photos:
    * [Full size](https://i.imgur.com/5qGIv2K.jpg)
    * [PCB front](https://i.imgur.com/OmGBqvC.jpg)
    * [PCB back](https://i.imgur.com/rvoZZ5f.jpg)

Make example for this keyboard (after setting up your build environment):

    make atlantis/ps17:default

Flashing example for this keyboard:

    make atlantis/ps17:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Attributions

Pin mapping and LED physical layout based on [Solartempest work](https://github.com/solartempest/qmk_firmware/tree/master/keyboards/solartempest/ps17)
