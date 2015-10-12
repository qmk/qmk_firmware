## TMK running on top of ChibiOS

### Notes

- To use, unpack or symlink [ChibiOS] {currently 3.0.2} to `tmk_core/tool/chibios/chibios`. For Kinetis support, you'll need a fork which implements the USB driver, e.g. [this one](https://github.com/flabbergast/ChibiOS/tree/kinetis).
- For gcc options, inspect `tmk_core/tool/chibios/chibios.mk`. For instance, I enabled `-Wno-missing-field-initializers`, because TMK common bits generated a lot of warnings on that.
Also pay attention to `-O0` (enabled for debugging); for deployment use `-O2`.
- USB string descriptors are messy. I did not find a way to cleanly generate the right structures from actual strings, so the definitions in individual keyboards' `config.h` are ugly as heck.
- There are some random constants left so far, e.g. 5ms sleep between calling `keyboard_task`, or 1.5sec wait for USB init, in `main.c`. There should be no such in `usb_main.c` (the main USB stack). Everything is based on timers/interrupts/kernel scheduling (well except `keyboard_task`), so no periodically called things (again, except `keyboard_task`, which is just how TMK is designed).
- It is easy to add some code for testing (e.g. blink LED, do stuff on button press, etc...) - just create another thread in `main.c`, it will run independently of the keyboard business.
- Jumping to (the built-in) bootloaders on STM32 works, but it is not entirely pleasant, since it is very much MCU dependent. So, one needs to dig out the right address to jump to, and either pass it to the compiler in the `Makefile`, or better, define it in `<your_kb>/bootloader_defs.h`. Also, a patch to upstream ChibiOS is needed (supplied), because it `ResetHandler` needs adjusting.
- Sleep LED works, but at the moment only on/off, i.e. no breathing.

### Immediate todo

- host-wakeup packet sending during suspend
- power saving for suspend?
- PWM for sleep led

### Not tested, but possibly working

- backlight

### Missing / not working (TMK vs ChibiOS bits)

- eeprom / bootmagic for STM32 (will be chip dependent; eeprom needs to be emulated in flash, which means less writes; wear-levelling?) There is a semi-official ST "driver" for eeprom, with wear-levelling, but I think it consumes a lot of RAM (like 2 pages, i.e. 1kB or so).

### Tried with

- ChibiOS 3.0.1, 3.0.2 and ST F072RB DISCOVERY board.
- Need to test on other STM32 chips (F3, F4) to make it as much chip-independent as possible.
- ChibiOS with Kinetis patches and Teensy LC and 3.0.

## ChibiOS-supported MCUs (as of 3.0.2)

- Pretty much all STM32 chips.
- There is some support for K20x and KL2x Freescale chips (i.e. Teensy 3.x/LC, mchck, FRDM-KL2{5,6}Z, FRDM-K20D50M), but again, no official USB stack yet. However the `kinetis` branch of [my ChibiOS fork](https://github.com/flabbergast/ChibiOS). With this fork, TMK work normally on all the ARM Teensies.
- There is also support for AVR8, but the USB stack is not implemented for them yet, and also the kernel itself takes about 1k of RAM. I think people managed to get ChibiOS running on atmega32[8p/u4] though.
- I've seen community support for Nordic NRF51822 (the chip in Adafruit's Bluefruit bluetooth-low-energy boards), but not sure about the extent.

## STM32-based keyboard design considerations

- STM32F0x2 chips can do crystal-less USB, but they still need a 3.3V voltage regulator.
- The BOOT0 pin should be tied to GND.
- For a hardware way of accessing the in-built DFU bootloader, in addition to the reset button, put another button between the BOOT0 pin and 3V3.
- For breathing the caps lock LED during the suspended state ("sleep LED"), it is desirable to have that LED on a hardware PWM pin (there's usually plenty of those, look for TIMERs in the datasheet). However this is not strictly necessary, because instead of direct output of a timer to a pin (better of course), it is easy to define timer callbacks in ChibiOS that turn on/off an arbitrary pin.



[ChibiOS]: http://chibios.org
