# MultipleGlove

![MultipleGlove](https://github.com/ambergon/MultipeGlove/blob/master/img/1.jpg)
![MultipleGlove](https://github.com/ambergon/MultipeGlove/blob/master/img/2.jpg)
![MultipleGlove](https://github.com/ambergon/MultipeGlove/blob/master/img/6.jpg)

This keyboard was strongly influenced by the text editor Vim and the Keyball61 by Shirogane Labs.
The emphasis is on the home position of the left hand and access to the three rotary encoders without moving the hand significantly.
this keyboard specialize in 0-15 layer switching.


* Keyboard Maintainer: [ATSUTO_NAKAYAMA](https://github.com/ambergon)
* Hardware Supported: Pro Micro
* Hardware Availability: [Here](https://github.com/ambergon/MultipeGlove/tree/master#%E3%82%AD%E3%83%83%E3%83%88%E3%81%AE%E8%B2%A9%E5%A3%B2%E5%A0%B4%E6%89%80)

Make example for this keyboard (after setting up your build environment):

## build hex file
```.sh
make ambergon/MultipleGlove:default
```

## flash hex file
```.sh
make ambergon/MultipleGlove:default:flash
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
