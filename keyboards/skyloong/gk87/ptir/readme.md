# GK87 PTIR Keyboard

![GK87 PTIR ANSI](https://i.imgur.com/TYx22dhh.jpg)
![GK87 PTIR ISO](https://i.imgur.com/RFngtv6h.jpg)

## The PCB features:
* QMK & VIA compatibility
* RGB Matrix backlight
* Use PTIR switches instead of mechanical switches to increase the service life and reliability of switches.


The following is the QMK Firmware for the Destop 87% keylayout -  designed by Dongguan Jizhi Electronic Technology Co., Ltd

* Keyboard Maintainer: [JZ-Skyloong](https://github.com/JZ-skyloong)
* Hardware Supported: DestopPCB for Skyloong keylayout 85%, STM32F103C8T6
* Hardware Availability: http://www.skyloong.com.cn  https://skyloong.vip

Make example for this keyboard (after setting up your build environment):

    make skyloong/gk87/ptir/ansi:default
    make skyloong/gk87/ptir/iso:default

Flashing example for this keyboard:

    make skyloong/gk87/ptir/ansi:default:flash
    make skyloong/gk87/ptir/iso:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
