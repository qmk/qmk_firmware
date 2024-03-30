# Rookey

![takashicompany/rookey](https://i.imgur.com/kLQDeZZh.jpg)

Rookey, as the name implies, is a DIY keyboard "Rookie" creation.

With its small number of parts and simple structure, it can be easily completed even by first-time assemblers.

Despite its small size, it can be used as a 9-key macro pad, and a rotary encoder can also be attached.

It can be used not only as a first unit, but also as a long-lasting unit.

---

Rookeyは名前の通り、DIYキーボードの"Rookie"のために作られた一作です。

部品数が少なく、構造がシンプルなため初めて組み立てる人でも容易に完成させることができます。

小さいながらも9キーのマクロパッドとして使用ができる上に、ロータリーエンコーダの取り付けも可能です。

初めての一台としてはもちろん、永く使い続ける一台としても愛用することができます。

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: Rookey PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/rookey

Make example for this keyboard (after setting up your build environment):

    make takashicompany/rookey:default

Flashing example for this keyboard:

    make takashicompany/rookey:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
