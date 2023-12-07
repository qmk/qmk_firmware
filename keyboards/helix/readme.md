# Helix

![image](https://i.imgur.com/fpHr3Bqh.jpg)

* Keyboard Maintainer: [MakotoKurachi](https://github.com/MakotoKurauchi)
* Hardware Supported: Pro Micro or compatible alternative with Helix PCBS
* Hardware Availability: [Github](https://github.com/MakotoKurauchi/helix), [Yushakobo Shop](https://shop.yushakobo.jp)

Make example for this keyboard (after setting up your build environment):

    make helix/pico:default
    make helix/rev2:default
    make helix/rev3_4rows:default
    make helix/rev3_5rows:default


Flashing example for this keyboard:

    make helix/pico:default:flash
    make helix/rev2:default:flash
    make helix/rev3_4rows:default:flash
    make helix/rev3_5rows:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix 
* **Physical reset button**: If using a promicro, double tap reset button (or short GND & RST pins). If using Elite-C/similar, press reset button once. If using RP2040 replacement, hold BOOT button while plugging keyboard in.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
