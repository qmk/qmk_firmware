# Microdox

![boardsource Microdox](https://i.imgur.com/AliShkvl.jpg)

* Keyboard Maintainer: [Boardsource](https://github.com/daysgobye) 
* Hardware Supported: Pro Micro and compatible alternatives
* Hardware Availability: this keyboard is available from the [Boardsource store](https://boardsource.xyz/store/5f2e7e4a2902de7151494f92)

Make example for this keyboard (after setting up your build environment):

    make boardsource/microdox/v1:default
    make boardsource/microdox/v2:default

Compile `v1` firmware if you purchased your PCBs prior to April 2022.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## my notes

### build and flash

flash each side independently with the trrs cable disconnected.

press the reset button on the side of the keyboard you are flashing while it is connected via usb-c and then run the following to flash.

```sh
make boardsource/microdox:chadhs:dfu-split-left
make boardsource/microdox:chadhs:dfu-split-right
```
