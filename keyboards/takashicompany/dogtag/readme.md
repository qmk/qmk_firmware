# DogTag

![dogtag](https://github.com/takashicompany/dogtag/blob/master/images/qmk.jpg?raw=true)

DogTag is a compact macro pad with 9 keys.  
It is assembled from a PCB no larger than 100mm x 100mm.  
It is reversible and can be used as a split macro pad by connecting two units with a TRRS cable.  
Other features include a rotary encoder and MX sockets for hot-swapping of keyswitches.  
LED underglow is also available.  

DogTagは9キーのコンパクトなマクロパッドです。  
100mm x 100mm 以内のPCBから組み立てます。  
リバーシブルに対応しており、2台をTRRSケーブルで接続することで分割型のマクロパッドとしても使用できます。  
その他にもロータリーエンコーダの搭載やMXソケットによるキースイッチの付け替え(ホットスワップ)も可能です。  
LEDによるアンダーグロウも可能です。  

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/dogtag

Make example for this keyboard (after setting up your build environment):

    make takashicompany/dogtag:default

Flashing example for this keyboard:

    make takashicompany/dogtag:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
