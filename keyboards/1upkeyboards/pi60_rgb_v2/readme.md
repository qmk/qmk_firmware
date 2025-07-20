# 1up pi60 rgb v2

![1up pi60 rgb v2](https://i.imgur.com/H1tRGZh.png)

The pi60 RGB v2 is a 60% pcb from 1upkeyboards. This keyboard features an ANSI layout hot swap PCB with per-key in-switch RGB lighting as well as RGB underglow. The controller is a Raspberry Pi rp2040 microcontroller.

* Keyboard Maintainer: [ziptyze](https://github.com/ziptyze)

Make example for this keyboard (after setting up your build environment):

    make 1upkeyboards/pi60_rgb_v2:default

Flashing example for this keyboard:

    make 1upkeyboards/pi60_rgb_v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Bootloader button**: Hold the button on the back of the PCB and plug in the keyboard
