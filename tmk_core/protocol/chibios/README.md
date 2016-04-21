## TMK running on top of ChibiOS

This code can be used to run TMK keyboard logic on top of [ChibiOS], meaning that you can run TMK on whatever [ChibiOS] supports. The notable examples are ARM-based Teensies (3.x and LC) and on the boards with STM32 MCUs.

### Usage

- To use, unpack or symlink [ChibiOS] to `tmk_core/tool/chibios/chibios`. For Kinetis support (this means Teensies, Infinity keyboard, WhiteFox keyboard), you'll need a fork which implements the USB driver, e.g. [this one](https://github.com/flabbergast/ChibiOS/tree/kinetis).
- You will also need to install an ARM toolchain, for instance from [here](https://launchpad.net/gcc-arm-embedded). On linux, this is usually also present as a package for your distribution (as `gcc-arm` or something similar). On OS X, you can use [homebrew](http://brew.sh/) with an appropriate tap.

### Notes

- Some comments about ChibiOS syntax and the most commonly used GPIO functions are, as well as an example for ARM Teensies, is [here](https://github.com/tmk/tmk_keyboard/blob/master/keyboard/teensy_lc_onekey/instructions.md).
- For gcc options, inspect `tmk_core/tool/chibios/chibios.mk`. For instance, I enabled `-Wno-missing-field-initializers`, because TMK common bits generated a lot of warnings on that.
Also pay attention to `-O0` (enabled for debugging); for deployment use `-O2`.
- USB string descriptors are messy. I did not find a way to cleanly generate the right structures from actual strings, so the definitions in individual keyboards' `config.h` are ugly as heck.
- It is easy to add some code for testing (e.g. blink LED, do stuff on button press, etc...) - just create another thread in `main.c`, it will run independently of the keyboard business.
- Jumping to (the built-in) bootloaders on STM32 works, but it is not entirely pleasant, since it is very much MCU dependent. So, one needs to dig out the right address to jump to, and either pass it to the compiler in the `Makefile`, or better, define it in `<your_kb>/bootloader_defs.h`. An additional startup code is also needed; the best way to deal with this is to define custom board files. (Example forthcoming.)

### Experimental pre-ChibiOS 4 support
- As an alternative to the mentioned flabbergast branch above, you can use the [master branch of ChibiOS](https://github.com/ChibiOS/ChibiOS). 
- Note that the Kinetis support has moved to the [ChibiOS-Contrib repository](https://github.com/ChibiOS/ChibiOS-Contrib), so you need to put that into your repository in the same way as you did for the main ChibiOS repository. 
- You also need to define CHIBIOS_CONTRIB in your makefile and point it to the right directory.
- You need to add some new options to chconf.h, or you will get compiler errors. Just copy the new options from samples provided by the ChibiOS-Contrib repository.

### Immediate todo

- power saving for suspend

### Not tested, but possibly working

- backlight

### Missing / not working (TMK vs ChibiOS bits)

- eeprom / bootmagic for STM32 (will be chip dependent; eeprom needs to be emulated in flash, which means less writes; wear-levelling?) There is a semi-official ST "driver" for eeprom, with wear-levelling, but I think it consumes a lot of RAM (like 2 pages, i.e. 1kB or so).

### Tried with

- Infinity, WhiteFox keyboards
- all ARM-based Teensies
- some STM32-based boards (e.g. ST-F072RB-DISCOVERY board, STM32F042 breakout board, Maple Mini (STM32F103-based))

## ChibiOS-supported MCUs

- Pretty much all STM32 chips.
- There is some support for K20x and KL2x Freescale chips (i.e. Teensy 3.x/LC, mchck, FRDM-KL2{5,6}Z, FRDM-K20D50M), but again, no official USB stack yet. However the `kinetis` branch of [flabbergast's ChibiOS fork](https://github.com/flabbergast/ChibiOS). With this fork, TMK work normally on all the ARM Teensies.
- There is also support for AVR8, but the USB stack is not implemented for them yet, and also the kernel itself takes about 1k of RAM. I think people managed to get ChibiOS running on atmega32[8p/u4] though.
- I've seen community support for Nordic NRF51822 (the chip in Adafruit's Bluefruit bluetooth-low-energy boards), but not sure about the extent.

## STM32-based keyboard design considerations

- STM32F0x2 chips can do crystal-less USB, but they still need a 3.3V voltage regulator.
- The BOOT0 pin should be tied to GND.
- For a hardware way of accessing the in-built DFU bootloader, in addition to the reset button, put another button between the BOOT0 pin and 3V3.



[ChibiOS]: http://chibios.org
