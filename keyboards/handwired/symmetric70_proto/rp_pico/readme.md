#  Raspberry Pi Pico version of symmetric70_proto

![sym70_pico](https://user-images.githubusercontent.com/2170248/204007204-2196b9ce-c50d-4461-a64a-1e775c2e1cc1.png)
<img width="45%" alt="sym70_pico_zoom" src="https://user-images.githubusercontent.com/2170248/204007369-5e384096-85c5-49ac-8e3f-18caa0d50fc4.png"> <img width="45%" alt="sym70_pico_zoom2" src="https://user-images.githubusercontent.com/2170248/204007392-fbedcfbe-1f5c-4998-adbd-08e2e82b9a2e.png">


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
