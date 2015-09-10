## TMK running on top of ChibiOS

### Notes

- To use, unpack or symlink [ChibiOS] {currently 3.0.1} to `tmk_core/tool/chibios/chibios`.
- For gcc options, inspect `tmk_core/tool/chibios/chibios.mk`. For instance, I enabled `-Wno-missing-field-initializers`, because TMK common bits generated a lot of warnings on that.
Also pay attention to `-O0` (enabled for debugging); for deployment use `-O2`.
- USB string descriptors are messy. I did not find a way to cleanly generate the right structures from actual strings, so the definitions in individual keyboards' `config.h` are ugly as heck.
- There are some random constants left so far, e.g. 5ms sleep between calling `keyboard_task`, or 1.5sec wait for USB init, in `main.c`. There should be no such in `usb_main.c` (the main USB stack). Everything is based on timers/interrupts/kernel scheduling (well except `keyboard_task`), so no periodically called things (again, except `keyboard_task`, which is just how TMK is designed).
- It is easy to add some code for testing (e.g. blink LED, do stuff on button press, etc...) - just create another thread in `main.c`, it will run independently of the keyboard business.
- Jumping to bootloader works, but it is not entirely pleasant, since it is very much MCU dependent. The code is now geared towards STM32 chips and their built-in bootloaders. So, one needs to dig out the right address to jump to, and pass it to the compiler in the `Makefile`. Also, a patch to upstream ChibiOS is needed (supplied), because it `ResetHandler` needs adjusting.
- Sleep LED works, but at the moment only on/off, i.e. no breathing.
- The USB stack works pretty completely; however there are bits of other TMK stuff that are not done yet:

### Immediate todo

- host-wakeup packet sending during suspend
- power saving for suspend?
- PWM for sleep led

### Not tested, but possibly working

- backlight

### Missing / not working (TMK vs ChibiOS bits)

- eeprom / bootmagic (will be chip dependent; eeprom needs to be emulated in flash, which means less writes; wear-levelling?) There is a semi-official ST "driver" for eeprom, with wear-levelling, but I think it consumes a lot of RAM (like 2 pages, i.e. 1kB or so).

### Tried with

- ChibiOS 3.0.1 and ST F072RB DISCOVERY board.
- Need to test on other STM32 chips (F3, F4) to make it as much chip-independent as possible.

## STM32-based keyboard design considerations

- STM32F0x2 chips can do crystal-less USB, but they still need a 3.3V voltage regulator.
- The BOOT0 pin should be tied to GND.
- For a hardware way of accessing the in-built DFU bootloader, in addition to the reset button, put another button between the BOOT0 pin and 3V3.
- For breathing the caps lock LED during the suspended state ("sleep LED"), it is desirable to have that LED on a hardware PWM pin (there's usually plenty of those, look for TIMERs in the datasheet).

## ChibiOS-supported MCUs (as of 3.0.1)

- Pretty much all STM32 chips.
- There is also support for AVR8, but the USB stack is not implemented for them yet, and also the kernel itself takes about 1k of RAM. I think people managed to get ChibiOS running on atmega32[8p/u4] though.
- There is some support for K20 and KL25 Freescale chips (i.e. Teensy 3.0, mchck, FRDM-KL25Z, FRDM-K20D50M), but again, no USB stack yet.
- I've seen community support for Nordic NRF51822 (the chip in Adafruit's Bluefruit bluetooth-low-energy boards), but not sure about the extent.



[ChibiOS]: http://chibios.org
