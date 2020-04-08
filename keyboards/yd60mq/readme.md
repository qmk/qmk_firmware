# YD60MQ

![YD60MQ PCB](https://ae01.alicdn.com/kf/HTB1PVQ2X_HuK1RkSndVq6xVwpXaO.jpg)

Customizable 60% PCB by [YMDK](https://ymdk.aliexpress.com/store/429151?spm=2114.10010108.0.0.3ab23641lIkgzm).

* Keyboard Maintainer: QMK Community
* Hardware Supported: YD60MQ PCB
    * 12led (unknown revision number, has 12 RGB LEDs on the back) – _default version_
    * 16led (unknown revision number, has 16 RGB LEDs on the back)
* Hardware Availability: [YMDK on AliExpress](https://www.aliexpress.com/i/32869207240.html)

Make example for this keyboard (after setting up your build environment):

    make yd60mq:default        # builds the 12 LED version
    make yd60mq/12led:default  # also builds the 12 LED version
    make yd60mq/16led:default  # builds the 16 LED version

The keyboard uses a DFU bootloader. To make a keymap and use dfu to flash it:

    make yd60mq:default:flash        # builds and flashes the 12 LED version
    make yd60mq/12led:default:flash  # also builds and flashes the 12 LED version
    make yd60mq/16led:default:flash  # builds and flashes the 16 LED version

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
