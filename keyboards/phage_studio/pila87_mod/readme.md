# Pila87 / XM87 Pro (Modding version)

![Pila87](https://i.imgur.com/rLLJemMh.jpg)

This is the Pila87 / XM87 Pro made by the Phage Studio

* Keyboard Maintainer: [HorrorTroll](https://github.com/HorrorTroll)
* Hardware Supported: Pila87 / XM87 Pro
* Hardware Availability: From 小淼外设 on Taobao

**Bootloader:**
```
Make sure to flash STM32duino (Maple 003) first:
- First way: Press FN + Esc at the same times on user mode
- Second way: Hold B key and plug in USB cable
- Third way: Hold Esc key and plug in USB cable (this way will reset EEPROM)
```
**Warning:**
```
Before using this QMK firmware, you need these thing below:
- 1 Quartz Crystal (SMD 3225) 8 Mhz
- 2 Capacitor 0603 18pF (or 22pF)
- 1 ST-Link v2 to connect SWD and flash jumploader
```
Make example for this keyboard (after setting up your build environment):

    make phage_studio/pila87_mod:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).