# suika27melo
(English Follows Japanese)

## 概要
![suika27melo1](https://i.imgur.com/iFz3c1U.jpg)
![suika27melo2](https://i.imgur.com/xR7KpVR.jpg)

suika27meloは2オクターブのピアノ鍵盤型マクロキーパッドです。
通常のマクロキーパッドとしても使えるほか、MIDIキーボードとしてDAWソフトの入力や演奏に使用できます。

* 制作 : すいか技研 （Website: https://suikagiken.net GitHub: [suikagiken](https://github.com/suikagiken) ）
* 販売 : すいか技研の[booth](https://suikagiken.booth.pm/)にて販売予定です

## ビルドガイド

[こちら](https://github.com/suikagiken/suika27melo/blob/main/buildguide_1.1.md)からご覧下さい。

---

## Overview

suika27melo is a 2-octave piano shaped macro keypad.
You can use it as a normal macro keypad, or use it as a MIDI keyboard for DAW software input and musical performance.

* Keyboard Maintainer: [suikagiken](https://github.com/suikagiken)
* Hardware Availability: Available at [booth](https://suikagiken.booth.pm/) soon.

Make example for this keyboard (after setting up your build environment):

    make suikagiken/suika27melo:default

Flashing example for this keyboard:

    make suikagiken/suika27melo:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
