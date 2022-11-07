# CC67

A 65% keyboard made by XCStore, which controlled by an STM32F401xC (probably not genuine) chipset. The keyboard features per-key RGB, RGB underglow.

* Keyboard Maintainer: XCStore
* Hardware Supported: STM32F401xC (probably not genuine)
* Hardware Availability: From XCStore on Taobao

Make example for this keyboard (after setting up your build environment):

    make xcstore/cc67:default

Flashing example for this keyboard:

    make xcstore/cc67:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Warning

Due to using PA10 as GPIO, built-in STM32 DFU from USB doesn't working normally. So before using this QMK firmware, you need to do these thing below:

* Grab an ST-Link and hook up into SWD from PCB
* Download this: [TinyUF2 binary](https://github.com/HorrorTroll/tinyuf2/blob/stm32f401_8mhz/ports/stm32f4/build/stm32f401ce_discovery/tinyuf2-stm32f401ce_discovery.bin)
* Using any flash tool that support ST-Link. Connect ST-Link, then do full chip erase and then flash TinyUF2 binary
* Wait for it done and disconnect ST-Link.
* Then plug USB from PCB to PC, now it should pop up a new disk drive.
* Compile firmware, drag & drop your compile file into UF2 disk drive.
* Done! Your PCB should boot up your compile firmware.

Not only that, PA9 is using as GPIO too. So it need a custom matrix for disable VBUS sensing on USB OTG

## Bootloader

Enter the bootloader in 2 ways (only work if you flash TinyUF2 correctly):

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
