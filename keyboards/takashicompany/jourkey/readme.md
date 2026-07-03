# Joukey

![takashicompany/jourkey](https://i.imgur.com/pCrTbKn.jpeg)

Jourkey was designed as “a keyboard for taking pictures with scenery while traveling.

The layout is like a smaller version of a traditional keyboard.
Decorate it with your favorite keycaps and case to make it your travel companion.

Of course, it can also be used as a macro pad.

---

Jourkeyは「旅先で景色と写真を撮るためのキーボード」としてデザインされました。

従来のキーボードを小さくしたようなレイアウトです。
お気に入りのキーキャップやケースでデコレーションして貴方の旅のお供になります。

もちろん、マクロパッドとして使用することも可能です。

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: Jourkey PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/jourkey

Make example for this keyboard (after setting up your build environment):

    make takashicompany/jourkey:default

Flashing example for this keyboard:

    make takashicompany/jourkey:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
