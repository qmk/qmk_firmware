
# SmartPro

*A short description of the keyboard/project*

* Keyboard Maintainer: [Jacky](https://github.com/jackyjia73)
* Hardware Supported: *GD32F303*
* Hardware Availability: *www.i-chip.cn*

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb smart/smart80 -km default

Flashing example for this keyboard:

    qmk flash -kb smart/smart80 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available




# 智芯云 QMK 固件

采用智芯云（i-chip)为QMK定制的芯片套件，实现USB,BLE,2.4G三模键盘。

* 维护支持: [Jacky](https://github.com/JackyJia73/qmk_firmware) ，[智芯云](http://www.i-chip.cn/)

## 烧录
1. 按住ESC，插上USB接口。
2. 点击电脑弹出窗口，按网页提示选择正确bin文件烧录。  
