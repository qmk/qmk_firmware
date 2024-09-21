# miniDivide

![miniDivide](https://i.imgur.com/x91x9yjh.jpg)

miniDivide is a split keyboard with 0.8u (16mm) key pitch.
The size of a single key is 80% of that of a conventional keyboard key.
Although the key size is more compact than usual, it has the advantage of requiring minimal finger movement.
The number of keys is 19 keys for one hand and 38 keys for two hands.

It is small and thin, making it easy to carry around.
The option to mount a coin cell battery on the PCB is available so that the BLE Micro Pro can be installed.
OLED can also be mounted.

miniDivideは0.8u(16mm)キーピッチの分割型のキーボードです。
一つのキーの大きさが従来のキーボードのキーと比較すると80%のサイズとなっています。
通常よりコンパクトなキーサイズですが、指の動きが最小限で済むという強みがあります。
キー数は片手で19キー、両手で38キーとなります。

小さく、薄いので持ち運びにも便利です。
またBLE Micro Proを搭載できるよう、コイン電池をPCBに搭載するオプションが可能です。
OLEDも搭載できます。

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/minidivide

Make example for this keyboard (after setting up your build environment):

    make takashicompany/minidivide:default

Flashing example for this keyboard:

    make takashicompany/minidivide:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
