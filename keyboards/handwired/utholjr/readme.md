UtholJR
===
Handwired 4x12 ortholinear keyboard with OLED and encoder support based on the STM32F01CCuB

Keyboard Maintainer: Uthol

Hardware Supported: Rev1

Hardware Availability:Me

Make example for this keyboard (after setting up your build environment):

    make handwired/utholjr/rev1:default

Install examples:

    make handwired/utholjr/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Use all your cpu cores to compile:

    export MAKEFLAGS="-j$(nproc) --output-sync". 
