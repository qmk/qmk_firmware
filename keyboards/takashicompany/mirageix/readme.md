# MirageiX

![takashicompany/mirageix](https://i.imgur.com/93krKWQ.jpeg)

MirageiX is a 44-key integrated keyboard.
The PCB has been trimmed to the limit to create a visual appearance in which only the keycaps seem to float.
By using a transparent acrylic case, you can enjoy a mirage-like keyboard expression.
The key layout is based on the TRON keyboard layout, making typing smoother than it looks.

Keyswitches are fixed with sockets, allowing easy replacement of keyswitches.

MirageiXは44キーの一体型キーボードです。
PCBを極限まで切り詰めたことでキーキャップのみが浮き出るようなビジュアルを実現しました。
透明なアクリルケースを用いることで蜃気楼のようなキーボード表現が楽しめます。
キー配列もTRONというキーボードの配置を参考にしているため、見た目以上にスムーズなタイピングを実現します。

キースイッチはソケットで固定されるため、キースイッチの交換を容易に行えます。

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: MirageiX PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/mirageix

Make example for this keyboard (after setting up your build environment):

    make takashicompany/mirageix:default

Flashing example for this keyboard:

    make takashicompany/mirageix:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
