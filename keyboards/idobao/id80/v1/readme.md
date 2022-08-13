# IDOBAO ID80

![ID80](https://i.imgur.com/977ENjph.png)

A 75% hotswap keyboard from IDOBAO.

* Keyboard Maintainer: [Sergey Vlasov](https://github.com/sigprof)
* Hardware Supported: IDOBAO ID80
* Hardware Availability: [Drop](https://drop.com/buy/idobao-id80-75-hot-swappable-mechanical-keyboard-kit?mode=guest_open)

---
> &#x26a0; **Please note:** The source folder for this keyboard has moved to `../v2`.
---

Make example for this keyboard (after setting up your build environment):

    make idobao/id80/v2:default BACKLIGHT_ENABLE=no
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Escape key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
