# takashicompany/spreadwriter

![takashicompany/spreadwriter](https://i.imgur.com/mMAzyvUh.jpg)

"Spreadwriter" はGL516ケースに対応した50%キーボードです。  
放射状のキーレイアウトは、手を自然な形で置くことができ、楽な姿勢での打鍵を可能にしています。  

LEDを用いたキーの照明や、ロータリーエンコーダの搭載も可能です。
---
"Spreadwriter" is a 50% keyboard for the GL516 case.
The radial key layout allows for a natural hand placement and comfortable typing posture.

LED-based key illumination and a rotary encoder are also available.

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: Spreadwriter PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/spreadwriter

Make example for this keyboard (after setting up your build environment):

    make takashicompany/spreadwriter:default

Flashing example for this keyboard:

    make takashicompany/spreadwriter:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
