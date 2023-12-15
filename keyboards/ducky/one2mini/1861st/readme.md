# one2mini

![one2mini](http://www.duckychannel.com.tw/page-en/One_2_Mini_RGB/images/One2_Mini_01_02.jpg)

A 60% keyboard featuring per-key RGB LEDs.

* Keyboard Maintainer: [Reza Jelveh](https://github.com/fishman)
* Hardware Supported: Ducky One 2 Mini RGB / NUC123SD4AN0 / MBI5042GP
* Hardware Availability: [Ducky Channel](http://www.duckychannel.com.tw/page-en/One_2_Mini_RGB/)

Make example for this keyboard (after setting up your build environment):

    make ducky/one2mini:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

RGB LEDs are currently disabled until the driver is merged.

This firmware was tested on the duckyon2mini 1861ST version. To enter the 1861ST bootloader to flash you can boot the keyboard while holding D+L.

There are then two ways to flash the keyboard:

    pip install --user nuvoton-isp
    nuvoisp -f ducky_one2mini_default.bin

Alternatively you can use elfmimi's [nu-isp-cli](https://lib.rs/crates/nu-isp-cli) which is more complete than nuvoisp and allows flashing .hex files as well.

    cargo install nu-isp-cli
    nu-isp-cli flash ducky_one2mini_default.bin
