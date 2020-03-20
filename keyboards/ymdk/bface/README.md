# The YMDK Bface

![ymdk_bface](https://i.imgur.com/qhFxN0g.jpg)

A 60% keyboard that runs ps2avrgb natively and fits the popular GH60 form factor. Another "bfake" or clone of the original B.face PCB by [Winkeyless](https://winkeyless.kr/product/b-face-x2-pcb/). This PCB has slightly different switch matrix than the origninal B.face, and is also different than the bfake. It commonly comes as the PCB in 60% keyboard kits sold by YMDK on Aliexpress.

* Keyboard Maintainer: QMK Community
* Hardware Supported: White Bface Mini USB PCB with no RGB.
* Hardware Availability: [Shenzhen YMD Tech Co. (YMDK) on Aliexpress](https://www.aliexpress.com/item/32799437588.html)

Make example for this keyboard (after setting up your build environment):

    make ymdk/bface:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make ymdk/bface:default:flash

This board has a pair of jumper holes on the left edge of the PCB marked "Jb", near TAB and CAPS LOCK. If you short the contacts with tweezers or wire the board will enter into the bootloader and you can flash it.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
