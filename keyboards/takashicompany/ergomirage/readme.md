# takashicompany/ergomirage

![takashicompany/ergomirage](https://i.imgur.com/PbaRAn8h.jpg)

Ergomirage (Ergo-Mirage) is a 44-key Tron-inspired keyboard.  
Although the layout is distinctive, we aimed for a key layout that fits the shape of the human hand.  
The key layout is such that the keys can be typed by moving the fingers vertically.  

The PCB is as space-saving as possible and has a transparent design that looks like hand-wired.  
Combined with a transparent acrylic case, it can create a space where only the keys seem to float.  

Ergomirage(Ergo-Mirage)は44キーのTron配列に影響を受けたキーボードです。  
特徴的なレイアウトですが、人間の手のカタチに合うようなキー配列を目指しました。  
指を縦方向を動かすことで打鍵が可能なキー配置になっています。  

PCBは可能な限りの省スペース化がされており、まるでHand-wiredのような透明感のあるデザインとなっております。  
透明なアクリルケースと組み合わせることで、キーだけが浮き出るような空間を演出することができます。  

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: Ergomirage PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/ergomirage

Make example for this keyboard (after setting up your build environment):

    make takashicompany/ergomirage:default

Flashing example for this keyboard:

    make takashicompany/ergomirage:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
