# miniDivide MAX

![miniDivide Max](https://i.imgur.com/5xozuXDh.jpg)

miniDivide MAX is a 56-key segmented keyboard with 16mm spaced key layout.  
The keys are 80% the size of conventional keys, making this keyboard suitable for people with small hands as well as those who want to type with minimal finger movement.  
The 56-key layout makes it possible to start using this keyboard with a feel similar to a conventional keyboard.  
It is also smaller and thinner than a conventional keyboard, making it suitable for carrying around and taking up minimal space when placed on a desk.  
The split design allows you to type in a natural position.  
In addition, it is also compatible with underglow LEDs and BLE Micro Pro, so it can be reconfigured to suit the case in which it is used.  

---

miniDivide MAXは16mm間隔のキー配置を採用した56キーの分割キーボードです。  

キーが従来の80%の大きさなので、手が小さい人はもちろん最小限の指の移動で文字を打ちたい人に適したキーボードです。  

56キー配置されているため、従来のキーボードに近い使用感で使い始めることが可能です。  

また従来のキーボードよりも小さく薄いため持ち運びにも適していますし、デスクに置いた時にスペースが最小限で済むメリットもあります。  

分割型なため、自然な体勢で文字を打つことができます。  

その他、アンダーグロウLEDやBLE Micro Proなどにも対応しているため使用ケースにあわせて組み替えることが可能です。  



* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: miniDivide MAX PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/minidivide_max

Make example for this keyboard (after setting up your build environment):

    make takashicompany/minidivide_max:default

Flashing example for this keyboard:

    make takashicompany/minidivide_max:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
