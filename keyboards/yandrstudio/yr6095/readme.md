# yr6095

> This is only for the wired-only PCB, not the tri-mode PCB.

![yr6095](https://i.imgur.com/k2SVb94h.png)

A 60% multi-layout keyboard (there are 95 keys in total) with 1 RGB in capslock key.
This keyboard use 16mhz HSE and APM32F103CBT6(STM32F103CBT6) as MCU.

- Keyboard Maintainer: https://github.com/jiaxin96
- Hardware Supported: yr6095
- Hardware Availability:
  - Keebox60 R2 PCB - [Keebox Store](https://keebox.store/products/keebox60-r2-pcb) / [Taobao](https://item.taobao.com/item.htm?id=800145163764)

Make example for this keyboard (after setting up your build environment):

    make yandrstudio/yr6095:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

Enter the bootloader in 2 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
