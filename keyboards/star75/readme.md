# 大星外设 DXWS Star75

75% Hotswap PCB with optional rotary encoder.

![View of Star75 Keyboard](https://i.imgur.com/UrvnjiZ.jpeg)
![Star75 Default Layout](https://i.imgur.com/LkTP0Cj.png)

* Keyboard Maintainer: QMK Community
* Hardware Supported: Star75 1.2mm Flex-cut Hotswap PCB
* Hardware Availability: [大星外设](https://item.taobao.com/item.htm?id=656392112467)

Make example for this keyboard (after setting up your build environment):

    make star75:default

Flashing example for this keyboard:

    make star75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

