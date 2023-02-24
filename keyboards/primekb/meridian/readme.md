# ai03 x PrimeKB Meridian

![Meridian](https://i.imgur.com/c90ZTJJl.jpg)

* Keyboard Maintainer: [Holten Campbell](https://github.com/holtenc)
* Hardware Supported: STM32F072CBT6

## Compiling firmware and flashing

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: hold down the key at (0,0) in the matrix (usually Escape) and plug in the keyboard; or
* **Physical reset button**: press the button on the bottom of the PCB; or
* **Keycode in layout**: press the key mapped to `QK_BOOT` if it is available (Escape key on layer 1 in the default layout).

### Compile firmware

The Meridian PCB was delivered in two variants, equal in design but using different RGB LED models: one using WS2812 and another using KTR1010 LEDs. Both can be compiled using

    make primekb/meridian/ws1812:default
    make primekb/meridian/ktr1010:default

After compiling, enter bootloader in the PCB and flash the firmware using `dfu-util` or QMK Toolbox. For direct compile-and-flashing, put the PCB in DFU state and use

    make primekb/meridian/ws1812:default:flash
    make primekb/meridian/ktr1010:default:flash

VIA-supported firmwares are also available.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
