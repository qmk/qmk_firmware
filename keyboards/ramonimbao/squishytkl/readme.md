# SquishyTKL

![SquishyTKL](https://i.imgur.com/b04ooQ7l.png)

A stacked acrylic o-ring gasket mounted TKL-sized keyboard with a twist!

* Keyboard Maintainer: [Ramon Imbao](https://github.com/ramonimbao)
* Hardware Supported: STM32F103RB

Make example for this keyboard (after setting up your build environment):

    make ramonimbao/squishytkl:via

Flashing example for this keyboard:

    dfu-util -d 1eaf:0003 -a 2 -D path/to/ramonimbao_squishytkl_via.bin

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
