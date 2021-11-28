# heavy_left

![heavy_left](https://github.com/takashicompany/heavy_left/blob/master/images/qmk.jpg)

This is a 95-key split type Japanese keyboard.  
It has a numeric keypad on the left hand side, which can be used not only for entering numbers but also as a dedicated macro pad.  
It also supports key switch replacement with MX sockets and LED underglow.  

95キーの分割型の日本語配列のキーボードです。  
左手側にテンキーが備え付けられており、数字の入力だけでなく専用のマクロパッドとしても使用が可能です。  
MXソケットによるキースイッチの付替えや、LEDによるアンダーグロウにも対応しています。  

* Keyboard Maintainer: [takashicompany](https://github.com/yourusername)
* Hardware Supported: PCB, Pro Micro 
* Hardware Availability: https://github.com/takashicompany/heavy_left

Make example for this keyboard (after setting up your build environment):

    make takashicompany/heavy_left:default

Flashing example for this keyboard:

    make takashicompany/heavy_left:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
