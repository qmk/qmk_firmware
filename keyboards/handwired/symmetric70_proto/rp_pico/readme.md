#  Raspberry Pi Pico version of symmetric70_proto

![symmetric70_proto](https://user-images.githubusercontent.com/2170248/201344543-9499fa47-40f6-40fe-8e4d-aa274a7c9935.png)

A compact 70keys keyboard (prototype) designed by mtei

* Keyboard Maintainer: [mtei](https://github.com/mtei)
* Hardware Supported: Raspberry Pi Pico
* Hardware Availability: This is just prototype

Make example for this keyboard (after setting up your build environment):

    make handwired/symmetric70_proto/rp_pico/normal:default
    make handwired/symmetric70_proto/rp_pico/boost:default

Flashing example for this keyboard:

    make handwired/symmetric70_proto/rp_pico/normal:default:flash
    make handwired/symmetric70_proto/rp_pico/boost:default:flash

Testing options: (see more options: [local_features.mk](../local_features.mk), [matrix_boost](../matrix_boost/readme.md))

    make MTEST=mdelay0 handwired/symmetric70_proto/rp_pico/normal:default:flash
    make MTEST=mdelay0 handwired/symmetric70_proto/rp_pico/boost:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
