# Pro Micro version of symmetric70_proto

![sym70_promicro](https://user-images.githubusercontent.com/2170248/204003678-8a9316cb-b9c1-4bf3-a05a-264c31bbc3e1.png)
<img width="50%" alt="matrix_74HC157d" src="https://user-images.githubusercontent.com/2170248/115988014-a3943580-a5f2-11eb-9a0a-038f7ea6a8d9.png"> <img width="40%" alt="sym70_promicro_zoom" src="https://user-images.githubusercontent.com/2170248/204003760-bf16bc04-c5fa-46d1-bece-a0815189e1fb.png">

A compact 70keys keyboard (prototype) designed by mtei

* Keyboard Maintainer: [mtei](https://github.com/mtei)
* Hardware Supported: Pro Micro (ATmega32U4) & 74HC157
* Hardware Availability: This is just prototype

Make example for this keyboard (after setting up your build environment):

    make handwired/symmetric70_proto/promicro/normal:default
    make handwired/symmetric70_proto/promicro/boost:default
    make handwired/symmetric70_proto/promicro/fast:default

Flashing example for this keyboard:

    make handwired/symmetric70_proto/promicro/normal:default:flash
    make handwired/symmetric70_proto/promicro/boost:default:flash
    make handwired/symmetric70_proto/promicro/fast:default:flash

Testing options: (see more options: [local_features.mk](../local_features.mk), [matrix_boost](../matrix_boost/readme.md) and [matrix_fast](../matrix_fast/readme.md) )

    make MTEST=mdelay0 handwired/symmetric70_proto/promicro/normal:default:flash
    make MTEST=mdelay0 handwired/symmetric70_proto/promicro/boost:default:flash
    make MTEST=mdelay0 handwired/symmetric70_proto/promicro/fast:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
