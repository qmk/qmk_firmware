# Gray Studio Aero 75

![Gray Studio Aero 75](https://graystudio.site/wp-content/uploads/2022/09/aero75-png-1024x442.png)

A 75% keyboard featuring an anodized aluminum case around a gasket-mounted, flex-cut PCB.

* Keyboard Maintainer: [edwardslau](https://github.com/edwardslau)
* Hardware Supported: Aero 75 Hotswap (STM32F103)
  * Aero 75 Soldered version is **not currently supported**.
* Hardware Availability: [GrayStudio](https://graystudio.site/en/aero75/)

Make example for this keyboard (after setting up your build environment):

    make gray_studio/aero75:default

Flashing example for this keyboard:

    make gray_studio/aero75:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top-left key (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (top-right on the Function layer by default)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
