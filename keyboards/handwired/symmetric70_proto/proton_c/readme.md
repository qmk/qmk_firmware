# Proton C version of symmetric70_proto

![symmetric70_proto](https://i.imgur.com/SCtlXOS.jpg)

A compact 70keys keyboard (prototype) designed by mtei

* Keyboard Maintainer: [mtei](https://github.com/mtei)
* Hardware Supported: Proton C (STM32F303CCT6)
* Hardware Availability: This is just prototype

Make example for this keyboard (after setting up your build environment):

    make handwired/symmetric70_proto/proton_c/normal:default
    make handwired/symmetric70_proto/proton_c/fast:default

Flashing example for this keyboard:

    make handwired/symmetric70_proto/proton_c/normal:default:flash
    make handwired/symmetric70_proto/proton_c/fast:default:flash

Testing options: (see more options: [local_features.mk](../local_features.mk), [matrix_debug](../matrix_debug/readme.md) and [matrix_fast](../matrix_fast/readme.md) )

    make MTEST=mdelay0 handwired/symmetric70_proto/proton_c/normal:default:flash
    make MTEST=mdelay0 handwired/symmetric70_proto/proton_c/fast:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
