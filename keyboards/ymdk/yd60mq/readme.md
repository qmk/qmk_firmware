# YD60MQ

![YD60MQ PCB](https://i.imgur.com/4X8km1q.jpeg)

Multi-layout, Soldered, 60% PCB compatible with GH60 cases.

* Keyboard Maintainer: QMK Community
* Hardware Supported: YD60MQ PCB
    * 12led (unknown revision number, has 12 RGB LEDs on the back) – _default variant_
    * 16led (unknown revision number, has 16 RGB LEDs on the back)
* Hardware Availability: [YMDK](https://ymdkey.com/)

Make example for this keyboard (after setting up your build environment):

```sh
make ymdk/yd60mq:default        # builds the 12 LED variant
make ymdk/yd60mq/12led:default  # also builds the 12 LED variant
make ymdk/yd60mq/16led:default  # builds the 16 LED variant
```

The keyboard uses a DFU bootloader. To make a keymap and use dfu to flash it:

```sh
make ymdk/yd60mq:default:flash        # builds and flashes the 12 LED variant
make ymdk/yd60mq/12led:default:flash  # also builds and flashes the 12 LED variant
make ymdk/yd60mq/16led:default:flash  # builds and flashes the 16 LED variant
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
