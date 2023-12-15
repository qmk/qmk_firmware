# Pila87 / XM87 Pro

![Pila87](https://i.imgur.com/rLLJemMh.jpg)

A TKL keyboard made by 小淼外设 (Phage Studio), which controlled by an CKS32F103RBT6 (clone STM32F103RBT6) chipset. The keyboard features per-key RGB, 3 external RGB underglow ports.

* Keyboard Maintainer: Phage Studio
* Hardware Supported: CKS32F103RBT6 (clone STM32F103RBT6)
* Hardware Availability: From 小淼外设 on Taobao

Make example for this keyboard (after setting up your build environment):

    make phage_studio/pila87:default

Flashing example for this keyboard:

    make phage_studio/pila87:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Warning

Before using this QMK firmware, you need these thing below:

* 1 Quartz Crystal (SMD 3225) 8 Mhz
* 2 Capacitor 0603 18pF (or 22pF)
* 1 ST-Link v2 to connect SWD and flash STM32duino (Maple 003). If you don't know how to flash, please read this guide: [Click here](https://github.com/qmk/qmk_firmware/blob/master/docs/isp_flashing_guide.md#flashing-stm32duino-bootloader)

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (B key) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
