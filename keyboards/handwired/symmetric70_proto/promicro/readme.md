# Pro Micro version of symmetric70_proto

![symmetric70_proto](https://i.imgur.com/Br4pH9ol.jpg)
<img width="80%" alt="matrix_74HC157d" src="https://user-images.githubusercontent.com/2170248/115988014-a3943580-a5f2-11eb-9a0a-038f7ea6a8d9.png">

A compact 70keys keyboard (prototype) designed by mtei

* Keyboard Maintainer: [mtei](https://github.com/mtei)
* Hardware Supported: Pro Micro (ATmega32U4) & 74HC157
* Hardware Availability: This is just prototype

Make example for this keyboard (after setting up your build environment):

    make symmetric70_proto/promicro:default

Flashing example for this keyboard:

    make symmetric70_proto/promicro:default:flash

Testing options: (see more options: [local_features.mk](../local_features.mk), [matrix_debug](../matrix_debug/readme.md) )

    make MTEST=mdelay0 symmetric70_proto/promicro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
