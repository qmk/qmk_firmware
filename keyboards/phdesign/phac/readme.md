# phac

![phac](https://i.imgur.com/bQdYGMf.png)

A rhythm game controller with 7 keys and 2 encoders on it.

* Keyboard Maintainer: [Xufeng Tao](https://github.com/nonameCCC)
* Hardware Supported: RP2040 minimal system
* Hardware Availability: https://m.tb.cn/h.gLFXLaX?tk=7DpL3TuPVxx (currently not available outside of mainland China)

Make example for this keyboard (after setting up your build environment):

    make phdesign/phac:default

Flashing example for this keyboard:

    make phdesign/phac:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,5) in the matrix (the START button) and plug in the controller
* **Physical reset button**: Short pin hole SW1 on the back of the PCB (not recommended as the case is not easy to open)
