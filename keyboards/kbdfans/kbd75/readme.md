# KBD75

Keyboard Maintainer: QMK Community  
Hardware Supported: KBD75 PCB rev 1 and 2  
Hardware Availability:
* https://kbdfans.com/collections/75-diy-kit/products/kbd75-keyboard-set
* https://kbdfans.com/collections/75-diy-kit/products/kbd75v2-custom-keyboard-diy-kit

The KBD75 was sold through various rounds, with various PCB changes between them. 

* **Round 1 (2017)**: Black PCB - Bootmapper Client, atmega32a MCU (Use [Winkeyless.kr B.mini](../../winkeyless/bmini/) firmware)
* **Round 2 (2018)**: White PCB - Bootmapper Client, atmega32a MCU (Use [ymd75/rev1](../../ymd75/rev1/) firmware)
* **Round 3-5 (2018)**: White PCB - QMK Firmware, atmega32u4 MCU (Use KBD75 rev1 or rev2(without numpad support)) 
* **Round 6 (2019)**: White PCB with USB C - QMK Firmware, atmega32u4 MCU (Use KBD75 rev1 or rev2(with numpad support))
* **V2 (2019-)**: Same as **Round 6** (above).

Make example for this keyboard (after setting up your build environment):

    make kbdfans/kbd75/rev1:default
    make kbdfans/kbd75/rev2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
