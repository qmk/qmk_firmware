# Palmslave

![Palmslave](https://i.imgur.com/oDluHBC.jpeg)

Palmslave is a split keyboard with 0.8u (16mm) key pitch.
The size of a single key is 80% of the size of a key on a conventional keyboard.
Although the key size is more compact than usual, it has the advantage of requiring minimal finger movement.
The number of keys is 19 keys for one hand and 38 keys for two hands.
Keyswitches are compatible with Choc v1 and Choc v2.
The board can be fitted with a key switch socket, allowing the keyswitch to be replaced according to mood or fashion.

Palmslaveは0.8u(16mm)キーピッチの分割型のキーボードです。
一つのキーの大きさが従来のキーボードのキーと比較すると80%のサイズとなっています。
通常よりコンパクトなキーサイズですが、指の動きが最小限で済むという強みがあります。
キー数は片手で19キー、両手で38キーとなります。
キースイッチはChoc v1とChoc v2に対応しています。
基板はキースイッチソケットの取り付けが可能で、気分や流行でキースイッチを付け替えることが可能です。

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: Palmslave PCB(s), x2 Pro Micro development board
* Hardware Availability: https://github.com/takashicompany/palmslave

Make example for this keyboard (after setting up your build environment):

    make takashicompany/palmslave:default

Flashing example for this keyboard:

    make takashicompany/palmslave:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
