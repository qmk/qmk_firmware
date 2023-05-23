# DT40

![DT40](http://semitek.oss-cn-hangzhou.aliyuncs.com/qmk_imaging%2Fdt40%20layout05192023.jpg?OSSAccessKeyId=ogxQdo6geQXQVIK5&Expires=1684576837&Signature=GUNgvZ5GDL9uZY6CfpKYN1KvsJk%3D)

## The PCB features:
* QMK & VIA compatibility
* RGB Matrix backlight
* Thin body & Simple keys


The following is the QMK Firmware for the Destop 40% keylayout -  designed in Dongguan Jizhi Electronic Technology Co., Ltd
* Keyboard Maintainer: [JZ-Skyloong](https://github.com/JZ-Skyloong)
* Hardware Supported: DestopPCB for Skyloong keylayout 40%, STM32F103C8T6
* Hardware Availability: http://www.skyloong.com.cn

Make example for this keyboard (after setting up your build environment):

    make skyloong/dt40:default
    make skyloong/dt40:via

Flashing example for this keyboard:

    make skyloong/dt40:default:flash
    make skyloong/dt40:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
