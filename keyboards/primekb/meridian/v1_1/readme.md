# Meridian v1.1 PCB with KTR-1010RGBC-1812-4 RGB LEDs for indicators

![Meridian](https://cdn.shopify.com/s/files/1/2016/1211/files/IMG_0934.JPG?v=1612649071)

* Keyboard Maintainer: [Holten Campbell](https://github.com/holtenc)
* Hardware Supported: STM32F072CBT6 with KTR-1010RGBC-1812-4 LEDs

V1.1 PCBs are generally identified by:
* Having a holographic sticker on the front reading "QC3" or "QC5".
* By visually identifying which LEDs you have in reference to the abvove image. 

Enter bootloader mode by either:
* Pressing the physical reset button on the back of the PCB
* Holding left spacebar and pressing escape (assuming default keymap)

Make example for this keyboard (after setting up your build environment):

    make primekb/meridian/v1.1:default
    make primekb/meridian/v1.1:via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).